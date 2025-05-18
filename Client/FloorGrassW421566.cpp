#include "FloorGrassW421566.h"
#include "Export_Function.h"


FloorGrassW421566::FloorGrassW421566(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorGrassW421566::~FloorGrassW421566()
{
}

CGameObject * FloorGrassW421566::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorGrassW421566* pInstance = new FloorGrassW421566(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorGrassW421566::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorGrassW #421566", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorGrassW #421566", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorGrassW421566::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}

