#include <cstdio>
#include "CyVideoSourceOO.h"

typedef void * PDevice;

int GetDeviceCount()
{
    return CyVideoSourceOO::DeviceCount();
}

void GetDeviceDescrption(const int index, char* pDst, const size_t dstLen)
{
    CyVideoSourceOO::DeviceDescrption(index, pDst, dstLen);
}

PDevice OpenDevice(const int deviceIndex)
{
    auto pDev = new CyVideoSourceOO();
    if (pDev->Open(deviceIndex))
    {
        return static_cast<void *>(pDev);
    }
    delete pDev;
    return nullptr;
}
unsigned char * QuaryFrame(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    auto pmat = new cv::Mat(lpDev->GetFrame());
    return reinterpret_cast<unsigned char *>(pmat);
}

int GetImgWidth(unsigned char * pframe)
{
    auto pmat = reinterpret_cast<cv::Mat*>(pframe);
    return pmat->cols;
}

int GetImgHeight(unsigned char * pframe)
{
    auto pmat = reinterpret_cast<cv::Mat*>(pframe);
    return pmat->rows;
}

unsigned char * GetImg(unsigned char * pframe)
{
    auto pmat = reinterpret_cast<cv::Mat*>(pframe);
    return pmat->data;
}

void RetriveFrame(unsigned char *pframe)
{
    auto pmat = reinterpret_cast<cv::Mat*>(pframe);
    delete pmat;
}

void CloseDevice(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    delete lpDev;
}

bool VideoStart(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    return lpDev->Start();
}

void VideoStop(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    lpDev->Stop();
}

float GetFPS(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    return lpDev->FPS();
}

bool SetParameter(PDevice pDev, unsigned char * param, const size_t paramLen)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    return lpDev->SetParam(param, paramLen);
}