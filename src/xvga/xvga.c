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
#include "xvga_def.h"

// ******************************************************************
// * static functions
// ******************************************************************
static void init_unchained(void);
static void write_vgareg(int port, int index, int value);

// ******************************************************************
// * init_unchained
// ******************************************************************
void init_unchained(void)
{
    uint08 x;

    CRTC_WRITE(CRTC_REG_INDEX, 0x11);

    x = CRTC_READ(CRTC_REG_DATA) & 0x7F;

    CRTC_WRITE(CRTC_REG_INDEX, 0x11);

    CRTC_WRITE(CRTC_REG_DATA, x);
}

// ******************************************************************
// * write_vgareg
// ******************************************************************
void write_vgareg(int port, int index, int value)
{
    if(port == 0x03C0)
    {
        CRTC_WRITE(CRTC_REG_INDEX, index | 0x20);
        CRTC_WRITE(CRTC_REG_INDEX, value);
    }
    else if(port == 0x03C2)
    {
        MISC_WRITE(MISC_REG, value);
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
	
        real_port[0] = index;
        real_port[1] = value;
    }
}

// ******************************************************************
// * xvga_set256x240
// ******************************************************************
void xvga_set256x240()
{
    uint32 v = 0;

    init_unchained();

    for(v=0;v<MODE256x240SIZE;v++)
        write_vgareg(mode_256x240[v].port, mode_256x240[v].index, mode_256x240[v].value);
}


// ******************************************************************
// * xvga_set320x240
// ******************************************************************
void xvga_set320x240()
{
    uint32 v = 0;

    init_unchained();

    for(v=0;v<MODE320x240SIZE;v++)
        write_vgareg(mode_320x240[v].port, mode_320x240[v].index, mode_320x240[v].value);
}


// ******************************************************************
// * xvga_set320x200
// ******************************************************************
void xvga_set320x200()
{
    uint32 v = 0;

    init_unchained();

    for(v=0;v<MODE320x200SIZE;v++)
        write_vgareg(mode_320x200[v].port, mode_320x200[v].index, mode_320x200[v].value);
}

// ******************************************************************
// * xvga_wait_vblank
// ******************************************************************
void xvga_wait_vblank()
{
    // wait until we are not vblank
    while(CRTC_READ(VERTICAL_BLANK) & 0x08);

    // wait until we are in vblank
    while(CRTC_READ(VERTICAL_BLANK) ^ 0x08);
}