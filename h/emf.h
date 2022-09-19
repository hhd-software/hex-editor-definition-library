// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"

struct RECT
{
	DWORD left, top, right, bottom;
};

struct SIZE
{
	DWORD cx;
	DWORD cy;
};

struct POINT
{
	DWORD x;
	DWORD y;
};

struct POINTS
{
	SHORT x;
	SHORT y;
};

enum RecordType : DWORD
{
	EMR_HEADER = 0x00000001,
	EMR_POLYBEZIER = 0x00000002,
	EMR_POLYGON = 0x00000003,
	EMR_POLYLINE = 0x00000004,
	EMR_POLYBEZIERTO = 0x00000005,
	EMR_POLYLINETO = 0x00000006,
	EMR_POLYPOLYLINE = 0x00000007,
	EMR_POLYPOLYGON = 0x00000008,
	EMR_SETWINDOWEXTEX = 0x00000009,
	EMR_SETWINDOWORGEX = 0x0000000A,
	EMR_SETVIEWPORTEXTEX = 0x0000000B,
	EMR_SETVIEWPORTORGEX = 0x0000000C,
	EMR_SETBRUSHORGEX = 0x0000000D,
	EMR_EOF = 0x0000000E,
	EMR_SETPIXELV = 0x0000000F,
	EMR_SETMAPPERFLAGS = 0x00000010,
	EMR_SETMAPMODE = 0x00000011,
	EMR_SETBKMODE = 0x00000012,
	EMR_SETPOLYFILLMODE = 0x00000013,
	EMR_SETROP2 = 0x00000014,
	EMR_SETSTRETCHBLTMODE = 0x00000015,
	EMR_SETTEXTALIGN = 0x00000016,
	EMR_SETCOLORADJUSTMENT = 0x00000017,
	EMR_SETTEXTCOLOR = 0x00000018,
	EMR_SETBKCOLOR = 0x00000019,
	EMR_OFFSETCLIPRGN = 0x0000001A,
	EMR_MOVETOEX = 0x0000001B,
	EMR_SETMETARGN = 0x0000001C,
	EMR_EXCLUDECLIPRECT = 0x0000001D,
	EMR_INTERSECTCLIPRECT = 0x0000001E,
	EMR_SCALEVIEWPORTEXTEX = 0x0000001F,
	EMR_SCALEWINDOWEXTEX = 0x00000020,
	EMR_SAVEDC = 0x00000021,
	EMR_RESTOREDC = 0x00000022,
	EMR_SETWORLDTRANSFORM = 0x00000023,
	EMR_MODIFYWORLDTRANSFORM = 0x00000024,
	EMR_SELECTOBJECT = 0x00000025,
	EMR_CREATEPEN = 0x00000026,
	EMR_CREATEBRUSHINDIRECT = 0x00000027,
	EMR_DELETEOBJECT = 0x00000028,
	EMR_ANGLEARC = 0x00000029,
	EMR_ELLIPSE = 0x0000002A,
	EMR_RECTANGLE = 0x0000002B,
	EMR_ROUNDRECT = 0x0000002C,
	EMR_ARC = 0x0000002D,
	EMR_CHORD = 0x0000002E,
	EMR_PIE = 0x0000002F,
	EMR_SELECTPALETTE = 0x00000030,
	EMR_CREATEPALETTE = 0x00000031,
	EMR_SETPALETTEENTRIES = 0x00000032,
	EMR_RESIZEPALETTE = 0x00000033,
	EMR_REALIZEPALETTE = 0x00000034,
	EMR_EXTFLOODFILL = 0x00000035,
	EMR_LINETO = 0x00000036,
	EMR_ARCTO = 0x00000037,
	EMR_POLYDRAW = 0x00000038,
	EMR_SETARCDIRECTION = 0x00000039,
	EMR_SETMITERLIMIT = 0x0000003A,
	EMR_BEGINPATH = 0x0000003B,
	EMR_ENDPATH = 0x0000003C,
	EMR_CLOSEFIGURE = 0x0000003D,
	EMR_FILLPATH = 0x0000003E,
	EMR_STROKEANDFILLPATH = 0x0000003F,
	EMR_STROKEPATH = 0x00000040,
	EMR_FLATTENPATH = 0x00000041,
	EMR_WIDENPATH = 0x00000042,
	EMR_SELECTCLIPPATH = 0x00000043,
	EMR_ABORTPATH = 0x00000044,
	EMR_RESERVED_69 = 0x00000045,
	EMR_COMMENT = 0x00000046,
	EMR_FILLRGN = 0x00000047,
	EMR_FRAMERGN = 0x00000048,
	EMR_INVERTRGN = 0x00000049,
	EMR_PAINTRGN = 0x0000004A,
	EMR_EXTSELECTCLIPRGN = 0x0000004B,
	EMR_BITBLT = 0x0000004C,
	EMR_STRETCHBLT = 0x0000004D,
	EMR_MASKBLT = 0x0000004E,
	EMR_PLGBLT = 0x0000004F,
	EMR_SETDIBITSTODEVICE = 0x00000050,
	EMR_STRETCHDIBITS = 0x00000051,
	EMR_EXTCREATEFONTINDIRECTW = 0x00000052,
	EMR_EXTTEXTOUTA = 0x00000053,
	EMR_EXTTEXTOUTW = 0x00000054,
	EMR_POLYBEZIER16 = 0x00000055,
	EMR_POLYGON16 = 0x00000056,
	EMR_POLYLINE16 = 0x00000057,
	EMR_POLYBEZIERTO16 = 0x00000058,
	EMR_POLYLINETO16 = 0x00000059,
	EMR_POLYPOLYLINE16 = 0x0000005A,
	EMR_POLYPOLYGON16 = 0x0000005B,
	EMR_POLYDRAW16 = 0x0000005C,
	EMR_CREATEMONOBRUSH = 0x0000005D,
	EMR_CREATEDIBPATTERNBRUSHPT = 0x0000005E,
	EMR_EXTCREATEPEN = 0x0000005F,
	EMR_POLYTEXTOUTA = 0x00000060,
	EMR_POLYTEXTOUTW = 0x00000061,
	EMR_SETICMMODE = 0x00000062,
	EMR_CREATECOLORSPACE = 0x00000063,
	EMR_SETCOLORSPACE = 0x00000064,
	EMR_DELETECOLORSPACE = 0x00000065,
	EMR_GLSRECORD = 0x00000066,
	EMR_GLSBOUNDEDRECORD = 0x00000067,
	EMR_PIXELFORMAT = 0x00000068,
	EMR_DRAWESCAPE = 0x00000069,
	EMR_EXTESCAPE = 0x0000006A,
	EMR_RESERVED_107 = 0x0000006B,
	EMR_SMALLTEXTOUT = 0x0000006C,
	EMR_FORCEUFIMAPPING = 0x0000006D,
	EMR_NAMEDESCAPE = 0x0000006E,
	EMR_COLORCORRECTPALETTE = 0x0000006F,
	EMR_SETICMPROFILEA = 0x00000070,
	EMR_SETICMPROFILEW = 0x00000071,
	EMR_ALPHABLEND = 0x00000072,
	EMR_SETLAYOUT = 0x00000073,
	EMR_TRANSPARENTBLT = 0x00000074,
	EMR_RESERVED_117 = 0x00000075,
	EMR_GRADIENTFILL = 0x00000076,
	EMR_SETLINKEDUFIS = 0x00000077,
	EMR_SETTEXTJUSTIFICATION = 0x00000078,
	EMR_COLORMATCHTOTARGETW = 0x00000079,
	EMR_CREATECOLORSPACEW = 0x0000007A
};

