// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
/*
* Note: TIFF file format uses 2 bytes in TIFF_IMAGE_FILE_HEADER as endianness switch
* (i.e. 0x4d4d - Big endian/ 0x4949 - little endian)
* Hex editor NEO is not capable of switching endianness "on the fly", but we use a little trick here:
* we have 2 definitions for each structure - one for Big endian mode (default) and one for Little endian mode
* (LE is appended to the structure name).
*/
#include "stddefs.h"

//#pragma byte_order(BigEndian)

// see p.117 of "TIFF 6.0 Specification"
enum IFD_Tag : USHORT
{
	GPSVersionID = 0, GPSLatitudeRef, GPSLatitude, GPSLongitudeRef, GPSLongitude, GPSAltitudeRef, GPSAltitude, GPSTimeStamp, GPSSatellites, GPSStatus, GPSMeasureMode, GPSDOP, GPSSpeedRef, GPSSpeed, GPSTrackRef, GPSTrack, GPSImgDirectionRef, GPSImgDirection, GPSMapDatum, GPSDestLatitudeRef, GPSDestLatitude, GPSDestLongitudeRef, GPSDestLongitude, GPSDestBearingRef, GPSDestBearing, GPSDestDistanceRef, GPSDestDistance, GPSProcessingMethod, GPSAreaInformation, GPSDateStamp, GPSDifferential,
	NewSubFileType = 254, SubFileType, ImageWidth, ImageLength, BitsPerSample, Compression, PhotometricInterpretation = 262, Thresholding, CellWidth, CellLength, FillOrder,
	DocumentName = 269, ImageDescription, Make, Model, StripOffsets, Orientation, SamplesPerPixel = 277, RowsPerStrip, StripByteCounts, MinSampleValue, MaxSampleValue, XResolution, YResolution, PlanarConfiguration, PageName, XPosition, YPosition, FreeOffsets, FreeByteCounts, GrayResponseUnit, GrayResponseCurve, Group3Options, Group4Options,
	ResolutionUnit = 296, PageNumber, ColorResponseUnit = 300, TransferFunction, Software = 305, DateTime, Artist = 315, HostComputer, Predictor, WhitePoint, PrimaryChromacities, ColorMap, HalftoneHints, TileWidth, TileLength, TileOffsets, TileByteCounts, BadFaxLines, CleanFaxData, ConsecutiveBadFaxLines,
	SubIFDs = 330, InkSet = 332, InkNames, NumberOfInks, DotRange = 336, TargetPrinter, ExtraSamples, SampleFormat, SMinSampleValue, SMaxSampleValue, TransferRange, ClipPath, XClipPathUnits, YClipPathUnits, Indexed, JPEGTables,
	OPIProxy = 351, GlobalParametersIFD = 400, ProfileType, FaxProfile, CodingMethods, VersionYear, ModeNumber, JPEGProc = 512, JPEGInterchangeFormat, JPEGInterchangeFormatLength, JPEGRestartInterval, JPEGLosslessPredictors = 517, JPEGPointTransforms, JPEGQTables, JPEGDCTables, JPEGACTables, YCbCrCoefficients = 529, YCbCrSubsampling, YCbCrPositioning, ReferenceBlackWhite, XMP = 700, ImageID = 32781, Wang_Annotation = 32932, Matteing = 32995, DataType, ImageDepth, TileDepth, CFARepeatPatternDim = 33421, CFAPattern, BatteryLevel,
	Copyright = 33432, ExposureTime = 33434, FNumber = 33437, ModelPixelScaleTag = 33550, IPTC_NAA = 33723, INGR_Packet_Data_Tag = 33918, INGR_Flag_Registers, IntergraphMatrixTag,
	ModelTiepointTag = 33922, Site = 34016, ColorSequence, IT8Header, RasterPadding, BitsPerRunLength, BitsPerExtendedRunLength, ColorTable, ImageColorIndicator, BackgroundColorIndicator, ImageColorValue, BackgroundColorValue, PixelInensityRange, TransparencyIndicator, ColorCharacterization, HCUsage,
	ModelTransformationTag = 34264, PhotoshopImageResources = 34377, ExifIFD = 34665, InterColourProfile = 34675, GeoKeyDirectoryTag = 34735, GeoDoubleParamsTag, GeoAsciiParamsTag, ExposureProgram = 34850,
	SpectralSensitibity = 34852, GPSInfo, ISOSpeedRatings = 34855, OECF, Interlace, TimeZoneOffset, SelfTimerMode, FaxRecvParams = 34908, FaxSubAddress, FaxRecvTime, ExifVersion = 36864, DateTimeOriginal = 36867, DateTimeDigitized,
	ComponentsConfiguration = 37121, CompressedBitsPerPixel, ShutterSpeedValue = 37377, ApertureValue, BrightnessValue, ExposureBiasValue, MaxApertureValue, SubjectDistance, MeteringMode, LightSource, Flash, FocalLength, FlashEnergy, SpatialFrequencyResponse, Noise, FocalPlaneXResolution, FocalPlaneYResolution, FocalPlaneResolutionUnit, ImageNumber, SecurityClassification, ImageHistory, SubjectArea, ExposureIndex, TIFF_EPStandardID, SensingMethod,
	StoNits = 37439, MakerNote = 37500, UserComment = 37510, SubSecTime = 37520, SubSecTimeOriginal, SubSecTimeDigitized, ImageSourceData = 37724, MSFax_CSID = 40001, MSFax_TSID, MSFax_Device, MSFax_RoutingInfo, MSFax_CallerID, MSFax_RecipientName, MSFax_RecipientFaxNumber, MSFax_RecipientCompany, MSFax_RecipientAddress, MSFax_RecipientStreet, MSFax_RecipientCity, MSFax_RecipientZipCode, MSFax_RecipientCountry, MSFax_RecipientTitle, MSFax_RecipientDepartment, MSFax_RecipientOffice, MSFax_RecipientOfficePhone,
	MSFax_RecipientHomePhone, MSFax_Recipient40019, MSFax_RecipientEmail, MSFax_SenderName, MSFax_SenderFaxNumber, MSFax_SenderCompany, MSFax_SenderAddress, MSFax_SenderStreet, MSFax_SenderCity, MSFax_SenderZipCode, MSFax_SenderCountry, MSFax_SenderTitle, MSFax_SenderDepartment, MSFax_SenderOffice, MSFax_SenderOfficePhone, MSFax_SenderHomePhone, MSFax_Sender40034, MSFax_SenderEmail, MSFax_BillingCode, MSFax_UserName, MSFax_40038, MSFax_Document, MSFax_CoverPageSubject, MSFax_Retries, MSFax_Priority,
	MSFax_ParentJobID, MSFax_SubmissionTime, MSFax_Scheduled, MSFax_TotalPages, MSFax_Type, MSFax_40048, MSFax_ErrorCode, MSFax_40050, MSFax_StartTime, MSFax_EndTime, MSFax_40053,
	FlashpixVersion = 40960, ColorSpace, PixelXDimension, PixelYDimension, RelatedSoundFile, InteroperabilityIFD, FlashEnergy_Exif = 41483, SpatialFrequencyResponse_Exif,
	FocalPlaneXResolution_Exif = 41486, FocalPlaneYResolution_Exif, FocalPlaneResolutionUnit_Exif, SubjectLocation_Exif = 41492, ExposureIndex_Exif,
	SensingMethod_Exif = 41495, FileSource = 41728, SceneType, CFAPattern_Exif, CustomRendered = 41985, ExposureMode, WhiteBalance, DigitalZoomRatio, FocalLengthIn35mmFilm, SceneCaptureType, GainControl, Contrast, Saturation, Sharpness, DeviceSettingDescription, SubjectDistanceRange,
	GDAL_METADATA = 42112, GDAL_NODATA, Oce_Scanjob_Description = 50215, Oce_Application_Selector, Oce_Identification_Number, Oce_ImageLogic_Characteristics,
	PhotoshopAnnotations = 50255, DNGVersion = 50706, DNGBackwardVersion, UniqueCameraModel, LocalizedCameraModel, CFAPlaneColor, CFALayout, LinearizationTable, BlackLevelRepeatDim, BlackLevel, BlackLevelDeltaH, BlackLevelDeltaV, WhiteLevel, DefaultScale, DefaultCropOrigin, DefaultCropSize, ColorMatrix1, ColorMatrix2, CameraCalibration1, CameraCalibration2, ReductionMatrix1, ReductionMatrix2, AnalogBalnace, AsShortNeutral, AsShortWhiteXY, BaselineExposure, BaselineNoise, BaselineSharpness, BayerGreenSplit,
	LinearResponseLimit, CameraSerialNumber, LensInfo, ChromaBlurRadius, AntiAliasStrength, DNGPrivateDatea = 50740, MakerNoteSafety, CalibrationIlluminant1 = 50778, CalibrationIlluminant2, BestQualityScale, Alias_Layer_Metadata = 50784
};

