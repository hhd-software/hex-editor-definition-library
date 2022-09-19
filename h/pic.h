// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// http://www.fileformat.info/format/pictor/
#include "stddefs.h"

enum VideoModeType : BYTE
{
	_40_columnText = '0',
	_80columnText = '1',
	MonochromeText = '2',
	EGA43lineText = '3',
	VGA50lineText = '4',
	CGA320x200x4 = 'A',
	CGA320x200x16 = 'B',
	CGA640x200x2 = 'C',
	EGA640x200x16 = 'D',
	EGA640x350x2 = 'E',
	EGA640x350x4 = 'F',
	EGA640x350x16 = 'G',
	EGA720x348x2Hercules = 'H',
	EGA320x200x16Plantronics = 'I',
	EGA320x200x16 = 'J',
	EGA640x400x2ATT = 'K',
	VGA320x200x256 = 'L',
	VGA640x480x16 = 'M',
	EGA720x348x16HerculesInColor = 'N',
	VGA640x480x2 = 'O',
};

// pictor pic
struct PicHeader
{
	WORD wId; // Magic number (always 1234h)
	$assert(wId == 0x1234, "Hex editor is unable to parse file");

	WORD wWidth; // Width of image in pixels
	WORD wHeight; // Height of image in pixels
	WORD wXOffset; // X of lower left corner of image
	WORD wYOffset; // Y of lower left corner of image
	BYTE nPlaneInfo; // BPP and number color planes
	BYTE nPaletteFlag; // Color palette/video flag
	if (nPaletteFlag == 0xff)
	{
		VideoModeType nVideoMode; // Video mode of image
		WORD wPaletteType; // Type of color palette
		WORD wPaletteSize; // Size of color palette

		BYTE pallete_data[wPaletteSize];
	}
};

struct PicBlockItem
{
	if (nRunLengthBlock <= 0)
		$break_array(false);

	BYTE nNextByte;
	if (nNextByte == nRunMarker)
	{
		BYTE nOneMoreByte;
		if (nOneMoreByte != 0)
		{
			$print("RunLength", nOneMoreByte);
			BYTE nRunValue;
		}
		else
		{
			WORD wRunCount;
		}
	}
	else
	{
		BYTE nPixelValue;
	}

	nRunLengthBlock = nRunLengthBlock - (current_offset - this);
};

struct PicBlockHead
{
	WORD wBlockSize; // Size of encoded block including header
	WORD wRunLength; // Size of decoded pixel data
	BYTE nRunMarker; // Start-of-run indicator

	var nRunLengthBlock = nRunLength;

	[noindex] PicBlockItem block_items[*];
};


public struct PIC_File
{
	PicHeader header;
	PicBlockHead blocks[*];
};
