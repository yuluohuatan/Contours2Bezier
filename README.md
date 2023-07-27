Contours2Bezier
=========
[Chinese](README.md) | [English](README_EN.md)
## 简介
C++ 基于Opencv，Eigen 实现的轮廓转贝塞尔曲线的算法。

## 实现步骤：
1. 查找轮廓，使用参数：CV_RETR_EXTERNAL/CV_RETR_LIST, CV_CHAIN_APPROX_NONE
2. 轮廓一维高斯平滑处理
3. 轮廓点集合拟合贝塞尔曲线

## 依赖
* Opencv 3.4.6
* Eigen 3.3.9
* C++ 17

## 参考和引用
* [轮廓高斯平滑](https://blog.csdn.net/qq_15947787/article/details/78518834)
* [ParametricCurve](https://github.com/tanzby/ParametricCurve)