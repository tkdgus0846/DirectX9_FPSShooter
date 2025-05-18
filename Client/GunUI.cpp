#include "GunUI.h"
#include "Export_Function.h"
#include "Player.h"

CGunUI::CGunUI(LPDIRECT3DDEVICE9 pGraphicDev) :
	CUI(pGraphicDev)
{
	Set_ObjTag(L"GunUI");

}

CGunUI::~CGunUI()
{
}

_int CGunUI::Update_GameObject(const _float& fTimeDelta)
{
	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	matView.Inverse();

	_vec3 pos = { matView._41, matView._42, matView._43 };
	Compute_ViewZ(&pos);
	Engine::Add_RenderGroup(RENDER_AFTER_ALPHA_UI, this);
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CGunUI::Add_Component()
{
	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Gun", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Gun", texture });
}

HRESULT CGunUI::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CGunUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CGunUI::Render_GameObject(void)
{
	if (Engine::Get_Player() == nullptr) { return; }

	if (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_bAimHack() == true) { return; }

	static _float posX = 200.f;
	static _float incX = 1.9f;
	static _float angle = -10.f;


	/*if (posX >= 190.f)
		incX *= -1.f;
	
	if (posX < 150.f)
		incX *= -1.f;

	posX += incX;*/
	_matrix viewMatrix, transMatrix, scaleMatrix, rotationMatrix;
	transMatrix.Translation(posX, -190.f, 0.f);
	scaleMatrix.Scaling(120.f, 120.f, 0.f);
	rotationMatrix.RotationZ(D3DXToRadian(angle));
	viewMatrix.Identity();

	viewMatrix = viewMatrix * scaleMatrix * rotationMatrix * transMatrix;
	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &viewMatrix);
	
	__super::Render_GameObject();
}

CGunUI* CGunUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGunUI*		pInstance = new CGunUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGunUI::Free(void)
{
	__super::Free();
}
