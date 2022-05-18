
// C_LUADlg.h : 头文件
//

#pragma once
#include "lua.hpp"

// CC_LUADlg 对话框
class CC_LUADlg : public CDialogEx
{
// 构造
public:
	CC_LUADlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_C_LUA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
