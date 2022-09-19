// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma once
#include "stddefs.h"
#include "icc.h"

#pragma script("get_doc_size.js")

#pragma byte_order(BigEndian)

typedef DWORD Fixed;

// Photoshop CS File Formats Specification (October 2003) 
struct RGB
{
	BYTE r, g, b;
};

struct Rect
{
	DWORD dwTop, dwLeft, dwBottom, dwRight;
};

struct Rect64
{
	QWORD dwTop, dwLeft, dwBottom, dwRight;
};

enum ColorMode : WORD
{
	COLORMODE_BITMAP = 0,
	COLORMODE_GRAYSCALE,
	COLORMODE_INDEXED,
	COLORMODE_RGB,
	COLORMODE_CMYK,
	COLORMODE_MULTICHANNEL = 7,
	COLORMODE_DUOTONE,
	COLORMODE_LAB
};

struct FileHeader
{
	DWORD signature; // .ATN for action file format
	// 8BPS for psd
	// TODO: check EPS files 

	$assert(signature == 'SPB8', "Hex Editor is unable to parse file: wrong PSD signature");

	WORD wVersion;
	$assert(wVersion == 1, "Hex Editor is unable to parse file: wrong PSD version");

	BYTE reserved[6];

	WORD wChannels;
	DWORD dwHeight;
	DWORD dwWidth;
	WORD wColorDepth;
	ColorMode color_mode;
};

struct ColorModeData
{
	DWORD dwLength;
	BYTE color_data[dwLength];
};

// 
enum IRB_Types : WORD
{
	OBSOLETE_PS2 = 0x3E8,
	MAC_PRINT_MANAGER,
	OBSOLETE_PS2_INDEXCOLORTABLE = 0x3EB,
	RESOLUTION_INFO = 0x3ED,
	ALPHA_CHANEL_NAMES,
	DISPLAY_INFO,
	CAPTION,
	BORDER_INFORMATION,
	BACKGROUND_COLOR,
	PRINT_FLAGS,
	GRAYSCALE_HALFTONE_INFO,
	COLOR_HALFTONE_INFO,
	DUOTONE_INFO,

	GRAYSCALE_AND_MC_TRANSFER,
	COLOR_TRANSFER_FUNCTIONS,
	DUOTONE_TRANSFER,
	DUOTONE_IMAGE_INFO,
	EFFECTIVE_BW_DOTS_VALS,
	EPS_OPTIONS,
	QUICK_MASK_INFO,
	LAYER_STATE_INFO,
	WORKING_PATH,
	LAYERS_GROUP_INFO,
	IPTC_NAA_RECORD,
	IMAGE_MODE_FOR_RAW_FORMATS,
	JPEG_QUALITY,

	PS4_GRIDS_AND_GUIDES = 0x0408,
	PS4_THUMBNAIL_RESOURCE,
	PS4_COPYRIGHT_FLAG,
	PS4_URL,

	PS5_THUMBNAIL,
	PS5_GLOBAL_ANGLE,
	PS5_COLOR_SAMPLERS,
	PS5_ICC_PROFILE,
	PS5_WATERMARK,
	PS5_ICC_UNTAGGED_PROFILE,
	PS5_EFFECTS_VISIBLE,
	PS5_SPOT_HALFTONE,
	PS5_DOC_SPECIFIC_IDS_SEED,
	PS5_UNICODE_ALPHA_NAMES,

	PS6_INDEXED_ALPHA_TABLE_COUNT,
	PS6_TRANSPARENCY_INDEX,
	PS6_GLOBAL_ALTITUDE = 0x0419,
	PS6_SLICES,
	PS6_WORKFLOW_URL,
	PS6_JUMP_TO_XPEP,
	PS6_ALPHA_IDS,
	PS6_URL_LIST,
	PS6_VERSION_INFO = 0x0421,

	PS7_EXIF_DATA1,
	PS7_EXIF_DATA3,
	PS7_XMP_METADATA,
	PS7_CAPTION_DIGEST,
	PS7_PRINT_SCALE,

	PCS_PIXEL_ASPECT_RATIO = 0x0428,
	PCS_LAYER_COMPS,
	PCS_ALTERNATE_DUOTONE_COLORS,
	PCS_ALTERNATE_SPOT_COLORS,

	PATH_INFO = 0x07D0,
	LAST_PATH_INFO = 0x0BB6, // not an actual tag!!!
	NAME_CLIPPING_PATH = 0x0BB7,
	PRINT_FLAGS_INFO = 0x2710,

};

struct GridAndGuidesData
{
	DWORD dwVersion;
	//Future implementation of document-specific grids (4 bytes horizontal, 4
	// bytes vertical). Currently, sets the grid cycle to every quarter inch, i.e. 576
	// for both horizontal & vertical (at 72 dpi, that is 18 * 32 = 576)
	DWORD dwHor, dwVert;
	DWORD dwGuideCount;

	[noindex] struct Guide
	{
		DWORD dwGuideLocation;
		BYTE bHorizontal; // 0 - vertical; 1 - horizontal
	}guides[dwGuideCount];
};


enum ThumbnailFormat : DWORD
{
	kRawRGB = 0,
	kJpegRGB
};

struct ThumbnailData
{
	ThumbnailFormat format;
	WORD dwWidth;
	DWORD dwHeight;
	DWORD dwWidthBytes; // Widthbytes: Padded row bytes = (width * bits per pixel + 31) / 32 * 4
	DWORD dwTotalSize; // Total size = widthbytes * height * planes
	DWORD dwSizeCompressed;
	WORD wBitsPerPixel;
	WORD wNumberOfPlanes;
	// TODO: JFIF data in RGB format!!!
};

