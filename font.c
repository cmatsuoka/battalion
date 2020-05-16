/*
 * (c) Copyright 1993, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
#include "tk.h"
#include "string.h"


enum {
    FONT_BEGIN = 1,
    FONT_NEXT,
    FONT_END,
    FONT_ADVANCE
};
#define MAX_STROKES 256
#define END_OF_LIST 256

/* 0.0513 */
#define STROKE_SCALE 0.045

/*#define STROKE_SCALE 1.71*/


GLint strokeFont[][1+MAX_STROKES*3] = {
    {
	1,
	FONT_BEGIN, 0, 4,
	FONT_NEXT, 2, 2,
	FONT_END, 4, 4,
	FONT_BEGIN, 2, 8,
	FONT_END, 2, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	2,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 3, 5,
	FONT_END, 4, 6,
	FONT_BEGIN, 3, 5,
	FONT_NEXT, 3, 3,
	FONT_END, 4, 2,
	FONT_BEGIN, 3, 3,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	3,
	FONT_BEGIN, 0, 0,
	FONT_NEXT, 1, 1,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 5, 5,
	FONT_NEXT, 4, 4,
	FONT_END, 1, 4,
	FONT_BEGIN, 4, 4,
	FONT_NEXT, 5, 3,
	FONT_NEXT, 4, 2,
	FONT_END, 1, 2,
	FONT_ADVANCE, 7, 0
    },
    {
	4,
	FONT_BEGIN, 0, 4,
	FONT_NEXT, 2, 6,
	FONT_END, 4, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	5,
	FONT_BEGIN, 0, 5,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	6,
	FONT_BEGIN, 1, 4,
	FONT_END, 3, 4,
	FONT_BEGIN, 3, 6,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 1, 3,
	FONT_NEXT, 2, 2,
	FONT_END, 3, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	7,
	FONT_BEGIN, 1, 2,
	FONT_END, 1, 6,
	FONT_BEGIN, 0, 6,
	FONT_END, 4, 6,
	FONT_BEGIN, 3, 6,
	FONT_END, 3, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	8,
	FONT_BEGIN, 0, 2,
	FONT_END, 2, 4,
	FONT_BEGIN, 0, 7,
	FONT_NEXT, 0, 6,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	10,
	FONT_ADVANCE, 0, -9
    },
    {
	11,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 1, 1,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 2, 7,
	FONT_NEXT, 3, 8,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	12,
	FONT_BEGIN, 0, 3,
	FONT_END, 4, 3,
	FONT_BEGIN, 4, 6,
	FONT_END, 0, 6,
	FONT_BEGIN, 2, 8,
	FONT_END, 2, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	14,
	FONT_BEGIN, 1, 3,
	FONT_NEXT, 2, 4,
	FONT_NEXT, 2, 5,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 3,
	FONT_END, 2, 4,
	FONT_BEGIN, 2, 5,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 0, 4,
	FONT_END, 1, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	15,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 0, 4,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 3, 5,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 2, 8,
	FONT_END, 1, 8,
	FONT_BEGIN, 4, 4,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	16,
	FONT_BEGIN, 4, 7,
	FONT_NEXT, 1, 7,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 0, 4,
	FONT_NEXT, 1, 3,
	FONT_END, 4, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	17,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 3, 3,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 3, 7,
	FONT_END, 0, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	18,
	FONT_BEGIN, 0, 4,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 7,
	FONT_NEXT, 3, 7,
	FONT_NEXT, 4, 6,
	FONT_END, 4, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	19,
	FONT_BEGIN, 0, 7,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 4,
	FONT_NEXT, 3, 4,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	20,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 2, 2,
	FONT_END, 4, 8,
	FONT_BEGIN, 3, 6,
	FONT_END, 1, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	21,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 4, 2,
	FONT_NEXT, 4, 5,
	FONT_END, 1, 5,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 4, 8,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	22,
	FONT_BEGIN, 0, 4,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 7,
	FONT_NEXT, 3, 7,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 3,
	FONT_NEXT, 1, 3,
	FONT_END, 0, 4,
	FONT_BEGIN, 1, 4,
	FONT_END, 3, 6,
	FONT_BEGIN, 1, 6,
	FONT_END, 3, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	23,
	FONT_BEGIN, 2, 0,
	FONT_NEXT, 0, 2,
	FONT_NEXT, 4, 6,
	FONT_END, 2, 8,
	FONT_BEGIN, 0, 6,
	FONT_END, 4, 6,
	FONT_BEGIN, 0, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	24,
	FONT_BEGIN, 0, 0,
	FONT_END, 4, 0,
	FONT_ADVANCE, 6, 0
    },
    {
	25,
	FONT_BEGIN, 2, 3,
	FONT_NEXT, 4, 5,
	FONT_END, 2, 7,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	26,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 1, 9,
	FONT_NEXT, 2, 9,
	FONT_NEXT, 2, 8,
	FONT_NEXT, 3, 8,
	FONT_END, 4, 9,
	FONT_ADVANCE, 6, 0
    },
    {
	27,
	FONT_BEGIN, 0, 1,
	FONT_END, 4, 7,
	FONT_BEGIN, 4, 5,
	FONT_END, 0, 5,
	FONT_BEGIN, 0, 3,
	FONT_END, 4, 3,
	FONT_ADVANCE, 6, 1
    },
    {
	28,
	FONT_BEGIN, 1, 2,
	FONT_END, 3, 2,
	FONT_BEGIN, 3, 4,
	FONT_NEXT, 1, 6,
	FONT_END, 3, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	29,
	FONT_BEGIN, 1, 2,
	FONT_END, 3, 2,
	FONT_BEGIN, 1, 4,
	FONT_NEXT, 3, 6,
	FONT_END, 1, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	30,
	FONT_BEGIN, 0, 3,
	FONT_END, 4, 3,
	FONT_BEGIN, 4, 5,
	FONT_END, 0, 5,
	FONT_BEGIN, 0, 7,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	31,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 2, 4,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	32,
	FONT_ADVANCE, 6, 0
    },
    {
	33,
	FONT_BEGIN, 2, 1,
	FONT_END, 2, 2,
	FONT_BEGIN, 2, 4,
	FONT_END, 2, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	34,
	FONT_BEGIN, 1, 7,
	FONT_END, 1, 9,
	FONT_BEGIN, 3, 9,
	FONT_END, 3, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	35,
	FONT_BEGIN, 1, 2,
	FONT_END, 1, 7,
	FONT_BEGIN, 3, 7,
	FONT_END, 3, 2,
	FONT_BEGIN, 4, 3,
	FONT_END, 0, 3,
	FONT_BEGIN, 0, 6,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	36,
	FONT_BEGIN, 2, 1,
	FONT_END, 2, 9,
	FONT_BEGIN, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 3, 5,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 2,
	FONT_NEXT, 3, 1,
	FONT_NEXT, 1, 1,
	FONT_END, 0, 2,
	FONT_ADVANCE, 6, -1
    },
    {
	37,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 4, 7,
	FONT_END, 4, 8,
	FONT_BEGIN, 1, 8,
	FONT_NEXT, 0, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 7,
	FONT_END, 1, 8,
	FONT_BEGIN, 4, 3,
	FONT_NEXT, 5, 3,
	FONT_NEXT, 5, 2,
	FONT_NEXT, 4, 2,
	FONT_END, 5, 2,
	FONT_ADVANCE, 8, 1
    },
    {
	38,
	FONT_BEGIN, 4, 4,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 4,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 2, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 6,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	39,
	FONT_BEGIN, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 1, 9,
	FONT_NEXT, 2, 9,
	FONT_NEXT, 2, 8,
	FONT_END, 1, 8,
	FONT_ADVANCE, 6, 1
    },
    {
	40,
	FONT_BEGIN, 4, 2,
	FONT_NEXT, 2, 4,
	FONT_NEXT, 2, 6,
	FONT_END, 4, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	41,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 2, 4,
	FONT_NEXT, 2, 6,
	FONT_END, 0, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	42,
	FONT_BEGIN, 2, 2,
	FONT_END, 2, 8,
	FONT_BEGIN, 0, 7,
	FONT_END, 4, 3,
	FONT_BEGIN, 4, 5,
	FONT_END, 0, 5,
	FONT_BEGIN, 0, 3,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	43,
	FONT_BEGIN, 2, 3,
	FONT_END, 2, 7,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	44,
	FONT_BEGIN, 0, 1,
	FONT_NEXT, 1, 2,
	FONT_END, 1, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	45,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	46,
	FONT_BEGIN, 1, 2,
	FONT_END, 2, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	47,
	FONT_BEGIN, 0, 3,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	48,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	49,
	FONT_BEGIN, 1, 2,
	FONT_END, 3, 2,
	FONT_BEGIN, 2, 2,
	FONT_NEXT, 2, 8,
	FONT_END, 1, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	50,
	FONT_BEGIN, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 0, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	51,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 5,
	FONT_END, 2, 5,
	FONT_BEGIN, 3, 5,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_END, 0, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	52,
	FONT_BEGIN, 3, 2,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 0, 4,
	FONT_END, 4, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	53,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 0, 8,
	FONT_END, 4, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	54,
	FONT_BEGIN, 0, 5,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 5,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 2, 8,
	FONT_END, 3, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	55,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 4, 8,
	FONT_NEXT, 2, 4,
	FONT_END, 2, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	56,
	FONT_BEGIN, 1, 5,
	FONT_NEXT, 0, 4,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 5,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 6,
	FONT_END, 3, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	57,
	FONT_BEGIN, 1, 2,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	58,
	FONT_BEGIN, 0, 3,
	FONT_END, 1, 3,
	FONT_BEGIN, 1, 6,
	FONT_END, 0, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	59,
	FONT_BEGIN, 0, 1,
	FONT_NEXT, 1, 2,
	FONT_END, 1, 3,
	FONT_BEGIN, 1, 6,
	FONT_END, 0, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	60,
	FONT_BEGIN, 3, 3,
	FONT_NEXT, 1, 5,
	FONT_END, 3, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	61,
	FONT_BEGIN, 0, 4,
	FONT_END, 4, 4,
	FONT_BEGIN, 4, 6,
	FONT_END, 0, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	62,
	FONT_BEGIN, 1, 7,
	FONT_NEXT, 3, 5,
	FONT_END, 1, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	63,
	FONT_BEGIN, 1, 2,
	FONT_END, 2, 2,
	FONT_BEGIN, 2, 4,
	FONT_NEXT, 2, 5,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_END, 0, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	64,
	FONT_BEGIN, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 2, 4,
	FONT_NEXT, 2, 6,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	65,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_END, 4, 2,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	66,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 3, 5,
	FONT_END, 0, 5,
	FONT_BEGIN, 3, 5,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 0, 8,
	FONT_END, 0, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	67,
	FONT_BEGIN, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_END, 4, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	68,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_END, 0, 8,
	FONT_BEGIN, 1, 8,
	FONT_END, 1, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	69,
	FONT_BEGIN, 4, 2,
	FONT_NEXT, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_END, 4, 8,
	FONT_BEGIN, 3, 5,
	FONT_END, 0, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	70,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_END, 4, 8,
	FONT_BEGIN, 3, 5,
	FONT_END, 0, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	71,
	FONT_BEGIN, 3, 4,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	72,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 8,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_BEGIN, 4, 8,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	73,
	FONT_BEGIN, 1, 2,
	FONT_END, 3, 2,
	FONT_BEGIN, 2, 2,
	FONT_END, 2, 8,
	FONT_BEGIN, 1, 8,
	FONT_END, 3, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	74,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_END, 4, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	75,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 8,
	FONT_BEGIN, 4, 8,
	FONT_NEXT, 1, 5,
	FONT_END, 4, 2,
	FONT_ADVANCE, 8, 0
    },
    {
	76,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 0, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	77,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 4, 8,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	78,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_NEXT, 4, 2,
	FONT_END, 4, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	79,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	80,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 3, 5,
	FONT_END, 0, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	81,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_BEGIN, 2, 5,
	FONT_END, 4, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	82,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 8,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 4, 7,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 3, 5,
	FONT_END, 0, 5,
	FONT_BEGIN, 1, 5,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	83,
	FONT_BEGIN, 4, 7,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 0, 7,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 3, 5,
	FONT_NEXT, 4, 4,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	84,
	FONT_BEGIN, 0, 8,
	FONT_END, 4, 8,
	FONT_BEGIN, 2, 8,
	FONT_END, 2, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	85,
	FONT_BEGIN, 0, 3,
	FONT_END, 0, 8,
	FONT_BEGIN, 4, 8,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	86,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	87,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 8,
	FONT_BEGIN, 4, 8,
	FONT_NEXT, 4, 2,
	FONT_NEXT, 2, 4,
	FONT_END, 0, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	88,
	FONT_BEGIN, 0, 2,
	FONT_END, 4, 8,
	FONT_BEGIN, 0, 8,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	89,
	FONT_BEGIN, 2, 2,
	FONT_NEXT, 2, 5,
	FONT_END, 0, 8,
	FONT_BEGIN, 4, 8,
	FONT_END, 2, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	90,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 4, 8,
	FONT_NEXT, 0, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	91,
	FONT_BEGIN, 3, 1,
	FONT_NEXT, 1, 1,
	FONT_NEXT, 1, 9,
	FONT_END, 3, 9,
	FONT_ADVANCE, 6, 0
    },
    {
	92,
	FONT_BEGIN, 0, 7,
	FONT_END, 4, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	93,
	FONT_BEGIN, 1, 9,
	FONT_NEXT, 3, 9,
	FONT_NEXT, 3, 1,
	FONT_END, 1, 1,
	FONT_ADVANCE, 6, 0
    },
    {
	94,
	FONT_BEGIN, 2, 2,
	FONT_END, 2, 8,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 2, 8,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	95,
	FONT_BEGIN, 2, 3,
	FONT_NEXT, 0, 5,
	FONT_END, 2, 7,
	FONT_BEGIN, 0, 5,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	96,
	FONT_BEGIN, 3, 8,
	FONT_NEXT, 2, 8,
	FONT_NEXT, 2, 9,
	FONT_NEXT, 3, 9,
	FONT_NEXT, 3, 8,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	97,
	FONT_BEGIN, 1, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 4, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 4,
	FONT_END, 4, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	98,
	FONT_BEGIN, 0, 8,
	FONT_NEXT, 0, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 3, 6,
	FONT_END, 0, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	99,
	FONT_BEGIN, 4, 5,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	100,
	FONT_BEGIN, 4, 8,
	FONT_NEXT, 4, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	101,
	FONT_BEGIN, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 3, 4,
	FONT_END, 0, 4,
	FONT_ADVANCE, 6, 0
    },
    {
	102,
	FONT_BEGIN, 1, 2,
	FONT_NEXT, 1, 7,
	FONT_NEXT, 2, 8,
	FONT_NEXT, 3, 8,
	FONT_END, 4, 7,
	FONT_BEGIN, 2, 5,
	FONT_END, 0, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	103,
	FONT_BEGIN, 1, 0,
	FONT_NEXT, 3, 0,
	FONT_NEXT, 4, 1,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	104,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 8,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	105,
	FONT_BEGIN, 2, 2,
	FONT_END, 2, 5,
	FONT_BEGIN, 2, 6,
	FONT_END, 2, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	106,
	FONT_BEGIN, 0, 1,
	FONT_NEXT, 1, 0,
	FONT_NEXT, 3, 0,
	FONT_NEXT, 4, 1,
	FONT_END, 4, 5,
	FONT_BEGIN, 4, 6,
	FONT_END, 4, 7,
	FONT_ADVANCE, 6, 0
    },
    {
	107,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 8,
	FONT_BEGIN, 4, 6,
	FONT_NEXT, 2, 4,
	FONT_END, 0, 4,
	FONT_BEGIN, 2, 4,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	108,
	FONT_BEGIN, 1, 2,
	FONT_END, 1, 8,
	FONT_ADVANCE, 6, 0
    },
    {
	109,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 2, 5,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 2,
	FONT_BEGIN, 2, 2,
	FONT_END, 2, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	110,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 1, 5,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	111,
	FONT_BEGIN, 0, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	112,
	FONT_BEGIN, 0, 0,
	FONT_NEXT, 0, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 2,
	FONT_END, 0, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	113,
	FONT_BEGIN, 4, 2,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 4, 5,
	FONT_END, 4, 0,
	FONT_ADVANCE, 6, 0
    },
    {
	114,
	FONT_BEGIN, 0, 2,
	FONT_END, 0, 6,
	FONT_BEGIN, 0, 4,
	FONT_NEXT, 2, 6,
	FONT_NEXT, 3, 6,
	FONT_END, 4, 5,
	FONT_ADVANCE, 6, 0
    },
    {
	115,
	FONT_BEGIN, 0, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_NEXT, 3, 4,
	FONT_NEXT, 1, 4,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 1, 6,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	116,
	FONT_BEGIN, 0, 6,
	FONT_END, 4, 6,
	FONT_BEGIN, 2, 8,
	FONT_NEXT, 2, 3,
	FONT_NEXT, 3, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	117,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	118,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 0, 4,
	FONT_NEXT, 2, 2,
	FONT_NEXT, 4, 4,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	119,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 0, 3,
	FONT_NEXT, 1, 2,
	FONT_NEXT, 2, 3,
	FONT_NEXT, 3, 2,
	FONT_NEXT, 4, 3,
	FONT_END, 4, 6,
	FONT_ADVANCE, 6, 0
    },
    {
	120,
	FONT_BEGIN, 0, 2,
	FONT_END, 4, 6,
	FONT_BEGIN, 0, 6,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	121,
	FONT_BEGIN, 0, 0,
	FONT_NEXT, 4, 4,
	FONT_END, 4, 6,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 0, 4,
	FONT_END, 2, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	122,
	FONT_BEGIN, 0, 6,
	FONT_NEXT, 4, 6,
	FONT_NEXT, 0, 2,
	FONT_END, 4, 2,
	FONT_ADVANCE, 6, 0
    },
    {
	123,
	FONT_BEGIN, 4, 9,
	FONT_NEXT, 3, 8,
	FONT_NEXT, 3, 6,
	FONT_NEXT, 2, 5,
	FONT_NEXT, 3, 4,
	FONT_NEXT, 3, 2,
	FONT_END, 4, 1,
	FONT_ADVANCE, 6, 0
    },
    {
	124,
	FONT_BEGIN, 2, 9,
	FONT_END, 2, 0,
	FONT_ADVANCE, 6, 0
    },
    {
	125,
	FONT_BEGIN, 2, 2,
	FONT_NEXT, 2, 3,
	FONT_NEXT, 0, 5,
	FONT_NEXT, 2, 7,
	FONT_END, 2, 8,
	FONT_BEGIN, 2, 7,
	FONT_NEXT, 4, 5,
	FONT_END, 2, 3,
	FONT_ADVANCE, 6, 0
    },
    {
	126,
	FONT_BEGIN, 0, 9,
	FONT_NEXT, 1, 8,
	FONT_NEXT, 1, 6,
	FONT_NEXT, 2, 5,
	FONT_NEXT, 1, 4,
	FONT_NEXT, 1, 2,
	FONT_END, 0, 1,
	FONT_ADVANCE, 6, 0
    },
    {
	END_OF_LIST
    }
};

