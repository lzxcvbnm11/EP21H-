/* link at 0x00004000 */
#include "volcano6.h"

#pragma CONST_SEG V5_NVRAM

v_uint8 V_NVRAM v_config[] = {
	/* 0x00004000 */ 0x47, 0x94, 0x50, 0x16, 0x00, 0x00, 0x2f, 0x00, 
	/* 0x00004008 */ 0x01, 0xbf, 0x2f, 0x00, 0x4e, 0x57, 0x00, 0x00, 
	/* 0x00004010 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x30, 
	/* 0x00004018 */ 0x10, 0x30, 0x0e, 0x2f, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004020 */ 0x80, 0x07, 0x00, 0x40, 0x40, 0x04, 0x00, 0x11, 
	/* 0x00004028 */ 0x30, 0x5c, 0x30, 0x5c, 0x30, 0x5c, 0x00, 0x00, 
	/* 0x00004030 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 
	/* 0x00004038 */ 0x13, 0x30, 0x5e, 0x30, 0x5e, 0x30, 0x5e, 0x00, 
	/* 0x00004040 */ 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 
	/* 0x00004048 */ 0xff, 0x11, 0x30, 0x5f, 0x30, 0x5f, 0x30, 0x5f, 
	/* 0x00004050 */ 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004058 */ 0x01, 0xff, 0x11, 0x30, 0x60, 0x30, 0x60, 0x30, 
	/* 0x00004060 */ 0x60, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
	/* 0x00004068 */ 0x00, 0x02, 0xff, 0x13, 0x30, 0x13, 0x30, 0x11, 
	/* 0x00004070 */ 0x2f, 0x01, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 
	/* 0x00004078 */ 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 0x12, 0x30, 
	/* 0x00004080 */ 0x11, 0x2f, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	/* 0x00004088 */ 0x00, 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 0x11, 
	/* 0x00004090 */ 0x30, 0x11, 0x2f, 0x01, 0x00, 0x00, 0x00, 0xff, 
	/* 0x00004098 */ 0x00, 0x00, 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 
	/* 0x000040a0 */ 0x62, 0x30, 0x62, 0x30, 0x62, 0x00, 0x00, 0x00, 
	/* 0x000040a8 */ 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x13, 
	/* 0x000040b0 */ 0x30, 0x17, 0x30, 0x17, 0x2f, 0x01, 0x00, 0x00, 
	/* 0x000040b8 */ 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x08, 0x00, 
	/* 0x000040c0 */ 0x0e, 0x30, 0x1f, 0x30, 0x1f, 0x2f, 0x02, 0x00, 
	/* 0x000040c8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x08, 
	/* 0x000040d0 */ 0x00, 0x0e, 0x30, 0x0e, 0x30, 0x0e, 0x2f, 0x00, 
	/* 0x000040d8 */ 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x40, 0x40, 
	/* 0x000040e0 */ 0x04, 0x00, 0x11, 0x30, 0x27, 0x30, 0x27, 0x2f, 
	/* 0x000040e8 */ 0x01, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x40, 
	/* 0x000040f0 */ 0x40, 0x02, 0x00, 0x13, 0x30, 0x29, 0x30, 0x27, 
	/* 0x000040f8 */ 0x2f, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 
	/* 0x00004100 */ 0x40, 0x40, 0x01, 0x00, 0x11, 0x30, 0x0e, 0x30, 
	/* 0x00004108 */ 0x0e, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
	/* 0x00004110 */ 0x00, 0x40, 0x40, 0x04, 0x00, 0x11, 0x30, 0x2a, 
	/* 0x00004118 */ 0x30, 0x2a, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x30, 
	/* 0x00004120 */ 0x04, 0x00, 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 
	/* 0x00004128 */ 0x2b, 0x30, 0x2b, 0x2f, 0x01, 0x00, 0x00, 0x00, 
	/* 0x00004130 */ 0xff, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x11, 
	/* 0x00004138 */ 0x30, 0x2d, 0x30, 0x2b, 0x2f, 0x01, 0x00, 0x00, 
	/* 0x00004140 */ 0x00, 0x08, 0x03, 0x00, 0x02, 0x02, 0x01, 0x00, 
	/* 0x00004148 */ 0x11, 0x30, 0x30, 0x30, 0x30, 0x2f, 0x01, 0x00, 
	/* 0x00004150 */ 0x00, 0x00, 0x40, 0x06, 0x00, 0x04, 0x04, 0x01, 
	/* 0x00004158 */ 0x00, 0x11, 0x30, 0x2c, 0x30, 0x2b, 0x2f, 0x01, 
	/* 0x00004160 */ 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x02, 0x02, 
	/* 0x00004168 */ 0x04, 0x00, 0x11, 0x30, 0x0f, 0x30, 0x0e, 0x2f, 
	/* 0x00004170 */ 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x40, 
	/* 0x00004178 */ 0x40, 0x04, 0x00, 0x11, 0x30, 0x14, 0x30, 0x11, 
	/* 0x00004180 */ 0x2f, 0x01, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 
	/* 0x00004188 */ 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 0x64, 0x30, 
	/* 0x00004190 */ 0x64, 0x30, 0x64, 0x00, 0x00, 0x00, 0xff, 0x00, 
	/* 0x00004198 */ 0x00, 0x00, 0x00, 0x02, 0xff, 0x13, 0x30, 0x31, 
	/* 0x000041a0 */ 0x30, 0x31, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x20, 
	/* 0x000041a8 */ 0x05, 0x00, 0x04, 0x04, 0x04, 0x00, 0x11, 0x30, 
	/* 0x000041b0 */ 0x66, 0x30, 0x66, 0x30, 0x66, 0x00, 0x00, 0x00, 
	/* 0x000041b8 */ 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x13, 
	/* 0x000041c0 */ 0x30, 0x15, 0x30, 0x11, 0x2f, 0x01, 0x00, 0x00, 
	/* 0x000041c8 */ 0x00, 0x3f, 0x00, 0x00, 0x20, 0x20, 0x01, 0x00, 
	/* 0x000041d0 */ 0x11, 0x30, 0x68, 0x30, 0x68, 0x30, 0x68, 0x00, 
	/* 0x000041d8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
	/* 0x000041e0 */ 0xff, 0x0e, 0x30, 0x32, 0x30, 0x32, 0x2f, 0x02, 
	/* 0x000041e8 */ 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x02, 0x02, 
	/* 0x000041f0 */ 0x01, 0x00, 0x11, 0x30, 0x35, 0x30, 0x35, 0x2f, 
	/* 0x000041f8 */ 0x01, 0x00, 0x00, 0x00, 0xf0, 0x04, 0x00, 0x10, 
	/* 0x00004200 */ 0x10, 0x01, 0x00, 0x11, 0x30, 0x39, 0x30, 0x36, 
	/* 0x00004208 */ 0x2f, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x00, 
	/* 0x00004210 */ 0x01, 0x01, 0x01, 0x00, 0x11, 0x30, 0x38, 0x30, 
	/* 0x00004218 */ 0x36, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 
	/* 0x00004220 */ 0x00, 0x01, 0x01, 0x01, 0x00, 0x11, 0x30, 0x37, 
	/* 0x00004228 */ 0x30, 0x36, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 
	/* 0x00004230 */ 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x11, 0x30, 
	/* 0x00004238 */ 0x36, 0x30, 0x36, 0x2f, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004240 */ 0xf0, 0x04, 0x00, 0x01, 0x01, 0x01, 0x00, 0x11, 
	/* 0x00004248 */ 0x30, 0x36, 0x30, 0x36, 0x2f, 0x00, 0x00, 0x00, 
	/* 0x00004250 */ 0x00, 0x08, 0x03, 0x00, 0x01, 0x01, 0x01, 0x00, 
	/* 0x00004258 */ 0x11, 0x30, 0x3a, 0x30, 0x3a, 0x2f, 0x00, 0x00, 
	/* 0x00004260 */ 0x00, 0x00, 0x04, 0x02, 0x00, 0x80, 0x80, 0x01, 
	/* 0x00004268 */ 0x00, 0x11, 0x30, 0x3a, 0x30, 0x3a, 0x2f, 0x00, 
	/* 0x00004270 */ 0x00, 0x00, 0x00, 0x08, 0x03, 0x00, 0x80, 0x80, 
	/* 0x00004278 */ 0x01, 0x00, 0x11, 0x30, 0x31, 0x30, 0x31, 0x2f, 
	/* 0x00004280 */ 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x00, 0x04, 
	/* 0x00004288 */ 0x04, 0x04, 0x00, 0x11, 0x30, 0x3b, 0x30, 0x3b, 
	/* 0x00004290 */ 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
	/* 0x00004298 */ 0x02, 0x02, 0x04, 0x00, 0x11, 0x30, 0x0e, 0x30, 
	/* 0x000042a0 */ 0x0e, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 
	/* 0x000042a8 */ 0x00, 0x40, 0x40, 0x04, 0x00, 0x11, 0x30, 0x16, 
	/* 0x000042b0 */ 0x30, 0x11, 0x2f, 0x01, 0x00, 0x00, 0x00, 0x3f, 
	/* 0x000042b8 */ 0x00, 0x00, 0x20, 0x20, 0x01, 0x00, 0x11, 0x30, 
	/* 0x000042c0 */ 0x33, 0x30, 0x32, 0x2f, 0x02, 0x00, 0x00, 0x00, 
	/* 0x000042c8 */ 0xff, 0x00, 0x00, 0x02, 0x02, 0x02, 0x00, 0x13, 
	/* 0x000042d0 */ 0x30, 0x70, 0x30, 0x70, 0x30, 0x70, 0x00, 0x00, 
	/* 0x000042d8 */ 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 0xff, 
	/* 0x000042e0 */ 0x11, 0x30, 0x71, 0x30, 0x71, 0x30, 0x71, 0x00, 
	/* 0x000042e8 */ 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 
	/* 0x000042f0 */ 0xff, 0x11, 0x30, 0x3c, 0x30, 0x3c, 0x2f, 0x00, 
	/* 0x000042f8 */ 0x00, 0x00, 0x00, 0x30, 0x04, 0x00, 0x08, 0x08, 
	/* 0x00004300 */ 0x01, 0x00, 0x11, 0x30, 0x3c, 0x30, 0x3c, 0x2f, 
	/* 0x00004308 */ 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x00, 0x08, 
	/* 0x00004310 */ 0x08, 0x04, 0x00, 0x11, 0x30, 0x3a, 0x30, 0x3a, 
	/* 0x00004318 */ 0x2f, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 
	/* 0x00004320 */ 0x80, 0x80, 0x01, 0x00, 0x11, 0x30, 0x0f, 0x30, 
	/* 0x00004328 */ 0x0e, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
	/* 0x00004330 */ 0x00, 0x40, 0x40, 0x04, 0x00, 0x11, 0x30, 0x2e, 
	/* 0x00004338 */ 0x30, 0x2b, 0x2f, 0x01, 0x00, 0x00, 0x00, 0xff, 
	/* 0x00004340 */ 0x00, 0x00, 0x02, 0x02, 0x02, 0x00, 0x13, 0x30, 
	/* 0x00004348 */ 0x2d, 0x30, 0x2b, 0x2f, 0x01, 0x00, 0x00, 0x00, 
	/* 0x00004350 */ 0x01, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x11, 
	/* 0x00004358 */ 0x30, 0x3d, 0x30, 0x3d, 0x2f, 0x00, 0x00, 0x00, 
	/* 0x00004360 */ 0x00, 0x0f, 0x00, 0x00, 0x10, 0x10, 0x01, 0x00, 
	/* 0x00004368 */ 0x11, 0x30, 0x3d, 0x30, 0x3d, 0x2f, 0x00, 0x00, 
	/* 0x00004370 */ 0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x10, 0x01, 
	/* 0x00004378 */ 0x00, 0x11, 0x30, 0x3e, 0x30, 0x3e, 0x2f, 0x01, 
	/* 0x00004380 */ 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x01, 0x01, 
	/* 0x00004388 */ 0x02, 0x00, 0x16, 0x30, 0x41, 0x30, 0x3e, 0x2f, 
	/* 0x00004390 */ 0x01, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x01, 
	/* 0x00004398 */ 0x01, 0x01, 0x00, 0x11, 0x30, 0x42, 0x30, 0x42, 
	/* 0x000043a0 */ 0x2f, 0x01, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 
	/* 0x000043a8 */ 0x08, 0x08, 0x02, 0x00, 0x13, 0x30, 0x42, 0x30, 
	/* 0x000043b0 */ 0x42, 0x2f, 0x01, 0x00, 0x00, 0x00, 0x80, 0x07, 
	/* 0x000043b8 */ 0x00, 0x08, 0x08, 0x01, 0x00, 0x11, 0x30, 0x72, 
	/* 0x000043c0 */ 0x30, 0x72, 0x30, 0x72, 0x00, 0x00, 0x00, 0xff, 
	/* 0x000043c8 */ 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x11, 0x30, 
	/* 0x000043d0 */ 0x73, 0x30, 0x73, 0x30, 0x73, 0x00, 0x00, 0x00, 
	/* 0x000043d8 */ 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x11, 
	/* 0x000043e0 */ 0x30, 0x74, 0x30, 0x74, 0x30, 0x74, 0x00, 0x00, 
	/* 0x000043e8 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 
	/* 0x000043f0 */ 0x11, 0x30, 0x75, 0x30, 0x75, 0x30, 0x75, 0x00, 
	/* 0x000043f8 */ 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 
	/* 0x00004400 */ 0xff, 0x11, 0x30, 0x45, 0x30, 0x45, 0x2f, 0x20, 
	/* 0x00004408 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
	/* 0x00004410 */ 0x18, 0x00, 0x0e, 0x30, 0x4e, 0x30, 0x4e, 0x2f, 
	/* 0x00004418 */ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	/* 0x00004420 */ 0x01, 0x18, 0x00, 0x0d, 0x30, 0x56, 0x30, 0x56, 
	/* 0x00004428 */ 0x2f, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 
	/* 0x00004430 */ 0x00, 0x04, 0x14, 0x00, 0x11, 0x30, 0x58, 0x30, 
	/* 0x00004438 */ 0x58, 0x2f, 0x20, 0x00, 0x00, 0x00, 0x20, 0x05, 
	/* 0x00004440 */ 0x00, 0x00, 0x02, 0x14, 0x00, 0x11, 0x30, 0x58, 
	/* 0x00004448 */ 0x30, 0x58, 0x2f, 0x20, 0x00, 0x00, 0x00, 0x10, 
	/* 0x00004450 */ 0x04, 0x00, 0x00, 0x02, 0x14, 0x00, 0x11, 0x30, 
	/* 0x00004458 */ 0x58, 0x30, 0x58, 0x2f, 0x20, 0x00, 0x00, 0x00, 
	/* 0x00004460 */ 0x03, 0x00, 0x00, 0x00, 0x02, 0x11, 0x00, 0x11, 
	/* 0x00004468 */ 0x30, 0x58, 0x30, 0x58, 0x2f, 0x20, 0x00, 0x00, 
	/* 0x00004470 */ 0x00, 0x0c, 0x02, 0x00, 0x00, 0x02, 0x11, 0x00, 
	/* 0x00004478 */ 0x11, 0x30, 0x58, 0x30, 0x58, 0x2f, 0x20, 0x00, 
	/* 0x00004480 */ 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x02, 0x14, 
	/* 0x00004488 */ 0x00, 0x11, 0x30, 0x59, 0x30, 0x58, 0x2f, 0x20, 
	/* 0x00004490 */ 0x00, 0x00, 0x00, 0xf0, 0x04, 0x00, 0x00, 0x02, 
	/* 0x00004498 */ 0x11, 0x00, 0x11, 0x30, 0x5b, 0x30, 0x5b, 0x2f, 
	/* 0x000044a0 */ 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x08, 
	/* 0x000044a8 */ 0x08, 0x14, 0x00, 0x11, 0x08, 0x00, 0x00, 0x00, 
	/* 0x000044b0 */ 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044b8 */ 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x02, 
	/* 0x000044c0 */ 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 
	/* 0x000044c8 */ 0x46, 0xdf, 0x47, 0x21, 0x47, 0x42, 0x47, 0x55, 
	/* 0x000044d0 */ 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044d8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044e0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044e8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044f0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000044f8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004500 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004508 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004510 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004518 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004520 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004528 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004530 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004538 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004540 */ 0x00, 0x00, 0x4a, 0x37, 0x47, 0xb3, 0x48, 0x79, 
	/* 0x00004548 */ 0x49, 0xee, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 
	/* 0x00004550 */ 0x47, 0xab, 0x47, 0xab, 0x49, 0xe6, 0x49, 0xe2, 
	/* 0x00004558 */ 0x4a, 0x1a, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 
	/* 0x00004560 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004568 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004570 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004578 */ 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004580 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004588 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004590 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004598 */ 0x00, 0x00, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045a0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045a8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045b0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045b8 */ 0x00, 0x00, 0x03, 0x01, 0x4b, 0x4f, 0x4a, 0x81, 
	/* 0x000045c0 */ 0x4a, 0xc3, 0x4b, 0x06, 0xff, 0xff, 0x0b, 0x00, 
	/* 0x000045c8 */ 0x00, 0x00, 0x4a, 0x79, 0x4a, 0x79, 0x4b, 0x00, 
	/* 0x000045d0 */ 0x4a, 0xfc, 0x4b, 0x32, 0x00, 0x80, 0x01, 0x00, 
	/* 0x000045d8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045e0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045e8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000045f0 */ 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	/* 0x000045f8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004600 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004608 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004610 */ 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	/* 0x00004618 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004620 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004628 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004630 */ 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x4c, 0x9d, 
	/* 0x00004638 */ 0x4b, 0x99, 0x4b, 0xfc, 0x4c, 0x54, 0xff, 0xff, 
	/* 0x00004640 */ 0x0f, 0x00, 0x00, 0x00, 0x4b, 0x91, 0x4b, 0x91, 
	/* 0x00004648 */ 0x4c, 0x4c, 0x4c, 0x48, 0x4c, 0x80, 0x00, 0x80, 
	/* 0x00004650 */ 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004658 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004660 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004668 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 
	/* 0x00004670 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004678 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004680 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004688 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 
	/* 0x00004690 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004698 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046a0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046a8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 
	/* 0x000046b0 */ 0x02, 0x00, 0x05, 0x04, 0x40, 0x01, 0x40, 0x02, 
	/* 0x000046b8 */ 0x00, 0x4c, 0xdf, 0x4d, 0x57, 0x2f, 0xee, 0x43, 
	/* 0x000046c0 */ 0x14, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	/* 0x000046c8 */ 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 
	/* 0x000046d0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046d8 */ 0x00, 0x10, 0x51, 0x00, 0x2f, 0xed, 0x01, 0x00, 
	/* 0x000046e0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046e8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046f0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000046f8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	/* 0x00004700 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004708 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004710 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004718 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004720 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004728 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004730 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004738 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004740 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004748 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004750 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004758 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004760 */ 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004768 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004770 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004778 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004780 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004788 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004790 */ 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004798 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000047a0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000047a8 */ 0x00, 0x00, 0x00, 0x49, 0xcf, 0x49, 0xbc, 0x49, 
	/* 0x000047b0 */ 0xa9, 0x48, 0x58, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x000047b8 */ 0xff, 0xff, 0xff, 0x6d, 0x80, 0x00, 0x00, 0x2f, 
	/* 0x000047c0 */ 0x20, 0x30, 0x58, 0x30, 0x76, 0x00, 0x00, 0x00, 
	/* 0x000047c8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 
	/* 0x000047d0 */ 0x00, 0x03, 0x01, 0x00, 0xfd, 0xff, 0xff, 0xff, 
	/* 0x000047d8 */ 0xff, 0xff, 0xff, 0xff, 0x88, 0x20, 0x00, 0x00, 
	/* 0x000047e0 */ 0x2f, 0x20, 0x30, 0x5b, 0x30, 0x78, 0x00, 0x00, 
	/* 0x000047e8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 
	/* 0x000047f0 */ 0x01, 0x00, 0x01, 0x03, 0x00, 0xfd, 0xff, 0xff, 
	/* 0x000047f8 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0x89, 0x20, 0x00, 
	/* 0x00004800 */ 0x00, 0x2f, 0x20, 0x30, 0x56, 0x30, 0x79, 0x00, 
	/* 0x00004808 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
	/* 0x00004810 */ 0x04, 0x01, 0x00, 0x01, 0x02, 0x00, 0xff, 0xff, 
	/* 0x00004818 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x40, 
	/* 0x00004820 */ 0x00, 0x00, 0x2f, 0x20, 0x30, 0x4e, 0x30, 0x82, 
	/* 0x00004828 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004830 */ 0x04, 0x01, 0x07, 0x00, 0x7f, 0x00, 0x00, 0x00, 
	/* 0x00004838 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004840 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004848 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004850 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004858 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004860 */ 0xed, 0x60, 0x00, 0x00, 0x2f, 0x20, 0x30, 0x45, 
	/* 0x00004868 */ 0x30, 0x7a, 0x44, 0xac, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004870 */ 0x00, 0x00, 0x03, 0x08, 0x08, 0x00, 0xff, 0xff, 
	/* 0x00004878 */ 0x00, 0x30, 0x2b, 0x30, 0x89, 0x2f, 0x01, 0x2f, 
	/* 0x00004880 */ 0xef, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x08, 
	/* 0x00004888 */ 0x00, 0xe5, 0x00, 0x00, 0x30, 0x27, 0x30, 0x8e, 
	/* 0x00004890 */ 0x2f, 0x01, 0x2f, 0xef, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004898 */ 0x40, 0x40, 0x08, 0x00, 0x07, 0x00, 0x00, 0x30, 
	/* 0x000048a0 */ 0x0e, 0x30, 0x91, 0x2f, 0x00, 0x2f, 0xee, 0x00, 
	/* 0x000048a8 */ 0x00, 0x00, 0x00, 0x40, 0x40, 0x06, 0x00, 0x0b, 
	/* 0x000048b0 */ 0x00, 0x01, 0x30, 0x3d, 0x30, 0x94, 0x2f, 0x00, 
	/* 0x000048b8 */ 0x2f, 0xee, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 
	/* 0x000048c0 */ 0x08, 0x00, 0x08, 0x00, 0x00, 0x30, 0x30, 0x30, 
	/* 0x000048c8 */ 0x95, 0x2f, 0x01, 0x2f, 0xef, 0x00, 0x00, 0x00, 
	/* 0x000048d0 */ 0x00, 0x04, 0x04, 0x08, 0x00, 0x10, 0x00, 0x00, 
	/* 0x000048d8 */ 0x30, 0x3a, 0x30, 0x96, 0x2f, 0x00, 0x2f, 0xee, 
	/* 0x000048e0 */ 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x08, 0x00, 
	/* 0x000048e8 */ 0x01, 0x00, 0x00, 0x30, 0x3c, 0x30, 0x97, 0x2f, 
	/* 0x000048f0 */ 0x00, 0x2f, 0xee, 0x00, 0x00, 0x00, 0x00, 0x08, 
	/* 0x000048f8 */ 0x08, 0x02, 0x00, 0x01, 0x00, 0x01, 0x30, 0x2a, 
	/* 0x00004900 */ 0x30, 0x98, 0x2f, 0x00, 0x2f, 0xee, 0x00, 0x00, 
	/* 0x00004908 */ 0x00, 0x00, 0x20, 0x20, 0x08, 0x00, 0x02, 0x00, 
	/* 0x00004910 */ 0x00, 0x30, 0x42, 0x30, 0x99, 0x2f, 0x01, 0x2f, 
	/* 0x00004918 */ 0xef, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 
	/* 0x00004920 */ 0x00, 0x03, 0x00, 0x00, 0x30, 0x36, 0x30, 0x9b, 
	/* 0x00004928 */ 0x2f, 0x00, 0x2f, 0xee, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004930 */ 0x01, 0x01, 0x08, 0x00, 0x96, 0x00, 0x00, 0x30, 
	/* 0x00004938 */ 0x3b, 0x30, 0x9f, 0x2f, 0x00, 0x2f, 0xee, 0x00, 
	/* 0x00004940 */ 0x00, 0x00, 0x00, 0x02, 0x02, 0x08, 0x00, 0x80, 
	/* 0x00004948 */ 0x00, 0x00, 0x30, 0x35, 0x30, 0xa0, 0x2f, 0x01, 
	/* 0x00004950 */ 0x2f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 
	/* 0x00004958 */ 0x08, 0x00, 0x80, 0x00, 0x00, 0x30, 0x31, 0x30, 
	/* 0x00004960 */ 0xa4, 0x2f, 0x00, 0x2f, 0xee, 0x00, 0x00, 0x00, 
	/* 0x00004968 */ 0x00, 0x04, 0x04, 0x08, 0x00, 0x10, 0x00, 0x00, 
	/* 0x00004970 */ 0x30, 0x3e, 0x30, 0xa5, 0x2f, 0x01, 0x2f, 0xef, 
	/* 0x00004978 */ 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x08, 0x00, 
	/* 0x00004980 */ 0x0f, 0x00, 0x00, 0x30, 0x11, 0x30, 0xa9, 0x2f, 
	/* 0x00004988 */ 0x01, 0x2f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x20, 
	/* 0x00004990 */ 0x20, 0x08, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004998 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000049a0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000049a8 */ 0x00, 0x30, 0x32, 0x30, 0xa1, 0x2f, 0x02, 0x2f, 
	/* 0x000049b0 */ 0xf0, 0x44, 0xc1, 0x00, 0x00, 0x02, 0x02, 0x03, 
	/* 0x000049b8 */ 0x00, 0x07, 0x00, 0x01, 0x30, 0x1f, 0x30, 0xaf, 
	/* 0x000049c0 */ 0x2f, 0x02, 0x2f, 0xf0, 0x44, 0xba, 0x00, 0x00, 
	/* 0x000049c8 */ 0x01, 0x01, 0x08, 0x00, 0xff, 0x00, 0x00, 0x30, 
	/* 0x000049d0 */ 0x17, 0x30, 0xb7, 0x2f, 0x01, 0x2f, 0xef, 0x44, 
	/* 0x000049d8 */ 0xb3, 0x00, 0x00, 0x80, 0x80, 0x08, 0x00, 0xff, 
	/* 0x000049e0 */ 0x00, 0x00, 0x48, 0x58, 0x00, 0x00, 0x49, 0xa9, 
	/* 0x000049e8 */ 0x49, 0xbc, 0x49, 0xcf, 0x00, 0x00, 0x4a, 0x2d, 
	/* 0x000049f0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x000049f8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a10 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a18 */ 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
	/* 0x00004a20 */ 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x10, 0x0c, 
	/* 0x00004a28 */ 0x0d, 0x0e, 0x11, 0x12, 0xff, 0x47, 0xb3, 0x47, 
	/* 0x00004a30 */ 0xd4, 0x47, 0xf5, 0x48, 0x58, 0x48, 0x16, 0x06, 
	/* 0x00004a38 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a40 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a48 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 
	/* 0x00004a58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a78 */ 0x00, 0x4a, 0xe9, 0x4a, 0xd6, 0x00, 0x00, 0x4a, 
	/* 0x00004a80 */ 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a88 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004a98 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004aa0 */ 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004aa8 */ 0xff, 0xff, 0xed, 0x60, 0x00, 0x00, 0x2f, 0x20, 
	/* 0x00004ab0 */ 0x30, 0x45, 0x30, 0x7a, 0x44, 0xac, 0x00, 0x00, 
	/* 0x00004ab8 */ 0x00, 0x00, 0x00, 0x00, 0x03, 0x08, 0x08, 0x00, 
	/* 0x00004ac0 */ 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ac8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ad0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x1f, 
	/* 0x00004ad8 */ 0x30, 0xaf, 0x2f, 0x02, 0x2f, 0xf0, 0x44, 0xba, 
	/* 0x00004ae0 */ 0x00, 0x00, 0x01, 0x01, 0x08, 0x00, 0xff, 0x00, 
	/* 0x00004ae8 */ 0x00, 0x30, 0x17, 0x30, 0xb7, 0x2f, 0x01, 0x2f, 
	/* 0x00004af0 */ 0xef, 0x44, 0xb3, 0x00, 0x00, 0x80, 0x80, 0x08, 
	/* 0x00004af8 */ 0x00, 0xff, 0x00, 0x00, 0x4a, 0xa2, 0x00, 0x00, 
	/* 0x00004b00 */ 0x4a, 0xd6, 0x4a, 0xe9, 0x00, 0x00, 0x4b, 0x45, 
	/* 0x00004b08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b10 */ 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b18 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b20 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b28 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b30 */ 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004b38 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004b40 */ 0xff, 0xff, 0x01, 0x02, 0xff, 0x00, 0x00, 0x00, 
	/* 0x00004b48 */ 0x00, 0x00, 0x00, 0x4a, 0xa2, 0x00, 0x00, 0x00, 
	/* 0x00004b50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	/* 0x00004b70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b80 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b88 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004b90 */ 0x00, 0x4c, 0x35, 0x4c, 0x22, 0x4c, 0x0f, 0x4b, 
	/* 0x00004b98 */ 0xdb, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004ba0 */ 0xff, 0x88, 0x20, 0x00, 0x00, 0x2f, 0x20, 0x30, 
	/* 0x00004ba8 */ 0x5b, 0x30, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004bb0 */ 0x00, 0x00, 0x00, 0x01, 0x08, 0x01, 0x00, 0x01, 
	/* 0x00004bb8 */ 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004bc0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004bc8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004bd0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004bd8 */ 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004be0 */ 0xff, 0xff, 0xff, 0xed, 0x60, 0x00, 0x00, 0x2f, 
	/* 0x00004be8 */ 0x20, 0x30, 0x45, 0x30, 0x7a, 0x44, 0xac, 0x00, 
	/* 0x00004bf0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x08, 0x08, 
	/* 0x00004bf8 */ 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
	/* 0x00004c10 */ 0x32, 0x30, 0xa1, 0x2f, 0x02, 0x2f, 0xf0, 0x44, 
	/* 0x00004c18 */ 0xc1, 0x00, 0x00, 0x02, 0x02, 0x03, 0x00, 0x07, 
	/* 0x00004c20 */ 0x00, 0x01, 0x30, 0x1f, 0x30, 0xaf, 0x2f, 0x02, 
	/* 0x00004c28 */ 0x2f, 0xf0, 0x44, 0xba, 0x00, 0x00, 0x01, 0x01, 
	/* 0x00004c30 */ 0x08, 0x00, 0xff, 0x00, 0x00, 0x30, 0x17, 0x30, 
	/* 0x00004c38 */ 0xb7, 0x2f, 0x01, 0x2f, 0xef, 0x44, 0xb3, 0x00, 
	/* 0x00004c40 */ 0x00, 0x80, 0x80, 0x08, 0x00, 0xff, 0x00, 0x00, 
	/* 0x00004c48 */ 0x4b, 0xdb, 0x00, 0x00, 0x4c, 0x0f, 0x4c, 0x22, 
	/* 0x00004c50 */ 0x4c, 0x35, 0x00, 0x00, 0x4c, 0x93, 0x00, 0x00, 
	/* 0x00004c58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c60 */ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004c80 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0x00004c88 */ 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 
	/* 0x00004c90 */ 0x02, 0x03, 0xff, 0x00, 0x00, 0x4b, 0x99, 0x00, 
	/* 0x00004c98 */ 0x00, 0x4b, 0xdb, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ca0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ca8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004cb0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004cb8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 
	/* 0x00004cc0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004cc8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004cd0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004cd8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 
	/* 0x00004ce0 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x11, 0x12, 
	/* 0x00004ce8 */ 0x12, 0x12, 0x10, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004cf0 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x0c, 0x12, 
	/* 0x00004cf8 */ 0x12, 0x12, 0x09, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d00 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x0a, 0x12, 0x12, 
	/* 0x00004d08 */ 0x12, 0x0d, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d10 */ 0x05, 0x06, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d18 */ 0x12, 0x12, 0x12, 0x03, 0x12, 0x04, 0x12, 0x07, 
	/* 0x00004d20 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d28 */ 0x02, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x0e, 
	/* 0x00004d30 */ 0x0f, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d38 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x00, 0x12, 
	/* 0x00004d40 */ 0x12, 0x12, 0x08, 0x12, 0x12, 0x12, 0x12, 0x0b, 
	/* 0x00004d48 */ 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 
	/* 0x00004d50 */ 0x01, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x0c, 
	/* 0x00004d58 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d60 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d68 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x58, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d70 */ 0x70, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d78 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d80 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x48, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d88 */ 0x0c, 0x38, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004d90 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x30, 0x0c, 0x0c, 
	/* 0x00004d98 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x40, 0x0c, 0x0c, 
	/* 0x00004da0 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004da8 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004db0 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004db8 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004dc0 */ 0x0c, 0x60, 0x0c, 0x0c, 0x18, 0x20, 0x0c, 0x0c, 
	/* 0x00004dc8 */ 0x0c, 0x68, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004dd0 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004dd8 */ 0x0c, 0x0c, 0x10, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004de0 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x28, 0x0c, 0x0c, 0x0c, 
	/* 0x00004de8 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004df0 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004df8 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x50, 
	/* 0x00004e00 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e08 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e10 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e18 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e20 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e28 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e30 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e38 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e40 */ 0x0c, 0x0c, 0x0c, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e48 */ 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	/* 0x00004e50 */ 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 
	/* 0x00004e58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e80 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e88 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004e98 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ea0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ea8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004eb0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004eb8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ec0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ec8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ed0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ed8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ee0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ee8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ef0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ef8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f10 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f18 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f20 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f28 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f30 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f38 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f40 */ 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	/* 0x00004f48 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f80 */ 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
	/* 0x00004f88 */ 0x00, 0x00, 0x70, 0x01, 0x00, 0x68, 0x01, 0x00, 
	/* 0x00004f90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004f98 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fa0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fa8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fb0 */ 0x60, 0x00, 0x00, 0x00, 0xc8, 0x0f, 0x32, 0x00, 
	/* 0x00004fb8 */ 0xc8, 0x05, 0xdc, 0x00, 0x64, 0x70, 0x01, 0x61, 
	/* 0x00004fc0 */ 0x01, 0x1f, 0x10, 0x62, 0x21, 0x17, 0x11, 0x00, 
	/* 0x00004fc8 */ 0x00, 0x1c, 0x0e, 0x14, 0x14, 0x00, 0x00, 0x00, 
	/* 0x00004fd0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fd8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fe0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004fe8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ff0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00004ff8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00005000 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00005008 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0x00005010 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0xd6, 
	/* 0x00005018 */ 0x9e, 0xa9, 0xd4, 0x76, 0x40, 0x55, 
};
#pragma CONST_SEG DEFAULT

