#pragma once
#include "Rectangle.h"
#include "Player.h"

class Playergui
{

public:
	Playergui();
	~Playergui();
	Playergui(Player * theplayer);
	void MoveX(double x);
	void MoveY(double y);
	void Print(SDL_Renderer* grender);
	void SetBorder(int x);
	int GuiIndexClicked(int x, int y);
	bool clickedleft(int x, int y);
	bool clickedright(int x, int y);
	bool clickedleftx(int x, int y);
	bool clickedrightx(int x, int y);
	void HandleDottedSquareClick(int x, int y, int hitbox = true);
	void HandleDottedSquareMotion(int x, int y, int hitbox = true);
	void SetSquareSide(int i);

	Player* Theplayer;
	Rectangle imagebox;
	Rectangle imagebox2;
	Rectangle hitboxbox;
	Rectangle hitboxbox2;
	Rectangle doublejumpbox;
	Rectangle doublejumpbox2;
	Rectangle heightbox;
	Rectangle heightbox2;
	Rectangle heightboxleft;
	Rectangle heightboxright;
	Rectangle deletesquarebox;
	Rectangle sizebox;
	Rectangle sizebox2;
	Rectangle speedbox;
	Rectangle speedbox2;
	Rectangle speedboxleft;
	Rectangle speedboxright;
	bool speedboxborder;
	bool sizeboxborder;
	bool imageboxborder;
	bool hitboxborder;
	bool doublejumpboxborder;
	bool heightboxborder;
	bool deleteboxborder;
	int squareside;
	vec2d mouseposition;
	bool holddownclick;
};