// forward declaration
struct Record;

struct OffsetDescriptor
{
	if (current_offset != 0)
	{
		WORD descriptor_bytes[nDescription];

		// records are located immediately after description!!!
		//WORD wPad; // check if it's OK for your file! 
	}
};

struct Records;

struct EMR_HEADER
{
	RecordType type;
	$assert(type == EMR_HEADER, "Invalid EMF file format");

	DWORD dwSize as Records *;
	RECT rcBounds;
	RECT rcFrame;

	DWORD dwSignature;
	DWORD dwVersion;
	DWORD dwBytes;
	DWORD dwRecords;

	var nRecords = dwRecords;

	WORD wHandles;
	WORD wReserved;
	DWORD nDescription;

	DWORD description as OffsetDescriptor *;
	//var nRecordsOffset = description + nDescription;

	DWORD dwPalEntries;

	SIZE szDevice;
	SIZE szMillimeters;

	//$bind("struct Records","records",dwSize);
};

/*
* Different record types
*/
struct EMRPOLYBEZIER
{
	RECT rcBounds;
	DWORD dwCount;
	[noindex] POINT points[dwCount];
};

struct EMRPOLYPOLYLINE
{
	RECT rcBounds;
	DWORD dwNumberOfPolylines;
	DWORD dwCount;

	[noindex] POINT polyline_points[nNumberOfPolylines];
	[noindex] POINT points[dwCount];
};

struct EMRSETWINDOWEXTEX
{
	SIZE extent;
};

struct EMRSETWINDOWORGEX
{
	POINT origin;
};

struct EMREOF
{
	DWORD nPalEntries;
	DWORD offPalEntries;
	DWORD nSizeLast;
};

struct EMRSETPIXELV
{
	POINT ptlPixel;
	COLORREF crColor;
};

