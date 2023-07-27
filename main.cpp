#include <iostream>
#include <filesystem>

#include "opencv2/opencv.hpp"
#include "smooth_contours.hpp"

#include "bezier.hpp"


using namespace cv;
using namespace std;

const std::string SAVEDIR = R"(D:\workspace\Contours2Bezier\result\)";

int findContours(const cv::Mat &src, std::vector<std::vector<cv::Point>> &contours) {

    if (src.empty()) {
        return -1;
    }
    Mat gray;
    if (src.channels() == 1) {
        gray = src;
    } else {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    }
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    vector<vector<Point>> contoursTmp;
    findContours(binary, contours, RETR_LIST, CHAIN_APPROX_NONE);

    // filter contours
    for (int i = (int) contours.size() - 1; i >= 0; i--) {
        if (contours[i].size() < 10) {
            contours.erase(contours.begin() + i);
        }
    }

    Mat dst = Mat::zeros(src.size(), CV_8UC3);
    drawContours(dst, contours, -1, Scalar(0, 0, 255), 2, 8);
    namedWindow("source contours", WINDOW_NORMAL);
    imshow("source contours", dst);
    imwrite(SAVEDIR + "source_contours.tif", dst);
    return 0;
}

void drawBezier(cv::Mat& img, const PiecewiseBezierCurve<2>& curve) {
    for (const auto& b : curve.getPiecewiseBeziers()) {

        vector<Point> draw_points;
        double t = 0.0;
        double step = 0.01;
        while (t <= 1.0) {
            auto p = b.at(t);
            draw_points.emplace_back(p[0], p[1]);
            t += step;
        }
        polylines(img,
                  draw_points,
                  false,
                  Scalar(int(b.length()) * 100811 % 255,
                         int(b.length()) * 337919 % 255,
                         int(b.length()) * 639701 % 255),
                  2, 8, 0);
    }
}



int main() {
    std::filesystem::path curDir = std::filesystem::current_path();
    std::string imagePath = curDir.append(R"(..\images\srcImage.tif)").string();
    cv::Mat img = cv::imread(imagePath);

    std::vector<std::vector<cv::Point>> contours;
    findContours(img, contours);

    cv::Mat smoothImage = cv::Mat::zeros(img.size(), CV_8UC3);
    cv::Mat bezierImage = img.clone();

    std::vector<std::vector<cv::Point>> sc;
    for (auto & contour : contours) {
        std::vector<cv::Point2f> smoothContours2f;
        smoothContours(contour, smoothContours2f, 10);
        std::vector<Eigen::Vector2d> eContour;
        contour.clear();
        for (auto & i : smoothContours2f) {
            eContour.emplace_back(i.x, i.y);
            contour.emplace_back(i.x, i.y);
        }
        PiecewiseBezierCurve<2> curve;
        auto& resultBezier = curve.fit(eContour, 10);
        drawBezier(bezierImage, curve);
    }
    drawContours(smoothImage, contours, -1, cv::Scalar(0, 0, 255), 2, 8);

    namedWindow("smooth contours", cv::WINDOW_NORMAL);
    imshow("smooth contours", smoothImage);
    imwrite(SAVEDIR + "smooth_contours.tif", smoothImage);

    namedWindow("bezier contours", cv::WINDOW_NORMAL);
    imshow("bezier contours", bezierImage);
    imwrite(SAVEDIR + "bezier_contours.tif", bezierImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
