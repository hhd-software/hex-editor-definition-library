// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include <stddefs.h>

#pragma script("cdfs.js")

#define CDFS_DEFAULT_CACHESIZE 128
#define CDFS_BLOCKSIZE 2048
#define CD_BASE_YEAR 1900
#define BYTE_COUNT_8_DOT_3 24
#define SHORT_NAME_SHIFT 5
#define MAX_FILE_ID_LENGTH 255



enum CDAttributes :BYTE
{
	Hidden = 1,
	Directory = 0x2,
	AssociatedFile = 0x4,
	Record = 0x8,
	Protection = 0xf,
	Reserved1 = 0x20,
	Reserved2 = 0x40,
	Multi = 0x80
};


javascript
{
	function convertToFiletime(year, month, day, hour, minute, second)
	{
		var dateObj = new Date(Date.UTC(year, month, day, hour, minute, second));
		return (dateObj.getTime() * 1e4) + 11644473600 * 1e7;
	}
}

struct FileEntry
{
	var StartOffset = current_offset;
	BYTE RecordLength;

	if (RecordLength == 0)
	{
		var AlignedOffset = (current_offset / CDFS_BLOCKSIZE) * CDFS_BLOCKSIZE;
		BYTE Padding[CDFS_BLOCKSIZE - (current_offset - AlignedOffset)];
	}
	else
	{
		BYTE XAttribLength;
		DWORD FileLocationPtr;
		DWORD FileLocationPtrBE;
		DWORD DataLength;
		DWORD DataLengthBE;
		BYTE RecordTime[6];
		BYTE FlagsHSG;
		CDAttributes FlagsISO;
		BYTE IntLeaveSize;
		BYTE IntLeaveSkip;
		WORD Vssn;
		WORD VssnLE;
		BYTE FileRecordLength;
		char FileName[FileRecordLength];

		// fileid parentid name datalength attribs dir/file created modified accessed
#ifdef VOLUME_NAVIGATOR_BIND
		if (!(FlagsISO & Directory))
		{
			var filetime = convertToFiletime(1900 + RecordTime[0], RecordTime[1] - 1, RecordTime[2], RecordTime[3], RecordTime[4] - FlagsHSG * 15, RecordTime[5]);
			var FileID = vn_additem(DirID, StartOffset, FileName, DataLength, "RO", FlagsISO & Directory, filetime, filetime, filetime);
			// fileid streamid datalength start end
			vn_addstream(FileID, 0, DataLength, FileLocationPtr * CDFS_BLOCKSIZE, filetime);
		}
#endif

		if (RecordLength > 0)
			BYTE SystemUse[RecordLength - (current_offset - this)];
	}
};

[display(format("{0}", entry.FileName))]
struct FileEntry_
{
	if (current_offset >= LastDirectoriesOffset)
		$break_array(false);
	FileEntry entry;
};

struct Directories
{
	var LastDirectoriesOffset = current_offset;
	FileEntry root;
	LastDirectoriesOffset = LastDirectoriesOffset + root.DataLength;
	FileEntry_ files[*];
};

public struct VolumeTest
{
	BYTE DescriptorType; // volume type: 1 = standard, 2 = coded
	char StandardId[5]; // volume structure standard id = CD001

	$assert(StandardId == "CD001", "Invalid Header");
};

struct IsoVolumeDescriptor
{
	var LastDirectoriesOffset = current_offset;

	BYTE DescriptorType; // volume type: 1 = standard, 2 = coded
	if (DescriptorType == 0xFF)
		$break_array(true);
	BYTE StandardId[5]; // volume structure standard id = CD001
	BYTE Version; // volume structure version number = 1
	BYTE VolumeFlags; // volume flags
	char SystemId[32]; // system identifier
	char VolumeId[32]; // volume identifier
	BYTE Reserved[8];
	DWORD VolumeSpace; // size of the volume in LBN's (LittleEndian)
	DWORD VolumeSpaceBE; // size of the volume in LBN's (BigEndian)
	BYTE CharSet[32];
	WORD VolumeSetSize;
	WORD VolumeSetSizeBE;
	WORD VolumeSeqNum;
	WORD VolumeSeqNumBE;
	WORD LogicalBlockSize;
	WORD LogicalBlockSizeBE;
	DWORD PathTableSize;
	DWORD PathTableSizeBE;
	DWORD PathTabLocation[2];
	DWORD PathTabLocationBE[2];
	//if (DescriptorType != 0xFF)
	// FileEntry_ RootDe;// dir entry of the root directory
	//else
	BYTE RootDe[34];
	char VolSetId[128];
	char PublisherId[128];
	char PreparerId[128];
	char AppId[128];
	char Copyright[37]; // file name of copyright notice
	char Abstract[37]; // file name of abstract
	char Bibliograph[37]; // file name of bibliography
	char CreateDate[17]; // volume creation date and time
	char ModDate[17]; // volume modification date and time
	char ExpireDate[17]; // volume expiration date and time
	char EffectDate[17]; // volume effective date and time
	BYTE FileStructVer; // file structure version number = 1
	BYTE Reserved3; // reserved
	BYTE ResApp[512]; // reserved for application
	BYTE Reserved4[653]; // remainder of 2048 bytes reserved

   // vn_additem(PublId);
};

function ConvertParent(value) //convert to zero based index
{
	return value - 1;
}

struct IsoRawPath
{

#ifdef VOLUME_NAVIGATOR_BIND
	var DirID = vn_additem(true, current_offset);
#endif

	BYTE RecordLength;
	BYTE XAttributesLength;

	DWORD DirLocationPtr as Directories *(DirLocationPtr *CDFS_BLOCKSIZE - DirLocationPtr);
	WORD ParentNum;
	char DirName[RecordLength];
	if (RecordLength % 2)
		BYTE Padding;

#ifdef VOLUME_NAVIGATOR_BIND
	if (RecordLength > 0)
	{
		if (DirName[0] == 0)
			vn_modifyname(DirID, "..");
		else
			vn_modifyname(DirID, DirName);
		vn_adoptitem(DirID, ConvertParent(ParentNum));
	}
#endif
};

[display(format("{0}", path.DirName))]
union IsoRawPath_
{
	if (current_offset >= PathTableLastOffset)
		$break_array(false);

	IsoRawPath path;
};

struct PathTable
{
	var PathTableLastOffset = GetPathsLastOffset();
	IsoRawPath_ paths[*];
};

struct VolumeDescriptors
{
	IsoVolumeDescriptor descriptors[*];

	var PathTableSize = descriptors[0].PathTableSize;
	var PathTableLBN = descriptors[0].PathTabLocation[0];

	var PathTableLastOffset = PathTableLBN * CDFS_BLOCKSIZE + PathTableSize;
	SetPathsLastOffset(PathTableLastOffset);

	$bind("struct PathTable", "PathTable", PathTableLBN *CDFS_BLOCKSIZE);

};

public struct CDFS
{
	var FileID = 0;

	$bind("struct VolumeDescriptors", "VolumeDescriptors", 16 * CDFS_BLOCKSIZE);
};
