#include "SandWaterFill.h"
#include "Export_Function.h"


SandWaterFill::SandWaterFill(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

SandWaterFill::~SandWaterFill()
{
}

CGameObject * SandWaterFill::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	SandWaterFill* pInstance = new SandWaterFill(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT SandWaterFill::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SandWaterFill", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SandWaterFill", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void SandWaterFill::OnCollisionStay(const Collision * collision)
{
}