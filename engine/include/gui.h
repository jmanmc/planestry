#pragma once
#include <Drawable.h>

namespace gui
{
	class Image
	{
		public:
			Image() {};
			~Image() {};
			
			std::string filename;
			unsigned char* pixels;
	};

	class Canvas;
	class BaseWidget : public scx::Drawable
	{
		public:
			BaseWidget(std::string Type, std::string Name, Canvas* ParentCanvas = NULL) 
				: TypeName(Type),
	   			  CanvasName(Name), 
				  canvas(ParentCanvas),
				  Drawable(Name)
				  {
						Active = true;
						Hidden = false;
						Dynamic = false;
				  };
				  
			virtual ~BaseWidget() {};
			
			std::string TypeName;
			std::string CanvasName;
			
			bool Active;
			bool Hidden;
			bool Dynamic;
			
			std::vector<Image> Images;
			
			Canvas *canvas;
	};

	class Canvas
	{
		public:
			Canvas() {};
			~Canvas() {};
			
			void AddWidget(BaseWidget *Widget)
			{
				std::cout << Widget->CanvasName << " added to this canvas.\n";
				Widgets.push_back(Widget);
			};

			void RemoveWidget(BaseWidget *Widget)
			{
				std::vector<BaseWidget*> NewWidgets;
				for(std::vector<BaseWidget*>::iterator i = Widgets.begin(); i != Widgets.end(); ++i)
				{
					if((*i)->CanvasName.compare(Widget->CanvasName))
						NewWidgets.push_back(*i);
				}

				Widgets = NewWidgets;

				std::cout << "New widgets: \n";

				for(std::vector<BaseWidget*>::iterator i = Widgets.begin(); i != Widgets.end(); ++i)
					std::cout << (*i)->CanvasName << std::endl;
			}
			
		private:
			std::vector<BaseWidget*> Widgets;
	};
}