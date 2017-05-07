#include <windows.h>
#include <thread>
#include <cstdio>
#include <CyAPI.h>
#include <opencv2/opencv.hpp>

//struct HeadInfo
//{
//    unsigned short check0;//0x5a5a
//    unsigned short check1;//0xa5a5
//    unsigned short height;
//    unsigned short width;
//    unsigned pixelCount;
//    unsigned index;
//    static constexpr int headSize = 80;
//};
//void DealFrame(unsigned char * pframe, const long size)
//{
//    printf("one frame got, %d! img 2592*1944 = %d, diff is %d\n,", size, 2592*1944, size- 2592 * 1944 );
//    HeadInfo* pheader = (HeadInfo*)(pframe + size - HeadInfo::headSize);
//    printf("check0=%x, check1=%x, width=%d, height=%d, pixelCount=%d, index=%d\n",
//        pheader->check0, pheader->check1, pheader->width, pheader->height, pheader->pixelCount, pheader->index);
//    cv::Mat i(pheader->height, pheader->width, CV_8UC1, pframe);
//    cv::Mat o(pheader->height, pheader->width, CV_8UC3);
//    cv::cvtColor(i, o, CV_BayerRG2RGB);
//    cv::Mat oo(pheader->height/4, pheader->width/4, CV_8UC3);
//    cv::resize(o, oo, cv::Size(pheader->width / 4, pheader->height / 4));
//    cv::imshow("az", oo);
//    cv::waitKey(1);
//    delete[] pframe;
//}
int main()
{
   // bool isRun = true;
   // 
   // CCyUSBDevice *USBDevice = new CCyUSBDevice(NULL);
   // constexpr int frameLen = 2592 * 1944 + 256+80;
   // auto pframe = new unsigned char[frameLen];
   // constexpr auto bufLen = 1024*1024;
   //// std::thread([&isRun]() {getchar(); isRun = false; });
   // long sumRecv = 0;
   // while (isRun)
   // {
   //     auto pbuf = pframe + sumRecv;
   //     long recv = bufLen;
   //     USBDevice->BulkInEndPt->XferData(pbuf, recv);
   //     sumRecv += recv;
   //     if (recv % 512 != 0)
   //     {
   //         DealFrame(pframe, sumRecv);
   //         pframe = new unsigned char[frameLen * 3];
   //         sumRecv = 0;
   //     }
   // }

    return 0;
}