struct EMRSETMAPPERFLAGS
{
	DWORD dwFlags;
};

enum MapMode : DWORD
{
	MM_TEXT = 1,
	MM_LOMETRIC = 2,
	MM_HIMETRIC = 3,
	MM_LOENGLISH = 4,
	MM_HIENGLISH = 5,
	MM_TWIPS = 6,
	MM_ISOTROPIC = 7,
	MM_ANISOTROPIC = 8
};
struct EMRSETMAPMODE
{
	MapMode mode;
};

enum ClipModeEnum : DWORD
{
	RGN_AND = 1,
	RGN_OR = 2,
	RGN_XOR = 3,
	RGN_DIFF = 4,
	RGN_COPY = 5
};
struct EMRSELECTCLIPPATH
{
	ClipModeEnum Mode;
};

enum StretchModeEnum : DWORD
{
	BLACKONWHITE = 1,
	WHITEONBLACK = 2,
	COLORONCOLOR = 3,
	HALFTONE = 4,
};
struct EMRSETSTRETCHMODE
{
	StretchModeEnum mode;
};

enum BkModeEnum : DWORD
{
	TRANSPARENT = 1,
	OPAQUE = 2
};
struct EMRSETBKMODE
{
	BkModeEnum mode;
};

enum PolyFillModeEnum : DWORD
{
	ALTERNATE = 1,
	WINDING = 2
};
struct EMRSETPOLYFILLMODE
{
	PolyFillModeEnum mode;
};

enum RopModeEnum :DWORD
{
	R2_BLACK = 1,
	R2_NOTMERGEPEN = 2,
	R2_MASKNOTPEN = 3,
	R2_NOTCOPYPEN = 4,
	R2_MASKPENNOT = 5,
	R2_NOT = 6,
	R2_XORPEN = 7,
	R2_NOTMASKPEN = 8,
	R2_MASKPEN = 9,
	R2_NOTXORPEN = 10,
	R2_NOP = 11,
	R2_MERGENOTPEN = 12,
	R2_COPYPEN = 13,
	R2_MERGEPENNOT = 14,
	R2_MERGEPEN = 15,
	R2_WHITE = 16,
	R2_LAST = 16,
};
struct EMRSETROP2
{
	RopModeEnum mode;
};

enum TextAlignModeEnum :DWORD
{
	TA_NOUPDATECP = 0,
	TA_TOP = 0,
	TA_LEFT = 0,
	TA_UPDATECP = 1,
	TA_RIGHT = 2,
	TA_CENTER = 6,
	TA_BOTTOM = 8,
	TA_BASELINE = 24,
	TA_RTLREADING = 256,

	VTA_BASELINE = TA_BASELINE, // TODO: check 
	VTA_CENTER = TA_CENTER
};

struct EMRSETTEXTALIGN
{
	TextAlignModeEnum mode;
};

struct EMRSETCOLORADJUSTMENT
{
	WORD wSize;
	WORD wFlags;
	WORD wIlluminantIndex;
	WORD wRedGamma;
	WORD wGreenGamma;
	WORD wBlueGamma;
	WORD wReferenceBlack;
	WORD wReferenceWhite;

	SHORT shContrast;
	SHORT shBrightness;
	SHORT shColorfulness;
	SHORT shRedGreenTint;
};

struct EMREXCLUDECLIPRECT
{
	RECT rc;
};

struct EMRSCALEVIEWPORTEXTEX
{
	LONG lgXNum;
	LONG lgXDenom;
	LONG lgYNum;
	LONG lgYDenom;
};

struct XFORM
{
	FLOAT eM11;
	FLOAT eM12;
	FLOAT eM21;
	FLOAT eM22;
	FLOAT eDx;
	FLOAT eDy;
};

struct EMRSETWORLDTRANSFORM
{
	XFORM xform;
};

enum WordlTransformFlags :DWORD
{
	MWT_IDENTITY = 1,
	MWT_LEFTMULTIPLY = 2,
	MWT_RIGHTMULTIPLY = 3
};

struct EMRMODIFYWORLDTRANSFORM
{
	EMRSETWORLDTRANSFORM set_world_transform;
	WordlTransformFlags flags;
};

enum PenStyle :DWORD
{
	PS_SOLID = 0,
	PS_DASH = 1,
	PS_DOT = 2,
	PS_DASHDOT = 3,
	PS_DASHDOTDOT = 4,
	PS_NULL = 5,
	PS_INSIDEFRAME = 6,
	PS_USERSTYLE = 7,
	PS_ALTERNATE = 8
};

struct LOGPEN
{
	PenStyle lopnStyle;
	POINT lopnWidth;
	COLORREF lopnColor;
};

struct EMRCREATEPEN
{
	DWORD dwPenIndex; // Pen handle index
	LOGPEN lopn;
};

