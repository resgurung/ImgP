//
//  main.cpp
//  tracker
//
//  Created by Robin Gurung on 19/11/2014.
//  Copyright (c) 2014 Rg. All rights reserved.
//


#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{

    // insert code here...
    
    
    //CvCapture*  captureWebcam;    //assign later for webcam video stream from the computer webcam
    //CvSize size640x480 =  cvSize(640,480); //640x480 size for all window , also make sure webcam is set to the same size
    
    CvCapture* captureWebcam  = cvCaptureFromCAM(CV_CAP_ANY); //[0] == use the cam from the computer used
    IplImage *  current_frame = cvQueryFrame ( captureWebcam);
    CvSize size640x480 = cvSize(current_frame->width, current_frame->height);
    if(captureWebcam == NULL){
        
        printf("Error capturing Cam");
        getchar();
        return (-1);
    }
   
    IplImage* imgOriginal;    //pointer to the image structure, this will be the input image from the webcam
    IplImage* imgprocessed; //processed image
    
                            //Ipl is short for intel image processes library
    CvMemStorage* storage;  //necessary storage variable to pass into cvHoughCircle()
    CvSeq* circle;          //pointer to an open cv sequence, will be return by cvHoughCircle() and will contain all circle..
    
    float* XYRadius = nullptr;        //pointer to the 3 element arrayof float
                            //[0] => x position of detected object
                            //[1] => y position of detected object
                            //[2] => radius of detected object
    
    int i ;                 //loop counter
    char checkForEscKey;    //come out of loop
    
  
    
    //declare tow window
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE); //original image from webcam
    cvNamedWindow("processed", CV_WINDOW_AUTOSIZE);//processed image we will used for decting circle
    
    
    imgprocessed = cvCreateImage(size640x480, IPL_DEPTH_8U, 1);/**1st parameter:pixel size 640x480, 2nd parameter: 8 bit color depth 3rd parameter:1 channel greyscale, if this was a color image then use 3*/
    
    //for each frame
    while (1) {
        imgOriginal  = cvQueryFrame(captureWebcam);  // capture web frame
        if(imgOriginal == NULL){
            printf("Error capturing image");
            getchar();
            break;
            
        }
        cvInRangeS(imgOriginal, CV_RGB(175, 0, 0), CV_RGB(256, 100, 100), imgprocessed );
        
        storage = cvCreateMemStorage(0);
        
        cvSmooth(imgprocessed, imgprocessed, CV_GAUSSIAN,9,9);
        
        circle = cvHoughCircles(imgprocessed, storage, CV_HOUGH_GRADIENT, 2, imgprocessed->height/4,100,50,10,400);
        
        for (i =0;i < circle->total; i++){
            XYRadius =(float*)cvGetSeqElem(circle, i);
            printf("ball position x =%f , y =%f , r = %f ", XYRadius[0],XYRadius[1],XYRadius[2]);
        
        
        //cvCircle(imgOriginal, cvPoint(cvRound(XYRadius[0]), XYRadius[1])), 3, CV_RGB(0, 255, 0)  ,CV_FILLED) ;
    
        cvCircle(imgOriginal, cvPoint(cvRound(XYRadius[0]), cvRound(XYRadius[1])), 3, CV_RGB(0, 255, 0),CV_FILLED);
        //cvCircle(imgOriginal, cvPoint(cvRound(XYRadius[0]), XYRadius[1])), cvPoint(cvRound( XYRadius[2])), CV_RGB( 255,0, 0) ,3);
    
        cvCircle(imgprocessed, cvPoint(cvRound(XYRadius[0]), cvRound(XYRadius[1])), cvRound(XYRadius[2]), CV_RGB(255, 0, 0),3);
            
        }
        cvShowImage("original", imgOriginal);
        cvShowImage("processed", imgprocessed);
        
        cvReleaseMemStorage(&storage);
        checkForEscKey = cvWaitKey(10);
        if(checkForEscKey ==27)
            break;
        
    }
    //cvReleaseCapture(captureWebcam);
    cvReleaseCapture(&captureWebcam);
    cvDestroyWindow("original");
    cvDestroyWindow("processed");
    
    return (0);
}







