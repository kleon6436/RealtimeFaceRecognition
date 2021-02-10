#include <iostream>
#include "opencv2/opencv.hpp"

int main()
{
    const std::string cascadeClass = "../haarcascade_frontalface_default.xml.txt";
    auto faceCascade = cv::CascadeClassifier(cascadeClass);

    cv::VideoCapture camera(0);
    if (!camera.isOpened())
    {
        return -1;
    }

    cv::Mat inputFrame;
    std::vector<cv::Rect> contour;
    while (camera.read(inputFrame))
    {
        cv::Mat flipFrame;
        cv::flip(inputFrame, flipFrame, 1);

        faceCascade.detectMultiScale(flipFrame, contour, 1.2, 5, 0, cv::Size(20, 20));

        for (auto & i : contour)
        {
            cv::rectangle(flipFrame, cv::Point(i.x, i.y),
                          cv::Point(i.x + i.width, i.y + i.height),
                          cv::Scalar(255, 255, 255), 1); //矩形の可視化
        }

        cv::imshow("win", flipFrame);
        const auto key = cv::waitKey(1);
        if (key == 'q')
        {
            break;
        }
    }

    camera.release();
    cv::destroyAllWindows();
    return 0;
}