enum LogBrushStyle :DWORD
{
	BS_SOLID = 0,
	BS_NULL = 1,
	BS_HOLLOW = BS_NULL,
	BS_HATCHED = 2,
	BS_PATTERN = 3,
	BS_INDEXED = 4,
	BS_DIBPATTERN = 5,
	BS_DIBPATTERNPT = 6,
	BS_PATTERN8X8 = 7,
	BS_DIBPATTERN8X8 = 8,
	BS_MONOPATTERN = 9
};
struct LOGBRUSH
{
	LogBrushStyle lbStyle;
	COLORREF lbColor;
	ULONG lbHatch;
};

struct EMRCREATEBRUSHINDIRECT
{
	DWORD dwBrushIndex;
	LOGBRUSH log_brush;
};

struct EMRANGLEARC
{
	POINT ptlCenter;
	DWORD dwRadius;
	FLOAT fStartAngle;
	FLOAT fSweepAngle;
};

struct EMRROUNDRECT
{
	RECT rclBox;
	SIZE szlCorner;
};

struct EMRARC
{
	RECT rclBox;
	POINT ptlStart;
	POINT ptlEnd;
};

struct PALETTEENTRY
{
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
};

struct LOGPALETTE
{
	WORD palVersion;
	WORD palNumEntries;
	[noindex] PALETTEENTRY palPalEntry[palNumEntries];
};

struct EMRCREATEPALETTE
{
	DWORD dwPal;
	LOGPALETTE lgpl;
};

struct EMRSETPALETTEENTRIES
{
	DWORD ihPal;
	DWORD iStart;
	DWORD cEntries;
	[noindex] PALETTEENTRY aPalEntries[cEntries];
};

struct EMREXTFLOODFILL
{
	POINT ptlStart;
	COLORREF crColor;
	DWORD dwMode;
};

struct EMRPOLYDRAW
{
	RECT rclBounds;
	DWORD cptl;
	[noindex] POINT aptl[cptl];
	[noindex] BYTE abTypes[cptl];
};

struct EMRFILLRGN
{
	RECT rclBounds;
	DWORD dwRgnData;
	DWORD dwBrush;
	[noindex] BYTE nRgnData[dwRgnData];
};

struct EMRFRAMERGN
{
	RECT rclBounds;
	DWORD dwRgnData;
	DWORD dwBrush;
	SIZE szlStroke;
	BYTE nRgnData[dwRgnData];
};

struct EMRINVERTRGN
{
	RECT rclBounds;
	DWORD dwRgnData;
	BYTE nRgnData[dwRgnData];
};

struct EMREXTSELECTCLIPRGN
{
	DWORD dwRgnData;
	ClipModeEnum mode;
	BYTE nRgnData[dwRgnData];
};

struct EMRBITBLT
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG cxDest;
	LONG cyDest;
	DWORD dwRop;
	LONG xSrc;
	LONG ySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
};

struct EMRSTRETCHBLT
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG cxDest;
	LONG cyDest;
	DWORD dwRop;
	LONG xSrc;
	LONG ySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	LONG cxSrc;
	LONG cySrc;
};

struct EMRMASKBLT
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG cxDest;
	LONG cyDest;
	DWORD dwRop;
	LONG xSrc;
	LONG ySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	LONG xMask;
	LONG yMask;
	DWORD iUsageMask;
	DWORD offBmiMask;
	DWORD cbBmiMask;
	DWORD offBitsMask;
	DWORD cbBitsMask;
};

struct EMRPLGBLT
{
	RECT rclBounds;
	[noindex] POINT aptlDest[3];
	LONG xSrc;
	LONG ySrc;
	LONG cxSrc;
	LONG cySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	LONG xMask;
	LONG yMask;
	DWORD iUsageMask;
	DWORD offBmiMask;
	DWORD cbBmiMask;
	DWORD offBitsMask;
	DWORD cbBitsMask;
};

struct EMRSETDIBITSTODEVICE
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG xSrc;
	LONG ySrc;
	LONG cxSrc;
	LONG cySrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	DWORD iUsageSrc;
	DWORD iStartScan;
	DWORD cScans;
};

struct EMRSTRETCHDIBITS
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG xSrc;
	LONG ySrc;
	LONG cxSrc;
	LONG cySrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	DWORD iUsageSrc;
	DWORD dwRop;
	LONG cxDest;
	LONG cyDest;
};

#define LF_FULLFACESIZE 64
#define LF_FACESIZE 32
#define ELF_VENDOR_SIZE 4