enum ColorSpace : WORD
{
	kDummySpace = -1, kRGBSpace, kHSBSpace,
	kCMYKSpace, kPantoneSpace, kFocoltoneSpace,
	kTrumatchSpace, kToyoSpace, kLabSpace, kGraySpace,
	kWideCMYKSpace, kHKSSpace, kDICSpace, kTotalInkSpace,
	kMonitorRGBSpace, kDuotoneSpace, kOpacitySpace
};

struct ColorSamplerData
{
	DWORD dwVersion;
	DWORD dwCount;

	[noindex] struct ColorSampler
	{
		DWORD dwVertical;
		DWORD dwHorizontal; // or maybe first hor, then vert???
		ColorSpace color_space;
	}samplers[dwCount];
};

enum PathType : WORD
{
	Closed_LengthRecord = 0,
	Closed_BezierKnotLinked,
	Closed_BezierKnotUnlinked,

	Open_LengthRecord,
	Open_BezierKnotLinked,
	Open_BezierKnotUnlinked,

	PathFillRuleRecord,
	ClipboardRecord,
	InitialFillRuleRecord
};

// 26 byte record
struct PathInfoData
{
	PathType wSelector; // TODO: swap for Windows???
	switch (wSelector)
	{
	case Closed_LengthRecord:
	case Open_LengthRecord:
		WORD wBezierKnotsNumber;
		BYTE data[22];
		break;
	case Closed_BezierKnotLinked:
	case Closed_BezierKnotUnlinked:
	case Open_BezierKnotLinked:
	case Open_BezierKnotUnlinked:
		struct Point
		{
			DWORD dwVertical;
			DWORD dwHorizontal;
		};
		Point control_point_pre;
		Point anchor_point;
		Point control_point_leaving;
		break;
	case ClipboardRecord:
		Rect rect;
		DWORD dwResolution;
		BYTE reserved[6];
		break;
	case InitialFillRuleRecord:
		WORD wFillStartsWithAllPixels;
		BYTE reserved[24];
		break;
	default:
		BYTE data[26];
	}
};

struct UnicodeString
{
	DWORD dwLength;
	wchar_t string[dwLength];
};

struct PascalString
{
	WORD wLength;
	wchar_t string[wLength];
};

struct String
{
	DWORD dwLength;
	char string[dwLength];
};

struct Slice
{
	DWORD dwID;
	DWORD dwGroupID;
	DWORD dwOrigin;
	DWORD dwAssociatedLayerID;
	UnicodeString name;

	DWORD dwType;
	DWORD dwLeft, dwTop, dwRight, dwBottom;

	UnicodeString url, target, message, alt_tag;
	BYTE bCellTextIsHtml;
	UnicodeString cell_text;
	DWORD dwHorAlignment, dwVertAlignment;

	BYTE nAlphaColor;
	RGB rgb;
};

struct SliceHeader
{
	DWORD dwVersion;
	$assert(dwVersion == 6, "Hex Editor is unable to parse file: wrong SliceHeader signature");
	Rect rect;

	UnicodeString unicode_string;
	DWORD dwSlicesToFollow;

	[noindex] Slice slices[dwSlicesToFollow];
};

enum Ps7PrintScaleStyle : WORD
{
	CENTERED,
	SIZE_TO_FIT,
	USER_DEFINED
};

struct Ps7PrintScale
{
	Ps7PrintScaleStyle style;
	DWORD x,
		y;
	DWORD scale;
};

struct Ps5GlobalAngle
{
	DWORD dwLightingAngleForEffects; // 4 bytes that contain an integer between 0 and 359, which is the global
	// lighting angle for effects layer. If not present, assumed to be 30.
};

struct ResolutionInfo
{
	Fixed hRes;
	WORD wResUnit;
	WORD wWidthUnit;
	Fixed vRes;
	WORD wResUnit;
	WORD wHeightUnit;
};

enum DisplayInfoKind : BYTE
{
	Selected,
	Protected
};

struct DisplayInfo
{
	WORD wColorSpace;
	WORD wColor[4];
	WORD wOpacity; // 0..100
	DisplayInfoKind kind;
	BYTE padding; // should be zero
};

enum BorderInformationUnits : WORD
{
	Inches,
	Cm,
	Points,
	Picas,
	Columns
};

// Forward Declaration
struct Color;

struct ColorSwatches
{
	ColorSpace color_space;
	USHORT colors[4];
};

struct Descriptor;

public struct ImageResourceBlock
{
	if (ImageResourceSize <= 0)
		$break_array(false);

	DWORD signature;
	$assert(signature == 'MIB8', "Hex Editor is unable to parse file: wrong ImageResourceBlock signature");

	IRB_Types wID;

	// Name: Pascal string, padded to make the size even (a null name
	// consists of two bytes of 0)
	PascalString name;
	DWORD dwDataSize;

	var nCurrentPointer = current_offset;

