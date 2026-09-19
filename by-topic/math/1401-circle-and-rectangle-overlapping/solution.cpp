#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <array>

using namespace std;

/*
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        if(xCenter < x1 && yCenter < y1)
        {
            int distance = abs(xCenter - x1) * abs(xCenter - x1) + abs(yCenter - y1) * abs(yCenter - y1);
            if(distance <= radius * radius) return true;
            else return false;
        }
        else if(xCenter < x1 && yCenter > y2)
        {
            int distance = abs(xCenter - x1) * abs(xCenter - x1) + abs(yCenter - y2) * abs(yCenter - y2);
            if(distance <= radius * radius) return true;
            else return false;            
        }
        else if(xCenter > x2 && yCenter < y1)
        {
            int distance = abs(xCenter - x2) * abs(xCenter - x2) + abs(yCenter - y1) * abs(yCenter - y1);
            if(distance <= radius * radius) return true;
            else return false;                
        }
        else if(xCenter > x2 && yCenter > y2)
        {
            int distance = abs(xCenter - x2) * abs(xCenter - x2) + abs(yCenter - y2) * abs(yCenter - y2);
            if(distance <= radius * radius) return true;
            else return false;               
        }
        else if(yCenter > y2) return yCenter - y2 > radius ? false : true;
        else if(yCenter < y1) return y1 - yCenter > radius ? false : true;
        else if(xCenter < x1) return x1 - xCenter > radius ? false : true;
        else if(xCenter > x2) return xCenter - x2 > radius ? false : true;
        else return true;
    }

private:

};

/* 1401. 圆和矩形是否有重叠：
给你一个以 (radius, xCenter, yCenter) 表示的圆和一个与坐标轴平行的矩形 (x1, y1, x2, y2) ，
其中 (x1, y1) 是矩形左下角的坐标，而 (x2, y2) 是右上角的坐标。
如果圆和矩形有重叠的部分，请你返回 true ，否则返回 false 。
换句话说，请你检测是否 存在 点 (xi, yi) ，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。
*/
