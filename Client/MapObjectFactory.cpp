#include "MapObjectFactory.h"

#include "HardPyramid.h"
#include "SoftPyramid.h"
#include "Slider.h"
#include "TallGrass.h"
#include "Tree.h"
#include "SnowTree.h"
#include "SnowSoTree.h"
#include "SnowMan.h"
#include "Cactus1.h"
#include "Cactus2.h"
#include "Cactus3.h"
#include "Cactus4.h"
#include "Cactus5.h"

IMPLEMENT_SINGLETON(CMapObjectFactory)

CMapObjectFactory::CMapObjectFactory()
{
}


CMapObjectFactory::~CMapObjectFactory()
{
	Release();
}

HRESULT CMapObjectFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(CHardPyramid::Tag(),	&CHardPyramid::Create);
	Register(CSoftPyramid::Tag(),	&CSoftPyramid::Create);
	Register(CSlider::Tag(),		&CSlider::Create);
	Register(CTallGrass::Tag(),		&CTallGrass::Create);
	Register(CTree::Tag(), &CTree::Create);
	Register(CSnowTree::Tag(), &CSnowTree::Create);
	Register(CSnowSoTree::Tag(), &CSnowSoTree::Create);
	Register(CSnowMan::Tag(), &CSnowMan::Create);

	Register(Cactus1::Tag(), &Cactus1::Create);
	Register(Cactus2::Tag(), &Cactus2::Create);
	Register(Cactus3::Tag(), &Cactus3::Create);
	Register(Cactus4::Tag(), &Cactus4::Create);
	Register(Cactus5::Tag(), &Cactus5::Create);

	ExtractTextureKey();

	return hResult;
}
