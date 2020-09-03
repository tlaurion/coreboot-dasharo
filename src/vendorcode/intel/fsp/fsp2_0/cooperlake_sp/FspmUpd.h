/** @file

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

  This file is automatically generated. Please do NOT modify !!!

**/

#ifndef __FSPMUPD_H__
#define __FSPMUPD_H__

#include <FspUpd.h>

/*
 * Intel CPX-SP FSP has been using FSPM_CONFIG intead of FSP_M_CONFIG.
 * Other Intel FSPs have been using FSP_M_CONFIG. The feedback from Intel
 * is that they will converge to use FSPM_CONFIG over time. So both will
 * co-exist for some time. Today coreboot common code expects FSP_M_CONFIG.
 */
#define FSP_M_CONFIG	FSPM_CONFIG

#define SPEED_REC_96GT      0
#define SPEED_REC_104GT     1
#define ADAPTIVE_CTLE 	    0x3f

#define CPXSP_2S6KTI_EPARAM_TABLE \
        /* Socket 0  */                                                                                       \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK0), 0x2C33383F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK1), 0x2B35353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK2), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK3), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK4), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK5), 0x2C35363F, ADAPTIVE_CTLE},   \
        /* Socket 1 */                                                                                        \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK0), 0x2C33383F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK1), 0x2B35353F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK2), 0x2D35373F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK3), 0x2D35373F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK4), 0x2A2F3A3F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK5), 0x2C35363F, ADAPTIVE_CTLE}

#define CPXSP_2S6KTI_EPARAM_TABLE_COUNT 12 // NOTE - needs to match number of elements in CPXSP_2S6KTI_EPARAM_TABLE


#pragma pack(1)

typedef struct {
	UINT8  SocketID;
	UINT8  Freq;
	UINT32 Link;
	UINT32 AllLanesTXEQ;
	UINT8  CTLEPEAK;
} ALL_LANES_EPARAM_LINK_INFO;

typedef enum {
	KTI_LINK0 =  0x0,
	KTI_LINK1,
	KTI_LINK2,
	KTI_LINK3,
	KTI_LINK4,
	KTI_LINK5
} KTI_LOGIC_LINK;

#define IIO_BIFURCATE_xxxxxxxx          0xFE
#define IIO_BIFURCATE_x4x4x4x4          0x0
#define IIO_BIFURCATE_x4x4xxx8          0x1
#define IIO_BIFURCATE_xxx8x4x4          0x2
#define IIO_BIFURCATE_xxx8xxx8          0x3
#define IIO_BIFURCATE_xxxxxx16          0x4
#define IIO_BIFURCATE_x2x2x4x8          0x5
#define IIO_BIFURCATE_x4x2x2x8          0x6
#define IIO_BIFURCATE_x8x2x2x4          0x7
#define IIO_BIFURCATE_x8x4x2x2          0x8
#define IIO_BIFURCATE_x2x2x4x4x4        0x9
#define IIO_BIFURCATE_x4x2x2x4x4        0xA
#define IIO_BIFURCATE_x4x4x2x2x4        0xB
#define IIO_BIFURCATE_x4x4x4x2x2        0xC
#define IIO_BIFURCATE_x2x2x2x2x8        0xD
#define IIO_BIFURCATE_x8x2x2x2x2        0xE
#define IIO_BIFURCATE_x2x2x2x2x4x4      0xF
#define IIO_BIFURCATE_x2x2x4x2x2x4      0x10
#define IIO_BIFURCATE_x2x2x4x4x2x2      0x11
#define IIO_BIFURCATE_x4x2x2x2x2x4      0x12
#define IIO_BIFURCATE_x4x2x2x4x2x2      0x13
#define IIO_BIFURCATE_x4x4x2x2x2x2      0x14
#define IIO_BIFURCATE_x2x2x2x2x2x2x4    0x15
#define IIO_BIFURCATE_x2x2x2x2x4x2x2    0x16
#define IIO_BIFURCATE_x2x2x4x2x2x2x2    0x17
#define IIO_BIFURCATE_x4x2x2x2x2x2x2    0x18
#define IIO_BIFURCATE_x2x2x2x2x2x2x2x2  0x19
#define IIO_BIFURCATE_AUTO              0xFF

