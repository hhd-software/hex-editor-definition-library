// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#pragma pack(1)

#include "stddefs.h"

// PE Header uses Little Endian byte order
#pragma byte_order(LittleEndian)

// connect to helper script
#pragma script("pe_functions.js")

// Part of definition is in another file
#include "pe_resources.h"				// includes bitmap.h

// Directory Entries
enum
{
	IMAGE_DIRECTORY_ENTRY_EXPORT = 0,   // Export Directory
	IMAGE_DIRECTORY_ENTRY_IMPORT = 1,   // Import Directory
	IMAGE_DIRECTORY_ENTRY_RESOURCE = 2,   // Resource Directory
	IMAGE_DIRECTORY_ENTRY_EXCEPTION = 3,   // Exception Directory
	IMAGE_DIRECTORY_ENTRY_SECURITY = 4,   // Security Directory
	IMAGE_DIRECTORY_ENTRY_BASERELOC = 5,   // Base Relocation Table
	IMAGE_DIRECTORY_ENTRY_DEBUG = 6,   // Debug Directory
	IMAGE_DIRECTORY_ENTRY_ARCHITECTURE = 7,   // Architecture Specific Data
	IMAGE_DIRECTORY_ENTRY_GLOBALPTR = 8,   // RVA of GP
	IMAGE_DIRECTORY_ENTRY_TLS = 9,   // TLS Directory
	IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG = 10,   // Load Configuration Directory
	IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT = 11,   // Bound Import Directory in headers
	IMAGE_DIRECTORY_ENTRY_IAT = 12,   // Import Address Table
	IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT = 13,   // Delay Load Import Descriptors
	IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR = 14,   // COM Runtime descriptor
};

// Supported architecture types
enum ArchitectureType : WORD
{
	IMAGE_FILE_MACHINE_UNKNOWN = 0,
	IMAGE_FILE_MACHINE_I386 = 0x014c,	// Intel 386.
	IMAGE_FILE_MACHINE_R3000 = 0x0162,	// MIPS little-endian, 0x160 big-endian
	IMAGE_FILE_MACHINE_R4000 = 0x0166,	// MIPS little-endian
	IMAGE_FILE_MACHINE_R10000 = 0x0168,	// MIPS little-endian
	IMAGE_FILE_MACHINE_WCEMIPSV2 = 0x0169,	// MIPS little-endian WCE v2
	IMAGE_FILE_MACHINE_ALPHA = 0x0184,	// Alpha_AXP
	IMAGE_FILE_MACHINE_SH3 = 0x01a2,	// SH3 little-endian
	IMAGE_FILE_MACHINE_SH3DSP = 0x01a3,
	IMAGE_FILE_MACHINE_SH3E = 0x01a4,	// SH3E little-endian
	IMAGE_FILE_MACHINE_SH4 = 0x01a6,	// SH4 little-endian
	IMAGE_FILE_MACHINE_SH5 = 0x01a8,	// SH5
	IMAGE_FILE_MACHINE_ARM = 0x01c0,	// ARM Little-Endian
	IMAGE_FILE_MACHINE_THUMB = 0x01c2,	// ARM Thumb/Thumb-2 Little-Endian
	IMAGE_FILE_MACHINE_ARMNT = 0x01c4,	// ARM Thumb-2 Little-Endian
	IMAGE_FILE_MACHINE_AM33 = 0x01d3,
	IMAGE_FILE_MACHINE_POWERPC = 0x01F0,	// IBM PowerPC Little-Endian
	IMAGE_FILE_MACHINE_POWERPCFP = 0x01f1,
	IMAGE_FILE_MACHINE_IA64 = 0x0200,	// Intel 64
	IMAGE_FILE_MACHINE_MIPS16 = 0x0266,	// MIPS
	IMAGE_FILE_MACHINE_ALPHA64 = 0x0284,	// ALPHA64
	IMAGE_FILE_MACHINE_MIPSFPU = 0x0366,	// MIPS
	IMAGE_FILE_MACHINE_MIPSFPU16 = 0x0466,	// MIPS
	IMAGE_FILE_MACHINE_AXP64 = IMAGE_FILE_MACHINE_ALPHA64,
	IMAGE_FILE_MACHINE_TRICORE = 0x0520,	// Infineon
	IMAGE_FILE_MACHINE_CEF = 0x0CEF,
	IMAGE_FILE_MACHINE_EBC = 0x0EBC,	// EFI Byte Code
	IMAGE_FILE_MACHINE_AMD64 = 0x8664,	// AMD64 (K8)
	IMAGE_FILE_MACHINE_M32R = 0x9041,	// M32R little-endian
	IMAGE_FILE_MACHINE_ARM64 = 0xAA64,	// ARM64 Little-Endian
	IMAGE_FILE_MACHINE_CEE = 0xC0EE,
};

// Image Characteristics flags
enum ImageCharacteristicsType : WORD
{
	IMAGE_FILE_RELOCS_STRIPPED = 0x0001,
	IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002,
	IMAGE_FILE_LINE_NUMS_STRIPPED = 0x0004,
	IMAGE_FILE_LOCAL_SYMS_STRIPPED = 0x0008,
	IMAGE_FILE_AGGRESIVE_WS_TRIM = 0x0010,
	IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020,
	IMAGE_FILE_BYTES_REVERSED_LO = 0x0080,
	IMAGE_FILE_32BIT_MACHINE = 0x0100,
	IMAGE_FILE_DEBUG_STRIPPED = 0x0200,
	IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP = 0x0400,
	IMAGE_FILE_NET_RUN_FROM_SWAP = 0x0800,
	IMAGE_FILE_SYSTEM = 0x1000,
	IMAGE_FILE_DLL = 0x2000,
	IMAGE_FILE_UP_SYSTEM_ONLY = 0x4000,
	IMAGE_FILE_BYTES_REVERSED_HI = 0x8000,
};

