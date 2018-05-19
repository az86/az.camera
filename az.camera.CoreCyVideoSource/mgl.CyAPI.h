#pragma once

#include <HalconCpp.h>
using namespace HalconCpp;
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


////////////////////////////////////////////////////////////////
/// �������·��APIͷ�ļ���δ����Ȩ��ֹʹ�á�
/// ���ߣ������������
/// ���л��� windows 7�����ϰ汾, 32bit.
/// �������� visual studio 2015.
/// Version: 1.0
/// ////////////////////////////////////////////////////////////

typedef void * PDevice;

////////////////////////////////////////////////////////////////
/// <Function> GetDeviceCount </Function>
/// <Description> ��ȡ���ӵ��豸����</Description>
/// <Return>���ӵ��豸����</Return>
////////////////////////////////////////////////////////////////
extern int GetDeviceCount();

////////////////////////////////////////////////////////////////
/// <Function> GetDeviceDescrption </Function>
/// <Description> ��ȡ�豸����</Description>
/// <index> �豸������ </index>
/// <pDst> ������������� </pDst>
/// <dstLen> ������������鳤�� <dstLen/>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void GetDeviceDescrption(const int index, char* pDst, const size_t dstLen);

////////////////////////////////////////////////////////////////
/// <Function> OpenDevice </Function>
/// <Description> ���豸</Description>
/// <index> �豸������ </index>
/// <Return>�򿪵��豸����, ���ʧ�ܷ���nullptr</Return>
////////////////////////////////////////////////////////////////
extern PDevice OpenDevice(const int deviceIndex);

////////////////////////////////////////////////////////////////
/// <Function> QuaryFrame </Function>
/// <Description> ��ȡһ֡ͼ�����ݰ���ʹ����Ϻ���Ҫ����RetriveFrame����ͼ���ڴ棬�����ڴ�й¶</Description>
/// <pDev> �豸���� </pDev>
/// <cci> Բ����Ϣ </cci>
/// <Return>ͼ�����ݰ�</Return>
////////////////////////////////////////////////////////////////
extern unsigned char * QuaryFrame(PDevice pDev, CycleCenterInfo &cci);

////////////////////////////////////////////////////////////////
/// <Function> GetImgWidth </Function>
/// <Description> ��һ֡ͼ�����ݰ��л�ȡͼ��Ŀ��</Description>
/// <Return>ͼ��Ŀ��</Return>
////////////////////////////////////////////////////////////////
extern int GetImgWidth(unsigned char * pframe);

////////////////////////////////////////////////////////////////
/// <Function> GetImgHeight </Function>
/// <Description> ��һ֡ͼ�����ݰ��л�ȡͼ��ĸ߶�</Description>
/// <Return>ͼ��ĸ߶�</Return>
////////////////////////////////////////////////////////////////
extern int GetImgHeight(unsigned char * pframe);

////////////////////////////////////////////////////////////////
/// <Function> GetImg </Function>
/// <Description> ��һ֡ͼ�����ݰ��л�ȡͼ������</Description>
/// <Return>ͼ������</Return>
////////////////////////////////////////////////////////////////
extern unsigned char * GetImg(unsigned char * pframe);


////////////////////////////////////////////////////////////////
/// <Function> RetriveFrame </Function>
/// <Description> ��ͼ���ڴ滹��ͼ���ȡ���񣬱����ڴ�й¶</Description>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void RetriveFrame(unsigned char *pframe);

////////////////////////////////////////////////////////////////
/// <Function> CloseDevice </Function>
/// <Description> �ر��豸</Description>
/// <pDev> �豸���� </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void CloseDevice(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> VideoStart </Function>
/// <Description> ��ʼ����ͼ��</Description>
/// <pDev> �豸���� </pDev>
/// <Return>true����ɹ�������ʧ��</Return>
////////////////////////////////////////////////////////////////
extern bool VideoStart(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> VideoStop </Function>
/// <Description> ֹͣ����ͼ��</Description>
/// <pDev> �豸���� </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void VideoStop(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> GetFPS </Function>
/// <Description> ��ȡ֡��</Description>
/// <pDev> �豸���� </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern float GetFPS(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> SetParameter </Function>
/// <Description> ���ò���</Description>
/// <pDev> �豸���� </pDev>
/// <param> �������� <param/>
/// <paramLen> �������鳤�� <paramLen/>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern bool SetParameter(PDevice pDev, unsigned char * param, const size_t paramLen);

////////////////////////////////////////////////////////////////
/// <Function> SetLED </Function>
/// <Description> ����LED</Description>
/// <pDev> �豸���� </pDev>
/// <value> ��������ĵ�8λ����8��620nm��,��������ĸ�8λ��������1��850nm�Ƶģ������ǿ��Ե��Եġ�����8λ = 0xF0ʱ��850nm������ģ�����8λ = 0xF1ʱ��850nm���Ǳ�����������������һ�㣬����8λ = 0xF2ʱ��850nm��������˫������һ�㣬����8λ = 0xFEʱ��850nm���Ƿǳ����ģ�����8λ = 0xFFʱ��850nm���������ġ�<value/>
/// <Return>�ɹ� true������false</Return>
////////////////////////////////////////////////////////////////
extern int SetLED(PDevice pDev, unsigned short value);

////////////////////////////////////////////////////////////////
/// <Function> SetSensorGain </Function>
/// <Description> �����������ֵ</Description>
/// <pDev> �豸���� </pDev>
/// <value> ����ֵ��Ĭ��ֵΪ0x0008�����0x0063<value/>
/// <Return>�ɹ� true������false</Return>
////////////////////////////////////////////////////////////////
extern bool SetSensorGain(PDevice pDev, unsigned short value);

////////////////////////////////////////////////////////////////
/// <Function> InitSersor </Function>
/// <Description> ��ʼ�����</Description>
/// <pDev> �豸���� </pDev>
/// <Return>�ɹ� true������false</Return>
////////////////////////////////////////////////////////////////
extern bool InitSersor(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> LoadFirmware </Function>
/// <Description> ���¹̼�</Description>
/// <pDev> �豸���� </pDev>
/// <Return>�ɹ� true������false</Return>
////////////////////////////////////////////////////////////////
extern bool LoadFirmware(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> SetSensor1080P </Function>
/// <Description> ����1080Pģʽ</Description>
/// <pDev> �豸���� </pDev>
/// <Return>�ɹ� true������false</Return>
////////////////////////////////////////////////////////////////
extern bool SetSensor1080P(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> GetProductID </Function>
/// <Description> ��ȡ�豸id</Description>
/// <pDev> �豸���� </pDev>
/// <Return>Product ID</Return>
////////////////////////////////////////////////////////////////
extern unsigned short GetProductID(PDevice pDev);
