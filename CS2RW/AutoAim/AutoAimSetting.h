#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../KeyBoard/VK_Value.h"

#define 头部 0x01
#define 脖子 0x02
#define 胸脯 0x03
#define 裆部 0x04
#define 腿部 0x05
#define 脚部 0x06

namespace AutoAim{

    enum class AllBodyPart :unsigned int{ 
        HEAD = 头部, NECK = 脖子, CHEST = 胸脯, CROTCH = 裆部, LEGS = 腿部, FEET = 脚部 
    };

    struct AutoAim
    {
        int HotKey;
        int Range;
        AllBodyPart BodyPart;
        float RotationAngle;
        AutoAim() {
            this->HotKey = 鼠标右键;
            this->Range = 30;
            this->BodyPart = AllBodyPart::HEAD;
            this->RotationAngle = 363.65;
        }
    };

    AutoAim AutoAimSetting;

    std::string GetBracketedString(const std::string& line) {
        std::string str1 = "";
        std::regex bracketRegex("\\[.*?\\]");
        if (std::regex_search(line, bracketRegex)) {
            size_t index1 = line.find('[');
            size_t index2 = line.find(']');
            str1 = line.substr(index1 + 1, index2 - 1);
        };
        return str1;
    };

    std::string removeSpaces(const std::string& str) {
        std::string result;
        for (size_t i = 0; i < str.length(); ) {
            if (str[i] != ' ') {
                result += str[i];
                i++;
            }
            else {
                i++;
            }
        }
        return result;
    }
    void GetUserInI(AutoAim &AutoAimSetting) {

        std::ifstream inputFile("Setting.ini");

        if (!inputFile.is_open()) {
            return;
        }

        std::string line; BOOL 是否配置节点头 = 0; std::string 等号左边; std::string 等号右边; size_t equals_pos; std::string 键 = ""; std::string 值 = "";

        while (std::getline(inputFile, line)) {

            if (GetBracketedString(line) == "配置") { 是否配置节点头 = TRUE; continue; }
            else if (GetBracketedString(line) == "END") { 是否配置节点头 = FALSE; };

            if (!是否配置节点头) { continue; };

            equals_pos = line.find('=');

            if (equals_pos != std::string::npos) {

                等号左边 = line.substr(0, equals_pos);
                等号右边 = line.substr(equals_pos + 1, line.length());
                键 = removeSpaces(等号左边);
                值 = removeSpaces(等号右边);
            }
            else { 键 = ""; 值 = ""; continue; };

            if (键 == "" || 值 == "") { continue; };

            if (键 == "自瞄键") {
                if (值 == "无自瞄热键") { AutoAimSetting.HotKey = 无自瞄热键; }
                else if (值 == "鼠标左键") { AutoAimSetting.HotKey = 鼠标左键; }
                else if (值 == "鼠标右键") { AutoAimSetting.HotKey = 鼠标右键; }
                else if (值 == "X1鼠标按钮") { AutoAimSetting.HotKey = X1鼠标按钮; }
                else if (值 == "X2鼠标按钮") { AutoAimSetting.HotKey = X2鼠标按钮; }
                else if (值 == "BACKSPACE键") { AutoAimSetting.HotKey = BACKSPACE键; }
                else if (值 == "Tab键") { AutoAimSetting.HotKey = Tab键; }
                else if (值 == "SHIFT键") { AutoAimSetting.HotKey = SHIFT键; }
                else if (值 == "CTRL键") { AutoAimSetting.HotKey = CTRL键; }
                else if (值 == "Alt键") { AutoAimSetting.HotKey = Alt键; }
                else if (值 == "CAPSLOCK键") { AutoAimSetting.HotKey = CAPSLOCK键; }
                else if (值 == "Q键") { AutoAimSetting.HotKey = Q键; }
                else if (值 == "E键") { AutoAimSetting.HotKey = E键; }
                else if (值 == "F键") { AutoAimSetting.HotKey = F键; }
                else if (值 == "空格键") { AutoAimSetting.HotKey = 空格键; }
                else { AutoAimSetting.HotKey = 鼠标右键; };
            };

            if (键 == "自瞄部位") {
                if (值 == "无自瞄部位") { AutoAimSetting.BodyPart = AllBodyPart::CHEST; }
                else if (值 == "头部") { AutoAimSetting.BodyPart = AllBodyPart::HEAD; }
                else if (值 == "脖子") { AutoAimSetting.BodyPart = AllBodyPart::NECK; }
                else if (值 == "胸脯") { AutoAimSetting.BodyPart = AllBodyPart::CHEST; }
                else if (值 == "裆部") { AutoAimSetting.BodyPart = AllBodyPart::CROTCH; }
                else if (值 == "腿部") { AutoAimSetting.BodyPart = AllBodyPart::LEGS; }
                else if (值 == "脚部") { AutoAimSetting.BodyPart = AllBodyPart::FEET; }
                else { AutoAimSetting.BodyPart = AllBodyPart::CHEST; };
            };

            if (键 == "微自瞄范围") {
                float 微自瞄范围;
                try {
                    微自瞄范围 = std::stof(值);
                    AutoAimSetting.Range = 微自瞄范围;
                }
                catch (const std::invalid_argument& e) {
                    MessageBoxA(0, "自瞄范围数字不符合规范", "自瞄配置", 0);
                    AutoAimSetting.Range = 10;
                }
                catch (const std::out_of_range& e) {
                    MessageBoxA(0, "自瞄范围数字超出限制", "自瞄配置", 0);
                    AutoAimSetting.Range = 10;
                }
            }

            if (键 == "假陀螺转速") {
                float 假陀螺转速;
                try {
                    假陀螺转速 = std::stof(值);
                    AutoAimSetting.RotationAngle = 假陀螺转速;
                }
                catch (const std::invalid_argument& e) {
                    MessageBoxA(0, "假陀螺转速数字不符合规范", "自瞄配置", 0);
                    AutoAimSetting.RotationAngle = 45;
                }
                catch (const std::out_of_range& e) {
                    MessageBoxA(0, "假陀螺转速数字超出限制", "自瞄配置", 0);
                    AutoAimSetting.RotationAngle = 45;
                }
            }
        };

        inputFile.close();

        return;
    };
}
