// SREERAG MURALEEDHARAN

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include "docScan.hpp"
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;


Mat imgOriginal, imgGray, imgCanny, imgBlur, imgThre, imgDil, imgWarp, imgCrop, imgAdpThre, imgFinal, gammaCorrected;
vector<Point> initialPoints, docPoints;
static string path;

//w = width and h = height of an A4 paper multiplied by 2
float w = 420, h = 596;

Mat preProcessing(Mat image)
{
    //Converts the image to Grey
    cvtColor(image, imgGray, COLOR_BGR2GRAY);

    //Adds Blur
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);

    //Finds edges 
    Canny(imgBlur, imgCanny, 25, 75);

    //Refining the edges
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    return imgDil;
}

vector<Point> getContours(Mat image)
{

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;


    //Inbuild function to find contours 
    findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Point> biggest;
    int maxArea = 0;

    //Area threshold inorder to be detected as a Contour
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);

        if (area > 1000)
        {
            //Checks if the contour perimeter is closed or open
            float peri = arcLength(contours[i], true);

            //Detects the points on the contours
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            //Checks if the contour is a rectangle
            //and returns the biggest rectangle
            if (area > maxArea && conPoly[i].size() == 4)
            {
                biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
                maxArea = area;

            }
        }
    }
    return biggest;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
    Point2f src[4] = { points[0],points[1],points[2],points[3] };
    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;

}
vector<Point> reorder(vector<Point> points)
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++)

    {
        //Adds/Subtracts the x and y co-ordinates of the points
        //and adds the value to the vector sumPoints/subPoints

        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    //Sets the first and the last points as the smallest and the biggest values of sumPoints, respectively
    //Sets the second and third points as the biggest and the smallest values of subPoints, respectively 

    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  //0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  //1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  //2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  //3

    return newPoints;
}

bool fileExists(const string& filename) 
{
    ifstream file(filename.c_str());
    return file.good();
}

string getOutputFileName(string r, string s, string a)
{
    string fname, ext, kname;

    if (r == r)
    {
        // Extract file name and extension from the provided original file path or name
        size_t sep = r.find_last_of("\\");
        r = r.substr(sep + 1, r.size() - sep - 1);

        size_t dot = r.find_last_of(".");
        if (dot != string::npos)
        {
            fname = r.substr(0, dot);
            ext = r.substr(dot, r.size() - dot);
        }
        else
        {
            fname = r;
            ext = "";
        }
    }
    kname = a;
    string outputFileName = kname + "\\" + fname + "_" + s + ext;

    // Check if the file already exists
    int counter = 1;
    while (fileExists(outputFileName)) {
        // Append a number to the file name to make it more definite
        stringstream ss;
        ss << counter++;
        outputFileName = kname + "\\" + fname + "_" + s + "_" + ss.str() + ext;
    }

    return outputFileName;
}

int findCircleIndex(const vector<Point>& centers, const Point& point)
{
    // Find the index of the circle (center) clicked by the user
    for (size_t i = 0; i < centers.size(); ++i)
    {
        int distance = norm(centers[i] - point);

        if (distance < 5)
        {
            return static_cast<int>(i);
        }
    }
    return -1;  // No circle found
}
void drawPoints(vector<Point> points, Scalar color)
{
    int j[5] = { 0,1,3,2,0 };

    for (int i = 0; i < points.size(); i++)
    {
        circle(imgOriginal, points[i], 10, color, FILLED);
        line(imgOriginal, points[j[i]], points[j[i + 1]], color, 2);
    }

}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    static int activeCircleIndex = -1;

    if (event == EVENT_LBUTTONDOWN)
    {
        activeCircleIndex = findCircleIndex(docPoints, Point(x, y));

    }

    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        // Update the active circle while dragging
        int activeCircleIndex = findCircleIndex(docPoints, Point(x, y));

        if (activeCircleIndex != -1)
        {
            imgOriginal = imread(path);
            // resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
            docPoints[activeCircleIndex] = Point(x, y);

        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        // Move the active circle to the current mouse position when left button is released
        if (activeCircleIndex != -1)
        {

            imgOriginal = imread(path);
            // resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
            docPoints[activeCircleIndex] = Point(x, y);

        }
        activeCircleIndex = -1;

    }

}

void main()
{
    string despath, base_path;
    int check, n;
    char e;

    cout << "Enter the number of documents to be scanned : ";
    cin >> n;

    printf("\n Enter the address path for the scanned documents (C:/location) : ");
    cin >> base_path;

    string folder_name = "OUTPUT";
    string result = base_path + "\\" + folder_name;
    struct stat sb;

    check = _mkdir(result.c_str());

    if (!check)
    {
        printf("\n Directory created\n");
    }
    else if (stat(result.c_str(), &sb) == 0)
    {
        cout << "\n Directory Exist";
    }
    else
    {
        printf("\n Unable to create directory\n");
        exit(1);
    }

    while (n != 0)
    {
        cout << "\n Enter the image path :";
        cin >> path;

        imgOriginal = imread(path);

        imgThre = preProcessing(imgOriginal);

        initialPoints = getContours(imgThre);

        docPoints = reorder(initialPoints);

    label:
        drawPoints(docPoints, Scalar(255, 0, 0));

        imgWarp = getWarp(imgOriginal, docPoints, w, h);

        int cropVal = 5;
        Rect roi(5, 5, w - (2 * 5), h - (2 * 5));
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

        cout << "\n Do you want to edit? (y/n) : ";
        cin >> e;

        if (e == 'y')
        {

            namedWindow("ImageEdit");
            setMouseCallback("ImageEdit", onMouse, nullptr);

            while (true)
            {
                // Draw the circles directly on the window
                drawPoints(docPoints, Scalar(255, 0, 0));

                imshow("ImageEdit", imgOriginal);

                int key = waitKey(1) & 0xFF;

                if (getWindowProperty("ImageEdit", WND_PROP_VISIBLE) == 0) {
                    break;
                }

            }
            for (const auto& element : docPoints) {
                std::cout << element << " ";
            }


            goto label;

        }
        else if (e == 'n')
        {

            imwrite(getOutputFileName(path, "scanned", result.c_str()), imgAdpThre);
            n = n--;

        }


    }

}


