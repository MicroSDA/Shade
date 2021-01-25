#include "stdafx.h"
#include "System.h"

se::System::System() :
	m_isVideoInitialized(false), m_isAudioInitialized(false)
{
}

se::System::~System()
{
}

void se::System::InitVideo(const se::RenderAPI& api, const int& major, const int& minor)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw se::ShadeException((std::string("Video initializing failed!") + SDL_GetError()).c_str(), se::SECode::Error);

	switch (api)
	{
	case se::RenderAPI::OpenGL:
	{
		//Set Opengl Version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		////////////////////////////////////////////////////
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		Get().m_isVideoInitialized = true;

		break;
	}
	default:
		throw se::ShadeException("Undefined render api !", se::SECode::Error);
		break;
	}
}

void se::System::InitAudio()
{
	// TODO 
	if(SDL_Init(SDL_INIT_AUDIO) != 0);
		throw se::ShadeException((std::string("Audio initializing failed!") + SDL_GetError()).c_str(), se::SECode::Error);

		/*SDL_AudioSpec wavSpec;
		Uint32 wavLength;
		Uint8* wavBuffer;

		SDL_LoadWAV("Test.wav", &wavSpec, &wavBuffer, &wavLength);
		SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
		int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceId, 0);
		SDL_Delay(300000);
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
		SDL_Quit();*/
}

const bool& se::System::IsVideoInit()
{
	return Get().m_isVideoInitialized;
}

const bool& se::System::IsAudioInit()
{
	return Get().m_isAudioInitialized;
}

se::System& se::System::Get()
{
	static System _Instatnce;
	return _Instatnce;
}
