// stdafx.h : �� ������� �ʰ� ���� ����ϴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Windows ������� ���� ������ �ʴ� ������ ���ܽ�ŵ�ϴ�.
#endif

// �Ʒ� ������ �÷������� �켱�ϴ� �÷����� ������� �ϴ� ��� ���� ���Ǹ� �����Ͻʽÿ�.
// �ٸ� �÷����� ���Ǵ� �ش� ���� �ֽ� ������ MSDN�� �����Ͻʽÿ�.
#ifndef WINVER				// Windows 95 �� Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define WINVER 0x0400		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT		// Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINNT 0x0400		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_IE			// IE 4.0 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_IE 0x0400	// IE 5.0 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ���
#include <afxext.h>         // MFC �ͽ��ټ�
#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ����

#include <afxdtctl.h>		// Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC ����
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows ���� ��Ʈ�ѿ� ���� MFC ����
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atldbcli.h>  //OLEDB Consumer �� ���� ���ø� ���̺귯��
#include "afxcmn.h"

#include "resource.h"

#define _XDEF_CATEGORYMAXSIZE	100
#define _XDEF_MAXSTRINGSIZE		2500

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <hash_map>
#include <algorithm>

#include "XOLEDBConnector.h"

typedef enum _XLANGUAGE_INDEX
{
	_XLANGUAGE_INDEX_KOREAN = 0,
	_XLANGUAGE_INDEX_VIETNAMESE,
	_XLANGUAGE_INDEX_TAIWANESE,
	_XLANGUAGE_INDEX_ENGLISH,
	_XLANGUAGE_INDEX_CHINESE,
	_XLANGUAGE_INDEX_JAPANESE,
	_XLANGUAGE_INDEX_RUSSIAN,
	_XLANGUAGE_INDEX_THAI,
	_XLANGUAGE_MAXCOUNT
};

#define _XCHECKDBCONNECTED if( !g_LocalizeDB.IsConnected() ){ _ISM( _T("WARNING : Not connected to localize database") ); return; }
#define _XCHECKDBCONNECTED_RETBOOL if( !g_LocalizeDB.IsConnected() ){ _ISM( _T("WARNING : Not connected to localize database") ); return FALSE; }

#define _XDEF_MODPERMISSION_VIEWER		0
#define _XDEF_MODPERMISSION_KOREAN		1
#define _XDEF_MODPERMISSION_VIETNAMESE	2
#define _XDEF_MODPERMISSION_TAIWANESE	4
#define _XDEF_MODPERMISSION_ENGLISH		8
#define _XDEF_MODPERMISSION_CHINESE		16
#define _XDEF_MODPERMISSION_JAPANESE	32
#define _XDEF_MODPERMISSION_RUSSIAN		64
#define _XDEF_MODPERMISSION_THAI		128

#define _XDEF_MODPERMISSION_ADMIN		256

extern DWORD  g_ModifyPermission;

extern TCHAR*   g_DataBaseName[];
extern int g_DataBaseNameIndex;