	if (wID >= PATH_INFO && wID <= LAST_PATH_INFO)
	{
		// path info
		PathInfoData data;
	}
	else
	{
		switch (wID)
		{
		case OBSOLETE_PS2:
			WORD wChannels;
			WORD wRows;
			WORD wColumns;
			WORD wDepth;
			WORD wMode;
			break;
		case RESOLUTION_INFO:
			ResolutionInfo resolution_info;
			break;
		case DISPLAY_INFO:
			DisplayInfo display_info;
			break;
		case CAPTION:
			PascalString caption;
			break;
		case BORDER_INFORMATION:
			struct BorderInformation
			{
				DWORD dwBorderWidth;
				BorderInformationUnits units;
			};
			break;
		case BACKGROUND_COLOR:
			ColorSwatches back_color;
			break;
		case PRINT_FLAGS:
			struct PrintFlags
			{
				BYTE labels, crop, marks, color_bars, reg_marks, negative, flip, interpolate, caption, print_flags;
			}print_flags;
			break;
		case EFFECTIVE_BW_DOTS_VALS:
			BYTE nBlack, nWhite;
			break;
		case QUICK_MASK_INFO:
			struct QuickMask
			{
				WORD wQuickMaskChannelID;
				BYTE bMaskInitiallyEmpty;
			}quick_mask;
			break;
		case LAYER_STATE_INFO:
			WORD wTargerLayerIndex;
			break;
		case WORKING_PATH:
			PathInfoData working_path;
			break;
		case LAYERS_GROUP_INFO:
			WORD wGroupID[dwDataSize / 2];
			break;
			//case IPTC_NAA_RECORD:
			// TODO: see IPTC in documentation folder
			// break;
		case PS4_GRIDS_AND_GUIDES:
			GridAndGuidesData grid_guides;
			break;
		case PS4_THUMBNAIL_RESOURCE:
		case PS5_THUMBNAIL:
			ThumbnailData thumbnail;
			break;
		case PS4_COPYRIGHT_FLAG:
			BYTE bImageCopyrighted;
			break;
		case PS5_COLOR_SAMPLERS:
			ColorSamplerData data;
			break;
		case PS7_PRINT_SCALE:
			Ps7PrintScale print_scale;
			break;
		case PS5_GLOBAL_ANGLE:
			Ps5GlobalAngle global_angle;
			break;
		case PS5_ICC_PROFILE:
			// from icc.h
			ICC icc;
			break;
		case PS5_WATERMARK:
			BYTE nWatermark;
			break;
		case PS5_ICC_UNTAGGED_PROFILE:
			BYTE bIntentionallyUntagged;
			break;
		case PS5_EFFECTS_VISIBLE:
			BYTE bEffectVisible;
			break;
		case PS5_SPOT_HALFTONE:
			[noindex] struct SpotHalftone
			{
				DWORD dwVersion;
				DWORD dwLength;
				BYTE data[dwLength];
			}spot_halftone;
			break;
		case PS5_DOC_SPECIFIC_IDS_SEED:
			DWORD dwBaseValue; // Base value, starting at which layer IDs will be generated (or a
			// greater value if existing IDs already exceed it)
			break;
		case PS5_UNICODE_ALPHA_NAMES:
			UnicodeString alha_names;
			break;
		case PS6_INDEXED_ALPHA_TABLE_COUNT:
			WORD wNumberOfColors;
			break;
		case PS6_TRANSPARENCY_INDEX:
			WORD nIndex;
			break;
		case PS6_GLOBAL_ALTITUDE:
			DWORD dwAlt;
			break;
			// WARNING: not working
			//case PS6_SLICES: 
			// SliceHeader slice_header;
			// break;
		case PS6_WORKFLOW_URL:
			UnicodeString url;
			break;
		case PS6_JUMP_TO_XPEP:
			struct Xpep
			{
				WORD wMajorVersion;
				WORD wMinorVersion;
				DWORD dwCount;

				[noindex] struct Block
				{
					DWORD dwBlockSize;
					DWORD dwKey;

					var nUsedBytes = 0;
					if (dwKey == 'dDtj')
					{
						BYTE bDirtyFlag;
						nUsedBytes = 1;
					}
					else
					{
						DWORD dwModDate;
						nUsedBytes = 4;
					}
					BYTE not_parsed_data[dwBlockSize - sizeof(dwKey) - nUsedBytes];
				}blocks[dwCount];
			}jump_to_xpep;
			break;
		case PS6_ALPHA_IDS:
			DWORD ids[dwDataSize / 4];
			break;
		case PS6_URL_LIST:
			DWORD dwUrlCount;

			[noindex] struct Url
			{
				DWORD unknown; // see p.16
				DWORD dwID; // ??? for each url???
				UnicodeString url;
			}urls[dwUrlCount];
			break;
		case PS6_VERSION_INFO:
			struct VersionInfo
			{
				DWORD dwVersion;
				BYTE bHasRealMergedData;
				UnicodeString writer_name, reader_name;
				DWORD dwFileVersion;
			}version_info;
			break;
			//case PS7_EXIF_DATA1:
			// TODO: exif data
			// break;
			//case PS7_EXIF_DATA3:
			// TODO: exit data
			// break;
		case PCS_PIXEL_ASPECT_RATIO:
			struct PixelAspectRatio
			{
				DWORD dwVersion;
				double fXByY;
			}aspect_ratio;
			break;
		case PCS_LAYER_COMPS:
			DWORD dwVersion;
			Descriptor descriptor;
			break;
		case PCS_ALTERNATE_DUOTONE_COLORS:
			struct DuotoneColors
			{
				WORD wVersion;
				WORD wCount;
				[noindex] Color colors[wCount];

				WORD wCount2;
				[noindex] struct LabColor
				{
					BYTE L, a, b;
				}lab_colors[wCount2];
			}duotone_colors;
			break;
		case PCS_ALTERNATE_SPOT_COLORS:
			struct AlternateSpot
			{
				WORD wVersion;
				WORD wChannelCount;
				[noindex] struct Channel
				{
					DWORD dwChannelID;
					Color color;
				}channels[wChannelCount];
			}alternate_spot;
			break;
		case NAME_CLIPPING_PATH:
			PathInfoData clipping_path;
			break;
		case PRINT_FLAGS_INFO:
			struct PrintFlagsInfo
			{
				WORD wVersion;
				BYTE nCenterCropMarks;
				BYTE nReserved;
				DWORD dwBleedWidthValue;
				WORD wBleedWidthScale;
			}flags_info;
			break;
		default:
			BYTE data[dwDataSize];
			if (dwDataSize % 2)
				BYTE padding[dwDataSize % 2];
		}

		/*
		// NOT implemented (bad documentation or no need)
		case MAC_PRINT_MANAGER:
		break;
		case OBSOLETE_PS2_INDEXCOLORTABLE:
		break;
		case ALPHA_CHANEL_NAMES:
		break;
		case GRAYSCALE_HALFTONE_INFO:
		break;
		case COLOR_HALFTONE_INFO:
		break;
		case DUOTONE_INFO:
		break;
		case GRAYSCALE_AND_MC_TRANSFER:
		break;
		case COLOR_TRANSFER_FUNCTIONS:
		break;
		case DUOTONE_TRANSFER:
		break;
		case DUOTONE_IMAGE_INFO:
		break;
		case EPS_OPTIONS:
		break;
		case IMAGE_MODE_FOR_RAW_FORMATS:
		break;
		case JPEG_QUALITY:
		break;
		case PS4_URL:
		break;
		case PS7_XMP_METADATA:
		break;
		case PS7_CAPTION_DIGEST: // RSA Data Security, MD5 message-digest algorithm
		break;
		*/
	}

