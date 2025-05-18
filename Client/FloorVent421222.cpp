#include "FloorVent421222.h"
#include "Export_Function.h"


FloorVent421222::FloorVent421222(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent421222::~FloorVent421222()
{
}

CGameObject * FloorVent421222::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent421222* pInstance = new FloorVent421222(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent421222::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent #421222", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent #421222", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}
