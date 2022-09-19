// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see "Truevision TGA FILE FORMAT SPECIFICATION Version 2.0"

#include "stddefs.h"

#pragma script("get_doc_size.js")

enum ColorMapType : BYTE
{
	NoColorMapData = 0,
	ColorMapIncluded
};

enum ImageType : BYTE
{
	NoImageData,
	UncompressedColorMappedImage,
	UncompressedTrueColorImage,
	UncompressedBWImage,

	CompressedColorMappedImage,
	CompressedTrueColorImage,
	CompressedBWImage,

	RunLengthEncodedColorMappedImage = 9,
	RunLengthEncodedTrueColorImage,
	RunLengthEncodedBWImage,
};

struct ColorMapSpecifications
{
	WORD first_entry_index;
	WORD color_map_length;
	BYTE entry_size;
};

struct ImageSpecifications
{
	WORD x_origin;
	WORD y_origin;
	WORD width;
	WORD height;
	BYTE pixel_depth;

	struct ImageDescriptor
	{
		BYTE attr_per_pixel : 4;
		BYTE pixel_data_order : 2;
		BYTE reserved : 2;
	}descriptor;
};

struct TGA_Header
{
	BYTE id_length;

	ColorMapType color_map_type;
	ImageType image_type;

	ColorMapSpecifications color_map_spec;
	ImageSpecifications image_specifications;

	nImageHeight = image_specifications.height;

	// image ID
	BYTE image_id[id_length];

	// ColorMapData
	if (color_map_type == ColorMapIncluded)
	{
		/*
		Each color map entry is stored using an integral number of bytes. The RGB specification for each color
		map entry is stored in successive bit-fields in the multi-byte entries. Each color bit-field is assumed to be
		MIN(Field4.3/3, 8) bits in length. If Field 4.3 contains 24, then each color specification is 8 bits in length;
		if Field 4.3 contains 32, then each color specification is also 8 bits (32/3 gives 10, but 8 is smaller). Unused
		bit(s) in the multi-byte entries are assumed to specify attribute bits. The attribute bit field is often called the
		Alpha Channel, Overlay Bit(s) or Interrupt Bit(s).
		*/
		/*
		// however - don't care what bits they don't use!!!

		var nColorMapLength = 0;
		// min
		if(color_map_spec.entry_size/3 <8)
			nColorMapLength = color_map_spec.entry_size/3;
		else
			nColorMapLength = 8;
		*/
		var nBytesUsed = color_map_spec.entry_size / 8;
		if (color_map_spec.entry_size % 8)
			nBytesUsed = nBytesUsed + 1;

		[noindex] struct ColorMapEntry
		{
			BYTE color[nBytesUsed];
		} entries[color_map_spec.color_map_length];
	}

	// ImageData
	var nPixels = image_specifications.width * image_specifications.height;

	nPerPixelByteCount = image_specifications.pixel_depth / 8;

	switch (image_type)
	{
	case UncompressedTrueColorImage:

		[noindex] struct Pixel
		{
			BYTE pixel[nPerPixelByteCount];
		}pixels[nPixels];
		break;
	case RunLengthEncodedTrueColorImage:
		[noindex] struct RunLengthPixel
		{
			BYTE PixelCount : 7;
			BYTE IsRunLengthPacket : 1;

			if (IsRunLengthPacket)
			{
				// only one pixel in current field
				BYTE pixel[nPerPixelByteCount];
			}
			else
			{
				// current field + PixelCount additional pixels 
				[noindex] struct SinglePixel
				{
					BYTE pixel[nPerPixelByteCount];
				}pixels[PixelCount + 1];
			}

			nPixels = nPixels - (PixelCount + 1);

			if (nPixels <= 0)
				$break_array(true);
		} run_length_pixels[*];
		break;
	}
};

// TODO: check if it's like this ???
struct TagData
{
	BYTE data[tag_size];
};

/*
This information is provided, at the developers’ request, for two purposes:
1) To make random access of compressed images easy.
2) To allow “giant picture” access in smaller “chunks”.
This table should contain a series of 4-byte offsets. Each offset you write should point
to the start of the next scan line, in the order that the image was saved (i.e., top down
or bottom up).
*/
struct ColorCorrectionTable
{
	if (current_offset != 0)
	{
		[noindex] struct Argb
		{
			WORD a, r, g, b;
		} argbs[256];
	}
};

/*
The Postage Stamp area is a smaller representation of the original image. This is
useful for “browsing” a collection of image files. If your application can deal with a
postage stamp image, it is recommended that you create one using sub-sampling
techniques to create the best representation possible. The postage stamp image must
be stored in the same format as the normal image specified in the file, but without any
compression.
*/
struct PostageStamp
{
	if (current_offset != 0 && nPerPixelByteCount != 0)
	{
		BYTE width;
		BYTE height;

		[noindex] struct Pixel
		{
			// same format as in header!!! p.21
			BYTE pixel_data[nPerPixelByteCount];
		} pixels[width * height];
	}
};

struct ScanLine
{
	if (current_offset != 0)
	{
		DWORD offsets[nImageHeight];
	}
};

enum AlphaValue : BYTE
{
	NoAlpha,
	UndefinedIgnore,
	UndefinedDontIgnore,
	UsefulAlpha,
	PreMultipliedAlpha
};

struct ExtensionArea
{
	if (current_offset != 0)
	{
		WORD size;
		char author_name[41];
		char author_comments[324];

		WORD month;
		WORD day;
		WORD year;
		WORD hour;
		WORD minute;
		WORD second;

		char job_name[41];

		WORD hours;
		WORD minutes;
		WORD seconds;

		char software_id[41];
		BYTE software_version[3];
		DWORD key_color;

		WORD pixel_aspect_ratio_numerator;
		WORD pixel_aspect_ratio_denominator;

		WORD gamma_value_numerator;
		WORD gamma_value_denominator;

		DWORD color_correction_table as ColorCorrectionTable *;
		DWORD postage_stamp_image as PostageStamp *;
		DWORD scan_line as ScanLine *;

		AlphaValue alpha_value;
	}
};

struct DeveloperFields
{
	if (current_offset != 0)
	{
		WORD tags_count;
		[noindex] struct Tag
		{
			WORD tag;
			DWORD tag_data as TagData *;
			DWORD tag_size;
		} tags[tags_count];
	}
};


/*
A TGA Reader should begin by determining whether the desired file is in the Original TGA
Format or the New TGA Format. This is accomplished by examining the last 26 bytes of the
file (most operating systems support some type of SEEK function). Reading the last 26 bytes
from the file will either retrieve the last 26 bytes of image data (if the file is in the Original
TGA Format), or it will retrieve the TGA File Footer (if the file is in the New TGA Format)
*/
public struct TGA_Footer
{
	// Extension area offset
	DWORD ext_area as ExtensionArea *;

	// developer directory offset
	DWORD dev_dir as DeveloperFields *;

	BYTE signature[18];
};

public struct TGA_File
{
	var nImageHeight;
	var nPerPixelByteCount = 0;

	TGA_Header	header;

	var nFooterOffset = GetDocumentSize();
	if (nFooterOffset >= sizeof(TGA_Footer))
		$bind("struct TGA_Footer", "footer", nFooterOffset - sizeof(TGA_Footer));
};