	if (dwDataSize > (current_offset - nCurrentPointer))
		BYTE not_parsed[dwDataSize - (current_offset - nCurrentPointer)];

	var nUsedBytesForChunk = current_offset - nCurrentPointer;
	BYTE padding[nUsedBytesForChunk % 2];

	ImageResourceSize = ImageResourceSize - (current_offset - this);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
enum LayerFlags : BYTE
{
	TransparencyProtectedBit = 0,
	VisibleBit,
	IsBit4_WithInfo = 4, // bit 3 = 1 for Photoshop 5.0 and later, tells if bit 4 has useful information;
	PixelDataIrrelevantToAppearance = 8 // pixel data irrelevant to appearance of document
};

enum MaskFlags : BYTE
{
	PositionRelativeToLayer = 1,
	LayerMaskDisabled = 2,
	InvertLayerMaskWhenblending = 4,
};

enum CompressionType : WORD
{
	Compression_RawData,
	Compression_RLE,
	Compression_ZIP_no_prediction,
	Compression_ZIP_with_prediction,
};

struct ChannelImageDataArray
{
	var nLayerIndex = array_index;

	$print("channel count (from Layer structure)=", layers[array_index].wChannelNumber);

	struct ChannelImageData
	{
		CompressionType wCompression;
		if (wCompression == 0)
		{
			BYTE raw_image_data[(layers[nLayerIndex].rect.dwBottom - layers[nLayerIndex].rect.dwTop)
				* (layers[nLayerIndex].rect.dwRight - layers[nLayerIndex].rect.dwLeft)];
		}
		else if (wCompression == 1)
		{
			var nLines = (layers[nLayerIndex].rect.dwBottom - layers[nLayerIndex].rect.dwTop);

			struct LineCount
			{
				WORD wByteCountForLine;
			}line_counts[nLines];

			struct Line
			{
				BYTE data[line_counts[array_index].wByteCountForLine];
			}lines[nLines];
		}

		//BYTE channel_info_data[layers[array_index].channels[array_index].dwChannelInfoLength];
	}image_data[layers[array_index].wChannelNumber];
};

// forward declaration
struct AdditionalLayerData;

struct Layer
{
	Rect rect;
	WORD wChannelNumber;
	[noindex] struct Channel
	{
		WORD wID;
		DWORD dwChannelInfoLength;
	}channels[wChannelNumber];

	DWORD signature;
	char mode[4];
	BYTE nOpacity;
	BYTE nClipping;
	LayerFlags flags;

	BYTE nReserved;

	DWORD dwLengthOfExtraDataField;

	var ExtraDataStart = current_offset;
	var nMaskSize = 0;
	struct MaskData
	{
		DWORD dwSizeOfData;
		nMaskSize = dwSizeOfData;

		if (dwSizeOfData != 0)
		{
			Rect rect;
			BYTE nDefaultColor;
			MaskFlags mask_flags;

			if (dwSizeOfData == 20)
			{
				BYTE reserved[2];
			}
			else if (dwSizeOfData == 36)
			{
				MaskFlags real_flags;
				MaskFlags real_user_mask_background;
				DWORD dwTop2, dwLeft2, dwBottom2, dwRight2; // ??? see documentation -> this field is identical to DWORDs above!
			}
			else if (dwSizeOfData < dwLengthOfExtraDataField)
				BYTE mask_data[dwSizeOfData];
		}
	}mask_data;

	if (nMaskSize >= dwLengthOfExtraDataField)
	{
		// error
		BYTE not_parsed_data[dwLengthOfExtraDataField - (current_offset - ExtraDataStart)];
	}
	else
	{
		[noindex] struct BlendingRanges
		{
			DWORD dwSizeOfData;
			BYTE nBlackValues[2];
			BYTE nWhiteValues[2];

			DWORD dwCompositeGreyBlendRange;

			var nChannels = (dwSizeOfData - 8) / 8;
			$assert(((dwSizeOfData - 8) % 8) == 0, "Hex editor is unable to parse file");

			struct ChannelRange
			{
				DWORD src_range;
				DWORD dst_range;
			}channels[nChannels];
		}blending_ranges;

		BYTE nStringLength;
		char layer_name[nStringLength];

		var nTempPad = ((sizeof(layer_name) + 1 + 3) / 4);
		var nPad = (nTempPad * 4) - (sizeof(layer_name) + 1);
		BYTE padding[nPad];

		// calculate total AdditionalLayerData chunks sizes
		var nAdditionalLength = dwLengthOfExtraDataField - (current_offset - ExtraDataStart);

		[noindex] AdditionalLayerData layer_data[*];
	}
};

struct LayerInfo
{
	DWORD dwLengthOfInfo;
	WORD wLayerCount;
	// NO [noindex]!!!
	Layer layers[wLayerCount];

