// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

//FAT32
#include "stddefs.h"

#define ATTR_READ_ONLY 0x01
#define ATTR_HIDDEN 0x02
#define ATTR_SYSTEM 0x04
#define ATTR_VOLUME_ID 0x08
#define ATTR_DIRECTORY 0x10
#define ATTR_ARCHIVE 0x20
#define ATTR_LONG_NAME 0x0F
#define ATTR_LONG_NAME_MASK (ATTR_READ_ONLY | \
	ATTR_HIDDEN | \
	ATTR_SYSTEM | \
	ATTR_VOLUME_ID | \
	ATTR_DIRECTORY | \
	ATTR_ARCHIVE)

#define LAST_LONG_ENTRY 0x40
#define FAT_END_CHAIN = 0x0FFFFFFF;
#define EOC 0x0FFFFFF8

#define DEFAULT_CLUSTER_SIZE 512
#define MAX_CLUSTERS_TO_SHOW 5

javascript
{
	var FAT1TableOffset = 0;
	var FAT2TableOffset = 0;
	var FATClusterSizeBytes = 0;
	var SectorPerCluster = 0;
	var StartSector = 0;
	var SectorSize = 0;
	var FatTableSize = 0;
	var PartitionOffset = 0;

	function SetPartitionOffset(b)
	{
		PartitionOffset = b;
	}

	function SetFAT1TableOffset(b)
	{
		FAT1TableOffset = b;
	}

	function GetFAT1TableOffset()
	{
		return FAT1TableOffset;
	}

	function SetFAT2TableOffset(b)
	{
		FAT2TableOffset = b;
	}

	function GetFAT2TableOffset()
	{
		return FAT2TableOffset;
	}

	function SetFatTableSize(size)
	{
		FatTableSize = size;
	}

	function GetFatTableSize()
	{
		return FatTableSize;
	}

	function SetClusterSizeBytes(b)
	{
		FATClusterSizeBytes = b;
	}

	function GetClusterSizeBytes()
	{
		return FATClusterSizeBytes;
	}

	function SetStartSector(start)
	{
		StartSector = start;
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
		return PartitionOffset + (StartSector + ((cluster - 2) * SectorPerCluster)) * SectorSize;
	}

	function MakePrettyName(name1, name2, name3)
	{
		var str = "";

		for (var i = 0; i < 5; i++)
		{
			if (name1[i] == '\0' || name1[i] == '\xFFFF')
				return str;
			str += name1[i];
		}

		for (var i = 0; i < 6; i++)
		{
			if (name2[i] == '\0' || name2[i] == '\xFFFF')
				return str;
			str += name2[i];
		}

		for (var i = 0; i < 2; i++)
		{
			if (name3[i] == '\0' || name3[i] == '\xFFFF')
				return str;
			str += name3[i];
		}

		return str;
	}

	function MakeFilename(name)
	{
		var str = "";
		var i = 7;
		while (name[i] == ' ' && i > 0)
		{
			i--;
		}

		for (var j = 0; j <= i; j++)
		{
			str += name[j].toLowerCase();
		}

		i = 2;
		while (name[i + 7] == ' ' && i > 0)
		{
			i--;
		}

		if (i > 0)
		{
			str += ".";
			for (var j = 8; j <= 8 + i; j++)
			{
				str += name[j].toLowerCase();
			}
		}
		return str;
	}

	function convertToFiletime(date, time)
	{
		var year = (date >> 9) + 1980;
		var month = (date & 0x00000000000001E0) >> 5;
		var day = (date & 0x000000000000001F);

		var hour = time >> 11;
		var minute = (time & 0x00000000000007E0) >> 5;
		var second = (time & 0x000000000000000F) * 2;

		var dateObj = new Date(year, month - 1, day, hour, minute, second);
		return (dateObj.getTime() * 1e4) + 11644473600 * 1e7;
	}
}

struct DirectoryEntry;

struct FAT_BPB
{
	BYTE BootJmp[3];
	char OEMName[8];
	WORD BytsPerSec;
	BYTE SecPerClus;
	WORD RsvdSecCnt;
	BYTE NumFATs;
	WORD RootEntCnt;
	WORD TotSec16;
	BYTE Media;
	WORD FATsz16;
	WORD SecPerTrk;
	WORD NumHeads;
	DWORD HiddSec;
	DWORD TotSec32;

