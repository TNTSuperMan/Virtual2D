# VOICEVOXAPI����
���̎d�g�݂̐����̂���
�S��JSON�̘b��
HTTP�ł�������
�Ȃ��̂��邼
## �A�h���X��localhost:50021

## ���̃��X�g
GET /speakers
## ���N�G�X�g
�Ȃ�
## ���X
����̂�������
```
�z��
  name:�L������
  styles:�z��
    name:�X�^�C����
	id:speaker�Ƃ���ID
```
## ���̃N�G���̎擾
POST /audio_query
### ���N�G�X�g
text(string) ����ׂ镶��
speaker(int) �b���l
### ���X�|���X
����API�h�L�������g������p
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
���̂܂܉��������ɓ˂�����ł���
## ���������ɍ���
POST /synthesis
### ���N�G�X�g
/audio_query�̃��X�Ɠ���
### ���X�|���X
wav�t�@�C��