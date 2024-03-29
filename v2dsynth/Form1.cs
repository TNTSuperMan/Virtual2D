using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Http;
using System.Text.Json;
using System.Text.Encodings.Web;
using System.Text.Unicode;

namespace v2dsynth
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll",SetLastError = true, EntryPoint = "SendMessage")]
        static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

        void Msg(string msg) => MessageBox.Show(msg, "Virtual2d 発声ウインドウ");

        public Form1()
        {
            InitializeComponent();
        }
        #region 変数
        bool isConnected = false;
        bool isGenerating = false;
        IntPtr v2dhwnd = IntPtr.Zero;
        Properties.Settings cfg = new Properties.Settings();
        voicevox vc = new voicevox();
        #endregion
        private void button2_Click(object sender, EventArgs e)
        {
            Process.Start(Application.ExecutablePath, "cfg");
            Application.Exit();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            if (!isConnected)
            {
                v2dhwnd = IntPtr.Zero;
                //Virtual2Dウインドウを検索
                foreach(Process p in Process.GetProcesses())
                {
                    if("Virtual2D" == p.MainWindowTitle)
                    {
                        //Virtual2Dと接続を検証
                        if(SendMessage(p.MainWindowHandle, 0x0FAC, IntPtr.Zero, IntPtr.Zero).ToInt64() == 1248)
                        {
                            v2dhwnd = p.MainWindowHandle;
                        }
                    }
                }
                if (v2dhwnd != IntPtr.Zero) //接続しているかを分岐
                {
                    if(await vc.Request(Protcol.GET,"speakers",null) != null)
                    {
                        Msg("接続に成功しました。");
                        button1.Text = "発声";
                        isConnected = true;
                    }
                    else
                    {
                        if (!File.Exists(cfg.voicevox_path))
                        {
                            Msg("Voicevoxに接続できませんでした。\nVoicevoxを起動してから試してください。");
                        }
                        else
                        {
                            Process.Start(cfg.voicevox_path);
                            Msg("Voicevoxに接続できませんでした。\nVoicevoxを起動したので、起動が完了してから試してください。");
                        }
                    }
                }
                else
                {
                    Msg("Virtual2Dに接続できませんでした。\nVirtual2Dが正しく起動しているかを確認してください。");
                }
            }
            else
            {
                if (isGenerating) return;
                if(SendMessage(v2dhwnd,0xFAC,IntPtr.Zero, IntPtr.Zero).ToInt32() != 1248)
                {
                    Msg("Virtual2Dに接続できませんでした。");
                    isConnected = false;
                    v2dhwnd = IntPtr.Zero;
                    return;
                }
                isGenerating = true;
                button1.Text = "生成中";
                var vvquery = await vc.Request(Protcol.POST, "audio_query?text=" + Uri.EscapeUriString(textBox1.Text) + "&speaker=" + cfg.speaker.ToString(),null);
                if(vvquery == null)
                {
                    Msg("声クエリの生成でエラーが発生しました。");
                    button1.Text = "発声";
                    isGenerating = false;
                    return;
                }

                /*
                AudioQuery q = JsonSerializer.Deserialize<AudioQuery>(JsonDocument.Parse(await vvquery.ReadAsStringAsync()),
                new JsonSerializerOptions
                {
                    WriteIndented = true,
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.All)
                }); */

                var voice = await vc.Request(Protcol.POST, "synthesis?speaker=" + cfg.speaker.ToString(), vvquery);
                if (voice == null)
                {
                    Msg("声の生成でエラーが発生しました。");
                    button1.Text = "発声";
                    isGenerating = false;
                    return;
                }
                byte[] vb = await voice.ReadAsByteArrayAsync();
                string synthpath = Path.GetTempFileName() + ".wav";
                FileStream fs = new FileStream(synthpath, FileMode.CreateNew);
                foreach(byte b in vb)
                {
                    fs.WriteByte(b);
                }
                fs.Close();

                SendMessage(v2dhwnd, 0x0FAD, (IntPtr)1, IntPtr.Zero); //ファイル名の初期化
                foreach(char spc in synthpath)
                {
                    SendMessage(v2dhwnd, 0x0FAD, (IntPtr)2, (IntPtr)spc);
                }
                SendMessage(v2dhwnd, 0x0FAD, (IntPtr)3, IntPtr.Zero);

                button1.Text = "発声";
                isGenerating = false;
            }
        }
    }
    struct COPYDATASTRUCT
    {
        public int dwData;
        public int cbData;
        public string lpData;
    }
}
