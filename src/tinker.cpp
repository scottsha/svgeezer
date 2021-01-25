//
// Created by scott on 1/19/21.
//

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
int main()
{
    std::string image_path = samples::findFile("sorolla.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
//    imshow("Display window", img);
//    int k = waitKey(0); // Wait for a keystroke in the window
//    if(k == 's')
//    {
//        imwrite("starry_night.png", img);
//    }


    // Declare the variables we are going to use
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char* window_name = "Laplace Demo";
    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur( img, src, Size(3, 3), 0, 0, BORDER_DEFAULT );
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
//    cvtColor( img, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
    Mat abs_dst;
    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    // converting back to CV_8U
    GaussianBlur( dst, dst, Size(3, 3), 0, 0, BORDER_DEFAULT );
    GaussianBlur( dst, dst, Size(3, 3), 0, 0, BORDER_DEFAULT );
    GaussianBlur( dst, dst, Size(3, 3), 0, 0, BORDER_DEFAULT );
    GaussianBlur( dst, dst, Size(3, 3), 0, 0, BORDER_DEFAULT );
    dst = 10 * dst;
    convertScaleAbs( dst, abs_dst );
    imshow( window_name, abs_dst );
    waitKey(0);

    return 0;
}