	DWORD FATsz32;
	WORD ExtFlags;
	WORD FSVer;
	DWORD RootClus;
	WORD FSInfo;
	WORD BkBootSec;
	BYTE Reserved[12];
	BYTE DrvNum;
	BYTE Reserverd1;
	BYTE BootSig;
	DWORD VolID;
	char VolLab[11];
	char FilSysType[8];
};

struct FATDirEntry
{
	char DIR_Name[11];
	BYTE DIR_Attr;
	BYTE DIR_NTRes;
	BYTE DIR_CrtTimeTenth;
	WORD DIR_CrtTime;
	WORD DIR_CrtDate;
	WORD DIR_LstAccDate;
	WORD DIR_FstClusHi;
	WORD DIR_WrtTime;
	WORD DIR_WrtDate;
	WORD DIR_FstClusLo;
	DWORD DIR_FileSize;
};

[display(format("{0}", LDIR_Name1 + LDIR_Name2 + LDIR_Name3))]
struct LFNEntry
{
	BYTE LDIR_Ord;
	wchar_t LDIR_Name1[5];
	BYTE LDIR_ATT;
	BYTE LDIR_Type;
	BYTE LDIR_Chksum;
	wchar_t LDIR_Name2[6];
	WORD LDIR_FstClusLO;
	wchar_t LDIR_Name3[2];
};

[display(format("{0}", EntryName))]
union FATDirEntryUn
{
	var isSpecial = false;

	BYTE Tag;
	FATDirEntry ShortEntry;

	if (((ShortEntry.DIR_Attr & ATTR_LONG_NAME_MASK) != ATTR_LONG_NAME) && (ShortEntry.DIR_Name[0] != 0xE5))
	{
		if ((ShortEntry.DIR_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) == ATTR_VOLUME_ID)
			isSpecial = true;
		// If the first byte is the 0x2E (".") than this is probably one of the "." or ".." entries 
		// In the start of each folder
		else if (((ShortEntry.DIR_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) == ATTR_DIRECTORY) &&
			(ShortEntry.DIR_Name[0] == 0x2E))
			isSpecial = true;
	}

	if (Tag != 0xE5 && Tag != 0x00)
	{
		var isLong = ((ShortEntry.DIR_Attr & ATTR_LONG_NAME_MASK) == ATTR_LONG_NAME);
		var EntryName = MakeFilename(ShortEntry.DIR_Name);

		if (isLong)
		{
			LFNEntry LongEntry;

			$print("isSpecial", isSpecial);

			if (!isSpecial)
			{
				EntryName = "";
				var NumOfLFNOrds = (LongEntry.LDIR_Ord & 0x1F);
				if (NumOfLFNOrds > 0)
					LFNEntry LFNs[NumOfLFNOrds];

				$print("NumOfLFNOrds", NumOfLFNOrds);

				for (var i = NumOfLFNOrds - 1; i >= 1; i = i - 1)
				{
					EntryName = EntryName + (LFNs[i].LDIR_Name1 + LFNs[i].LDIR_Name2 + LFNs[i].LDIR_Name3);
				}

				if (NumOfLFNOrds > 0)
					EntryName = EntryName + MakePrettyName(LFNs[0].LDIR_Name1, LFNs[0].LDIR_Name2, LFNs[0].LDIR_Name3);
			}
		}
	}
	else
	{
		$print("isDeleted", Tag == 0xE5);
	}
};

struct Cluster
{
	DWORD id;
	var clust = id & 0x0FFFFFFF;
	if (clust == 0 || clust >= EOC || clus_count > MAX_CLUSTERS_TO_SHOW)
	{
		//$break_array(true);
	}
	else
	{
	hidden:
		char dummy;
		$shift_by(-sizeof(char));
	visible:
		char clusters as Cluster *(TableOffset - dummy + (id * 4));
		clus_count = clus_count + 1;
	}
};

struct ClusterChain
{
hidden:
	char dummy;
	$shift_by(-sizeof(char));
visible:
	$print("TableOffset", TableOffset);
	$print("current_offset", current_offset);
	var clus_count = 0;

	Cluster chain;
};

