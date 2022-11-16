# 层板等分衣柜问题

Shelves are divided into equal wardrobes -> SDQW

## 写在前面的话

本项目主要参考了[leetcode中对于本题目的思路](https://leetcode.cn/circle/discuss/J1Kq0j/)与[CSDN中对于本题目的思路](https://blog.csdn.net/weixin_46089456/article/details/126557327)。非常感谢`LeetCode`用户[zhaokk](https://leetcode.cn/u/zhaokk/)与`CSDN`用户[学习份子](https://blog.csdn.net/weixin_46089456)。

调试环境如下：

键|值|版本
-|-|-
系统|`Ubuntu`|$20.04$
编译器|`g++`|$9.4.0$

## 题目描述

给定一个高度为 $2000mm$ 的柜子空间，以及 $n$ 个层板距离柜子底部高度，满足移动层板位置，使得层板等分衣柜的空间。**计算所有移动层板的顺序**。

层板号自下向上依次排列，$1, 2{\ldots}n$。层板需要考虑空间位置，**不能跨层板移动**。

![problems](https://pic.leetcode-cn.com/1655206172-XJLRyZ-IMG_4659.PNG)

示例 1

输入:n = 3，zs = 50，60，1000 输出:

321

示例 2

输入:n = 4，zs = 50，600，700，1000 输出:

1，4，3，2

4，1，3，2

4，3，1，2

4，3，2，1

提示 1:1 <= n <= 10

提示 2:输出结果需要按小到大排序

## 运行方式

```bash
> g++ SDQW.cpp SDQW.h -o SDQW

> ./SDQW
```