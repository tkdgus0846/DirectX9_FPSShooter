#pragma once

#include "Base.h"
#include "Include.h"

class CLoading : public CBase
{
public:
	explicit CLoading(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoading();

public:
	_bool				Get_Finish(void)	{ return m_bFinish; }
	CRITICAL_SECTION	Get_Crt(void)		{ return m_Crt; }
	LOADINGID			Get_LoadingID(void) { return m_eID; }
	void				Set_LoadingID(LOADINGID loadingID)
	{
		m_eID = loadingID;
	}
	const _tchar*		Get_String(void)	{ return m_szString; }
	void				Set_String(_tchar* pString) { lstrcpy(m_szString, pString); }

public:
	static unsigned int CALLBACK Thread_Main(void* pArg);

public:
	HRESULT				Ready_Loading(LOADINGID eID);

	_uint				Loading_ForEditStage(void);
	_uint				Loading_ForStage(void);
	_uint				Loading_ForStage2(void);
	_uint				Loading_ForStage3(void);
	_uint				Loading_ForStage4(void);

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	HANDLE						m_hThread;
	LOADINGID					m_eID;
	_bool						m_bFinish;
	_tchar						m_szString[128];

	CRITICAL_SECTION			m_Crt;

	// �ӽ� �ڵ�
	list<const _tchar*>			m_listTags;

public:
	static CLoading*		Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID);

private:
	virtual void		Free(void);
};

