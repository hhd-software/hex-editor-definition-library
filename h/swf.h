// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
// see SWF File Format Specifications (version 10)

#include "stddefs.h"
#pragma script("get_document_size.js")

typedef string STRING;

enum CompressionBool : BYTE
{
	Uncompressed = 'F',
	Compressed = 'C'
};

struct RECT
{
	int left, top, right, bottom;
};

struct SWFHeader
{
	CompressionBool compression;
	char signature[2];
	$assert(signature == 'WS', "Hex Editor is unable to parse file: invalid signature");

	BYTE nVersion;
	DWORD dwLength;
	RECT rcFrameSizeInTwips;
	WORD wFrameRate;
	WORD wFrameCount;
};

// Short tag headers are used for tags with 62 bytes of data or less
struct RECORDHEADER_short
{
	WORD type : 10;
	WORD length : 6;
};

// Long tag headers, with a signed 32-bit length field, can be used for any tag size up to 2GB
struct RECORDHEADER_long
{
	WORD type : 10;
	WORD length_short : 6;
	DWORD dwLength;
};

// basic types
struct FLOAT16
{
	WORD sign : 1;
	WORD exponent : 5;
	WORD mantissa : 10;
};

struct RGBA
{
	BYTE r, g, b, a;
};

struct  ENCODEDU32
{
	// TODO: p.14
};

struct RECT
{
	// TODO: p.17
};

struct MATRIX
{
	// TODO: p.20
};

struct CXFORM
{
	// TODO: p.22
};

struct CXFORMWITHALPHA
{
	// TODO: p.24
};

struct GRADIENT
{
	// TODO
};

struct FOCALGRADIENT
{
	// TODO
};

struct CLIPEVENTFLAGS
{
	union Actions
	{
		struct Bitfields
		{
			WORD ClipEventKeyUp : 1;
			WORD ClipEventKeyDown : 1;
			WORD ClipEventMouseUp : 1;
			WORD ClipEventMouseDown : 1;
			WORD ClipEventMouseMove : 1;
			WORD ClipEventUnload : 1;
			WORD ClipEventEnterFrame : 1;
			WORD ClipEventLoad : 1;
			WORD ClipEventDragOver : 1;
			WORD ClipEventRollOut : 1;
			WORD ClipEventRollOver : 1;
			WORD ClipEventReleaseOutside : 1;
			WORD ClipEventRelease : 1;
			WORD ClipEventPress : 1;
			WORD ClipEventInitialize : 1;
			WORD ClipEventData : 1;
		} bitfields;

		WORD wValue;
	} actions;

	// TODO: global variable?
	if (swf_version >= 6)
	{
		union Actions2
		{
			struct Bitfield2
			{
				BYTE wReserved : 5;
				BYTE ClipEventConstruct : 1;
				BYTE ClipEventKeyPress : 1;
				BYTE ClipEventDragOut : 1;

				BYTE nReserved;
			} bitfields2;

			WORD wValue;
		} actions2;
	}
};

struct Empty
{
	// empty
};

// actions
enum ActionCodes : WORD
{
	ActionGotoFrame = 0x81,
	ActionGetURL = 0x83,

	ActionNextFrame = 0x4,
	ActionPrevFrame,
	ActionPlay,
	ActionStop,
	ActionToggleQuality,
	ActionStopSounds,

	ActionWaitForFrame = 0x8A,
	ActionSetTarget,
	ActionGoToLabel,

	// SWF 4 actions
	ActionAdd = 0xa,
	ActionDivide = 0xd,
	ActionMultiply = 0xc,
	ActionSubtract = 0xb,

	ActionEquals = 0xe,
	ActionLess = 0xf,
	ActionAnd = 0x10,
	ActionNot = 0x12,
	ActionOr = 0x11,

	ActionStringAdd = 0x21,
	ActionStringEquals = 0x13,
	ActionStringExtract = 0x15,
	ActionStringLength = 0x14,
	ActionMBStringExtract = 0x35,
	ActionMBStringLength = 0x31,
	ActionStringLess = 0x29,

	ActionPop = 0x17,
	ActionPush = 0x96,
	ActionAsciiToChar = 0x33,
	ActionCharToAscii = 0x32,
	ActionToInteger = 0x18,
	ActionMBAsciiToChar = 0x37,
	ActionMBCharToAscii = 0x36,
	ActionCall = 0x9e,
	ActionIf = 0x9d,
	ActionJump = 0x99,
	ActionGetVariable = 0x1c,
	ActionSetVariable = 0x1d,

