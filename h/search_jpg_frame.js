// Copyright (c) 2015-2023 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor
// For usage and distribution policies, consult the license distributed with a product installation program

// JScript source code

// find next JPEG frame by searching for marker
// parameter: current offset to start searching from
// frames are started with 0xff
function JS_SearchForJpegFrame(offset_start)
{
	var seq_search_me = document.CreateSequence();
	seq_search_me.AddData(0, 0xff);

	var sel = document.CreateEmptySelection();
	sel.AddRange(0, document.FileSize);

	var out = document.Find(seq_search_me, sel, offset_start, false, true);
	return out;
}