[display(format("{0}", un.EntryName))]
struct DirEntry
{
	var startOffset = current_offset;
	FATDirEntryUn un;
	if (current_offset - StartOffset >= GetClusterSizeBytes() || un.Tag == 0)
	{
		$break_array(false);
	}

	if (un.Tag != 0xE5 && un.Tag != 0x00)
	{
		var isDir = ((un.ShortEntry.DIR_Attr & ATTR_DIRECTORY) == ATTR_DIRECTORY);
		if (un.isLong)
		{
			FATDirEntry FileEntry;
			isDir = ((FileEntry.DIR_Attr & ATTR_DIRECTORY) == ATTR_DIRECTORY);
		}

		var cluster = un.isLong ? (FileEntry.DIR_FstClusHi << 16) | FileEntry.DIR_FstClusLo : un.ShortEntry.DIR_FstClusHi << 16 | un.ShortEntry.DIR_FstClusLo;
		$print("isDir", isDir);
		$print("Special", un.isSpecial);

#ifndef VOLUME_NAVIGATOR_BIND

		var TableOffset = GetFAT1TableOffset();
	hidden:
		char dummy;
		$shift_by(-sizeof(char));
	visible:
		char clusters as ClusterChain *(TableOffset - dummy + cluster * 4);
		$shift_by(-sizeof(char));
#endif
		//var next_cluster = cluster;
		//var clusters;
		//while (next_cluster != 0 && next_cluster < EOC)
		//{
		// var offset = ClusterToOffset(next_cluster);
		// next_cluster = FatTable[next_cluster] & 0x0FFFFFFF;
		// //$print("Clusters", active_cluster);
		// clusters.push(next_cluster);
		//}


#ifdef VOLUME_NAVIGATOR_BIND
		if (!un.isSpecial)
		{
			var attribs = "";

			if (isDir)
			{
				var DirID = vn_additem(true, startOffset);
				vn_modifyname(DirID, un.EntryName);
				vn_adoptitem(DirID, ParentDir);
			}
			else
			{
				var dataOffset = ClusterToOffset(cluster);
				if (un.isLong)
				{
					if (FileEntry.DIR_Attr & ATTR_READ_ONLY)
						attribs = attribs + " RO";
					if (FileEntry.DIR_Attr & ATTR_HIDDEN)
						attribs = attribs + " H";
					if (FileEntry.DIR_Attr & ATTR_SYSTEM)
						attribs = attribs + " S";
					if (FileEntry.DIR_Attr & ATTR_ARCHIVE)
						attribs = attribs + " A";

					var dateCreate = convertToFiletime(FileEntry.DIR_CrtDate, FileEntry.DIR_CrtTime);
					var dateLastAccess = convertToFiletime(FileEntry.DIR_LstAccDate, 0);
					var dateWriteTime = convertToFiletime(FileEntry.DIR_WrtDate, FileEntry.DIR_WrtTime);

					var FileID = vn_additem(ParentDir, startOffset, un.EntryName, FileEntry.DIR_FileSize, attribs, 0, dateCreate, dateWriteTime, dateLastAccess);
					// fileid streamid datalength start end
					vn_addstream(FileID, 0, FileEntry.DIR_FileSize, dataOffset, dateCreate);
				}
				else
				{
					if (un.ShortEntry.DIR_Attr & ATTR_READ_ONLY)
						attribs = attribs + " RO";
					if (un.ShortEntry.DIR_Attr & ATTR_HIDDEN)
						attribs = attribs + " H";
					if (un.ShortEntry.DIR_Attr & ATTR_SYSTEM)
						attribs = attribs + " S";
					if (un.ShortEntry.DIR_Attr & ATTR_ARCHIVE)
						attribs = attribs + " A";

					var dateCreate = convertToFiletime(un.ShortEntry.DIR_CrtDate, un.ShortEntry.DIR_CrtTime);
					var dateLastAccess = convertToFiletime(un.ShortEntry.DIR_LstAccDate, 0);
					var dateWriteTime = convertToFiletime(un.ShortEntry.DIR_WrtDate, un.ShortEntry.DIR_WrtTime);
					var FileID = vn_additem(ParentDir, startOffset, un.EntryName, un.ShortEntry.DIR_FileSize, attribs, 0, dateCreate, dateWriteTime, dateLastAccess);
					// fileid streamid datalength start end
					vn_addstream(FileID, 0, un.ShortEntry.DIR_FileSize, dataOffset, dateCreate);
				}
			}
		}
#endif

		if (isDir && !un.isSpecial)
		{
			var next_cluster = cluster;
			while (next_cluster != 0 && next_cluster < EOC)
			{
				var offset = ClusterToOffset(next_cluster);

			hidden:
				char dummy;
				$shift_by(-sizeof(char));
			visible:
				char sub_dir as DirectoryEntry *(offset - dummy);
				$shift_by(-sizeof(char));

				next_cluster = FatTable[next_cluster] & 0x0FFFFFFF;
			}

			//hidden:
			// char dummy;
			// $shift_by(-sizeof(char));
			//visible:
			// char sub_dir as Directory *(offset - dummy);
			// $shift_by(-sizeof(char));
		}
	}
};

