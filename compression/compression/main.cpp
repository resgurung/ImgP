//
//  main.cpp
//  compression
//  Compress a given image and decompress
//  MAPPER->QUANTIZER->ENCODER->INVERSE->DECODER
//  Created by Resham Gurung on 20/11/2014.
//  Copyright (c) 2014 Rg. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>//"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[])
{
    // inisilize variable
     Mat original;              // original image
     Mat processed;
    char checkForAnyKeyPressed;       //pressed any key to exit the window
    //Read the image from the file
    original = imread("/Users/robingurung/Desktop/image analysis/image.jpg");
    //Check if the image data is loaded
    if(!original.data)
    {
        printf("Error loading Image from the File. Re-check the url......");
        return (-1);
    }
    else
        printf("Image loaded.");
    
    //Create window for Display
    namedWindow(" Display Window", CV_WINDOW_AUTOSIZE);
    //Draw image in the window with imshow
    imshow(" Display Window",original);
    
        checkForAnyKeyPressed = cvWaitKey(0);

    
    /** 
     color to grey  by cvtColor(input image, processed image, cv function to convert rgb to grey)
     */
    
    cvtColor(original, processed, CV_RGB2GRAY);
    //Create window for Display
    namedWindow(" Display Window", CV_WINDOW_AUTOSIZE);
    //Draw image in the window with imshow
    imshow(" Display Window",processed);
    //grey scale image "processed"
    checkForAnyKeyPressed = cvWaitKey(0);
    
    /**
     FFT/DCT/PCA transform the image    ********[MAPPER]********
     */
    //DCT is implemented to show avaiable data redundency
    Mat padded;
    int m = getOptimalDFTSize(original.rows);
    int n = getOptimalDFTSize(original.cols);
    
    /**
     Vector/scalar transform the image    ********[QUANTIZER]********
     */
    
    /**
     Houghman coding/line coding transform the image    ********[ENCODER]********
     */
    //main
    return 0;
 
}//end main


