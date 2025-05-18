#include "SandWaterArc.h"
#include "Export_Function.h"


SandWaterArc::SandWaterArc(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

SandWaterArc::~SandWaterArc()
{
}

CGameObject * SandWaterArc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	SandWaterArc* pInstance = new SandWaterArc(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT SandWaterArc::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SandWaterArc", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SandWaterArc", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void SandWaterArc::OnCollisionStay(const Collision * collision)
{
}
