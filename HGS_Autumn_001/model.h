//===========================================================================================================================================================
// 
// model.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "object3D.h"
#include "modeldata.h"

class CModel :public CObject3D
{
private:
	CModeldata::ModelData m_ModelInfo;
public:
	// �����Ă������
	typedef enum
	{
		DIRECTION_NONE = 0,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	}DIRECTION;

	CModel(int nPriority = PRIORITY_DEFAULT);
	~CModel();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindModel(CModeldata::ModelData* modelinfo);	// ���f���̐ݒ�
	void SetDirection(DIRECTION dire);	// �����̐ݒ�
	int GetDirection();					// �����̎擾

	void SetMat(D3DCOLORVALUE mat);
	void bMat(bool bmat) { m_bMat = bmat; }
	void SetDefaultMat(D3DCOLORVALUE mat, int nummat);
	void FixRot();	// �p�x���C������

	static CModel* Create(D3DXVECTOR3 pos);

	void SetModel(const char* address);
	void SetModelIdx(int nIdx) { m_nIdx = nIdx; }	// ���f���̔ԍ���ۑ�����
	int GetModelIdx() { return m_nIdx; }	// ���f���ԍ����擾����
	void SetModelAddress(const char* Address) { m_pModelAddress = Address; }
	const char* GetModelAddress() { return m_pModelAddress; }
private:
	int m_nIdx;
	int m_Direction;
	LPDIRECT3DTEXTURE9 m_apTexture[16] = {};
	D3DCOLORVALUE m_Diffuse[64];
	bool m_bMat;	// �_���[�W��Ԃ̃}�e���A���ύX
	const char* m_pModelAddress;	// ���f���f�[�^�̃A�h���X
	
};

#endif // !_MODEL_H_
