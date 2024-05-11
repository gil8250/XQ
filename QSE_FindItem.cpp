// QSE_FindItem.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "XQuestScriptEditor.h"
#include "QSE_FindItem.h"
#include ".\qse_finditem.h"


// QSE_FindItem ��ȭ �����Դϴ�.

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


// QSE_FindItem �޽��� ó�����Դϴ�.

void CQSE_FindItem::OnBnClickedOk()
{
	
	UpdateData(TRUE); //IDC_STR->m_str 
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

BOOL CQSE_FindItem::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	UpdateData(FALSE);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
