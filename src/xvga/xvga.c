// ******************************************************************
// * 
// * proj : OpenXDK
// *
// * desc : Open Source XBox Development Kit
// *
// * file : xvga.c
// *
// * note : XBox VGA
// *
// ******************************************************************
#include "xvga.h"

// ******************************************************************
// * static functions
// ******************************************************************
static void init_unchained(void);
static void write_vgareg(int port, int index, int value);

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

// ******************************************************************
// * init_unchained
// ******************************************************************
void init_unchained(void)
{
    uint08 x;

    *CRTC_REG_INDEX = 0x11;

    x = (*CRTC_REG_DATA) & 0x7F;

    *CRTC_REG_INDEX = 0x11;

    *CRTC_REG_DATA = x;
}

// ******************************************************************
// * write_vgareg
// ******************************************************************
void write_vgareg(int port, int index, int value)
{
    if(port == 0x03C0)
    {
        *CRTC_REG_INDEX = index | 0x20;
        *CRTC_REG_INDEX = value;
    }
    else if(port == 0x03C2)
    {
        *MISC_REG = value;
    }
    else if(port == 0x03C3)
    {
        *(char * const)0x000c03c3 = value;
    }
    else
    {
        char *real_port = 0;

        if(port == 0x03CE || port == 0x03CF || port == 0x03C4 || port == 0x03C5)
        {
            real_port = (char*)(port + 0xFD0C0000);
        }
        else
        {
            real_port = (char*)(port + 0xFD601000);
        }

        *real_port = index;
        *(real_port+1) = value;
    }
}

// ******************************************************************
// * xvga_set320x240
// ******************************************************************
void xvga_set320x240()
{
    uint32 v = 0;

    for(v=0;v<sizeof(mode_320x240);v++)
        write_vgareg( mode_320x240[v].port, mode_320x240[v].index, mode_320x240[v].value );
}
