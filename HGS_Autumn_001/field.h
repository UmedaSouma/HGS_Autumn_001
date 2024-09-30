//===========================================================================================================================================================
// 
// field.cpp�̃w�b�_�[ [field.h]
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _FIELD_H_
#define _FIELD_H_

// include
#include "main.h"
#include "object3D.h"

// ���N���X�̒�`
class CField : public CObject3D
{
	CField();				// �R���X�g���N�^
	~CField()override;		// �f�X�g���N�^
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CField* Create(D3DXVECTOR3 pos);   // ��������

};
#endif