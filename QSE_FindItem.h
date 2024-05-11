#pragma once


// QSE_FindItem 대화 상자입니다.

class CQSE_FindItem : public CDialog
{
	DECLARE_DYNAMIC(CQSE_FindItem)

public:
	CQSE_FindItem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CQSE_FindItem();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_QSE_FINDITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 검색할 문자가 들어가는 곳
	CString m_str;
	virtual BOOL OnInitDialog();
};
