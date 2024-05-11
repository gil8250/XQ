#include "StdAfx.h"
#include "XOLEDBConnector.h"

_XSTRINGSECTIONINFODATA g_ScriptStringList[_XDEF_CATEGORYMAXSIZE];
_XOLEDBConnector	g_LocalizeDB;

struct DELETEOBJECT
{
	template <typename T>
		void operator()(T* ptr) const 
	{
		if(ptr)
			delete ptr;
	}
};

void _XSTRINGSECTIONINFODATA::Release(void)
{
	std::for_each( m_StringVector.begin(), m_StringVector.end(), DELETEOBJECT() );
	
	m_StringVector.clear();
	m_StringMap.clear();
	//m_StringMap_UID.clear();
}

void _XSTRINGSECTIONINFODATA::Insert( CLocalizeDataInfo* pObject )
{
	m_StringVector.push_back( pObject );
	m_StringMap.insert(smdef_XTEXTSTRING_INFOMAP::value_type(pObject->resourceid, pObject ));
	//m_StringMap_UID.insert(smdef_XTEXTSTRING_INFOMAP::value_type(pObject->stringuid, pObject ));
	//if( m_MaxResourceID < pObject->resourceid )
	//	m_MaxResourceID = pObject->resourceid;
}

void _XSTRINGSECTIONINFODATA::Delete( CLocalizeDataInfo* pObject )
{
	//m_StringVector.erase( pObject );
	_ISM(_T("ERROR!"));
}

void _XSTRINGSECTIONINFODATA::Delete( int RID )
{
	CLocalizeDataInfo* pObject = GetObject( RID );
	
	if( pObject )
	{
		svdef_XTEXTSTRING_INFO::iterator iter;
		for(iter = m_StringVector.begin() ; iter != m_StringVector.end() ; iter++)
		{
			//CLocalizeDataInfo* plocalizeinfo = (*iter);
			if( (*iter)->resourceid == RID )
			{
				m_StringMap.erase( pObject->resourceid );
				//m_StringMap_UID.erase( RID );
				m_StringVector.erase( iter );
				break;
			}
		}
	}
}

void _XSTRINGSECTIONINFODATA::Clear( void )
{
	std::for_each( m_StringVector.begin(), m_StringVector.end(), DELETEOBJECT() );

	m_StringVector.clear();
	m_StringMap.clear();
	//m_StringMap_UID.clear();

}

int _XSTRINGSECTIONINFODATA::GetMaxResourceID( void )
{
	int maxresid = -1;

	svdef_XTEXTSTRING_INFO::iterator iter;
	for(iter = m_StringVector.begin() ; iter != m_StringVector.end() ; iter++)
	{
		CLocalizeDataInfo* plocalizeinfo = (*iter);
		if(plocalizeinfo)
		{
            if( plocalizeinfo->resourceid > maxresid )
			{
				maxresid = plocalizeinfo->resourceid;
			}
		}
	}

	return maxresid;
}

CLocalizeDataInfo* _XSTRINGSECTIONINFODATA::GetObject( int ResourceID )
{
	smdef_XTEXTSTRING_INFOMAP::iterator it = m_StringMap.find(ResourceID);
	if(it != m_StringMap.end())
	{
		return (*it).second;
	}

	return NULL;
}

int	_XSTRINGSECTIONINFODATA::FindString( LPCTSTR szString )
{
	CString szCompleteString = szString;
	szCompleteString.Replace( _T('\''), _T('"') );

	svdef_XTEXTSTRING_INFO::iterator iter;
	for(iter = m_StringVector.begin() ; iter != m_StringVector.end() ; iter++)
	{
		CLocalizeDataInfo* plocalizeinfo = (*iter);
		if(plocalizeinfo)
		{
			if( wcscmp( szCompleteString, plocalizeinfo->KoreanString ) == 0 )
			{
				return plocalizeinfo->resourceid;
			}
		}
	}

	_ISM( _T("Can't find text [%s]"), szString );
	return -1;
}

/*
CLocalizeDataInfo* _XSTRINGSECTIONINFODATA::GetObject_UID( int UID )
{
	smdef_XTEXTSTRING_INFOMAP::iterator it = m_StringMap_UID.find(UID);
	if(it != m_StringMap_UID.end())
	{
		return (*it).second;
	}

	return NULL;
}
*/

_XOLEDBConnector::_XOLEDBConnector(void)
{
	m_Connected = FALSE;
}

_XOLEDBConnector::~_XOLEDBConnector(void)
{
	
}


