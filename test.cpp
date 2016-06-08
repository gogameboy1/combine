#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;

int main() {

    cout <<"enter main"<< endl;
    VideoCapture cap;
    cap.open("/dev/stdin");
    if (!cap.isOpened()) {
      cout << "Video not opened" << endl;
      return -1;
                        
    }
    cout << "Video Captured" <<endl;
    Mat edges;
    namedWindow("Show Video",1);
    for(;;) {
      Mat frame;
      cap >> frame; // get a new frame from camera
      if (!cap.read(frame)) {
        break;
      }
      imshow("Show Video", frame);
      waitKey(30);
    }
    waitKey(0);
    return 0;
                        
}

