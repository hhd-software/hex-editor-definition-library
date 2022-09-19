// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see imgformat-1.0.pdf (not-official)
// NOTE: this format was manually reversed by John Mechalas, so many fields are "reserved" (i.e. unknown)
#include "stddefs.h"

struct IMG_Header
{
	BYTE nXor;
	BYTE reserved[9];

	BYTE nUpdateMonth;
	BYTE nUpdateYear;

	var nRealYear = 1900 + nUpdateYear;
	if (nUpdateYear <= 0x62)
		nRealYear = 2000 + nUpdateYear;
	$print("Year", nRealYear);

	BYTE reserved2[3];
	BYTE nChecksum;

	char signature[7];
	$assert(signature == "DSKIMG", "Hex editor is unable to parse file");

	BYTE reserved3;
	WORD wSectors;
	WORD wHeades;
	WORD wCylinders;

	WORD reserved4;

	BYTE reserved4[25];

	WORD wCreationYear;
	BYTE nCreationMonth;
	BYTE nCreationDay;
	BYTE nCreationHour;
	BYTE nCreationMinute;
	BYTE nCreationSecond;

	BYTE reserved5;

	char map_id[7];
	BYTE reserved6;

	char map_desc[20];
	WORD wHeads2;
	WORD wSectors2;
	BYTE nBlockSizeExponent1;
	BYTE nBlockSizeExponent2;

	// == (0x1A)*(0x18)*(0x1C)/2^(0x62)
	WORD unknown;

	BYTE map_name_continued[31];
	BYTE reserved7[314];
};

struct PartitionTable
{
	BYTE nBoot;
	BYTE nStartHead;
	BYTE nStartSector;
	BYTE nStartCylinder;
	BYTE nSystemType;
	BYTE nEndHead;
	BYTE nEndSector;
	BYTE nEndCylinder;
	DWORD dwRelSectors;
	DWORD dwNumOfSectors;
	BYTE reserved[50];

	BYTE reserved2[512];
	BYTE reserved3;
	BYTE reserved4[11];
	DWORD dwFirstSubfileOffsetAbsolute;
	BYTE reserved5;
	BYTE reserved6[15];
	BYTE block_sequence_number[480];
};

struct FAT_Block
{
	BYTE nTrueDubfile;
	BYTE img_subfile_name[8];
	char subfile_type[3];

	DWORD dwFileSize;
	if (array_index == 0)
	{
		nFileSize = dwFileSize;
	}

	WORD wSubFilePart;
	BYTE reserved[14];
	WORD block_sequences[240];
};

// TRE file
struct TripleByte
{
	BYTE a, b, c;
};

struct MapLevels
{
	if (!bLockedMap)
	{
		BYTE nZoomLevel : 4;
		BYTE unknown : 3;
		BYTE bInherited;
		BYTE nBitsPerCoord;
		WORD wSubdivisions;
	}
};

enum SubdivisionObjectTypes : BYTE
{
	Points = 0x10,
	IndexedPoints = 0x20,
	Polylines = 0x40,
	Polygons = 0x80
};

struct Subdivision
{
	BYTE nRgnSubfileOffset[3];
	SubdivisionObjectTypes type;
	BYTE nLongitudeCenter[3];
	BYTE nLatitudeCenter[3];

	WORD wWidth : 15;
	WORD bTerminatingFlag : 1;

	WORD wHeight;

	// TODO
	//if(!bLowestLevel)
	WORD wNextLevelSubdivision; // 1-based index
};


struct TreFile
{
	TripleByte north_boundary;
	TripleByte east_boundary;
	TripleByte south_boundary;
	TripleByte west_boundary;

	DWORD dwMapLevelsOffset as MapLevels *;
	DWORD dwMapLevelsSize;

	DWORD dwSubdivisionSectionOffset as Subdivision *;
	DWORD dwSubdivisionSectionSize;

	DWORD dwCopyrightSectionOffset;
	DWORD dwCopyrightSectionSize;

	WORD wCopyrightRecordSize;

	DWORD reserved;

	BYTE nPOIDisplayFlags;
	BYTE reserved2[3];
	DWORD reserved3;
	WORD reserved4;
	BYTE reserved5;

	DWORD dwPolylineOverviewSectionOffset;
	DWORD dwPolylineOverviewSectionSize;
	WORD wPolylineRecordsSize;
	WORD reserved6;
	WORD reserved7;

