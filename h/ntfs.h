// Copyright (c) 2015 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include <stddefs.h>

#define NTFS_SIGNATURE "NTFS    "
#define FILE_RECORD_MAGIC 'FILE'
#define INDEX_BLOCK_MAGIC 'INDX'

enum EVolumeInfoFlags : WORD
{
	VOLUME_INFO_FLAG_DIRTY = 0x0001,
	VOLUME_INFO_FLAG_RLF = 0x0002,
	VOLUME_INFO_FLAG_UOM = 0x0004,
	VOLUME_INFO_FLAG_MONT = 0x0008,
	VOLUME_INFO_FLAG_DUSN = 0x0010,
	VOLUME_INFO_FLAG_ROI = 0x0020,
	VOLUME_INFO_FLAG_MBC = 0x8000
};

enum EIndexRootFlags : BYTE
{
	INDEX_ROOT_FLAG_SMALL = 0x00,
	INDEX_ROOT_FLAG_LARGE = 0x01
};

enum EIndexEntryFlags : BYTE
{
	INDEX_ENTRY_FLAG_SUBNODE = 0x01,
	INDEX_ENTRY_FLAG_LAST = 0x02
};

enum EFileRecordFlags : WORD
{
	FILE_RECORD_NOTUSE,
	FILE_RECORD_INUSE_FILE,
	FILE_RECORD_DIRECTORY
};

enum EAttributeType : DWORD
{
	ATTR_TYPE_STANDARD_INFORMATION = 0x10,
	ATTR_TYPE_ATTRIBUTE_LIST = 0x20,
	ATTR_TYPE_FILE_NAME = 0x30,
	ATTR_TYPE_OBJECT_ID = 0x40,
	ATTR_TYPE_SECURITY_DESCRIPTOR = 0x50,
	ATTR_TYPE_VOLUME_NAME = 0x60,
	ATTR_TYPE_VOLUME_INFORMATION = 0x70,
	ATTR_TYPE_DATA = 0x80,
	ATTR_TYPE_INDEX_ROOT = 0x90,
	ATTR_TYPE_INDEX_ALLOCATION = 0xA0,
	ATTR_TYPE_BITMAP = 0xB0,
	ATTR_TYPE_REPARSE_POINT = 0xC0,
	ATTR_TYPE_EA_INFORMATION = 0xD0,
	ATTR_TYPE_EA = 0xE0,
	ATTR_TYPE_LOGGED_UTILITY_STREAM = 0x100,
	ATTR_TYPE_LAST = 0xFFFFFFFF
};

enum EReparseTag : DWORD
{
	IO_REPARSE_TAG_IS_ALIAS = 0x20000000,
	IO_REPARSE_TAG_IS_HIGH_LATENCY = 0x40000000,
	IO_REPARSE_TAG_IS_MICROSOFT = 0x80000000,

	IO_REPARSE_TAG_RESERVED_ZERO = 0x00000000,
	IO_REPARSE_TAG_RESERVED_ONE = 0x00000001,
	IO_REPARSE_TAG_RESERVED_RANGE = 0x00000001,

	IO_REPARSE_TAG_NSS = 0x68000005,
	IO_REPARSE_TAG_NSS_RECOVER = 0x68000006,
	IO_REPARSE_TAG_SIS = 0x68000007,
	IO_REPARSE_TAG_DFS = 0x68000008,

	IO_REPARSE_TAG_MOUNT_POINT = 0x88000003,

	IO_REPARSE_TAG_HSM = 0xa8000004,

	IO_REPARSE_TAG_SYMBOLIC_LINK = 0xe8000000,

	IO_REPARSE_TAG_VALID_VALUES = 0xe000ffff,
};

struct NTFS_BPB
{
	BYTE Jmp[3];
	BYTE Signature[8];
	WORD BytesPerSector;
	BYTE SectorsPerCluster;
	WORD ReservedSectors;
	BYTE Zeros1[3];
	WORD NotUsed1;
	BYTE MediaDescriptor;
	WORD Zeros2;
	WORD SectorsPerTrack;
	WORD NumberOfHeads;
	DWORD HiddenSectors;
	DWORD NotUsed2;
	DWORD NotUsed3;
	ULONGLONG TotalSectors;
	ULONGLONG LCN_MFT;
	ULONGLONG LCN_MFTMirr;
	DWORD ClustersPerFileRecord;
	DWORD ClustersPerIndexBlock;
	BYTE VolumeSN[8];
	BYTE Code[430];
	WORD AA55;
};

