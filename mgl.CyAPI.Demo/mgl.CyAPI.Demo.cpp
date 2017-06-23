#include <cstdio>
#include <thread>
#include <mutex>
#include <chrono>
#include <tuple>
#include "../publish/include/mgl.CyAPI.h"
#pragma comment(lib, "../publish/lib/az.camera.CoreCyVideoSource.lib")
///注意在项目文件属性中 配置属性->生成事件->预先生成事件->命令行 中有设置拷贝运行所需dll

#include <opencv2/opencv.hpp> // 仅为了cv::imshow("mgl", m)显示图像

char gFPS[256] = { 0 };
std::vector<std::tuple<PDevice, std::mutex*>> gDevs;
std::mutex muVector;
void play(int index, bool *isRun);
void playcmd();

int main()
{
    //获取连接的设备数量
    const auto devCount = GetDeviceCount();
    if (devCount < 1)
    {
        printf("No device found!\n");
        return 0;
    }
    LoadFirmware(nullptr);
    //更新固件后要等待设备重新连接
    while (GetDeviceCount() < devCount)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::vector<std::shared_ptr<std::thread>> ths;
    bool isRun = true;
    for (auto i = 0; i < devCount; i++)
    {
        // 获取连接的第i个设备描述
        constexpr auto descLen = 256;
        char desc[descLen];
        GetDeviceDescrption(0, desc, descLen); //第一个参数指定获取第几个设备描述
        printf("device count = %d : %s\n", devCount, desc);
        auto th = std::make_shared<std::thread>(std::bind(play, i, &isRun));
        ths.push_back(th);
    }


    /*printf("\n press any key to quit...\n");
    getchar();*/
    playcmd();

    isRun = false;
    for (auto th : ths)
    {
        th->join();
    }
}

void play(int index, bool *isRun)
{
    char winName[64];
    sprintf_s(winName, 64, "%d", index);

    std::mutex muDev;
    auto pDev = OpenDevice(index);// 打开第一个设备
    {
        std::lock_guard<std::mutex> lg(muVector);
        gDevs.push_back(std::make_tuple(pDev, &muDev));
    }

    VideoStart(pDev);
    // 循环获取50帧数据
    constexpr auto frames = 500;
    int i = 0;
    while (*isRun)
    {
        muDev.lock();
        auto frame = QuaryFrame(pDev);
        auto width = GetImgWidth(frame);
        auto height = GetImgHeight(frame);
        auto img = GetImg(frame); // 从图像数据帧中获取RGB数据
        auto fps = GetFPS(pDev);
        muDev.unlock();
        // 显示图像数据
        cv::Mat m(height, width, CV_8UC3, img);
        cv::imshow(winName, m);
        cv::waitKey(1);
        sprintf_s(gFPS, " %3d: image got, width=%d, height=%d, FPS=%f", i++, width, height, fps);

        //还回用完的图像数据，避免内存泄露
        RetriveFrame(frame);
    }
    VideoStop(pDev);
    CloseDevice(pDev);    //关闭设备 
}

void playcmd()
{
    printf("input ? for help.\n");
    char buf[256] = { 0 };
    while (true)
    {
        printf(">>>");
        gets_s(buf, 256);
        if (strstr(buf, "fps") == buf)
        {
            printf("%s\n", gFPS);
        }
        else if (strstr(buf, "1080p") == buf)
        {
            std::lock_guard<std::mutex> lckVec(muVector);
            for (auto &dev : gDevs)
            {
                std::lock_guard<std::mutex> lg(*std::get<1>(dev));
                VideoStop(std::get<0>(dev));
                SetSensor1080P(std::get<0>(dev));
                VideoStart(std::get<0>(dev));
            }
        }
        else if (strstr(buf, "gain") == buf)
        {
            std::lock_guard<std::mutex> lckVec(muVector);
            int val;
            sscanf_s(buf, "gain %d", &val);
            for (auto &dev : gDevs)
            {
                std::lock_guard<std::mutex> lg(*std::get<1>(dev));
                SetSensorGain(std::get<0>(dev), val);
            }
        }
        else if (strstr(buf, "led") == buf)
        {
            std::lock_guard<std::mutex> lckVec(muVector);
            int val;
            sscanf_s(buf, "led 0x%x", &val);
            for (auto &dev : gDevs)
            {
                std::lock_guard<std::mutex> lg(*std::get<1>(dev));
                SetLED(std::get<0>(dev), val);
            }
        }
        else if (strstr(buf, "id") == buf)
        {
            std::lock_guard<std::mutex> lckVec(muVector);
            int val;
            sscanf_s(buf, "id %d", &val);
            for (auto &dev : gDevs)
            {
                std::lock_guard<std::mutex> lg(*std::get<1>(dev));
                auto val = GetProductID(std::get<0>(dev));
                printf("device %p:product id is 0x%X\n", std::get<0>(dev), val);
            }
        }
        else if (strcmp(buf, "?") == 0)
        {
            printf("fps:\n\tget fps\n");
            printf("1080p:\n\tset 1080p mode.\n");
            printf("gain [number]:\n\tset gain value.\n");
            printf("led [number]:\n\tset led value.\n");
            printf("id:\n\tget product id value.\n");
            printf("exit:\n\texit the process.\n");
        }
        else if (strcmp(buf, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("bad input! ? for help\n");
        }

    }
}