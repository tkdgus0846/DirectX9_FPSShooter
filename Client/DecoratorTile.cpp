#include "DecoratorTile.h"
#include "Export_Function.h"


CDecoratorTile::CDecoratorTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CDecoratorTile::~CDecoratorTile()
{
}

CGameObject * CDecoratorTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDecoratorTile* pInstance = new CDecoratorTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CDecoratorTile::Add_Component()
{
	__super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Explosion_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Explosion_Texture", texture });

	return S_OK;
}

void CDecoratorTile::OnCollisionStay(const Collision * collision)
{
}
