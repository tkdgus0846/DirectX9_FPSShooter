#include "SpreadShot.h"

#include "ShockWave.h"
#include "RootAttack.h"
#include "BulletMgr.h"
#include "EffectManager.h"
#include "Export_Function.h"

CSpreadShot::CSpreadShot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_pBulletTag(nullptr)
	, m_iDegree(0), m_fSpeed(0.f)
{
	ZeroMemory(&m_vScale, sizeof(_vec3));
}

CSpreadShot::CSpreadShot(const CSpreadShot & rhs)
	: CBehavior(rhs), m_vScale(rhs.m_vScale), m_fSpeed(rhs.m_fSpeed)
	, m_pBulletTag(rhs.m_pBulletTag), m_iDegree(rhs.m_iDegree)
{
}

CSpreadShot::~CSpreadShot()
{
}

HRESULT CSpreadShot::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CSpreadShot::Update_Component(const _float & fTimeDelta)
{
	_int iResult = 0;
	switch (m_eOption)
	{
	case SPRD_X:
		iResult = Spread_X(fTimeDelta);
		break;

	case SPRD_PLUS:
		iResult = Spread_Plus(fTimeDelta);
		break;

	case SPRD_CIRCLE:
		iResult = Spread_Circle(fTimeDelta);
		break;

	case SPRD_TORNADO:
		iResult = Spread_Tornado(fTimeDelta);
		break;

	case SPRD_LOOK:
		iResult = Spread_Look(fTimeDelta);
		break;

	case SPRD_END:
	default:
		return BEHAVIOR_ERROR;
	}

	return iResult;
}

void CSpreadShot::Setting_Option(const _tchar* pBulletTag, const _float& fSpeed,
	const _vec3& vScale)
{
	m_pBulletTag = pBulletTag;
	m_fSpeed = fSpeed;
	m_vScale = vScale;
}

_int CSpreadShot::Spread_X(const _float & fTimeDelta)
{
	m_iDegree = 45;

	_matrix matRot;
	_vec3 vLook{};
	_vec3 vPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vPos.y = 1.f;

	for (_int i = 0; i < 4; ++i)
	{
		for (_int j = -18; j < 18; j += 6)
		{
			_float fAngle = D3DXToRadian((_float)m_iDegree + j);

			D3DXMatrixRotationY(&matRot, fAngle);
			D3DXVec3TransformNormal(&vLook, &_vec3(1.f, 0.f, 0.f), &matRot);

			CBullet* bullet = CBulletMgr::GetInstance()->Pop(
				m_pBulletTag, m_pGraphicDev,
				vPos, vLook, m_vScale, true, m_fSpeed);

			Add_GameObject(bullet);
		}
		m_iDegree += 90;
	}

	m_iDegree = 0;
	return BEHAVIOR_SUCCES;
}

_int CSpreadShot::Spread_Plus(const _float & fTimeDelta)
{
	_matrix matRot;
	_vec3 vLook{};
	_vec3 vPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vPos.y = 1.f;

	for (_int i = 0; i < 4; ++i)
	{
		for (_int j = -18; j < 18; j += 6)
		{
			_float fAngle = D3DXToRadian((_float)m_iDegree + j);

			D3DXMatrixRotationY(&matRot, fAngle);
			D3DXVec3TransformNormal(&vLook, &_vec3(1.f, 0.f, 0.f), &matRot);

			CBullet* bullet = CBulletMgr::GetInstance()->Pop(
				m_pBulletTag, m_pGraphicDev,
				vPos, vLook, m_vScale, true, m_fSpeed);

			Add_GameObject(bullet);
		}
		m_iDegree += 90;
	}

	m_iDegree = 0;
	return BEHAVIOR_SUCCES;
}

_int CSpreadShot::Spread_Circle(const _float & fTimeDelta)
{
	_matrix matRot;
	_vec3 vLook{};
	_vec3 vPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vPos.y = 1.f;

	while (m_iDegree < 360)
	{
		D3DXMatrixRotationY(&matRot, D3DXToRadian((_float)m_iDegree));
		D3DXVec3TransformNormal(&vLook, &_vec3(1.f, 0.f, 0.f), &matRot);

		CBullet* bullet = CBulletMgr::GetInstance()->Pop(
			m_pBulletTag, m_pGraphicDev,
			vPos, vLook, m_vScale, true, m_fSpeed);

		Add_GameObject(bullet);

		m_iDegree += 6;
	}

	m_iDegree = 0;
	return BEHAVIOR_SUCCES;
}

_int CSpreadShot::Spread_Tornado(const _float & fTimeDelta)
{
	if (m_iDegree >= 360)
	{
		m_iDegree = 0;
		return BEHAVIOR_SUCCES;
	}

	_matrix matRot;
	_vec3 vLook{};
	_vec3 vPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vPos.y = 1.f;
	D3DXMatrixRotationY(&matRot, D3DXToRadian((_float)m_iDegree));
	D3DXVec3TransformNormal(&vLook, &_vec3(1.f, 0.f, 0.f), &matRot);

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(
		m_pBulletTag, m_pGraphicDev,
		vPos, vLook, m_vScale, true, m_fSpeed);

	if (bullet)
		Add_GameObject(bullet);

	m_iDegree += 6;

	return BEHAVIOR_RUNNING;
}

_int CSpreadShot::Spread_Look(const _float & fTimeDelta)
{
	_matrix matRot;
	_vec3 vLook{};
	_vec3 vPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vPos.y = 1.f;

	for (_int j = -12; j < 12; j += 6)
	{
		_float fAngle = D3DXToRadian((_float)m_iDegree + j);

		D3DXMatrixRotationY(&matRot, fAngle);
		D3DXVec3TransformNormal(&vLook, &m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], &matRot);

		CBullet* bullet = CBulletMgr::GetInstance()->Pop(
			m_pBulletTag, m_pGraphicDev,
			vPos, vLook, m_vScale, true, m_fSpeed);

		Add_GameObject(bullet);
	}

	m_iDegree = 0;
	return BEHAVIOR_SUCCES;
}

CSpreadShot * CSpreadShot::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSpreadShot* pInstance = new CSpreadShot(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CSpreadShot::Clone(void)
{
	return new CSpreadShot(*this);
}

void CSpreadShot::Free()
{
	__super::Free();
}
