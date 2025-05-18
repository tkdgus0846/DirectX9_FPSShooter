#include "WaterTile.h"

#include "Export_Function.h"


CWaterTile::CWaterTile(LPDIRECT3DDEVICE9 pGraphicDev) :
	CFloorTile(pGraphicDev),
	m_fTime(0.f),
	m_fMaxTime(1.f)
{
	Set_ObjTag(Tag());
}

CWaterTile::~CWaterTile()
{
}

CGameObject * CWaterTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWaterTile* pInstance = new CWaterTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CWaterTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

void CWaterTile::SetDead(_bool bDead /*= true*/)
{
	return __super::SetDead(bDead);
}

HRESULT CWaterTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture  = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorWater", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorWater", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture, 0.25f);

	return result;
}

void CWaterTile::OnCollisionStay(const Collision * collision)
{

}

_int CWaterTile::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	return __super::Update_GameObject(fTimeDelta);
}

