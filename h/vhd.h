// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see http://technet.microsoft.com/en-us/virtualserver/bb676673.aspx
#include "stddefs.h"

#pragma byte_order(BigEndian)

enum FooterFeaturesEnum : DWORD
{
	NO_FEATURES = 0,
	TEMPORARY = 1,		// This bit is set if the current disk is a temporary disk. 
							// A temporary disk designation indicates to an application 
							// that this disk is a candidate for deletion on shutdown
	RESERVED = 2
};

enum PlatformEnum : DWORD
{
	PLATFORM_WI2r = 0x57693272,
	PLATFORM_WI2k = 0x5769326B,
	PLATFORM_W2ru = 0x57327275,
	PLATFORM_W2ku = 0x57326B75,

	PLATFORM_MAC = 0x4D616320,
	PLATFORM_MAC_X = 0x4D616358
};

// This structure stores the cylinder, heads, and sectors per track value for the hard disk
/*
When a hard disk is configured as an ATA hard disk, the CHS values (that is, Cylinder, Heads,
	Sectors per track) are used by the ATA controller to determine the size of the disk.
	When the user creates a hard disk of a certain size, the size of the hard disk image in
	the virtual machine is smaller than that created by the user. This is because CHS value calculated
	from the hard disk size is rounded down. The pseudo-code for the algorithm used to determine the
	CHS values can be found in the appendix of this document
*/
struct DiskGeometry
{
	WORD wCylinders;
	BYTE nHeads;
	BYTE nSectors;
};

enum DiskTypeEnum : DWORD
{
	DISKTYPE_RESERVED = 1,
	DISKTYPE_FIXED,
	DISKTYPE_DYNAMIC,
	DISKTYPE_DIFFERENCING
};

enum SavedStateEnum : BYTE
{
	STATE_NOT_SAVED = 0,
	STATE_SAVED = 1
};

struct HardDiskFooter
{
	char	Cookie[8];			// conectix
	$assert(Cookie == "conectix", "Invalid VHD file");
	var nBlockSize;			// TODO: make global!

	FooterFeaturesEnum	Features;

	DWORD dwVersion;
	$assert(dwVersion == 0x00010000, "Invalid VHD file");

	QWORD qwDataOffset;
	if (qwDataOffset != 0xFFFFFFFF)
	{
		// next disk pointer
		$bind("struct DynDiskHeader", "dyn_disk_header", qwDataOffset);
	}
	else
	{

	}

	DWORD dwTimeStamp;			// This is the number of seconds since January 1, 
									// 2000 12:00:00 AM in UTC/GMT

	DWORD dwCreatorApplication;	// If the hard disk is created by Microsoft Virtual PC, 
									// "vpc " is written in this field. If the hard disk 
									// image is created by Microsoft Virtual Server, then "vs  " 
									// is written in this field.
									// Other applications should use their own unique identifiers

	DWORD dwCreatorVersion;		// Virtual Server 2004 sets this value to 0x00010000 
									// Virtual PC 2004 sets this to 0x00050000
	PlatformEnum CreatorHostOS;

	QWORD qwOriginalSize;
	QWORD qwCurrentSize;

	DiskGeometry DiskGeometry;
	DiskTypeEnum DiskType;

	DWORD dwChecksum;				// This field holds a basic checksum of the hard disk footer. 
									// It is just a one’s complement of the sum of all the bytes 
									// in the footer without the checksum field
	GUID ID;

	SavedStateEnum SavedState;

	BYTE Reserved[427];
};

struct ParentLocatorEntry
{
	PlatformEnum dwPlatformCode;			// The platform code describes which platform-specific format
									// is used for the file locator. For Windows, a file locator 
									// is stored as a path (for example. “c:\disksimages\ParentDisk.vhd”). 
									// On a Macintosh system, the file locator is a binary large 
									// object (blob) that contains an “alias.” 
	DWORD dwPlatformDataSpace;
	DWORD dwPlatformDataLen;

	DWORD dwReserved;

	QWORD qwPlatformDataOffset;
};

struct BlockAllocationTable;		// FDs

public struct DataBlock
{
	BYTE sector_bitmap[(nBlockSize / 512) / 8];		// for each sector - sector size is 512
	DWORD dwBlockData[nBlockSize];
};

union Block
{
hidden:
	DWORD block_offset;
visible:
	if (block_offset != 0xFFFFFFFF && block_offset != 0)
		DWORD block as DataBlock *;
};

struct BAT
{
	[noindex] Block blocks[dwMaxTableEntries];
};

/*
For dynamic and differencing disk images, the “Data Offset” field within the image footer points
to a secondary structure that provides additional information about the disk image
*/
public struct DynDiskHeader
{
	BYTE Cookie[8];		// "cxsparse"
	$assert(Cookie == "cxsparse", "Invalid VHD file");

	QWORD qwDataOffset;
	QWORD qwTableOffset as BlockAllocationTable *;

	DWORD dwVersion;
	$assert(dwVersion == 0x00010000, "Invalid VHD file");

	DWORD dwMaxTableEntries;
	DWORD dwBlockSize;			// A block is a unit of expansion for dynamic and differencing 
								// hard disks. It is stored in bytes. This size does not include 
								// the size of the block bitmap. It is only the size of the data 
								// section of the block. The sectors per block must always be a power of two
	DWORD dwChecksum;

	GUID ParentID;
	DWORD dwParentTimeStamp;	// This is the number of seconds since January 1, 
								// 2000 12:00:00 AM in UTC/GMT

	DWORD dwReserved;
	wchar_t strParentName[256];

	[noindex] ParentLocatorEntry entries[8];

	BYTE Reserved[256];

	// BAT
	var nBlockSize = dwBlockSize;
	BAT block_allocation_table;
};

struct BlockAllocationTable
{
	DWORD blocks[dwMaxTableEntries];
};

public struct VHD_File
{
	HardDiskFooter footer_mirror;
};