struct FILE_RECORD_HEADER
{
	WORD OffsetOfUS;
	WORD SizeOfUS;
	ULONGLONG LSN;
	WORD SeqNo;
	WORD Hardlinks;
	WORD OffsetOfAttr;
	EFileRecordFlags Flags;
	[color_scheme("Size")] DWORD RealSize;
	DWORD AllocSize;
	ULONGLONG RefToBase;
	WORD NextAttrId;
	WORD Align;
	DWORD RecordNo;

	WORD UpdateSequenceNumber;
	BYTE UpdateSequenceArray[SizeOfUS - sizeof(WORD)];
};

struct ATTR_HEADER_COMMON
{
	DWORD TotalSize; // Length (including this header)
	[color_scheme("Residency")] BYTE NonResident;
	BYTE NameLength; // name length (char_t)
	WORD NameOffset; // offset to the name
	WORD Flags;
	WORD Id;
};

struct ATTR_HEADER_RESIDENT
{
	[color_scheme("Size")] DWORD AttrSize;
	WORD AttrOffset;
	BYTE IndexedFlag;
	BYTE Padding;
};

struct ATTR_HEADER_NON_RESIDENT
{
	ULONGLONG StartVCN;
	ULONGLONG LastVCN;
	WORD DataRunOffset;
	WORD CompUnitSize;
	DWORD Padding;
	ULONGLONG AllocSize;
	[color_scheme("Size")] ULONGLONG RealSize;
	ULONGLONG IniSize;
};

struct ATTR_STANDARD_INFORMATION
{
	ULONGLONG CreateTime;
	ULONGLONG AlterTime;
	ULONGLONG MFTTime;
	ULONGLONG ReadTime;
	DWORD Permission;
	DWORD MaxVersionNo;
	DWORD VersionNo;
	DWORD ClassId;
};

struct ATTR_STANDARD_INFORMATION_2K
{
	ULONGLONG CreateTime;
	ULONGLONG AlterTime;
	ULONGLONG MFTTime;
	ULONGLONG ReadTime;
	DWORD Permission;
	DWORD MaxVersionNo;
	DWORD VersionNo;
	DWORD ClassId;
	DWORD OwnerId;
	DWORD SecurityId;
	ULONGLONG QuotaCharged;
	ULONGLONG USN;
};


struct ATTR_ATTRIBUTE_LIST
{
	DWORD AttrType;
	WORD RecordLength;
	BYTE NameLength;
	BYTE NameOffset;
	ULONGLONG StartVCN;
	ULONGLONG BaseRef;
	WORD AttrId;
};


struct ATTR_FILE_NAME
{
	ULONGLONG ParentRef;
	ULONGLONG CreateTime;
	ULONGLONG AlterTime;
	ULONGLONG MFTTime;
	ULONGLONG ReadTime;
	ULONGLONG AllocSize;
	ULONGLONG RealSize;
	DWORD Flags;
	DWORD ER;
	BYTE NameLength; // Filename length in characters
	BYTE NameSpace;
	wchar_t Name[NameLength];
};


struct ATTR_VOLUME_INFORMATION
{
	BYTE Reserved1[8];
	BYTE MajorVersion;
	BYTE MinorVersion;
	EVolumeInfoFlags Flags;
	BYTE Reserved2[4];
};


struct ATTR_INDEX_ROOT
{
	DWORD AttrType;
	DWORD CollationRule;
	DWORD IndexBlockSize;
	BYTE ClustersPerIndexBlock;
	BYTE Padding1[3];
	DWORD EntryOffset; // Offset to the first index entry, relative to this address(0x10)
	DWORD TotalEntrySize;
	DWORD AllocEntrySize;
	EIndexRootFlags Flags;
	BYTE Padding2[3];
};

struct INDEX_ENTRY
{
	struct FileRef
	{
		ULONGLONG RecordIndex : 6;
		ULONGLONG SequenceNumber : 2;
	}FileReference;

	WORD Size;
	WORD StreamSize;
	EIndexEntryFlags Flags;
	BYTE Padding[3];
	BYTE Stream[StreamSize];
};

struct INDEX_BLOCK
{
	WORD OffsetOfUS;
	WORD SizeOfUS;
	ULONGLONG LSN; // $LogFile Sequence Number
	ULONGLONG VCN;
	DWORD EntryOffset; // Offset of the index entries, relative to this address(0x18)
	[color_scheme("Size")] DWORD TotalEntrySize;
	DWORD AllocEntrySize;
	BYTE NotLeaf;
	BYTE Padding[3];
};


