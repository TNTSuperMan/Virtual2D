#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
class Setting
{
public:
	unsigned int backgroundColor; //�w�i�F �N���}�L�[�ŏ�肭�����F�ł��t���Ƃ�
	int BodyY;          //�̂�Y���W
	int BodyCentY;      //�̂̉�]�̒��S
	int BodySize;       //�̂̑傫��
	int neckY;          //���̒��S����̎��Y���W�̑��΍��W
	int HeadY;          //���̍��W
	int HeadSize;       //���̑傫��
	int EyePos;         //�ڂ̈ʒu
	int EyeSize;        //�ڂ̑傫��
	int EyeKankaku;     //�ڂ̊Ԋu
	int BodyFurehaba;   //�̂̐U�ꕝ
	int HeadFurehaba;   //���̐U�ꕝ
	int FureSpeed;      //�U�ꕝ�X�s�[�h ��1000�Ŏ��ۂ̒l
	int GetdownMode;    //�Q�b�_�������[�h
	int EyePointerSize; //�ڂ��ǂ̂��炢�|�C���^�ɉe������邩
	int HeadPointerSize;//�̂��ǂ̂��炢�|�C���^�ɉe������邩
	int PointerHoseX;   //�|�C���^�[�ǐՂ̕␮
	int PointerHoseY;   //�|�C���^�[�ǐՂ̕␮
	Setting();
};
