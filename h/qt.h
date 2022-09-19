// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see "QuickTime File Format Specification (2007-09-04)"
#include "stddefs.h"
#pragma script("get_doc_size.js")

#pragma byte_order(BigEndian)

// forward declaration
struct Atom;
struct AtomList;
struct QT_AtomContainer;

struct Rect
{
	WORD l, t, r, b;
};

struct Color3
{
	WORD r, g, b;
};

struct Color4
{
	WORD a, r, g, b;
};

struct PascalString
{
	BYTE nStringLength;	// TODO: data type ???
	char str[nStringLength];
};

struct Ftyp
{
	DWORD dwMajorBrand;
	DWORD dwMinorVersion;

	var nSizeLeft = nAtomSize - (current_offset - this);
	DWORD dwCompatibleBrands[nSizeLeft / 4];
};

struct PreviewAtom
{
	DWORD dwModificationDate;
	WORD  wVersionNumber;
	DWORD dwAtomType;
	WORD  wAtomIndex;
};

// 36 bytes
struct Matrix
{
	DWORD a, b, u,
		c, d, v,
		x, y, w;
};

struct MovieHeader
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwCreationTime;
	DWORD dwModificationTime;
	DWORD dwTimeScale;
	DWORD dwDuration;
	DWORD dwPreferredRate;
	WORD  wPreferredVolume;

	BYTE reserved[10];

	Matrix matrix;

	DWORD dwPreviewTime;
	DWORD dwPreviewDuration;
	DWORD dwPosterTime;
	DWORD dwSelectionTime;
	DWORD dwSelectionDuration;
	DWORD dwCurrentTime;
	DWORD dwNextTrackID;
};

struct ColorTable
{
	DWORD dwColorTableSeed;
	WORD wColorTableFlags;
	WORD wColorTableSize;

	Color4 colors[wColorTableSize + 1];	// This is a zero-relative
										// value; setting this field to 0 means that there is one color in the array.
};

struct TrackHeader
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwCreationTime;
	DWORD dwModificationTime;
	DWORD dwTrackID;
	DWORD dwReserved;
	DWORD dwDuration;
	BYTE  reserved[8];
	WORD wLayer;
	WORD wAlternateGroup;
	WORD wVolume;
	WORD wReserved;
	Matrix matrix;
	DWORD dwTrackWith;
	DWORD dwTrackHeight;
};

struct ClipRegionHeader
{
	WORD wRegionSize;
	BYTE rcRegionBound[4];
	BYTE data[wRegionSize - 4];
};

struct TrackMatte
{
	BYTE nVersion;
	BYTE nFlags[3];
	Atom sample_desc;
};

struct Edit
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	struct EditListEntry
	{
		DWORD dwTrackDuration;
		DWORD dwMediaTime;
		DWORD dwMediaRate;
	}entries[dwEntries];
};

struct SampleDesc
{
	DWORD dwSampleSize;
	DWORD dwSampleType;
	BYTE  reserved[6];
	WORD  wDataReference;

	switch (dwSampleType)
	{
		// TODO: p.95
	// "rtp "
	case 0x20707472:		// p.164
		WORD  wHintTrackVersion;
		WORD  wLastCompatibleHintTrackVersion;
		DWORD dwMaxPacketSize;
		Atom  atoms;		// TODO: multiple!!!
		break;
	case 0x20776172:		// 'raw ':
	case 'sowt':			// p.114
		WORD wVersion;
		WORD wRevision;
		DWORD dwVendor;
		WORD  wNumberOfChannels;
		WORD  wSampleSize;
		WORD  wCompressionID;
		WORD  wPacketSize;
		DWORD dwSampleRate;
		if (wVersion == 1)
		{
			// added in QT3
			DWORD dwSamplesPerSecond;
			DWORD dwBytesPerPacket;
			DWORD dwBytesPerFrame;
			DWORD dwBytesPerSample;

			// TODO: size is unknown. test it and set proper size
			// AtomList additional_atoms;
		}
		break;
		// TODO: check
	case 'txet':
		// TODO: implement text data desc. p.125
		DWORD dwFlags;
		DWORD dwTextJustification;
		Color3 background_color;
		Rect   default_text_box;
		QWORD  reserved;
		WORD   wFontNumber;
		WORD   wFontFace;
		BYTE   reserved2;
		WORD   reserved3;
		Color3  fore_color;
		PascalString text_name;
		break;
	case 'htxt':	// p.126

		break;
	case 'isum':
		DWORD dwAdditional;
		break;
	case 'trps':
		// sprite 
		QT_AtomContainer sprite_container;
		break;
	}

