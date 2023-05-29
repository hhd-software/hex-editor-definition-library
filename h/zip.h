// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include "stddefs.h"

/*
	Overall .ZIP file format:

	[local file header 1]
	[file data 1]
	[data descriptor 1]
	.
	.
	.
	[local file header n]
	[file data n]
	[data descriptor n]
	[archive decryption header]
	[archive extra data record]
	[central directory]
	[zip64 end of central directory record]
	[zip64 end of central directory locator]
	[end of central directory record]
*/

enum ZIP_CompressionType<USHORT> {
	COMP_STORED = 0,
	COMP_SHRUNK = 1,
	COMP_REDUCED1 = 2,
	COMP_REDUCED2 = 3,
	COMP_REDUCED3 = 4,
	COMP_REDUCED4 = 5,
	COMP_IMPLODED = 6,
	COMP_TOKEN = 7,
	COMP_DEFLATE = 8,
	COMP_DEFLATE64 = 9,
	COMP_PKWARE = 10,
	COMP_PKWARE_RESERVED = 11,
	COMP_BZIP2 = 12,
	COMP_PKWARE_RESERVED2 = 13,
	COMP_LZMA = 14,
	COMP_PKWARE_RESERVED3 = 15,
	COMP_PKWARE_RESERVED4 = 16,
	COMP_PKWARE_RESERVED5 = 17,
	COMP_IBM_TERSE = 18,
	COMP_IBM_LZ77 = 19,
	COMP_PPMD = 98
};

union DOSDATE
{
	WORD word;

	struct PackedDosDate
	{
		WORD day : 5;		// 1-31
		WORD month : 4;	// 1 = January, 2 = February ...
		WORD year : 7;	// Year offset from 1980
	} packed;
};

union DOSTIME
{
	WORD word;

	struct PackedDosTime
	{
		WORD second : 5;	// second divided by 2!
		WORD minute : 6;  // 0-59
		WORD hour : 5;	// 0-23
	} packed;
};

union ZIP_GeneralPurpsFlags
{
	WORD word;

	struct PackedFlags
	{
		BYTE b0 : 1;
		BYTE b1 : 1;
		BYTE data_descriptor_avail : 1;
		BYTE b3 : 1;
		BYTE b4 : 1;
		BYTE b5 : 1;
		BYTE b6 : 1;
		BYTE b7 : 1;

		BYTE b8 : 1;
		BYTE b9 : 1;
		BYTE b10 : 1;
		BYTE b11 : 1;
		BYTE b12 : 1;
		BYTE b13 : 1;
		BYTE b14 : 1;
		BYTE b15 : 1;
	} packed;
};

enum ZIP_ExtraFieldEnum<USHORT>
{
	FIELD_Zip64Extra = 1,
	FIELD_AVInfo = 7,
	FIELD_PFS = 8,
	FIELD_OS2 = 9,
	FIELD_NTFS = 0xa,
	FIELD_OpenVMS = 0xc,
	FIELD_UNIX = 0xd,
	FIELD_FileStreamAndForkDesc = 0xe,
	FIELD_Patch = 0xf,
	FIELD_PKCS7 = 0x14,
	FIELD_X509_IndividualFile = 0x15,
	FIELD_X509_CentralDirectory = 0x16,
	FIELD_StrongEncryptionHeader = 0x17,
	FIELD_RecordManagementControls = 0x18,
	FIELD_PKCS7_EncrRecipient = 0x19,
	FIELD_MVS = 0x65,
	FIELD_IBM_S390_AS400 = 0x66,
	FIELD_POSZIP4690 = 0x4690,
	FIELD_Mac = 0x7c8,
	FIELD_ZipItMac = 0x2605,
	FIELD_ZipItMac135 = 0x2705,
	FIELD_ZipItMac135_ = 0x2805,
	FIELD_InfoZipMac = 0x334d,
	FIELD_Acorn = 0x4341,
	FIELD_WinNT_ACL = 0x4453,
	FIELD_VM_CMS = 0x4704,
	FIELD_MVS = 0x470f,
	FIELD_FWKCS_MD5 = 0x4b46,
	FIELD_OS2_ACL = 0x4c41,
	FIELD_InfoZIP_OpenVMS = 0x4d49,
	FIELD_AOS_VS_ACL = 0x5356,
	FIELD_ExtendedTimestamp = 0x5455,
	FIELD_Xceed = 0x554e,
	FIELD_InfoZip_UNIX = 0x5855,
	FIELD_BeOS_BeBox = 0x6542,
	FIELD_ASI_UNIX = 0x756e,
	FIELD_InfoZIP_UNIX_New = 0x7855,
	FIELD_MicrosoftOpenPackaging = 0xa220,
	FIELD_SMS_QDOS = 0xfd4a,
};

