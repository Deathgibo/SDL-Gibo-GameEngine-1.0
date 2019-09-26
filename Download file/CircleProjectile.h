#pragma once
#include "Circle.h"
class CircleProjectile : public Circle
{
public:
	CircleProjectile();
	CircleProjectile(int radius, vec2d Center, SDL_Texture* atexture = 0);
	CircleProjectile(vector<vec2d> thepoints);
	void Print(SDL_Renderer* grender);
	void Print(SDL_Renderer* grender, int r, int g, int b);
	void PrintTexture(SDL_Renderer* grender);
	vector<line> GetLines();
	void UpdateCircle();

private:

};
CircleProjectile::CircleProjectile(int radius, vec2d Center, SDL_Texture* atexture)
{
	texture = atexture;
	shapetype = CIRCLE;
	circleRadius = radius;
	circleCenter = Center;
	vec2d one(radius*cos(0) + circleCenter.x, radius*sin(0) + circleCenter.y);
	points.push_back(Center); points.push_back(one);
	for (int i = 45; i <= 360 + 45; i += 90)//this number adding to i has to be divisor of 360
	{
		vec2d tmp(radius*cos((i*3.14) / 180) + circleCenter.x, radius*sin((i*3.14) / 180) + circleCenter.y);
		points.push_back(tmp);
	}
}
CircleProjectile::CircleProjectile(vector<vec2d> thepoints)
{
	extern SDL_Texture* redcircle;
	texture = redcircle;
	shapetype = CIRCLE;
	circleCenter = thepoints[0];
	circleRadius = abs(thepoints[1].x - thepoints[0].x);
	for (int i = 0; i < thepoints.size(); i++)
	{
		points.push_back(thepoints[i]);
	}
}
void CircleProjectile::Print(SDL_Renderer* grender)
{
	//PrintCircle(grender);
	extern SDL_Texture* balljump;
	SDL_Rect tmprect = { points[4].x,points[4].y,points[5].x-points[4].x,points[3].y-points[4].y };
	if (GetDoubleJumper())
	{
		SDL_RenderCopy(grender, balljump, 0, &tmprect);
	}
	else
	{
		for (int i = 2; i < points.size() - 1; i++)
		{
			SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}
	}
}
void CircleProjectile::UpdateCircle()
{
	circleCenter = points[0];
	circleRadius = points[1].x - points[0].x;
}
void CircleProjectile::PrintTexture(SDL_Renderer* grender)
{
	//PrintCircle(grender);
	int leftmostx = -circleRadius + circleCenter.x;
	int rightmostx = circleRadius + circleCenter.x;
	int lowesty = -circleRadius + circleCenter.y;
	int highesty = circleRadius + circleCenter.y;
	vector<vec2d> squarepoints;
	vec2d one(leftmostx, lowesty); vec2d two(rightmostx, lowesty); vec2d three(rightmostx, highesty); vec2d four(leftmostx, highesty);
	squarepoints.push_back(one); squarepoints.push_back(two); squarepoints.push_back(three); squarepoints.push_back(four);
	SDL_Rect tmprect = { squarepoints[0].x,squarepoints[0].y,squarepoints[1].x - squarepoints[0].x,squarepoints[2].y - squarepoints[1].y };
	SDL_RenderCopy(grender, texture, 0, &tmprect);
}
void CircleProjectile::Print(SDL_Renderer* grender, int r, int g, int b)
{
	SDL_SetRenderDrawColor(grender, r, g, b, 0);
	if (doublejumper)
		SDL_SetRenderDrawColor(grender, 15, 42, 149, 0);
	if (damage)
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	for (int i = 0; i < 360; i+=10)
	{
		SDL_RenderDrawLine(grender, circleCenter.x, circleCenter.y, circleRadius*cos((i*3.14) / 180) + circleCenter.x, circleRadius*sin((i*3.14) / 180) + circleCenter.y);
	}
	if (ballspawner)
	{
		int rotation = GetTotalAmountRotated();
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
		SDL_RenderDrawLine(grender, circleCenter.x, circleCenter.y, circleRadius*cos((rotation*3.14) / 180) + circleCenter.x, circleRadius*sin((rotation*3.14) / 180) + circleCenter.y);
	}
	/*SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	for (int i = 2; i < points.size() - 1; i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}*/
}
vector<line> CircleProjectile::GetLines()
{
	vector<line> lines;
	for (int i = 2; i < points.size() - 1; i++)
	{
		line tmp(points[i], points[i + 1]);
		lines.push_back(tmp);
	}
	return lines;
}