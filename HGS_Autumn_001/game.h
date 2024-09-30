//===========================================================================================================================================================
// 
// game.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "main.h"
#include "scene.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetInitUI();	// ui�̃Z�b�g
	static void UpdateDelay();
	static void SetDelay() { m_Delay = true; m_nDelayEnd = 60;}
private:
	static int m_nDelayEnd;	// �|���Ă��烊�U���g�ɂȂ�܂�
	static bool m_Delay;

public:
};