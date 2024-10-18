using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace v2dsynth
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll",SetLastError = true, EntryPoint = "SendMessage")]
        static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

        void Msg(string msg) => scr = scr;//MessageBox.Show(msg, "Virtual2d 発声ウインドウ");

        public Form1()
        {
            InitializeComponent();
            SetWindow(WindowMode.NonConnected);
        }
        string scr = Path.GetTempFileName();
        #region 変数
        bool isConnected = false;
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
                SetWindow(WindowMode.Connecting);
                v2dhwnd = IntPtr.Zero;
                //Virtual2Dウインドウを検索
                foreach(Process p in Process.GetProcesses())
                {
                    if("Virtual2D" == p.MainWindowTitle)
                    {
                        //Virtual2Dと接続を検証
                        if(SendMessage(p.MainWindowHandle, 0xBACA, IntPtr.Zero, IntPtr.Zero).ToInt64() == 1248)
                        {
                            v2dhwnd = p.MainWindowHandle;
                        }
                    }
                }
                if (v2dhwnd != IntPtr.Zero) //接続しているかを分岐
                {
                    if(await vc.Request(Protcol.GET,"speakers",null) != null)
                    {
                        SetWindow(WindowMode.Connected);
                        return;
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
                SetWindow(WindowMode.NonConnected);
            }
            else
            {
                if (SendMessage(v2dhwnd, 0xBACA, IntPtr.Zero, IntPtr.Zero).ToInt64() != 1248)
                {
                    Msg("Virtual2Dに接続できませんでした。");
                    SetWindow(WindowMode.NonConnected);
                    v2dhwnd = IntPtr.Zero;
                    return;
                }
                if (textBox1.Text.Length == 0) return;
                SetWindow(WindowMode.Generating);
                
                var vvquery = await vc.Request(Protcol.POST, "audio_query?text=" + Uri.EscapeUriString(textBox1.Text) + "&speaker=" + cfg.speaker.ToString(),null);
                if(vvquery == null)
                {
                    Msg("声クエリの生成でエラーが発生しました。");
                    SetWindow(WindowMode.Connected);
                    return;
                }
                byte[] querytext = await vvquery.ReadAsByteArrayAsync();



                var voice = await vc.Request(Protcol.POST, "synthesis?speaker=" + cfg.speaker.ToString(), vvquery);
                if (voice == null)
                {
                    Msg("声の生成でエラーが発生しました。");
                    SetWindow(WindowMode.Connected);
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

                string qtpath = Path.GetTempFileName();
                File.WriteAllBytes(qtpath, querytext);

                SendMessage(v2dhwnd, 0xBACA, (IntPtr)1, IntPtr.Zero); //ファイル名の初期化
                foreach(char spc in synthpath)
                {
                    SendMessage(v2dhwnd, 0xBACA, (IntPtr)2, (IntPtr)spc);
                }

                foreach(byte aq in qtpath)
                {
                    SendMessage(v2dhwnd, 0xBACA, (IntPtr)3, (IntPtr)aq);
                }
                SendMessage(v2dhwnd, 0xBACA, (IntPtr)4, (IntPtr)querytext.Length);


                SendMessage(v2dhwnd, 0xBACA, (IntPtr)5, IntPtr.Zero);
                SetWindow(WindowMode.Connected);
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                button1_Click(null, null);
            }
        }
        private void SetWindow(WindowMode wmode)
        {
            switch (wmode)
            {
                case WindowMode.NonConnected:
                    isConnected = false;
                    button1.Text = "接続";
                    button1.Enabled = true;
                    textBox1.Enabled = false;
                    textBox1.Text = string.Empty;
                    button3.Enabled = false;
                    break;
                case WindowMode.Connecting:
                    button1.Text = "接続中";
                    button1.Enabled = false;
                    textBox1.Enabled = false;
                    textBox1.Text = string.Empty;
                    button3.Enabled = false;
                    break;
                case WindowMode.Connected:
                    isConnected = true;
                    button1.Text = "発声";
                    button1.Enabled = true;
                    textBox1.Enabled = true;
                    textBox1.Text = string.Empty;
                    button3.Enabled = true;
                    break;
                case WindowMode.Generating:
                    isConnected = true;
                    button1.Text = "生成中";
                    button1.Enabled = false;
                    textBox1.Enabled = false;
                    button3.Enabled = true;
                    break;

            }
        }
    }
    public enum WindowMode
    {
        NonConnected = 0,
        Connecting = 1,
        Connected = 2,
        Generating = 3
    }
}
