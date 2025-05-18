#include "CheckPoint.h"
#include "Export_Function.h"

#include "Player.h"
#include "Weapon.h"
#include "..\Engine\SoundMgr.h"
CCheckPoint::CCheckPoint(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CCheckPoint::~CCheckPoint()
{
}

HRESULT CCheckPoint::Add_Component()
{

	CRcTex* pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pRcTex });

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"CheckPoint_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"CheckPoint_Texture", pTexture });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 3.f, 2.f, 3.f });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, pTexture, 0.2f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	return S_OK;
}

HRESULT CCheckPoint::Ready_GameObject(void)
{
	m_pTransform->m_vScale = { 2.f, 2.f, 0.f };
	m_pTransform->Set_Pos(_vec3{ 33.f, 0.1f, 85.f });
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);


	_matrix matRot;
	_vec3 Axis = { 1.f, 0.f, 0.f };

	D3DXMatrixRotationAxis(&matRot, &Axis, D3DXToRadian(90.f));
	D3DXVec3TransformNormal(&m_pTransform->m_vInfo[INFO_UP], &m_pTransform->m_vInfo[INFO_UP], &matRot);
	D3DXVec3TransformNormal(&m_pTransform->m_vInfo[INFO_LOOK], &m_pTransform->m_vInfo[INFO_LOOK], &matRot);

	__super::Ready_GameObject();
	return S_OK;
}

_int CCheckPoint::Update_GameObject(const _float & fTimeDelta)
{
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	__super::Update_GameObject(fTimeDelta);
	return OBJ_NOEVENT;
}

void CCheckPoint::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCheckPoint::Render_GameObject(void)
{
	__super::Render_GameObject();
}


void CCheckPoint::OnCollisionEnter(const Collision * collsion)
{
	if (Engine::Get_Player == nullptr) { return; }
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);
	if (pPlayer && collsion->OtherCollider == collsion->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) 
		&& collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		CWeapon* pWeapon = pPlayer->Get_CurWeapon();
		_float Max = pWeapon->Get_MaxBulletNum();
		pWeapon->GainBullet(Max);
		PLAY_SOUND(L"sfxStart.wav", SOUND_SUSTAIN, 1.f);
	}

	__super::OnCollisionEnter(collsion);
}

CGameObject * CCheckPoint::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCheckPoint* pInstance = new CCheckPoint(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCheckPoint::Free(void)
{
	__super::Free();
}
