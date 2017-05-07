using System;
using System.Collections;
//using System.ComponentModel.Design;
using System.Runtime.InteropServices;
//using System.Security.Cryptography.X509Certificates;
using az.camera.player;

namespace az.camera.VideoSource
{
    public class CyVideoSource : IUnmanagedVideoSource
    {
        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "GetDeviceCount", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern int CoreGetDeviceCount();

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "GetDeviceDescrption", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern void GetDeviceDescrption(int index, IntPtr pDst, int dstLen);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "OpenDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern IntPtr OpenDevice(int deviceIndex);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "QuaryFrame", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern IntPtr QuaryFrame(IntPtr pDevice);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "GetImg", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern IntPtr GetImg(IntPtr frame);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "GetImgWidth", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern int GetImgWidth(IntPtr frame);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "GetImgHeight", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern int GetImgHeight(IntPtr frame);


        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "RetriveFrame", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern void RetriveImgFrame(IntPtr frame);

        [DllImport("az.camera.CoreCyVideoSource.dll", EntryPoint = "CloseDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern void CloseDevice(IntPtr pDevice);

        IntPtr _device;

        public static int GetDeviceCount()
        {
            return CoreGetDeviceCount();
        }

        public static string GetDeviceDesc(int devIndex)
        {
            var arr = new byte[256];
            unsafe
            {
                fixed (byte* pArr= &arr[0])
                {
                    GetDeviceDescrption(devIndex, new IntPtr(pArr), 256);
                }
            }
            return System.Text.Encoding.ASCII.GetString(arr);
        }

        public Image GetImg()
        {
            var frame = QuaryFrame(_device);
            var img = new Image
            {
                Frame = frame,
                Width = GetImgWidth(frame),
                Height = GetImgHeight(frame),
                Img = GetImg(frame)
            };
            return img;
        }

        public void RetriveImg(Image img)
        {
            RetriveImgFrame(img.Frame);
        }

        public bool Open(int devIndex)
        {
            if (_device != IntPtr.Zero)
                CloseDevice(_device);
            _device = OpenDevice(devIndex);
            return _device != IntPtr.Zero;
        }

        public void Close()
        {
            CloseDevice(_device);
            _device = IntPtr.Zero;
        }
    }
}
