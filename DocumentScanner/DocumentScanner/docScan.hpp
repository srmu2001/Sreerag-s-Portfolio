
// Sreerag Muraleedharan



using namespace cv;
using namespace std;
///      <summary>
///      Preprocesses the input image by converting it to grayscale, applying blur,
///      finding edges, and refining edges. Returns an image with enhanced edges.
///      </summary>
Mat preProcessing(Mat image);

///      <summary>
///      Finds and returns the points of the largest rectangle contour in the input image.
///      Returns vector of points representing the vertices of the largest rectangle contour.
///      </summary>
vector<Point> getContours(Mat image);

///      <summary>
///      Reorders the given set of points to ensure they represent a proper rectangle.
///      Returns vector of points representing reordered vertices of a rectangle.
///      </summary>
vector<Point> reorder(vector<Point> points);

///      <summary>
///      Applies perspective transformation to the input image based on the given set of source points.
///      Return warped image after applying perspective transformation.
///      </summary>
Mat getWarp(Mat img, vector<Point> points, float w, float h);

///      <summary>
///      Generates the output file name based on input parameters.
///      Returns constructed output file name.
///      </summary>
string getOutputFileName(string r, string s, string a);

///      <summary>
///      Draws points and connecting lines on the input image.
///      </summary>
void drawPoints(vector<Point> points, Scalar color);

///      <summary>
///      Finds the index of the circle (center) closest to the given point.
///      Returns index of the closest circle in the vector. 
///      If no circle is found within a threshold, returns -1.
///      </summary>
int findCircleIndex(const vector<Point>& centers, const Point& point);

///      <summary>
///      Callback function for mouse events.
///      </summary>
void onMouse(int event, int x, int y, int flags, void* userdata);

///      <summary>
///      Checks if the folder has an iamge with the same name
///      </summary>
bool fileExists(const string& filename);