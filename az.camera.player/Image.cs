using System;

namespace az.camera.player
{
    public struct Image
    {
        /// <summary>
        /// 图像数据帧，包括数据头
        /// </summary>
        public IntPtr Frame;
        /// <summary>
        /// RGB数据
        /// </summary>
        public IntPtr Img;
        /// <summary>
        /// 图像宽度
        /// </summary>
        public int Width;
        /// <summary>
        /// 图像高度
        /// </summary>
        public int Height;
        /// <summary>
        /// RGB数据长度
        /// </summary>
        public int ImgSize {get { return Width*Height*3; } }
    }
}
