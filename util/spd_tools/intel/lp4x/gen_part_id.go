/* SPDX-License-Identifier: GPL-2.0-or-later */

package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"
)

/*
 * This program allocates DRAM strap IDs for different parts that are being used by the variant.
 *
 * It expects the following inputs:
 *  Pointer to SPD directory. This is the location where SPD files and SPD Manifest generated by
 *  gen_spd.go are placed.
 *  Pointer to Makefile directory. Makefile.inc generated by this program is placed in this
 *  location.
 *  Text file containing a list of memory parts names used by the board. Each line in the file
 *  is expected to have one memory part name.
 */
const (
	SPDManifestFileName = "spd_manifest.generated.txt"
	MakefileName = "Makefile.inc"
	DRAMIdFileName = "dram_id.generated.txt"
)

func usage() {
	fmt.Printf("\nUsage: %s <spd_dir> <makefile_dir> <mem_parts_used_file>\n\n", os.Args[0])
	fmt.Printf("   where,\n")
	fmt.Printf("   spd_dir = Directory path containing SPD files and manifest generated by gen_spd.go\n")
	fmt.Printf("   makefile_dir = Directory path where generated Makefile.inc should be placed\n")
	fmt.Printf("   mem_parts_used_file = File containing list of memory parts used by the board\n\n\n")
}

func checkArgs() error {

	for _, arg := range os.Args[1:] {
		if _, err := os.Stat(arg); err  != nil {
			return err
		}
	}

	return nil
}

/*
 * Read input file that contains list of memory part names used by the variant (one on a line)
 * and split into separate strings for each part name.
 */
func readParts(memPartsUsedFileName string) ([]string, error) {
	lines, err := ioutil.ReadFile(memPartsUsedFileName)
	if err != nil {
		return nil, err
	}
	str := string(lines)
	parts := strings.Split(str, "\n")

	return parts, nil
}

/*
 * Read SPD manifest file(CSV) generated by gen_spd program and generate two maps:
 * 1. Part to SPD Map : This maps global memory part name to generated SPD file name
 * 2. SPD to Index Map: This generates a map of deduplicated SPD file names to index assigned to
 *                      that SPD. This function sets index for all SPDs to -1. This index gets
 *                      updated as part of genPartIdInfo() depending upon the SPDs actually used
 *                      by the variant.
 */
func readSPDManifest(SPDDirName string) (map[string]string, map[string]int, error) {
	f, err := os.Open(filepath.Join(SPDDirName, SPDManifestFileName))
	if err != nil {
		return nil, nil, err
	}
	defer f.Close()
	r := csv.NewReader(f)

	partToSPDMap := make(map[string]string)
	SPDToIndexMap := make(map[string]int)

	for {
		fields, err := r.Read()

		if err == io.EOF {
			break
		}

		if err != nil {
			return nil, nil, err
		}

		if len(fields) != 2 {
			return nil, nil, fmt.Errorf("CSV file is incorrectly formatted")
		}

		partToSPDMap[fields[0]] = fields[1]
		SPDToIndexMap[fields[1]] = -1
	}

	return partToSPDMap, SPDToIndexMap, nil
}

/* Print information about memory part used by variant and ID assigned to it. */
func appendPartIdInfo(s *string, partName string, index int) {
	*s += fmt.Sprintf("%-30s %d (%04b)\n", partName, index, int64(index))
}

type partIds struct {
	SPDFileName string
	memParts string
}

/*
 * For each part used by variant, check if the SPD (as per the manifest) already has an ID
 * assigned to it. If yes, then add the part name to the list of memory parts supported by the
 * SPD entry. If not, then assign the next ID to the SPD file and add the part name to the
 * list of memory parts supported by the SPD entry.
 *
 * Returns list of partIds that contains spdFileName and supported memory parts for each
 * assigned ID.
 */
func genPartIdInfo(parts []string, partToSPDMap map[string]string, SPDToIndexMap map[string]int, makefileDirName string) ([]partIds, error) {
	partIdList := []partIds{}
	curId := 0
	var s string

	s += fmt.Sprintf("%-30s %s\n", "DRAM Part Name", "ID to assign")

	for _, p := range parts {
		if p == "" {
			continue
		}

		SPDFileName,ok := partToSPDMap[p]
		if !ok {
			return nil, fmt.Errorf("Failed to find part ", p, " in SPD Manifest. Please add the part to global part list and regenerate SPD Manifest")
		}

		index := SPDToIndexMap[SPDFileName]
		if index != -1 {
			partIdList[index].memParts += ", " + p
			appendPartIdInfo(&s, p, index)
			continue
		}

		SPDToIndexMap[SPDFileName] = curId

		appendPartIdInfo(&s, p, curId)
		entry := partIds{SPDFileName: SPDFileName, memParts: p}
		partIdList = append(partIdList, entry)

		curId++
	}

	fmt.Printf("%s", s)
	err := ioutil.WriteFile(filepath.Join(makefileDirName, DRAMIdFileName), []byte(s), 0644)

	return partIdList, err
}

var generatedCodeLicense string = "## SPDX-License-Identifier: GPL-2.0-or-later"
var autoGeneratedInfo string = "## This is an auto-generated file. Do not edit!!"

/*
 * This function generates Makefile.inc under the variant directory path and adds assigned SPDs
 * to SPD_SOURCES.
 */
func genMakefile(partIdList []partIds, makefileDirName string) error {
	var s string

	s += fmt.Sprintf("%s\n%s\n\n", generatedCodeLicense, autoGeneratedInfo)
	s += fmt.Sprintf("SPD_SOURCES =\n")

	for i := 0; i < len(partIdList); i++ {
		s += fmt.Sprintf("SPD_SOURCES += %s ", partIdList[i].SPDFileName)
		s += fmt.Sprintf("     # ID = %d(0b%04b) ", i, int64(i))
		s += fmt.Sprintf(" Parts = %04s\n", partIdList[i].memParts)
	}

	return ioutil.WriteFile(filepath.Join(makefileDirName, MakefileName), []byte(s), 0644)
}

func main() {
	if len(os.Args) != 4 {
		usage()
		log.Fatal("Incorrect number of arguments")
	}

	SPDDir, MakefileDir, MemPartsUsedFile := os.Args[1], os.Args[2], os.Args[3]

	partToSPDMap, SPDToIndexMap, err := readSPDManifest(SPDDir)
	if err != nil {
		log.Fatal(err)
	}

	parts, err := readParts(MemPartsUsedFile)
	if err != nil {
		log.Fatal(err)
	}

	partIdList, err := genPartIdInfo(parts, partToSPDMap, SPDToIndexMap, MakefileDir)
	if err != nil {
		log.Fatal(err)
	}

	if err := genMakefile(partIdList, MakefileDir); err != nil {
		log.Fatal(err)
	}
}