struct ZIP_64Extra
{
	QWORD compressed_size;
	QWORD offset;
	UINT	disk_start_number;
};

struct ZIP_Os2Extra
{
	UINT	uncompressed_block_size;
	USHORT compression_type;
	UINT	crc;

	// TODO: please check the definition of this field's size!!! it seems like this is COMPRESSED block
	// but size for UNCOMPRESSED block used :-( so we will fix this problem
	BYTE	block[/*uncompressed_block_size*/compression_type];
};

struct ZIP_NTFSExtra
{
	UINT reserved;

	[noindex] struct ZIP_NTFSExtraAttribute
	{
		if (SizeLeft <= 0)
			$break_array(false);

		USHORT tag;
		USHORT size;
		BYTE extra_attrib_data[size];

		SizeLeft = SizeLeft - sizeof(reserved) - sizeof(tag) - sizeof(size) - size;
	} attributes[*];
};

// same
typedef ZIP_NTFSExtra ZIP_OpenVMSExtra;

struct ZIP_UNIXExtra
{
	UINT	last_access_time;
	UINT	last_modification_time;
	USHORT file_user_id;
	USHORT file_group_id;

	BYTE	extra_data[data_size - sizeof(last_access_time)
		- sizeof(last_modification_time)
		- sizeof(file_user_id)
		- sizeof(file_group_id)];
};

struct ZIP_PatchExtra
{
	USHORT version;
	UINT	flags;

	UINT	old_size;
	UINT	old_crc;

	UINT	new_size;
	UINT	new_crc;
};

struct ZIP_PKCS7Extra
{
	BYTE data_to_store[data_size];
};

struct ZIP_X509Extra
{
	BYTE signature[data_size];
};

struct ZIP_StrongEncryptionExtra
{
	USHORT format;
	USHORT alg_id;
	USHORT bit_len;
	USHORT flags;

	BYTE	cert_data[data_size - 8];
};

typedef ZIP_NTFSExtra ZIP_RecordManControlsExtra;

struct ZIP_PKCS7ERExtra
{
	USHORT version;		// should be 1
	BYTE data[data_size - 2];
};

struct ZIP_MVSExtra
{
	UINT id;
	BYTE data[data_size - 4];
};

struct ZIP_ZipItMacExtra
{
	UINT extra_signature;				// ZPIT
	BYTE filename_len;
	char filename[filename_len];
	BYTE filetype[4];
	BYTE creator[4];
};

struct ZIP_ZipItMac135Extra
{
	UINT extra_signature;				// ZPIT
	BYTE filetype[4];
	BYTE creator[4];
	USHORT flags;
	USHORT reserved;
};

struct ZIP_ZipItMac135_Extra
{
	UINT	extra_signature;				// ZPIT
	USHORT flags;
	USHORT view;
};

struct ZIP_FWKCS_MD5Extra
{
	BYTE preface[3];
	BYTE md5_hash[16];
};

struct ZIP_MSOpenPackagingExtra
{
	USHORT sig;
	USHORT pad_value;
	BYTE padding[data_size - 4];
};


// generic
struct EXTRA_FIELD
{
	ZIP_ExtraFieldEnum header_id;
	USHORT data_size;

