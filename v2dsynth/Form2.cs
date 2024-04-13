using System;
using System.Diagnostics;
using System.IO;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Windows.Forms;
using System.Text.Unicode;

namespace v2dsynth
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            textBox1.Text = cfg.voicevox_path;
        }
        voicevox req = new voicevox();
        Properties.Settings cfg = new Properties.Settings();

        private void button1_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;
                cfg.Save();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            cfg.voicevox_path = textBox1.Text;
            cfg.Save();
        }

        private async void button2_Click(object sender, EventArgs e)
        {

            var vt = await req.Request(Protcol.GET, "speakers", null);
            if (vt == null)
            {
                if (!File.Exists(cfg.voicevox_path))
                {
                    MessageBox.Show("Voicevoxに接続できませんでした。\nVoicevoxを起動してください。");
                    return;
                }
                Process.Start(cfg.voicevox_path);
                MessageBox.Show("Voicevoxに接続できませんでした。\nVoicevoxの起動が完了してから試してください。");
                return;
            }

            Speaker[] spkobj = JsonSerializer.Deserialize<Speaker[]>(JsonDocument.Parse(await vt.ReadAsStringAsync()), 
                new JsonSerializerOptions
                {
                    WriteIndented = true,
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.All)
                });
            CharacterText t = null;
            listBox1.Items.Clear();
            foreach(Speaker spkr in spkobj)
            {
                foreach(Style style in spkr.styles)
                {
                    t = new CharacterText(spkr.name + " - " + style.name, style.id);
                    listBox1.Items.Add(t);
                    if (cfg.speaker == style.id) listBox1.SelectedItem = t;
                }
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            cfg.speaker = ((CharacterText)listBox1.SelectedItem).id;
            cfg.Save();
        }
    }
}
