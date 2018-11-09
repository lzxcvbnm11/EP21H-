/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : nvm.c
* Description : nvm module
* Author: Xuenian.Feng
* Date: 2016-12-1
******************************************************************************/
/* Files for including */
#include "nvm_info.inc"

static BOOL nvm_InitSts = FALSE;
static U8 nvm_WriteCmdCnt =0;

static U8 nvm_Busy = FALSE;
static NVMKeyBlock_ENUM nvm_WriteCmdBuf[INDEX_NVM_ALL] = {INDEX_NVM_NONE};


static nvm_RW_ST nvm_W_Data;
/***************************************************
* Function: nvm_Init
* Description: NVM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/


void NVM_Init(void)
{
    BOOL res = 0;
    U16 i,j = 0;
    U8 buf[32] = {0};
    U8 chkSum = 0;
    PU8 pData = NULL;

    memset(nvm_Data.PedtrnAlrtSndSel.buf,0,NVM_SOUND_SELECT_LEN);
    memset(nvm_Data.PedtrnAlrtSndVol.buf,0,NVM_VOLUME_SELECT_LEN);

    memset(&nvm_W_Data,0,sizeof(nvm_RW_ST));

    res = DEPM_Read(ADDR_PEDTRN_ALRT_SND_SLT,nvm_Data.PedtrnAlrtSndSel.buf,NVM_SOUND_SELECT_LEN); //EED_ReadBytes(ADDR_SYS_PAGE0+0x00, nvm_Data.page0.buf, SIZE_NVM_PAGE);
    res = DEPM_Read(ADDR_PEDTRN_ALRT_SDN_VOL, nvm_Data.PedtrnAlrtSndVol.buf, NVM_VOLUME_SELECT_LEN);
	
    nvm_InitSts = DEPM_GetInitStatus();


 }

/***************************************************
* Function: NVM_Process_50ms
* Description: the process of the NVM module
* Parameters: none
* Returns: NONE
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/
void NVM_Process_50ms(void)
{
   NVMKeyBlock_ENUM index =INDEX_NVM_NONE;
   U8 i;

    if (TRUE == nvm_InitSts)
    {
        if (nvm_WriteCmdCnt >0)
        {
            nvm_Busy = TRUE;
			index =nvm_WriteCmdBuf[0];
			if (TRUE ==nvm_Write(index))
			{
		       nvm_WriteCmdCnt--;
	             for (i =0; i <nvm_WriteCmdCnt; i++)
	             {
	                nvm_WriteCmdBuf[i] =nvm_WriteCmdBuf[i+1];
	             }
			}
			else
			{
			/*do nothing*/
			}
        }
        else
        {
            nvm_Busy = FALSE;
        }

    }
    else
    {
        /*do nothing*/
    }
}

/***************************************************
* Function: NVM_GetParas
* Description: Read the paras of NVM module
* Parameters:
    input:   index :  the index of NVMEEDParaMap_ENUM
                 size : the size of the para
    output:   pRes : get the value of the para
* Returns:  RET_FAIL
                    RET_OK
                    RET_INVALID
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/

U8 NVM_GetParas(NVMKeyBlock_ENUM index, PU8 pRes, U8 size)
{
    U8 res = FALSE;

    U8 len = size;
    U8 buf[32] ={ 0};

    U8 nvm_Res = RET_FAIL;                 /* á??? return*/

    if (FALSE == nvm_InitSts)
    {
        nvm_Res = NVM_WR_DATAINVALID;
    }
    else if ( NULL_PTR == pRes)
    {
        nvm_Res =  NVM_WR_DATAINVALID;
    }
    else
    {
        switch (nvm_datasts[index].sts)
        {
            case STS_ERR:
                nvm_Res =  NVM_WR_EEDFLT;
                break;

            case STS_WAIT:
            case STS_WRITE:
                nvm_Res =  NVM_WR_ING;
                break;

            case STS_IDLE:
            default:
                nvm_Res =  NVM_WR_OK;
                switch (index)
                {
                    case INDEX_NVM_PEDTRN_ALRT_SND_SLT:
                        if (nvm_DataBase[index].size == (size+1))
                        {
                           memcpy(pRes, &(nvm_Data.PedtrnAlrtSndSel.data.PedtrnAlrtSndSel),size);
                           res = TRUE;
                        }
						else
						{
						}
                        break;
					case INDEX_NVM_PEDTRN_ALRT_SND_VOL:
				   		if (nvm_DataBase[index].size == (size+1))
				   		{
					  		memcpy(pRes, &(nvm_Data.PedtrnAlrtSndVol.data.PedtrnAlrtSndVol),size);
					  		res = TRUE;
				  		}
				   		else
				   		{
				   		}
				   		break;
					 
                   default:
                         break;
                }
                break;
        }


    }
    return nvm_Res;
}

