// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see "Microsoft Cabinet File Format 1997"
#include "stddefs.h"

enum HeaderFlags : WORD
{
	cfhdrPREV_CABINET = 1,
	cfhdrNEXT_CABINET = 2,
	cfhdrRESERVE_PRESENT = 4
};

// forward declaration
struct CFFILE_ARRAY;

struct CFHEADER
{
	BYTE signature[4]; // cabinet file signature
	$assert(signature == "MSCF", "Hex editor is unable to parse file");
	DWORD reserved1; // reserved 
	DWORD cbCabinet; // size of this cabinet file in bytes 
	DWORD reserved2; // reserved 
	DWORD coffFiles as CFFILE_ARRAY *; // offset of the first CFFILE entry 
	DWORD reserved3; // reserved 
	BYTE versionMinor; // cabinet file format version, minor 
	BYTE versionMajor; // cabinet file format version, major 
	WORD cFolders; // number of CFFOLDER entries in this cabinet 
	WORD cFiles; // number of CFFILE entries in this cabinet 
	HeaderFlags flags; // cabinet file option indicators 
	WORD setID; // must be the same for all cabinets in a set 
	WORD iCabinet; // number of this cabinet file in a set 

	if (flags & cfhdrRESERVE_PRESENT)
	{
		WORD cbCFHeader; // (optional) size of per-cabinet reserved area 
		BYTE cbCFFolder; // (optional) size of per-folder reserved area 
		BYTE cbCFData; // (optional) size of per-datablock reserved area 
		BYTE abReserve[cbCFHeader]; // (optional) per-cabinet reserved area 
	}

	if (flags & cfhdrPREV_CABINET)
	{
		string szCabinetPrev; // (optional) name of previous cabinet file 
		string szDiskPrev; // (optional) name of previous disk 
	}

	if (flags & cfhdrNEXT_CABINET)
	{
		string szCabinetNext; // (optional) name of next cabinet file 
		string szDiskNext; // (optional) name of next disk 
	}
};

// forward declaration
struct CFDATA_ARRAY;

struct CFFOLDER
{
	DWORD coffCabStart as CFDATA_ARRAY *; // offset of the first CFDATA block in this folder 
	WORD cCFData; // number of CFDATA blocks in this folder 
	WORD typeCompress; // compression type indicator 
	BYTE abReserve[header.cbCFFolder]; // (optional) per-folder reserved area 
};

enum CffileAttributes : WORD
{
	_A_RDONLY = 1,
	_A_HIDDEN = 2,
	_A_SYSTEM = 4,
	_A_ARCH = 0x20,
	_A_EXEC = 0x40,
	_A_NAME_IS_UTF = 0x80,
};

struct CFFILE
{
	DWORD cbFileUncompressedSize; // uncompressed size of this file in bytes 
	DWORD uoffFolderStart; // uncompressed offset of this file in the folder 
	WORD iFolder; // index into the CFFOLDER area 
	WORD date; // date stamp for this file 
	WORD time; // time stamp for this file 
	CffileAttributes attribs; // attribute flags for this file 
	string szName; // name of this file 
};

struct CFFILE_ARRAY
{
	CFFILE files[cFiles]; // WARNING: forward reading?
};

struct CFDATA
{
	DWORD csum; // checksum of this CFDATA entry 
	WORD cbData; // number of compressed bytes in this block 
	WORD cbUncomp; // number of uncompressed bytes in this block 
	if (header.flags & cfhdrRESERVE_PRESENT)
		BYTE abReserve[header.cbCFData]; // (optional) per-datablock reserved area 

	BYTE ab[cbData]; // compressed data bytes 
};

struct CFDATA_ARRAY
{
	CFDATA data[cCFData];
};

public struct CAB_File
{
	CFHEADER header;
	CFFOLDER folders[header.cFolders];
};
