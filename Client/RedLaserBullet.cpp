#include "RedLaserBullet.h"

#include "BulletMgr.h"
#include "EffectManager.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "Effect.h"
#include "SoftPyramid.h"
#include "..\Engine\SoundMgr.h"

CRedLaserBullet::CRedLaserBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBullet(pGraphicDev), m_bShot(false), m_bPoint(false)
{
	Set_ObjTag(L"RedLaserBullet");
	m_fSpeed = 1000.f;
	m_fLifeSpan = 12.f;
	m_fAge = 0.f;
	m_Damage = 1;

	ZeroMemory(m_vDir, sizeof(_vec3));
}

CRedLaserBullet::~CRedLaserBullet()
{
}

void CRedLaserBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
	{
		m_bShot = false;
		m_bPoint = false;
		CBulletMgr::GetInstance()->Push(L"RedLaserBullet", this);
	}
}

HRESULT CRedLaserBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pRcTex->Set_RenderFlag();

	return result;
}

_int CRedLaserBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead())
		return OBJ_RETPOOL;

	_float fRotSpeed = 360.f * 3.f;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	if (!m_bShot)
	{
		m_pTransform->Rot_Pitch(-90.f, 1.f);
		m_bShot = true;
	}

	m_vDir = -m_pTransform->m_vInfo[INFO_UP];
	m_pTransform->m_vInfo[INFO_POS] += m_vDir * m_fSpeed * fTimeDelta;
	m_pTransform->Rot_Yaw(fRotSpeed, fTimeDelta);
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CRedLaserBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CRedLaserBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();

	if (false == m_bPoint)
		return;

	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_matrix matWorld, matScale, matRot, matTrans;
	matWorld.Identity();

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationX(&matRot, D3DXToRadian(90.f));

	D3DXMatrixTranslation(&matTrans, vPos.x, 0.1f, vPos.z);

	matWorld = matScale * matRot * matTrans;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTextureCom->Render_Texture();
	m_pRcTex->Render_Component();
}

void CRedLaserBullet::OnCollisionEnter(const Collision * collsion)
{
}

void CRedLaserBullet::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);
	CWall* wall = dynamic_cast<CWall*>(collision->OtherGameObject);
	CFloor* floor = dynamic_cast<CFloor*>(collision->OtherGameObject);
	CSoftPyramid* softPyramid = dynamic_cast<CSoftPyramid*>(collision->OtherGameObject);

	_vec3 vPos = collision->intersectBox._max;

	if(wall || floor || softPyramid)
	{
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", vPos, { 1.7f, 1.7f, 1.7f }, 0.1f);
		Add_GameObject(effect);
		STOP_PLAY_SOUND(L"sfxKill.wav", SOUND_ENEMY_BULLET, 1.f);
		SetDead();
	}

	if (pPlayer && collision->OtherCollider == pPlayer->Get_Component(L"BodyCollider", ID_ALL))
	{
		pPlayer->Get_Damaged(1);
		STOP_PLAY_SOUND(L"sfxKill.wav", SOUND_ENEMY_BULLET, 1.f);
		SetDead();
	}
}

void CRedLaserBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CRedLaserBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Laser_Red_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"Laser_Red_Texture", texture);

	/////// Attack Point component
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Boss_AttackPoint_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Boss_AttackPoint_Texture", m_pTextureCom);

	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"AttackPointTex", m_pRcTex);
	////////////////////////////////////////

	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMYBULLET));
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	return S_OK;
}

void CRedLaserBullet::Free(void)
{
	__super::Free();
}

CRedLaserBullet * CRedLaserBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRedLaserBullet*		pInstance = new CRedLaserBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
