#pragma once
//
// Created by kleon6436 on 2021/02/11.
//

#include <string>
#include <vector>
#include <tuple>
#include "opencv2/opencv.hpp"

namespace kchary::RealtimeFaceRecognition::FaceCapture
{
    class FaceCaptureController {
    public:
        int FaceDetectionAndCapture() const;
        int LearnFace() const;
        int RecognitionFace() const;

    private:
        static int GetImagesAndLabel(const std::string& path, std::tuple<std::vector<cv::Mat>, std::vector<int>>& imagesAndLabel);
        static int GetFilePaths(const std::string& path, std::vector<std::string>& filePaths);
    };
}