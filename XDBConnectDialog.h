#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// _XDBConnectDialog 대화 상자입니다.

class _XDBConnectDialog : public CDialog
{
	DECLARE_DYNAMIC(_XDBConnectDialog)

public:
	_XDBConnectDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~_XDBConnectDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DBCONNECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedServeripaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeIdedit();
	afx_msg void OnEnChangePwdedit();	
	CString m_ID;
	CString m_PWD;
	afx_msg void OnEnChangePortedit();
	DWORD m_Port;
	CIPAddressCtrl m_IPControl;
	CString		   m_IPAdressString;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CEdit m_PasswordEditCtrl;
	int m_DataBaseNameIndex;
	afx_msg void OnCbnSelendokServerlistcombo();
};
