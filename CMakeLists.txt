cmake_minimum_required(VERSION 3.1)

set(OpenCV_DIR "/home/intel/Downloads/opencv-4.8.0/build")


if(WIN32)




set(OpenCV_DIR "D:/opencv-4.5.5/build_release")
# set(OpenCV_DIR "D:/opencv-4.5.5/build_release_disable_intrinsics")

# set(OpenCV_DIR "D:/opencv-4.5.5/build_debug")
# set(OpenCV_DIR "D:/opencv-4.5.5/build_debug_disable_intrinsics")



# set(OpenCV_DIR "C:/Users/RS/Downloads/opencv_4.5.5/sources/build_release")

# set(OpenCV_DIR "C:/Users/RS/Downloads/opencv_4.5.5/sources/build_release_disable_intrinsics")

# set(OpenCV_DIR "C:/Users/RS/Downloads/opencv_4.5.5/sources/build_debug")
# set(OpenCV_DIR "C:/Users/RS/Downloads/opencv_4.5.5/sources/build_debug_disable_intrinsics")
# set(OpenCV_DIR "C:/Users/RS/Downloads/opencv_4.5.5/sources/build_debug_disable_avx_sse_code")


set(ITT_DIR "C:/Program Files (x86)/Intel/oneAPI/advisor/latest/lib64")
include_directories(
    "C:/Program Files (x86)/Intel/oneAPI/advisor/latest/include"
    ${OpenCV_DIR}
)





# set(opencv_debug_lib_dir "${OpenCV_DIR}/bin/Debug")
# set(opencv_include       "${OpenCV_DIR}/../include")
# find_library(CV_WORLD opencv_world455d PATHS ${opencv_debug_lib_dir})
# include_directories( ${opencv_include} )
# include_directories( ${OpenCV_INCLUDE_DIRS} )
# include_directories( ${OpenCV_DIR} )


endif()



project ("learn_opencv" LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})

message(STATUS "suhao CMAKE_SOURCE_DIR is  ${CMAKE_SOURCE_DIR}  ")

find_package( OpenCV REQUIRED )

if(WIN32)
find_library(ITT_NOTIFY libittnotify PATHS ${ITT_DIR})
endif()

message(STATUS "suhao libs is  ${OpenCV_LIBS}  ")


add_executable( v01_AddingImages    v01_AddingImages.cpp )
add_executable( v02_univ_intrin     v02_univ_intrin.cpp )
add_executable( v03_intrin          v03_intrin.cpp )
add_executable( v04_intrin_auto     v04_intrin_auto.cpp )
add_executable( v05_gauss           v05_gauss.cpp )
add_executable( v06_warp            v06_warp.cpp  )


target_compile_options(v02_univ_intrin  PRIVATE -mavx512f)
target_compile_options(v03_intrin       PRIVATE -mavx2)
target_compile_options(v04_intrin_auto  PRIVATE -mavx2)


target_link_libraries( v01_AddingImages ${OpenCV_LIBS}   )
target_link_libraries( v02_univ_intrin  ${OpenCV_LIBS}   )
target_link_libraries( v03_intrin       ${OpenCV_LIBS}   )
target_link_libraries( v04_intrin_auto  ${OpenCV_LIBS}   )
target_link_libraries( v05_gauss        ${OpenCV_LIBS}   )
target_link_libraries( v06_warp         ${OpenCV_LIBS} ${ITT_NOTIFY}   )

add_custom_target(run02 ./v02_univ_intrin ../data/lena.jpg )



if(WIN32)
set_target_properties(  v01_AddingImages 
                        v06_warp
                        PROPERTIES VS_DEBUGGER_ENVIRONMENT  "PATH=%PATH%;${OpenCV_DIR}/bin/Release")


set_target_properties(v06_warp PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_SOURCE_DIR}/data/color_4288.jpg" )

endif()