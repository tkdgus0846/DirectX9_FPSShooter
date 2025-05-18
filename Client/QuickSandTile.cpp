#include "QuickSandTile.h"
#include "Export_Function.h"

CQuickSandTile::CQuickSandTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CQuickSandTile::~CQuickSandTile()
{
}

CGameObject * CQuickSandTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CQuickSandTile* pInstance = new CQuickSandTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CQuickSandTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CQuickSandTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorQuicksand", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorQuicksand", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CQuickSandTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}