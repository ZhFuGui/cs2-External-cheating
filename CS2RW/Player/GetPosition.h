//得到人物点位
#pragma once
#include <string>
#include <Windows.h>
#include "../Define/Definition.h"
std::string GetWhere(MAP map, float x, float y, float z) {
	switch (map)
	{
	case MAP::UNKNOW: {
		return "没有进入游戏";
	}

	case MAP::DustII: {
		if (x > -2204 && x < 440 && y > -1164 && y < -637) {
			return "匪家";
		}
		else if (x > -2204 && x < -980 && y > -637 && y < -180) {
			return "匪家看台";
		}
		else if (x > -2044 && x < -1272 && y > -180 && y < 680) {
			return "后花园";
		}
		else if (x > -2186 && x < -1167 && y > 680 && y < 1387) {
			return "B2";
		}
		else if (x > -2030 && x < -1942 && y > 1387 && y < 1814) {
			return "B洞口";
		}
		else if (x > -1708 && x < -1364 && y > 1620 && y < 1900) {
			return "B点车位";
		}
		else if (x > -2183 && x < -1364 && y > 1814 && y < 3118) {
			return "B点";
		}
		else if (x > -1364 && x < -1070 && y > 2558 && y < 2695) {
			return "脚手架";
		}
		else if (x > -1364 && x < -242 && y > 2000 && y < 2558) {
			return "沙地";
		}
		else if (x > -242 && x < 564 && y > 2009 && y < 2547 && z < 85) {
			return "警家";
		}
		else if (x > 564 && x < 1237 && y > 2038 && y < 2276 && z < 85) {
			return "警家斜坡";
		}
		else if (x > 564 && x < 860 && y > 2276 && y < 2380 && z < 90) {
			return "上A小箱子";
		}
		else if (x > 860 && x < 1005 && y > 2276 && y < 2380 && z < 90) {
			return "电梯";
		}
		else if (x > -242 && x < 564 && y > 2009 && y < 2444 && z > 95) {
			return "警家上方";
		}
		else if (x > 278 && x < 1300 && y > 2264 && y < 3060 && z>90) {
			return "A点平台";
		}
		else if (x > 1300 && x < 1610 && y > 2264 && y < 3060) {
			return "A点斜坡";
		}
		else if (x > 1602 && x < 1788 && y > 1650 && y < 2265) {
			return "蓝车";
		}
		else if (x > 1237 && x < 1602 && y > 1008 && y < 2264) {
			return "A大";
		}
		else if (x > 1572 && x < 1769 && y > 310 && y < 1008) {
			return "A大厕所";
		}
		else if (x > 1292 && x < 1572 && y > 201 && y < 728) {
			return "A大坑";
		}
		else if (x > 916 && x < 1572 && y > 728 && y < 1210) {
			return "A大内侧";
		}
		else if (x > 968 && x < 1292 && y > 215 && y < 728) {
			return "大坑站台";
		}
		else if (x > 516 && x < 916 && y > 788 && y < 1071) {
			return "警A门外";
		}
		else if (x > 516 && x < 686 && y > 1071 && y < 1189) {
			return "蓝箱";
		}
		else if (x > 539 && x < 742 && y > 470 && y < 788) {
			return "A门内（箱后）";
		}
		else if (x > 539 && x < 742 && y > 255 && y < 470) {
			return "A门内（门后）";
		}
		else if (x > 460 && x < 760 && y > 102 && y < 255) {
			return "匪A门外";
		}
		else if (x > 460 && x < 760 && y > -408 && y < 102) {
			return "黄车";
		}
		else if (x > 136 && x < 460 && y > -637 && y < 300) {
			return "匪家黄车附近的平台";
		}
		else if (x > -492 && x < -323 && y > -637 && y < 212) {
			return "暗道";
		}
		else if (x > -323 && x < 136 && y > -594 && y < -470) {
			return "暗道附近的过道";
		}
		else if (x > -726 && x < -494 && y >212 && y < 702) {
			return "80";
		}
		else if (x > -494 && x < -149 && y >212 && y < 702) {
			return "中远";
		}
		else if (x > -149 && x < 460 && y >300 && y < 458) {
			return "L点";
		}
		else if (x > -522 && x < -275 && y >702 && y < 1277) {
			return "中路";
		}
		else if (x > -388 && x < -275 && y >1277 && y < 1518) {
			return "X箱";
		}
		else if (x > -490 && x < -342 && y >1518 && y < 1583) {
			return "匪中门";
		}
		else if (x > -606 && x < -276 && y >1583 && y < 1744) {
			return "警中门近点（门后）";
		}
		else if (x > -606 && x < -276 && y >1744 && y < 2000) {
			return "警中门远点（凹槽）";
		}
		else if (x > -522 && x < -388 && y >1277 && y < 1518) {
			return "B1门口";
		}
		else if (x > -1200 && x < -522 && y >1334 && y < 1520) {
			return "B1";
		}
		else if (x > -1167 && x < -1048 && y >1042 && y < 1334) {
			return "B通楼梯";
		}
		else if (x > -275 && x < -148 && y >702 && y < 1582) {
			return "A小站台";
		}
		else if (x > -148 && x < 490 && y >1250 && y < 1582) {
			return "A小";
		}
		else if (x > 273 && x < 490 && y >1582 && y < 2009) {
			return "A小楼梯";
		}
		else {
			return "未知点位：dust2";
		}
	}
	case MAP::Mirage: {
		if (x > -2032 && x < -1711 && y > -2120 && y < -1620) {
			return "警家坦克凹槽";
		}
		else if (x > -2204 && x < -980 && y > -637 && y < -180) {
			return "匪家看台";
		}
		else {
			return "未知点位：Mirage";
		}
	};
	default: {
		return "地图未更新";
	};

	};

};