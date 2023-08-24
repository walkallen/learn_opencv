
#include <opencv2/opencv.hpp>

using cv::GaussianBlur;
using cv::Mat;
using std::cout;
using std::endl;

using millis = std::chrono::milliseconds;
using micros = std::chrono::microseconds;

static const bool DEBUG = false;
static const bool INFO = true;

long long gaussian_opencv(int ksize, double sigma, cv::Mat &img, cv::Mat &smoothed)
{


    auto start = std::chrono::high_resolution_clock::now();

    // int ksize = 5;
    // int sigma = 3;

    GaussianBlur(img, smoothed, cv::Size(ksize, ksize), sigma, sigma, cv::BORDER_REPLICATE);

    auto stop = std::chrono::high_resolution_clock::now();
    auto opencv_time = std::chrono::duration_cast<micros>(stop - start).count();

    if (INFO)
        printf("opencv gaussian filter took %ld microseconds \n", opencv_time);

    if (DEBUG)
    {
        cout << "smoothed (grad_x) = \n"
             << format(smoothed, cv::Formatter::FMT_C) << ";" << endl
             << endl
             << endl;
    }

    return opencv_time;
}

int main()
{
    long long consumeTime = 0;
    int kernelSize = 21;
    double sigma = 4.3;
    int TEST_NUM = 30;

    Mat smoothed;



    std::string filename = "data/lena.jpg";

    cout << "image file is " << filename << endl;

    // Mat img = imread(filename);
    Mat img = imread(filename, cv::IMREAD_GRAYSCALE);

    for(int i=0;i<TEST_NUM;++i)
        consumeTime = gaussian_opencv(kernelSize, sigma, img, smoothed);
}
