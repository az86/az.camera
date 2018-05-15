/*************************************************
Copyright:DaJiaKeJi
Author:WZP
Date:2018-04-11
Description:四轮定位标靶定位
**************************************************/
#pragma once

/**************函数简要说明********************
Function Name:              GetAllTargetPose
Function Description:       获得图像中前后靶的位姿、圆心坐标、圆心距离。
@param ho_Image             输入的灰度图像
@param hv_CameraParam       输入摄像机内参
@param *hvec_VecPose        输出的所有位姿
@param *hv_RowF, *hv_ColF, *hv_DistanceF     输出的前靶圆心坐标及圆心距离
@param *hv_RowB, *hv_ColB, *hv_DistanceB     输出的前靶圆心坐标及圆心距离
@return                     无返回值
@attention                  输入的图像为灰度图像，默认前靶为空心圆，后靶为实心圆       
***********************************************/
__declspec(dllimport) void GetAllTarget(HObject ho_ImageRaw, HTuple hv_CameraParam, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecPose,
	HTuple *hv_RowF, HTuple *hv_ColF, HTuple *hv_DistanceF, HTuple *hv_RowB, HTuple *hv_ColB, HTuple *hv_DistanceB);



/**************函数简要说明********************
Function Name:              GenCaltabID
Function Description:       设定标靶信息，生成一个标靶的ID供给后面识别使用。
@param hv_CamParam             输入的相机内参
@param hv_Diameter       输入圆直径，单位：mm
@param hv_Distance       输入圆心距离，单位：mm
@param hv_CircleRowNum   输入圆的行数
@param hv_CircleColNum   输入圆的列数
@param *hv_CalibDataID   输出的标靶识别用的ID号
@return                  无返回值
@attention               为了缩短识别时间，该步骤只需要在初始化时候进行一次调用，实时识别时只要传递ID即可。
***********************************************/
__declspec(dllimport) void GenCaltabID(HTuple hv_CamParam, HTuple hv_Diameter, HTuple hv_Distance, HTuple hv_CircleRowNum,
	HTuple hv_CircleColNum, HTuple *hv_CalibDataID);

/**************函数简要说明********************
Function Name:              GetBoardInfo
Function Description:       获得图像中前后靶的位姿、圆心坐标、圆心距离。(标靶为标准的halcon带斜角的标靶，黑圆、白背景)
@param ho_Image             输入的灰度图像
@param hv_CamParam       输入摄像机内参
@param *hvec_VecPose        输出的所有位姿
@param *hvec_VecRow, *hvec_VecCol     输出的前后靶圆心坐标，单位：像素
@param *hvec_VecDistance     输出的前后靶圆心距离，单位：mm
@return                     无返回值
@attention                  当图像中只有1个标靶时，输出的向量长度为1。前后靶需要自行根据Z向距离（HTuple z1 = hvec_VecPose[0].T()[2];）来区分，可设定距离例如在3.5m处作为前后靶的区分。
							当图像中只有2个标靶时，输出的向量长度为2。此时已经是按顺序排好，下标为0的为前靶，下标为1的为后靶。
***********************************************/
__declspec(dllimport) void GetBoardInfo(HObject ho_Image, HTuple hv_CamParam, HTuple hv_CalibDataID, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecPose,
	HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecRow, HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecCol,
	HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_VecDistance);