	BYTE not_parsed_data[dwSampleSize - (current_offset - this)];
};

struct SampleDescription
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	SampleDesc descriptions[dwEntries];
};

// TODO: connect!!!
// TODO: test! 
// media description
struct VideoSampleDesc		// p.96
{
	DWORD dwSampleSize;
	DWORD dwSampleType;
	BYTE  reserved[6];
	WORD  wDataReference;

	// added
	WORD wVersion;
	WORD wRevisionLevel;
	DWORD dwVendor;					// offten contains "appl"
	DWORD dwTempQuality;
	DWORD dwSpatialQuality;
	WORD wWidth;
	WORD wHeight;
	DWORD dwHorResolution;
	DWORD dwVertResolution;
	DWORD dwDataSize;
	WORD wFrameCount;
	DWORD dwCompressorName;
	WORD wDepth;
	WORD wColorTableID;

	if (wColorTableID == 0)
		Atom color_table;

	nAtomSize = nAtomSize - (current_offset - this);
	AtomList additional_extensions;
};


struct TrackLoadSettings
{
	DWORD dwPreloadStartTime;
	DWORD dwPreloadDuration;
	DWORD dwPreloadFlags;
	DWORD dwDefaultHints;
};

struct TrackReference
{
	DWORD dwTrackIds[nAtomSize / sizeof(DWORD)];
};

struct TrackInput
{
	DWORD dwAtomID;
	WORD wReserved;
	WORD wChildCount;
	DWORD dwReserved;

	if (wChildCount >= 1)
	{
		Atom input_type;
		if (wChildCount >= 2)
			Atom object_id;
	}
};

enum InputTypeEnum : DWORD
{
	kTrackModifierTypeMatrix = 1,
	kTrackModifierTypeClip,
	kTrackModifierTypeVolume,
	kTrackModifierTypeBalance,
	kTrackModifierTypeGraphicsMode,
	kTrackModifierObjectMatrix,
	kTrackModifierObjectGraphicsMode,
	kTrackModifierTypeImage = 0x76696465
};

struct InputType
{
	InputTypeEnum dwInputType;
};

struct AtomInList
{
	if (nListSize <= 0)
		$break_array(false);

	Atom atom;
	nListSize = nListSize - (current_offset - this);
};

struct AtomList
{
	var nListSize = nAtomSize;
	[noindex] AtomInList list[*];
};

struct MediaHeader
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwCreationTime;
	DWORD dwModificationTime;
	DWORD dwTimeScale;
	DWORD dwDuration;
	WORD wLanguage;
	WORD wQuality;
};

struct HandlerReference
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwComponentType;
	DWORD dwComponentSubtype;
	DWORD dwComponentManufacturer;
	DWORD dwComponentFlags;
	DWORD dwComponentFlagsMask;
	BYTE  strComponentName[nAtomSize - (current_offset - this)];
};

struct VideoMediaInformation
{
	BYTE nVersion;
	BYTE nFlags[3];
	WORD wGraphicsMode;
	Color3 opcolor;
};

struct SoundMediaInformation
{
	BYTE nVersion;
	BYTE nFlags[3];
	WORD wBalance;
	WORD wReserved;
};

struct BaseMediaInfo
{
	BYTE nVersion;
	BYTE nFlags[3];
	WORD wGraphicsMode;
	Color3 opcolor;
	WORD wBalance;
	WORD wReserved;
};

struct DataReference
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	Atom entries[dwEntries];
};

struct TimeToSample
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	DWORD entries[dwEntries];		// ??? see p.79! unknown data type here
};

struct SyncSample
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	struct Entry
	{
		DWORD dwSampleCount;
		DWORD dwSampleDuration;
	}entries[dwEntries];
};

