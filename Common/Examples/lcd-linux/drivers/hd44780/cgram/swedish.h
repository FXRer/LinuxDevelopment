/* swedish.h
 *
 * $Id: swedish.h,v 1.2 2006/12/12 16:04:03 mjona Exp $
 *
 * Swedish characters for lcdmod
 *
 * Thanks to Erik Zetterberg <mr.z@linux.se>
 *
 * Description: Adds support for the last three last letters in the
 * swedish alphabet (a/A with ring above, a/A with diaeresis and o/O
 * with diaeresis). And maps the location of where they should be
 * according to the ISO-8859-1 character set to their location in CGRAM.
 *
 */

static void init_charmap(void)
{
	charmap[ 0xe5 ] = 0;
	charmap[ 0xe4 ] = 1;
	charmap[ 0xf6 ] = 2;
	charmap[ 0xc5 ] = 3;
	charmap[ 0xc4 ] = 4;
	charmap[ 0xd6 ] = 5;
}

static unsigned char cg0[] = { 0x04, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f, 0x00 };
static unsigned char cg1[] = { 0x0a, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f, 0x00 };
static unsigned char cg2[] = { 0x0a, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e, 0x00 };
static unsigned char cg3[] = { 0x04, 0x00, 0x0e, 0x11, 0x1f, 0x11, 0x11, 0x00 };
static unsigned char cg4[] = { 0x0a, 0x00, 0x0e, 0x11, 0x1f, 0x11, 0x11, 0x00 };
static unsigned char cg5[] = { 0x0a, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e, 0x00 };
static unsigned char cg6[] = { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f };
static unsigned char cg7[] = { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f };