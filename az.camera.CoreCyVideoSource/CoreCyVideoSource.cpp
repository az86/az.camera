#include <cstdio>
#include "CyVideoSourceOO.h"
#include <CommandConfig.h>

/////////////////////////////////////////////////////////////
// for halcon
// �������Ŀ¼�з���HALCON-17.12-Progress�����а���halcon17��ͷ�ļ���
// ͷ�ļ���������algorithmrt.h�б�ʹ�ã��俪����δ�ṩ�����Ͷ���
#include <HalconCpp.h>
using namespace HalconCpp;
#include "../algorithmrt/algorithmrt.h"
#pragma comment(lib, "../algorithmrt/algorithmrt.lib")
#pragma comment(lib, "HalconCpp.lib")
#pragma pack(push,1)
struct CycleCenterInfo
{
	CycleCenterInfo():mec_vecPose(1) {}
	HTuple m_cameraParam;		//����: ������ڲ�
	HTupleVector mec_vecPose;	// {eTupleVector,Dim=1} ���������λ��
	HTuple m_rowFront;			// �����ǰ��Բ�����꼰Բ�ľ���
	HTuple m_colFront;			// �����ǰ��Բ������
	HTuple m_distanceF;			// �����ǰ��Բ�ľ���
	HTuple m_rowBehind;			// �����ǰ��Բ�����꼰Բ�ľ���
	HTuple m_colBehind;			// �����ǰ��Բ������
	HTuple m_distanceB;			// �����ǰ��Բ�ľ���
};
#pragma pack(pop)
/////////////////////////////////////////////////////////////


void GetAllTargetAz(unsigned char *pframe, HTuple hv_CameraParam, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecPose, HTuple *hv_RowFront, HTuple *hv_ColFront, HTuple *hv_DistanceF, HTuple *hv_RowBehind, HTuple *hv_ColBehind, HTuple *hv_DistanceB)
{
	auto pmat = reinterpret_cast<cv::Mat*>(pframe);
	HImage ho_Image;
	GenImage1(&ho_Image, "byte", pmat->cols, pmat->rows, (Hlong)pmat->data);
	GetAllTarget(ho_Image, hv_CameraParam, hvec_VecPose, hv_RowFront, hv_ColFront, hv_DistanceF, hv_RowBehind, hv_ColBehind, hv_DistanceB);
}

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
unsigned char * QuaryFrame(PDevice pDev, CycleCenterInfo &cci)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    auto pmat = new cv::Mat(lpDev->GetFrame());
	auto pimg = reinterpret_cast<unsigned char *>(pmat);
	GetAllTargetAz(pimg, cci.m_cameraParam, &cci.mec_vecPose, &cci.m_rowFront, &cci.m_colFront, &cci.m_distanceF, &cci.m_rowBehind, &cci.m_colBehind, &cci.m_distanceB);
    return pimg;
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
bool SetSensor1080P(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    auto rval = true;
    auto &ins  = CommandConfig::Instance();
    for (auto &it : CommandConfig::Instance().configs["SET 1080P"])
    {
        rval = rval && lpDev->SetParam(it.reqCode, it.value, it.index, nullptr, 0);
    }
    return rval;
}

unsigned short GetProductID(PDevice pDev)
{
    auto lpDev = static_cast<CyVideoSourceOO *>(pDev);
    return lpDev->CoreGetProductID();

}