	DWORD dwPolygonOverviewSectionOffset;
	DWORD dwPolygonOverviewSectionSize;
	WORD wPolygonRecordsSize;
	WORD reserved8;
	WORD reserved9;

	DWORD dwPointOverviewSectionOffset;
	DWORD dwPointOverviewSectionSize;
	WORD wPointRecordsSize;
	WORD reserved8;
	WORD reserved9;

	// TODO: p.11
	// if(header size>116)
	DWORD dwMapID; // unknown
	DWORD reserved10;
	DWORD dwTRE7SectionOffset;
	DWORD dwTRE7SectionSize;
	WORD wTRE7RecordsSize;
	DWORD reserved11;
	DWORD dwTRE8SectionOffset;
	DWORD dwTRE8SectionSize;
	DWORD reserved12;
	DWORD reserved13;

	// TODO: 
	// if(header size>154)
	BYTE encryption_key; // ???
	DWORD dwTRE9SectionOffset;
	DWORD dwTRE9SectionSize;
	WORD wTRE9RecordsSize;
	DWORD reserved12;
};

// TODO: forward reading of wRecordSize and dwDefnsSize
struct CountryRecords
{
	if (wRecordSize == 1)
	{
		struct CountryRecord
		{
			BYTE nDataPointer[3];
		}records[dwCountryDefnsLength / wRecordSize];
	}
	else
		BYTE unknown_data[dwCountryDefnsLength];
};

// TODO: forward reading of wRegionRecordSize and dwRegionDefnsSize
struct RegionRecords
{
	if (wRegionRecordSize == 5)
	{
		struct RegionRecord
		{
			WORD wCountryIndex;
			BYTE nDataPointer[3];
		}records[dwRegionDefnsSize / wRegionRecordSize];
	}
	else
		BYTE unknown_data[dwRegionDefnsSize];
};

// forward read
struct CityRecords
{
	if (wCityDefnsRecordSize == 5)
	{
		struct CityRecord
		{
			BYTE nCityDataOffset[3];
			WORD wCityInfo;
		}records[dwCityDefnsSize / wCityDefnsRecordSize];
	}
	else
		BYTE unknown_data[dwCityDefnsSize];
};

enum PoiPropsMask : BYTE
{
	HasStreetNum = 1,
	HasStreet = 2,
	HasCity = 4,
	HasZip = 8,
	HasPhone = 16,
	HasExit = 32,
	HasTidePrediction = 64
};

struct VariableBYTE
{
	BYTE nValue;
	if (nValue & 128)
	{
		// terminator
		$break_array(false);
	}
};

struct VariableLen
{
	BYTE nFirstByte;
	if (!(nFirstByte & 128))
	{
		// 3 byte offset into data
		BYTE nPartOfOffset[2];
	}
	else
	{
		VariableBYTE byte_arr[*];
	}
};

struct PoiProps
{
	BYTE data_ptr : 22;
	BYTE unknown : 1;
	BYTE has_partial_propertirs : 1;

	var nMask = nPOIPropsGlobalMask;
	if (has_partial_propertirs)
	{
		PoiPropsMask property_map;
		nMask = property_map;
	}

	if (nMask & HasStreetNum)
		VariableLen street_num;

	if (nMask & HasStreet)
		BYTE nStreetLblOffset[3];

	if (nMask & HasCity)
		WORD nCity; // WARN: or 1 bytes!!!

	if (nMask & HasZip)
		WORD wZipIndex; // WARN: or 1 byte!

	if (nMask & HasPhone)
		VariableLen phone_num;
};

// p.17
struct LblFile
{
	DWORD dwLbl1DataOffset;
	DWORD dwDataLength;
	BYTE nLabelOffsetMultiplier; // power of 2
	BYTE nLabelCoding;
	DWORD dwCountryDefnsOffset as CountryRecords *;
	DWORD dwCountryDefnsLength;
	WORD wRecordSize;

	DWORD reserved;

	DWORD dwRegionDefnsOffset as RegionRecords *;
	DWORD dwRegionDefnsSize;
	WORD wRegionRecordSize;
	DWORD reserved2;

	DWORD dwCityDefnsOffset as CityRecords *;
	DWORD dwCityDefnsSize;
	WORD wCityDefnsRecordSize;

	DWORD reserved3;