	[noindex] ChannelImageDataArray channel_image_data[wLayerCount];
};

enum LayerMaskKind : BYTE
{
	ColorInverted = 0,
	ColorProtected,
	UseValueStoredPerLayer = 128
};

struct LayerMaskInfo
{
	DWORD dwDataLength;
	WORD wOverlayColorSpace;
	WORD color_components[4];
	WORD opacity;
	LayerMaskKind kind;

	//if(dwDataLength > (current_offset - this))
	// BYTE data_not_used[dwDataLength - (current_offset - this)];
};

struct LayerAndMaskInfo
{
	DWORD dwLength;

	var nDataBeginning = current_offset;
	LayerInfo layer_info;
	LayerMaskInfo global_layer_mask_info;

	BYTE not_parsed_data[dwLength - (current_offset - nDataBeginning)];
};


///effects://///////////////
struct CommonStateEffects
{
	DWORD dwSize;
	DWORD dwVersion;
	BYTE bVisible;
	WORD wReserved;
};

struct Color
{
	WORD wSpace;
	WORD color_components[4];
};

struct BlendMode
{
	DWORD dwSignature;
	DWORD dwKey;
};

struct ShadowInfo
{
	DWORD dwSize;
	DWORD dwVersion;
	DWORD dwBlurValueInPixels;
	DWORD dwIntensityAsPercent;
	DWORD dwAngleInDegrees;
	DWORD dwDistanceInPixels;

	Color color;

	BlendMode blend_mode;
	BYTE bEffectsEnabled;
	BYTE bUseThidAngleInAllLayers;
	BYTE nOpacityAsPercent;
	Color native_color;
};

struct OuterGlowInfo
{
	DWORD dwSize;
	DWORD dwVersion;
	DWORD dwBlurInPixels;
	DWORD dwIntensityAsPercent;

	Color color;
	BlendMode blend_mode;

	BYTE bEffectEnabled;
	BYTE nOpacityAsPercent;
	if (dwSize == 42)
		Color native_colorspace;
};

struct InnerGlowInfo
{
	DWORD dwSize;
	DWORD dwVersion;
	DWORD dwBlurInPixels;
	DWORD dwIntensityAsPercent;
	Color color;
	BlendMode blend_mode;

	BYTE bEffectEnabled;
	BYTE nOpacityAsPercent;
	if (dwSize == 43)
	{
		BYTE bInvert;
		Color native_colorspace;
	}
};

struct BevelInfo
{
	DWORD dwSize;
	DWORD dwVersion;
	DWORD dwAngleInDegrees;
	DWORD dwStrength_DepthInPixels;
	DWORD dwBlurInPixels;

	BlendMode blend_mode,
		shadow_blend_mode;
	Color highlight_color,
		shadow_color;

	BYTE nBevelStyle;
	BYTE nHighlightOpacityAsPercent;
	BYTE nShadowOpacityAsPercent;
	BYTE bEffectEnabled;
	BYTE bUseThisAngleInAllLayerEffects;
	BYTE bUpOrDown; // hm :-)
	if (dwSize == 78)
	{
		Color real_high_color;
		Color real_shadow_color;
	}
};

struct SolidFillInfo
{
	DWORD dwSize; // must be set to 34 bytes
	DWORD dwVersion;
	DWORD dwBlendModeKey;
	Color color_space;
	BYTE nOpacity;
	BYTE bEnabled;
	Color native_color_space;

	// WARNING: don't know but files i've tested can not be parsed without this fake field
	// there are some problems with documentation (total size of all previous fields without dwSize is 30 bytes!!!)
	BYTE pad[6];
};

struct EffectsLayer
{
	WORD wVersion;
	WORD wEffectsCount;

	[noindex] struct Effect
	{
		DWORD signature;
		$assert(signature == 'MIB8', "Hex editor is unable to parse file: wrong signature of Effect");

		DWORD effect_signature;
		switch (effect_signature)
		{
		case 'Snmc':
			CommonStateEffects common_state_effects;
			break;
		case 'wdsd':case 'wdsi':
			ShadowInfo shadow_info;
			break;
		case 'wlgo':
			OuterGlowInfo outer_glow;
			break;
		case 'wlgi':
			InnerGlowInfo inner_glow;
			break;
		case 'lveb':
			BevelInfo bevel;
			break;
		case 'ifos':
			SolidFillInfo solid_fill;
			break;
		}
	}effects[wEffectsCount];
};
//end of effects//////////////////////

// Has been superseded in Photoshop 6.0 and beyond by a different structure
// with the key 'TySh' (see Table 1.49).
struct TypeToolInfoPrePS60
{
	WORD wVersion;
	QWORD transform_info[6];

	struct FontInfo
	{
		WORD wVersion;
		WORD wCountOfFaces;

