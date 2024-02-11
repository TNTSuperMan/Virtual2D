using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace mtedit
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        bool isOkEdit = true;
        string fpath;
        bool isOpen = false;

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
            string ret = string.Empty;
            ret += ((uint)colorDialog1.Color.ToArgb()).ToString() + "\n";
            ret += numericUpDown1.Value.ToString() + "\n";
            ret += numericUpDown2.Value.ToString() + "\n";
            ret += numericUpDown3.Value.ToString() + "\n";
            ret += numericUpDown4.Value.ToString() + "\n";
            ret += numericUpDown5.Value.ToString() + "\n";
            ret += numericUpDown6.Value.ToString() + "\n";
            ret += numericUpDown7.Value.ToString() + "\n";
            ret += numericUpDown8.Value.ToString() + "\n";
            ret += numericUpDown9.Value.ToString();
            File.WriteAllText(fpath, ret);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;
                isOkEdit = false;
                isOpen = true;
                fpath = openFileDialog1.FileName;
                string[] fd = File.ReadAllText(fpath).Split('\r');
                string fd2 = string.Empty;
                foreach(string fdt in fd) fd2 += fdt;
                fd = fd2.Split('\n');

                Color c = Color.FromArgb((int)uint.Parse(fd[0]));
                
                colorDialog1.Color = c;
                panel1.BackColor = c;


                numericUpDown1.Value = int.Parse(fd[1]);
                numericUpDown2.Value = int.Parse(fd[2]);
                numericUpDown3.Value = int.Parse(fd[3]);
                numericUpDown4.Value = int.Parse(fd[4]);
                numericUpDown5.Value = int.Parse(fd[5]);
                numericUpDown6.Value = int.Parse(fd[6]);
                numericUpDown7.Value = int.Parse(fd[7]);
                numericUpDown8.Value = int.Parse(fd[8]);
                numericUpDown9.Value = int.Parse(fd[9]);

                isOkEdit = true;
            }
        }
    }
}
