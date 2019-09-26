//use vectors and linear algebra for this game engine. points can be represented by vectors and rotations maybe even physics can be handled with linear algebra disjoint sets
//could do physics with all lines just figure out how to tell if a line intersects, axis theorom
#pragma once
#include "Player.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Shapes.h"
#include "LTimer.h"
#include "LevelMakergui.h"
#include "Scene.h"
#include "Shapegui.h"
#include "Game.h"
#undef main
#include <chrono>
#include <string>
#include <thread>
#include <sstream>
#include <stdio.h>
#include <iostream>
//#include <Windows.h>
using namespace std;


struct Pixel
{
	int type;//0 empty | 1 wall | 2 enemies
	
	Pixel()
	{
		type = 0;
	}
};

//SDL Window stuff
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 500;
SDL_Window* gwindow = 0;
SDL_Renderer* grender = 0;
SDL_Surface* gsurface = 0;
SDL_Texture* rectangleimage = 0;
SDL_Texture* triangleimage = 0;
SDL_Texture* circleimage = 0;
SDL_Texture* lineimage = 0;
SDL_Texture* fourarrowbox = 0;
SDL_Texture* dottedbox = 0;
SDL_Texture* numberbox = 0;
SDL_Texture* deletebox = 0;
SDL_Texture* rotatebox = 0;
SDL_Texture* scriptbox = 0;
SDL_Texture* rotateone = 0;
SDL_Texture* rotatenone = 0;
SDL_Texture* rotatetwo = 0;
SDL_Texture* rotatentwo = 0;
SDL_Texture* rotatethree = 0;
SDL_Texture* rotatenthree = 0;
SDL_Texture* rotatefour = 0;
SDL_Texture* rotatenfour = 0;
SDL_Texture* rotatefive = 0;
SDL_Texture* rotatenfive = 0;
SDL_Texture* rotatezero = 0;
SDL_Texture* theleftarrow = 0;
SDL_Texture* therightarrow = 0;
SDL_Texture* plussign = 0;
SDL_Texture* anumber = 0;
SDL_Texture* playerskin = 0;
SDL_Texture* subtract = 0;
SDL_Texture* hand = 0;
SDL_Texture* zoomin = 0;
SDL_Texture* normal = 0;
SDL_Texture* handon = 0;
SDL_Texture* copybox = 0;
SDL_Texture* save = 0;
SDL_Texture* mainmenu = 0;
SDL_Texture* mainmenuload = 0;
SDL_Texture* mainmenumake = 0;
SDL_Texture* mainmenuquit = 0;
SDL_Texture* loadmenu = 0;
SDL_Texture* gamemenu = 0;
SDL_Texture* gamemenuresume = 0;
SDL_Texture* gamemenumenu = 0;
SDL_Texture* gamemenuquit = 0;
SDL_Texture* playericon = 0;
SDL_Texture* damageicon = 0;
SDL_Texture* damageiconred = 0;
SDL_Texture* cameraicon = 0;
SDL_Texture* backgroundegypt = 0;
SDL_Texture* run1 = 0;
SDL_Texture* run2 = 0;
SDL_Texture* run3 = 0;
SDL_Texture* run4 = 0;
SDL_Texture* run5 = 0;
SDL_Texture* run6 = 0;
SDL_Texture* run7 = 0;
SDL_Texture* run8 = 0;
SDL_Texture* idle1 = 0;
SDL_Texture* idle2 = 0;
SDL_Texture* idle3 = 0;
SDL_Texture* idle4 = 0;
SDL_Texture* idle5 = 0;
SDL_Texture* idle6 = 0;
SDL_Texture* jump1 = 0;
SDL_Texture* jump2 = 0;
SDL_Texture* jump3 = 0;
SDL_Texture* jump4 = 0;
SDL_Texture* portalicon = 0;
SDL_Texture* lrarrows = 0;
SDL_Texture* udarrows = 0;
SDL_Texture* speedicon = 0;
SDL_Texture* distanceicon = 0;
SDL_Texture* shootericon = 0;
SDL_Texture* doublejumpericon = 0;
SDL_Texture* bounceicon = 0;
SDL_Texture* runicon = 0;
SDL_Texture* menu = 0;
SDL_Texture* menuplay = 0;
SDL_Texture* menuload = 0;
SDL_Texture* menunew = 0;
SDL_Texture* menuquit = 0;
SDL_Texture* savemenu = 0;
SDL_Texture* savemenu1 = 0;
SDL_Texture* savemenu2 = 0;
SDL_Texture* savemenu3 = 0;
SDL_Texture* ingamemenu = 0;
SDL_Texture* portaliconleft = 0;
SDL_Texture* portaliconright = 0;
SDL_Texture* checkpointicon = 0;
SDL_Texture* balljump = 0;
SDL_Texture* green = 0;
SDL_Texture* gray = 0;
SDL_Texture* bluecircle = 0;
SDL_Texture* redcircle = 0;
SDL_Texture* red = 0;

TTF_Font* gfont = 0;
SDL_Texture* fpstexture = 0;
const int FPS_CAP = 60;
int framecounter = 0;
LTimer framecaptimer;
bool restartframes = true;

bool menuset = true;
//Pixel ThePixels[SCREEN_WIDTH+1][SCREEN_HEIGHT+1];//x by y, x=5 y = 10 [5][10]
//when it spawns scan all pixels now your done just update whenever you move
//or when you move it doesnt update until its still