		[noindex] struct Face
		{
			WORD wMarkValue;
			DWORD dwFontTypeData;
			PascalString font_name;
			PascalString font_family_name;
			PascalString font_style_name;
			WORD wScriptValue;
			DWORD dwDesignAxesNumber;
			DWORD dwDesignVectorValue;
		}faces[wCountOfFaces];
	}font_info;

	struct StyleInfo
	{
		WORD wCountOfStyles;
		[noindex] struct Style
		{
			WORD wMarkValue;
			WORD wFaceMarkValue;
			DWORD dwSizeValue;
			DWORD dwTrackingValue;
			DWORD dwKerningValue;
			DWORD dwLeadingValue;
			DWORD dwBaseShiftValue;
			BYTE nAutoKernOn;
			// WARNING: please see this field p.34 (only in versions <=5)
			if (wVersion <= 5)
			{
				BYTE nRotateUpDown;
			}
		}styles[wCountOfStyles];
	}style_info;


	struct TextInformation
	{
		WORD wType;
		DWORD dwScalingFactor;
		DWORD dwCharacterCount;
		DWORD dwHorizontalPlacement;
		DWORD dwVerticalPlacement;
		DWORD dwSelectStart;
		DWORD dwSelectEnd;
		WORD wLineCount;

		[noindex] struct Line
		{
			DWORD dwCharacterCount;
			WORD wOrientation;
			WORD wAlignment;
			WORD wActualCharacter;
			WORD wStyleValue;
		}lines[wLineCount];
	}text_info;

	struct ColorInformation
	{
		WORD wColorSpaceValue;
		WORD wColorComponent[4];
	}color_info;
};

// PS6+
struct TypeToolInfo
{
	WORD wVersion;
	QWORD transform_info[6];
	WORD wTextVersion;
	DWORD dwDescriptorVersion;
	Descriptor desctiptor_text_data;

	WORD wWarpVersion;
	DWORD dwDescriptorVersion2;
	Descriptor desctiptor_warp_data;

	// WARN: in documentation: 4* 8!!! but we use DWORD insead
	Rect rect;
};

// descriptors:
struct ClassID
{
	String str;
	if (sizeof(str) == 4)
		DWORD dwClassID;
};

struct PropRefDescriptor
{
	UnicodeString name_from_clsid;
	ClassID clsid;
	ClassID keyid;
};

struct ClassRefDescriptor
{
	UnicodeString name_from_clasid;
	ClassID clsid;
};

struct EnumeratedRefDescriptor
{
	UnicodeString name_from_clsid;
	ClassID clsid;
	ClassID typeid;
	ClassID enum;
};

struct OffsetRefDescriptor
{
	UnicodeString name_from_clsid;
	ClassID classid;
	DWORD dwOffset;
};

struct ReferenceDesc
{
	DWORD dwItems;
	[noindex] struct RefItem
	{
		DWORD type;
		switch (type)
		{
		case 'porp':
			PropRefDescriptor prop;
			break;
		case 'sslS':
			ClassRefDescriptor class;
			break;
		case 'rmnE':
			EnumeratedRefDescriptor enum_ref;
			break;
		case 'eler':
			OffsetRefDescriptor offset;
			break;
			/*
			case 'tndI':

			break;
			case 'xdni':

			break;
			case 'eman':

			break;
			*/
		}
	}items[dwItems];
};

struct UnitFloat
{
	char units[4];
	QWORD qwValue;
};

union Double
{
	DWORD dwDouble;
	double fDouble;
};

struct Alias
{
	DWORD dwSize;
	BYTE alias_data[dwSize]; // ??? - FSSpec for Macintosh or a handle to a string to the full path on Windows
};

// Forward Declaration
struct OSTypeInternal;

struct ListStructure
{
	DWORD dwListItems;
	[noindex] struct ListItem
	{
		OSTypeInternal item;
	}items[dwListItems];
};

struct EnumeratedDescriptor
{
	ClassID typeid;
	ClassID enum;
};

// same as in OSType
struct OSTypeInternal
{
	DWORD os_type;
	switch (os_type)
	{
	case 'atdt':
		struct TData
		{
			DWORD dwDataLength;
			BYTE data[dwDataLength];
		}t_data;
		break;
		// not switched (in LE)
	case 0x6f626a20: // 'obj '
		ReferenceDesc reference;
		break;
	case 'cjbO':case 'OblG':
		// descriptor
		Descriptor desc;
		break;
	case 'sLlV':
		ListStructure list;
		break;
	case 'buod':
		Double value;
		break;
	case 'FtnU':
		UnitFloat unit_float;
		break;
	case 'TXET':
		UnicodeString string;
		break;
	case 'mune':
		EnumeratedDescriptor enum_desc;
		break;
	case 'gnol':
		DWORD dwValue;
		break;
	case 'loob':
		BYTE bBoolean;
		break;
	case 'epyt':case 'CblG':
		// TODO: class
		struct Empty
		{

		};
		break;
	case 'sila':
		Alias alias;
		break;
	}
};

struct OSType
{
	String key;
	if (sizeof(key) == 4)
	{
		DWORD key_dword;
	}

	DWORD os_type;
	switch (os_type)
	{
	case 'atdt':
		struct TData
		{
			DWORD dwDataLength;
			BYTE data[dwDataLength];
		}t_data;
		break;
		// not switched (in BE) 
	case 0x206a626f/*0x6f626a20*/: // 'obj '
		ReferenceDesc reference;
		break;
	case 'cjbO':case 'OblG':
		// descriptor
		Descriptor desc;
		break;
	case 'sLlV':
		ListStructure list;
		break;
	case 'buod':
		Double value;
		break;
	case 'FtnU':
		UnitFloat unit_float;
		break;
	case 'TXET':
		UnicodeString string;
		break;
	case 'mune':
		EnumeratedDescriptor enum_desc;
		break;
	case 'gnol':
		DWORD dwValue;
		break;
	case 'loob':
		BYTE bBoolean;
		break;
	case 'epyt':case 'CblG':
		// TODO: class
		struct Empty
		{

		};
		break;
	case 'sila':
		Alias alias;
		break;
	}
};

struct Descriptor
{
	UnicodeString name_from_class_id;
	ClassID class_id;
	DWORD dwItems;
	OSType os[dwItems];
};

struct Patterns
{
	DWORD dwLengthOfThisPattern;

