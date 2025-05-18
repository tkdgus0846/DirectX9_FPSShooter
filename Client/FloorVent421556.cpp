#include "FloorVent421556.h"
#include "Export_Function.h"



FloorVent421556::FloorVent421556(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent421556::~FloorVent421556()
{
}

CGameObject * FloorVent421556::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent421556* pInstance = new FloorVent421556(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent421556::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent #421556", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent #421556", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}
