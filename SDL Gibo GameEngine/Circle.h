#pragma once
#include "Shapes.h"

class Circle : public Shapes
{
public:
	Circle();
	Circle(int radius, vec2d Center, SDL_Texture* atexture = 0);
	Circle(vector<vec2d> thepoints);
	void Print(SDL_Renderer* grender);
	void Print(SDL_Renderer* grender, int r, int g, int b);
	void PrintTexture(SDL_Renderer* grender);
	vector<line> GetLines();
	void UpdateCircle();
private:

};
Circle::Circle()
{

}
Circle::Circle(int radius, vec2d Center, SDL_Texture* atexture) : Shapes()
{
	texture = atexture;
	shapetype = CIRCLE;
	circleRadius = radius;
	circleCenter = Center;
	vec2d one(radius*cos(0) + circleCenter.x, radius*sin(0) + circleCenter.y);
	points.push_back(Center); points.push_back(one);
	vector<vec2d> vects;
	for (int i = 0; i <= 360; i += 30)//this number adding to i has to be divisor of 360
	{
		vec2d tmp(radius*cos((i*3.14) / 180) + circleCenter.x, radius*sin((i*3.14) / 180) + circleCenter.y);
		points.push_back(tmp);
	}
}
Circle::Circle(vector<vec2d> thepoints) : Shapes()
{
	extern SDL_Texture* bluecircle;
	texture = bluecircle;
	shapetype = CIRCLE;
	circleCenter = thepoints[0];
	circleRadius = abs(thepoints[1].x- thepoints[0].x);
	for (int i = 0; i < thepoints.size(); i++)
	{
		points.push_back(thepoints[i]);
	}
}
void Circle::Print(SDL_Renderer* grender)
{
	//PrintCircle(grender);
	for (int i = 2; i < points.size() - 1; i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i+1].x, points[i + 1].y);
	}
}
void Circle::UpdateCircle()
{
	circleCenter = points[0];
	circleRadius = points[1].x - points[0].x;
}
void Circle::Print(SDL_Renderer* grender, int r, int g, int b)
{
	//PrintCircle(grender);
	SDL_SetRenderDrawColor(grender, r, g, b, 0);
	if(doublejumper)
		SDL_SetRenderDrawColor(grender, 15, 42, 149, 0);
	if(ballspawner)
		SDL_SetRenderDrawColor(grender, 174, 125, 137, 0);
	if (damage)
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	for (int i = 0; i < 360; i+=5)
	{
		SDL_RenderDrawLine(grender, circleCenter.x, circleCenter.y, circleRadius*cos((i*3.14) / 180) + circleCenter.x, circleRadius*sin((i*3.14) / 180) + circleCenter.y);
	}	
	if (ballspawner)
	{
		int rotation = GetTotalAmountRotated();
		SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
		SDL_RenderDrawLine(grender, circleCenter.x, circleCenter.y, circleRadius*cos((rotation*3.14)/180) + circleCenter.x, circleRadius*sin((rotation*3.14) / 180) + circleCenter.y);
	}
	/*SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	for (int i = 2; i < points.size() - 1; i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}*/
}
void Circle::PrintTexture(SDL_Renderer* grender)
{
	//PrintCircle(grender);
	extern SDL_Texture* redcircle;
	int leftmostx = -circleRadius + circleCenter.x;
	int rightmostx = circleRadius + circleCenter.x;
	int lowesty = -circleRadius + circleCenter.y;
	int highesty = circleRadius + circleCenter.y;
	vector<vec2d> squarepoints;
	vec2d one(leftmostx, lowesty); vec2d two(rightmostx, lowesty); vec2d three(rightmostx, highesty); vec2d four(leftmostx, highesty);
	squarepoints.push_back(one); squarepoints.push_back(two); squarepoints.push_back(three); squarepoints.push_back(four);
	SDL_Rect tmprect = { squarepoints[0].x,squarepoints[0].y,squarepoints[1].x - squarepoints[0].x,squarepoints[2].y - squarepoints[1].y };
	if (damage)
	{
		SDL_RenderCopy(grender, redcircle, 0, &tmprect);
	}
	else
	{
		SDL_RenderCopy(grender, texture, 0, &tmprect);
	}
}
vector<line> Circle::GetLines()
{
	/*vector<line> lines;
	vec2d one(circleRadius*cos(0.785398) + circleCenter.x,circleRadius*sin(0.785398) + circleCenter.y);
	vec2d two(circleRadius*cos(2.35619) + circleCenter.x, circleRadius*sin(2.35619) + circleCenter.y);
	vec2d three(circleRadius*cos(3.92699) + circleCenter.x, circleRadius*sin(3.92699) + circleCenter.y);
	vec2d four(circleRadius*cos(5.49779) + circleCenter.x, circleRadius*sin(5.49779) + circleCenter.y);
	line lineone(one, two);
	line linetwo(two, three);
	line linethree(three, four);
	line linefour(four, one);
	lines.push_back(lineone); lines.push_back(linetwo); lines.push_back(linethree); lines.push_back(linefour);*/
	vector<line> lines;
	for (int i = 2; i < points.size() - 1; i++)
	{
		line tmp(points[i], points[i + 1]);
		lines.push_back(tmp);
	}
	return lines;
}
