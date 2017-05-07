using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using az.camera.VideoSource;

namespace az.camera.UI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            var devCount = CyVideoSource.GetDeviceCount();
            for (int i = 0; i < devCount; i++)
            {
                Console.WriteLine(CyVideoSource.GetDeviceDesc(i));
            }
            //player.VS = new CyVideoSource();
            //player.VS.Open(0);
            //player.Start();
        }
    }
}
