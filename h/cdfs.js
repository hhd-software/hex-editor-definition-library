// Copyright (c) 2021-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
var PathsLastOffset = 0;
var PathsTableEntries = 0;
var PathsDirectoryExchageId = 0;

function SetPathsLastOffset(b)
{
	PathsLastOffset = b;
}

function GetPathsLastOffset()
{
	return PathsLastOffset;
}

function SetPathsTableEntries(b)
{
	PathsTableEntries = b;
}

function GetPathsTableEntries()
{
	return PathsTableEntries;
}


function SetDirectoryId(b)
{
	PathsDirectoryExchageId = b;
}

function GetDirectoryId()
{
	return PathsDirectoryExchageId;
}
