// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see http://www.libpng.org/pub/png/spec/ for specifications (version 1.2 + extensions 1.2)
// see http://www.w3.org/TR/PNG/

#include "stddefs.h"
//#include "strings.h"

#pragma pack(1)

// PNG uses Big Endian byte order
#pragma byte_order(BigEndian)

// Color type bit mask (see IHDR chunk)
enum ColorTypeEnum : BYTE
{
	Grayscale = 0,
	PaletteUsed = 1,
	ColorUsed = 2,
	AlphaChannelUsed = 4,
	ColorPlusAlphaUsed = 6
};

// Supported compression methods
enum CompressionMethodType : BYTE
{
	DeflateInflateWindow,
};

// Supported filtering methods
enum FilteringMethodType : BYTE
{
	AdaptiveFiltering,
};


// Supported interlacing methods
enum InterlaceMethodType : BYTE
{
	NoInterlace,
	Adam7Interlace,
};

// sRGB chunk rendering intent
enum RenderingIntentType : BYTE
{
	Perceptual,
	RelativeColorimetric,
	Saturation,
	AbsoluteColorimetric,
};

enum UnitSpecifierType : BYTE
{
	Unknown,
	Meter,
};

enum UnitSpecifierType2 : BYTE
{
	Pixel,
	MicroMeter,
};

enum UnitSpecifierType3 : BYTE
{
	Unknown,
	Meter,
	Radian
};

// PNG file signature
union PNG_SIGNATURE
{
	[description("PNG File Header")] unsigned char Signature[8];
hidden:
	struct
	{
		unsigned long SignatureLow;
		unsigned long SignatureHigh;
	} SignaturePack;
};

struct ColorPoint
{
	DWORD X;
	DWORD Y;
	$print("pos(x,y)", format("({0},{1})", double(X) / 100000., double(Y) / 100000));
};

enum EquType : BYTE
{
	LinearMapping,
	ExponentialMapping,
	ArbitraryBaseExponentialMapping,
	HyperbolicMapping
};

[display(ChunkType.caChunkType)]
struct Chunk
{
	DWORD Length; // Length of chunk, in bytes
	union
	{
		char caChunkType[4]; // Chunk type (as character array)
		DWORD dwChunkType; // Chunk type (as DWORD)
	} ChunkType;

	var nOffsetDataBegin = current_offset;