/***************************************************
* Function: NVM_SetParas
* Description: Write a paras for nvm
* Parameters:
    input:   index :  the index of NVMEEDParaMap_ENUM
                 size : the size of the para
    output:   pRes : set  the value of the para
* Returns:  RET_FAIL
                    RET_OK
                    RET_INVALID
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/
U8 NVM_SetParas(NVMKeyBlock_ENUM index,  PU8 pRes, U8 size)
{
    U8 i = 0;

    U8 res = NVM_WR_OK;

    if (FALSE == nvm_InitSts)
    {
        res = NVM_WR_DATAINVALID;
    }
    else if ( (NULL_PTR == pRes) || (nvm_WriteCmdCnt >= INDEX_NVM_ALL))
    {
        res =  NVM_WR_DATAINVALID;
    }
    else
    {
    }

    if((STS_IDLE == nvm_datasts[index].sts)
        || (STS_WAIT== nvm_datasts[index].sts)
        ||(STS_ERR== nvm_datasts[index].sts))
    {

        //nvm_datasts[index].sts = STS_WAIT;
        res = nvm_Update(index, pRes, size);
        if(FALSE != res) /*IF DATA IS DIFFERENT*/
        {
            for (i = 0; i < nvm_WriteCmdCnt; i++)
            {
                if (nvm_WriteCmdBuf[i] == index)
                {
                    break;
                }
                else
                {
                /* do nothing */
                }
            }

            if (i == nvm_WriteCmdCnt)
            {
                nvm_WriteCmdBuf[nvm_WriteCmdCnt++] = index;
            }
            else
            {
                nvm_WriteCmdBuf[i] = index;
            }

           if(STS_ERR == nvm_datasts[index].sts)
            {
                res = NVM_WR_ERR_PRIVIOUS;
            }
           else
            {
                 res = NVM_WR_ING;
            }
            nvm_datasts[index].sts = STS_WAIT;
        }
        else
        {
            res = NVM_WR_OK;
        }
    }
    else/* nvm is writing a data*/
    {
        res = NVM_WR_ING;
    }
    return  res;
}


U8 NVM_GetWriteResult(NVMKeyBlock_ENUM index,  PU8 pRes)
{
    U8 i = 0;

    U8 res = RET_FAIL;

    if (FALSE == nvm_InitSts)
    {
        res = RET_FAIL;
    }
    else if (NULL_PTR == pRes)
    {
        res =  RET_INVALID;
    }
    else
    {
    	*pRes =nvm_datasts[index].sts;
		 res = RET_OK;
    }
     

    return  res;
}


U8 NVM_GetWorkSts(void)
{
    return nvm_Busy;
}


/***************************************************
* Function: nvm_Write
* Description: write the value to the nvm
* Parameters: input :   index: the index of NVMKeyBlock_ENUM
* Returns:TRUE or FALSE
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/
static U8 nvm_Write(NVMKeyBlock_ENUM index)
{
    U8 res = TRUE;

    switch (nvm_W_Data.Step) 
	{
		case WRITE_FINAL_PAGE:
		    if (nvm_W_Data.EndByte >0)   /*最后一页剩下字节数*/
		    {
			    res =DEPM_Write(nvm_W_Data.PageAddr, nvm_DataBase[index].pValue+nvm_W_Data.ofs, nvm_W_Data.EndByte);
		    }
		    else
		    {
		    }

		    if (res ==TRUE)
		    {
    			nvm_W_Data.Error=0;
    			nvm_W_Data.Step = WRITE_FIRST_PAGE;
                nvm_datasts[index].sts = STS_IDLE;
		    }
		    else
		    {
			     if (++nvm_W_Data.Error>3)
				 {
				 	nvm_W_Data.Step = WRITE_FIRST_PAGE; /* EED故障*/
	                nvm_datasts[index].sts = STS_ERR;
				 }
				 else
				 {
				 }
		    }
   		    break;

		case WRITE_MIDDLE_PAGE:
		    if (nvm_W_Data.PageNum >0)  /*剩下完整页*/
		    {
			    res =DEPM_Write(nvm_W_Data.PageAddr, nvm_DataBase[index].pValue+nvm_W_Data.ofs, E2PROM_PAGE_LEN);
		       if (res ==TRUE)
		       {
    		        nvm_W_Data.PageNum--;
    			    nvm_W_Data.PageAddr +=E2PROM_PAGE_LEN;
			    	nvm_W_Data.ofs +=E2PROM_PAGE_LEN;		
		       }
               else
               {
               }
		    }
		    else
		    {
		    }

		    if (res ==TRUE)
		    {
				nvm_W_Data.Error=0;
				if (nvm_W_Data.PageNum ==0)
				{
                   if (nvm_W_Data.EndByte >0)
			       {
			        	nvm_W_Data.Step = WRITE_FINAL_PAGE;
                   }
                   else
                   {
                        nvm_W_Data.Step = WRITE_FIRST_PAGE;
                        nvm_datasts[index].sts = STS_IDLE;
                   }
				}
				else
				{
				}
		    }
		    else
		    {
		    	 if (++nvm_W_Data.Error>3)
				 {
				 	nvm_W_Data.Step = WRITE_FIRST_PAGE; /* EED故障*/
	                nvm_datasts[index].sts = STS_ERR;
				 }
				 else
				 {
				 }
		    }
   		    break;

		case WRITE_FIRST_PAGE:
		default:
            nvm_datasts[index].sts = STS_WRITE;
		    nvm_W_Data.ofs =0;	
 		    nvm_W_Data.PageAddr =nvm_DataBase[index].addr;
 	        nvm_W_Data.FirstByte =E2PROM_PAGE_LEN -(nvm_DataBase[index].addr%E2PROM_PAGE_LEN);
            if (nvm_DataBase[index].size >nvm_W_Data.FirstByte) 
			{
        		  nvm_W_Data.PageNum =(nvm_DataBase[index].size -nvm_W_Data.FirstByte)/E2PROM_PAGE_LEN;
    		      nvm_W_Data.EndByte =(nvm_DataBase[index].size -nvm_W_Data.FirstByte)%E2PROM_PAGE_LEN;
            }
            else
			{
        		  nvm_W_Data.PageNum =0;
    		      nvm_W_Data.EndByte =0;
            }

	    	res =DEPM_Write(nvm_W_Data.PageAddr, nvm_DataBase[index].pValue, nvm_W_Data.FirstByte);
		    if (res == TRUE)
		    {		          

			    nvm_W_Data.Error=0;
                if (nvm_DataBase[index].size >nvm_W_Data.FirstByte) 
				{
    			    nvm_W_Data.PageAddr +=nvm_W_Data.FirstByte;
			   		nvm_W_Data.ofs +=nvm_W_Data.FirstByte;		
                    if (nvm_W_Data.PageNum >0)
			        {
			       		nvm_W_Data.Step = WRITE_MIDDLE_PAGE;
                    }
                    else
                    {
                        nvm_W_Data.Step = WRITE_FINAL_PAGE;
                    }
                 }
                 else
                 {
                     nvm_datasts[index].sts = STS_IDLE;
                 }
		    }
		    else
		    {
		    	 if (++nvm_W_Data.Error>3)
				 {
	                 nvm_datasts[index].sts = STS_ERR; /* EED故障*/
				 }
				 else
				 {
				 }
		    }
  		    break;
    }

    if (WRITE_FIRST_PAGE == nvm_W_Data.Step)
    {
        res =TRUE;
    }
    else
    {
        res =FALSE;
    }
    return res;
}

