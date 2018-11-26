
// B_Tree.h : B_Tree Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "B_TreeNode.h"
#include <math.h>

// CB_TreeApp:
// �йش����ʵ�֣������ B_Tree.cpp
//

class CB_TreeApp : public CWinApp
{
public:
	CB_TreeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CB_TreeApp theApp;
