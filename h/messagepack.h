// Copyright (c) 2021-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include <stddefs.h>
#pragma byte_order(BigEndian)

enum ETagType : BYTE
{
	Fixmap = 0x80,
	Fixarray = 0x90,
	Fixstr = 0xa0,

	Nil = 0xc0,
	Unused = 0xc1,
	False = 0xc2,
	True = 0xc3,
	Bin8 = 0xc4,
	Bin16 = 0xc5,
	Bin32 = 0xc6,
	Ext8 = 0xc7,
	Ext16 = 0xc8,
	Ext32 = 0xc9,
	Float32 = 0xca,
	Float64 = 0xcb,
	Uint8 = 0xcc,
	Uint16 = 0xcd,
	Uint32 = 0xce,
	Uint64 = 0xcf,
	Int8 = 0xd0,
	Int16 = 0xd1,
	Int32 = 0xd2,
	Int64 = 0xd3,
	Fixext1 = 0xd4,
	Fixext2 = 0xd5,
	Fixext4 = 0xd6,
	Fixext8 = 0xd7,
	Fixext16 = 0xd8,
	Str8 = 0xd9,
	Str16 = 0xda,
	Str32 = 0xdb,
	Array16 = 0xdc,
	Array32 = 0xdd,
	Map16 = 0xde,
	Map32 = 0xdf
};

[display(str)]
struct DataString
{
	union
	{
		BYTE bfType : 3;
		BYTE Length : 5;
	} bType;

	char str[bType.Length];
};

[display(str)]
struct DataString8
{
	BYTE bType;
	BYTE nLength;

	char str[nLength];
};

[display(str)]
struct DataString16
{
	BYTE bType;
	WORD nLength;

	char str[nLength];
};

[display(str)]
struct DataString32
{
	BYTE bType;
	DWORD nLength;

	char str[nLength];
};

struct DataObject;

[display(Name)]
union DataFieldName
{
hidden:
	BYTE bType;
visible:
	var Name = "";

	if (bType | Fixstr)
	{
		DataString Value;
		Name = Value.str;
	}
	else
	{
		switch (bType)
		{
		case Str8:
			DataString8 Value;
			Name = Value.str;
			break;
		case Str16:
			DataString16 Value;
			Name = Value.str;
			break;
		case Str32:
			DataString32 Value;
			Name = Value.str;
			break;
		}
	}
};

struct DataField
{
	DataFieldName name;
	DataObject value;
};

struct MapObject
{
	union
	{
		BYTE bfType : 4;
		BYTE Length : 4;
	} bType;

	DataField fields[bType.Length];
};

struct Map16Object
{
	BYTE bType;
	WORD nLength;

	DataField fields[nLength];
};

struct Map32Object
{
	BYTE bType;
	DWORD nLength;

	DataField fields[nLength];
};

struct ArrayObject
{
	union
	{
		BYTE bfType : 4;
		BYTE Length : 4;
	} bType;

	DataObject elements[bType.Length];
};

struct Array16Object
{
	BYTE bType;
	WORD nLength;

	DataObject elements[nLength];
};

struct Array32Object
{
	BYTE bType;
	DWORD nLength;

	DataObject elements[nLength];
};

[display(Value)]
struct SimpleObject
{
	ETagType Type;

	switch (Type)
	{
	case Bin8:
		BYTE Length;
		BYTE Value[Length];
		break;
	case Bin16:
		WORD Length;
		BYTE Value[Length];
		break;
	case Bin32:
		DWORD Length;
		BYTE Value[Length];
		break;
	case Ext8:
		BYTE Length;
		char Type;
		BYTE Value[Length];
		break;
	case Ext16:
		WORD Length;
		char Type;
		BYTE Value[Length];
		break;
	case Ext32:
		DWORD Length;
		char Type;
		BYTE Value[Length];
		break;
	case Float32:
		float Value;
		break;
	case Float64:
		double Value;
		break;
	case Uint8:
		BYTE Value;
		break;
	case Uint16:
		WORD Value;
		break;
	case Uint32:
		DWORD Value;
		break;
	case Uint64:
		QWORD Value;
		break;
	case Int8:
		char Value;
		break;
	case Int16:
		short Value;
		break;
	case Int32:
		int Value;
		break;
	case Int64:
		long Value;
		break;
	case Fixext1:
		char Type;
		BYTE Value;
		break;
	case Fixext2:
		char Type;
		BYTE Value[2];
		break;
	case Fixext4:
		char Type;
		BYTE Value[4];
		break;
	case Fixext8:
		char Type;
		BYTE Value[8];
		break;
	case Fixext16:
		char Type;
		BYTE Value[16];
		break;
	default:
		var Value = "Unknown object data type";
	}
};

[display(Value)]
union DataObject
{
//hidden:
	ETagType Tag;
visible:
	switch (Tag)
	{
	case Nil:
		var Value = 0;
		break;
	case Unused:
		break;
	case False:
		var Value = "false";
		break;
	case True:
		var Value = "true";
		break;
	case Str8:
		DataString8 Value;
		break;
	case Str16:
		DataString16 Value;
		break;
	case Str32:
		DataString32 Value;
		break;
	case Array16:
		Array16Object Value;
		break;
	case Array32:
		Array32Object Value;
		break;
	case Map16:
		Map16Object object;
		break;
	case Map32:
		Map32Object object;
		break;
	default:
		if (Tag <= 0x7f)
		{
			var Value = Tag;
		}
		else if (Tag >= 0xe0)
		{
			var Value = Tag & 0x1f;
		}
		else if ((Tag & 0xF0) == Fixmap)
		{
			MapObject object;
		}
		else if ((Tag & 0xF0) == Fixarray)
		{
			ArrayObject Value;
		}
		else if ((Tag & 0xF0) == Fixstr)
		{
			DataString Value;
		}
		else
		{
			SimpleObject Value;
		}
	}
};

public struct MessagePack
{
	DataObject objects;
};
