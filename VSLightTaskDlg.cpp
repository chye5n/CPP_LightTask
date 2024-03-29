// VSLightTaskDlg.cpp : ���� ����
/**//*port�� �ȿ���*//**/
#include "stdafx.h"
#include "VSLightTask.h"
#include "VSLightTaskDlg.h"
#include "afxdialogex.h"
#include "define.h"
#include "portlight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVSLightTaskDlg ��ȭ ����

portlight aa;

CVSLightTaskDlg::CVSLightTaskDlg(BOOL check)
{

}

CVSLightTaskDlg::CVSLightTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVSLightTaskDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVSLightTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_comport);
	DDX_Control(pDX, IDC_LIST, m_listLog);
	DDX_Control(pDX, IDC_COMBO_CHANNEL1, m_combo_c1);
	DDX_Control(pDX, IDC_COMBO_CHANNEL2, m_combo_c2);
	DDX_Control(pDX, IDC_COMBO_CHANNEL3, m_combo_c3);
	DDX_Control(pDX, IDC_COMBO_CHANNEL4, m_combo_c4);
	DDX_Control(pDX, IDC_COMBO_CHANNEL5, m_combo_c5);
	DDX_Control(pDX, IDC_COMBO_CHANNEL6, m_combo_c6);
	DDX_Control(pDX, IDC_COMBO_CHANNEL7, m_combo_c7);
	DDX_Control(pDX, IDC_COMBO_CHANNEL8, m_combo_c8);
	DDX_Control(pDX, IDC_COMBO_BORATE, m_combo_borate);
}

BEGIN_MESSAGE_MAP(CVSLightTaskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_DRAWITEM()
	ON_CBN_DROPDOWN(IDC_COMBO_PORT, &CVSLightTaskDlg::OnCbnDropdownComboPort)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CVSLightTaskDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND1, &CVSLightTaskDlg::OnBnClickedButtonSend1)
	ON_BN_CLICKED(IDC_BUTTON_TOTALSEND, &CVSLightTaskDlg::OnBnClickedButtonTotalsend)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CVSLightTaskDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CVSLightTaskDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SEND2, &CVSLightTaskDlg::OnBnClickedButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_SEND3, &CVSLightTaskDlg::OnBnClickedButtonSend3)
	ON_BN_CLICKED(IDC_BUTTON_SEND4, &CVSLightTaskDlg::OnBnClickedButtonSend4)
	ON_BN_CLICKED(IDC_BUTTON_SEND5, &CVSLightTaskDlg::OnBnClickedButtonSend5)
	ON_BN_CLICKED(IDC_BUTTON_SEND6, &CVSLightTaskDlg::OnBnClickedButtonSend6)
	ON_BN_CLICKED(IDC_BUTTON_SEND7, &CVSLightTaskDlg::OnBnClickedButtonSend7)
	ON_BN_CLICKED(IDC_BUTTON_SEND8, &CVSLightTaskDlg::OnBnClickedButtonSend8)
END_MESSAGE_MAP()

// CVSLightTaskDlg �޽��� ó����

BOOL CVSLightTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	this->SetWindowText(theApp.m_pLight->GetControllerName());

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// Task ���� ���� Timer
	SetTimer(eTIMER_UpdateTaskStatus, 1000, NULL);	
	aa.getPort(m_comport);
	m_combo_c1.SetCurSel(0);
	m_combo_c2.SetCurSel(0);
	m_combo_c3.SetCurSel(0);
	m_combo_c4.SetCurSel(0);
	m_combo_c5.SetCurSel(0);
	m_combo_c6.SetCurSel(0);
	m_combo_c7.SetCurSel(0);
	m_combo_c8.SetCurSel(0);
	m_combo_borate.SetCurSel(1);
	m_comport.SetCurSel(0);
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CVSLightTaskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else { CDialogEx::OnPaint(); }
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CVSLightTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVSLightTaskDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	BOOL bHide = FALSE;
	BOOL bClose = FALSE;

	if(nID == SC_CLOSE	)
	{
		bHide = TRUE;
//#if defined(_DEBUG)
		if ( (GetKeyState(VK_SHIFT) < 0) && (AfxMessageBox(_T("���� �����Ͻðڽ��ϱ�?"), MB_YESNO|MB_ICONQUESTION)==IDYES) ) 
		{
			bClose = TRUE;
		}
//#else
//		bClose = TRUE;
//#endif
	}
	else if (nID == SC_MINIMIZE) { ShowWindow(SW_HIDE); }

	if (bClose) { CDialog::OnSysCommand(nID, lParam); }
	else if (bHide)
	{
		ShowWindow(SW_HIDE);
		return;

	}
	else { CDialogEx::OnSysCommand(nID, lParam); }

}

BOOL CVSLightTaskDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	return CDialogEx::PreTranslateMessage(pMsg);

}

void CVSLightTaskDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	//���ҽ� ����
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDI_ICON1;

	Shell_NotifyIcon(NIM_DELETE,&nid);
}

void CVSLightTaskDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	HWND hButton = NULL;

	switch (nIDEvent)
	{
	case eTIMER_UpdateTaskStatus:
		hButton	= ::GetDlgItem(m_hWnd, IDC_BTN_IPC_CONNECT);
		::InvalidateRect(hButton, NULL, FALSE);
		hButton	= ::GetDlgItem(m_hWnd, IDC_BTN_LIGHT);
		::InvalidateRect(hButton, NULL, FALSE);
		break;
	}	

	CDialogEx::OnTimer(nIDEvent);
}

void CVSLightTaskDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// nIDCtl = IDC��
	switch(nIDCtl)
	{
		case IDC_BTN_IPC_CONNECT:
		{
			if (theApp.GetIPCState()) { m_fnChangeBtnColor(lpDrawItemStruct, LIGHT_GREEN, DARK_GREEN); }
			else { m_fnChangeBtnColor(lpDrawItemStruct, LIGHT_RED, DARK_RED); }
		}
		break;
		case IDC_BTN_LIGHT:
		{
			if (theApp.GetLightState()) { m_fnChangeBtnColor(lpDrawItemStruct, LIGHT_GREEN, DARK_GREEN); }
			else { m_fnChangeBtnColor(lpDrawItemStruct, LIGHT_RED, DARK_RED); }
		}
		break;
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CVSLightTaskDlg::m_fnChangeBtnColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF colorBtn, COLORREF colorText)
{
	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);					//��ư�� dc���ϱ�
	rect = lpDrawItemStruct->rcItem;					//��ư���� ���ϱ�
	dc.Draw3dRect(&rect,WHITE,BLACK);					//��ư�� �ܰ��� �׸���

	dc.FillSolidRect(&rect, colorBtn);					//��ư����
	dc.SetBkColor(colorBtn);							//text�� ��׶��� ����
	dc.SetTextColor(colorText);							//texttort

	UINT state = lpDrawItemStruct->itemState;			//��ư���±��ϱ�
	if((state &ODS_SELECTED)) { dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT); }
	else { dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT); }

	TCHAR buffer[MAX_PATH];											//��ư�� text�� ������� �ӽù���
	ZeroMemory(buffer,MAX_PATH);									//�����ʱ�ȭ
	::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH);	//��ư�� text���
	dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);	//��ư�� text�ֱ�
	dc.Detach();													//��ư�� dc Ǯ���ֱ�
}

void CVSLightTaskDlg::OnCbnDropdownComboPort()	//Port Combobox�� ���� ���
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	aa.getPort(m_comport);
}

void CVSLightTaskDlg::OnBnClickedButtonConnect()	//Connect Button�� ���� ���
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_BORATE, baudRate);

	// �ø��� ��Ʈ �ڵ�
	HANDLE hSerialPort = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSerialPort != INVALID_HANDLE_VALUE)
	{
		// DCB ����ü ����
		DCB dcbSerialParams = { 0 };
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

		// ������ �ø��� ��Ʈ ������ ����
		if (GetCommState(hSerialPort, &dcbSerialParams))
		{
			// ������Ʈ ����
			dcbSerialParams.BaudRate = _ttoi(baudRate);

			// ������ ��Ʈ, �и�Ƽ, ���� ��Ʈ ���� (8-N-1 ����)
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.Parity = NOPARITY;
			dcbSerialParams.StopBits = ONESTOPBIT;

			// ���ο� ������ �ø��� ��Ʈ�� ����
			if (SetCommState(hSerialPort, &dcbSerialParams)) { m_listLog.InsertString(-1, _T("����")); CHECK = true; }	// ���� ����
			else { m_listLog.InsertString(-1, _T("���� ����: SetCommState ����")); CHECK = false; }						// ���� ����
		}
		else { m_listLog.InsertString(-1, _T("���� ����: GetCommState ����")); CHECK = false; }	// ���� ����

		// �ø��� ��Ʈ �ڵ� �ݱ�
		CloseHandle(hSerialPort);
	}
	else { m_listLog.InsertString(-1, _T("���� ����: CreateFile ����")); CHECK = false; } // ���� ����
}

