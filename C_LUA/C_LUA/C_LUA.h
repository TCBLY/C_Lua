
// C_LUA.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CC_LUAApp: 
// �йش����ʵ�֣������ C_LUA.cpp
//

class CC_LUAApp : public CWinApp
{
public:
	CC_LUAApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CC_LUAApp theApp;