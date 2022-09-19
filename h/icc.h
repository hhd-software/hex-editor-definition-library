// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file

// see http://www.color.org/icc_specs2.xalter for specifications
// http://www.color.org/ICC1v42_2006-05.pdf was used
// version - 4.2 (encoded as 0x04200000)
// + version 2!!!
#pragma once

#include "stddefs.h"

#pragma script("Pow.js")

#pragma byte_order(BigEndian)

// everything is in BigEndian!!!
struct dateTimeNumber
{
	WORD nYear;
	WORD nMonth;
	WORD nDay;

	WORD nHours;
	WORD nMinutes;
	WORD nSeconds;
};

// TODO: decode it (p.19)
struct s15Fixed16Number
{
	DWORD nNumber;
};

struct u16Fixed16Number
{
	DWORD nNumber;
};

struct u1Fixed15Number
{
	WORD nNumber;
};

struct u8Fixed8Number
{
	WORD nNumber;
};

struct XYZNumber
{
	s15Fixed16Number x, y, z;
};

struct response16Number
{
	WORD nInterval;
	WORD nReserved;
	s15Fixed16Number nMeasurement;
};

// ***********************************************************************
enum ProfileOrDeviceClass : DWORD
{
	InputDeviceProfile = 0x73636E72, // 'scnr'
	DisplayDeviceProfile = 0x6D6E7472, // 'mntr'
	OutputDeviceProfile = 0x70727472, // 'prtr'
	DeviceLinkProfile = 0x6C696E6B, // 'link'
	ColorSpaceConversionProfile = 0x73706163, // 'spac'
	AbstractProfile = 0x61627374, // 'abst'
	NamedColorProfile = 0x6E6D636C, // 'nmcl'
};

enum DataColorSpace : DWORD
{
	XYZData = 0x58595A20,
	labData = 0x4C616220,
	luvData = 0x4C757620,
	YCbCrData = 0x59436272,
	YxyData = 0x59787920,
	rgbData = 0x52474220,
	grayData = 0x47524159,
	hsvData = 0x48535620,
	hlsData = 0x484C5320,
	cmykData = 0x434D594B,
	cmyData = 0x434D5920,
	_2colorData = 0x32434C52, // '2CLR'
	_3colorData = 0x33434C52, // '3CLR'
	_4colorData = 0x34434C52, // '4CLR'
	_5colorData = 0x35434C52, // '5CLR'
	_6colorData = 0x36434C52, // '6CLR'
	_7colorData = 0x37434C52, // '7CLR'
	_8colorData = 0x38434C52, // '8CLR'
	_9colorData = 0x39434C52, // '9CLR'
	_10colorData = 0x41434C52, // 'ACLR'
	_11colorData = 0x42434C52, // 'BCLR'
	_12colorData = 0x43434C52, // 'CCLR'
	_13colorData = 0x44434C52, // 'DCLR'
	_14colorData = 0x45434C52, // 'ECLR'
	_15colorData = 0x46434C52 // 'FCLR'
};

enum MeasurementUnit : DWORD
{
	ISO_53_STAA = 0x53746141, // 'StaA'
	ISO_53_STAE = 0x53746145, // 'StaE'
	ISO_53_STAL = 0x53746149, // 'Stal'
	ISO_53_STAT = 0x53746154, // 'StaT'
	ISO_53_STAM = 0x5374614D, // 'StaM'
	DIN_16536_2_DN = 0x434E2020, // 'DN '
	DIN_16536_2_DNP = 0x434E2050, // 'DN P'
	DIN_16536_2_DNN = 0x434E4E20, // 'DNN '
	DIN_16536_2_DNNP = 0x434E4E50, // 'DNNP'
};

enum PlatformSignature : DWORD
{
	AppleSignature = 0x4150504C, // 'appl'
	MicrosoftSignature = 0x4D534654, // 'msft'
	SiliconGraphicsSignature = 0x53474920, // 'sgi'
	SunMicrosystems = 0x53554E57, // 'sunw'
};

