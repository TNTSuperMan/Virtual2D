# VOICEVOXAPIメモ
声の仕組みの整理のため
全部JSONの話な
HTTPでいい多分
省くのあるぞ
## アドレスはlocalhost:50021

## 声のリスト
GET /speakers
## リクエスト
なし
## レス
いるのだけ書く
```
配列
  name:キャラ名
  styles:配列
    name:スタイル名
	id:speakerとかのID
```
## 声のクエリの取得
POST /audio_query
### リクエスト
text(string) しゃべる文字
speaker(int) 話す人
### レスポンス
公式APIドキュメントから引用
```
{
	"accent_phrases": [
		...
	],
	"speedScale": 0,
	"pitchScale": 0,
	"intonationScale": 0,
	"volumeScale": 0,
	"prePhonemeLength": 0,
	"postPhonemeLength": 0,
	"outputSamplingRate": 0,
	"outputStereo": true,
	"kana": "string"
}
```
そのまま音声合成に突っ込んでいい
## 音声をついに合成
POST /synthesis
### リクエスト
/audio_queryのレスと同じ
### レスポンス
wavファイル