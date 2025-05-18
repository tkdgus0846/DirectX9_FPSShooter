#include "WallFactory.h"
#include "ShortWall.h"
#include "ShortWall420376.h"
#include "ShortWall420588.h"
#include "ShortWall420740.h"
#include "ShortWall420954.h"
#include "ShortWall421217.h"
#include "ShortWall421405.h"
#include "ShWallPipes420367ortWall.h"
#include "WallLongDoor.h"
#include "WallPanels.h"
#include "WallPanels420377.h"
#include "WallPanels420595.h"
#include "WallPanels420744.h"
#include "WallPanels420948.h"
#include "WallPanels421219.h"
#include "WallPanels421417.h"
#include "WallPanels421568.h"
#include "WallPanels421731.h"
#include "WallPipes.h"
#include "WallPipes420605.h"
#include "WallPipes420745.h"
#include "WallPipes420956.h"
#include "Walls.h"
#include "WallShort.h"
#include "WallShortDoor.h"
#include "WallSpecial.h"
#include "WallSpecial420366.h"
#include "WallSpecial420600.h"
#include "WallSpecial420730.h"
#include "WallSpecial420958.h"
#include "WallSpecial421565.h"
#include "WallVent.h"
#include "WallVent420375.h"
#include "WallVent420596.h"
#include "WallVent420738.h"
#include "WallVent420952.h"
#include "WallVent421863.h"

IMPLEMENT_SINGLETON(CWallFactory)

CWallFactory::CWallFactory()
{
}


CWallFactory::~CWallFactory()
{
	Release();
}

HRESULT CWallFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(ShortWall::Tag(), ShortWall::Create);
	Register(ShortWall420376::Tag(), ShortWall420376::Create);
	Register(ShortWall420588::Tag(), ShortWall420588::Create);
	Register(ShortWall420740::Tag(), ShortWall420740::Create);
	Register(ShortWall420954::Tag(), ShortWall420954::Create);
	Register(ShortWall421217::Tag(), ShortWall421217::Create);
	Register(ShortWall421405::Tag(), ShortWall421405::Create);
	Register(ShWallPipes420367ortWall::Tag(), ShWallPipes420367ortWall::Create);
	Register(WallLongDoor::Tag(), WallLongDoor::Create);
	Register(WallPanels::Tag(), WallPanels::Create);
	Register(WallPanels420377::Tag(),	WallPanels420377::Create);
	Register(WallPanels420595::Tag(),	WallPanels420595::Create);
	Register(WallPanels420744::Tag(),	WallPanels420744::Create);
	Register(WallPanels420948::Tag(),	WallPanels420948::Create);
	Register(WallPanels421219::Tag(),	WallPanels421219::Create);
	Register(WallPanels421417::Tag(),	WallPanels421417::Create);
	Register(WallPanels421568::Tag(),	WallPanels421568::Create);
	Register(WallPanels421731::Tag(),	WallPanels421731::Create);
	Register(WallPipes::Tag(), WallPipes::Create);
	Register(WallPipes420605::Tag(),	WallPipes420605::Create);
	Register(WallPipes420745::Tag(),	WallPipes420745::Create);
	Register(WallPipes420956::Tag(),	WallPipes420956::Create);
	Register(Walls::Tag(), Walls::Create);
	Register(WallShort::Tag(), WallShort::Create);
	Register(WallShortDoor::Tag(), WallShortDoor::Create);
	Register(WallSpecial::Tag(), WallSpecial::Create);
	Register(WallSpecial420366::Tag(), WallSpecial420366::Create);
	Register(WallSpecial420600::Tag(), WallSpecial420600::Create);
	Register(WallSpecial420730::Tag(), WallSpecial420730::Create);
	Register(WallSpecial420958::Tag(), WallSpecial420958::Create);
	Register(WallSpecial421565::Tag(), WallSpecial421565::Create);
	Register(WallVent::Tag(), WallVent::Create);
	Register(WallVent420375::Tag(), WallVent420375::Create);
	Register(WallVent420596::Tag(), WallVent420596::Create);
	Register(WallVent420738::Tag(), WallVent420738::Create);
	Register(WallVent420952::Tag(), WallVent420952::Create);
	Register(WallVent421863::Tag(), WallVent421863::Create);


	ExtractTextureKey();

	return hResult;
}