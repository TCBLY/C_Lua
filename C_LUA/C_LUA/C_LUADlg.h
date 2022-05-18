
// C_LUADlg.h : ͷ�ļ�
//

#pragma once
#include "lua.hpp"

// CC_LUADlg �Ի���
class CC_LUADlg : public CDialogEx
{
// ����
public:
	CC_LUADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_C_LUA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	lua_State* L;
	int luaadd(int x, int y);

	static int l_SayHello(lua_State *L);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