enum IFD_EntryType : USHORT
{
	etBYTE = 1,
	etASCII,
	etSHORT,
	etLONG,
	etRATIONAL,

	// TIFF 6.0:
	etSBYTE,
	etUNDEF,
	etSSHORT,
	etSLONG,
	etSRATIONAL,
	etFLOAT,
	etDOUBLE
};

struct RATIONAL
{
	LONG dwNumerator;
	LONG dwDenominator;
};

struct URATIONAL
{
	ULONG dwNumerator;
	ULONG	dwDenominator;
};

struct ByteArray
{
	BYTE arr[dwCount];
};

struct CharArray
{
	char arr[dwCount];
};

struct UshortArray
{
	USHORT arr[dwCount];
};

struct UlongArray
{
	ULONG arr[dwCount];
};

struct UrationalArray
{
	URATIONAL arr[dwCount];
};

struct ShortArray
{
	SHORT arr[dwCount];
};

struct LongArray
{
	LONG arr[dwCount];
};

struct RationalArray
{
	RATIONAL arr[dwCount];
};

struct FloatArray
{
	FLOAT arr[dwCount];
};

struct DoubleArray
{
	DOUBLE arr[dwCount];
};

// generic
struct TIFF_IMAGE_FILE_DIRECTORY_ENTRY
{
	IFD_Tag wTag;
	IFD_EntryType wType;
	ULONG dwCount;

