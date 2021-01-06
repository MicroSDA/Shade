#pragma once
#include <Shade/Shade.h>
#include "MainScene.h"

class ShadeEditor : public se::Application
{
public:
	ShadeEditor();
	~ShadeEditor();
private:
	virtual void OnInit() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
};

