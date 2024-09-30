//===========================================================================================================================================================
// 
// ƒ^ƒCƒgƒ‹‚Ìˆ—
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player3D.h"
#include "field.h"
#include "titleBG.h"

CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}

HRESULT CTutorial::Init()
{
	CScene::Init();

	CTitleBG::Create();

	CText* pText = CRenderer::GetText();
	pText->SetText(CText::TEXT_SCORE);

	return S_OK;
}

void CTutorial::Uninit()
{
	CScene::Uninit();
}

void CTutorial::Update()
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

void CTutorial::Draw()
{
	CScene::Draw();
}