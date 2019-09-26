#include <iostream>
#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

 int screenwidth = 1200;
 int screenheight = 650;
SDL_Window* gwindow = 0;
SDL_Renderer* grender = 0;
SDL_Surface* gsurface = 0;
SDL_Texture* picture1 = 0;
SDL_Texture* picture2 = 0;
SDL_Texture* picture3 = 0;
SDL_Texture* tigerwoods = 0;
SDL_Texture* trihard = 0;
SDL_Texture* hotgirl = 0;
SDL_Texture* back = 0;
SDL_Texture* currentsurface = 0;


bool init();
bool loadmedia();
void close();
SDL_Texture* loadtexture(string a);
int main(int argc, char* argv[])
{
	if (!init())
	{
		cout << "initialization failed";
	}
	else if (!loadmedia())
	{
		cout << "could not load media";
	}
	else
	{
		int counter = 2;
		bool exit = false;
		SDL_Event e;
		while (exit == false)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					exit = true;
				}
				if (e.type == SDL_WINDOWEVENT)
				{
					if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						screenwidth = e.window.data1;
						screenheight = e.window.data2;
					}
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						if (currentsurface == picture1)
						{

						}
						else if (currentsurface == picture2)
						{
							currentsurface = picture1;
						}
						else if (currentsurface == picture3)
						{
							currentsurface = picture2;
						}
						break;
					case SDLK_DOWN:
						if (currentsurface == picture1)
						{
							currentsurface = picture2;
						}
						else if (currentsurface == picture2)
						{
							currentsurface = picture3;
						}
						else if (currentsurface == picture3)
						{
							
						}
						break;
					case SDLK_RETURN:
						if (currentsurface == picture1)
						{
							currentsurface = hotgirl;
						}
						else if (currentsurface == picture2)
						{
							currentsurface = trihard;
						}
						else if (currentsurface == picture3)
						{
							currentsurface = tigerwoods;
						}
						break;
					case SDLK_BACKSPACE:
						if (currentsurface == hotgirl)
						{
							currentsurface = picture1;
						}
						else if (currentsurface == trihard)
						{
							currentsurface = picture2;
						}
						else if (currentsurface == tigerwoods)
						{
							currentsurface = picture3;
						}
						break;
					}
				}
				else if (e.type == SDL_MOUSEMOTION)
				{
					if (currentsurface == hotgirl || currentsurface == trihard || currentsurface == tigerwoods)
					{
						
					}
					else
					{
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x < 538 && x>486 && y < 395 && y>315)
						{
							currentsurface = picture1;
						}
						if (x < 548 && x>470 && y < 511 && y>418)
						{
							currentsurface = picture2;
						}
						if (x < 564 && x>467 && y < 650 && y>526)
						{
							currentsurface = picture3;
						}
						
					}
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (x < 538 && x>486 && y < 395 && y>315)
					{
						currentsurface = hotgirl;
					}
					if (x < 548 && x>470 && y < 511 && y>418)
					{
						currentsurface = trihard;
					}
					if (x < 564 && x>467 && y < 650 && y>526)
					{
						currentsurface = tigerwoods;
					}
					if (x < 50 && x>0 && y < 50 && y>0)
						{
						if (currentsurface == hotgirl)
						{
							currentsurface = picture1;
						}
						else if (currentsurface == trihard)
						{
							currentsurface = picture2;
						}
						else if (currentsurface == tigerwoods)
						{
							currentsurface = picture3;
						}
						}
				}
			}
			SDL_Rect rectback = { 0,0,50,50 };
			SDL_Rect rectx = { 0,0,screenwidth,screenheight};
			SDL_RenderClear(grender);
			SDL_RenderSetViewport(grender, &rectx);
			SDL_RenderCopy(grender, currentsurface, 0, 0);
			if (currentsurface == trihard || currentsurface == hotgirl || currentsurface == tigerwoods)
			{
				
				SDL_RenderSetViewport(grender, &rectback);
				SDL_RenderCopy(grender, back, 0, &rectback);
			}
			
			SDL_RenderPresent(grender);
			
			
		}
	}
	close();
	return 0;
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Could not initialize SDL";
		success = false;
	}
	else
	{
		gwindow = SDL_CreateWindow("Pictures", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (gwindow == 0)
		{
			cout << "could not create window";
			success = false;
		}
		else
		{
			gsurface = SDL_GetWindowSurface(gwindow);
			if (gsurface == 0)
			{
				cout << "could not upload surface";
				success = false;
			}
			else
			{
				int flags = IMG_INIT_PNG;
				if ((IMG_Init(flags) & flags) != flags)
				{
					cout << "failed to initialize png";
					success = false;
				}
				if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				{
					cout << "failed to scale quality";
				}
				grender = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);
			
			}
		}
	}
	return success;
}
bool loadmedia()
{
	bool success = true;

	picture2 = loadtexture("Pictures 2.PNG");
	if (picture2 == 0)
	{
		cout << "could not load image1";
		success = false;
	}
	
	picture1 = loadtexture("Pictures 1.PNG");
	if (picture1 == 0)
	{
		cout << "could not load image1";
		success = false;
	}
	
	picture3 = loadtexture("Pictures 3.PNG");
	if (picture3 == 0)
	{
		cout << "could not load image1";
		success = false;
	}
	currentsurface = picture2;
	trihard = loadtexture("triihard.PNG");
	
	tigerwoods = loadtexture("scott.JPG");
	
	hotgirl = loadtexture("Hot girl.PNG");
	back = loadtexture("back.PNG");
	
	return success;
}
SDL_Texture* loadtexture(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 255, 255, 255));
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void close()
{
	SDL_DestroyRenderer(grender);
	SDL_DestroyWindow(gwindow);
	gwindow = 0;
	SDL_FreeSurface(gsurface);
	gsurface = 0;
	SDL_DestroyTexture(picture1);

	SDL_Quit();
	IMG_Quit();
}