// Copyright (c) 2015-2022 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program

// Hex Editor Neo's Structure Viewer sample declaration file
#include <stddefs.h>

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
	ELFOSABI_SOLARIS = 6, // Sun Solaris 
	ELFOSABI_AIX = 7, // AIX 
	ELFOSABI_IRIX = 8, // IRIX 
	ELFOSABI_FREEBSD = 9, // FreeBSD 
	ELFOSABI_TRU64 = 10, // Compaq TRU64 UNIX 
	ELFOSABI_MODESTO = 11, // Novell Modesto 
	ELFOSABI_OPENBSD = 12, // Open BSD 
	ELFOSABI_OPENVMS = 13, // Open VMS 
	ELFOSABI_NSK = 14, // HP Non-Stop Kernel 
	ELFOSABI_AROS = 15 // Amiga Research OS
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
	SHT_LOPROC = 0x70000000,
	SHT_HIPROC = 0x7fffffff,
	SHT_LOUSER = 0x80000000,
	SHT_HIUSER = 0xffffffff
};

enum SectionHeaderFlags :Elf32_Word
{
	SHF_WRITE = 1,
	SHF_ALLOC = 2,
	SHF_EXECINSTR = 4,
	SHF_MASKPROC = 0xf0000000
};

// Forward Declarations:
struct ElfSymbolSection32;
struct ElfSymbolSection64;

struct ElfStringSection32;
struct ElfStringSection64;


struct ElfSectionHeader32
{
	Elf32_Word sh_name;
	SectionHeaderType sh_type;
	SectionHeaderFlags sh_flags;

	Elf32_Addr sh_addrs;

	case_union
	{
	case sh_type == SHT_SYMTAB:
		Elf32_Off sym_table as ElfSymbolSection32 *;
	case sh_type == SHT_STRTAB:
		Elf32_Off str_table as ElfStringSection32 *;
	default:
		Elf32_Off sh_offset_value;
	}sh_offset;

	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
};

struct ElfSectionHeader64
{
	Elf64_Word sh_name;
	SectionHeaderType sh_type;
	SectionHeaderFlags sh_flags;

	Elf64_Addr sh_addrs;

	case_union
	{
	case sh_type == SHT_SYMTAB:
		Elf64_Off sym_table as ElfSymbolSection64 *;
	case sh_type == SHT_STRTAB:
		Elf64_Off str_table as ElfStringSection64 *;
	default:
		Elf64_Off sh_offset_value;
	}sh_offset;

	Elf64_Word sh_size;
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


/*
* Different sections
*/

// Symbol Table
struct ElfSymbolSectionEntry32
{
	Elf32_Word st_name;
	Elf32_Addr st_value;
	Elf32_Word st_size;
	unsigned char st_info;
	unsigned char st_other;
	Elf32_Half st_shndx;
};

struct ElfSymbolSectionEntry64
{
	Elf64_Word st_name;
	unsigned char st_info;
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
	char symbols[sh_size];
};

struct ElfStringSection64
{
	char symbols[sh_size];
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

struct ELF_HEADER
{
	ElfIdent ident;

	$assert(ident.pre_id == 0x7f, "Not an ELF file");
	$assert(ident.id == "ELF", "Not an ELF file");

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
