// Copyright (c) 2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see https://qoiformat.org/qoi-specification.pdf
// see https://github.com/phoboslab/qoi

#include "stddefs.h"

#pragma pack(1)

// PNG uses Big Endian byte order
#pragma byte_order(BigEndian)

#define QOI_OP_INDEX  0x00
#define QOI_OP_DIFF   0x40
#define QOI_OP_LUMA   0x80
#define QOI_OP_RUN    0xc0
#define QOI_OP_RGB    0xfe
#define QOI_OP_RGBA   0xff

#define QOI_MASK_2    0xc0

struct qoi_header
{
	char magic[4]; 		// magic bytes "qoif"
	uint32 width; 		// image width in pixels (BE)
	uint32 height; 		// image height in pixels (BE)
	uint8 channels; 	// 3 = RGB, 4 = RGBA
	uint8 colorspace;  	// 0 = sRGB with linear alpha
						// 1 = all channels linear
};

struct qoi_op_rgb
{
	uint8 tag;
	uint8 red;
	uint8 green;
	uint8 blue;
};

struct qoi_op_rgba
{
	uint8 tag;
	uint8 red;
	uint8 green;
	uint8 blue;
	uint8 alpha;
};

struct qoi_op_index
{
	uint8 tag : 2;
	uint8 index : 6;
};

struct qoi_op_diff
{
	uint8 tag : 2;
	uint8 dr : 2;
	uint8 dg : 2;
	uint8 db : 2;
};

struct qoi_op_luma
{
	uint8 tag : 2;
	uint8 dif_green : 6;
	uint8 dr_dg : 4;
	uint8 db_dg : 4;
};

struct qoi_op_run
{
	uint8 tag : 2;
	uint8 run : 6;
};

[display(type)]
union qoi_pixel
{
hidden:
	uint8 tag;

visible:
	if (tag == QOI_OP_RGB)
	{
		$print("type", "RGB");
		qoi_op_rgb rgb;
	}
	else if (tag == QOI_OP_RGBA)
	{
		$print("type", "RGBA");
		qoi_op_rgba rgba;
	}
	else if (((tag & QOI_MASK_2) == QOI_OP_INDEX))
	{
		$print("type", "Index");
		qoi_op_index index;
	}
	else if ((tag & QOI_MASK_2) == QOI_OP_DIFF)
	{
		$print("type", "Diff");
		qoi_op_diff diff;
	}
	else if ((tag & QOI_MASK_2) == QOI_OP_LUMA)
	{
		$print("type", "Luma");
		qoi_op_luma luma;
	}
	else if ((tag & QOI_MASK_2) == QOI_OP_RUN)
	{
		$print("type", "Run");
		qoi_op_run run;
	}
};

public struct QOI_FILE
{
	qoi_header Signature;
	$assert(Signature.magic == "qoif");

	[noindex] qoi_pixel Pixels[*];
};
