//===========================================================================================================================================================
// 
// アイテムの処理 [item.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "item.h"
#include "search.h"
#include "player3D.h"
#include "manager.h"
#include "score.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CItem::CItem()
{

}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CItem::~CItem()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CItem::Init()
{
	SetSize({ 5.0f,10.0f,10.0f });

	// モデルの設定
	SetModelAddress("data\\model\\item.x");		// アドレスを保存しておく
	CModeldata* pModeldata = CManager::GetModeldata();	// modeldata のポインタを持ってくる
	int nIdx = pModeldata->Regist(GetModelAddress());	// モデルデータの登録
	BindModel(pModeldata->GetAddress(nIdx));			// モデル情報をセットする
	SetModelIdx(nIdx);

	CModel::Init();

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CItem::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CItem::Update()
{
	CModel::Update();

	if (Collision())
	{
		Uninit();
		CScore::SetScore(10000);
	}
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CItem::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CItem* CItem::Create(D3DXVECTOR3 pos)
{
	CItem* pItem = new CItem;

	pItem->SetPos(pos);
	pItem->Init();

	return pItem;
}

//===========================================================================================================
// 当たり判定
//===========================================================================================================
bool CItem::Collision()
{
	// プレイヤーを探す
	CPlayer3D* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, PLAYER);

	// アイテムの情報を持ってくる
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// プレイヤーの情報を持ってくる
	D3DXVECTOR3 pos_P = pPlayer->GetPos();
	D3DXVECTOR3 size_P = pPlayer->GetSize();

	//        アイテム     と     プレイヤー    の位置が重なったとき
	if (   pos.x - size.x <= pos_P.x + size_P.x
		&& pos.x + size.x >= pos_P.x - size_P.x
		&& pos.y - size.y <= pos_P.y + size_P.y
		&& pos.y + size.y >= pos_P.y - size_P.y
		&& pos.z - size.z <= pos_P.z + size_P.z
		&& pos.z + size.z >= pos_P.z - size_P.z
		)
	{
		return true;
	}

	return false;
}