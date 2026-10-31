// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include <stddefs.h>

//32 bit
typedef uint32 Elf32_Addr;
typedef uint32 Elf32_Off;
typedef uint32 Elf32_SWord;
typedef uint32 Elf32_Word;
typedef uint16 Elf32_Half;

//64 bit
typedef uint32 Elf64_Word;
typedef uint64 Elf64_Off;
typedef uint64 Elf64_Addr;
typedef uint16 Elf64_Half;
typedef uint64 Elf64_QWord;

enum IdentElfClass :BYTE
{
	ELFCLASSNONE = 0,
	ELFCLASS32 = 1,
	ELFCLASS64 = 2
};

enum IdentDataEncoding :BYTE
{
	ELFDATANONE = 0,
	ELFDATA2LSB = 1,
	ELFDATA2MSB = 2
};

enum IdentElfVersion :BYTE
{
	ELFVERSIONNONE = 0,
	ELFVERSIONCURRENT = 1
};

enum IdentElfOS :BYTE
{
	ELFOSABI_NONE = 0, //
	ELFOSABI_HPUX = 1, // HP-UX 
	ELFOSABI_NETBSD = 2, // NetBSD 
	ELFOSABI_LINUX = 3, // Linux
	ELFOSABI_SOLARIS = 6, // Sun Solaris 
	ELFOSABI_AIX = 7, // AIX 
	ELFOSABI_IRIX = 8, // IRIX 
	ELFOSABI_FREEBSD = 9, // FreeBSD 
	ELFOSABI_TRU64 = 10, // Compaq TRU64 UNIX 
	ELFOSABI_MODESTO = 11, // Novell Modesto 
	ELFOSABI_OPENBSD = 12, // Open BSD 
	ELFOSABI_OPENVMS = 13, // Open VMS 
	ELFOSABI_NSK = 14, // HP Non-Stop Kernel 
	ELFOSABI_AROS = 15, // Amiga Research OS
	ELFOSABI_ARM = 97, //ARM
	ELFOSABI_STANDALONE = 255
};


struct ElfIdent
{
	char pre_id;
	char id[3];

	IdentElfClass file_class;
	IdentDataEncoding data_encoding;
	IdentElfVersion file_version;
	IdentElfOS os_abi;

	uint8 os_abi_ver;
	uint8 padding[6];
	uint8 ident_size;
};

/*
* Section Header
*/
enum SectionHeaderType :Elf32_Word
{
	SHT_NULL = 0,
	SHT_PROGBITS = 1,
	SHT_SYMTAB = 2,
	SHT_STRTAB = 3,
	SHT_RELA = 4,
	SHT_HASH = 5,
	SHT_DYNAMIC = 6,
	SHT_NOTE = 7,
	SHT_NOBITS = 8,
	SHT_REL = 9,
	SHT_SHLIB = 10,
	SHT_DYNSYM = 11,

	//Oracle
	SUNW_SYMNSORT = 0X6FFFFFEC,
	SUNW_PHNAME = 0X6FFFFFED,
	SUNW_ANCILLARY = 0X6FFFFFEE,
	SUNW_CAPCHAIN = 0X6FFFFFEF,
	SUNW_CAPINFO = 0X6FFFFFF0,
	SUNW_SYMSORT = 0X6FFFFFF1,
	SUNW_TLSSORT = 0X6FFFFFF2,
	SUNW_LDYNSYM = 0X6FFFFFF3,
	SUNW_DOF = 0X6FFFFFF4,
	SUNW_CAP = 0X6FFFFFF5,
	SUNW_SIGNATURE = 0X6FFFFFF6,
	SUNW_ANNOTATE = 0X6FFFFFF7,
	SUNW_DEBUGSTR = 0X6FFFFFF8,
	SUNW_DEBUG = 0X6FFFFFF9,
	SUNW_MOVE = 0X6FFFFFFA,
	SUNW_COMDAT = 0X6FFFFFFB,
	SUNW_SYMINFO = 0X6FFFFFFC,
	SUNW_VERDEF = 0X6FFFFFFD,
	SUNW_VERNEED = 0X6FFFFFFE,
	SUNW_VERSYM = 0X6FFFFFFF,
	//SHT_LOPROC = 0x70000000,
	SPARC_GOTDATA = 0X70000000,
	AMD64_UNWIND = 0X70000001,
	ARM_PREEMPTMAP = 0X70000002,
	ARM_ATTRIBUTES = 0X70000003,
	ARM_DEBUGOVERLAY = 0X70000004,
	ARM_OVERLAYSECTION = 0X70000005,
	
	SHT_HIPROC = 0x7fffffff,
	SHT_LOUSER = 0x80000000,
	SHT_HIUSER = 0xffffffff
};

