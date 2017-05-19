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
    return lpDev->SetParam(0x05, 1, 0, param, paramLen);
}

int SetLED(PDevice pDev, unsigned short value)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    value &= 0x1FF;
    if (lpDev->SetParam(0xB5, 0x009A, value, nullptr, 0))
        return value;
    return 0;
}

bool SetSensorGain(PDevice pDev,unsigned short value)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    if (value > 0x63)
        return false;
    return lpDev->SetParam(0xB4, 0x0035, value, nullptr, 0);
}

bool InitSersor(PDevice pDev)
{
        auto lpDev = static_cast<CyVideoSourceOO *>(pDev);

        auto rval0 = lpDev->SetParam(0xB4, 0x0008, 0x0000, nullptr, 0);
        auto rval1 = lpDev->SetParam(0xB4, 0x0009, 0x00E6, nullptr, 0);
        auto rval2 = lpDev->SetParam(0xB4, 0x000C, 0x0613, nullptr, 0);
        auto rval3 = lpDev->SetParam(0xB4, 0x002B, 0x0008, nullptr, 0);
        auto rval4 = lpDev->SetParam(0xB4, 0x002C, 0x0012, nullptr, 0);
        auto rval5 = lpDev->SetParam(0xB4, 0x002D, 0x000A, nullptr, 0);
        auto rval6 = lpDev->SetParam(0xB4, 0x002E, 0x0008, nullptr, 0);

        return rval0&& rval1&& rval2&&rval3&&rval4&&rval5&&rval6;
}

bool LoadFirmware(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    return lpDev->LoadDeviceFirmware();
}