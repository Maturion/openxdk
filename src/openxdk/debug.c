//
//	Debug output scrolling code submitted by Robin Mulloy
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <openxdk/debug.h>

#define FONT_WIDTH      8
#define FONT_HEIGHT     8
#define MARGIN         25
#define MARGINS        50 // MARGIN*2

int SCREEN_WIDTH	= 640;
int SCREEN_HEIGHT	= 480;
int SCREEN_BPP = 32;

int nextRow = MARGIN;
int nextCol = MARGIN; 

// a very simple 256 char bitmapped font
// that was blatantly liberated from the 
// www.svgalib.org site. Graciously provided
// by John Remyn, originally distributed
// with sasteroids.
static unsigned char systemFont[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,56,56,56,56,56,0,56,56,
	108,108,0,0,0,0,0,0,0,108,254,254,108,254,254,108,
	48,126,224,124,14,254,252,48,98,230,204,24,48,102,206,140,
	120,220,252,120,250,222,252,118,28,28,56,0,0,0,0,0,
	14,28,28,28,28,28,28,14,112,56,56,56,56,56,56,112,
	0,0,0,230,124,56,124,206,0,0,28,28,127,127,28,28,
	0,0,0,0,0,28,28,56,0,0,0,0,124,124,0,0,
	0,0,0,0,0,0,56,56,28,28,56,56,112,112,224,224,
	124,254,238,238,238,254,254,124,56,120,248,56,56,254,254,254,
	252,254,14,60,112,254,254,254,252,254,14,60,14,254,254,252,
	238,238,238,254,254,14,14,14,254,254,224,252,14,254,254,252,
	124,252,224,252,238,254,254,124,252,254,14,14,28,28,56,56,
	124,254,238,124,238,254,254,124,124,254,238,126,14,254,254,252,
	0,0,28,28,0,28,28,28,0,0,28,28,0,28,28,56,
	6,14,28,56,56,28,14,6,0,0,124,124,0,124,124,124,
	112,56,28,14,14,28,56,112,124,254,206,28,56,0,56,56,
	124,198,190,182,190,182,200,126,124,254,238,254,238,238,238,238,
	252,254,206,252,206,254,254,252,124,254,238,224,238,254,254,124,
	252,254,238,238,238,254,254,252,254,254,224,248,224,254,254,254,
	126,254,224,248,224,224,224,224,126,254,224,238,238,254,254,124,
	238,238,238,254,238,238,238,238,254,254,56,56,56,254,254,254,
	254,254,14,14,238,254,254,124,238,238,252,248,252,238,238,238,
	224,224,224,224,224,254,254,126,130,198,238,254,254,238,238,238,
	206,238,254,254,254,254,238,230,124,254,238,238,238,254,254,124,
	252,254,238,238,252,224,224,224,124,254,238,238,254,254,252,118,
	252,254,238,238,252,238,238,238,126,254,224,124,14,254,254,252,
	254,254,56,56,56,56,56,56,238,238,238,238,238,254,254,124,
	238,238,238,238,238,238,124,56,238,238,238,254,254,238,198,130,
	238,238,124,56,124,238,238,238,238,238,124,124,56,56,112,112,
	254,254,28,56,112,254,254,254,124,124,112,112,112,124,124,124,
	112,112,56,56,28,28,14,14,124,124,28,28,28,124,124,124,
	56,124,238,198,0,0,0,0,0,0,0,0,0,254,254,254,
	56,56,28,0,0,0,0,0,0,124,254,238,254,238,238,238,
	0,252,254,206,252,206,254,252,0,124,254,238,224,238,254,124,
	0,252,254,238,238,238,254,252,0,254,254,224,248,224,254,254,
	0,126,254,224,248,224,224,224,0,126,254,224,238,238,254,124,
	0,238,238,238,254,238,238,238,0,254,254,56,56,56,254,254,
	0,254,254,14,14,238,254,124,0,238,238,252,248,252,238,238,
	0,224,224,224,224,224,254,126,0,130,198,238,254,254,238,238,
	0,206,238,254,254,254,238,230,0,124,254,238,238,238,254,124,
	0,252,254,238,238,252,224,224,0,124,254,238,238,254,252,118,
	0,252,254,238,238,252,238,238,0,126,254,224,124,14,254,252,
	0,254,254,56,56,56,56,56,0,238,238,238,238,238,254,124,
	0,238,238,238,238,238,124,56,0,238,238,238,254,238,198,130,
	0,238,238,124,56,124,238,238,0,238,238,124,124,56,56,112,
	0,254,254,28,56,112,254,254,60,124,112,112,112,124,124,60,
	56,56,56,0,56,56,56,56,120,124,28,28,28,124,124,120,
	236,254,118,0,0,0,0,0,0,16,56,124,254,254,254,254,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void drawChar(unsigned char c, int x, int y, int fgColour, int bgColour)
{
	char *videoBuffer = XVideoGetFB();
	videoBuffer += (y * SCREEN_WIDTH + x) * (SCREEN_BPP >> 3);

	unsigned char mask;
	unsigned char *font = systemFont + (c * FONT_WIDTH);
	int colourToDraw;

	for (int h = 0; h < FONT_HEIGHT; h++)
	{
		mask = 0x80;
		for (int w = 0; w < FONT_WIDTH; w++)
		{
			if ((*font) & mask)
			{
				colourToDraw = fgColour;
			}
			else
			{
				colourToDraw = bgColour;
			}
			switch (SCREEN_BPP)
			{
				case 32:
					*((int*)videoBuffer) = colourToDraw;
					videoBuffer += sizeof(int);
					break;
				case 16:
					*((short*)videoBuffer) = colourToDraw & 0xFFFF;
					videoBuffer += sizeof(short);
					break;
			}
			mask >>= 1;
		}
		
		videoBuffer += (SCREEN_WIDTH-FONT_WIDTH)  * (SCREEN_BPP >> 3);
		font++;
	}
}

// given an unsigned nibble (4 bits) between 0x00 to 0x0F, return '0' to 'F'
char n2c(int byte)
{
	switch(byte)
	{
		case 0x00: return '0';
		case 0x01: return '1';
		case 0x02: return '2';
		case 0x03: return '3';
		case 0x04: return '4';
		case 0x05: return '5';
		case 0x06: return '6';
		case 0x07: return '7';
		case 0x08: return '8';
		case 0x09: return '9';
		case 0x0A: return 'A';
		case 0x0B: return 'B';
		case 0x0C: return 'C';
		case 0x0D: return 'D';
		case 0x0E: return 'E';
		case 0x0F: return 'F';
		default: return '?';
	}
}

void debugPrintNum(int i)
{
	char num[11];
	num[0] = '0';
	num[1] = 'x';
	num[2] = n2c((i >> 28) & 0x0F);
	num[3] = n2c((i >> 24) & 0x0F);
	num[4] = n2c((i >> 20) & 0x0F);
	num[5] = n2c((i >> 16) & 0x0F);
	num[6] = n2c((i >> 12) & 0x0F);
	num[7] = n2c((i >> 8) & 0x0F);
	num[8] = n2c((i >> 4) & 0x0F);
	num[9] = n2c((i >> 0) & 0x0F);
	num[10] = 0;
	debugPrint(num);
}

void debugPrintBinary( int num )
{
   int x = 0;
   char binNum[50] = {0};
   for( int i=31;i>=0;i-- )
   {
      binNum[x++] = 0x30 + ((num & (0x01 << i))?1:0);
      if( (i%4) == 0 ) 
         binNum[x++] = ' ';
   }
   binNum[x] = 0;
   debugPrint( binNum );
}

void debugPrint(char *format, ...)
{
	char buffer[512];
	unsigned short len;
	va_list argList;
	va_start(argList, format);
	vsprintf(buffer, format, argList);
	va_end(argList);
	
	VIDEO_MODE vm = XVideoGetMode();
	SCREEN_WIDTH = vm.width;
	SCREEN_HEIGHT = vm.height;
	SCREEN_BPP = vm.bpp;
	int fgColour;
	int bgColour;
	switch (SCREEN_BPP) {
	case 32:
		fgColour = WHITE;
		bgColour = BLACK;
		break;
	case 16:
		fgColour = WHITE_16BPP;
		bgColour = BLACK_16BPP;
	}

	unsigned char *s = buffer;
	while (*s)
	{
		if( nextRow >= (SCREEN_HEIGHT-MARGINS) )
			advanceScreen();
		
		if (*s == '\n')
		{
			nextRow += FONT_HEIGHT+1;
			nextCol = MARGIN;
		}
		else
		{
			drawChar( *s, nextCol, nextRow, fgColour, bgColour );

			nextCol += FONT_WIDTH+1;
			if( nextCol > (SCREEN_WIDTH-MARGINS))
			{
				nextRow += FONT_HEIGHT+1;
				nextCol  = MARGIN;
			}
		}

		s++;
	}
}

void advanceScreen( void )
{
	int pixelSize = SCREEN_BPP >> 3;
	int screenSize  = SCREEN_WIDTH * (SCREEN_HEIGHT - MARGINS)  * pixelSize;
	int lineSize    = SCREEN_WIDTH * (FONT_HEIGHT + 1) * pixelSize;
	
	char* thisScreen = XVideoGetFB() + (SCREEN_WIDTH * MARGIN)  * pixelSize;
	char* prevScreen = thisScreen+lineSize;
    	
	memmove(thisScreen, prevScreen, screenSize);

	nextRow -= (FONT_HEIGHT+1);
	nextCol  = MARGIN; 
}

void debugClearScreen( void )
{
	char* videoBuffer = XVideoGetFB();

	memset( videoBuffer, 0, (SCREEN_BPP >> 3) * (SCREEN_WIDTH * SCREEN_HEIGHT) );
	nextRow = MARGIN;
	nextCol = MARGIN; 
}

void debugPrintHex(char *buffer, int length)
{
	char tmp[10];
	for (int i = 0; i < length; i++)
	{
		sprintf(tmp, "%02x ", buffer[i]);
		debugPrint(tmp);
	}
}