	if (wTag == ExifIFD && dwCount == 4)		// special tag parsing
	{
		// new directory also!
		ULONG exif_ifd as TIFF_IMAGE_FILE_DIRECTORY_ENTRY *(nBeginning);
	}
	else
	{
		switch (wType)
		{
		case etBYTE:
		case etUNDEF:
			if (dwCount <= 4)
			{
				BYTE dwValue[dwCount];
				BYTE unused[4 - dwCount];
			}
			else
			{
				// pointer
				ULONG value as ByteArray *(nBeginning);
			}
			break;
		case etASCII:
		case etSBYTE:
			if (dwCount <= 4)
			{
				char chValue[dwCount];
				BYTE unused[4 - dwCount];
			}
			else
			{
				// pointer
				ULONG value as CharArray *(nBeginning);
			}
			break;
		case etSHORT:
			if (dwCount <= 2)
			{
				USHORT shValue[dwCount];
				BYTE unused[4 - (dwCount * 2)];
			}
			else
			{
				// pointer
				ULONG value as UshortArray *(nBeginning);
			}
			break;
		case etLONG:
			if (dwCount <= 1)
			{
				ULONG lValue[dwCount];
				BYTE unused[4 - (dwCount * 4)];
			}
			else
			{
				// pointer
				ULONG value as UlongArray *(nBeginning);
			}
			break;
		case etRATIONAL:
			// only pointer
			ULONG value as UrationalArray *(nBeginning);
			break;
		case etSSHORT:
			if (dwCount <= 2)
			{
				SHORT shValue[dwCount];
				BYTE unused[4 - (dwCount * 2)];
			}
			else
			{
				// pointer
				ULONG value as ShortArray *(nBeginning);
			}
			break;
		case etSLONG:
			if (dwCount <= 1)
			{
				LONG lValue[dwCount];
				BYTE unused[4 - (dwCount * 4)];
			}
			else
			{
				// pointer
				ULONG value as LongArray *(nBeginning);
			}
			break;
		case etSRATIONAL:
			ULONG value as RationalArray *(nBeginning);
			break;
		case etFLOAT:
			ULONG value as FloatArray *(nBeginning);
			break;
		case etDOUBLE:
			ULONG value as DoubleArray *(nBeginning);
			break;
		}
	}
};

