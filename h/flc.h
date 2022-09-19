// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"
#pragma script("get_doc_size.js")

struct FLC_Header
{
	WORD wFrameCount;
	WORD wScreenWidth;
	nScreenHeight = wScreenHeight; // save for future use by FliBrun

	WORD wScreenHeight;
	WORD wColorDepth;
	WORD wFlags;

	$assert(wFlags == 3, "Hex editor is unable to parse file");

	DWORD dwSpeed;
	WORD wReserved;

	DWORD dwCreationTime;
	DWORD dwUpdateTime;

	DWORD dwUpdater;

	WORD wAspectX;
	WORD wAspectY;

	BYTE reserved[38];

	DWORD dwFirstFrameOffset;
	DWORD dwSecondFrameOffset;

	BYTE reserved[40];
};

struct FLC_Prefix
{
	WORD wChunkCount;
	BYTE reserved[8];
};

enum ChunkType : WORD
{
	FLI_COLOR256 = 4,
	FLI_SS2 = 7,
	FLI_COLOR = 11,
	FLI_LC = 12,
	FLI_BLACK = 13,
	FLI_BRUN = 15,
	FLI_COPY = 16,
	FLI_PSTAMP = 18
};

struct FliColor256
{
	WORD wPackets;
	struct Packet
	{
		BYTE nColorIndexSkipCount;
		BYTE nColorCount;
		COLORREF colors[nColorCount];
	}packets[wPackets];
};

struct FliCopy
{
	WORD wPixels;
	if (dwSize - 4 == sizeof(COLORREF) * wPixels)
		COLORREF pixels[wPixels]; // TODO: like this???
};

struct FliBrun
{
	if (nScreenHeight != 0)
	{
		struct Line
		{
			BYTE nPacketCount;
			struct Packet
			{
				char nTypeOrSize;
				if (nTypeOrSize < 0)
				{
					// it is count
					COLORREF pixels[-nTypeOrSize];
				}
				else
				{
					// it is type
					COLORREF single_pixel;
					$print("replicate count", nTypeOrSize);
				}
			}packets[nPacketCount];
		}lines[nScreenHeight];
	}
};

// This chunk contains the differences between the previous frame and this frame
struct FliLc
{
	WORD wFirstLineChunkPosition;
	WORD wLineCount;

	struct Line
	{
		BYTE xPos;
		BYTE nPackets;
		struct Packet
		{
			char nTypeOrSize;
			if (nTypeOrSize < 0)
			{
				// it is count
				COLORREF pixels[-nTypeOrSize];
			}
			else
			{
				// it is type
				COLORREF single_pixel;
				$print("replicate count", nTypeOrSize);
			}
		}packets[nPackets];
	}lines[wLineCount];
};

struct FliSs2
{
	WORD wLineCount;

	struct Line
	{
		WORD wWord;

		// TODO: while
		while (true)
		{
			var nCount = 0;
			if ((wWord & 0xC000) == 0)
			{
				// it's a count
				nCount = wWord;
				break;
			}
			else if ((wWord & 0xC000) == 0xC000)
			{
				// line skip count
				$print("line skip count", wWord);
			}
			else if ((wWord & 0xC000) == 0x8000)
			{
				// last byte in line
				$print("last byte of current line", (wWord & 0xFF));
			}
		}

		if (nCount)
		{
			struct Packet
			{
				char nTypeOrSize;
				if (nTypeOrSize < 0)
				{
					// it is count
					COLORREF pixels[-nTypeOrSize];
				}
				else
				{
					// it is type
					COLORREF single_pixel;
					$print("replicate count", nTypeOrSize);
				}
			}packets[nCount];
		}
	}lines[wLineCount];
};

struct FliPstamp
{
	DWORD dwSize;
	WORD wPstampId;
	WORD wHeight;
	WORD wWidth;
	WORD wXLate;
};

struct FLC_FrameChunk
{
	WORD wChunkCount;
	BYTE reserved[8];

	struct Chunk
	{
		DWORD dwSize;
		ChunkType wType;

