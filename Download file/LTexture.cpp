#include "LTexture.h"
#include <iostream>
using namespace std;



LTexture::LTexture()
{
	lwidth = 0;
	lheight = 0;
	ltexture = 0;
}
LTexture::~LTexture()
{
	free();
}
bool LTexture::loadfromfile(std::string a, SDL_Renderer* r)
{
	free();
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 0, 0, 0));

	returntexture = SDL_CreateTextureFromSurface(r, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void LTexture::free()
{
	SDL_DestroyTexture(ltexture);
	ltexture = 0;
	lwidth = 0;
	lheight = 0;
}
void LTexture::render(int x, int y,SDL_Renderer* r, SDL_Texture* t)
{
	SDL_Rect renderrect = { x,y,lwidth,lheight };
	SDL_RenderCopy(r, t, 0, &renderrect);
}
int LTexture::getwidth()
{
	return lwidth;
}
int LTexture::getheight()
{
	return lheight;
}