#include "FaceCaptureController.h"

using namespace kchary::RealtimeFaceRecognition::FaceCapture;

int main(int, char *argv[]) {
    const std::string mode = argv[1];

    auto faceCaptureController = std::make_unique<FaceCaptureController>();
    if (mode == "FaceCapture")
    {
        if (faceCaptureController->FaceDetectionAndCapture() != 0)
        {
            return -1;
        }
    }
    else if (mode == "LearnFace")
    {
        if (faceCaptureController->LearnFace() != 0)
        {
            return -1;
        }
    }
    else if (mode == "RecognitionFace")
    {
        if (faceCaptureController->RecognitionFace() != 0)
        {
            return -1;
        }
    }

    return 0;
}
