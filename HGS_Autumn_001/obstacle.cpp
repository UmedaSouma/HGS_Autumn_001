//===========================================================================================================================================================
// 
// obstacle.cpp
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

// include
#include "obstacle.h"
#include "search.h"
#include "manager.h"
#include "player3D.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CObstacle::CObstacle(int nPriority)
{
	m_Type = TYPE_NONE;
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CObstacle::~CObstacle()
{
	m_Type = TYPE_NONE;
}

//========================================================================================================================
// 初期化処理
//========================================================================================================================
HRESULT CObstacle::Init()
{
	CModel::Init();

	switch (m_Type)
	{
	case OBSTACLETYPE::TYPE_DEATHZERO:
		SetModelAddress("data\\model\\BlockRun001.x");		// アドレスを保存しておく
		SetSize({ MAX_SIZE + 5.0f ,MAX_SIZE ,MAX_SIZE });

		break;
	case OBSTACLETYPE::TYPE_DEATHONE:
		SetModelAddress("data\\model\\BlockRun001.x");		// アドレスを保存しておく
		SetSize({ MAX_SIZE + 5.0f ,MAX_SIZE ,MAX_SIZE });

		break;
	case OBSTACLETYPE::TYPE_STACK:
		SetModelAddress("data\\model\\hurdle001.x");		// アドレスを保存しておく
		SetSize({ MAX_SIZE + 0.1f ,MAX_SIZE ,MAX_SIZE });

		break;
	}

	CModeldata* pModeldata = CManager::GetModeldata();		// modeldata のポインタを持ってくる
	int nIdx = pModeldata->Regist(GetModelAddress());		// モデルデータの登録
	BindModel(pModeldata->GetAddress(nIdx));				// モデル情報をセットする


	SetType(TYPE::OBSTACLE);

	return S_OK;

}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CObstacle::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CObstacle::Update()
{
	CModel::Update();

	Collision();

}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CObstacle::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CObstacle* CObstacle::Create(D3DXVECTOR3 pos, OBSTACLETYPE nType)
{
	CObstacle* pObstacle = new CObstacle;

	pObstacle->m_Type = nType;

	pObstacle->SetPos(pos);

	pObstacle->Init();

	return nullptr;
}

//========================================================================================================================
// 当たり判定
//========================================================================================================================
bool CObstacle::Collision()
{
	// プレイヤーを探す
	CPlayer3D* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, PLAYER);

	// 障害物情報を持ってくる
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	// プレイヤーの情報を持ってくる
	D3DXVECTOR3 pos_P = pPlayer->GetPos();
	D3DXVECTOR3 size_P = pPlayer->GetSize();
	float fCurrentLife = pPlayer->GetLife();

	switch (m_Type)
	{
	case TYPE_DEATHZERO:
		//        障害物     と     プレイヤー    の位置が重なったとき
		if (pos.x - size.x <= pos_P.x + size_P.x
			&& pos.x + size.x >= pos_P.x - size_P.x
			&& pos.y - size.y <= pos_P.y + size_P.y
			&& pos.y + size.y >= pos_P.y - size_P.y
			&& pos.z - size.z <= pos_P.z + size_P.z
			&& pos.z + size.z >= pos_P.z - size_P.z
			)
		{
			pPlayer->SetLife(0);	// プレイヤーのライフをなくす

			return true;
		}

		break;
	case TYPE_DEATHONE:
		//        障害物     と     プレイヤー    の位置が重なったとき
		if (pos.x - size.x <= pos_P.x + size_P.x
			&& pos.x + size.x >= pos_P.x - size_P.x
			&& pos.y - size.y <= pos_P.y + size_P.y
			&& pos.y + size.y >= pos_P.y - size_P.y
			&& pos.z - size.z <= pos_P.z + size_P.z
			&& pos.z + size.z >= pos_P.z - size_P.z
			)
		{
			pPlayer->SetLife(0);	// プレイヤーのライフをなくす

			return true;
		}

		break;
	case TYPE_STACK:
		//        障害物     と     プレイヤー    の位置が重なったとき
		if (pos.x - size.x <= pos_P.x + size_P.x
			&& pos.x + size.x >= pos_P.x - size_P.x
			&& pos.y - size.y <= pos_P.y + size_P.y
			&& pos.y + size.y >= pos_P.y - size_P.y
			&& pos.z - size.z <= pos_P.z + size_P.z
			&& pos.z + size.z >= pos_P.z - size_P.z
			)
		{
			return true;
		}
		break;
	}

	return false;
}