struct LOGFONTW
{
	LONG lfHeight;
	LONG lfWidth;
	LONG lfEscapement;
	LONG lfOrientation;
	LONG lfWeight;
	BYTE lfItalic;
	BYTE lfUnderline;
	BYTE lfStrikeOut;
	BYTE lfCharSet;
	BYTE lfOutPrecision;
	BYTE lfClipPrecision;
	BYTE lfQuality;
	BYTE lfPitchAndFamily;
	[noindex] WCHAR lfFaceName[LF_FACESIZE];
};

struct PANOSE
{
	BYTE bFamilyType;
	BYTE bSerifStyle;
	BYTE bWeight;
	BYTE bProportion;
	BYTE bContrast;
	BYTE bStrokeVariation;
	BYTE bArmStyle;
	BYTE bLetterform;
	BYTE bMidline;
	BYTE bXHeight;
};

struct EXTLOGFONTW
{
	LOGFONTW elfLogFont;
	WCHAR elfFullName[LF_FULLFACESIZE];
	WCHAR elfStyle[LF_FACESIZE];
	DWORD elfVersion;
	DWORD elfStyleSize;
	DWORD elfMatch;
	DWORD elfReserved;
	BYTE elfVendorId[ELF_VENDOR_SIZE];
	DWORD elfCulture;
	PANOSE elfPanose;
};
struct EMREXTCREATEFONTINDIRECTW
{
	DWORD ihFont;
	EXTLOGFONTW elfw;
};

struct EMRTEXT
{
	POINT ptReference;
	DWORD nChars;
	DWORD offString; // Offset to the string
	DWORD fOptions;
	RECT rc;
	DWORD offDx; // Offset to the inter-character spacing array.
	// This is always given.
};

struct EMREXTTEXTOUTA
{
	RECT rcBounds;
	DWORD iGraphicsMode;
	FLOAT exScale;
	FLOAT eyScale;
	EMRTEXT emrtext;
};

struct EMRPOLYBEZIER16
{
	RECT rcBounds;
	DWORD cpts;
	[noindex] POINTS apts[cpts];
};

struct EMRPOLYPOLYLINE16
{
	RECT rclBounds;
	DWORD nPolys;
	DWORD cpts;
	DWORD aPolyCounts[nPolys];
	[noindex] POINTS apts[cpts];
};

struct EMRPOLYDRAW16
{
	RECT rcBounds;
	DWORD cpts;
	[noindex] POINTS apts[cpts];
	BYTE abTypes[cpts];
};

struct EMRCREATEMONOBRUSH
{
	DWORD dwhBrush;
	DWORD dwUsage;
	DWORD dwBmi;
	DWORD dwBmi;
	DWORD dwBits;
	DWORD dwBits;
};

struct EXTLOGPEN
{
	DWORD dwPenStyle;
	DWORD dwWidth;
	UINT dwBrushStyle;
	COLORREF crColor;
	DWORD qwHatch;
	DWORD dwNumEntries;
	DWORD dwStyleEntry[dwNumEntries];
};

struct EMREXTCREATEPEN
{
	DWORD dwPen;
	DWORD dwOffBmi;
	DWORD dwCbBmi;
	DWORD dwOffBits;
	DWORD dwCbBits;
	EXTLOGPEN elp;
};

struct EMRPOLYTEXTOUTA
{
	RECT rclBounds;
	DWORD dwGraphicsMode;
	FLOAT fExScale;
	FLOAT fEyScale;
	LONG dwStrings;
	[noindex] EMRTEXT aemrtext[dwStrings];
};

enum IcmModeEnum :DWORD
{
	ICM_ON,
	ICM_OFF,
	ICM_QUERY,
	ICM_DONE_OUTSIDEDC
};

struct EMRSETICMMODE
{
	IcmModeEnum mode;
};

#define MAX_PATH 260

typedef long FXPT2DOT30;

struct CIEXYZ
{
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
};

struct CIEXYZTRIPLE
{
	CIEXYZ ciexyzRed;
	CIEXYZ ciexyzGreen;
	CIEXYZ ciexyzBlue;
};

struct LOGCOLORSPACEA
{
	DWORD lcsSignature;
	DWORD lcsVersion;
	DWORD lcsSize;
	LONG lcsCSType;
	LONG lcsIntent;
	CIEXYZTRIPLE lcsEndpoints;
	DWORD lcsGammaRed;
	DWORD lcsGammaGreen;
	DWORD lcsGammaBlue;
	CHAR lcsFilename[MAX_PATH];
};

struct EMRCREATECOLORSPACE
{
	DWORD ihCS; // ColorSpace handle index
	LOGCOLORSPACEA lcs;
};

struct EMRGLSBOUNDEDRECORD
{
	RECT rcBounds; // Bounds in recording coordinates
	DWORD cbData; // Size of data in bytes
	BYTE Data[cbData];
};

