#include "test_io.h"
//#include"key.h"
#include"chndot.h"

#include"word_lib.h"

#include "port.h"
#include"servo.h"
#include"keyboard.h"


Int8U Borard1_2=0;//选择硬件版本

Int8U Flag_1dw;
Int8U Flag_2dw;
Int8U Flag_3dw;
Int8U Flag_4dw;
Int8U Flag_5dw;
Int8U Flag_6dw;
Int8U Flag_7dw;
Int8U Flag_8dw;
Int8U Flag_9dw;
Int8U Flag_10dw;
Int8U Flag_11dw;
Int8U Flag_12dw;
Int8U Flag_13dw;
Int8U Flag_14dw;
Int8U Flag_15dw;
Int8U Flag_Mdw;

Int8U Flag_1up;
Int8U Flag_2up;
Int8U Flag_3up;
Int8U Flag_4up;
Int8U Flag_5up;
Int8U Flag_6up;
Int8U Flag_7up;
Int8U Flag_8up;
Int8U Flag_9up;
Int8U Flag_10up;
Int8U Flag_11up;
Int8U Flag_12up;
Int8U Flag_13up;
Int8U Flag_14up;
Int8U Flag_15up;
Int8U Flag_Mup;


void InPutDis(Int8U num,Int16U Xp,Int16U Yp,Int16U Colar)   //输入端口  测试
{
Int8U Num[2];

GLCD_SetWindow_Fill(Xp-5,Yp-5,Xp+80,Yp+40,Colar,Colar);

switch(num)
    {
	case 0:
	//ASCII_Printf("IN0",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 1:
		Printf24("原点",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 2:
		Printf24("切刀",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 3:
		Printf24("压纸",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 4:
		Printf24("托板",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 5:
		Printf24("红外",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 6:
		Printf24("A",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 7:
		Printf24("B",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 8:
		Printf24("Z",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 9:
		Printf24("ALARM",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 10:
		Printf24("10",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 11:
		Printf24("前极限",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 12:
		Printf24("中极限",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 13:
		Printf24("后极限",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 14:
		Printf24("手轮",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 15:
	//ASCII_Printf("IN15",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 16:
		Printf24("mZ_AC",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	}
    

}   

void IO_Stus_Dis(Int8U num,Int16U Xp,Int16U Yp,Int16U Colar)
{
switch(num)
    {
	case 0:
	//ASCII_Printf("IN0",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 1:
		Printf24("原点",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 2:
		Printf24("切刀",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 3:
		Printf24("压纸",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 4:
		Printf24("托板",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 5:
		Printf24("红外",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 6:
		Printf24("A",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 7:
		Printf24("B",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 8:
		Printf24("Z",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 9:
		Printf24("ALARM",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 10:
		Printf24("10",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 11:
		Printf24("前极限",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 12:
		Printf24("中极限",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 13:
		Printf24("后极限",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 14:
		Printf24("手轮",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;
	case 15:
	//ASCII_Printf("IN15",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 16:
		Printf24("mZ_AC",Xp,Yp,BLACK_COLOR,1,Colar);
	       break;	   
	}
   
}



void KeyDis(Int8U num,Int16U Xp,Int16U Yp,Int8U Keydown)   //测试键盘输入
{
Int8U Num[2];
Int16U Colar;
if(Keydown==1)
   Colar=GREEN_COLOR;
else 
   Colar=0xf07f;  
if(WorkStart_flag==0) 
GLCD_SetWindow_Fill(Xp-5,Yp-5,Xp+60,Yp+40,Colar,Colar);
else
	GLCD_SetWindow_Fill(Xp,Yp,Xp+50,Yp+25,Colar,Colar);

switch(num)
    {
	case 1:
		Printf24("1",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 2:
		Printf24("4",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 3:
		Printf24("7",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 4:
		Printf24("C",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 5:
		Printf24("2",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 6:
		Printf24("5",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 7:
		Printf24("8",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 8:
		Printf24("0",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 9:
		Printf24("3",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 10:
		Printf24("6",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 11:
		Printf24("9",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 12:
		Printf24(".",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 13:
		Printf24("+",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 14:
		Printf24("-",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 15:
		Printf24("=",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 16:
		Printf24("确定",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	case 17:
		Printf24("乘",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 18:
		Printf24("除",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 19:
		Printf24("前页",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 20:
		Printf24("后页",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 21:
		Printf24("推纸",Xp,Yp,BLACK_COLOR,0,0xffff);//Jostle
	       break;
	case 22:
		Printf24("插入",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 23:
		Printf24("删除",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 24:
		Printf24("修改",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 25:
		Printf24("上",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 26:
		Printf24("下",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 27:
		Printf24("左",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 28:
		Printf24("右",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 29:
		if(WorkStart_flag==0)
		Printf24("Shift",Xp,Yp,BLACK_COLOR,0,0xffff);
		else
			Printf16("Shift",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 30:
		Printf24("编程",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 31:
		Printf24("自动",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 32:
		Printf24("手动",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 33:
		Printf24("程序",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
			   
	case 34:
		Printf24("F1",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 35:
		Printf24("F2",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 36:
		Printf24("F3",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 37:
		Printf24("F4",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	case 38:
		Printf24("F5",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 39:
		Printf24("F6",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 40:  
		Printf24("帮助",Xp,Yp,BLACK_COLOR,0,0xffff);     //返回帮助---
		if(WorkStart_flag==0)
			{
		if(Keydown==1)
			{
			Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面
			Board_TestMod=0;
			RunDisplay_flag=0;
			outF_flag=0;
			outM_flag=0;
			outB_flag=0;
			Wheel_flag=0;
			OutFront_limit=0;
			OutMiddle_limit=0;
			OutBack_limit=0;
			Wheel_limit=0;
			OriginalError_flag=0;
			BackLimitError_flag=0;StartCheck_mode=0;
			ServoDisconnect_flag=0;
			MoveStop();
			RLOUT1_OFF;    // 允许裁切
			KeyLinkDis_flag=0;
			}
			}
		
			break;
	case 41:
		Printf24("运行",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 42:
		Printf24("停止",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	case 43:
		Printf24("后退",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=3;    //中速 
			SetMotorSpeed(MoveSpeed);
			MoveBack();
			}
	       break;
	case 44:
		Printf24("快退",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=1;    //高速 
			SetMotorSpeed(MoveSpeed);
			MoveBack();
			}
	       break;	   
	case 45:
		Printf24("快进",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=1;    //高速 
			SetMotorSpeed(MoveSpeed);
			MoveForward();
			}
	       break;
	case 46:
		Printf24("前进",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=3;    //中速 
			SetMotorSpeed(MoveSpeed);
			MoveForward();
			}
	       break;
	
	}
  
}   

void KeyDis_sel(Int32U Keycode,Int8U Keydown)//按键状态显示
{
if(WorkStart_flag==0) 
	{
switch(Keycode)
    {
		case k_1:
	     KeyDis(1,COL_0,ROW_1,Keydown);
		 
		            break;
		case k_4:
	     KeyDis(2,COL_0,ROW_2,Keydown);
		 
		            break;
		case k_7:
	     KeyDis(3,COL_0,ROW_3,Keydown);
		 
		            break;
		case k_cancel:
	     KeyDis(4,COL_0,ROW_4,Keydown);
		 
		            break;
					
		case k_2:
	     KeyDis(5,COL_1,ROW_1,Keydown);
		            break;
		case k_5:
	     KeyDis(6,COL_1,ROW_2,Keydown);
		            break;
		case k_8:
	     KeyDis(7,COL_1,ROW_3,Keydown);
		            break;
		case k_0:
	     KeyDis(8,COL_1,ROW_4,Keydown); 
		            break;
					
		case k_3:
			KeyDis(9,COL_2,ROW_1,Keydown);
		            break;
		case k_6:
			KeyDis(10,COL_2,ROW_2,Keydown);
		            break;
		case k_9:
			KeyDis(11,COL_2,ROW_3,Keydown);
		            break;
		case k_dot:
			KeyDis(12,COL_2,ROW_4,Keydown);
		            break;
					
		case k_add:
	     KeyDis(13,COL_3,ROW_1,Keydown);
		            break;
		case k_sub:
	     KeyDis(14,COL_3,ROW_2,Keydown);
		            break;
		case k_equal:
	     KeyDis(15,COL_3,ROW_3,Keydown);
		            break;
		case k_enter:
	     KeyDis(16,COL_3,ROW_4,Keydown);
		            break;
					
		case k_mul:
	     KeyDis(17,COL_4,ROW_1,Keydown);
		            break;
		case k_div:
	     KeyDis(18,COL_4,ROW_2,Keydown);
		            break;
		case k_pgup:
	     KeyDis(19,COL_4,ROW_3,Keydown);
		            break;
		case k_pgdown:
	     KeyDis(20,COL_4,ROW_4,Keydown);
		            break;
					
		//case k_backspace:
		case k_pushpap:  //推 纸
	     KeyDis(21,COL_5,ROW_1,Keydown);
		            break;
		case k_insert:
	     KeyDis(22,COL_5,ROW_2,Keydown);
		            break;
		case k_delete:
	     KeyDis(23,COL_5,ROW_3,Keydown);
		            break;
		case k_modify:
	     KeyDis(24,COL_5,ROW_4,Keydown);
		            break;
					
		case k_up:
			KeyDis(25,COL_7,ROW_1,Keydown);
			break;
		case k_down:
			KeyDis(26,COL_7,ROW_3,Keydown);
			break;
		case k_left:
			KeyDis(27,COL_6,ROW_2,Keydown);
			break;
		case k_right:
			KeyDis(28,COL_8,ROW_2,Keydown);
			break;
		
		case k_shift:
			KeyDis(29,COL_7,ROW_2,Keydown);
			break;
			
		case k_program:
			KeyDis(30,COL_6,ROW_4,Keydown);
			break;
		case k_auto:
			KeyDis(31,COL_7,ROW_4,Keydown);
			break;
		case k_manual:
			KeyDis(32,COL_8,ROW_4,Keydown);
			break;
		case k_procedure:
			KeyDis(33,COL_0,ROW_5,Keydown);
		            break;
		
		case k_f1:
			KeyDis(34,COL_1,ROW_5,Keydown);
			break;
		case k_f2:
			KeyDis(35,COL_2,ROW_5,Keydown);
			break;
		case k_f3:
			KeyDis(36,COL_3,ROW_5,Keydown);
		            break;
					
		case k_f4:
			KeyDis(37,COL_4,ROW_5,Keydown);
		            break;
		case k_f5:
			KeyDis(38,COL_5,ROW_5,Keydown);
		            break;
					
		case k_f6:
			KeyDis(39,COL_6,ROW_5,Keydown);
		            break;
		case k_help:
			KeyDis(40,COL_7,ROW_5,Keydown);
			break;
		
		case k_run:
			KeyDis(41,COL_1,ROW_6,Keydown);
			break;
		case k_stop:
			KeyDis(42,COL_3,ROW_6,Keydown);
			break;
			
		case k_back:
			KeyDis(43,COL_5,ROW_6,Keydown);
			break;
		case k_fast_back:
			KeyDis(44,COL_6,ROW_6,Keydown);
			break;
		case k_fast_ahead:
			KeyDis(45,COL_7,ROW_6,Keydown);
			break;
		case k_ahead:
			KeyDis(46,COL_8,ROW_6,Keydown);
			break;
		case k_fun_ahead:			//shift+前进==快进
			KeyDis(45,COL_7,ROW_6,Keydown);
			KeyDis(29,COL_7,ROW_2,Keydown);
			break;
		case k_fun_back:			//shift+后退==快退
			KeyDis(44,COL_6,ROW_6,Keydown);
			KeyDis(29,COL_7,ROW_2,Keydown);
		            break;
	
	}
	}
else
	{
switch(Keycode)
	{
	case k_1:
			KeyDis(1,TSTMOD_COL_0,TSTMOD_ROW_1,Keydown);
		break;
	case k_4:
			KeyDis(2,TSTMOD_COL_0,TSTMOD_ROW_2,Keydown);
		break;
	case k_7:
			KeyDis(3,TSTMOD_COL_0,TSTMOD_ROW_3,Keydown);
		break;
	case k_cancel:
			KeyDis(4,TSTMOD_COL_0,TSTMOD_ROW_4,Keydown);
		break;
	
	case k_2:
			KeyDis(5,TSTMOD_COL_1,TSTMOD_ROW_1,Keydown);
		break;
	case k_5:
			KeyDis(6,TSTMOD_COL_1,TSTMOD_ROW_2,Keydown);
		break;
	case k_8:
			KeyDis(7,TSTMOD_COL_1,TSTMOD_ROW_3,Keydown);
		break;
	case k_0:
			KeyDis(8,TSTMOD_COL_1,TSTMOD_ROW_4,Keydown);
		break;	
		
	case k_3:
			KeyDis(9,TSTMOD_COL_2,TSTMOD_ROW_1,Keydown);
		break;
	case k_6:
			KeyDis(10,TSTMOD_COL_2,TSTMOD_ROW_2,Keydown);
		break;
	case k_9:
			KeyDis(11,TSTMOD_COL_2,TSTMOD_ROW_3,Keydown);
		break;
	case k_dot:
			KeyDis(12,TSTMOD_COL_2,TSTMOD_ROW_4,Keydown);
		break;
	
	case k_add:
			KeyDis(13,TSTMOD_COL_3,TSTMOD_ROW_1,Keydown);
		break;
	case k_sub:
			KeyDis(14,TSTMOD_COL_3,TSTMOD_ROW_2,Keydown);
		break;
	case k_equal:
			KeyDis(15,TSTMOD_COL_3,TSTMOD_ROW_3,Keydown);
		break;
	case k_enter:
			KeyDis(16,TSTMOD_COL_3,TSTMOD_ROW_4,Keydown);
		break;
		
	case k_mul:
			KeyDis(17,TSTMOD_COL_4,TSTMOD_ROW_1,Keydown);
		break;
	case k_div:
			KeyDis(18,TSTMOD_COL_4,TSTMOD_ROW_2,Keydown);
		break;
	case k_pgup:
			KeyDis(19,TSTMOD_COL_4,TSTMOD_ROW_3,Keydown);
		break;
	case k_pgdown:
			KeyDis(20,TSTMOD_COL_4,TSTMOD_ROW_4,Keydown);
		break;
	
	//case k_backspace:
	case k_pushpap:  //推 纸
			KeyDis(21,TSTMOD_COL_5,TSTMOD_ROW_1,Keydown);
		break;
	case k_insert:
			KeyDis(22,TSTMOD_COL_5,TSTMOD_ROW_2,Keydown);
		break;
	case k_delete:
			KeyDis(23,TSTMOD_COL_5,TSTMOD_ROW_3,Keydown);
		break;
	case k_modify:
			KeyDis(24,TSTMOD_COL_5,TSTMOD_ROW_4,Keydown);
		break;
	
	case k_up:
			KeyDis(25,TSTMOD_COL_7,TSTMOD_ROW_1,Keydown);
		break;
	case k_down:
			KeyDis(26,TSTMOD_COL_7,TSTMOD_ROW_3,Keydown);
		break;
	case k_left:
			KeyDis(27,TSTMOD_COL_6,TSTMOD_ROW_2,Keydown);
		break;
	case k_right:
			KeyDis(28,TSTMOD_COL_8,TSTMOD_ROW_2,Keydown);
		break;
	
	case k_shift:
			KeyDis(29,TSTMOD_COL_7,TSTMOD_ROW_2,Keydown);
		break;
		
	case k_program:
			KeyDis(30,TSTMOD_COL_6,TSTMOD_ROW_4,Keydown);
		break;
	case k_auto:
			KeyDis(31,TSTMOD_COL_7,TSTMOD_ROW_4,Keydown);
		break;
	case k_manual:
			KeyDis(32,TSTMOD_COL_8,TSTMOD_ROW_4,Keydown);
		break;
	case k_procedure:
			KeyDis(33,TSTMOD_COL_0,TSTMOD_ROW_5,Keydown);
		break;
	
	case k_f1:
			KeyDis(34,TSTMOD_COL_1,TSTMOD_ROW_5,Keydown);
		break;
	case k_f2:
			KeyDis(35,TSTMOD_COL_2,TSTMOD_ROW_5,Keydown);
		break;
	case k_f3:
			KeyDis(36,TSTMOD_COL_3,TSTMOD_ROW_5,Keydown);
		break;
		
	case k_f4:
			KeyDis(37,TSTMOD_COL_4,TSTMOD_ROW_5,Keydown);
		break;
	case k_f5:
			KeyDis(38,TSTMOD_COL_5,TSTMOD_ROW_5,Keydown);
		break;
	case k_f6:
			KeyDis(39,TSTMOD_COL_6,TSTMOD_ROW_5,Keydown);
		break;
	case k_help:
			KeyDis(40,TSTMOD_COL_7,TSTMOD_ROW_5,Keydown);
		break;
	
	case k_run:
			KeyDis(41,TSTMOD_COL_1,TSTMOD_ROW_6,Keydown);
		break;
	case k_stop:
			KeyDis(42,TSTMOD_COL_3,TSTMOD_ROW_6,Keydown);
		break;
		
	case k_back:
			KeyDis(43,TSTMOD_COL_5,TSTMOD_ROW_6,Keydown);
		break;
	case k_fast_back:
			KeyDis(44,TSTMOD_COL_6,TSTMOD_ROW_6,Keydown);
		break;
	case k_fast_ahead:
			KeyDis(45,TSTMOD_COL_7,TSTMOD_ROW_6,Keydown);
		break;
	case k_ahead:
			KeyDis(46,TSTMOD_COL_8,TSTMOD_ROW_6,Keydown);
		break;
	case k_fun_ahead:			//shift+前进==快进
			KeyDis(45,TSTMOD_COL_7,TSTMOD_ROW_6,Keydown);
			KeyDis(29,TSTMOD_COL_7,TSTMOD_ROW_2,Keydown);
		break;
	case k_fun_back:			//shift+后退==快退
			KeyDis(44,TSTMOD_COL_6,TSTMOD_ROW_6,Keydown);
			KeyDis(29,TSTMOD_COL_7,TSTMOD_ROW_2,Keydown);
		break;
	}
}
}


void KeyDis_Init(void)//按键显示初始化
{
KeyDis_sel(k_1, 0);
KeyDis_sel(k_2, 0);
KeyDis_sel(k_3, 0);
KeyDis_sel(k_4, 0);
KeyDis_sel(k_5, 0);
KeyDis_sel(k_6, 0);
KeyDis_sel(k_7, 0);
KeyDis_sel(k_8, 0);
KeyDis_sel(k_9, 0);
KeyDis_sel(k_0, 0);

KeyDis_sel(k_cancel, 0);
KeyDis_sel(k_dot, 0);

KeyDis_sel(k_add, 0);
KeyDis_sel(k_sub, 0);
KeyDis_sel(k_equal, 0);
KeyDis_sel(k_enter, 0);

KeyDis_sel(k_mul, 0);
KeyDis_sel(k_div, 0);
KeyDis_sel(k_pgup, 0);
KeyDis_sel(k_pgdown, 0);

KeyDis_sel(k_pushpap, 0);
KeyDis_sel(k_insert, 0);
KeyDis_sel(k_delete, 0);
KeyDis_sel(k_modify, 0);

KeyDis_sel(k_up, 0);
KeyDis_sel(k_down, 0);
KeyDis_sel(k_left, 0);
KeyDis_sel(k_right, 0);
KeyDis_sel(k_shift, 0);

KeyDis_sel(k_program, 0);
KeyDis_sel(k_auto, 0);
KeyDis_sel(k_manual, 0);
KeyDis_sel(k_procedure, 0);

KeyDis_sel(k_f1, 0);
KeyDis_sel(k_f2, 0);
KeyDis_sel(k_f3, 0);
KeyDis_sel(k_f4, 0);
KeyDis_sel(k_f5, 0);
KeyDis_sel(k_f6, 0);
KeyDis_sel(k_help, 0);

KeyDis_sel(k_run, 0);
KeyDis_sel(k_stop, 0);
KeyDis_sel(k_back, 0);
KeyDis_sel(k_fast_back, 0);
KeyDis_sel(k_ahead, 0);
KeyDis_sel(k_fast_ahead, 0);

}


void IO_InputDisInit(void)  //Io 输入口初始值
{
 Flag_1dw=0;
 Flag_2dw=0;
 Flag_3dw=0;
 Flag_4dw=0;
 Flag_5dw=0;
 Flag_6dw=0;
 Flag_7dw=0;
 Flag_8dw=0;
 Flag_9dw=0;
 Flag_10dw=0;
 Flag_11dw=0;
 Flag_12dw=0;
 Flag_13dw=0;
 Flag_14dw=0;
 Flag_15dw=0;
 Flag_Mdw=0;

 Flag_1up=0;
 Flag_2up=0;
 Flag_3up=0;
 Flag_4up=0;
 Flag_5up=0;
 Flag_6up=0;
 Flag_7up=0;
 Flag_8up=0;
 Flag_9up=0;
 Flag_10up=0;
 Flag_11up=0;
 Flag_12up=0;
 Flag_13up=0;
 Flag_14up=0;
 Flag_15up=0;
 Flag_Mup=0;
}

void IOinputTest1_2(void)//IO  输入测试********1.2
{
if(OIN1_PIN==0) //1
	     {
		  if(Flag_1dw==0)
		    {
	        InPutDis(1,START_X,START_Y,DOWN_COL);
			Flag_1dw=1;
			Flag_1up=0;
			}
		 }
	  else
	     {
		  if(Flag_1up==0)
		    {
	        InPutDis(1,START_X,START_Y,UP_COL);
			Flag_1up=1;
			Flag_1dw=0;
			}
		 }
		 
	  if(OIN2_PIN==0)//2
	    {
		  if(Flag_2dw==0)
		    {
	        InPutDis(2, START_X+Num_W,START_Y,DOWN_COL);
			Flag_2up=0;
			Flag_2dw=1;
			}
		 }
	  else
	     {
		  if(Flag_2up==0)
		    {
	        InPutDis(2, START_X+Num_W,START_Y,UP_COL);
			Flag_2up=1;
			Flag_2dw=0;
			}
		 }

	  if(OIN3_PIN==0) //3
	    {
		  if(Flag_3dw==0)
		    {
	        InPutDis(3, START_X+Num_W*2,START_Y,DOWN_COL);
			Flag_3up=0;
			Flag_3dw=1;
			}
		 }
	  else
	     {
		  if(Flag_3up==0)
		    {
	        InPutDis(3, START_X+Num_W*2,START_Y,UP_COL);
			Flag_3up=1;
			Flag_3dw=0;
			}
		 }
	        
			
	  if(OIN4_PIN==0)//4
	    {
		  if(Flag_4dw==0)
		    {
	        InPutDis(4, START_X+Num_W*3,START_Y,DOWN_COL);
			Flag_4up=0;
			Flag_4dw=1;
			}
		 }
	  else
	     {
		  if(Flag_4up==0)
		    {
	        InPutDis(4, START_X+Num_W*3,START_Y,UP_COL);
			Flag_4up=1;
			Flag_4dw=0;
			}
		 }
	        
			
	  if(OIN5_PIN==0)//5
	    {
		  if(Flag_5dw==0)
		    {
	        InPutDis(5, START_X+Num_W*4,START_Y,DOWN_COL);
			Flag_5up=0;
			Flag_5dw=1;
			}
		 }
	  else
	     {
		  if(Flag_5up==0)
		    {
	        InPutDis(5, START_X+Num_W*4,START_Y,UP_COL);
			Flag_5up=1;
			Flag_5dw=0;
			}
		 }
	        
			
	  if(OIN6_PIN==0) //6
	    {
		  if(Flag_6dw==0)
		    {
	        InPutDis(6, START_X+Num_W*5,START_Y,DOWN_COL);
			Flag_6up=0;
			Flag_6dw=1;
			}
		 }
	  else
	     {
		  if(Flag_6up==0)
		    {
	        InPutDis(6, START_X+Num_W*5,START_Y,UP_COL);
			Flag_6up=1;
			Flag_6dw=0;
			}
		 }
	  	    
			
	  if(OIN7_PIN==0)//7
	    {
		  if(Flag_7dw==0)
		    {
	        InPutDis(7, START_X+Num_W*6,START_Y,DOWN_COL);
			Flag_7up=0;
			Flag_7dw=1;
			}
		 }
	  else
	     {
		  if(Flag_7up==0)
		    {
	        InPutDis(7, START_X+Num_W*6,START_Y,UP_COL);
			Flag_7up=1;
			Flag_7dw=0;
			}
		 }
	  	    	
	  if(M_ZIN_PIN==0) //M_Zin
	    {
		  if(Flag_Mdw==0)
		    {
	        InPutDis(16, START_X+Num_W*7,START_Y,DOWN_COL);
			Flag_Mup=0;
			Flag_Mdw=1;
			}
		 }
	  else
	     {
		  if(Flag_Mup==0)
		    {
	        InPutDis(16, START_X+Num_W*7,START_Y,UP_COL);
			Flag_Mup=1;
			Flag_Mdw=0;
			}
		 } 
	  
	  
	  if(OIN8_PIN==0) //
	    {
		  if(Flag_8dw==0)
		    {
	        InPutDis(8, START_X,START_Y+Num_H,DOWN_COL);
			Flag_8up=0;
			Flag_8dw=1;
			}
		 }
	  else
	     {
		  if(Flag_8up==0)
		    {
	        InPutDis(8, START_X,START_Y+Num_H,UP_COL);
			Flag_8up=1;
			Flag_8dw=0;
			}
		 }
	  	    
		/*	
	  if(OIN9_PIN==0) //
	    {
		  if(Flag_9dw==0)
		    {
	        InPutDis(9, START_X+Num_W,START_Y+Num_H,DOWN_COL);
			Flag_9up=0;
			Flag_9dw=1;
			}
		 }
	  else
	     {
		  if(Flag_9up==0)
		    {
	        InPutDis(9, START_X+Num_W,START_Y+Num_H,UP_COL);
			Flag_9up=1;
			Flag_9dw=0;
			}
		 }
	  	    
			
	  if(OIN10_PIN==0) //10
	    {
		  if(Flag_10dw==0)
		    {
	        InPutDis(10, START_X+Num_W*2,START_Y+Num_H,DOWN_COL);
			Flag_10up=0;
			Flag_10dw=1;
			}
		 }
	  else
	     {
		  if(Flag_10up==0)
		    {
	        InPutDis(10, START_X+Num_W*2,START_Y+Num_H,UP_COL);
			Flag_10up=1;
			Flag_10dw=0;
			}
		 }
	  	    */
			
	  if(OIN11_PIN==0) //
	    {
		  if(Flag_11dw==0)
		    {
	        InPutDis(11, START_X+Num_W*3,START_Y+Num_H,DOWN_COL);
			Flag_11up=0;
			Flag_11dw=1;
			}
		 }
	  else
	     {
		  if(Flag_11up==0)
		    {
	        InPutDis(11, START_X+Num_W*3,START_Y+Num_H,UP_COL);
			Flag_11up=1;
			Flag_11dw=0;
			}
		 }
	  	    
		/*	
	  if(OIN12_PIN==0) //
	    {
		  if(Flag_12dw==0)
		    {
	        InPutDis(12, START_X+Num_W*4,START_Y+Num_H,DOWN_COL);
			Flag_12up=0;
			Flag_12dw=1;
			}
		 }
	  else
	     {
		  if(Flag_12up==0)
		    {
	        InPutDis(12, START_X+Num_W*4,START_Y+Num_H,UP_COL);
			Flag_12up=1;
			Flag_12dw=0;
			}
		 }
	  	    
			
	  if(OIN13_PIN==0) //
	    {
		  if(Flag_13dw==0)
		    {
	        InPutDis(13, START_X+Num_W*5,START_Y+Num_H,DOWN_COL);
			Flag_13up=0;
			Flag_13dw=1;
			}
		 }
	  else
	     {
		  if(Flag_13up==0)
		    {
	        InPutDis(13, START_X+Num_W*5,START_Y+Num_H,UP_COL);
			Flag_13up=1;
			Flag_13dw=0;
			}
		 }
	  	    
			
	  if(OIN14_PIN==0) //
	    {
		  if(Flag_14dw==0)
		    {
	        InPutDis(14, START_X+Num_W*6,START_Y+Num_H,DOWN_COL);
			Flag_14up=0;
			Flag_14dw=1;
			}
		 }
	  else
	     {
		  if(Flag_14up==0)
		    {
	        InPutDis(14, START_X+Num_W*6,START_Y+Num_H,UP_COL);
			Flag_14up=1;
			Flag_14dw=0;
			}
		 }
		 
	  if(OIN15_PIN==0) //
	    {
		  if(Flag_15dw==0)
		    {
	        InPutDis(15, START_X+Num_W*7,START_Y+Num_H,DOWN_COL);
			Flag_15up=0;
			Flag_15dw=1;
			}
		 }
	  else
	     {
		  if(Flag_15up==0)
		    {
	        InPutDis(15, START_X+Num_W*7,START_Y+Num_H,UP_COL);
			Flag_15up=1;
			Flag_15dw=0;
			}
		 }
*/
}


void IOinputTest1_3(void)//IO  输入测试********1.3
{
if(OIN1_PIN==0) //1
	     {
		  if(Flag_1dw==0)
		    {
	        InPutDis(1,START_X,START_Y,DOWN_COL);
			Flag_1dw=1;
			Flag_1up=0;
			}
		 }
	  else
	     {
		  if(Flag_1up==0)
		    {
	        InPutDis(1,START_X,START_Y,UP_COL);
			Flag_1up=1;
			Flag_1dw=0;
			}
		 }
		 
	  if(OIN2_PIN==0)//2
	    {
		  if(Flag_2dw==0)
		    {
	        InPutDis(2, START_X+Num_W,START_Y,DOWN_COL);
			Flag_2up=0;
			Flag_2dw=1;
			}
		 }
	  else
	     {
		  if(Flag_2up==0)
		    {
	        InPutDis(2, START_X+Num_W,START_Y,UP_COL);
			Flag_2up=1;
			Flag_2dw=0;
			}
		 }

	  if(OIN3_PIN==0) //3
	    {
		  if(Flag_3dw==0)
		    {
	        InPutDis(3, START_X+Num_W*2,START_Y,DOWN_COL);
			Flag_3up=0;
			Flag_3dw=1;
			}
		 }
	  else
	     {
		  if(Flag_3up==0)
		    {
	        InPutDis(3, START_X+Num_W*2,START_Y,UP_COL);
			Flag_3up=1;
			Flag_3dw=0;
			}
		 }
	        
			
	  if(OIN4_PIN==0)//4
	    {
		  if(Flag_4dw==0)
		    {
	        InPutDis(4, START_X+Num_W*3,START_Y,DOWN_COL);
			Flag_4up=0;
			Flag_4dw=1;
			}
		 }
	  else
	     {
		  if(Flag_4up==0)
		    {
	        InPutDis(4, START_X+Num_W*3,START_Y,UP_COL);
			Flag_4up=1;
			Flag_4dw=0;
			}
		 }
	        
			
	  if(OIN5_PIN==0)//5
	    {
		  if(Flag_5dw==0)
		    {
	        InPutDis(5, START_X+Num_W*4,START_Y,DOWN_COL);
			Flag_5up=0;
			Flag_5dw=1;
			}
		 }
	  else
	     {
		  if(Flag_5up==0)
		    {
	        InPutDis(5, START_X+Num_W*4,START_Y,UP_COL);
			Flag_5up=1;
			Flag_5dw=0;
			}
		 }
	        
			
	  if(OIN6_PIN==0) //6
	    {
		  if(Flag_6dw==0)
		    {
	        InPutDis(6, START_X+Num_W*5,START_Y,DOWN_COL);
			Flag_6up=0;
			Flag_6dw=1;
			}
		 }
	  else
	     {
		  if(Flag_6up==0)
		    {
	        InPutDis(6, START_X+Num_W*5,START_Y,UP_COL);
			Flag_6up=1;
			Flag_6dw=0;
			}
		 }
	  	    
			
	  if(OIN7_PIN==0)//7
	    {
		  if(Flag_7dw==0)
		    {
	        InPutDis(7, START_X+Num_W*6,START_Y,DOWN_COL);
			Flag_7up=0;
			Flag_7dw=1;
			}
		 }
	  else
	     {
		  if(Flag_7up==0)
		    {
	        InPutDis(7, START_X+Num_W*6,START_Y,UP_COL);
			Flag_7up=1;
			Flag_7dw=0;
			}
		 }
	  	    	
	  
	  
	  if(OIN8_PIN==0) //
	    {
		  if(Flag_8dw==0)
		    {
	        InPutDis(8, START_X,START_Y+Num_H,DOWN_COL);
			Flag_8up=0;
			Flag_8dw=1;
			}
		 }
	  else
	     {
		  if(Flag_8up==0)
		    {
	        InPutDis(8, START_X,START_Y+Num_H,UP_COL);
			Flag_8up=1;
			Flag_8dw=0;
			}
		 }
	  	    
		/*	
	  if(OIN9_PIN==0) //
	    {
		  if(Flag_9dw==0)
		    {
	        InPutDis(9, START_X+Num_W,START_Y+Num_H,DOWN_COL);
			Flag_9up=0;
			Flag_9dw=1;
			}
		 }
	  else
	     {
		  if(Flag_9up==0)
		    {
	        InPutDis(9, START_X+Num_W,START_Y+Num_H,UP_COL);
			Flag_9up=1;
			Flag_9dw=0;
			}
		 }
	  	    
			
	  if(OIN10_PIN==0) //10
	    {
		  if(Flag_10dw==0)
		    {
	        InPutDis(10, START_X+Num_W*2,START_Y+Num_H,DOWN_COL);
			Flag_10up=0;
			Flag_10dw=1;
			}
		 }
	  else
	     {
		  if(Flag_10up==0)
		    {
	        InPutDis(10, START_X+Num_W*2,START_Y+Num_H,UP_COL);
			Flag_10up=1;
			Flag_10dw=0;
			}
		 }
	  	    */
			
	  if(OIN11_PIN==0) //
	    {
		  if(Flag_11dw==0)
		    {
	        InPutDis(11, START_X+Num_W*3,START_Y+Num_H,DOWN_COL);
			Flag_11up=0;
			Flag_11dw=1;
			}
		 }
	  else
	     {
		  if(Flag_11up==0)
		    {
	        InPutDis(11, START_X+Num_W*3,START_Y+Num_H,UP_COL);
			Flag_11up=1;
			Flag_11dw=0;
			}
		 }
	  	    
			
	  if(OIN12_PIN==0) //
	    {
		  if(Flag_12dw==0)
		    {
	        InPutDis(12, START_X+Num_W*4,START_Y+Num_H,DOWN_COL);
			Flag_12up=0;
			Flag_12dw=1;
			}
		 }
	  else
	     {
		  if(Flag_12up==0)
		    {
	        InPutDis(12, START_X+Num_W*4,START_Y+Num_H,UP_COL);
			Flag_12up=1;
			Flag_12dw=0;
			}
		 }
	  	    
			
	  if(OIN13_PIN==0) //
	    {
		  if(Flag_13dw==0)
		    {
	        InPutDis(13, START_X+Num_W*5,START_Y+Num_H,DOWN_COL);
			Flag_13up=0;
			Flag_13dw=1;
			}
		 }
	  else
	     {
		  if(Flag_13up==0)
		    {
	        InPutDis(13, START_X+Num_W*5,START_Y+Num_H,UP_COL);
			Flag_13up=1;
			Flag_13dw=0;
			}
		 }
	  	    
			
	  if(OIN14_PIN==0) //
	    {
		  if(Flag_14dw==0)
		    {
	        InPutDis(14, START_X+Num_W*6,START_Y+Num_H,DOWN_COL);
			Flag_14up=0;
			Flag_14dw=1;
			}
		 }
	  else
	     {
		  if(Flag_14up==0)
		    {
	        InPutDis(14, START_X+Num_W*6,START_Y+Num_H,UP_COL);
			Flag_14up=1;
			Flag_14dw=0;
			}
		 }
		
	  	    
	/*		
	  if(OIN15_PIN==0) //
	    {
		  if(Flag_15dw==0)
		    {
	        InPutDis(15, START_X+Num_W*7,START_Y+Num_H,DOWN_COL);
			Flag_15up=0;
			Flag_15dw=1;
			}
		 }
	  else
	     {
		  if(Flag_15up==0)
		    {
	        InPutDis(15, START_X+Num_W*7,START_Y+Num_H,UP_COL);
			Flag_15up=1;
			Flag_15dw=0;
			}
		 }
*/
}
void IOinputTest(void)//IO  输入测试********all
{
if(OIN1_PIN==0) //1
	 {
	  if(Flag_1dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(1,START_X,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(1,IO_STUS_X1,IO_STUS_Y1,DOWN_COL);
		Flag_1dw=1;
		Flag_1up=0;
		}
	 }
  else
	 {
	  if(Flag_1up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(1,START_X,START_Y,UP_COL);
		else
			IO_Stus_Dis(1,IO_STUS_X1,IO_STUS_Y1,UP_COL);
		Flag_1up=1;
		Flag_1dw=0;
		}
	 }
	 
  if(OIN2_PIN==0)//2
	{
	  if(Flag_2dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(2, START_X+Num_W,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(2,IO_STUS_X2,IO_STUS_Y1,DOWN_COL);
		Flag_2up=0;
		Flag_2dw=1;
		}
	 }
  else
	 {
	  if(Flag_2up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(2, START_X+Num_W,START_Y,UP_COL);
		else
			IO_Stus_Dis(2,IO_STUS_X2,IO_STUS_Y1 ,UP_COL);
		Flag_2up=1;
		Flag_2dw=0;
		}
	 }

  if(OIN3_PIN==0) //3
	{
	  if(Flag_3dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(3, START_X+Num_W*2,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(3,IO_STUS_X3,IO_STUS_Y1 ,DOWN_COL);
		Flag_3up=0;
		Flag_3dw=1;
		}
	 }
  else
	 {
	  if(Flag_3up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(3, START_X+Num_W*2,START_Y,UP_COL);
		else
			IO_Stus_Dis(3,IO_STUS_X3,IO_STUS_Y1 ,UP_COL);
		Flag_3up=1;
		Flag_3dw=0;
		}
	 }
		
		
  if(OIN4_PIN==0)//4
	{
	  if(Flag_4dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(4, START_X+Num_W*3,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(4,IO_STUS_X4,IO_STUS_Y1 ,DOWN_COL);
		Flag_4up=0;
		Flag_4dw=1;
		}
	 }
  else
	 {
	  if(Flag_4up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(4, START_X+Num_W*3,START_Y,UP_COL);
		else
			IO_Stus_Dis(4,IO_STUS_X4,IO_STUS_Y1 ,UP_COL);
		Flag_4up=1;
		Flag_4dw=0;
		}
	 }
		
		
  if(OIN5_PIN==0)//5
	{
	  if(Flag_5dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(5, START_X+Num_W*4,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(5,IO_STUS_X5,IO_STUS_Y1 ,DOWN_COL);
		Flag_5up=0;
		Flag_5dw=1;
		}
	 }
  else
	 {
	  if(Flag_5up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(5, START_X+Num_W*4,START_Y,UP_COL);
		else
			IO_Stus_Dis(5,IO_STUS_X5,IO_STUS_Y1 ,UP_COL);
		Flag_5up=1;
		Flag_5dw=0;
		}
	 }
		
		
  if(OIN6_PIN==0) //6
	{
	  if(Flag_6dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(6, START_X+Num_W*5,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(6,IO_STUS_X6,IO_STUS_Y1 ,DOWN_COL);
		Flag_6up=0;
		Flag_6dw=1;
		}
	 }
  else
	 {
	  if(Flag_6up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(6, START_X+Num_W*5,START_Y,UP_COL);
		else
			IO_Stus_Dis(6,IO_STUS_X6,IO_STUS_Y1 ,UP_COL);
		Flag_6up=1;
		Flag_6dw=0;
		}
	 }
		
		
  if(OIN7_PIN==0)//7
	{
	  if(Flag_7dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(7, START_X+Num_W*6,START_Y,DOWN_COL);
		else
			IO_Stus_Dis(7,IO_STUS_X7,IO_STUS_Y1 ,DOWN_COL);
		Flag_7up=0;
		Flag_7dw=1;
		}
	 }
  else
	 {
	  if(Flag_7up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(7, START_X+Num_W*6,START_Y,UP_COL);
		else
			IO_Stus_Dis(7,IO_STUS_X7,IO_STUS_Y1 ,UP_COL);
		Flag_7up=1;
		Flag_7dw=0;
		}
	 }
			
  
  if(OIN8_PIN==0) //
	{
	  if(Flag_8dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(8, START_X,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(8,IO_STUS_X1,IO_STUS_Y2 ,DOWN_COL);
		Flag_8up=0;
		Flag_8dw=1;
		}
	 }
  else
	 {
	  if(Flag_8up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(8, START_X,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(8,IO_STUS_X1,IO_STUS_Y2 ,UP_COL);
		Flag_8up=1;
		Flag_8dw=0;
		}
	 }
		
		
  if(OIN9_PIN==0) //
	{
	  if(Flag_9dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(9, START_X+Num_W,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(9,IO_STUS_X2,IO_STUS_Y2 ,DOWN_COL);
		Flag_9up=0;
		Flag_9dw=1;
		}
	 }
  else
	 {
	  if(Flag_9up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(9, START_X+Num_W,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(9,IO_STUS_X2,IO_STUS_Y2 ,UP_COL);
		Flag_9up=1;
		Flag_9dw=0;
		}
	 }
	
if(M_ZIN_PIN==0) //M_Zin
	{
	  if(Flag_Mdw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(16, START_X+Num_W*2,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(16,IO_STUS_X3,IO_STUS_Y2 ,DOWN_COL);
		Flag_Mup=0;
		Flag_Mdw=1;
		}
	 }
  else
	 {
	  if(Flag_Mup==0)
		{
		if(WorkStart_flag==0)
		InPutDis(16, START_X+Num_W*2,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(16,IO_STUS_X3,IO_STUS_Y2 ,UP_COL);
		Flag_Mup=1;
		Flag_Mdw=0;
		}
	 } 
	
		
  if(OIN11_PIN==0) //
	{
	  if(Flag_11dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(11, START_X+Num_W*3,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(11,IO_STUS_X4,IO_STUS_Y2 ,DOWN_COL);
		Flag_11up=0;
		Flag_11dw=1;
		}
	 }
  else
	 {
	  if(Flag_11up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(11, START_X+Num_W*3,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(11,IO_STUS_X4,IO_STUS_Y2 ,UP_COL);
		Flag_11up=1;
		Flag_11dw=0;
		}
	 }
		
		
  if(OIN12_PIN==0) //
	{
	  if(Flag_12dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(12, START_X+Num_W*4,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(12,IO_STUS_X5,IO_STUS_Y2 ,DOWN_COL);
		Flag_12up=0;
		Flag_12dw=1;
		}
	 }
  else
	 {
	  if(Flag_12up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(12, START_X+Num_W*4,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(12,IO_STUS_X5,IO_STUS_Y2 ,UP_COL);
		Flag_12up=1;
		Flag_12dw=0;
		}
	 }
		
		
  if(OIN13_PIN==0) //
	{
	  if(Flag_13dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(13, START_X+Num_W*5,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(13,IO_STUS_X6,IO_STUS_Y2 ,DOWN_COL);
		Flag_13up=0;
		Flag_13dw=1;
		}
	 }
  else
	 {
	  if(Flag_13up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(13, START_X+Num_W*5,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(13,IO_STUS_X6,IO_STUS_Y2 ,UP_COL);
		Flag_13up=1;
		Flag_13dw=0;
		}
	 }
		
		
  if(OIN14_PIN==0) //
	{
	  if(Flag_14dw==0)
		{
		if(WorkStart_flag==0)
		InPutDis(14, START_X+Num_W*6,START_Y+Num_H,DOWN_COL);
		else
			IO_Stus_Dis(14,IO_STUS_X7,IO_STUS_Y2 ,DOWN_COL);
		Flag_14up=0;
		Flag_14dw=1;
		}
	 }
  else
	 {
	  if(Flag_14up==0)
		{
		if(WorkStart_flag==0)
		InPutDis(14, START_X+Num_W*6,START_Y+Num_H,UP_COL);
		else
			IO_Stus_Dis(14,IO_STUS_X7,IO_STUS_Y2 ,UP_COL);
		Flag_14up=1;
		Flag_14dw=0;
		}
	 }
	
		
/*		
  if(OIN15_PIN==0) //
	{
	  if(Flag_15dw==0)
		{
		InPutDis(15, START_X+Num_W*7,START_Y+Num_H,DOWN_COL);
		Flag_15up=0;
		Flag_15dw=1;
		}
	 }
  else
	 {
	  if(Flag_15up==0)
		{
		InPutDis(15, START_X+Num_W*7,START_Y+Num_H,UP_COL);
		Flag_15up=1;
		Flag_15dw=0;
		}
	 }
*/
}
