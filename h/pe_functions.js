// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

/*
*	These functions are used by pe.h and pe_resources.h files
*   1.Don't forget to explicitly cast resturn values in your .h files
*   for example: var x = int(RvaToPaBiased(my_offset))
*
*   2.Even if you don't want to get/save return value - you have to 
*   declare variable in .h file
*   for example:   

valid         - var not_used_any_more = MyFunction();
invalid      -  MyFunction();
*/

var DataDirectory = [];          // dynamic array
var Sections = [];          // dynamic array

var MachineType = 0;          // x86/x64
var ImageOffset = 0;

// Report a session offset and size
function AddSection(va_, size_, pa_)
{
	if (va_ && size_ && pa_)
		Sections.push({ va: va_, size: size_, pa: pa_ });

	return 0;
}

// MachineType getter/setter
function GetMachineType()
{
	return MachineType;
}

function SetMachineType(b)
{
	MachineType = b;
	return 0;
}

// Relative Virtual Address to Physical Address translation (address in raw file BEFORE mapping by loader)
function RvaToPa(rva)
{
	if (!rva)
		return -1;
	for (var i = 0; i < Sections.length; ++i)
	{
		if (rva >= Sections[i].va && rva < Sections[i].va + Sections[i].size)
			return (rva - Sections[i].va) + Sections[i].pa;
	}
	return -1;
}

// when you use pointers within sview definition files
// you use something like this: 
// DWORD MyOwnData as StructureType* (int(RvaToPa(MyOwnData)) - MyOwnData);
// because MyOwnData valued will be used as base (expression inside brackets is added to it)

// If an absolute address is required, we need to subtract a base
// ...
// For convenience we introduced RvaToPaBiased that could be used just like this:
// DWORD MyOwnData as StructureType* (int(RvaToPaBiased(MyOwnData)));
// 
function RvaToPaBiased(rva)
{
	return (RvaToPa(rva) - rva);
}

// ImageOffset setter
function SetVirtualBase(base)
{
	ImageOffset = base;
}

// absolute virtual address
function VaToPa(va)
{
	if (!ImageOffset)
		return 0;
	var x = va - ImageOffset;
	return RvaToPa(x);
}

function VaToPaBiased(va)
{
	if (!ImageOffset)
		return 0;

	return VaToPa(va) - va;
}

// Report data directory offset and size
function SetDataDirectory(id, off_, sz_)
{
	DataDirectory[id] = { off: off_, sz: sz_ };
	return 0;
}

function GetDataDirectoryOffset(id)
{
	return DataDirectory[id].off;
}

function GetDataDirectorySize(id)
{
	return DataDirectory[id].sz;
}
