#include "SkillUI.h"
#include "Export_Function.h"
#include "Player.h"
CSkillUI::CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
	, m_bRenderEnable(true)
{
	Set_ObjTag(L"SkillUI");
}

CSkillUI::~CSkillUI()
{
}

HRESULT CSkillUI::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Skill_List_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Skill_List_Texture", Texture });

	m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Reload_Texture", this));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);

	Ani2 = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani2, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Animation2", Ani2 });
	Ani2->BindAnimation(ANIM_IDLE, m_pTexture, 0.2f, false);
	Ani2->SelectState(ANIM_IDLE);

	Ani3 = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani3, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Animation3", Ani3 });
	Ani3->BindAnimation(ANIM_IDLE, m_pTexture, 0.2f, false);
	Ani3->SelectState(ANIM_IDLE);

	Ani1 = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani1, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Animation1", Ani1 });
	Ani1->BindAnimation(ANIM_IDLE, m_pTexture, 0.0002f, false);
	Ani1->SelectState(ANIM_IDLE);

	return S_OK;
}

HRESULT CSkillUI::Ready_GameObject(void)
{
	m_vScale = { 112.f, 28.f, 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CSkillUI::Update_GameObject(const _float & fTimeDelta)
{
	if (Engine::Get_Player() == nullptr) { return 0; }
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(Engine::Get_Player());

	if (!pPlayer->Get_bAimHack())
	{
		m_bRenderEnable = true;
	}
	else
	{
		m_bRenderEnable = false;
	}

	Engine::Add_RenderGroup(RENDER_AFTER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	if (Ani2->GetFinished())
	{ m_bGravition = false; }

	if (Ani3->GetFinished()) 
	{ m_bAimHack = false;	}

	if (Ani1->GetFinished())
	{ m_bJump = false; }

	return 0;
}

void CSkillUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSkillUI::Render_GameObject(void)
{
	Set_ViewMatrix_UI(-200.f, -182.f);

	if (m_bRenderEnable == true)
	{
		__super::Render_GameObject();
	}

	if (Engine::Get_Player() == nullptr) { return; }
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(Engine::Get_Player());

	if (pPlayer->Get_bGravition() || m_bGravition == true)
	{
		pPlayer->Set_bGravition(false);
		m_bGravition = true;
		Set_ViewMatrix_UI(-227.f, -182.f, 20.f, 19.f);

		if (m_bRenderEnable == true)
		{
			Ani2->Render_Component();
			m_pRcTex->Render_Component();
		}
	}
	else { Ani2->AnimationClear();}

	if (pPlayer->Get_bAimHack() || m_bAimHack == true)
	{
		Ani3->SelectState(ANIM_IDLE);
		m_bAimHack = true;
		Set_ViewMatrix_UI(-172.f, -182.f, 20.f, 19.f);

		if (m_bRenderEnable == true)
		{
			Ani3->Render_Component();
			m_pRcTex->Render_Component();
		}	
	}
	else { Ani3->AnimationClear(); }

	if (pPlayer->Get_bJumped() || m_bJump == true)
	{
		Ani1->SelectState(ANIM_IDLE);
		m_bJump = true;
		Set_ViewMatrix_UI(-117.f, -182.f, 20.f, 19.f);

		if (m_bRenderEnable == true)
		{
			Ani1->Render_Component();
			m_pRcTex->Render_Component();
		}
	}
	else { Ani1->AnimationClear(); }
}

CSkillUI * CSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkillUI* pInstance = new CSkillUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSkillUI::Free(void)
{
	Safe_Release(m_pRcTex);
	Safe_Release(m_pTexture);

	__super::Free();
}