// IFD
struct TIFF_IMAGE_FILE_DIRECTORY
{
	WORD nIFDEntriesNumber;
	TIFF_IMAGE_FILE_DIRECTORY_ENTRY ifd_entries[nIFDEntriesNumber];
	ULONG next_ifd_ptr;
	if(next_ifd_ptr != 0)
	{
		$remove_to(ref(next_ifd_ptr));
		ULONG next_ifd as TIFF_IMAGE_FILE_DIRECTORY *(nBeginning);
	}
};


// LITTLE endian (copy of structures, but with different names)
//#pragma byte_order(LittleEndian)
enum IFD_TagLE : USHORT
{
	GPSVersionID = 0, GPSLatitudeRef, GPSLatitude, GPSLongitudeRef, GPSLongitude, GPSAltitudeRef, GPSAltitude, GPSTimeStamp, GPSSatellites, GPSStatus, GPSMeasureMode, GPSDOP, GPSSpeedRef, GPSSpeed, GPSTrackRef, GPSTrack, GPSImgDirectionRef, GPSImgDirection, GPSMapDatum, GPSDestLatitudeRef, GPSDestLatitude, GPSDestLongitudeRef, GPSDestLongitude, GPSDestBearingRef, GPSDestBearing, GPSDestDistanceRef, GPSDestDistance, GPSProcessingMethod, GPSAreaInformation, GPSDateStamp, GPSDifferential,
	NewSubFileType = 254, SubFileType, ImageWidth, ImageLength, BitsPerSample, Compression, PhotometricInterpretation = 262, Thresholding, CellWidth, CellLength, FillOrder,
	DocumentName = 269, ImageDescription, Make, Model, StripOffsets, Orientation, SamplesPerPixel = 277, RowsPerStrip, StripByteCounts, MinSampleValue, MaxSampleValue, XResolution, YResolution, PlanarConfiguration, PageName, XPosition, YPosition, FreeOffsets, FreeByteCounts, GrayResponseUnit, GrayResponseCurve, Group3Options, Group4Options,
	ResolutionUnit = 296, PageNumber, ColorResponseUnit = 300, TransferFunction, Software = 305, DateTime, Artist = 315, HostComputer, Predictor, WhitePoint, PrimaryChromacities, ColorMap, HalftoneHints, TileWidth, TileLength, TileOffsets, TileByteCounts, BadFaxLines, CleanFaxData, ConsecutiveBadFaxLines,
	SubIFDs = 330, InkSet = 332, InkNames, NumberOfInks, DotRange = 336, TargetPrinter, ExtraSamples, SampleFormat, SMinSampleValue, SMaxSampleValue, TransferRange, ClipPath, XClipPathUnits, YClipPathUnits, Indexed, JPEGTables,
	OPIProxy = 351, GlobalParametersIFD = 400, ProfileType, FaxProfile, CodingMethods, VersionYear, ModeNumber, JPEGProc = 512, JPEGInterchangeFormat, JPEGInterchangeFormatLength, JPEGRestartInterval, JPEGLosslessPredictors = 517, JPEGPointTransforms, JPEGQTables, JPEGDCTables, JPEGACTables, YCbCrCoefficients = 529, YCbCrSubsampling, YCbCrPositioning, ReferenceBlackWhite, XMP = 700, ImageID = 32781, Wang_Annotation = 32932, Matteing = 32995, DataType, ImageDepth, TileDepth, CFARepeatPatternDim = 33421, CFAPattern, BatteryLevel,
	Copyright = 33432, ExposureTime = 33434, FNumber = 33437, ModelPixelScaleTag = 33550, IPTC_NAA = 33723, INGR_Packet_Data_Tag = 33918, INGR_Flag_Registers, IntergraphMatrixTag,
	ModelTiepointTag = 33922, Site = 34016, ColorSequence, IT8Header, RasterPadding, BitsPerRunLength, BitsPerExtendedRunLength, ColorTable, ImageColorIndicator, BackgroundColorIndicator, ImageColorValue, BackgroundColorValue, PixelInensityRange, TransparencyIndicator, ColorCharacterization, HCUsage,
	ModelTransformationTag = 34264, PhotoshopImageResources = 34377, ExifIFD = 34665, InterColourProfile = 34675, GeoKeyDirectoryTag = 34735, GeoDoubleParamsTag, GeoAsciiParamsTag, ExposureProgram = 34850,
	SpectralSensitibity = 34852, GPSInfo, ISOSpeedRatings = 34855, OECF, Interlace, TimeZoneOffset, SelfTimerMode, FaxRecvParams = 34908, FaxSubAddress, FaxRecvTime, ExifVersion = 36864, DateTimeOriginal = 36867, DateTimeDigitized,
	ComponentsConfiguration = 37121, CompressedBitsPerPixel, ShutterSpeedValue = 37377, ApertureValue, BrightnessValue, ExposureBiasValue, MaxApertureValue, SubjectDistance, MeteringMode, LightSource, Flash, FocalLength, FlashEnergy, SpatialFrequencyResponse, Noise, FocalPlaneXResolution, FocalPlaneYResolution, FocalPlaneResolutionUnit, ImageNumber, SecurityClassification, ImageHistory, SubjectArea, ExposureIndex, TIFF_EPStandardID, SensingMethod,
	StoNits = 37439, MakerNote = 37500, UserComment = 37510, SubSecTime = 37520, SubSecTimeOriginal, SubSecTimeDigitized, ImageSourceData = 37724, MSFax_CSID = 40001, MSFax_TSID, MSFax_Device, MSFax_RoutingInfo, MSFax_CallerID, MSFax_RecipientName, MSFax_RecipientFaxNumber, MSFax_RecipientCompany, MSFax_RecipientAddress, MSFax_RecipientStreet, MSFax_RecipientCity, MSFax_RecipientZipCode, MSFax_RecipientCountry, MSFax_RecipientTitle, MSFax_RecipientDepartment, MSFax_RecipientOffice, MSFax_RecipientOfficePhone,
	MSFax_RecipientHomePhone, MSFax_Recipient40019, MSFax_RecipientEmail, MSFax_SenderName, MSFax_SenderFaxNumber, MSFax_SenderCompany, MSFax_SenderAddress, MSFax_SenderStreet, MSFax_SenderCity, MSFax_SenderZipCode, MSFax_SenderCountry, MSFax_SenderTitle, MSFax_SenderDepartment, MSFax_SenderOffice, MSFax_SenderOfficePhone, MSFax_SenderHomePhone, MSFax_Sender40034, MSFax_SenderEmail, MSFax_BillingCode, MSFax_UserName, MSFax_40038, MSFax_Document, MSFax_CoverPageSubject, MSFax_Retries, MSFax_Priority,
	MSFax_ParentJobID, MSFax_SubmissionTime, MSFax_Scheduled, MSFax_TotalPages, MSFax_Type, MSFax_40048, MSFax_ErrorCode, MSFax_40050, MSFax_StartTime, MSFax_EndTime, MSFax_40053,
	FlashpixVersion = 40960, ColorSpace, PixelXDimension, PixelYDimension, RelatedSoundFile, InteroperabilityIFD, FlashEnergy_Exif = 41483, SpatialFrequencyResponse_Exif,
	FocalPlaneXResolution_Exif = 41486, FocalPlaneYResolution_Exif, FocalPlaneResolutionUnit_Exif, SubjectLocation_Exif = 41492, ExposureIndex_Exif,
	SensingMethod_Exif = 41495, FileSource = 41728, SceneType, CFAPattern_Exif, CustomRendered = 41985, ExposureMode, WhiteBalance, DigitalZoomRatio, FocalLengthIn35mmFilm, SceneCaptureType, GainControl, Contrast, Saturation, Sharpness, DeviceSettingDescription, SubjectDistanceRange,
	GDAL_METADATA = 42112, GDAL_NODATA, Oce_Scanjob_Description = 50215, Oce_Application_Selector, Oce_Identification_Number, Oce_ImageLogic_Characteristics,
	PhotoshopAnnotations = 50255, DNGVersion = 50706, DNGBackwardVersion, UniqueCameraModel, LocalizedCameraModel, CFAPlaneColor, CFALayout, LinearizationTable, BlackLevelRepeatDim, BlackLevel, BlackLevelDeltaH, BlackLevelDeltaV, WhiteLevel, DefaultScale, DefaultCropOrigin, DefaultCropSize, ColorMatrix1, ColorMatrix2, CameraCalibration1, CameraCalibration2, ReductionMatrix1, ReductionMatrix2, AnalogBalnace, AsShortNeutral, AsShortWhiteXY, BaselineExposure, BaselineNoise, BaselineSharpness, BayerGreenSplit,
	LinearResponseLimit, CameraSerialNumber, LensInfo, ChromaBlurRadius, AntiAliasStrength, DNGPrivateDatea = 50740, MakerNoteSafety, CalibrationIlluminant1 = 50778, CalibrationIlluminant2, BestQualityScale, Alias_Layer_Metadata = 50784
};

