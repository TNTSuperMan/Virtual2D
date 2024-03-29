using System;
using System.Net.Http;
using System.Net;
using System.IO;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Text.Json.Serialization;
using System.Windows.Forms;

namespace v2dsynth
{
    enum Protcol
    {
        GET = 0,
        POST = 1
    }
    internal class voicevox
    {
        private HttpClient http;
        public voicevox()
        {
            http = new HttpClient();
            http.BaseAddress = new Uri("http://127.0.0.1:50021");
        }
        public async Task<HttpContent> Request(Protcol p,string path,HttpContent content)
        {
            HttpResponseMessage getres;
            try
            {
                getres = await (p == Protcol.POST ? http.PostAsync(path, content) : http.GetAsync(path));
            }
            catch {
                return null;
            }
            if(getres.StatusCode != HttpStatusCode.OK)
            {
                return null;
            }
            return getres.Content;
        }
    }
    internal class CharacterText
    {
        public CharacterText(string n, int i)
        {
            name = n;
            id = i;
        }
        public string name;
        public int id;
        public override string ToString()
        {
            return name;
        }
    }

    #region Speaker Deserialize Class
    [JsonSerializable(typeof(Speaker))]
    internal class Speaker
    {
        public string name { get; set; }
        public Style[] styles { get; set; }

        [JsonConstructor]
        public Speaker(string name, Style[] styles)
        {
            this.name = name;
            this.styles = styles;
        }
        public Speaker() { }
    }
    [JsonSerializable(typeof(Style))]
    internal class Style
    {
        public string name { get; set; }
        public int id { get; set; }
        public Style() { }

        [JsonConstructor]
        public Style(string name, int id)
        {
            this.name = name;
            this.id = id;
        }
    }
    #endregion

    #region Audio Query Deserialize Class
    [JsonSerializable(typeof(AudioQuery))]
    class AudioQuery
    {
        public Accent[] accent_phrases { get; set; }
        public int speedScale { get; set; }
        public int pitchScale { get; set; }
        public int intonationScale { get; set; }
        public int volumeScale { get; set; }
        public int prePhonemeLength { get; set; }
        public int postPhonemeLength { get; set; }
        public int outputSamplingRate { get; set; }
        public bool outputStereo { get; set; }
        public string kana { get; set; }
    }
    [JsonSerializable(typeof(Accent))]
    class Accent
    {
        public Moras[] moras { get; set; }
        public int accent { get; set; }
        public PauseMora pause_mora { get; set; }
        public bool is_interrogative { get; set; }
    }
    [JsonSerializable(typeof(Moras))]
    class Moras
    {
        public string text { get; set; }
        public string consonant { get; set; }
        public int consonant_length { get; set; }
        public string vowel { get; set; }
        public int vowel_length { get; set; }
        public int pitch { get; set; }
    }
    [JsonSerializable(typeof(PauseMora))]
    class PauseMora
    {
        public string text { get; set; }
        public string consonant { get; set; }
        public int consonant_length { get; set; }
        public string vowel { get; set; }
        public int vowel_length { get; set; }
        public int pitch { get; set; }
    }
    #endregion
}
