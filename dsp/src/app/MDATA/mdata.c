/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mdata.c
* Description : MDATA module app
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* Files for including */
#include "mdata_info.inc"


static BOOL mdata_InitStatus = RET_FAIL;
static MdataSendMsg_ST mdata_SendMsg;
static MdataRecvMsg_ST mdata_RecvMsg;
static u8  NowGreamode = 0;
static u8  OldGreamode = 0;
/***************************************************
* Function: MDATA_Init
* Description: ADM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void MDATA_Init(void)
{
   PU8 PMdataSend = (PU8)&mdata_SendMsg;
   PU8 PMdatasRecv = (PU8)&mdata_RecvMsg;
   u8  i = 0;
   u8  len = 0;
   
   mdata_InitStatus = MCOM_GetInitStatus();

   mdata_RecvMsg.header_h = 0xa5;
   mdata_RecvMsg.vehspeed_h = 0;
   mdata_RecvMsg.length = sizeof(mdata_RecvMsg);
   mdata_RecvMsg.vehspeed_l = 0;
   mdata_RecvMsg.pasenable = 0;
   mdata_RecvMsg.passltreq = 11;
   mdata_RecvMsg.pasvolvalue = 0x1f;
   mdata_RecvMsg.pasenginereq = 0;
   mdata_RecvMsg.crc = 0;
  
   mdata_SendMsg.header_h = 0xaa;
   mdata_SendMsg.header_l = 0x55;
   mdata_SendMsg.length = sizeof(mdata_SendMsg);
   mdata_SendMsg.passltsts = 0;
   mdata_SendMsg.pasvolval = 0;
   mdata_SendMsg.pasenablests = 1;
   mdata_SendMsg.psaenginersts = 1;
   mdata_SendMsg.reserve0 = 0;
   mdata_SendMsg.reserve1 = 0;
   mdata_SendMsg.reserve2 = 0;
   mdata_SendMsg.crc = 0;

}                            
             
/***************************************************
* Function: MDATA_Process_20ms 
* Description: the process of the ADM module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void MDATA_Process_20ms(void)
{

    PU8 PMdataSendMsg = (PU8)&mdata_SendMsg;
	PU8 PMdataRvceMsg = (PU8)&mdata_RecvMsg;
    BOOL ret = RET_FAIL;
	u8  len = sizeof(mdata_RecvMsg);

	int i = 0;
	
    if (RET_FAIL == mdata_InitStatus)
    {
    	printf("mdata init fail\r\n");
    }
    else
    {	

	   MDATA_GetInformation();

       ret = MCOM_Process_20ms(PMdataSendMsg, PMdataRvceMsg, len);

       EVT_SetPasvolreqVaule(mdata_RecvMsg.pasvolvalue);

	 //  MDATA_GremodeDebounce();

    }
    
}

/***************************************************
* Function: MDATA_GetInitStatus
* Description: get the ADM module initialized status
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL MDATA_GetInitStatus(void)
{
    return mdata_InitStatus;
}

/***************************************************
* Function: MDATA_GetVehspeedVaule
* Description: get the mdata_speech vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
float MDATA_GetVehspeedVaule(void)
{	
	float mdata_speech = 0.0;
	int mdata_speech_tmp = 0;
	int mdata_speech_dot = 0;

	if(mdata_InitStatus == RET_FAIL) 
	{
	  return 0xffff; 
	}

	mdata_speech_tmp = (mdata_RecvMsg.vehspeed_h & 0x01);
	mdata_speech_tmp = mdata_speech_tmp*128 + mdata_RecvMsg.vehspeed_l;
	mdata_speech_dot = (mdata_RecvMsg.vehspeed_h >> 1);
	mdata_speech = mdata_speech_dot * 0.01 + mdata_speech_tmp;

    return mdata_speech;
}

/***************************************************
* Function: MDATA_GetGearodeVaule
* Description: get the NowGreamode vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8  MDATA_GetGearodeVaule(void)
{	
	
	if(mdata_InitStatus == RET_FAIL) 
	{
	  return 255; 
	}
	
    return NowGreamode;
}
/***************************************************
* Function: MDATA_GetPasenableVaule
* Description: get the pasenable vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8  MDATA_GetPasenableSts(void)
{	
	
	if(mdata_InitStatus == RET_FAIL) 
	{
	  return 255; 
	}
	
    return mdata_RecvMsg.pasenable;
}
/***************************************************
* Function: MDATA_Getpaspasenablesltreq
* Description: get the  passltreq vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8  MDATA_GetpassltreqVaule(void)
{	
	u8 Passltrvaule = 0;

	if(mdata_InitStatus == RET_FAIL) 
	{
	  return 255; 
	}
	
	/*no request*/
	if(mdata_RecvMsg.passltreq != 0)
	{
		Passltrvaule = mdata_RecvMsg.passltreq - 1;
	}
	else
	{
		Passltrvaule = MDATA_SLTRNOREQUEST;
	}

	if(Passltrvaule == MDATA_SINEWARE - 1)
	{
		Passltrvaule = MDATA_SINEWARE;
	}

    return Passltrvaule;
}
/***************************************************
* Function: MDATA_Getpasvolreq
* Description: get the Pasvolreq vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8 MDATA_GetPasvolreqVaule()
{	
	u8  vol_vaule = 0;
	vol_vaule = mdata_RecvMsg.pasvolvalue;

	if(mdata_InitStatus == RET_FAIL) 
	{
	  return INDEX_LEVEL_H;
	}
	
	if(vol_vaule == INDEX_LEVEL_H)
	{
		return INDEX_LEVEL_H;
	}
	else
	{
		return INDEX_LEVEL_L;
	}
		
}
/***************************************************
* Function: MDATA_GetPasenable
* Description: get the pasenginereq vaule
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8  MDATA_GetPasenginereqVaule(void)
{	
	
	if(mdata_InitStatus == RET_FAIL) 
	{
	  return 255; 
	}
	
    return mdata_RecvMsg.pasenginereq;
}

/***************************************************
* Function: MDATA_GetInformation
* Description: get the information
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void MDATA_GetInformation()
{	
	
    mdata_SendMsg.passltsts = EVT_GetpassltreqVaule();                          /*闂傚倸鍊风粈渚�骞栭位鍥焼瀹ュ懐锛熼梺鐟邦嚟婵攱绋夊澶嬬厵闁绘垶锕╁▓鏇熴亜閵夈儻韬柡灞界Ч瀹曨偊宕熼锟藉▍锝囩磽娴ｅ搫啸闁轰礁顭峰濠氭偄閸忕厧浜遍梺鍓插亞閸犳捇宕欓敓鐘斥拺闁告繂瀚刊鐓幟瑰搴濈盎妞ゎ偄绻掔槐鎺懳熼懖鈺冩闂傚鍋勫ú锕傚蓟閵娾晩鏁傞柨鐕傛嫹*/
    mdata_SendMsg.pasvolval = EVT_GetPasvolreqVaule();       				 /*闂傚倸鍊风粈渚�骞栭位鍥焼瀹ュ懐锛熼梺鐟邦嚟婵攱绋夊澶嬬厵婵炲枴銈庡殭婵炶濡囬幑銏犫攽閸♀晜鍍靛銈嗗笒閸嬪棝宕禒瀣拻濞达絽鎲＄拹鈥愁熆瑜庨〃鍛粹�﹂崹顕呮建闁跨喕妫勯锝夊蓟閵夘喗鏅滈梺鍓插亞閸熷潡骞忕紒妯肩瘈闁汇垽娼у瓭闂佺锕ら…鐑藉极瀹ュ拋鍚嬮柛娑变簼閺傦拷婵＄偑鍊栧Λ浣规叏閵堝纾归柟閭﹀弾濞堜粙鏌ｉ幋婵囧閻庢艾缍婂缁樻媴閼恒儳銆婇梺闈╃秶缁犳捇鐛箛娑欐櫢闁跨噦鎷�*/
   mdata_SendMsg.pasenablests = EVT_GetPasenableVaule();					/*闂傚倸鍊搁崐椋庣矆娓氾拷楠炲鏁撻悩鍐蹭画闂佹寧娲栭崐鎼佸垂閸岀偞鐓曟い顓熷灥娴滄繈鏌涘▎蹇曠闁哄苯绉瑰畷顐﹀礋椤掞拷濞咃綁鏌ｆ惔銏ｅ妞わ妇鏁诲濠氭晲婢跺﹦顓洪梺缁樺姀閺呮粓鏁嶆径瀣闁规儳顕崯鏌ユ煙閻戣姤鏁辨い銊ｅ劦閹瑩鎳犻鍌ゅ晪闂備浇顕栭崰鎾诲垂閽樺鏆︽繛鍡樻尭鍥撮梺鎼炲劗閺呮繈宕㈤鍕拺閻犲洦褰冮銏°亜閺冿拷閻楃姴鐣烽幎绛嬫晬闁绘劘灏欓鍡涙⒑缂佹ê鐏卞┑顔哄�濋幃锟犲即閵忋垹褰勯梺鎼炲劘閸庨亶宕濆鍫熷�垫慨妯煎亾鐎氾拷*/
   mdata_SendMsg.psaenginersts = EVT_GetPasenginereqVaule();			/*闂傚倸鍊搁崐椋庣矆娓氾拷楠炲鏁撻悩鍐蹭画闂佹寧娲栭崐鎼佸垂閸岀偞鐓曟い顓熷灥娴滄繈鏌涘▎蹇曠闁哄苯绉瑰畷顐﹀礋椤掞拷濞咃綁鏌ｆ惔銏ｅ妞わ附澹嗛幑銏犫槈濮楀棗鏅犲銈嗘瀹曠敻寮弽顓熲拺闁告稑锕﹂幊鍥╃磼閻樺磭澧い顐㈢箰鐓ゆい蹇撳椤斿矂姊洪崷顓炲妺婵﹤顭烽、娆撳箳濡や讲鎷洪柣鐘充航閸斿矂寮稿▎鎰箚妞ゆ劑鍨归顓㈡寠濠靛鐓欐繛鍫濈仢濞呮瑩鏌熷畡鏉挎Щ妞ゎ偅绻堥幃娆擃敆閿熶粙顢旈敓锟�*/
}
/***************************************************
* Function: MDATA_GetInformation
* Description: get the MDATA_GremodeDebounce
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
static u8  MDATA_GremodeDebounce(void)
{
    u8  value = 0;
    u8  res = RET_FAIL;
	static u8  cnt = 0;
	
    value = mdata_RecvMsg.greadmod;
    
  if (RET_OK == mdata_InitStatus)
    {
        if (OldGreamode == value)
        {
            if (cnt >= MDATA_DEBOUNCE_MAXCNT)
            {
                cnt = 0;
                NowGreamode = value;
                res = RET_OK;
            }
            else
            {
	            cnt++;
            }
        }
        else
        {
            cnt = 0;
            OldGreamode = value;
            res = RET_FAIL;
        }
		
    }/*end of if()*/
    else
    {
      ;
    }    
    return res;
}
/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-05      Initial
*
*===========================================================================*/