// Forward declarations
struct IMAGE_FILE_HEADER;
struct IMAGE_OPTIONAL_HEADER32;
struct IMAGE_OPTIONAL_HEADER64;
struct IMAGE_SECTION_HEADER;

// IMAGE_DATA_DIRECTORY describes the entry in the DataDirectory field of IMAGE_OPTIONAL_HEADER structure
struct IMAGE_DATA_DIRECTORY
{
	DWORD VirtualAddress;
	DWORD Size;
};

struct IMAGE_IMPORT_BY_NAME
{
	WORD Hint;
	string Name;
};

[display(AddressOfData.Name)]
union IMAGE_THUNK_DATA64
{
	ULONGLONG ForwarderString;  // PBYTE
	ULONGLONG Function;         // PDWORD
	ULONGLONG Ordinal;

	// PIMAGE_IMPORT_BY_NAME
	if (Function)
	{
		if (Function & 0x80000000)
		{
			DWORD Ordinal : 31;
		}
		else
		{
			if (Bound != -1 && int(RvaToPa(Function)) > 0)
				ULONGLONG  AddressOfData as IMAGE_IMPORT_BY_NAME *(int(RvaToPaBiased(Ordinal)));
		}
	}
	else
		$break_array(true);
};

[display(AddressOfData.Name)]
union IMAGE_THUNK_DATA32
{
	DWORD Function;             // PDWORD

	// PIMAGE_IMPORT_BY_NAME
	if (Function)
	{
		if (Function & 0x80000000)
		{
			DWORD Ordinal : 31;
		}
		else
		{
			if (int(RvaToPa(Function)) > 0)
			{
				if (Bound != -1)
					DWORD  AddressOfData as IMAGE_IMPORT_BY_NAME *(int(RvaToPaBiased(AddressOfData)));
				else
				{
					//DWORD  AddressOfData as IMAGE_IMPORT_BY_NAME *(int(RvaToPaBiased(AddressOfData)));
				}
			}
		}
	}
	else
		$break_array(true);
};

struct IMAGE_THUNK_DATA64ARRAY
{
	[noindex] IMAGE_THUNK_DATA64 arr[*];
};

struct IMAGE_THUNK_DATA32ARRAY
{
	[noindex] IMAGE_THUNK_DATA32 arr[*];
};

struct FUNCTION_ADDRESS_TABLE
{
	[noindex] union
	{
		DWORD Rva;

		if (Rva)
		{
			var va = int(RvaToPa(Rva));

			if (va >= GetDataDirectoryOffset(IMAGE_DIRECTORY_ENTRY_EXPORT)
				&& va < GetDataDirectoryOffset(IMAGE_DIRECTORY_ENTRY_EXPORT) + GetDataDirectorySize(IMAGE_DIRECTORY_ENTRY_EXPORT))
			{
				// forwarded!!!
				DWORD ForwardedTo as StringWrapper *(int(RvaToPaBiased(ForwardedTo)));
			}
			else
			{
				DWORD FunctionBody as DWORD *(int(RvaToPaBiased(FunctionBody)));
			}
		}
	} Functions[NumberOfFunctions];
};

struct FUNCTION_NAME_TABLE
{
	[noindex] union StringArray
	{
		DWORD StringRva;
		if (StringRva)
		{
			DWORD str as StringWrapper *(int(RvaToPaBiased(StringRva)));
		}
	} string_rva_array[NumberOfNames];
};

struct FUNCTION_ORDINAL_TABLE
{
	USHORT array[NumberOfFunctions];
};

// Export directory
public struct IMAGE_EXPORT_DIRECTORY
{
	[color_scheme("Characteristics")] DWORD Characteristics;
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;
	[color_scheme("VerMajor")] WORD MajorVersion;
	[color_scheme("VerMinor")] WORD MinorVersion;

	union
	{
		DWORD NameRva;
		if (NameRva)
			DWORD NameString as StringWrapper *(int(RvaToPaBiased(NameRva)));
	} Name;

	DWORD OrdinalBase;
	DWORD NumberOfFunctions;
	DWORD NumberOfNames;

	union
	{
		DWORD AddressOfFunctionsRva;     // RVA from base of image
		if (AddressOfFunctionsRva)
			DWORD functions as FUNCTION_ADDRESS_TABLE *(int(RvaToPaBiased(AddressOfFunctionsRva)));
	} AddressOfFunctions;

	union
	{
		DWORD AddressOfNamesRva;         // RVA from base of image
		if (AddressOfNamesRva)
			DWORD names as FUNCTION_NAME_TABLE *(int(RvaToPaBiased(AddressOfNamesRva)));
	} AddressOfNames;

	union
	{
		DWORD AddressOfNameOrdinalsRva;  // RVA from base of image
		if (AddressOfNameOrdinalsRva)
			DWORD ordinals as FUNCTION_ORDINAL_TABLE *(int(RvaToPaBiased(AddressOfNameOrdinalsRva)));
	} AddressOfNameOrdinals;
};

struct StringWrapper
{
	string value;
};

struct WTStringWrapper
{
	WORD Size;
	wchar_t value[Size];
};

enum TimeDateStamp : DWORD
{
	NotBound = 0,
	BoundNew = -1,
	BoundOld = 1,
};

