//===========================================================================================================================================================
// 
// �^�C�g���̏���
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	CScene::Init();

	CText* pText = CRenderer::GetText();
	pText->SetText(CText::TEXT_TEST);

	return S_OK;
}

void CTitle::Uninit()
{
	CScene::Uninit();
}

void CTitle::Update()
{
	CScene::Update();

	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();

	if (keyboard->GetTrigger(DIK_RETURN) || joypad->GetTrigger(CInputJoypad::JOYKEY_START))
	{
		CFade* pFade = CManager::GetFade();

		pFade->SetFade(CScene::MODE_GAME);

		//CManager::SetMode(CScene::MODE_GAME);
	}
}

void CTitle::Draw()
{
	CScene::Draw();
}