	var nPatternBegin = current_offset;

	DWORD dwVersion;
	ColorMode mode;
	WORD wVertPoint;
	WORD wHorPoint;
	UnicodeString name;
	PascalString unique_patter_id;
	if (mode == COLORMODE_INDEXED)
	{
		// index color table
		RGB color_table[256];
	}

	// virtual memory array list:
	DWORD dwVersion;
	DWORD dwLength;
	Rect rect;
	DWORD dwMaxChannels;

	// wChannelNumber declared in Layer
	struct VirtualMemoryArray
	{
		// WARNING: please note that in documentation (p.36) this boolean field has size of 4!!!)
		BYTE bArrayIsWritten;
		DWORD dwLength;
		DWORD dwPixelDepth;
		BYTE bCompressionModeOfDataToFollow;

		// WARNING: dwLength is used only as data length or it includes 'dwPixelDepth' and 'bCompressionModeOfDataToFollow' too???
		BYTE data[dwLength - sizeof(dwPixelDepth) - sizeof(bCompressionModeOfDataToFollow)];
	}array_list[wChannelNumber];

	// no need
	//BYTE not_parsed_data[dwLengthOfThisPattern - (current_offset-nPatternBegin)];
};

struct Annotation
{
	WORD wMajorVersion;
	WORD wMinorVersion;
	DWORD dwCount;

	struct AnnotationItem
	{
		DWORD dwLength;
		char type[4];
		BYTE bIsAnnoOpen;
		BYTE bFlags;
		WORD wOptionalBlock;
		Rect icon_rect;
		Rect popup_location;
		WORD wSpace;
		WORD wColorCompopnents[4];
		PascalString author_name;
		PascalString name;
		PascalString mod_date;
		DWORD dwLnegthNext;
		char type2[4];
		DWORD dwLengthActualData;
		BYTE actual_data[dwLengthActualData];

		// TODO: padding to align to multiple of 4

	}annotations[dwCount];
};

struct BlendClipping
{
	BYTE bBlendClippedElement;
hidden:
	BYTE padding[3];
};

struct BlendInterior
{
	BYTE bBlendIneriorElement;
hidden:
	BYTE padding[3];
};

struct Knockout
{
	BYTE bKnockout;
hidden:
	BYTE padding[3];
};

struct PtotectionSetting
{
	DWORD dwProtectionFlags;
};

struct SheetColorSettings
{
	WORD wColor[4];
};

struct ReferencePoint
{
	Double ref_point[2];
};

enum SectionDividerType : DWORD
{
	AnyOtherLayerType = 0,
	OpenFolder,
	ClosedFolder,
	BoundingSectionDivider
};
struct SectionDivider
{
	SectionDividerType type;
	char sig[4];
	char blend_key[4];
};

struct AdditionalLayerData
{
	if (nAdditionalLength <= 0)
		$break_array(false);

	DWORD signature;
	$assert(signature == 'MIB8', "Hex editor is unable to parse file: wrong signature of AdditionalLayerData");

	DWORD key;
	DWORD dwDataLength;

	var nPointerBefore = current_offset;

