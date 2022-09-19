// Copyright (c) 2021-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program
//https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/FileIO/exfat-specification.md
// 
// 
//Ex-FAT
#include "stddefs.h"

#define EXFAT_FIRST_DATA_CLUSTER 2
#define EXFAT_LAST_DATA_CLUSTER 0xfffffff6

#define EXFAT_CLUSTER_FREE 0 /* free cluster */
#define EXFAT_CLUSTER_BAD 0xfffffff7 /* cluster contains bad sector */
#define EXFAT_CLUSTER_END 0xffffffff /* final cluster of file or directory */

#define EXFAT_ENTRY_VALID 0x80
#define EXFAT_ENTRY_CONTINUED 0x40
#define EXFAT_ENTRY_OPTIONAL 0x20

#define EXFAT_ENTRY_BITMAP (0x01 | EXFAT_ENTRY_VALID)
#define EXFAT_ENTRY_UPCASE (0x02 | EXFAT_ENTRY_VALID)
#define EXFAT_ENTRY_LABEL (0x03 | EXFAT_ENTRY_VALID)
#define EXFAT_ENTRY_FILE (0x05 | EXFAT_ENTRY_VALID)
#define EXFAT_ENTRY_FILE_INFO (0x00 | EXFAT_ENTRY_VALID | EXFAT_ENTRY_CONTINUED)
#define EXFAT_ENTRY_FILE_NAME (0x01 | EXFAT_ENTRY_VALID | EXFAT_ENTRY_CONTINUED)
#define EXFAT_ENTRY_FILE_TAIL (0x00 | EXFAT_ENTRY_VALID | EXFAT_ENTRY_CONTINUED | EXFAT_ENTRY_OPTIONAL)

javascript
{
	var Fat1TableOffset = 0;
	var Fat2TableOffset = 0;
	var SectorPerCluster = 0;
	var SectorSize = 0;
	var DataSegmentOffset = 0;

	function SetDataSegmentOffset(b)
	{
		DataSegmentOffset = b;
	}

	function SetFat1Offset(b)
	{
		Fat1TableOffset = b;
	}

	function SetFat2Offset(b)
	{
		Fat2TableOffset = b;
	}

	function SetSectorPerCluster(v)
	{
		SectorPerCluster = v;
	}

	function SetSectorSize(s)
	{
		SectorSize = s;
	}

	function ClusterToOffset(cluster)
	{
		return DataSegmentOffset + ((cluster - 2) * SectorPerCluster) * SectorSize;
	}

	function convertToFiletime(year, month, day, hour, minute, second)
	{
		var dateObj = new Date(year + 1980, month, day, hour, minute, second * 2);
		return (dateObj.getTime() * 1e4) + 11644473600 * 1e7;
	}

	function MakePrettyName(name)
	{
		var str = "";
		for (var i = 0; i < 15; i++)
		{
			if (name[i] == '\0' || name[i] == '\xFFFF')
			return str;
			str += name[i];
		}

		return str;
	}
}

struct BootSector
{
	BYTE BootJmp[3];
	char szName[8];
	char unused[53];
	//$shift_by(61);

	ULONGLONG nSectorStart;
	ULONGLONG nSectorCount;

	DWORD nFATOffset;
	DWORD nFATLength;
	DWORD nClusterOffset;
	DWORD nClusterCount;
	DWORD nRootDirectory;
	// $shift_by(6);
	DWORD dwVolumeSerial;
	struct VolumeVersion
	{
		BYTE szMinor;
		BYTE szMajor;
	} version;
	WORD wVolumeFlags;

	BYTE szBytesPerSector;
	BYTE szSectorPerCluster;
	BYTE szNumberOfFATs;
	BYTE nDriveNumber;
	BYTE nAllocatedPercent;
	BYTE unused[397];
	WORD wBootSignature;
};

struct VolumeLabelEntry
{
	BYTE szEntryType;
	BYTE szCharacterCount;
	wchar_t wVolumeLabel[11];
	ULONGLONG nReserved;
};

struct ClusterHeap
{
	BYTE szEntryType;
	BYTE szBitMapFlags;
	BYTE szReserved[18];
	DWORD dwFirstCluster;
	ULONGLONG nDataLength;
};

struct UpCaseTable
{
	BYTE szEntryType;
	BYTE szReserved[3];
	DWORD dwChecksum;
	BYTE szReserved[12];
	DWORD dwFirstCluster;
	ULONGLONG nDataLength;
};

[display(format("{0}/{1}/{2} {3}:{4}:{5}", Day, Month, Year + 1980, Hour, Minute, Seconds * 2))]
struct ExFatTimestamp
{
	DWORD Seconds : 5;
	DWORD Minute : 6;
	DWORD Hour : 5;
	DWORD Day : 5;
	DWORD Month : 4;
	DWORD Year : 7;
};

struct ExFatFileAttributes
{
	WORD ReadOnly : 1;
	WORD Hidden : 1;
	WORD System : 1;
	WORD Reserved1 : 1;
	WORD Directory : 1;
	WORD Archive : 1;
	WORD Reserved2 : 10;
};

struct StreamEntry;
struct ExFatFileName;
struct FileDirectoryEntry;

struct ExFatDirectory
{
#ifdef VOLUME_NAVIGATOR_BIND
	var ParentDir = DirID;
#endif

	FileDirectoryEntry entry[*];
};

[display(format("{0}", filename))]
struct FileDirectoryEntry
{
	var filename = "";
	var startOffset = current_offset;

	BYTE szEntryType;

	if (szEntryType != 0x85 && szEntryType != 0x05)
		$break_array(false);

