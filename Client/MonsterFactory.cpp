#include "MonsterFactory.h"
#include "Baller.h"
#include "Bub.h"
#include "Cryder.h"
#include "Speyeder.h"
#include "NubPilot.h"
#include "Rub.h"
#include "Nub.h"
#include "Turret.h"
#include "Walker.h"
#include "Evasioner.h"
#include "ShopNpc.h"
#include "Bird.h"
#include "Guppi.h"
#include "MiniGuppi.h"
#include "Lizard.h"

IMPLEMENT_SINGLETON(CMonsterFactory)

CMonsterFactory::CMonsterFactory()
{
}


CMonsterFactory::~CMonsterFactory()
{
	Release();
}

HRESULT CMonsterFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(CBaller::Tag(),	&CBaller::Create);
	Register(CBub::Tag(),		&CBub::Create);
	Register(CNub::Tag(),		&CNub::Create);
	Register(CCryder::Tag(),	&CCryder::Create);
	Register(CNubPilot::Tag(),	&CNubPilot::Create);
	Register(CSpeyeder::Tag(),	&CSpeyeder::Create);
	Register(CEvasioner::Tag(),	&CEvasioner::Create);
	Register(CRub::Tag(),		&CRub::Create);
	Register(CTurret::Tag(),	&CTurret::Create);
	Register(CWalker::Tag(),	&CWalker::Create);
	Register(CShopNpc::Tag(),	&CShopNpc::Create);
	Register(CBird::Tag(),		&CBird::Create);
	Register(CGuppi::Tag(),		&CGuppi::Create);
	Register(CMiniGuppi::Tag(), &CMiniGuppi::Create);
	Register(CLizard::Tag(),	&CLizard::Create);

	ExtractTextureKey();

	return hResult;
}
