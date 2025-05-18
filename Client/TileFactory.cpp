#include "TileFactory.h"

#include "BeltTile.h"
#include "BloodTile.h"
#include "ElectricTile.h"
#include "IceTile.h"
#include "GrassTile.h"
#include "LavaTile.h"
#include "OilTile.h"
#include "QuickSandTile.h"
#include "SandTile.h"
#include "SnowTile.h"
#include "SwampTile.h"
#include "DecoratorTile.h"

#include "FloorBeltCorner.h"
#include "FloorGrassS.h"
#include "FloorGrassSE421553.h"
#include "FloorGrassSW.h"
#include "FloorGrassW.h"
#include "FloorGrassW421566.h"
#include "FloorHole421407.h"
#include "FloorHole421573.h"
#include "FloorHole421724.h"
#include "FloorHole421777.h"
#include "FloorSmall.h"
#include "FloorSmall420592.h"
#include "FloorSmall421201.h"
#include "FloorSmall421410.h"
#include "FloorSmall421572.h"
#include "FloorSmall421575.h"
#include "FloorSmall421723.h"
#include "FloorSmall421733.h"

#include "FloorStripes.h"
#include "FloorVent.h"
#include "FloorVent420959.h"
#include "FloorVent421222.h"
#include "FloorVent421406.h"
#include "FloorVent421556.h"
#include "FloorVent421725.h"
#include "FloorVent421869.h"
#include "WaterTile.h"

#include "FloorLarge421204.h"
#include "FloorLarge421409.h"
#include "FloorLarge421559.h"
#include "FloorLarge421721.h"
#include "FloorLarge421865.h"
#include "FloorLarge421871.h"
#include "FloorLarge421874.h"
#include "FloorLarge.h"

#include "SandWaterArc.h"
#include "SandWaterFill.h"
#include "SandWaterLine.h"
IMPLEMENT_SINGLETON(CTileFactory)

CTileFactory::CTileFactory()
{
}

CTileFactory::~CTileFactory()
{
	Release();
}

HRESULT CTileFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);


	Register(CBeltTile::Tag(), &CBeltTile::Create);
	Register(CFloorBeltCorner::Tag(), &CFloorBeltCorner::Create);
	Register(CIceTile::Tag(), &CIceTile::Create);
	Register(CGrassTile::Tag(), &CGrassTile::Create);
	Register(CLavaTile::Tag(), &CLavaTile::Create);
	Register(COilTile::Tag(), &COilTile::Create);
	Register(CQuickSandTile::Tag(), &CQuickSandTile::Create);
	Register(CSandTile::Tag(), &CSandTile::Create);
	Register(CSnowTile::Tag(), &CSnowTile::Create);
	Register(CSwampTile::Tag(), &CSwampTile::Create);
	Register(CElectricTile::Tag(), &CElectricTile::Create);

	//Register(CDecoratorTile::Tag(), &CDecoratorTile::Create);

	Register(FloorGrassS::Tag(),		FloorGrassS::Create);
	Register(FloorGrassSE421553::Tag(), FloorGrassSE421553::Create);
	Register(FloorGrassSW::Tag(),		FloorGrassSW::Create);
	Register(FloorGrassW::Tag(),		FloorGrassW::Create);
	Register(FloorGrassW421566::Tag(),	FloorGrassW421566::Create);
	Register(FloorHole421407::Tag(),	FloorHole421407::Create);
	Register(FloorHole421573::Tag(),	FloorHole421573::Create);
	Register(FloorHole421724::Tag(),	FloorHole421724::Create);
	Register(FloorHole421777::Tag(),	FloorHole421777::Create);
	Register(FloorSmall::Tag(),			FloorSmall::Create);
	Register(FloorSmall420592::Tag(),	FloorSmall420592::Create);
	Register(FloorSmall421201::Tag(),	FloorSmall421201::Create);
	Register(FloorSmall421410::Tag(),	FloorSmall421410::Create);
	Register(FloorSmall421572::Tag(),	FloorSmall421572::Create);
	Register(FloorSmall421575::Tag(),	FloorSmall421575::Create);
	Register(FloorSmall421723::Tag(),	FloorSmall421723::Create);
	Register(FloorSmall421733::Tag(), FloorSmall421733::Create);

	Register(FloorStripes::Tag(), FloorStripes::Create);
	Register(FloorVent::Tag(), FloorVent::Create);
	Register(FloorVent420959::Tag(), FloorVent420959::Create);
	Register(FloorVent421222::Tag(), FloorVent421222::Create);
	Register(FloorVent421406::Tag(), FloorVent421406::Create);
	Register(FloorVent421556::Tag(), FloorVent421556::Create);
	Register(FloorVent421725::Tag(), FloorVent421725::Create);
	Register(FloorVent421869::Tag(), FloorVent421869::Create);

	Register(CWaterTile::Tag(), CWaterTile::Create);

	Register(FloorLarge421204::Tag(), FloorLarge421204::Create);
	Register(FloorLarge421409::Tag(), FloorLarge421409::Create);
	Register(FloorLarge421559::Tag(), FloorLarge421559::Create);
	Register(FloorLarge421721::Tag(), FloorLarge421721::Create);
	Register(FloorLarge421865::Tag(), FloorLarge421865::Create);
	Register(FloorLarge421871::Tag(), FloorLarge421871::Create);
	Register(FloorLarge421874::Tag(), FloorLarge421874::Create);
	Register(FloorLarge::Tag(), FloorLarge::Create);
	Register(SandWaterArc::Tag(), SandWaterArc::Create);
	Register(SandWaterFill::Tag(), SandWaterFill::Create);
	Register(SandWaterLine::Tag(), SandWaterLine::Create);

	ExtractTextureKey();

	return hResult;
}