struct PIXELFORMATDESCRIPTOR
{
	WORD nSize;
	WORD nVersion;
	DWORD dwFlags;
	BYTE iPixelType;
	BYTE cColorBits;
	BYTE cRedBits;
	BYTE cRedShift;
	BYTE cGreenBits;
	BYTE cGreenShift;
	BYTE cBlueBits;
	BYTE cBlueShift;
	BYTE cAlphaBits;
	BYTE cAlphaShift;
	BYTE cAccumBits;
	BYTE cAccumRedBits;
	BYTE cAccumGreenBits;
	BYTE cAccumBlueBits;
	BYTE cAccumAlphaBits;
	BYTE cDepthBits;
	BYTE cStencilBits;
	BYTE cAuxBuffers;
	BYTE iLayerType;
	BYTE bReserved;
	DWORD dwLayerMask;
	DWORD dwVisibleMask;
	DWORD dwDamageMask;
};

struct EMRPIXELFORMAT
{
	PIXELFORMATDESCRIPTOR pfd;
};

struct EMREXTESCAPE
{
	DWORD ihPen;
	DWORD offBmi;
	DWORD cbBmi;
	DWORD offBits;
	DWORD cbBits;
	EXTLOGPEN elp;
};

struct EMRCOLORCORRECTPALETTE
{
	DWORD ihPalette; // Palette handle index
	DWORD nFirstEntry; // Index of first entry to correct
	DWORD nPalEntries; // Number of palette entries to correct
	DWORD nReserved;
};

struct EMRSETICMPROFILEA
{
	DWORD dwFlags; // flags
	DWORD cbName; // Size of desired profile name
	DWORD cbData; // Size of raw profile data if attached
	BYTE Data[cbName + cbData]; // Array size is cbName + cbData
};

struct EMRALPHABLEND
{
	RECT rcBounds;
	LONG xDest;
	LONG yDest;
	LONG cxDest;
	LONG cyDest;
	DWORD dwRop;
	LONG xSrc;
	LONG ySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	LONG cxSrc;
	LONG cySrc;
};

enum SetLayoutEnum :DWORD
{
	LAYOUT_BITMAPORIENTATIONPRESERVED,
	LAYOUT_RTL
};

struct EMRSETLAYOUT
{
	SetLayoutEnum layout;
};

struct EMRTRANSPARENTBLT
{
	RECT rclBounds;
	LONG xDest;
	LONG yDest;
	LONG cxDest;
	LONG cyDest;
	DWORD dwRop;
	LONG xSrc;
	LONG ySrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DWORD offBmiSrc;
	DWORD cbBmiSrc;
	DWORD offBitsSrc;
	DWORD cbBitsSrc;
	LONG cxSrc;
	LONG cySrc;
};

typedef USHORT COLOR16;

struct TRIVERTEX
{
	LONG x;
	LONG y;
	COLOR16 Red;
	COLOR16 Green;
	COLOR16 Blue;
	COLOR16 Alpha;
};

struct EMRGRADIENTFILL
{
	RECT rclBounds;
	DWORD nVer;
	DWORD nTri;
	ULONG ulMode;
	[noindex] TRIVERTEX Ver[nTri];
};

enum ColorMatchToTargetActionEnum :DWORD
{
	CS_ENABLE,
	CS_DISABLE,
	CS_DELETE_TRANSFORM
};

struct EMRCOLORMATCHTOTARGETW
{
	ColorMatchToTargetActionEnum dwAction;
	DWORD dwFlags;
	DWORD cbName;
	DWORD cbData;
	BYTE Data[cbData];
};

struct Record
{
	RecordType nType;
	DWORD dwSize;

