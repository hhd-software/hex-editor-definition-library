// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file

#pragma byte_order(LittleEndian)

#include "stddefs.h"

// Forward declarations

struct BITMAPFILEHEADER;
struct BITMAPINFO;
union BITMAPINFOHEADER_SELECTOR;
struct BITMAPINFOHEADER;
struct BITMAPV4HEADER;
struct BITMAPV5HEADER;
struct RGBQUAD;
struct BITMAPDATA;

#pragma pack(1)
// Pixel Color
struct RGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
};

typedef long FXPT2DOT30;

struct CIEXYZ
{
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
};

struct CIEXYZTRIPLE
{
	CIEXYZ  ciexyzRed;
	CIEXYZ  ciexyzGreen;
	CIEXYZ  ciexyzBlue;
};

#pragma pack(2)
// Bitmap file header
public struct BITMAPFILEHEADER
{
	union
	{
		WORD    bfType;
		char bfTypeSignature[2];
	} bfTypeAndSignature;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits as BITMAPDATA *;

	// Verify that the header is in fact a bitmap header
	$assert(bfTypeAndSignature.bfType == 'BM' && bfReserved1 == 0 && bfReserved2 == 0, "Invalid bitmap file header");

	BITMAPINFO info;
};
#pragma pack(1)

struct BITMAPINFO
{
	BITMAPINFOHEADER_SELECTOR bmiHeader;
	// Image palette, if present    
	RGBQUAD bmiColors[bmiHeader.header.biClrUsed];
};

// Supported image compression types
enum BI_COMPRESSION<DWORD>
{
	BI_RGB = 0,
	BI_RLE8 = 1,
	BI_RLE4 = 2,
	BI_BITFIELDS = 3,
	BI_JPEG = 4,
	BI_PNG = 5,
};

// Bitmap info header (legacy)
struct BITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	BI_COMPRESSION biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

// Bitmap info header (version 4)
struct BITMAPV4HEADER
{
	DWORD bV4Size;
	LONG bV4Width;
	LONG bV4Height;
	WORD bV4Planes;
	WORD bV4BitCount;
	BI_COMPRESSION bV4V4Compression;
	DWORD biSizeImage;
	LONG bV4XPelsPerMeter;
	LONG bV4YPelsPerMeter;
	DWORD biClrUsed;
	DWORD bV4ClrImportant;
	DWORD bV4RedMask;
	DWORD bV4GreenMask;
	DWORD bV4BlueMask;
	DWORD bV4AlphaMask;
	DWORD bV4CSType;
	CIEXYZTRIPLE bV4Endpoints;
	DWORD bV4GammaRed;
	DWORD bV4GammaGreen;
	DWORD bV4GammaBlue;
};

// Bitmap info header (version 5)
struct BITMAPV5HEADER
{
	DWORD bV5Size;
	LONG bV5Width;
	LONG bV5Height;
	WORD bV5Planes;
	WORD bV5BitCount;
	BI_COMPRESSION bV5Compression;
	DWORD biSizeImage;
	LONG bV5XPelsPerMeter;
	LONG bV5YPelsPerMeter;
	DWORD biClrUsed;
	DWORD bV5ClrImportant;
	DWORD bV5RedMask;
	DWORD bV5GreenMask;
	DWORD bV5BlueMask;
	DWORD bV5AlphaMask;
	DWORD bV5CSType;
	CIEXYZTRIPLE bV5Endpoints;
	DWORD bV5GammaRed;
	DWORD bV5GammaGreen;
	DWORD bV5GammaBlue;
	DWORD bV5Intent;
	DWORD bV5ProfileData;
	DWORD bV5ProfileSize;
	DWORD bV5Reserved;
};


// Check the size of the Info header and select one of three headers
union BITMAPINFOHEADER_SELECTOR
{
	DWORD biSize;
	switch (biSize)
	{
		case sizeof(BITMAPINFOHEADER):
			BITMAPINFOHEADER header;
			break;
		case sizeof(BITMAPV4HEADER) :
			BITMAPV4HEADER header;
			break;
		case sizeof(BITMAPV5HEADER) :
			BITMAPV5HEADER header;
			break;
		default:
			// Unsupported image header
			struct
			{
				var biClrUsed = 0;
				var biSizeImage = 0;
			} header;
	}
};

// Limited part of bitmap pixel data
struct BITMAPDATA
{
	char RawData[info.bmiHeader.header.biSizeImage];
};
