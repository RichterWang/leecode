# 1401. 圆和矩形是否有重叠

## 题目描述

给你一个以 `(radius, xCenter, yCenter)` 表示的圆和一个与坐标轴平行的矩形 `(x1, y1, x2, y2)`，其中 `(x1, y1)` 是矩形左下角的坐标，而 `(x2, y2)` 是右上角的坐标。

如果圆和矩形有重叠的部分，请你返回 `true`，否则返回 `false`。

换句话说，请你检测是否**存在**点 `(xi, yi)`，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。

**示例 1：**

![示例1](https://assets.leetcode.com/uploads/2020/02/20/sample_4_1728.png)

```
输入：radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
输出：true
解释：圆和矩形存在公共点 (1, 0)。
```

**示例 2：**

```
输入：radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
输出：false
```

**示例 3：**

![示例3](https://assets.leetcode.com/uploads/2020/02/20/sample_2_1728.png)

```
输入：radius = 1, xCenter = 0, yCenter = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
输出：true
```

**提示：**
- `1 <= radius <= 2000`
- `-10^4 <= xCenter, yCenter <= 10^4`
- `-10^4 <= x1 < x2 <= 10^4`
- `-10^4 <= y1 < y2 <= 10^4`

## 解题思路

这道题的核心是**几何判断**，需要分情况讨论圆心相对于矩形的位置。

### 思路分析

圆和矩形有重叠，等价于：**圆心到矩形的最短距离 ≤ 半径**

关键是如何计算**圆心到矩形的最短距离**。

### 分情况讨论

根据圆心相对于矩形的位置，可以分为以下几种情况：

#### 1. 圆心在矩形的四个角的外侧区域（4种情况）

```
    左上区域  |  上方区域  |  右上区域
    --------- + ---------- + ---------
    左侧区域  |   矩形内   |  右侧区域
    --------- + ---------- + ---------
    左下区域  |  下方区域  |  右下区域
```

**四个角的外侧区域**：
- **左下角外侧**：`xCenter < x1 && yCenter < y1`
  - 最近点是矩形的左下角 `(x1, y1)`
  - 距离：`sqrt((xCenter - x1)^2 + (yCenter - y1)^2)`
  
- **左上角外侧**：`xCenter < x1 && yCenter > y2`
  - 最近点是矩形的左上角 `(x1, y2)`
  - 距离：`sqrt((xCenter - x1)^2 + (yCenter - y2)^2)`
  
- **右下角外侧**：`xCenter > x2 && yCenter < y1`
  - 最近点是矩形的右下角 `(x2, y1)`
  - 距离：`sqrt((xCenter - x2)^2 + (yCenter - y1)^2)`
  
- **右上角外侧**：`xCenter > x2 && yCenter > y2`
  - 最近点是矩形的右上角 `(x2, y2)`
  - 距离：`sqrt((xCenter - x2)^2 + (yCenter - y2)^2)`

判断：`距离 <= radius`，即 `距离^2 <= radius^2`

#### 2. 圆心在矩形的四条边的外侧区域（4种情况）

- **上方区域**：`y1 <= yCenter <= y2 && yCenter > y2`
  - 实际上这个条件矛盾，应该是 `y1 <= xCenter <= x2 && yCenter > y2`
  - 最短距离：`yCenter - y2`
  
- **下方区域**：`y1 <= xCenter <= x2 && yCenter < y1`
  - 最短距离：`y1 - yCenter`
  
- **左侧区域**：`y1 <= yCenter <= y2 && xCenter < x1`
  - 最短距离：`x1 - xCenter`
  
- **右侧区域**：`y1 <= yCenter <= y2 && xCenter > x2`
  - 最短距离：`xCenter - x2`

判断：`最短距离 <= radius`

#### 3. 圆心在矩形内部

如果圆心在矩形内部，则必然重叠，返回 `true`。

### 代码实现

```cpp
bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // 情况1：四个角的外侧区域
    if(xCenter < x1 && yCenter < y1) {
        // 左下角
        int distance = (xCenter - x1) * (xCenter - x1) + (yCenter - y1) * (yCenter - y1);
        return distance <= radius * radius;
    }
    else if(xCenter < x1 && yCenter > y2) {
        // 左上角
        int distance = (xCenter - x1) * (xCenter - x1) + (yCenter - y2) * (yCenter - y2);
        return distance <= radius * radius;
    }
    else if(xCenter > x2 && yCenter < y1) {
        // 右下角
        int distance = (xCenter - x2) * (xCenter - x2) + (yCenter - y1) * (yCenter - y1);
        return distance <= radius * radius;
    }
    else if(xCenter > x2 && yCenter > y2) {
        // 右上角
        int distance = (xCenter - x2) * (xCenter - x2) + (yCenter - y2) * (yCenter - y2);
        return distance <= radius * radius;
    }
    
    // 情况2：四条边的外侧区域
    else if(yCenter > y2) return yCenter - y2 <= radius;
    else if(yCenter < y1) return y1 - yCenter <= radius;
    else if(xCenter < x1) return x1 - xCenter <= radius;
    else if(xCenter > x2) return xCenter - x2 <= radius;
    
    // 情况3：圆心在矩形内部
    else return true;
}
```

### 复杂度分析

- **时间复杂度**：O(1)
  - 只需要常数次比较和计算

- **空间复杂度**：O(1)
  - 只使用常数个变量

## 优化思路

可以用更简洁的方式计算圆心到矩形的最短距离：

```cpp
bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // 找到矩形上距离圆心最近的点
    int closestX = max(x1, min(xCenter, x2));
    int closestY = max(y1, min(yCenter, y2));
    
    // 计算距离的平方
    int distanceSquared = (xCenter - closestX) * (xCenter - closestX) + 
                          (yCenter - closestY) * (yCenter - closestY);
    
    return distanceSquared <= radius * radius;
}
```

**原理**：
- `closestX = max(x1, min(xCenter, x2))` 将圆心的 x 坐标"钳制"到矩形的 x 范围内
- `closestY = max(y1, min(yCenter, y2))` 将圆心的 y 坐标"钳制"到矩形的 y 范围内
- `(closestX, closestY)` 就是矩形上距离圆心最近的点

这种方法更简洁，避免了繁琐的分类讨论。

## 关键点总结

1. **几何分析**：根据圆心相对矩形的位置，分情况计算最短距离
2. **避免浮点运算**：用 `距离^2 <= radius^2` 避免开方运算
3. **简洁写法**：用"钳制"思想找到矩形上最近的点

## 标签

- 几何
- 数学
- 分类讨论
