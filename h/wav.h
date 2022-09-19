// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma once
#include "stddefs.h"

union FOURCC
{
	char FourCCs[4];
	DWORD FourCC;
};

enum WaveFormats<WORD>
{
	WAVE_FORMAT_PCM = 1,
	FORMAT_MULAW = 0x101,
	IBM_FORMAT_ALAW = 0x102,
	IBM_FORMAT_ADPCM = 0x103,

	WAVE_FORMAT_G723_ADPCM = 0x0014,			/* Antex Electronics Corporation */
	WAVE_FORMAT_ANTEX_ADPCME = 0x0033,			/* Antex Electronics Corporation */
	WAVE_FORMAT_APTX = 0x0025,			/* Audio Processing Technology */
	WAVE_FORMAT_AUDIOFILE_AF36 = 0x0024,			/* Audiofile, Inc. */
	WAVE_FORMAT_AUDIOFILE_AF10 = 0x0026,			/* Audiofile, Inc. */
	WAVE_FORMAT_CONTROL_RES_VQLPC = 0x0034,		/* Control Resources Limited */
	WAVE_FORMAT_CONTROL_RES_CR10 = 0x0037,		/* Control Resources Limited */
	WAVE_FORMAT_CREATIVE_ADPCM = 0x0200,			/* Creative Labs, Inc */
	WAVE_FORMAT_DOLBY_AC2 = 0x0030,			/* Dolby Laboratories */
	WAVE_FORMAT_DSPGROUP_TRUESPEECH = 0x0022, /* DSP Group, Inc */
	WAVE_FORMAT_DIGISTD = 0x0015,			/* DSP Solutions, Inc. */
	WAVE_FORMAT_DIGIFIX = 0x0016,			/* DSP Solutions, Inc. */
	WAVE_FORMAT_DIGIREAL = 0x0035,			/* DSP Solutions, Inc. */
	WAVE_FORMAT_DIGIADPCM = 0x0036,			/* DSP Solutions, Inc. */
	WAVE_FORMAT_ECHOSC1 = 0x0023,			/* Echo Speech Corporation */
	WAVE_FORMAT_FM_TOWNS_SND = 0x0300,			/* Fujitsu Corp. */
	WAVE_FORMAT_IBM_CVSD = 0x0005,			/* IBM Corporation */
	WAVE_FORMAT_OLIGSM = 0x1000,			/* Ing C. Olivetti & C., S.p.A. */
	WAVE_FORMAT_OLIADPCM = 0x1001,			/* Ing C. Olivetti & C., S.p.A. */
	WAVE_FORMAT_OLICELP = 0x1002,			/* Ing C. Olivetti & C., S.p.A. */
	WAVE_FORMAT_OLISBC = 0x1003,			/* Ing C. Olivetti & C., S.p.A. */
	WAVE_FORMAT_OLIOPR = 0x1004,			/* Ing C. Olivetti & C., S.p.A. */
	WAVE_FORMAT_DVI_ADPCM = 0x0011,			/* Intel Corporation */
	WAVE_FORMAT_UNKNOWN = 0x0000,			/* Microsoft Corporation */
	WAVE_FORMAT_PCM = 0x0001,			/* Microsoft Corporation */
	WAVE_FORMAT_ADPCM = 0x0002,			/* Microsoft Corporation */
	WAVE_FORMAT_ALAW = 0x0006,			/* Microsoft Corporation */
	WAVE_FORMAT_MULAW = 0x0007,			/* Microsoft Corporation */
	WAVE_FORMAT_GSM610 = 0x0031,			/* Microsoft Corporation */
	WAVE_FORMAT_MPEG = 0x0050,			/* Microsoft Corporation */
	WAVE_FORMAT_NMS_VBXADPCM = 0x0038,			/* Natural MicroSystems */
	WAVE_FORMAT_OKI_ADPCM = 0x0010,			/* OKI */
	WAVE_FORMAT_SIERRA_ADPCM = 0x0013,			/* Sierra Semiconductor Corp */
	WAVE_FORMAT_SONARC = 0x0021,			/* Speech Compression */
	WAVE_FORMAT_MEDIASPACE_ADPCM = 0x0012,		/* Videologic */
	WAVE_FORMAT_YAMAHA_ADPCM = 0x0020,			/* Yamaha Corporation of America */
};

