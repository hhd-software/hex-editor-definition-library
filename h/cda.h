// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"

#pragma pack(1)
#pragma byte_order(LittleEndian)

union FOURCC
{
	char FourCCs[4];
	DWORD FourCC;
};

struct RedBookFrame
{
	BYTE nFrames;
	BYTE nSeconds;
	BYTE nMinutes;
	BYTE nReserved;
};

// HSG format: time = minute * 4500 + second * 75 + frame
// this headers is located before each track
struct CDAINFORMATION
{
	WORD wVersion;
	WORD wTrackNumber;
	DWORD dwSerialNumber;

	DWORD dwBeginningOfTrackHSG; // in HSG format
	DWORD dwLengthOftrackHSG; // in HSG format

	RedBookFrame dwStartMS;
	$print("Start time value", "Start time= " + dwStartMS.nMinutes + ":" + dwStartMS.nSeconds);

	RedBookFrame dwLengthMS;
	$print("Length of track value", "Length of track= " + dwLengthMS.nMinutes + ":" + dwLengthMS.nSeconds);
};

public struct CDA
{
	FOURCC dwRiff; // FOURCC is defined in stddefs.h which is included from bitmap.h
	$assert(dwRiff.FourCC == 'RIFF', "Not a RIFF file");

	DWORD dwFileSize;
	FOURCC dwFileType;
	$assert(dwFileType.FourCCs == "CDDA", "Not a CDA file");
	DWORD dwReserved;
	DWORD dwEOLn;

	CDAINFORMATION track_information;
};
