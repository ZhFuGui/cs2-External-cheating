#pragma once
//汇编定义
#define NOP 0X90
#define XOR 0X32
#define AL_AL 0xC0
//随机字符串样式
#define RSS_DEFAULT 0
#define RSS_MIXSYNBOLS 2
#define RSS_CHINESE 4
//固定偏移值
#define Sensitivity_Mouse_Second_Offset 0x40
#define HP_Offset 0xA74
#define STATE_LIFE_Offset 0XB18
#define CAMP_Offset 0X3C3
#define X_FOOT_Offset 0XD58
#define Y_FOOT_Offset 0XD5C
#define Z_FOOT_Offset 0XD60
#define RatioOfC2CT_Second_Offset 0xD78
#define ANGLE_Vertical_Offset 0X119C
#define ANGLE_Horizontal_Offset 0X11A0
#define X_HEAD_Offset 0X12D4
#define Y_HEAD_Offset 0X12D8
#define Z_HEAD_Offset 0X12DC
#define ANGLE_COS_Horizontal_Offset 0X12E0
#define ANGLE_SIN_Horizontal_Offset 0X12E4
#define ANGLE_SIN_Vertical_Offset 0X12E8

#define ANGLE_Vertical_Offset 0X119C
#define ANGLE_Horizontal_Offset 0X11A0

#define X_Speed_Offset 0X1428
#define Y_Speed_Offset 0X142C
#define Z_Speed_Offset 0X1430
#define BulletsLeft_Offset 0X1CF8



//变化偏移值
#define 更新中 FALSE
#define IfGmaeView 0x01E6F88
#define Xray_Offset	0x806EE2//9.110x807052 //2024.9.4 0x806F92 170
#define RatioOfC2CT_First_Offset 0X01597518
#define GameModel_Offset 0x17727B8//0x17747B8 //2024.9.4 0x17847B8    2000
#define NEW_LIST_PLAYER_Offset	0x017CEAE8//0X017D0AE8//0x017E0AE8	//0x017E1B08 2000
#define Sensitivity_Mouse_Frist_Offset 0x019B2B38//0x019B5038  //2024.9.4  0x019C6AC8	2500
#define PLAYER_MainVeiw_Offset	0x017C17F0
#define LIST_PLAYER_Offset 0X017D0B00  //0x017E1B00  
//自定义值
#define MaxNum_PeopleOnline 20
#define 开启报点 1
#define 关闭报点 0
#define	LENGTH_GameStatusInfo 50
//游戏信息定义：游戏模式
#define	UNKNOWN 404
#define	Competitive 1
#define Wingman 2
#define Casual 3
#define Deathmatch 4
#define ArmsRace 5
//地图
#define DustII 1
#define Mirage 2
#define Vertigo 3
#define Ancient 4
#define Inferno 5
#define Nuke 6
#define Anubis 7
#define Overpass 8
#define Thera 9
#define Mills 10
#define Office 11
#define Italy 12
#define Assembly 13
#define Memento 14
#define Baggage 15
#define Shoots 16
#define PoolDay 17
//自瞄模式
//对象
#define AimAtTheEnemy 1
#define AimAtTheAll 2
#define AimAtTheAlly 3
#define 假装陀螺 4
//方式
#define AimByDistance 4
#define AimByAngle 5
#define AimByHP 6





