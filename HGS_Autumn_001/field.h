//===========================================================================================================================================================
// 
// field.cpp�̃w�b�_�[
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _FIELD_H_
#define _FIELD_H_

// include 
#include "main.h"
#include "object3D.h"

// ���̃e�N�X�`���N���X�̒�`
class CField : public CObject3D
{
public:
	CField(int nPriority = PRIORITY_DEFAULT);			// �R���X�g���N�^
	~CField()override;									// �f�X�g���N�^
	HRESULT Init()override;								// ����������
	void Uninit()override;								// �I������
	void Update()override;								// �X�V����
	void Draw()override;								// �`�揈��
	static CField*Create(D3DXVECTOR3 pos);				// ��������
};
#endif