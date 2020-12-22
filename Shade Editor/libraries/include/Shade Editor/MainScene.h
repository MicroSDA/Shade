#pragma once
#include <Shade/Core/Engine/Scene.h>
#include "MainLayer.h"

class MainScene : public se::Scene
{
public:
	MainScene(const std::string& name);
	~MainScene();

	// ������������ ����� Scene
	virtual void OnCreate() override;

	virtual void OnInit() override;

	virtual void OnUpdate() override;

	virtual void OnRender() override;

	virtual void OnDelete() override;

};
