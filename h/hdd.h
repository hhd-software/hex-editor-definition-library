// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma once

#include <stddefs.h>
#include <ntfs.h>

#pragma script("hdd_functions.js")

#define SectorSize 512
#define VblkStartSequenceNumber 4

public struct HDD_Header
{
	char Signature[8]; /* 0x00 */
	DWORD Revision; /* 0x08 */
	DWORD Size; /* 0x0c */
	DWORD CrcSelf; /* 0x10 */
	DWORD Reserved; /* 0x14 */
	QWORD LbaSelf; /* 0x18 */
	QWORD LbaAlt; /* 0x20 */
	QWORD LbaStart; /* 0x28 */
	QWORD LbaEnd; /* 0x30 */
	GUID Guid; /* 0x38 disk GUID */
	QWORD LbaTable; /* 0x48 */
	DWORD Entries; /* 0x50 */
	DWORD Entsz; /* 0x54 */
	DWORD CrcTable; /* 0x58 */
	unsigned char Padding[420]; /* 0x5c */
};

//struct gpt_hdr
//{
// char hdr_sig[8]; /* 0x00 */
//#define GPT_HDR_SIG "EFI PART"
// uint32_t hdr_revision; /* 0x08 */
//#define GPT_HDR_REVISION 0x00010000
// uint32_t hdr_size; /* 0x0c */
// uint32_t hdr_crc_self; /* 0x10 */
// uint32_t __reserved; /* 0x14 */
// uint64_t hdr_lba_self; /* 0x18 */
// uint64_t hdr_lba_alt; /* 0x20 */
// uint64_t hdr_lba_start; /* 0x28 */
// uint64_t hdr_lba_end; /* 0x30 */
// efi_guid_t hdr_guid; /* 0x38 disk GUID */
// uint64_t hdr_lba_table; /* 0x48 */
// uint32_t hdr_entries; /* 0x50 */
// uint32_t hdr_entsz; /* 0x54 */
// uint32_t hdr_crc_table; /* 0x58 */
// uint8_t padding[420]; /* 0x5c */
//} __attribute__((__packed__));

enum VblkType : BYTE
{
	VblkComponent = 0x32,
	VblkPartition = 0x33,
	VblkVolume = 0x51,
	VblkDisk1 = 0x34,
	VblkDisk2 = 0x44,
	VblkDiskGroup1 = 0x35,
	VblkDiskGroup2 = 0x45
};

enum VblkFileSystemType : BYTE
{
	VblkFsRawOrFat16 = 0x6,
	VblkFsNtfs = 0x7,
	VblkFsFat32 = 0xB
};

struct VblkHeader
{
#pragma byte_order(BigEndian)
	char Magic[4];
	DWORD SequenceNumber;
	DWORD GroupNumber;
	WORD RecordNumber;
	WORD NumberOfRecords;
#pragma byte_order(LittleEndian)
};

[display(format("{0}", Value))]
struct VblkValue
{
	BYTE Length;
	switch (Length)
	{
	case 1:
		BYTE Value;
		break;
	case 2:
		BYTE WORD;
		break;
	case 4:
		DWORD Value;
		break;
	case 8:
		QWORD Value;
		break;
	}
};

[display(format("{0}", String))]
struct VblkString
{
	BYTE Length;
	char String[Length];
};

enum ExtVblkFlags : BYTE
{
	ExtVblkOk,
	ExtVblkDeleted, //was deleted, but is still active
	ExtVblkCreated, //was created, but is not yet active
};

struct ExtendedVblk
{
#pragma byte_order(BigEndian)
	VblkHeader Header;
	WORD UpdateStatus;
	ExtVblkFlags Flags;
	VblkType Type;
	DWORD length; //length of useful data from otherData

