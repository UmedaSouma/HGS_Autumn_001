//===========================================================================================================================================================
// 
// obstacle.cppのヘッダー
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

// include
#include "main.h"
#include "model.h"

// 障害物クラスの定義
class CObstacle : public CModel
{
public:
	// 障害物の種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_DEATHZERO,		// 即死①
		TYPE_DEATHONE,		// 即死②
		TYPE_DEATHTWO,		// 即死③
		TYPE_STACK,			// スタックする(敵との距離が近くなる)
		TYPE_MAX,
	}OBSTACLETYPE;
	CObstacle(int nPriority = PRIORITY_DEFAULT);					// コンストラクタ
	~CObstacle()override;											// デストラクタ
	HRESULT Init()override;											// 初期化処理
	void Uninit()override;											// 終了処理
	void Update()override;											// 更新処理
	void Draw()override;											// 描画処理
	static CObstacle* Create(D3DXVECTOR3 pos, OBSTACLETYPE nType);	// 生成処理
	bool Collision();												// 当たり判定


	static inline const float MAX_SIZE = 5.0f;						// 障害物のサイズ
private:
	OBSTACLETYPE m_Type;											// 種類
};
#endif