public struct MFTEntry
{
	var EntryStart = this;
	[color_scheme("FileRecordMagic")] DWORD Magic;
	var EntrySize = 0;
	switch (Magic)
	{
	case FILE_RECORD_MAGIC:
		FILE_RECORD_HEADER FileHeader;
		EntrySize = FileHeader.AllocSize;
		if (current_offset - this < FileHeader.OffsetOfAttr)
			BYTE Reserved[FileHeader.OffsetOfAttr - (current_offset - this)];
		break;
	case INDEX_BLOCK_MAGIC:
		INDEX_BLOCK IndexHeader;
		EntrySize = IndexHeader.AllocEntrySize;
		break;
	}
	struct Attribute
	{
		var AttributeStart = this;
		[color_scheme("AttributeHeader")] EAttributeType dwHeader;
		if (dwHeader == ATTR_TYPE_LAST || current_offset >= EntryStart + 1024)
			$break_array(false);

		ATTR_HEADER_COMMON header;

		var nAttribSize = 0;

		if (header.NonResident)
			ATTR_HEADER_NON_RESIDENT nonresident;
		else
		{
			ATTR_HEADER_RESIDENT resident;
			nAttribSize = resident.AttrSize;
		}

		if (header.TotalSize > 0)
		{
			switch (dwHeader)
			{
			case ATTR_TYPE_STANDARD_INFORMATION:// 0x10
                switch (header.TotalSize)
				{
					case 72:
						ATTR_STANDARD_INFORMATION info;
						break;
					default:
						ATTR_STANDARD_INFORMATION_2K info_2k;
					    break;
				}
				break;
			case ATTR_TYPE_ATTRIBUTE_LIST:// 0x20
			//ATTR_ATTRIBUTE_LIST list;
				break;
			case ATTR_TYPE_FILE_NAME:// 0x30
				ATTR_FILE_NAME filename;
				break;
			case ATTR_TYPE_OBJECT_ID:// 0x40
				struct ATTR_ATTRIBUTE_OBJECT_ID
				{
					GUID object_id;
					if ((current_offset - AttributeStart) < header.TotalSize)
						GUID birth_volume_id;
					if ((current_offset - AttributeStart) < header.TotalSize)
						GUID birth_object_id;
					if ((current_offset - AttributeStart) < header.TotalSize)
						GUID domain_id;
				}object_id;
				break;
			case ATTR_TYPE_SECURITY_DESCRIPTOR:// 0x50
				break;
			case ATTR_TYPE_VOLUME_NAME:// 0x60
				var nNameLength = nAttribSize >> 1;

				break;
			case ATTR_TYPE_VOLUME_INFORMATION:// 0x70
				ATTR_VOLUME_INFORMATION volume_info;
				break;
			case ATTR_TYPE_DATA:// 0x80
				break;
			case ATTR_TYPE_INDEX_ROOT:// 0x90
				ATTR_INDEX_ROOT index_root;
				break;
			case ATTR_TYPE_INDEX_ALLOCATION:// 0xA0
				break;
			case ATTR_TYPE_BITMAP:// 0xB0
				struct BITMAP_ATTR
				{
					BYTE bitmap[0];
				}bitmap;
				break;
			case ATTR_TYPE_REPARSE_POINT:// 0xC0
				struct ATTR_REPARSE_POINT
				{
					EReparseTag ReparseTag;
					WORD ReparseDataLength;
					WORD Reserved; // Align to 8-byte boundary.
					BYTE ReparseData[0];
				}reparse;
				break;
			case ATTR_TYPE_EA_INFORMATION:// 0xD0
				struct ATTR_EA_INFORMATION
				{
					WORD EaLength; // Byte size of the packed extended attributes.
					WORD NeedEaCount;
					DWORD EaQueryLength; /* Byte size of the buffer required to query
					the extended attributes when calling
					ZwQueryEaFile() in Windows NT/2k. I.e. the
					byte size of the unpacked extended
					attributes. */
				}ea_info;
				break;
			case ATTR_TYPE_EA: // 0xE0
				struct ATTR_EA
				{
					enum EEAFlags : BYTE
					{
						NEED_EA = 0x80
					};

					DWORD NextEntryOffset; // Offset to the next EA_ATTR.
					EEAFlags Flags;
					BYTE NameLength; //in bytes
					WORD ValueLength;
					BYTE Name[NameLength];
					BYTE Value[ValueLength];
				}ea;
				break;
			case ATTR_TYPE_LOGGED_UTILITY_STREAM:// 0x100
				break;
		}
			var remaining = header.TotalSize - (current_offset - this);
			if(remaining > 0)
				BYTE Data[remaining];
		}
	}attribs[*];

	var unallocated_size = EntrySize - (current_offset - this);
	if(unallocated_size > 0)
		BYTE unallocated[unallocated_size];
};

public struct NTFS
{
	NTFS_BPB pbp;
};