	switch (Type)
	{
	case VblkComponent:
		struct VblkComponent
		{
			VblkValue Id;
			BYTE NameLength;
			char Name[NameLength];
			BYTE StateLength;
			char State[StateLength];
			BYTE Layout;
			DWORD Flags;
			VblkValue NumberOfPartitions;
			QWORD CommitTransactionId;
			QWORD Zero;
			VblkValue VolumeId; //QWORD
			VblkValue logsd; //QWORD

			if (Flags & 0x10)
			{
				VblkValue StripeSizeLba; //QWORD
				VblkValue NumberOfColumns; //QWORD
			}
		}component;
		break;
	case VblkPartition:
		struct VblkPartition
		{
			VblkValue ObjectId; //QWORD
			BYTE NameLength;
			char Name[NameLength];
			DWORD Flags;
			QWORD CommitTransactionId;
			QWORD DiskOffsetLba;
			QWORD PartitionOffsetInColumnLba;
			VblkValue SizeLba; //QWORD
			VblkValue ComponentId; //QWORD
			VblkValue DiskId; //QWORD
		   // VblkValue ComponentPartIndex;

			if (Flags & 0x08)
				VblkValue ColumnIndex; //QWORD

			if (Flags & 0x02)
				VblkValue HiddenSectorsCount; //QWORD
		}partition;
		break;
	case VblkVolume:
		struct VblkVolume
		{
			VblkValue objectId; //QWORD
			VblkString Name;
			VblkString Type;
			VblkString DisableDriveLetterAssignment;
			char State[14];
			char ReadPolicy;
			VblkValue volumeNumber; //QWORD
			DWORD Flags;
			VblkValue NumberOfComponents;
			QWORD CommitTransactionId;
			QWORD UnknownTransactionId;
			VblkValue Size; //QWORD
			BYTE Zeroes[4];
			VblkFileSystemType PartitionType;
			GUID guid;

			if (Flags & 0x08)
				VblkValue Id1; //QWORD

			if (Flags & 0x20)
				VblkValue Id2; //QWORD

			if (Flags & 0x80)
				VblkValue ColumnSizeLba; //QWORD

			if (Flags & 0x02)
				VblkString MountHint; //QWORD

				//var nPartitionOffset = GetPublicRegionStart() + ;

			switch (PartitionType)
			{
			case VblkFsRawOrFat16:
				break;
			case VblkFsNtfs:
				$bind("struct NTFS", "NTFS", 0x100000);
				break;
			case VblkFsFat32:
				break;
			}
		}volume;
		break;
	case VblkDisk1:
		struct VblkDisk1
		{
			VblkValue ObjectId; //QWORD
			VblkString Name;
			VblkString Guid;
			VblkString LastDeviceName;
			DWORD Flags;
			QWORD CommitTransactionId;
		}disk1;
		break;
	case VblkDisk2:
		struct VblkDisk2
		{
			VblkValue ObjectId; //QWORD
			VblkString Name;
			GUID Guid;
			GUID DiskSetGuid;
			VblkString LastDeviceName;
			DWORD Flags;
			QWORD CommitTransactionId;
		}disk2;
		break;
	case VblkDiskGroup1:
		struct VblkGroup1
		{
			VblkValue ObjectId; //QWORD
			VblkString Name;
			VblkString Guid;
			BYTE Zeroes[4];
			DWORD Flags; //TODO: check flags field
			QWORD CommitTransactionId;
			if (Flags & 0x08)
			{
				VblkValue NumberOfConfigs;
				VblkValue NumberOfLogs;
			}

			if (Flags & 0x10)
				VblkValue minors;
		}group1;
		break;
	case VblkDiskGroup2:
		struct VblkGroup2
		{
			VblkValue ObjectId;
			VblkString Name;
			GUID Guid;
			GUID LastDiskSetGuid;
			BYTE Zeroes[4];
			DWORD Flags;//TODO: check flags field
			QWORD CommitTransactionId;
			if (Flags & 0x08)
			{
				VblkValue NumberOfConfigs; //QWORD
				VblkValue NumberOfLogs; //QWORD
			}

			if (Flags & 0x10)
				VblkValue Minors; //QWORD
		}group2;
		break;
	}
	BYTE otherData[SizeOfVblk - (current_offset - this)];


#pragma byte_order(LittleEndian)
};

