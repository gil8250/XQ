#pragma once


// QSE_FindItem ��ȭ �����Դϴ�.

class CQSE_FindItem : public CDialog
{
	DECLARE_DYNAMIC(CQSE_FindItem)

public:
	CQSE_FindItem(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CQSE_FindItem();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_QSE_FINDITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// �˻��� ���ڰ� ���� ��
	CString m_str;
	virtual BOOL OnInitDialog();
};