	ActionGetURL2 = 0x9a,
	ActionGetProperty = 0x22,
	ActionGotoFrame2 = 0x9f,
	ActionRemoveSprite = 0x25,
	ActionSetProperty = 0x23,
	ActionSetTarget2 = 0x20,
	ActionStartDrag = 0x27,
	ActionWaitForFrame2 = 0x8d,
	ActionCloneSprite = 0x24,
	ActionEndDrag = 0x28,
	ActionGetTime = 0x34,
	ActionRandomNumber = 0x30,
	ActionTrace = 0x26,

	// SWF 5
	ActionCallFunction = 0x3d,
	ActionCallMethod = 0x52,
	ActionConstantPool = 0x88,
	ActionDefineFunction = 0x9B,
	ActionDefineLocal = 0x3c,
	ActionDefineLocal2 = 0x41,
	ActionDelete = 0x3a,
	ActionDelete2 = 0x3b,
	ActionEnumerate = 0x46,
	ActionEquals2 = 0x49,
	ActionGetMember = 0x4e,
	ActionInitArray = 0x42,
	ActionInitObject = 0x43,
	ActionNewMethod = 0x53,
	ActionNewObject = 0x40,
	ActionSetMember = 0x4f,
	ActionTargetPath = 0x45,
	ActionWith = 0x94,

	ActionToNumber = 0x4a,
	ActionToString = 0x4b,
	ActionTypeOf = 0x44,
	ActionAdd2 = 0x47,
	ActionLess2 = 0x48,
	ActionModulo = 0x3f,

	ActionBitAnd = 0x60,
	ActionBitLShift = 0x63,
	ActionBitOr = 0x61,
	ActionBitRShift = 0x64,
	ActionBitURShift = 0x65,
	ActionBitXor = 0x62,
	ActionDecrement = 0x51,
	ActionIncrement = 0x50,

	ActionPushDuplicate = 0x4c,
	ActionReturn = 0x3e,
	ActionStackSwap = 0x4d,
	ActionStoreRegister = 0x87,

	// SWF 6 
	DoInitAction = 0x59,
	ActionInstanceOf = 0x54,
	ActionEnumerate2 = 0x55,
	ActionStrictEquals = 0x66,
	ActionGreater = 0x67,
	ActionStringGreater = 0x68,

	// SWF 7
	ActionDefineFunction2 = 0x8E,
	ActionExtends = 0x69,
	ActionCastOp = 0x2b,
	ActionImplementsOp = 0x2c,
	ActionTry = 0x8f,
	ActionThrow = 0x2a,
};

enum PushType : BYTE
{
	TypeString,
	TypeFloat,
	TypeNull,
	TypeUndefined,
	TypeRegister,
	TypeBoolean,
	TypeDouble,
	TypeInteger,
	TypeConstant8,
	TypeConstant16,
};

struct Action
{
	BYTE nActionCode;
	WORD wLength;

	var nActionBegin = current_offset;

