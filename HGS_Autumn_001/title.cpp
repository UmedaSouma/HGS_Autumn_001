//===========================================================================================================================================================
// 
// ƒ^ƒCƒgƒ‹‚Ìˆ—
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player3D.h"
#include "field.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	CScene::Init();

	CPlayer3D::Create({ 0.0f,0.0f,0.0f });

	CField::Create({ 0.0f,-21.0f,0.0f });

	CText* pText = CRenderer::GetText();
	pText->SetText(CText::TEXT_SCORE);

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