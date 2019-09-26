#pragma once
#include "Rectangle.h"
class Shapegui
{
public:
	Shapegui();
	~Shapegui();
	Shapegui(Shapes * theshape);
	void ShapeguiInitialize();
	void MoveTrianglePoint(int x, int y);
	void SetTriangleSide(int x);
	void SetSquareSide(int x);
	void SetPolyLineSide(int x);
	void MoveXwithoutShape(double x);
	void MoveYwithoutShape(double y);
	void MoveX(double x);
	void MoveY(double y);
	void MoveYindex(double y, vector<int> indexs);
	void MoveXindex(double x, vector<int> indexs);
	void SetBorder(int x);
	void Print(SDL_Renderer* grender);
	void HandleDottedSquareClick(int x,int y);
	void HandleDottedSquareMotion(int x, int y);
	void HandleDeletedSquareClick(int x, int y, vector<Shapes*>& theshapes,int index);
	int GuiIndexClicked(int x, int y);
	bool clickedistanceleft(int x, int y);
	bool clickeddistanceright(int x, int y);
	bool clickedspeedleft(int x, int y);
	bool clickedspeedright(int x, int y);
	bool clickedbounceleft(int x, int y);
	bool clickedbounceright(int x, int y);

	void RotateMouse(int degrees, int& x, int& y, vec2d center);
	Rectangle arrowbox;
	Rectangle arrowboxborder;
	Rectangle dottedsquarebox;
	Rectangle dottedsquareboxborder;
	Rectangle numbersquarebox;
	Rectangle numbersquareboxborder;
	Rectangle rotatesquarebox;
	Rectangle rotatesquareboxborder;
	Rectangle rotatehelperbox;
	Rectangle deletesquarebox;
	Rectangle deletesquareboxborder;
	Rectangle scriptsquarebox;
	Rectangle scriptsquareboxborder;
	Rectangle zoominsquarebox;
	Rectangle zoominsquareboxborder;
	Rectangle damagesquarebox;
	Rectangle damagesquareboxborder;
	Rectangle lrarrowsquarebox;
	Rectangle lrarrowsquareboxborder;
	Rectangle udarrowsquarebox;
	Rectangle udarrowsquareboxborder;
	Rectangle speedsquarebox;
	Rectangle speedsquareboxborder;
	Rectangle speedsquareboxleft;
	Rectangle speedsquareboxright;
	Rectangle distancesquarebox;
	Rectangle distancesquareboxborder;
	Rectangle distancesquareboxleft;
	Rectangle distancesquareboxright;
	Rectangle bouncesquarebox;
	Rectangle bouncesquareboxborder;
	Rectangle bouncesquareboxleft;
	Rectangle bouncesquareboxright;
	bool arrowborder;
	bool dottedsquareborder;
	bool numbersquareborder;
	bool rotatesquareborder;
	bool deletesquareborder;
	bool scriptsquareborder;
	bool zoominsquareborder;
	bool damagesquareborder;
	bool lrarrrowsquareborder;
	bool udarrowsquareborder;
	bool distancesquareborder;
	bool speedsquareborder;
	bool bouncesquareborder;
	bool holddownclick;
	int squareside;
	int triangleside;
	int polylineside;
	vec2d mouseposition;
	Shapes * guishape;
};
Shapegui::Shapegui()
{

}
Shapegui::~Shapegui()
{
	guishape = 0;
}
void Shapegui::ShapeguiInitialize()
{

}
Shapegui::Shapegui(Shapes * theshape)
{
	extern SDL_Texture* fourarrowbox;
	extern SDL_Texture* dottedbox;
	extern SDL_Texture* numberbox;
	extern SDL_Texture* rotatebox;
	extern SDL_Texture* rotatezero;
	extern SDL_Texture* deletebox;
	extern SDL_Texture* scriptbox;
	extern SDL_Texture* zoomin;
	extern SDL_Texture* copybox;
	extern SDL_Texture* damageicon;
	extern SDL_Texture* lrarrows;
	extern SDL_Texture* udarrows;
	extern SDL_Texture* speedicon;
	extern SDL_Texture* distanceicon;
	extern SDL_Texture* bounceicon;
	triangleside = 0;
	squareside = 0;
	polylineside = 0;
	holddownclick = false;
	arrowborder = false;
	dottedsquareborder = false;
	numbersquareborder = false;
	rotatesquareborder = false;
	deletesquareborder = false;
	scriptsquareborder = false;
	zoominsquareborder = false;
	damagesquareborder = false;
	lrarrrowsquareborder = false;
	udarrowsquareborder = false;
	distancesquareborder = false;
	speedsquareborder = false;
	bouncesquareborder = false;
	int x = 25;
	int y = 25;
	guishape = theshape;
	vector<vec2d> tmppoints = theshape->AccessPoints();
	if (theshape->GetShapeType() == TRIANGLE)
	{
		arrowbox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - 2 * y, x, y, fourarrowbox);
		arrowboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - 2 * y, x, y);
		dottedsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - 2 * y, x, y, dottedbox);
		dottedsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - 2 * y, x, y);
		numbersquarebox.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - 2 * y, x, y, copybox);
		numbersquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - 2 * y, x, y);
		rotatesquarebox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - 2 * y, x, y, rotatebox);
		rotatesquareboxborder.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - 2 * y, x, y);
		rotatehelperbox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - (2 * y) - y, x + 15, y, rotatezero);
		deletesquarebox.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - 2 * y, x, y, deletebox);
		deletesquareboxborder.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - 2 * y, x, y);
		scriptsquarebox.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - 2 * y, x, y, scriptbox);
		scriptsquareboxborder.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - 2 * y, x, y);
		zoominsquarebox.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - 2 * y, x, y, zoomin);
		zoominsquareboxborder.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - 2 * y, x, y);
		damagesquarebox.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - 2 * y, x, y, damageicon);
		damagesquareboxborder.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - 2 * y, x, y);
		lrarrowsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y) - y, x, y, lrarrows);
		lrarrowsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y)-y, x, y);
		udarrowsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y) - y, x, y, udarrows);
		udarrowsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y) - y, x, y);
		speedsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y) - 2*y, x, y, speedicon);
		speedsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y) - 2*y, x, y);
		speedsquareboxleft.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y) - 2 * y, x/2, y);
		speedsquareboxright.RectangleInitialize(tmppoints[0].x + (x / 2), tmppoints[0].y - (2 * y) - 2 * y, x / 2, y);
		distancesquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y) - 2*y, x, y, distanceicon);
		distancesquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y) - 2*y, x, y);
		distancesquareboxleft.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y) - 2 * y, x / 2, y);
		distancesquareboxright.RectangleInitialize(tmppoints[0].x + x + (x/2), tmppoints[0].y - (2 * y) - 2 * y, x/2, y);
		bouncesquarebox.RectangleInitialize(tmppoints[0].x + 2*x, tmppoints[0].y - (2 * y) - 2 * y, x, y, bounceicon);
		bouncesquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (2 * y) - 2 * y, x, y);
		bouncesquareboxleft.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (2 * y) - 2 * y, x / 2, y);
		bouncesquareboxright.RectangleInitialize(tmppoints[0].x + 2 * x + (x / 2), tmppoints[0].y - (2 * y) - 2 * y, x / 2, y);
	}
	if (theshape->GetShapeType() == CIRCLE)
	{
		double theradius = theshape->GetCircleRadiusOutside();
		arrowbox.RectangleInitialize(tmppoints[0].x- theradius, tmppoints[0].y - theradius - y, x, y, fourarrowbox);
		arrowboxborder.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - y, x, y);
		dottedsquarebox.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - y, x, y, dottedbox);
		dottedsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - y, x, y);
		numbersquarebox.RectangleInitialize(tmppoints[0].x - theradius + 2 * x, tmppoints[0].y - theradius - y, x, y, copybox);
		numbersquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 2 * x, tmppoints[0].y - theradius - y, x, y);
		rotatesquarebox.RectangleInitialize(tmppoints[0].x - theradius + 3 * x, tmppoints[0].y - theradius - y, x, y, rotatebox);
		rotatesquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 3 * x, tmppoints[0].y - theradius - y, x, y);
		rotatehelperbox.RectangleInitialize(tmppoints[0].x - theradius + 3 * x, tmppoints[0].y - theradius - (2 * y), x + 15, y, rotatezero);
		deletesquarebox.RectangleInitialize(tmppoints[0].x - theradius + 4 * x, tmppoints[0].y - theradius - y, x, y, deletebox);
		deletesquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 4 * x, tmppoints[0].y - theradius - y, x, y);
		scriptsquarebox.RectangleInitialize(tmppoints[0].x - theradius + 5 * x, tmppoints[0].y - theradius - y, x, y, scriptbox);
		scriptsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 5 * x, tmppoints[0].y - theradius - y, x, y);
		zoominsquarebox.RectangleInitialize(tmppoints[0].x - theradius + 6 * x, tmppoints[0].y - theradius - y, x, y, zoomin);
		zoominsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 6 * x, tmppoints[0].y - theradius - y, x, y);
		damagesquarebox.RectangleInitialize(tmppoints[0].x - theradius + 7 * x, tmppoints[0].y - theradius - y, x, y, damageicon);
		damagesquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 7 * x, tmppoints[0].y - theradius - y, x, y);
		
		lrarrowsquarebox.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - (2 * y), x, y, lrarrows);
		lrarrowsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - (2 * y), x, y);
		udarrowsquarebox.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - (2 * y), x, y, udarrows);
		udarrowsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - (2 * y), x, y);
		speedsquarebox.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - (3 * y), x, y, speedicon);
		speedsquareboxborder.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - (3 * y), x, y);
		speedsquareboxleft.RectangleInitialize(tmppoints[0].x - theradius, tmppoints[0].y - theradius - (3 * y), x / 2, y);
		speedsquareboxright.RectangleInitialize(tmppoints[0].x - theradius + (x / 2), tmppoints[0].y - theradius - (3 * y), x / 2, y);
		distancesquarebox.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - (3 * y), x, y, distanceicon);
		distancesquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - (3 * y), x, y);
		distancesquareboxleft.RectangleInitialize(tmppoints[0].x - theradius + x, tmppoints[0].y - theradius - (3 * y), x / 2, y);
		distancesquareboxright.RectangleInitialize(tmppoints[0].x - theradius + x + (x / 2), tmppoints[0].y - theradius - (3 * y), x / 2, y);
		bouncesquarebox.RectangleInitialize(tmppoints[0].x - theradius + 2 * x, tmppoints[0].y - theradius - (3 * y), x, y, bounceicon);
		bouncesquareboxborder.RectangleInitialize(tmppoints[0].x - theradius + 2*x, tmppoints[0].y - theradius - (3 * y), x, y);
		bouncesquareboxleft.RectangleInitialize(tmppoints[0].x - theradius + 2 * x, tmppoints[0].y - theradius - (3 * y), x / 2, y);
		bouncesquareboxright.RectangleInitialize(tmppoints[0].x - theradius + 2 * x + (x / 2), tmppoints[0].y - theradius - (3 * y), x / 2, y);
	}
	if (theshape->GetShapeType() == RECTANGLE)
	{
		arrowbox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - y, x, y, fourarrowbox);
		arrowboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - y, x, y);
		dottedsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - y, x, y, dottedbox);
		dottedsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - y, x, y);
		numbersquarebox.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - y, x, y, copybox);
		numbersquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - y, x, y);
		rotatesquarebox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - y, x, y, rotatebox);
		rotatesquareboxborder.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - y, x, y);
		rotatehelperbox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - (2 * y), x + 15, y, rotatezero);
		deletesquarebox.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - y, x, y, deletebox);
		deletesquareboxborder.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - y, x, y);
		scriptsquarebox.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - y, x, y, scriptbox);
		scriptsquareboxborder.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - y, x, y);
		zoominsquarebox.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - y, x, y, zoomin);
		zoominsquareboxborder.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - y, x, y);
		damagesquarebox.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - y, x, y, damageicon);
		damagesquareboxborder.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - y, x, y);
		lrarrowsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y), x, y, lrarrows);
		lrarrowsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y), x, y);
		udarrowsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y), x, y, udarrows);
		udarrowsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y), x, y);
		speedsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x, y, speedicon);
		speedsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x, y);
		speedsquareboxleft.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x/2, y);
		speedsquareboxright.RectangleInitialize(tmppoints[0].x + (x/2), tmppoints[0].y - (3 * y), x/2, y);
		distancesquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x, y, distanceicon);
		distancesquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x, y);
		distancesquareboxleft.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x/2, y);
		distancesquareboxright.RectangleInitialize(tmppoints[0].x + x+ (x/2), tmppoints[0].y - (3 * y), x/2, y);
		bouncesquarebox.RectangleInitialize(tmppoints[0].x + 2*x, tmppoints[0].y - (3 * y), x, y, bounceicon);
		bouncesquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (3 * y), x, y);
		bouncesquareboxleft.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (3 * y), x / 2, y);
		bouncesquareboxright.RectangleInitialize(tmppoints[0].x + 2 * x + (x / 2), tmppoints[0].y - (3 * y), x / 2, y);
	}
	if (theshape->GetShapeType() == POLYLINE)
	{
		arrowbox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - y, x, y, fourarrowbox);
		arrowboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - y, x, y);
		dottedsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - y, x, y, dottedbox);
		dottedsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - y, x, y);
		numbersquarebox.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - y, x, y, copybox);
		numbersquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - y, x, y);
		rotatesquarebox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - y, x, y, rotatebox);
		rotatesquareboxborder.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - y, x, y);
		rotatehelperbox.RectangleInitialize(tmppoints[0].x + 3 * x, tmppoints[0].y - (2 * y), x + 15, y, rotatezero);
		deletesquarebox.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - y, x, y, deletebox);
		deletesquareboxborder.RectangleInitialize(tmppoints[0].x + 4 * x, tmppoints[0].y - y, x, y);
		scriptsquarebox.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - y, x, y, scriptbox);
		scriptsquareboxborder.RectangleInitialize(tmppoints[0].x + 5 * x, tmppoints[0].y - y, x, y);
		zoominsquarebox.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - y, x, y, zoomin);
		zoominsquareboxborder.RectangleInitialize(tmppoints[0].x + 6 * x, tmppoints[0].y - y, x, y);
		damagesquarebox.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - y, x, y, damageicon);
		damagesquareboxborder.RectangleInitialize(tmppoints[0].x + 7 * x, tmppoints[0].y - y, x, y);
		lrarrowsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y), x, y, lrarrows);
		lrarrowsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (2 * y), x, y);
		udarrowsquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y), x, y, udarrows);
		udarrowsquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (2 * y), x, y);
		speedsquarebox.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x, y, speedicon);
		speedsquareboxborder.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x, y);
		speedsquareboxleft.RectangleInitialize(tmppoints[0].x, tmppoints[0].y - (3 * y), x / 2, y);
		speedsquareboxright.RectangleInitialize(tmppoints[0].x + (x / 2), tmppoints[0].y - (3 * y), x / 2, y);
		distancesquarebox.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x, y, distanceicon);
		distancesquareboxborder.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x, y);
		distancesquareboxleft.RectangleInitialize(tmppoints[0].x + x, tmppoints[0].y - (3 * y), x / 2, y);
		distancesquareboxright.RectangleInitialize(tmppoints[0].x + x + (x / 2), tmppoints[0].y - (3 * y), x / 2, y);
		bouncesquarebox.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (3 * y), x, y, bounceicon);
		bouncesquareboxborder.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (3 * y), x, y);
		bouncesquareboxleft.RectangleInitialize(tmppoints[0].x + 2 * x, tmppoints[0].y - (3 * y), x / 2, y);
		bouncesquareboxright.RectangleInitialize(tmppoints[0].x + 2 * x + (x / 2), tmppoints[0].y - (3 * y), x / 2, y);
	}
}
void Shapegui::MoveTrianglePoint(int x, int y)
{
	if (triangleside != -1)
	{
		guishape->MoveXpointindex(x, triangleside);
		guishape->MoveYpointindex(y, triangleside);
	}
}
void Shapegui::SetTriangleSide(int x)
{
	triangleside = x;
}
void Shapegui::SetSquareSide(int x)
{
	squareside = x;
}
void Shapegui::SetPolyLineSide(int x)
{
	polylineside = x;
}
void Shapegui::MoveXwithoutShape(double x)
{
	arrowbox.MoveX(x);
	arrowboxborder.MoveX(x);
	dottedsquarebox.MoveX(x);
	dottedsquareboxborder.MoveX(x);
	numbersquarebox.MoveX(x);
	numbersquareboxborder.MoveX(x);
	rotatehelperbox.MoveX(x);
	rotatesquarebox.MoveX(x);
	rotatesquareboxborder.MoveX(x);
	deletesquarebox.MoveX(x);
	deletesquareboxborder.MoveX(x);
	scriptsquarebox.MoveX(x);
	scriptsquareboxborder.MoveX(x);
	zoominsquarebox.MoveX(x);
	zoominsquareboxborder.MoveX(x);
	damagesquarebox.MoveX(x);
	damagesquareboxborder.MoveX(x);
	lrarrowsquarebox.MoveX(x);
	lrarrowsquareboxborder.MoveX(x);
	udarrowsquarebox.MoveX(x);
	udarrowsquareboxborder.MoveX(x);
	speedsquarebox.MoveX(x);
	speedsquareboxborder.MoveX(x);
	distancesquarebox.MoveX(x);
	distancesquareboxborder.MoveX(x);
	distancesquareboxleft.MoveX(x);
	distancesquareboxright.MoveX(x);
	speedsquareboxleft.MoveX(x);
	speedsquareboxright.MoveX(x);
	bouncesquarebox.MoveX(x);
	bouncesquareboxborder.MoveX(x);
	bouncesquareboxleft.MoveX(x);
	bouncesquareboxright.MoveX(x);
	
}
void Shapegui::MoveYwithoutShape(double y)
{
	arrowbox.MoveY(y);
	arrowboxborder.MoveY(y);
	dottedsquarebox.MoveY(y);
	dottedsquareboxborder.MoveY(y);
	numbersquarebox.MoveY(y);
	numbersquareboxborder.MoveY(y);
	rotatesquarebox.MoveY(y);
	rotatesquareboxborder.MoveY(y);
	rotatehelperbox.MoveY(y);
	deletesquarebox.MoveY(y);
	deletesquareboxborder.MoveY(y);
	scriptsquarebox.MoveY(y);
	scriptsquareboxborder.MoveY(y);
	zoominsquarebox.MoveY(y);
	zoominsquareboxborder.MoveY(y);
	damagesquarebox.MoveY(y);
	damagesquareboxborder.MoveY(y);
	lrarrowsquarebox.MoveY(y);
	lrarrowsquareboxborder.MoveY(y);
	udarrowsquarebox.MoveY(y);
	udarrowsquareboxborder.MoveY(y);
	speedsquarebox.MoveY(y);
	speedsquareboxborder.MoveY(y);
	distancesquarebox.MoveY(y);
	distancesquareboxborder.MoveY(y);
	distancesquareboxleft.MoveY(y);
	distancesquareboxright.MoveY(y);
	speedsquareboxleft.MoveY(y);
	speedsquareboxright.MoveY(y);
	bouncesquarebox.MoveY(y);
	bouncesquareboxborder.MoveY(y);
	bouncesquareboxleft.MoveY(y);
	bouncesquareboxright.MoveY(y);
}
void Shapegui::MoveX(double x)
{
	guishape->MoveX(x);
	arrowbox.MoveX(x,0,0);
	arrowboxborder.MoveX(x, 0, 0);
	dottedsquarebox.MoveX(x, 0, 0);
	dottedsquareboxborder.MoveX(x, 0, 0);
	numbersquarebox.MoveX(x, 0, 0);
	numbersquareboxborder.MoveX(x, 0, 0);
	rotatehelperbox.MoveX(x, 0, 0);
	rotatesquarebox.MoveX(x, 0, 0);
	rotatesquareboxborder.MoveX(x, 0, 0);
	deletesquarebox.MoveX(x, 0, 0);
	deletesquareboxborder.MoveX(x, 0, 0);
	scriptsquarebox.MoveX(x, 0, 0);
	scriptsquareboxborder.MoveX(x, 0, 0);
	zoominsquarebox.MoveX(x, 0, 0);
	zoominsquareboxborder.MoveX(x, 0, 0);
	damagesquarebox.MoveX(x, 0, 0);
	damagesquareboxborder.MoveX(x, 0, 0);
	lrarrowsquarebox.MoveX(x, 0, 0);
	lrarrowsquareboxborder.MoveX(x, 0, 0);
	udarrowsquarebox.MoveX(x, 0, 0);
	udarrowsquareboxborder.MoveX(x, 0, 0);
	speedsquarebox.MoveX(x, 0, 0);
	speedsquareboxborder.MoveX(x, 0, 0);
	distancesquarebox.MoveX(x, 0, 0);
	distancesquareboxborder.MoveX(x, 0, 0);
	distancesquareboxleft.MoveX(x, 0, 0);
	distancesquareboxright.MoveX(x, 0, 0);
	speedsquareboxleft.MoveX(x, 0, 0);
	speedsquareboxright.MoveX(x, 0, 0);
	bouncesquarebox.MoveX(x, 0, 0);
	bouncesquareboxborder.MoveX(x, 0, 0);
	bouncesquareboxleft.MoveX(x, 0, 0);
	bouncesquareboxright.MoveX(x, 0, 0);
}
void Shapegui::MoveY(double y)
{
	guishape->MoveY(y);
	arrowbox.MoveY(y,0,0);
	arrowboxborder.MoveY(y, 0, 0);
	dottedsquarebox.MoveY(y, 0, 0);
	dottedsquareboxborder.MoveY(y, 0, 0);
	numbersquarebox.MoveY(y, 0, 0);
	numbersquareboxborder.MoveY(y, 0, 0);
	rotatesquarebox.MoveY(y, 0, 0);
	rotatesquareboxborder.MoveY(y, 0, 0);
	rotatehelperbox.MoveY(y, 0, 0);
	deletesquarebox.MoveY(y, 0, 0);
	deletesquareboxborder.MoveY(y, 0, 0);
	scriptsquarebox.MoveY(y, 0, 0);
	scriptsquareboxborder.MoveY(y, 0, 0);
	zoominsquarebox.MoveY(y, 0, 0);
	zoominsquareboxborder.MoveY(y, 0, 0);
	damagesquarebox.MoveY(y, 0, 0);
	damagesquareboxborder.MoveY(y, 0, 0);
	lrarrowsquarebox.MoveY(y, 0, 0);
	lrarrowsquareboxborder.MoveY(y, 0, 0);
	udarrowsquarebox.MoveY(y, 0, 0);
	udarrowsquareboxborder.MoveY(y, 0, 0);
	speedsquarebox.MoveY(y, 0, 0);
	speedsquareboxborder.MoveY(y, 0, 0);
	distancesquarebox.MoveY(y, 0, 0);
	distancesquareboxborder.MoveY(y, 0, 0);
	distancesquareboxleft.MoveY(y, 0, 0);
	distancesquareboxright.MoveY(y, 0, 0);
	speedsquareboxleft.MoveY(y, 0, 0);
	speedsquareboxright.MoveY(y, 0, 0);
	bouncesquarebox.MoveY(y, 0, 0);
	bouncesquareboxborder.MoveY(y, 0, 0);
	bouncesquareboxleft.MoveY(y, 0, 0);
	bouncesquareboxright.MoveY(y, 0, 0);
}
void Shapegui::MoveYindex(double y, vector<int> indexs)
{
	for (int i = 0; i < indexs.size(); i++)
	{
		guishape->MoveYpointindex(y, indexs[i]);
	}
	vector<vec2d> thepoints = guishape->AccessPoints();
	if (thepoints[0].y >= thepoints[2].y - 1)
	{
		for (int i = 0; i < indexs.size(); i++)
		{
			guishape->MoveYpointindex(-y, indexs[i]);
		}
	}
}
void Shapegui::MoveXindex(double x, vector<int> indexs)
{
	for (int i = 0; i < indexs.size(); i++)
	{
		guishape->MoveXpointindex(x, indexs[i]);
	}
	vector<vec2d> thepoints = guishape->AccessPoints();
	if (thepoints[0].x >= thepoints[1].x - 1)
	{
		for (int i = 0; i < indexs.size(); i++)
		{
			guishape->MoveXpointindex(-x, indexs[i]);
		}
	}
}
void Shapegui::SetBorder(int x)
{
	rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false;
	switch (x)
	{
	case 1: arrowborder = true; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = false;	lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 2: arrowborder = false; dottedsquareborder = true; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 3: arrowborder = false; dottedsquareborder = false; numbersquareborder = true; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 4: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = true; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 5: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = true; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 6: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 8: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = true; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 9: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = false; zoominsquareborder = false; damagesquareborder = true; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 10: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = true; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 11: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = true; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = false; break;
	case 12: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = true; speedsquareborder = false; bouncesquareborder = false; break;
	case 13: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = true; bouncesquareborder = false; break;
	case 14: arrowborder = false; dottedsquareborder = false; numbersquareborder = false; rotatesquareborder = false; deletesquareborder = false; scriptsquareborder = true; zoominsquareborder = false; damagesquareborder = false; lrarrrowsquareborder = false; udarrowsquareborder = false; distancesquareborder = false; speedsquareborder = false; bouncesquareborder = true; break;
	}
}
void Shapegui::Print(SDL_Renderer* grender)
{
	arrowbox.PrintTexture(grender);
	dottedsquarebox.PrintTexture(grender);
	numbersquarebox.PrintTexture(grender);
	rotatesquarebox.PrintTexture(grender);
	deletesquarebox.PrintTexture(grender);
	scriptsquarebox.PrintTexture(grender);
	zoominsquarebox.PrintTexture(grender);
	damagesquarebox.PrintTexture(grender);
	if (arrowborder)
		arrowboxborder.Print(grender);
	if (dottedsquareborder)
		dottedsquareboxborder.Print(grender);
	if (numbersquareborder)
		numbersquareboxborder.Print(grender);
	if (rotatesquareborder)
	{
		rotatesquareboxborder.Print(grender);
		rotatehelperbox.PrintTexture(grender);
	}
	if (deletesquareborder)
		deletesquareboxborder.Print(grender);
	if (scriptsquareborder)
	{
		lrarrowsquarebox.PrintTexture(grender);
		udarrowsquarebox.PrintTexture(grender);
		speedsquarebox.PrintTexture(grender);
		distancesquarebox.PrintTexture(grender);
		scriptsquareboxborder.Print(grender);
		bouncesquarebox.PrintTexture(grender);
	}
	if (zoominsquareborder)
		zoominsquareboxborder.Print(grender);
	if (damagesquareborder)
		damagesquareboxborder.Print(grender);
	if(lrarrrowsquareborder)
		lrarrowsquareboxborder.Print(grender);
	if(udarrowsquareborder)
		udarrowsquareboxborder.Print(grender);
	if(speedsquareborder)
		speedsquareboxborder.Print(grender);
	if(distancesquareborder)
		distancesquareboxborder.Print(grender);
	if (bouncesquareborder)
		bouncesquareboxborder.Print(grender);
}
void Shapegui::HandleDeletedSquareClick(int x, int y,vector<Shapes*>& theshapes,int index)
{
	int guiindex = -1;
	guiindex = GuiIndexClicked(x, y);
	if (guiindex == -1)
	{
		Shapes * ptr = theshapes[index];
		theshapes.erase(theshapes.begin() + index);
		delete ptr;
	}
}
void Shapegui::HandleDottedSquareMotion(int x, int y)
{
	double xchange = x - mouseposition.x;
	double ychange = y - mouseposition.y;
	if (guishape->GetShapeType() == POLYLINE)
	{
		guishape->MoveXpointindex(xchange, polylineside);
		guishape->MoveYpointindex(ychange, polylineside);
	}
	if (guishape->GetShapeType() == TRIANGLE)
	{
		MoveTrianglePoint(xchange, ychange);
	}
	if (guishape->GetShapeType() == CIRCLE)
	{
		
	}
	if (guishape->GetShapeType() == RECTANGLE)
	{
		if (squareside != -1)
		{
			vector<vec2d> thepoints = guishape->AccessPoints();
			int xcountersmall = 0;
			int ycountersmall = 0;
			int theindexx = 0;
			for (int i = 0; i < 4; i++)
			{
				if (squareside != i)
				{
					if (thepoints[squareside].x < thepoints[i].x)
						xcountersmall++;
					if (thepoints[squareside].y < thepoints[i].y)
						ycountersmall++;
				}
			}
			if (xcountersmall >= 2)
			{
				if (ycountersmall >= 2)
					theindexx = 0;
				else
					theindexx = 3;
			}
			else
			{
				if (ycountersmall >= 2)
					theindexx = 1;
				else
					theindexx = 2;
			}
			double rotateback = guishape->ResetAngle();
			switch (squareside)
			{
			case 0:
				switch (theindexx)
				{
				case 0: theindexx = ychange; break;
				case 1: theindexx = -xchange; break;
				case 2: theindexx = -ychange; break;
				case 3: theindexx = xchange; break;
				}
				guishape->MoveYpointindex(theindexx, 0, 0); guishape->MoveYpointindex(theindexx, 1, 0); break;
			case 1:
				switch (theindexx)
				{
				case 0: theindexx = -ychange; break;
				case 1: theindexx = xchange; break;
				case 2: theindexx = ychange; break;
				case 3: theindexx = -xchange; break;
				}
				guishape->MoveXpointindex(theindexx, 1, 0); guishape->MoveXpointindex(theindexx, 2, 0); break;
			case 2:
				switch (theindexx)
				{
				case 0: theindexx = -ychange; break;
				case 1: theindexx = xchange; break;
				case 2: theindexx = ychange; break;
				case 3: theindexx = -xchange; break;
				}
				guishape->MoveYpointindex(theindexx, 2, 0); guishape->MoveYpointindex(theindexx, 3, 0); break;
			case 3:
				switch (theindexx)
				{
				case 0: theindexx = ychange; break;
				case 1: theindexx = -xchange; break;
				case 2: theindexx = -ychange; break;
				case 3: theindexx = xchange; break;
				}
				guishape->MoveXpointindex(theindexx, 3, 0); guishape->MoveXpointindex(theindexx, 0, 0); break;
			}
			guishape->Rotate(rotateback);
			guishape->UpdateCircle();
		}
	}
}
void Shapegui::HandleDottedSquareClick(int x,int y)
{
	vector<vec2d> thepoints = guishape->AccessPoints();
	if (guishape->GetShapeType() == POLYLINE)
	{
		int radius = 10;
		for (int i = 0; i < thepoints.size(); i++)
		{
			if (sqrt(pow(thepoints[i].x - x, 2) + pow(thepoints[i].y - y, 2)) / 2 < radius)
			{
				SetPolyLineSide(i);
			}
		}

	}
	if (guishape->GetShapeType() == TRIANGLE)
	{
		int radius = 10;
		if (sqrt(pow(thepoints[0].x - x, 2) + pow(thepoints[0].y - y, 2)) / 2 < radius)
		{
			SetTriangleSide(0);
		}
		else if (sqrt(pow(thepoints[1].x - x, 2) + pow(thepoints[1].y - y, 2)) / 2 < radius)
		{
			SetTriangleSide(1);
		}
		else if (sqrt(pow(thepoints[2].x - x, 2) + pow(thepoints[2].y - y, 2)) / 2 < radius)
		{
			SetTriangleSide(2);
		}
		else
		{
			SetTriangleSide(-1);
		}

	}
	if (guishape->GetShapeType() == CIRCLE)
	{

	}
	if (guishape->GetShapeType() == RECTANGLE)//***generalize this so it just knows the line you clicked and its slope
	{
		double rotateback = guishape->ResetAngle();
		vec2d originalxy(x, y);
		RotateMouse(-rotateback, x, y, guishape->GetOuterCircleCenter());
		thepoints = guishape->AccessPoints();
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
		guishape->Rotate(rotateback);
		x = originalxy.x;
		y = originalxy.y;
	}
}
int Shapegui::GuiIndexClicked(int x, int y)
{
	vector<vec2d>arrowpoints = arrowbox.AccessPoints();
	vector<vec2d>boxpoints = dottedsquarebox.AccessPoints();
	vector<vec2d>numberbox = numbersquarebox.AccessPoints();
	vector<vec2d>rotatebox = rotatesquarebox.AccessPoints();
	vector<vec2d>rotatehelperboxz = rotatehelperbox.AccessPoints();
	vector<vec2d>deletebox = deletesquarebox.AccessPoints();
	vector<vec2d>scriptbox = scriptsquarebox.AccessPoints();
	vector<vec2d>zoominbox = zoominsquarebox.AccessPoints();
	vector<vec2d>damagebox = damagesquarebox.AccessPoints();
	vector<vec2d> lrarrowbox = lrarrowsquarebox.AccessPoints();
	vector<vec2d> udarrowbox = udarrowsquarebox.AccessPoints();
	vector<vec2d> speedbox = speedsquarebox.AccessPoints();
	vector<vec2d> distancebox = distancesquarebox.AccessPoints();
	vector<vec2d> bouncebox = bouncesquarebox.AccessPoints();
	if (x <= arrowpoints[1].x && x >= arrowpoints[0].x && y <= arrowpoints[3].y && y >= arrowpoints[0].y)
	{
		return 1;
	}
	else if (x <= boxpoints[1].x && x >= boxpoints[0].x && y <= boxpoints[3].y && y >= boxpoints[0].y)
	{
		return 2;
	}
	else if (x <= numberbox[1].x && x >= numberbox[0].x && y <= numberbox[3].y && y >= numberbox[0].y)
	{
		return 3;
	}
	else if (x <= rotatebox[1].x && x >= rotatebox[0].x && y <= rotatebox[3].y && y >= rotatebox[0].y)
	{
		return 4;
	}
	else if (x <= deletebox[1].x && x >= deletebox[0].x && y <= deletebox[3].y && y >= deletebox[0].y)
	{
		return 5;
	}
	else if (x <= scriptbox[1].x && x >= scriptbox[0].x && y <= scriptbox[3].y && y >= scriptbox[0].y)
	{
		return 6;
	}
	else if (x <= rotatehelperboxz[1].x && x >= rotatehelperboxz[0].x && y <= rotatehelperboxz[3].y && y >= rotatehelperboxz[0].y)
	{
		return 7;
	}
	else if (x <= zoominbox[1].x && x >= zoominbox[0].x && y <= zoominbox[3].y && y >= zoominbox[0].y)
	{
		return 8;
	}
	else if (x <= damagebox[1].x && x >= damagebox[0].x && y <= damagebox[3].y && y >= damagebox[0].y)
	{
		return 9;
	}
	if (scriptsquareborder)
	{
	if (x <= lrarrowbox[1].x && x >= lrarrowbox[0].x && y <= lrarrowbox[3].y && y >= lrarrowbox[0].y)
	{
		return 10;
	}
	else if (x <= udarrowbox[1].x && x >= udarrowbox[0].x && y <= udarrowbox[3].y && y >= udarrowbox[0].y)
	{
		return 11;
	}
	else if (x <= speedbox[1].x && x >= speedbox[0].x && y <= speedbox[3].y && y >= speedbox[0].y)
	{
		return 13;
	}
	else if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return 12;
	}
	else if (x <= bouncebox[1].x && x >= bouncebox[0].x && y <= bouncebox[3].y && y >= bouncebox[0].y)
	{
		return 14;
	}
	}
	return -1;
}
bool Shapegui::clickedistanceleft(int x,int y)
{
	vector<vec2d> distancebox = distancesquareboxleft.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
bool Shapegui::clickeddistanceright(int x, int y)
{
	vector<vec2d> distancebox = distancesquareboxright.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
bool Shapegui::clickedspeedleft(int x, int y)
{
	vector<vec2d> distancebox = speedsquareboxleft.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
bool Shapegui::clickedspeedright(int x, int y)
{
	vector<vec2d> distancebox = speedsquareboxright.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
bool Shapegui::clickedbounceleft(int x, int y)
{
	vector<vec2d> distancebox = bouncesquareboxleft.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
bool Shapegui::clickedbounceright(int x, int y)
{
	vector<vec2d> distancebox = bouncesquareboxright.AccessPoints();
	if (x <= distancebox[1].x && x >= distancebox[0].x && y <= distancebox[3].y && y >= distancebox[0].y)
	{
		return true;
	}
	return false;
}
void Shapegui::RotateMouse(int degrees, int& x, int& y, vec2d center)
{
	vec2d lol(x, y);
	mat2x2 rotatematrix;
	rotatematrix.column1x = cos(degrees*3.14 / 180);
	rotatematrix.column1y = sin(degrees*3.14 / 180);
	rotatematrix.column2x = -sin(degrees*3.14 / 180);
	rotatematrix.column2y = cos(degrees*3.14 / 180);
	lol = rotatematrix.matrixvectorMult(lol, center.x, center.y);
	x = lol.x;
	y = lol.y;
}