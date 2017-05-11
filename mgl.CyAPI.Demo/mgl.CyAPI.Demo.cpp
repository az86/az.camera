#include <cstdio>

#include "../publish/include/mgl.CyAPI.h"
#pragma comment(lib, "../publish/lib/az.camera.CoreCyVideoSource.lib")
///ע������Ŀ�ļ������� ��������->�����¼�->Ԥ�������¼�->������ �������ÿ�����������dll

#include <opencv2/opencv.hpp> // ��Ϊ��cv::imshow("mgl", m)��ʾͼ��

int main()
{
    //��ȡ���ӵ��豸����
    const auto devCount = GetDeviceCount();
    if (devCount < 1)
    {
        printf("No device found!\n");
        return 0;
    }

    // ��ȡ���ӵĵ�1���豸����
    constexpr auto descLen = 256;
    char desc[descLen];
    GetDeviceDescrption(0, desc, descLen); //��һ������ָ����ȡ�ڼ����豸����
    printf("device count = %d : %s\n", devCount, desc);

    
    auto pDev = OpenDevice(0);// �򿪵�һ���豸
    VideoStart(pDev);
    // ѭ����ȡ50֡����
    constexpr auto frames = 500;
    for(int i = 0; i < frames; i++)
    {
        auto frame = QuaryFrame(pDev);
        auto width = GetImgWidth(frame);
        auto height = GetImgHeight(frame);
        auto img = GetImg(frame); // ��ͼ������֡�л�ȡRGB����
        auto fps = GetFPS(pDev);
        // ��ʾͼ������
        cv::Mat m(height, width, CV_8UC3, img);
        cv::imshow("mgl", m);
        cv::waitKey(1);
        printf("\b\r %3d: image got, width=%d, height=%d, FPS=%f", i + 1, width, height, fps);

        //���������ͼ�����ݣ������ڴ�й¶
        RetriveFrame(frame);
    }
    VideoStop(pDev);
    CloseDevice(pDev);    //�ر��豸 
    printf("\n press any key to quit...\n");
    getchar();
}