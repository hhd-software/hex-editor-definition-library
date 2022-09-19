// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma once
#pragma script("search_jpg_frame.js")

// used by EXIF - see APP1_EXIF
#include "tiff.h"
#include "icc.h"

enum JpegMarker : BYTE
{
	M_SOF0 = 0xC0, // Start Of Frame N
	M_SOF1,
	M_SOF2,
	M_SOF3,
	M_DHT, //Huffman Table 
	M_SOF5,
	M_SOF6,
	M_SOF7,
	M_SOF8,
	M_SOF9,
	M_SOF10,
	M_SOF11,
	M_DAC,
	M_SOF13,
	M_SOF14,
	M_SOF15,

	M_SOI = 0xD8, // Start Of Image 
	M_EOI, // End Of Image 
	M_SOS, // Start Of Scan (begins compressed data)
	M_DQT, // db
	M_DNL, // dc
	M_DRI, // dd
	M_DHP, // de
	M_EXP, // dfs

	M_APP0 = 0xE0, // Jfif marker
	M_APP1_EXIF, // Exif marker
	M_APP2,
	M_APP3,
	M_APP4,
	M_APP5,
	M_APP6,
	M_APP7,
	M_APP8,
	M_APP9,
	M_APP10,
	M_APP11,
	M_APP12,
	M_APP13,
	M_APP14,
	M_APP15,
	M_COM = 0xFE // Comment 
};

struct JpegBlock
{
	char marker;
	JpegMarker marker2;
	USHORT size;
};

struct SOS
{
	WORD wHeaderLength;
	BYTE nComponentsNumber;

	[noindex] struct COMPSOS
	{
		BYTE nComponentSelector;
		BYTE DC_entropy : 4;
		BYTE AC_entropy : 4;
	}comp[nComponentsNumber];

	BYTE spectral_prediction_start; // start of spectral prediction selection
	BYTE spectral_prediction_end;
	BYTE ah : 4;
	BYTE al : 4;
};

// Quantization table
struct DQT
{
	WORD wHeaderLength;

	var nLength = (wHeaderLength - 2) / 65;
	$assert((wHeaderLength - 2) % 65 == 0, "Hex editor is unable to parse file: DQT size is wrong!");

	[noindex] struct DQT_Element
	{
		BYTE nPrecision : 4;
		BYTE nDestinationId : 4;
		BYTE nQuantizationElement[64];
	}elements[nLength];
};

// instead of 'for' statement
struct TempBlock
{
	nTotalSLASize = nTotalSLASize + lengths[array_index];
};

struct DHT_Element
{
	if (nDHTLen <= 0)
		$break_array(false);

	BYTE nTableClass : 4;
	BYTE nHuffmanID : 4;
	BYTE lengths[16];

	var nTotalSLASize = 0;
	// TODO:
	//for(i; i<16; ++i)
	// nTotalSLASize+=lengths[i];
	TempBlock blocks[16];
	BYTE sla[nTotalSLASize];
};

// Huffman table
struct DHT
{
	WORD wHeaderLength;

	var nDHTLen = wHeaderLength - 2;
	[noindex] DHT_Element elements[*];
};

struct DAC
{
	WORD wHeaderLength;
	var nElements = wHeaderLength / 2;
	$assert((wHeaderLength % 2) == 0, "Hex editor is unable to parse file: DAC size is wrong!");

	[noindex] struct DAC_Element
	{
		BYTE nTableClass : 4;
		BYTE nTableId : 4;
		BYTE nConditioningValue;
	}elements[nElements];
};

struct DRI
{
	WORD wHeaderLength;
	$assert(wHeaderLength == 4, "Hex editor is unable to parse file: DRI size is wrong!");
	WORD wRestartInterval;
};

struct COMMENT
{
	WORD wHeaderLength;
	BYTE comment_data[wHeaderLength - 2];
};

// TODO: check that length is always 4!!! by specification it is very obscure!!! 
struct DNL
{
	WORD wHeaderLength;
	$assert(wHeaderLength == 4, "Hex editor is unable to parse file: DNL size is wrong!");
	WORD wLines;
};

struct EXP
{
	WORD wHeaderLength;
	BYTE nExpandHorizontally : 4;
	BYTE nExpandVertically : 4;
};

struct SOF0
{
	WORD wHeaderLength;

	BYTE nPrecision;
	WORD wImageY;
	WORD wImageX;
	BYTE nCompNumber;

	[noindex] struct COMPS
	{
		BYTE nId;
		BYTE nHorz : 4;
		BYTE nVert : 4;
		BYTE nCompDestSelector;
	}comp[nCompNumber];
};

struct RGB
{
	BYTE r, g, b;
};

enum JFXX_ExtCode<BYTE>
{
	ExtCode_Thumbnail_JPEG = 0x10,
	ExtCode_Thumbnail_1byte_per_pixel = 0x11,
	ExtCode_Thumbnail_3bytes_per_pixel = 0x13
};

