#pragma once
#include "Rectangle.h"

struct GuiSquare
{
	SDL_Rect rect;
	SDL_Texture* text;

	GuiSquare()
	{
		text = 0;
	}
	~GuiSquare()
	{
		text = 0;
	}
	GuiSquare(int x, int y, int h, int w, SDL_Texture* texture)
	{
		rect.x = x; rect.y = y; rect.h = h; rect.w = w;
		text = texture;
	}
	void GuiSquareInitialize(int x, int y, int h, int w, SDL_Texture* texture)
	{
		rect.x = x; rect.y = y; rect.h = h; rect.w = w;
		text = texture;
	}
	void PrintTexture(SDL_Renderer* grender)
	{
		SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
		SDL_RenderCopy(grender, text, 0, &rect);
	}
};
class LevelMakergui
{
public:
	LevelMakergui();
	~LevelMakergui();
	bool IsMouseInRect(int x, int y, SDL_Rect therect);
	void LevelMakerguiInitialize();
	void Print(SDL_Renderer* grender);
	void ChangeSceneTexture(SDL_Texture* textz);
	void ToggleDrag();
	bool IsDragOn();
	bool IsMouseDown();
	void SetHoldClick(bool set);
	void SetMouseposition(int x, int y);
	vec2d Accessmouseposition();
	GuiSquare GetSquareBox();
	GuiSquare GetTriangleBox();
	GuiSquare GetPolyLineBox();
	GuiSquare GetcircleBox();
	GuiSquare GetAddSceneBox();
	GuiSquare GetDoubleJumperBox();
	GuiSquare GetBounceBox();
	GuiSquare GetPortalBox();
	GuiSquare GetSubtractSceneBox();
	GuiSquare GetDragSceneBox();
	GuiSquare GetNormalBox();
	GuiSquare GetLeftArrow();
	GuiSquare GetRightArrow();
	GuiSquare GetSaveBox();
	GuiSquare GetPlayerBox();
	GuiSquare GetCameraBox();
	GuiSquare GetShooterBox();
	GuiSquare GetCheckpointBox();

private:
	GuiSquare CreateSquareBox;
	GuiSquare CreateTriangleBox;
	GuiSquare CreatePolyLineBox;
	GuiSquare CreateCircleBox;
	GuiSquare CreatePortalBox;
	GuiSquare CreateShooterBox;
	GuiSquare CreateDoubleJumper;
	GuiSquare CreateBounceBox;
	GuiSquare AddSceneBox;
	GuiSquare SubtractSceneBox;
	GuiSquare DragSceneBox;
	GuiSquare NormalBox;
	GuiSquare SaveBox;
	GuiSquare PlayerBox;
	GuiSquare CameraBox;
	GuiSquare CreateCheckpointBox;
	bool DragSceneon;
	bool holdclick;
	vec2d mouseposition;
	vector<GuiSquare> SceneSwitchbox;
};
LevelMakergui::LevelMakergui()
{

}
void LevelMakergui::LevelMakerguiInitialize()
{
	extern SDL_Texture* rectangleimage;
	extern SDL_Texture* triangleimage;
	extern SDL_Texture* plussign;
	extern SDL_Texture* theleftarrow;
	extern SDL_Texture* anumber;
	extern SDL_Texture* therightarrow;
	extern SDL_Texture* subtract;
	extern SDL_Texture* hand;
	extern SDL_Texture* normal;
	extern SDL_Texture* lineimage;
	extern SDL_Texture* save;
	extern SDL_Texture* playericon;
	extern SDL_Texture* cameraicon;
	extern SDL_Texture* portalicon;
	extern SDL_Texture* circleimage;
	extern SDL_Texture* shootericon;
	extern SDL_Texture* doublejumpericon;
	extern SDL_Texture* bounceicon;
	extern SDL_Texture* checkpointicon;
	DragSceneon = false;
	holdclick = false;
	mouseposition.x = 0; mouseposition.y = 0;
	CreateSquareBox.GuiSquareInitialize(0, 0, 50, 50, rectangleimage);
	CreateTriangleBox.GuiSquareInitialize(0, 55, 50, 50, triangleimage);
	CreatePolyLineBox.GuiSquareInitialize(0, 110, 50, 50, lineimage);
	CreateCircleBox.GuiSquareInitialize(0, 160, 50, 50, circleimage);
	CreatePortalBox.GuiSquareInitialize(0, 210, 50, 50, portalicon);
	CreateShooterBox.GuiSquareInitialize(0, 260, 50, 50, shootericon);
	CreateDoubleJumper.GuiSquareInitialize(0, 310, 50, 50, doublejumpericon);
	CreateBounceBox.GuiSquareInitialize(0, 360, 50, 50, bounceicon);
	CreateCheckpointBox.GuiSquareInitialize(0, 410, 50, 50, checkpointicon);
	AddSceneBox.GuiSquareInitialize(115, 5, 25, 25, plussign);
	SubtractSceneBox.GuiSquareInitialize(140, 5, 25, 25, subtract);
	DragSceneBox.GuiSquareInitialize(165, 5, 25, 25, hand);
	NormalBox.GuiSquareInitialize(190, 5, 25, 50, normal);
	SaveBox.GuiSquareInitialize(250, 5, 25, 25, save);
	PlayerBox.GuiSquareInitialize(280, 5, 25, 25, playericon);
	CameraBox.GuiSquareInitialize(310, 5, 25, 25, cameraicon);
	GuiSquare leftarrowbox(50, 5, 25, 25, theleftarrow);
	GuiSquare numberbox(72, 10, 15, 20, anumber);
	GuiSquare rightarrowbox(90, 5, 25, 25, therightarrow);
	SceneSwitchbox.push_back(leftarrowbox); SceneSwitchbox.push_back(numberbox); SceneSwitchbox.push_back(rightarrowbox);
}
LevelMakergui::~LevelMakergui()
{

}
void LevelMakergui::Print(SDL_Renderer* grender)
{
	CreateSquareBox.PrintTexture(grender);
	CreateTriangleBox.PrintTexture(grender);
	CreatePolyLineBox.PrintTexture(grender);
	CreateCircleBox.PrintTexture(grender);
	CreatePortalBox.PrintTexture(grender);
	CreateShooterBox.PrintTexture(grender);
	CreateDoubleJumper.PrintTexture(grender);
	CreateBounceBox.PrintTexture(grender);
	CreateCheckpointBox.PrintTexture(grender);
	AddSceneBox.PrintTexture(grender);
	SubtractSceneBox.PrintTexture(grender);
	DragSceneBox.PrintTexture(grender);
	NormalBox.PrintTexture(grender);
	SaveBox.PrintTexture(grender);
	PlayerBox.PrintTexture(grender);
	CameraBox.PrintTexture(grender);
	for (int i = 0; i < SceneSwitchbox.size(); i++)
		SceneSwitchbox[i].PrintTexture(grender);
}
bool LevelMakergui::IsMouseInRect(int x, int y, SDL_Rect therect)
{
	if (x > therect.x && x < therect.x + therect.w)
	{
		if (y<therect.y + therect.h && y>therect.y)
		{
			return true;
		}
	}
	return false;
}
GuiSquare LevelMakergui::GetSquareBox()
{
	return CreateSquareBox;
}
GuiSquare LevelMakergui::GetTriangleBox()
{
	return CreateTriangleBox;
}
GuiSquare LevelMakergui::GetPolyLineBox()
{
	return CreatePolyLineBox;
}
GuiSquare LevelMakergui::GetcircleBox()
{
	return CreateCircleBox;
}
GuiSquare LevelMakergui::GetAddSceneBox()
{
	return AddSceneBox;
}
GuiSquare LevelMakergui::GetPortalBox()
{
	return CreatePortalBox;
}
GuiSquare LevelMakergui::GetDoubleJumperBox()
{
	return CreateDoubleJumper;
}
GuiSquare LevelMakergui::GetCheckpointBox()
{
	return CreateCheckpointBox;
}
GuiSquare LevelMakergui::GetBounceBox()
{
	return CreateBounceBox;
}
GuiSquare LevelMakergui::GetShooterBox()
{
	return CreateShooterBox;
}
GuiSquare LevelMakergui::GetSubtractSceneBox()
{
	return SubtractSceneBox;
}
GuiSquare LevelMakergui::GetDragSceneBox()
{
	return DragSceneBox;
}
GuiSquare LevelMakergui::GetNormalBox()
{
	return NormalBox;
}
GuiSquare LevelMakergui::GetCameraBox()
{
	return CameraBox;
}
GuiSquare LevelMakergui::GetLeftArrow()
{
	return SceneSwitchbox[0];
}
GuiSquare LevelMakergui::GetRightArrow()
{
	return SceneSwitchbox[2];
}
GuiSquare LevelMakergui::GetSaveBox()
{
	return SaveBox;
}
GuiSquare LevelMakergui::GetPlayerBox()
{
	return PlayerBox;
}
void LevelMakergui::ChangeSceneTexture(SDL_Texture* textz)
{
	SceneSwitchbox[1].text = textz;
}
void LevelMakergui::ToggleDrag()
{
	extern SDL_Texture* handon;
	extern SDL_Texture* hand;
	DragSceneon = !DragSceneon;
	if(DragSceneBox.text == hand)
		DragSceneBox.text = handon;
	else
		DragSceneBox.text = hand;

}
bool LevelMakergui::IsDragOn()
{
	return DragSceneon;
}
void LevelMakergui::SetHoldClick(bool set)
{
	holdclick = set;
}
void LevelMakergui::SetMouseposition(int x, int y)
{
	mouseposition.x = x;
	mouseposition.y = y;
}
bool LevelMakergui::IsMouseDown()
{
	return holdclick;
}
vec2d LevelMakergui::Accessmouseposition()
{
	return mouseposition;
}