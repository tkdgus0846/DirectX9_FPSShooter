#include "IceTile.h"
#include "Export_Function.h"
#include "Player.h"
#include "Pyramid.h"

CIceTile::CIceTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CIceTile::~CIceTile()
{
}

CGameObject * CIceTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIceTile* pInstance = new CIceTile(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CIceTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorIce", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorIce", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	
	return result;
}

void CIceTile::OnCollisionEnter(const Collision * collision)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (pPlayer && IsBodyCollider(collision))
	{
		//if (IntersectPoint(&pPlayer->m_pTransform->m_vInfo[INFO_POS]))
		//	Set_Trigger(true);
	}
}

void CIceTile::OnCollisionStay(const Collision * collision)
{

}

void CIceTile::OnCollisionExit(const Collision * collision)
{

}

void CIceTile::InteractGameObject(const InteractInfo* tInteractInfo)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(tInteractInfo->pGameObject);
	if (pPlayer)
	{
		CCollider* pCol = dynamic_cast<CCollider*>(pPlayer->Get_Component(L"BodyCollider", ID_ALL));

		if (!pCol)
			return;

		for (auto& Object : pCol->Get_CollisionList())
			if (dynamic_cast<CPyramid*>(Object.second.OtherGameObject))
				return;

		pPlayer->IsOnIceTile(true);
		_vec3 vDir = pPlayer->GetDeltaVec();
		vDir.Normalize();

		if (fabs(vDir.x) <= 0.001f && fabs(vDir.y) <= 0.001f && fabs(vDir.z) <= 0.001f)
			vDir = pPlayer->m_pTransform->m_vInfo[INFO_LOOK];

		// 방향 구하는 코드.
		_vec3 comp[4] = { _vec3::Look(), -_vec3::Look(), _vec3::Right(), -_vec3::Right() };
		_vec3 vMinDir = {};
		float fMinDegree = FLT_MAX;
		for (_int i = 0; i < 4; ++i)
		{
			float fDegree = vDir.Degree(comp[i]);
			if (fMinDegree > fDegree)
			{
				fMinDegree = fDegree;
				vMinDir = comp[i];
			}
		}
		
		pPlayer->m_pTransform->Move_WalkWithVec(vMinDir, 10.f, tInteractInfo->_fTimeDelta);
	}
}