#pragma once

#include <HalconCpp.h>
using namespace HalconCpp;
#pragma pack(push,1)
struct CycleCenterInfo
{
	CycleCenterInfo():mec_vecPose(1) {}
	HTuple m_cameraParam;		//输入: 摄像机内参
	HTupleVector mec_vecPose;	// {eTupleVector,Dim=1} 输出的所有位姿
	HTuple m_rowFront;			// 输出的前靶圆心坐标及圆心距离
	HTuple m_colFront;			// 输出的前靶圆心坐标
	HTuple m_distanceF;			// 输出的前靶圆心距离
	HTuple m_rowBehind;			// 输出的前靶圆心坐标及圆心距离
	HTuple m_colBehind;			// 输出的前靶圆心坐标
	HTuple m_distanceB;			// 输出的前靶圆心距离
};
#pragma pack(pop)


////////////////////////////////////////////////////////////////
/// 马国良电路板API头文件，未经授权禁止使用。
/// 作者：马国梁，孙奇
/// 运行环境 windows 7及以上版本, 32bit.
/// 开发环境 visual studio 2015.
/// Version: 1.0
/// ////////////////////////////////////////////////////////////

typedef void * PDevice;

////////////////////////////////////////////////////////////////
/// <Function> GetDeviceCount </Function>
/// <Description> 获取连接的设备数量</Description>
/// <Return>连接的设备数量</Return>
////////////////////////////////////////////////////////////////
extern int GetDeviceCount();

////////////////////////////////////////////////////////////////
/// <Function> GetDeviceDescrption </Function>
/// <Description> 获取设备描述</Description>
/// <index> 设备的索引 </index>
/// <pDst> 存放描述的数组 </pDst>
/// <dstLen> 存放描述的数组长度 <dstLen/>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void GetDeviceDescrption(const int index, char* pDst, const size_t dstLen);

////////////////////////////////////////////////////////////////
/// <Function> OpenDevice </Function>
/// <Description> 打开设备</Description>
/// <index> 设备的索引 </index>
/// <Return>打开的设备对象, 如果失败返回nullptr</Return>
////////////////////////////////////////////////////////////////
extern PDevice OpenDevice(const int deviceIndex);

////////////////////////////////////////////////////////////////
/// <Function> QuaryFrame </Function>
/// <Description> 获取一帧图像数据包，使用完毕后需要调用RetriveFrame销毁图像内存，避免内存泄露</Description>
/// <pDev> 设备对象 </pDev>
/// <cci> 圆心信息 </cci>
/// <Return>图像数据包</Return>
////////////////////////////////////////////////////////////////
extern unsigned char * QuaryFrame(PDevice pDev, CycleCenterInfo &cci);

////////////////////////////////////////////////////////////////
/// <Function> GetImgWidth </Function>
/// <Description> 从一帧图像数据包中获取图像的宽度</Description>
/// <Return>图像的宽度</Return>
////////////////////////////////////////////////////////////////
extern int GetImgWidth(unsigned char * pframe);

////////////////////////////////////////////////////////////////
/// <Function> GetImgHeight </Function>
/// <Description> 从一帧图像数据包中获取图像的高度</Description>
/// <Return>图像的高度</Return>
////////////////////////////////////////////////////////////////
extern int GetImgHeight(unsigned char * pframe);

////////////////////////////////////////////////////////////////
/// <Function> GetImg </Function>
/// <Description> 从一帧图像数据包中获取图像数据</Description>
/// <Return>图像数据</Return>
////////////////////////////////////////////////////////////////
extern unsigned char * GetImg(unsigned char * pframe);


////////////////////////////////////////////////////////////////
/// <Function> RetriveFrame </Function>
/// <Description> 把图像内存还给图像获取服务，避免内存泄露</Description>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void RetriveFrame(unsigned char *pframe);

////////////////////////////////////////////////////////////////
/// <Function> CloseDevice </Function>
/// <Description> 关闭设备</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void CloseDevice(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> VideoStart </Function>
/// <Description> 开始传输图像</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>true代表成功，否则失败</Return>
////////////////////////////////////////////////////////////////
extern bool VideoStart(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> VideoStop </Function>
/// <Description> 停止传输图像</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern void VideoStop(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> GetFPS </Function>
/// <Description> 获取帧率</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern float GetFPS(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> SetParameter </Function>
/// <Description> 设置参数</Description>
/// <pDev> 设备对象 </pDev>
/// <param> 参数数组 <param/>
/// <paramLen> 参数数组长度 <paramLen/>
/// <Return>NA</Return>
////////////////////////////////////////////////////////////////
extern bool SetParameter(PDevice pDev, unsigned char * param, const size_t paramLen);

////////////////////////////////////////////////////////////////
/// <Function> SetLED </Function>
/// <Description> 控制LED</Description>
/// <pDev> 设备对象 </pDev>
/// <value> 输入参数的低8位控制8个620nm灯,输入参数的高8位用来控制1个850nm灯的，亮度是可以调试的。当高8位 = 0xF0时，850nm灯是最暗的，当高8位 = 0xF1时，850nm灯是比最暗的情况亮度增加了一点，当高8位 = 0xF2时，850nm灯是亮度双增加了一点，当高8位 = 0xFE时，850nm灯是非常亮的，当高8位 = 0xFF时，850nm灯是最亮的。<value/>
/// <Return>成功 true，否则false</Return>
////////////////////////////////////////////////////////////////
extern int SetLED(PDevice pDev, unsigned short value);

////////////////////////////////////////////////////////////////
/// <Function> SetSensorGain </Function>
/// <Description> 控制相机增益值</Description>
/// <pDev> 设备对象 </pDev>
/// <value> 增益值，默认值为0x0008，最大0x0063<value/>
/// <Return>成功 true，否则false</Return>
////////////////////////////////////////////////////////////////
extern bool SetSensorGain(PDevice pDev, unsigned short value);

////////////////////////////////////////////////////////////////
/// <Function> InitSersor </Function>
/// <Description> 初始化相机</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>成功 true，否则false</Return>
////////////////////////////////////////////////////////////////
extern bool InitSersor(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> LoadFirmware </Function>
/// <Description> 更新固件</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>成功 true，否则false</Return>
////////////////////////////////////////////////////////////////
extern bool LoadFirmware(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> SetSensor1080P </Function>
/// <Description> 设置1080P模式</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>成功 true，否则false</Return>
////////////////////////////////////////////////////////////////
extern bool SetSensor1080P(PDevice pDev);

////////////////////////////////////////////////////////////////
/// <Function> GetProductID </Function>
/// <Description> 获取设备id</Description>
/// <pDev> 设备对象 </pDev>
/// <Return>Product ID</Return>
////////////////////////////////////////////////////////////////
extern unsigned short GetProductID(PDevice pDev);
