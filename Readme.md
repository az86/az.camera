# ˵��
## 1��SDK��ͷ�ļ�:    publish\include\mgl.CyAPI.h 
## 2��SDK��lib�ļ�:   publish\lib\az.camera.CoreCyVideoSource.lib
## 3��SDK����dll�ļ���publish\bin\*.dll
## 4����������x86�����±��롣
## 5����������˵����publish\include\mgl.CyAPI.h����ͷע��
## 6��ʹ�÷�����mgl.CyAPI.Demo
## 7������Release�� mgl.CyAPI.Demo.exe ��������demo����
## 8����Ҫ����˵����
  ### 1����ȡ���ӵ��豸���� int GetDeviceCount();
  ### 2����ȡ�豸���� void GetDeviceDescrption(const int index, char* pDst, const size_t dstLen);
  ### 3���򿪵��豸���� PDevice OpenDevice (const int deviceIndex);
  ### 4����ȡһ֡ͼ�����ݰ���unsigned char * QuaryFrame(PDevice pDev),ʹ����Ϻ���Ҫ����RetriveFrame����ͼ���ڴ棬�����ڴ�й¶;
  ### 5����һ֡ͼ�����ݰ��л�ȡͼ��Ŀ�� int GetImgWidth(unsigned char * pframe);
  ### 6����һ֡ͼ�����ݰ��л�ȡͼ��ĸ߶� int GetImgHeight(unsigned char * pframe);
  ### 7����һ֡ͼ�����ݰ��л�ȡͼ������ unsigned char * GetImg(unsigned char * pframe);
  ### 8����ͼ���ڴ滹��ͼ���ȡ���񣬱����ڴ�й¶ void RetriveFrame(unsigned char *pframe);
  ### 9���ر��豸 void CloseDevice(PDevice pDev);

