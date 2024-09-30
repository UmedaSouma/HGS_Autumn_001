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
// �R���X�g���N�^
//========================================================================================================================
CObstacle::CObstacle(int nPriority)
{
	m_Type = TYPE_NONE;
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CObstacle::~CObstacle()
{
	m_Type = TYPE_NONE;
}

//========================================================================================================================
// ����������
//========================================================================================================================
HRESULT CObstacle::Init()
{
	CModel::Init();

	switch (m_Type)
	{
	case OBSTACLETYPE::TYPE_DEATHZERO:
		SetModelAddress("data\\model\\BlockRun001.x");		// �A�h���X��ۑ����Ă���
		SetSize({ MAX_SIZE + 5.0f ,MAX_SIZE ,MAX_SIZE });

		break;
	case OBSTACLETYPE::TYPE_DEATHONE:
		SetModelAddress("data\\model\\BlockRun001.x");		// �A�h���X��ۑ����Ă���
		SetSize({ MAX_SIZE + 5.0f ,MAX_SIZE ,MAX_SIZE });

		break;
	case OBSTACLETYPE::TYPE_STACK:
		SetModelAddress("data\\model\\hurdle001.x");		// �A�h���X��ۑ����Ă���
		SetSize({ MAX_SIZE + 0.1f ,MAX_SIZE ,MAX_SIZE });

		break;
	}

	CModeldata* pModeldata = CManager::GetModeldata();		// modeldata �̃|�C���^�������Ă���
	int nIdx = pModeldata->Regist(GetModelAddress());		// ���f���f�[�^�̓o�^
	BindModel(pModeldata->GetAddress(nIdx));				// ���f�������Z�b�g����


	SetType(TYPE::OBSTACLE);

	return S_OK;

}

//========================================================================================================================
// �I������
//========================================================================================================================
void CObstacle::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CObstacle::Update()
{
	CModel::Update();

	Collision();

}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CObstacle::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// ��������
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
// �����蔻��
//========================================================================================================================
bool CObstacle::Collision()
{
	// �v���C���[��T��
	CPlayer3D* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, PLAYER);

	// ��Q�����������Ă���
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	// �v���C���[�̏��������Ă���
	D3DXVECTOR3 pos_P = pPlayer->GetPos();
	D3DXVECTOR3 size_P = pPlayer->GetSize();
	float fCurrentLife = pPlayer->GetLife();

	switch (m_Type)
	{
	case TYPE_DEATHZERO:
		//        ��Q��     ��     �v���C���[    �̈ʒu���d�Ȃ����Ƃ�
		if (pos.x - size.x <= pos_P.x + size_P.x
			&& pos.x + size.x >= pos_P.x - size_P.x
			&& pos.y - size.y <= pos_P.y + size_P.y
			&& pos.y + size.y >= pos_P.y - size_P.y
			&& pos.z - size.z <= pos_P.z + size_P.z
			&& pos.z + size.z >= pos_P.z - size_P.z
			)
		{
			pPlayer->SetLife(0);	// �v���C���[�̃��C�t���Ȃ���

			return true;
		}

		break;
	case TYPE_DEATHONE:
		//        ��Q��     ��     �v���C���[    �̈ʒu���d�Ȃ����Ƃ�
		if (pos.x - size.x <= pos_P.x + size_P.x
			&& pos.x + size.x >= pos_P.x - size_P.x
			&& pos.y - size.y <= pos_P.y + size_P.y
			&& pos.y + size.y >= pos_P.y - size_P.y
			&& pos.z - size.z <= pos_P.z + size_P.z
			&& pos.z + size.z >= pos_P.z - size_P.z
			)
		{
			pPlayer->SetLife(0);	// �v���C���[�̃��C�t���Ȃ���

			return true;
		}

		break;
	case TYPE_STACK:
		//        ��Q��     ��     �v���C���[    �̈ʒu���d�Ȃ����Ƃ�
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
