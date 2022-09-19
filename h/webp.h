// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see https://developers.google.com/speed/webp/docs/riff_container for specifications

#include "wav.h"			// WAVEFORMATEX
#include "tiff.h"			// TIFF_IMAGE_FILE_DIRECTORY_ENTRY_LE
#include "icc.h"			// ICC

#pragma byte_order(LittleEndian)

[display(format("{0}", b[2] << 16 | b[1] << 8 | b[0]))]
struct Int24
{
	BYTE b[3];
};

struct VP8Chunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

struct VP8LChunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

struct VP8XChunk
{
	DWORD dwChunkSize;
	DWORD Reserved : 2;
	DWORD ICC : 1;
	DWORD Alpha : 1;
	DWORD Exif : 1;
	DWORD XMP : 1;
	DWORD Animation : 1;
	DWORD Reserved2 : 1;
	DWORD Reserved3 : 24;

	Int24 CanvasWidth;
	Int24 CanvasHeight;
};

[display(format("#{0b16w2arf0}{1b16w2arf0}{2b16w2arf0}{3b16w2arf0}", R, G, B, A))]
struct Color
{
	BYTE B;
	BYTE G;
	BYTE R;
	BYTE A;
};

struct AnimChunk
{
	DWORD dwChunkSize;
	Color BackgroundColor;
	USHORT LoopCount;
};

struct AnimFChunk
{
	DWORD dwChunkSize;
	Int24 FrameX;
	Int24 FrameY;
	Int24 FrameHeight;
	Int24 FrameWidth;
	DWORD FrameDuration : 24;
	DWORD Reserved : 6;
	DWORD BlendingMethod : 1;
	DWORD DisposalMethod : 1;
};

struct AlphaChunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

struct ColorProfileChunk
{
	DWORD dwChunkSize;
#pragma byte_order(BigEndian)
	ICC icc;
	//move to the end of chunk
	$shift_by(icc.pStart - current_offset);
	$shift_by(dwChunkSize);
#pragma byte_order(LittleEndian)
};

struct ExifChunk
{
	DWORD dwChunkSize;
	var nBeginning = current_offset;
	TIFF_IMAGE_FILE_HEADER ifh;
	$shift_by(dwChunkSize - 8);
};

struct XmpChunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

[display(id.FourCCs)]
struct WebpBlock
{
	if (SizeLeft <= 0)
		$break_array(false);

	FOURCC id;

	var nChunkBeginning = current_offset;

	switch (id.FourCC)
	{
	case 'VP8 ':
		VP8Chunk vp8;
		break;
	case 'VP8L':
		VP8LChunk vp8_lossless;
		break;
	case 'VP8X':
		VP8XChunk vp8_extended;
		break;
	case 'ANIM':
		AnimChunk anim;
		break;
	case 'ANMF':
		AnimFChunk anim_f;
		break;
	case 'ALPH':
		AlphaChunk alpha;
		break;
	case 'ICCP':
		ColorProfileChunk color_profile;
		break;
	case 'EXIF':
		ExifChunk exif;
		break;
	case 'XMP ':
		XmpChunk xmp;
		break;
	default:
		UnknownChunk unknown_chunk;
	}

	var nSize = current_offset - nChunkBeginning;
	BYTE padding[nSize % 2];

	SizeLeft = SizeLeft - nSize;
};


public struct Webp
{
	var StreamType;
	FOURCC RIFF;
	$assert(RIFF.FourCC == 'RIFF', "Not a RIFF file");
	DWORD	fileSize;
	FOURCC	type;

	$assert(type.FourCC == 'WEBP', "Not a WEBP file");

	var SizeLeft = fileSize - sizeof(type);

	[noindex]
	WebpBlock chunks[*];
};