	switch (nActionCode)
	{
	case ActionGotoFrame:
		if (wLength == 2)
		{
			struct GoToFrame
			{
				WORD wFrameIndex;
			} goto_frame;
		}
		break;
	case ActionGetURL:
		struct GetURL
		{
			string url, target;
		} get_url;
		break;
	case ActionNextFrame:
	case ActionPrevFrame:
	case ActionPlay:
	case ActionStop:
	case ActionToggleQuality:
	case ActionStopSounds:
		Empty empty;
		break;
	case ActionWaitForFrame:
		if (wLength == 3)
		{
			struct WaitForFrame
			{
				WORD wFrame;
				BYTE nSkipCount;	// Number of actions to skip if
									// frame is not loaded
			} wait_for_frame;
		}
		break;
	case ActionSetTarget:
		struct SetTarget
		{
			string target_name;
		} set_target;
		break;
	case ActionGoToLabel:
		struct GoToLabel
		{
			string label;
		} go_to_label;
		break;
		// SWF 4
	case ActionPush:
		struct Push
		{
			PushType type;
			switch (type)
			{
			case 0:
				string str;
				break;
			case 1:
				FLOAT fl;
				break;
			case 4:
				BYTE reg_number;
				break;
			case 5:
				BYTE bool_val;
				break;
			case 6:
				DOUBLE double_val;
				break;
			case 7:
				DWORD int_val;
				break;
			case 8:
				BYTE const_pool_index;
				break;
			case 9:
				WORD const_pool_index;
				break;
			}
		} push;
		break;
	case ActionPop:
	case ActionAdd:
	case ActionSubtract:
	case ActionMultiply:
	case ActionDivide:
	case ActionEquals:
	case ActionLess:
	case ActionAnd:
	case ActionOr:
	case ActionStringEquals:
	case ActionStringLength:
	case ActionStringAdd:
	case ActionStringExtract:
	case ActionStringLess:
	case ActionMBStringLength:
	case ActionMBStringExtract:
	case ActionToInteger:
	case ActionCharToAscii:
	case ActionAsciiToChar:
	case ActionMBCharToAscii:
	case ActionMBAsciiToChar:
	case ActionCall:
	case ActionGetVariable:
	case ActionSetVariable:
	case ActionSetTarget2:
	case ActionGetProperty:
	case ActionSetProperty:
	case ActionCloneSprite:
	case ActionRemoveSprite:
	case ActionStartDrag:
	case ActionEndDrag:
	case ActionTrace:
	case ActionGetTime:
	case ActionRandomNumber:
		Empty empty;
		break;
	case ActionNot:
		struct Not
		{
			BYTE result;
		} not;
		break;
	case ActionJump:
		struct Jump
		{
			short wShortOffset;
		} jump;
		break;
	case ActionIf:
		struct If
		{
			short wBranchOffset;
		} if_action;
		break;
	case ActionGetURL2:
		struct GetURL2
		{
			BYTE SendVarsMethod : 2;
			BYTE Reserved : 4;
			BYTE LoadTargetFlag : 1;
			BYTE LoadVariablesFlag : 1;
		} get_url2;
		break;
	case ActionGotoFrame2:
		struct GoToFrame2
		{
			BYTE Reserved : 6;
			BYTE SceneBiasFlag : 1;
			BYTE PlayFlag : 1;

			if (SceneBiasFlag)
				WORD wSceneBias;
		} goto_frame2;
		break;
	case ActionWaitForFrame2:
		struct WaitForFrame2
		{
			BYTE nSkipCount;
		} wait_for_frame2;
		break;

		// SWF 5
	case ActionCallFunction:
	case ActionCallMethod:
	case ActionDefineLocal:
	case ActionDefineLocal2:
	case ActionDelete:
	case ActionDelete2:
	case ActionEnumerate:
	case ActionEquals2:
	case ActionGetMember:
	case ActionInitArray:
	case ActionInitObject:
	case ActionNewMethod:
	case ActionNewObject:
	case ActionSetMember:
	case ActionTargetPath:
	case ActionTargetPath:
	case ActionToNumber:
	case ActionToString:
	case ActionTypeOf:
	case ActionAdd2:
	case ActionLess2:
	case ActionModulo:
	case ActionBitAnd:
	case ActionBitLShift:
	case ActionBitOr:
	case ActionBitRShift:
	case ActionBitURShift:
	case ActionBitXor:
	case ActionDecrement:
	case ActionIncrement:
	case ActionPushDuplicate:
	case ActionReturn:
	case ActionStackSwap:
	case ActionStoreRegister:
		Empty empty;
		break;
	case ActionConstantPool:
		struct ConstantPool
		{
			WORD	wCount;
			string  pool[wCount];
		} constant_pool;
		break;
	case ActionDefineFunction:
		// p.97 
		struct DefineFunction
		{
			string function_name;
			WORD wNumParams;
			string param1[wNumParams];
			WORD wCodeSize;

			// TODO: ???
			//BYTE code[wCodeSize];
		} define_function;
		break;
	case ActionWith:
		struct With
		{
			WORD wSize;
			// TODO: ???
			//BYTE code[wCodeSize];
		}with;
		break;
	case DoInitAction:
		struct InitAction
		{
			WORD wSpriteID;
			// TODO: while 0 tag is not found
			ACTIONRECORD action_records[*];
		}init_action;
		break;
		// SWF 6
	case ActionInstanceOf:
	case ActionEnumerate2:
	case ActionStrictEquals:
	case ActionGreater:
	case ActionStringGreater:
		Empty empty;
		break;

		// SWF 7
	case ActionDefineFunction2:
		// p.117
		struct DefineFunction2
		{
			string function_name;
			WORD wNumParameters;
			BYTE nRegisterCount;

			WORD wPreloadParentFlag : 1;
			WORD wPreloadRootFlag : 1;
			WORD wSupressSuperFlag : 1;
			WORD wPreloadSuperFlag : 1;
			WORD wSupressArgumentsFlag : 1;
			WORD wPreloadArgumentsFlag : 1;
			WORD wSupressThisFlag : 1;
			WORD wPreloadThisFlag : 1;
			WORD wReserved : 7;
			WORD wPreloadGlobalFlag : 1;

			struct REGISTERPARAM
			{
				BYTE nRegister;
				string param_name;
			}params[wNumParameters];

			WORD wCodeSize;
			// TODO: ???
			//BYTE code[wCodeSize];
		}define_function2;
		break;
	case ActionExtends:
	case ActionCastOp:
	case ActionImplementsOp:
	case ActionThrow:
		Empty empty;
		break;
	case ActionTry:
		struct Try
		{
			BYTE Reserved : 5;
			BYTE CatchInRegisterFlag : 1;
			BYTE FinallyBlockFlag : 1;
			BYTE CatchBlockFlag : 1;

			WORD wTrySize;
			WORD wCatchSize;
			WORD wFinallySize;

			if (CatchInRegisterFlag)
			{
				string catch_name;
				BYTE   nCatchReg;
			}

			BYTE try_body[wTrySize];
			BYTE catch_body[wCatchSize];
			BYTE finally_body[wFinallySize];
		}try_action;
		break;
	}

