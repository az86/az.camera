#pragma once
#include <windows.h>
#include <CyAPI.h>
#include <memory>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Queue.h"

struct FrameDesc
{
    unsigned char * m_frame;
    long m_frameSize;
};

struct HeadInfo
{
    unsigned short check0;//0x5a5a
    unsigned short check1;//0xa5a5
    unsigned short height;
    unsigned short width;
    unsigned pixelCount;
    unsigned index;
    static constexpr int headSize = 80;
};

class CyVideoSourceOO
{
public:
    CyVideoSourceOO();
    ~CyVideoSourceOO();
    cv::Mat GetFrame();
    bool Open(int index);
    bool Start();
    void Stop();
    static int DeviceCount();
    static void DeviceDescrption(const int & index, char *pDst, const size_t & dstLen);
    bool SetParam(unsigned char * param, const size_t & paramLen);
    float FPS() const;
private:
    void CoreRecv();
    void CoreCVT();
    std::shared_ptr<CCyUSBDevice> m_USBDevice;
    az::queue<FrameDesc> m_rawFrames;
    az::queue<cv::Mat> m_rgbFrames;
    std::shared_ptr<std::thread> m_recvThd;
    std::shared_ptr<std::thread> m_cvtThd;
    bool m_isRecvRun;
    bool m_isCvtRun;
    float m_fps;
    clock_t m_tmpClock;

};
