//
// Created by scott on 1/19/21.
//

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

// Draw a single point
static void draw_point( Mat& img, Point2f fp, Scalar color )
{
    circle( img, fp, 2, color );
}

// Draw delaunay triangles
static void draw_delaunay( Mat& img, Subdiv2D& subdiv, Scalar delaunay_color )
{

    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    vector<Point> pt(3);
    Size size = img.size();
    Rect rect(0,0, size.width, size.height);

    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

        // Draw rectangles completely inside the image.
        if ( rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
        {
            line(img, pt[0], pt[1], delaunay_color, 1);
            line(img, pt[1], pt[2], delaunay_color, 1);
            line(img, pt[2], pt[0], delaunay_color, 1);
        }
    }
}

//Draw voronoi diagram
static void draw_voronoi( Mat& img, Subdiv2D& subdiv )
{
    vector<vector<Point2f> > facets;
    vector<Point2f> centers;
    subdiv.getVoronoiFacetList(vector<int>(), facets, centers);

    vector<Point> ifacet;
    vector<vector<Point> > ifacets(1);

    for( size_t i = 0; i < facets.size(); i++ )
    {
        ifacet.resize(facets[i].size());
        for( size_t j = 0; j < facets[i].size(); j++ )
            ifacet[j] = facets[i][j];

        Scalar color;
        color[0] = rand() & 255;
        color[1] = rand() & 255;
        color[2] = rand() & 255;
        fillConvexPoly(img, ifacet, color, 8, 0);

        ifacets[0] = ifacet;
        polylines(img, ifacets, true, Scalar(), 1);
        circle(img, centers[i], 3, Scalar());
    }
}


int obama_delaunay()
{

    // Define window names
    string win_delaunay = "Delaunay Triangulation";
    string win_voronoi = "Voronoi Diagram";

    // Turn on animation while drawing triangles
    bool animate = true;

    // Define colors for drawing.
    Scalar delaunay_color(255,255,255), points_color(0, 0, 255);

    // Read in the image.
    Mat img = imread("obama.jpg");

    // Keep a copy around
    Mat img_orig = img.clone();

    // Rectangle to be used with Subdiv2D
    Size size = img.size();
    Rect rect(0, 0, size.width, size.height);

    // Create an instance of Subdiv2D
    Subdiv2D subdiv(rect);

    // Create a vector of points.
    vector<Point2f> points;

    // Read in the points from a text file
    ifstream ifs("points.txt");
    int x, y;
    while(ifs >> x >> y)
    {
        points.push_back(Point2f(x,y));
    }

    // Insert points into subdiv
    for( vector<Point2f>::iterator it = points.begin(); it != points.end(); it++)
    {
        subdiv.insert(*it);
        // Show animation
        if (animate)
        {
            Mat img_copy = img_orig.clone();
            // Draw delaunay triangles
            draw_delaunay( img_copy, subdiv, delaunay_color );
            imshow(win_delaunay, img_copy);
            waitKey(100);
        }

    }

    // Draw delaunay triangles
    draw_delaunay( img, subdiv, delaunay_color );

    // Draw points
    for( vector<Point2f>::iterator it = points.begin(); it != points.end(); it++)
    {
        draw_point(img, *it, points_color);
    }

    // Allocate space for Voronoi Diagram
    Mat img_voronoi = Mat::zeros(img.rows, img.cols, CV_8UC3);

    // Draw Voronoi diagram
    draw_voronoi( img_voronoi, subdiv );

    // Show results.
    imshow( win_delaunay, img);
    imshow( win_voronoi, img_voronoi);
    waitKey(0);

    return 0;
}

int sorolla_example(){
    std::string image_path = samples::findFile("obama.jpg");
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

int main()
{
    return obama_delaunay();
}