enum SectionHeaderFlags :Elf32_Word
{
	SHF_WRITE = 1,
	SHF_ALLOC = 2,
	SHF_EXECINSTR = 4,
	SHF_MERGE = 0x10,
	SHF_STRINGS = 0x20,
	SHF_INFO_LINK = 0x40,
	SHF_LINK_ORDER = 0x80,
	SHF_OS_NONCONFORMING = 0x100,
	SHF_GROUP = 0x200,
	SHF_TLS = 0x400,
	SHF_COMPRESSED = 0x800,
	SHF_MASKOS = 0x0FF00000,
	SHF_MASKPROC = 0xf0000000
};

enum SectionHeaderFlags64 :Elf64_QWord
{
	SHF_WRITE = 1,
	SHF_ALLOC = 2,
	SHF_EXECINSTR = 4,
	SHF_MERGE = 0x10,
	SHF_STRINGS = 0x20,
	SHF_INFO_LINK  = 0x40,
	SHF_LINK_ORDER = 0x80,
	SHF_OS_NON_CONFORMING = 0x100,
	SHF_GROUP = 0x200,
	SHF_TLS = 0x400,
	SHF_ORDERED = 0x04000000,
	SHF_EXCLUDE = 0x08000000,
	SHF_MASK_OS = 0x0FF00000,
	SHF_MASKPROC = 0xf0000000
};

// Forward Declarations:
struct ElfSymbolSection32;
struct ElfSymbolSection64;

struct ElfStringSection32;
struct ElfStringSection64;

case_union DynamicValue64
{
	case d_tag == DT_FLAGS:
		enum EFlags64 : Elf64_QWord
		{
			DF_ORIGIN = 0x00000001,
			DF_SYMBOLIC = 0x00000002,
			DF_TEXTREL = 0x00000004,
			DF_BIND_NOW = 0x00000008,
			DF_STATIC_TLS = 0x00000010
		}d_val;
		break;
	case d_tag == DT_FLAGS_1:
		enum EFlags64_1 : Elf64_QWord
		{
			DF_1_NOW = 0x00000001,
			DF_1_GLOBAL = 0x00000002,
			DF_1_GROUP = 0x00000004,
			DF_1_NODELETE = 0x00000008,
			DF_1_LOADFLTR = 0x00000010,
			DF_1_INITFIRST = 0x00000020,
			DF_1_NOOPEN = 0x00000040,
			DF_1_ORIGIN = 0x00000080,
			DF_1_DIRECT = 0x00000100,
			DF_1_TRANS = 0x00000200,
			DF_1_INTERPOSE = 0x00000400,
			DF_1_NODEFLIB = 0x00000800,
			DF_1_NODUMP = 0x00001000,
			DF_1_CONFALT = 0x00002000,
			DF_1_ENDFILTEE = 0x00004000,
			DF_1_DISPRELDNE = 0x00008000,
			DF_1_DISPRELPND = 0x00010000,
			DF_1_NODIRECT = 0x00020000,
			DF_1_IGNMULDEF = 0x00040000,
			DF_1_NOKSYMS = 0x00080000,
			DF_1_NOHDR = 0x00100000,
			DF_1_EDITED = 0x00200000,
			DF_1_NORELOC = 0x00400000,
			DF_1_SYMINTPOSE = 0x00800000,
			DF_1_GLOBAUDIT = 0x01000000,
			DF_1_SINGLETON = 0x02000000,
			DF_1_STUB = 0x04000000,
			DF_1_PIE = 0x08000000
		}d_val;
		break;
	case d_tag == DT_NEEDED || d_tag == DT_SONAME || d_tag == DT_RPATH || d_tag == DT_RUNPATH:
		Elf64_Addr  d_name as NullTermString * (stringOffset(sh_off, sh_link, 8, is_little_endian));
		break;
	default:
		Elf64_Addr  d_ptr;
};

case_union DynamicValue32
{
	case d_tag == DT_FLAGS:
		enum EFlags32 : Elf32_Word
		{
			DF_ORIGIN = 0x00000001,
			DF_SYMBOLIC = 0x00000002,
			DF_TEXTREL = 0x00000004,
			DF_BIND_NOW = 0x00000008,
			DF_STATIC_TLS = 0x00000010
		}d_val;
		break;
	case d_tag == DT_FLAGS_1:
		enum EFlags32_1 : Elf32_Word
		{
			DF_1_NOW = 0x00000001,
			DF_1_GLOBAL = 0x00000002,
			DF_1_GROUP = 0x00000004,
			DF_1_NODELETE = 0x00000008,
			DF_1_LOADFLTR = 0x00000010,
			DF_1_INITFIRST = 0x00000020,
			DF_1_NOOPEN = 0x00000040,
			DF_1_ORIGIN = 0x00000080,
			DF_1_DIRECT = 0x00000100,
			DF_1_TRANS = 0x00000200,
			DF_1_INTERPOSE = 0x00000400,
			DF_1_NODEFLIB = 0x00000800,
			DF_1_NODUMP = 0x00001000,
			DF_1_CONFALT = 0x00002000,
			DF_1_ENDFILTEE = 0x00004000,
			DF_1_DISPRELDNE = 0x00008000,
			DF_1_DISPRELPND = 0x00010000,
			DF_1_NODIRECT = 0x00020000,
			DF_1_IGNMULDEF = 0x00040000,
			DF_1_NOKSYMS = 0x00080000,
			DF_1_NOHDR = 0x00100000,
			DF_1_EDITED = 0x00200000,
			DF_1_NORELOC = 0x00400000,
			DF_1_SYMINTPOSE = 0x00800000,
			DF_1_GLOBAUDIT = 0x01000000,
			DF_1_SINGLETON = 0x02000000,
			DF_1_STUB = 0x04000000,
			DF_1_PIE = 0x08000000
		}d_val;
		break;
	case d_tag == DT_NEEDED || d_tag == DT_SONAME || d_tag == DT_RPATH || d_tag == DT_RUNPATH:
		Elf32_Addr  d_name as NullTermString * (stringOffset(sh_off, sh_link, 4, is_little_endian));
		break;
	default:
		Elf32_Addr  d_ptr;
};

