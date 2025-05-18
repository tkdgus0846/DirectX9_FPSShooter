#include "BossHp.h"
#include "Export_Function.h"
#include "Creature.h"
#include "WalkerBoss.h"
#include "..\Engine\SoundMgr.h"

CBossHp::CBossHp(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"BossHp");
}

CBossHp::~CBossHp()
{
}

HRESULT CBossHp::Add_Component()
{
	m_dRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_dRcTex, E_FAIL);

	m_sRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_sRcTex, E_FAIL);

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BossHpBar_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_HP] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BossHpGuage_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_GUAGE] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_FONT] = Texture;

	return S_OK;
}

HRESULT CBossHp::Ready_GameObject(void)
{
	m_vScale.x = 32.f;
	m_vScale.y = 32.f;

	__super::Ready_GameObject();

	return S_OK;
}

_int CBossHp::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CBossHp::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBossHp::Render_GameObject(void)
{
	CLayer* pLayer = Engine::Get_Layer(LAYER_BOSS);
	if (pLayer == nullptr) { return; }

	pLayer->Get_GameObject_ALL(&vecBoss);
	if (vecBoss.empty()) { return; }


	auto iter = *vecBoss.begin();
	if (iter->Get_ObjTag() == L"WalkerBoss")
	{
		if (!IS_PLAYING(SOUND_BGM_BOSS))
		{
			STOP_ALL_BGM;
			PLAY_BGM(L"finalboss4.wav", SOUND_BGM_BOSS, BGM_SOUND_VOLUME);
		}
	}
	else
	{
		if (!IS_PLAYING(SOUND_BGM_BOSS))
		{
			STOP_ALL_BGM;
			PLAY_BGM(L"Boss.wav", SOUND_BGM_BOSS, BGM_SOUND_VOLUME);
		}
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	for (size_t i = 0; i < BOSS_UI_END; i++)
	{
		switch (i)
		{
		case BOSS_UI_B:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::B);
			break;
		case BOSS_UI_O:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::O);
			break;
		case BOSS_UI_S:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::S);
			break;
		case BOSS_UI_S2:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::S);
			break;
		case BOSS_UI_HP:
			Set_ViewMatrix_UI(0.f, 220.f, 150.f, 15.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_HP])->Render_Texture();
			break;
		case BOSS_UI_GUAGE:
			_float MaxHp = dynamic_cast<CCreature*>(iter)->Get_MaxHP();
			_float CurHp = dynamic_cast<CCreature*>(iter)->Get_HP();
			m_CurHp = CurHp / MaxHp;
			m_dRcTex->Edit_VB(m_CurHp);
			Set_ViewMatrix_UI(0.f, 220.f, 146.f, 13.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_GUAGE])->Render_Texture();
			m_dRcTex->Render_Component();
			continue;
		}
		m_sRcTex->Render_Component();
	}
	__super::Render_GameObject();

	vecBoss.clear();
}


CBossHp * CBossHp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossHp* pInstance = new CBossHp(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBossHp::Free(void)
{
	Safe_Release(m_sRcTex);
	Safe_Release(m_dRcTex);

	auto iter = m_arrMap.begin();
	for (; iter != m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}

	//for_each(vecBoss.begin(), vecBoss.end(), CDeleteObj());
	vecBoss.clear();

	__super::Free();
}