[display(Name.NameString.value)]
struct IMAGE_IMPORT_DIRECTORY
{
	if (ImportDirSize <= 0)
		$break_array(false);

	union
	{
		[color_scheme("Characteristics")] DWORD Characteristics;            // 0 for terminating null import descriptor

		if (Characteristics)
		{
			if (int(GetMachineType()) == IMAGE_FILE_MACHINE_I386)
				DWORD   thunk as IMAGE_THUNK_DATA32ARRAY *(int(RvaToPaBiased(Characteristics)));
			else
				DWORD   thunk as IMAGE_THUNK_DATA64ARRAY *(int(RvaToPaBiased(Characteristics)));
		}
	} OriginalFirstThunk;

	[color_scheme("TimeStamp")] TimeDateStamp Bound;					// 0 if not bound,
											// -1 if bound, and real date\time stamp
											//     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
											// O.W. date/time stamp of DLL bound to (Old BIND)

	DWORD ForwarderChain;                 // -1 if no forwarders

	// Name
	union
	{
		DWORD NameRva;
		if (NameRva)
			DWORD NameString as StringWrapper *(int(RvaToPaBiased(NameRva)));
	} Name;

	// FirstThunk
	union
	{
		DWORD FirstThunkRva;                     // RVA to IAT (if bound this IAT has actual addresses)

		if (FirstThunkRva)
		{
			if (int(GetMachineType()) == IMAGE_FILE_MACHINE_I386)
				DWORD ImportAddressTable as IMAGE_THUNK_DATA32ARRAY *(int(RvaToPaBiased(FirstThunkRva)));
			else
				DWORD ImportAddressTable as IMAGE_THUNK_DATA64ARRAY *(int(RvaToPaBiased(FirstThunkRva)));
		}
	}FirstThunk;

	ImportDirSize = ImportDirSize - (current_offset - this);

	// check if this is last (terminator) IMAGE_IMPORT_DIRECTORY
	if (OriginalFirstThunk.Characteristics == 0 && Bound == 0 && ForwarderChain == 0 && Name.NameRva == 0 && FirstThunk.FirstThunkRva == 0)
		$break_array(false);
};

public struct IMAGE_IMPORT_DIRECTORY_ARRAY
{
	var ImportDirSize = int(GetDataDirectorySize(IMAGE_DIRECTORY_ENTRY_IMPORT));
	[noindex] IMAGE_IMPORT_DIRECTORY directories[*];
};

enum RelocationType : BYTE
{
	IMAGE_REL_BASED_ABSOLUTE = 0,
	IMAGE_REL_BASED_HIGH = 1,
	IMAGE_REL_BASED_LOW = 2,
	IMAGE_REL_BASED_HIGHLOW = 3,
	IMAGE_REL_BASED_HIGHADJ = 4,
	
	IMAGE_REL_BASED_MIPS_JMPADDR = 5,
	IMAGE_REL_BASED_ARM_MOV32 = 5,
	IMAGE_REL_BASED_RISCV_HIGH20 = 5,

	IMAGE_REL_BASED_THUMB_MOV32 = 7,
	IMAGE_REL_BASED_RISCV_LOW12I = 7,
	
	IMAGE_REL_BASED_RISCV_LOW12S = 8,
	IMAGE_REL_BASED_LOONGARCH32_MARK_LA = 8,
	IMAGE_REL_BASED_LOONGARCH64_MARK_LA = 8,

	IMAGE_REL_BASED_MIPS_JMPADDR16 = 9,
	IMAGE_REL_BASED_IA64_IMM64 = 9,

	IMAGE_REL_BASED_DIR64 = 10,
};

struct IMAGE_BASE_RELOCATION
{
	if (sz <= 0)
		$break_array(false);

	DWORD VirtualAddress;
	DWORD SizeOfBlock;

	var CountOfRelocations = (SizeOfBlock - 8) / sizeof(WORD);

	[noindex] struct RelocFixup
	{
	hidden:
		// bitfields!!!
		BYTE nFixupAddress;
		BYTE nType;
	visible:
		var type_ = (nType >> 4);
		switch (type_)
		{
		case IMAGE_REL_BASED_ABSOLUTE:
			$print("type", "Absolute");
			break;
		case IMAGE_REL_BASED_HIGH:
			$print("type", "High");
			break;
		case IMAGE_REL_BASED_LOW:
			$print("type", "Low");
			break;
		case IMAGE_REL_BASED_HIGHLOW:
			$print("type", "HighLow");
			break;
		case IMAGE_REL_BASED_HIGHADJ:
			$print("type", "HighAdj");
			break;
		case IMAGE_REL_BASED_MIPS_JMPADDR:
			$print("type", "MipsJmpAddr/ArmMov32/RISCV_HIGH20");
			break;
		case IMAGE_REL_BASED_THUMB_MOV32:
			$print("type", "Thumb MOVW MOVT/RISCV_LOW12I");
			break;
		case IMAGE_REL_BASED_RISCV_LOW12S:
			$print("type", "RISCV_LOW12S");
			break;
		case IMAGE_REL_BASED_IA64_IMM64:
			$print("type", "Ia64Imm64");
			break;
		case IMAGE_REL_BASED_DIR64:
			$print("type", "Dir64");
			break;
		default:
			$print("type", type_);
		}

		// warning: read documentation.
		// For example: in case of IMAGE_REL_BASED_HIGHLOW this value should be added to VirtualAddress
		$print("RealFixupAddress", nFixupAddress | ((nType & 0x0f) << 8));
	} TypeOffset[CountOfRelocations];

