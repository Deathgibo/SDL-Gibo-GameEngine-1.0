#include <SDL.h>
#include <SDL_image.h>
#include <string>

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadfromfile(std::string a,SDL_Renderer* r);
	void free();
	void render(int x, int y, SDL_Renderer* r,SDL_Texture* t);

	int getwidth();
	int getheight();

private:
	int lwidth;
	int lheight;
	SDL_Texture* ltexture;

};