struct FileEntry
{
	var StartOffset = current_offset;
	var EndOffset = current_offset + GetClusterSizeBytes();

	DirEntry entry;
};

struct DirectoryEntry
{
#ifdef VOLUME_NAVIGATOR_BIND
	var ParentDir = DirID;
#endif
	var StartOffset = current_offset;
	var EndOffset = current_offset + GetClusterSizeBytes();

	DirEntry entry[*];
};

struct Directory
{
	FATDirEntryUn un;
	if (un.Tag != 0xE5 && un.Tag != 0x00)
	{
		var isDir = ((un.ShortEntry.DIR_Attr & ATTR_DIRECTORY) == ATTR_DIRECTORY);
		if (un.isLong)
		{
			FATDirEntry FileEntry;
		}

		var cluster = un.isLong ? (FileEntry.DIR_FstClusHi << 16) | FileEntry.DIR_FstClusLo : un.ShortEntry.DIR_FstClusHi << 16 | un.ShortEntry.DIR_FstClusLo;
		$print("Special", un.isSpecial);
		$print("First Cluster", cluster);
	}
};

struct RootDirectory
{
#ifdef VOLUME_NAVIGATOR_BIND
	var DirID = vn_additem(true, current_offset);
	vn_modifyname(DirID, "..");
	var ParentDir = DirID;
#endif

	var StartOffset = current_offset;
	var EndOffset = current_offset + GetClusterSizeBytes();

	DirEntry entry[*];
};

public struct FAT32
{
	var partitionOffset = current_offset;
	SetPartitionOffset(partitionOffset);

	FAT_BPB bpb;
	var lFatTableSize = bpb.FATsz32 * bpb.BytsPerSec;
	var Fat1Table = partitionOffset + bpb.RsvdSecCnt * bpb.BytsPerSec;
	var Fat2Table = partitionOffset + (bpb.RsvdSecCnt + bpb.FATsz32) * bpb.BytsPerSec;
	var ClusterSizeBytes = bpb.SecPerClus * bpb.BytsPerSec;

	SetClusterSizeBytes(ClusterSizeBytes);
	SetSectorPerCluster(bpb.SecPerClus);
	SetSectorSize(bpb.BytsPerSec);
	SetStartSector(bpb.RsvdSecCnt + bpb.NumFATs * bpb.FATsz32);

	SetFatTableSize(lFatTableSize);

	var SectorNum = bpb.NumFATs * bpb.FATsz32 +
		(bpb.RootClus - 2) * bpb.SecPerClus;

	SetFAT1TableOffset(Fat1Table);

	$print("Fat1Table", Fat1Table);
	$print("Fat2Table", Fat2Table);
	$print("root offset", partitionOffset + (bpb.RsvdSecCnt + SectorNum) * bpb.BytsPerSec);

	var offset = GetFAT1TableOffset() - current_offset;
	$shift_by(offset);
	DWORD FatTable[GetFatTableSize() / 4];

hidden:
	char dummy;
	$shift_by(-sizeof(char));
visible:
	char root_directory as RootDirectory *(partitionOffset + ((bpb.RsvdSecCnt + SectorNum) * bpb.BytsPerSec) - dummy);
	$shift_by(-sizeof(char));
};

public struct VolumeTest
{
	FAT_BPB bpb;
	$assert(bpb.FilSysType == "FAT32   ", "Invalid Header");
};
