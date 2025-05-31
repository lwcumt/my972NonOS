#include "bmp.h"
#include "drv_glcd.h"


int Picwidth;
int Picheight;

struct BMP_HEADER
{
	unsigned int  iFile_Type;		// 0~1byte
	unsigned long lFile_Size;		// 2
	//rsv 2bytes						// 6
	//rsv 2bytes						// 8
	unsigned long lBmp_Data_Offset;	//offset=10
};

struct BMP_INFO
{
	unsigned long lInfo_Size;		// 14
	unsigned long lBmp_Width;		// 18
	unsigned long lBmp_Height;		// 22
	//2bytes							//26
	unsigned int  iBit_Count;		// 28
	//2bytes							// 30
	unsigned long lImage_Size;		// 32
	unsigned long lXPels_Per_Meter;	// 36
	unsigned long lYPels_Per_Meter;	// 40
	//4bytes
};

struct BMP_HEADER 	bmp_header;
struct BMP_INFO		bmp_info;





void Get_Bmp_Info(Int32U Bmp_add)
{
    pInt8U p =(pInt8U)Bmp_add;
	bmp_header.lBmp_Data_Offset		= *(p+13)<<24;
	bmp_header.lBmp_Data_Offset	   |= *(p+12)<<16;
	bmp_header.lBmp_Data_Offset	   |= *(p+11)<<8;
	bmp_header.lBmp_Data_Offset	   |= *(p+10);
	
	bmp_info.lBmp_Width				= *(p+21)<<24;
	bmp_info.lBmp_Width			   |= *(p+20)<<16;
	bmp_info.lBmp_Width			   |= *(p+19)<<8;
	bmp_info.lBmp_Width			   |= *(p+18);
	
	bmp_info.lBmp_Height			= *(p+25)<<24;
	bmp_info.lBmp_Height		   |= *(p+24)<<16;
	bmp_info.lBmp_Height		   |= *(p+23)<<8;
	bmp_info.lBmp_Height		   |= *(p+22);
	
	bmp_info.iBit_Count				= *(p+28);
	
	Picwidth=bmp_info.lBmp_Width;//图片尺寸保存
	Picheight=bmp_info.lBmp_Height;//
}

