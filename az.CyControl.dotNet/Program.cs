using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CyUSB;

namespace az.CyControl.dotNet
{
    class Program
    {
        static void Main(string[] args)
        {
            USBDeviceList usbDevices = new USBDeviceList(CyConst.DEVICES_CYUSB);
            foreach (var dev in usbDevices)
            {
                var fxDev = dev as CyFX2Device;
                Console.WriteLine(fxDev.ProductID.ToString("X"));
            }
            //return;
            foreach (var dev in usbDevices)
            {
                var fxDev = dev as CyFX2Device;
                var devId = fxDev.ProductID.ToString("X");
                var hexFilePath = ConfigurationManager.AppSettings[devId];
                if (string.IsNullOrEmpty(hexFilePath))
                {
                    Console.WriteLine("App.config {0} incorrect or not found this device!", devId);
                    Console.ReadKey();
                }
                if (!System.IO.File.Exists(hexFilePath))
                {
                    Console.WriteLine("{0} not found!", hexFilePath);
                }
                Console.WriteLine("Camera {0} update firmware {1}!", devId, hexFilePath);
                if (fxDev != null && fxDev.LoadExternalRam(hexFilePath))
                {
                    Console.WriteLine("update firmware successed!");
                }
                else
                {
                    Console.WriteLine("update firmware falied!");
                }
            }
        }
    }
}