struct SampleToChunk
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwEntries;
	struct Entry
	{
		DWORD dwFirstChunk;
		DWORD dwSamplesPerChunk;
		DWORD dwSampleDescID;
	}entries[dwEntries];
};

struct SampleSize
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwSampleSize;
	DWORD dwEntries;
	DWORD sizes[dwEntries];
};

struct ChunkOffset
{
	BYTE nVersion;
	BYTE nFlags[3];
	DWORD dwSampleSize;
	DWORD dwEntries;
	DWORD offsets[dwEntries];
};

struct DataReferenceChunk
{
	BYTE nVersion;
	BYTE nFlags[3];
	Atom child;
};

struct DataRate
{
	DWORD dwFlags;
	DWORD dwDataRateInBitsPerSecond;
};

struct CpuSpeed
{
	DWORD dwFlags;
	DWORD dwRelativeCPURanking;
};

struct VersionCheck
{
	DWORD dwFlags;
	DWORD dwSoftwarePackage;
	DWORD dwVersion;
	DWORD dwMask;
	WORD wCheckType;
};

struct ComponentDescription
{
	DWORD dwComponentType;
	DWORD dwComponentSubType;
	DWORD dwComponentManufacturer;
	DWORD dwComponentFlags;
	DWORD dwComponentFlagsMask;
};

struct ComponentDetect
{
	DWORD dwFlags;
	ComponentDescription description;
	DWORD dwMinimumVersion;
};

struct Quality
{
	DWORD dwQuality;
};

struct PixelAspectRation
{
	DWORD dwHorSpacing;
	DWORD dwVertSpacing;
};

struct StreamDesc
{
	BYTE nVersion;
	BYTE nFlags[3];
	// elementary stream description
};

struct Color
{
	DWORD dwColorParam;
	WORD wPrimariesIndex;
	WORD wTransferFunctionIndex;
	WORD wMatrixIndex;
};

struct CleanAperture
{
	DWORD dwApertureWidthNumerator;
	DWORD dwApertureWidthDenominator;

	DWORD dwApertureHeightNumerator;
	DWORD dwApertureHeightDenominator;

	DWORD dwHorOffsetNumerator;
	DWORD dwHorOffsetDenomerator;

	DWORD dwVertOffsetNumerator;
	DWORD dwVertOffsetDenomerator;
};

enum TextFaceEnum : WORD
{
	Bold = 1,
	Italic = 2,
	Underline = 4,
	Outline = 8,
	Shadow = 16,
	Condense = 32,
	Extend = 64
};

struct TimecodeMedia
{
	BYTE nVersion;
	BYTE nFlags[3];
	WORD wTextFont;
	TextFaceEnum text_face;
	WORD wTextSize;
	Color3 text_color;
	Color3 back_color;
	PascalString font_name;
};

public struct Atom
{
	DWORD dwAtomSize;
	DWORD dwType;

	var nAtomSize = dwAtomSize - (current_offset - this);
	if (dwAtomSize == 1)
	{
		QWORD qwRealSize;
		nAtomSize = qwRealSize - (current_offset - this);
	}