enum IFD_EntryTypeLE : USHORT
{
	etBYTE = 1,
	etASCII,
	etSHORT,
	etLONG,
	etRATIONAL,

	// TIFF 6.0:
	etSBYTE,
	etUNDEF,
	etSSHORT,
	etSLONG,
	etSRATIONAL,
	etFLOAT,
	etDOUBLE
};

struct RATIONAL_LE
{
	LONG dwNumerator;
	LONG dwDenominator;
};

struct URATIONAL_LE
{
	ULONG dwNumerator;
	ULONG dwDenominator;
};

struct ByteArrayLE
{
	BYTE arr[dwCount];
};

struct CharArrayLE
{
	char arr[dwCount];
};

struct UshortArrayLE
{
	USHORT arr[dwCount];
};

struct UlongArrayLE
{
	ULONG arr[dwCount];
};

struct UrationalArrayLE
{
	URATIONAL arr[dwCount];
};

struct ShortArrayLE
{
	SHORT arr[dwCount];
};

struct LongArrayLE
{
	LONG arr[dwCount];
};

struct RationalArrayLE
{
	RATIONAL arr[dwCount];
};

struct FloatArrayLE
{
	FLOAT arr[dwCount];
};

struct DoubleArrayLE
{
	DOUBLE arr[dwCount];
};

