#ifndef __VIETNAM_FONT_H
#define __VIETNAM_FONT_H

#define VIETNAM_FUN_EN     1   //越南语 功能 开关


extern unsigned char const Viet_Font24_Pic_1[];  // 1电脑检测完成,请按运行键!>点此处
extern unsigned char const Viet_Font24_Pic_2[];  // 2：程序     ???????
extern unsigned char const Viet_Font24_Pic_3[]; // 3：步骤
extern unsigned char const Viet_Font24_Pic_4[]; // 4：标称位置
extern unsigned char const Viet_Font24_Pic_5[]; // 5：手动模式
extern unsigned char const Viet_Font24_Pic_6[]; // 6：自动模式
extern unsigned char const Viet_Font24_Pic_7[]; // 7：自刀模式
extern unsigned char const Viet_Font24_Pic_8[]; // 8：示教模式
extern unsigned char const Viet_Font24_Pic_9[]; // 9：输入数据范围：
extern unsigned char const Viet_Font24_Pic_10[]; // 10：查找模式
extern unsigned char const Viet_Font24_Pic_11[]; // 11：序号
extern unsigned char const Viet_Font24_Pic_12[]; // 12：名称
extern unsigned char const Viet_Font24_Pic_13[]; // 13：修改日期
extern unsigned char const Viet_Font24_Pic_14[]; // 14：确认
extern unsigned char const Viet_Font24_Pic_15[]; // 15：取消
extern unsigned char const Viet_Font24_Pic_16_1[]; // 16：自刀模式高度危险，请按确认按键进入！
extern unsigned char const Viet_Font24_Pic_16_2[];
extern unsigned char const Viet_Font24_Pic_17[]; // 17：拼音输入
extern unsigned char const Viet_Font24_Pic_18[]; // 18：是否删除全部数据？
extern unsigned char const Viet_Font24_Pic_19[]; // 19：总长
extern unsigned char const Viet_Font24_Pic_20[]; // 20：标签
extern unsigned char const Viet_Font24_Pic_21[]; // 21：废边
extern unsigned char const Viet_Font24_Pic_22[]; // 22：标签模式
extern unsigned char const Viet_Font24_Pic_23[]; // 23：等分模式
extern unsigned char const Viet_Font24_Pic_24[]; // 24：等分值
extern unsigned char const Viet_Font24_Pic_25[]; // 25：等分数
extern unsigned char const Viet_Font24_Pic_26[]; // 26：推纸
extern unsigned char const Viet_Font24_Pic_27[]; // 27：理纸
extern unsigned char const Viet_Font24_Pic_28[]; // 28：压纸
extern unsigned char const Viet_Font24_Pic_29[]; // 29：单次自刀
extern unsigned char const Viet_Font24_Pic_30[]; // 30：批量自刀
extern unsigned char const Viet_Font24_Pic_31[]; // 31：自加模式
extern unsigned char const Viet_Font24_Pic_32[]; // 32：自减模式
extern unsigned char const Viet_Font24_Pic_33[]; // 33：标记设定
extern unsigned char const Viet_Font24_Pic_34[]; // 34：再按
extern unsigned char const Viet_Font24_Pic_35[]; // 35：退出
extern unsigned char const Viet_Font24_Pic_36[]; // 36：前极限
extern unsigned char const Viet_Font24_Pic_37[]; // 37：中极限
extern unsigned char const Viet_Font24_Pic_38[]; // 38：后极限
extern unsigned char const Viet_Font24_Pic_39[]; // 39：语言
extern unsigned char const Viet_Font24_Pic_40[]; // 40：单位
extern unsigned char const Viet_Font24_Pic_41[]; // 41：提前量
extern unsigned char const Viet_Font24_Pic_42[]; // 42：无
extern unsigned char const Viet_Font24_Pic_43[]; // 43：推纸距离
extern unsigned char const Viet_Font24_Pic_44[]; // 44：压纸停机
extern unsigned char const Viet_Font24_Pic_45[]; // 45：无效
extern unsigned char const Viet_Font24_Pic_46[]; // 46：关气距离
extern unsigned char const Viet_Font24_Pic_47[]; // 47：运行速度
extern unsigned char const Viet_Font24_Pic_48[]; // 48：光电选择
extern unsigned char const Viet_Font24_Pic_49[]; // 49：低有效
extern unsigned char const Viet_Font24_Pic_50[]; // 50：高有效
extern unsigned char const Viet_Font24_Pic_51[]; // 51：参数模式
extern unsigned char const Viet_Font24_Pic_52[]; // 52：基准模式
extern unsigned char const Viet_Font24_Pic_53[]; // 53：请输入6位密码 687610
extern unsigned char const Viet_Font24_Pic_54[]; // 54：请输入密码
extern unsigned char const Viet_Font24_Pic_55[]; // 55：年
extern unsigned char const Viet_Font24_Pic_56[]; // 56：月
extern unsigned char const Viet_Font24_Pic_57[]; // 57：日
extern unsigned char const Viet_Font24_Pic_58[]; // 58：小时
extern unsigned char const Viet_Font24_Pic_59[]; // 59：分钟
extern unsigned char const Viet_Font24_Pic_60[]; // 60：时间模式
extern unsigned char const Viet_Font24_Pic_61[]; // 61：脉冲当量模式
extern unsigned char const Viet_Font24_Pic_62[]; // 62：请输入脉冲当量
extern unsigned char const Viet_Font24_Pic_63_1[]; // 63：电脑自检，数据加载.，，，需要六秒，请稍等
extern unsigned char const Viet_Font24_Pic_63_2[]; // 63_2: 需要六秒，请稍等


void vietnam_print(unsigned char *pic,int x,int y,unsigned short fcolor,unsigned char bflag,unsigned int bkcolor);

#endif