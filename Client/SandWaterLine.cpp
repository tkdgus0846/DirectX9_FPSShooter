#include "SandWaterLine.h"
#include "Export_Function.h"


SandWaterLine::SandWaterLine(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

SandWaterLine::~SandWaterLine()
{
}

CGameObject * SandWaterLine::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	SandWaterLine* pInstance = new SandWaterLine(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT SandWaterLine::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SandWaterLine", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SandWaterLine", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void SandWaterLine::OnCollisionStay(const Collision * collision)
{
}