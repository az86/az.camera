#include <cstdio>
#include <thread>
#include <chrono>

#include "../publish/include/mgl.CyAPI.h"
#pragma comment(lib, "../publish/lib/az.camera.CoreCyVideoSource.lib")
///ע������Ŀ�ļ������� ��������->�����¼�->Ԥ�������¼�->������ �������ÿ�����������dll

#include <opencv2/opencv.hpp> // ��Ϊ��cv::imshow("mgl", m)��ʾͼ��


void play(int index)
{
    char winName[64];
    sprintf_s(winName,64, "%d", index);
    auto pDev = OpenDevice(index);// �򿪵�һ���豸
    VideoStart(pDev);
    // ѭ����ȡ50֡����
    constexpr auto frames = 500;
    for (int i = 0; i < frames; i++)
    {
        auto frame = QuaryFrame(pDev);
        auto width = GetImgWidth(frame);
        auto height = GetImgHeight(frame);
        auto img = GetImg(frame); // ��ͼ������֡�л�ȡRGB����
        auto fps = GetFPS(pDev);
        // ��ʾͼ������
        cv::Mat m(height, width, CV_8UC3, img);
        cv::imshow(winName, m);
        cv::waitKey(1);
        printf("\b\r %3d: image got, width=%d, height=%d, FPS=%f", i + 1, width, height, fps);

        //���������ͼ�����ݣ������ڴ�й¶
        RetriveFrame(frame);
    }
    VideoStop(pDev);
    CloseDevice(pDev);    //�ر��豸 
}
int main()
{
    //��ȡ���ӵ��豸����
    const auto devCount = GetDeviceCount();
    if (devCount < 1)
    {
        printf("No device found!\n");
        return 0;
    }
    LoadFirmware(nullptr);
    //���¹̼���Ҫ�ȴ��豸��������
    while(GetDeviceCount() < devCount)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::vector<std::shared_ptr<std::thread>> ths;
    for (auto i = 0; i < devCount; i++)
    {
        // ��ȡ���ӵĵ�i���豸����
        constexpr auto descLen = 256;
        char desc[descLen];
        GetDeviceDescrption(0, desc, descLen); //��һ������ָ����ȡ�ڼ����豸����
        printf("device count = %d : %s\n", devCount, desc);
        auto th = std::make_shared<std::thread> (std::bind(play, i));
        ths.push_back(th);
    }

    for (auto th : ths)
    {
        th->join();
    }
    printf("\n press any key to quit...\n");
    getchar();
}