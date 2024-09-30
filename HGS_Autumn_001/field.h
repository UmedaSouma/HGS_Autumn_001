//===========================================================================================================================================================
// 
// field.cppのヘッダー
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _FIELD_H_
#define _FIELD_H_

// include 
#include "main.h"
#include "object3D.h"

// 床のテクスチャクラスの定義
class CField : public CObject3D
{
public:
	CField(int nPriority = PRIORITY_DEFAULT);			// コンストラクタ
	~CField()override;									// デストラクタ
	HRESULT Init()override;								// 初期化処理
	void Uninit()override;								// 終了処理
	void Update()override;								// 更新処理
	void Draw()override;								// 描画処理
	static CField*Create(D3DXVECTOR3 pos);				// 生成処理
};
#endif