	BYTE not_parsed_data[wLength - (current_offset - nActionBegin)];
};

struct ACTIONRECORD
{
	if (nActionRecords <= 0)
		$break_array(false);

	if (nActionRecords <= 1)
	{
		$break_array(true);
		BYTE nTerminator;		// TODO: check how it works
	}
	else
	{
		// TODO: p.73
		Action action;
		nActionRecords = nActionRecords - (current_offset - this);
	}
};

struct CLIPACTIONS
{
	WORD wReserved;
	CLIPEVENTFLAGS all_event_flags;

	[[noindex]]
	struct CLIPACTIONRECORD
	{
		CLIPEVENTFLAGS event_flags;

		var bBreak = 0;

		// TODO: test double break_array!!
		if (event_flags.actions.wValue == 0)
		{
			if (swf_version >= 6)
			{
				if (event_flags.actions2.wValue == 0)
				{
					$break_array(true);
					bBreak = 1;
				}
			}
			else
			{
				$break_array(true);
				bBreak = 1;
			}
		}

		// bBreak is flag (extra safety)
		if (bBreak == 0)
		{
			DWORD dwRecordSize;
			var nActionRecords = dwRecordSize;
			if (event_flags.ClipEventKeys)
			{
				BYTE nKeyCode;
				nActionRecords = nActionRecords - 1;
			}
			ACTIONRECORD action_records[*];
		}
	} records[*];
};

// filters:
enum FilterID : BYTE
{
	HasDropShadowFilter,
	HasBlurFilter,
	HasGlowFilter,
	HasBevelFilter,
	HasGradientGlowFilter,
	HasConvolutionFilter,
	HasColorMatrixFilter,
	HasGradientBevelFilter,
};

struct COLORMATRIXFILTER
{
	FLOAT matrix[20];
};

struct CONVOLUTIONFILTER
{
	BYTE nMatrixX, nMatrixY;
	FLOAT fDivisor, fBias;
	FLOAT matrix[nMatrixX * nMatrixY];
	RGBA default_color;

	BYTE reserved : 6;
	BYTE clamp_mode : 1;
	BYTE preserve_alpha : 1;
};

struct BLURFILTER
{
	FIXED nBlurX, nBlurY;
	BYTE  passes : 5;
	BYTE  reserved : 3;
};

struct DROPSHADOWFILTER
{
	RGBA   DropShadowColor;
	FIXED  BlurX, BlurY, Angle, Distance;
	FIXED8 Strength;

	BYTE inner_shadow : 1;
	BYTE knockout : 1;
	BYTE composite_source : 1;
	BYTE passes : 5;
};

struct GLOWFILTER
{
	RGBA GlowColor;
	FIXED BlurX, BlurY;
	FIXED8 Strength;

	BYTE inner_shadow : 1;
	BYTE knockout : 1;
	BYTE composite_source : 1;
	BYTE passes : 5;
};

