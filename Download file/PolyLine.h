#pragma once
#include "Shapes.h"

class PolyLine : public Shapes
{
public:
	PolyLine(int one, int two);
	PolyLine(vector<vec2d> points);
	void Print(SDL_Renderer* grender);
	void Print(SDL_Renderer* grender, int r, int g, int b);
	void AddLine();
	vector<line> GetLines();
	void UpdateCircle();
private:

};

PolyLine::PolyLine(vector<vec2d> thepoints) : Shapes()
{
	shapetype = POLYLINE;
	for (int i = 0; i < thepoints.size(); i++)
	{
		vec2d onez(thepoints[i].x, thepoints[i].y);
		points.push_back(onez);
	}
	circleCenter.x = 0; circleCenter.y = 0;
	circleRadius = 1;
}
PolyLine::PolyLine(int one, int two) : Shapes()
{
	shapetype = POLYLINE;
	vec2d onez(100, 100);
	vec2d twoz(150, 150);
	points.push_back(onez); points.push_back(twoz);
	circleCenter.x = 0; circleCenter.y = 0;
	circleRadius = 1;
}
void PolyLine::Print(SDL_Renderer* grender)
{
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	for (int i = 0; i < points.size()-1; i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
	}
}
void PolyLine::Print(SDL_Renderer* grender, int r, int g, int b)
{
	SDL_SetRenderDrawColor(grender, r, g, b, 0);
	if (damage)
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	for (int i = 0; i < points.size() - 1; i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
}
vector<line> PolyLine::GetLines()
{
	vector<line> lines;
	for (int i = 0; i < points.size()-1; i++)
	{
		line linetmp(points[i], points[i + 1]);
		lines.push_back(linetmp);
	}
	return lines;
}
void PolyLine::AddLine()
{
	vec2d twoz(points[points.size() - 1].x + 50, points[points.size() - 1].y + 50);
	points.push_back(twoz);
}
void PolyLine::UpdateCircle()
{

}