struct Elf64_Dyn 
{
	enum EDynamicType64 : __int64
	{
		DT_NULL = 0,
		DT_NEEDED = 1,
		DT_PLTRELSZ = 2,
		DT_PLTGOT = 3,
		DT_HASH = 4,
		DT_STRTAB = 5,
		DT_SYMTAB = 6,
		DT_RELA = 7,
		DT_RELASZ = 8,
		DT_RELAENT = 9,
		DT_STRSZ = 10,
		DT_SYMENT = 11,
		DT_INIT = 12,
		DT_FINI = 13,
		DT_SONAME = 14,
		DT_RPATH = 15,
		DT_SYMBOLIC = 16,
		DT_REL = 17,
		DT_RELSZ = 18,
		DT_RELENT = 19,
		DT_PLTREL = 20,
		DT_DEBUG = 21,
		DT_TEXTREL = 22,
		DT_JMPREL = 23,
		DT_BIND_NOW = 24,
		DT_INIT_ARRAY = 25,
		DT_FINI_ARRAY = 26,
		DT_INIT_ARRAYSZ = 27,
		DT_FINI_ARRAYSZ = 28,
		DT_RUNPATH = 29,
		DT_FLAGS = 30,
		DT_ENCODING = 32,
		DT_PREINIT_ARRAY = 32,
		DT_PREINIT_ARRAYSZ = 33,
		DT_SYMTAB_SHNDX = 34,
		DT_RELRSZ = 35,
		DT_RELR = 36,
		DT_RELRENT = 37,
		DT_LOOS = 0x6000000D,
		DT_HIOS = 0x6FFFF000,
		DT_VALRNGLO = 0x6FFFFD00,
		DT_GNU_PRELINKED = 0x6FFFFDF5,
		DT_GNU_CONFLICTSZ = 0x6FFFFDF6,
		DT_GNU_LIBLISTSZ = 0x6FFFFDF7,
		DT_CHECKSUM = 0x6FFFFDF8,
		DT_PLTPADSZ = 0x6FFFFDF9,
		DT_MOVEENT = 0x6FFFFDFA,
		DT_MOVESZ = 0x6FFFFDFB,
		DT_FEATURE_1 = 0x6FFFFDFC,
		DT_POSFLAG_1 = 0x6FFFFDFD,
		DT_SYMINSZ = 0x6FFFFDFE,
		DT_SYMINENT = 0x6FFFFDFF,
		DT_GNU_HASH = 0x6FFFFEF5,
		DT_TLSDESC_PLT = 0x6FFFFEF6,
		DT_TLSDESC_GOT = 0x6FFFFEF7,
		DT_GNU_CONFLICT = 0x6FFFFEF8,
		DT_GNU_LIBLIST = 0x6FFFFEF9,
		DT_CONFIG = 0x6FFFFEFA,
		DT_DEPAUDIT = 0x6FFFFEFB,
		DT_AUDIT = 0x6FFFFEFC,
		DT_PLTPAD = 0x6FFFFEFD,
		DT_MOVETAB = 0x6FFFFEFE,
		DT_SYMINFO = 0x6FFFFEFF,
		DT_VERSYM = 0x6FFFFFF0,
		DT_RELACOUNT = 0x6FFFFFF9,
		DT_RELCOUNT = 0x6FFFFFFA,
		DT_FLAGS_1 = 0x6FFFFFFB,
		DT_VERDEF = 0x6FFFFFFC,
		DT_VERDEFNUM = 0x6FFFFFFD,
		DT_VERNEED = 0x6FFFFFFE,
		DT_VERNEEDNUM = 0x6FFFFFFF,
		DT_LOPROC = 0x70000000,
		DT_HIPROC = 0x7FFFFFFF,
	}d_tag;
	DynamicValue64 d_un;
};

