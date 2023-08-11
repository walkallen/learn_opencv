// https://mp.weixin.qq.com/s?__biz=MjM5NTE3NjY5MA==&mid=2247484025&idx=1&sn=132d0fc0a242df11bd5b59cd22eaad99&chksm=a6fdcbe4918a42f2dae5c150541b8e243bfe4d70e126813852c0d8b108d37af28e9713a4699e&scene=21#wechat_redirect
// 使用 OpenCV 中的 universal intrinsics 为算法提速 (1)

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/simd_intrinsics.hpp"

using namespace cv;

int main()
{
    const int SIZE = 16;

    float a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float b[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float c[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

#if (CV_SIMD == 1)

    printf("CV_SIMD is defined. \n");
    printf("sizeof(v_float32) is %ld total %ld bits \n", sizeof(v_float32), sizeof(v_float32) * 8);

    int step = v_float32().nlanes; // 得到一个向量可以存储几个 float32
    printf("v_float32().nlanes is %d \n", step);

    for (int i = 0; i < SIZE; i += v_float32().nlanes)
    {
        v_float32 va = vx_load(a+i); //vx_load 可以自动装载最大宽度
        v_float32 vb = vx_load(b+i); 
        v_float32 vc = va*vb;
        vx_store(c+i, vc);
    }

#else

#endif

    // 打印 opencv 基本编译信息
    // std::cout << cv::getBuildInformation().c_str() << std::endl;

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d: %g\n", i, c[i]);
    }
}