	sz = sz - (current_offset - this);
};

public struct IMAGE_BASE_RELOCATION_ARRAY
{
	var sz = int(GetDataDirectorySize(IMAGE_DIRECTORY_ENTRY_BASERELOC));
	var i = 0;

	[noindex] IMAGE_BASE_RELOCATION ibr[*];
};

struct IMAGE_COFF_SYMBOLS_HEADER
{
	DWORD NumberOfSymbols;
	DWORD LvaToFirstSymbol;
	DWORD NumberOfLinenumbers;
	DWORD LvaToFirstLinenumber;
	DWORD RvaToFirstByteOfCode;
	DWORD RvaToLastByteOfCode;
	DWORD RvaToFirstByteOfData;
	DWORD RvaToLastByteOfData;
};

struct IMAGE_DEBUG_MISC
{
	DWORD DataType;               // type of misc data, see defines
	DWORD Length;                 // total length of record, rounded to four
										// byte multiple.
	BYTE Unicode;                // TRUE if data is unicode string
	BYTE Reserved[3];

	BYTE Data[Length];              // Actual data
};

struct FPO_DATA
{
	DWORD ulOffStart;             // offset 1st byte of function code
	DWORD cbProcSize;             // # bytes in function
	DWORD cdwLocals;              // # bytes in locals/4
	WORD cdwParams;              // # bytes in params/4
	WORD cbProlog : 8;           // # bytes in prolog
	WORD cbRegs : 3;           // # regs saved
	WORD fHasSEH : 1;           // TRUE if SEH in func
	WORD fUseBP : 1;           // TRUE if EBP has been allocated
	WORD reserved : 1;           // reserved for future use
	WORD cbFrame : 2;           // frame type
};

enum DebugDirectoryType : DWORD
{
	IMAGE_DEBUG_TYPE_UNKNOWN = 0,
	IMAGE_DEBUG_TYPE_COFF = 1,
	IMAGE_DEBUG_TYPE_CODEVIEW = 2,
	IMAGE_DEBUG_TYPE_FPO = 3,
	IMAGE_DEBUG_TYPE_MISC = 4,
	IMAGE_DEBUG_TYPE_EXCEPTION = 5,
	IMAGE_DEBUG_TYPE_FIXUP = 6,
	IMAGE_DEBUG_TYPE_OMAP_TO_SRC = 7,
	IMAGE_DEBUG_TYPE_OMAP_FROM_SRC = 8,
	IMAGE_DEBUG_TYPE_BORLAND = 9,
	IMAGE_DEBUG_TYPE_RESERVED10 = 10,
	IMAGE_DEBUG_TYPE_CLSID = 11,
	IMAGE_DEBUG_TYPE_REPRO = 16,
	IMAGE_DEBUG_TYPE_EX_DLLCHARACTERISTICS = 20,
};

public struct IMAGE_DEBUG_DIRECTORY_DATA
{
	// use Type and SizeOfData
	switch (Type)
	{
	case IMAGE_DEBUG_TYPE_COFF:
		IMAGE_COFF_SYMBOLS_HEADER	payload;
		break;
		/*
	case IMAGE_DEBUG_TYPE_CODEVIEW:
		// CodeView debugging information. The format of the data block is
		// described by the CodeView 4.0 (pdb) specification.
		break;
		*/
	case IMAGE_DEBUG_TYPE_FPO:
		FPO_DATA payload;
		break;
	case IMAGE_DEBUG_TYPE_MISC:
		IMAGE_DEBUG_MISC			payload;
		break;
		/*
		case IMAGE_DEBUG_TYPE_EXCEPTION:

			break;
		case IMAGE_DEBUG_TYPE_FIXUP:

			break;
		case IMAGE_DEBUG_TYPE_OMAP_TO_SRC:

			break;
		case IMAGE_DEBUG_TYPE_OMAP_FROM_SRC:

			break;
		case IMAGE_DEBUG_TYPE_BORLAND:

			break;
		case IMAGE_DEBUG_TYPE_RESERVED10:

			break;
		case IMAGE_DEBUG_TYPE_CLSID:

			break;
		*/
	default:
		BYTE data[SizeOfData];
	}
};

public struct IMAGE_DEBUG_DIRECTORY
{
	[color_scheme("Characteristics")] DWORD Characteristics;
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;
	[color_scheme("VerMajor")] WORD MajorVersion;
	[color_scheme("VerMinor")] WORD MinorVersion;
	DebugDirectoryType Type;
	[color_scheme("Size")] DWORD SizeOfData;

	union
	{
		DWORD Rva;
		if (Rva)
			DWORD Data as IMAGE_DEBUG_DIRECTORY_DATA *(int(RvaToPaBiased(Rva)));
	} AddressOfRawData;

	DWORD PointerToRawData;
};

struct IMAGE_BOUND_FORWARDER_REF
{
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;

	union
	{
		WORD Rva;
		WORD Name as StringWrapper *(int(RvaToPaBiased(Name)));
	} ModuleName;

	WORD Reserved;
};

struct IMAGE_BOUND_IMPORT_DESCRIPTOR
{
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;

	union
	{
		WORD Rva;
		WORD Name as StringWrapper *(int(RvaToPaBiased(Name)));
	}ModuleName;

	WORD NumberOfModuleForwarderRefs;

	[noindex] IMAGE_BOUND_FORWARDER_REF array[NumberOfModuleForwarderRefs];
};

