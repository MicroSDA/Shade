#include "stdafx.h"
#include "FileDialog.h"

#include <commdlg.h>

#include <winnt.h>
#include <minwinbase.h>
#include <vendors/SDL2/SDL.h>
#include <vendors/SDL2/SDL_syswm.h>

#include "Shade/Core/Engine/WindowManager.h"

std::string se::FileDialog::OpenFile(const char* filter)
{

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(se::WindowManager::GetWindow().Handler , &wmInfo);
	HWND hwnd = wmInfo.info.win.window;


	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	CHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = wmInfo.info.win.window;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	if (GetCurrentDirectoryA(256, currentDir))
		ofn.lpstrInitialDir = currentDir;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	std::string path;
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		path = ofn.lpstrFile;
		std::replace(path.begin(), path.end(), '\\', '/');
	}

	return path;
}