enum TagType : DWORD
{
	AToB0Tag = 0x41324230, // 'A2B0'
	AToB1Tag = 0x41324231,
	AToB2Tag = 0x41324232,
	blueMatrixColumnTag = 0x6258595A, // 'bXYZ'
	blueTRCTag = 0x62545243, // 'bTRC'
	BToA0Tag = 0x42324130, // 'B2A0'
	BToA1Tag = 0x42324131, // 'B2A1'
	BToA2Tag = 0x42324132, // 'B2A2'
	calibrationDateTimeTag = 0x63616C74,// 'calt'
	charTargetTag = 0x74617267, // 'targ'
	chromaticAdaptationTag = 0x63686164,// 'chad'
	chromaticityTag = 0x6368726D, // 'chrm'
	colorantOrderTag = 0x636C726F, // 'clro'
	colorantTableTag = 0x636C7274, // 'clrt'
	colorantTableOutTag = 0x636C6F74, // 'clot'
	copyrightTag = 0x63707274, // 'cprt'
	deviceMfgDescTag = 0x646D6E64, // 'dmnd'
	deviceModelDescTag = 0x646D6464, // 'dmdd'
	gamutTag = 0x67616D74, // 'gamt'
	grayTRCTag = 0x6B545243, // 'kTRC'
	greenMatrixColumnTag = 0x6758595A, // 'gXYZ'
	greenTRCTag = 0x67545243, // 'gTRC'
	luminanceTag = 0x6C756D69, // 'lumi'
	measurementTag = 0x6D656173, // 'meas'
	mediaBlackPointTag = 0x636B7074, // 'bkpt'
	mediaWhitePointTag = 0x77747074, // 'wtpt'
	namedColor2Tag = 0x6E636C32, // 'ncl2',
	outputResponseTag = 0x72657370, // 'resp'
	preview0Tag = 0x70726530, // 'pre0'
	preview1Tag = 0x70726531, // 'pre2'
	preview2Tag = 0x70726532, // 'pre2'
	profileDescriptionTag = 0x64657363, // 'desc'
	profileSequenceDescTag = 0x70736571, // 'pseq'
	redMatrixColumnTag = 0x7258595A, // 'rXYZ'
	redTRCTag = 0x72545243, //'rTRC'
	technologyTag = 0x74656368, // 'tech'
	viewingCondDescTag = 0x76756564, // 'vued'
	viewingConditionsTag = 0x76696577, // 'view'

	// only in version 2
	deviceSettingsTag = 0x64657673, // 'devs'
	crdInfoTag = 0x63726469, // 'crdi'
	greenColorantTag = 0x6758595A, // 'gXYZ'
	ps2CRD0Tag = 0x70736430, // 'psd0'
	ps2CRD1Tag = 0x70736431,
	ps2CRD2Tag = 0x70736432,
	ps2CRD3Tag = 0x70736433,
	ps2CSATag = 0x70736434,
	ps2RenderingIntenetTag = 0x70733269, // 'ps2i'
	redColorantTag = 0x7258595A, // 'rXYZ'
	screeningTag = 0x7363726E, // 'scrn'
	ucrbgTag = 0x62666420, // 'bfd'

	namedColorType = 0x6E636F6C, // 'ncol' (obsolete)
};

