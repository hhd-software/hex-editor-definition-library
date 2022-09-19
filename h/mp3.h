// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma once
#include "stddefs.h"

#pragma byte_order(BigEndian)

#pragma script("get_doc_size.js")
#pragma script("search_mp3_frame.js")

// TODO: array construction
/*
enum Id3Genre<BYTE>
{
 "Blues",
 "Classic Rock",
 "Country",
 "Dance",
 "Disco",
 "Funk",
 "Grunge",
 "Hip-Hop",
 "Jazz",
 "Metal",
 "New Age",
 "Oldies",
 "Other",
 "Pop",
 "R&B",
 "Rap",
 "Reggae",
 "Rock",
 "Techno",
 "Industrial",
 "Alternative",
 "Ska",
 "Death Metal",
 "Pranks",
 "Soundtrack",
 "Euro-Techno",
 "Ambient",
 "Trip-Hop",
 "Vocal",
 "Jazz+Funk",
 "Fusion",
 "Trance",
 "Classical",
 "Instrumental",
 "Acid",
 "House",
 "Game",
 "Sound Clip",
 "Gospel",
 "Noise",
 "AlternRock",
 "Bass",
 "Soul",
 "Punk",
 "Space",
 "Meditative",
 "Instrumental Pop",
 "Instrumental Rock",
 "Ethnic",
 "Gothic",
 "Darkwave",
 "Techno-Industrial",
 "Electronic",
 "Pop-Folk",
 "Eurodance",
 "Dream",
 "Southern Rock",
 "Comedy",
 "Cult",
 "Gangsta",
 "Top 40",
 "Christian Rap",
 "Pop/Funk",
 "Jungle",
 "Native American",
 "Cabaret",
 "New Wave",
 "Psychadelic",
 "Rave",
 "Showtunes",
 "Trailer",
 "Lo-Fi",
 "Tribal",
 "Acid Punk",
 "Acid Jazz",
 "Polka",
 "Retro",
 "Musical",
 "Rock & Roll",
 "Hard Rock",
 "Unknown",
};
*/

struct Id3Tag
{
	char Title[30];
	char Artist[30];
	char Album[30];
	char Year[4];
	char Comment[30];

	if (Comment[28] == 0 && Comment[29] != 0)
	{
		// TODO: ID3 v1.1 (with track number)
		$print("track", Comment[29]);
	}

	//Id3Genre genre;
	BYTE genre;
};

enum V2EFlags : USHORT
{
	FLAG_EXT_TAG_IS_AN_UPDATE = 2,
	FLAG_EXT_CRC_PRESENT = 4,
	FLAG_EXT_TAG_RESTRICTIONS = 8,
};

struct Id3v2ExtendedHeader
{
	DWORD dwSize;
	$assert(dwSize >= 6, "Hex editor is unable to parse ID3v2 tag - extended header size is <6");

	BYTE nFlagDataLen;
	V2EFlags extended_flags;

	var nExtraLen = 0;
	if ((flags & FLAG_EXT_CRC_PRESENT) && nFlagDataLen == 5)
	{
		DWORD crc;
		nExtraLen = sizeof(crc);
	}

	$assert(dwSize - sizeof(nNumberOfFlags) - sizeof(extended_flags) - nExtraLen >= 0, "Hex editor is unable to parse ID3v2 tag - padding size is wrong");
	BYTE padding[dwSize - sizeof(nNumberOfFlags) - sizeof(extended_flags) - nExtraLen];
};

enum V2FrameHeaderFalgs1 : BYTE
{
	TAG_ALTER_PRESERVATION = 2,
	TAG_FILE_ALTER_PRESENTATION = 4,
	READ_ONLY = 8,
};

enum V2FrameHeaderFalgs2 : BYTE
{
	GROUPING_IDENTITY = 2,
	COMPRESSION = 16,
	ENCRYPTION = 32,
	UNSYNCHRONIZATION = 64,
	DATA_LENGHT_INDICATOR = 128,
};


struct Id3v2FrameHeader
{
	char ID[4];
	DWORD dwSize;
	V2FrameHeaderFalgs1 nFlags1;
	V2FrameHeaderFalgs2 nFlags2;
};


