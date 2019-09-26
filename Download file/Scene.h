#pragma once
#include "Rectangle.h"
#include "PolyLine.h"
#include "CircleProjectile.h"
#include "Player.h"
#include "Shapegui.h"
#include "Shapes.h"
#include "LevelMakergui.h"
#include "Playergui.h"

class Scene
{
public:
	Scene();
	Scene(Scene const& thescene);
	void SceneInitialize();
	~Scene();
	void PrintScene(SDL_Renderer* grender, Player theplayer, bool playermode = false);
	Shapegui* Accessshapegui();
	Playergui* AccessPlayergui();
	void AddRectangle(bool portal = false);
	void AddTriangle();
	void AddPolyLine();
	void AddCircle(int x = 150, int y = 100, int r = 50);
	void AddCircleProjectile(int x = 150, int y = 100, int r = 50);
	void AddDoubleJumper();
	void AddBouncer();
	void AddCheckpoint();
	void AddRectangleKnown(Rectangle*& ptr);
	void AddTriangleKnown(Triangle*& ptr);
	void AddPolyLineKnown(PolyLine*& ptr);
	void AddCircleKnown(Circle*& ptr);
	void AddCircleProjectileKnown(CircleProjectile*& ptr);
	void DeleteShape(int x, int y, int index);
	int ShapeIndexClicked(int x, int y);
	void changelevelmakerscenetexture(SDL_Texture* textz);
	void ShapeguiDelete();
	void ShapeguiCreate(int index);
	void PlayerguiCreate(Player* theplayer);
	void PlayerguiDelete();
	void ToggleDrag();
	void MoveShapes(double x, double y);
	void ZoomShapes(double x,int mx,int my);
	void ZoomShapeSolo(double x,int index);
	void RevertZoom();
	void RevertMove();
	void AddCopy(Shapes* theshape);
	vector<Shapes*>& AccessShapes();
	LevelMakergui* AccessLevelMakergui();
	void HandleShapeScript(SDL_Renderer* grender);//call every frame

private:
	vector<zoomedinreverter> zoomedininfo;
	vector<Shapes*> TheShapes;
	Shapegui* TheShapeGUI;
	Playergui* ThePlayerGUI;
	LevelMakergui TheLevelMakerGUI;
	Rectangle Reverter;
	float area(int x1, int y1, int x2, int y2, int x3, int y3);
	bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);
};
Scene::Scene(Scene const& thescene)
{
	*this = thescene;
}
Scene::Scene()
{
	extern SDL_Texture* gray;
	Reverter.RectangleInitialize(0, 0, 10, 10, gray);
	TheShapeGUI = 0;
	ThePlayerGUI = 0;
	TheLevelMakerGUI.LevelMakerguiInitialize();
	Rectangle * rect1ptr = new Rectangle(-100, 400, 1200, 100, gray);
	TheShapes.push_back(rect1ptr);
}
void Scene::SceneInitialize()
{
	extern SDL_Texture* gray;
	Reverter.RectangleInitialize(0, 0, 10, 10,gray);
	TheShapeGUI = 0;
	ThePlayerGUI = 0;
	TheLevelMakerGUI.LevelMakerguiInitialize();
	Rectangle * rect1ptr = new Rectangle(0, 400, 1000, 100,gray);
	TheShapes.push_back(rect1ptr);
}
Shapegui* Scene::Accessshapegui()
{
	return TheShapeGUI;
}
Playergui* Scene::AccessPlayergui()
{
	return ThePlayerGUI;
}
Scene::~Scene()
{
	zoomedininfo.clear();
	TheShapes.clear();
	TheShapeGUI = 0;
	ThePlayerGUI = 0;
}
void Scene::ShapeguiDelete()
{
	delete TheShapeGUI;
	TheShapeGUI = 0;
}
void Scene::ShapeguiCreate(int index)
{
	TheShapeGUI = new Shapegui(TheShapes[index]);
}
void Scene::PlayerguiCreate(Player * theplayer)
{
	ThePlayerGUI = new Playergui(theplayer);
}
void Scene::PlayerguiDelete()
{
	delete ThePlayerGUI;
	ThePlayerGUI = 0;
}
void Scene::PrintScene(SDL_Renderer* grender,Player theplayer,bool playermode)
{
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	//if the shape is in the screen boundaries print it
	int printcounter = 0;
	for (int i = 0; i < TheShapes.size(); i++)
	{
		vec2d center = TheShapes[i]->GetOuterCircleCenter();
		vec2d playercenter = theplayer.AccessCenter();
		vec2d screencenter; screencenter.x = SCREEN_WIDTH / 2; screencenter.y = SCREEN_HEIGHT / 2;
		double distance = sqrt(pow(center.x - playercenter.x, 2) + pow(center.y - playercenter.y, 2));
		double distancescreen = sqrt(pow(center.x - screencenter.x, 2) + pow(center.y - screencenter.y, 2));
		if (distancescreen < SCREEN_WIDTH*2)
		{
			printcounter++;
			if (TheShapes[i]->GetScriptTempDeath() != 1)
			{
				if (TheShapes[i]->GetShapeType() == RECTANGLE)
				{
					if ((TheShapes[i]->AccessTeleport() || TheShapes[i]->GetCheckpoint()))
					{
						if(!playermode)
							TheShapes[i]->PrintTexture(grender);
					}
					else
					{
						if (TheShapes[i]->GetTotalAmountRotated() != 0)
						{
							TheShapes[i]->Print(grender,150,150,150);
						}
						else
						{
							TheShapes[i]->PrintTexture(grender);
						}
					
					}
				}
				else if (TheShapes[i]->GetShapeType() == POLYLINE)
				{
					TheShapes[i]->Print(grender, 0, 0, 0);
					//TheShapes[i]->Print(grender);
				}
				else if (TheShapes[i]->GetShapeType() == TRIANGLE)
				{
					TheShapes[i]->Print(grender, 0, 0, 255);
					//TheShapes[i]->Print(grender);
				}
				else if (TheShapes[i]->GetShapeType() == CIRCLE)
				{
					if (TheShapes[i]->GetDoubleJumper())
					{
						TheShapes[i]->Print(grender);
					}
					else if (TheShapes[i]->GetBallSpawner())
					{
						TheShapes[i]->Print(grender, 0, 0, 255);
					}
					else
					{
						TheShapes[i]->PrintTexture(grender);
					}
					//TheShapes[i]->Print(grender);
				}
				TheShapes[i]->Rotate();
			}
		}
	}
	//cout << "amount of shapes printed: " << printcounter << endl;
	if (!playermode)
	{
		if (TheShapeGUI != 0)
			TheShapeGUI->Print(grender);
		if (ThePlayerGUI != 0)
			ThePlayerGUI->Print(grender);
		TheLevelMakerGUI.Print(grender);
	}
	//Reverter.Print(grender);
}
void Scene::AddCopy(Shapes* theshape)
{
	if (theshape->GetShapeType() == TRIANGLE)
	{
		vector<vec2d> thepoints = theshape->AccessPoints();
		Triangle* tmpptr = new Triangle(thepoints[0], thepoints[1], thepoints[2]);
		TheShapes.push_back(tmpptr);
	}
	if (theshape->GetShapeType() == RECTANGLE)
	{
		vector<vec2d> thepoints = theshape->AccessPoints();
		Rectangle* tmpptr = new Rectangle(thepoints);
		TheShapes.push_back(tmpptr);
	}
	if (theshape->GetShapeType() == CIRCLE)
	{
		vector<vec2d> thepoints = theshape->AccessPoints();
		Circle* tmpptr = new Circle(thepoints);
		TheShapes.push_back(tmpptr);
	}
	if (theshape->GetShapeType() == POLYLINE)
	{
		theshape->AddLine();
	}
}
void Scene::AddRectangleKnown(Rectangle*& ptr)
{
	TheShapes.push_back(ptr);
}
void Scene::AddTriangleKnown(Triangle*& ptr)
{
	TheShapes.push_back(ptr);
}
void Scene::AddPolyLineKnown(PolyLine*& ptr)
{
	TheShapes.push_back(ptr);
}
void Scene::AddCircleKnown(Circle*& ptr)
{
	TheShapes.push_back(ptr);
}
void Scene::AddCircleProjectileKnown(CircleProjectile*& ptr)
{
	TheShapes.push_back(ptr);
}
void Scene::AddRectangle(bool portal)
{
	extern SDL_Texture* portalicon;
	extern SDL_Texture* gray;
	vec2d lol(10, 10);
	vector<vec2d> sup;
	sup.push_back(lol);
	Rectangle* tmpptr;
	if (portal)
		tmpptr = new Rectangle(100, 100, 100, 100,portalicon);
	else
		tmpptr = new Rectangle(100, 100, 100, 100,gray);
	TheShapes.push_back(tmpptr);
}
void Scene::AddPolyLine()
{
	PolyLine* tmpptr = new PolyLine(100,100);
	TheShapes.push_back(tmpptr);
}
void Scene::AddCircle(int x, int y,int r)
{
	extern SDL_Texture* bluecircle;
	vec2d lol(x, y);
	Circle* tmpptr = new Circle(r, lol,bluecircle);
	TheShapes.push_back(tmpptr);
}
void Scene::AddCircleProjectile(int x, int y , int r)
{
	extern SDL_Texture* redcircle;
	vec2d lol(x, y);
	CircleProjectile* tmpptr = new CircleProjectile(r, lol, redcircle);
	TheShapes.push_back(tmpptr);
}
void Scene::AddDoubleJumper()
{
	AddCircleProjectile(150, 100, 10);
	int lastindex = AccessShapes().size() - 1;
	AccessShapes()[lastindex]->SetDoubleJumper(true);
}
void Scene::AddCheckpoint()
{
	Rectangle* tmpptr = new Rectangle(100, 100, 100, 100);
	TheShapes.push_back(tmpptr);
	int lastindex = AccessShapes().size() - 1;
	AccessShapes()[lastindex]->SetCheckpoint(true);
}
void Scene::AddBouncer()
{
	extern SDL_Texture* green;
	Rectangle* tmpptr = new Rectangle(100, 100, 100, 100,green);
	TheShapes.push_back(tmpptr);
	int lastindex = AccessShapes().size() - 1;
	AccessShapes()[lastindex]->SetBouncer(true);
}
void Scene::AddTriangle()
{
	vec2d one(100, 100);
	vec2d two(200, 0);
	vec2d three(300, 100);
	Triangle* tmpptr = new Triangle(one, two, three);
	TheShapes.push_back(tmpptr);
}
int Scene::ShapeIndexClicked(int x, int y)
{

	//if the disance from center is less than radius good
	for (int i = 0; i < TheShapes.size(); i++)
	{
		vector<vec2d> shapepoints = TheShapes[i]->AccessPoints();
		if (TheShapes[i]->GetShapeType() == RECTANGLE)
		{
			if (isInside(shapepoints[0].x, shapepoints[0].y, shapepoints[1].x, shapepoints[1].y, shapepoints[2].x, shapepoints[2].y, x, y) ||
				isInside(shapepoints[0].x, shapepoints[0].y, shapepoints[2].x, shapepoints[2].y, shapepoints[3].x, shapepoints[3].y, x, y))
			{
				return i;
			}
		}
		if (TheShapes[i]->GetShapeType() == TRIANGLE)
		{
			vector<vec2d> tmpoints = TheShapes[i]->AccessPoints();
			vec2d tmppoint(x, y);
			if (isInside(tmpoints[0].x, tmpoints[0].y, tmpoints[1].x, tmpoints[1].y, tmpoints[2].x, tmpoints[2].y, x, y))
			{
				return i;
			}
		}
		if (TheShapes[i]->GetShapeType() == POLYLINE)
		{
			vector<vec2d> tmpoints = TheShapes[i]->AccessPoints();
			for (int z = 0; z < tmpoints.size() - 1; z++)
			{
				double slope;
				if (tmpoints[z].x - tmpoints[z+ 1].x != 0)
					slope = (tmpoints[z].y - tmpoints[z + 1].y) / (tmpoints[z].x - tmpoints[z + 1].x);
				else
					slope = 0;
				double b1 = tmpoints[z].y - slope * tmpoints[z].x;
				int answer = slope * x + b1;
				if (answer>=y - 5 && answer <= y + 5)
				{
					return i;
				}
			}
		}
		if (TheShapes[i]->GetShapeType() == CIRCLE)
		{
			//take difference between point and center if its less than radius ur good
			double difference = sqrt(pow(x - TheShapes[i]->GetOuterCircleCenter().x, 2) + pow(y - TheShapes[i]->GetOuterCircleCenter().y, 2));
			if (abs(difference) <= TheShapes[i]->GetCircleRadiusOutside())
			{
				return i;
			}
		}
	}
	return -1;
}
void Scene::DeleteShape(int x, int y, int index)
{
	//TheShapeGUI->HandleDeletedSquareClick(x, y, TheShapes, index);
	Shapes * ptr = TheShapes[index];
	TheShapes.erase(TheShapes.begin() + index);
	delete ptr;
	ptr = 0;
}
vector<Shapes*>& Scene::AccessShapes()
{
	return TheShapes;
}
float Scene::area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}
bool Scene::isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
	/* Calculate area of triangle ABC */
	float A = area(x1, y1, x2, y2, x3, y3);

	/* Calculate area of triangle PBC */
	float A1 = area(x, y, x2, y2, x3, y3);

	/* Calculate area of triangle PAC */
	float A2 = area(x1, y1, x, y, x3, y3);

	/* Calculate area of triangle PAB */
	float A3 = area(x1, y1, x2, y2, x, y);

	/* Check if sum of A1, A2 and A3 is same as A */
	return (A == A1 + A2 + A3);
}
LevelMakergui* Scene::AccessLevelMakergui()
{
	return &TheLevelMakerGUI;
}
void Scene::changelevelmakerscenetexture(SDL_Texture* textz)
{
	TheLevelMakerGUI.ChangeSceneTexture(textz);
}
void Scene::ToggleDrag()
{
	TheLevelMakerGUI.ToggleDrag();
}
void Scene::MoveShapes(double x, double y)
{
	ShapeguiDelete();
	for (int i = 0; i < TheShapes.size(); i++)
	{
		TheShapes[i]->MoveX(x,1,1);
		TheShapes[i]->MoveY(y,1,1);
	}
	Reverter.MoveX(x, 1, 1);
	Reverter.MoveY(y, 1, 1);
}
void Scene::ZoomShapes(double x, int mx, int my)
{
	ShapeguiDelete();
	double value = .9;
	if (x >= 0)
		value = 1.1;
	for (int i = 0; i < TheShapes.size(); i++)
	{
		//TheShapes[i]->Zoomnomouse(value);
		TheShapes[i]->Zoomtomouse(value,mx,my);
	}
	Reverter.Zoomtomouse(value, mx, my);
	zoomedinreverter tmpinfo;
	tmpinfo.amount = value; tmpinfo.xmouse = mx; tmpinfo.ymouse = my;
	zoomedininfo.push_back(tmpinfo);
}
void Scene::ZoomShapeSolo(double x,int index)
{
	double value = .9;
	if (x >= 0)
		value = 1.1;
	TheShapes[index]->ZoomShapeSolo(x);

}
void Scene::RevertZoom()
{
	for (int i = 0; i < zoomedininfo.size(); i++)
	{
		Reverter.Zoomtomouseinverse(zoomedininfo[i].amount, zoomedininfo[i].xmouse, zoomedininfo[i].ymouse, 0);
	}
	double xchange = 0 - Reverter.AccessPoints()[0].x;
	double ychange = 0 -Reverter.AccessPoints()[0].y;
	Reverter.MoveX(xchange);
	Reverter.MoveY(ychange);
	//figure out how reverter switched then do same for all
	for (int i = 0; i < TheShapes.size(); i++)
	{
		for (int x = 0; x < zoomedininfo.size(); x++)
		{
			TheShapes[i]->Zoomtomouseinverse(zoomedininfo[x].amount, zoomedininfo[x].xmouse, zoomedininfo[x].ymouse, 0);
		}
		TheShapes[i]->MoveX(xchange);
		TheShapes[i]->MoveY(ychange);
		TheShapes[i]->SetScriptorigins(xchange, ychange);
	}
	zoomedininfo.clear();
}
void Scene::RevertMove()
{
	for (int i = 0; i < TheShapes.size(); i++)
	{
		TheShapes[i]->RevertMoveAmount();
	}
}
void Scene::HandleShapeScript(SDL_Renderer* grender)//call every frame
{
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	for (int i = 0; i < TheShapes.size(); i++)
	{
		if (TheShapes[i]->GetScriptTempDeath())
		{
			TheShapes[i]->ScriptTempDeath();
		}
		if (TheShapes[i]->GetBallSpawner())
		{
			//TheShapes[i]->SetScriptDistanceReal(100);
			//TheShapes[i]->ScriptBallShooter();
			TheShapes[i]->SetScriptCounter(TheShapes[i]->GetScriptCounter() + 1);
			if (TheShapes[i]->GetScriptCounter() % static_cast<int>(TheShapes[i]->GetScriptDistance()) == 0)
			{
				int rotation = TheShapes[i]->GetTotalAmountRotated();
				AddCircleProjectile(TheShapes[i]->GetOuterCircleCenter().x, TheShapes[i]->GetOuterCircleCenter().y,10);
				int lastindex = AccessShapes().size() - 1;
				AccessShapes()[lastindex]->ToggleDamage(true);
				AccessShapes()[lastindex]->SetScriptMove(true);
				AccessShapes()[lastindex]->SetScriptSpeedReal(cos((rotation*3.14)/180) *TheShapes[i]->GetScriptSpeed());
				AccessShapes()[lastindex]->SetScriptSpeedy(sin((rotation*3.14) / 180)*TheShapes[i]->GetScriptSpeed());
			}
		}
		if (TheShapes[i]->GetScriptLefttoRight())
		{
			TheShapes[i]->ScriptLefttoRight(grender);
		}
		if (TheShapes[i]->GetScriptUptoDown())
		{
			TheShapes[i]->ScriptUptoDown();
		}
		if (TheShapes[i]->GetScriptMove())
		{
			TheShapes[i]->ScriptMove();
			TheShapes[i]->SetScriptCounter(TheShapes[i]->GetScriptCounter() + 1);
			if (TheShapes[i]->GetOuterCircleCenter().x > SCREEN_WIDTH*2 || TheShapes[i]->GetOuterCircleCenter().x < 0 || TheShapes[i]->GetOuterCircleCenter().y > SCREEN_HEIGHT*2 || TheShapes[i]->GetOuterCircleCenter().y < 0)
			{
				DeleteShape(0,0,i);
			}
		}
	}
}