struct BEVELFILTER
{
	RGBA ShadowColor, HighlightColor;
	FIXED BlurX, BlurY, Angle, Distance;
	FIXED8 Strength;

	BYTE inner_shadow : 1;
	BYTE knockout : 1;
	BYTE composite_source : 1;
	BYTE on_top : 1;
	BYTE passes : 4;
};

struct GRADIENTGLOWFILTER
{
	BYTE nNumColors;
	RGBA GradientColors[nNumColors];
	BYTE GradientRatio[nNumColors];
	FIXED BlurX, BlurY, Angle, Distance;
	FIXED8 Strength;

	BYTE inner_shadow : 1;
	BYTE knockout : 1;
	BYTE composite_source : 1;
	BYTE on_top : 1;
	BYTE passes : 4;
};

typedef GRADIENTGLOWFILTER GRADIENBEVELFILTER;

struct FILTER
{
	FilterID nFilterID;
	switch (nFilterID)
	{
	case HasDropShadowFilter:
		DROPSHADOWFILTER drop_filter;
		break;
	case HasBlurFilter:
		BLURFILTER blur_filter;
		break;
	case HasGlowFilter:
		GLOWFILTER glow_filter;
		break;
	case HasBevelFilter:
		BEVELFILTER bevel_filter;
		break;
	case HasGradientGlowFilter:
		GRADIENTGLOWFILTER gradient_flow_filter;
		break;
	case HasConvolutionFilter:
		CONVOLUTIONFILTER convolution_filter;
		break;
	case HasColorMatrixFilter:
		COLORMATRIXFILTER color_matrix_filter;
		break;
	case HasGradientBevelFilter:
		GRADIENBEVELFILTER gradient_bevel_filter;
		break;
	}
};

struct FILTERLIST
{
	BYTE nNumberOfFilters;
	FILTER filters[nNumberOfFilters];
};
//////////////////////////
struct Asset
{
	WORD wTag;
	string name;
};

typedef Asset Symbol;

enum TagType : WORD
{
	TagDefineShape = 2,
	TagDefineShape2 = 22,
	TagDefineShape3 = 32,
	TagDefineShape4 = 83,

	TagPlaceObject = 4,
	TagPlaceObject2 = 26,
	TagRemoveObject = 5,
	TagRemoveObject2 = 28,
	TagShowFrame = 1,

	// control tags
	TagSetBackground = 9,
	TagFrameLable = 43,
	TagProtect = 24,
	TagEnd = 0,
	TagExportAssets = 56,
	TagImportAssets = 57,
	TagEnableDebugger = 58,
	TagEnableDebugger2 = 64,
	TagScriptLimits = 65,
	TagSetTabIndex = 66,
	TagFileAttributes = 69,
	TagImportAssets2 = 71,
	TagSymbolClass = 76,
	TagXMLMetadata = 77,
	TagDefineScalingGrid = 78,
	TagDefineSceneAndFrameLabelData = 86,

	TagDoAction = 12,
};

enum BlendMode : BYTE
{
	ModeNormalStd = 0,
	ModeNormal = 1,
	ModeLayer,
	MoodeMultiply,
	ModeScreen,
	ModeLighten,
	ModeDarken,
	ModeDiff,
	ModeAdd,
	ModeSubtrackt,
	ModeInvert,
	ModeAlpha,
	ModeErase,
	ModeOverlay,
	ModeHadrlight
};

// forward declaration
struct DEFINE_SHAPE;
struct DEFINE_SHAPE2;
struct DEFINE_SHAPE3;
struct DEFINE_SHAPE4;

