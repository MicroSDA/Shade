#pragma once
#include <Shade/Core/Engine/Layer.h>

class MainLayer :public se::Layer
{
public:
	MainLayer(const std::string& name, se::Scene* scene);
	virtual ~MainLayer();
	// ������������ ����� Layer
	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnRenderBegin() override;
	virtual void OnRender() override;
	virtual void OnRenderEnd() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnDelete() override;
	virtual void OnEvent(const se::Event& event) override;
private:
	//se::ShadeShared<se::FrameBuffer>	m_FrameBuffer;
	se::AssetPointer<se::Shader>		m_BasicModelShader;
	se::AssetPointer<se::Shader>		m_GridShader;
	se::AssetPointer<se::Shader>		m_TextShader;
};