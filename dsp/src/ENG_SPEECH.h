#ifndef ENG_SPEECH_H
#define ENG_SPEECH_H

#define BEGIN_ADDR   0x70000

typedef	signed int		s32;
typedef	unsigned int	u32;
typedef	unsigned char	u8;


/**发动机相关函数***********************************************************************************************************/
typedef struct
{
	float	spd;          
}
vehicle_para_inst;

u32 ENG_init(u32 mode);  //初始化

float ENG_process(void); //用于返回当前音频数据

void ESG_update(vehicle_para_inst para); //用于更新参数
/*************************************************************************************************************/



/**语音相关函数***********************************************************************************************************/
void Speech_init(u32 mode);

float Speech_process(u32* flag);
/*************************************************************************************************************/


/**混音*******************************************************************************************************/
float data_mix(float ENG_source, float Speech_source);
/*************************************************************************************************************/


/**************************************************调试实时配置参数*******************************************************/
void Set_Para(u32 mode, u8* para_stream);
/*************************************************************************************************************/


/**************************************************需要第三方实现*********************************************/
void data_in(u32 flash_addr, u32* data_buf, u32 len);
/*************************************************************************************************************/

#endif