enum TechnologyTypes : DWORD
{
	FilmScanner = 0x6673636E, // ‘fscn’
	DigitalCamera = 0x6463616D, // ‘dcam’
	ReflectiveScanner = 0x7273636E, // ‘rscn’
	InkJetPrinter = 0x696A6574, // ‘ijet’
	ThermalWaxPrinter = 0x74776178, // ‘twax’
	ElectrophotographicPrinter = 0x6570686F, // ‘epho’
	ElectrostaticPrinter = 0x65737461, // ‘esta’
	DyeSublimationPrinter = 0x64737562, // ‘dsub’
	PhotographicPaperPrinter = 0x7270686F, // ‘rpho’
	FilmWriter = 0x6670726E, // ‘fprn’
	VideoMonitor = 0x7669646D, // ‘vidm’
	VideoCamera = 0x76696463, // ‘vidc’
	ProjectionTelevision = 0x706A7476, // ‘pjtv’
	CathodeRayTubeDisplay = 0x43525420, // ‘CRT ’
	PassiveMatrixDisplay = 0x504D4420, // ‘PMD ’
	ActiveMatrixDisplay = 0x414D4420, // ‘AMD ’
	PhotoCD = 0x4B504344, // ‘KPCD’
	PhotoImageSetter = 0x696D6773, // ‘imgs’
	Gravure = 0x67726176, // ‘grav’
	OffsetLithography = 0x6F666673, // ‘offs’
	Silkscreen = 0x73696C6B, // ‘silk’
	Flexography = 0x666C6578, // ‘flex’
};

enum ProfileFlags : DWORD
{
	EMBEDDED_PROFILE = 1,
	USE_WITH_EMBEDDED_COLOR = 2 // Profile cannot be used independently from the embedded colour data (set to 1 if true, 0 if false)
};

enum DeviceAttributes : QWORD
{
	ATTR_TRANSPARENT = 1,
	ATTR_MATTE = 2,
	ATTR_POLARIY_NEGATIVE = 4,
	ATTR_MEDIA_BLACKANDWHITE = 8
};

enum RenderingIntent : DWORD
{
	PERCEPTUAL = 0,
	MEDIA_RELATIVE_COLORIMETRIC,
	SATURATION,
	ICC_ABSOLUTE_COLORIMETRIC,
};

struct ProfileHeader
{
	DWORD dwProfileSize;
	DWORD dwPreferredCMMType;
	DWORD dwProfileVersion;

	ProfileOrDeviceClass nProfileDeviceClass;
	DataColorSpace nColorSpaceOfData;
	DataColorSpace nProfileConnectionSpace;

	dateTimeNumber date_time;

	DWORD signature;

	// acsp !!!
	$assert(signature == 'psca', "Hex Editor is unable to parse file: wrong profile header signature");

	PlatformSignature nPrimaryPlatformSignature;
	ProfileFlags nProfileFlags;
	DWORD dwDeviceManufacturer;
	DWORD dwDeviceModel;

	DeviceAttributes device_attributes;
	RenderingIntent rendering_intent;

	XYZNumber illuminant_values;
	DWORD dwProfileCreatorSignature;

	if (dwProfileVersion >= 0x04000000)
	{
		char profile_id[16];
		BYTE reserved[28];
	}
	else
	{
		BYTE reserved[44];
	}
};

// **********************************************************************************************
// Tags:
enum ColorantAndPhosphorType : WORD
{
	ITU_R_BT709 = 1,
	SMPTE_RP145_1994 = 2,
	EBU_TECH3213E = 3,
	P22 = 4,
};

// chromaticityTag
struct ChromaticityTagData
{
	DWORD dwReserved;
	WORD wDeviceChanelNumber;
	ColorantAndPhosphorType type;

	struct ChromaData
	{
		u16Fixed16Number x, y;
	}cie_xy[wDeviceChanelNumber];
};

// colorantOrderTag
struct ColorandOrderTagData
{
	DWORD dwReserved;
	DWORD dwNumberOfColorants;
	BYTE colorants[dwNumberOfColorants];
};

// colorantTableTag
struct ColorantTableTagData
{
	DWORD dwReserved;
	DWORD dwNumberOfColorants;

	struct Colorant
	{
		char colorant_name[32];
		WORD p, c, s;
	}colorants[dwNumberOfColorants];
};

// blueTRCTag , grayTRCTag, greenTRCTag, redTRCTag 
struct CurveTypeData
{
	DWORD dwReserved;
	DWORD dwNumber;

	if (dwNumber == 1)
	{
		u8Fixed8Number curve;
	}
	else
	{
		WORD curves[dwNumber];
	}
};

