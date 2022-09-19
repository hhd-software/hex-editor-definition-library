// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// RAR version 2.02
#include "stddefs.h"

#pragma script("get_doc_size.js")

// 10 * Major version + minor version.
struct RarVersion
{
	BYTE nVersion;
	$print("version: major = ", nVersion / 10 + "; minor = " + nVersion % 10);
};

enum HEAD_TYPE : BYTE
{
	HEAD_TYPE_MARKER = 0x72,				// marker block
	HEAD_TYPE_ARCHIVE = 0x73,				// archive header
	HEAD_TYPE_FILE = 0x74,				// file header
	HEAD_TYPE_COMMENT = 0x75,				// comment header
	HEAD_TYPE_EXTRA = 0x76,				// extra information
	HEAD_TYPE_SUBBLOCK = 0x77,				// subblock
	HEAD_TYPE_RECOVERY = 0x78,				// recovery record
	HEAD_TYPE_END = 0x7B
};

enum HEAD_FLAGS : USHORT
{
	ARCHIVE_VOLUME = 0x1,
	ARCHIVE_COMMENT_PRESENT = 0x2,
	ARCHIVE_LOCKED = 0x4,
	ARCHIVE_SOLID = 0x8,
	NEW_VOLUME_NAMING = 0x10,
	AV_PRESENT = 0x20,
	RECOVERY_PRESENT = 0x40,
	BLOCK_HEADERS_ENCRYPTED = 0x80,
	IS_FIRST_VOLUME = 0x100,

	// if set, older RAR versions will ignore the block
	// and remove it when the archive is updated.
	// if clear, the block is copied to the new archive
	// file when the archive is updated;
	OLD_VERSION_IGNORE = 0x4000,

	// if set, ADD_SIZE field is present and the full block
	// size is HEAD_SIZE+ADD_SIZE.
	ADD_SIZE_PRESENT = 0x8000
};

enum ARCHIVE_FLAGS : USHORT
{
	/*
	0x01    - Volume attribute (archive volume)
	0x02    - Archive comment present
	0x04    - Archive lock attribute
	0x08    - Solid attribute (solid archive)
	0x10    - Unused
	0x20    - Authenticity information present
	*/

	ARCH_TYPE_VOLUME = 0x1,
	ARCH_TYPE_COMMENT_PRESENT = 0x2,
	ARCH_TYPE_LOCK = 0x4,
	ARCH_TYPE_SOLID = 0x8,
	ARCH_TYPE_AUTH_PRESENT = 0x20,

	IGNORE_IF_NEW_VERSION = 0x4000,
	ADD_SIZE_PRESENT = 0x8000,
};

struct FILE_FLAGS
{
	USHORT FILE_CONTINUED_FROM_PREV : 1;		// 0x1
	USHORT FILE_CONTINUED_IN_NEXT : 1;		// 0x2
	USHORT FILE_ENCRYPTED_PASSWORD : 1;		// 0x4
	USHORT FILE_COMMENT_PRESENT : 1;		// 0x8
	USHORT FILE_SOLID_FLAG : 1;		// 0x10

	/*
	 0 0 0    - dictionary size   64 Kb
	 0 0 1    - dictionary size  128 Kb
	 0 1 0    - dictionary size  256 Kb
	 0 1 1    - dictionary size  512 Kb
	 1 0 0    - dictionary size 1024 Kb
	 1 0 1    - reserved
	 1 1 0    - reserved
	 1 1 1    - file is directory
	*/
	USHORT FILE_DICTIONARY : 3;		// !!!
	USHORT FILE_HIGH_SIZE : 1;		// 0x100
	USHORT FILE_UNICODE_FILENAME : 1;		// 0x200
	USHORT FILE_ENCRYPTION : 1;		// 0x400
	USHORT FILE_IS_OLD_VERSION : 1;		// 0x800
	USHORT FILE_EXTENDED_TIME_INFO : 1;		// 0x1000
	USHORT reserved : 1;		// 0x2000
	USHORT FILE_ODL_VERSION_IGNORE : 1;		// 0x4000
	USHORT FILE_ADD_SIZE_PRESENT : 1;		// 0x8000
};

enum HOST_OS : BYTE
{
	OS_TYPE_MSDOS = 0x0,
	OS_TYPE_OS2,
	OS_TYPE_WIN32,
	OS_TYPE_UNIX,
	OS_TYPE_MAC,
	OS_TYPE_BEOS,
};

enum PACKING_METHOD : BYTE
{
	METHOD_STORING = 0x30,
	METHOD_FASTEST = 0x31,
	METHOD_FAST = 0x32,
	METHOD_NORMAL = 0x33,
	METHOD_GOOD = 0x34,
	METHOD_BEST = 0x35
};

enum SUBBLOCK_TYPE : USHORT
{
	TYPE_OS2 = 0x100,
};

// ******************************************************

struct UnixStyleAttrs
{
	DWORD Owner_eXecute : 1;
	DWORD Owner_Write : 1;
	DWORD Owner_Read : 1;

	DWORD Group_eXecute : 1;
	DWORD Gorup_Write : 1;
	DWORD Group_Read : 1;

	DWORD Everybody_eXecute : 1;
	DWORD Everybody_Write : 1;
	DWORD Everybody_Read : 1;

	DWORD Reserved : 23;
};

struct DosFileAttrs
{
	DWORD Readonly : 1;
	DWORD Hidden : 1;
	DWORD System : 1;
	DWORD Volume : 1;
	DWORD Directory : 1;
	DWORD Archive : 1;

	DWORD Reserved : 26;
};