struct Elf32_Dyn
{
	enum EDynamicType32 : int
	{
		DT_NULL = 0,
		DT_NEEDED = 1,
		DT_PLTRELSZ = 2,
		DT_PLTGOT = 3,
		DT_HASH = 4,
		DT_STRTAB = 5,
		DT_SYMTAB = 6,
		DT_RELA = 7,
		DT_RELASZ = 8,
		DT_RELAENT = 9,
		DT_STRSZ = 10,
		DT_SYMENT = 11,
		DT_INIT = 12,
		DT_FINI = 13,
		DT_SONAME = 14,
		DT_RPATH = 15,
		DT_SYMBOLIC = 16,
		DT_REL = 17,
		DT_RELSZ = 18,
		DT_RELENT = 19,
		DT_PLTREL = 20,
		DT_DEBUG = 21,
		DT_TEXTREL = 22,
		DT_JMPREL = 23,
		DT_BIND_NOW = 24,
		DT_INIT_ARRAY = 25,
		DT_FINI_ARRAY = 26,
		DT_INIT_ARRAYSZ = 27,
		DT_FINI_ARRAYSZ = 28,
		DT_RUNPATH = 29,
		DT_FLAGS = 30,
		DT_ENCODING = 32,
		DT_PREINIT_ARRAY = 32,
		DT_PREINIT_ARRAYSZ = 33,
		DT_SYMTAB_SHNDX = 34,
		DT_RELRSZ = 35,
		DT_RELR = 36,
		DT_RELRENT = 37,
		DT_LOOS = 0x6000000D,
		DT_HIOS = 0x6FFFF000,
		DT_VALRNGLO = 0x6FFFFD00,
		DT_GNU_PRELINKED = 0x6FFFFDF5,
		DT_GNU_CONFLICTSZ = 0x6FFFFDF6,
		DT_GNU_LIBLISTSZ = 0x6FFFFDF7,
		DT_CHECKSUM = 0x6FFFFDF8,
		DT_PLTPADSZ = 0x6FFFFDF9,
		DT_MOVEENT = 0x6FFFFDFA,
		DT_MOVESZ = 0x6FFFFDFB,
		DT_FEATURE_1 = 0x6FFFFDFC,
		DT_POSFLAG_1 = 0x6FFFFDFD,
		DT_SYMINSZ = 0x6FFFFDFE,
		DT_SYMINENT = 0x6FFFFDFF,
		DT_GNU_HASH = 0x6FFFFEF5,
		DT_TLSDESC_PLT = 0x6FFFFEF6,
		DT_TLSDESC_GOT = 0x6FFFFEF7,
		DT_GNU_CONFLICT = 0x6FFFFEF8,
		DT_GNU_LIBLIST = 0x6FFFFEF9,
		DT_CONFIG = 0x6FFFFEFA,
		DT_DEPAUDIT = 0x6FFFFEFB,
		DT_AUDIT = 0x6FFFFEFC,
		DT_PLTPAD = 0x6FFFFEFD,
		DT_MOVETAB = 0x6FFFFEFE,
		DT_SYMINFO = 0x6FFFFEFF,
		DT_VERSYM = 0x6FFFFFF0,
		DT_RELACOUNT = 0x6FFFFFF9,
		DT_RELCOUNT = 0x6FFFFFFA,
		DT_FLAGS_1 = 0x6FFFFFFB,
		DT_VERDEF = 0x6FFFFFFC,
		DT_VERDEFNUM = 0x6FFFFFFD,
		DT_VERNEED = 0x6FFFFFFE,
		DT_VERNEEDNUM = 0x6FFFFFFF,
		DT_LOPROC = 0x70000000,
		DT_HIPROC = 0x7FFFFFFF,
	}d_tag;
	DynamicValue32 d_un;
};

struct ElfDynamicSection32
{
	Elf32_Dyn dynamic[sh_size / 8];
};

struct ElfDynamicSection64
{
	Elf64_Dyn dynamic[sh_size / 16] ;
};

enum ERelaType64 : uint64
{
    R_X86_64_NONE,
	R_X86_64_64,
	R_X86_64_PC32,
	R_X86_64_GOT32,
	R_X86_64_PLT32,
	R_X86_64_COPY,
	R_X86_64_GLOB_DAT,
	R_X86_64_JUMP_SLOT,
	R_X86_64_RELATIVE,
	R_X86_64_GOTPCREL,
	R_X86_64_32,
	R_X86_64_32S,
	R_X86_64_16,
	R_X86_64_PC16,
	R_X86_64_8,
	R_X86_64_PC8,
	R_X86_64_DTPMOD64,
	R_X86_64_DTPOFF64,
	R_X86_64_TPOFF64,
	R_X86_64_TLSGD,
	R_X86_64_TLSLD,
	R_X86_64_DTPOFF32,
	R_X86_64_GOTTPOFF,
	R_X86_64_TPOFF32,
	R_X86_64_PC64,
	R_X86_64_GOTOFF64,
	R_X86_64_GOTPC32,
	R_X86_64_IRELATIVE
};

