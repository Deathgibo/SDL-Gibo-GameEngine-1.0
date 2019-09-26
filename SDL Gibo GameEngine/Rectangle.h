#pragma once
#include "Shapes.h"

class Rectangle : public Shapes
{
public:
	Rectangle();
	~Rectangle();
	Rectangle(vec2d one, vec2d two, vec2d three, vec2d four, SDL_Texture* atexture = 0);
	Rectangle(double x, double y, double width, double height, SDL_Texture* atexture = 0);
	Rectangle(vector<vec2d> points);
	void RectangleInitialize(double x, double y, double width, double height, SDL_Texture* atexture = 0);
	void UpdateCircle();
	void Print(SDL_Renderer* grender);
	void Print(SDL_Renderer* grender, int r, int g, int b);
	void PrintTexture(SDL_Renderer* grender);
	vector<line> GetLines();

private:
};
Rectangle::Rectangle() : Shapes()
{

}
Rectangle::~Rectangle()
{
	texture = 0;
	points.clear();
}
Rectangle::Rectangle(vector<vec2d> thepoints) : Shapes()
{
	extern SDL_Texture* gray;
	shapetype = RECTANGLE;
	points.push_back(thepoints[0]); points.push_back(thepoints[1]); points.push_back(thepoints[2]); points.push_back(thepoints[3]);
	texture = gray;
	//calculae circle stuff
	circleCenter.x = points[0].x + ((points[1].x - points[0].x) / 2);
	circleCenter.y = points[0].y + ((points[3].y - points[0].y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));
	UpdateCircle();
}
Rectangle::Rectangle(double x, double y, double width, double height, SDL_Texture* atexture) : Shapes()
{
	shapetype = RECTANGLE;
	vec2d one(x,y);
	vec2d two(x+width, y);
	vec2d three(x+width, y+height);
	vec2d four(x, y+height);
	points.push_back(one); points.push_back(two); points.push_back(three); points.push_back(four);
	texture = atexture;
	//calculae circle stuff
	circleCenter.x = points[0].x + ((points[1].x - points[0].x) / 2);
	circleCenter.y = points[0].y + ((points[3].y - points[0].y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));
}
void Rectangle::UpdateCircle()
{
	double tallesty = points[0].y;
	double shortesty = points[0].y;
	double smallestx = points[0].x;
	double largestx = points[0].x;
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i].x > largestx)
			largestx = points[i].x;
		if (points[i].x < smallestx)
			smallestx = points[i].x;
		if (points[i].y < tallesty)
			tallesty = points[i].y;
		if (points[i].y > shortesty)
			shortesty = points[i].y;
	}
	double circleCenterX = sqrt(pow(largestx - smallestx, 2));// + pow(points[0].y - points[1].y, 2));
	double circleCenterY = sqrt(pow(tallesty - shortesty, 2));//pow(points[0].x - points[3].x, 2) + 
	circleCenter.x = smallestx + (circleCenterX / 2);
	circleCenter.y = tallesty + (circleCenterY / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));
	//circleCenter.x = points[0].x + ((points[1].x - points[0].x) / 2);
	//circleCenter.y = points[0].y + ((points[3].y - points[0].y) / 2);
}
void Rectangle::RectangleInitialize(double x, double y, double width, double height, SDL_Texture* atexture)
{
	shapetype = RECTANGLE;
	vec2d one(x, y);
	vec2d two(x + width, y);
	vec2d three(x + width, y + height);
	vec2d four(x, y + height);
	points.push_back(one); points.push_back(two); points.push_back(three); points.push_back(four);
	texture = atexture;
	//calculae circle stuff
	circleCenter.x = points[0].x + ((points[1].x - points[0].x) / 2);
	circleCenter.y = points[0].y + ((points[3].y - points[0].y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));
}
Rectangle::Rectangle(vec2d one, vec2d two, vec2d three, vec2d four, SDL_Texture* atexture) : Shapes()
{
	shapetype = RECTANGLE;
	points.push_back(one); points.push_back(two); points.push_back(three); points.push_back(four);
	texture = atexture;
	//calculae circle stuff
	circleCenter.x = points[0].x + ((points[1].x - points[0].x) / 2);
	circleCenter.y = points[0].y + ((points[3].y - points[0].y) / 2);
	circleRadius = sqrt(pow(circleCenter.x - points[0].x, 2) + pow(circleCenter.y - points[0].y, 2));
}
vector<line> Rectangle::GetLines()
{
	vector<line> lines;
	line line1(points[0],points[1]);
	line line2(points[1], points[2]);
	line line3(points[2], points[3]);
	line line4(points[3], points[0]);
	lines.push_back(line1); lines.push_back(line2); lines.push_back(line3); lines.push_back(line4);
	return lines;
}
void Rectangle::PrintTexture(SDL_Renderer* grender)
{
	extern SDL_Texture* portalicon;
	extern SDL_Texture* portaliconleft;
	extern SDL_Texture* portaliconright;
	extern SDL_Texture* checkpointicon;
	extern SDL_Texture* gray;
	extern SDL_Texture* red;
	extern SDL_Texture* green;
	SDL_Rect tmprect = { points[0].x,points[0].y,points[1].x - points[0].x,points[3].y - points[0].y };
	SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
	if (AccessTeleport())
	{
		if(teleportright)
			SDL_RenderCopy(grender, portaliconright, 0, &tmprect);
		else
			SDL_RenderCopy(grender, portaliconleft, 0, &tmprect);
		SDL_RenderDrawLine(grender, points[0].x, points[0].y, points[1].x, points[1].y);
		SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
		SDL_RenderDrawLine(grender, points[1].x, points[1].y, points[2].x, points[2].y);
		SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
		SDL_RenderDrawLine(grender, points[2].x, points[2].y, points[3].x, points[3].y);
		SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
		SDL_RenderDrawLine(grender, points[3].x, points[3].y, points[0].x, points[0].y);
	}
	else
	{
		if (checkpoint)
		{
			SDL_RenderCopy(grender, checkpointicon, 0, &tmprect);
			SDL_RenderDrawLine(grender, points[0].x, points[0].y, points[1].x, points[1].y);
			SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
			SDL_RenderDrawLine(grender, points[1].x, points[1].y, points[2].x, points[2].y);
			SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
			SDL_RenderDrawLine(grender, points[2].x, points[2].y, points[3].x, points[3].y);
			SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
			SDL_RenderDrawLine(grender, points[3].x, points[3].y, points[0].x, points[0].y);
		}
		else
		{
			if (bouncer)
			{
				SDL_RenderCopy(grender, green, 0, &tmprect);
			}
			else
			{
				if (damage)
				{
					SDL_RenderCopy(grender, red, 0, &tmprect);
				}
				else
				{
					SDL_RenderCopy(grender, texture, 0, &tmprect);
				}
			}
		}
	}
}
void Rectangle::Print(SDL_Renderer* grender)
{
	extern SDL_Texture* gray;
	extern SDL_Texture* green;
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);

	SDL_RenderDrawLine(grender, points[0].x, points[0].y, points[1].x, points[1].y);
	SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
	SDL_RenderDrawLine(grender, points[1].x, points[1].y, points[2].x, points[2].y);
	SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	SDL_RenderDrawLine(grender, points[2].x, points[2].y, points[3].x, points[3].y);
	SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	SDL_RenderDrawLine(grender, points[3].x, points[3].y, points[0].x, points[0].y);
	//PrintCircle(grender);
	//draw lines
	/*for (int i = 0; i < points[3].y - points[0].y; i++)
	{
		for (int j = 0; j < points[1].x - points[0].x; j++)
		{
			SDL_RenderDrawPoint(grender, points[0].x + j, points[0].y + i);
		}
	}*/
}
void Rectangle::Print(SDL_Renderer* grender, int r, int g, int b)
{
	//PrintCircle(grender);
	SDL_SetRenderDrawColor(grender, r, g, b, 0);
	if(bouncer)
		SDL_SetRenderDrawColor(grender, 66, 238, 146, 0);
	if(damage)
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);

	//triangle one 0,1,3
	double highesty = points[0].y;
	double lowesty = points[0].y;
	int indexhighesty = 0;
	int indexlowesty = 0;
	int indexmiddley = 3;
	for (int i = 0; i < 4; i++)
	{
		if (i != 2)
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
	}
	if (indexhighesty == 0 && indexlowesty == 1 || indexhighesty == 1 && indexlowesty == 0)
	{
		indexmiddley = 3;
	}
	if (indexhighesty == 1 && indexlowesty == 3 || indexhighesty == 3 && indexlowesty == 1)
	{
		indexmiddley = 0;
	}
	if (indexhighesty == 0 && indexlowesty == 3 || indexhighesty == 3 && indexlowesty == 0)
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
	for (double i = 0; i < points[indexlowesty].y - points[indexmiddley].y; i += increaseamount)//raise lowest up to the middle one then do normal triangle thing
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1 * i, points[indexlowesty].y - i, points[indexmiddley].x, points[indexmiddley].y);
		finalxamount = amount1 * i;
		finalyamount = i;
	}
	for (double i = 0; i < points[indexmiddley].y - points[indexhighesty].y; i += increaseamount)
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1 * i - finalxamount, points[indexlowesty].y - i - finalyamount, points[indexmiddley].x - amount2 * i, points[indexmiddley].y - i);
	}

	//triangle 2 1,2,3
	highesty = points[1].y;
	lowesty = points[1].y;
	indexhighesty = 1;
	indexlowesty = 1;
	indexmiddley = 2;
	for (int i = 1; i < 4; i++)
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
	if (indexhighesty == 1 && indexlowesty == 2 || indexhighesty == 2 && indexlowesty == 1)
	{
		indexmiddley = 3;
	}
	if (indexhighesty == 2 && indexlowesty == 3 || indexhighesty == 3 && indexlowesty == 2)
	{
		indexmiddley = 1;
	}
	if (indexhighesty == 1 && indexlowesty == 3 || indexhighesty == 3 && indexlowesty == 1)
	{
		indexmiddley = 2;
	}
	//cout << indexhighesty << " " << indexmiddley << " " << indexlowesty << endl;
	slope1 = (points[indexhighesty].y - points[indexlowesty].y) / (points[indexhighesty].x - points[indexlowesty].x);
	amount1 = 1 / slope1;
	slope2 = (points[indexhighesty].y - points[indexmiddley].y) / (points[indexhighesty].x - points[indexmiddley].x);
	amount2 = 1 / slope2;
	finalxamount = 0;
	finalyamount = 0;
	for (double i = 0; i < points[indexlowesty].y - points[indexmiddley].y; i += increaseamount)//raise lowest up to the middle one then do normal triangle thing
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1 * i, points[indexlowesty].y - i, points[indexmiddley].x, points[indexmiddley].y);
		finalxamount = amount1 * i;
		finalyamount = i;
	}
	for (double i = 0; i < points[indexmiddley].y - points[indexhighesty].y; i += increaseamount)
	{
		SDL_RenderDrawLine(grender, points[indexlowesty].x - amount1 * i - finalxamount, points[indexlowesty].y - i - finalyamount, points[indexmiddley].x - amount2 * i, points[indexmiddley].y - i);
	}
}