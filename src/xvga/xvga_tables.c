// ******************************************************************
// * 
// * proj : OpenXDK
// *
// * desc : Open Source XBox Development Kit
// *
// * file : xvga_tables.c
// *
// * note : XBox VGA
// *
// ******************************************************************
#include "xvga_tables.h"

// NOT-WORKING!!
// ******************************************************************
// * mode_256x240
// ******************************************************************
static vga_reg mode_256x240[] =
{
	{ 0x03C2, 0x00, 0xE3 },
	{ 0x03D4, 0x00, 0x5F },
	{ 0x03D4, 0x01, 0x3F },
	{ 0x03D4, 0x02, 0x40 },
	{ 0x03D4, 0x03, 0x82 },
	{ 0x03D4, 0x04, 0x4E },
	{ 0x03D4, 0x05, 0x96 },
	{ 0x03D4, 0x06, 0x0D },
	{ 0x03D4, 0x07, 0x3E },
	{ 0x03D4, 0x08, 0x00 },
	{ 0x03D4, 0x09, 0x41 },
	{ 0x03D4, 0x10, 0xEA },
	{ 0x03D4, 0x11, 0xAC },
	{ 0x03D4, 0x12, 0xDF },
	{ 0x03D4, 0x13, 0x20 },
	{ 0x03D4, 0x14, 0x00 },
	{ 0x03D4, 0x15, 0xE7 },
	{ 0x03D4, 0x16, 0x06 },
	{ 0x03D4, 0x17, 0xE3 },
	{ 0x03C4, 0x01, 0x01 },
	{ 0x03C4, 0x04, 0x06 },
	{ 0x03CE, 0x05, 0x40 },
	{ 0x03CE, 0x06, 0x05 },
	{ 0x03C0, 0x10, 0x41 },
	{ 0x03C0, 0x13, 0x00 }
};

// ******************************************************************
// * mode_320x240
// ******************************************************************
static vga_reg mode_320x240[] =
{
	{ 0x3c2, 0x00, 0xe3 },
	{ 0x3d4, 0x00, 0x5f },
	{ 0x3d4, 0x01, 0x4f },
	{ 0x3d4, 0x02, 0x50 },
	{ 0x3d4, 0x03, 0x82 },
	{ 0x3d4, 0x04, 0x54 },
	{ 0x3d4, 0x05, 0x80 },
	{ 0x3d4, 0x06, 0x0d },
	{ 0x3d4, 0x07, 0x3e },
	{ 0x3d4, 0x08, 0x00 },
	{ 0x3d4, 0x09, 0x41 },
	{ 0x3d4, 0x10, 0xea },
	{ 0x3d4, 0x11, 0xac },
	{ 0x3d4, 0x12, 0xdf },
	{ 0x3d4, 0x13, 0x28 },
	{ 0x3d4, 0x14, 0x00 },
	{ 0x3d4, 0x15, 0xe7 },
	{ 0x3d4, 0x16, 0x06 },
	{ 0x3d4, 0x17, 0xe3 },
	{ 0x3c4, 0x01, 0x01 },
	{ 0x3c4, 0x04, 0x06 },
	{ 0x3ce, 0x05, 0x40 },
	{ 0x3ce, 0x06, 0x05 },
	{ 0x3c0, 0x10, 0x41 },
	{ 0x3c0, 0x13, 0x00 }
};

// may or may not be working?!?!
// ******************************************************************
// * mode_320x200
// ******************************************************************
static vga_reg mode_320x200[] =
{
	{ 0x03C2, 0x00, 0x63 },
	{ 0x03D4, 0x00, 0x5F },
	{ 0x03D4, 0x01, 0x4F },
	{ 0x03D4, 0x02, 0x50 },
	{ 0x03D4, 0x03, 0x82 },
	{ 0x03D4, 0x04, 0x54 },
	{ 0x03D4, 0x05, 0x80 },
	{ 0x03D4, 0x06, 0xBF },
	{ 0x03D4, 0x07, 0x1F },
	{ 0x03D4, 0x08, 0x00 },
	{ 0x03D4, 0x09, 0x41 },
	{ 0x03D4, 0x10, 0x9C },
	{ 0x03D4, 0x11, 0x8E },
	{ 0x03D4, 0x12, 0x8F },
	{ 0x03D4, 0x13, 0x28 },
	{ 0x03D4, 0x14, 0x00 },
	{ 0x03D4, 0x15, 0x96 },
	{ 0x03D4, 0x16, 0xB9 },
	{ 0x03D4, 0x17, 0xE3 },
	{ 0x03C4, 0x01, 0x01 },
	{ 0x03C4, 0x04, 0x06 },
	{ 0x03CE, 0x05, 0x40 },
	{ 0x03CE, 0x06, 0x05 },
	{ 0x03C0, 0x10, 0x41 },
	{ 0x03C0, 0x13, 0x00 }
};
