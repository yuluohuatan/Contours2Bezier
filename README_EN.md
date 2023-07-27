Contours2Bezier
=========
[Chinese](README.md) | [English](README_EN.md)

## Introduction
C++ algorithm for contour to bezier curve based on Opencv and Eigen.

## Implementation steps:
1. Find the contour, use parameters: CV_RETR_EXTERNAL/CV_RETR_LIST, CV_CHAIN_APPROX_NONE
2. One-dimensional Gaussian smoothing of the contour
3. Contour point set fitting bezier curve

## Dependencies
* Opencv 3.4.6
* Eigen 3.3.9
* C++ 17

## Reference and quote
* [Contour Gaussian smoothing](https://blog.csdn.net/qq_15947787/article/details/78518834)
* [ParametricCurve](https://github.com/tanzby/ParametricCurve)
