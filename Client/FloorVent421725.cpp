#include "FloorVent421725.h"
#include "Export_Function.h"


FloorVent421725::FloorVent421725(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent421725::~FloorVent421725()
{
}

CGameObject * FloorVent421725::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent421725* pInstance = new FloorVent421725(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent421725::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent #421725", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent #421725", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}
