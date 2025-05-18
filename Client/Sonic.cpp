#include "Sonic.h"
#include "Export_Function.h"
#include "SonicGround.h"
#include "SonicUI.h"
#include "..\Engine\SoundMgr.h"

CSonic::CSonic(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_fMaxJumpTime(2.f)
{
	Set_LayerID(LAYER_PLAYER);
	Set_ObjTag(L"Sonic");

	m_pTransform->Set_MoveType(CTransform::MOVETYPE::AIRCRAFT);

	m_fJumpTime = 0.f;
	m_fForce = 0.f;
	m_bJumped = false;
	m_bFirstJump = true;
}

CSonic::~CSonic()
{
}

_int CSonic::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Add_RenderGroup(RENDER_ALPHA, this);

	Key_Input(fTimeDelta);
	
	Jump(fTimeDelta);
	
	return __super::Update_GameObject(fTimeDelta);
}

void CSonic::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonic::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_ViewMat);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_Projmat);

	__super::Render_GameObject();
}

void CSonic::Key_Input(const _float& fTimeDelta)
{
	if (Key_Up(DIK_SPACE))
	{
	}

	if (Key_Pressing(DIK_SPACE))
	{

		if (m_bFirstJump == true)
		{
			m_pGround->Game_Start();
			m_pUI->Start_Game();
			m_bFirstJump = false;
			/*STOP_ALL_BGM;
			PLAY_BGM(L"SonicBGM.wav", SOUND_BGM, 0.5f);*/
		}
		
		if (m_bJumped == false)
		{
			STOP_PLAY_SOUND(L"SonicJump.wav", SOUND_EFFECT, 1.f);
			m_pUI->Add_Score(10);
			m_pAnimation->SelectState(ANIM_RUN);

			m_bJumped = true;

			m_fForce = 6.0f;
			m_fJumpTime = 0.f;
		}
		/*else
		{
			m_fJumpTime += fTimeDelta;
		}*/
		
	}

	if (Engine::Key_Down((DIK_C))) Engine::Toggle_ColliderRender();
	
	//if (Key_Pressing(DIK_F)) m_pUI->Add_Score();
}

void CSonic::Jump(const _float& fTimeDelta)
{
	if (m_bJumped == true)
	{
		m_fJumpTime += fTimeDelta;
		_float fY = m_fForce  * m_fJumpTime - 9.9f * m_fJumpTime * m_fJumpTime;

		m_pTransform->m_vInfo[INFO_POS].y += fY;

		if (m_pTransform->m_vInfo[INFO_POS].y < 0.f)
		{
			m_pTransform->m_vInfo[INFO_POS].y = 0.f;
			m_bJumped = false;
			m_pAnimation->SelectState(ANIM_WALK);
			return;
		}
	}
	
}

void CSonic::Set_Ground(CGameObject* obj)
{
	m_pGround = dynamic_cast<CSonicGround*>(obj);
}

void CSonic::Set_UI(CGameObject* obj)
{
	m_pUI = dynamic_cast<CSonicUI*>(obj);
}

void CSonic::OnCollisionStay(const class Collision* collision)
{
	PLAY_SOUND(L"sfxBreak.wav", SOUND_ENEMY, 1.f);
	SetDead();
}

HRESULT CSonic::Add_Component()
{
	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYER));
	NULL_CHECK_RETURN(pCollider);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 5.f,7.f,10.f });

	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicWalk_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicWalk_Texture", Texture });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);

	m_pAnimation->BindAnimation(ANIM_WALK, Texture, 0.08f);
	
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicRun_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicRun_Texture", Texture });

	m_pAnimation->BindAnimation(ANIM_RUN, Texture, 0.06);

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicDead_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicDead_Texture", Texture });

	m_pAnimation->BindAnimation(ANIM_DEAD, Texture);

	m_pAnimation->SelectState(ANIM_WALK);

	m_ViewMat.Identity();
	D3DXMatrixPerspectiveFovLH(&m_Projmat, D3DXToRadian(60.f), ((_float)WINCX / WINCY), 0.f, 1000.f);

	m_pTransform->Set_Pos({ -30.f,0.f,100.f });
	m_pTransform->Set_Scale({ 10.f,10.f,1.f });

	return S_OK;
}

CSonic * CSonic::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonic*		pInstance = new CSonic(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