Playergui::Playergui()
{

}
Playergui::~Playergui()
{
	Theplayer = 0;
}
Playergui::Playergui(Player * theplayer)
{
	holddownclick = false;
	squareside = 0;
	extern SDL_Texture* fourarrowbox;
	extern SDL_Texture* dottedbox;
	extern SDL_Texture* doublejumpericon;
	extern SDL_Texture* speedicon;
	extern SDL_Texture* deletebox;
	extern SDL_Texture* playericon;
	extern SDL_Texture* runicon;
	Theplayer = theplayer;
	sizeboxborder = false;
	imageboxborder = false;
	hitboxborder = false;
	doublejumpboxborder = false;
	heightboxborder = false;
	deleteboxborder = false;
	speedboxborder = false;
	double px = theplayer->AccessPlayerx();
	double py = theplayer->AccessPlayery();
	double x = 25;
	double y = 25;
	sizebox.RectangleInitialize(px + x, py - 3 * y, x, y, playericon);
	sizebox2.RectangleInitialize(px + x, py - 3 * y, x, y);
	imagebox.RectangleInitialize(px, py - 2*y, x, y, fourarrowbox);
	imagebox2.RectangleInitialize(px, py - 2 * y, x, y);
	hitboxbox.RectangleInitialize(px+ x, py - 2 * y, x, y, dottedbox);
	hitboxbox2.RectangleInitialize(px + x, py - 2 * y, x, y);
	doublejumpbox.RectangleInitialize(px + 2*x, py - 2 * y, x, y, doublejumpericon);
	doublejumpbox2.RectangleInitialize(px + 2*x, py - 2 * y, x, y);
	heightbox.RectangleInitialize(px + 3*x, py - 2 * y, x, y, speedicon);
	heightbox2.RectangleInitialize(px + 3*x, py - 2 * y, x, y);
	heightboxleft.RectangleInitialize(px + 3 * x, py - 2 * y, x/2, y, speedicon);
	heightboxright.RectangleInitialize(px + 3 * x + (x/2), py - 2 * y, x/2, y, speedicon);
	deletesquarebox.RectangleInitialize(px + 4 * x, py - 2 * y, x, y, deletebox);
	speedbox.RectangleInitialize(px + 3 * x, py - 3 * y, x, y, runicon);
	speedbox2.RectangleInitialize(px + 3 * x, py - 3 * y, x, y);
	speedboxleft.RectangleInitialize(px + 3 * x, py - 3 * y, x/2, y);
	speedboxright.RectangleInitialize(px + 3 * x +(x/2), py - 3 * y, x/2, y);
}
void Playergui::MoveX(double x)
{
	sizebox.MoveX(x, 0, 0);
	sizebox2.MoveX(x, 0, 0);
	imagebox.MoveX(x);
	imagebox2.MoveX(x);
	hitboxbox.MoveX(x);
	hitboxbox2.MoveX(x);
	doublejumpbox.MoveX(x);
	doublejumpbox2.MoveX(x);
	heightbox.MoveX(x);
	heightbox2.MoveX(x);
	heightboxleft.MoveX(x);
	heightboxright.MoveX(x);
	deletesquarebox.MoveX(x);
    speedbox.MoveX(x);
    speedbox2.MoveX(x);
    speedboxleft.MoveX(x);
    speedboxright.MoveX(x);
}
void Playergui::MoveY(double y)
{
	sizebox.MoveY(y, 0, 0);
	sizebox2.MoveY(y, 0, 0);
	imagebox.MoveY(y);
	imagebox2.MoveY(y);
	hitboxbox.MoveY(y);
	hitboxbox2.MoveY(y);
	doublejumpbox.MoveY(y);
	doublejumpbox2.MoveY(y);
	heightbox.MoveY(y);
	heightbox2.MoveY(y);
	heightboxleft.MoveY(y);
	heightboxright.MoveY(y);
	deletesquarebox.MoveY(y);
	speedbox.MoveY(y);
	speedbox2.MoveY(y);
	speedboxleft.MoveY(y);
	speedboxright.MoveY(y);
}
void Playergui::Print(SDL_Renderer* grender)
{
	sizebox.PrintTexture(grender);
	imagebox.PrintTexture(grender);
	hitboxbox.PrintTexture(grender);
	doublejumpbox.PrintTexture(grender);
	heightbox.PrintTexture(grender);
	deletesquarebox.PrintTexture(grender);
	speedbox.PrintTexture(grender);
	if (speedboxborder)
		speedbox2.Print(grender);
	if (sizeboxborder)
		sizebox2.Print(grender);
	if (imageboxborder)
		imagebox2.Print(grender);
	if (hitboxborder)
		hitboxbox2.Print(grender);
	if (doublejumpboxborder)
		doublejumpbox2.Print(grender);
	if (heightboxborder)
		heightbox2.Print(grender);
}
int Playergui::GuiIndexClicked(int x, int y)
{
	vector<vec2d>imagepoints = imagebox.AccessPoints();
	vector<vec2d>hitboxpoints = hitboxbox.AccessPoints();
	vector<vec2d>doublejumppoints = doublejumpbox.AccessPoints();
	vector<vec2d>heightpoints = heightbox.AccessPoints();
	vector<vec2d>deletepoints = deletesquarebox.AccessPoints();
	vector<vec2d>sizepoints = sizebox.AccessPoints();
	vector<vec2d>speedpoints = speedbox.AccessPoints();
	if (x <= imagepoints[1].x && x >= imagepoints[0].x && y <= imagepoints[3].y && y >= imagepoints[0].y)
	{
		return 1;
	}
	else if (x <= hitboxpoints[1].x && x >= hitboxpoints[0].x && y <= hitboxpoints[3].y && y >= hitboxpoints[0].y)
	{
		return 2;
	}
	else if (x <= doublejumppoints[1].x && x >= doublejumppoints[0].x && y <= doublejumppoints[3].y && y >= doublejumppoints[0].y)
	{
		return 3;
	}
	else if (x <= heightpoints[1].x && x >= heightpoints[0].x && y <= heightpoints[3].y && y >= heightpoints[0].y)
	{
		return 4;
	}
	else if (x <= deletepoints[1].x && x >= deletepoints[0].x && y <= deletepoints[3].y && y >= deletepoints[0].y)
	{
		return 5;
	}
	if (x <= sizepoints[1].x && x >= sizepoints[0].x && y <= sizepoints[3].y && y >= sizepoints[0].y)
	{
		return 6;
	}
	if (x <= speedpoints[1].x && x >= speedpoints[0].x && y <= speedpoints[3].y && y >= speedpoints[0].y)
	{
		return 7;
	}
	return -1;
}
bool Playergui::clickedleft(int x, int y)
{
	vector<vec2d>imagepoints = heightboxleft.AccessPoints();
	if (x <= imagepoints[1].x && x >= imagepoints[0].x && y <= imagepoints[3].y && y >= imagepoints[0].y)
	{
		return 1;
	}
	return 0;
}
bool Playergui::clickedright(int x, int y)
{
	vector<vec2d>imagepoints = heightboxright.AccessPoints();
	if (x <= imagepoints[1].x && x >= imagepoints[0].x && y <= imagepoints[3].y && y >= imagepoints[0].y)
	{
		return 1;
	}
	return 0;
}
bool Playergui::clickedleftx(int x, int y)
{
	vector<vec2d>imagepoints = speedboxleft.AccessPoints();
	if (x <= imagepoints[1].x && x >= imagepoints[0].x && y <= imagepoints[3].y && y >= imagepoints[0].y)
	{
		return 1;
	}
	return 0;
}
bool Playergui::clickedrightx(int x, int y)
{
	vector<vec2d>imagepoints = speedboxright.AccessPoints();
	if (x <= imagepoints[1].x && x >= imagepoints[0].x && y <= imagepoints[3].y && y >= imagepoints[0].y)
	{
		return 1;
	}
	return 0;
}
void Playergui::SetBorder(int x)
{
	switch (x)
	{
	case 1: imageboxborder = true; hitboxborder = false; doublejumpboxborder = false; heightboxborder = false;  deleteboxborder = false; sizeboxborder = false; speedboxborder = false; break;
	case 2: imageboxborder = false; hitboxborder = true; doublejumpboxborder = false; heightboxborder = false; deleteboxborder = false; sizeboxborder = false; speedboxborder = false; break;
	case 3: imageboxborder = false; hitboxborder = false; doublejumpboxborder = true; heightboxborder = false;  deleteboxborder = false; sizeboxborder = false; speedboxborder = false; break;
	case 4: imageboxborder = false; hitboxborder = false; doublejumpboxborder = false; heightboxborder = true; deleteboxborder = false; sizeboxborder = false; speedboxborder = false; break;
	case 5: imageboxborder = false; hitboxborder = false; doublejumpboxborder = false; heightboxborder = false; deleteboxborder = true; sizeboxborder = false; speedboxborder = false; break;
	case 6: imageboxborder = false; hitboxborder = false; doublejumpboxborder = false; heightboxborder = false; deleteboxborder = false; sizeboxborder = true; speedboxborder = false; break;
	case 7: imageboxborder = false; hitboxborder = false; doublejumpboxborder = false; heightboxborder = false; deleteboxborder = false; sizeboxborder = false; speedboxborder = true; break;
	}
}
void Playergui::HandleDottedSquareClick(int x, int y, int hitbox)
{;
cout << squareside << endl;
	vec2d originalxy(x, y);
	vector<vec2d> thepoints;
	if (hitbox)
		thepoints = Theplayer->Gethitbox()->AccessPoints();
	else
	{
		SDL_Rect tmp = Theplayer->GetPlayerRect();
		vec2d one(tmp.x,tmp.y);
		vec2d two(tmp.x + tmp.w, tmp.y);
		vec2d three(tmp.x + tmp.w, tmp.y + tmp.h);
		vec2d four(tmp.x,tmp.y + tmp.h);
		thepoints.push_back(one); thepoints.push_back(two); thepoints.push_back(three); thepoints.push_back(four);
	}
	if (x <= thepoints[1].x && x >= thepoints[0].x && y <= thepoints[0].y + 10 && y >= thepoints[0].y)
	{
		SetSquareSide(0);
	}
	else if (x <= thepoints[1].x && x >= thepoints[1].x - 10 && y <= thepoints[2].y && y >= thepoints[1].y)
	{
		SetSquareSide(1);
	}
	else if (x <= thepoints[1].x && x >= thepoints[0].x && y <= thepoints[2].y && y >= thepoints[2].y - 10)
	{
		SetSquareSide(2);
	}
	else if (x <= thepoints[0].x + 10 && x >= thepoints[0].x && y <= thepoints[2].y && y >= thepoints[0].y)
	{
		SetSquareSide(3);
	}
	else
	{
		SetSquareSide(-1);
	}
	x = originalxy.x;
	y = originalxy.y;
}
void Playergui::HandleDottedSquareMotion(int x, int y, int hitbox)
{
	int xchange = (x - mouseposition.x);
	int ychange = (y - mouseposition.y);
	if (squareside != -1)
	{
		if (hitbox)
		{
			if (squareside == 0)
			{
				Theplayer->SetYamount(Theplayer->GetYamount() + ychange);
			}
			if (squareside == 1)
			{
				Theplayer->SetXamount(Theplayer->GetXamount() - xchange);
			}
			if (squareside == 2)
			{
				Theplayer->SetYamount(Theplayer->GetYamount() - ychange);
			}
			if (squareside == 3)
			{
				Theplayer->SetXamount(Theplayer->GetXamount() + xchange);
			}
		}
		else
		{
			if (squareside == 0)
			{
				Theplayer->SetHeight(Theplayer->GetHeight() + ychange);
			}
			if (squareside == 1)
			{
				Theplayer->SetWidth(Theplayer->GetWidth() + xchange);
			}
			if (squareside == 2)
			{
				Theplayer->SetHeight(Theplayer->GetHeight() + ychange);
			}
			if (squareside == 3)
			{
				Theplayer->SetWidth(Theplayer->GetWidth() + xchange);
			}
		}
	}
}
void Playergui::SetSquareSide(int i)
{
	squareside = i;
}