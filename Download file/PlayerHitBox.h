#pragma once
#include "Shapes.h"

class PlayerHitBox : public Shapes
{
public:
	PlayerHitBox(vec2d one, vec2d one2, vec2d two, vec2d two2, vec2d three, vec2d three2, vec2d four, vec2d four2, SDL_Texture* atexture = 0);
	void Print(SDL_Renderer* grender);

private:

};

PlayerHitBox::PlayerHitBox(vec2d one, vec2d one2, vec2d two, vec2d two2, vec2d three, vec2d three2, vec2d four, vec2d four2, SDL_Texture* atexture)
{
	shapetype = PLAYERHITBOX;
	points.push_back(one); points.push_back(one2); points.push_back(two); points.push_back(two2); points.push_back(three); points.push_back(three2); points.push_back(four);
	points.push_back(four2);
	texture = atexture;
	circleCenter.x = points[0].x + ((points[2].x - points[0].x) / 2);
	circleCenter.y = points[0].y + ((points[4].y - points[0].y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));

}
void PlayerHitBox::Print(SDL_Renderer* grender)
{
	//PrintCircle(grender);
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderDrawLine(grender, points[0].x, points[0].y, points[1].x, points[1].y);
	SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
	//SDL_RenderDrawLine(grender, points[2].x, points[2].y, points[3].x, points[3].y);
	SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	//SDL_RenderDrawLine(grender, points[4].x, points[4].y, points[5].x, points[5].y);
	SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	//SDL_RenderDrawLine(grender, points[6].x, points[6].y, points[7].x, points[7].y);
}