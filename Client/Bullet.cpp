#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

#include "Export_Function.h"


CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_Damage(1),
	m_bHit(FALSE)
{
	Set_LayerID(LAYER_BULLET);
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
}

CBullet::~CBullet()
{
}

void CBullet::Free(void)
{
	OBJ_INFO objInfo = Get_ObjInfo();
	for (int i = 0; i < objInfo.colNameVec.size(); i++)
	{
		CCollider* pCol = dynamic_cast<CCollider*>(Get_Component(objInfo.colNameVec[i], ID_ALL));
		if (pCol)
			pCol->Get_CollisionList().clear();
	}
	__super::Free();
}

void CBullet::OnCollisionStay(const Collision * collision)
{/*
	CMonster* monster = dynamic_cast<CMonster*>(collision->OtherGameObject);

	if (monster && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
		dynamic_cast<CPlayer*>(Engine::Get_Player())->Gain_UltiGuage(m_Damage);*/
}
