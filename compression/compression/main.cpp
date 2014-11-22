/**
    Compression & Decompression
    Compress a given image and decompress
    MAPPER->QUANTIZER->ENCODER->INVERSE->DECODER
    Image size -> 551,996 bytes (553 KB )
    Dimension -> 1920x1018
    Image Src ->http://blog.jimdo.com/wp-content/uploads/2014/01/tree-247122.jpg
    Note: I do not own this image
    Created by Resham Gurung on 20/11/2014.
    Copyright (c) 2014 Rg. All rights reserved.
 
*/

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
    original = imread("/Users/robingurung/Desktop/k/compression/image.jpg");
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
    //FFT is implemented to show avaiable data redundency
    Mat padded;
    //expand the image into optimal size
    int m = getOptimalDFTSize(original.rows);
    int n = getOptimalDFTSize(original.cols);
    //On the border add zero values
  
    copyMakeBorder(original, padded, 0, m - original.rows, 0, n - original.cols, BORDER_CONSTANT, Scalar::all(0));
    
    //The frequency domains range is much larger than its spatial counterpart. Therefore, we will store these in a float format.
    
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexImg;
    merge(planes,2, complexImg); // Add to the expanded another plane with zeros
    
    //DFT transform
    
    dft(complexImg, complexImg);   //ComplexImage fits in the source matrix
    
    //Transform the real and complex value to magnitude
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magImg = planes[0];
    
    // switch to logarithmic scale
    magImg +=Scalar::all(0);
    log(magImg, magImg);
    
     // crop the spectrum, if it has an odd number of rows or columns
    magImg = magImg(Rect(0,0,magImg.cols & -2, magImg.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magImg.cols/2;
    int cy = magImg.rows/2;
    
    /**
     Vector/scalar transform the image    ********[QUANTIZER]********
     */
    
    /**
     Houghman coding/line coding transform the image    ********[ENCODER]********
     */
    //main
    return 0;
 
}//end main


