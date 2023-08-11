cmake_minimum_required(VERSION 3.1)

set(OpenCV_DIR "/home/intel/Downloads/opencv-4.8.0/build")



project ("learn_opencv" LANGUAGES CXX)


find_package( OpenCV REQUIRED )


add_executable( v01_AddingImages    v01_AddingImages.cpp )
add_executable( v02_univ_intrin     v02_univ_intrin.cpp )
add_executable( v03_intrin          v03_intrin.cpp )
add_executable( v04_intrin_auto     v04_intrin_auto.cpp )

target_compile_options(v02_univ_intrin  PRIVATE -mavx512f)
target_compile_options(v03_intrin       PRIVATE -mavx2)
target_compile_options(v04_intrin_auto  PRIVATE -mavx2)


target_link_libraries( v01_AddingImages ${OpenCV_LIBS}   )
target_link_libraries( v02_univ_intrin ${OpenCV_LIBS}   )
target_link_libraries( v03_intrin ${OpenCV_LIBS}   )
target_link_libraries( v04_intrin_auto ${OpenCV_LIBS}   )

add_custom_target(run02 ./v02_univ_intrin ../data/lena.jpg )