enum DatatypeDataFlag : DWORD
{
	TYPE_ASCII = 0,
	TYPE_BINARY = 1
};

struct DatatypeData
{
	DWORD dwReserved;
	DatatypeDataFlag dwDataFlag;
	if (dwDataFlag == TYPE_ASCII)
		char data[12];
	else
		BYTE data[12];
};

struct DataTimeData
{
	DWORD dwReserved;
	dateTimeNumber date_time;
};

struct Lut16TypeData
{
	DWORD dwReserved;

	BYTE nInputChannelsNumber;
	BYTE nOutputChannelsNumber;
	BYTE nCLUT_GridPointsNumber;
	BYTE nReserved;

	s15Fixed16Number e00;
	s15Fixed16Number e01;
	s15Fixed16Number e02;
	s15Fixed16Number e10;
	s15Fixed16Number e11;
	s15Fixed16Number e12;
	s15Fixed16Number e20;
	s15Fixed16Number e21;
	s15Fixed16Number e22;

	WORD dwInputTableEntriesNumber;
	WORD dwOutputTableEntriesNumber;

	// TODO: unknown error
	/*
	WORD input_table[dwInputTableEntriesNumber * nInputChannelsNumber];

	// WARN: JavaScript function needed as long as no power available!!!
	//var nValTemp = JS_Pow(nCLUT_GridPointsNumber,nInputChannelsNumber);
	WORD clut_values[nOutputChannelsNumber /* * nValTemp/];
	WORD output_table[dwOutputTableEntriesNumber * nOutputChannelsNumber];
	*/
};

struct Lut8TypeData
{
	DWORD dwReserved;

	BYTE nInputChannelsNumber;
	BYTE nOutputChannelsNumber;
	BYTE nCLUT_GridPointsNumber;
	BYTE nReserved;

	s15Fixed16Number e00;
	s15Fixed16Number e01;
	s15Fixed16Number e02;
	s15Fixed16Number e10;
	s15Fixed16Number e11;
	s15Fixed16Number e12;
	s15Fixed16Number e20;
	s15Fixed16Number e21;
	s15Fixed16Number e22;

	BYTE input_table[256 * nInputChannelsNumber];
	BYTE clut_values[nOutputChannelsNumber * (nCLUT_GridPointsNumber ^ nInputChannelsNumber)];
	BYTE output_table[256 * nOutputChannelsNumber];
};

// 'mAB'
struct LuAtoBTypeData
{
	DWORD dwReserved;

	BYTE nInputChannelsNumber;
	BYTE nOutputChannelsNumber;
	WORD wReserved;

	DWORD dwOffsetToFirstBCurve;
	DWORD dwOffsetToMatrix;
	DWORD dwOffsetToMCurve;
	DWORD dwOffsetToFirstACurve;

	BYTE data[dwTagSize - (current_offset - this)];
};

// 'mBA'
struct LuBToATypeData
{
	DWORD dwReserved;

	BYTE nInputChannelsNumber;
	BYTE nOutputChannelsNumber;
	WORD wReserved;

	DWORD dwOffsetToFirstACurve;
	DWORD dwOffsetToMatrix;
	DWORD dwOffsetToMCurve;
	DWORD dwOffsetToFirstBCurve;

	BYTE data[dwTagSize - (current_offset - this)];
};

// measurementTag
enum MeasurementObserverEncodings : DWORD
{
	UNKNOWN = 0,
	CIE_1931 = 1,
	CIE_1964 = 2
};

enum MeasurementGeometry : DWORD
{
	UNKNOWN = 0,
	_045_450 = 1, // 0/45 or 45/0
	_0d_d0 = 2, // 0/D or D/0
	// etc
};

enum MeasurementFlare : DWORD
{
	ZERO_PERCENT = 0,
	HUNDRED_PERCENT = 0x10000
	// etc
};

