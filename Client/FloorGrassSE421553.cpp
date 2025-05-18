#include "FloorGrassSE421553.h"
#include "Export_Function.h"


FloorGrassSE421553::FloorGrassSE421553(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorGrassSE421553::~FloorGrassSE421553()
{
}

CGameObject * FloorGrassSE421553::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorGrassSE421553* pInstance = new FloorGrassSE421553(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorGrassSE421553::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorGrassSE #421553", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorGrassSE #421553", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorGrassSE421553::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}


