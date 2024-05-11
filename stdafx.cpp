// stdafx.cpp : 표준 포함 파일을 포함하는 소스 파일입니다.
// XQuestScriptEditor.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj는 미리 컴파일된 형식 정보를 포함합니다.

#include "stdafx.h"


DWORD g_ModifyPermission = 0;

TCHAR*   g_DataBaseName[] = 
{
	_T("NDLocalizeDB2"),
};

int g_DataBaseNameIndex = 0;