// TODO: connect to a type with TagType!!!
struct Tag
{
	switch (type)
	{
	case TagDefineShape:
		DEFINE_SHAPE define_shape;
		break;
	case TagDefineShape2:
		DEFINE_SHAPE2 define_shape2;
		break;
	case TagDefineShape3:
		DEFINE_SHAPE3 define_shape3;
		break;
	case TagDefineShape4:
		DEFINE_SHAPE4 define_shape4;
		break;

	case TagPlaceObject:
		// p. 35
		struct PlaceObject
		{
			WORD wCharacterID;
			WORD wDepth;
			MATRIX matrix;
			CXFORM color_transform;
		}place_object;
		break;
	case TagPlaceObject2:
		//  p.37
		struct PlaceObject2
		{
			BYTE PlaceFlagHasClipActions : 1;
			BYTE PlaceFlagHasClipDepth : 1;
			BYTE PlaceFlagHasName : 1;
			BYTE PlaceFlagHasRatio : 1;
			BYTE PlaceFlagHasColorTransform : 1;
			BYTE PlaceFlagHasMatrix : 1;
			BYTE PlaceFlagHasCharacter : 1;
			BYTE PlaceFlagMove : 1;

			WORD wDepth;
			if (PlaceFlagHasCharacter)
				WORD wCharacterID;

			if (PlaceFlagHasMatrix)
				MATRIX matrix;

			if (PlaceFlagHasColorTransform)
				CXFORMWITHALPHA color_transform;

			if (PlaceFlagHasRatio)
				WORD wRatio;

			if (PlaceFlagHasName)
				STRING name;

			if (PlaceFlagHasClipDepth)
				WORD wClipDepth;

			if (PlaceFlagHasClipActions)
				CLIPACTIONS clip_actions;
		}place_object2;
		break;
	case TagPlaceObject3:
		// p.40
		struct PlaceObject3
		{
			WORD PlaceFlagHasClipActions : 1;
			WORD PlaceFlagHasClipDepth : 1;
			WORD PlaceFlagHasName : 1;
			WORD PlaceFlagHasRatio : 1;
			WORD PlaceFlagHasColorTransform : 1;
			WORD PlaceFlagHasMatrix : 1;
			WORD PlaceFlagHasCharacter : 1;
			WORD PlaceFlagMove : 1;

			WORD Reserved : 3;
			WORD PlaceFlagHasImage : 1;
			WORD PlaceFlagHasClassName : 1;
			WORD PlaceFlagHasCacheAsBitmap : 1;
			WORD PlaceFlagHasBlendMode : 1;
			WORD PlaceFlagHasFilterList : 1;

			WORD wDepth;
			if (PlaceFlagHasClassName || (PlaceFlagHasImage && PlaceFlagHasCharacter))
				string ClassName;

			if (PlaceFlagHasCharacter)
				WORD wCharacterID;

			if (PlaceFlagHasMatrix)
				MATRIX matrix;

			if (PlaceFlagHasColorTransform)
				CXFORMWITHALPHA color_transform;

			if (PlaceFlagHasRatio)
				WORD wRatio;

			if (PlaceFlagHasName)
				STRING name;

			if (PlaceFlagHasClipDepth)
				WORD wClipDepth;

			if (PlaceFlagHasFilterList)
				FILTERLIST filter_list;

			if (PlaceFlagHasBlendMode)
				BlendMode nBlendMode;

			if (PlaceFlagHasCacheAsBitmap)
				BYTE nBitmapCache;

			if (PlaceFlagHasClipActions)
				CLIPACTIONS clip_actions;
		}place_object3;
		break;
	case TagRemoveObject:
		struct RemoveObject
		{
			WORD wCharacterID;
			WORD wDepth;
		}remove_object;
		break;
	case TagRemoveObject2:
		struct RemoveObject2
		{
			WORD wDepth;
		}remove_object2;
		break;
	case TagShowFrame:
		struct ShowFrame
		{
			// empty			
		}show_frame;
		break;
	case TagSetBackground:
		struct SetBackground
		{
			RGB rgb;
		}set_background;
		break;
	case TagFrameLable:
		struct FrameLable
		{
			string name;
			if (swf_version >= 6)
				BYTE nNamedAnchorFlag;
		}frame_label;
		break;
	case TagProtect:
		struct Protect
		{
			// empty
		}protect;
		break;
	case TagEnd:
		struct End
		{
			// empty
		}end;
		break;
	case TagExportAssets:
		struct ExportAssets
		{
			WORD wCount;
			Asset assets[wCount];
		}export_assets;
		break;
	case TagImportAssets:
		struct ImportAssets
		{
			string url;
			WORD wCount;
			Asset assets[wCount];
		}import_assets;
		break;
	case TagEnableDebugger:
		struct EnableDebugger
		{
			string encrypted_password;  // MD-5 encrypted :-)
		}enable_debugger;
		break;
	case TagEnableDebugger2:
		struct EnableDebugger2
		{
			WORD wReserved;
			string encrypted_password;  // MD-5 encrypted :-)
		}enable_debugger2;
		break;
	case TagScriptLimits:
		struct ScriptLimits
		{
			WORD wMaxRecursionDepth;
			WORD wScriptTimeoutSeconds;
		}script_limits;
		break;
	case TagSetTabIndex:
		struct SetTabIndex
		{
			WORD wDepth;
			WORD wTabIndex;
		}set_tab_index;
		break;
	case TagFileAttributes:
		struct FileAttributes
		{
			DWORD reserved : 1;
			DWORD UseDirectBlit : 1;
			DWORD UseGPU;
			DWORD HasMetadata : 1;
			DWORD ActionScript3 : 1;
			DWORD Reserved : 2;
			DWORD UseNetwork : 1;
			DWORD Reserved : 24;
		}file_attributes;
		break;
	case TagImportAssets2:
		struct ImportAssets
		{
			string url;
			BYTE nReserved[2];
			WORD wCount;
			Asset assets[wCount];
		}import_assets;
		break;
	case TagSymbolClass:
		struct SymbolClass
		{
			WORD wNumSymbols;
			Symbol symbols[wNumSymbols];
		}symbol_class;
		break;
	case TagXMLMetadata:
		struct XMLMetadata
		{
			string xml_metadata;
		}metadata;
		break;
	case TagDefineScalingGrid:
		// p.65
		struct DefineScalingGrid
		{
			WORD wCharacterID;
			RECT splitter;
		}define_scaling_grid;
		break;
	case TagDefineSceneAndFrameLabelData:
		struct DefineSceneAndFrameLabelData
		{
			ENCODEDU32 nSceneCount;

			struct Scene
			{
				ENCODEDU32	nOffset;
				string		name;
			}scenes[nSceneCount];

			ENCODEDU32 nFrameLabelCount;

			struct Frame
			{
				ENCODEDU32 nFrameNum;
				string     frame_label;
			}frames[nFrameLabelCount];
		}define_scene_and_frame_label_data;
		break;
	case TagDoAction:
		// p.68
		struct DoAction
		{
			var nActionRecords = header.dwLength - ;	// TODO: calculate length properly
			ACTIONRECORD action_records[*];
		}do_action;
		break;
	}
};

