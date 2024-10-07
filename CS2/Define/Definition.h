#pragma once
//全局黄金常量
#define g_initV (float)5.0316
//汇编定义
#define NOP 0X90
#define XOR 0X32
#define AL_AL 0xC0
//随机字符串样式
#define RSS_DEFAULT 0
#define RSS_MIXSYNBOLS 2
#define RSS_CHINESE 4 
//自定义值
#define MaxNum_PeopleOnline 20
#define 开启报点 1
#define 关闭报点 0
#define	LENGTH_GameStatusInfo 50
#define	WM_VERSION_UNUSEFUL 0x888
//游戏信息定义：游戏模式
#define	UNKNOWN 404
#define	Competitive 1
#define Wingman 2
#define Casual 3
#define Deathmatch 4
#define ArmsRace 5
//地图
enum class MAP {
	UNKNOW,
	DustII,
	Mirage,
	Vertigo,
	Ancient, 
	Inferno,
	Nuke,
	Anubis,
	Overpass,
	Thera,
	Mills,
	Office,
	Italy,
	Assembly,
	Memento,
	Baggage,
	Shoots, 
	PoolDay
};
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