void CVSLightTaskDlg::OnBnClickedButtonSend1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel1;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL1, channel1);

	int intChannel1 = _tcstol(channel1, nullptr, 10);
	int a = (intChannel1 / 100) + 48;
	int b = ((intChannel1 / 10) % 10) + 48;
	int c = ((intChannel1 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(48, a, b, c) + i);
	}
	
	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel2;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL2, channel2);

	int intChannel2 = _tcstol(channel2, nullptr, 10);
	int a = (intChannel2 / 100) + 48;
	int b = ((intChannel2 / 10) % 10) + 48;
	int c = ((intChannel2 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(49, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel3;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL3, channel3);

	int intChannel3 = _tcstol(channel3, nullptr, 10);
	int a = (intChannel3 / 100) + 48;
	int b = ((intChannel3 / 10) % 10) + 48;
	int c = ((intChannel3 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(50, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel4;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL4, channel4);

	int intChannel4 = _tcstol(channel4, nullptr, 10);
	int a = (intChannel4 / 100) + 48;
	int b = ((intChannel4 / 10) % 10) + 48;
	int c = ((intChannel4 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(51, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel5;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL5, channel5);

	int intChannel5 = _tcstol(channel5, nullptr, 10);
	int a = (intChannel5 / 100) + 48;
	int b = ((intChannel5 / 10) % 10) + 48;
	int c = ((intChannel5 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(52, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel6;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL6, channel6);

	int intChannel6 = _tcstol(channel6, nullptr, 10);
	int a = (intChannel6 / 100) + 48;
	int b = ((intChannel6 / 10) % 10) + 48;
	int c = ((intChannel6 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(53, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel7;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL7, channel7);

	int intChannel7 = _tcstol(channel7, nullptr, 10);
	int a = (intChannel7 / 100) + 48;
	int b = ((intChannel7 / 10) % 10) + 48;
	int c = ((intChannel7 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(54, a, b, c) + i);
	}

	// �ø��� ��Ʈ �ڵ�
	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel8;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL8, channel8);

	int intChannel8 = _tcstol(channel8, nullptr, 10);
	int a = (intChannel8 / 100) + 48;
	int b = ((intChannel8 / 10) % 10) + 48;
	int c = ((intChannel8 % 10)) + 48;

	unsigned char AllSend[7];
	for (int i = 0; i < 7; i++)
	{
		AllSend[i] = *(aa.LightSetting(55, a, b, c) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonTotalsend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL1, channel1);
	GetDlgItemText(IDC_COMBO_CHANNEL2, channel2);
	GetDlgItemText(IDC_COMBO_CHANNEL3, channel3);
	GetDlgItemText(IDC_COMBO_CHANNEL4, channel4);
	GetDlgItemText(IDC_COMBO_CHANNEL5, channel5);
	GetDlgItemText(IDC_COMBO_CHANNEL6, channel6);
	GetDlgItemText(IDC_COMBO_CHANNEL7, channel7);
	GetDlgItemText(IDC_COMBO_CHANNEL8, channel8);

	int intChannel1 = _tcstol(channel1, nullptr, 10);
	int intChannel2 = _tcstol(channel2, nullptr, 10);
	int intChannel3 = _tcstol(channel3, nullptr, 10);
	int intChannel4 = _tcstol(channel4, nullptr, 10);
	int intChannel5 = _tcstol(channel5, nullptr, 10);
	int intChannel6 = _tcstol(channel6, nullptr, 10);
	int intChannel7 = _tcstol(channel7, nullptr, 10);
	int intChannel8 = _tcstol(channel8, nullptr, 10);

	unsigned char AllSend[14];
	for (int i = 0; i < 14; i++)
	{
		AllSend[i] = *(aa.LightTotalSetting(0, intChannel1, intChannel2, intChannel3, intChannel4, intChannel5, intChannel6, intChannel7, intChannel8) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName, baudRate, channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_CHANNEL1, channel1);
	GetDlgItemText(IDC_COMBO_CHANNEL2, channel2);
	GetDlgItemText(IDC_COMBO_CHANNEL3, channel3);
	GetDlgItemText(IDC_COMBO_CHANNEL4, channel4);
	GetDlgItemText(IDC_COMBO_CHANNEL5, channel5);
	GetDlgItemText(IDC_COMBO_CHANNEL6, channel6);
	GetDlgItemText(IDC_COMBO_CHANNEL7, channel7);
	GetDlgItemText(IDC_COMBO_CHANNEL8, channel8);

	int intChannel1 = _tcstol(channel1, nullptr, 10);
	int intChannel2 = _tcstol(channel2, nullptr, 10);
	int intChannel3 = _tcstol(channel3, nullptr, 10);
	int intChannel4 = _tcstol(channel4, nullptr, 10);
	int intChannel5 = _tcstol(channel5, nullptr, 10);
	int intChannel6 = _tcstol(channel6, nullptr, 10);
	int intChannel7 = _tcstol(channel7, nullptr, 10);
	int intChannel8 = _tcstol(channel8, nullptr, 10);

	unsigned char AllSend[14];
	for (int i = 0; i < 14; i++)
	{
		AllSend[i] = *(aa.LightTotalSetting(87, intChannel1, intChannel2, intChannel3, intChannel4, intChannel5, intChannel6, intChannel7, intChannel8) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString portName;
	GetDlgItemText(IDC_COMBO_PORT, portName);

	unsigned char AllSend[14];
	for (int i = 0; i < 14; i++)
	{
		AllSend[i] = *(aa.LightTotalSetting(83, 0, 0, 0, 0, 0, 0, 0, 0) + i);
	}

	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::AddValueTocomport(const CString& value)
{
	m_comport.AddString(value);
}