
// C_LUADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "C_LUA.h"
#include "C_LUADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CC_LUADlg 对话框



CC_LUADlg::CC_LUADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_C_LUA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CC_LUADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CC_LUADlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CC_LUADlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CC_LUADlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CC_LUADlg 消息处理程序

BOOL CC_LUADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CC_LUADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CC_LUADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









int CC_LUADlg::luaadd(int x, int y)
{
	int sum;
	/*函数名*/
	lua_getglobal(L, "add");
	/*参数入栈*/
	lua_pushnumber(L, x);
	/*参数入栈*/
	lua_pushnumber(L, y);
	/*开始调用函数，有2个参数，1个返回值*/
	lua_call(L, 2, 1);
	/*取出返回值*/
	sum = (int)lua_tonumber(L, -1);
	/*清除返回值的栈*/
	lua_pop(L, 1);
	return sum;
}

void CC_LUADlg::OnBnClickedButton1()
{
	int sum;
	L = luaL_newstate();  /* 创建lua状态机 */
	luaL_openlibs(L);   /* 打开Lua状态机中所有Lua标准库 */
						/*加载lua脚本*/
	luaL_dofile(L, "Test.lua");
	/*调用C函数，这个里面会调用lua函数*/
	sum = luaadd(99, 10);
	printf("The sum is %d \n", sum);
	/*清除Lua*/
	lua_close(L);
}






int CC_LUADlg::l_SayHello(lua_State *L)
{
	const char *d = luaL_checkstring(L, 1);		//获取参数，字符串类型
	int len = strlen(d);
	char str[100] = "hello ";
	strcat_s(str, d);
	lua_pushstring(L, str);						/* 返回给lua的值压栈 */
	return 1;
}

void CC_LUADlg::OnBnClickedButton2()
{
	lua_State *L = luaL_newstate();				/* 创建lua状态机 */
	luaL_openlibs(L);							/* 打开Lua状态机中所有Lua标准库 */
	lua_register(L, "SayHello", l_SayHello);	//注册C函数到lua

	const char* testfunc = "print(SayHello('0.0'))";//lua中调用c函数
	if (luaL_dostring(L, testfunc))				// 执行Lua命令。
		printf("Failed to invoke.\n");

	/*清除Lua*/
	lua_close(L);
}
