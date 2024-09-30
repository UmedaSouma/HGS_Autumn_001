//===========================================================================================================================================================
// 
// field.cppのヘッダー [field.h]
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _FIELD_H_
#define _FIELD_H_

// include
#include "main.h"
#include "object3D.h"

// 床クラスの定義
class CField : public CObject3D
{
	CField();				// コンストラクタ
	~CField()override;		// デストラクタ
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CField* Create(D3DXVECTOR3 pos);   // 生成処理

};
#endif