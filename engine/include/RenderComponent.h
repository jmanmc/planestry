#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

#include <SDL.h>

namespace scx
{
	class RenderComponent
	{
	public:
		RenderComponent() {};
		~RenderComponent() {};

		void Initialize()
		{
			PlayLogo();
		};

	private:

		void PlayLogo()
		{

		}
	};
}