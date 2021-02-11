# RealtimeFaceRecognition
## 概要
OpenCVでリアルタイム顔認識の記事を見つけたので、それをC++でやってみました！

元ネタ：https://www.hackster.io/mjrobot/real-time-face-recognition-an-end-to-end-project-a10826

## 使い方
以下の手順を行ってください。

1. OpenCVのインストール  
    拡張機能を使っているので、拡張機能も含めてビルドし直してください。
    https://swallow-incubate.com/archives/blog/20200508/
2. CMakeLists.txtの「OpenCV_DIR」をお使いの環境のパスに変更
3. ビルド
4. コマンドライン引数「FaceCapture」に設定し、顔画像を撮影。  
    FaceCaptureController.cpp内に書き出し先が指定されています。
    環境に合わせて修正してください。
5. コマンドライン引数「LearnFace」に設定し、顔画像を学習。  
    FaceCaptureController.cpp内に学習データの出力先が指定されています。
    環境に合わせて修正してください。
6. コマンドライン引数「RecognitionFace」に設定し、顔認証。  
    FaceCaptureController.cpp内に表示する名前が記載されています。
    環境に合わせて修正してください。

## 備考
実験用のプロジェクトですので、色々、大規模にソースが変わるかもしれないです。