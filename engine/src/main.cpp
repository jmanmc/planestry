#include <stdio.h>
#include <scx.h>

void DrawScene();
int RunApp() 
{ 
	using namespace scx;
	int done = 0;
	while (!done) 
	{
		DrawScene();
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT)
				done = 1;

			if ( event.type == SDL_KEYDOWN ) 
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) 
					done = 1;

				if(event.key.keysym.sym == SDLK_F1)
				{
					if(DrawGrid)
						DrawGrid = false;
					else
						DrawGrid = true;
				}
			}
		}
	}

	SDL_Quit();
	return 1;
}

class Grid : public scx::Mesh
{

public:
	Grid(std::string name) : scx::Mesh(name) {};
	~Grid() {};

	virtual void Draw()
	{
		using namespace scx;
		int x, y;
		float float_x, float_y, float_xb, float_yb;
 
		glLoadIdentity();                            
		glTranslatef(0.0f, -2.0f, -12.0f);

		glRotatef(yrot,0.0f,1.0f,0.0f);  
		glRotatef(90,1.0f,0.0f,0.0f);

		//glRotatef(zrot,0.0f,0.0f,1.0f);

		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glPolygonMode( GL_BACK, GL_FILL );
		glPolygonMode( GL_FRONT, GL_LINE );


		glBegin( GL_QUADS );

		for( x = 0; x < 44; x++ )
		{
			for( y = 0; y < 44; y++ )
			{

				float_x = (float)(x)/44;
				float_y = (float)(y)/44;
				float_xb = (float)(x+1)/44;
				float_yb = (float)(y+1)/44;


				glTexCoord2f( float_x, float_y);
				glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );

				glTexCoord2f( float_x, float_yb );
				glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );

				glTexCoord2f( float_xb, float_yb );
				glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );

				glTexCoord2f( float_xb, float_y );
				glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
			}
		}

		glEnd();

		xrot+=0.3f;
		yrot+=0.2f;
		zrot+=0.4f;
	}
};

/* The main drawing function. */
void DrawScene()
{
	scx::Drawable RootNode("root node");
	scx::SceneGraph<scx::Drawable> Graph(&RootNode);

	Grid grid("grid node");

	if(scx::DrawGrid)
		Graph.Add(&grid);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	Graph.DrawNodes();

	SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) 
{
	scx::Initialize();

	RunApp();

	system("pause");
	return 0;
}