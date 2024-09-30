//===========================================================================================================================================================
// 
// ���f���̊Ǘ�
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "model.h"
#include "manager.h"

//===================================================================================
// �R���X�g���N�^
//===================================================================================
CModel::CModel(int nPriority) :CObject3D(nPriority)
, m_Direction(0)
, m_nIdx(-1)
, m_bMat(false)
, m_Diffuse{}
, m_pModelAddress{}
, m_apTexture{}
{
	m_ModelInfo = {};
}

//===================================================================================
// �f�X�g���N�^
//===================================================================================
CModel::~CModel()
{
}

//===================================================================================
// �����ݒ�
//===================================================================================
HRESULT CModel::Init()
{
	UpdateMatrix();

	return S_OK;
}

//===================================================================================
// �I������
//===================================================================================
void CModel::Uninit()
{
	Release();
}

//===================================================================================
// �X�V����
//===================================================================================
void CModel::Update()
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update();	// �����Ń}�g���b�N�X�̐ݒ�����Ă���

	FixRot();
}

//===================================================================================
// �`�揈��
//===================================================================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				// �}�e���A���f�[�^�̃|�C���^

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMatrix());

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_ModelInfo.BuffMat != nullptr
		&& m_ModelInfo.Mesh != nullptr
		&& m_ModelInfo.NumMat != 0)
	{
		// �}�e���A���f�[�^�̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_ModelInfo.BuffMat->GetBufferPointer();
		CModeldata* pModeldata = CManager::GetModeldata();	// Modeldata �̃|�C���^�������Ă���

		if (pModeldata)
		{
			for (int nCntMat = 0; nCntMat < (int)m_ModelInfo.NumMat; nCntMat++)
			{
				if (m_bMat)
				{// �_���[�W���󂯂��Ƃ�
					pMat[nCntMat].MatD3D.Diffuse = { 1.0f,0.0f,0.0f,0.5f };	// �Ԃ�����
				}
				else
				{// ���̂ق��̏�Ԃ̎�

					//if (CScene::GetMode() != CScene::MODE_EDITOR)
					{
						pMat[nCntMat].MatD3D.Diffuse = *pModeldata->GetMatData(m_pModelAddress, nCntMat);	// �ʏ�F�ɂ���
					}

				}

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, nullptr);

				// ���f���p�[�c�̕`��
				m_ModelInfo.Mesh->DrawSubset(nCntMat);
			}
		}
	
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// �p�x���C������
//===========================================================================================================
void CModel::FixRot()
{
	if (GetRot().x >= D3DX_PI*2 ||  GetRot().x <= -D3DX_PI*2)
	{
		SetRot({ 0.0f,GetRot().y,GetRot().z });
	}
	if (GetRot().y >= D3DX_PI * 2 || GetRot().y <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,0.0f,GetRot().z });
	}
	if (GetRot().z >= D3DX_PI * 2 ||  GetRot().z <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,GetRot().y,0.0f });
	}
}

//===================================================================================
// ��������
//===================================================================================
CModel* CModel::Create(D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel;

	pModel->SetPos(pos);
	pModel->SetType(TYPE::MODEL);

	pModel->Init();

	return pModel;
}

//===================================================================================
// ���f���̏����Z�b�g����
//===================================================================================
void CModel::BindModel(CModeldata::ModelData *modelinfo)
{
	m_ModelInfo.Mesh = modelinfo->Mesh;
	m_ModelInfo.BuffMat = modelinfo->BuffMat;
	m_ModelInfo.NumMat = modelinfo->NumMat;
}

//===========================================================================================================
// ������ݒ�
//===========================================================================================================
void CModel::SetDirection(DIRECTION dire)
{
	switch (dire)
	{
	case DIRECTION_LEFT:
		m_Direction = -1;
		SetRot({
			0.0f
			,D3DX_PI * 0.5f
			,0.0f
			});
		break;

	case DIRECTION_RIGHT:
		m_Direction = 1;
		SetRot({
			0.0f
			,D3DX_PI * -0.5f
			,0.0f
			});
		break;

	default:
		break;
	}
}

//===========================================================================================================
// �������擾
//===========================================================================================================
int CModel::GetDirection()
{
	return m_Direction;
}

//===========================================================================================================
// ���f���̌����ڐݒ�
//===========================================================================================================
void CModel::SetModel(const char* address)
{
	CModeldata* pModeldata = nullptr;
	int nIdx = 0;

	SetModelAddress(address);		// �A�h���X��ۑ����Ă���
	pModeldata = CManager::GetModeldata();
	nIdx = pModeldata->Regist(address);
	BindModel(CManager::GetModeldata()->GetAddress(nIdx));
}