// WARNING: just a sample of delayed import implementation
public struct IMAGE_DELAY_IMPORT_DESCRIPTOR
{
	DWORD Attributes;			// 0 - VA / 1 - RVA

	// VAs or RVAs
	union
	{
		DWORD NameRva;
		if (NameRva)
			WORD Name as StringWrapper *(int(RvaToPaBiased(NameRva)));
	} Name;

	DWORD Module;
	DWORD IAT;
	DWORD INT;
	DWORD OptionalBoundIAT;
	DWORD OptionalCopyIAT;
	DWORD TimeStamp;				// 0 if not bound
};


// config directory
struct IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY
{
	ULONGLONG BeginAddress;
	ULONGLONG EndAddress;
	ULONGLONG ExceptionHandler;
	ULONGLONG HandlerData;
	ULONGLONG PrologEndAddress;
};

struct IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY
{
	DWORD BeginAddress;
	DWORD EndAddress;
	DWORD ExceptionHandler;
	DWORD HandlerData;
	DWORD PrologEndAddress;
};

struct IMAGE_RUNTIME_FUNCTION_ENTRY
{
	DWORD BeginAddress;
	DWORD EndAddress;
	DWORD UnwindInfoAddress;
};

struct IMAGE_CE_RUNTIME_FUNCTION_ENTRY
{
	DWORD FuncStart;
	DWORD PrologLen : 8;
	DWORD FuncLen : 22;
	DWORD ThirtyTwoBit : 1;
	DWORD ExceptionFlag : 1;
};

struct SEH_TABLE
{
	switch (int(GetMachineType()))
	{
	case IMAGE_FILE_MACHINE_I386:
		[noindex] IMAGE_RUNTIME_FUNCTION_ENTRY functions[SEHandlerCount];
		break;
	case IMAGE_FILE_MACHINE_ALPHA:
		[noindex] IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY functions[SEHandlerCount];
		break;
	case IMAGE_FILE_MACHINE_ALPHA64:
		[noindex] IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY functions[SEHandlerCount];
		break;
		// ???
	case IMAGE_FILE_MACHINE_CEE:
	case IMAGE_FILE_MACHINE_CEF:
		[noindex] IMAGE_CE_RUNTIME_FUNCTION_ENTRY functions[SEHandlerCount];
		break;
	}
};

public struct IMAGE_LOAD_CONFIG_DIRECTORY32
{
	[color_scheme("Size")] DWORD Size;
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;
	[color_scheme("VerMajor")] WORD MajorVersion;
	[color_scheme("VerMinor")] WORD MinorVersion;
	DWORD GlobalFlagsClear;
	DWORD GlobalFlagsSet;
	DWORD CriticalSectionDefaultTimeout;
	DWORD DeCommitFreeBlockThreshold;
	DWORD DeCommitTotalFreeThreshold;

	union
	{
		DWORD Va;
		if (Va)
			DWORD Table as DWORD *(int(VaToPaBiased(Table)));
	} LockPrefixTable;

	[color_scheme("Size")] DWORD   MaximumAllocationSize;
	DWORD VirtualMemoryThreshold;
	DWORD ProcessHeapFlags;
	DWORD ProcessAffinityMask;
	WORD CSDVersion;
	WORD Reserved1;

	union
	{
		DWORD Va;
		if (Va)
			DWORD List as DWORD *(int(VaToPaBiased(List)));
	} EditList;

	union
	{
		DWORD Va;
		if (Va)
			DWORD Cookie as DWORD *(int(VaToPaBiased(Cookie)));
	} SecurityCookie;

	union
	{
		DWORD Va;
		if (Va)
			DWORD Table as SEH_TABLE *(int(VaToPaBiased(Table)));
	} SEHandlerTable;

	DWORD SEHandlerCount;
};

public struct IMAGE_LOAD_CONFIG_DIRECTORY64
{
	[color_scheme("Size")] DWORD Size;
	[color_scheme("TimeStamp")] DWORD TimeDateStamp;
	[color_scheme("VerMajor")] WORD MajorVersion;
	[color_scheme("VerMinor")] WORD MinorVersion;
	DWORD GlobalFlagsClear;
	DWORD GlobalFlagsSet;
	DWORD CriticalSectionDefaultTimeout;
	ULONGLONG DeCommitFreeBlockThreshold;
	ULONGLONG DeCommitTotalFreeThreshold;
	ULONGLONG LockPrefixTable;         // VA
	[color_scheme("Size")] ULONGLONG MaximumAllocationSize;
	ULONGLONG VirtualMemoryThreshold;
	ULONGLONG ProcessAffinityMask;
	DWORD ProcessHeapFlags;
	WORD CSDVersion;
	WORD Reserved1;

	ULONGLONG EditList;                // VA
	ULONGLONG SecurityCookie;          // VA

	union
	{
		DWORD Va;
		if (Va)
			ULONGLONG Table as SEH_TABLE *(int(VaToPaBiased(Table)));
	} SEHandlerTable;

	ULONGLONG SEHandlerCount;
};

public struct IMAGE_TLS_DIRECTORY32
{
	DWORD StartAddressOfRawData;
	DWORD EndAddressOfRawData;
	DWORD AddressOfIndex;             // PDWORD
	DWORD AddressOfCallBacks;         // PIMAGE_TLS_CALLBACK *
	[color_scheme("Size")] DWORD SizeOfZeroFill;
	[color_scheme("Characteristics")] DWORD Characteristics;
};

