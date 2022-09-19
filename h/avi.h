// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// AVI files use Little Endian byte order
#pragma byte_order(LittleEndian)

#pragma pack(2)

#include "bitmap.h"
#include "wav.h" // WAVEFORMATEX

#pragma script("get_doc_size.js")

// Several defines from aviriff.h from MSDN
#define streamtypeVIDEO ('vids')
#define streamtypeAUDIO ('auds')
#define streamtypeMIDI ('mids')
#define streamtypeTEXT ('txts')

enum AviMainHeaderFlags : DWORD
{
	AVIF_HASINDEX = 0x00000010,
	AVIF_MUSTUSEINDEX = 0x00000020,
	AVIF_ISINTERLEAVED = 0x00000100,
	AVIF_TRUSTCKTYPE = 0x00000800,
	AVIF_WASCAPTUREFILE = 0x00010000,
	AVIF_COPYRIGHTED = 0x00020000,
};

enum AviStreamHeaderFlags : DWORD
{
	AVISF_DISABLED = 0x00000001,
	AVISF_VIDEO_PALCHANGES = 0x00010000,
};

struct AVIMAINHEADER
{
	DWORD cb;
	DWORD dwMicroSecPerFrame;
	DWORD dwMaxBytesPerSec;
	DWORD dwPaddingGranularity;
	AviMainHeaderFlags dwFlags;
	DWORD dwTotalFrames;
	DWORD dwInitialFrames;
	DWORD dwStreams;
	DWORD dwSuggestedBufferSize;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwReserved[4];
};

struct AVISTREAMHEADER
{
	DWORD cb;
	FOURCC fccType;

	switch (fccType.FourCC)
	{
	case streamtypeAUDIO:
		$print("Description", "Audio stream");
		break;
	case streamtypeMIDI:
		$print("Description", "MIDI stream");
		break;
	case streamtypeTEXT:
		$print("Description", "Text stream");
		break;
	case streamtypeVIDEO:
		$print("Description", "Video stream");
		break;
	default:
		$print("Description", "Unknown stream");
	}

	// Capture stream type for later header selection
	StreamType = fccType.FourCC;

	FOURCC fccHandler;
	AviStreamHeaderFlags dwFlags;
	WORD wPriority;
	WORD wLanguage;
	DWORD dwInitialFrames;
	DWORD dwScale;
	DWORD dwRate;
	DWORD dwStart;
	DWORD dwLength;
	DWORD dwSuggestedBufferSize;
	DWORD dwQuality;
	DWORD dwSampleSize;
	struct {
		short int left;
		short int top;
		short int right;
		short int bottom;
	} rcFrame;
};

enum WaveFormatEnum : WORD
{
	WAVE_FORMAT_PCM = 1,
};

enum AviOldIndexFlagsEnum : DWORD
{
	AVIIF_LIST = 0x00000001,
	AVIIF_KEYFRAME = 0x00000010,
	AVIIF_NO_TIME = 0x00000100,
};

/*
struct WAVEFORMATEX
{
 WaveFormatEnum wFormatTag; // format type
 WORD nChannels; // number of channels (i.e. mono, stereo...)
 DWORD nSamplesPerSec; // sample rate
 DWORD nAvgBytesPerSec; // for buffer estimation
 WORD nBlockAlign; // block size of data
 WORD wBitsPerSample; // number of bits per sample of mono data
 if (wFormatTag!=WAVE_FORMAT_PCM)
 {
 WORD cbSize; // the count in bytes of the size of
 BYTE additional[cbSize];
 }
};*/

struct AVISUPERINDEX
{
	WORD wLongsPerEntry; // ==4
	BYTE bIndexSubType; // ==0 (frame index) or AVI_INDEX_SUB_2FIELD 
	BYTE bIndexType; // ==AVI_INDEX_OF_INDEXES
	DWORD nEntriesInUse; // offset of next unused entry in aIndex
	FOURCC dwChunkId; // chunk ID of chunks being indexed, (i.e. RGB8)
	DWORD dwReserved[3]; // must be 0
	struct
	{
		ULONGLONG qwOffset; // 64 bit offset to sub index chunk
		DWORD dwSize; // 32 bit size of sub index chunk
		DWORD dwDuration; // time span of subindex chunk (in stream ticks)
	} aIndex[nEntriesInUse];
};

struct ListOrChunk;
struct Blocks;
struct RIFFHeader;

struct ListOrChunk
{
	FOURCC id;

	switch (id.FourCC)
	{
	case 'LIST':
		DWORD listSize;
		FOURCC listType;
		var SizeLeft = listSize - sizeof(listType);
		Blocks chunks;
		break;
	case 'avih': // avi main header
		AVIMAINHEADER mainheader;
		break;
	case 'strh':
		AVISTREAMHEADER streamheader;
		break;
	case 'strf':
		switch (StreamType)
		{
		case streamtypeVIDEO:
			DWORD chunkSize;
			BITMAPINFO vidformat;
			break;
		case streamtypeAUDIO:
			WaveFormatChunk wavformat;
			break;
		}
		break;
	case 'strn':
		DWORD chunkSize;
		string Description;
		break;
	case 'indx':
		DWORD chunkSize;
		AVISUPERINDEX index;
		BYTE junk[chunkSize - sizeof(index)];
		break;
	case 'idx1':
		DWORD chunkSize;
		[noindex]
		struct AVIOLDINDEX
		{
			char dwChunkId[4];
			AviOldIndexFlagsEnum dwFlags;
			DWORD dwOffset;
			DWORD dwSize;
		} aIndex[chunkSize / sizeof(AVIOLDINDEX)];
		break;
	default:
		DWORD chunkSize;
		BYTE data[chunkSize + (chunkSize % 2)];
	}
};

struct Blocks
{
	[noindex] struct
	{
		if (SizeLeft <= 0)
			$break_array(false);
		ListOrChunk chunk;
		SizeLeft = SizeLeft - sizeof(chunk);
	} chunks[*];
};

struct RIFFHeader
{
	if (SizeLeftFile <= 0)
		$break_array(false);

	var StreamType;
	FOURCC RIFF; // FOURCC is defined in stddefs.h which is included from bitmap.h
	//$assert(RIFF.FourCC=='RIFF' || RIFF.FourCC=='JUNK',"Not a RIFF file");

	if (RIFF.FourCC == 'RIFF')
	{
		DWORD fileSize;
		FOURCC fileType;
		$assert(fileType.FourCCs == "AVI " || fileType.FourCCs == "AVIX", "Not an AVI file");

		var SizeLeft = fileSize - 4;
		var nStart = current_offset;
		Blocks chunks;

		// add additional data if not all used
		if (SizeLeft > (current_offset - nStart))
			BYTE not_parsed_data[SizeLeft - (current_offset - nStart)];
	}
	else
	{
		BYTE unknown[SizeLeftFile - sizeof(RIFF)];
	}

	SizeLeftFile = SizeLeftFile - (current_offset - this);
};

public struct RIFFHeaders
{
	var SizeLeftFile = GetDocumentSize();
	[noindex] RIFFHeader headers[*];
};