	switch (header_id)
	{
	case FIELD_Zip64Extra:
		ZIP_64Extra data;
		break;
	case FIELD_OS2:
		ZIP_Os2Extra data;
		break;
	case FIELD_NTFS:
		var SizeLeft = data_size;
		ZIP_NTFSExtra data;
		break;
	case FIELD_OpenVMS:
		ZIP_OpenVMSExtra data;
		break;
	case FIELD_UNIX:
		ZIP_UNIXExtra data;
		break;
	case FIELD_Patch:
		ZIP_PatchExtra data;
		break;
	case FIELD_PKCS7:
		ZIP_PKCS7Extra data;
		break;
	case FIELD_X509_IndividualFile:
		ZIP_X509Extra data;
		break;
	case FIELD_StrongEncryptionHeader:
		ZIP_StrongEncryptionExtra data;
		break;
	case FIELD_RecordManagementControls:
		ZIP_RecordManControlsExtra data;
		break;
	case FIELD_PKCS7_EncrRecipient:
		ZIP_PKCS7ERExtra data;
		break;
	case FIELD_MVS:
		ZIP_MVSExtra data;
		break;
	case FIELD_ZipItMac:
		ZIP_ZipItMacExtra	data;
		break;
	case FIELD_ZipItMac135:
		ZIP_ZipItMac135Extra data;
		break;
	case FIELD_ZipItMac135_:
		ZIP_ZipItMac135_Extra data;
		break;
	case FIELD_FWKCS_MD5:
		ZIP_FWKCS_MD5Extra data;
		break;
	case FIELD_MicrosoftOpenPackaging:
		ZIP_MSOpenPackagingExtra data;
		break;
	default:
		BYTE data[data_size];
	}

	$assert(sizeof(data) == data_size, "Invalid data size of EXTRA_FIELD");
};

struct LOCAL_FILE_HEADER
{
	USHORT version;
	ZIP_GeneralPurpsFlags flags;
	ZIP_CompressionType compression;

	DOSTIME file_time;
	DOSDATE file_date;

	UINT crc;
	UINT compressed_size;
	UINT uncompressed_size;
	USHORT filename_len;
	USHORT extra_field_len;

	char filename[filename_len];

	if (extra_field_len >= 4)
	{
		EXTRA_FIELD extra_field;
		$assert(sizeof(extra_field) == extra_field_len, "Invalid ZIP format: size of extra field is wrong");
	}
};

struct FILE_DATA_DESCRIPTOR
{
	// so called "data descriptor"
	UINT data_crc;
	UINT data_compressed_size;
	UINT data_unncompressed_size;
};

struct ARCHIVE_EXTRA_DATA_RECORD
{
	UINT extra_len;
	BYTE extra[extra_len];
};

enum VersionMadeByEnum<BYTE>
{
	VERSION_MSDOS_OS2 = 0,			// MS-DOS and OS/2 (FAT / VFAT / FAT32 file systems)
	VERSION_AMIGA,
	VERSION_OPEN_VMS,
	VERSION_UNIX,
	VERSION_VM_CMS,
	VERSION_ATARI_ST,
	VERSION_OS2_HPFS,
	VERSION_MAC,
	VERSION_Z_SYSTEM,
	VERSION_CPM,
	VERSION_WINDOWS_NTFS,
	VERSION_MVS,
	VERSION_VSE,
	VERSION_ACORN,
	VERSION_VFAT,
	VERSION_MVS_ALTERNATE,
	VERSION_BEOS,
	VERSION_TANDEM,
	VERSION_OS_400,
	VERSION_OS_X
};

struct VersionMadeBy
{
	BYTE zip_specification;
	VersionMadeByEnum version;
};

struct CENTRAL_DIRECTORY
{
	VersionMadeBy version_made_by;
	USHORT version_to_extract;
	USHORT flags;
	ZIP_CompressionType deCompression;

	DOSTIME deFileTime;
	DOSDATE deFileDate;

