using System;

namespace az.camera.player
{
    public interface IUnmanagedVideoSource
    {
        bool Open(int devIndex);
        Image GetImg();
        void RetriveImg(Image img);
    }
}
