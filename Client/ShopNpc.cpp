#include "ShopNpc.h"
#include "Bullet.h"
#include "Export_Function.h"
#include "Player.h"
#include "SellItem.h"
#include "..\Engine\SoundMgr.h"
CShopNpc::CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
	Set_LayerID(LAYER_NPC);
	Set_ObjTag(Tag());

	m_iHp = 1000;
	m_SellNum = 0;
	m_fPlayBGMTime = 0.f;
}

CShopNpc::~CShopNpc()
{
}

HRESULT CShopNpc::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"shopkeeperidle_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"shopkeeperidle_Texture", Texture });

	Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.1f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"shopkeeperdamaged_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"shopkeeperdamaged_Texture", Texture });
	Ani->BindAnimation(ANIM_DAMAGED, Texture, 0.1f, FALSE);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 6.f, 10.f, 6.f });

	m_pTransform->Set_BillMode(true);

	return S_OK;
}

HRESULT CShopNpc::Ready_GameObject(void)
{
	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };
	m_pTransform->Set_Pos(_vec3{ 25.f, -5.f, 85.f });
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	__super::Ready_GameObject();
	return S_OK;
}

_int CShopNpc::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	if (Get_Static_GameObject_Size() < m_SellNum)
	{
		m_fPlayBGMTime += fTimeDelta;

		if (m_fPlayBGMTime > 1.f)
		{
			CSoundMgr::GetInstance()->SetVolumeCurBGM(0.5f);
			m_SellNum--;
			m_fPlayBGMTime = 0.f;
		}
	}
	
	

	
	

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);

	viewMat.Inverse();
	m_pTransform->Rot_Bill(0.01f);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CShopNpc::LateUpdate_GameObject(void)
{
	if (Ani->GetFinished())
	{
		Ani->AnimationClear();
		Ani->SelectState(ANIM_IDLE);
		m_redTexture = false;
	}

	__super::LateUpdate_GameObject();
}

void CShopNpc::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CShopNpc::Get_Damaged(_int Damage)
{
	__super::Get_Damaged(Damage);

	Ani->SelectState(ANIM_DAMAGED);
}

void CShopNpc::Add_SellItem_Stage1()
{
	_vec3 Pos = m_pTransform->m_vInfo[INFO_POS];
	Pos.y += 6.f;
	Pos.z -= 5.f;
	
	//Pos.x += 5.5f;
	CSellItem* item1 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 1, RAPIDSHOT);
	Pos.x += 4.f;

	CSellItem* item2 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 30, SPREADSHOT);
	Pos.x -= 8.f;

	CSellItem* item3 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 500, LASERSHOT);

	Add_Static_GameObject(item1);
	Add_Static_GameObject(item2);
	Add_Static_GameObject(item3);
	m_SellNum = 3;

}

void CShopNpc::Add_SellItem_Stage2()
{
	_vec3 Pos = m_pTransform->m_vInfo[INFO_POS];
	Pos.y += 6.f;
	Pos.z -= 5.f;

	//Pos.x += 5.5f;
	CSellItem* item1 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 50, FLAMESHOT);
	Pos.x += 4.f;

	CSellItem* item2 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 600, EXPLOSIVESHOT);
	Pos.x -= 8.f;

	CSellItem* item3 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 70, FREEZESHOT);

	Add_Static_GameObject(item1);
	Add_Static_GameObject(item2);
	Add_Static_GameObject(item3);
	m_SellNum = 3;
}

void CShopNpc::Add_SellItem_Stage3()
{
	_vec3 Pos = m_pTransform->m_vInfo[INFO_POS];
	Pos.y += 6.f;
	Pos.z -= 5.f;

	//Pos.x += 5.5f;
	CSellItem* item1 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 30, FREEZESHOT);
	Pos.x += 4.f;

	CSellItem* item2 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 20, LASERSHOT);
	Pos.x -= 8.f;

	CSellItem* item3 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 30, EXPLOSIVESHOT);

	Add_Static_GameObject(item1);
	Add_Static_GameObject(item2);
	Add_Static_GameObject(item3);
	m_SellNum = 3;
}

void CShopNpc::Add_SellItem_Stage4()
{
	_vec3 Pos = m_pTransform->m_vInfo[INFO_POS];
	Pos.y += 6.f;
	Pos.z -= 5.f;

	//Pos.x += 5.5f;
	CSellItem* item1 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 10, EXPLOSIVESHOT);
	Pos.x += 4.f;

	CSellItem* item2 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 50, SPREADSHOT);
	Pos.x -= 8.f;

	CSellItem* item3 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 100, FREEZESHOT);

	Add_Static_GameObject(item1);
	Add_Static_GameObject(item2);
	Add_Static_GameObject(item3);
	m_SellNum = 3;
}

void CShopNpc::OnCollisionEnter(const Collision * collsion)
{

}

void CShopNpc::OnCollisionStay(const Collision * collision)
{
	if (dynamic_cast<CBullet*>(collision->OtherGameObject) &&
		collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) &&
		collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		m_redTexture = true;
		m_fCurTime = Get_WorldTime();
		m_fPreTime = Get_WorldTime();
	}
}


CGameObject * CShopNpc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShopNpc* pInstance = new CShopNpc(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}


void CShopNpc::Free(void)
{
	__super::Free();
}