enum MeasurementStdIlluminat : DWORD
{
	UNKNOWN = 0,
	D50 = 1,
	D65,
	D93,
	F2,
	D55,
	A,
	EQUI_POWER,
	F8
};

struct MeasurementTagData
{
	DWORD dwReserved;
	MeasurementObserverEncodings dwStandardObserverEncodedValue;
	XYZNumber xyz_tristimulus_backing_measurement;
	MeasurementGeometry geometry;
	MeasurementFlare flare;
	MeasurementStdIlluminat illuminant;
};

struct MultiLocalizedUnicodeText
{
	wchar_t string[dwNameLength];
};
struct MultiLocalizedUnicodeTypeData
{
	DWORD dwReserved;
	DWORD dwNumberOfNames;
	DWORD dwNameRecordSize;

	struct NameRecord
	{
		WORD wLanguageCode;
		WORD wCountryCode;
		DWORD dwNameLength;
		// TODO: check why not good (SNAP2007.icc)
		DWORD name as MultiLocalizedUnicodeText *(this);

		$assert(dwNameRecordSize >= 12, "Hex editor is unable to parse file: NameRecord length is wrong");
		BYTE not_parsed_data[dwNameRecordSize - 12];
	}name_records[dwNumberOfNames];
};

// 'ncl2'
struct NamedColor2TypeData
{
	DWORD dwReserved;
	DWORD dwVendorSpecificTag;

	DWORD dwCountOfNamedColors;
	DWORD dwNumberOfDeviceCoords;

	char szPrefix[32];
	char szSuffix[32];

	struct NamedColor
	{
		char szRootName[32];
		WORD p, c, s;
		WORD wDeviceCoordinates[dwNumberOfDeviceCoords];
	}named_colors[dwCountOfNamedColors];
};

// 'para'
struct ParametricCurveType
{
	DWORD dwReserved;

	WORD wEncodedValue;
	WORD wReserved;

	switch (wEncodedValue)
	{
	case 0:
		s15Fixed16Number gamma;
		break;
	case 1:
		s15Fixed16Number gamma, a, b;
		break;
	case 2:
		s15Fixed16Number gamma, a, b, c;
		break;
	case 3:
		s15Fixed16Number gamma, a, b, c, d;
		break;
	case 4:
		s15Fixed16Number gamma, a, b, c, d, e, f;
		break;
	}
};

// Forward Declaration
struct Tag;

struct DescriptionStructure
{
	if (nByteCount <= 0)
		$break_array(false);

	char szDeviceManufacturerSignature[4];
	char szDeviceModelSignature[4];
	char szDeviceAttributes[8];
	Tag device_tech_info;

	nByteCount = nByteCount - (current_offset - this);
};

// 'pseq'
struct ProfileSequenceDescTypeData
{
	DWORD dwReserved;
	DWORD dwCount;

	var nByteCount = (dwTagSize - 12);
	[noindex] DescriptionStructure description_structures[*];
};

struct CurveStructure
{
	MeasurementUnit measurement_unit;
	DWORD dwNumberOfMeasurementsForChannels[wChannelNumber];
	XYZNumber xyzPerChannel[wChannelNumber];
	response16Number response_array[wMeasurementTypesCount];
};

struct ResponseCurveSet16TypeData
{
	DWORD dwReserved;
	WORD wChannelNumber;
	WORD wMeasurementTypesCount;

	struct PointerToData
	{
		// relative to byte 0 of this structure
		DWORD curve as CurveStructure *(this);
	}data_offsets[wMeasurementTypesCount];
};

// 'sf32'
struct s15Fixed16ArrayType
{
	DWORD dwReserved;
	s15Fixed16Number arr[(dwTagSize - 8) / sizeof(s15Fixed16Number)];
};

// 'sig'
struct SignatureTypeData
{
	DWORD dwReserved;

	union Signature
	{
		char signature_string[4];
		BYTE signature_bytes[4];
		DWORD signature_value;
	}signature;
};

