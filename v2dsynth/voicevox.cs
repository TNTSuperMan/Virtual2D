using System;
using System.Net.Http;
using System.Net;
using System.Threading.Tasks;
using System.Text.Json.Serialization;

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
        public AudioQuery() { }
        [JsonConstructor]
        public AudioQuery(Accent[] accent_phrases,int speedScale, int pitchScale,
                            int intonationScale, int volumeScale, int prePhonemeLength,
                            int postPhonemeLength, int outputSamplingRate, bool outputStereo, string kana)
        {
            this.accent_phrases = accent_phrases;
            this.speedScale = speedScale;
            this.pitchScale = pitchScale;
            this.intonationScale = intonationScale;
            this.volumeScale = volumeScale;
            this.prePhonemeLength = prePhonemeLength;
            this.postPhonemeLength = postPhonemeLength;
            this.outputSamplingRate = outputSamplingRate;
            this.outputStereo = outputStereo;
            this.kana = kana;
        }
    }
    [JsonSerializable(typeof(Accent))]
    class Accent
    {
        public Moras[] moras { get; set; }
        public int accent { get; set; }
        public Moras pause_mora { get; set; }
        public bool is_interrogative { get; set; }
        public Accent() { }
        [JsonConstructor]
        public Accent(Moras[] moras, int accent, Moras pause_mora, bool is_interrogative)
        {
            this.moras = moras;
            this.accent = accent;
            this.pause_mora = pause_mora;
            this.is_interrogative = is_interrogative;
        }
    }
    [JsonSerializable(typeof(Moras))]
    class Moras
    {
        public string text { get; set; }
        public string consonant { get; set; }
        public double consonant_length { get; set; }
        public string vowel { get; set; }
        public double vowel_length { get; set; }
        public double pitch { get; set; }
        public Moras() { }
        [JsonConstructor]
        public Moras(string text, string consonant, double consonant_length, string vowel, double vowel_length, double pitch)
        {
            this.text = text;
            this.consonant = consonant;
            this.consonant_length = consonant_length;
            this.vowel = vowel;
            this.vowel_length = vowel_length;
            this.pitch = pitch;
        }
    }
    #endregion
}
