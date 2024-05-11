// XDBConnectDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainFrm.h"
#include "QuestScriptEditorFormView.h"
#include "XDBConnectDialog.h"

// _XDBConnectDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(_XDBConnectDialog, CDialog)
_XDBConnectDialog::_XDBConnectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(_XDBConnectDialog::IDD, pParent)
{
	m_IPAdressString = _T("0.0.0.0");
	m_ID = _T("");
	m_PWD = _T("");
	m_Port = 1043;	
	m_DataBaseNameIndex = 0;
}

_XDBConnectDialog::~_XDBConnectDialog()
{
}

void _XDBConnectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IDEDIT, m_ID);
	DDX_Text(pDX, IDC_PWDEDIT, m_PWD);
	DDX_Text(pDX, IDC_PORTEDIT, m_Port);
	DDX_Control(pDX, IDC_SERVERIPADDRESS, m_IPControl);
	DDX_Control(pDX, IDC_PWDEDIT, m_PasswordEditCtrl);
	DDX_CBIndex(pDX, IDC_SERVERLISTCOMBO, m_DataBaseNameIndex);
}


BEGIN_MESSAGE_MAP(_XDBConnectDialog, CDialog)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_SERVERIPADDRESS, OnIpnFieldchangedServeripaddress)
	ON_EN_CHANGE(IDC_IDEDIT, OnEnChangeIdedit)
	ON_EN_CHANGE(IDC_PWDEDIT, OnEnChangePwdedit)
	ON_EN_CHANGE(IDC_PORTEDIT, OnEnChangePortedit)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)	
	ON_CBN_SELENDOK(IDC_SERVERLISTCOMBO, OnCbnSelendokServerlistcombo)
END_MESSAGE_MAP()


// _XDBConnectDialog 메시지 처리기입니다.

void _XDBConnectDialog::OnIpnFieldchangedServeripaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	
	UpdateData();

	*pResult = 0;
}

void _XDBConnectDialog::OnEnChangeIdedit()
{
	UpdateData();
}

void _XDBConnectDialog::OnEnChangePwdedit()
{
	UpdateData();
}

void _XDBConnectDialog::OnEnChangePortedit()
{
	UpdateData();
}

BOOL _XDBConnectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
#ifdef  _DEBUG
	m_IPControl.SetAddress( 221, 147, 34, 38 );	
	UpdateData(TRUE);
	m_ID = _T("$indy21");
	m_PWD = _T("_theone_");
	UpdateData(FALSE);
#endif
	*/

	CMainFrame* pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	if( pMainFrame )
	{
		m_ID = pMainFrame->m_DBConnectUID;
		m_PWD = pMainFrame->m_DBConnectPWD;
		m_Port = pMainFrame->m_DBPort;

		if( wcslen( pMainFrame->m_DBServerIP ) > 0  )
		{
			CString _ipadress = pMainFrame->m_DBServerIP;
			_ipadress.Replace( _T('.'), _T('\t') );

			DWORD _a,_b,_c,_d;
			swscanf( _ipadress, _T("%d %d %d %d"), &_a, &_b, &_c, &_d );
            
			m_IPControl.SetAddress( _a, _b, _c, _d );
			m_IPAdressString = pMainFrame->m_DBServerIP;
		}

		m_DataBaseNameIndex = g_DataBaseNameIndex;
		
		UpdateData(FALSE);

		/*
		if( m_ID.GetLength() > 0 )
		{
			m_PasswordEditCtrl.SetFocus();
		}
		*/
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void _XDBConnectDialog::OnBnClickedOk()
{

	if( m_DataBaseNameIndex < 0 )
	{
		AfxMessageBox( _T("Please select a data base.") );
		return;
	}

	BYTE add1,add2,add3,add4;
	m_IPControl.GetAddress( add1,add2,add3,add4 );
	m_IPAdressString.Format( _T("%d.%d.%d.%d"), add1,add2,add3,add4 );	
	g_DataBaseNameIndex = m_DataBaseNameIndex;
	OnOK();
}


void _XDBConnectDialog::OnCbnSelendokServerlistcombo()
{
	UpdateData();
}

