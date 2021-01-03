#pragma once
#include "Shade/Core/Engine/Application.h"

extern se::Application* se::CreateApplication();

int main()
{
	se::Application* _pApp = nullptr;

	try
	{
		_pApp = se::CreateApplication();
		_pApp->OnInit();
		_pApp->Start();
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

	if(_pApp)
		delete _pApp;
	
	return EXIT_SUCCESS;
}