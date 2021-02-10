#pragma once
#include <Shade/Core/Engine/Scene.h>
#include "MainLayer.h"
//#include "EditorLayer.h"
#include "EditorLayerTest.h"
#include "Shade/Core/Engine/Text.h"

class MainScene : public se::Scene
{
public:
	MainScene(const std::string& name);
	~MainScene();

	// ������������ ����� Scene
	virtual void OnCreate() override;

	virtual void OnInit() override;

	virtual void OnUpdate(const se::Timer& deltaTime) override;

	virtual void OnRender() override;

	virtual void OnDelete() override;

	
private:
	
};

