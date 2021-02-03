#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/ShadeException.h"
#include <SDL2/SDL.h>
#include "Vendors/glad/glad.h"
#undef main // For SDL

namespace se
{
	enum class RenderAPI
	{
	    OpenGL = 1,
		Vulkan = 2
	};

	class SE_API System
	{
	public:
		static void InitVideo(const se::RenderAPI& api, const int& major = 4, const int& minor = 5);
		static void InitAudio();
		static const bool& IsVideoInit();
		static const bool& IsAudioInit();
	private:
		System();
		~System();
		System(const System&) = delete;
		System& operator= (const System&) = delete;
		System(const System&&) = delete;
		System& operator= (const System&&) = delete;
		static System& Get();

		bool m_isVideoInitialized;
		bool m_isAudioInitialized;
	};
}