enum DirEntryTypes
{
	TYPE_BYTES = 0,
	TYPE_CHARS = 0x800,
	TYPE_WORDS = 0x1000,
	TYPE_DWORDS = 0x1800,
	TYPE_SUBDIR = 0x3000
};

struct ByteTypeArray
{
	BYTE data[dwDataSize];
};

struct CharsArray
{
	char data[dwDataSize];
};

struct WordsArray
{
	WORD data[dwDataSize / 2];
};

struct DwordArray
{
	WORD data[dwDataSize / 4];
};

// Forward Declaration
struct CDIR;

struct DirEntry
{
	WORD wTag;
	DWORD dwDataSize;

	if (!(Tag & 0xC000))
	{
		var nTag = wTag & 0x3800;
		switch (nTag)
		{
		case TYPE_BYTES:
			DWORD data as ByteTypeArray *;
			break;
		case TYPE_CHARS:
			DWORD data as CharsArray *;
			break;
		case TYPE_WORDS:
			DWORD data as WordsArray *;
			break;
		case TYPE_DWORDS:
			DWORD data as DwordArray *;
			break;
		case TYPE_SUBDIR:
			DWORD subdir as CDIR *;
			break;
		default:
			DWORD dwDataPointer;
		}
	}
};

struct CDIR
{
	WORD wEntries;
	[noindex] DirEntry entries[wEntries];
	DWORD dwValues;
};

// Forward Declaration
struct JpegFile;

struct APP0
{
	WORD wHeaderLength;
	char type[5];

	var nSizeUsed = 0;
	switch (type)
	{
	case 'JFIF':
		WORD wVersion;
		BYTE nUnits;
		WORD wDensityX;
		WORD wDensityY;
		BYTE nThumbnailX;
		BYTE nThumbnailY;

		RGB rgbs[nThumbnailX * nThumbnailY];
		break;
	case 'JFXX':
		JFXX_ExtCode nExtensionCode;
		if (nExtensionCode == ExtCode_Thumbnail_JPEG)
		{
			// thumbnail follows
			JpegFile thumbnail;
		}
		break;
	case 'II':case 'MM':
		// TODO: wrong offset -> read only 2 bytes!!! type[5] read 5!!!
		DWORD BlockStart;
		char Signature[8];
		CDIR cdir;
		break;
	}

	// 7 is size of wHeaderLength + type
	BYTE not_parsed_data[wHeaderLength - (current_offset - this)];
};

struct APP1_EXIF
{
	WORD wHeaderLength;
	char exif_header[6]; // 'EXIF00'

	// TODO: check if needed
	if (exif_header != "EXIF" && exif_header != "META")
		$print("warning:", "EXIF header is wrong");

	TIFF_IMAGE_FILE_HEADER tiff;
};

struct Stim
{
	WORD wHeaderLength;
};

public struct JpegChunk
{
	BYTE marker;
	$assert(marker == 0xff, "Hex editor is unable to parse file: wrong marker");
	JpegMarker marker2;

	switch (marker2)
	{
	case M_SOS:
		SOS sstart_of_scan;
		break;
	case M_DHT:
		DHT huffman_table;
		break;
	case M_DQT:
		DQT quantization_table;
		break;
	case M_DAC:
		DAC dac;
		break;
	case M_DRI:
		DRI restart_interval;
		break;
	case M_COM:
		COMMENT comment;
		break;
	case M_DNL:
		DNL number_of_lines;
		break;
	case M_EXP:
		EXP exp;
		break;
	case M_SOF0: // start of frame 0 (baseline DCT)
		SOF0 sof0;
		break;
	case M_APP0:
		APP0 app0;
		break;
	case M_APP1_EXIF:
	case M_APP3: // Kodak meta data / EXIF
	// or JPS Stereo JPEG File
		APP1_EXIF app1;
		break;
	case M_APP2:
		ICC icc_profile;
		break;

		//case M_APP12: // OLYMPUS Digital Camera Information
		// Adobe Ducky Segment 
		// //Picture Info
		// APP12 app12;
		// break;
	case M_APP13: // Photoshop Image Resource Block(IRB)
	// "Photoshop IRB"
		Stim stim;
		break;
		//case M_APP14: // Adobe segment Ver.100 Flags 
		// // "Adobe"
		// break;
	}
};

struct JpegFileChunk
{
	var nFrameOffset = JS_SearchForJpegFrame(nCurrentOffset);
	if (nFrameOffset != -1) // TODO: 1000 is only for debug!!!
	{
		var nWasOffset = current_offset;
		if (nFrameOffset < current_offset)
		{
			$print("nFrameOffset", nFrameOffset);
			$print("current_offset", current_offset);
		}
		else
		{
			BYTE unknown_data[nFrameOffset - current_offset];
			//$print("nFrame",nFrame);
			//$bind("struct JpegChunk","jpegframe",nFrameOffset);
			JpegChunk chunk;
		}
		nCurrentOffset = nFrameOffset + (current_offset - nWasOffset);
	}
	else
		$break_array(false);
};

public struct JpegFile
{
	var nCurrentOffset = 0;
	JpegFileChunk chunks[3];
};
