// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// ZSoft PCX File Format Technical Reference Manual
#include "stddefs.h"

enum PcxVersion : BYTE
{
	Version2_5,
	Version2_8Palette,
	Version2_8,
	VersionForWin,
	Version3_0
};

struct RECT
{
	WORD xMin, yMin, xMax, yMax;
};

public struct PCX_Header
{
	BYTE nManufacturer;
	PcxVersion nVersion;
	BYTE nEncoding;
	BYTE nBitsPerPixel;
	RECT rcWindow;

	WORD hdpi, vdpi;

	BYTE colormap[48];
	BYTE reserved;
	BYTE nNumPlanes;

	WORD wBytesPerPixel;
	WORD wPaletteInfo;
	WORD wHScreenSize;
	WORD wVScreenSize;

	BYTE padding[54];

	var XSize = rcWindow.xMax - rcWindow.xMin + 1;
	var YSize = rcWindow.yMax - rcWindow.yMin + 1;
	var BytesPerLine = XSize * wBytesPerPixel;
	var TotalBytes = nNumPlanes * BytesPerLine;

	$print("TotalBytes after expansion", TotalBytes);
};