GLenum tkCreateStrokeFont(GLuint fontBase)
{
    GLint mode, i, j;

    for (i = 0; strokeFont[i][0] != END_OF_LIST; i++) {
	glNewList(fontBase+(unsigned int)strokeFont[i][0], GL_COMPILE);
	for (j = 1; mode = strokeFont[i][j]; j += 3) {
	    if (mode == FONT_BEGIN) {
		glBegin(GL_LINE_STRIP);
		glVertex2f((float)strokeFont[i][j+1]*STROKE_SCALE,
			   (float)strokeFont[i][j+2]*STROKE_SCALE);
	    } else if (mode == FONT_NEXT) {
		glVertex2f((float)strokeFont[i][j+1]*STROKE_SCALE,
			   (float)strokeFont[i][j+2]*STROKE_SCALE);
	    } else if (mode == FONT_END) {
		glVertex2f((float)strokeFont[i][j+1]*STROKE_SCALE,
			   (float)strokeFont[i][j+2]*STROKE_SCALE);
		glEnd();
	    } else if (mode == FONT_ADVANCE) {
		glTranslatef((float)strokeFont[i][j+1]*STROKE_SCALE,
			     (float)strokeFont[i][j+2]*STROKE_SCALE, 0.0);
		break;
	    }
	}
	glEndList();
    }
    return GL_TRUE;
}


void tkDrawStr(GLuint base, char *str)
{

    glPushAttrib(GL_LIST_BIT);
    glListBase(base);
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, (unsigned char *)str);
    glPopAttrib();
}