	switch (nType)
	{
	case EMR_POLYBEZIER:
	case EMR_POLYGON:
	case EMR_POLYLINE:
	case EMR_POLYBEZIERTO:
	case EMR_POLYLINETO:
		EMRPOLYBEZIER points;
		break;
	case EMR_POLYPOLYLINE:
	case EMR_POLYPOLYGON:
		EMRPOLYPOLYLINE points;
		break;
	case EMR_SETWINDOWEXTEX: // SIZE
	case EMR_SETVIEWPORTEXTEX:
		EMRSETWINDOWEXTEX set_window_text_ex;
		break;
	case EMR_SETWINDOWORGEX: // POINT
	case EMR_SETVIEWPORTORGEX:
	case EMR_SETBRUSHORGEX:
	case EMR_OFFSETCLIPRGN:
	case EMR_MOVETOEX:
	case EMR_LINETO:
		EMRSETWINDOWORGEX set_window_org_ex;
		break;
	case EMR_EOF:
		EMREOF eof;
		break;
	case EMR_SETPIXELV:
		EMRSETPIXELV set_pixel;
		break;
	case EMR_SETMAPPERFLAGS:
		EMRSETMAPPERFLAGS set_flags;
		break;
	case EMR_SETMAPMODE:
		EMRSETMAPMODE map_mode;
		break;
	case EMR_SETBKMODE:
		EMRSETBKMODE bk_mode;
		break;
	case EMR_SETPOLYFILLMODE:
		EMRSETPOLYFILLMODE fill_mode;
		break;
	case EMR_SETROP2:
		EMRSETROP2 rop_mode;
		break;
	case EMR_SETSTRETCHBLTMODE:
		EMRSETSTRETCHMODE stretch_mode;
		break;
	case EMR_SETTEXTALIGN:
		EMRSETTEXTALIGN ta_mode;
		break;
	case EMR_SETCOLORADJUSTMENT:
		EMRSETCOLORADJUSTMENT set_color_adjustment;
		break;
	case EMR_SETTEXTCOLOR:
	case EMR_SETBKCOLOR:
		COLORREF clr;
		break;
	case EMR_SETMETARGN: // no data
	case EMR_SAVEDC:
	case EMR_REALIZEPALETTE:
	case EMR_BEGINPATH:
	case EMR_ENDPATH:
	case EMR_CLOSEFIGURE:
	case EMR_FLATTENPATH:
	case EMR_WIDENPATH:
	case EMR_BEGINPATH:
	case EMR_ENDPATH:
	case EMR_CLOSEFIGURE:
	case EMR_FLATTENPATH:
	case EMR_WIDENPATH:
	case EMR_ABORTPATH:
		struct None
		{
			// TODO: it is empty
		};
		break;
	case EMR_EXCLUDECLIPRECT:
	case EMR_INTERSECTCLIPRECT: // RECT
	case EMR_ELLIPSE:
	case EMR_RECTANGLE:
	case EMR_FILLPATH:
	case EMR_STROKEANDFILLPATH:
	case EMR_STROKEPATH:
	case EMR_FILLPATH:
	case EMR_STROKEANDFILLPATH:
	case EMR_STROKEPATH:
		EMREXCLUDECLIPRECT rect;
		break;
	case EMR_SCALEVIEWPORTEXTEX:
	case EMR_SCALEWINDOWEXTEX:
		EMRSCALEVIEWPORTEXTEX scale_viewport;
		break;
	case EMR_RESTOREDC:
		LONG nRelative;
		break;
	case EMR_SETWORLDTRANSFORM:
		EMRSETWORLDTRANSFORM set_world_transform;
		break;
	case EMR_MODIFYWORLDTRANSFORM:
		EMRMODIFYWORLDTRANSFORM modify_world_transform;
		break;
	case EMR_SELECTOBJECT:
		DWORD dwInObject;
		break;
	case EMR_CREATEPEN:
		EMRCREATEPEN create_pen;
		break;
	case EMR_CREATEBRUSHINDIRECT:
		EMRCREATEBRUSHINDIRECT create_brush;
		break;
	case EMR_DELETEOBJECT:
		DWORD dwObjectIndex;
		break;
	case EMR_ANGLEARC:
		EMRANGLEARC angle_arc;
		break;
	case EMR_ROUNDRECT:
		EMRROUNDRECT round_rect;
		break;
	case EMR_ARC:
	case EMR_CHORD:
	case EMR_PIE:
	case EMR_ARCTO:
		EMRARC arc;
		break;
	case EMR_SELECTPALETTE:
		DWORD dwPaletteIndex;
		break;
	case EMR_CREATEPALETTE:
		EMRCREATEPALETTE create_palette;
		break;
	case EMR_SETPALETTEENTRIES:
		EMRSETPALETTEENTRIES set_palette_entries;
		break;
	case EMR_RESIZEPALETTE:
		DWORD dwPaletteIndex;
		DWORD dwEntries;
		break;
	case EMR_EXTFLOODFILL:
		EMREXTFLOODFILL ext_flood_fill;
		break;
	case EMR_POLYDRAW:
		EMRPOLYDRAW poly_draw;
		break;
	case EMR_SETARCDIRECTION:
		DWORD dwArcDirection;
		break;
	case EMR_SETMITERLIMIT:
		FLOAT fMiterLimit;
		break;
	case EMR_SELECTCLIPPATH:
		EMRSELECTCLIPPATH clip_path;
		break;
	case EMR_FILLRGN:
		EMRFILLRGN fill_rect;
		break;
		// TODO: fix it!!!
		//case EMR_FRAMERGN:
		// EMRFRAMERGN frame_rgn;
		// break;
	case EMR_INVERTRGN:
	case EMR_PAINTRGN:
		EMRINVERTRGN invert_rgn;
		break;
	case EMR_EXTSELECTCLIPRGN:
		EMREXTSELECTCLIPRGN select_clip_rgn;
		break;
	case EMR_BITBLT:
		EMRBITBLT bit_blt;
		break;
	case EMR_STRETCHBLT:
		EMRSTRETCHBLT stretch_blt;
		break;
	case EMR_MASKBLT:
		EMRMASKBLT mask_blt;
		break;
	case EMR_PLGBLT:
		EMRPLGBLT plg_blt;
		break;
	case EMR_SETDIBITSTODEVICE:
		EMRSETDIBITSTODEVICE set_bits;
		break;
	case EMR_STRETCHDIBITS:
		EMRSTRETCHDIBITS stretch_dib_bits;
		break;
	case EMR_EXTCREATEFONTINDIRECTW:
		EMREXTCREATEFONTINDIRECTW ext_create_font_w;
		break;
	case EMR_EXTTEXTOUTA:
	case EMR_EXTTEXTOUTW:
		EMREXTTEXTOUTA ext_text_out_a;
		break;
	case EMR_POLYBEZIER16:
	case EMR_POLYGON16:
	case EMR_POLYLINE16:
	case EMR_POLYBEZIERTO16:
	case EMR_POLYLINETO16:
		EMRPOLYBEZIER16 poly_bezier16;
		break;
	case EMR_POLYPOLYLINE16:
	case EMR_POLYPOLYGON16:
		EMRPOLYPOLYLINE16 poly_poly_line;
		break;
	case EMR_POLYDRAW16:
		EMRPOLYDRAW16 poly_draw;
		break;
	case EMR_CREATEMONOBRUSH:
	case EMR_CREATEDIBPATTERNBRUSHPT:
		EMRCREATEMONOBRUSH create_mono_brush;
		break;
	case EMR_EXTCREATEPEN:
		EMREXTCREATEPEN ext_create_pen;
		break;
	case EMR_POLYTEXTOUTA:
	case EMR_POLYTEXTOUTW:
		EMRPOLYTEXTOUTA poly_text_out_a;
		break;
	case EMR_SETICMMODE:
		EMRSETICMMODE set_icm_mode;
		break;
	case EMR_CREATECOLORSPACE:
	case EMR_CREATECOLORSPACEW:
		EMRCREATECOLORSPACE create_color_space;
		break;
	case EMR_SETCOLORSPACE:
	case EMR_DELETECOLORSPACE:
		DWORD dwColorSpaceIndex;
		break;
	case EMR_GLSRECORD:
		DWORD cbData; // size of Data[], in bytes
		BYTE Data[cbData];
		break;
	case EMR_GLSBOUNDEDRECORD:
		EMRGLSBOUNDEDRECORD gls_bounded_record;
		break;
	case EMR_PIXELFORMAT:
		EMRPIXELFORMAT pixel_format;
		break;
	case EMR_DRAWESCAPE:
		DWORD dwObjectIndex;
		break;
	case EMR_EXTESCAPE:
		EMREXTESCAPE ext_escape;
		break;

	case EMR_SMALLTEXTOUT:
	case EMR_FORCEUFIMAPPING:
	case EMR_NAMEDESCAPE:
	case EMR_SETLINKEDUFIS:
	case EMR_SETTEXTJUSTIFICATION:
		struct Empty
		{
			// TODO:
		};
		break;
	case EMR_COLORCORRECTPALETTE:
		EMRCOLORCORRECTPALETTE color_correct_palette;
		break;
	case EMR_SETICMPROFILEA:
	case EMR_SETICMPROFILEW:
		EMRSETICMPROFILEA set_icm_profile;
		break;
	case EMR_ALPHABLEND:
		EMRALPHABLEND alpha_blend;
		break;
	case EMR_SETLAYOUT:
		EMRSETLAYOUT set_layout;
		break;
	case EMR_TRANSPARENTBLT:
		EMRTRANSPARENTBLT set_transparent_blt;
		break;
	case EMR_GRADIENTFILL:
		EMRGRADIENTFILL gradient_fill;
		break;
	case EMR_COLORMATCHTOTARGETW:
		EMRCOLORMATCHTOTARGETW color_match;
		break;
	}

	if (dwSize - (current_offset - this) >= 200000 || (dwSize < (current_offset - this))
		/*|| array_index>=100000*/)
	{
		$print("DEBUG: index", array_index);
		$print("DEBUG: offset", current_offset);
		$break_array(true);
	}
	else
	{
		BYTE not_parsed_data[dwSize - (current_offset - this)];
	}
};

public struct EmfHeader
{
	// Header
	EMR_HEADER header;
};

// please see pointer to this structure, because we don't want to use $bind directive
// (it will not see nRecords field)
struct Records
{
	//$print("current offset=",current_offset);
	if (current_offset)
		[noindex]Record records[nRecords - 1];
};
