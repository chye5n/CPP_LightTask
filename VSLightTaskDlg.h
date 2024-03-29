
// VSLightTaskDlg.h : 헤더 파일
//

#pragma once

// for Tray Icon - User Message
#define	WM_TRAYICON_MSG	WM_USER + 1
#define WM_PRINT_UI_LOG_MSG_UNICODE		WM_USER + 2
#define	WM_PRINT_UI_LOG_MSG_MULTI_BYTE	WM_USER + 3

// Timer
enum {
	eTIMER_UpdateTaskStatus	= 0,	// Task 상태 UI 표시 Timer
};

#define LIGHT_RED	RGB(255,153,153)
#define DARK_RED	RGB(102,0,0)
#define LIGHT_GREEN	RGB(204,255,153)
#define DARK_GREEN	RGB(0,51,0)
#define DARK_GRAY	RGB(51,51,51)
#define WHITE		RGB(255,255,255)
#define BLACK		RGB(0,0,0)

// CVSLightTaskDlg 대화 상자
class CVSLightTaskDlg : public CDialogEx
{
// 생성입니다.
public:
	CVSLightTaskDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CVSLightTaskDlg(BOOL check);

// 대화 상자 데이터입니다.
	enum { IDD = 102 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.	


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
private:
	void m_fnChangeBtnColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF colorBtn, COLORREF colorText);	
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CComboBox m_comport;
	void AddValueTocomport(const CString& value);
	afx_msg void OnCbnDropdownComboPort();
	CComboBox& getComport() { return m_comport; }
	afx_msg void OnBnClickedButtonConnect();
	CListBox m_listLog;
	CListBox& getList() { return m_listLog; }
	afx_msg void OnBnClickedButtonSend1();
	afx_msg void OnBnClickedButtonTotalsend();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSend2();
	afx_msg void OnBnClickedButtonSend3();
	afx_msg void OnBnClickedButtonSend4();
	afx_msg void OnBnClickedButtonSend5();
	afx_msg void OnBnClickedButtonSend6();
	afx_msg void OnBnClickedButtonSend7();
	afx_msg void OnBnClickedButtonSend8();
	CComboBox m_combo_c1;
	CComboBox m_combo_c2;
	CComboBox m_combo_c3;
	CComboBox m_combo_c4;
	CComboBox m_combo_c5;
	CComboBox m_combo_c6;
	CComboBox m_combo_c7;
	CComboBox m_combo_c8;
	CComboBox m_combo_borate;
	BOOL CHECK = false;
};
