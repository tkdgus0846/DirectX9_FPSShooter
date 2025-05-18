#include "SonicGame.h"
#include "Sonic.h"
#include "SonicGround.h"
#include "SonicUI.h"
#include "SonicBird.h"
#include "BulletMgr.h"

CSonicGame::CSonicGame(LPDIRECT3DDEVICE9 pGraphicDev) :
	CMiniGame(pGraphicDev),
	m_bGameStarted(false),
	m_fBirdGenCool(2.f),
	m_fBirdGenTime(0.f),
	m_fSpeedUpCool(10.f),
	m_fSpeedUpTime(0.f)
{

}

CSonicGame::~CSonicGame()
{
}

HRESULT CSonicGame::Ready_Scene(void)
{
	m_pSonic = CSonic::Create(m_pGraphicDev);
	m_pGround = CSonicGround::Create(m_pGraphicDev);
	CSonicUI* ui = CSonicUI::Create(m_pGraphicDev);

	m_pSonic->Set_Ground(m_pGround);
	m_pSonic->Set_UI(ui);

	m_fGameSpeed = 4.f;

	
	m_pGround->Set_GameSpeed(m_fGameSpeed);
	Add_GameObject(m_pSonic);
	Add_GameObject(m_pGround);
	Add_GameObject(ui);	
	return S_OK;
}

_int CSonicGame::Update_Scene(const _float& fTimeDelta)
{

	if (m_pSonic->Get_FirstJump() == false)
		m_bGameStarted = true;

	if (m_bGameStarted == true)
	{
		/*m_fSpeedUpTime += fTimeDelta;
		if (m_fSpeedUpCool <= m_fSpeedUpTime)
		{
			m_fGameSpeed += 1.f;
			m_fSpeedUpTime = 0.f;

			m_pGround->Set_GameSpeed(m_fGameSpeed);
		}*/
		Game_Pattern(fTimeDelta);
	}

	return __super::Update_Scene(fTimeDelta);
}

void CSonicGame::Render_Scene(void)
{
}

void CSonicGame::Game_Pattern(const _float& fTimeDelta)
{
	m_fBirdGenTime += fTimeDelta;

	if (m_fBirdGenTime >= m_fBirdGenCool)
	{
		_int randNum = rand() % 4;
		switch (randNum)
		{
		case 0:
			Game_Pattern1(fTimeDelta);
			break;
		case 1:
			Game_Pattern2(fTimeDelta);
			break;
		case 2:
			Game_Pattern3(fTimeDelta);
			break;
		case 3:
			Game_Pattern4(fTimeDelta);
			break;
		}
		m_fBirdGenCool = GetRandomFloat(1.0f, 3.f);
		m_fBirdGenTime = 0.f;
	}
	
}

void CSonicGame::Game_Pattern1(const _float & fTimeDelta)
{
	CBullet* bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 60.f,0.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);
}

void CSonicGame::Game_Pattern2(const _float & fTimeDelta)
{
	CBullet* bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 60.f,0.f,100.f }, {0.f,0.f,1.f}, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);

	bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 70.f,0.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);
}

void CSonicGame::Game_Pattern3(const _float & fTimeDelta)
{
	CBullet* bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 60.f,0.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);

	bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 60.f,10.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);
}

void CSonicGame::Game_Pattern4(const _float & fTimeDelta)
{
	CBullet* bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 60.f,0.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);

	bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 70.f,0.f,100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);

	bird = CBulletMgr::GetInstance()->Pop(L"SonicBird", m_pGraphicDev, { 65.f, 10.f, 100.f }, { 0.f,0.f,1.f }, { 5.f,5.f,1.f }, true, m_fGameSpeed);
	Add_GameObject(bird);
}

CSonicGame* CSonicGame::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicGame *	pInstance = new CSonicGame(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSonicGame::Free(void)
{
	__super::Free();
}
