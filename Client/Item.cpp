#include "Item.h"
#include "Export_Function.h"
#include "Player.h"
#include "SoundMgr.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_ITEM);
	m_bDrop = false;
	m_bBill = true;
	m_fSpeed = 1.f; // 여기 이런식으로 작게줘서 작업하면 나중에 노가다가 심해짐 1초당으로 계산하는게 좋음
	m_fTime = 0.f;

	m_fAge = 0.f;
	m_fLifeSpan = 5.f;

	m_randNum = rand() % 360;
	_matrix matRot;
	D3DXMatrixIdentity(&matRot);

	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_randNum));

	D3DXVec3TransformNormal(&m_pTransform->m_vInfo[INFO_LOOK],
		&m_pTransform->m_vInfo[INFO_LOOK],
		&matRot);
}

CItem::~CItem()
{
}

_int CItem::Update_GameObject(const _float & fTimeDelta)
{
	
	Add_RenderGroup(RENDER_ALPHA, this);

	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	if (m_bBill)
		m_pTransform->Set_Billboard(&matView);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);


	if (m_bDrop == false)	ItemDrop(fTimeDelta);
	return __super::Update_GameObject(fTimeDelta);
}

void CItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);	
	CPlayer* player = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (player && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		SetDead();
	}
}

void CItem::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	CPlayer* player = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (player && collision->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		STOP_PLAY_SOUND(L"sfxpickup.wav", SOUND_EFFECT, 1.f);
		SetDead();
	}
}


void CItem::ItemPatrol(const _float& fTimeDelta)
{
	m_pTransform->Set_Pos(m_pTransform->m_vInfo[INFO_POS].x,
		m_fY,
		m_pTransform->m_vInfo[INFO_POS].z);

	m_fY += m_fSpeed * fTimeDelta; // 이렇게하면 1초에 m_fSpeed 만큼 움직이겠죠?
	if (m_fY >= m_fMaxY || m_fY <= m_fMinY)
	{
		m_fSpeed *= -1.f; // 이건 부호 뒤집어주는거임? 방향?
	}
}

void CItem::ItemMagnetic(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}
	_vec3 pPlayerInfo;

	pPlayer->m_pTransform->Get_Info(INFO_POS, &pPlayerInfo);
	_vec3 vDir = pPlayerInfo - m_pTransform->m_vInfo[INFO_POS];
	D3DXVec3Normalize(&vDir, &vDir);
	m_pTransform->m_vInfo[INFO_POS] +=  vDir * 0.5f; // 이건 아이템 끌어당기는거임?
}

void CItem::ItemDrop(const _float& fTimeDelta)
{
	m_pTransform->m_vInfo[INFO_POS].y += 2.f * m_fTime - (4.9f * m_fTime * m_fTime) * 0.5f;

	m_pTransform->m_vInfo[INFO_POS] += m_pTransform->m_vInfo[INFO_LOOK] * ((_float)(rand() % 2) / 2);

	m_fTime += 0.1f;

	if (m_pTransform->m_vInfo[INFO_POS].y < 0.f)
	{
		m_pTransform->m_vInfo[INFO_POS].y = m_fY;
		m_fTime = 0.f;
		m_bDrop = true;
	}
}

void CItem::Free()
{
	OBJ_INFO objInfo = Get_ObjInfo();
	for (int i = 0; i < objInfo.colNameVec.size(); i++)
	{
		CCollider* pCol = dynamic_cast<CCollider*>(Get_Component(objInfo.colNameVec[i], ID_ALL));
		if (pCol)
			pCol->Get_CollisionList().clear();
	}
	Safe_Release(m_pAniCom);
	Safe_Release(m_pTextureCom);
	__super::Free();
}