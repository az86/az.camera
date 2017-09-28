# 说明
## 1、SDK的头文件:    publish\include\mgl.CyAPI.h 
## 2、SDK的lib文件:   publish\lib\az.camera.CoreCyVideoSource.lib
## 3、SDK所需dll文件：publish\bin\*.dll
## 4、程序请在x86环境下编译。
## 5、函数具体说明见publish\include\mgl.CyAPI.h函数头注释
## 6、使用方法见mgl.CyAPI.Demo
## 7、运行Release下 mgl.CyAPI.Demo.exe 可以运行demo程序。
## 8、简要函数说明：
  ### 1）获取连接的设备数量 int GetDeviceCount();
  ### 2）获取设备描述 void GetDeviceDescrption(const int index, char* pDst, const size_t dstLen);
  ### 3）打开的设备对象 PDevice OpenDevice (const int deviceIndex);
  ### 4）获取一帧图像数据包，unsigned char * QuaryFrame(PDevice pDev),使用完毕后需要调用RetriveFrame销毁图像内存，避免内存泄露;
  ### 5）从一帧图像数据包中获取图像的宽度 int GetImgWidth(unsigned char * pframe);
  ### 6）从一帧图像数据包中获取图像的高度 int GetImgHeight(unsigned char * pframe);
  ### 7）从一帧图像数据包中获取图像数据 unsigned char * GetImg(unsigned char * pframe);
  ### 8）把图像内存还给图像获取服务，避免内存泄露 void RetriveFrame(unsigned char *pframe);
  ### 9）关闭设备 void CloseDevice(PDevice pDev);

