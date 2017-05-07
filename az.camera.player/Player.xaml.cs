using System.Threading;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace az.camera.player
{
    /// <summary>
    /// Player.xaml 的交互逻辑
    /// </summary>
    public partial class Player : UserControl
    {
        public IUnmanagedVideoSource VS { get; set; }

        private Thread _th;

        bool _isPlay;

        public Player()
        {
            InitializeComponent();
        }

        public void Start()
        {
            if (_th == null && VS != null)
            {
                _isPlay = true;
                _th = new Thread(PlayImg) {IsBackground = true};
                _th.Start();
            }
        }

        internal void PlayImg()
        {
            while (_isPlay)
            {
                if (VS != null)
                {
                    var img = VS.GetImg();
                    Dispatcher.Invoke(() =>
                    {
                        var bmp = BitmapSource.Create(img.Width, img.Height, 96, 96, PixelFormats.Rgb24, BitmapPalettes.Gray256, img.Img, img.ImgSize, img.Width * 3);
                        player.Source = bmp;
                    });
                    VS.RetriveImg(img);
                }
            }
        }
    }
}
