
// SREERAG MURALEEDHARAN


#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include "docScan.h"


using namespace cv;
using namespace std;


Mat imgOriginal, imgGray, imgCanny, imgBlur, imgThre, imgDil, imgWarp, imgCrop, imgAdpThre, imgFinal, gammaCorrected;
vector<Point> initialPoints, docPoints;
static string path;

//w = width and h = height of an A4 paper multiplied by 2
float w = 420, h = 596;

Mat preProcessing(Mat image)
{    
    // Converts the image to grayscale
    cvtColor(image, imgGray, COLOR_BGR2GRAY);

    // Applies Gaussian blur to reduce noise
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);

    // Finds edges using the Canny edge detector
    Canny(imgBlur, imgCanny, 25, 75);

    // Refines the edges using dilation with a 3x3 kernel
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    // Returns the preprocessed image with enhanced edges
    return imgDil;
}

vector<Point> getContours(Mat image)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // Inbuilt function to find contours 
    findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Vector to store polygonal approximation of contours
    vector<vector<Point>> conPoly(contours.size());

    // Vector to store the vertices of the biggest rectangle contour
    vector<Point> biggest;

    int maxArea = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        // Calculate the area of the contour
        int area = contourArea(contours[i]);

        // Check if the area exceeds a threshold to be considered as a contour
        if (area > 1000)
        {
            // Calculate the perimeter of the contour
            float peri = arcLength(contours[i], true);

            // Approximate the contour to a polygon with 4 vertices
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            // Check if the contour is a rectangle and has the maximum area
            if (area > maxArea && conPoly[i].size() == 4)
            {
                // Update the vector of the biggest rectangle contour vertices
                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                maxArea = area;
            }
        }
    }
    return biggest;
}

vector<Point> reorder(vector<Point> points)
{
    vector<int> sumPoints, subPoints;

    // Calculate the sum and difference of x and y coordinates for each point
    for (int i = 0; i < 4; i++)
    {   
        // Adds/Subtracts the x and y coordinates of the points
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    vector<Point> newPoints;

    // Set the first point as the one with the smallest sum of coordinates
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  // 0

    // Set the second point as the one with the largest difference of coordinates
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  // 1

    // Set the third point as the one with the smallest difference of coordinates
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  // 2

    // Set the fourth point as the one with the largest sum of coordinates
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  // 3

    return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
    // Define source points/Destination points
    Point2f src[4] = { points[0],points[1],points[2],points[3] };
    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

    Mat matrix = getPerspectiveTransform(src, dst);

    // Apply perspective transformation to the input image
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;

}

string getOutputFileName(string r, string s, string a)
{
    string fname, ext, kname;

    // Extract file name and extension from the provided original file path or name
    size_t sep = r.find_last_of("\\");
    r = r.substr(sep + 1, r.size() - sep - 1);

    size_t dot = r.find_last_of(".");
    if (dot != string::npos)
    {
        // If a dot is found, separate the file name and extension
        fname = r.substr(0, dot);
        ext = r.substr(dot, r.size() - dot);
    }
    else
    {
        // If no dot is found, use the entire string as the file name and leave extension empty
        fname = r;
        ext = "";
    }

    kname = a;

    return kname + "\\" + fname + "_" + s + ext;
}

void drawPoints(vector<Point> points, Scalar color)
{
    // Array to define a loop for connecting lines between points
    int j[5] = { 0, 1, 3, 2, 0 };

    for (int i = 0; i < points.size(); i++)
    {
        circle(imgOriginal, points[i], 10, color, FILLED);
        line(imgOriginal, points[j[i]], points[j[i + 1]], Scalar(0, 255, 0), 2);
    }
}

int findCircleIndex(const vector<Point>& centers, const Point& point)
{
    // Find the index of the circle (center) clicked by the user
    for (size_t i = 0; i < centers.size(); ++i)
    {
        // Calculate the Euclidean distance between the current center and the given point
        int distance = norm(centers[i] - point);

        // Check if the distance is below a threshold (5 in this case) to consider it a click on the circle
        if (distance < 5)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    // Variable to store the index of the active circle being interacted with
    static int activeCircleIndex = -1;

    if (event == EVENT_LBUTTONDOWN)
    {
        // Set the active circle index when the left button is pressed
        activeCircleIndex = findCircleIndex(docPoints, Point(x, y));
    }
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        // Update the position of the active circle while dragging
        int activeCircleIndex = findCircleIndex(docPoints, Point(x, y));

        // Check if an active circle is found
        if (activeCircleIndex != -1)
        {
            // Reload the original image and update the active circle's position
            imgOriginal = imread(path);
            docPoints[activeCircleIndex] = Point(x, y);
        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        // Move the active circle to the current mouse position when the left button is released
        if (activeCircleIndex != -1)
        {
            imgOriginal = imread(path);
            docPoints[activeCircleIndex] = Point(x, y);
        }
        // Reset the active circle index when the left button is released
        activeCircleIndex = -1;
    }
}

void main()
{
    // Variables for user input and directory creation
    string base_path, folder_name, result;
    int check, n;
    char e;

    cout << "Enter the number of documents to be scanned: ";
    cin >> n;

    cout << "\nEnter the base path for the scanned documents (C:/location): ";
    cin >> base_path;

    folder_name = "OUTPUT";
    result = base_path + "\\" + folder_name;
    struct stat sb;

    check = _mkdir(result.c_str());

    if (!check)
    {
        cout << "\nDirectory created\n";
    }
    else if (stat(result.c_str(), &sb) == 0)
    {
        cout << "\nDirectory exists";
    }
    else
    {
        cout << "\nUnable to create directory\n";
        exit(1);
    }

    while (n != 0)
    {
        cout << "\nEnter the image path: ";
        cin >> path;
        imgOriginal = imread(path);

        imgThre = preProcessing(imgOriginal);

        initialPoints = getContours(imgThre);

        docPoints = reorder(initialPoints);

        // Label for potential editing loop
        label:

        drawPoints(docPoints, Scalar(0, 255, 0));

        imgWarp = getWarp(imgOriginal, docPoints, w, h);

        int cropVal = 5;
        Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
        imgCrop = imgWarp(roi);

        cvtColor(imgCrop, imgFinal, COLOR_BGR2GRAY);

        // Apply histogram equalization to enhance contrast
        Mat equalizedImage;
        equalizeHist(imgFinal, equalizedImage);

        // Increase the brightness
        imgAdpThre = equalizedImage + Scalar(150, 25, 60);

        imshow("Image", imgOriginal);
        resize(imgAdpThre, imgAdpThre, Size(), 1.5, 1.5);
        imshow("Image Adaptive Threshold", imgAdpThre);
        waitKey(0);

        cout << "\nDo you want to edit? (y/n): ";
        cin >> e;

        if (e == 'y')
        {
            setMouseCallback("ImageEdit", onMouse, nullptr);

            while (true)
            {
                // Draw the circles directly on the window
                drawPoints(docPoints, Scalar(0, 255, 0));

                imshow("ImageEdit", imgOriginal);

                int key = waitKey(1) & 0xFF;

                waitKey(0);
            }

            // Print the final points after editing
            for (const auto& element : docPoints)
            {
                cout << element << " ";
            }

            goto label;
        }
        else if (e == 'n')
        {
            // Save the scanned and edited document
            imwrite(getOutputFileName(path, "scanned", result.c_str()), imgAdpThre);
            n = n--;
        }
    }

}

