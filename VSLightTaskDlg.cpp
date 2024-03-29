// VSLightTaskDlg.cpp : 구현 파일
/**//*port가 안열림*//**/
#include "stdafx.h"
#include "VSLightTask.h"
#include "VSLightTaskDlg.h"
#include "afxdialogex.h"
#include "define.h"
#include "portlight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVSLightTaskDlg 대화 상자

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

// CVSLightTaskDlg 메시지 처리기

BOOL CVSLightTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	this->SetWindowText(theApp.m_pLight->GetControllerName());

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// Task 상태 갱신 Timer
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
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CVSLightTaskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else { CDialogEx::OnPaint(); }
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CVSLightTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVSLightTaskDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BOOL bHide = FALSE;
	BOOL bClose = FALSE;

	if(nID == SC_CLOSE	)
	{
		bHide = TRUE;
//#if defined(_DEBUG)
		if ( (GetKeyState(VK_SHIFT) < 0) && (AfxMessageBox(_T("정말 종료하시겠습니까?"), MB_YESNO|MB_ICONQUESTION)==IDYES) ) 
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CDialogEx::PreTranslateMessage(pMsg);

}

void CVSLightTaskDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//리소스 해제
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDI_ICON1;

	Shell_NotifyIcon(NIM_DELETE,&nid);
}

void CVSLightTaskDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// nIDCtl = IDC값
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
	dc.Attach(lpDrawItemStruct->hDC);					//버튼의 dc구하기
	rect = lpDrawItemStruct->rcItem;					//버튼영역 구하기
	dc.Draw3dRect(&rect,WHITE,BLACK);					//버튼의 외곽선 그리기

	dc.FillSolidRect(&rect, colorBtn);					//버튼색상
	dc.SetBkColor(colorBtn);							//text의 백그라운드 색상
	dc.SetTextColor(colorText);							//texttort

	UINT state = lpDrawItemStruct->itemState;			//버튼상태구하기
	if((state &ODS_SELECTED)) { dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT); }
	else { dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT); }

	TCHAR buffer[MAX_PATH];											//버튼의 text를 얻기위한 임시버퍼
	ZeroMemory(buffer,MAX_PATH);									//버퍼초기화
	::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH);	//버튼의 text얻기
	dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);	//버튼의 text넣기
	dc.Detach();													//버튼의 dc 풀어주기
}

void CVSLightTaskDlg::OnCbnDropdownComboPort()	//Port Combobox를 내릴 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	aa.getPort(m_comport);
}

void CVSLightTaskDlg::OnBnClickedButtonConnect()	//Connect Button을 누른 경우
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString portName, baudRate;
	GetDlgItemText(IDC_COMBO_PORT, portName);
	GetDlgItemText(IDC_COMBO_BORATE, baudRate);

	// 시리얼 포트 핸들
	HANDLE hSerialPort = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSerialPort != INVALID_HANDLE_VALUE)
	{
		// DCB 구조체 설정
		DCB dcbSerialParams = { 0 };
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

		// 현재의 시리얼 포트 설정을 얻어옴
		if (GetCommState(hSerialPort, &dcbSerialParams))
		{
			// 보레이트 설정
			dcbSerialParams.BaudRate = _ttoi(baudRate);

			// 데이터 비트, 패리티, 정지 비트 설정 (8-N-1 설정)
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.Parity = NOPARITY;
			dcbSerialParams.StopBits = ONESTOPBIT;

			// 새로운 설정을 시리얼 포트에 적용
			if (SetCommState(hSerialPort, &dcbSerialParams)) { m_listLog.InsertString(-1, _T("연결")); CHECK = true; }	// 연결 성공
			else { m_listLog.InsertString(-1, _T("연결 실패: SetCommState 실패")); CHECK = false; }						// 연결 실패
		}
		else { m_listLog.InsertString(-1, _T("연결 실패: GetCommState 실패")); CHECK = false; }	// 연결 실패

		// 시리얼 포트 핸들 닫기
		CloseHandle(hSerialPort);
	}
	else { m_listLog.InsertString(-1, _T("연결 실패: CreateFile 실패")); CHECK = false; } // 연결 실패
}

void CVSLightTaskDlg::OnBnClickedButtonSend1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	// 시리얼 포트 핸들
	m_listLog.InsertString(-1, aa.SerialPortHandle(portName, AllSend, sizeof(AllSend), CHECK));
}

void CVSLightTaskDlg::OnBnClickedButtonSend8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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