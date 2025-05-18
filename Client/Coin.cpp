#include "Coin.h"
#include "Export_Function.h"
#include "Player.h"


CCoin::CCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"Coin");

}

CCoin::~CCoin()
{
}

HRESULT CCoin::Add_Component()
{
	// 코인
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Coin_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Coin_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.15f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });


	// 숫자
	for (size_t i = 0; i < m_MaxNumber; i++)
	{
		CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);
		m_vecRc.push_back(RcTex);
	}

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);

	return S_OK;
}

HRESULT CCoin::Ready_GameObject(void)
{

	m_vScale = { 12.f, 12.f, 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CCoin::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCoin::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCoin::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(Engine::Get_Player());
	if (pPlayer == nullptr) return;

	_int coin = pPlayer->Get_Coin();

	string strCoin = to_string(coin);

	int strLen = strCoin.length();
	for (size_t i = 0, j = 2, k = 0; i < m_MaxNumber; i++, j--, k++)
	{
		_int iNum = 26;
		if (j >= strLen)
		{
			iNum = 26;
			k--;
		}
		else
		{
			iNum = m_iStartNum + strCoin[k] - 48;
		}
		CUI::Set_ViewMatrix_UI(330 + (25.f * i), 250.f, 22.f, 20.f);
		m_pTextureCom->Render_Texture(iNum);
		m_vecRc[i]->Render_Component();
	}

	Set_ViewMatrix_UI(300.f, 250.f, 12.f, 12.f);

	__super::Render_GameObject();
}

_int CCoin::Compute_Num(string pPlayerCoin)
{

	return _int();
}

CCoin * CCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCoin* pInstance = new CCoin(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCoin::Free(void)
{
	Safe_Release(m_pTextureCom);
	for_each(m_vecRc.begin(), m_vecRc.end(), CDeleteObj());
	__super::Free();
}