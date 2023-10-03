#include <opencv2/opencv.hpp> //include opencv  for tools

int main() {
    cv::VideoCapture cap(0);  // Open the default camera
    if(!cap.isOpened()) {  // Check if we succeeded
        return -1; //return error otherwise
    }

    cv::Mat frame;
    while(true) {
        cap >> frame;  // Get a new frame from camera
        cv::imshow("Webcam Feed", frame); // Present frame
        
        if(cv::waitKey(30) >= 0) break;  // Wait for a keystroke then close when done. 
    }
    return 0;
}