#include "stdafx.h"
#include "TowerOfHanoi.h"

/**
* @file TowerOfHanoi.cpp
* @brief �~���������e�J������p���ċ��߂�v���O������܂Ƃ߂��\�[�X�ł���B
* @author ��
* @date 2016/12/15
*/

/*
�n�m�C�̓��i�o�������̓��@���[�J�X�^���[�Ƃ�Ă΂��B�j

3�{�̍Y�����A���A�E�ɂ���B
���S�Ɍ����J�����~�Ղ�N����B
�~�Ղ͂��ꂼ��傫�����قȂ�B
�ŏ��͍����̍Y�ɏ��������ŉ~�Ղ��ς܂�Ă���B
�~�Ղ͈��Ɉꖇ���ǂꂩ�̍Y�Ɉړ����邱�Ƃ��ł���B
�����ȉ~�Ղ̏�ɑ傫�ȉ~�Ղ�悹�邱�Ƃ͂ł��Ȃ��B
�S�Ẳ~�Ղ�E�̍Y�ֈړ�����B
*/

#define LEFT 0
#define CENTER 1
#define RIGHT 2

int TowerOfHanoiDo(int disc_count) {

	//int* discs;
	//int i;

	//discs = (int*) malloc(sizeof(int) * disc_count);
	
	//for (i = 0; i < disc_count; i++) discs[i] = 0;
	
	Move(disc_count, "���̍Y", "���̍Y", "�E�̍Y");

	//free(discs);
	return 0;
}

void Move(int disc_count, char* a, char* b, char* c) {
	if (0 < disc_count) {
		Move(disc_count - 1, a, c, b);
		printf("%d�Ԃ̉~�Ղ�%s����%s�Ɉړ�\n", disc_count, a, b);
		Move(disc_count - 1, c, b, a);

	}
}
