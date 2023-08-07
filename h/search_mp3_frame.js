// Copyright (c) 2015-2023 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor
// For usage and distribution policies, consult the license distributed with a product installation program

// JScript source code

// find next MPEG frame by searching for marker
// parameter: current offset to start searching from
function JS_SearchForMpegFrame(offset_start)
{
	var sel = document.CreateEmptySelection();
	sel.AddRange(0, document.FileSize);

	do
	{
		var out = document.Find([0, 0xff], sel, offset_start, false, true);

		var seq_aux = document.Read(out + 1, 1);

		var byte_to_check = seq_aux[0];
		if (byte_to_check & 0xE0)
		{
			// it's a marker!
			return out;
		}
	} while (false);

	return -1;
}