	switch (key)
	{
	case 'XFrl':
		EffectsLayer effects_layer; // Photoshop 5
		break;
	case 'hSyt':case 'hSyT':
		// TODO: if photoshop version<6
		//if(false)
		// TypeToolInfoPrePS60 type_tool_info
		//else
		TypeToolInfo type_tool_info;
		break;
	case 'inul':
		UnicodeString layer_name;
		break;
	case 'diyl':
		// TODO: test it!!! in documentation they icluded key,dwDataLength keys twice!!! i don't think they really mean it.
		DWORD dwLayerID;
		break;
	case '2xfl':
		DWORD dwObjectEffectsVersion;
		DWORD dwDescriptorVersion;
		Descriptor descriptor; // i've encountered error in some sample PSD files - so this one will check the size
		break;
	case 'ttaP':case '2taP':
		Patterns patterns;
		break;
	case 'onnA':
		Annotation anno;
		break;
	case 'lblc':
		BlendClipping clbl;
		break;
	case 'xfni':
		BlendInterior infx;
		break;
	case 'oknk':
		Knockout knko;
		break;
	case 'fpsl':
		PtotectionSetting protection;
		break;
	case 'rlcl':
		SheetColorSettings color_settings;
		break;
	case 'prxf':
		ReferencePoint ref_point;
		break;
	case 'mdrg':
		struct GradientSettings
		{
			WORD wVersion;
			BYTE bIsGradientReversed;
			BYTE bIsGradientDithered;
			UnicodeString name_of_gradient;
			WORD wNumberOfColorStops;
			struct ColorStops
			{
				DWORD dwLocationOfColorStop;
				DWORD dwMidpointOfColorStop;
				WORD wMode;
				WORD wActualColorStop[4];
				WORD wTransparencyStops;
				struct TransparencyStop
				{
					DWORD dwTranspStopLocation;
					DWORD dwTranspStopMidpoint;
					WORD wOpacity;
					WORD wExpansionCount;
					WORD wInterpolation;
					WORD wLength;
					WORD wGradientMode;
					DWORD dwRandomNumberSeed;
					WORD wTransparencyShowFlag;
					WORD wFlagForUsingVectorColor;
					DWORD dwRoughnessFactor;
					WORD wColorMode;
					WORD wMinColorValues[4];
					WORD wMaximColorValue[4];
					WORD wDummy;
				}transp_stop[wTransparencyStops];
			}color_stops[wNumberOfColorStops];
		}gradient_settings;
		break;
	case 'tcsl':
		if (dwDataLength == sizeof(SectionDivider))
			SectionDivider section_divider;
		break;
	case 'tsrb':
		struct ChannelBlendingRestriction
		{
			DWORD dwRestrictedChannelNumber[dwDataLength / sizeof(DWORD)];
		};

		// if(dwDataLength==sizeof(ChannelBlendingRestriction))
		ChannelBlendingRestriction restriction;
		break;
	case 'oCoS':
	case 'lFtP':
	case 'lFdG':
		struct SolidColor
		{
			DWORD dwVersion;
			Descriptor descriptor;
		}solid_color;
		break;
	case 'ksmv':
		DWORD dwVersion;
		DWORD dwFlags;
		PathInfoData paths;
		break;
	case 'ixff':
		DWORD dwForeignEffectID;
		break;
	case 'rsnl':
		DWORD dwIDForLayerName;
		break;
	case 'aphs':
		struct PatternData
		{
			DWORD dwVersion;
			DWORD dwCount;

			struct Set
			{
				DWORD dwPatternSignature;
				DWORD dwPatternKey;
				DWORD dwPatternCount;
				BYTE nCopyOfSheet;
				BYTE padding[3];

				struct Pattern
				{
					char color_handling[4];
					PascalString pattern_name;
					UnicodeString unicode_pattern_name;
					PascalString unique_id;
				}patterns[dwPatternCount];
			}sets[dwCount];
		}patter_data;
		break;
	case 'dmhs':
		struct Metadata
		{
			DWORD dwCount;
			[noindex] struct MetadataItems
			{
				char sig[4];
				DWORD dwKey;
				BYTE bCopyOfSheetDuplication;
				BYTE padding[3];
				DWORD dwLength;
				BYTE undocumented_data[dwLength];
			}items[dwCount];
		}metadata;
		break;
	case 'rvyl':
		DWORD dwPhotoshopVersionNeeededToReadLayer;
		break;
	case 'ylst':case 'mgmv':case 'mgml':
		struct TransparencyShapes
		{
			BYTE bTransparency; // the transparency of the layer is used in determining the shape of the
			// effects. This is the default for behavior like previous versions.
			BYTE padding[3];
		}transp_shapes;
		break;
	case 'tirb':
		struct BrightnessAndContrast
		{
			WORD wBrigtnessAndContrast;
			WORD wContrast;
			WORD wMeanValue;
			BYTE bLabColor;
		}brightness_and_contrast;
		break;
	case 'rxim':
		struct ChannelMixer
		{
			WORD wVersion;
			WORD wMonochrome;
			WORD wColor[4];
			WORD wColor[2]; // TODO: documentation says 20 bytes!!!
		}channel_mixer;
		break;
	case 'lfhp':
		struct PhotoFilter
		{
			WORD wVersion;
			DWORD x, y, z;
			DWORD dwDensity;
			BYTE bPreserveLuminosity;
		}photo_filter;
		break;
	}

	if (dwDataLength - (current_offset - nPointerBefore) > 0)
		BYTE not_parsed_data[dwDataLength - (current_offset - nPointerBefore)];

	// decrement remaining data size
	nAdditionalLength = nAdditionalLength - (current_offset - this);
};

// p.47 ...
struct Pixel
{
	BYTE r[3];
	BYTE g[3];
	BYTE b[3];
};

struct CompressedLine
{
	var nCount = wByteCounts[array_index];
	BYTE compressed_data[nCount];
};

struct ImageDataSection
{
	CompressionType compression_type;

	var nSize = GetDocumentSize();
	if (compression_type == Compression_RLE)
	{
		WORD wByteCounts[file_header.dwHeight * file_header.wChannels];
		CompressedLine compressed_line_data[file_header.dwHeight * file_header.wChannels];
	}
	else
	{
		var data_pixels = ((nSize - current_offset) / sizeof(Pixel));
		[noindex] Pixel image_data[data_pixels];
	}
};

struct ImageResourceSection
{
	DWORD dwSectionSize;

	var ImageResourceSectionStart = current_offset;
	var ImageResourceSize = dwSectionSize;

	[noindex] ImageResourceBlock image_resource_blocks[*];

	BYTE not_parsed_data[dwSectionSize - (current_offset - ImageResourceSectionStart)];
};

public struct PSD
{
	var nDebug;

	FileHeader file_header;
	ColorModeData color_mode;
	ImageResourceSection image_resource_section;

	LayerAndMaskInfo layer_and_mask;
	ImageDataSection imagedata_section;

	//$print("debug offset",nDebug);
};

// not used. p.68
// file extension - .aco
struct ColorSwatchesFile
{
	nDebug = current_offset;
	DWORD signature;
	$assert(signature == 'OCB8', "Hex Editor is unable to parse file: wrong ColorSwatches signature");

	WORD wVersion;
	WORD wColorCount;
	[noindex] Color colors[wColorCount];

	WORD wVersion2;
	WORD wColorCount2;
	[noindex] Color colors2[wColorCount2];
	UnicodeString color_name;
};