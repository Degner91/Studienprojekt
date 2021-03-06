/**
 ******************************************************************************
 * @file    Font_Helvetica_16.c
 * @author  Auto-generated
 * @version V1.0.0
 * @date    08.06.2017
 * @brief   Auto-generated font
 * @copyright
 * Copyright (c) FH O� Forschungs und Entwicklungs GmbH, thermocollect
 * You may not use or copy this file except with written permission of the owners.
 ******************************************************************************
 */

#include "Font_Helvetica_16.h"

/* Bitmaps for all available characters */

static const uint32_t bm_0[] = /**< char:   */
{
	0x00000000, 0xe7f80000, 0xe9fe739c, 0xfe5e9325, 0x7f9ce739, 0x00000000, 0x00000000
};

static const uint32_t bm_1[] = /**< char: ! */
{
	0x9ce00000, 0x6319ce73, 0x00007380, 0x00000000
};

static const uint32_t bm_2[] = /**< char: " */
{
	0xe0000000, 0x007cf9f3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_3[] = /**< char: # */
{
	0x00000000, 0x8360d800, 0xf1fc360d, 0xfe3f8fe7, 0x1b06c1b0, 0x00000000, 0x00000000
};

static const uint32_t bm_4[] = /**< char: $ */
{
	0x00000000, 0xff0fc0e0, 0x7e3fc7f8, 0xe07f07e0, 0xf9ff3f63, 0x80f83f87, 0x00000003, 0x00000000
};

static const uint32_t bm_5[] = /**< char: % */
{
	0x00000000, 0x00000000, 0x9fc387c0, 0x7703bb83, 0xf807fe07, 0x01fee0ff, 0x0eee077e, 0x1f9c1dce, 0x00003e1c, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_6[] = /**< char: & */
{
	0x00000000, 0x0f800000, 0xe07703f8, 0x0f80f807, 0xe1f70ff0, 0xff879c3c, 0x00007fe1, 0x00000000, 0x00000000
};

static const uint32_t bm_7[] = /**< char: ' */
{
	0x9ce00000, 0x00000073, 0x00000000, 0x00000000
};

static const uint32_t bm_8[] = /**< char: ( */
{
	0x80000000, 0x0e1870c3, 0x70e1c387, 0x0c1c1830, 0x0000000e
};

static const uint32_t bm_9[] = /**< char: ) */
{
	0xe0000000, 0x18387060, 0xc3870e0c, 0x861c3860, 0x00000003
};

static const uint32_t bm_10[] = /**< char: * */
{
	0x00000000, 0x3f9fc380, 0x00006c3e, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_11[] = /**< char: + */
{
	0x00000000, 0x00000000, 0xc0701c00, 0xfe7f9fe1, 0x1c0701c1, 0x00000000, 0x00000000
};

static const uint32_t bm_12[] = /**< char: , */
{
	0x00000000, 0x00000000, 0x18cc7380, 0x00000000
};

static const uint32_t bm_13[] = /**< char: - */
{
	0x00000000, 0x00000000, 0x03e7cf80, 0x00000000, 0x00000000
};

static const uint32_t bm_14[] = /**< char: . */
{
	0x00000000, 0x00000000, 0x00007380, 0x00000000
};

static const uint32_t bm_15[] = /**< char: / */
{
	0x00000000, 0x181c0c00, 0xe0607038, 0x0381c0c0, 0x00000703, 0x00000000
};

static const uint32_t bm_16[] = /**< char: 0 */
{
	0x00000000, 0xfe0fc000, 0x8e71c738, 0x1ce39c73, 0xf0e738e7, 0x00001f87, 0x00000000, 0x00000000
};

static const uint32_t bm_17[] = /**< char: 1 */
{
	0x00000000, 0x7e7e7e70, 0x70707070, 0x70707070, 0x00000000, 0x00000000
};

static const uint32_t bm_18[] = /**< char: 2 */
{
	0x00000000, 0xfe1fc000, 0x8e71ce38, 0xf07c0e03, 0xf80f03c1, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_19[] = /**< char: 3 */
{
	0x00000000, 0xfe1fc000, 0xf071ce38, 0x007c0f81, 0xf0c738e7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_20[] = /**< char: 4 */
{
	0x00000000, 0xf01c0000, 0xf83e07c0, 0xfc770ee1, 0x01ff3fe7, 0x00003807, 0x00000000, 0x00000000
};

static const uint32_t bm_21[] = /**< char: 5 */
{
	0x00000000, 0xfe1fc000, 0xfc058030, 0x00638fe1, 0xf8c738e7, 0x00001f87, 0x00000000, 0x00000000
};

static const uint32_t bm_22[] = /**< char: 6 */
{
	0x00000000, 0xfe1f8000, 0xfe0dc670, 0x1c638ff1, 0xf0c638e7, 0x00001f87, 0x00000000, 0x00000000
};

static const uint32_t bm_23[] = /**< char: 7 */
{
	0x00000000, 0x381fcfe0, 0xe0707038, 0x0381c0c0, 0x00000e07, 0x00000000
};

static const uint32_t bm_24[] = /**< char: 8 */
{
	0x00000000, 0xff1fc000, 0xfe71ce38, 0x1c7f0fe1, 0xf9c738e7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_25[] = /**< char: 9 */
{
	0x00000000, 0xfe0fc000, 0x8e31c638, 0x70ff1ff3, 0xf0e618e7, 0x00001f87, 0x00000000, 0x00000000
};

static const uint32_t bm_26[] = /**< char: : */
{
	0x00000000, 0x00000e70, 0x00007380, 0x00000000
};

static const uint32_t bm_27[] = /**< char: ; */
{
	0x00000000, 0x00000e70, 0x18cc7380, 0x00000000
};

static const uint32_t bm_28[] = /**< char: < */
{
	0x00000000, 0x00000000, 0xe1e06000, 0x1e0383e3, 0x701f01f0, 0x00000100, 0x00000000
};

static const uint32_t bm_29[] = /**< char: = */
{
	0x00000000, 0x00000000, 0xf8000000, 0xfe7f9fe7, 0x001fe7f9, 0x00000000, 0x00000000
};

static const uint32_t bm_30[] = /**< char: > */
{
	0x00000000, 0x00000000, 0xf01e0180, 0xe0701f01, 0x0383e3e1, 0x00000002, 0x00000000
};

static const uint32_t bm_31[] = /**< char: ? */
{
	0x00000000, 0xfe1fc000, 0x8e71ce38, 0xe0380e03, 0xc0380701, 0x00000e01, 0x00000000, 0x00000000
};

static const uint32_t bm_32[] = /**< char: @ */
{
	0x00000000, 0x00000000, 0xf0ffc07f, 0x7e3ff87f, 0xcf9d9f3f, 0xffc3ffc7, 0x3fe0fbe1, 0x00000fe0, 0x00000000, 0x00000000
};

static const uint32_t bm_33[] = /**< char: A */
{
	0x00000000, 0xe0000000, 0x3e007801, 0x03700fc0, 0xe07f81cc, 0x870ff83f, 0x7039c1c3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_34[] = /**< char: B */
{
	0x00000000, 0x3fe00000, 0x71c387fc, 0x7fc3fe38, 0xe7071ff8, 0xff9c1ce0, 0x00003ff1, 0x00000000, 0x00000000
};

static const uint32_t bm_35[] = /**< char: C */
{
	0x00000000, 0x7f000000, 0x73871ff8, 0x01c00e70, 0xe6070038, 0xff1c38e0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_36[] = /**< char: D */
{
	0x00000000, 0x3fe00000, 0x71c38ffc, 0xc1ce0e30, 0xe3073839, 0xff8e1c70, 0x00001ff0, 0x00000000, 0x00000000
};

static const uint32_t bm_37[] = /**< char: E */
{
	0x00000000, 0xff3fe000, 0xfe01c039, 0x1cff9ff3, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_38[] = /**< char: F */
{
	0x00000000, 0xff3fe000, 0xfe01c039, 0x1c7f8ff1, 0x380700e0, 0x000001c0, 0x00000000, 0x00000000
};

static const uint32_t bm_39[] = /**< char: G */
{
	0x00000000, 0xf8000000, 0xe1c3ff07, 0x9f8e3030, 0x39f8e7e3, 0xc71e0e70, 0x7fc1ffc7, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_40[] = /**< char: H */
{
	0x00000000, 0xe0e00000, 0x73839c1c, 0xffcffe70, 0xe7073ff9, 0x839c1ce0, 0x00007073, 0x00000000, 0x00000000
};

static const uint32_t bm_41[] = /**< char: I */
{
	0x9ce00000, 0xe739ce73, 0x0000739c, 0x00000000
};

static const uint32_t bm_42[] = /**< char: J */
{
	0x00000000, 0x0701c000, 0x01c0701c, 0xce739c07, 0x3f0fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_43[] = /**< char: K */
{
	0x00000000, 0x78e00000, 0x7073879c, 0x0fc07e07, 0xe0f703f8, 0xe3871c1c, 0x00007871, 0x00000000, 0x00000000
};

static const uint32_t bm_44[] = /**< char: L */
{
	0x00000000, 0x0700e000, 0x0e01c038, 0x1c038070, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_45[] = /**< char: M */
{
	0x00000000, 0xe0000000, 0x79e0f3c1, 0x3e7c7cf8, 0xdf9f9f3e, 0xbee76fcf, 0xe739df73, 0x0000739c, 0x00000000, 0x00000000
};

static const uint32_t bm_46[] = /**< char: N */
{
	0x00000000, 0xe0e00000, 0xf38f9c3c, 0xdfce7e71, 0xe7e73bb9, 0xc39f1cfc, 0x00007873, 0x00000000, 0x00000000
};

static const uint32_t bm_47[] = /**< char: O */
{
	0x00000000, 0xf0000000, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_48[] = /**< char: P */
{
	0x00000000, 0xe3fe0000, 0x70e70e3f, 0xfe3fe70e, 0xe00e1fe3, 0x00e00e00, 0x00000000, 0x00000000
};

static const uint32_t bm_49[] = /**< char: Q */
{
	0x00000000, 0xf0000000, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xe70f8e30, 0x3fc0ffc3, 0x00000c00, 0x00000000, 0x00000000
};

static const uint32_t bm_50[] = /**< char: R */
{
	0x00000000, 0xe3fe0000, 0x70e70e3f, 0xfe3fe70e, 0xe70e3fe3, 0x70e70e70, 0x00000000, 0x00000000
};

static const uint32_t bm_51[] = /**< char: S */
{
	0x00000000, 0x3fc00000, 0x71c38ff8, 0x7f803e30, 0xe3871fc0, 0xff1c3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_52[] = /**< char: T */
{
	0x00000000, 0xff3fe000, 0x700e01c1, 0xe01c0380, 0xc0380700, 0x00000e01, 0x00000000, 0x00000000
};

static const uint32_t bm_53[] = /**< char: U */
{
	0x00000000, 0xe0e00000, 0x73839c1c, 0xc1ce0e70, 0xe7073839, 0xff0e3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_54[] = /**< char: V */
{
	0x00000000, 0xe0e00000, 0xe3871c38, 0xe7073838, 0x01f80cc0, 0x7803c03f, 0x00000f00, 0x00000000, 0x00000000
};

static const uint32_t bm_55[] = /**< char: W */
{
	0x00000000, 0x00000000, 0x71ce3860, 0xe738f39c, 0xb877cc33, 0xe1dbf0ed, 0x03e781f7, 0x0f1e078f, 0x00000e1c, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_56[] = /**< char: X */
{
	0x00000000, 0xe1c00000, 0x81ee0e78, 0x3c01f01f, 0x81f80780, 0xc70e703f, 0x000070f3, 0x00000000, 0x00000000
};

static const uint32_t bm_57[] = /**< char: Y */
{
	0x00000000, 0xe0e00000, 0xc1c70e3c, 0x3e03f81d, 0x00700380, 0x3801c00e, 0x00000700, 0x00000000, 0x00000000
};

static const uint32_t bm_58[] = /**< char: Z */
{
	0x00000000, 0xff3fe000, 0xe03c0f01, 0x781e0380, 0xf80701c0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_59[] = /**< char: [ */
{
	0x9e000000, 0xe38e38e7, 0x38e38e38, 0x0001e78e
};

static const uint32_t bm_60[] = /**< char: \ */
{
	0x00000000, 0x070180e0, 0xc070180e, 0x0c070380, 0x00006038, 0x00000000
};

static const uint32_t bm_61[] = /**< char: ] */
{
	0xe0000000, 0x3870e1f3, 0xc3870e1c, 0x9f3870e1, 0x0000000f
};

static const uint32_t bm_62[] = /**< char: ^ */
{
	0x00000000, 0x78070000, 0x9c3b03e0, 0x1ce31ce1, 0x00000006, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_63[] = /**< char: _ */
{
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1fe7f9fe, 0x00000000
};

static const uint32_t bm_64[] = /**< char: ` */
{
	0x0e000000, 0x00000187, 0x00000000, 0x00000000
};

static const uint32_t bm_65[] = /**< char: a */
{
	0x00000000, 0x00000000, 0xfe3f8000, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_66[] = /**< char: b */
{
	0x00000000, 0x0700e000, 0xfe1fc038, 0x1ce38e71, 0xf8e738e7, 0x00001fc7, 0x00000000, 0x00000000
};

static const uint32_t bm_67[] = /**< char: c */
{
	0x00000000, 0x00000000, 0xfc3f0000, 0x1c039c71, 0xf1c738e0, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_68[] = /**< char: d */
{
	0x00000000, 0xc0380000, 0xfc7f8e01, 0x1ce39e73, 0xf1e738e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_69[] = /**< char: e */
{
	0x00000000, 0x00000000, 0xfc1f0000, 0xfc7f8e71, 0xf0c73fe7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_70[] = /**< char: f */
{
	0xc0000000, 0x1e3c71e3, 0xe1c3870e, 0x00003870, 0x00000000
};

static const uint32_t bm_71[] = /**< char: g */
{
	0x00000000, 0x00000000, 0xfc7f0000, 0x1ce39e73, 0xf1e738e7, 0xf18e7f8f, 0x00007f0f, 0x00000000
};

static const uint32_t bm_72[] = /**< char: h */
{
	0x00000000, 0xe0380e00, 0x38fe3f80, 0xce739ce7, 0x739ce739, 0x00000000, 0x00000000
};

static const uint32_t bm_73[] = /**< char: i */
{
	0x1ce00000, 0xe739ce70, 0x0000739c, 0x00000000
};

static const uint32_t bm_74[] = /**< char: j */
{
	0x1c000000, 0xc71c7007, 0x71c71c71, 0x0000e79c
};

static const uint32_t bm_75[] = /**< char: k */
{
	0x00000000, 0xe0380e00, 0xf8fe7b80, 0xfe1f83e1, 0x739ce3b8, 0x00000000, 0x00000000
};

static const uint32_t bm_76[] = /**< char: l */
{
	0x9ce00000, 0xe739ce73, 0x0000739c, 0x00000000
};

static const uint32_t bm_77[] = /**< char: m */
{
	0x00000000, 0x00000000, 0x00000000, 0xfe3ffc00, 0x739ce73f, 0x9ce739ce, 0xe739ce73, 0x0000739c, 0x00000000, 0x00000000
};

static const uint32_t bm_78[] = /**< char: n */
{
	0x00000000, 0x00000000, 0x38fe3f80, 0xce739ce7, 0x739ce739, 0x00000000, 0x00000000
};

static const uint32_t bm_79[] = /**< char: o */
{
	0x00000000, 0x00000000, 0x1f800000, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_80[] = /**< char: p */
{
	0x00000000, 0x00000000, 0xfe1fc000, 0x1ce38e71, 0xf8e738e7, 0x700e1fc7, 0x00000380, 0x00000000
};

static const uint32_t bm_81[] = /**< char: q */
{
	0x00000000, 0x00000000, 0xfc7f8000, 0x1ce39e73, 0xf1e738e7, 0x03807f8f, 0x0000e01c, 0x00000000
};

static const uint32_t bm_82[] = /**< char: r */
{
	0x00000000, 0x7e000000, 0x0e0e1e7e, 0x0e0e0e0e, 0x00000000, 0x00000000
};

static const uint32_t bm_83[] = /**< char: s */
{
	0x00000000, 0x00000000, 0xfe3f8000, 0xf81f8c71, 0xf9c73e03, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_84[] = /**< char: t */
{
	0x1c000000, 0xc71e79c7, 0x71c71c71, 0x00000000
};

static const uint32_t bm_85[] = /**< char: u */
{
	0x00000000, 0x00000000, 0x39ce7380, 0xce739ce7, 0x7f1fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_86[] = /**< char: v */
{
	0x00000000, 0x00000000, 0x39ce6380, 0xfc3f0cc7, 0x1e0781e0, 0x00000000, 0x00000000
};

static const uint32_t bm_87[] = /**< char: w */
{
	0x00000000, 0x00000000, 0x00000000, 0x9dee6738, 0xf0dec77b, 0xde0ffc3f, 0x1ce07383, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_88[] = /**< char: x */
{
	0x00000000, 0x00000000, 0xfc39c000, 0xf01e07e1, 0x787e0f80, 0x000079c7, 0x00000000, 0x00000000
};

static const uint32_t bm_89[] = /**< char: y */
{
	0x00000000, 0x00000000, 0x39ce6380, 0xf83f0dc7, 0x0c0781e0, 0x01c0f038, 0x00000000
};

static const uint32_t bm_90[] = /**< char: z */
{
	0x00000000, 0x00000000, 0xe1e0fe7f, 0x81c1c1c1, 0x00007f3f, 0x00000000
};

static const uint32_t bm_91[] = /**< char: { */
{
	0xc0000000, 0x1c3871e3, 0xe0e1c78e, 0x1e1c3870, 0x0000000f
};

static const uint32_t bm_92[] = /**< char: | */
{
	0x9ce73800, 0xe739ce73, 0x39ce739c, 0x00000000
};

static const uint32_t bm_93[] = /**< char: } */
{
	0xe0000000, 0x1c3870f0, 0xe3c70f0e, 0x8f1c3870, 0x00000003
};

static const uint32_t bm_94[] = /**< char: ~ */
{
	0x00000000, 0x00000000, 0x00000000, 0xfe7f98c0, 0x00000389, 0x00000000, 0x00000000
};

static const uint32_t bm_95[] = /**< char: � */
{
	0x00000000, 0x63180e70, 0x39ce739c, 0x00000000
};

static const uint32_t bm_96[] = /**< char: � */
{
	0x00000000, 0x38000000, 0xfc3f81c0, 0xfcff9ff3, 0xf1ff07e0, 0x80703f8f, 0x00000003, 0x00000000
};

static const uint32_t bm_97[] = /**< char: � */
{
	0x00000000, 0xff1fc000, 0x7e71ce38, 0x701f83f0, 0xf80e0380, 0x00007fc7, 0x00000000, 0x00000000
};

static const uint32_t bm_98[] = /**< char: � */
{
	0x00000000, 0x40000000, 0x3fe7fe26, 0x0e70e39e, 0xe3fc38e7, 0x0002f47f, 0x00000000, 0x00000000
};

static const uint32_t bm_99[] = /**< char: � */
{
	0x00000000, 0xc70e0000, 0x3b839c31, 0xf81f01f8, 0x81f81f81, 0x0e00e01f, 0x00000000, 0x00000000
};

static const uint32_t bm_100[] = /**< char: � */
{
	0x9c000000, 0x00000e73, 0x01ce7380, 0x00000000
};

static const uint32_t bm_101[] = /**< char: � */
{
	0x00000000, 0x7e0f8000, 0x7c3b8770, 0x3c7b87f0, 0xc0fe3bc7, 0xe1dc3f83, 0x00003e0f, 0x00000000
};

static const uint32_t bm_102[] = /**< char: � */
{
	0x00000000, 0x00007e7e, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_103[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x1ff80ff0, 0x3ffc3ffc, 0x703e763e, 0x77fe763e, 0x3dfc3ffc, 0x0ff01ff8, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_104[] = /**< char: � */
{
	0x00000000, 0x7e7c7c3c, 0x006c7e7e, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_105[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x367e7e6c, 0x00486c7e, 0x00000000, 0x00000000
};

static const uint32_t bm_106[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x00000000, 0xfe7fe7fe, 0x07007007, 0x00000070, 0x00000000, 0x00000000
};

static const uint32_t bm_107[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x03e7cf80, 0x00000000, 0x00000000
};

static const uint32_t bm_108[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x1ff80ff0, 0x3ffc3ffc, 0x77ee7fee, 0x77ee73ee, 0x3efc3efc, 0x0ff01ff8, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_109[] = /**< char: � */
{
	0x7e000000, 0x00007e7e, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_110[] = /**< char: � */
{
	0x00000000, 0x7e7e7e3c, 0x0000183c, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_111[] = /**< char: � */
{
	0x00000000, 0x00000000, 0xf8701c00, 0x707f9fe7, 0x7f9fe1c0, 0x00000000, 0x00000000
};

static const uint32_t bm_112[] = /**< char: � */
{
	0x00000000, 0x3b9fc7c0, 0xf8787877, 0x0007e3f1, 0x00000000, 0x00000000
};

static const uint32_t bm_113[] = /**< char: � */
{
	0x00000000, 0x3f9fc7c0, 0xf9dc7038, 0x000383e3, 0x00000000, 0x00000000
};

static const uint32_t bm_114[] = /**< char: � */
{
	0x1c000000, 0x000000e7, 0x00000000, 0x00000000
};

static const uint32_t bm_115[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x39ce7380, 0xce739ce7, 0x7f9fe739, 0x00e0380e, 0x00000000
};

static const uint32_t bm_116[] = /**< char: � */
{
	0x00000000, 0xff3fc000, 0xfe7fcff9, 0xe0ff1ff3, 0xc1f83f07, 0x83f07e0f, 0x07e0fc1f, 0x00000000
};

static const uint32_t bm_117[] = /**< char: � */
{
	0x00000000, 0x07388000, 0x00000000, 0x00000000
};

static const uint32_t bm_118[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x20000000, 0x0001e79c
};

static const uint32_t bm_119[] = /**< char: � */
{
	0xe0000000, 0x3870f9f3, 0x00000e1c, 0x00000000, 0x00000000
};

static const uint32_t bm_120[] = /**< char: � */
{
	0x00000000, 0x3b8fc7c0, 0xe0f8fe77, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_121[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x7e7e3612, 0x0012367e, 0x00000000, 0x00000000
};

static const uint32_t bm_122[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x063e0c3e, 0x0338073e, 0x39b803b8, 0x3ec03df8, 0x7f603fe0, 0x38383870, 0x00000038, 0x00000000, 0x00000000
};

static const uint32_t bm_123[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x063e0e3e, 0x03b8073e, 0x3ff803b8, 0x70e07ff8, 0x1e7038e0, 0x3f383f30, 0x00000018, 0x00000000, 0x00000000
};

static const uint32_t bm_124[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x0cfe1c7c, 0x06700efe, 0x3bfe07f0, 0x3fb83ffe, 0x7fe03fc0, 0x38703860, 0x00000030, 0x00000000, 0x00000000
};

static const uint32_t bm_125[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x700e0000, 0x701c0380, 0x380e03c0, 0xf1ce71ce, 0x00003f0f, 0x00000000
};

static const uint32_t bm_126[] = /**< char: � */
{
	0x003800e0, 0xe000001c, 0x3e007801, 0x03700fc0, 0xe07f81cc, 0x870ff83f, 0x7039c1c3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_127[] = /**< char: � */
{
	0x00700380, 0xe000001c, 0x3e007801, 0x03700fc0, 0xe07f81cc, 0x870ff83f, 0x7039c1c3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_128[] = /**< char: � */
{
	0x007801c0, 0xe000003f, 0x3e007801, 0x03700fc0, 0xe07f81cc, 0x870ff83f, 0x7039c1c3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_129[] = /**< char: � */
{
	0x00fc0240, 0xe00ec03f, 0x3e007801, 0x03700fc0, 0xe07f81cc, 0x870ff83f, 0x7039c1c3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_130[] = /**< char: � */
{
	0x00fc03f0, 0xe000003f, 0x1f007801, 0x03b00fc0, 0xe07f80ce, 0x870ffc1f, 0x7038e0e3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_131[] = /**< char: � */
{
	0x00fc01e0, 0xe007803f, 0x1e007800, 0x03300fc0, 0xf07f81ce, 0x830ffc1f, 0x7039c0e3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_132[] = /**< char: � */
{
	0x00000000, 0x00000000, 0xf80ffc00, 0xf001f81f, 0xe0ff7003, 0xc3ffe1fe, 0x807fc03f, 0x3fc380e3, 0x00007f87, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_133[] = /**< char: � */
{
	0x00000000, 0xf0000000, 0xe1c3ff07, 0x800e3038, 0x3800e003, 0x870c0e70, 0x1fe0ffc3, 0x007801e0, 0x0000001e, 0x00000000
};

static const uint32_t bm_134[] = /**< char: � */
{
	0x1c01c038, 0xff3fe000, 0xfe01c039, 0x1cff9ff3, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_135[] = /**< char: � */
{
	0x1c0380e0, 0xff3fe000, 0xfe01c039, 0x1cff9ff3, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_136[] = /**< char: � */
{
	0x3f03c070, 0xff3fe000, 0xfe01c039, 0x1cff9ff3, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_137[] = /**< char: � */
{
	0x3f07e0fc, 0xff3fe000, 0xfe01c039, 0x1c7f8ff1, 0xf80700e0, 0x00007fcf, 0x00000000, 0x00000000
};

static const uint32_t bm_138[] = /**< char: � */
{
	0x1c01c38e, 0xc71c71c7, 0x71c71c71, 0x00000000
};

static const uint32_t bm_139[] = /**< char: � */
{
	0x8e00e71c, 0xe38e38e3, 0x38e38e38, 0x00000000
};

static const uint32_t bm_140[] = /**< char: � */
{
	0xc00f9f1c, 0x1c3870e1, 0xe1c3870e, 0x00003870, 0x00000000
};

static const uint32_t bm_141[] = /**< char: � */
{
	0x800f9f3e, 0x183060c1, 0xc183060c, 0x00003060, 0x00000000
};

static const uint32_t bm_142[] = /**< char: � */
{
	0x00000000, 0x3fe00000, 0x71c38ffc, 0xcfce7e30, 0xe30739f9, 0xff8e1c70, 0x00001ff0, 0x00000000, 0x00000000
};

static const uint32_t bm_143[] = /**< char: � */
{
	0xe07f0320, 0xe0e0ec07, 0xf38f9c3c, 0xdfce7e71, 0xe7e73bb9, 0xc39f1cfc, 0x00007873, 0x00000000, 0x00000000
};

static const uint32_t bm_144[] = /**< char: � */
{
	0x00380070, 0xf000000c, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_145[] = /**< char: � */
{
	0x007001c0, 0xf000000e, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_146[] = /**< char: � */
{
	0x007801e0, 0xf000003f, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_147[] = /**< char: � */
{
	0x00fc03e0, 0xf000001f, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_148[] = /**< char: � */
{
	0x00fc03f0, 0xf000003f, 0xf1c1ff03, 0x8c0e3838, 0x39c0e703, 0xc70e0e30, 0x0fc07fc3, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_149[] = /**< char: � */
{
	0x00000000, 0x00000000, 0xb9ce2180, 0x7c1e0fc7, 0x619ce3f8, 0x00000000, 0x00000000
};

static const uint32_t bm_150[] = /**< char: � */
{
	0x00000000, 0xf0000000, 0xf1c3ff1f, 0x8d8e3c38, 0xb9cee773, 0xc70e3e31, 0x0ff87fc3, 0x00000004, 0x00000000, 0x00000000
};

static const uint32_t bm_151[] = /**< char: � */
{
	0x801e0070, 0xe0e00003, 0x73839c1c, 0xc1ce0e70, 0xe7073839, 0xff0e3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_152[] = /**< char: � */
{
	0x803c01c0, 0xe0e00003, 0x73839c1c, 0xc1ce0e70, 0xe7073839, 0xff0e3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_153[] = /**< char: � */
{
	0xe03e00e0, 0xe0e00006, 0x73839c1c, 0xc1ce0e70, 0xe7073839, 0xff0e3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_154[] = /**< char: � */
{
	0xe03f01f8, 0xe0e00007, 0x73839c1c, 0xc1ce0e70, 0xe7073839, 0xff0e3ce0, 0x00001fc1, 0x00000000, 0x00000000
};

static const uint32_t bm_155[] = /**< char: � */
{
	0x803c01c0, 0xe0e00003, 0xc1c70e3c, 0x3e03f81d, 0x00700380, 0x3801c00e, 0x00000700, 0x00000000, 0x00000000
};

static const uint32_t bm_156[] = /**< char: � */
{
	0x00000000, 0xe00e0000, 0x3fe3fe07, 0x0e70e70e, 0xe3fe3fe7, 0x00e00e1f, 0x00000000, 0x00000000
};

static const uint32_t bm_157[] = /**< char: � */
{
	0x00000000, 0x7f0fc000, 0xfe39c738, 0x1c7f87f0, 0xf8c738e7, 0x00301fc7, 0x00000000, 0x00000000
};

static const uint32_t bm_158[] = /**< char: � */
{
	0x00000000, 0x38038000, 0xfe3f8180, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_159[] = /**< char: � */
{
	0x00000000, 0x381e0000, 0xfe3f80c0, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_160[] = /**< char: � */
{
	0x00000000, 0xfc0f8000, 0xfe3f8770, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_161[] = /**< char: � */
{
	0x00000000, 0x7e1fc1e0, 0xfe3f8000, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_162[] = /**< char: � */
{
	0x00000000, 0xfc1f8000, 0xfe3f8000, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_163[] = /**< char: � */
{
	0x1e010000, 0x3c0f81f0, 0xfe3f81c0, 0xf8fc1c73, 0xf9c739e7, 0x00007f8f, 0x00000000, 0x00000000
};

static const uint32_t bm_164[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x00000000, 0xfe000000, 0x1c7ffe1f, 0xe3fff8c7, 0xcfffe7ff, 0x1fff9c71, 0x00003ffe, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t bm_165[] = /**< char: � */
{
	0x00000000, 0x00000000, 0xfc3f0000, 0x1c039c71, 0xf1c738e0, 0xc0703f87, 0x00003e07, 0x00000000
};

static const uint32_t bm_166[] = /**< char: � */
{
	0x00000000, 0x38038000, 0xfc1f0180, 0xfc7f8e71, 0xf0c73fe7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_167[] = /**< char: � */
{
	0x00000000, 0x380e0000, 0xfc1f00c0, 0xfc7f8e71, 0xf0c73fe7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_168[] = /**< char: � */
{
	0x00000000, 0x7c078000, 0xfc1f0360, 0xfc7f8e71, 0xf0c73fe7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_169[] = /**< char: � */
{
	0x00000000, 0x7c0f8000, 0xfc1f0000, 0xfc7f8e71, 0xf0c73fe7, 0x00003f87, 0x00000000, 0x00000000
};

static const uint32_t bm_170[] = /**< char: � */
{
	0x0e000000, 0xc71c7187, 0x71c71c71, 0x00000000
};

static const uint32_t bm_171[] = /**< char: � */
{
	0x9c000000, 0xe38e3863, 0x38e38e38, 0x00000000
};

static const uint32_t bm_172[] = /**< char: � */
{
	0x00000000, 0x386e7e3c, 0x38383838, 0x38383838, 0x00000000, 0x00000000
};

static const uint32_t bm_173[] = /**< char: � */
{
	0x00000000, 0x38006e6e, 0x38383838, 0x38383838, 0x00000000, 0x00000000
};

static const uint32_t bm_174[] = /**< char: � */
{
	0x00000000, 0x81f03f00, 0x3f83d81f, 0x0e38e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_175[] = /**< char: � */
{
	0x00000000, 0xc3f0fc00, 0x38fe3f86, 0xce739ce7, 0x739ce739, 0x00000000, 0x00000000
};

static const uint32_t bm_176[] = /**< char: � */
{
	0x00000000, 0x00780000, 0x1f806007, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_177[] = /**< char: � */
{
	0x00000000, 0x01e00000, 0x1f80700f, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_178[] = /**< char: � */
{
	0x00000000, 0x80f00000, 0x1f81d81f, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_179[] = /**< char: � */
{
	0x00000000, 0x81f80e00, 0x1f80000f, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_180[] = /**< char: � */
{
	0x00000000, 0x81f80000, 0x1f80001f, 0x0e39e3fc, 0xe70e70e7, 0x1f83fc39, 0x00000000, 0x00000000
};

static const uint32_t bm_181[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x80701c00, 0xfe7f9fe0, 0x1c070081, 0x00000000, 0x00000000
};

static const uint32_t bm_182[] = /**< char: � */
{
	0x00000000, 0x00000000, 0x7f820000, 0xce3de3fc, 0xe73e76e7, 0x1fe3fc39, 0x00000006, 0x00000000
};

static const uint32_t bm_183[] = /**< char: � */
{
	0x00000000, 0x00e03800, 0x39ce7383, 0xce739ce7, 0x7f1fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_184[] = /**< char: � */
{
	0x00000000, 0x00c07000, 0x39ce7381, 0xce739ce7, 0x7f1fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_185[] = /**< char: � */
{
	0x00000000, 0xc3f07800, 0x39ce738e, 0xce739ce7, 0x7f1fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_186[] = /**< char: � */
{
	0x00000000, 0x03f0fc00, 0x39ce7380, 0xce739ce7, 0x7f1fe739, 0x00000000, 0x00000000
};

static const uint32_t bm_187[] = /**< char: � */
{
	0x00000000, 0x01c0f000, 0x39ce6383, 0xf83f0dc7, 0x0c0781e0, 0x01c0f038, 0x00000000
};

static const uint32_t bm_188[] = /**< char: � */
{
	0x00000000, 0x0700e000, 0xfe1fc038, 0x1ce38e71, 0xf8e738e7, 0x700e1fc7, 0x00000380, 0x00000000
};

static const uint32_t bm_189[] = /**< char: � */
{
	0x00000000, 0xfc1f8000, 0x9c61c000, 0xf0661ce3, 0xc0780f83, 0xe0700c03, 0x00000f01, 0x00000000
};

/**
 * @brief Array containing all available glyphs
 */
static const Font_GlyphType glyphs[] = 
{
	{ 0x0a, bm_0 },
	{ 0x04, 0 },
	{ 0x05, bm_1 },
	{ 0x07, bm_2 },
	{ 0x0a, bm_3 },
	{ 0x0b, bm_4 },
	{ 0x11, bm_5 },
	{ 0x0d, bm_6 },
	{ 0x05, bm_7 },
	{ 0x07, bm_8 },
	{ 0x07, bm_9 },
	{ 0x09, bm_10 },
	{ 0x0a, bm_11 },
	{ 0x05, bm_12 },
	{ 0x07, bm_13 },
	{ 0x05, bm_14 },
	{ 0x09, bm_15 },
	{ 0x0b, bm_16 },
	{ 0x08, bm_17 },
	{ 0x0b, bm_18 },
	{ 0x0b, bm_19 },
	{ 0x0b, bm_20 },
	{ 0x0b, bm_21 },
	{ 0x0b, bm_22 },
	{ 0x09, bm_23 },
	{ 0x0b, bm_24 },
	{ 0x0b, bm_25 },
	{ 0x05, bm_26 },
	{ 0x05, bm_27 },
	{ 0x0a, bm_28 },
	{ 0x0a, bm_29 },
	{ 0x0a, bm_30 },
	{ 0x0b, bm_31 },
	{ 0x0f, bm_32 },
	{ 0x0e, bm_33 },
	{ 0x0d, bm_34 },
	{ 0x0d, bm_35 },
	{ 0x0d, bm_36 },
	{ 0x0b, bm_37 },
	{ 0x0b, bm_38 },
	{ 0x0e, bm_39 },
	{ 0x0d, bm_40 },
	{ 0x05, bm_41 },
	{ 0x0a, bm_42 },
	{ 0x0d, bm_43 },
	{ 0x0b, bm_44 },
	{ 0x0f, bm_45 },
	{ 0x0d, bm_46 },
	{ 0x0e, bm_47 },
	{ 0x0c, bm_48 },
	{ 0x0e, bm_49 },
	{ 0x0c, bm_50 },
	{ 0x0d, bm_51 },
	{ 0x0b, bm_52 },
	{ 0x0d, bm_53 },
	{ 0x0d, bm_54 },
	{ 0x11, bm_55 },
	{ 0x0d, bm_56 },
	{ 0x0d, bm_57 },
	{ 0x0b, bm_58 },
	{ 0x06, bm_59 },
	{ 0x09, bm_60 },
	{ 0x07, bm_61 },
	{ 0x0b, bm_62 },
	{ 0x0a, bm_63 },
	{ 0x06, bm_64 },
	{ 0x0b, bm_65 },
	{ 0x0b, bm_66 },
	{ 0x0b, bm_67 },
	{ 0x0b, bm_68 },
	{ 0x0b, bm_69 },
	{ 0x07, bm_70 },
	{ 0x0b, bm_71 },
	{ 0x0a, bm_72 },
	{ 0x05, bm_73 },
	{ 0x06, bm_74 },
	{ 0x0a, bm_75 },
	{ 0x05, bm_76 },
	{ 0x0f, bm_77 },
	{ 0x0a, bm_78 },
	{ 0x0c, bm_79 },
	{ 0x0b, bm_80 },
	{ 0x0b, bm_81 },
	{ 0x08, bm_82 },
	{ 0x0b, bm_83 },
	{ 0x06, bm_84 },
	{ 0x0a, bm_85 },
	{ 0x0a, bm_86 },
	{ 0x0e, bm_87 },
	{ 0x0b, bm_88 },
	{ 0x0a, bm_89 },
	{ 0x09, bm_90 },
	{ 0x07, bm_91 },
	{ 0x05, bm_92 },
	{ 0x07, bm_93 },
	{ 0x0a, bm_94 },
	{ 0x05, bm_95 },
	{ 0x0b, bm_96 },
	{ 0x0b, bm_97 },
	{ 0x0c, bm_98 },
	{ 0x0c, bm_99 },
	{ 0x05, bm_100 },
	{ 0x0b, bm_101 },
	{ 0x08, bm_102 },
	{ 0x10, bm_103 },
	{ 0x08, bm_104 },
	{ 0x08, bm_105 },
	{ 0x0c, bm_106 },
	{ 0x07, bm_107 },
	{ 0x10, bm_108 },
	{ 0x08, bm_109 },
	{ 0x08, bm_110 },
	{ 0x0a, bm_111 },
	{ 0x09, bm_112 },
	{ 0x09, bm_113 },
	{ 0x06, bm_114 },
	{ 0x0a, bm_115 },
	{ 0x0b, bm_116 },
	{ 0x05, bm_117 },
	{ 0x06, bm_118 },
	{ 0x07, bm_119 },
	{ 0x09, bm_120 },
	{ 0x08, bm_121 },
	{ 0x10, bm_122 },
	{ 0x10, bm_123 },
	{ 0x10, bm_124 },
	{ 0x0b, bm_125 },
	{ 0x0e, bm_126 },
	{ 0x0e, bm_127 },
	{ 0x0e, bm_128 },
	{ 0x0e, bm_129 },
	{ 0x0e, bm_130 },
	{ 0x0e, bm_131 },
	{ 0x11, bm_132 },
	{ 0x0e, bm_133 },
	{ 0x0b, bm_134 },
	{ 0x0b, bm_135 },
	{ 0x0b, bm_136 },
	{ 0x0b, bm_137 },
	{ 0x06, bm_138 },
	{ 0x06, bm_139 },
	{ 0x07, bm_140 },
	{ 0x07, bm_141 },
	{ 0x0d, bm_142 },
	{ 0x0d, bm_143 },
	{ 0x0e, bm_144 },
	{ 0x0e, bm_145 },
	{ 0x0e, bm_146 },
	{ 0x0e, bm_147 },
	{ 0x0e, bm_148 },
	{ 0x0a, bm_149 },
	{ 0x0e, bm_150 },
	{ 0x0d, bm_151 },
	{ 0x0d, bm_152 },
	{ 0x0d, bm_153 },
	{ 0x0d, bm_154 },
	{ 0x0d, bm_155 },
	{ 0x0c, bm_156 },
	{ 0x0b, bm_157 },
	{ 0x0b, bm_158 },
	{ 0x0b, bm_159 },
	{ 0x0b, bm_160 },
	{ 0x0b, bm_161 },
	{ 0x0b, bm_162 },
	{ 0x0b, bm_163 },
	{ 0x11, bm_164 },
	{ 0x0b, bm_165 },
	{ 0x0b, bm_166 },
	{ 0x0b, bm_167 },
	{ 0x0b, bm_168 },
	{ 0x0b, bm_169 },
	{ 0x06, bm_170 },
	{ 0x06, bm_171 },
	{ 0x08, bm_172 },
	{ 0x08, bm_173 },
	{ 0x0c, bm_174 },
	{ 0x0a, bm_175 },
	{ 0x0c, bm_176 },
	{ 0x0c, bm_177 },
	{ 0x0c, bm_178 },
	{ 0x0c, bm_179 },
	{ 0x0c, bm_180 },
	{ 0x0a, bm_181 },
	{ 0x0c, bm_182 },
	{ 0x0a, bm_183 },
	{ 0x0a, bm_184 },
	{ 0x0a, bm_185 },
	{ 0x0a, bm_186 },
	{ 0x0a, bm_187 },
	{ 0x0b, bm_188 },
	{ 0x0b, bm_189 },
};

/**
 * @brief Definition of the font
 */
const FontType Font_Helvetica_16 =
{
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40,
		0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
		0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
		0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e,
		0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
		0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e,
		0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae,
		0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe
	},	/**< Array that contains the indices in the glyphs array for each char value */
	FONT_HELVETICA_16_GLYPH_COUNT,	/**< Number of available glyphs */
	FONT_HELVETICA_16_HEIGHT,	/**< Height of the glyphs */
	glyphs	/**< Array containing all glyphs */
};
