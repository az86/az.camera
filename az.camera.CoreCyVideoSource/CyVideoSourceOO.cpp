#include <functional>
#include <vector>
#include <mutex>
#include "CyVideoSourceOO.h"

CyVideoSourceOO::CyVideoSourceOO()
    : m_isRecvRun(false)
    , m_isCvtRun(false)
    , m_fps(0)
    , m_tmpClock(0)
{
}


CyVideoSourceOO::~CyVideoSourceOO()
{
    Stop();
}

cv::Mat CyVideoSourceOO::GetFrame()
{
    return m_rgbFrames.pop();
}

int CyVideoSourceOO::DeviceCount()
{
    return AzUSBDevice().DeviceCount();
}

void CyVideoSourceOO::DeviceDescrption(const int & index, char* pDst, const size_t& dstLen)
{
    AzUSBDevice local;
    local.Open(index);
    strcpy_s(pDst, dstLen, local.FriendlyName);
    local.Close();
}

bool CyVideoSourceOO::SetParam(unsigned char reqCode, unsigned short value, unsigned short index, unsigned char * param, const size_t& paramLen)
{
    static std::mutex logMutex;
    logMutex.lock();
    printf("dev [%p] set param: req: 0x%02x, value: 0x%04x, index: 0x%04x, param: %s, length: %u ", this, reqCode, value, index, param, paramLen);
    if (!m_USBDevice->IsOpen())
        return false;
 /*   auto state = m_isRecvRun;
    if (state == true)
        Stop();*/
    auto ept = m_USBDevice->ControlEndPt;
    ept->Target = TGT_DEVICE;
    ept->ReqType = REQ_VENDOR;
    ept->Direction = DIR_TO_DEVICE;
    ept->ReqCode = reqCode;// 0x05;
    ept->Value = value;// 1;
    ept->Index = index;// 0;
    long len = paramLen;
    auto r = ept->XferData(param, len);
    logMutex.unlock();
    //if (state == true)
    //    Start();
    printf("%s!\n", r ? "ok" : "failed");
    return r;
}

float CyVideoSourceOO::FPS() const
{
    return m_fps;
}

bool CyVideoSourceOO::LoadDeviceFirmware()
{
    STARTUPINFOA info = { 0 };
    PROCESS_INFORMATION infor = { 0 };
    CreateProcessA("az.CyControl.dotNet.exe", nullptr, nullptr, nullptr, true, NORMAL_PRIORITY_CLASS, NULL, NULL, &info, &infor);
    WaitForSingleObject(infor.hProcess, INFINITE);
    CloseHandle(infor.hProcess);
    CloseHandle(infor.hThread);
    return true;
}

bool CyVideoSourceOO::Open(int index)
{
    m_USBDevice = std::make_shared<AzUSBDevice>();
    m_USBDevice->Open(index);
    return m_USBDevice->IsOpen();
}

bool CyVideoSourceOO::Start()
{
    if (m_USBDevice->IsOpen())
    {
        m_isCvtRun = m_isRecvRun = true;
        m_recvThd = std::make_shared<std::thread>(std::bind(&CyVideoSourceOO::CoreRecv, this));
        m_cvtThd = std::make_shared<std::thread>(std::bind(&CyVideoSourceOO::CoreCVT, this));
    }
    return m_USBDevice->IsOpen();
}

void CyVideoSourceOO::Stop()
{
    m_isCvtRun = false;
    if (m_cvtThd != nullptr)
    {
        m_cvtThd->join();
        m_cvtThd.reset();
    }
    m_isRecvRun = false;
    if (m_recvThd != nullptr)
    {
        m_recvThd->join();
        m_recvThd.reset();
    }

}

ushort CyVideoSourceOO::CoreGetProductID()
{
    return m_USBDevice->ProductID;
}

