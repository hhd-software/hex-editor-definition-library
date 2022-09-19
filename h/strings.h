// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file

struct CStringCharA
{
	char c;
	if (c == 0)
		$break_array(true);
};

union CStringA
{
hidden:
	CStringCharA string_lowlevel[*];
visible:
	char string[sizeof(string_lowlevel) - 1];
};

struct CStringCharW
{
	wchar_t c;
	if (c == 0)
		$break_array(true);
};

union CStringW
{
hidden:
	CStringCharW string_lowlevel[*];
visible:
	wchar_t string[sizeof(string_lowlevel) / sizeof(wchar_t) - 1];
};
