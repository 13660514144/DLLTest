# DLLTest
# C# 调用
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DllTestNet
{
    public class VCSDK
    {
        public const string dllpath = "DLLTest.dll";
        [DllImport(dllpath, EntryPoint = "SayHello", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr SayHello();//直接返回指针给调用

        [DllImport(dllpath, EntryPoint = "readnet", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int readnet(IntPtr str);//通过参数指针返回数据

        /// <summary>
        /// 获取字符  传出参数（C++ char * == C# IntPtr）
        /// </summary>
        /// <param name="ptr"></param>
        /// <returns></returns>
        [DllImport(dllpath, EntryPoint = "GetFileName", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetFileName(IntPtr ptr);

        /*
         ////[DllImport("FilePolice", CallingConvention = CallingConvention.Cdecl)]

    ////[DllImport("FilePolice", CallingConvention = CallingConvention.StdCall)]

    ////UnmanagedType.LPStr 為 ANSI

    ////UnmanagedType.LPWStr 為 Unicode

    [DllImport("FilePolice", CharSet = CharSet.Unicode)]
        [MarshalAs(UnmanagedType.LPWStr)]string  针对 C++ char*  传参
    public static extern IntPtr EncryptStringW([MarshalAs(UnmanagedType.LPWStr)]string inString);

    [DllImport("FilePolice", CharSet = CharSet.Ansi)]

    public static extern IntPtr EncryptString([MarshalAs(UnmanagedType.LPStr)]string inString);* 
         */
    }
}


///
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DllTestNet
{
    public class ICCARDSDK
    {
        public const string dllpath = "Qunta.DM300.DLL.dll";
        [DllImport(dllpath, EntryPoint = "Isconnect", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Isconnect();//声明外部的标准动态库, 跟Win32API是一样的

        [DllImport(dllpath, EntryPoint = "readcard", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr readcard();//声明外部的标准动态库, 跟Win32API是一样的

        [DllImport(dllpath, EntryPoint = "writecard", CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr writecard(string inString);//声明外部的标准动态库, 跟Win32API是一样的
    }
}
////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using RestApiHttp;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
namespace DllTestNet
{
    public partial class Form1 : Form
    {
        public RestApi RestClass;
        public Form1()
        {
            InitializeComponent();
            RestClass = new RestApi();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            StringBuilder sb = new StringBuilder(1024);
            string txt = string.Empty;
            //IntPtr ptr = Marshal.StringToHGlobalAnsi(txt);
            //int flg=VCSDK.SayHello(ptr);
            //MessageBox.Show(flg.ToString());
            IntPtr ip = VCSDK.SayHello();

            string strIP = Marshal.PtrToStringAnsi(ip);
            // 把 IntPtr 指针指向的内存数据字符串获取出来
            //string rest = Marshal.PtrToStringAnsi(ptr);
            // 释放 ptr 的内存
            //Marshal.FreeHGlobal(ptr);

            textBox1.Text += "\r\n"+ $"{strIP}";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string txt = textBox2.Text.ToString();
            IntPtr ptr1 = Marshal.StringToHGlobalAnsi(txt);
            int flg = VCSDK.readnet(ptr1);
            MessageBox.Show(flg.ToString());
            // 把 IntPtr 指针指向的内存数据字符串获取出来
            string rest = Marshal.PtrToStringAnsi(ptr1);
            // 释放 ptr 的内存
            Marshal.FreeHGlobal(ptr1);

            textBox1.Text += "\r\n" + rest;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            IntPtr ip = ICCARDSDK.readcard();

            string strIP = Marshal.PtrToStringAnsi(ip);
            textBox1.Text += "\r\n" + $"{strIP}";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string txt = textBox2.Text.ToString().Trim();
            /*  这一段式一比特流传入 对应 C++ char* C#用 string 可
            byte[] inStr = System.Text.Encoding.Default.GetBytes(txt);
            //添加字符串结束符'\0'
            Array.Resize(ref inStr, inStr.Length + 1);
            inStr[inStr.Length - 1] = 0;*/
            IntPtr ptr = ICCARDSDK.writecard(txt);
            //Marshal.FreeHGlobal(ptr);
            string strIP = Marshal.PtrToStringAnsi(ptr);
            textBox1.Text += "\r\n" + $"{strIP}";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            RestClass.Sethost("http://124.223.82.154:8222", "Api/PassRecoadGuest/PostFile");
            Dictionary<string, object> Dict = new Dictionary<string, object>
            {
                { "Ver","26"},
                { "DeviceType","HA000-101"}
            };
            var res = RestClass.RestPostFormFile(Dict,$@"g:/test.png").Result;
            JObject obj = JObject.Parse(res.ToString());
            textBox1.Text = JsonConvert.SerializeObject(obj);// JsonConvert.SerializeObject(obj);
            
        }
        public class Version
        { 
            public string Ver { get; set; }
            public string DeviceType { get; set; }
        }

 
    }
}
