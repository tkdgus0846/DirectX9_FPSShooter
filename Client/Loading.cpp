#include "stdafx.h"
#include "Loading.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"

#include "RoomMgr.h"
#include "BulletMgr.h"
#include "ItemManager.h"
#include "EffectManager.h"

#include "TileFactory.h"
#include "WallFactory.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"
#include "FileSystem.h"
#include "ShopNpc.h"
#include "NubBoss.h"
#include "WalkerBoss.h"
#include "TreeBoss.h"
#include "WormHead.h"

#include "CheckPoint.h"

#include "NubBoss.h"
#include "TreeBoss.h"
#include "WormHead.h"
#include "WalkerBoss.h"
#include "..\Engine\ParticleMgr.h"

#include "Snow.h"
#include "..\Engine\SandStorm.h"
#include "WaterTile.h"
#include "..\Engine\VentParticle.h"

#define LEVEL1_EDIT_DATANAME L"Level1.dat"

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	ZeroMemory(m_szString, sizeof(_tchar) * 128);
	m_pGraphicDev->AddRef();
}

CLoading::~CLoading()
{
}

unsigned int CLoading::Thread_Main(void * pArg)
{
	CLoading*	pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag = 0;

	EnterCriticalSection(&(pLoading->Get_Crt()));

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_EDITSTAGE:
		iFlag = pLoading->Loading_ForEditStage();
		break;
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;
	case LOADING_STAGE2:
		iFlag = pLoading->Loading_ForStage2();
		break;
	case LOADING_STAGE3:
		iFlag = pLoading->Loading_ForStage3();
		break;
	case LOADING_STAGE4:
		iFlag = pLoading->Loading_ForStage4();
		break;
	case LOADING_BOSS:
		break;
	}
	
	LeaveCriticalSection(&(pLoading->Get_Crt()));

	//_endthreadex(0);

	if (iFlag == E_FAIL)
		exit(-1);

	return iFlag;
}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	// 1. 보안 속성
	// 2. 스택 메모리의 크기, 0인 경우 쓰레드가 요구하는 크기만큼 할당
	// 3. 쓰레드 함수의 이름(함수 포인터)
	// 4. 쓰레드 함수를 통해 가공하고자 하는 데이터의 주소
	// 5. 쓰레드의 생성 및 실행을 조절하기 위한 FLAG 값, 기본 값으로 0
	// 6. 쓰레드 ID반환

	m_bFinish = false;
	
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);
	
	m_eID = eID;

	// 빨간색으로 블랜딩할 멀티 텍스처 용도의 텍스처 파일
	return S_OK;
}

_uint CLoading::Loading_ForEditStage(void)
{
	Loading_ForStage();

	return 0;
}

