// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see Adobe_EPS3_0.pdf
#include "tiff.h"

#pragma byte_order(LittleEndian)
#include "stddefs.h"

struct PSCode
{
	if (current_offset != 0 && dwPSCodeLength != 0)
		BYTE ps_data[dwPSCodeLength];
};

struct Metafile
{
	if (current_offset != 0 && dwMetafileScreenRepresentationSize != 0)
		BYTE metafile_data[dwMetafileScreenRepresentationSize];
};

public struct EPS_File
{
	DWORD dwSignature;
	$assert(dwSignature == 0xC6D3D0C5, "Hex editor is unable to parse file");

	DWORD dwPSCodeOffset as PSCode *;
	DWORD dwPSCodeLength;

	DWORD dwMetafileScreenRepresentationOffset as Metafile *;
	DWORD dwMetafileScreenRepresentationSize;

	DWORD dwTiffRepresentationOffset as TiffFile *;
	DWORD dwTiffRepresentationSize;

	WORD wChecksum; // XOR of bytes 0 -27. if 0xffff -> ignore it
};
