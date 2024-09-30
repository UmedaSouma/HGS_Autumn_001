#pragma once
//===========================================================================================================================================================
// 
// tutorial.cpp�̃w�b�_�[ [tutorial.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "scene.h"

class CTutorial :public CScene
{
public:
	CTutorial();
	~CTutorial()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};


#endif // !TUTORIAL_H_