_uint CLoading::Loading_ForStage(void)
{
	Set_String(L"Texture Loading....");

	IDirect3DBaseTexture9* redTexture;
	FAILED_CHECK_RETURN(D3DXCreateTextureFromFile(m_pGraphicDev, L"../Resource/CollisionDebug/Red.png", (LPDIRECT3DTEXTURE9*)&redTexture), E_FAIL);
	m_pGraphicDev->SetTexture(1, redTexture);

	// Bullet Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"NormalBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/bigbullet_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"IceBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/iceBeam_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FireBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/smallExplode_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MeteorPoint_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/MeteorPoint.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FireBall_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/fireBall_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"EnemyBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/sprEnemyBullet_%d.png", 2)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"VortexBulletBefore_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/Energy_%d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"VortexBulletAfter_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/vortex.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Laser_Red_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/laserbullet-red.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Laser_Blue_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/laserbullet.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SwordBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/sword.png")), E_FAIL);

	/*FAILED_CHECK_RETURN(Engine::Ready_Proto(L"StarBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Star_%d.png",4)), E_FAIL);*/ // -> 로고에서 해주고있음.

	// Monster Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Nub_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/Nub_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Bub_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/bub_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Rub_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/rub_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Bird_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/robobird_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Nub_Pilot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/nub_pilot_%d.png", 3)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Lizard_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/SandLizard_%d.png", 3)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Blue_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_blue_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Baller_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/baller_%d.png", 14)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Walker_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/walker_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Turret_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/sprTurret_strip8_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Cryder_Walk_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/cryder_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Cryder_Stay_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/cryder_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Cryder_Jump_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/cryder_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Speyeder_Walk_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/speyeder_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Speyeder_Stay_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/speyeder_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Speyeder_Jump_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/speyeder_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Speyeder_Explosion_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/speyeder_off.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_NubBoss_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/boss1_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WalkerBoss_Walk_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/WalkerBoss_%d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WalkerBoss_Idle_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/WalkerBoss_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Drill_Side_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/worm_drill_side_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Drill_Top_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/worm_drill_top_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Drill_Face_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/worm_face_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Drill_Back_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/body_front.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Body_Side_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/body_side.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Body_Top_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/body_top.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Tail_Back_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/tail_back.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Tail_Side_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/tail_side.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_WormBoss_Tail_Top_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/tail_top.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_TreeBoss_Summon_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/TreeBoss_%d.png", 7)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_TreeBoss_Idle_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/TreeBoss_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Evasioner_Idle_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/head_forward.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Evasioner_Evasion_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/head_forward_aggro.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Evasioner_Dead_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/head_forward_dead.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BossShadow_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Boss/bossShadow.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Boss_AttackPoint_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/MeteorPoint.png")), E_FAIL);

	// Effect 텍스쳐
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Explosion_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/explosion_%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ExplosionBlue", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/ExplosionBlue_%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandBurst", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/sandburst_%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandBurst_Move", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/sandburst_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShockWave", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/shockwave_%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RootAttack", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/rootAttack_%d.png", 3)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RedBlood", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/redblood_%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Snow_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Level/wob_floor_4.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandStorm_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Level/SandStorm.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Portal_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Portal%d.png",3)), E_FAIL);
	

	// Collision Texture for the Debug
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collision_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/CollisionDebug/Green.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collision_Red_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/CollisionDebug/Red.png")), E_FAIL);

	static vector<wstring> decoratTile;
	// Tile Texture

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorDirt", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorDirt.png")), E_FAIL);
	decoratTile.push_back(L"FloorDirt");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorEmpty #421205", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorEmpty #421205.png")), E_FAIL);
	decoratTile.push_back(L"FloorEmpty #421205");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorEmpty #421414", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorEmpty #421414.png")), E_FAIL);
	decoratTile.push_back(L"FloorEmpty #421414");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorEmpty #421730", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorEmpty #421730.png")), E_FAIL);
	decoratTile.push_back(L"FloorEmpty #421730");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorEmpty #421769", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorEmpty #421769.png")), E_FAIL);
	decoratTile.push_back(L"FloorEmpty #421769");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorEmpty", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorEmpty.png")), E_FAIL);
	decoratTile.push_back(L"FloorEmpty");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrass #421563", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrass #421563.png")), E_FAIL);
	decoratTile.push_back(L"FloorGrass #421563");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrass", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrass.png")), E_FAIL);
	decoratTile.push_back(L"FloorGrass");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassE #421561", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassE #421561.png")), E_FAIL);
	decoratTile.push_back(L"FloorGrassE #421561");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassN", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassN.png")), E_FAIL);
		decoratTile.push_back(L"FloorGrassN");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassNE #421562", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassNE #421562.png")), E_FAIL); 
	decoratTile.push_back(L"FloorGrassNE #421562");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassNE", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassNE.png")), E_FAIL);
	decoratTile.push_back(L"FloorGrassNE");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassNW", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassNW.png")), E_FAIL);
		decoratTile.push_back(L"FloorGrassNW");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassS #421564", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassS #421564.png")), E_FAIL);
		decoratTile.push_back(L"FloorGrassS #421564");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassS", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassS.png")), E_FAIL); 
		decoratTile.push_back(L"FloorGrassS");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassSE #421553", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassSE #421553.png")), E_FAIL); 
		decoratTile.push_back(L"FloorGrassSE #421553");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassSW", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassSW.png")), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassW #421566", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassW #421566.png")), E_FAIL); 
		decoratTile.push_back(L"FloorGrassW #421566");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrassW", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrassW.png")), E_FAIL);
		decoratTile.push_back(L"FloorGrassW");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorHole #421407", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorHole #421407.png")), E_FAIL); 
		decoratTile.push_back(L"FloorHole #421407");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorHole #421573", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorHole #421573.png")), E_FAIL);
		decoratTile.push_back(L"FloorHole #421573");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorHole #421724", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorHole #421724.png")), E_FAIL); 
		decoratTile.push_back(L"FloorHole #421724");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorHole #421777", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorHole #421777.png")), E_FAIL); 
		decoratTile.push_back(L"FloorHole #421777");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #420592", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #420592.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #420592");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421201", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421201.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421201");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421410", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421410.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421410");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421572", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421572.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421572");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421575", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421575.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421575");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421723", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421723.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421723");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall #421733", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall #421733.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall #421733");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSmall", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSmall.png")), E_FAIL);
		decoratTile.push_back(L"FloorSmall");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421874", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421874.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421874");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421871", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421871.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421871");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421865", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421865.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421865");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421721", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421721.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421721");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421559", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421559.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421559");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421409", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421409.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421409");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLarge #421204", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421204.png")), E_FAIL);
		decoratTile.push_back(L"FloorLarge #421204");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandWaterArc", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/SandWaterArc_%d.png", 2)), E_FAIL);
		decoratTile.push_back(L"SandWaterArc");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandWaterFill", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/SandWaterFill_%d.png", 2)), E_FAIL);
		decoratTile.push_back(L"SandWaterFill");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandWaterLine", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/SandWaterLine_%d.png", 2)), E_FAIL);
		decoratTile.push_back(L"SandWaterLine");









		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorStripes", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorStripes.png")), E_FAIL);
		decoratTile.push_back(L"FloorStripes");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #420959", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #420959.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #420959");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #421222", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #421222.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #421222");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #421406", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #421406.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #421406");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #421556", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #421556.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #421556");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #421725", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #421725.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #421725");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent #421869", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent #421869.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent #421869");

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorVent", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorVent.png")), E_FAIL);
		decoratTile.push_back(L"FloorVent");





	// WallTexture

	// 기본
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels.png")), E_FAIL);

	// 정글
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #420377", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #420377.png")), E_FAIL);

	// 설원
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #420595", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #420595.png")), E_FAIL);
	
	// 사막
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #420744", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #420744.png")), E_FAIL);




	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Dock_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Level/dock_%d.png", 15)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Open_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Level/dock_14.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorCrate_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorCrate.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorGrass #421873", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorGrass #421873.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSand", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSand.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorIce", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorIce.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSnow", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorSnow.png")), E_FAIL);

	// Tile Multi Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorBelt", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorBelt_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorBeltCorner", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorBeltCorner_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorBlood", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorBlood_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorElectric", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorElectric_%d.png", 3)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorLava", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorLava_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorWater", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/Water_%d.png",4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorOil", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorOil_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorQuicksand", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorQuicksand_%d.png", 1)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorSwamp", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Tile/FloorSwamp_%d.png", 4)), E_FAIL);

	// Wall Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #420376", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #420376.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #420588", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #420588.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #420740", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #420740.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #420954", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #420954.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #421217", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #421217.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall #421405", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall #421405.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShortWall", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/ShortWall.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallLong", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallLong.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallLongDoor", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallLongDoor.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #420948", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #420948.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #421219", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #421219.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #421417", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #421417.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #421568", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #421568.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPanels #421731", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #421731.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ShWallPipes #420367ortWall", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPipes #420367.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPipes #420605", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPipes #420605.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPipes #420745", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPipes #420745.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPipes #420956", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPipes #420956.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallPipes", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPipes.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Walls", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Walls.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallShort", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallShort.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallShortDoor", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallShortDoor.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial #420366", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial #420366.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial #420600", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial #420600.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial #420730", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial #420730.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial #420958", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial #420958.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial #421565", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial #421565.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallSpecial", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallSpecial.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent #420375", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent #420375.png")), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent #420596", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent #420596.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent #420738", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent #420738.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent #420952", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent #420952.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent #421863", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent #421863.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallVent", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallVent.png")), E_FAIL);

	// Gun Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Gun", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gun/Gun.png")), E_FAIL);

	// Map Object
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SoftPyramid_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Entities/SoftPyramid.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HardPyramid_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Entities/HardPyramid.dds")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Slider_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/slider.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Tall_Grass_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/tall_grass.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Tree_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/tree.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"CheckPoint_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/checkpoint_%d.png", 8)), E_FAIL);



	// Snow Map Obj
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SnowSoTree", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Snow/SnowSoTree.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SnowTree", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Snow/SnowTree.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SnowMan", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Snow/SnowMan_%d.png", 4)), E_FAIL);

	// Dessert Map Obj
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus1", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Dessert/Cactus1.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus2", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Dessert/Cactus2.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus3", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Dessert/Cactus3.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus4", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Dessert/Cactus4.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus5", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/MapObject/Dessert/Cactus5.png")), E_FAIL);

	// UI
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletBar_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/hud_secondary_ext_edit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletGauge_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/hud_ammo_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"UltimateGuage_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Ultimate_Guage.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"CrossHair_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/sprReticle_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Hp_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/hud_hearts_%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Coin_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/sprBigCoin_strip6_%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Disc_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/data_%d.png", 4)), E_FAIL);
	/*FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Num_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Text/tigl_font2_DEPRECATE_%d.png", 42)), E_FAIL);*/
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BossHpBar_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/BossHpBar.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BossHpGuage_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/BossHpGuage.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_bigshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_bigshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_explosiveshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_explosiveshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_flameshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_flameshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_rapidshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_rapidshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_spreadshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_spreadshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_freezeshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_freezeshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_lasershot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Weapon_lasershot.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Scope_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/ScopeEdit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BloodScreen", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/BloodScreen.png")), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Skill_List_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Skill_List.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TimeStop_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/TimeStop.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Gravition_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Gravition.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Tactical_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Tactical.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Jump_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Jump.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Reload_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Reload100_%d.png", 100)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MiniMap_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/hud_map.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MapPos_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Map/mapPos.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ESWN_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Map/ESWN.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MiniMapBack_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/Map/MiniMapBack_%d.png", 19)), E_FAIL);

	// Item
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SmallCoin_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/sprCoin_strip6_%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletItem_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/sprBullet_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HeartItem_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/hearts_0.png")), E_FAIL);	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BootsItem_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/boots.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SkyBox_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/SkyBox/SkyBox.dds")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level1_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level1_Tennel.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level2_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level2_Tennel.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level3_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level3_Tennel.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level4_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level4_Tennel.dds")), E_FAIL);

	// NPC
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"shopkeeperidle_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/shopkeeperidle_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"shopkeeperdamaged_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/shopkeeperdamaged_%d.png",3)), E_FAIL);

	Set_String(L"Buffer Load ing.......");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TriCol", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcCol", CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"CubeTex", CCubeTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RoomTex", CRoomTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorTex", CFloorTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MapTex", CFloorTex::Create(m_pGraphicDev, 5, 5, 60)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallTex", CWallTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FrustrumNormalTex", CFrustrumNormalTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RigidBody", CRigidbody::Create(m_pGraphicDev)), E_FAIL);
	
	/*FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Animation", CAnimation::Create(m_pGraphicDev)), E_FAIL);*/
	
	/////////////////////////// 파티클
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Snow_Particle", CSnow::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SandStorm_Particle", CSandStorm::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Firework_Particle", CFirework::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Vortex_Particle", CVortexParticle::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"NormalBullet_Particle", CNormalBulletParticle::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"UpSmoke_Particle", CUpSmokeParticle::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"JumpSmoke_Particle", CJumpSmokeParticle::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"PyramidDestory_Particle", CPyramidDestoryParticle::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Vent_Particle", CVentParticle::Create(m_pGraphicDev)), E_FAIL);

	/////////////////////////// 파티클 텍스쳐 
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Smoke_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Particle/smoke.png")), E_FAIL);

	Set_String(L"Buffer Loading..........");


	Set_String(L"AI Loading..........");
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Move", CMoveLook::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Wait", CWait::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_RandomLook", CRandomLook::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Jump", CJump::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_BigJump", CBigJump::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Attack", CAttack::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Evasion", CEvasion::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_LeapJump", CLeapJump::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_BackJump", CBackJump::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_LookAtTarget", CLookAtTarget::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Rush", CRush::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_OnPlayer", COnPlayer::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Parabola", CParabola::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_MovePoint", CMovePoint::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_MoveCos", CMoveCos::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_MoveY", CMoveY::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_LookAtPlayer", CLookAtPlayer::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_ATKToPlayer", CAttackToPlayer::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_WormMoveCtrl", CWormMoveCtrl::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_SpreadShot", CSpreadShot::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_MoveUp", CMoveUp::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_TimeInLimit", CTimeInLimit::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_RangeCheck", CRangeCheck::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_RangeInPlayer", CRangeInPlayer::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_NotCollisionWall", CNotCollisionWall::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_CoolTime", CCoolTime::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_BoolCheck", CBoolCheck::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_DeadCheck", CDeadCheck::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_CutSceneCheck", CCutSceneCheck::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Sequence", CSequence::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Selector", CSelector::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Root", CRoot::Create(m_pGraphicDev)), E_FAIL);

	Set_String(L"Room Loading..........");
	// ==임시 코드==
	const auto& uMapProto = Engine::CProtoMgr::GetInstance()->Get_ProtoMap();

	for (auto iter : uMapProto)
	{
		if (dynamic_cast<CTexture*>(iter.second))
			m_listTags.push_back(iter.first);
	}

	Set_String(L"ObjectPool Loading..........");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 25, L"NormalBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 30, L"FireBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 10, L"IceBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 10, L"LaserBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 15, L"EnemyBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 30, L"RedLaserBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 10, L"SwordBullet");
	CBulletMgr::GetInstance()->Reserve(m_pGraphicDev, 60, L"ShockWave");

	CItemManager::GetInstance()->Reserve(m_pGraphicDev, 15, L"BulletItem");
	CItemManager::GetInstance()->Reserve(m_pGraphicDev, 15, L"CoinItem");
	CItemManager::GetInstance()->Reserve(m_pGraphicDev, 15, L"HeartItem"); 
	/*CEffectManager::GetInstance()->Reserve(m_pGraphicDev, 20, L"Explosion_Texture");*/


	Set_String(L"Factory Loading..........");

	TILE_FACTORY->Ready_Factory(m_pGraphicDev);
	WALL_FACTORY->Ready_Factory(m_pGraphicDev);
	MONSTER_FACTORY->Ready_Factory(m_pGraphicDev);
	MAPOBJ_FACTORY->Ready_Factory(m_pGraphicDev);
	//CLoader::GetInstance()->Ready_Loader(m_pGraphicDev);

	Set_String(L"Room Loading..........");
	
	ROOM_MGR->Create_Default_Room(STAGE1);

	CShopNpc* npc = dynamic_cast<CShopNpc*>(CShopNpc::Create(m_pGraphicDev));
	npc->Add_SellItem_Stage1();
	ROOM_MGR->Push_Back_Obj(3, npc);
	ROOM_MGR->Push_Back_Obj(3, CCheckPoint::Create(m_pGraphicDev));

	CFileSystem::Load(LEVEL1_EDIT_DATANAME);
	ROOM_MGR->Push_Back_Obj(4, CNubBoss::Create(m_pGraphicDev, { 85.f, 0.f, 85.f }));

	m_bFinish = true;
	Set_String(L"Loading Complete!!!!!!!!");

	return 0;
}