enum ERelaType32 : int
{
	R_X86_64_NONE,
	R_X86_64_64,
	R_X86_64_PC32,
	R_X86_64_GOT32,
	R_X86_64_PLT32,
	R_X86_64_COPY,
	R_X86_64_GLOB_DAT,
	R_X86_64_JUMP_SLOT,
	R_X86_64_RELATIVE,
	R_X86_64_GOTPCREL,
	R_X86_64_32,
	R_X86_64_32S,
	R_X86_64_16,
	R_X86_64_PC16,
	R_X86_64_8,
	R_X86_64_PC8,
	R_X86_64_DTPMOD64,
	R_X86_64_DTPOFF64,
	R_X86_64_TPOFF64,
	R_X86_64_TLSGD,
	R_X86_64_TLSLD,
	R_X86_64_DTPOFF32,
	R_X86_64_GOTTPOFF,
	R_X86_64_TPOFF32,
	R_X86_64_PC64,
	R_X86_64_GOTOFF64,
	R_X86_64_GOTPC32,
	R_X86_64_IRELATIVE
};


struct Elf32_Rel
{
	Elf32_Addr  r_offset;
	Elf32_Word  r_info;
};

struct Elf64_Rel
{
	Elf64_Addr   r_offset;
	Elf64_QWord  r_info;
};

struct Elf32_Rela
{
	Elf32_Addr  r_offset;
//	Elf32_Word	r_info;
	union Info
	{
		struct
		{
			ERelaType32 type : 8;
			Elf32_Word symbol : 24;
		}info;
		[format("b2w64arf0")]
		Elf32_Word  bmInfo;
	}r_info;
	int r_addend;
};

struct Elf64_Rela 
{
	Elf64_Addr   r_offset;
//	Elf64_QWord  r_info;
	union Info
	{
		struct
		{
			ERelaType64 type : 32;
			uint64 symbol : 32;
		}info;
		[format("b2w64arf0")]
		uint64  bmInfo;
	}r_info;

	int64 r_addend;
};

struct ElfRelSection32
{
	Elf32_Rel rel[sh_size / sizeof(Elf32_Rel)];
};

struct ElfRelSection64
{
	Elf64_Rel rel[sh_size / sizeof(Elf64_Rel)];
};

struct ElfRelocationsSection32
{
	Elf32_Rela rela[sh_size / sizeof(Elf32_Rela)];
};

struct ElfRelocationsSection64
{
	Elf64_Rela rela[sh_size / sizeof(Elf64_Rela)];
};


struct Elf64_Nhdr 
{
	Elf64_Word  n_namesz;
	Elf64_Word  n_descsz;
	Elf64_Word  n_type;
	char name[n_namesz];
	unsigned char padding[(4 - (n_namesz % 4)) & -5];
	char desc[n_descsz];
	unsigned char padding1[(4 - (n_descsz % 4)) & -5];
};

struct Elf64_GNU_Hash
{
	Elf64_Word  nbuckets;
	Elf64_Word  symndx;
	Elf64_Word  maskwords;
	Elf64_Word  shift2;
};

[display(sh_name.data)]
struct ElfSectionHeader32
{
	Elf32_Word sh_name as NullTermString *(stringOffset(sh_off, sti, 4, is_little_endian));
	SectionHeaderType sh_type;
	SectionHeaderFlags sh_flags;

	Elf32_Addr sh_addrs;

	case_union
	{
	case sh_type == SHT_SYMTAB || sh_type == SHT_DYNSYM:
		Elf32_Off sym_table as ElfSymbolSection32 *;
	case sh_type == SHT_STRTAB:
		Elf32_Off str_table as ElfStringSection32 *;
	case sh_type == SHT_DYNAMIC:
		Elf32_Off dyn_table as ElfDynamicSection32 *;
	case sh_type == SHT_RELA:
		Elf32_Off rela_table as ElfRelocationsSection32 *;
	case sh_type == SHT_REL:
		Elf32_Off rel_table as ElfRelSection32 *;
	case sh_type == SHT_NOTE:
		Elf32_Off note as Elf64_Nhdr *;
	case sh_type == SHT_HASH || sh_type == SUNW_SIGNATURE:
		Elf32_Off note as Elf64_GNU_Hash *;
	default:
		Elf32_Off sh_offset_value;
	}sh_offset;

	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
};

[display(sh_name.data)]
struct ElfSectionHeader64
{
	Elf64_Word sh_name as NullTermString *(stringOffset(sh_off, sti, 8, is_little_endian));

	SectionHeaderType sh_type;
	SectionHeaderFlags64 sh_flags;

	Elf64_Addr sh_addrs;

