// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor
// For usage and distribution policies, consult the license distributed with a product installation program

#pragma byte_order(LittleEndian)

#include <stddefs.h>

struct ListingChunk
{
	char Signature[4];
	// $assert(Signature=="PMGL","Not a valid CHM file");
	DWORD FreeSpaceLength;
	DWORD Unknown;
	DWORD PrevChunk;
	DWORD NextChunk;
};

struct DirectoryHeader
{
	char Signature[4];
	$assert(Signature == "ITSP", "Not a valid CHM file");
	DWORD Version;
	DWORD HeaderLength;
	DWORD Unknown1;
	DWORD ChunkSize;
	DWORD Density;
	DWORD Depth; // 1 or 2
	DWORD RootChunk;
	DWORD FirstPMGLChunk;
	DWORD LastPMGLChunk;
	DWORD Unknown2;
	DWORD TotalChunks;
	DWORD WindowsLanguageID;
	GUID guid;
	DWORD Length2;
	DWORD Unknown3[3];

	ListingChunk chunks[TotalChunks];
};

public struct CHMHeader
{
	char Signature[4];
	$assert(Signature == "ITSF", "Not a valid CHM file");
	DWORD Version;
	DWORD TotalHeaderLength;
	DWORD Unknown1; // usually 1
	DWORD Timestamp;
	DWORD LanguageID;
	GUID Unknown2[2];

	QWORD SectionOffset;
	QWORD SectionSize;

	if (Version >= 3)
		QWORD Section1Offset as DirectoryHeader *;
};
