//
// Created by Hosonsoft on 2023/7/27.
//

#ifndef CONTOURS2BEZIER_SMOOTH_CONTOURS_HPP
#define CONTOURS2BEZIER_SMOOTH_CONTOURS_HPP
#include "opencv2/opencv.hpp"

void smoothContours(std::vector<cv::Point>& pt, std::vector<cv::Point2f>& dst, int filterRadius)
{
    using namespace cv;
    using namespace std;
    vector<cv::Point>& contours = pt;

    // contour smoothing parameters for gaussian filter
    int filterSize = 2 * filterRadius + 1;
    double sigma = 0;

    size_t len = contours.size() + 2 * filterRadius;
    size_t idx = (contours.size() - filterRadius);
    vector<float> x, y;
    for (size_t i = 0; i < len; i++)
    {
        x.push_back(contours[(idx + i) % contours.size()].x);
        y.push_back(contours[(idx + i) % contours.size()].y);
    }
    // filter 1-D signals
    vector<float> xFilt, yFilt;
    GaussianBlur(x, xFilt, cv::Size(filterSize, filterSize), sigma, sigma);
    GaussianBlur(y, yFilt, cv::Size(filterSize, filterSize), sigma, sigma);

    // build smoothed contour
    vector<cv::Point2f> smoothContours2f;
    for (size_t i = filterRadius; i < contours.size() + filterRadius; i++)
    {
        smoothContours2f.emplace_back(xFilt[i], yFilt[i]);
    }
    dst = smoothContours2f;
}



#endif //CONTOURS2BEZIER_SMOOTH_CONTOURS_HPP
