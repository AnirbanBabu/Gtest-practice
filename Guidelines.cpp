#include <jni.h>
#include <string>
#include <android/log.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/imgproc/imgproc_c.h>


jbyteArray matToByteArray(JNIEnv* env, cv::Mat& mat) {
    // Create a vector to hold the Mat data
    std::vector<uchar> data;
    cv::imencode(".png", mat, data);

    // Create a new ByteArray object
    jbyteArray byteArray = env->NewByteArray(data.size());

    // Copy the Mat data to the ByteArray
    env->SetByteArrayRegion(byteArray, 0, data.size(), reinterpret_cast<const jbyte*>(data.data()));

    return byteArray;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_sasken_camera_1preview_ParkingGuidance_drawLine(JNIEnv *env, jobject thiz) {

    // Create an empty Transparent background frame with dimensions 1920x1080 and an alpha channel
    cv::Mat image = cv::Mat(1080, 1920, CV_8UC4, cv::Scalar(0, 0, 0, 0));  

    // Draw vertical lines of 1m, 2m, 3m 
    cv::line(image, cv::Point(660, 355), cv::Point(760, 240), cv::Scalar(0, 255, 0, 255), 5);
    cv::line(image, cv::Point(440, 605), cv::Point(660, 355), cv::Scalar(0, 255, 255, 255), 5);
    cv::line(image, cv::Point(40, 1050), cv::Point(440, 605), cv::Scalar(0, 0, 255, 255), 5);

    cv::line(image, cv::Point(1300, 355), cv::Point(1200, 240), cv::Scalar(0, 255, 0, 255), 5);
    cv::line(image, cv::Point(1500, 605), cv::Point(1300, 355), cv::Scalar(0, 255, 255, 255), 5);
    cv::line(image, cv::Point(1880, 1050), cv::Point(1500, 605), cv::Scalar(0, 0, 255, 255), 5);


    // Draw horizontal line (Greeen, yellow, red)
    cv::line(image, cv::Point(760, 240), cv::Point(1200, 240), cv::Scalar(0,255,0, 255), 5); 
    cv::line(image, cv::Point(660, 355), cv::Point(1300, 355), cv::Scalar(0, 255, 255, 255), 5);
    cv::line(image, cv::Point(440, 605), cv::Point(1500, 605), cv::Scalar(0, 0, 255, 255), 5);

    // Add level indicators (1m, 2m, 3m) at the end of each colored line
    cv::putText(image, "1M", cv::Point(485, 585), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(0, 0, 255, 255), 5);
    cv::putText(image, "2M", cv::Point(695, 345), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(0, 255, 255, 255), 5);
    cv::putText(image, "3M", cv::Point(790, 230), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(0, 255, 0, 255), 5);

    // Convert the Mat to jbyteArray
    jbyteArray byteArray = matToByteArray(env, image);

    return byteArray;
}
