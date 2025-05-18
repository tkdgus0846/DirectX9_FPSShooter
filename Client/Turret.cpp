#include "Turret.h"

#include "Export_Function.h"
#include "RoomMgr.h"

CTurret::CTurret(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev)
{
	Set_ObjTag(Tag());

}

CTurret::~CTurret()
{
}

HRESULT CTurret::Ready_GameObject(const _vec3& vPos)
{
	m_fSpeed = 10.f;
	m_iHp = 2.f;
	m_iAttack = 1.f;

	m_pTransform->m_vScale = { 2.f, 2.f, 2.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CTurret::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);
	InteractTile(fTimeDelta);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	

	return OBJ_NOEVENT;
}

void CTurret::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTurret::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CTurret::InteractTile(_float fTimeDelta)
{
	CFloorTile* pTile = CRoomMgr::GetInstance()->Get_CurRoom()->GetCurFloorTile(this);

	if (!pTile) return;

	InteractInfo tInfo;
	tInfo.pGameObject = this;
	tInfo._fTimeDelta = fTimeDelta;
	pTile->InteractGameObject(&tInfo);
}

HRESULT CTurret::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Turret_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Turret_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_WALK, texture, 0.3f);
	animation->SelectState(ANIM_WALK);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 5.f, 5.f, 5.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 60.f, 10.f, 60.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_TurretAI(3.f), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CTurret * CTurret::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CTurret* pInstance = new CTurret(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CTurret::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTurret* pInstance = new CTurret(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTurret::Free(void)
{
	__super::Free();
}