	case_union
	{
	case sh_type == SHT_SYMTAB || sh_type == SHT_DYNSYM:
		Elf64_Off sym_table as ElfSymbolSection64 *;
	case sh_type == SHT_STRTAB:
		Elf64_Off str_table as ElfStringSection64 *;
	case sh_type == SHT_DYNAMIC:
		Elf64_Off dyn_table as ElfDynamicSection64 *;
	case sh_type == SHT_RELA:
		Elf64_Off rela_table as ElfRelocationsSection64 *;
	case sh_type == SHT_REL:
		Elf64_Off rel_table as ElfRelSection64 *;
	case sh_type == SHT_NOTE:
		Elf64_Off note as Elf64_Nhdr *;
	case sh_type == SHT_HASH || sh_type == SUNW_SIGNATURE:
		Elf64_Off note as Elf64_GNU_Hash *;

	default:
		Elf64_Off sh_offset_value;
	}sh_offset;

	Elf64_QWord sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_QWord sh_addralign;
	Elf64_QWord sh_entsize;
};

struct ElfSectionHeader32Array
{
	ElfSectionHeader32 headers[she_num];
};

struct ElfSectionHeader64Array
{
	ElfSectionHeader64 headers[she_num];
};

/*
* Program header
*/
enum ProgramHeaderType :Elf32_Word
{
	PT_NULL = 0,
	PT_LOAD = 1,
	PT_DYNAMIC = 2,
	PT_INTERP = 3,
	PT_NOTE = 4,
	PT_SHLIB = 5,
	PT_PHDR = 6,
	PT_TLS = 7,
	PT_LOOS = 0x60000000,
	PT_GNU_EH_FRAME = 0x6474e550,
	PT_GNU_STACK = 0x6474e551,
	PT_GNU_RELRO = 0x6474e552,
	PT_GNU_PROPERTY = 0x6474e553,
	PT_HIOS = 0x6FFFFFFF,
	PT_LOPROC = 0x70000000,
	PT_HIPROC = 0x7ffffff
};

enum ProgramHeaderFlags :Elf32_Word
{
	PHF_NONE = 0,
	PHF_X = 1,
	PHF_W = 2,
	PHF_WX = 3,
	PHF_R = 4,
	PHF_RX = 5,
	PHF_RW = 6,
	PHF_RWX = 7
};

struct ElfProgramHeader32
{
	ProgramHeaderType p_type;

	Elf32_Off ph_offset;
	Elf32_Addr ph_vaddr;
	Elf32_Addr ph_paddr;
	Elf32_Word ph_filesz;
	Elf32_Word ph_memsz;

	ProgramHeaderFlags ph_flags;
	Elf32_Word ph_align;
};

struct ElfProgramHeader64
{
	ProgramHeaderType ph_type;
	ProgramHeaderFlags ph_flags;

	Elf64_Off ph_offset;
	Elf64_Addr ph_vaddr;
	Elf64_Addr ph_paddr;
	Elf64_QWord ph_filesz;
	Elf64_QWord ph_memsz;
	Elf64_QWord ph_align;
};

struct ElfProgramHeader32Array
{
	ElfProgramHeader32 headers[phe_num];
};

struct ElfProgramHeader64Array
{
	ElfProgramHeader64 headers[phe_num];
};

struct AsciiString
{
	char s;
	if (s == 0)
		$break_array(true);
	else
		data = data + format("{0c}", s);
};

[display(data)]
struct NullTermString
{
	var data = "";
	AsciiString str[*];
};

[display(data)]
struct NullTermStringArray
{
	var data = "";

	AsciiString str[*];

	if (current_offset >= last_offset)
		$break_array(true);
};

/*
* Different sections
*/
javascript
{
  function stringOffset(sh_off, sh_link, addrSize, littleEndian)
  {
		let bytes = document.Read(sh_off + sh_link * (addrSize * 6 + 16) + (8 + addrSize * 2), addrSize);
		let offset = 0;

		if (littleEndian) {
			for (let i = addrSize - 1; i >= 0; i--) {
				offset = (offset << 8) | Number(bytes[i]);
			}
		}
		else {
			for (let i = 0; i < addrSize; i++) {
				offset = (offset << 8) | Number(bytes[i]);
			}
		}

		return offset;
  }
};

// Symbol Table
enum EInfoType : unsigned char
{
	STT_NOTYPE = 0,
	STT_OBJECT = 1,
	STT_FUNC = 2,
	STT_SECTION = 3,
	STT_FILE = 4,
	STT_COMMON = 5,
	STT_TLS = 6,
	STT_NUM = 7,
	STT_LOOS = 10,
	STT_GNU_IFUNC = 11,
	STT_HIOS = 12,
	STT_LOPROC = 13,
	STT_HIPROC = 15
};

enum EInfoBind : unsigned char
{
	STB_LOCAL = 0,
	STB_GLOBAL = 1,
	STB_WEAK = 2,
	STB_NUM = 3,
	STB_LOOS = 10,
	STB_GNU_UNIQUE = 10,
	STB_HIOS = 12,
	STB_LOPROC = 13,
	STB_HIPROC = 15
};

