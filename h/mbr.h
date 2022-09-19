// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"

enum PartitionStatus : BYTE
{
	StatusBootable = 0,
	StatusNonBootable = 128
};

// 16 bytes total
struct PartitionRecord
{
	PartitionStatus status;

	BYTE begin_head;
	BYTE begin_sector; // sector is in bits 5–0; bits 9–8 of cylinder are in bits 7–6
	BYTE begin_cylinder; // bits 7–0 of cylinder

	var nSectorBeginVal = (begin_sector & 0x3f); // 0x3f is 00111111b
	var nCylinderBeginVal = ((begin_sector >> 6) << 8) | (begin_cylinder); // here shr and shl like this used for clarity
	$print("SectorBegin=", nSectorBeginVal);
	$print("CylinderBegin=", nCylinderBeginVal);

	BYTE partition_type;

	BYTE end_head;
	BYTE end_sector; // sector is in bits 5–0; bits 9–8 of cylinder are in bits 7–6
	BYTE end_cylinder; // bits 7–0 of cylinder

	var nSectorEndVal = (end_sector & 0x3f); // 0x3f is 00111111b
	var nCylinderEndVal = ((end_sector >> 6) << 8) | (end_cylinder); // here shr and shl like this used for clarity
	$print("SectorEnd=", nSectorEndVal);
	$print("CylinderBegin=", nCylinderEndVal);

	DWORD lba_of_first_sector;
	DWORD num_of_sectors;
};

// total 512 bytes
public struct MBR
{
	BYTE code_area[440]; // warning: maximum code area is 446!!!
	DWORD disk_signature; // this field is optional - it could be used as code
	USHORT reserved; // this field is optional - it could be used as code

	PartitionRecord primary_partitions[4];

	BYTE mbr_signature[2];
	$assert(mbr_signature[0] == 0x55 && mbr_signature[1] == 0xAA, "Hex editor is unable to parse MBR: signature is wrong");
};