		var nOffset = current_offset;
		switch (wType)
		{
		case FLI_COLOR256:
		case FLI_COLOR:
			FliColor256 color256;
			break;
		case FLI_COPY:
			FliCopy copy;
			break;
		case FLI_BRUN:
			FliBrun brun;
			break;
		case FLI_LC:
			FliLc lc;
			break;
		case FLI_SS2:
			FliSs2 ss2;
			break;
		case FLI_PSTAMP:
			FliPstamp stamp;
			break;
		}

		BYTE not_parsed_data[dwSize - (current_offset - nOffset)];
	}chunks[wChunkCount];
};

struct FLC_OrigHeader
{
	WORD wFrames;
	WORD wWidth;
	WORD wHeight;
	WORD wDepth;
	WORD wFlags;
	WORD wSpeed;
	BYTE reserved[110];
};

struct AnimatorProPIC_File
{
	WORD wWidth;
	WORD wHeight;
	WORD wCoordX, wCoordY;
	DWORD dwUserid;
	BYTE nDepth;
	BYTE reserved[45];
};

struct AnimatorProCOL_File
{
	WORD wVersion;
	COLORREF colors[(nDocSize - current_offset) / sizeof(COLORREF)];
};

struct ChunkList
{
	if (nDocSize <= 0)
		$break_array(false);

	DWORD dwSize;
	WORD wSignature;

	var nScreenHeight = 0;

	switch (wSignature)
	{
	case 0xAF12:
		FLC_Header header;
		break;
	case 0xF100:
		FLC_Prefix prefix;
		break;
	case 0xF1FA:
		FLC_FrameChunk chunk;
		break;
	case 0xAF11:
		FLC_OrigHeader header;
		break;
	case 0x9500:
		AnimatorPIC_File pic_file;
		break;
	case 0xB123:
		AnimatorProCOL_File col_file;
		break;
	}

	nDocSize = nDocSize - (current_offset - this);
};

public struct FLC_File
{
	var nDocSize = GetDocumentSize();
	ChunkList chunks[*];
};

public struct AnimatorPIC_File
{
	WORD wType;
	$assert(wType = 0x9119, "Hex editor is unable to parse file");

	WORD wWidth, wHeight;
	WORD wCoordX, wCoordY;
	BYTE nDepth;
	BYTE nCompress;
	DWORD dwDatasize;
	BYTE reserved[16];
};

public struct AnimatorCOL_File
{
	var nDocSize = GetDocumentSize();
	$assert(nDocSize == 768, "Hex editor is unable to parse file: illegal file size");
	COLORREG colors[256];
};

struct Point
{
	WORD x, y, z;
};

// same for AnimatorPro
public struct AnimatorPLY_File
{
	WORD wPoints;
	DWORD dwReserved;
	BYTE nClosed;
	BYTE nMagic;
	$assert(nMagic == 0x99, "Hex editor is unable to parse file: illegal file size");

	Point points[wPoints];
};

public struct AnimatorTWE_File
{
	WORD wMagic;
	$assert(nDocSize == 0x1995, "Hex editor is unable to parse file: illegal file size");
	WORD wVersion;
	DWORD dwTcount;
	BYTE reserved[8];
	DWORD dwLinkCount;

	struct Link
	{
		DWORD dwIndex; // index of the point in the first shape, 
		DWORD dwEndIndex; // index of the point in the ending shape
	}links[dwLinkCount];

	AnimatorPLY_File starting_shape, ending_shape;
};


public struct AnimatorOPT_File
{
	WORD wMagic;
	$assert(nDocSize == 0x1A3F, "Hex editor is unable to parse file: illegal file size");

	WORD wCount;
	// 50 bytes each
	struct Record
	{
		DWORD dwLink;
		Point spincenter;
		Point spinaxis;
		Point spinturns;

		DWORD spininter;
		Point sizecenter;
		WORD xmultiplier, xdivisor;
		WORD ymultiplier, ydivisor;

		WORD bothmult, bothdiv;
		Point linearmove;
	}records[wCount];
};
