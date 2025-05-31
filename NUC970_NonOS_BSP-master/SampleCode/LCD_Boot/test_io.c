
#include "test_io.h"
//#include"key.h"
#include"chndot.h"

#include"word_lib.h"

#include "port.h"
#include"servo.h"


Int8U Borard1_2=0;//Ñ¡ÔñÓ²¼þ°æ±¾

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


void InPutDis(Int8U num,Int16U Xp,Int16U Yp,Int16U Colar)   //ÊäÈë¶Ë¿Ú  ²âÊÔ
{
Int8U Num[2];

GLCD_SetWindow_Fill(Xp-5,Yp-5,Xp+90,Yp+40,Colar,Colar);

switch(num)
    {
	case 0:
	//ASCII_Printf("IN0",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 1:
		Printf24("Ô­µã",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 2:
		Printf24("ÇÐµ¶",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 3:
		Printf24("Ñ¹Ö½",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 4:
		Printf24("ÍÐ°å",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 5:
		Printf24("ºìÍâ",Xp,Yp,BLACK_COLOR,0,0xffff);
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
		Printf24("Ç°¼«ÏÞ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 12:
		Printf24("ÖÐ¼«ÏÞ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 13:
		Printf24("ºó¼«ÏÞ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 14:
		Printf24("ÊÖÂÖ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 15:
	//ASCII_Printf("IN15",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0);
	       break;
	case 16:
		Printf24("mZ_AC",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	}
    

}   



void KeyDis(Int8U num,Int16U Xp,Int16U Yp,Int8U Keydown)   //²âÊÔ¼üÅÌÊäÈë
{
Int8U Num[2];
Int16U Colar;
if(Keydown==1)
   Colar=GREEN_COLOR;
else 
   Colar=0xf07f;  
GLCD_SetWindow_Fill(Xp-5,Yp-5,Xp+80,Yp+40,Colar,Colar);

switch(num)
    {
	case 1:
		Printf24("F1",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 2:
		Printf24("F2",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 3:
		Printf24("F3",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 4:
		Printf24("F4",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	case 5:
		Printf24("±à³Ì",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 6:
		Printf24("×Ô¶¯",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 7:
		Printf24("ÊÖ¶¯",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 8:
		Printf24("F",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //ÏÔÊ¾¿ª»ú»­Ãæ
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
			RLOUT1_OFF;    // ÔÊÐí²ÃÇÐ
			}
	       break;
	case 9:
		Printf24("1",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 10:
		Printf24("4",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 11:
		Printf24("7",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 12:
		Printf24("C",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 13:
		Printf24("2",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 14:
		Printf24("5",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 15:
		Printf24("8",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 16:
		Printf24("0",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 17:
		Printf24("3",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 18:
		Printf24("6",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 19:
		Printf24("9",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 20:
		Printf24(".",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 21:
		Printf24("+",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 22:
		Printf24("-",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 23:
		Printf24("ºóÍË",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=3;    //ÖÐËÙ 
			SetMotorSpeed(MoveSpeed);
			MoveBack();
			}
	       break;
	case 24:
		Printf24("Ç°½ø",Xp,Yp,BLACK_COLOR,0,0xffff);
		if(Keydown==1)
			{
			MoveSpeed=3;    //ÖÐËÙ 
			SetMotorSpeed(MoveSpeed);
			MoveForward();
			}
	       break;
	case 25:
		Printf24("ÏòÉÏ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 26:
		Printf24("ÏòÏÂ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 27:
		Printf24("È·¶¨",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 28:
		Printf24("ÔËÐÐ",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 29:
		Printf24("²åÈë",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;
	case 30:
		Printf24("É¾³ý",Xp,Yp,BLACK_COLOR,0,0xffff);
	       break;	   
	}
  
}   

void KeyDis_sel(Int32U Keycode,Int8U Keydown)//°´¼ü×´Ì¬ÏÔÊ¾
{
switch(Keycode)
    {
	case AUTO_KEY_CODE:	//ÁãºÅ¼ü
	     KeyDis(1,COL_0,ROW_1,Keydown);
		 
		            break;
	case READ_KEY_CODE:	//ºÅ¼ü
	     KeyDis(2,COL_0,ROW_2,Keydown);
		 
		            break;
	case RETURN_KEY_CODE:	//ºÅ¼ü
	     KeyDis(3,COL_0,ROW_3,Keydown);
		 
		            break;
	case MANUAL_KEY_CODE:	//ºÅ¼ü
	     KeyDis(4,COL_0,ROW_4,Keydown);
		 
		            break;
					
	case FOUR_KEY_CODE:	//ÁãºÅ¼ü
	     KeyDis(5,COL_1,ROW_1,Keydown);
		// OOUT1_ANTI;
		            break;
	case THREE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(6,COL_1,ROW_2,Keydown);
		//  OOUT2_ANTI;
		            break;
	case TWO_KEY_CODE:	//ºÅ¼ü
	     KeyDis(7,COL_1,ROW_3,Keydown);
		// OOUT3_ANTI;
		            break;
	case ONE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(8,COL_1,ROW_4,Keydown); 
	//	 OOUT4_ANTI;
		            break;
					
	case NINE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(9,COL_2,ROW_1,Keydown);//RLOUT1_ANTI;
		            break;
	case EIGHT_KEY_CODE:	//ºÅ¼ü
	     KeyDis(10,COL_2,ROW_2,Keydown);//RLOUT2_ANTI;
		            break;
	case SEVEN_KEY_CODE:	//ºÅ¼ü
	     KeyDis(11,COL_2,ROW_3,Keydown);//RLOUT3_ANTI;
		            break;
	case SIX_KEY_CODE:	//ºÅ¼ü
	     KeyDis(12,COL_2,ROW_4,Keydown);//RLOUT4_ANTI;
		            break;
					
	case MOVE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(13,COL_3,ROW_1,Keydown);
		            break;
	case NO_KEY_CODE:	//ºÅ¼ü
	     KeyDis(14,COL_3,ROW_2,Keydown);
		            break;
	case YES_KEY_CODE:	//ºÅ¼ü
	     KeyDis(15,COL_3,ROW_3,Keydown);
		            break;
	case PROG_KEY_CODE:	//ºÅ¼ü
	     KeyDis(16,COL_3,ROW_4,Keydown);
		            break;
					
	case DELETE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(17,COL_4,ROW_1,Keydown);
		            break;
	case INSERT_KEY_CODE:	//ºÅ¼ü
	     KeyDis(18,COL_4,ROW_2,Keydown);
		            break;
	case SUB_KEY_CODE:	//ºÅ¼ü
	     KeyDis(19,COL_4,ROW_3,Keydown);
		            break;
	case ADD_KEY_CODE:	//ºÅ¼ü
	     KeyDis(20,COL_4,ROW_4,Keydown);
		            break;
					
	case REV_KEY_CODE:	//ºÅ¼ü
	     KeyDis(21,COL_5,ROW_1,Keydown);
		            break;
	case OPTION_KEY_CODE:	//ºÅ¼ü
	     KeyDis(22,COL_5,ROW_2,Keydown);
		            break;
	case ADJUST_KEY_CODE:	//ºÅ¼ü
	     KeyDis(23,COL_5,ROW_3,Keydown);
		            break;
	case NEXTKNIFE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(24,COL_5,ROW_4,Keydown);
		            break;
					
	case DENGJU_KEY_CODE:	//ºÅ¼ü
	     KeyDis(25,COL_6,ROW_1,Keydown);
		            break;
	case DENGFENG_KEY_CODE:	//ºÅ¼ü
	     KeyDis(26,COL_6,ROW_2,Keydown);
		            break;
					
	case DOWN_KEY_CODE:	//ºÅ¼ü
	     KeyDis(27,COL_7,ROW_3,Keydown);
		            break;
	case UP_KEY_CODE:	//ºÅ¼ü
	     KeyDis(28,COL_7,ROW_4,Keydown);
		            break;
					
	case ZERO_KEY_CODE:	//ºÅ¼ü
	     KeyDis(29,COL_8,ROW_1,Keydown);
		            break;
	case FIVE_KEY_CODE:	//ºÅ¼ü
	     KeyDis(30,COL_8,ROW_2,Keydown);
		            break;
	
	}

}


void KeyDis_Init(void)//°´¼üÏÔÊ¾³õÊ¼»¯
{
KeyDis_sel(AUTO_KEY_CODE,0);
 KeyDis_sel(READ_KEY_CODE,0);
 KeyDis_sel(RETURN_KEY_CODE,0);
 KeyDis_sel(MANUAL_KEY_CODE,0);
 
 KeyDis_sel(ONE_KEY_CODE,0);
 KeyDis_sel(TWO_KEY_CODE,0);
 KeyDis_sel(THREE_KEY_CODE,0);
 KeyDis_sel(FOUR_KEY_CODE,0);
 KeyDis_sel(FIVE_KEY_CODE,0);
 
 KeyDis_sel(SIX_KEY_CODE,0);
 KeyDis_sel(SEVEN_KEY_CODE,0);
 KeyDis_sel(EIGHT_KEY_CODE,0);
 KeyDis_sel(NINE_KEY_CODE,0);
 
 KeyDis_sel(MOVE_KEY_CODE,0);
 KeyDis_sel(YES_KEY_CODE,0);
 KeyDis_sel(NO_KEY_CODE,0);
 KeyDis_sel(PROG_KEY_CODE,0);
 
 KeyDis_sel(DELETE_KEY_CODE,0);
 KeyDis_sel(INSERT_KEY_CODE,0);
 KeyDis_sel(SUB_KEY_CODE,0);
 KeyDis_sel(ADD_KEY_CODE,0);
 
 KeyDis_sel(REV_KEY_CODE,0);
 KeyDis_sel(OPTION_KEY_CODE,0);
 KeyDis_sel(ADJUST_KEY_CODE,0);
 KeyDis_sel(NEXTKNIFE_KEY_CODE,0);
 
KeyDis_sel(DENGFENG_KEY_CODE,0);
 KeyDis_sel(DENGJU_KEY_CODE,0);
 KeyDis_sel(ZERO_KEY_CODE,0);
 KeyDis_sel(UP_KEY_CODE,0);
 KeyDis_sel(DOWN_KEY_CODE,0);
}


void IO_InputDisInit(void)  //Io ÊäÈë¿Ú³õÊ¼Öµ
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

void IOinputTest1_2(void)//IO  ÊäÈë²âÊÔ********1.2
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


void IOinputTest1_3(void)//IO  ÊäÈë²âÊÔ********1.3
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
void IOinputTest(void)//IO  ÊäÈë²âÊÔ********all
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
	
if(M_ZIN_PIN==0) //M_Zin
	{
	  if(Flag_Mdw==0)
		{
		InPutDis(16, START_X+Num_W*2,START_Y+Num_H,DOWN_COL);
		Flag_Mup=0;
		Flag_Mdw=1;
		}
	 }
  else
	 {
	  if(Flag_Mup==0)
		{
		InPutDis(16, START_X+Num_W*2,START_Y+Num_H,UP_COL);
		Flag_Mup=1;
		Flag_Mdw=0;
		}
	 } 
	
	/*	
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
