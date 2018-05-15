/*************************************************
Copyright:DaJiaKeJi
Author:WZP
Date:2018-04-11
Description:���ֶ�λ��ж�λ
**************************************************/
#pragma once

/**************������Ҫ˵��********************
Function Name:              GetAllTargetPose
Function Description:       ���ͼ����ǰ��е�λ�ˡ�Բ�����ꡢԲ�ľ��롣
@param ho_Image             ����ĻҶ�ͼ��
@param hv_CameraParam       ����������ڲ�
@param *hvec_VecPose        ���������λ��
@param *hv_RowF, *hv_ColF, *hv_DistanceF     �����ǰ��Բ�����꼰Բ�ľ���
@param *hv_RowB, *hv_ColB, *hv_DistanceB     �����ǰ��Բ�����꼰Բ�ľ���
@return                     �޷���ֵ
@attention                  �����ͼ��Ϊ�Ҷ�ͼ��Ĭ��ǰ��Ϊ����Բ�����Ϊʵ��Բ       
***********************************************/
__declspec(dllimport) void GetAllTarget(HObject ho_ImageRaw, HTuple hv_CameraParam, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecPose,
	HTuple *hv_RowF, HTuple *hv_ColF, HTuple *hv_DistanceF, HTuple *hv_RowB, HTuple *hv_ColB, HTuple *hv_DistanceB);



/**************������Ҫ˵��********************
Function Name:              GenCaltabID
Function Description:       �趨�����Ϣ������һ����е�ID��������ʶ��ʹ�á�
@param hv_CamParam             ���������ڲ�
@param hv_Diameter       ����Բֱ������λ��mm
@param hv_Distance       ����Բ�ľ��룬��λ��mm
@param hv_CircleRowNum   ����Բ������
@param hv_CircleColNum   ����Բ������
@param *hv_CalibDataID   ����ı��ʶ���õ�ID��
@return                  �޷���ֵ
@attention               Ϊ������ʶ��ʱ�䣬�ò���ֻ��Ҫ�ڳ�ʼ��ʱ�����һ�ε��ã�ʵʱʶ��ʱֻҪ����ID���ɡ�
***********************************************/
__declspec(dllimport) void GenCaltabID(HTuple hv_CamParam, HTuple hv_Diameter, HTuple hv_Distance, HTuple hv_CircleRowNum,
	HTuple hv_CircleColNum, HTuple *hv_CalibDataID);

/**************������Ҫ˵��********************
Function Name:              GetBoardInfo
Function Description:       ���ͼ����ǰ��е�λ�ˡ�Բ�����ꡢԲ�ľ��롣(���Ϊ��׼��halcon��б�ǵı�У���Բ���ױ���)
@param ho_Image             ����ĻҶ�ͼ��
@param hv_CamParam       ����������ڲ�
@param *hvec_VecPose        ���������λ��
@param *hvec_VecRow, *hvec_VecCol     �����ǰ���Բ�����꣬��λ������
@param *hvec_VecDistance     �����ǰ���Բ�ľ��룬��λ��mm
@return                     �޷���ֵ
@attention                  ��ͼ����ֻ��1�����ʱ���������������Ϊ1��ǰ�����Ҫ���и���Z����루HTuple z1 = hvec_VecPose[0].T()[2];�������֣����趨����������3.5m����Ϊǰ��е����֡�
							��ͼ����ֻ��2�����ʱ���������������Ϊ2����ʱ�Ѿ��ǰ�˳���źã��±�Ϊ0��Ϊǰ�У��±�Ϊ1��Ϊ��С�
***********************************************/
__declspec(dllimport) void GetBoardInfo(HObject ho_Image, HTuple hv_CamParam, HTuple hv_CalibDataID, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecPose,
	HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecRow, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecCol,
	HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecDistance);