void Bmp_Decode(Int32U Bmp_add,Int16U StartX,Int16U StartY,pInt16U PicBase_RAM)
{
    Int8U color_byte;
	Int8U rgb = 0;
 //   Int8U count = 0;
    Int8U m = 0;
    Int16U byte1 = 0;
    Int8U byte2 = 0;
    Int8U byte3 = 0;
	Int16U color = 0;
    Int16U x = 0;
    Int16U y = 0;
	Int16U temp_col = 0;
	
	pInt16U pic_F;
	
	Get_Bmp_Info(Bmp_add);
	if(bmp_header.lBmp_Data_Offset>200) return;
	if(bmp_info.lBmp_Width>800) return;
	if(bmp_info.lBmp_Height>480) return;	
	pic_F=PicBase_RAM+((bmp_info.lBmp_Height - 1 + StartY)*C_GLCD_H_SIZE + StartX);//第PicBase_RAM显示缓冲区
	
	pInt8U cbmp =(pInt8U)(Bmp_add+bmp_header.lBmp_Data_Offset);

	if(bmp_info.lBmp_Width>4)
       {
	    color_byte = bmp_info.iBit_Count>>3;
        m=(bmp_info.lBmp_Width*color_byte)%4;
        if(m>0)
        m=4-m;//宽度与4求余后的补数
       }
	if(color_byte>4) return;
	while(1)
	   {	
		if(color_byte == 3)//24位颜色图
		  {   
				/*
		  switch ( rgb ) 
		     {
			 case 0 : //b

			    color= *cbmp++ ;
                color>>=3;  
				//color&=0x1f;
    			//color |= (temp_col&0x001f) ;
			 		  rgb ++ ;
			       break ;			
			case 1 : //g
			    temp_col = *cbmp++ ;
                temp_col <<= 3 ;  
			    color |= (temp_col&0x07e0) ;
					  rgb ++ ;
			       break ;
			case 2 : //r
			    temp_col = *cbmp++ ;
			    temp_col <<= 8 ;   
			    color |= (temp_col&0xf800);
					  rgb ++ ;
			       break ;
		     }
				 */
				 
			 color= *cbmp++ ;
       color>>=3;  

			 temp_col = *cbmp++ ;
       temp_col <<= 3 ;  
			 color |= (temp_col&0x07e0) ;

			 temp_col = *cbmp++ ;
			 temp_col <<= 8 ;   
			 color |= (temp_col&0xf800);
			
				 
			*pic_F++=color;
	        rgb=color = 0 ;
		    x++ ;
		    if(x >= bmp_info.lBmp_Width)
		       {
		        x = 0 ;
				cbmp += m;
		        y++ ;
			    if(y>=bmp_info.lBmp_Height)
			           break;
				   
		        pic_F=PicBase_RAM+((bmp_info.lBmp_Height - 1- y + StartY)*C_GLCD_H_SIZE + StartX);//第PicBase_RAM显示缓冲区
			   }				 
		  }
		else
		  {
			if(color_byte==2)//16位颜色图
			  { 
/*					
			    switch ( rgb )
			        {
				    case 0 : 
					    temp_col = *cbmp++ ;
				         break ; 
				    case 1 :    //高8位
				        color = *cbmp++ ;
				        color<<=8 ;
				        color |= temp_col ;
				        break ;
			        }
			    rgb++ ;
							*/
					
				temp_col = *cbmp++ ;
				color = *cbmp++ ;
				color<<=8 ;
				color |= temp_col ;			
					
				*pic_F++=color;
	      rgb=color = 0 ;
		    x++ ;
		    if(x >= bmp_info.lBmp_Width)
		       {
		        x = 0 ;
				cbmp += m;
		        y++ ;
			    if(y>=bmp_info.lBmp_Height)
			           break;
				   
		        pic_F=PicBase_RAM+((bmp_info.lBmp_Height - 1- y + StartY)*C_GLCD_H_SIZE + StartX);//第PicBase_RAM显示缓冲区
					}								
			  }
			else
			  {
				if(color_byte==4) //32位颜色图
				   {
						 /*
					switch ( rgb )
				        {
						case 0 :  
						    byte1 = *cbmp++ ;	
							break ; 
						case 1 :  
						    byte2 = *cbmp++ ;
							break ;
						case 2 :  
						    byte3 = *cbmp++ ;
							break ;
						case 3 : 
                            cbmp++;
						    temp_col = byte1 >> 3 ;
					        color |= temp_col;
						    temp_col = byte2 >>2 ;
					        temp_col <<= 5 ;
					        color |= temp_col ;
							temp_col = byte3 >>3 ;
					        temp_col <<= 11 ;
					        color |= temp_col ;
							break ;
					    }
				    rgb ++ ;
							*/
							
							
						    byte1 = *cbmp++ ;	

						    byte2 = *cbmp++ ;

						    byte3 = *cbmp++ ;

                cbmp++;
						    temp_col = byte1 >> 3 ;
					        color |= temp_col;
						    temp_col = byte2 >>2 ;
					        temp_col <<= 5 ;
					        color |= temp_col ;
							temp_col = byte3 >>3 ;
					        temp_col <<= 11 ;
					        color |= temp_col ;							
							
					*pic_F++=color;
					rgb=color = 0 ;
					x++ ;
					if(x >= bmp_info.lBmp_Width)
						{
							x = 0 ;
						cbmp += m;
							y++ ;
						if(y>=bmp_info.lBmp_Height)
									break;
				   
							pic_F=PicBase_RAM+((bmp_info.lBmp_Height - 1- y + StartY)*C_GLCD_H_SIZE + StartX);//第PicBase_RAM显示缓冲区
						}								
				   }
			  }   
		  }
			
			/*

	    if(rgb == color_byte)
		  {        //读取1像素数数据后显示
	       // rgb = 0 ;			
			*pic_F++=color;
	        rgb=color = 0 ;
		    x++ ;
		    if(x >= bmp_info.lBmp_Width)
		       {
		        x = 0 ;
				cbmp += m;
		        y++ ;
			    if(y>=bmp_info.lBmp_Height)
			           break;
				   
		        pic_F=PicBase_RAM+((bmp_info.lBmp_Height - 1- y + StartY)*C_GLCD_H_SIZE + StartX);//第PicBase_RAM显示缓冲区
			   }
		  }
			*/
	   }
}