typedef struct {
	UINT8 Socket;
	UINT8 IouNumber;
	UINT8 Bifurcation;
} UPD_IIO_BIFURCATION_DATA_ENTRY;

typedef enum {
        Iio_Socket0 = 0,
        Iio_Socket1,
        Iio_Socket2,
        Iio_Socket3,
        Iio_Socket4,
        Iio_Socket5,
        Iio_Socket6,
        Iio_Socket7
} IIO_SOCKETS;

typedef enum {
        Iio_Iou0 = 0,
        Iio_Iou1,
        Iio_Iou2,
        Iio_Iou3,
        Iio_Mcp0,
        Iio_Mcp1,
        Iio_IouMax
} IIO_IOUS;

/** FSP-M Configuration
**/
typedef struct {

/** Offset 0x0040 - Customer Revision
  The Customer can set this revision string for their own purpose.
**/
  UINT8                       CustomerRevision[32];

/** Offset 0x0060 - Bus Ratio
  Indicates the ratio of Bus/MMIOL/IO resource to be allocated for each CPU's IIO
**/
  UINT8                       BusRatio[8];

/** Offset 0x0068 - D2K Credit Config
  Set the D2K Credit Config
  1:Min, 2:Med, 3:Max
**/
  UINT8                       D2KCreditConfig;

/** Offset 0x0069 - Snoop Throttle Config
  Set the Snoop Throttle Config
  0:DIS, 1:Min, 2:Med, 3:Max
**/
  UINT8                       SnoopThrottleConfig;

/** Offset 0x006A - Legacy VGA Soc
  Socket that claims the legacy VGA range
**/
  UINT8                       LegacyVgaSoc;

/** Offset 0x006B - Legacy VGA Stack
  Stack that claims the legacy VGA range
**/
  UINT8                       LegacyVgaStack;

/** Offset 0x006C - Pcie P2P Performance Mode
  Determine if to enable PCIe P2P Performance Mode
  $EN_DIS
**/
  UINT8                       P2pRelaxedOrdering;

/** Offset 0x006D - Debug Print Level
  Set Debug Print Level
  1:Fatal, 2:Warning, 4:Summary, 8:Detail, 0x0F:All
**/
  UINT8                       DebugPrintLevel;

/** Offset 0x006E - SNC
  Enable or Disable SNC
  $EN_DIS
**/
  UINT8                       SncEn;

/** Offset 0x006F - UMA Clustering
  Set UMA Clusters
  0:Disable, 2:Two Clusters, 4:Four Clusters
**/
  UINT8                       UmaClustering;

/** Offset 0x0070 - IODC Mode
  IODC Setup Option
  0:Disable, 1:Auto, 2:Push, 3:AllocFlow 4:NonAlloc, 5:WCILF
**/
  UINT8                       IoDcMode;

/** Offset 0x0071 - Degrade Precedence
  Setup Degrade Precedence
  0:Topology, 1:Feature
**/
  UINT8                       DegradePrecedence;

/** Offset 0x0072 - Degrade 4 Socket Preference
  Setup Degrade 4 Socket Preference
  0:Fully Connect, 1:Dual Link Ring
**/
  UINT8                       Degrade4SPreference;

/** Offset 0x0073 - Directory Mode
  Enable or Disable Directory Mode
  $EN_DIS
**/
  UINT8                       DirectoryModeEn;

/** Offset 0x0074 - XPT Prefetch Enable
  Enable or Disable XPT Prefetch
**/
  UINT8                       XptPrefetchEn;

/** Offset 0x0075 - KTI Prefetch Enable
  Enable or Disable KTI Prefetch
  $EN_DIS
**/
  UINT8                       KtiPrefetchEn;

/** Offset 0x0076 - XPT Remote Prefetch Enable
  Enable or Disable XPT Remote Prefetch Enable
  $EN_DIS
**/
  UINT8                       XptRemotePrefetchEn;

/** Offset 0x0077 - KTI FPGA
  Enable or Disable KTI FPGA
  $EN_DIS
**/
  UINT8                       KtiFpgaEnable[8];

/** Offset 0x007F - DDRT QoS Mode
  Setup DDRT QoS
**/
  UINT8                       DdrtQosMode;

/** Offset 0x0080 - KTI Link Speed Mode
  Choose KTI Link Speed Mode
**/
  UINT8                       KtiLinkSpeedMode;

/** Offset 0x0081 - KTI Link Speed
  Setup KTI Link Speed
**/
  UINT8                       KtiLinkSpeed;

/** Offset 0x0082 - KTI Link L0p
  Enable or Disable KTI Link L0p
**/
  UINT8                       KtiLinkL0pEn;

/** Offset 0x0083 - KTI Link L1
  Enable or Disable KTI Link L1
**/
  UINT8                       KtiLinkL1En;

/** Offset 0x0084 - KTI Failover
  Enable or Disable KTI Failover
**/
  UINT8                       KtiFailoverEn;

/** Offset 0x0085 - KTI LB Enable
  Enable or Disable KTI LB
  $EN_DIS
**/
  UINT8                       KtiLbEn;

/** Offset 0x0086 - KTI CRC Mode
  Select KTI CRC Mode
  0:16bit, 1:32bit, 2:Auto
**/
  UINT8                       KtiCrcMode;

/** Offset 0x0087 - KTI CPU Socket Hotplug
  Enable or Disable KTI CPU Socket Hotplug
  $EN_DIS
**/
  UINT8                       KtiCpuSktHotPlugEn;

/** Offset 0x0088 - KTI CPU Socket HotPlug Topology
  Select KTI CPU Socket HotPlug Topology
  0:4Socket, 1:8Socket
**/
  UINT8                       KtiCpuSktHotPlugTopology;

/** Offset 0x0089 - KTI SKU Mismatch Check
  Enable or Disable KTI SKU Mismatch Check
  $EN_DIS
**/
  UINT8                       KtiSkuMismatchCheck;

/** Offset 0x008A - IRQ Threshold
  Select IRQ Threshold
  0:Disable, 1:Auto, 2:Low, 3:Medium, 4:High
**/
  UINT8                       IrqThreshold;

/** Offset 0x008B - IRQ Threshold
  Enable or Disable
  0:Disable, 1:Auto, 2:Low, 3:Medium, 4:High
**/
  UINT8                       TorThresLoctoremNorm;

/** Offset 0x008C - TOR threshold - Loctorem threshold empty
  Select TOR threshold - Loctorem threshold empty
  0:Disable, 1:Auto, 2:Low, 3:Medium, 4:High
**/
  UINT8                       TorThresLoctoremEmpty;

/** Offset 0x008D - MBA BW Calibration
  MBA BW Calibration setting
  0:Linear, 1:Biased, 2:Legacy, 3:Auto
**/
  UINT8                       MbeBwCal;

/** Offset 0x008E - TSC Sync in Sockets
  Enable or Disable TSC Sync in Sockets
**/
  UINT8                       TscSyncEn;

/** Offset 0x008F - HA A to S directory optimization
  Enable or Disable HA A to S directory optimization
**/
  UINT8                       StaleAtoSOptEn;

/** Offset 0x0090 - LLC Deadline Allocation
  Enable or Disable LLC Deadline Allocation
  $EN_DIS
**/
  UINT8                       LLCDeadLineAlloc;

/** Offset 0x0091 - Split Lock
  Enable or Disable Split Lock
**/
  UINT8                       SplitLock;

/** Offset 0x0092 - MMCFG Base Address
  Setup MMCFG Base Address
  0:1G, 1:1.5G, 2:1.75G, 3:2G, 4:2.25G, 5:3G, 6:Auto
**/
  UINT8                       mmCfgBase;

/** Offset 0x0093 - MMCFG Size
  Select MMCFG Size
  0:64M, 1:128M, 2:256M, 3:512M, 4:1G, 5:2G, 6: Auto
**/
  UINT8                       mmCfgSize;

/** Offset 0x0094 - MMIO High Base Address
  MMIO High Base Address, a hex number for Bit[51:32]
**/
  UINT32                      mmiohBase;

/** Offset 0x0098 - CPU Physical Address Limit
  CPU Physical Address Limit
  0:Disable, 1:Enable
**/
  UINT8                       CpuPaLimit;

/** Offset 0x0099 - High Gap
  Enable or Disable High Gap
  $EN_DIS
**/
  UINT8                       highGap;

/** Offset 0x009A - MMIO High Size
  MMIO High Size, Number of 1GB contiguous regions to be assigned for MMIOH space
  per CPU.  Range 1-1024
**/
  UINT16                      mmiohSize;

/** Offset 0x009C - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT8                       isocEn;

/** Offset 0x009D - DCA
  Enable or Disable DCA
  $EN_DIS
**/
  UINT8                       dcaEn;

/** Offset 0x009E
**/
  UINT8                       UnusedUpdSpace0[2];

/** Offset 0x00A0 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      BoardTypeBitmask;

/** Offset 0x00A4 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      AllLanesPtr;

/** Offset 0x00A8 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      PerLanePtr;

/** Offset 0x00AC - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      AllLanesSizeOfTable;

/** Offset 0x00B0 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      PerLaneSizeOfTable;

/** Offset 0x00B4 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT32                      WaitTimeForPSBP;

/** Offset 0x00B8 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT8                       IsKtiNvramDataReady;

/** Offset 0x00B9 - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT8                       BoardId;

/** Offset 0x00BA - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT8                       WaSerializationEn;

/** Offset 0x00BB - } TYPE:{Combo
  Enable or Disable
  $EN_DIS
**/
  UINT8                       KtiInEnableMktme;

/** Offset 0x00BC - Usage type for Processor VmxEnable Function
  Processor VmxEnable Function, if enabled, the value is 0x01, if disabled, the value is 0x00
  $EN_DIS
**/
  UINT8                       VmxEnable;

/** Offset 0x00BD - Usage type for Processor X2apic Function
  Processor X2apic Function, if enabled, the value is 0x01, if disabled, the value is 0x00
**/
  UINT8                       X2apic;

/** Offset 0x00BE - Usage type for DDR frequency limit
  Processor X2apic Function, if enabled, the value is 0x01, if disabled, the value is 0x00
**/
  UINT8                       DdrFreqLimit;

/** Offset 0x00BF - Usage type for Memory Serial Debug Message Level
  Processor X2apic Function, if enabled, the value is 0x01, if disabled, the value is 0x00
**/
  UINT8                       serialDebugMsgLvl;

/** Offset 0x00C0 - IIO ConfigIOU0
  ConfigIOU[MAX_SOCKET][0]: MAX_SOCKET=8, 0x00:x4x4x4x4, 0x01:x4x4xxx8, 0x02:xxx8x4x4,
  0x03:xxx8xxx8, 0x04:xxxxxx16, 0xFF:AUTO
**/
  UINT8                       IioConfigIOU0[8];

/** Offset 0x00C8 - IIO ConfigIOU1
  ConfigIOU[MAX_SOCKET][1]: MAX_SOCKET=8, 0x00:x4x4x4x4, 0x01:x4x4xxx8, 0x02:xxx8x4x4,
  0x03:xxx8xxx8, 0x04:xxxxxx16, 0xFF:AUTO
**/
  UINT8                       IioConfigIOU1[8];

/** Offset 0x00D0 - IIO ConfigIOU2
  ConfigIOU[MAX_SOCKET][2]: MAX_SOCKET=8, 0x00:x4x4x4x4, 0x01:x4x4xxx8, 0x02:xxx8x4x4,
  0x03:xxx8xxx8, 0x04:xxxxxx16, 0xFF:AUTO
**/
  UINT8                       IioConfigIOU2[8];

/** Offset 0x00D8 - IIO ConfigIOU3
  ConfigIOU[MAX_SOCKET][3]: MAX_SOCKET=8, 0x00:x4x4x4x4, 0x01:x4x4xxx8, 0x02:xxx8x4x4,
  0x03:xxx8xxx8, 0x04:xxxxxx16, 0xFF:AUTO
**/
  UINT8                       IioConfigIOU3[8];

/** Offset 0x00E0 - IIO ConfigIOU4
  ConfigIOU[MAX_SOCKET][4]: MAX_SOCKET=8, 0x00:x4x4x4x4, 0x01:x4x4xxx8, 0x02:xxx8x4x4,
  0x03:xxx8xxx8, 0x04:xxxxxx16, 0xFF:AUTO
**/
  UINT8                       IioConfigIOU4[8];

/** Offset 0x00E8 - Usage type for IIO PCIE Config Table Ptr
  IIO PCIE Config Table Ptr
**/
  UINT32                      IioPcieConfigTablePtr;

/** Offset 0x00EC - Usage type for IIO PCIE Config Table Number
  IIO PCIE Config Table Number
**/
  UINT32                      IioPcieConfigTableNumber;

/** Offset 0x00F0 - Usage type for IIO PCIE Root Port Enable or Disable
  IIO PCH rootport, if port is enabled, the value is 0x01, if the port is disabled,
  the value is 0x00
**/
  UINT8                       IIOPcieRootPortEnable;

/** Offset 0x00F1 - Usage type for IIO DeEmphasis
  IIO DeEmphasis
**/
  UINT8                       DeEmphasis;

/** Offset 0x00F2 - Usage type for IIO PCIE Root Port link speed
  IIO root port link speed
**/
  UINT8                       IIOPciePortLinkSpeed;

/** Offset 0x00F3 - Usage type for IIO PCIE Root Port Max Payload
  IIO Root Port Max Payload
**/
  UINT8                       IIOPcieMaxPayload;

/** Offset 0x00F4 - Usage type for IIO DfxDnTxPreset
  IIO DfxDnTxPreset
**/
  UINT8                       DfxDnTxPreset;

/** Offset 0x00F5 - Usage type for IIO DfxRxPreset
  IIO DfxRxPreset
**/
  UINT8                       DfxRxPreset;

/** Offset 0x00F6 - Usage type for IIO DfxUpTxPreset
  IIO DfxUpTxPreset
**/
  UINT8                       DfxUpTxPreset;

/** Offset 0x00F7 - Usage type for IIO PcieCommonClock
  IIO PcieCommonClock
**/
  UINT8                       PcieCommonClock;

/** Offset 0x00F8 - Usage type for IIO NtbPpd
  IIO NtbPpd
**/
  UINT8                       NtbPpd;

/** Offset 0x00F9 - Usage type for IIO NtbBarSizeOverride
  IIO NtbBarSizeOverride
**/
  UINT8                       NtbBarSizeOverride;

/** Offset 0x00FA - Usage type for IIO NtbSplitBar
  IIO NtbSplitBar
**/
  UINT8                       NtbSplitBar;

/** Offset 0x00FB - Usage type for IIO NtbBarSizeImBar1
  IIO NtbBarSizeImBar1
**/
  UINT8                       NtbBarSizeImBar1;

/** Offset 0x00FC - Usage type for IIO NtbBarSizeImBar2
  IIO PNtbBarSizeImBar2
**/
  UINT8                       NtbBarSizeImBar2;

/** Offset 0x00FD - Usage type for IIO NtbBarSizeImBar2_0
  IIO PNtbBarSizeImBar2_0
**/
  UINT8                       NtbBarSizeImBar2_0;

/** Offset 0x00FE - Usage type for IIO NtbBarSizeImBar2_1
  IIO NtbBarSizeImBar2_1
**/
  UINT8                       NtbBarSizeImBar2_1;

/** Offset 0x00FF - Usage type for IIO NtbBarSizeEmBarSZ1
  IIO NtbBarSizeEmBarSZ1
**/
  UINT8                       NtbBarSizeEmBarSZ1;

/** Offset 0x0100 - Usage type for IIO NtbBarSizeEmBarSZ2
  IIO NtbBarSizeEmBarSZ2
**/
  UINT8                       NtbBarSizeEmBarSZ2;

/** Offset 0x0101 - Usage type for IIO NtbBarSizeEmBarSZ2_0
  IIO NtbBarSizeEmBarSZ2_0
**/
  UINT8                       NtbBarSizeEmBarSZ2_0;

/** Offset 0x0102 - Usage type for IIO NtbBarSizeEmBarSZ2_1
  IIO NtbBarSizeEmBarSZ2_1
**/
  UINT8                       NtbBarSizeEmBarSZ2_1;

/** Offset 0x0103 - Usage type for IIO NtbXlinkCtlOverride
  IIO NtbXlinkCtlOverride
**/
  UINT8                       NtbXlinkCtlOverride;

/** Offset 0x0104 - Usage type for IIO VT-D Function
  IIO VT-D Function, if supported, the value is 0x01, if not supported, the value is 0x00
**/
  UINT8                       VtdSupport;

/** Offset 0x0105 - Usage type for IIO Pcie Port Hide
  Hide or visible for IIO Pcie Port, 1 : Hide, 0 : Visible
**/
  UINT8                       PEXPHIDE;

/** Offset 0x0106 - Usage type for IIO Pcie Port Menu Hide
  Hide or visible for IIO Pcie Port Menu, 1 : Hide, 0 : Visible
**/
  UINT8                       HidePEXPMenu;

/** Offset 0x0107 - PchSirqMode
  Enable or Disable PchSirqMode
**/
  UINT8                       PchSirqMode;

/** Offset 0x0108 - PchAdrEn
  Enable or Disable PchAdr
**/
  UINT8                       PchAdrEn;

/** Offset 0x0109 - ThermalDeviceEnable
  Enable or Disable ThermalDeviceEnable with PCI or ACPI mode
**/
  UINT8                       ThermalDeviceEnable;

/** Offset 0x010A - } TYPE:{Combo
  Root port swapping based on device connection status : TRUE or FALSE
  TRUE : 0x01, FALSE : 0x00
**/
  UINT8                       PchPcieRootPortFunctionSwap;

/** Offset 0x010B - PCH PCIE PLL Ssc
  Valid spread range : 0x00-0x14 (A value of 0 is SSC of 0.0%. A value of 20 is SSC
  of 2.0%), Auto : 0xFE(Set to hardware default), Disable : 0xFF
**/
  UINT8                       PchPciePllSsc;

/** Offset 0x010C - Usage type for PCH PCIE Root Port Index
  Index assigned to every PCH PCIE Root Port
**/
  UINT8                       PchPciePortIndex[20];

/** Offset 0x0120 - Usage type for PCH PCIE Root Port Enable or Disable
  0-19: PCH rootport, if port is enabled, the value is 0x01, if the port is disabled,
  the value is 0x00
**/
  UINT8                       PchPcieForceEnable[20];

/** Offset 0x0134 - Usage type for PCH PCIE Root Port Link Speed
  0-19: PCH rootport, 0x00 : Pcie Auto Speed, 0x01 : Pcie Gen1 Speed, 0x02 : Pcie
  Gen2 Speed, 0x03 : Pcie Gen3 Speed
**/
  UINT8                       PchPciePortLinkSpeed[20];

/** Offset 0x0148 - PchDciEn
  Enable or Disable Pch DciEn
**/
  UINT8                       PchDciEn;

/** Offset 0x0149 - SerialIoUartDebugEnable
  Enable SerialIo Uart debug library in FSP.
  0:Disable, 1:Enable
**/
  UINT8                       SerialIoUartDebugEnable;

/** Offset 0x014A - ISA Serial Base selection
  Select ISA Serial Base address could be initialized by boot loader. Default is 0x3F8
  0x3F8, 0x2F8
**/
  UINT16                      SerialIoUartDebugIoBase;

/** Offset 0x014C
**/
  UINT8                       ReservedMemoryInitUpd[16];
} FSPM_CONFIG;

/** Fsp M UPD Configuration
**/
typedef struct {

/** Offset 0x0000
**/
  FSP_UPD_HEADER              FspUpdHeader;

/** Offset 0x0020
**/
  FSPM_ARCH_UPD               FspmArchUpd;

/** Offset 0x0040
**/
  FSPM_CONFIG                 FspmConfig;

/** Offset 0x015C
**/
  UINT8                       UnusedUpdSpace1[2];

/** Offset 0x015E
**/
  UINT16                      UpdTerminator;
} FSPM_UPD;

#pragma pack()

#endif
