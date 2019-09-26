#pragma once
#include "Shapes.h"

class Triangle : public Shapes
{
public:
	Triangle(vec2d one, vec2d two, vec2d three, SDL_Texture* atexture = 0);
	Triangle(vector<vec2d> points);
	Triangle(Shapes & thetri);
	void Print(SDL_Renderer* grender);
	void Print(SDL_Renderer* grender, int r, int g, int b);
	//void PrintTexture(SDL_Renderer* grender);
	vector<line> GetLines();
	void UpdateCircle();
private:

};
Triangle::Triangle(vector<vec2d> thepoints) : Shapes()
{
	shapetype = TRIANGLE;
	points.push_back(thepoints[0]); points.push_back(thepoints[1]); points.push_back(thepoints[2]);
	texture = 0;
	//construct rectangle from triangle and use that to find circle
	double smallest = points[0].y;
	double largest = points[1].y;
	for (int i = 0; i < 3; i++)
	{
		if (points[i].y < smallest)
		{
			smallest = points[i].y;
		}
		if (points[i].y > largest)
		{
			largest = points[i].y;
		}
	}
	vec2d oner(points[0].x, smallest);
	vec2d twor(points[2].x, smallest);
	vec2d threer(points[2].x, largest);
	vec2d fourr(points[0].x, largest);
	circleCenter.x = oner.x + ((twor.x - oner.x) / 2);
	circleCenter.y = oner.y + ((fourr.y - oner.y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - oner.x, 2) + pow(circleCenter.y - oner.y, 2));
	vec2d insideone();
}
Triangle::Triangle(vec2d one, vec2d two, vec2d three, SDL_Texture* atexture) : Shapes()
{
	shapetype = TRIANGLE;
	points.push_back(one); points.push_back(two); points.push_back(three);
	texture = atexture;
	//construct rectangle from triangle and use that to find circle
	double smallest = one.y;
	double largest = two.y;
	for (int i = 0; i < 3; i++)
	{
		if (points[i].y < smallest)
		{
			smallest = points[i].y;
		}
		if (points[i].y > largest)
		{
			largest = points[i].y;
		}
	}
	vec2d oner(one.x,smallest);
	vec2d twor(three.x,smallest);
	vec2d threer(three.x,largest);
	vec2d fourr(one.x,largest);
	circleCenter.x = oner.x + ((twor.x - oner.x) / 2);
	circleCenter.y = oner.y + ((fourr.y - oner.y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - oner.x, 2) + pow(circleCenter.y - oner.y, 2));
	vec2d insideone();
}
Triangle::Triangle(Shapes & thetri) : Shapes()
{
	shapetype = TRIANGLE;
	vector<vec2d> thepoints = thetri.AccessPoints();
	vec2d one;
	vec2d two;
	vec2d three;
	one.x = thepoints[0].x; one.y = thepoints[0].y;
	two.x = thepoints[1].x; two.y = thepoints[1].y;
	three.x = thepoints[2].x; three.y = thepoints[2].y;
	points.push_back(one); points.push_back(two); points.push_back(three);
	texture = 0;
	//construct rectangle from triangle and use that to find circle
	double smallest = one.y;
	double largest = two.y;
	for (int i = 0; i < 3; i++)
	{
		if (points[i].y < smallest)
		{
			smallest = points[i].y;
		}
		if (points[i].y > largest)
		{
			largest = points[i].y;
		}
	}
	vec2d oner(one.x, smallest);
	vec2d twor(three.x, smallest);
	vec2d threer(three.x, largest);
	vec2d fourr(one.x, largest);
	circleCenter.x = oner.x + ((twor.x - oner.x) / 2);
	circleCenter.y = oner.y + ((fourr.y - oner.y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - oner.x, 2) + pow(circleCenter.y - oner.y, 2));
	vec2d insideone();
}
void Triangle::UpdateCircle()
{
	double smallest = points[0].y;
	double largest = points[1].y;
	double leftmost = points[0].x;
	double rightmost = points[1].x;
	for (int i = 0; i < 3; i++)
	{
		if (points[i].x < leftmost)
		{
			leftmost = points[i].x;
		}
		if (points[i].x > rightmost)
		{
			rightmost = points[i].x;
		}
		if (points[i].y < smallest)
		{
			smallest = points[i].y;
		}
		if (points[i].y > largest)
		{
			largest = points[i].y;
		}
	}
	vec2d oner(leftmost, smallest);
	vec2d twor(rightmost, smallest);
	vec2d threer(rightmost, largest);
	vec2d fourr(leftmost, largest);
	circleCenter.x = oner.x + ((twor.x - oner.x) / 2);
	circleCenter.y = oner.y + ((fourr.y - oner.y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - oner.x, 2) + pow(circleCenter.y - oner.y, 2));
}
vector<line> Triangle::GetLines()
{
	vector<line> lines;
	line line1(points[0], points[1]);
	line line2(points[1], points[2]);
	line line3(points[2], points[0]);
	lines.push_back(line1); lines.push_back(line2); lines.push_back(line3);
	return lines;
}
void Triangle::Print(SDL_Renderer* grender)
{
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderDrawLine(grender, points[0].x, points[0].y, points[1].x, points[1].y);
	SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
	SDL_RenderDrawLine(grender, points[1].x, points[1].y, points[2].x, points[2].y);
	SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	SDL_RenderDrawLine(grender, points[2].x, points[2].y, points[0].x, points[0].y);
	//PrintCircle(grender);
}
void Triangle::Print(SDL_Renderer* grender, int r, int g, int b)
{
	//PrintCircle(grender);
	SDL_SetRenderDrawColor(grender, r, g, b, 0);
	if (damage)
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	double highesty = points[0].y;
	double lowesty = points[0].y;
	int indexhighesty = 0;
	int indexlowesty = 0;
	int indexmiddley = 2;
	for (int i = 0; i < 3; i++)
	{
		if (points[i].y < highesty)
		{
			highesty = points[i].y;
			indexhighesty = i;
		}
		if (points[i].y > lowesty)
		{
			lowesty = points[i].y;
			indexlowesty = i;
		}
	}
	if (indexhighesty == 0 && indexlowesty == 1 || indexhighesty == 1 && indexlowesty == 0)
	{
		indexmiddley = 2;
	}
	if (indexhighesty == 1 && indexlowesty == 2 || indexhighesty == 2 && indexlowesty == 1)
	{
		indexmiddley = 0;
	}
	if (indexhighesty == 0 && indexlowesty == 2 || indexhighesty == 2 && indexlowesty == 0)
	{
		indexmiddley = 1;
	}
	//cout << indexhighesty << " " << indexmiddley << " " << indexlowesty << endl;
	double slope1 = (points[indexhighesty].y - points[indexlowesty].y) / (points[indexhighesty].x - points[indexlowesty].x);
	double amount1 = 1 / slope1;
	double slope2 = (points[indexhighesty].y - points[indexmiddley].y) / (points[indexhighesty].x - points[indexmiddley].x);
	double amount2 = 1 / slope2;
	double finalxamount = 0;
	double finalyamount = 0;
	double increaseamount = 2;
	for (double i = 0; i < points[indexlowesty].y - points[indexmiddley].y; i+= increaseamount)//raise lowest up to the middle one then do normal triangle thing
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1 * i, points[indexlowesty].y - i, points[indexmiddley].x, points[indexmiddley].y);
		finalxamount = amount1 * i;
		finalyamount = i;
	}
	for (double i = 0; i < points[indexmiddley].y - points[indexhighesty].y; i+= increaseamount)
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1*i - finalxamount, points[indexlowesty].y - i - finalyamount, points[indexmiddley].x - amount2 *i, points[indexmiddley].y - i);
	}
}
