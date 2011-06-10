#pragma once
#include <string>
#include <RenderComponent.h>

namespace scx
{
	class WindowHandle
	{
		public:
			WindowHandle(int width, int height, std::string title) : Width(width), Height(height), Title(title) 
			{
				Paused = false;
			};
			
			WindowHandle() 
			{
				Title = "";
				Width = 0;
				Height = 0;
				
				Paused = false;
			};
			
			void Initialize(int width, int height, std::string title)
			{
				Title = title;
				Width = width;
				Height = height;

				Renderer.Initialize();


			};
			
			virtual ~WindowHandle() {};
		
			std::string GetTitle() { return Title; };
			
			int GetWidth() { return Width; };
			int GetHeight() { return Height; };
			
			bool IsPaused() { return Paused; };
			
			void SetPaused(bool IsPaused) { Paused = IsPaused; };
		private:
		
			std::string Title;
			
			int Width;
			int Height;
			
			bool Paused;

			RenderComponent Renderer;
	};
}