public struct IMAGE_TLS_DIRECTORY64
{
	ULONGLONG StartAddressOfRawData;
	ULONGLONG EndAddressOfRawData;
	ULONGLONG AddressOfIndex;         // PDWORD
	ULONGLONG AddressOfCallBacks;     // PIMAGE_TLS_CALLBACK *;
	[color_scheme("Size")] DWORD SizeOfZeroFill;
	[color_scheme("Characteristics")] DWORD Characteristics;
};

struct IMAGE_FUNCTION_ENTRY64
{
	ULONGLONG StartingAddress;
	ULONGLONG EndingAddress;
	union
	{
		ULONGLONG EndOfPrologue;
		ULONGLONG UnwindInfoAddress;
	} DUMMYUNIONNAME;
};

public struct IMAGE_FUNCTION_ENTRY64ARRAY
{
	var nCount = GetDataDirectorySize(IMAGE_DIRECTORY_ENTRY_EXCEPTION) / sizeof(IMAGE_FUNCTION_ENTRY64);
	[noindex] IMAGE_FUNCTION_ENTRY64 functions[nCount];
};

// IMAGE_NT_HEADERS is a "PE" header
struct IMAGE_NT_HEADERS
{
	DWORD Signature;
	$assert(Signature == 'PE', "Invalid PE-Header");

	IMAGE_FILE_HEADER FileHeader;

	// Select a 32-bit or 64-bit header, depending on the FileHeader's Machine field
	var tmp = SetMachineType(FileHeader.Machine);

	case_union
	{
		case FileHeader.Machine == IMAGE_FILE_MACHINE_I386:
			IMAGE_OPTIONAL_HEADER32 OptionalHeader;
		default:
			IMAGE_OPTIONAL_HEADER64 OptionalHeader;
	} OptionalHeaderSelector;

	var _not_used_ = SetVirtualBase(OptionalHeaderSelector.OptionalHeader.ImageBase);

	// Section directory
	[noindex] IMAGE_SECTION_HEADER sections[FileHeader.NumberOfSections];

