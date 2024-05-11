#ifndef _XOLEDBCONNECTOR_
#define _XOLEDBCONNECTOR_

#include "stdafx.h"

#include <vector>
#include <map>
#include <list>

class CLocalizeDataInfo
{
public:
	// data elements
	int		stringuid;
	int		resourceid;	
	TCHAR	KoreanString[_XDEF_MAXSTRINGSIZE];
	int		KoreanOrder;
	TCHAR	VietnameseString[_XDEF_MAXSTRINGSIZE];
	int		VietnameseOrder;
	TCHAR	TaiwaneseString[_XDEF_MAXSTRINGSIZE];
	int		TaiwaneseOrder;
	TCHAR	EnglishString[_XDEF_MAXSTRINGSIZE];
	int		EnglishOrder;
	TCHAR	ChineseString[_XDEF_MAXSTRINGSIZE];
	int		ChineseOrder;
	int		Version;

	TCHAR	JapaneseString[_XDEF_MAXSTRINGSIZE];
	int		JapaneseOrder;
	TCHAR	RussianString[_XDEF_MAXSTRINGSIZE];
	int		RussianOrder;
	TCHAR	ThaiString[_XDEF_MAXSTRINGSIZE];
	int		ThaiOrder;

	BOOL    Modified;

	CLocalizeDataInfo()
	{
		stringuid  = -1;
		resourceid = -1;		
		Version	   =  0;
		ClearString();
		KoreanOrder = VietnameseOrder = TaiwaneseOrder = EnglishOrder = ChineseOrder = JapaneseOrder = RussianOrder = ThaiOrder = 0;

		Modified = FALSE;
	}

	void ClearString( void )
	{
		memset( KoreanString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( VietnameseString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( TaiwaneseString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( EnglishString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( ChineseString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( JapaneseString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( RussianString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
		memset( ThaiString, 0, sizeof(TCHAR) * _XDEF_MAXSTRINGSIZE );
	}

	// column binding  
	BEGIN_COLUMN_MAP(CLocalizeDataInfo)

		COLUMN_ENTRY(1,stringuid);		
		COLUMN_ENTRY(2,resourceid );
		
		COLUMN_ENTRY(3,KoreanString );
		COLUMN_ENTRY(4,KoreanOrder );

		COLUMN_ENTRY(5,VietnameseString );
		COLUMN_ENTRY(6,VietnameseOrder );

		COLUMN_ENTRY(7,TaiwaneseString );
		COLUMN_ENTRY(8,TaiwaneseOrder );

		COLUMN_ENTRY(9,EnglishString );
		COLUMN_ENTRY(10,EnglishOrder );

		COLUMN_ENTRY(11,ChineseString );
		COLUMN_ENTRY(12,ChineseOrder );	

		COLUMN_ENTRY(13,Version);	

		COLUMN_ENTRY(14,JapaneseString );
		COLUMN_ENTRY(15,JapaneseOrder );	

		COLUMN_ENTRY(16,RussianString );
		COLUMN_ENTRY(17,RussianOrder );	

		COLUMN_ENTRY(18,ThaiString );
		COLUMN_ENTRY(19,ThaiOrder );	

	END_COLUMN_MAP()
};

typedef std::vector<CLocalizeDataInfo*>							svdef_XTEXTSTRING_INFO;
typedef std::map<int, CLocalizeDataInfo*>						smdef_XTEXTSTRING_INFOMAP;

class _XSTRINGSECTIONINFODATA
{

public:
	//int								m_stringcnt;
	TCHAR							m_sectioname[64];

	svdef_XTEXTSTRING_INFO			m_StringVector;
	smdef_XTEXTSTRING_INFOMAP		m_StringMap;
	//smdef_XTEXTSTRING_INFOMAP		m_StringMap_UID;

	//int								m_MaxResourceID;

	void							Release(void);

	_XSTRINGSECTIONINFODATA()
	{
	//								m_stringcnt = 0;
									memset( m_sectioname, 0, sizeof(TCHAR) * 64 );
									//m_MaxResourceID = -1;
	}
	~_XSTRINGSECTIONINFODATA()
	{
									
	}

	void							Insert( CLocalizeDataInfo* pObject );
	void							Delete( CLocalizeDataInfo* pObject );
	void							Delete( int RID );
	void							Clear( void );	
	int								GetMaxResourceID( void );
	CLocalizeDataInfo*				GetObject( int ResourceID );
	//CLocalizeDataInfo*				GetObject_UID( int UID);

	int								FindString( LPCTSTR szString );
};

extern _XSTRINGSECTIONINFODATA g_ScriptStringList[_XDEF_CATEGORYMAXSIZE];

class CRetDataInfo
{
public:
	// data elements
	int		retdata;

	CRetDataInfo()
	{
		retdata  = -1;
	}

	// column binding  
	BEGIN_COLUMN_MAP(CRetDataInfo)
		COLUMN_ENTRY(1,retdata);
	END_COLUMN_MAP()
};

class CPermissionDataInfo
{
public:
	// data elements
	int		useruid;
	TCHAR	username[64];
	int		permission;

	CPermissionDataInfo()
	{
		useruid = -1;
		permission = -1;
		memset( username, 0, sizeof(TCHAR) * 64 );
	}

	// column binding  
	BEGIN_COLUMN_MAP(CPermissionDataInfo)
		COLUMN_ENTRY(1,useruid);
		COLUMN_ENTRY(2,username);
		COLUMN_ENTRY(3,permission);
	END_COLUMN_MAP()
};

class _XOLEDBConnector
{
public:
	CDataSource															m_DataSource;
	CSession															m_DBSession;
	CCommand	<CAccessor<CLocalizeDataInfo> >							m_localizedata;
	CCommand	<CAccessor<CRetDataInfo> >								m_retdata;
	CCommand	<CNoAccessor,CNoRowset,CNoMultipleResults>				m_commander;

	CCommand	<CAccessor<CPermissionDataInfo> >						m_permissiondata;
	
	CString																m_DBName;

	BOOL																m_Connected;

public:
	_XOLEDBConnector(void);
	~_XOLEDBConnector(void);

	BOOL		Initialize(  LPCTSTR serverip, long port, LPCTSTR uid, LPCTSTR pwd, LPCTSTR dbname  );	
	void		Release( void );

	BOOL		BeginQuery( LPCTSTR szQueryString );
	void		EndQuery( void );

	BOOL		BeginCommand( LPCTSTR szQueryString );
	void		EndCommand( void );

	BOOL		BeginCommand_ret( LPCTSTR szQueryString );
	void		EndCommand_ret( void );

	BOOL		BeginPermissionQuery( LPCTSTR szQueryString );
	void		EndPermissionQuery( void );

	BOOL		IsConnected( void ){ return m_Connected; }

	int			InsertNewString( LPCTSTR szString );
};

extern void _ISM( LPCTSTR Format, ... );
extern void _ISM_NOMESSAGEBOX( LPCTSTR Format, ... );

extern _XOLEDBConnector	g_LocalizeDB;

#endif