_uint CLoading::Loading_ForStage2(void)
{
	Set_String(L"Room Loading..........");
	//SECTION_MGR->Create_Section2();
	ROOM_MGR->Release_All_Room();
	ROOM_MGR->Set_Tennel_Texture(STAGE2);
	ROOM_MGR->Create_Default_Room(STAGE2); // 여기서 룸들을 싹다 만든다.

	CShopNpc* npc = dynamic_cast<CShopNpc*>(CShopNpc::Create(m_pGraphicDev));
	npc->Add_SellItem_Stage2();
	ROOM_MGR->Push_Back_Obj(3, npc);
	ROOM_MGR->Push_Back_Obj(3, CCheckPoint::Create(m_pGraphicDev));

	ROOM_MGR->Push_Back_Obj(4, CTreeBoss::Create(m_pGraphicDev, { 85.f, -4.f, 85.f }));

	CFileSystem::Load(L"Level2.dat");

	Set_String(L"Loading Complete!!!!!!!!");
	m_bFinish = true;
	return 0;
}

_uint CLoading::Loading_ForStage3(void)
{
	Set_String(L"Room Loading..........");
	ROOM_MGR->Release_All_Room();
	ROOM_MGR->Set_Tennel_Texture(STAGE3);
	ROOM_MGR->Create_Default_Room(STAGE3); // 여기서 룸들을 싹다 만든다.


	CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"SandStorm_Particle", 500, { 85.f,25.f,25.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);

	ROOM_MGR->Push_Back_Obj(1, particle);

	particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"SandStorm_Particle", 500, { 85.f,25.f,85.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);

	ROOM_MGR->Push_Back_Obj(4, particle);

	CShopNpc* npc = dynamic_cast<CShopNpc*>(CShopNpc::Create(m_pGraphicDev));
	npc->Add_SellItem_Stage3();
	ROOM_MGR->Push_Back_Obj(3, npc);
	ROOM_MGR->Push_Back_Obj(3, CCheckPoint::Create(m_pGraphicDev));

	ROOM_MGR->Push_Back_Obj(4, CWormHead::Create(m_pGraphicDev, { 85.f, -10.f, 65.f }));
	CFileSystem::Load(L"Level3.dat");

	Set_String(L"Loading Complete!!!!!!!!");
	m_bFinish = true;
	return 0;
}