	BYTE szSecondaryCount;
	WORD wChecksum;
	ExFatFileAttributes wFileAttributes;
	WORD wReserved;
	ExFatTimestamp nCreationTime;
	ExFatTimestamp nLastModified;
	ExFatTimestamp nLastAccessed;
	BYTE szCrTimeTenth;
	BYTE szModTimeTenth;
	BYTE szAccTimeTenth;
	BYTE szReserved[9];

	StreamEntry stream;
	ExFatFileName Filename[szSecondaryCount - 1];

	var isDirectory = wFileAttributes.Directory == 1;
	var isDeleted = szEntryType == 0x05;
	var next_cluster_ = stream.dwFirstCluster;

#ifdef VOLUME_NAVIGATOR_BIND
	if (!isDeleted)
	{
		var attribs = "";

		if (isDirectory)
		{
			var DirID = vn_additem(true, startOffset);
			vn_modifyname(DirID, filename);
			vn_adoptitem(DirID, ParentDir);
		}
		else
		{
			var dataOffset = ClusterToOffset(stream.dwFirstCluster);
			if (wFileAttributes.ReadOnly == 1)
				attribs = attribs + " RO";
			if (wFileAttributes.Hidden == 1)
				attribs = attribs + " H";
			if (wFileAttributes.System == 1)
				attribs = attribs + " S";
			if (wFileAttributes.Archive == 1)
				attribs = attribs + " A";

			var dateCreate = convertToFiletime(nCreationTime.Year, nCreationTime.Month, nCreationTime.Day, nCreationTime.Hour, nCreationTime.Minute, nCreationTime.Seconds);
			var dateLastAccess = convertToFiletime(nLastAccessed.Year, nLastAccessed.Month, nLastAccessed.Day, nLastAccessed.Hour, nLastAccessed.Minute, nLastAccessed.Seconds);
			var dateWriteTime = convertToFiletime(nLastModified.Year, nLastModified.Month, nLastModified.Day, nLastModified.Hour, nLastModified.Minute, nLastModified.Seconds);

			var FileID = vn_additem(ParentDir, startOffset, filename, stream.nDataLength, attribs, 0, dateCreate, dateWriteTime, dateLastAccess);
			// fileid streamid datalength start end
			vn_addstream(FileID, 0, stream.nDataLength, dataOffset, dateCreate);
		}
	}

#endif

	if (isDirectory)
	{
		next_cluster_ = stream.dwFirstCluster;
		while (next_cluster_ != 0 && next_cluster_ != 0xFFFFFFFF)
		{
			$print("next_cluster", next_cluster_);
			var offset_ = ClusterToOffset(next_cluster_);
			$print("offset", offset_);

			// hidden:
			char dummy;
			$shift_by(-sizeof(char));
			// visible:
			char sub_dir as ExFatDirectory *(offset_ - dummy);
			$shift_by(-sizeof(char));

			next_cluster_ = FatTable[next_cluster_];
		}
	}
};

struct ExFatGeneralSecFlags
{
	BYTE AllocationPossible : 1;
	BYTE NoFatChain : 1;
	BYTE Reserved : 6;
};

struct StreamEntry
{
	BYTE szEntryType;
	ExFatGeneralSecFlags GeneralSecFlags;
	BYTE Reserved1;
	BYTE szNameLength;
	WORD szNameHash;
	WORD Reserved2;
	ULONGLONG nValidDataLength;
	DWORD Reserved3;
	DWORD dwFirstCluster;
	ULONGLONG nDataLength;
};

struct ExFatFileName
{
	BYTE szEntryType;
	if (szEntryType != 0xc1 && szEntryType != 0x41)
		$break_array(false);

	ExFatGeneralSecFlags GeneralSecFlags;
	wchar_t szFilename[15];
	filename = filename + MakePrettyName(szFilename);
};

struct ExRootDirectory
{
#ifdef VOLUME_NAVIGATOR_BIND
	var DirID = vn_additem(true, current_offset);
	vn_modifyname(DirID, "..");
	var ParentDir = DirID;
#endif

	VolumeLabelEntry volume;
	ClusterHeap AllocationBitMap;
	UpCaseTable UpCaseTable;

	var next_cluster = 2;

	while (next_cluster != 0 && next_cluster != 0xFFFFFFFF)
	{
		FileDirectoryEntry entry[*];
		next_cluster = FatTable[next_cluster];
	}
};

public struct ExFat
{
	var partitionOffset = current_offset;

	BootSector boot;
	var BytesPerSector = 1 << boot.szBytesPerSector;

	var rootOffset = partitionOffset + boot.nClusterOffset * BytesPerSector +
		((boot.nRootDirectory - 2) * (1 << boot.szSectorPerCluster)) * BytesPerSector;

	SetDataSegmentOffset(partitionOffset + boot.nClusterOffset * BytesPerSector);
	SetSectorPerCluster(1 << boot.szSectorPerCluster);
	SetSectorSize(BytesPerSector);

	var FatSizeInBytes = boot.nFATLength * BytesPerSector;

	SetFat1Offset(partitionOffset + boot.nFATOffset * BytesPerSector);
	SetFat2Offset(partitionOffset + FatSizeInBytes + boot.nFATOffset * BytesPerSector);

	$shift_by(boot.nFATOffset *BytesPerSector - (current_offset - partitionOffset));
	DWORD FatTable[FatSizeInBytes / 4];


hidden:
	char dummy;
	$shift_by(-sizeof(char));
visible:
	char root_directory as ExRootDirectory *(rootOffset - dummy);
	$shift_by(-sizeof(char));
};

public struct VolumeTest
{
	BootSector bpb;
	$assert(bpb.szName == "EXFAT   ", "Invalid Header");
};