//*********************************************************************
// format structures
struct ADPCMCOEFSET
{
	int iCoef1;
	int iCoef2;
};


//**********************************************************************/

// WAVEFORMATEX
struct WaveFormatChunk
{
	DWORD dwChunkSize;

	var nBeginningOffset = current_offset;

	WaveFormats wFormatTag;        // Format category

	WORD nChannels;         // number of channels (i.e. mono, stereo, etc.)
	DWORD nSamplesPerSec;    // sample rate

	/*********************************************************************************
	For PCM data, the wAvgBytesPerSec field of the `fmt' chunk should be equal to the
	following formula rounded up to the next whole number:

								 wBitsPerSample
	wChannels x wBitsPerSecond x --------------
									   8
	/**********************************************************************************/

	DWORD nAvgBytesPerSec;   // for buffer estimation
	WORD nBlockAlign;       // block size of data

	var nSwitchBeginningOffset = current_offset;

	switch (wFormatTag)
	{
	case WAVE_FORMAT_MULAW:
		WORD wBitsPerSample;     // number of bits per sample of mono data
		break;
	case WAVE_FORMAT_PCM:
		WORD wBitsPerSample;     // number of bits per sample of mono data
		break;
	case WAVE_FORMAT_ADPCM:
		WORD wSamplesPerBlock;
		WORD wNumCoef;
		ADPCMCOEFSET aCoeff[wNumCoef];
		break;
	case WAVE_FORMAT_OKI_ADPCM:
		WORD wPole;
		break;
	case WAVE_FORMAT_DVI_ADPCM:
		WORD wSamplesPerBlock;
		break;
	case WAVE_FORMAT_SONARC:
		WORD wCompType;
		break;
	case WAVE_FORMAT_SIERRA_ADPCM:
	case WAVE_FORMAT_MEDIASPACE_ADPCM:
	case WAVE_FORMAT_CREATIVE_ADPCM:
		WORD wRevision;
		break;
	case WAVE_FORMAT_DSPGROUP_TRUESPEECH:
		WORD wRevision;
		break;
	case WAVE_FORMAT_DOLBY_AC2:
		WORD nAuxBitsCode;
		break;
	case WAVE_FORMAT_MPEG:
		WORD fwHeadLayer;
		DWORD dwHeadBitrate;
		WORD fwHeadMode;
		WORD fwHeadModeExt;
		WORD wHeadEmphasis;
		WORD fwHeadFlags;
		DWORD dwPTSLow;
		DWORD dwPTSHigh;
		break;
	}

	BYTE not_parsed_data[dwChunkSize - (current_offset - nBeginningOffset)];
};

struct CuePoint
{
	DWORD dwName;
	DWORD dwPosition;
	FOURCC fccChunk;
	DWORD dwChunkStart;
	DWORD dwBlockStart;
	DWORD dwSampleOffset;
};

struct CueChunk
{
	DWORD dwChunkSize;
	DWORD dwCuePoints;
	CuePoint cue_points[dwCuePoints];

	// TODO: check it (CueChunk size is dwCuePoints + cue_points[dwCuePoints], dwChunkSize is shared field for all types of Chunks)
	//sample
	//struct Chunk {DWORD id, DWORD dwChunkSize}
	//struct CueChunk : public Chunk

	$print("sizeof(CuePoint)", sizeof(CuePoint));
	BYTE extra_data[dwChunkSize /*- sizeof(dwChunkSize)*/ - sizeof(dwCuePoints) - dwCuePoints * sizeof(CuePoint)];
};

struct PlaySegment
{
	DWORD dwName;
	DWORD dwLength;
	DWORD dwLoops;
};

struct PlaylistChunk
{
	DWORD dwChunkSize;
	DWORD dwSegments;
	PlaySegment play_segments[dwSegments];