	switch (dwType)
	{
	case 'evaw':					// p.117
	case 'pami':
	case 'fert':
	case 'stde':
	case 'ttam':
	case 'pilc':
	case 'atdu':
	case 'fnid':
		//var nSave = nAtomSize;
		//Atom child;				// nested atom (1)
		//nAtomSize = nSave;
		//break;
	case 'voom':
	case 'kart':
	case 'aidm':
	case 'fnim':
	case 'lbts':				// p.74
	case 'armr':				// p.88
	case 'admr':
		var nSave = nAtomSize;
		AtomList atom_list;		// nested atoms (multiple)
		nAtomSize = nSave;
		break;
		// atom
	case 'pytf':
		Ftyp ftyp;
		break;
	case 'tonp':
		PreviewAtom preview;
		break;
		// movie types:
	case 'dhvm':
		// p.39
		MovieHeader movie_header;
		break;
	case 'batc':
		ColorTable color_table;
		break;
	case 'dhkt':
		TrackHeader track_header;
		break;
	case 'ngrc':
		ClipRegionHeader clip_header;
		break;
	case 'tamk':
		TrackMatte track_matte;
		break;
	case 'dsts':
		SampleDescription sample_desc;
		break;
	case 'tsle':
		Edit edit;
		break;
	case 'daol':
		TrackLoadSettings track_load;
		break;
	case 'dcmt':
	case 'cnys':
	case 'tpcs':
	case 'crss':
	case 'tnih':
		TrackReference track_ref;
		break;
	case 0x20766460:
		struct PrintToVideo
		{
			WORD wDisplaySize;
			WORD wReserved1;
			WORD wReserved2;
			BYTE bSlideshow;
			BYTE bPlayOnOpen;
		}print_to_video;
		break;
		// '  in'
	case 0x6e692020:
		TrackInput track_input;
		break;
		// '  ty'
	case 0x79742020:
		InputType user_type;
		break;
		// media atoms
	case 'dhdm':
		MediaHeader media_header;
		break;
	case 'rldh':
		HandlerReference handler_ref;
		break;
	case 'dhmv':
		VideoMediaInformation video_media_info;
		break;
	case 'dhms':
		SoundMediaInformation sound_media_info;
		break;
	case 'nimg':
		BaseMediaInfo base_media_info;
		break;
	case 'ferd':
		DataReference data_reference;
		break;
		// data reference types (not implemented because they are not defined)
		// samples
	case 'stts':
		TimeToSample time_to_sample;
		break;
	case 'ssts':		// p.79
		SyncSample sync_sample;
		break;
	case 'csts':
		SampleToChunk sample_to_chunk;
		break;
	case 'zsts':
		SampleSize sample_size;
		break;
	case 'octs':
		ChunkOffset chunk_offset;
		break;
	case 'frdr':
		DataReferenceChunk data_ref;
		break;
	case 'rdmr':
		DataRate data_rate;
		break;
	case 'crmr':
		CpuSpeed cpu_speed;
		break;
	case 'cvrm':
		VersionCheck version_check;
		break;
	case 'dcmr':
		ComponentDetect component_detect;
		break;
	case 'uqmr':
		Quality quality;
		break;

		// p.98
	case 'amag':
		DWORD dwGammaLevel;
		break;
	case 'leif':
		BYTE nFieldCount;
		BYTE nFieldOrdering;
		break;
	case 'sdse':	// p.100
		StreamDesc stream_desc;
		break;
	case 'rloc':
		Color color;
		break;
	case 'clap':	// p.106
		CleanAperture clean_aperture;
		break;
	case 'psap':
		PixelAspectRation pixel_aspect_ratio;
		break;
		// TODO: test, maybe it is inside sample descriptor?
	case 'imct':	// p.121
		TimecodeMedia timecode_media;
		break;

		// user atom types
		// TODO: revert all tags !!!
		/*
		case '©arg': $print("Atom type","Name of arranger");break;
		case '©ark': $print("Atom type","Keyword(s) for arranger X");break;
		case '©cok': $print("Atom type","Keyword(s) for composer X");break;
		case '©com': $print("Atom type","Name of composer");break;
		case '©cpy': $print("Atom type","Copyright statement");break;
		case '©day': $print("Atom type","Date the movie content was created");break;
		case '©dir': $print("Atom type","Name of movie’s director");break;
		case '©ed1': $print("Atom type","Edit dates and descriptions");break;
		case '©fmt': $print("Atom type","Indication of movie format (computer-generated, digitized, and so on)");break;
		case '©inf': $print("Atom type","Information about the movie");break;
		case '©isr': $print("Atom type","ISRC code");break;
		case '©lab': $print("Atom type","Name of record labe");break;
		case '©lal': $print("Atom type","URL of record label");break;
		case '©mak': $print("Atom type","Name of file creator or maker");break;
		case '©mal': $print("Atom type","URL of file creator or maker");break;
		case '©nak': $print("Atom type","Title keyword(s) of the content X");break;
		case '©nam': $print("Atom type","Title of the content");break;
		case '©pdk': $print("Atom type","Keyword(s) for producer X");break;
		case '©phg': $print("Atom type","Recording copyright statement, normally preceded by the symbol P");break;
		case '©prd': $print("Atom type","Name of producer");break;
		case '©prf': $print("Atom type","Names of performers");break;
		case '©prk': $print("Atom type","Keyword(s) of main artist and performer X");break;
		case '©prl': $print("Atom type","URL of main artist and performer");break;
		case '©req': $print("Atom type","Special hardware and software requirements");break;
		case '©snk': $print("Atom type","Sub-title keyword(s) of the content X");break;
		case '©snm': $print("Atom type","Sub-title of content");break;
		case '©src': $print("Atom type","Credits for those who provided movie source content");break;
		case '©swf': $print("Atom type","Name of songwriter");break;
		case '©swk': $print("Atom type","Keyword(s) for songwriter X ");break;
		case '©swr': $print("Atom type","Name and version number of the software (or hardware) that generated this movie");break;
		case '©wrt': $print("Atom type","Name of movie’s writer");break;
		case "AllF': $print("Atom type","Play all frames—byte indicating that all frames of video should be played, regardless of timing");break;
		case 'hinf': $print("Atom type","Hint track information—statistical data for real-time streaming of a particular track.");break;
		case 'hnti': $print("Atom type","Hint info atom—data used for real-time streaming of a movie or a track.");break;
		case 'name': $print("Atom type","Name of object");break;
		case 'LOOP': $print("Atom type","Long integer indicating looping style.");break;
		case 'SelO': $print("Atom type","Play selection only—byte indicating that only the selected area of the movie should be played");break;
		case 'WLOC': $print("Atom type","Default window location for movie—two 16-bit values, {x,y}");break;
		*/
	}
	if (nAtomSize + 8 < (current_offset - this))
	{
		$print("last index", array_index);
		$print("last offset", current_offset);
		$break_array(true);
	}
	else
		BYTE not_parsed_data[nAtomSize - (current_offset - this) + 8];
};

