//===========================================================================================================================================================
// 
// obstacle.cpp�̃w�b�_�[
// Author : Kasai Keisuke
// 
//===========================================================================================================================================================

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

// include
#include "main.h"
#include "model.h"

// ��Q���N���X�̒�`
class CObstacle : public CModel
{
public:
	// ��Q���̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_DEATHZERO,		// �����@
		TYPE_DEATHONE,		// �����A
		TYPE_DEATHTWO,		// �����B
		TYPE_STACK,			// �X�^�b�N����(�G�Ƃ̋������߂��Ȃ�)
		TYPE_MAX,
	}OBSTACLETYPE;
	CObstacle(int nPriority = PRIORITY_DEFAULT);					// �R���X�g���N�^
	~CObstacle()override;											// �f�X�g���N�^
	HRESULT Init()override;											// ����������
	void Uninit()override;											// �I������
	void Update()override;											// �X�V����
	void Draw()override;											// �`�揈��
	static CObstacle* Create(D3DXVECTOR3 pos, OBSTACLETYPE nType);	// ��������
	bool Collision();												// �����蔻��


	static inline const float MAX_SIZE = 5.0f;						// ��Q���̃T�C�Y
private:
	OBSTACLETYPE m_Type;											// ���
};
#endif