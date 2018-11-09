@rem /* ******************************************************************* */
@rem /*                                                                     */
@rem /*                     Mentor Graphics Corporation                     */
@rem /*                         All rights reserved                         */
@rem /*                                                                     */
@rem /* ******************************************************************* */
@rem
@rem /*         File: build.bat                                             */
@rem /*  Description: BUILDs the Volcano 6 "hello world" application for    */
@rem /*               Metrowerks Codewarrior / Star12                       */

@cls

@echo "------------------------> Set variables <--------------------------------"
@set APP=180516-lh1_EP21H_PPV_PACM-V11
@set CPATH=c:\Program Files\Freescale\CodeWarrior for S12(X) V5.0
@set VPATH=E:\EP21\项目\mcu_workspace\AS1380\AS1380\Sources\app\COM\volcano6\lib\mw50_s12_b
@set V6EXE=E:\EP21\项目\mcu_workspace\AS1380\AS1380\Sources\app\COM\volcano6\exe
@set CC="%CPATH%\prog\piper" chc12
@set LN="%CPATH%\prog\piper" linker
@set C_OPTS=-CpuHCS12 -DPPAGE_ADDR=0x15 -Mb -Os -Cc -D__NO_FLOAT__ -Lasm=%n.lst  -WmsgSd1106 -WmsgSd4443^
 -I%VPATH% -I"%CPATH%\lib\HC12c\include" -WmsgNu=abcde -WmsgSd4000
@set V_OPTS=-DNO_NM_CALLBACK
@set LIBS=%VPATH%\volcano6.lib "%CPATH%\lib\HC12c\lib\ansib.lib"

@echo "----------------> Process the Volcano config files <---------------------"
@rem /* Produce: "v_fn.out"                                                 */
@pause
@echo "test 11"
%V6EXE%\v6cfg %V_OPTS% -t -V %APP%.fix %APP%.net
@pause
@echo "test aaa"
@if errorlevel 1 goto :eof
@pause
@echo "test 22"
@rem /* Produce: "v_fp.out"                                                 */
%V6EXE%\v6cfg %V_OPTS% -l -t -V %APP%.fix %APP%.pri
@if errorlevel 1 goto :eof
@pause
@echo "test 33"
@rem /* Produce: "nvram.c" 
@pause
@echo "test 44"                                                 */
@if errorlevel 1 goto :eof
@pause
@echo "test 55"
@rem /* Produce: "v_gen.c" and "v_hand.h"                                   */
%V6EXE%\v6bnd %V_OPTS% -V -P %APP%.tgt
%V6EXE%\v6bnd %V_OPTS% -V -N %APP%.tgt
@pause
@echo "test 66"
@if errorlevel 1 goto :eof
@pause
@echo "test 77"


