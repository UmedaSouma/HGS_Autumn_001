//==============================================================================================================================================
// 
// カメラ操作・管理
// Author umeda souma
// 
//==============================================================================================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"

//======================================================================================================
// コンストラクタ
//======================================================================================================
CCamera::CCamera() :
	m_posV{ 0.0f,0.0f,0.0f }				// 視点(カメラ位置)
	, m_posR{ 0.0f,0.0f,0.0f }			// 注視点(カメラの見ている先)
	, m_rot{ 0.0f,0.0f,0.0f }			// 向き
	, m_vecU{ 0.0f,0.0f,0.0f }			// vectorUP 
	, m_targetpos{ 0.0f,0.0f,0.0f }		// ターゲット
	, m_fDis(0)							// 視点と注視点の距離
	, nCntFollow(0)						// カメラの追いつく間隔
	, m_fStrength(0.0f)
	, m_nFrame(0)
	, m_mtxProjection{}
	, m_mtxView{}
{
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CCamera::~CCamera()
{
}

//======================================================================================================
// 初期設定
//======================================================================================================
HRESULT CCamera::Init()
{
	if (CScene::GetMode() == CScene::MODE_TITLE)
	{
		m_fDis = 0.0f;
	}
	else
	{
		m_fDis = 200.0f;
	}
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -0.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	m_follow = 0.08f;

	return S_OK;
}

//======================================================================================================
// 終了処理
//======================================================================================================
void CCamera::Uninit()
{

}

//======================================================================================================
// 更新処理
//======================================================================================================
void CCamera::Update()
{
	if (CScene::GetMode() == CScene::MODE_TITLE)
	{
		m_posV =
		{
			sinf(m_rot.x) * sinf(m_rot.y) * m_fDis,
			/*cosf(m_rot.x) * m_fDis,*/100.0f,
			sinf(m_rot.x) * cosf(m_rot.y) * m_fDis
		};
	}
	else
	{
		m_posV =
		{
			sinf(m_rot.x) * sinf(m_rot.y) * m_fDis,
			/*cosf(m_rot.x) * m_fDis,*/50.0f,
			sinf(m_rot.x) * cosf(m_rot.y) * m_fDis
		};
	}
	//m_posV =
	//{
	//	sinf(m_rot.x) * sinf(m_rot.y) * m_fDis,
	//	/*cosf(m_rot.x) * m_fDis,*/50.0f,
	//	sinf(m_rot.x) * cosf(m_rot.y) * m_fDis
	//};

	m_posV += m_posR;

	m_posR.x += (m_targetpos.x - m_posR.x) * m_follow*2.0f;
	m_posR.y += (m_targetpos.y - m_posR.y) * m_follow*0.5f;
	m_posR.z += (m_targetpos.z - m_posR.z) * m_follow;


	// カメラが一周すると角度をリセットする
	if (m_rot.y >= D3DX_PI * 2 || m_rot.y <= -D3DX_PI * 2)
	{
		m_rot.y = 0;
	}
	
}

//======================================================================================================
// 描画処理
//======================================================================================================
void CCamera::Draw()
{

}

//======================================================================================================
// カメラの設定
//======================================================================================================
void CCamera::SetCamera()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//// プロジェクションマトリックスを作成(平衡投影)
	//D3DXMatrixOrthoLH(
	//	&m_mtxProjection,
	//	(float)SCREEN_WIDTH*0.1f,
	//	(float)SCREEN_HEIGHT * 0.1f,
	//	10.0f,
	//	1000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };

	if (m_nFrame > 0)
	{// 揺れが続いている間

		m_nFrame--;	// 揺れの時間を減らしていく

		//揺れの数値をランダムで生成
		adjust = {
			(float)(rand() % (int)m_fStrength - 1),
			(float)(rand() % (int)m_fStrength - 1),
			0.0f
		};
	}
	// 揺れた値をposと合わせて一時保存
	D3DXVECTOR3 posv = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posv,
		&posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//======================================================================================================
// カメラ位置の設定
//======================================================================================================
void CCamera::SetTargetPos(D3DXVECTOR3 pos)
{
	m_targetpos = pos;
}

//======================================================================================================
// カメラ揺れ
//======================================================================================================
void CCamera::SetShake(int frame, float strength)
{
	m_nFrame = frame;
	m_fStrength = strength;
}