#include "stdafx.h"
#include "Camera.h"

#include <chrono>
#include <random>
#include "Component.h"

#include "Export_Function.h"


CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev), m_bSwitch(false)
	, m_pName(nullptr), m_fShakeForce(0.f), m_fShakeTime(0.f)
	, m_eType(SHAKE_END)
{
	//ZeroMemory(m_szName, sizeof(_tchar) * 256);
	ZeroMemory(&m_tViewParams, sizeof(VIEWPARAMS));
	ZeroMemory(&m_tProjParams, sizeof(PROJPARAMS));
}

CCamera::CCamera(const CCamera & rhs)
	:CComponent(rhs), m_bSwitch(false)
	, m_pName(rhs.m_pName), m_fShakeForce(rhs.m_fShakeForce)
	, m_fShakeTime(rhs.m_fShakeTime), m_eType(rhs.m_eType)
{
	//ZeroMemory(m_szName, sizeof(_tchar) * 256);
	m_tViewParams = rhs.m_tViewParams;
	m_tProjParams = rhs.m_tProjParams;
	m_matView = rhs.m_matView;
	m_matProj = rhs.m_matProj;

}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Camera(VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam)
{
	m_tViewParams = tViewParam;
	m_tProjParams = tProjParam;

	m_tViewParams.LookAtLH(&m_matView);
	m_tProjParams.PerspectiveLH(&m_matProj);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

_int CCamera::Update_Component(const _float & fTimeDelta)
{
	if (!m_bSwitch)
		return 0;

	m_tViewParams.vEye = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	m_tViewParams.vAt = m_tViewParams.vEye + m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];

	if (m_bShake)
		Shake(fTimeDelta);

	m_tViewParams.LookAtLH(&m_matView);
	m_tProjParams.PerspectiveLH(&m_matProj);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return 0;
}

void CCamera::On_Shake(SHAKE_TYPE eType, const _float & fForce, const _float & fTime)
{
	m_eType = eType;
	m_bShake = true;
	m_fShakeForce = fForce;
	m_fShakeTime = fTime;
}

void CCamera::Shake_X(const _float & fTimeDelta)
{
	static _float fX = 0.f, fY = 0.f;

	fX += fTimeDelta * 5.f;

	fY = sinf(fX * 10.f) * sinf(fX * 10.f) * powf(0.4f, fX);

	m_tViewParams.vEye.x += fY * m_fShakeForce;
	m_tViewParams.vAt.x += fY * m_fShakeForce;

	if (fX > m_fShakeTime)
	{
		fX = 0.f;
		fY = 0.f;
		m_bShake = false;
	}
}

void CCamera::Shake_Y(const _float & fTimeDelta)
{
	static _float fX = 0.f, fY = 0.f;

	fX += fTimeDelta * 5.f;

	fY = sinf(fX * 10.f) * sinf(fX * 10.f) * powf(0.4f, fX);

	m_tViewParams.vEye.y += fY * m_fShakeForce;
	m_tViewParams.vAt.y += fY * m_fShakeForce;

	if (fX > m_fShakeTime)
	{
		fX = 0.f;
		fY = 0.f;
		m_bShake = false;
	}
}

void CCamera::Shake_LR(const _float & fTimeDelta)
{
	static _float fX = 0.f, fY = 0.f;

	fX += fTimeDelta * 5.f;

	fY = sinf(fX * 10.f) * sinf(fX * 10.f) * powf(0.4f, fX);

	_vec3 vRight{};
	_vec3 vLook = m_tViewParams.vAt - m_tViewParams.vEye;
	vLook.RightUpFromLook(vRight, _vec3());
	vRight.Normalize();

	vRight *= fY;

	m_tViewParams.vEye += vRight * m_fShakeForce;
	m_tViewParams.vAt += vRight * m_fShakeForce;

	if (fX > m_fShakeTime)
	{
		fX = 0.f;
		fY = 0.f;
		m_bShake = false;
	}
}

void CCamera::Shake(const _float & fTimeDelta)
{
	switch (m_eType)
	{
	case Engine::SHAKE_X:
		Shake_X(fTimeDelta);
		break;

	case Engine::SHAKE_Y:
		Shake_Y(fTimeDelta);
		break;

	case Engine::SHAKE_LR:
		Shake_LR(fTimeDelta);
		break;
	}
}

CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam)
{
	CCamera* pInstance = new CCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Camera(tViewParam, tProjParam)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCamera::Clone(void)
{
	CCamera* pInstance = new CCamera(*this);
	NULL_CHECK_RETURN(pInstance, nullptr);

	Engine::CCameraMgr::GetInstance()->Add_Camera(m_pName, pInstance);
	
	return pInstance;
}

void CCamera::Free()
{
	__super::Free();
}
