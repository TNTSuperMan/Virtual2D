using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Windows.Forms;

namespace mjedit
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll", SetLastError = true, EntryPoint = "SendMessage")]
        static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);
        public Form1()
        {
            InitializeComponent();
        }
        bool isOkEdit = true;
        string fpath;
        bool isOpen = false;
        Process v2dprc = null;

        private void button2_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                panel1.BackColor = colorDialog1.Color;
                chg(sender, e);
            }
        }

        private void chg(object sender, EventArgs e)
        {
            if (!isOkEdit) return;
            if (!isOpen) return;
            List<string> aniluas = new List<string>();
            foreach(object p in aniluaList.Items)
                aniluas.Add(p.ToString());
            Model model = new Model
            {
                backgroundColor = (uint)colorDialog1.Color.ToArgb(),
                BodyY = (int)bodyY.Value,
                BodyCentY = (int)bodyCentY.Value,
                BodySize = (int)bodySize.Value,
                NeckY = (int)neckY.Value,
                HeadY = (int)headY.Value,
                HeadSize = (int)headSize.Value,
                EyePos = (int)eyePos.Value,
                EyeSize = (int)eyeSize.Value,
                EyeKankaku = (int)eyeKankaku.Value,
                BodyFurehaba = (int)bodyFurehaba.Value,
                HeadFurehaba = (int)headFurehaba.Value,
                FureSpeed = (int)fureSpeed.Value,
                GetdownMode = checkBox1.Checked,
                EyePointerSize = (int)eyePointerSize.Value,
                HeadPointerSize = (int)headPointerSize.Value,
                PointerHoseX = (int)pointerHoseX.Value,
                PointerHoseY = (int)pointerHoseY.Value,
                MouthSize = (int)mouthSize.Value,
                CloseMouthSize = (int)closeMouthSize.Value,
                MouthY = (int)mouthY.Value,
                MouthPointerSize = (int)mouthPointerSize.Value,
                MabatakiKankaku = (int)mabatakiKankaku.Value,
                MabatakiSize = (int)mabatakiSize.Value,
                MabatakiTime = (int)mabatakiTime.Value,
                Aniluas = aniluas
            };
            string jstr = JsonSerializer.Serialize(model);
            File.WriteAllText(fpath, jstr);

            if (checkBox2.Checked && v2dprc != null) { 
                if(SendMessage(v2dprc.MainWindowHandle, 0xBAFA, IntPtr.Zero, IntPtr.Zero) != (IntPtr)4545)
                {
                    MessageBox.Show("Virtual2Dが停止したため、\nホットリロードが出来なくなりました。", "model.jsonエディタ");
                    v2dprc.Exited -= v2dprcClosed;
                    v2dprc = null;
                    checkBox2.Checked = false;
                    return;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (modeljsonDialog.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = modeljsonDialog.FileName;
                isOkEdit = false;
                isOpen = true;
                fpath = modeljsonDialog.FileName;
                object originobj = null;
                try
                {
                    originobj = JsonSerializer.Deserialize(File.ReadAllText(fpath), typeof(Model));
                }
                catch
                {
                    MessageBox.Show("設定ファイルが間違っています。\n新規で読み込みます。", "Virtual2D");
                    isOkEdit = true;
                    return;
                }
                Model model = (Model)originobj;
                Color c = Color.FromArgb((int)model.backgroundColor);
                panel1.BackColor = c;
                colorDialog1.Color = c;
                bodyY.Value = model.BodyY;
                bodyCentY.Value = model.BodyCentY;
                bodySize.Value = model.BodySize;
                neckY.Value = model.NeckY;
                headY.Value = model.HeadY;
                headSize.Value = model.HeadSize;
                eyePos.Value = model.EyePos;
                eyeSize.Value = model.EyeSize;
                eyeKankaku.Value = model.EyeKankaku;
                bodyFurehaba.Value = model.BodyFurehaba;
                headFurehaba.Value = model.HeadFurehaba;
                fureSpeed.Value = model.FureSpeed;
                checkBox1.Checked = model.GetdownMode;
                eyePointerSize.Value = model.EyePointerSize;
                headPointerSize.Value = model.HeadPointerSize;
                pointerHoseX.Value = model.PointerHoseX;
                pointerHoseY.Value = model.PointerHoseY;
                mouthY.Value = model.MouthY;
                mouthSize.Value = model.MouthSize;
                mouthPointerSize.Value = model.MouthPointerSize;
                closeMouthSize.Value = model.CloseMouthSize;
                mabatakiKankaku.Value = model.MabatakiKankaku;
                mabatakiSize.Value = model.MabatakiSize;
                mabatakiTime.Value = model.MabatakiTime;
                aniluaList.Items.Clear();
                foreach(string p in model.Aniluas)
                    aniluaList.Items.Add(p);
                
                isOkEdit = true;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (!isOpen)
            {
                checkBox2.Checked = false;
                return;
            }
            if (checkBox2.Checked)
            {
                foreach (Process p in Process.GetProcesses())
                {

                    if ("Virtual2D" == p.MainWindowTitle)
                    {
                        //Virtual2Dと接続を検証
                        if (SendMessage(p.MainWindowHandle, 0xBACA, IntPtr.Zero, IntPtr.Zero).ToInt64() == 1248)
                        {
                            v2dprc = p;
                            v2dprc.Exited += v2dprcClosed;
                            return;
                        }
                    }
                }
                checkBox2.Checked = false;
            }
        }
        private void v2dprcClosed(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
            {
                MessageBox.Show("Virtual2Dが停止したため、\nホットリロードが出来なくなりました。", "model.jsonエディタ");
                v2dprc.Exited -= v2dprcClosed;
                v2dprc = null;
                checkBox2.Checked = false;
                return;
            }
            
        }
        [JsonSerializable(typeof(Model))]
        public class Model
        {
            public uint backgroundColor { get; set; }
            public int BodyY { get; set; }
            public int BodyCentY { get; set; }
            public int BodySize { get; set; }
            public int NeckY { get; set; }
            public int HeadY { get; set; }
            public int HeadSize { get; set; }
            public int EyePos { get; set; }
            public int EyeSize { get; set; }
            public int EyeKankaku { get; set; }
            public int MabatakiKankaku { get; set; }
            public int MabatakiTime { get; set; }
            public int MabatakiSize { get; set; }
            public int BodyFurehaba { get; set; }
            public int HeadFurehaba { get; set; }
            public int FureSpeed { get; set; }
            public bool GetdownMode { get; set; }
            public int EyePointerSize { get; set; }
            public int HeadPointerSize { get; set; }
            public int PointerHoseX { get; set; }
            public int PointerHoseY { get; set; }
            public int MouthSize { get; set; }
            public int CloseMouthSize { get; set; }
            public int MouthY { get; set; }
            public int MouthPointerSize { get; set; }
            public List<string> Aniluas { get; set; }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if(aniluaDialog.ShowDialog() == DialogResult.OK)
            {
                aniluaPathBox.Text = aniluaDialog.FileName;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            aniluaList.Items.Add(aniluaPathBox.Text);
            chg(sender, e);
        }

        private void aniluaDeleteBox_Click(object sender, EventArgs e)
        {
            if(aniluaList.SelectedIndex != -1)
            {
                aniluaList.Items.RemoveAt(aniluaList.SelectedIndex);
                chg(sender, e);
            }
        }

        private void aniluaOpenBox_Click(object sender, EventArgs e)
        {
            if(aniluaList.SelectedIndex != -1)
            {
                Process.Start(aniluaList.SelectedItem.ToString());
            }
        }

        private void aniluaUpBox_Click(object sender, EventArgs e)
        {
            if(aniluaList.SelectedIndex > 0)
            {
                int i = aniluaList.SelectedIndex;
                object t = aniluaList.Items[i - 1];
                aniluaList.Items[i - 1] = aniluaList.Items[i];
                aniluaList.Items[i] = t;
                chg(sender, e);
            }
        }
    }
}
