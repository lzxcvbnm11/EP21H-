#ifndef __YD_TYPEDEFS_H__
#define __YD_TYPEDEFS_H__

typedef signed long long             S64;      /* Signed 64Bit datatype */
typedef unsigned long long         U64;         /* Unsigned 64Bit datatype */
typedef signed long long *   	PS64;       /* Point to Signed 64Bit datatype */
typedef unsigned long long * 	PU64;       /* Point to Unsigned 64Bit datatype */
typedef unsigned char                U8;                    /* Unsigned 8Bit datatype */
typedef unsigned short               U16;                   /* Unsigned 16Bit datatype */
typedef unsigned long                   U32;                 /* Unsigned 32Bit datatype */
typedef signed char                    S8;                  /* Signed 8Bit datatype */
typedef signed short                   S16;                     /* Signed 16Bit datatype */
typedef signed long                       S32;                   /* Signed 32Bit datatype */
typedef unsigned char *     	        PU8;                 /* Point to Unsigned 8Bit datatype */
typedef unsigned short * 	        PU16;               /* Point to Unsigned 16Bit datatype */
typedef unsigned long *  	        PU32;            /* Point to Unsigned 32Bit datatype */
typedef signed char *                 PS8;              /* Point to Signed 8Bit datatype */
typedef signed short *   	        PS16;           /* Point to Signed 16Bit datatype */
typedef signed long *    	               PS32;                /* Point to Signed 32Bit datatype */
typedef unsigned char      	        BOOL;               /* BOOL datatype */

//#define NULL            (0u)                        /* NULL type */
#define NULL_PTR   ((void *)0)              /* NULL Pointer type */
//#define FALSE	   (0u)                          /* Def for FALSE */
//#define TRUE	          (1u)                    /* Def for True */


/* common define return status */
#define RET_FAIL         	(0u)
#define RET_OK            	(1u)
#define RET_INVALID   		(2u)
#define RET_BUSY        	(3u)
#define RET_IDLE         	(4u)
#define VALID               (0u)
#define INVALID           	(1u)

#define ACTIVE          1
#define INACTIVE       	0


#define LOW     		0														
#define HIGH    		1					
#define ON         		1
#define OFF       		0

#define FALSE 			0
#define TRUE 			1


/* operation define */
#define SET_BIT(byte, bit)          (byte |= (1<<bit))
#define CLR_BIT(byte, bit)          (byte &= ~(1<<bit))
#define GET_BIT(byte, bit)          ((byte & (1<<bit)) ? 1 : 0)

#define SET_MASK(bit) (1ul << (bit))
#define CLEAR_MASK(bit)   (~(1ul << (bit)))

#define  ABS_SUB(x, y)    (x>y?(x-y):(y-x))
#define  ABS(x)                 ((x&0x80000000)?((~x)+1):x)


#define S_TO_MS(x)         (x * 1000)
#define S_TO_HOUR(x)       (x / 3600)
#define MS_TO_MIN(x)       (x / 60000)
#define MS_TO_S(x)       (x / 1000)

typedef struct Task_Tag
{
	void (*fTask)(void);
	U16 TaskTick;
	U16 TaskNextTick;
	U8  TaskPrior;
}Task_ST;

#endif  /* __YD_TYPEDEFS_H__ */