/*
* Shapes
*/
struct FILLSTYLE;

struct FILLSTYLEARRAY
{
	BYTE nLineStyleCount;

	var nCount = nLineStyleCount;
	if (nLineStyleCount == 0xff)
	{
		WORD nLineStyleCountExtended;
		nCount = nLineStyleCountExtended;
	}

	FILLSTYLE fill_styles[nCount];
};

enum FillStyleType : BYTE
{
	SolidFill,
	LinearGradientFill = 0x10,
	RadialGradientFill = 0x12,
	FocalRadialGradientFill = 0x13,

	RepeatingBitmapFill = 0x40,
	ClippedBitmapFill = 0x41,
	NonSmoothedRepeatingBitmapFill = 0x42,
	NonSmoothedClippedBitmap = 0x43,
};

struct FILLSTYLE
{
	FillStyleType type;
	if (type == SolidFill)
	{
		if (nShapeIndex == 3)
			RGBA color; // if shape 3
		else
			RGB  color;
	}

	if (type == LinearGradientFill || type == RadialGradientFill || type == FocalRadialGradientFill)
		MATRIX gradient_matrix;

	if (type == LinearGradientFill || type == RadialGradientFill)
		GRADIENT gradient;

	if (type == FocalRadialGradientFill)
		FOCALGRADIENT gradient;

	if (type == RepeatingBitmapFill || type == ClippedBitmapFill || type == NonSmoothedRepeatingBitmapFill || type == NonSmoothedClippedBitmap)
	{
		WORD	wBitmapId;
		MATRIX	bitmap_matrix;
	}
};

struct LINESTYLE
{
	WORD wWidth;
	if (nShapeIndex == 3)
		RGBA color;
	else
		RGB color;
};

struct LINESTYLE2
{
	WORD wWidth;

	WORD start_cap_type : 2;
	WORD join_style : 2;

	WORD has_fill_flag : 1;
	WORD no_h_scale_flag : 1;
	WORD no_v_scale_flag : 1;
	WORD PixelHintingFlag : 1;
	WORD Reserved : 5;
	WORD NoClose : 1;
	WORD EndCapStyle : 2;

	if (join_style == 2)
		WORD MiterLimitFactor;

	if (has_fill_flag == 0)
		RGBA color;
	else
		FILLSTYLE fill_style;
};

struct LINESTYLEARRAY
{
	BYTE nLineStyleCount;

