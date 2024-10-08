//===========================================================================================================================================================
// 
// リザルト画面の処理
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "result.h"
#include "input.h"
#include "manager.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CResult::CResult()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CResult::~CResult()
{
}

//===========================================================================================================
// 初期設定
//===========================================================================================================
HRESULT CResult::Init()
{
	CScene::Init();

	CText* pText = CRenderer::GetText();
	pText->SetText(CText::TEXT_SCORE_RESULT);

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CResult::Uninit()
{
	CText* pText = CRenderer::GetText();
	pText->UnSetText(CText::TEXT_SCORE_RESULT);

	CScene::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CResult::Update()
{
	CScene::Update();

	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();

	if (keyboard->GetTrigger(DIK_RETURN) || joypad->GetTrigger(CInputJoypad::JOYKEY_START))
	{
		CFade* pFade = CManager::GetFade();

		pFade->SetFade(CScene::MODE_TITLE);
	}
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CResult::Draw()
{
	CScene::Draw();
}