[display(st_name.data)]
struct ElfSymbolSectionEntry32
{
	Elf32_Word st_name as NullTermString *(stringOffset(sh_off, sh_link, 4, is_little_endian));
	Elf32_Addr st_value;
	Elf32_Word st_size;
	union StInfo
	{
		struct
		{
			EInfoType type : 4;
			EInfoBind bind : 4;
		}info;
		[format("b2w8arf0")]
		unsigned char  bmInfo;
	}st_info;
	unsigned char st_other;
	Elf32_Half st_shndx;
};

[display(st_name.data)]
struct ElfSymbolSectionEntry64
{
	Elf64_Word st_name as NullTermString *(stringOffset(sh_off, sh_link, 8, is_little_endian));

	union StInfo
	{
		struct
		{
			EInfoType type: 4;
			EInfoBind bind : 4;
		}info;
		[format("b2w8arf0")]
		unsigned char  bmstInfo;
	}st_info;

	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_QWord st_size;
};

// array of items
// 'sh_size' is located in ElfSectionHeader32
struct ElfSymbolSection32
{
	ElfSymbolSectionEntry32 symbols[sh_size / sizeof(ElfSymbolSectionEntry32)];
};

// array of items
// 'sh_size' is located in ElfSectionHeader64
struct ElfSymbolSection64
{
	ElfSymbolSectionEntry64 symbols[sh_size / sizeof(ElfSymbolSectionEntry64)];
};


struct ElfStringSection32
{
	var last_offset = current_offset + sh_size;
	NullTermStringArray strings[*];
};

struct ElfStringSection64
{
	var last_offset  = current_offset  + sh_size;
	NullTermStringArray strings[*];
};

/*
* ELF_HEADER
*/
enum ElfType :Elf32_Half
{
	ET_NONE = 0,
	ET_REL = 1,
	ET_EXEC = 2,
	ET_DYN = 3,
	ET_CORE = 4,
	ET_LOPROC = 0xff00,
	ET_HIPROC = 0xffff
};

enum ElfMachine :Elf32_Half
{
	EM_NONE = 0, //
	EM_M32 = 1, //AT&T WE 32100 
	EM_SPARC = 2, //SPARC 
	EM_386 = 3, //Intel 80386 
	EM_68K = 4, //Motorola 68000 
	EM_88K = 5, //Motorola 88000 
	EM_860 = 7, //Intel 80860 
	EM_MIPS = 8, //MIPS I Architecture 
	EM_S370 = 9, //IBM System/370 Processor 
	EM_MIPS_RS3_LE = 10, //MIPS RS3000 Little-endian 
	EM_PARISC = 15, //Hewlett-Packard PA-RISC 
	EM_VPP500 = 17, //Fujitsu VPP500 
	EM_SPARC32PLUS = 18, //Enhanced instruction set SPARC 
	EM_960 = 19, //Intel 80960 
	EM_PPC = 20, //PowerPC 
	EM_PPC64 = 21, //64-bit PowerPC 
	EM_S390 = 22, //IBM System/390 Processor 
	EM_V800 = 36, //NEC V800 
	EM_FR20 = 37, //Fujitsu FR20 
	EM_RH32 = 38, //TRW RH-32 
	EM_RCE = 39, //Motorola RCE 
	EM_ARM = 40, //Advanced RISC Machines ARM 
	EM_ALPHA = 41, //Digital Alpha 
	EM_SH = 42, //Hitachi SH 
	EM_SPARCV9 = 43, //SPARC Version 9 
	EM_TRICORE = 44, //Siemens TriCore embedded processor 
	EM_ARC = 45, //Argonaut RISC Core, Argonaut Technologies Inc. 
	EM_H8_300 = 46, //Hitachi H8/300 
	EM_H8_300H = 47, //Hitachi H8/300H 
	EM_H8S = 48, //Hitachi H8S 
	EM_H8_500 = 49, //Hitachi H8/500 
	EM_IA_64 = 50, //Intel IA-64 processor architecture 
	EM_MIPS_X = 51, //Stanford MIPS-X 
	EM_COLDFIRE = 52, //Motorola ColdFire 
	EM_68HC12 = 53, //Motorola M68HC12 
	EM_MMA = 54, //Fujitsu MMA Multimedia Accelerator 
	EM_PCP = 55, //Siemens PCP 
	EM_NCPU = 56, //Sony nCPU embedded RISC processor 
	EM_NDR1 = 57, //Denso NDR1 microprocessor 
	EM_STARCORE = 58, //Motorola Star*Core processor 
	EM_ME16 = 59, //Toyota ME16 processor 
	EM_ST100 = 60, //STMicroelectronics ST100 processor 
	EM_TINYJ = 61, //Advanced Logic Corp. TinyJ embedded processor family 
	EM_X86_64 = 62, //AMD x86-64 architecture 
	EM_PDSP = 63, //Sony DSP Processor 
	EM_PDP10 = 64, //Digital Equipment Corp. PDP-10 
	EM_PDP11 = 65, //Digital Equipment Corp. PDP-11 
	EM_FX66 = 66, //Siemens FX66 microcontroller 
	EM_ST9PLUS = 67, //STMicroelectronics ST9+ 8/16 bit microcontroller 
	EM_ST7 = 68, //STMicroelectronics ST7 8-bit microcontroller 
	EM_68HC16 = 69, //Motorola MC68HC16 Microcontroller 
	EM_68HC11 = 70, //Motorola MC68HC11 Microcontroller 
	EM_68HC08 = 71, //Motorola MC68HC08 Microcontroller 
	EM_68HC05 = 72, //Motorola MC68HC05 Microcontroller 
	EM_SVX = 73, //Silicon Graphics SVx 
	EM_ST19 = 75, //Digital VAX 
	EM_CRIS = 76, //Axis Communications 32-bit embedded processor 
	EM_JAVELIN = 77, //Infineon Technologies 32-bit embedded processor 
	EM_FIREPATH = 78, //Element 14 64-bit DSP Processor 
	EM_ZSP = 79, //LSI Logic 16-bit DSP Processor 
	EM_MMIX = 80, //Donald Knuth's educational 64-bit processor 
	EM_HUANY = 81, //Harvard University machine-independent object files 
	EM_PRISM = 82, //SiTera Prism 
	EM_AVR = 83, //Atmel AVR 8-bit microcontroller 
	EM_FR30 = 84, //Fujitsu FR30 
	EM_D10V = 85, //Mitsubishi D10V 
	EM_D30V = 86, //Mitsubishi D30V 
	EM_V850 = 87, //NEC v850 
	EM_M32R = 88, //Mitsubishi M32R 
	EM_MN10300 = 89, //Matsushita MN10300 
	EM_MN10200 = 90, //Matsushita MN10200 
	EM_PJ = 91, //picoJava 
	EM_OPENRISC = 92, //OpenRISC 32-bit embedded processor 
	EM_ARC_A5 = 93, //ARC Cores Tangent-A5 
	EM_XTENSA = 94, //Tensilica Xtensa Architecture 
	EM_VIDEOCORE = 95, //Alphamosaic VideoCore processor 
	EM_TMM_GPP = 96, //Thompson Multimedia General Purpose Processor 
	EM_NS32K = 97, //National Semiconductor 32000 series 
	EM_TPC = 98, //Tenor Network TPC processor 
	EM_SNP1K = 99, //Trebia SNP 1000 processor 
	EM_ST200 = 100, //STMicroelectronics (www.st.com) ST200 microcontroller 
	EM_IP2K = 101, //Ubicom IP2xxx microcontroller family 
	EM_MAX = 102, //MAX Processor 
	EM_CR = 103, //National Semiconductor CompactRISC microprocessor 
	EM_F2MC16 = 104, //Fujitsu F2MC16 
	EM_MSP430 = 105, //Texas Instruments embedded microcontroller msp430 
	EM_BLACKFIN = 106, //Analog Devices Blackfin (DSP) processor 
	EM_SE_C33 = 107, //S1C33 Family of Seiko Epson processors 
	EM_SEP = 108, //Sharp embedded microprocessor 
	EM_ARCA = 109, //Arca RISC Microprocessor 
	EM_UNICORE = 110 //Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University

};

