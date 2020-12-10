#pragma once
#include <Shade.h>
#include <core/render/Shader.h>

class MainLayer :public se::Layer
{
public:
	MainLayer(const std::string& name, const void* scene);
	~MainLayer();
	// Inherited via Layer
	virtual void OnCreate() override;
	virtual void OnInit()   override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnDelete() override;

private:
	const mutable se::Shader* shader;

};