//************** just make it so if the slope is less than 3 it automatically transforms it to 0 like its better than it breaking and it raelly doesnt effect anything why would you need a .03 slope and not a 0

void Handlefpstimer(int& countedframe, LTimer& fpstimer);
SDL_Texture* loadtext(string s, SDL_Color textcolor);
SDL_Texture* loadtexture(string a);
SDL_Texture* loadseethroughwhite(string a);
void Menu(Game *& TheGame);
void SaveMenu(Game *& TheGame);
void InGameMenu(Game *& TheGame, bool & renderz, vec2d & point, bool clicked);
int AngleofLine(vec2d one, vec2d two, SDL_Renderer* grender);
bool InitializeSDL();
void InitializeImages();
int main(int argc, char* argv[])
{
	//system("explorer.exe");
	InitializeSDL();
	InitializeImages();
	//counter stuff
	LTimer fpsTimer;
	int countedFrames = 0;
	float avgFPS = 0;
	fpsTimer.start();

	//TheGame
	Game * TheGame = new Game;
	bool exit = false;
	int angle = 0;
	SDL_Event e;
	//Menu
	bool rendermenu = false;
	vec2d currentmouseclick;
	bool mouseclicked = false;
	while (exit == false)
	{
		if (menuset)
		{
			Menu(TheGame);
			menuset = false;
		}

		framecaptimer.start();

		while (SDL_PollEvent(&e) != 0)
		{
			mouseclicked = false;
			int x, y;
			SDL_GetMouseState(&x, &y);
			currentmouseclick.x = x; currentmouseclick.y = y;
			if (e.type == SDL_QUIT)
			{
				exit = true;
			}
				if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_w:    break;
					case SDLK_s:	break;
					case SDLK_a:	break;
					case SDLK_d:	break;
					case SDLK_ESCAPE: rendermenu = !rendermenu; break;
					}
				}
				if (e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_w:	break;
					case SDLK_s:	break;
					case SDLK_a:	break;
					case SDLK_d:	break;
					}
				}
				if (!TheGame->GetPlayMode())
				{
				if (e.type == SDL_MOUSEMOTION)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					//LevelMakergui* Currentlevelmakergui = TheGame.AccessCurrentScene()->AccessLevelMakergui();
					if (TheGame->AccessCurrentScene()->AccessLevelMakergui() != 0)
					{
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsDragOn() && TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseDown())
						{
							vec2d currentmousepos = TheGame->AccessCurrentScene()->AccessLevelMakergui()->Accessmouseposition();
							double xchange = x - currentmousepos.x;
							double ychange = y - currentmousepos.y;
							TheGame->AccessCurrentScene()->MoveShapes(xchange, ychange);
							TheGame->AccessCurrentScene()->AccessLevelMakergui()->SetMouseposition(x, y);
						}
					}
					if (TheGame->AccessPlayergui() != 0)
					{
						if (TheGame->AccessPlayergui()->holddownclick)
						{
							double xchange = x - TheGame->AccessPlayergui()->mouseposition.x;
							double ychange = y - TheGame->AccessPlayergui()->mouseposition.y;
							if (TheGame->AccessPlayergui()->imageboxborder)
							{
								TheGame->AccessPlayerPoint()->MovePlayer(xchange, ychange);
							}
							if (TheGame->AccessPlayergui()->hitboxborder)
							{
								TheGame->AccessPlayergui()->HandleDottedSquareMotion(x, y);
							}
							if (TheGame->AccessPlayergui()->sizeboxborder)
							{
								TheGame->AccessPlayergui()->HandleDottedSquareMotion(x, y, 0);
							}
							TheGame->AccessPlayergui()->mouseposition.x = x;
							TheGame->AccessPlayergui()->mouseposition.y = y;
						}
					}
					if (TheGame->AccessShapegui() != 0)
					{
						if (TheGame->AccessShapegui()->holddownclick)
						{
							double xchange = x - TheGame->AccessShapegui()->mouseposition.x;
							double ychange = y - TheGame->AccessShapegui()->mouseposition.y;
							if (TheGame->AccessShapegui()->arrowborder)
							{
								TheGame->AccessShapegui()->MoveX(xchange);
								TheGame->AccessShapegui()->MoveY(ychange);
							}
							if (TheGame->AccessShapegui()->dottedsquareborder)
							{
								TheGame->AccessShapegui()->HandleDottedSquareMotion(x, y);
							}
							if (TheGame->AccessShapegui()->zoominsquareborder)
							{
								double yikes = .9;
								if (xchange < 0)
									yikes = 1.1;
								if (TheGame->AccessShapegui()->guishape->GetShapeType() != POLYLINE)
									TheGame->AccessShapegui()->guishape->ZoomShapeSolo(yikes);
							}
							if (TheGame->AccessShapegui()->distancesquareborder)
							{
								if (xchange != 0)
								{
									//TheGame.AccessShapegui()->guishape->SetScriptDistance(abs(xchange));
								}
							}
							if (TheGame->AccessShapegui()->speedsquareborder)
							{
								if (xchange != 0)
								{
									//TheGame.AccessShapegui()->guishape->SetScriptSpeed(abs(xchange));
								}
							}
							if (TheGame->AccessShapegui()->rotatesquareborder)
							{
								if (TheGame->AccessShapegui()->guishape->GetShapeType() != POLYLINE)
									TheGame->AccessShapegui()->guishape->Rotate(xchange);
							}
							TheGame->AccessShapegui()->mouseposition.x = x;
							TheGame->AccessShapegui()->mouseposition.y = y;
						}
					}
				}
				//cout << " after mousemotion" << endl;
				//cout << "before mousedown";
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					mouseclicked = true;
					int x, y;
					SDL_GetMouseState(&x, &y);
					//LevelMakergui* Currentlevelmakergui = TheGame.AccessCurrentScene()->AccessLevelMakergui();
					if (TheGame->AccessCurrentScene()->AccessLevelMakergui() != 0)
					{
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetDragSceneBox().rect))
						{
							TheGame->ToggleDrag();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsDragOn())
						{
							TheGame->AccessCurrentScene()->AccessLevelMakergui()->SetHoldClick(true);
							TheGame->AccessCurrentScene()->AccessLevelMakergui()->SetMouseposition(x, y);
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetSquareBox().rect))
						{
							TheGame->CreateRectangle();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetTriangleBox().rect))
						{
							TheGame->CreateTriangle();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetPolyLineBox().rect))
						{
							TheGame->CreatePolyLine();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetcircleBox().rect))
						{
							TheGame->CreateCircle();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetDoubleJumperBox().rect))
						{
							TheGame->CreateDoubleJumper();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetBounceBox().rect))
						{
							TheGame->CreateBouncer();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetCheckpointBox().rect))
						{
							TheGame->CreateCheckpoint();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetPortalBox().rect))
						{
							TheGame->CreateRectangle(1);
							int lastindex = TheGame->AccessCurrentScene()->AccessShapes().size() - 1;
							TheGame->AccessCurrentScene()->AccessShapes()[lastindex]->ToggleTeleport(true);
							if (e.button.button == SDL_BUTTON_RIGHT)
							{
								TheGame->AccessCurrentScene()->AccessShapes()[lastindex]->SetTeleportRight(true);
							}
							else
							{
								TheGame->AccessCurrentScene()->AccessShapes()[lastindex]->SetTeleportRight(false);
							}
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetShooterBox().rect))
						{
							TheGame->CreateCircle();
							int lastindex = TheGame->AccessCurrentScene()->AccessShapes().size() - 1;
							TheGame->AccessCurrentScene()->AccessShapes()[lastindex]->SetBallSpawner(true);
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetAddSceneBox().rect))
						{
							TheGame->AddScene();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetSubtractSceneBox().rect))
						{
							TheGame->RemoveScene();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetLeftArrow().rect))
						{
							TheGame->SwitchSceneLeft();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetRightArrow().rect))
						{
							TheGame->SwitchSceneRight();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetNormalBox().rect))
						{
							TheGame->RevertZoom();
							//TheGame.AccessCurrentScene()->RevertMove();
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetSaveBox().rect))
						{
							SaveMenu(TheGame);
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetPlayerBox().rect))
						{
							//sTheGame->MovePlayerToPosition(100, 100);
							TheGame->AccessPlayerPoint()->Respawn(100,100);
						}
						if (TheGame->AccessCurrentScene()->AccessLevelMakergui()->IsMouseInRect(x, y, TheGame->AccessCurrentScene()->AccessLevelMakergui()->GetCameraBox().rect))
						{
							bool currentstate = TheGame->IsCameraLock();
							TheGame->SetCameraLock(!currentstate);
						}
					}
					/*  If you clicked on a shape */
					int index = TheGame->WhatShapeClicked(x, y);
					if (index != -1)
					{
						if (TheGame->AccessShapegui() == 0)
						{
							TheGame->ShapeguiCreate(index);
						}
						else
						{
							if (TheGame->AccessScene()->AccessShapes()[index] != TheGame->AccessShapegui()->guishape)
							{
								TheGame->ShapeguiDelete();
								TheGame->ShapeguiCreate(index);
							}
						}
						if (TheGame->AccessShapegui()->arrowborder)
						{

						}
						if (TheGame->AccessShapegui()->numbersquareborder)
						{
							TheGame->MakeaCopy(TheGame->AccessScene()->AccessShapes()[index]);
						}
						if (TheGame->AccessShapegui()->dottedsquareborder)
						{
							TheGame->AccessShapegui()->HandleDottedSquareClick(x, y);
						}
						if (TheGame->AccessShapegui()->rotatesquareborder)
						{

						}
						if (TheGame->AccessShapegui()->zoominsquareborder)
						{
							//TheGame.AccessCurrentScene()->ZoomShapeSolo(1.1,index);
						}
						if (TheGame->AccessShapegui()->lrarrrowsquareborder)
						{
							//TheGame.AccessShapegui()->guishape->SetScriptlefttoright(!TheGame.AccessShapegui()->guishape->GetScriptLefttoRight());
						}
						if (TheGame->AccessShapegui()->udarrowsquareborder)
						{
							//TheGame.AccessShapegui()->guishape->SetSCriptUptoDown(!TheGame.AccessShapegui()->guishape->GetScriptUptoDown());
						}
						if (TheGame->AccessShapegui()->damagesquareborder)
						{
							bool currentstate = TheGame->AccessShapegui()->guishape->AccessDamage();
							TheGame->AccessShapegui()->guishape->ToggleDamage(!currentstate);
							if (TheGame->AccessShapegui()->guishape->AccessDamage() == true)
							{
								TheGame->AccessShapegui()->damagesquarebox.ChangeTexture(damageiconred);
							}
							else
							{
								TheGame->AccessShapegui()->damagesquarebox.ChangeTexture(damageicon);
							}
						}
						if (TheGame->AccessShapegui()->deletesquareborder)
						{
							if (TheGame->AccessShapegui() != 0)
							{
								TheGame->DeleteShape(x, y, index);
								TheGame->ShapeguiDelete();
							}
						}
						if (TheGame->AccessShapegui() != 0)
						{
							TheGame->AccessShapegui()->mouseposition.x = x;
							TheGame->AccessShapegui()->mouseposition.y = y;
							TheGame->AccessShapegui()->holddownclick = true;
						}
					}
					/*if you cliked on player*/
					SDL_Rect pr = TheGame->AccessPlayer().GetPlayerRect();
					if (x <= pr.x + pr.w && x >= pr.x && y <= pr.y + pr.h && y >= pr.y)
					{
						if (TheGame->AccessPlayergui() == 0)
						{
							TheGame->PlayerguiCreate();
						}
						else
						{
						}
						if (TheGame->AccessPlayergui() != 0)
						{
							TheGame->AccessPlayergui()->mouseposition.x = x;
							TheGame->AccessPlayergui()->mouseposition.y = y;
							TheGame->AccessPlayergui()->holddownclick = true;
						}
						if (TheGame->AccessPlayergui()->hitboxborder)
						{
							TheGame->AccessPlayergui()->HandleDottedSquareClick(x, y);
						}
						if (TheGame->AccessPlayergui()->sizeboxborder)
						{
							TheGame->AccessPlayergui()->HandleDottedSquareClick(x, y, 0);
						}
					}

					int playerguiindex = -1;
					if (TheGame->AccessCurrentScene()->AccessPlayergui() != 0)
					{
						playerguiindex = TheGame->AccessCurrentScene()->AccessPlayergui()->GuiIndexClicked(x, y);
					}
					if (playerguiindex != -1)
					{
						if (TheGame->AccessPlayergui()->sizeboxborder)
						{
							if (e.button.button == SDL_BUTTON_RIGHT)
							{
								TheGame->AccessPlayerPoint()->SetWidth(100);
								TheGame->AccessPlayerPoint()->SetHeight(100);
							}
						}
						if (TheGame->AccessPlayergui()->speedboxborder)
						{
							if (e.button.button == SDL_BUTTON_RIGHT)
							{
								TheGame->AccessPlayerPoint()->Setxspeed(5);
							}
							else
							{
								if (TheGame->AccessPlayergui()->clickedleftx(x, y))
								{
									TheGame->AccessPlayerPoint()->Setxspeed(TheGame->AccessPlayerPoint()->Getxspeed() - 1);
								}
								if (TheGame->AccessPlayergui()->clickedrightx(x, y))
								{
									TheGame->AccessPlayerPoint()->Setxspeed(TheGame->AccessPlayerPoint()->Getxspeed() + 1);
								}
							}
						}
						if (TheGame->AccessPlayergui()->hitboxborder)
						{
							if (e.button.button == SDL_BUTTON_RIGHT)
							{
								TheGame->AccessPlayerPoint()->SetXamount(40);
								TheGame->AccessPlayerPoint()->SetYamount(25);
							}
						}
						if (TheGame->AccessPlayergui()->doublejumpboxborder && playerguiindex == 3)
						{
							TheGame->AccessPlayerPoint()->SetDoubleJump(!TheGame->AccessPlayer().GetDoubleJump());
						}
						if (TheGame->AccessPlayergui()->heightboxborder)
						{
							if (e.button.button == SDL_BUTTON_RIGHT)
							{
								TheGame->AccessPlayerPoint()->SetJumpHeight(8);
							}
							else
							{
								if (TheGame->AccessPlayergui()->clickedleft(x, y))
								{
									TheGame->AccessPlayerPoint()->SetJumpHeight(TheGame->AccessPlayerPoint()->GetJumpHeight() - 1);
								}
								if (TheGame->AccessPlayergui()->clickedright(x, y))
								{
									TheGame->AccessPlayerPoint()->SetJumpHeight(TheGame->AccessPlayerPoint()->GetJumpHeight() + 1);
								}
							}
						}
						switch (playerguiindex)
						{
						case 1: TheGame->AccessPlayergui()->SetBorder(1); break;
						case 2: TheGame->AccessPlayergui()->SetBorder(2); break;
						case 3: TheGame->AccessPlayergui()->SetBorder(3); break;
						case 4: TheGame->AccessPlayergui()->SetBorder(4); break;
						case 5: TheGame->AccessPlayergui()->SetBorder(5); break;
						case 6: TheGame->AccessPlayergui()->SetBorder(6); break;
						case 7: TheGame->AccessPlayergui()->SetBorder(7); break;
						}
						if (TheGame->AccessPlayergui()->deleteboxborder)
						{
							TheGame->PlayerguiDelete();
						}
					}
					/* if you clicked on a guibox */
					int guiindex = -1;
					if (TheGame->AccessShapegui() != 0)
						guiindex = TheGame->AccessShapegui()->GuiIndexClicked(x, y);
					if (guiindex != -1)
					{
						if (TheGame->AccessShapegui()->rotatesquareborder)
						{
							if (guiindex == 4 && SDL_BUTTON_RIGHT)
							{
								TheGame->AccessShapegui()->guishape->ResetAngle();
							}
							if (guiindex == 7)
							{
								TheGame->AccessShapegui()->guishape->SetRotationAmount(1);
								//TheGame.AccessShapegui()->rotatehelperbox.ChangeTexture(TheGame.AccessShapegui()->);
							}
						}
						switch (guiindex)
						{
						case 1: TheGame->AccessShapegui()->SetBorder(1); break;
						case 2: TheGame->AccessShapegui()->SetBorder(2); break;
						case 3: TheGame->AccessShapegui()->SetBorder(3); break;
						case 4: TheGame->AccessShapegui()->SetBorder(4); break;
						case 5:TheGame->AccessShapegui()->SetBorder(5); break;
						case 6:TheGame->AccessShapegui()->SetBorder(6); break;
						case 8:TheGame->AccessShapegui()->SetBorder(8); break;
						case 9:TheGame->AccessShapegui()->SetBorder(9); break;
						case 10:TheGame->AccessShapegui()->SetBorder(10); break;
						case 11:TheGame->AccessShapegui()->SetBorder(11); break;
						case 12:TheGame->AccessShapegui()->SetBorder(12); break;
						case 13:TheGame->AccessShapegui()->SetBorder(13); break;
						case 14:TheGame->AccessShapegui()->SetBorder(14); break;
						}
						if (TheGame->AccessShapegui()->lrarrrowsquareborder)
						{
							TheGame->AccessShapegui()->guishape->SetScriptlefttoright(!TheGame->AccessShapegui()->guishape->GetScriptLefttoRight());
						}
						if (TheGame->AccessShapegui()->udarrowsquareborder)
						{
							TheGame->AccessShapegui()->guishape->SetSCriptUptoDown(!TheGame->AccessShapegui()->guishape->GetScriptUptoDown());
						}
						if (TheGame->AccessShapegui()->distancesquareborder)
						{
							if (TheGame->AccessShapegui()->clickeddistanceright(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetScriptDistance(5);
							}
							if (TheGame->AccessShapegui()->clickedistanceleft(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetScriptDistance(-5);
							}
						}
						if (TheGame->AccessShapegui()->speedsquareborder)
						{
							if (TheGame->AccessShapegui()->clickedspeedleft(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetScriptSpeed(-1);
							}
							if (TheGame->AccessShapegui()->clickedspeedright(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetScriptSpeed(1);
							}
						}
						if (TheGame->AccessShapegui()->bouncesquareborder)
						{
							int l = TheGame->AccessShapegui()->guishape->GetBounceAmount();
							if (TheGame->AccessShapegui()->clickedbounceleft(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetBounceAmount(l - 1);
							}
							if (TheGame->AccessShapegui()->clickedbounceright(x, y))
							{
								TheGame->AccessShapegui()->guishape->SetBounceAmount(l + 1);
							}
						}
					}

				}
				//cout << " after mousedown" << endl;
				if (e.type == SDL_MOUSEBUTTONUP)
				{
					if (TheGame->AccessShapegui() != 0)
						TheGame->AccessShapegui()->holddownclick = false;
					if (TheGame->AccessPlayergui() != 0)
						TheGame->AccessPlayergui()->holddownclick = false;
					TheGame->AccessCurrentScene()->AccessLevelMakergui()->SetHoldClick(false);
				}
				if (e.type == SDL_MOUSEWHEEL)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					//cout << e.wheel.y << endl;
					TheGame->AccessScene()->ZoomShapes(e.wheel.y, x, y);
				}
			}
				else
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						mouseclicked = true;
					}
				}
		}
		//Physics fix for slopes if your going right and slope is positive or going left and slope is negative good everything else is going downhill so we dont need physics for slopes
		
		/*								MAIN LOOP							*/

		SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
		SDL_RenderClear(grender);
		SDL_RenderCopy(grender, backgroundegypt, 0, 0);
		TheGame->Print(grender);
		if (rendermenu)
			InGameMenu(TheGame, rendermenu,currentmouseclick,mouseclicked);
		angle++;
		TheGame->HandlePlayerInput(grender);
		TheGame->HandleShapesScripts(grender);


		Handlefpstimer(countedFrames, fpsTimer);
		SDL_RenderPresent(grender);
		//cout << framecaptimer.getTicks() << endl;
		if (framecaptimer.getTicks() < 16.6667)//if greater than 1/60 of a second cap it
		{
			double delaytime = 16.6667 - framecaptimer.getTicks();
			SDL_Delay(delaytime);
			//cout << "delaying..." << endl;
		}
	}

	return 0;
}
bool InitializeSDL()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "Could not initialize SDL";
		success = false;
	}
	else
	{
		gwindow = SDL_CreateWindow("Gibo Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gwindow == 0)
		{
			cout << "could not create window";
			success = false;
		}
		else
		{
			gsurface = SDL_GetWindowSurface(gwindow);
			if (gsurface == 0)
			{
				cout << "could not upload surface";
				success = false;
			}
			else
			{
				int flags = IMG_INIT_PNG;
				if ((IMG_Init(flags) & flags) != flags)
				{
					cout << "failed to initialize png";
					success = false;
				}
				if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				{
					cout << "failed to scale quality";
				}
				grender = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);// | SDL_RENDERER_PRESENTVSYNC
				SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);

				TTF_Init();
				//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
			}
		}
	}
	return success;
}
void InitializeImages()
{
	gfont = TTF_OpenFont("NewAmsterdam.ttf", 28);
	SDL_Color textcolor = { 0,0,0 };
	SDL_Color textcolorwhite = { 255,255,255 };
	SDL_Color textcoloryellow = { 255,255,0 };
	SDL_Color textcolorblue = { 0,0,255 };
	fpstexture = loadtext("5", textcolorblue);
	playerskin = loadtexture("face.PNG");
	rectangleimage = loadtexture("square.PNG");
	triangleimage = loadseethroughwhite("triangle.PNG");
	lineimage = loadtexture("line.PNG");
	fourarrowbox = loadtexture("arrows.PNG");
	dottedbox = loadtexture("dottedbox.JPG");
	numberbox = loadtexture("number.PNG");
	deletebox = loadtexture("delete.PNG");
	rotatebox = loadtexture("rotate.PNG");
	scriptbox = loadtexture("script.PNG");
	rotateone = loadtexture("1.PNG");
	rotatenone = loadtexture("-1.PNG");
	rotatetwo = loadtexture("2.PNG");
	rotatentwo = loadtexture("-2.PNG");
	rotatethree = loadtexture("3.PNG");
	rotatenthree = loadtexture("-3.PNG");
	rotatefour = loadtexture("4.PNG");
	rotatenfour = loadtexture("-4.PNG");
	rotatefive = loadtexture("5.PNG");
	rotatenfive = loadtexture("-5.PNG");
	rotatezero = loadtexture("0.PNG");
	theleftarrow = loadtexture("leftarrow.PNG");
	therightarrow = loadtexture("rightarrow.PNG");
	plussign = loadtexture("add.PNG");
	subtract = loadtexture("subtract.PNG");
	playericon = loadtexture("stickfigure.PNG");
	hand = loadtexture("hand.PNG");
	zoomin = loadtexture("zoomin.PNG");
	normal = loadtexture("normal.PNG");
	handon = loadtexture("handon.PNG");
	copybox = loadtexture("copy.PNG");
	save = loadtexture("save.JPG");
	mainmenu = loadtexture("mainmenu.PNG");
	mainmenuload = loadtexture("mainmenuload.PNG");
	mainmenumake = loadtexture("mainmenumake.PNG");
	mainmenuquit = loadtexture("mainmenuquit.PNG");
	loadmenu = loadtexture("LoadMenu.PNG");
	gamemenu = loadtexture("gamemenu.PNG");
	gamemenuresume = loadtexture("gamemenuresume.PNG");
	gamemenumenu = loadtexture("gamemenumenu.PNG");
	gamemenuquit = loadtexture("gamemenuquit.PNG");
	damageicon = loadtexture("damageicon.PNG");
	damageiconred = loadtexture("damageiconred.PNG");
	cameraicon = loadtexture("camera.PNG");
	backgroundegypt = loadtexture("background1.PNG");
	run1 = loadseethroughwhite("frame0014.PNG");
	run2 = loadseethroughwhite("frame0015.PNG");
	run3 = loadseethroughwhite("frame0016.PNG");
	run4 = loadseethroughwhite("frame0017.PNG");
	run5 = loadseethroughwhite("frame0018.PNG");
	run6 = loadseethroughwhite("frame0019.PNG");
	run7 = loadseethroughwhite("frame0020.PNG");
	run8 = loadseethroughwhite("frame0021.PNG");
	idle1 = loadseethroughwhite("frame0000.PNG");
	idle2 = loadseethroughwhite("frame0001.PNG");
	idle3 = loadseethroughwhite("frame0002.PNG");
	idle4 = loadseethroughwhite("frame0003.PNG");
	idle5 = loadseethroughwhite("frame0004.PNG");
	idle6 = loadseethroughwhite("frame0005.PNG");
	jump1 = loadseethroughwhite("frame0032.PNG");
	jump2 = loadseethroughwhite("frame0032.PNG");
	jump3 = loadseethroughwhite("frame0032.PNG");
	jump4 = loadseethroughwhite("frame0032.PNG");
	portalicon = loadseethroughwhite("portalicon.PNG");
	doublejumpericon = loadseethroughwhite("doublejumpericon.PNG");
	lrarrows = loadtexture("lrarrows.PNG");
	udarrows = loadtexture("udarrows.PNG");
	distanceicon = loadtexture("distanceicon.PNG");
	speedicon = loadtexture("speedicon.PNG");
	circleimage = loadtexture("circle.PNG");
	bounceicon = loadseethroughwhite("bounceicon.PNG");
	shootericon = loadtexture("shootericon.PNG");
	runicon = loadtexture("runicon.PNG");
	menu = loadtexture("GiboEngineLogo1.PNG");
	menuplay = loadtexture("logoplay.PNG");
	menuload = loadtexture("logoload.PNG");
	menunew = loadtexture("logonew.PNG");
	menuquit = loadtexture("logoquit.PNG");
	savemenu = loadtexture("savemenu.PNG");
	savemenu1 = loadtexture("savemenu1.PNG");
	savemenu2 = loadtexture("savemenu2.PNG");
	savemenu3 = loadtexture("savemenu3.PNG");
	ingamemenu = loadtexture("ingamemenu.PNG");
	portaliconleft = loadtexture("portaliconleft.PNG");
	portaliconright = loadtexture("portaliconright.PNG");
	checkpointicon = loadtexture("checkpointicon.PNG");
	balljump = loadseethroughwhite("balljump.PNG");
	green = loadtexture("green.PNG");
	gray = loadtexture("gray.JPG");
	bluecircle = loadtexture("bluecircle.PNG");
	redcircle = loadseethroughwhite("redcircle.PNG");
	red = loadtexture("red.PNG");

	anumber = loadtext("1", textcolor);
}
SDL_Texture* loadtext(string s, SDL_Color textcolor)
{
	SDL_Surface* tempsurface = TTF_RenderText_Blended_Wrapped(gfont, s.c_str(), textcolor, SCREEN_WIDTH);
	SDL_Texture* returntexture;
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	//cout << tempsurface->w << " " << tempsurface->h;
	//get width and height
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
SDL_Texture* loadtexture(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	//SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 255, 255, 255));
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
SDL_Texture* loadseethroughwhite(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 255, 255, 255)); //white
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void Handlefpstimer(int& countedframe, LTimer& fpstimer)
{
	stringstream timetext;
	SDL_Rect fpsrect = { SCREEN_WIDTH - 100,0,125,50 };
	if (static_cast<int>(fpstimer.getTicks() % 1000) - 10 <= 0)
	{
		countedframe = 0;
		fpstimer.start();
	}
	double avgFPS = countedframe / (fpstimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	timetext.str("");
	timetext << "FPS: " << avgFPS;
	SDL_Color black = { 0,0,0 };
	fpstexture = loadtext(timetext.str().c_str(), black);
	SDL_RenderCopy(grender, fpstexture, 0, &fpsrect);
	countedframe++;
}
int AngleofLine(vec2d one, vec2d two, SDL_Renderer* grender)
{
	vec2d center(((one.x + two.x) / 2), ((one.y + two.y) / 2));
	double radius = sqrt(pow(two.x - one.x, 2) + pow(two.y - one.y, 2)) / 2;

	double slopeAngle = 0;
	double xdistancefromcenter = one.x - center.x;
	slopeAngle = acos(xdistancefromcenter / radius);//% 90
	slopeAngle = slopeAngle * 180 / 3.14;
	int theslope = slopeAngle;
	if (theslope > 90)
	{
		theslope = 180 - slopeAngle;
	}

	return theslope;
}
void Menu(Game* & TheGame)
{
	SDL_Rect play = { (SCREEN_WIDTH / 2) - 130,(SCREEN_HEIGHT / 2) - 60,210,60 };
	SDL_Rect load = { (SCREEN_WIDTH/2) - 130,(SCREEN_HEIGHT/2),210,65 };
	SDL_Rect make = { (SCREEN_WIDTH / 2) - 130,load.y + 65,210,65 };
	SDL_Rect quit = { (SCREEN_WIDTH / 2) - 130,load.y + 130,210,70 };
	SDL_Rect back = { 0,0,110,90 };
	SDL_Rect save1 = { (SCREEN_WIDTH / 2) - 400,(SCREEN_HEIGHT / 2)-90,150,150 };
	SDL_Rect save2 = { (SCREEN_WIDTH / 2) - 100,(SCREEN_HEIGHT / 2) - 90,150,150 };
	SDL_Rect save3 = { (SCREEN_WIDTH / 2) + 200,(SCREEN_HEIGHT / 2) - 90,150,150 };
	SDL_Texture* image = menu;
	int menuscene = 0;//0 is main menu, 1 is play menu, 2 is load menu
		bool exitmenu = false;
		int angle = 0;
		SDL_Event e;
		while (exitmenu == false)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_MOUSEMOTION)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (menuscene == 0)
					{
						if (x <= play.x + play.w && x >= play.x && y <= play.y + play.h && y >= play.y)
						{
							image = menuplay;
						}
						else if (x <= load.x + load.w && x >= load.x && y <= load.y + load.h && y >= load.y)
						{
							image = menuload;
						}
						else if (x <= make.x + make.w && x >= make.x && y <= make.y + make.h && y >= make.y)
						{
							image = menunew;
						}
						else if (x <= quit.x + quit.w && x >= quit.x && y <= quit.y + quit.h && y >= quit.y)
						{
							image = menuquit;
						}
						else
						{
							image = menu;
						}
					}
					else if(menuscene == 1)
					{
						if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
						{
							image = savemenu1;;
						}
						else if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
						{
							image = savemenu2;

						}
						else if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
						{
							image = savemenu3;
						}
						else
						{
							image = savemenu;
						}
					}
					else if (menuscene == 2)
					{
						if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
						{
							image = savemenu1;;
						}
						else if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
						{
							image = savemenu2;

						}
						else if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
						{
							image = savemenu3;
						}
						else
						{
							image = savemenu;
						}
					}
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (menuscene == 0)
					{
						if (x <= play.x + play.w && x >= play.x && y <= play.y + play.h && y >= play.y)
						{
							image = savemenu;
							menuscene = 1;
						}
						if (x <= load.x + load.w && x >= load.x && y <= load.y + load.h && y >= load.y)
						{
							image = savemenu;
							menuscene = 2;
						}
						if (x <= make.x + make.w && x >= make.x && y <= make.y + make.h && y >= make.y)
						{
							delete TheGame;
							TheGame = new Game;
							exitmenu = true;
						}
						if (x <= quit.x + quit.w && x >= quit.x && y <= quit.y + quit.h && y >= quit.y)
						{
							SDL_Quit();
							exit(0);
						}
					}
					else if(menuscene == 1)
					{
						if (x <= back.x + back.w && x >= back.x && y <= back.y + back.h && y >= back.y)
						{
							image = menu;
							menuscene = 0;
						}
						if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(1);
							if (answer)
							{
								TheGame->SetPlayerMode(1);
								exitmenu = true;
							}
						}
						if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(2);
							if (answer)
							{
								TheGame->SetPlayerMode(1);
								exitmenu = true;
							}
						}
						if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(3);
							if (answer)
							{
								TheGame->SetPlayerMode(1);
								exitmenu = true;
							}
						}
					}
					else if (menuscene == 2)
					{
						if (x <= back.x + back.w && x >= back.x && y <= back.y + back.h && y >= back.y)
						{
							image = menu;
							menuscene = 0;
						}
						if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(1);
							if (answer)
							{
								TheGame->SetPlayerMode(0);
								exitmenu = true;
							}
						}
						if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(2);
							if (answer)
							{
								TheGame->SetPlayerMode(0);
								exitmenu = true;
							}
						}
						if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
						{
							delete TheGame;
							TheGame = new Game;
							bool answer = TheGame->LoadGame(3);
							if (answer)
							{
								TheGame->SetPlayerMode(0);
								exitmenu = true;
							}
						}
					}
				}
			}
		SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
		SDL_RenderClear(grender);
		SDL_RenderCopy(grender, image, 0, 0);
		SDL_RenderPresent(grender);
	}
}
void SaveMenu(Game *& TheGame)
{
	SDL_Rect back = { 0,0,110,90 };
	SDL_Rect save1 = { (SCREEN_WIDTH / 2) - 400,(SCREEN_HEIGHT / 2) - 90,150,150 };
	SDL_Rect save2 = { (SCREEN_WIDTH / 2) - 100,(SCREEN_HEIGHT / 2) - 90,150,150 };
	SDL_Rect save3 = { (SCREEN_WIDTH / 2) + 200,(SCREEN_HEIGHT / 2) - 90,150,150 };
	SDL_Texture* image = savemenu;
	bool exitmenu = false;
	SDL_Event e;
	while (exitmenu == false)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
				{
					image = savemenu1;
				}
				else if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
				{
					image = savemenu2;

				}
				else if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
				{
					image = savemenu3;
				}
				else
				{
					image = savemenu;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x <= back.x + back.w && x >= back.x && y <= back.y + back.h && y >= back.y)
				{
					exitmenu = true;
				}
				if (x <= save1.x + save1.w && x >= save1.x && y <= save1.y + save1.h && y >= save1.y)
				{
					TheGame->SaveGame(1);
					exitmenu = true;
				}
				if (x <= save2.x + save2.w && x >= save2.x && y <= save2.y + save2.h && y >= save2.y)
				{
					TheGame->SaveGame(2);
					exitmenu = true;
				}
				if (x <= save3.x + save3.w && x >= save3.x && y <= save3.y + save3.h && y >= save3.y)
				{
					TheGame->SaveGame(3);
					exitmenu = true;
				}
			}
		}
		SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
		SDL_RenderClear(grender);
		SDL_RenderCopy(grender, image, 0, 0);
		SDL_RenderPresent(grender);
	}
}
void InGameMenu(Game *& TheGame, bool & renderz, vec2d & point, bool clicked)
{
	//print menu and take input
	SDL_Rect back = { 0,0,110,90 };
	SDL_Rect menu = { (SCREEN_WIDTH / 2) - 100,(SCREEN_HEIGHT / 2) - 175,200,350 };
	SDL_Rect menureturn = { (SCREEN_WIDTH / 2) - 50,(SCREEN_HEIGHT / 2) - 30,80,30 };
	SDL_Rect menumain = { (SCREEN_WIDTH / 2) - 60,(SCREEN_HEIGHT / 2) + 30,110,50 };
	SDL_Rect menuquit = { (SCREEN_WIDTH / 2) - 30,(SCREEN_HEIGHT / 2) + 90,50,40 };
	SDL_Texture* image = ingamemenu;
	if (clicked)
	{
		int x, y;
		x = point.x; y = point.y;
		if (x <= menureturn.x + menureturn.w && x >= menureturn.x && y <= menureturn.y + menureturn.h && y >= menureturn.y)
		{
			renderz = false;
		}
		if (x <= menumain.x + menumain.w && x >= menumain.x && y <= menumain.y + menumain.h && y >= menumain.y)
		{
			renderz = false;
			menuset = true;
		}
		if (x <= menuquit.x + menuquit.w && x >= menuquit.x && y <= menuquit.y + menuquit.h && y >= menuquit.y)
		{
			SDL_Quit();
			exit(0);
		}
	}
	SDL_RenderCopy(grender, image, 0, &menu);
}