enum ElfVersion :Elf32_Word
{
	EV_NONE = 0,
	EV_CURRENT = 1
};


public struct ELF_HEADER
{
	ElfIdent ident;

	$assert(ident.pre_id == 0x7f, "Not an ELF file");
	$assert(ident.id == "ELF", "Not an ELF file");
	var is_big_endian = ident.data_encoding == ELFDATA2MSB;
	var is_little_endian = !is_big_endian;

	if (is_big_endian)
	{
		#pragma byte_order(BigEndian)
	}

	ElfType type;
	ElfMachine machine;
	ElfVersion version;

	switch (ident.file_class)
	{
	case ELFCLASS32:
		Elf32_Addr entry;
		Elf32_Off ph_off as ElfProgramHeader32Array *;
		Elf32_Off sh_off as ElfSectionHeader32Array *;

		Elf32_Word flags;
		Elf32_Half eh_size; // size of ELF_HEADER

		Elf32_Half phe_size; // size in bytes of one entry in the file’s program header table
		Elf32_Half phe_num; // number of entries in the program header table

		Elf32_Half she_size; // section header’s size in bytes
		Elf32_Half she_num; // number of entries in the section header table

		Elf32_Half sti; // string table index
		break;
	case ELFCLASS64:
		Elf64_Addr entry;
		Elf64_Off ph_off as ElfProgramHeader64Array *;
		Elf64_Off sh_off as ElfSectionHeader64Array *;

		Elf32_Word flags;
		Elf64_Half eh_size; // size of ELF_HEADER

		Elf64_Half phe_size; // size in bytes of one entry in the file’s program header table
		Elf64_Half phe_num; // number of entries in the program header table

		Elf64_Half she_size; // section header’s size in bytes
		Elf64_Half she_num; // number of entries in the section header table
		Elf64_Half sti; // STRING_TABLE_INDEX
		break;
	}
};
