#include "EndingBackground.h"

#include "Export_Function.h"


CEndingBackground::CEndingBackground(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_iSeperator(0),
	m_CurSeperatorIndex(0)
{
	Set_LayerID(LAYER_BACKGROUND);
	Set_ObjTag(L"Background");
}


CEndingBackground::~CEndingBackground()
{
}

CEndingBackground* CEndingBackground::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEndingBackground*		pInstance = new CEndingBackground(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CEndingBackground::Add_Component()
{
	m_LogoTextTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));

	

	Make_Logo_Text("KIM SANG HYEON", { 190.f,200.f,0.f }, 16.f);
	Make_Logo_Text("JOO SEONG HWAN", { 190.f,250.f,0.f }, 16.f);
	Make_Logo_Text("JEON DAE IN", { 190.f,300.f,0.f }, 16.f);
	Make_Logo_Text("JEON YUN HYEOK", { 190.f,350.f,0.f }, 16.f);

	Make_Logo_Text("THANK YOU FOR WATCHING!!", { 250.f,425.f,0.f }, 16.f);

	m_TextSeperator.push_back(m_LogoTextBufferVec.size());

	m_CurSeperatorIndex = 0;
	return S_OK;
}

void CEndingBackground::Render_GameObject(void)
{
	// m_TextSeperator[m_CurSeperatorIndex] 부터
	// m_TextSeperator[m_CurSeperatorIndex + 1] 까지 해야함.

	_int startIndex = m_TextSeperator[m_CurSeperatorIndex];
	_int endIndex = m_TextSeperator[m_CurSeperatorIndex + 1];

	for (int i = 0; i < m_LogoTextBufferVec.size(); i++)
	{
		const _vec3& pos = m_LogoTextPosVec[i];
		/*Set_ViewMatrix_UI(pos.x, pos.y, 30.f, 30.f);*/

		_matrix endingMatrix, transMatrix, rotationMatrix, scaleMatrix;
		transMatrix.Translation(pos.x, pos.y, -180.f);
		scaleMatrix.Scaling(10.f, 10.f, 10.f);
		rotationMatrix.RotationY(D3DXToRadian(180.f));

		endingMatrix = scaleMatrix * rotationMatrix * transMatrix;

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &endingMatrix);

		m_LogoTextTexture->Render_Texture(m_LogoTextNumVec[i]);
		m_LogoTextBufferVec[i]->Render_Component();
	}


	__super::Render_GameObject();
}

_int CEndingBackground::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}

void CEndingBackground::Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq)
{
	_vec3 myPoint = startPoint;

	m_TextSeperator.push_back(m_iSeperator);
	m_iSeperator += msg.length();

	// . => 46   ! => 33  A => 65
	for (int i = 0; i < msg.length(); i++)
	{
		_uint num = msg[i] - 'A';
		if (msg[i] < 'A')
		{
			if (msg[i] == '.')
				num = 38;
			else if (msg[i] == '!')
				num = 39;
			else
				num = 999;
		}


		if (num != 999)
		{
			CRcTex* textBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
			m_LogoTextBufferVec.push_back(textBuffer);
			m_LogoTextNumVec.push_back(num);
			m_LogoTextPosVec.push_back(myPoint);
			textBuffer->Set_RenderFlag();
		}

		myPoint.x -= seq;
	}
}

void CEndingBackground::Free(void)
{
	Safe_Release(m_LogoTextTexture);
	for_each(m_LogoTextBufferVec.begin(), m_LogoTextBufferVec.end(), CDeleteObj());
	__super::Free();
}
