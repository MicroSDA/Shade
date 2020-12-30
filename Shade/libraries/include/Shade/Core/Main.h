#pragma once
#include "Shade/Core/Engine/Application.h"

extern se::Application* se::CreateApplication();

int main()
{
	auto app = se::CreateApplication();

	try
	{
		app->OnInit();
		app->Start();
	}
	catch (se::ShadeException& exception)
	{
		switch (exception.code())
		{
		case se::SECode::Warning:
		{
			se::Log::Print((std::string("Exception: ") + exception.what()).c_str(), se::SLCode::Warning);
			break;
		}
		case se::SECode::Error:
		{
			se::Log::Print((std::string("Exception: ") + exception.what()).c_str(), se::SLCode::Error);
			exit((int)se::SECode::Error);
			break;
		}
		default:
			break;
		}
	}
	
	delete app;
	return EXIT_SUCCESS;
}