_uint CLoading::Loading_ForStage4(void)
{
	Set_String(L"Room Loading..........");
	ROOM_MGR->Release_All_Room();
	ROOM_MGR->Set_Tennel_Texture(STAGE4);
	ROOM_MGR->Create_Default_Room(STAGE4); // 여기서 룸들을 싹다 만든다.

	CShopNpc* npc = dynamic_cast<CShopNpc*>(CShopNpc::Create(m_pGraphicDev));
	npc->Add_SellItem_Stage4();
	ROOM_MGR->Push_Back_Obj(3, npc);
	ROOM_MGR->Push_Back_Obj(3, CCheckPoint::Create(m_pGraphicDev));

	CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"Snow_Particle", 80, { 85.f,25.f,25.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);


	ROOM_MGR->Push_Back_Obj(1, particle);

	particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"Snow_Particle", 80, { 25.f,25.f,25.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);

	ROOM_MGR->Push_Back_Obj(0, particle);

	particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"Snow_Particle", 80, { 25.f,25.f,145.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);

	ROOM_MGR->Push_Back_Obj(6, particle);

	particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"Snow_Particle", 80, { 85.f,25.f,85.f }, { 0.f,0.f,0.f }, { 50.f,50.f,50.f }, true);
	ROOM_MGR->Push_Back_Obj(4, particle);

	ROOM_MGR->Push_Back_Obj(4, CWalkerBoss::Create(m_pGraphicDev, { 85.f, 0.f, 65.f }));
	CFileSystem::Load(L"Level4.dat");

	Set_String(L"Loading Complete!!!!!!!!");
	m_bFinish = true;
	return 0;
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading *	pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}