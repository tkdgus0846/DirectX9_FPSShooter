#include "stdafx.h"
#include "CameraMgr.h"
#include "Camera.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
	:m_pCurCamera(nullptr)
{
}

CCameraMgr::~CCameraMgr()
{
	Free();
}

CCamera * CCameraMgr::Find_Camera(const _tchar * pCamTag)
{
	for (auto Cam : m_CameraList)
	{
		if (0 == lstrcmpW(pCamTag, Cam->m_pName))
			return Cam;
	}

	return nullptr;
}

void CCameraMgr::On_Camera(const _tchar * pCamTag)
{
	CCamera* pCamera = Find_Camera(pCamTag);

	NULL_CHECK(pCamera);

	if (m_pCurCamera)
		m_pCurCamera->Off_Camera();

	pCamera->On_Camera();
	m_pCurCamera = pCamera;
}

void CCameraMgr::On_Shake(SHAKE_TYPE eType, const _float& fForce, const _float& fTime)
{
	m_pCurCamera->On_Shake(eType, fForce, fTime);
}

void CCameraMgr::Add_Camera(const _tchar* pCamTag, CCamera * pCamera)
{
	if (Find_Camera(pCamTag))
		return;

	m_CameraList.push_back(pCamera);
}

void CCameraMgr::Remove_Camera(const _tchar * pCamTag)
{
	for (list<CCamera*>::iterator iter = m_CameraList.begin(); iter != m_CameraList.end(); ++iter)
	{
		if (0 == lstrcmpW(pCamTag, (*iter)->m_pName))
		{
			m_CameraList.erase(iter);
			return;
		}
	}
}

void CCameraMgr::Free(void)
{
	m_CameraList.clear();
}
