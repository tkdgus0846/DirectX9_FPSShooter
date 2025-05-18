#include "NubPilot.h"

#include "Export_Function.h"

CNubPilot::CNubPilot(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev), m_fTime(0.f)
{
	Set_ObjTag(Tag());
}

CNubPilot::~CNubPilot()
{
}

HRESULT CNubPilot::Ready_GameObject(const _vec3& vPos)
{
	m_fSpeed = 10.f;
	m_iHp = 1.f;

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CNubPilot::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;

	m_fTime += fTimeDelta;
	_float fVal = cosf(m_fTime) * fTimeDelta;
	m_pTransform->m_vInfo[INFO_POS].y += fVal;

	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return S_OK;
}

void CNubPilot::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNubPilot::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CNubPilot::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", animation);
	animation->SelectState(ANIM_WALK);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Nub_Pilot_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Nub_Pilot_Texture", texture });
	animation->BindAnimation(ANIM_WALK, texture, 0.3f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.f, 2.f, 2.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 70.f, 20.f, 70.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PAF_AttckAI(L"EnemyBullet"), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CNubPilot * CNubPilot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CNubPilot* pInstance = new CNubPilot(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CNubPilot::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNubPilot* pInstance = new CNubPilot(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNubPilot::Free(void)
{
	__super::Free();
}