BOOL _XOLEDBConnector::Initialize( LPCTSTR serverip, long port, LPCTSTR uid, LPCTSTR pwd, LPCTSTR dbname )
{
	m_DBName = dbname;
	m_Connected = FALSE;

	_ISM(_T("Create DB Connector [%s]..."), m_DBName);

	CDBPropSet	dbinitdata(DBPROPSET_DBINIT);

	HRESULT hr = CoInitialize(0);
	if(FAILED(hr))
	{
		_ISM(_T("Failed : CoInitialize"));
		return FALSE;
	}

	TCHAR propertiesstring[1024];
	CString szPropertiesString;

	szPropertiesString.Format( _T("PROVIDER=SQLOLEDB;SERVER=%s;UID=%s;PWD=%s;DATABASE=%s"), serverip, uid, pwd, dbname );
	memset( propertiesstring, 0, sizeof(TCHAR) * 1024 );
	wcscpy( propertiesstring, szPropertiesString.GetBuffer() );
	
	dbinitdata.AddProperty(DBPROP_INIT_PROMPT, (short)4);   //DBPROP_INIT_PROMPT->
	dbinitdata.AddProperty(DBPROP_INIT_PROVIDERSTRING, propertiesstring);
	dbinitdata.AddProperty(DBPROP_INIT_LCID, (long)port);   //DBPROP_INIT_LCID ->Locale Identifier
	
	hr = m_DataSource.Open(_T("SQLOLEDB"), &dbinitdata);

	if(FAILED(hr))  
	{
		_ISM( _T("ERROR : Could not connect to MSSQL database. [LOCALIZEPC]") );
		return FALSE;
	}

	hr = m_DBSession.Open(m_DataSource);
	if(FAILED(hr))
	{
		_ISM( _T("ERROR : Could not open DB Session. [LOCALIZEPC]") );
		m_DataSource.Close();  
		return FALSE;
	}

	_ISM(_T("Initialized db connector."));
	
	m_Connected = TRUE;

	return TRUE;
}


void _XOLEDBConnector::Release( void )
{
	m_localizedata.Close();
	m_retdata.Close();
	m_commander.Close();

	m_DBSession.Close();
	m_DataSource.Close();

	m_Connected = FALSE;
}


BOOL _XOLEDBConnector::BeginQuery( LPCTSTR szQueryString )
{
	if(!m_Connected) return FALSE;

	m_localizedata.Close();

	HRESULT hr = m_localizedata.Open( m_DBSession, szQueryString );
	if(FAILED(hr))
	{
		_ISM(_T("ERROR : Could not open db table [%s : %s]"), m_DBName, szQueryString );
		return FALSE;
	}		

	return TRUE;
}

void _XOLEDBConnector::EndQuery( void )
{
	if( !m_Connected ) return;

	m_localizedata.Close();
}


BOOL _XOLEDBConnector::BeginCommand( LPCTSTR szQueryString )
{
	if(!m_Connected) return FALSE;

	m_commander.Close();
	HRESULT hr = m_commander.Open( m_DBSession, szQueryString );
	if(FAILED(hr))
	{
		_ISM(_T("ERROR : Could not send to command [%s : %s]"), m_DBName, szQueryString );
		return FALSE;
	}	

	return TRUE;
}

void _XOLEDBConnector::EndCommand( void )
{
	m_commander.Close();
}

BOOL _XOLEDBConnector::BeginCommand_ret( LPCTSTR szQueryString )
{
	if(!m_Connected) return FALSE;

    m_retdata.Close();
	HRESULT hr = m_retdata.Open( m_DBSession, szQueryString );
	if(FAILED(hr))
	{
		_ISM(_T("ERROR : Could not send to command [%s : %s]"), m_DBName, szQueryString );
		return FALSE;
	}	

	return TRUE;	
}

void _XOLEDBConnector::EndCommand_ret( void )
{
	m_retdata.Close();
}


BOOL _XOLEDBConnector::BeginPermissionQuery( LPCTSTR szQueryString )
{
	if(!m_Connected) return FALSE;

	m_permissiondata.Close();
	HRESULT hr = m_permissiondata.Open( m_DBSession, szQueryString );
	if(FAILED(hr))
	{
		_ISM(_T("ERROR : Could not send to permission command [%s : %s]"), m_DBName, szQueryString );
		return FALSE;
	}	

	return TRUE;	
}

void _XOLEDBConnector::EndPermissionQuery( void )
{
	m_permissiondata.Close();
}

int _XOLEDBConnector::InsertNewString( LPCTSTR szString )
{
	CString szCompleteString = szString;
	szCompleteString.Replace( _T('\''), _T('"') );

	CLocalizeDataInfo* pLocalizeDataInfo = new CLocalizeDataInfo;

	pLocalizeDataInfo->stringuid = 0;
	pLocalizeDataInfo->resourceid = g_ScriptStringList[0].GetMaxResourceID() + 1;
	
	wcscpy( pLocalizeDataInfo->KoreanString , szCompleteString );
	pLocalizeDataInfo->KoreanOrder = 0;
	
	g_ScriptStringList[0].Insert( pLocalizeDataInfo );

	CString querystring;

	querystring.Format(_T( "Insert into %s values(%d,'%s',%d,'%s',%d,'%s',%d,'%s',%d,'%s',%d, %d )" ), 
		_T("QuestScript"),
		pLocalizeDataInfo->resourceid,
		szCompleteString,0,
		_T(""),0,
		_T(""),0,
		_T(""),0,
		_T(""),0,
		0 );

	if( g_LocalizeDB.BeginCommand(querystring) )
	{
		g_LocalizeDB.EndCommand();
	}
	else
	{
		return -1;
	}

	_ISM( _T("New text inserted [%d:%s]"), pLocalizeDataInfo->resourceid, szCompleteString );

	return pLocalizeDataInfo->resourceid;
}