// generic
struct TIFF_IMAGE_FILE_DIRECTORY_ENTRY_LE
{
	IFD_TagLE wTag;
	IFD_EntryTypeLE wType;
	ULONG dwCount;

	if (wTag == ExifIFD && dwCount == 4)		// special tag parsing
	{
		// new directory also!
		ULONG exif_ifd as TIFF_IMAGE_FILE_DIRECTORY_ENTRY_LE *(nBeginning);
	}
	else
	{
		switch (wType)
		{
		case etBYTE:
		case etUNDEF:
			if (dwCount <= 4)
			{
				BYTE	 dwValue[dwCount];
				BYTE	 unused[4 - dwCount];
			}
			else
			{
				// pointer
				ULONG value as ByteArrayLE *(nBeginning);
			}
			break;
		case etASCII:
		case etSBYTE:
			if (dwCount <= 4)
			{
				char chValue[dwCount];
				BYTE unused[4 - dwCount];
			}
			else
			{
				// pointer
				ULONG value as CharArrayLE *(nBeginning);
			}
			break;
		case etSHORT:
			if (dwCount <= 2)
			{
				USHORT shValue[dwCount];
				BYTE unused[4 - (dwCount * 2)];
			}
			else
			{
				// pointer
				ULONG value as UshortArrayLE *(nBeginning);
			}
			break;
		case etLONG:
			if (dwCount <= 1)
			{
				ULONG lValue[dwCount];
				BYTE unused[4 - (dwCount * 4)];
			}
			else
			{
				// pointer
				ULONG value as UlongArrayLE *(nBeginning);
			}
			break;
		case etRATIONAL:
			// only pointer
			ULONG value as UrationalArrayLE *(nBeginning);
			break;
		case etSSHORT:
			if (dwCount <= 2)
			{
				SHORT shValue[dwCount];
				BYTE unused[4 - (dwCount * 2)];
			}
			else
			{
				// pointer
				ULONG value as ShortArrayLE *(nBeginning);
			}
			break;
		case etSLONG:
			if (dwCount <= 1)
			{
				LONG lValue[dwCount];
				BYTE unused[4 - (dwCount * 4)];
			}
			else
			{
				// pointer
				ULONG value as LongArrayLE *(nBeginning);
			}
			break;
		case etSRATIONAL:
			ULONG value as RationalArrayLE *(nBeginning);
			break;
		case etFLOAT:
			ULONG value as FloatArrayLE *(nBeginning);
			break;
		case etDOUBLE:
			ULONG value as DoubleArrayLE *(nBeginning);
			break;
		}
	}
};