	// TODO: check it
	BYTE extra_data[dwChunkSize - sizeof(dwChunkSize) - sizeof(dwSegments) - dwSegments * sizeof(PlaySegment)];
};

struct LabelChunk
{
	DWORD dwChunkSize;
	DWORD dwLabelName;
	string label;
};

struct NoteChunk
{
	DWORD dwChunkSize;
	DWORD dwNoteName;
	string note;
};

struct LabelTxtChunk
{
	DWORD dwChunkSize;
	DWORD dwName;
	DWORD dwSampleLength;
	DWORD dwPurpose;
	WORD wCountry;
	WORD wLanguage;
	WORD wDialect;
	WORD wCodePage;

	$assert(dwChunkSize >= 24, "Hex Editor Neo is unable to parse file: data size is less then 0");
	BYTE data[dwChunkSize - 24];
};

struct FileChunk
{
	DWORD dwChunkSize;
	DWORD dwName;
	DWORD dwMedType;

	$assert(dwChunkSize >= 12, "Hex Editor Neo is unable to parse file: data size is less then 0");
	BYTE data[dwChunkSize - 12];
};

struct AssocDataList
{
	DWORD dwChunkSize;
};

struct FactChunk
{
	DWORD dwChunkSize;
	if (dwChunkSize == 4)
		DWORD dwUncompressedSize;
	else
		BYTE data[dwChunkSize];
};

struct ListSubChunk
{
	if (SizeSubChunks <= 0)
		$break_array(false);

	var nChunkBeginning = current_offset;

	FOURCC chunkID;
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];

	var nSize = current_offset - nChunkBeginning;
	BYTE padding[nSize % 2];

	SizeSubChunks = SizeSubChunks - sizeof(chunkID) - sizeof(dwChunkSize) - dwChunkSize - nSize % 2;
};

struct ListChunk
{
	DWORD dwChunkSize;
	FOURCC id;				// TODO: check this "wavl" label

	var SizeSubChunks = dwChunkSize - sizeof(dwChunkSize) - sizeof(id);
	[noindex] ListSubChunk chunks[*];
};

struct UnknownChunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

// no parsing
struct DataChunk
{
	DWORD dwChunkSize;
	BYTE data[dwChunkSize];
};

struct WaveListOrChunk
{
	FOURCC id;

	var nChunkBeginning = current_offset;
	switch (id.FourCC)
	{
	case 0x20746d66:
		//case 0x666d7420:		// 	'fmt '
		WaveFormatChunk format_chunk;
		break;
	case 'fact':
		FactChunk fact_chunk;
		break;
	case 0x20657563:		// 	'cue '
		CueChunk cue_block;
		break;
	case 'LIST':
		ListChunk list_chunk;
		break;
	case 'plst':
		PlaylistChunk playlist_chunk;
		break;
	case 'adtl':
		// just a wrapper for labl/note/ltxt/file
		AssocDataList assoc_data_list;
		break;
	case 'labl':
		LabelChunk label_chunk;
		break;
	case 'note':
		NoteChunk note_chunk;
		break;
	case 'ltxt':
		LabelTxtChunk label_txt_chunk;
		break;
	case 'file':
		FileChunk file_chunk;
		break;
	case 'DATA':
		DataChunk data_chunk;
		break;
	default:
		UnknownChunk unknown_chunk;
	}

	var nSize = current_offset - nChunkBeginning;
	BYTE padding[nSize % 2];
};

struct WaveBlocks
{
	[noindex] struct
	{
		if (SizeLeft <= 0)
			$break_array(false);
		WaveListOrChunk chunk;
		SizeLeft = SizeLeft - sizeof(chunk);
	} chunks[*];
};

public struct WavHeader
{
	var StreamType;
	FOURCC RIFF;			// FOURCC is defined in stddefs.h which is included from bitmap.h
	$assert(RIFF.FourCC == 'RIFF', "Not a RIFF file");
	DWORD fileSize;
	FOURCC type;

	$assert(type.FourCC == 'WAVE', "Not a WAVE file");

	var SizeLeft = fileSize - sizeof(type);

	WaveBlocks chunks;
};