struct WinFileAttrs
{
	DWORD Readonly : 1;
	DWORD Hidden : 1;
	DWORD Systen : 1;
	DWORD Volume : 1;
	DWORD Directory : 1;
	DWORD Archive : 1;
	DWORD Device : 1;
	DWORD Normal : 1;
	DWORD Temporary : 1;
	DWORD SparseFile : 1;
	DWORD ReparsePoint : 1;
	DWORD Compressed : 1;
	DWORD Offline : 1;
	DWORD ContentsNotIndexed : 1;
	DWORD Encrypted : 1;

	DWORD Reserved : 17;
};

struct MarkerBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;

	if (flags & ADD_SIZE_PRESENT)
		DWORD add_size;
};

struct ArchiveBlock
{
	ARCHIVE_FLAGS flags;
	USHORT head_size;
	if (flags & ADD_SIZE_PRESENT)
		DWORD add_size;
	BYTE reserved[6];
};

struct CommentBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;

	if (flags & ADD_SIZE_PRESENT)
		DWORD add_size;

	USHORT unpacked_size;			// Uncompressed comment size
	RarVersion version;		// RAR version needed to extract comment
	PACKING_METHOD packing_method;
};

struct FileBlock
{
	FILE_FLAGS flags;
	USHORT head_size;

	DWORD packed_size;
	DWORD unpacked_size;
	HOST_OS host_os;

	DWORD crc32;
	DWORD ftime;		// in std MS DOS format

	RarVersion version;
	PACKING_METHOD packing_method;

	USHORT file_name_size;

	switch (host_os)
	{
	case OS_TYPE_OS2:
	case OS_TYPE_MSDOS:
	case OS_TYPE_MAC:
		DosFileAttrs file_attributes;
		break;
	case OS_TYPE_WIN32:
		WinFileAttrs   file_attributes;
		break;
	case OS_TYPE_UNIX:
	case OS_TYPE_BEOS:
		UnixStyleAttrs file_attributes;
		break;
	default:
		DWORD file_attributes;
	}

	char file_name[file_name_size];

	var off = current_offset;

	BYTE packed_payload[packed_size];

	//var debug = head_size - (off - this);
	//$print("debug=",debug);

	BYTE reserved[head_size - (off - this) - 3];
};

struct ExtraBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;

	if (flags & ADD_SIZE_PRESENT)
		DWORD add_size;
};

struct OS2_Subblock
{
	DWORD unpacked_size;
	RarVersion version;
	PACKING_METHOD packing_method;
	DWORD ea_crc32;		// extended attributes CRC
};

struct SubBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;
	if (flags & ADD_SIZE_PRESENT)
		DWORD add_size;

	DWORD data_size;
	SUBBLOCK_TYPE	type;
	BYTE reserved;

	switch (type)
	{
	case TYPE_OS2:
		OS2_Subblock os2_subblock;
		break;
	default:
		if (data_size)
		{
			if (data_size >= 200000)
				$print("current offset", current_offset);
			else
				BYTE payload[data_size];
		}
	}
};

struct EndBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;
};

struct UnknownBlock
{
	HEAD_FLAGS flags;
	USHORT head_size;
	if (flags & ADD_SIZE_PRESENT)
	{
		DWORD nAddSize;
		BYTE data[head_size - 2 * sizeof(USHORT) - sizeof(HEAD_FLAGS) - sizeof(HEAD_TYPE) - sizeof(DWORD) + nAddSize];
	}
	else
	{
		BYTE data[head_size - 2 * sizeof(USHORT) - sizeof(HEAD_FLAGS) - sizeof(HEAD_TYPE)];
	}
};

struct RarBlock
{
	if (SizeLeft <= 0)
		$break_array(false);

	USHORT crc16;
	HEAD_TYPE type;

	var block_len = 0;

	switch (type)
	{
	case HEAD_TYPE_MARKER:
		MarkerBlock marker_block;
		//if(archive_block.flags & ARCH_TYPE_COMMENT_PRESENT)
		//	BYTE comment_block[archive_block.head_size - sizeof(archive_block) - sizeof(crc16) - sizeof(type)];
		block_len = sizeof(marker_block);
		break;
	case HEAD_TYPE_ARCHIVE:
		ArchiveBlock archive_block;
		//if(archive_block.flags & ARCH_TYPE_COMMENT_PRESENT)
		//	BYTE comment_block[archive_block.head_size - sizeof(archive_block) - sizeof(crc16) - sizeof(type)];
		block_len = sizeof(archive_block);
		break;
	case HEAD_TYPE_FILE:
		FileBlock file_block;
		block_len = 0;
		if (file_block.flags.FILE_COMMENT_PRESENT == 1)
		{
			CommentBlock comment_block;
			block_len = sizeof(comment_block);
		}
		block_len = block_len + sizeof(file_block);
		break;
	case HEAD_TYPE_COMMENT:
		CommentBlock comment_block;
		block_len = sizeof(comment_block);
		break;
	case HEAD_TYPE_EXTRA:
		ExtraBlock	 extra_block;
		BYTE info[extra_block.head_size - sizeof(extra_block) - sizeof(crc16) - sizeof(type)];
		block_len = sizeof(extra_block);
		break;
	case HEAD_TYPE_SUBBLOCK:
		SubBlock	sub_block;
		block_len = sizeof(sub_block);
		break;
	case HEAD_TYPE_END:
		EndBlock    end_block;
		block_len = sizeof(end_block);
		break;
	default:
		// unknown
		UnknownBlock	unknown_block;
		block_len = sizeof(unknown_block);
	}

	SizeLeft = SizeLeft - sizeof(crc16) - sizeof(type) - block_len;
};

public struct RarFile
{
	var FileSize = GetDocumentSize();
	var SizeLeft = FileSize;

	[noindex] RarBlock blocks[*];		// 240
};
