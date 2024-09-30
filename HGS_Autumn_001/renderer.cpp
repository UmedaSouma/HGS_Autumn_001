#include "renderer.h"
#include "object.h"
#include "scene.h"
#include "manager.h"
#include "search.h"

// �ÓI�����o�ϐ��̏�����
CText* CRenderer::m_pText = nullptr;

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pFont = nullptr;
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CRenderer::~CRenderer()
{

}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;	// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	m_pText = new CText;
	m_pText->Init();

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʂ̃T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// 
	d3dpp.BackBufferCount = 1;									// 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 
	d3dpp.EnableAutoDepthStencil = TRUE;						// 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// 
	d3dpp.Windowed = bWindow;									// 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// 

	// 
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// 
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CRenderer::Uninit()
{
	// 
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// 
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	if (m_pText != nullptr)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = nullptr;
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CRenderer::Update()
{
	// �S�čX�V
	CObject::UpdateAll();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CRenderer::Draw()
{
	// �w�i�Ȃǂ̐ݒ�
	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(100, 178, 255, 0), 1.0f, 0);
	}
	else
	{
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	}

	

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		char aStr[256] = {};
		char aEnemyStr[256] = {};

		CManager::GetCamera()->SetCamera();

		// �S�ĕ`��
		CObject::DrawAll();

		m_pText->DrawAll();

		// �f�o�b�O�e�L�X�g
		DebugPrint(aStr[0],aEnemyStr[0]);

		// 
		m_pD3DDevice->EndScene();

		// �e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		m_pFont->DrawText(NULL, &aEnemyStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//===========================================================================================================
// �f�o�b�O�e�L�X�g�̕`��
//===========================================================================================================
void CRenderer::DebugPrint(char& pStr, char& pStr2)
{

}

//===========================================================================================================
// �f�o�C�X�̎擾
//===========================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}