	// enumerate each data directory
	for (var i = 0; i < OptionalHeaderSelector.OptionalHeader.NumberOfRvaAndSizes; i = i + 1)
	{
		if (OptionalHeaderSelector.OptionalHeader.DataDirectory[i].VirtualAddress)
		{
			var va = int(RvaToPa(OptionalHeaderSelector.OptionalHeader.DataDirectory[i].VirtualAddress));
			var tmp0 = SetDataDirectory(i, OptionalHeaderSelector.OptionalHeader.DataDirectory[i].VirtualAddress, OptionalHeaderSelector.OptionalHeader.DataDirectory[i].Size);

			if (va != -1)
			{
				switch (i)
				{
				case IMAGE_DIRECTORY_ENTRY_IMPORT:
					$bind("struct IMAGE_IMPORT_DIRECTORY_ARRAY", "ImportDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_EXPORT:
					$bind("struct IMAGE_EXPORT_DIRECTORY", "ExportDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_BASERELOC:
					$bind("struct IMAGE_BASE_RELOCATION_ARRAY", "BaseRelocationArray", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_RESOURCE:
					$bind("struct IMAGE_RESOURCE_DIRECTORY_ROOT", "ResourceDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
					$bind("struct IMAGE_DELAY_IMPORT_DESCRIPTOR", "DelayImportDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_DEBUG:
					$bind("struct IMAGE_DEBUG_DIRECTORY", "DebugDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT:
					$bind("struct IMAGE_BOUND_IMPORT_DESCRIPTOR", "BoundImportDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG:
					if (FileHeader.Machine == IMAGE_FILE_MACHINE_I386)
						$bind("struct IMAGE_LOAD_CONFIG_DIRECTORY32", "ConfigDirectory", va);
					else
						$bind("struct IMAGE_LOAD_CONFIG_DIRECTORY64", "ConfigDirectory", va);
					break;
				case IMAGE_DIRECTORY_ENTRY_TLS:
					if (FileHeader.Machine == IMAGE_FILE_MACHINE_I386)
						$bind("struct IMAGE_TLS_DIRECTORY32", "TlsDirectory", va);
					else
						$bind("struct IMAGE_TLS_DIRECTORY64", "TlsDirectory", va);
					break;

					// ignored on x86
					/*
					case IMAGE_DIRECTORY_ENTRY_EXCEPTION:
						if(FileHeader.Machine!=IMAGE_FILE_MACHINE_I386)
							$bind("struct IMAGE_FUNCTION_ENTRY64ARRAY","FunctionEntryTable",va);
						break;
					/*
					case IMAGE_DIRECTORY_ENTRY_SECURITY:

						break;
					case IMAGE_DIRECTORY_ENTRY_ARCHITECTURE:

						break;
					case IMAGE_DIRECTORY_ENTRY_GLOBALPTR:

						break;
					case IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR:
						// MSIL
						break;
					*/
				}
			}
		}
	}
};

// Image File Header
struct IMAGE_FILE_HEADER
{
	ArchitectureType Machine;
	WORD NumberOfSections;

	// According to specification, there can be maximum of 96 sections
	$assert(NumberOfSections <= 96, "Maximum number of section exceeded");

	[color_scheme("TimeStamp")] DWORD TimeDateStamp;

	// ignored by loaders/debuggers
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;

	[color_scheme("Size")] WORD SizeOfOptionalHeader;

	// if Characteristics has no IMAGE_FILE_EXECUTABLE_IMAGE bit - will not be loaded by Win loader
	// if file has exports - IMAGE_FILE_DLL must be set
	[color_scheme("Characteristics")] ImageCharacteristicsType Characteristics;
};

enum OptionalHeaderMagic : WORD
{
	IMAGE_NT_OPTIONAL_HDR32_MAGIC = 0x10b,
	IMAGE_NT_OPTIONAL_HDR64_MAGIC = 0x20b,
	IMAGE_ROM_OPTIONAL_HDR_MAGIC = 0x107,
};

// Defined subsystem types
enum SubsystemType : WORD
{
	IMAGE_SUBSYSTEM_UNKNOWN = 0,
	IMAGE_SUBSYSTEM_NATIVE = 1,
	IMAGE_SUBSYSTEM_WINDOWS_GUI = 2,
	IMAGE_SUBSYSTEM_WINDOWS_CUI = 3,
	IMAGE_SUBSYSTEM_OS2_CUI = 5,
	IMAGE_SUBSYSTEM_POSIX_CUI = 7,
	IMAGE_SUBSYSTEM_WINDOWS_CE_GUI = 9,
	IMAGE_SUBSYSTEM_EFI_APPLICATION = 10,
	IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER = 11,
	IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER = 12,
	IMAGE_SUBSYSTEM_EFI_ROM = 13,
	IMAGE_SUBSYSTEM_XBOX = 14,
	IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION = 16,
};

// "DLL" characteristics
enum DllCharacteristicsType : WORD
{
	IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA = 0x0020,
	IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE = 0x0040,
	IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY = 0x0080,
	IMAGE_DLLCHARACTERISTICS_NX_COMPAT = 0x0100,
	IMAGE_DLLCHARACTERISTICS_NO_ISOLATION = 0x0200,
	IMAGE_DLLCHARACTERISTICS_NO_SEH = 0x0400,
	IMAGE_DLLCHARACTERISTICS_NO_BIND = 0x0800,
	IMAGE_DLLCHARACTERISTICS_APPCONTAINER = 0x1000,
	IMAGE_DLLCHARACTERISTICS_WDM_DRIVER = 0x2000,
	IMAGE_DLLCHARACTERISTICS_GUARD_CF = 0x4000,
	IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE = 0x8000
};

// 32-bit "optional" header
struct IMAGE_OPTIONAL_HEADER32
{
	//
	// Standard fields.
	//

	[color_scheme("Signature")] OptionalHeaderMagic Magic;

	$assert(
		Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC || Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC || IMAGE_ROM_OPTIONAL_HDR_MAGIC,
		"Invalid optional header magic number");

	BYTE    MajorLinkerVersion;
	BYTE    MinorLinkerVersion;
	[color_scheme("Size")] DWORD SizeOfCode;
	[color_scheme("Size")] DWORD SizeOfInitializedData;
	[color_scheme("Size")] DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	DWORD BaseOfData;				// removed in 64 bit version

	//
	// NT additional fields.
	//

	DWORD ImageBase;				// widened in x64 (PE32+) version
	DWORD SectionAlignment;
	DWORD FileAlignment;
	WORD MajorOperatingSystemVersion;
	WORD MinorOperatingSystemVersion;
	WORD MajorImageVersion;
	WORD MinorImageVersion;
	WORD MajorSubsystemVersion;
	WORD MinorSubsystemVersion;
	DWORD Win32VersionValue;
	[color_scheme("Size")] DWORD SizeOfImage;
	[color_scheme("Size")] DWORD SizeOfHeaders;

	// set to 0 to avoid checking
	DWORD CheckSum;
	SubsystemType Subsystem;
	[color_scheme("Characteristics")] DllCharacteristicsType DllCharacteristics;
	[color_scheme("Size")] DWORD SizeOfStackReserve;		// widened in x64 (PE32+) version
	[color_scheme("Size")] DWORD SizeOfStackCommit;		// widened in x64 (PE32+) version
	[color_scheme("Size")] DWORD SizeOfHeapReserve;		// widened in x64 (PE32+) version
	[color_scheme("Size")] DWORD SizeOfHeapCommit;		// widened in x64 (PE32+) version
	DWORD LoaderFlags;
	DWORD NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[NumberOfRvaAndSizes];
};

// 64-bit "optional" header
struct IMAGE_OPTIONAL_HEADER64
{
	[color_scheme("Signature")] OptionalHeaderMagic Magic;

	$assert(
		Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC || Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC || IMAGE_ROM_OPTIONAL_HDR_MAGIC,
		"Invalid optional header magic number");

	BYTE MajorLinkerVersion;
	BYTE MinorLinkerVersion;
	[color_scheme("Size")] DWORD SizeOfCode;
	[color_scheme("Size")] DWORD SizeOfInitializedData;
	[color_scheme("Size")] DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	ULONGLONG ImageBase;
	DWORD SectionAlignment;
	DWORD FileAlignment;
	WORD MajorOperatingSystemVersion;
	WORD MinorOperatingSystemVersion;
	WORD MajorImageVersion;
	WORD MinorImageVersion;
	WORD MajorSubsystemVersion;
	WORD MinorSubsystemVersion;
	DWORD Win32VersionValue;
	[color_scheme("Size")] DWORD SizeOfImage;
	[color_scheme("Size")] DWORD SizeOfHeaders;
	DWORD CheckSum;
	SubsystemType Subsystem;
	[color_scheme("Characteristics")] DllCharacteristicsType DllCharacteristics;
	[color_scheme("Size")] ULONGLONG SizeOfStackReserve;
	[color_scheme("Size")] ULONGLONG SizeOfStackCommit;
	[color_scheme("Size")] ULONGLONG SizeOfHeapReserve;
	[color_scheme("Size")] ULONGLONG SizeOfHeapCommit;
	DWORD LoaderFlags;
	DWORD NumberOfRvaAndSizes;

	IMAGE_DATA_DIRECTORY DataDirectory[NumberOfRvaAndSizes];
};

// Image "DOS" Header. Starts at the beginning of the executable file.
public struct IMAGE_DOS_HEADER       // DOS .EXE header
{
	// other valid values: 'ZM' (calling dos stub) / 'NE' (calling dos stub with segment registers DS=CS)
	[color_scheme("Signature")] WORD e_magic;
	$assert(e_magic == 'MZ', "Invalid DOS header");

	WORD e_cblp;
	WORD e_cp;
	WORD e_crlc;

	// size of DOS stub in paragraphs (1 par = 0x200 bytes)
	WORD e_cparhdr;
	WORD e_minalloc;
	WORD e_maxalloc;
	WORD e_ss;
	WORD e_sp;
	WORD e_csum;
	WORD e_ip;
	WORD e_cs;
	WORD e_lfarlc;
	WORD e_ovno;
	WORD e_res[4];
	WORD e_oemid;
	WORD e_oeminfo;
	WORD e_res2[10];
	[color_scheme("HeaderNt")] LONG e_lfanew as IMAGE_NT_HEADERS *(this);
};

// Length of the section name
enum
{
	IMAGE_SIZEOF_SHORT_NAME = 8,
};

// Section characteristics
enum SectionCharacteristics<DWORD>
{
	IMAGE_SCN_TYPE_NO_PAD = 0x00000008,	// Reserved.
	IMAGE_SCN_CNT_CODE = 0x00000020,		// Section contains code.
	IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040,		// Section contains initialized data.
	IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080,	// Section contains uninitialized data.
	IMAGE_SCN_LNK_OTHER = 0x00000100,	// Reserved.
	IMAGE_SCN_LNK_INFO = 0x00000200,	// Section contains comments or some other type of information.
	IMAGE_SCN_LNK_REMOVE = 0x00000800,	// Section contents will not become part of image.
	IMAGE_SCN_LNK_COMDAT = 0x00001000,	// Section contents comdat.
	IMAGE_SCN_NO_DEFER_SPEC_EXC = 0x00004000,	// Reset speculative exceptions handling bits in the TLB entries for this section.
	IMAGE_SCN_GPREL = 0x00008000,	// Section content can be accessed relative to GP
	IMAGE_SCN_MEM_FARDATA = 0x00008000,
	IMAGE_SCN_MEM_PURGEABLE = 0x00020000,
	IMAGE_SCN_MEM_16BIT = 0x00020000,
	IMAGE_SCN_MEM_LOCKED = 0x00040000,
	IMAGE_SCN_MEM_PRELOAD = 0x00080000,
	IMAGE_SCN_ALIGN_1BYTES = 0x00100000,	//
	IMAGE_SCN_ALIGN_2BYTES = 0x00200000,	//
	IMAGE_SCN_ALIGN_4BYTES = 0x00300000,	//
	IMAGE_SCN_ALIGN_8BYTES = 0x00400000,	//
	IMAGE_SCN_ALIGN_16BYTES = 0x00500000,	// Default alignment if no others are specified.
	IMAGE_SCN_ALIGN_32BYTES = 0x00600000,	//
	IMAGE_SCN_ALIGN_64BYTES = 0x00700000,	//
	IMAGE_SCN_ALIGN_128BYTES = 0x00800000,	//
	IMAGE_SCN_ALIGN_256BYTES = 0x00900000,	//
	IMAGE_SCN_ALIGN_512BYTES = 0x00A00000,	//
	IMAGE_SCN_ALIGN_1024BYTES = 0x00B00000,	//
	IMAGE_SCN_ALIGN_2048BYTES = 0x00C00000,	//
	IMAGE_SCN_ALIGN_4096BYTES = 0x00D00000,	//
	IMAGE_SCN_ALIGN_8192BYTES = 0x00E00000,	//
	IMAGE_SCN_ALIGN_MASK = 0x00F00000,
	IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000,	// Section contains extended relocations.
	IMAGE_SCN_MEM_DISCARDABLE = 0x02000000,	// Section can be discarded.
	IMAGE_SCN_MEM_NOT_CACHED = 0x04000000,	// Section is not cachable.
	IMAGE_SCN_MEM_NOT_PAGED = 0x08000000,	// Section is not pageable.
	IMAGE_SCN_MEM_SHARED = 0x10000000,	// Section is shareable.
	IMAGE_SCN_MEM_EXECUTE = 0x20000000,	// Section is executable.
	IMAGE_SCN_MEM_READ = 0x40000000,	// Section is readable.
	IMAGE_SCN_MEM_WRITE = 0x80000000,	// Section is writeable.
};

// Section header
[display("Section name: " + Name)]
struct IMAGE_SECTION_HEADER
{
	char Name[IMAGE_SIZEOF_SHORT_NAME];
	union
	{
		DWORD PhysicalAddress;
		DWORD VirtualSize;
	} Misc;
	DWORD VirtualAddress;
	[color_scheme("Size")] DWORD SizeOfRawData;
	DWORD PointerToRawData;

	// only used by object files
	DWORD PointerToRelocations;
	DWORD PointerToLinenumbers;
	WORD NumberOfRelocations;
	WORD NumberOfLinenumbers;

	[color_scheme("Characteristics")] SectionCharacteristics Characteristics;

	var tmp = AddSection(VirtualAddress, MAX(SizeOfRawData, Misc.VirtualSize), PointerToRawData);
};
