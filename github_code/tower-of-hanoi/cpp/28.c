#pragma once

#include <stdio.h>
#include <assert.h>
#include <stack>

// �n�m�C�̓��𗧂Ă邽�߂̓�1��\���N���X
class TowerOfHanoi : public std::stack<int> {

public:
	char _name; // ���̏��Ԃ�\��

	// �������~�Ղ̏�ɑ傫���~�Ղ�����Ă��Ȃ����`�F�b�N���܂�
	/// @ret:bool ���� = true,����ȊO = false
	bool CheckDisk();

	TowerOfHanoi(char name) :_name(name) {};

};


//////////////////////////////////////////////////
////// �ȉ��쐬�ɂ������Ďg���Ă����֐� //////
//////////////////////////////////////////////////


// x�̓�����y�̓��։~�Ղ�ړ����܂�
// ���g��菬�����~�Ղ̏�Ɉړ����悤�Ƃ���ƃG���[
/// @para:x �ړ����̓�
/// @para:y �ړ���̓�
void move(TowerOfHanoi &x, TowerOfHanoi &y);


// ��x���󂩂ǂ�����Ԃ��܂�
/// @para:x ��
/// @ret:bool �� = true,����ȊO = false
bool empty(const TowerOfHanoi &x);


// ��x�ɐς܂�Ă���~�Ղ̐���Ԃ��܂�
/// @para:x ��
/// @ret:int �ς܂�Ă��鐔
bool size(const TowerOfHanoi &x);


// ��x�̓�e��\�����܂�
/// @para:x �\�����铃
void print(TowerOfHanoi x);


// ��x,y,z�̓�e��\�����܂�
/// @para:x �\�����铃
/// @para:y �\�����铃
/// @para:z �\�����铃
void print_all(const TowerOfHanoi x, const TowerOfHanoi y, const TowerOfHanoi z);
