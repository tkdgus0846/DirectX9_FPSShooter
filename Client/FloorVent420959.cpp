#include "FloorVent420959.h"
#include "Export_Function.h"


FloorVent420959::FloorVent420959(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent420959::~FloorVent420959()
{
}

CGameObject * FloorVent420959::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent420959* pInstance = new FloorVent420959(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent420959::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent #420959", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent #420959", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}
