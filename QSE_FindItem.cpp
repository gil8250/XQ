// QSE_FindItem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "XQuestScriptEditor.h"
#include "QSE_FindItem.h"
#include ".\qse_finditem.h"


// QSE_FindItem 대화 상자입니다.

IMPLEMENT_DYNAMIC(CQSE_FindItem, CDialog)
CQSE_FindItem::CQSE_FindItem(CWnd* pParent /*=NULL*/)
	: CDialog(CQSE_FindItem::IDD, pParent)
	, m_str(_T(""))
{
}

CQSE_FindItem::~CQSE_FindItem()
{
}

void CQSE_FindItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STR, m_str); //Dialog Data eXchange 
	DDV_MaxChars(pDX, m_str, 30);
}


BEGIN_MESSAGE_MAP(CQSE_FindItem, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// QSE_FindItem 메시지 처리기입니다.

void CQSE_FindItem::OnBnClickedOk()
{
	
	UpdateData(TRUE); //IDC_STR->m_str 
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

BOOL CQSE_FindItem::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	UpdateData(FALSE);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
