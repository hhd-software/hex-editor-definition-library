// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"

struct RGBA
{
	BYTE r, g, b, a;
};

public struct PAL_File
{
	// Declare the file header
	char file_sig[4];
	DWORD dwFileLength;
	char tag_type[4];

	// RIFF chunk
	char chunk_signature[4];
	DWORD dwChunkSize;
	WORD wVersion;
	$assert(wVersion == 0x300, "Hex editor is unable to parse file");

	WORD wNumColors;
	RGBA colors[wNumColors];
};