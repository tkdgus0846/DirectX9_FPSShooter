#include "FloorHole421777.h"
#include "Export_Function.h"
#include "Evasioner.h"



FloorHole421777::FloorHole421777(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorHole421777::~FloorHole421777()
{
}

CGameObject * FloorHole421777::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorHole421777* pInstance = new FloorHole421777(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorHole421777::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorHole #421777", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorHole #421777", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	CCollider* collider = dynamic_cast<CCollider*>(Clone_Proto(L"Collider", L"Collider", this, COL_TRIGGER));
	NULL_CHECK_RETURN(collider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", collider });
	collider->Set_BoundingBox({ 5.f, 1.f, 5.f });

	return result;
}

void FloorHole421777::OnCollisionStay(const Collision * collision)
{

	CEvasioner* evasioner = dynamic_cast<CEvasioner*>(collision->OtherGameObject);

	if (evasioner != nullptr)
	{
		
		if (evasioner->Get_Component(L"HoleCollider", ID_ALL) == collision->OtherCollider)
		{
			evasioner->SetInHole();
			_float fps60 = Engine::Get_Timer(L"Timer_FPS60");

			evasioner->m_pTransform->m_vInfo[INFO_POS].y -= 3.f * fps60;

			if (evasioner->m_pTransform->m_vInfo[INFO_POS].y < 0.f)
			{
				evasioner->SetDead();
			}
			
		}
	}
	
}