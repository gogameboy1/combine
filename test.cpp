#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


using namespace std;
using namespace cv;

int main() {

    int pipe_fds[2];
    pid_t pid;

    pipe(pipe_fds);

    char *cmd[] = {"raspivid" , "-t 0 -w 1280 -h 720 -fps 60 -hf -b 2000000 -o -" , 0};

    if((pid = fork()) == 0)
    {
      dup2(pipe_fds[1] , 1);
      close(pipe_fds[0]);
      execvp(cmd[0] , cmd);

      perror(cmd[0]);
      exit(0);
    }else if(pid == -1)
    {
      perror("fork");
      exit(1);
    }
  
    dup2(pipe_fds[0] , 0);
    close(pipe_fds[1]);

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

