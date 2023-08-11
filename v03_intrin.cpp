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

#if (CV_SIMD128 == 1)
    printf("CV_SIMD128 is defined.\n");

    for (int i = 0; i < SIZE; i += 4)
    {
        v_float32x4 va = v_load(a + i); // 从内存 a 装载 4 个 float 到寄存器 va
        v_float32x4 vb = v_load(b + i); // 从内存 b 装载 4 个 float 到寄存器 vb
        v_float32x4 vc = va*vb;         // 通过 c++ 运算符重载实现了向量乘法，4 个 float 一次完成
        v_store(c+i, vc);               // 从寄存器 vc 存储 4 个 float 到内存 c


    }

#endif

#if (CV_SIMD256 == 1)
    printf("CV_SIMD256 is defined.\n");

#endif

#if (CV_SIMD512 == 1)
    printf("CV_SIMD512 is defined.\n");

#endif

    // 打印 opencv 基本编译信息
    // std::cout << cv::getBuildInformation().c_str() << std::endl;

    for(int i=0;i<SIZE;i++){
        printf("%d: %g\n",i,c[i]);
    }
}