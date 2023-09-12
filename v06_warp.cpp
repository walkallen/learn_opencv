#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/core/utils/trace.hpp>
//#include <ittnotify.h>
#include "trace_function.hpp"

#define DEBUG

using std::cout;
using std::endl;
using cv::Mat;

//__itt_domain* domain = __itt_domain_create(/*(const wchar_t *)*/ "Example.Domain.Global");
//// Create string handles which associates with the "main" task.
//__itt_string_handle* handle_cv = __itt_string_handle_create(/*(const wchar_t *)*/"cv");


double coeffs[2][3] = { {1.0, 0.5, 0.0}, {0.5, 1.0, 0.0} };

int main(int argc, char **argv)
{
    Trace_function trace_func("suhao");
    //__itt_task_begin(domain, __itt_null, __itt_null, handle_cv);
    //CV_TRACE_FUNCTION();

    printf("Function signature: %s\n", __FUNCSIG__);

    if (argc < 2)
    {
        std::cerr << "No test files given. Pass the path of image files to the cv_dilate." << std::endl;
        return (-1);
    }

    const int TEST_NUM = 2;
    double cv_total_time = 0.0;

    cout << endl
         << endl
         << "This program run dilation on picture " << argv[1] << " for " << TEST_NUM << " times." << endl;
    cout << "Average running time as followed: " << endl;


    cv::setNumThreads(1);

    Mat warp_mat(2, 3, CV_64FC1, coeffs);

    std::string source_path = "../data/color_4288.jpg";

    cv::Mat image;
    try
    {
        image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    }
    catch (cv::Exception &e)
    {
        std::cout << "exception caught: " << e.what() << std::endl;
        return -1;
    }

    cv::Mat res_warp_cv = Mat::zeros(image.rows, image.cols, image.type());;

    for (int i = 0; i < TEST_NUM; i++)
    {
        auto start = std::chrono::steady_clock::now();

        warpAffine(image, res_warp_cv, warp_mat, res_warp_cv.size());

        auto stop = std::chrono::steady_clock::now();
        auto cv_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0;
        cv_total_time += cv_time;
#ifdef DEBUG
        printf("opencv    warp affine took %.3f milliseconds \n", cv_time);
#endif
    }

    //__itt_task_end(domain, __itt_null, __itt_null, handle_cv);


}
