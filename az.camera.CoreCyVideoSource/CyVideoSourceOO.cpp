#include <functional>
#include "CyVideoSourceOO.h"

CyVideoSourceOO::CyVideoSourceOO()
    : m_isRecvRun(false)
    , m_isCvtRun(false)
{
}


CyVideoSourceOO::~CyVideoSourceOO()
{
    m_isCvtRun = false;
    if (m_cvtThd != nullptr)
        m_cvtThd->join();
    m_isRecvRun = false;
    if (m_recvThd != nullptr)
        m_recvThd->join();

}

cv::Mat CyVideoSourceOO::GetFrame()
{
    return m_rgbFrames.pop();
}

int CyVideoSourceOO::DeviceCount()
{
    return CCyUSBDevice().DeviceCount();
}

void CyVideoSourceOO::DeviceDescrption(const int & index, char* pDst, const size_t& dstLen)
{
    CCyUSBDevice local;
    local.Open(index);
    strcpy_s(pDst, dstLen, local.FriendlyName);
}

bool CyVideoSourceOO::Open(int index)
{
    m_USBDevice = std::make_shared<CCyUSBDevice>();
    m_USBDevice->Open(index);
    m_isCvtRun = m_isRecvRun = m_USBDevice->IsOpen();
    if (m_isRecvRun)
    {
        m_recvThd = std::make_shared<std::thread>(std::bind(&CyVideoSourceOO::CoreRecv, this));
        m_cvtThd = std::make_shared<std::thread>(std::bind(&CyVideoSourceOO::CoreCVT, this));
    }
    return m_isRecvRun;
}

void CyVideoSourceOO::CoreRecv()
{
    constexpr int frameLen = 2592 * 1944 + 256 + 80;
    auto pframe = new unsigned char[frameLen];
    constexpr auto bufLen = 1024 * 1024;
    // std::thread([&isRun]() {getchar(); isRun = false; });
    long sumRecv = 0;
    while (m_isRecvRun)
    {
        auto pbuf = pframe + sumRecv;
        long recv = bufLen;
        m_USBDevice->BulkInEndPt->XferData(pbuf, recv);
        sumRecv += recv;
        if (recv % 512 != 0)
        {
            FrameDesc frameDesc{ pframe, sumRecv };
            m_rawFrames.push(frameDesc);
            pframe = new unsigned char[frameLen * 3];
            sumRecv = 0;
        }
    }
}

void CyVideoSourceOO::CoreCVT()
{

    while(m_isCvtRun)
    {
        auto frameDesc = m_rawFrames.pop();
        auto & pframe = frameDesc.m_frame;
        auto & size = frameDesc.m_frameSize;
        //printf("one frame got, %d! img 2592*1944 = %d, diff is %d\n,", size, 2592 * 1944, size - 2592 * 1944);
        HeadInfo* pheader = (HeadInfo*)(pframe + size - HeadInfo::headSize);
        //printf("check0=%x, check1=%x, width=%d, height=%d, pixelCount=%d, index=%d\n", pheader->check0, pheader->check1, pheader->width, pheader->height, pheader->pixelCount, pheader->index);
        cv::Mat i(pheader->height, pheader->width, CV_8UC1, pframe);
        cv::Mat o(pheader->height, pheader->width, CV_8UC3);
        cv::cvtColor(i, o, CV_BayerRG2RGB);
        m_rgbFrames.push(o);
        delete[] pframe;
    }

}
