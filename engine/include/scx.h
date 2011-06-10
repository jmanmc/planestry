#pragma once

#include <EngineSingleton.h>
#include <WindowHandle.h>
#include <math.h>
#include <SceneGraph.h>
#include <restclient/restclient.h>
#include <gui.h>
#include <widgets.h>

namespace scx
{

	class Mesh : public Drawable
	{

	public:
		Mesh(std::string name) :  Drawable(name) {};
		~Mesh() {};

		virtual void Draw()
		{
		}

	private:
	
	};

	static float points[ 45 ][ 45 ][3];    // The array for the points on the grid of our "wave"

	static GLfloat    xrot = 0;            // X Rotation
	static GLfloat    yrot = 0;            // Y Rotation
	static GLfloat    zrot = 0;            // Z Rotation

	static GLuint    texture[1];        // Storage for 1 texture

	static bool DrawGrid;

	static SDL_Surface *LoadBMP(char *filename)
	{
		Uint8 *rowhi, *rowlo;
		Uint8 *tmpbuf, tmpch;
		SDL_Surface *image;
		int i, j;

		image = SDL_LoadBMP(filename);
		if ( image == NULL ) {
			fprintf(stderr, "Unable to load %s: %s\n", filename, SDL_GetError());
			return(NULL);
		}

		/* GL surfaces are upsidedown and RGB, not BGR :-) */
		tmpbuf = (Uint8 *)malloc(image->pitch);
		if ( tmpbuf == NULL ) {
			fprintf(stderr, "Out of memory\n");
			return(NULL);
		}
		rowhi = (Uint8 *)image->pixels;
		rowlo = rowhi + (image->h * image->pitch) - image->pitch;
		for ( i=0; i<image->h/2; ++i ) {
			for ( j=0; j<image->w; ++j ) {
				tmpch = rowhi[j*3];
				rowhi[j*3] = rowhi[j*3+2];
				rowhi[j*3+2] = tmpch;
				tmpch = rowlo[j*3];
				rowlo[j*3] = rowlo[j*3+2];
				rowlo[j*3+2] = tmpch;
			}
			memcpy(tmpbuf, rowhi, image->pitch);
			memcpy(rowhi, rowlo, image->pitch);
			memcpy(rowlo, tmpbuf, image->pitch);
			rowhi += image->pitch;
			rowlo -= image->pitch;
		}
		free(tmpbuf);
		return(image);
	}

	static void LoadGLTextures(void)
	{	
		// Load Texture
		SDL_Surface *texture1;

		texture1 = LoadBMP("tim.bmp");
		if (!texture1) {
			SDL_Quit();
			exit(1);
		}

		// Create Texture	
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->w, texture1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->pixels);
	};

	/* A general OpenGL initialization function.  Sets all of the initial parameters. */
	static void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
	{
		float float_x, float_y;

		glViewport(0, 0, Width, Height);
		LoadGLTextures();                            // Load The Texture(s)
		glEnable(GL_TEXTURE_2D);                    // Enable Texture Mapping

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);        // This Will Clear The Background Color To Black
		glClearDepth(1.0);                            // Enables Clearing Of The Depth Buffer
		glDepthFunc(GL_LESS);                        // The Type Of Depth Test To Do
		glEnable(GL_DEPTH_TEST);                    // Enables Depth Testing
		glShadeModel(GL_SMOOTH);                    // Enables Smooth Color Shading

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();                            // Reset The Projection Matrix

		gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);    // Calculate The Aspect Ratio Of The Window

		glMatrixMode(GL_MODELVIEW);

		DrawGrid = true;
		for( float_x = 0.0f; float_x < 9.0f; float_x +=  0.04f )
		{
			for( float_y = 0.0f; float_y < 9.0f; float_y += 0.04f)
			{
				points[ (int)(float_x*5) ][ (int)(float_y*5) ][0] = float_x - 4.4f;
				points[ (int)(float_x*5) ][ (int)(float_y*5) ][1] = float_y - 4.4f;
				points[ (int)(float_x*5) ][ (int)(float_y*5) ][2] = 0;
			}
		}
	}
	
	static void InitializeSDL()
	{
		/* Initialize SDL for video output */
		if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{
			fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
			exit(1);
		}

		/* Create a 640x480 OpenGL screen */
		if (SDL_SetVideoMode(scx::Engine.GetWindow().GetWidth(), scx::Engine.GetWindow().GetHeight(), 0, SDL_OPENGL) == NULL) 
		{
			fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
			SDL_Quit();
			exit(2);
		}

		/* Set the title bar in environments that support it */
		SDL_WM_SetCaption(scx::Engine.GetWindow().GetTitle().c_str(), NULL);

		/* Loop, drawing and checking events */
		InitGL(scx::Engine.GetWindow().GetWidth(), scx::Engine.GetWindow().GetHeight());
	};

	static void Initialize()
	{
		Engine.Initialize();
		InitializeSDL();

		Drawable RootObjectNode("root node");
		Drawable RootGuiNode("root node");

		SceneGraph<Drawable> ObjectGraph(&RootObjectNode);
		SceneGraph<Drawable> GuiGraph(&RootGuiNode);

		Mesh sky("sky sphere");
		ObjectGraph.Add(&sky);

		Mesh cube("cube");
		ObjectGraph.Add(&cube);


		gui::Canvas MainMenu;

		gui::Button Button1("button1", &MainMenu);
		GuiGraph.Add(&Button1);

		gui::Button Button2("button2", &MainMenu);
		GuiGraph.Add(&Button2);

		gui::Button Button3("button3", &MainMenu);
		GuiGraph.Add(&Button3);

		ObjectGraph.DrawNodes();
		GuiGraph.DrawNodes();
	};
}