
// C_LUADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "C_LUA.h"
#include "C_LUADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CC_LUADlg �Ի���



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


// CC_LUADlg ��Ϣ�������

BOOL CC_LUADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CC_LUADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CC_LUADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









int CC_LUADlg::luaadd(int x, int y)
{
	int sum;
	/*������*/
	lua_getglobal(L, "add");
	/*������ջ*/
	lua_pushnumber(L, x);
	/*������ջ*/
	lua_pushnumber(L, y);
	/*��ʼ���ú�������2��������1������ֵ*/
	lua_call(L, 2, 1);
	/*ȡ������ֵ*/
	sum = (int)lua_tonumber(L, -1);
	/*�������ֵ��ջ*/
	lua_pop(L, 1);
	return sum;
}

void CC_LUADlg::OnBnClickedButton1()
{
	int sum;
	L = luaL_newstate();  /* ����lua״̬�� */
	luaL_openlibs(L);   /* ��Lua״̬��������Lua��׼�� */
						/*����lua�ű�*/
	luaL_dofile(L, "Test.lua");
	/*����C�����������������lua����*/
	sum = luaadd(99, 10);
	printf("The sum is %d \n", sum);
	/*���Lua*/
	lua_close(L);
}






int CC_LUADlg::l_SayHello(lua_State *L)
{
	const char *d = luaL_checkstring(L, 1);		//��ȡ�������ַ�������
	int len = strlen(d);
	char str[100] = "hello ";
	strcat_s(str, d);
	lua_pushstring(L, str);						/* ���ظ�lua��ֵѹջ */
	return 1;
}

void CC_LUADlg::OnBnClickedButton2()
{
	lua_State *L = luaL_newstate();				/* ����lua״̬�� */
	luaL_openlibs(L);							/* ��Lua״̬��������Lua��׼�� */
	lua_register(L, "SayHello", l_SayHello);	//ע��C������lua

	const char* testfunc = "print(SayHello('0.0'))";//lua�е���c����
	if (luaL_dostring(L, testfunc))				// ִ��Lua���
		printf("Failed to invoke.\n");

	/*���Lua*/
	lua_close(L);
}