	var nCount = nLineStyleCount;
	if (nLineStyleCount == 0xff)
	{
		WORD nLineStyleCountExtended;
		nCount = nLineStyleCountExtended;
	}

	// if shape1, shape2, shape3
	if (nShapeIndex == 4)
		LINESTYLE2 linestyles[nCount];
	else
		LINESTYLE linestyles[nCount];
};

struct ENDSHAPERECORD
{
	BYTE TypeFlag : 1;
	BYTE EndOfShape : 5;
	// TODO: not 8 bits
};

struct STRAIGHTEDGERECORD
{
	// TODO: bits
	WORD TypeFlag : 1;
	WORD StraightFlag : 1;
	WORD NumBits : 4;
	WORD GeneralLineFlag : 1;

	var nVertVal = 0;
	if (GeneralLineFlag == 0)
	{
		WORD VertLineFlag : 1;
		nVertVal = VertLineFlag;
	}

	if (GeneralLineFlag == 1 || nVertVal == 0)
		WORD DeltaX : NumBits + 2;		// TODO

	if (GeneralLineFlag == 1 || nVertVal == 1)
		WORD DeltaY : NumBits + 2;		// TODO
};

struct CURVEDEDGERECORD
{
	BYTE TypeFlag : 1;
	BYTE StraightFlag : 1;
	BYTE NumBits : 4;

	WORD ControlDeltaX : NumBits + 2; // TODO
	WORD ControlDeltaY : NumBits + 2; // TODO
	WORD AnchorDeltaX : NumBits + 2; // TODO
	WORD AnchorDeltaY : NumBits + 2; // TODO
};

struct DEFINE_SHAPE
{
	var nShapeIndex = 1;

	WORD wShapeID;
	RECT ShapeBoundsRect;
	SHAPEWITHSTYLE	shapes;
};

struct DEFINE_SHAPE2
{
	var nShapeIndex = 2;

	WORD ShapeId;
	RECT ShapeBounds;
	SHAPEWITHSTYLE shapes;
};

struct DEFINE_SHAPE3
{
	var nShapeIndex = 3;

	WORD ShapeId;
	RECT ShapeBounds;
	SHAPEWITHSTYLE shapes;
};

struct DEFINE_SHAPE4
{
	var nShapeIndex = 4;

	WORD ShapeId;
	RECT ShapeBounds;
	RECT EdgeBounds;

	BYTE Reserved : 5;
	BYTE UsesFillWindingRule : 1;
	BYTE UsesNonScalingStrokes : 1;
	BYTE UsesScalingStrokes : 1;
	SHAPEWITHSTYLE shapes;
};

struct STYLECHANGERECORD
{
	WORD TypeFlag : 1;
	WORD StateNewStyles : 1;
	WORD StateLineStyle : 1;
	WORD StateFillStyle1 : 1;
	WORD StateFillStyle0 : 1;
	WORD StateMoveTo : 1;
	// TODO: not 8 bits

	if (StateMoveTo)
	{
		BYTE MoveBits : 5;
		BYTE MoveDeltaX : MoveBits;	// TODO!!!
		BYTE MoveDeltaY : MoveBits;
	}

	if (StateFillStyle0)
	{
		// TODO: not in documentation
		BYTE FillBits : 5;
		BYTE FillStyle0 : FillBits;
		BYTE FillStyle1 : FillBits;
	}

	if (StateLineStyle)
	{
		// TODO: not in documentation
		BYTE LineBits : 5;
		BYTE LineStyle : LineBits;
	}

	if (StateNewStyles)
	{
		FILLSTYLEARRAY fill_styles;
		LINESTYLEARRAY line_styles;
		BYTE num_fill_bits : 4;
		BYTE num_line_bits : 4;
	}
};

struct SHAPEWITHSTYLE
{
	FILLSTYLEARRAY fill_styles;
	LINESTYLEARRAY line_style;
	BYTE			NumFillBits : 4;
	BYTE			NumLineBits : 4;
	SHAPERECORD		ShapeRecords[*];
};

struct SHAPE
{
	BYTE NumFillBits : 4;
	BYTE NumLineBits : 4;
	SHAPERECORD shapes[*];
};

// TODO: p.143 - gradients,bitmaps,shape morphing,font and text
public struct SWF_File
{
	SWFHeader header;
	if (header.compression == Uncompressed)
	{

	}
	else
	{
		var nDocSize = GetDocumentSize();
		BYTE compressed_data[nDocSize - sizeof(header)];
	}
};
