// Copyright (c) 2015 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"
#pragma script("pow.js")

struct RGB
{
	BYTE r, g, b;
};

struct GIF_HEADER
{
	char Signature[3];
	char Version[3];
};

struct BLOCK
{
	BYTE nDataLen;
	if (nDataLen == 0)
		$break_array(false); // terminator
	BYTE nData[nDataLen];
};

struct LOGICAL_SCREEN_DESCRIPTOR
{
	USHORT nScreenWidth;
	USHORT nScreenHeight;

	//Values : 0 - No Global Color Table follows, the Background
	// Color Index field is meaningless.
	// 1 - A Global Color Table will immediately follow, the
	// Background Color Index field is meaningful.
	BYTE GlobalColorTableFlag : 1;

	//Number of bits per primary color available
	// to the original image, minus 1
	BYTE ColorResolution : 3;

	//Values : 0 - Not ordered.
	// 1 - Ordered by decreasing importance, most
	// important color first.
	BYTE SortFlag : 1;

	// If the Global Color Table Flag is
	// set to 1, the value in this field is used to calculate the number
	// of bytes contained in the Global Color Table. To determine that
	// actual size of the color table, raise 2 to [the value of the field
	// + 1]
	BYTE SizeOfGlobalColorTable : 3;

	BYTE nBackgroundColorIndex;
	BYTE nPixelAspectRatio;
};

struct IMAGE_DESCRIPTOR
{
	USHORT nImageLeftPosition;
	USHORT nImageTopPosition;
	USHORT nImageWidth;
	USHORT nImageHeight;

	// Values : 0 - Local Color Table is not present. Use
	// Global Color Table if available.
	// 1 - Local Color Table present, and to follow
	// immediately after this Image Descriptor.
	BYTE LocalColorTableFlag : 1;

	// Values : 0 - Image is not interlaced.
	// 1 - Image is interlaced.
	BYTE InterlaceFlag : 1;

	// Values : 0 - Not ordered.
	// 1 - Ordered by decreasing importance, most
	// important color first.
	BYTE SortFlag : 1;

	BYTE Reserved : 2;

	// If the Local Color Table Flag is
	// set to 1, the value in this field is used to calculate the number
	// of bytes contained in the Local Color Table.
	BYTE SizeOfLocalColorTable : 3;
};

struct GRAPHIC_CONTROL_EXTENSION
{
	BYTE nBlockSize;
	$assert(nBlockSize == 4, "Invalid GRAPHIC_CONTROL_EXTENSION size");

	BYTE Reserved : 3;
	BYTE DisposalMethod : 3;
	BYTE UserInputFlag : 1;
	BYTE TransparentColorFlag : 1;

	USHORT nDelayTime;
	BYTE nTransparentColorIndex;

	BYTE nTerminator; // must be zero
	$assert(nTerminator == 0, "Invalid GRAPHIC_CONTROL_EXTENSION terminator");
};

struct BLOCK_ARRAY
{
	BLOCK blocks_arr[*];
};

struct COMMENT_DATA
{
	BLOCK_ARRAY blocks;
};

struct PLAIN_TEXT_EXTENSION
{
	BYTE nBlockSize;
	$assert(nBlockSize == 12, "Invalid PLAIN_TEXT_EXTENSION size");

	USHORT nTextGridLeftPosition;
	USHORT nTextGridTopPosition;
	USHORT nTextGridWidth;
	USHORT nTextGridHeight;

	BYTE nCharCellWidth;
	BYTE nCharCellHeigth;
	BYTE nTextForeColor;
	BYTE nTextBackColor;

	BLOCK_ARRAY blocks;
};

struct APPLICATION_EXTENSION
{
	BYTE nBlockSize;
	$assert(nBlockSize == 11, "Invalid PLAIN_TEXT_EXTENSION size");

	union
	{
		QWORD qw;
		BYTE nArray[4];
	} ApplicationIdentifier;

	BYTE ApplicationAuthCode[3];

	BLOCK_ARRAY blocks;
};

enum ExtensionIntroducerEnum : BYTE
{
	TRAILER_VALUE = 0x3b,
	EXTENSION_INTRODUCED = 0x21,
};

struct DATA; // FD

/*
// see GIF98m.txt

<GIF Data Stream> ::= Header <Logical Screen> <Data>* Trailer

<Logical Screen> ::= Logical Screen Descriptor [Global Color Table]


<Data> ::= <Graphic Block> |
 <Special-Purpose Block>

<Graphic Block> ::= [Graphic Control Extension] <Graphic-Rendering Block>

<Graphic-Rendering Block> ::= <Table-Based Image> |
 Plain Text Extension

<Table-Based Image> ::= Image Descriptor [Local Color Table] Image Data

<Special-Purpose Block> ::= Application Extension |
 Comment Extension
*/
public struct GIF_DATA_STREAM
{
	GIF_HEADER gif_header;
	$assert(gif_header.Signature == "GIF", "Invalid GIF file");

	LOGICAL_SCREEN_DESCRIPTOR logical_screen_descriptor;
	if (logical_screen_descriptor.GlobalColorTableFlag)
		RGB global_color_table[JS_Pow(1, logical_screen_descriptor.SizeOfGlobalColorTable)];

	ExtensionIntroducerEnum nExtensionIntroducer;
	switch (nExtensionIntroducer)
	{
	case TRAILER_VALUE:
		break; // end
	case EXTENSION_INTRODUCED:
		DATA data;
		break;
	}
};

struct DATA
{
	// Comment Extension
	BYTE nControlLabel;

	switch (nControlLabel)
	{
	case 0xF9:
		GRAPHIC_CONTROL_EXTENSION gce;
		BYTE nImageSeparator;
		if (nImageSeparator == 0x2c)
		{
			IMAGE_DESCRIPTOR image_descriptor;
			if (image_descriptor.LocalColorTableFlag)
				RGB local_color_table[1 << image_descriptor.SizeOfLocalColorTable];
		}
		break;
	case 0xFF:
		APPLICATION_EXTENSION ae;
		break;
	case 0xFE:
		COMMENT_DATA comment;
		break;
	case 0x01:
		PLAIN_TEXT_EXTENSION pte;
		break;
	case 0x2c:
		// without optional GRAPHIC_CONTROL_EXTENSION (see above)
		// Table-based image
		IMAGE_DESCRIPTOR image_descriptor;
		if (image_descriptor.LocalColorTableFlag)
			RGB local_color_table[1 << image_descriptor.SizeOfLocalColorTable];
		break;
	default:
		break;
	}
};