struct Id3v2Frame
{
	if (V2FrameSize <= 0)
		$break_array(false);

	Id3v2FrameHeader frame_header;
	if (frame_header.ID[0] == 0)
	{
		$break_array(false);
	}
	else
	{
		BYTE frame_data[frame_header.dwSize];
	}

	V2FrameSize = V2FrameSize - sizeof(frame_header) - frame_header.dwSize;
};

enum V2Flags : BYTE
{
	UNSYNCHRONISATION_USED = 1,
	EXTENDED_HEADER_PRESENT = 2,
	EXPERIMENTAL_TAG = 4
};

struct Id3v2Header
{
	BYTE nVersion; // this byte will never be $FF
	BYTE nRevision; // this byte will never be $FF

	V2Flags flags;
	DWORD dwSize;
};


struct Id3v2Tag
{
	Id3v2Header header;

	var nRealSize = header.dwSize & 0xff;
	nRealSize = nRealSize << 7;
	nRealSize = nRealSize | (header.dwSize & 0xff00);
	nRealSize = nRealSize << 7;
	nRealSize = nRealSize | (header.dwSize & 0xff0000);
	nRealSize = nRealSize << 7;
	nRealSize = nRealSize | (header.dwSize & 0xff000000);

	var nRealSize = header.dwSize;

	var ext_header_size = 0;
	if ((header.flags & UNSYNCHRONISATION_USED) || (header.flags & EXPERIMENTAL_TAG) || header.nVersion != 3)
	{
		BYTE unknown_tag_data[nRealSize];
	}
	else if (header.flags & EXTENDED_HEADER_PRESENT)
	{
		Id3v2ExtendedHeader extended_header;
		ext_header_size = sizeof(extended_header.dwSize);
	}

	var V2FrameSize = nRealSize - ext_header_size;

	// at least 1 frame
	$assert(V2FrameSize >= 7, "Hex editor is unable to parse ID3v2 tag - no frames");
	Id3v2Frame frames[*];
};


struct Id3v2Footer
{
	BYTE nVersion;
	BYTE nRevision;
	BYTE nFlags;
	DWORD dwSize;
};

#pragma byte_order(LittleEndian)

// TODO: check why not working (see layer_desc)
public struct MpegFrameHeader
{
	DWORD frame_sync : 11;
	DWORD mpeg_version : 2;
	DWORD layer_desc : 2;
	DWORD protection_bit : 1;
	DWORD bitrate_index : 4;
	DWORD sampling_rate : 2;
	DWORD padding_bit : 1;
	DWORD private_bit : 1;
	DWORD channel_mode : 2;
	DWORD mode_extension : 2;
	DWORD copyright : 1;
	DWORD original : 1;
	DWORD emphasis : 2;
};
#pragma byte_order(BigEndian)

public struct MpegFrame
{
	MpegFrameHeader mpeg_header;

