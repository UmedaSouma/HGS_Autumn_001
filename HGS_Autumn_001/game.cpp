//===========================================================================================================================================================
// 
// �Q�[���̏���
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "model.h"
#include "search.h"
#include "player3D.h"
#include "block3D.h"
#include "item.h"
#include "field.h"
#include "obstacle.h"
#include "score.h"

#include <random>

int CGame::m_nDelayEnd = 0; // �|���Ă��烊�U���g�ɂȂ�܂�
bool CGame::m_Delay = false;
int CGame::m_nCnt = 2;// ������

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CGame::CGame()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CGame::~CGame()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CGame::Init()
{
	CScene::Init();

	CText* pText = CRenderer::GetText();
	pText->SetText(CText::TEXT_SCORE);

	CScore::ResetScore();

	CPlayer3D::Create({ 0.0f,0.0f,0.0f });

	CField::Create(D3DXVECTOR3(40.0f, -9.0f, 10000.0f));

	std::random_device rnd;                // �񌈒�I�ȗ���������ŃV�[�h�����@�𐶐�
	std::mt19937 mt(rnd());                //  �����Z���k�c�C�X�^�[��32�r�b�g�ŁA�����͏����V�[�h
	std::uniform_int_distribution<> rand(1, 3);     // �J�n�̐��l����I���̐��l�� �͈͂̈�l����

	m_nCnt = 3;
	
	for (int nCnt = 0; nCnt < 100; nCnt++)
	{
		m_nRandNum[nCnt] = rand(mt);

		switch (m_nRandNum[nCnt])
		{
		case 1:
			CObstacle::Create(D3DXVECTOR3(10.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHZERO);
			CObstacle::Create(D3DXVECTOR3(40.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHONE);
			CItem::Create(D3DXVECTOR3(70.0f, -9.0f, 100.0f));
			break;
		case 2:
			CObstacle::Create(D3DXVECTOR3(40.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHONE);
			CObstacle::Create(D3DXVECTOR3(70.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHONE);
			CItem::Create(D3DXVECTOR3(10.0f, -9.0f, 100.0f));
			break;
		case 3:
			CObstacle::Create(D3DXVECTOR3(70.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHTWO);
			CObstacle::Create(D3DXVECTOR3(10.0f, -9.0f, 100.0f), CObstacle::OBSTACLETYPE::TYPE_DEATHTWO);
			CItem::Create(D3DXVECTOR3(40.0f, -9.0f, 100.0f));
			break;
		}
	}


	//for (int Vertical = 0; Vertical < 5; Vertical++)
	//{
	//	for (int Horizon = 0; Horizon < 1000; Horizon++)
	//	{
	//		CBlock3D::Create({ 0.0f + (Vertical * 20.0f),-30.0f,0.0f + (Horizon * 20.0f) });
	//	}
	//}

	//CItem::Create({ 30.0f,0.0f,0.0f });

	return S_OK;
}

//===========================================================================================================
// ����UI�̃Z�b�g
//===========================================================================================================
void CGame::SetInitUI()
{
	//CUI::Create(
	//	{ SCREEN_WIDTH * 0.4f,SCREEN_HEIGHT * 0.78f,0.0f }
	//	, { 50.0f,50.0f,0 }
	//	, -1
	//	, "data\\TEXTURE\\ui_key_square_1_000.png"
	//);
	//CUI::Create(
	//	{ SCREEN_WIDTH * 0.6f,SCREEN_HEIGHT * 0.78f,0.0f }
	//	, { 50.0f,50.0f,0 }
	//	, -1
	//	, "data\\TEXTURE\\ui_key_square_2_000.png"
	//);
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CGame::Uninit()
{
	CText* pText = CRenderer::GetText();
	pText->UnSetText(CText::TEXT_SCORE);

	CScene::Uninit();
}

void CGame::UpdateDelay()
{
	
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CGame::Update()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CFade* pFade = CManager::GetFade();

#ifdef _DEBUG
	

	// �f�o�b�O�p�E���ŃV�[���؂�ւ�
	if (keyboard->GetTrigger(DIK_RIGHTARROW))
	{
		pFade->SetFade(CScene::MODE_TITLE);

		//CManager::SetMode(CScene::MODE_GAME);
	}

	if (keyboard->GetTrigger(DIK_F2))
	{
		pFade->SetFade(CScene::MODE_EDITOR);
	}

#endif // _DEBUG

	CScene::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CGame::Draw()
{
	CScene::Draw();
}