//
// Created by kleon6436 on 2021/02/11.
//

#include <filesystem>
#include "FaceCaptureController.h"
#include "opencv2/face.hpp"

namespace kchary::RealtimeFaceRecognition::FaceCapture
{
    /**
     * You need to change it to the cascade class file path for your environment.
     */
    static std::string SascadeClass = "../haarcascade_frontalface_default.xml.txt";
    static std::string name[] = { "None", "kchary" };

    /**
     * Method of face detection and capture.
     * @return 0:Success 1: Failure
     */
    int FaceCaptureController::FaceDetectionAndCapture() const
    {
        cv::VideoCapture camera(0);
        if (!camera.isOpened())
        {
            return -1;
        }

        auto faceCascade = cv::CascadeClassifier(SascadeClass);
        cv::Mat inputFrame;
        std::vector<cv::Rect> faces;
        auto count = 0;
        while (camera.read(inputFrame))
        {
            cv::flip(inputFrame, inputFrame, 1);
            cv::Mat grayFrame;
            cv::cvtColor(inputFrame, grayFrame, cv::COLOR_BGR2GRAY);

            // face detection.
            faceCascade.detectMultiScale(inputFrame, faces, 1.3, 5);
            for (auto& i : faces)
            {
                cv::rectangle(inputFrame, cv::Point(i.x, i.y),
                              cv::Point(i.x + i.width, i.y + i.height),
                              cv::Scalar(255, 255, 255), 1);

                count += 1;
                const auto faceID = 1;
                cv::imwrite("../dataset/User_" + std::to_string(faceID) + "_" + std::to_string(count) + ".jpg",
                            grayFrame(cv::Rect(cv::Point(i.x, i.y), cv::Size(i.width, i.height))));
            }

            cv::imshow("VideoCapture", inputFrame);
            const auto key = cv::waitKey(1);
            if (key == 'q' || count >= 30)
            {
                break;
            }
        }

        camera.release();
        cv::destroyAllWindows();

        return 0;
    }

    /**
     * Method of learning face.
     * @return 0: Success, 1: Failure
     */
    int FaceCaptureController::LearnFace() const
    {
        std::tuple<std::vector<cv::Mat>, std::vector<int>> imagesAndLabels;
        const std::string directoryPath = "../dataset";
        if (GetImagesAndLabel(directoryPath, imagesAndLabels) != 0)
        {
            return -1;
        }

        const auto images = std::get<0>(imagesAndLabels);
        const auto labels = std::get<1>(imagesAndLabels);
        auto recognizer =  cv::face::LBPHFaceRecognizer::create();
        recognizer->train(images, labels);
        recognizer->write("../trainer/train.yml");

        return 0;
    }

    /**
     * Method of recognizing face.
     * @return 0: Success 1: Failure
     */
    int FaceCaptureController::RecognitionFace() const
    {
        const auto recognizer =  cv::face::LBPHFaceRecognizer::create();
        recognizer->read("../trainer/train.yml");

        cv::VideoCapture camera(0);
        if (!camera.isOpened())
        {
            return -1;
        }

        auto faceCascade = cv::CascadeClassifier(SascadeClass);
        cv::Mat inputFrame;
        std::vector<cv::Rect> faces;
        while (camera.read(inputFrame))
        {
            cv::flip(inputFrame, inputFrame, 1);
            cv::Mat grayFrame;
            cv::cvtColor(inputFrame, grayFrame, cv::COLOR_BGR2GRAY);

            // face detection and recognition.
            faceCascade.detectMultiScale(inputFrame, faces, 1.3, 5);
            for (auto& i : faces)
            {
                cv::rectangle(inputFrame, cv::Point(i.x, i.y),
                              cv::Point(i.x + i.width, i.y + i.height),
                              cv::Scalar(0, 255, 0), 1);

                // Predict
                auto label = -1;
                auto predictScore = 0.0;
                recognizer->predict(grayFrame(cv::Rect(cv::Point(i.x, i.y), cv::Size(i.width, i.height))), label, predictScore);

                if (predictScore < 100)
                {
                    // Show text.
                    cv::putText(inputFrame, name[label], cv::Point(i.x + 5, i.y - 5), static_cast<int>(cv::FONT_HERSHEY_SIMPLEX), 1, cv::Scalar(255, 255, 255), 2);
                    cv::putText(inputFrame, std::to_string(static_cast<int>(predictScore)) + "%", cv::Point(i.x + 5, i.y + i.height - 5),
                                static_cast<int>(cv::FONT_HERSHEY_SIMPLEX), 1, cv::Scalar(255, 255, 255), 1);
                }
            }

            cv::imshow("VideoCapture", inputFrame);
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

    /**
     * Method of getting images and labels.
     * @param directoryPath Directory path.
     * @param imagesAndLabel Tuple of images and labels.
     * @return 0: Success, 1: Failure
     */
    int FaceCaptureController::GetImagesAndLabel(const std::string& directoryPath, std::tuple<std::vector<cv::Mat>, std::vector<int>>& imagesAndLabel)
    {
        std::vector<std::string> filePaths;
        GetFilePaths(directoryPath, filePaths);

        std::vector<cv::Mat> images;
        std::vector<int> ids;
        for (const auto& filePath : filePaths)
        {
            // Get image data and face id.
            auto faceImg = cv::imread(filePath, cv::IMREAD_GRAYSCALE);
            if (faceImg.empty())
            {
                return -1;
            }

            cv::resize(faceImg, faceImg, cv::Size( 200, 200 ) );

            // Push data to vector array.
            images.push_back(faceImg.clone());
            const auto faceID = 1;
            ids.push_back(faceID);
        }

        // Create tuple.
        imagesAndLabel = std::make_pair(images, ids);

        return 0;
    }

    /**
     * Method of getting file paths.
     * @param path Directory path.
     * @param filePaths File paths (out)
     * @return 0: Success, 1: Failure
     */
    int FaceCaptureController::GetFilePaths(const std::string& path, std::vector<std::string>& filePaths)
    {
        std::filesystem::directory_iterator itr(path);
        const std::filesystem::directory_iterator end;
        std::error_code err;

        for (; itr != end && !err; itr.increment(err))
        {
            const auto entry = *itr;
            filePaths.push_back(entry.path().string());
        }

        return 0;
    }
}
