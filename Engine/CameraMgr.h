#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class CCamera;
class CCameraMgr : public CBase
{
	friend CCamera;
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit CCameraMgr();
	virtual ~CCameraMgr();

private:
	CCamera* Find_Camera(const _tchar* pCamTag);
	void Add_Camera(const _tchar* pCamTag, CCamera* pCamera);
	void Remove_Camera(const _tchar* pCamTag);

public:
	CCamera* Get_CurCamera() { return m_pCurCamera; }
	void On_Camera(const _tchar* pCamTag);
	void On_Shake(SHAKE_TYPE eType, const _float& fForce = 1.5f, const _float& fTime = 5.f);

private:
	CCamera*		m_pCurCamera;
	list<CCamera*>	m_CameraList;

private:
	virtual void Free(void) override;
};

END