	case_union
	{
	case ChunkType.dwChunkType == 'RDHI': // IHDR chunk
		DWORD Width; // Image width, in pixels
		DWORD Height; // Image height, in pixels
		BYTE BitDepth; // Bit depth
		// for future use
		ImageBitDepth = BitDepth;
		ColorTypeEnum ColorType; // Color type

		CompressionMethodType CompressionMethod; // Compression method
		FilteringMethodType FilterMethod; // Filtering method
		InterlaceMethodType InterlaceMethod; // Interlacing method
	break;
	case ChunkType.dwChunkType == 'ETLP': // PLTE chunk
		struct PaletteEntry
		{
			BYTE R,G,B;
		} Palette[Length / sizeof(PaletteEntry)]; // Array of palette colors
	break;
	case ChunkType.dwChunkType == 'AMAg': // Image gamma
		DWORD Gamma;
		$print("Real gamma","1/" + (100000. / double(Gamma)));
		break;
	case ChunkType.dwChunkType == 'DNEI': // Terminating chunk
		$break_array(true);
		break;
	case ChunkType.dwChunkType == 'SNRt': // Simple transparency
		$print("ImageBitDepth",ImageBitDepth);
		switch (ImageColorType)
		{
		case Grayscale:
			WORD TransparentGray[Length / 2];
			break;
		case PaletteUsed:
		case ColorUsed:
			BYTE Alpha[Length];
			break;
		case ColorUsed:
			WORD R, G, B;
			break;
		case ColorPlusAlphaUsed:
			BYTE R, G, B, Alpha;
			break;
		default:
			if (Length)
				BYTE UnknownData[Length];
		}
	break;
	case ChunkType.dwChunkType == 'DGKb': // Background chunk
		WORD R, G, B;
		break;
	case ChunkType.dwChunkType == 'MRHc': // Primary chromaticities
		ColorPoint WhitePoint;
		ColorPoint Red;
		ColorPoint Green;
		ColorPoint Blue;
		break;
	case ChunkType.dwChunkType == 'BGRs': // sRGB Standard RGB color space
		RenderingIntentType RenderingIntent;
		break;
	case ChunkType.dwChunkType == 'PCCi': // iCCP Embedded ICC profile
		string ProfileName;
		CompressionMethodType CompressionMethod;
		BYTE CompressedProfile[Length - sizeof(ProfileName) - sizeof(CompressionMethod)];
		break;
	case ChunkType.dwChunkType == 'zTXt':
		string Keyword;
		CompressionMethodType CompressionMethod;
		BYTE CompressedText[Length - sizeof(Keyword) - sizeof(CompressionMethod)];
		break;
	case ChunkType.dwChunkType == 'sYHp': // pHYs Physical pixel dimensions
		DWORD PixelsPerUnitX, PixelsPerUnitY;
		UnitSpecifierType UnitSpecifier;
		break;
	case ChunkType.dwChunkType == 'TADI': // actual image data
		BYTE ImageData[Length];
		break;
	case ChunkType.dwChunkType == 'tXEt':
		string Keyword;
		char Text[Length - sizeof(Keyword)]; // no null-terminator
		break;
	case ChunkType.dwChunkType == 'tXTi':
		string Keyword;
		BYTE Compression_flag;
		CompressionMethodType CompressionMethod;
		string Language_tag;
		string Translated_keyword;
		string Text;
		break;
	case ChunkType.dwChunkType == 'TIBs': // However, the sBIT chunk is provided in order to
	// store the original number of significant bits
		BYTE sBIT[Length];
		break;
	case ChunkType.dwChunkType == 'TLPs':
		var nWasCurrOffset = current_offset;
		string PaletteName;
		BYTE SampleDepth;

		var SampleWidth = 1;
		if (SampleDepth == 16)
			SampleWidth = 2;

		struct Sample
		{
			if (SampleWidth == 1)
				BYTE r, g, b, A;
			else
				WORD r, g, b, A;

			WORD Frequency;
		}samples[(Length - (current_offset - nWasCurrOffset)) / SampleWidth];
		break;
	case ChunkType.dwChunkType == 'EMIt':
		WORD Year;
		BYTE Month, Day, Hour, Minute, Second; // (yes, 60, for leap seconds; not 61, a common error)
		break;
		// extensions:
	case ChunkType.dwChunkType == 'sFFo':
		DWORD X, Y;
		UnitSpecifierType2 UnitSpecifier;
		break;
	case ChunkType.dwChunkType == 'LACp':
		string CalibrationName;
		DWORD X0, X1;
		EquType EquationType;
		BYTE NumberOfParameters;
		string UnitName;

		var UsedBytes = sizeof(CalibrationName) + 2 * sizeof(X0) + 2 * sizeof(EquationType) + sizeof(UnitName);
		if (NumberOfParameters)
		{
			string Parameters[NumberOfParameters - 1];
			UsedBytes = UsedBytes + sizeof(Parameters);
		}
		char LastParameter[Length - UsedBytes];

		break;
	case ChunkType.dwChunkType == 'LACs':
		UnitSpecifierType3 UnitSpecifier;
		string PixelWidth;
		char PixelHeight[Length - sizeof(UnitSpecifier) - sizeof(PixelWidth)];

		break;
	case ChunkType.dwChunkType == 'gFIg':
		BYTE DisposalMethod;
		BYTE UserInputFlag;
		WORD DelayTime;

		break;
	case ChunkType.dwChunkType == 'xFIg':
		char ApplicationId[8];
		char AuthCode[3];
		BYTE ApplicationData[Length - 11];
		break;
	case ChunkType.dwChunkType == 'tFIg':
		DWORD TextGridLeft, TextGridTop, TextGridWidth, TextGridHeight;
		BYTE CharCellWidth, CharacterCellHeight;
		BYTE ForeR, ForeG, ForeB;
		BYTE BackR, BackG, BackB;
		char PlainTextData[Length - 24];
		break;
	} data;

	if (Length >= 2000000)
	{
		$print("DEBUG: index", array_index);
		$print("DEBUG: Length", Length);
	}
	else
	{
		var size = Length - (current_offset - nOffsetDataBegin);
		if (size)
			BYTE UnknownData[size]; // Any non-described chunk
	}

	DWORD CRC; // Chunk cyclic redundancy code
};

// PNG file structure
public struct PNG_FILE
{
	// PNG file signature
	PNG_SIGNATURE Signature;
	$assert(Signature.SignaturePack.SignatureHigh == 0x0d0a1a0a && Signature.SignaturePack.SignatureLow == 0x89504e47);

	var ImageColorType, ImageBitDepth;
	[noindex] Chunk Chunks[*];
};