	// select bit rate index
	var BitRate = 0;
	if ((mpeg_header.mpeg_version == 3 && mpeg_header.layer_desc == 3) ||
		((mpeg_header.mpeg_version == 2 || mpeg_header.mpeg_version == 0) && mpeg_header.layer_desc == 3))
	{
		// MPEG v.1 , Layer 1
		// or
		// MPEG v.2 or v.2.5, Layer 1
		switch (mpeg_header.bitrate_index)
		{
		case 1:
			BitRate = 32;
			break;
		case 2:
			BitRate = 64;
			break;
		case 3:
			BitRate = 96;
			break;
		case 4:
			BitRate = 128;
			break;
		case 5:
			BitRate = 160;
			break;
		case 6:
			BitRate = 192;
			break;
		case 7:
			BitRate = 224;
			break;
		case 8:
			BitRate = 256;
			break;
		case 9:
			BitRate = 288;
			break;
		case 10:
			BitRate = 320;
			break;
		case 11:
			BitRate = 352;
			break;
		case 12:
			BitRate = 384;
			break;
		case 13:
			BitRate = 416;
			break;
		case 14:
			BitRate = 448;
			break;
		}
	}
	else if ((mpeg_header.mpeg_version == 3 && mpeg_header.layer_desc == 2) ||
		((mpeg_header.mpeg_version == 2 || mpeg_header.mpeg_version == 0) && mpeg_header.layer_desc == 2))
	{
		// MPEG v.1, Layer 2
		// or
		// MPEG v.2 or v.2.5, Layer 2
		switch (mpeg_header.bitrate_index)
		{
		case 1:
			BitRate = 32;
			break;
		case 2:
			BitRate = 48;
			break;
		case 3:
			BitRate = 56;
			break;
		case 4:
			BitRate = 64;
			break;
		case 5:
			BitRate = 80;
			break;
		case 6:
			BitRate = 96;
			break;
		case 7:
			BitRate = 112;
			break;
		case 8:
			BitRate = 128;
			break;
		case 9:
			BitRate = 160;
			break;
		case 10:
			BitRate = 192;
			break;
		case 11:
			BitRate = 224;
			break;
		case 12:
			BitRate = 256;
			break;
		case 13:
			BitRate = 320;
			break;
		case 14:
			BitRate = 384;
			break;
		}
	}
	else if ((mpeg_header.mpeg_version == 3 && mpeg_header.layer_desc == 1) ||
		((mpeg_header.mpeg_version == 2 || mpeg_header.mpeg_version == 0) && mpeg_header.layer_desc == 1))
	{
		// MPEG v.1, Layer 3
		// or
		// MPEG v.2 or v.2.5, Layer 3
		switch (mpeg_header.bitrate_index)
		{
		case 1:
			BitRate = 32;
			break;
		case 2:
			BitRate = 40;
			break;
		case 3:
			BitRate = 48;
			break;
		case 4:
			BitRate = 56;
			break;
		case 5:
			BitRate = 64;
			break;
		case 6:
			BitRate = 80;
			break;
		case 7:
			BitRate = 96;
			break;
		case 8:
			BitRate = 112;
			break;
		case 9:
			BitRate = 128;
			break;
		case 10:
			BitRate = 160;
			break;
		case 11:
			BitRate = 192;
			break;
		case 12:
			BitRate = 224;
			break;
		case 13:
			BitRate = 256;
			break;
		case 14:
			BitRate = 320;
			break;
		}
	}

	//select sample rate
	var SampleRate = 0;
	if (mpeg_header.mpeg_version == 3)
	{
		// MPEG 1
		switch (mpeg_header.sampling_rate)
		{
		case 0:
			SampleRate = 44100;
			break;
		case 1:
			SampleRate = 48000;
			break;
		case 2:
			SampleRate = 32000;
			break;
		}
	}
	else if (mpeg_header.mpeg_version == 2)
	{
		// MPEG 2
		switch (mpeg_header.sampling_rate)
		{
		case 0:
			SampleRate = 22050;
			break;
		case 1:
			SampleRate = 24000;
			break;
		case 2:
			SampleRate = 16000;
			break;
		}
	}
	else if (mpeg_header.mpeg_version == 0)
	{
		// MPEG 2.5
		switch (mpeg_header.sampling_rate)
		{
		case 0:
			SampleRate = 11025;
			break;
		case 1:
			SampleRate = 12000;
			break;
		case 2:
			SampleRate = 8000;
			break;
		}
	}

	// TODO: use padding!!!
	var Padding = 0;

	var FrameSize = (144 * (BitRate * 1000) / SampleRate) + Padding;
	//$print("FrameSize",FrameSize);

	BYTE frame_data[FrameSize];
};

public struct Mp3Tag
{
	char id[3];

	if (id == "TAG")
	{
		Id3Tag id3_header;
		//SizeLeft = SizeLeft - sizeof(id3_header);
	}
	else if (id == "ID3")
	{
		Id3v2Tag id3_header;
		//SizeLeft = SizeLeft - sizeof(id3_header);
	}
	else if (id == "3DI")
	{
		Id3v2Footer id3_footer;
		//SizeLeft = SizeLeft - sizeof(id3_footer);
	}
};

struct MpegFrameHolder
{
	var nMpegFrame = JS_SearchForMpegFrame(current_offset);
	$shift_by(nMpegFrame - current_offset);
	MpegFrame frame;
};

public struct Mp3File
{
	//var SizeLeft = GetDocumentSize();
	[noindex] MpegFrameHolder frames[*];
};
