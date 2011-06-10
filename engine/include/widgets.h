#include <gui.h>

namespace gui
{
	class Panel : public gui::BaseWidget
	{
		public:
			Panel(std::string name, gui::Canvas *ParentCanvas = NULL) : gui::BaseWidget("panel", name, ParentCanvas) 
			{
				if(ParentCanvas != NULL)
					ParentCanvas->AddWidget(this);
			};

			~Panel() {canvas->RemoveWidget(this);};
	};
	
	class Button : public gui::BaseWidget
	{
		public:
			Button(std::string name, gui::Canvas *ParentCanvas = NULL) : gui::BaseWidget("button", name, ParentCanvas) 
			{
				if(ParentCanvas != NULL)
					ParentCanvas->AddWidget(this);
			};

			void Draw() { std::cout << "Drawing a button.\n"; };

			~Button() {canvas->RemoveWidget(this);};
	};
}