struct Vmdb
{
	var VmdbOffset = this;
#pragma byte_order(BigEndian)
	char Magic[4];
	DWORD SequenceNumberOfLastVblk;
	DWORD SizeOfVblk;
	DWORD FirstVblkOffset;
	WORD UpdateStatus;
	WORD Major;
	WORD Minor;
	char DiskGroupName[31];
	BYTE DiskGroupGuid[64];
	QWORD CommittedSequence;
	QWORD PendingSequence;
	DWORD NumberofCommittedVolumeBlocks;
	DWORD NumberOfCommittedComponentBlocks;
	DWORD NumberOfCommittedPartitionBlocks;
	DWORD NumberOfCommittedDiskBlocks;
	DWORD NumberOfCommittedDiskAccessRecords;
	DWORD Unused1;
	DWORD Unused2;
	DWORD NumberOfPendingVolumeBlocks;
	DWORD NumberOfPendingComponentBlocks;
	DWORD NumberOfPendingPartitionBlocks;
	DWORD NumberOfPendingDiskBlocks;
	DWORD NumberOfPendingDiskAccessRecords;
	DWORD Unused3;
	DWORD Unused4;
	QWORD LastAccessTime;

	BYTE Reserved[FirstVblkOffset - (current_offset - VmdbOffset)];

	var BlocksCount = (SectorSize / SizeOfVblk);
	var count = (SequenceNumberOfLastVblk - VblkStartSequenceNumber) / BlocksCount;
	$print("count", count);
	$print("sector_vblk", BlocksCount);

	struct VblkRecord
	{
		ExtendedVblk vblk[BlocksCount];
	}vblk_record[count];
#pragma byte_order(LittleEndian)
};

struct TocRegion
{
	char name[8];
	WORD flags;
	ULONGLONG start;
	ULONGLONG size;
	WORD unk1;
	WORD copyNumber;
	BYTE zeroes[4];
};

struct TocBlock
{
	$print("toc_offset", this);
#pragma byte_order(BigEndian)
	char Magic[8];
	DWORD Checksum;
	ULONGLONG UpdateSequenceNumber;
	BYTE Zeroes[16];
	TocRegion Config;
	TocRegion Log;

	var proffset = GetPrivateRegionStart();

	var nVmdbOffset = (proffset + Config.start) * SectorSize;
	$bind("struct Vmdb", "VMDB", nVmdbOffset);

	//var nKLogOffset = (proffset + Log.start) * SectorSize;
	//$bind("struct KLogs", "Klogs", nKLogOffset);
#pragma byte_order(LittleEndian)
};

struct PrivHead
{
	char Magic[8];
	DWORD Checksum;
	WORD Major;
	WORD Minor;
	QWORD Timestamp;
	QWORD SequenceNumber;
	QWORD PrimaryPrivateHeaderLBA;
	QWORD SecondaryPrivateHeaderLBA;
	BYTE DiskId[64];
	BYTE HostId[64];
	BYTE DiskGroupId[64];
	char DiskGroupName[31];
	DWORD BytesPerBlock;
	DWORD PrivateHeaderFlags;
	WORD PublicRegionSliceNumber;
	WORD PrivateRegionSliceNumber;
	QWORD PublicRegionStart;
	QWORD PublicRegionSize;
	QWORD PrivateRegionStart;
	QWORD PrivateRegionSize;
	QWORD PrimaryTocLba;
	QWORD SecondaryTocLba;
	DWORD NumberOfConfigs;
	DWORD NumberOfLogs;
	QWORD ConfigSize;
	QWORD LogSize;
	BYTE DiskSignature[4];
	GUID DiskSetGuid;
	GUID DiskSetGuidDupicate;

	var proffset = SetPrivateRegionStart(PrivateRegionStart);
	SetPublicRegionStart(PublicRegionStart);

	var nTocOffset = (PrivateRegionStart + PrimaryTocLba) * SectorSize;
	$bind("struct TocBlock", "TocBlock", nTocOffset);
};

struct LDM
{
#pragma byte_order(BigEndian)
	PrivHead head;
#pragma byte_order(LittleEndian)
};

struct PartTable
{
	BYTE bActive;
	BYTE s_head;
	BYTE s_sector;
	BYTE s_cyl;

	BYTE s_code;
	BYTE e_head;
	BYTE e_sector;
	BYTE e_cyl;

	DWORD StartSector;
	DWORD Size;

	switch (s_code)
	{
	case 0x42:
		$bind("struct LDM", "Logical Disk Manager", 0xC00);
		break;
	}
};

public struct HDD_Parser
{
	BYTE BootCode[0x1BE]; //MBR code
	PartTable PT[4]; //Partition Tables
	WORD signature;
};