	UINT crc;
	UINT compressed_size;
	UINT uncompressed_size;
	USHORT filename_len;
	USHORT extra_field_len;
	USHORT file_comment_len;
	USHORT disk_number_start;
	USHORT internal_attributes;
	UINT external_attributes;
	UINT header_offset;

	char filename[filename_len];
	if (extra_field_len >= 4)
	{
		EXTRA_FIELD extra_field;
		$assert(sizeof(extra_field) == extra_field_len, "Invalid ZIP format: size of extra field is wrong");
	}
	BYTE file_comment[file_comment_len];
};

struct DIGITAL_SIGNATURE
{
	USHORT data_len;
};

struct CENTRAL_DIRECTORY_END
{
	USHORT disk_number;							// number of this disk

	USHORT start_disk_number;						// number of the disk with the
													// start of the central directory

	USHORT entries_on_disk;						// total number of entries in the
													// central directory on this disk

	USHORT entries_in_directory;					//  total number of entries in
													// the central directory

	UINT directory_size;
	UINT offset;
	USHORT comment_len;

	BYTE comment[comment_len];
};

// version 1 (no Strong Encryption Specification)
struct CENTRAL_DIRECTORY_END64		// zip64
{
	QWORD size;				// size = SizeOfFixedFields + SizeOfVariableData - 12.
	USHORT version_made_by;
	USHORT version_to_extract;

	UINT disk_number;
	UINT disk_number_with_start_of_cd;		// number of the disk with the
													// start of the central directory

	QWORD cd_entries_number_on_disk;			// total number of entries in the
													// central directory on this disk

	QWORD cd_entries_number;					// total number of entries in the
													// central directory

	QWORD cd_size;							// size of central directory

	QWORD cd_offset;							// offset of start of central
													// directory with respect to
													// the starting disk number

	$assert(size >= 44, "Invalid ZIP format: zip64 CENTRAL_DIRECTORY_END structure's size is wrong");
	BYTE zip64_extensible_data_sector[size - 44];
};

struct CENTRAL_DIRECTORY_LOCATOR_END64
{
	UINT number_of_disk;						// number of the disk with the
													// start of the zip64 end of
													// central directory

	QWORD offset;								// relative offset of the zip64
													// end of central directory record

	UINT disk_total_number;					// total number of disks
};

struct ZipFileBlockInternal
{
	union Signature
	{
		UINT as_uint;
		char as_chars[4];
	} signature;

	switch (signature.as_uint)
	{
	case 0x04034b50:			// local file header
		LOCAL_FILE_HEADER		file_header;
		BYTE					compressed_data[file_header.compressed_size];

		if (file_header.flags.packed.data_descriptor_avail)
			FILE_DATA_DESCRIPTOR	data_descriptor;
		break;
	case 0x08064b50:			// archive extra data record
		ARCHIVE_EXTRA_DATA_RECORD   archive_extra;
		break;
	case 0x02014b50:			// central directory
		CENTRAL_DIRECTORY central_directory;
		break;
	case 0x05054b50:			// digital signature
		DIGITAL_SIGNATURE digital_sig;
		break;
	case 0x06054b50:			// end of central directory (32 bit)
		CENTRAL_DIRECTORY_END	central_directory_end;
		break;
	case 0x06064b50:			// end of central directory (64 bit)
		CENTRAL_DIRECTORY_END64	central_directory_end;
		break;
	case 0x07064b50:			// end of central directory locator
		CENTRAL_DIRECTORY_LOCATOR_END64 central_directory_end_locator;
		break;
	}
};

[display(evaluate_if(block.file_header.filename, block.central_directory.filename))]
struct ZipFileBlock
{
	if (DocumentSizeLeft <= 0)
		$break_array(false);

	ZipFileBlockInternal block;

	DocumentSizeLeft = DocumentSizeLeft - sizeof(block);
};

// array of
#pragma script("get_doc_size.js")

public struct ZipFile
{
	var DocumentSizeLeft = GetDocumentSize();
	[noindex] ZipFileBlock blocks[*];
};