// IFD
struct TIFF_IMAGE_FILE_DIRECTORY_LE
{
#pragma byte_order(LittleEndian)
	if (current_offset != nBeginning)
	{
		WORD nIFDEntriesNumber;
		TIFF_IMAGE_FILE_DIRECTORY_ENTRY_LE ifd_entries[nIFDEntriesNumber];
		ULONG next_ifd as TIFF_IMAGE_FILE_DIRECTORY_LE *(nBeginning);
		//DWORD								next_ifd;
	}
#pragma byte_order(BigEndian)
};

struct TIFF_IMAGE_FILE_HEADER_CONT_LE
{
#pragma byte_order(LittleEndian)
	// little endian
	USHORT wTiffTag;
	$assert(wTiffTag == 0x2A, "Invalid TIFF file");
	ULONG	ifd as TIFF_IMAGE_FILE_DIRECTORY_LE *(nBeginning);
#pragma byte_order(BigEndian)
};

struct TIFF_IMAGE_FILE_HEADER_CONT
{
	if (current_offset != nBeginning)
	{
		USHORT wTiffTag;
		$assert(wTiffTag == 0x2A, "Invalid TIFF file");
		ULONG ifd as TIFF_IMAGE_FILE_DIRECTORY *(nBeginning);
	}
};

struct TIFF_IMAGE_FILE_HEADER
{
	var nBeginning = current_offset;
	BYTE	nByteOrder[2];

	// fork for endianness
	if (nByteOrder[0] == 0x49 && nByteOrder[1] == 0x49)
		TIFF_IMAGE_FILE_HEADER_CONT_LE header_continued;
	else
		TIFF_IMAGE_FILE_HEADER_CONT header_continued;
};

public struct TiffFile
{
	TIFF_IMAGE_FILE_HEADER ifh;
};
