#pragma once
#include <Shade/Shade.h>
#include "MainScene.h"

class ShadeEditor : public se::Application
{
public:
	ShadeEditor();
	~ShadeEditor();
private:
	// ������������ ����� Application
	virtual void OnInit() override;
	virtual void OnUpdate() override;
};