struct AtomWrapper
{
	if (nFileSize <= 0)
		$break_array(false);

	Atom atom;
	nFileSize = nFileSize - (current_offset - this);
};

public struct QT_File
{
	var nFileSize = GetDocumentSize();
	AtomWrapper atoms[6];
};


/*
// TODO: M-JPEG (p109)
*/
/*
enum SpriteAtomTypesEnum<DWORD>
{
	kSpriteAtomType					= 'sprt',
	kSpriteImagesContainerAtomType  = 'imct',
	kSpriteImageAtomType			= 'imag',
	kSpriteImageDataAtomType		= 'imda',
	kSpriteImageDataRefAtomType		= 'imre',
	kSpriteImageDataRefTypeAtomType = 'imrt',
	kSpriteImageGroupIDAtomType		= 'imgr',
	kSpriteImageRegistrationAtomType= 'imrg',
	kSpriteImageDefaultImageIndexAtomType	= 'defi',
	kSpriteSharedDataAtomType				= 'dflt',
	kSpriteNameAtomType						= 'name',
	kSpriteImageNameAtomType				= 'name',
	kSpriteUsesImageIDsAtomType				= 'uses',
	kSpriteBehaviorsAtomType = 'beha',
	kSpriteImageBehaviorAtomType = 'imag',
	kSpriteCursorBehaviorAtomType = 'crsr',
	kSpriteStatusStringsBehaviorAtomType = 'sstr',
	kSpriteVariablesContainerAtomType = 'vars',
	kSpriteStringVariableAtomType = 'strv',
	kSpriteFloatingPointVariableAtomType = 'flov'
	kSpriteSharedDataAtomType = 'dflt',
	kSpriteURLLinkAtomType = 'url '

	kSpritePropertyMatrix = 1
	kSpritePropertyVisible = 4
	kSpritePropertyLayer = 5
	kSpritePropertyGraphicsMode = 6
	kSpritePropertyImageIndex = 100
	kSpritePropertyBackgroundColor = 101
	kSpritePropertyOffscreenBitDepth = 102
	kSpritePropertySampleFormat = 103
};
*/

// p.22
struct QT_Atom
{
	DWORD dwSize;
	DWORD dwType;

	DWORD dwAtomID;
	WORD wReserved;
	WORD wChildCount;
	DWORD dwReserved;

	QT_Atom atom[wChildCount];
	if (!wChildCount)
	{
		// leaf node
	}
};

struct QT_AtomContainer
{
	BYTE	reserved[10];
	WORD wLockCount;
	QT_Atom atom;
};