void CyVideoSourceOO::CoreRecv()
{
    constexpr int maxFrameLen = 2592 * 1944 + 256 + 80;
    auto pframe = new unsigned char[maxFrameLen];
    const auto bufLen = m_USBDevice->BulkInEndPt->MaxPktSize * 1024;
    constexpr auto queueSize = 64;
    OVERLAPPED ovs[queueSize] = { 0 };
    std::shared_ptr<unsigned char> bufs[queueSize];
    unsigned char * contexts[queueSize];
    for (auto i = 0; i < queueSize; i++)
    {
        bufs[i] = std::shared_ptr<unsigned char>(new unsigned char[bufLen], [](auto ptr) {delete[]ptr; });
        ovs[i].hEvent = CreateEventA(nullptr, false, false, nullptr);
        contexts[i] = m_USBDevice->BulkInEndPt->BeginDataXfer(bufs[i].get(), bufLen, ovs + i);
    }
    auto pbegin = pframe;
    auto pend = pframe + maxFrameLen;
    while (m_isRecvRun)
    {
        for (auto i = 0; i != queueSize; i++)
        {
            if (m_USBDevice->BulkInEndPt->WaitForXfer(ovs + i, 1000))
            {
                long len = 0;
                m_USBDevice->BulkInEndPt->FinishDataXfer(bufs[i].get(), len, ovs + i, contexts[i]);
                if (pbegin + len <= pend)
                {
                    memcpy(pbegin, bufs[i].get(), len);
                    pbegin += len;
                }
                else
                {
#ifdef _DEBUG
//                    printf("bad img data over stack\n");
#endif
                    memset(pframe, 0, maxFrameLen);
                    pbegin = pframe;

                }
                contexts[i] = m_USBDevice->BulkInEndPt->BeginDataXfer(bufs[i].get(), bufLen, ovs + i);

                if (len % 512 != 0)
                {
                    auto clk = clock();
                    m_fps = 1000.0f / (clk - m_tmpClock);
                    m_tmpClock = clk;
                    FrameDesc frameDesc{ pframe, pbegin - pframe };
                    //printf("/n%d, %d\n", sumRecv, frameLen);
                    if (frameDesc.m_frameSize > 0)
                    {
                        m_rawFrames.push(frameDesc);
                        pframe = new unsigned char[maxFrameLen];
                    }
                    memset(pframe, 0, maxFrameLen);
                    pbegin = pframe;
                    pend = pframe + maxFrameLen;
                }
            }

        }
    }
    for (auto i = 0; i != queueSize; i++)
    {
        long len = 0;
        m_USBDevice->BulkInEndPt->FinishDataXfer(bufs[i].get(), len, ovs + i, contexts[i]);
        CloseHandle(ovs[i].hEvent);
    }
	delete[] pframe;
}

void CyVideoSourceOO::CoreCVT()
{

    while (m_isCvtRun)
    {
        auto frameDesc = m_rawFrames.pop();
        auto & pframe = frameDesc.m_frame;
        auto & size = frameDesc.m_frameSize;
        //printf("one frame got, %d! img 2592*1944 = %d, diff is %d\n,", size, 2592 * 1944, size - 2592 * 1944);
        HeadInfo* pheader = (HeadInfo*)(pframe + size - HeadInfo::headSize);
        if ((unsigned)size < pheader->pixelCount + pheader->headSize)
        {
#ifdef _DEBUG
 //           printf("bad img data lost\n");
#endif
            delete[] pframe;
            continue;
        }
        //printf("check0=%x, check1=%x, width=%d, height=%d, pixelCount=%d, index=%d\n", pheader->check0, pheader->check1, pheader->width, pheader->height, pheader->pixelCount, pheader->index);
        cv::Mat i(pheader->height, pheader->width, CV_8UC1, pframe);
        cv::Mat o(pheader->height, pheader->width, CV_8UC3);
        cv::cvtColor(i, o, CV_BayerRG2RGB);

        /// gay mode
        //cv::Mat o(pheader->height, pheader->width, CV_8UC1);
        //cv::cvtColor(i, o, CV_BayerBG2GRAY);
        m_rgbFrames.push(o);
        delete[] pframe;
    }
}
