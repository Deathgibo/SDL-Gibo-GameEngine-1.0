#pragma once
#include "Scene.h"
#include "Shapes.h"
#include <string>
#include <fstream>


class Game
{
public:
	Game();
	Game(vector<Scene> scene, Player player);
	~Game();
	void StartGame();
	void NewLevel();
	void Print(SDL_Renderer* grender);
	Shapegui* AccessShapegui();
	Playergui* AccessPlayergui();
	Scene* AccessScene();
	Scene* AccessSceneIndex(int i);
	void AddScene();
	void RemoveScene();
	void SwitchScene(int x);
	void SwitchSceneLeft();
	void SwitchSceneRight();
	void ShapeguiDelete();
	void ShapeguiCreate(int index);
	void PlayerguiCreate();
	void PlayerguiDelete();
	void CreateRectangle(bool portal = 0);
	void CreateTriangle();
	void CreatePolyLine();
	void CreateDoubleJumper();
	void CreateBouncer();
	void CreateCheckpoint();
	void CreateCircle(int x = 150, int y = 100, int r = 50);
	void ToggleDrag();
	void MakeaCopy(Shapes* theshape);
	void SaveGame(int save);
	bool LoadGame(int save);
	Player AccessPlayer();
	Player* AccessPlayerPoint();
	void RevertZoom();
	void RevertZoomIndex(int i);
	Scene* AccessCurrentScene();
	void DeleteShape(int x, int y, int index);
	int WhatShapeClicked(int x, int y);
	void HandlePlayerInput(SDL_Renderer * grender);
	void MovePlayerToPosition(int x, int y);
	void CameraMove(int x, int y);
	bool IsCameraLock();
	void SetCameraLock(bool i);
	void HandleShapesScripts(SDL_Renderer* grender);
	void SetPlayerMode(bool i);
	bool GetPlayMode();
private:
	Shapes* currentcheckpoint;
	int checkpointscene;
	bool playermode;
	bool cameralock;
	int currentscene;
	vector<Scene> Scenes;
	Player ThePlayer;
	SDL_Texture* loadtext(string s, SDL_Color textcolor);
	void DealWithTeleport();
};
void Game::NewLevel()
{
	playermode = 0;
	cameralock = 0;
	currentscene = 0;
	for (int i = 0; i < Scenes.size(); i++)
	{
		Scene* tmp = &Scenes[i];
		tmp->~Scene();
	}
	Scenes.clear();
	extern SDL_Texture* playerskin;
	ThePlayer.PlayerInitialize(100, 100, playerskin, 100, 100, this);
	Scene scene1;
	Scenes.push_back(scene1);
}
void Game::StartGame()
{
	extern SDL_Texture* playerskin;
	currentscene = 0;
	ThePlayer.PlayerInitialize(100, 100, playerskin, 100, 100, this);
	Scene scene1;
	Scenes.push_back(scene1);
	playermode = 0;
}
Game::Game()
{
	extern SDL_Texture* playerskin;
	currentscene = 0;
	cameralock = false;
	ThePlayer.PlayerInitialize(100, 100, playerskin, 100, 100, this);
	Scene scene1;
	Scenes.push_back(scene1);
	playermode = 0;
}
Game::~Game()
{
	currentscene = 0;
	Scenes.clear();
}
Game::Game(vector<Scene> scene, Player player)
{

}
void Game::DealWithTeleport()
{
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	if(ThePlayer.AccessTeleported())
	{
		vec2d theplayerposition = ThePlayer.GetPlayerPosition();
		int sidehit = ThePlayer.GetTeleportSideHit();
		if (ThePlayer.GetTeleportedRight())
			SwitchSceneRight();
		else
			SwitchSceneLeft();
		ThePlayer.ToggleTeleported(0);
		if (sidehit == 0)
		{
			ThePlayer.MovePlayerToPosition(theplayerposition.x, 0);
		}
		else if (sidehit == 1)
		{
			ThePlayer.MovePlayerToPosition(SCREEN_WIDTH,theplayerposition.y);
		}
		else if (sidehit == 2)
		{
			ThePlayer.MovePlayerToPosition(theplayerposition.x, SCREEN_HEIGHT - ThePlayer.GetHeight());
		}
		else if (sidehit == 3)
		{
			ThePlayer.MovePlayerToPosition(0, theplayerposition.y);
		}
	}
}
void Game::MovePlayerToPosition(int x, int y)
{
	ThePlayer.MovePlayerToPosition(x, y);
}
bool Game::IsCameraLock()
{
	return cameralock;
}
void Game::SetCameraLock(bool i)
{
	cameralock = i;
}
void Game::Print(SDL_Renderer* grender)
{
	if (ThePlayer.IsPlayerAlive())
	{
		ThePlayer.Print(grender);
	}
	Scenes[currentscene].PrintScene(grender,ThePlayer, playermode);
}
Shapegui* Game::AccessShapegui()
{
	return Scenes[currentscene].Accessshapegui();
}
Playergui* Game::AccessPlayergui()
{
	return Scenes[currentscene].AccessPlayergui();
}
void Game::CameraMove(int x, int y)
{
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	double playerx = ThePlayer.AccessPlayerx();
	double playery = ThePlayer.AccessPlayery();
	vec2d velocity = ThePlayer.AccessDistanceMovedThisFrame();
	double xvelocity = velocity.x;
	double yvelocity = velocity.y;
	int speed = 10;

	Scenes[currentscene].MoveShapes(xvelocity, 0);
	ThePlayer.MovePlayer(xvelocity, 0);
	Scenes[currentscene].MoveShapes(0, yvelocity);
	ThePlayer.MovePlayer(0, yvelocity);
	if (playerx <= SCREEN_WIDTH / 2 - 50)//playerx <= SCREEN_WIDTH / 3
	{
		//move everything right
		Scenes[currentscene].MoveShapes(speed, 0);
		ThePlayer.MovePlayer(speed, 0);
	}
	if (playerx >= SCREEN_WIDTH / 2 + 50)//playerx >= ((2 * SCREEN_WIDTH) / 3)
	{
		//move everything left
		Scenes[currentscene].MoveShapes(-speed, 0);
		ThePlayer.MovePlayer(-speed, 0);
	}
	if (playery <= SCREEN_HEIGHT / 2 - 25)//playery <= SCREEN_HEIGHT / 3
	{
		//move everything down
		Scenes[currentscene].MoveShapes(0, speed);
		ThePlayer.MovePlayer(0, speed);
	}
	if (playery >= SCREEN_HEIGHT / 2 + 15)//playery >= ((2 * SCREEN_HEIGHT) / 3)
	{
		//move everything up
		Scenes[currentscene].MoveShapes(0, -speed);
		ThePlayer.MovePlayer(0, -speed);
	}	
}
void Game::ShapeguiDelete()
{
	Scenes[currentscene].ShapeguiDelete();
}
void Game::ShapeguiCreate(int index)
{
	Scenes[currentscene].ShapeguiCreate(index);
}
void Game::PlayerguiCreate()
{
	Player * ptr = &ThePlayer;
	Scenes[currentscene].PlayerguiCreate(ptr);
}
void Game::PlayerguiDelete()
{
	Scenes[currentscene].PlayerguiDelete();
}
void Game::CreateRectangle(bool portal)
{
	Scenes[currentscene].AddRectangle(portal);
}
void Game::CreateTriangle()
{
	Scenes[currentscene].AddTriangle();
}
void Game::CreatePolyLine()
{
	Scenes[currentscene].AddPolyLine();
}
void Game::CreateDoubleJumper()
{
	Scenes[currentscene].AddDoubleJumper();
}
void  Game::CreateCircle(int x, int y, int r)
{
	Scenes[currentscene].AddCircle(x,y,r);
}
void Game::CreateBouncer()
{
	Scenes[currentscene].AddBouncer();
}
void Game::CreateCheckpoint()
{
	Scenes[currentscene].AddCheckpoint();
	//currentcheckpoint.RectangleInitialize(100, 100, 50, 50);
	//checkpointscene = currentscene;
}
int Game::WhatShapeClicked(int x, int y)
{
	return Scenes[currentscene].ShapeIndexClicked(x, y);
}
Scene* Game::AccessScene()
{
	return &Scenes[currentscene];
}
Scene* Game::AccessSceneIndex(int i)
{
	return &Scenes[i];
}
void Game::HandlePlayerInput(SDL_Renderer * grender)
{
	if (!ThePlayer.IsPlayerAlive())
	{
		if (currentcheckpoint == NULL)
		{
			ThePlayer.Respawn(100, 100);
		}
		else
		{
			vector<vec2d> points = currentcheckpoint->AccessPoints();
			if (!points.empty())
			{
				currentscene = checkpointscene;
				ThePlayer.Respawn(points[0].x, points[0].y);
				//ThePlayer.Respawn(points[0].x + ((points[1].x - points[0].x) / 2), points[1].y + ((points[2].y - points[1].y) / 2));
			}
			else
			{
				ThePlayer.Respawn(100, 100);
			}
		}
		return;
	}
	if (ThePlayer.IsPlayerAlive())
	{
		ThePlayer.HandleInput(AccessScene()->AccessShapes(), grender);
	}
	if (cameralock)
	{
		CameraMove(0, 0);
	}
	DealWithTeleport();
	if (ThePlayer.getcheckpoint() != currentcheckpoint)
	{
		currentcheckpoint = ThePlayer.getcheckpoint();
		checkpointscene = currentscene;
	}
}
void Game::DeleteShape(int x, int y, int index)
{
	Scenes[currentscene].DeleteShape(x, y, index);
}
void Game::AddScene()
{
	Scene newscene;
	Scenes.push_back(newscene);
	currentscene = Scenes.size()-1;
	SDL_Color textcolor = { 0,0,0 };
	SDL_Texture* anumber;
	anumber = loadtext(to_string(currentscene+1), textcolor);
	Scenes[currentscene].changelevelmakerscenetexture(anumber);
}
void Game::RemoveScene()
{
	if (currentscene == 0)
	{
		return;
	}
	Scenes.erase(Scenes.begin() + currentscene);
	currentscene--;
	SDL_Texture* anumber;
	SDL_Color textcolor = { 0,0,0 };
	for (int i = 0; i < Scenes.size(); i++)
	{
		anumber = loadtext(to_string(i+1), textcolor);
		Scenes[i].changelevelmakerscenetexture(anumber);
	}
}
void Game::SwitchScene(int x)
{
	currentscene = x;
	RevertZoom();
	MovePlayerToPosition(100, 100);
}
void Game::SwitchSceneLeft()
{
	if (currentscene == 0)
	{
		return;
	}
	currentscene--;
	RevertZoom();
	MovePlayerToPosition(100, 100);
}
void Game::SwitchSceneRight()
{
	if (Scenes.size()-1 == currentscene)
	{
		return;
	}
	currentscene++;
	RevertZoom();
	MovePlayerToPosition(100, 100);
}
Scene* Game::AccessCurrentScene()
{
	return &Scenes[currentscene];
}
SDL_Texture* Game::loadtext(string s, SDL_Color textcolor)
{
	//extern int SCREEN_WIDTH;
	extern TTF_Font* gfont;
	extern SDL_Renderer* grender;
	SDL_Surface* tempsurface = TTF_RenderText_Blended_Wrapped(gfont, s.c_str(), textcolor, 1000);
	SDL_Texture* returntexture;
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	//cout << tempsurface->w << " " << tempsurface->h;
	//get width and height
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void Game::HandleShapesScripts(SDL_Renderer* grender)
{
	//for playergui
	if (Scenes[currentscene].AccessPlayergui() == NULL)
	{
		ThePlayer.SetShowhitboxes(0);
	}
	else
	{
		ThePlayer.SetShowhitboxes(1);
	}
	Scenes[currentscene].HandleShapeScript(grender);
}
void Game::ToggleDrag()
{
	Scenes[currentscene].ToggleDrag();
}
void  Game::RevertZoom()
{
	Scenes[currentscene].RevertZoom();
}
void Game::RevertZoomIndex(int i)
{
	Scenes[i].RevertZoom();
}
Player Game::AccessPlayer()
{
	return ThePlayer;
}
bool Game::GetPlayMode()
{
	return playermode;
}
void Game::SetPlayerMode(bool i)
{
	playermode = i;
}
Player* Game::AccessPlayerPoint()
{
	Player* lol = &ThePlayer;
	return lol;
}
void Game::MakeaCopy(Shapes* theshape)
{
	Scenes[currentscene].AddCopy(theshape);
}
void Game::SaveGame(int save)
{
	string savename;
	switch (save)
	{
	case 1: savename = "SaveFile1.txt"; break;
	case 2: savename = "SaveFile2.txt"; break;
	case 3: savename = "SaveFile3.txt"; break;
	}
	fstream file;
	file.open(savename,ios::out);
	file.close();
	for (int s = 0; s < Scenes.size(); s++)
	{
		RevertZoomIndex(s);
		vector<Shapes*> CurrentShapes = AccessSceneIndex(s)->AccessShapes();
		if (s != 0)
		{
			file.open(savename, ios::app);
			file <<"$"<< endl;
			file.close();
		}
		for (int i = 0; i < CurrentShapes.size(); i++)
		{
			shapeType type = CurrentShapes[i]->GetShapeType();
			char letter;
			switch (type)
			{
			case 0: letter = 'R'; break;
			case 1: letter = 'C'; break;
			case 2: letter = 'T'; break;
			case 3: letter = 'H'; break;
			case 4: letter = 'P'; break;
			}
			if (CurrentShapes[i]->GetDoubleJumper() == 1)
			{
				letter = 'Z';//circleprojectile
			}
			vector<vec2d> points = CurrentShapes[i]->AccessPoints();
			file.open(savename, ios::app);
			file << letter << " ";
			for (int j = 0; j < points.size(); j++)
			{
				file << points[j].x << "," << points[j].y << " ";
			}
			if (CurrentShapes[i]->AccessDamage() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetBallSpawner() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetBouncer() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetDoubleJumper() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->AccessTeleport() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetScriptMove() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetScriptLefttoRight() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetScriptUptoDown() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetScriptdir() == 1)
				file << "T";
			else
				file << "F";
			if (ThePlayer.GetDoubleJump() == 1)
				file << "T";
			else
				file << "F";
			if (cameralock == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetCheckpoint() == 1)
				file << "T";
			else
				file << "F";
			if (CurrentShapes[i]->GetTeleportRight() == 1)
				file << "T";
			else
				file << "F";
			file <<" "<< CurrentShapes[i]->GetScriptCounter() << "," << CurrentShapes[i]->GetScriptDistance() << "," << CurrentShapes[i]->GetTotalAmountRotated();
			file << "," << CurrentShapes[i]->GetBounceAmount()<<","<<CurrentShapes[i]->GetScriptSpeed()<<","<<CurrentShapes[i]->GetRotationAmount()<<",";
			file << CurrentShapes[i]->GetScriptorigin().x << "," << CurrentShapes[i]->GetScriptorigin().y << "," << CurrentShapes[i]->GetScriptorigin2().x << ",";
			file << CurrentShapes[i]->GetScriptorigin2().y << "," << ThePlayer.Getxspeed() << "," << ThePlayer.GetJumpHeight() << "," << ThePlayer.GetWidth();
			file << "," << ThePlayer.GetHeight() << "," << ThePlayer.GetXamount() << "," << ThePlayer.GetYamount();
			file << " !" << endl;
			file.close();
		}
	}
	file.open(savename, ios::app);
	file << "@";
	file.close();
}
bool Game::LoadGame(int save)
{
	bool leaveline = false;
	bool once = true;
	bool leavefile = false;
	string holder;
	fstream file;
	int scene = 0;
	switch (save)
	{
	case 1: file.open("SaveFile1.txt"); break;
	case 2:	file.open("SaveFile2.txt"); break;
	case 3: file.open("SaveFile3.txt"); break;
	}
	if (file.peek() == -1)
	{
		file.close();
		return 0;
	}
	while (!leavefile)
	{
		vector<vec2d> points;
		double x;
		double y;
		string type;
		//read up to space read up to comma repeat
		getline(file, holder, ' ');
		type = holder;
		if (once)
		{
			if(!Scenes[scene].AccessShapes().empty())
				Scenes[scene].AccessShapes().clear();
			once = false;
		}
		while (!leaveline)
		{
			getline(file, holder, ',');
			x = stoi(holder);
			getline(file, holder, ' ');
			//cout << "peek: "<<file.peek() << endl;
			y = stoi(holder);
			//cout << x << " " << y << endl;
			vec2d tmppoint(x, y);
			//cout << tmppoint.x << " " << tmppoint.y << endl;
			points.push_back(tmppoint);
			if (file.peek() == 84 || file.peek() == 70)
			{
				//getline(file, holder);
				leaveline = true;
			}
		}
		leaveline = false;
		if (points.size() != 0)
		{
			if (type == "R")
			{
				Rectangle* ptr = new Rectangle(points);
				Scenes[scene].AddRectangleKnown(ptr);
			}
			else if (type == "P")
			{
				PolyLine* ptr = new PolyLine(points);
				Scenes[scene].AddPolyLineKnown(ptr);
			}
			else if (type == "T")
			{
				Triangle* ptr = new Triangle(points);
				Scenes[scene].AddTriangleKnown(ptr);
			}
			else if (type == "C")
			{
				Circle* ptr = new Circle(points);
				Scenes[scene].AddCircleKnown(ptr);
			}
			else if (type == "Z")
			{
				CircleProjectile* ptr = new CircleProjectile(points);
				Scenes[scene].AddCircleProjectileKnown(ptr);
			}
			char tf;
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->ToggleDamage(true);
			file.get(tf);
			if(tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetBallSpawner(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetBouncer(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetDoubleJumper(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->ToggleTeleport(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptMove(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptlefttoright(true,false);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetSCriptUptoDown(true,false);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptdir(true);
			file.get(tf);
			if (tf == 'T')
				ThePlayer.SetDoubleJump(true);
			file.get(tf);
			if (tf == 'T')
				cameralock = true;
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetCheckpoint(true);
			file.get(tf);
			if (tf == 'T')
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetTeleportRight(true);
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptCounter(stoi(holder));
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptDistanceReal(stoi(holder));
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetTotalAmountRotated(stoi(holder));
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetBounceAmount(stoi(holder));
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptSpeedReal(stoi(holder));
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetRotationAmount(stoi(holder));
			getline(file, holder, ',');
			double xtmp = stoi(holder);
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptorigin1real(xtmp,stoi(holder));
			getline(file, holder, ',');
			xtmp = stoi(holder);
			getline(file, holder, ',');
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptorigin2real(xtmp,stoi(holder));
			getline(file, holder, ',');
			ThePlayer.Setxspeed(stoi(holder));//speed is double this is int*
			getline(file, holder, ',');
			ThePlayer.SetJumpHeight(stoi(holder));
			getline(file, holder, ',');
			ThePlayer.SetWidth(stoi(holder));
			getline(file, holder, ',');
			ThePlayer.SetHeight(stoi(holder));
			getline(file, holder, ',');
			ThePlayer.SetXamount(stoi(holder));
			getline(file, holder, '!');
			ThePlayer.SetYamount(stoi(holder));
			getline(file, holder);
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->SetScriptOnce(false);
			Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->UpdateCircle();
			if (type == "R"&& Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->GetRotationAmount() != 0)
			{
				double save = Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->ResetAngle();
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->UpdateCircle();
				Scenes[scene].AccessShapes()[Scenes[scene].AccessShapes().size() - 1]->Rotate(save);
			}
		}
		points.clear();
		if (file.peek() == 36)
		{
			getline(file, holder);
			AddScene();
			once = true;
			scene++;
		}
		if (file.peek() == 64)
		{
			getline(file, holder);
			leavefile = true;
		}
	}
	currentscene = 0;
	file.close();
	return true;
}