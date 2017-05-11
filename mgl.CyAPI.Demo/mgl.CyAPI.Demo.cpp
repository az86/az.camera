#include <cstdio>

#include "../publish/include/mgl.CyAPI.h"
#pragma comment(lib, "../publish/lib/az.camera.CoreCyVideoSource.lib")
///注意在项目文件属性中 配置属性->生成事件->预先生成事件->命令行 中有设置拷贝运行所需dll

#include <opencv2/opencv.hpp> // 仅为了cv::imshow("mgl", m)显示图像

int main()
{
    //获取连接的设备数量
    const auto devCount = GetDeviceCount();
    if (devCount < 1)
    {
        printf("No device found!\n");
        return 0;
    }

    // 获取连接的第1个设备描述
    constexpr auto descLen = 256;
    char desc[descLen];
    GetDeviceDescrption(0, desc, descLen); //第一个参数指定获取第几个设备描述
    printf("device count = %d : %s\n", devCount, desc);

    
    auto pDev = OpenDevice(0);// 打开第一个设备
    VideoStart(pDev);
    // 循环获取50帧数据
    constexpr auto frames = 500;
    for(int i = 0; i < frames; i++)
    {
        auto frame = QuaryFrame(pDev);
        auto width = GetImgWidth(frame);
        auto height = GetImgHeight(frame);
        auto img = GetImg(frame); // 从图像数据帧中获取RGB数据
        auto fps = GetFPS(pDev);
        // 显示图像数据
        cv::Mat m(height, width, CV_8UC3, img);
        cv::imshow("mgl", m);
        cv::waitKey(1);
        printf("\b\r %3d: image got, width=%d, height=%d, FPS=%f", i + 1, width, height, fps);

        //还回用完的图像数据，避免内存泄露
        RetriveFrame(frame);
    }
    VideoStop(pDev);
    CloseDevice(pDev);    //关闭设备 
    printf("\n press any key to quit...\n");
    getchar();
}