// 'text'
struct TextTypeData
{
	DWORD dwReserved;
	char text[dwTagSize - 8];
};

// 'uf32'
struct u16Fixed16ArrayType
{
	DWORD dwReserved;
	u16Fixed16Number arr[(dwTagSize - 8) / sizeof(u16Fixed16Number)];
};

// 'ui16'
struct uInt16ArrayTypeData
{
	DWORD dwReserved;
	WORD arr[(dwTagSize - 8) / sizeof(WORD)];
};

// 'ui32'
struct uInt32ArrayTypeData
{
	DWORD dwReserved;
	DWORD arr[(dwTagSize - 8) / sizeof(DWORD)];
};

// 'ui64'
struct uInt64ArrayType
{
	DWORD dwReserved;
	QWORD arr[(dwTagSize - 8) / sizeof(QWORD)];
};

// 'ui08'
struct uInt8ArrayType
{
	DWORD dwReserved;
	BYTE arr[(dwTagSize - 8) / sizeof(BYTE)];
};

// 'view' - viewingConditionsTag
struct ViewingConditionsTypeData
{
	DWORD dwReserved;
	XYZNumber illuminant_absolute;
	XYZNumber surround_absolute;
	MeasurementStdIlluminat illuminant_type;
};

// 'XYZ'
struct XYZTypeData
{
	DWORD dwReserved;
	XYZNumber arr[(dwTagSize - 8) / sizeof(XYZNumber)];
};

// **********************************************************************************************
enum MediaType : DWORD
{
	DMMEDIA_STANDARD = 1,
	DMMEDIA_TRANSPARENCY,
	DMMEDIA_GLOSSY,
	DMMEDIA_USER = 256
};

enum HalftoneType : DWORD
{
	DMDITHER_NONE = 1,
	DMDITHER_COARSE,
	DMDITHER_FINE,
	DMDITHER_LINEART,
	DMDITHER_ERRORDIFFUSION,
	DMDITHER_RESERVED6,
	DMDITHER_RESERVED7,
	DMDITHER_RESERVED8,
	DMDITHER_RESERVED9,
	DMDITHER_GRAYSCALE,
	DMDITHER_USER = 256
};

struct Tag
{
	DWORD signature;