/***************************************************
* Function: nvm_UpdateData
* Description: update the data of the NVM
* Parameters:
    input:   index :  the index of NVMEEDParaMap_ENUM
                 size : the size of the para
    output:   pRes : get the value of the para
* Returns:TRUE or FALSE
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/
static U8 nvm_Update(NVMKeyBlock_ENUM index,  PU8 pRes, U8 size)
{
    U8 i = 0;

    U8 buf[32] ={ 0};

    S32 res = FALSE;
	
	
    if(NULL_PTR == pRes)
    {
        res = FALSE;
    }
    else
	{
	    switch (index)
	     {
	        case INDEX_NVM_PEDTRN_ALRT_SND_SLT:
	            if (nvm_DataBase[index].size == (size+1))
	            {
	                 res = memcmp(nvm_Data.PedtrnAlrtSndSel.buf,pRes,size);
	                 if(FALSE != res)
	                 {
		                memcpy(nvm_Data.PedtrnAlrtSndSel.buf,pRes,size);
		                nvm_Data.PedtrnAlrtSndSel.data.CheckSum = nvm_CalCheckSum(nvm_Data.PedtrnAlrtSndSel.buf, NVM_SOUND_SELECT_LEN-1);
	                 }
					 else
				 	 {
				 	 }
	            }
				else
			    {
			 	}
	            break;
			 case INDEX_NVM_PEDTRN_ALRT_SND_VOL:
	            if (nvm_DataBase[index].size == (size+1))
	            {
	                 res = memcmp(nvm_Data.PedtrnAlrtSndVol.buf,pRes,size);
	                 if(FALSE != res)
	                 {
		                memcpy(&(nvm_Data.PedtrnAlrtSndVol.buf),pRes,size);
		                nvm_Data.PedtrnAlrtSndVol.data.CheckSum = nvm_CalCheckSum(nvm_Data.PedtrnAlrtSndVol.buf, NVM_SOUND_SELECT_LEN-1);
	                 }
					 else
				 	 {
				 	 }
	            }
				else
			    {
			 	}
	            break;

	     }
	}

     return res;
}

/***************************************************
* Function: nvm_CalCheckSum
* Description: checksum
* Parameters: input :  the size of the data
                        output: the checksum of the data
* Returns: checkSum
* $Create & Verlog:$
* Author:Xuenian.Feng  Date:2016-12-1   Version:V1.0
****************************************************/
static U8 nvm_CalCheckSum(PU8 pRes, U8 size)
{
    U8 checkSum = 0;
    U8 i = 0;
    if (NULL != pRes)
    {
        for (i = 0; i < size; i++)
        {
            checkSum += *(pRes + i);
        }
    }
	else
    {
    }
    return checkSum;
}


/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Xuenian.Feng      2016-12-1               Initial
* V2.0       chensongming     2017-07-12             Initial
*===========================================================================*/

