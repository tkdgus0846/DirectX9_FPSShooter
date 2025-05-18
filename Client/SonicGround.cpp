#include "SonicGround.h"
#include "Export_Function.h"

CSonicGround::CSonicGround(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_BACKGROUND);
	Set_ObjTag(L"Ground");

	m_UValue = 0.f;
	m_bGameStart = false;
}

CSonicGround::~CSonicGround()
{
}

_int CSonicGround::Update_GameObject(const _float & fTimeDelta)
{
	//Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	//m_pTransform->m_vInfo[INFO_POS].x -= 10.f *fTimeDelta;

	if (m_bGameStart == true)
	{
		m_pTransform->m_vScale.x += 60.f*fTimeDelta;
		if (m_vMaxScale.x < m_pTransform->m_vScale.x)
			m_pTransform->m_vScale.x = m_vMaxScale.x;

		m_UValue += m_fGameSpeed * fTimeDelta;
		m_RcTex->Edit_U(m_UValue);
	}

	Add_RenderGroup(RENDER_NONALPHA, this);
	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CSonicGround::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonicGround::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_ViewMat);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_Projmat);
	__super::Render_GameObject();
}

void CSonicGround::Game_Start()
{
	m_bGameStart = true;
}

HRESULT CSonicGround::Add_Component()
{
	m_RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Ground_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Ground_Texture", Texture });

	m_ViewMat.Identity();
	D3DXMatrixPerspectiveFovLH(&m_Projmat, D3DXToRadian(60.f), ((_float)WINCX / WINCY), 0.f, 1000.f);

	m_pTransform->Set_Pos({ 0.f,-11.f,120.f });
	m_vMaxScale = { 70.f,4.f,1.f };
	m_pTransform->Set_Scale({ 0.f,4.f,1.f });
	return S_OK;
}

CSonicGround * CSonicGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicGround*		pInstance = new CSonicGround(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