	switch (signature)
	{
	case chromaticityTag:
		ChromaticityTagData chroma_tag;
		break;
	case colorantOrderTag:
		ColorandOrderTagData colorant_order_tag;
		break;
	case colorantTableTag:
		ColorantTableTagData colorant_table_tag;
		break;
	case 'vruc':
		CurveTypeData curve;
		break;
	case 'atad':
		DatatypeData data;
		break;
	case 'mitd':
		DataTimeData date_time;
		break;
	case '2tfm':
		Lut16TypeData lut16;
		break;
	case '1tfm':
		Lut8TypeData lut8;
		break;
	case measurementTag:
		MeasurementTagData meas;
		break;
	case 'culm':
		MultiLocalizedUnicodeTypeData mluc;
		break;
	case namedColor2Tag:
		NamedColor2TypeData ncl2;
		break;
	case 'arap':
		ParametricCurveType para_curve;
		break;
	case profileSequenceDescTag:
		ProfileSequenceDescTypeData pseq;
		break;
	case '2csr':
		ResponseCurveSet16TypeData rsc2;
		break;
	case '23fs':
		s15Fixed16ArrayType sf32;
		break;
	case 'txet':
		TextTypeData text;
		break;
	case '23fu':
		u16Fixed16ArrayType uf32_arr;
		break;
	case '61iu':
		uInt16ArrayTypeData ui16_arr;
		break;
	case '23iu':
		uInt32ArrayTypeData ui32_arr;
		break;
	case '46iu':
		uInt64ArrayType ui64_arr;
		break;
	case '80iu':
		uInt8ArrayType ui08_arr;
		break;
	case viewingConditionsTag:
		ViewingConditionsTypeData view;
		break;
	case 0x58595a20: // 'XYZ '
		XYZTypeData xyz;
		break;
	case 0x6d414220: // 'mAB '
		LuAtoBTypeData a2b;
		break;
	case 0x6d424120: // 'mBA '
		LuBToATypeData b2a;
		break;
	case 0x73696720: //' gis'
		SignatureTypeData sig;
		break;
	case technologyTag:
		TechnologyTypes technology_type;
		break;
		// version 2:
	case crdInfoTag:
		struct CrdInfo
		{
			DWORD dwReserved;
			DWORD dwCharCount;
			char product_name[dwCharCount];
			DWORD dwRenderIntentCount0;
			char rendering_intent0[dwRenderIntentCount0];

			DWORD dwRenderIntentCount1;
			char rendering_intent1[dwRenderIntentCount1];

			DWORD dwRenderIntentCount2;
			char rendering_intent2[dwRenderIntentCount2];

			DWORD dwRenderIntentCount3;
			char rendering_intent3[dwRenderIntentCount3];
		}info;
		break;
	case deviceSettingsTag:
		struct DeviceSettings
		{
			DWORD dwReserved;
			DWORD dwCount;
			struct PlatformEncoding
			{
				char signature[4];
				DWORD dwSize;
				DWORD dwCount;
				struct Combination
				{
					DWORD dwSize;
					DWORD dwSettingCount;
					struct Setting
					{
						char signature[4];
						DWORD dwSizeOfEachValue;
						DWORD dwValueCount;
						switch (signature)
						{
						case 0x72736C6E: // 'rsln' resolution
							$assert(dwSizeOfEachValue == 8, "Hex Editor is unable to parse file: wrong settings size");
							struct Reolution
							{
								DWORD x, y;
							}resolution[dwValueCount];
							break;
						case 0x6D747970:
							$assert(dwSizeOfEachValue == 4, "Hex Editor is unable to parse file: wrong settings size");
							MediaType media_type[dwValueCount];
							break;
						case 0x6866746E:
							$assert(dwSizeOfEachValue == 4, "Hex Editor is unable to parse file: wrong settings size");
							HalftoneType halftone_type[dwValueCount];
							break;
						default:
							BYTE not_parsed_data[dwValueCount * dwSizeOfEachValue];
						}
					}settings[dwSettingCount];
				}combinations[dwCount];
			}platforms[dwCount];
		}device_settings;
		break;
	case namedColorType:
		struct NamedColorType
		{
			DWORD dwReserved;
			DWORD dwVendorSpecificFlag;
			DWORD dwNamedColorsCount;

			string str_prefix;
			string str_suffix;
			struct NamedColor
			{
				string str_name;
				DataColorSpace color_space;
			}colors[dwNamedColorsCount];
		}named_color_type;
		break;
	case profileDescriptionTag:
		struct DescriptionTag
		{
			DWORD dwReserved;
			DWORD dwDescriptionCount;
			char invariant_description[dwDescriptionCount];
			DWORD dwUnicodeLanguageCode;
			DWORD dwUnicodeDescriptionCount;
			WORD unicode_description[dwUnicodeDescriptionCount];

			WORD wScriptCode;
			BYTE nMacDescCount;
			BYTE max_description[nMacDescCount];
		}description;
		break;
	case ucrbgTag:
		struct Ucrbg
		{
			DWORD dwReserved;
			DWORD dwUCRCount;
			WORD UCRcurve_values[dwCount];
			DWORD dwBGcount;
			WORD BGCurve_values[dwBGcount];
			string string;
		}ucrbg;
		break;
	default:
		BYTE unknown_data[dwTagSize - sizeof(signature)];
	}
};

struct TagTable
{
	DWORD dwTagCount;
	struct TagDescriptor
	{
		TagType signature;
		DWORD tag as Tag *(pStart);
		DWORD dwTagSize;
	}tags[dwTagCount];
};

public struct ICC
{
	var pStart = this;

	ProfileHeader profile_header;
	TagTable tags;
};