	DWORD dwSection5Offset;
	DWORD dwSection5Size;
	WORD wSection5RecordSize;

	DWORD reserved4;

	// p.23
	DWORD dwPOIPropsOffset as PoiProps *;
	BYTE nPOIPropsMultiplier;
	PoiPropsMask nPOIPropsGlobalMask;

	WORD reserved5;
	BYTE reserved6;

	DWORD dwSection7Offset;
	DWORD dwSection7Size;
	WORD wSection7RecordSize;
	DWORD reserved7;

	DWORD dwZipDefsOffset;
	DWORD dwZipDefsSize;
	WORD wZipDefsRecordSize;
	DWORD reserved8;

	DWORD dwHighwayDefsOffset;
	DWORD dwHighwayDefsSize;
	WORD wHighwayDefRecordSize;
	DWORD reserved9;

	DWORD dwExitDefsOffset;
	DWORD dwExitDefsSize;
	WORD wExitDefRecordSize;
	WORD reserved10;

	DWORD dwHighwayDataDefsOffset;
	DWORD dwHighwayDataDefsSize;
	WORD wHighwayDataRecordSize;
	DWORD reserved11;

	// TODO
	// if(header length>170 bytes)
	DWORD reserved12;
	WORD reserved13;

	DWORD dwSortDescriptorOffset;
	DWORD dwSortDescriptorSize;

	DWORD dwSection13Offset;
	DWORD dwSection13Size;
	WORD wSection13RecordSize;
	WORD reserved14;

	// TODO
	// if(header size>196)
	DWORD dwTidePredictionOffset;
	DWORD dwTidePredictionSize;
	WORD wTidePredicionRecordSize;
	WORD reserved15;
};

// TODO: forward reading
struct RgnData
{
	BYTE unknown_data[dwDataLength];
};

struct RgnFile
{
	DWORD dwDataOffset as RgnData *;
	DWORD dwDataLength;
};

struct NetFile
{
	DWORD dwRoadDefsOffset;
	DWORD dwRoadDefsSize;
	BYTE nRoadDefsOffsetMultiplier;

	DWORD dwSegmentedRoadDefsOffset;
	DWORD dwSegmentedRoadDefsSize;
	BYTE nSegmentedRoadDefsOffsetMultiplier;

	DWORD dwSortedRoadsOffset;
	DWORD dwSortedRoadsSize;
	WORD wSortedRoadsRecordSize;

	DWORD reserved;
	BYTE reserved2;
	BYTE reserved3;

	// TODO
	//if(header size>55)
	DWORD reserved4;

	// TODO
	//if(header size>59)
	DWORD reserved5;
	DWORD reserved6;
};

struct NodFile
{
	DWORD dwSection1Offset;
	DWORD dwSection1Size;
	WORD reserved;
	WORD reserved2;
	WORD reserved3;
	WORD reserved4;

	DWORD dwRoadDataOffset;
	DWORD dwRoadDataSize;
	DWORD reserved5;

	DWORD dwBoundaryNodesOffset;
	DWORD dwBoundaryNodesSize;
	BYTE nBoundaryNodesRecordSize;
	DWORD reserved6;
};

struct CommonSubFileHeader
{
	WORD wHeaderLength;
	char sig[7];
	char type[3];
	BYTE reserved;
	BYTE bLockedMap;
	WORD wCreationYear;
	BYTE nCreationMonth;
	BYTE nCreationDay;
	BYTE nCreationHour;
	BYTE nCreationMinute;
	BYTE nCreationSecond;

	switch (type)
	{
	case "TRE":
		TreFile tre;
		break;
	case "LBL":
		LblFile tbl;
		break;
	case "RGN":
		RgnFile rgn;
		break;
	case "NET":
		NetFile net;
		break;
	case "NOD":
		NodFile nod;
		break;
	}
};

struct SubFile
{
	CommonSubFileHeader header;
};

public struct IMG_File
{
	IMG_Header header;
	PartitionTable partition_table;

	var nFileSize = 0;

	var nFatSize = partition_table.dwFirstSubfileOffsetAbsolute - 0x600; // 0x600 is a start of FAT table
	var nFatBlocks = nFatSize / 512;
	$print("FatSize=", nFatSize);
	$print("FatBlocks=", nFatBlocks);

	FAT_Block blocks[nFatBlocks];
};

// TODO: 0x600 data is missing
