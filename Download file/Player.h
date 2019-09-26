#pragma once
#include <thread>
#include "Rectangle.h"
#include "Triangle.h"

#ifndef PLAYER_H
#define PLAYER_H


struct collisioninfo
{
	line theline;
	int lineangle;
	double lineslope;
	int sidehit;

	collisioninfo()
	{
		lineangle = 0;
		sidehit = 0;
	}
};
//physics lines are one pixel long so has to check physics every time player moves one
//could also give lines little hitboxes
//if your within circle then activate stuff for good fps
//if lines cross and within circle
//need to give lines equationsa
//what force was pushing you when you hit the object... now counteract that force
class Game;
class Player
{
public:
	Player();
	Player(int width, int height, SDL_Texture* atexture, int axposition = 0, int ayposition = 0, Game* thegame = 0);
	~Player();
	void PlayerInitialize(int width, int height, SDL_Texture* atexture, int axposition = 0, int ayposition = 0, Game* thegame = 0);
	void HandleInput(vector<Shapes*> theshapes, SDL_Renderer * grender);
	void Print(SDL_Renderer* grender);
	void IsPlayerHittingAnyShapes(vector<Shapes*> theshapes, SDL_Renderer * grender);
	bool checktwolinecollisiontest(vec2d two, vec2d two2, SDL_Renderer * grender);
	bool checkplayertriangle(vec2d one, vec2d one2, Shapes theshape);
	bool SegmentsIntersecttest(vec2d p3, vec2d p4);
	void MovePlayerToPosition(int x, int y);
	vec2d GetPlayerPosition();
	void LowerHealth(int x);
	bool IsPlayerAlive();
	void Respawn(int x, int y);
	double AccessPlayerx();
	double AccessPlayery();
	void MovePlayer(double x, double y);
	double AccessPlayerxvelocity();
	double AccessPlayeryvelocity();
	bool IsPlayerOnSlope();
	vec2d AccessDistanceMovedThisFrame();
	vec2d AccessCenter();
	void ToggleTeleported(bool i);
	bool AccessTeleported();
	SDL_Rect GetPlayerRect();
	bool GetDoubleJump();
	void SetDoubleJump(bool i);
	int GetJumpHeight();
	void SetJumpHeight(int i);
	void SetShowhitboxes(bool i);
	Rectangle* Gethitbox();
	void SetXamount(int i);
	int GetXamount();
	void SetYamount(int i);
	int GetYamount();
	int GetHeight();
	void SetHeight(int i);
	int GetWidth();
	void SetWidth(int i);
	void Setxspeed(int i);
	double Getxspeed();
	int GetTeleportSideHit();
	void SetTeleportedRight(bool i);
	bool GetTeleportedRight();
	Shapes* getcheckpoint();
private:
	Shapes* checkpoint;
	bool teleportright;
	int teleportsidehit;
	bool teleported;
	Game* theGame;
	vector<collisioninfo> playercollisioninfo;
	SDL_Rect playerRect;
	int playerwidth;
	int playerheight;
	SDL_Texture* texture;
	Rectangle* hitbox;
	Rectangle* feethitbox;
	double playerx;
	double playery;
	double xvelocity;
	double yvelocity;
	double playergravity = 5;
    double velocityx = 5;
	const double velocityy = 1;
	int health;
	bool alive;
	bool onslope;
	vec2d distancemovedthisframe;
	double lastxmoved;
	//trampoline stuff'
	bool bounceleft;
	bool bounceright;
	bool bounceup;
	bool bouncedown;
	int trampolinecounter;
	bool beingtrampolined;
	int trampolinex;
	int trampoliney;
	bool showhitboxes;
	//jump stuff
	int jumpheight;
	int doublejumpcounter;
	bool doublejump;
	bool canjump;
	bool jumping;
	int jumpcounter;
	bool running;
	int runningcounter;
	bool idle;
	int idlecounter;
	bool jumpanimation;
	int jumpcounteranimation;
	//hitbox stuff
	int amountx;
	int amounty;
	bool movingphysicsenabled;
	vector<int> movingsideshit;

	float area(int x1, int y1, int x2, int y2, int x3, int y3);
	bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);
	void Jump();
	void JumpStart();
	void JumpStartDouble();
	void Move(vector<Shapes*> theshapes, SDL_Renderer * grender);
	void Move2(vector<Shapes*> theshapes, SDL_Renderer * grender);
	void checkplayerwithlinescollision(vector<line> thelines, Shapes* theshape, SDL_Renderer * grender);
	int AngleofLine(vec2d one, vec2d two, SDL_Renderer* grender);
	double SlopeofLine(vec2d one, vec2d two, SDL_Renderer* grender);
	void PrintCollisioninfo();
	void UpdateHitBox();
	bool CircleCollision(int radiusplayer, vec2d center1, int radiusshape, vec2d center2);
	bool RectangleCollision(vector<vec2d> points1, vector<vec2d> points2);
	bool checktwolinecollision(vec2d one, vec2d one2, vec2d two, vec2d two2, SDL_Renderer * grender);
	bool checktwolinecollisionwithShapes(vec2d one, vec2d one2, vec2d two, vec2d two2, SDL_Renderer * grender, Shapes theshape);//*slope1 is player
	int Direction(vec2d p1, vec2d p2, vec2d p3);
	bool OnSegment(vec2d p1, vec2d p2, vec2d p3);
	bool SegmentsIntersect(vec2d p1, vec2d p2, vec2d p3, vec2d p4);
	void Animation();
	void RunningAnimation();
	void IdleAnimation();
	void JumpAnimation();
	void Trampolined();
	bool Find(int i);
};
#endif 
Player::~Player()
{
	playercollisioninfo.clear();
	playerRect = { 0,0,0,0 };
	texture = 0;
	hitbox = 0;
	feethitbox = 0;
	theGame = 0;
}
Player::Player()
{



}
Player::Player(int width, int height, SDL_Texture* atexture, int axposition, int ayposition,Game* thegame)
{
	teleportright = false;
	amountx = 40;
	amounty = 25;
	playerwidth = width;
	playerheight = height;
	showhitboxes = false;
	jumpheight = 8;
	bounceleft = false;
	bounceright = false;
	bounceup = false;
	bouncedown = false;
	trampolinecounter = 0;
	trampolinex = 0;
	trampoliney = 0;
	beingtrampolined = false;
	doublejump = false;
	doublejumpcounter = 0;
	teleported = false;
	theGame = thegame;
	jumpanimation = false;
	jumpcounter = 0;
	lastxmoved = 1;
	jumpcounter = 0;
	jumping = false;
	canjump = true;
	onslope = false;
	health = 5;
	alive = true;
	playerx = axposition;
	playery = ayposition;
	playercollisioninfo.clear();
	playerRect = { axposition,ayposition,width,height };
	texture = atexture;
	xvelocity = 0;
	yvelocity = 0;
	vec2d one(axposition+1, ayposition+1);
	vec2d two(axposition + width-1, ayposition+1);
	vec2d three(axposition + width-1, ayposition + height-1);
	vec2d four(axposition+1, ayposition + height-1);
	hitbox = new Rectangle(one, two, three, four);
	int distancex = two.x - one.x;
	int distancey = three.y - two.y;
	vec2d onefeet(one.x + (distancex / 4), one.y + (distancey/2));
	vec2d twofeet(two.x - (distancex/4),two.y + (distancey / 2));
	vec2d threefeet(three.x - (distancex/4),three.y);
	vec2d fourfeet(four.x + (distancex / 4), four.y);
	feethitbox = new Rectangle(onefeet, twofeet, threefeet, fourfeet);
}
void Player::PlayerInitialize(int width, int height, SDL_Texture* atexture, int axposition, int ayposition, Game* thegame)
{
	teleportright = false;
	playerwidth = width;
	playerheight = height;
	amountx = 40;
	amounty = 25;
	showhitboxes = false;
	jumpheight = 8;
	bounceleft = false;
	bounceright = false;
	bounceup = false;
	bouncedown = false;
	trampolinecounter = 0;
	trampolinex = 0;
	trampoliney = 0;
	beingtrampolined = false;
	doublejump = false;
	doublejumpcounter = 0;
	teleported = false;
	theGame = thegame;
	idle = false;
	idlecounter = 0;
	runningcounter = 0;
	running = false;
	jumpcounter = 0;
	jumping = false;
	canjump = true;
	onslope = false;
	health = 5;
	alive = true;
	playerx = axposition;
	playery = ayposition;
	playercollisioninfo.clear();
	playerRect = { axposition,ayposition,width,height };
	texture = atexture;
	xvelocity = 0;
	yvelocity = 0;
	/*vec2d one(axposition + 1, ayposition + 1);
	vec2d two(axposition + width - 1, ayposition + 1);
	vec2d three(axposition + width - 1, ayposition + height - 1);
	vec2d four(axposition + 1, ayposition + height - 1);*/
	vec2d one(axposition + amountx, ayposition + amounty);
	vec2d two(axposition + width - amountx, ayposition + amounty);
	vec2d three(axposition + width - amountx, ayposition + height - amounty);
	vec2d four(axposition + amountx, ayposition + height - amounty);
	//playerRect = { axposition,ayposition,static_cast<int>(two.x-one.x),static_cast<int>(three.y-two.y)};
	playerx = axposition;
	playery = ayposition;
	hitbox = new Rectangle(one, two, three, four);
	int distancex = two.x - one.x;
	int distancey = three.y - two.y;
	vec2d onefeet(one.x + (distancex / 4), one.y);
	vec2d twofeet(two.x - (distancex / 4), two.y);
	vec2d threefeet(three.x - (distancex / 4), three.y);
	vec2d fourfeet(four.x + (distancex / 4), four.y);
	feethitbox = new Rectangle(onefeet, twofeet, threefeet, fourfeet);
}
int Player::GetTeleportSideHit()
{
	return teleportsidehit;
}
void Player::SetTeleportedRight(bool i)
{
	teleportright = i;
}
bool Player::GetTeleportedRight()
{
	return teleportright;
}
int Player::GetHeight()
{
	return playerheight;
}
Shapes* Player::getcheckpoint()
{
	return checkpoint;
}
void Player::SetHeight(int i)
{
	playerheight = i;
}
int Player::GetWidth()
{
	return playerwidth;
}
void Player::SetWidth(int i)
{
	playerwidth = i;
}
void Player::Setxspeed(int i)
{
	velocityx = i;
}
double Player::Getxspeed()
{
	return velocityx;
}
bool Player::GetDoubleJump()
{
	return doublejump;
}
void Player::SetDoubleJump(bool i)
{
	doublejump = i;
}
int Player::GetJumpHeight()
{
	return jumpheight;
}
Rectangle* Player::Gethitbox()
{
	return hitbox;
}
void Player::SetJumpHeight(int i)
{
	jumpheight = i;
}
void Player::SetShowhitboxes(bool i)
{
	showhitboxes = i;
}
void Player::SetXamount(int i)
{
	amountx = i;
}
int Player::GetXamount()
{
	return amountx;
}
void Player::SetYamount(int i)
{
	amounty = i;
}
int Player::GetYamount()
{
	return amounty;
}
void Player::UpdateHitBox()
{
	/*vec2d one(playerx + 1, playery + 1);
	vec2d two(playerx + playerRect.w - 1, playery + 1);
	vec2d three(playerx + playerRect.w - 1, playery + playerRect.h - 1);
	vec2d four(playerx + 1, playery + playerRect.h - 1);*/
	playerRect.x = round(playerx);
	playerRect.y = round(playery);
	playerRect.w = playerwidth;
	playerRect.h = playerheight;
	vec2d one(playerx + amountx, playery + amounty);
	vec2d two(playerx + playerRect.w - amountx, playery + amounty);
	vec2d three(playerx + playerRect.w - amountx, playery + playerRect.h - amounty);
	vec2d four(playerx + amountx, playery + playerRect.h - amounty);
	hitbox = new Rectangle(one, two, three, four);
	int distancex = two.x - one.x;
	int distancey = three.y - two.y;
	vec2d onefeet(one.x + (distancex / 3), one.y);
	vec2d twofeet(two.x - (distancex / 3), two.y);
	vec2d threefeet(three.x - (distancex / 3), three.y);
	vec2d fourfeet(four.x + (distancex / 3), four.y);
	feethitbox = new Rectangle(onefeet, twofeet, threefeet, fourfeet);
}
vec2d Player::AccessCenter()
{
	double x = hitbox->AccessPoints()[0].x + ((hitbox->AccessPoints()[1].x - hitbox->AccessPoints()[0].x) / 2);
	double y = hitbox->AccessPoints()[0].y + ((hitbox->AccessPoints()[3].y - hitbox->AccessPoints()[0].y) / 2);
	vec2d sup(x, y);
	return sup;
}
void Player::PrintCollisioninfo()
{
	for (int i = 0; i < playercollisioninfo.size(); i++)
	{
		cout << "side hit: " << playercollisioninfo[i].sidehit << endl;
		cout << "angle: " << playercollisioninfo[i].lineangle << endl;
		cout << "linepoint: (" << playercollisioninfo[i].theline.pointone.x << ", " << playercollisioninfo[i].theline.pointone.y << ")" << endl << endl;
	}
}
void Player::ToggleTeleported(bool i)
{
	teleported = i;
}
bool Player::AccessTeleported()
{
	return teleported;
}
double Player::AccessPlayerxvelocity()
{
	return xvelocity;
}
double Player::AccessPlayeryvelocity()
{
	return yvelocity;
}
void Player::MovePlayer(double x, double y)
{
	playerx += x;
	playery += y;
	UpdateHitBox();
}
bool Player::IsPlayerAlive()
{
	return alive;
}
bool Player::IsPlayerOnSlope()
{
	return onslope;
}
vec2d Player::AccessDistanceMovedThisFrame()
{
	return distancemovedthisframe;
}
void Player::Print(SDL_Renderer* grender)
{
	Animation();
	SDL_SetRenderDrawColor(grender, 0, 0, 0, 255);
	playerRect.x = round(playerx);
	playerRect.y = round(playery);
	playerRect.w = playerwidth;
	playerRect.h = playerheight;
	if (lastxmoved >= 0)
	{
		SDL_RenderCopyEx(grender, texture, 0, &playerRect, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopyEx(grender, texture, 0, &playerRect, 0, 0, SDL_FLIP_NONE);
	}
	if (showhitboxes)
	{
		hitbox->Print(grender);
		//feethitbox->Print(grender);
		SDL_RenderDrawRect(grender, &playerRect);
	}
}
void Player::Animation()
{
	if (jumpcounter < 1 && canjump)
	{
		if (distancemovedthisframe.x != 0)
		{
			running = true;
			idle = false;
			idlecounter = 0;
		}
		else
		{
			idle = true;
			running = false;
			runningcounter = 0;
		}
	}
	if (running)
	{
		RunningAnimation();
	}
	if (idle)
	{
		IdleAnimation();
	}
	if (jumpcounter>=1)
	{
		jumpanimation = true;
		running = false;
		idle = false;
	}
	else
	{
		jumpanimation = false;
		jumpcounteranimation = 0;
	}
	if (jumpanimation)
	{
		JumpAnimation();
	}
}
void Player::IdleAnimation()
{
	extern SDL_Texture* idle1;
	extern SDL_Texture* idle2;
	extern SDL_Texture* idle3;
	extern SDL_Texture* idle4;
	extern SDL_Texture* idle5;
	extern SDL_Texture* idle6;
	vector<SDL_Texture*> images;
	images.push_back(idle1); images.push_back(idle2); images.push_back(idle3); images.push_back(idle4); images.push_back(idle5); images.push_back(idle6);
	idlecounter++;
	int amount = (idlecounter %36) / 6;
	texture = images[amount];
}
SDL_Rect Player::GetPlayerRect()
{
	return playerRect;
}
void Player::JumpAnimation()
{
	extern SDL_Texture* jump1;
	extern SDL_Texture* jump2;
	extern SDL_Texture* jump3;
	extern SDL_Texture* jump4;
	vector<SDL_Texture*> images;
	images.push_back(jump1); images.push_back(jump2); images.push_back(jump3); images.push_back(jump4);
	jumpcounteranimation++;
	int amount = (jumpcounteranimation) / 6;
	if (amount < 3)
	{
		texture = images[amount];
	}
}
void Player::RunningAnimation()
{
	extern SDL_Texture* run1;
	extern SDL_Texture* run2;
	extern SDL_Texture* run3;
	extern SDL_Texture* run4;
	extern SDL_Texture* run5;
	extern SDL_Texture* run6;
	extern SDL_Texture* run7;
	extern SDL_Texture* run8;
	vector<SDL_Texture*> images;
	images.push_back(run1); images.push_back(run2); images.push_back(run3); images.push_back(run4); images.push_back(run5); images.push_back(run6);
	images.push_back(run7); images.push_back(run8);
	runningcounter++;
	int amount = (runningcounter % 48)/6;
	texture = images[amount];
}
vec2d Player::GetPlayerPosition()
{
	vec2d tmp(playerx, playery);
	return tmp;
}
void Player::MovePlayerToPosition(int x, int y)
{
	playerx = x;
	playery = y;
	UpdateHitBox();
}
double Player::AccessPlayerx()
{
	return playerx;
}
double Player::AccessPlayery()
{
	return playery;
}
void Player::Respawn(int x,int y)
{
	health = 5;
	alive = true;
	MovePlayerToPosition(x, y);
	//set player to currentcheckpoint
}
void Player::LowerHealth(int x)
{
	health -= x;
	if (health <= 0)
	{
		alive = false;
	}
}
void Player::HandleInput(vector<Shapes*> theshapes, SDL_Renderer * grender)
{
	xvelocity = 0;
	yvelocity = 0;
	const Uint8* currentkeystatereset = SDL_GetKeyboardState(0);
	if (currentkeystatereset[SDL_SCANCODE_D] == 1)
	{
		xvelocity = velocityx;
	}
	else if (currentkeystatereset[SDL_SCANCODE_A] == 1)
	{
		xvelocity = -velocityx;
	}
	else
	{
		xvelocity = 0;
	}
	/*if (currentkeystatereset[SDL_SCANCODE_S] == 1)
	{
		yvelocity = velocityy;
	}
	else if (currentkeystatereset[SDL_SCANCODE_W] == 1)
	{
		yvelocity = -velocityy;
	}*/
	if (currentkeystatereset[SDL_SCANCODE_SPACE] == 1)
	{
		if (canjump)
		{
			beingtrampolined = false;
			trampolinecounter = 0;
			//JumpStartDouble();
			JumpStart();
		}
	}
	else
	{
		if (doublejumpcounter > 0 && canjump == false)
		{
			doublejumpcounter--;
			canjump = true;
		}
		yvelocity = 0;
	}
	if (jumping && (currentkeystatereset[SDL_SCANCODE_SPACE] == 1 || jumpcounter < 6))
	{
		Jump();

	}
	else
	{
		jumping = false;
		jumpcounter = 0;
	}
	if (showhitboxes)
	{

	}
	else
	{
		yvelocity += playergravity;
	}
	if (beingtrampolined)
	{
		Trampolined();
	}
	movingphysicsenabled = true;
	//vec2d maintainplayerposition(playerx, playery);
	IsPlayerHittingAnyShapes(theshapes, grender);//run onceto increate x or yvelocity based on moving objects, can only run moving objects if its inneficent
	movingphysicsenabled = false;
	playercollisioninfo.clear();
	//playerx = maintainplayerposition.x; playery = maintainplayerposition.y;
	UpdateHitBox();
	Move(theshapes,grender);
}
void Player::Trampolined()
{
	double value = 0;
	if (bounceup)
	{
		value = -pow(trampolinecounter / trampolinex, 2) + trampolinex;
		if (value >= -1)
		{
			yvelocity -= playergravity;
			yvelocity -= value;
		}
	}
	if (bouncedown)
	{
		value = pow(trampolinecounter / trampolinex, 2) - trampolinex;
		if (value < -1)
		{
			yvelocity -= playergravity;
			yvelocity -= value;
		}
	}
	if (bounceleft)
	{
		value = pow(trampolinecounter / trampolinex, 2) - trampolinex;
		if (value < -1)
		{
			xvelocity = 0;
			xvelocity += value;
		}
	}
	if (bounceright)
	{
		value = -pow(trampolinecounter / trampolinex, 2) + trampolinex;
		if (value >= -1)
		{
			xvelocity = 0;
			xvelocity += value;
		}
	}
	trampolinecounter++;
}
void Player::Jump()
{
	//default is 8 for jumpheight
	double value = -pow(jumpcounter/7,2)+ jumpheight;//3*log(jumpcounter+1) //(1/sqrt(jumpcounter+1))*10
	if (value >= -1)
	{
		yvelocity += -playergravity - value;
	}
	else
	{
		jumping = false;
		jumpcounter = 0;
	}
	jumpcounter++;
}
void Player::JumpStart()
{
	jumpcounter = 0;
	jumping = true;
	canjump = false;
}
void Player::JumpStartDouble()
{
	jumpcounter = 0;
	jumping = true;
	canjump = false;
	//doublejumpcounter++;
}
void Player::Move(vector<Shapes*> theshapes, SDL_Renderer * grender)
{
	/*error fix info
	there were wierd bugs but I think it was all dealing with precision. The player position I made doubles and just casted when printing
	and the cos and sin values I rounded to 3 decimal places to avoid weird .0008 stuff this seemse to work now. It was just precision errors
	*/
	/*corner error fix
	in real life you dont move x and y then check like go in the ground and move right then check.
	So I move y first then deal with y physics. then move x and deal with x physics. this has to run the physics twice though. but can make efficient with circle
	*/
	/*slope error fix
	just see if the slope isnt horinzontal or vertical then get the ratio of x to y by 1/slope move x one then move y to that ratio. It automatically takes care of x slow down
	because y moves up then it tries to go right if it hits then y goes up again. clean.
	*/
	/*multiple object fix
	made it so it checks x first because x changes y but y doesnt change x. So x changes y then we can update y and from there the y can take care of it.
	*/
	/*slope bouncy visual fix
	just made it so if its a slope it claculates the x and y needed first without actually moving player. then it moves y plaeyr based on that, then x player based on that very smooth
	a little inneficient.
	*/
	/*slope bug fixes
	bug where if you were not actually on the slope it would just raise you up, now youre bottom y has to be higher than the slopes bottom y to actually run along slope
	still a bug 1 pixel where you can jump through the roof but its 1 pixel
	*/
	/*moving object error fix
	*/
	//double extraxamountinvelocity = xvelocitysign * (abs(xvelocity - static_cast<int>(xvelocity))) / abs(xvelocity);
	for (int i = 0; i < playercollisioninfo.size(); i++)
	{
		//cout << i<<" : "<<playercollisioninfo[i].lineangle<<" "<<playercollisioninfo[i].sidehit<<endl;
	}
	if (playercollisioninfo.size() == 0)
	{
		//cout << "empty" << endl;
	}
	vec2d startposition(playerx, playery);
	bool breakfree = false;
	bool ychangedfromslope = false;
	double ychangeamount = 0;
	double xchangeamount = 0;
	double counter = 0;
	int xvelocitysign = 1;
	if (xvelocity < 0)
		xvelocitysign = -1;
	for (int x = 0; x < abs(xvelocity); x++)
	{
		if (breakfree)
			break;
		playerx += xvelocitysign;
		counter += xvelocitysign;
		UpdateHitBox();
		IsPlayerHittingAnyShapes(theshapes, grender);
		for (int i = 0; i < playercollisioninfo.size(); i++)
		{
			vec2d smallerpoint = playercollisioninfo[i].theline.pointone;
			vec2d largerpoint = playercollisioninfo[i].theline.pointtwo;
			if (playercollisioninfo[i].theline.pointtwo.y > smallerpoint.y)
			{
				smallerpoint = playercollisioninfo[i].theline.pointtwo;
				largerpoint = playercollisioninfo[i].theline.pointone;
			}
			if (playercollisioninfo[i].sidehit == 0 || playercollisioninfo[i].sidehit == 2)
			{
				if (playercollisioninfo[i].lineslope != 0)
				{
					if (playercollisioninfo[i].lineangle >= 80)// playery+ playerRect.h >= smallerpoint.y
					{
						playerx -= xvelocitysign;
						break;
					}
					if (hitbox->AccessPoints()[0].y + (hitbox->AccessPoints()[3].y - hitbox->AccessPoints()[0].y) - 5 >= smallerpoint.y)
					{
						playerx -= xvelocitysign;
						break;
					}
					if (xvelocitysign < 0 && playercollisioninfo[i].lineslope < 0 || xvelocitysign >= 0 && playercollisioninfo[i].lineslope >= 0)
					{
						int height = playercollisioninfo[i].theline.pointone.y;
						if (playercollisioninfo[i].theline.pointtwo.y < height)
							height = playercollisioninfo[i].theline.pointtwo.y;
						if(hitbox->AccessPoints()[0].y + (hitbox->AccessPoints()[3].y- hitbox->AccessPoints()[0].y) - 5 > height)
						{
							playerx -= xvelocitysign;
							break;
						}
					}
					ychangedfromslope = true;
					playerx -= counter;
					xchangeamount = xvelocity * ((90.0 - playercollisioninfo[i].lineangle) / 90.0);
					ychangeamount = -abs(playercollisioninfo[i].lineslope);;
					breakfree = true;
					break;
				}
			}
			if (playercollisioninfo[i].sidehit == 1 || playercollisioninfo[i].sidehit == 3)
			{
				if ((round(sin((playercollisioninfo[i].lineangle * 3.14) / 180) * 1000.0) / 1000.0) <= .001)//horizontal line
				{

				}
				else if (playercollisioninfo[i].lineslope == 0) //vertical
				{
					playerx -= xvelocitysign;
				}
				else
				{
					if (playercollisioninfo[i].lineangle >= 80)// || playery + playerRect.h >= smallerpoint.y
					{
						playerx -= xvelocitysign;
						break;
					}
					if (hitbox->AccessPoints()[0].y + (hitbox->AccessPoints()[3].y - hitbox->AccessPoints()[0].y) - 5 >= smallerpoint.y)//&&abs(slope) >.03
					{
						playerx -= xvelocitysign;
						break;
					}
					if (xvelocitysign < 0 && playercollisioninfo[i].lineslope < 0 || xvelocitysign >=0 && playercollisioninfo[i].lineslope >= 0)
					{
						int height = playercollisioninfo[i].theline.pointone.y;
						if (playercollisioninfo[i].theline.pointtwo.y < height)
							height = playercollisioninfo[i].theline.pointtwo.y;
						if (hitbox->AccessPoints()[0].y + (hitbox->AccessPoints()[3].y - hitbox->AccessPoints()[0].y) - 5 > height)
						{
							playerx -= xvelocitysign;
							break;
						}
					}
					ychangedfromslope = true;
					playerx -= counter;
					xchangeamount = xvelocity * ((90.0 - playercollisioninfo[i].lineangle) / 90.0);
					ychangeamount = -abs(playercollisioninfo[i].lineslope);
					breakfree = true;
					break;
				}
			}
			UpdateHitBox();
		}
	}
	UpdateHitBox();
	if (ychangedfromslope)
	{
		onslope = true;
		yvelocity += ychangeamount * abs(xchangeamount);
		yvelocity -= playergravity;
	}
	else
	{
		onslope = false;
	}
	int yvelocitysign = 1;
	if (yvelocity < 0)
		yvelocitysign = -1;
	if (abs(yvelocity) > 100)//glitch where slope was super close to zero so yvelocity was huge and it just froze game
	{
		cout << "fixing highyvelocity bug" << endl;
		if (yvelocity < 0)
			yvelocity = -5;
		else
			yvelocity = 5;
	}
	for (int x = 0; x < abs(yvelocity); x++)
	{
		playery += yvelocitysign;
		UpdateHitBox();
		IsPlayerHittingAnyShapes(theshapes, grender);
		for (int i = 0; i < playercollisioninfo.size(); i++)
		{
			if (playercollisioninfo[i].sidehit == 0 || playercollisioninfo[i].sidehit == 2)
			{
				if ((round(cos((playercollisioninfo[i].lineangle * 3.14) / 180) * 1000.0) / 1000.0) > .001)
				{
					playery -= yvelocitysign;
				}
				//playery -= yvelocitysign;
			}
			UpdateHitBox();
		}
	}
	xvelocitysign = 1;
	if (xchangeamount < 0)
		xvelocitysign = -1;
	if (abs(xchangeamount) > 100)//glitch where slope was super close to zero so yvelocity was huge and it just froze game
	{
		cout << "fixing high xvelocity bug" << endl;
		if (xchangeamount < 0)
			xchangeamount = -5;
		else
			xchangeamount = 5;
	}
	for (double x = 0; x < abs(xchangeamount); x++)
	{
		playerx += xvelocitysign;
		UpdateHitBox();
		IsPlayerHittingAnyShapes(theshapes, grender);
		for (int i = 0; i < playercollisioninfo.size(); i++)
		{
			if (playercollisioninfo[i].sidehit == 1 || playercollisioninfo[i].sidehit == 3)
			{
				if ((round(sin((playercollisioninfo[i].lineangle * 3.14) / 180) * 1000.0) / 1000.0) > .001)//not horizontal
				{
					playerx -= xvelocitysign;
				}
			}
			UpdateHitBox();
		}
	}
	UpdateHitBox();
	distancemovedthisframe.x = startposition.x - playerx;
	distancemovedthisframe.y = startposition.y - playery;
	if(distancemovedthisframe.x != 0)
		lastxmoved = distancemovedthisframe.x;
	//xvelocity = 0;
	//yvelocity = 0;
}
//* to make effeicent when you get shape see if the circle and player circle are touching if not skip it
void Player::IsPlayerHittingAnyShapes(vector<Shapes*> theshapes, SDL_Renderer * grender)
{
	playercollisioninfo.clear();
	int index;
	vector<line> shapelines;
	vector<vec2d> playerpoints = hitbox->AccessPoints();
	shapeType currentshape;
	//find out what your hitting
	//get its lines
	//check all those lines with the player
	if (movingphysicsenabled)//check all moving objects that we are within its circle
	{
		//first find all moving objects, objects with scripts enabled
		for (int i = 0; i < theshapes.size(); i++)
		{
			if (theshapes[i]->GetVelocity().x != 0 || theshapes[i]->GetVelocity().y != 0)
			{
				if (sqrt(pow(hitbox->GetOuterCircleCenter().x - theshapes[i]->GetOuterCircleCenter().x, 2) + pow(hitbox->GetOuterCircleCenter().y - theshapes[i]->GetOuterCircleCenter().y, 2)) < theshapes[i]->GetOuterRadius() + hitbox->GetOuterRadius())
				{
					movingsideshit.clear();
					currentshape = theshapes[i]->GetShapeType();
					switch (currentshape)
					{
					case RECTANGLE: shapelines = theshapes[i]->GetLines(); break;
					case TRIANGLE: shapelines = theshapes[i]->GetLines(); break;
					case POLYLINE: shapelines = theshapes[i]->GetLines(); break;
					case CIRCLE: shapelines = theshapes[i]->GetLines(); break;
					}
					int xvelocitytmp = theshapes[i]->GetVelocity().x;
					int xvelocitysign;
					if (xvelocitytmp < 0)
						xvelocitysign = -1;
					else
						xvelocitysign = 1;
					int yvelocitytmp = theshapes[i]->GetVelocity().y;
					int yvelocitysign;
					if (yvelocitytmp < 0)
						yvelocitysign = -1;
					else
						yvelocitysign = 1;
					if (xvelocitytmp != 0)
					{
						int counter = 0;
						for (int j = 0; j < abs(xvelocitytmp) + abs(velocityx); j++)
						{
							playerx += xvelocitysign;
							counter++;
							UpdateHitBox();
							checkplayerwithlinescollision(shapelines, theshapes[i], grender);
							if (playercollisioninfo.empty() != 0)
							{
								playercollisioninfo.clear();
								//playerx += xvelocitysign * counter;
								return;
							}
							if (j == abs(xvelocitytmp) + abs(velocityx) - 1)
							{
								//playerx += xvelocitysign * counter;
							}
						}
					}
					if (yvelocitytmp != 0)
					{
						int counter = 0;
						for (int j = 0; j < abs(yvelocitytmp); j++)
						{
							playery -= yvelocitysign;
							counter++;
							UpdateHitBox();
							checkplayerwithlinescollision(shapelines, theshapes[i], grender);
							if (playercollisioninfo.empty() != 0)
							{
								playercollisioninfo.clear();
								playery += yvelocitysign * counter;
								return;
							}
							if (j == abs(yvelocitytmp) - 1)
							{
								playery += yvelocitysign * counter;
							}
						}
					}
				}
			}
		}
		return;
	}
	int thecounter = 0;
	for (int i = 0; i < theshapes.size(); i++)
	{
		currentshape = theshapes[i]->GetShapeType();
		if (currentshape == POLYLINE)
		{
			vector<vec2d> points = theshapes[i]->AccessPoints();
			int leftmostx = points[0].x;
			int rightmostx = points[0].x;
			int lowestvaly = points[0].y;
			int highestvaly = points[0].y;
			for (int i = 0; i < points.size(); i++)
			{
				if (points[i].x < leftmostx)
					leftmostx = points[i].x;
				if (points[i].x > rightmostx)
					rightmostx = points[i].x;
				if (points[i].y < lowestvaly)
					lowestvaly = points[i].y;
				if (points[i].y > highestvaly)
					highestvaly = points[i].y;
			}
			vector<vec2d> polysquare;
			vec2d one(leftmostx, lowestvaly);
			vec2d two(rightmostx, lowestvaly);
			vec2d three(rightmostx, highestvaly);
			vec2d four(leftmostx, highestvaly);
			polysquare.push_back(one); polysquare.push_back(two); polysquare.push_back(three); polysquare.push_back(four);
			if (RectangleCollision(hitbox->AccessPoints(), polysquare))
			{
				thecounter++;
				shapelines = theshapes[i]->GetLines();
				checkplayerwithlinescollision(shapelines, theshapes[i], grender);
			}
		}
		else if (currentshape == TRIANGLE)
		{
			vector<vec2d> points = theshapes[i]->AccessPoints();
			int leftmostx = points[0].x;
			int rightmostx = points[0].x;
			int lowestvaly = points[0].y;
			int highestvaly = points[0].y;
			for (int i = 0; i < points.size(); i++)
			{
				if (points[i].x < leftmostx)
					leftmostx = points[i].x;
				if (points[i].x > rightmostx)
					rightmostx = points[i].x;
				if (points[i].y < lowestvaly)
					lowestvaly = points[i].y;
				if (points[i].y > highestvaly)
					highestvaly = points[i].y;
			}
			vector<vec2d> polysquare;
			vec2d one(leftmostx, lowestvaly);
			vec2d two(rightmostx, lowestvaly);
			vec2d three(rightmostx, highestvaly);
			vec2d four(leftmostx, highestvaly);
			polysquare.push_back(one); polysquare.push_back(two); polysquare.push_back(three); polysquare.push_back(four);
			if (RectangleCollision(hitbox->AccessPoints(), polysquare))
			{
				thecounter++;
				shapelines = theshapes[i]->GetLines();
				checkplayerwithlinescollision(shapelines, theshapes[i], grender);
			}
		}
		else if (currentshape == RECTANGLE)
		{
			if (theshapes[i]->GetTotalAmountRotated() == 0)
			{
				if (RectangleCollision(hitbox->AccessPoints(), theshapes[i]->AccessPoints()))
				{
					thecounter++;
					shapelines = theshapes[i]->GetLines();
					checkplayerwithlinescollision(shapelines, theshapes[i], grender);
				}
			}
			else
			{
			vector<vec2d> points = theshapes[i]->AccessPoints();
			int leftmostx = points[0].x;
			int rightmostx = points[0].x;
			int lowestvaly = points[0].y;
			int highestvaly = points[0].y;
			for (int i = 0; i < points.size(); i++)
			{
				if (points[i].x < leftmostx)
					leftmostx = points[i].x;
				if (points[i].x > rightmostx)
					rightmostx = points[i].x;
				if (points[i].y < lowestvaly)
					lowestvaly = points[i].y;
				if (points[i].y > highestvaly)
					highestvaly = points[i].y;
			}
			vector<vec2d> polysquare;
			vec2d one(leftmostx, lowestvaly);
			vec2d two(rightmostx, lowestvaly);
			vec2d three(rightmostx, highestvaly);
			vec2d four(leftmostx, highestvaly);
			polysquare.push_back(one); polysquare.push_back(two); polysquare.push_back(three); polysquare.push_back(four);
				if (RectangleCollision(hitbox->AccessPoints(), polysquare))
				{
					thecounter++;
					shapelines = theshapes[i]->GetLines();
					checkplayerwithlinescollision(shapelines, theshapes[i], grender);
				}
			}
		}
		else
		{
			if (CircleCollision(hitbox->GetOuterRadius(), hitbox->GetOuterCircleCenter(), theshapes[i]->GetOuterRadius(), theshapes[i]->GetOuterCircleCenter()))
			{
				switch (currentshape)
				{
				case CIRCLE: shapelines = theshapes[i]->GetLines(); break;
				}
				thecounter++;
				checkplayerwithlinescollision(shapelines, theshapes[i], grender);
			}
		}

	}
	//cout << "number of shapes collisiontesting: " << thecounter << endl;
	//PrintCollisioninfo();
}
bool Player::checkplayertriangle(vec2d one, vec2d one2, Shapes theshape)
{
	int index;
	bool vertical = false;
	vector<vec2d> shapepoints = theshape.AccessPoints();
	vector<vec2d> points = hitbox->AccessPoints();
	if (one.x - one2.x == 0)
		vertical = true;
	double highesty = one.y;
	double lowesty = one2.y;
	if (one2.y < one.y)
	{
		highesty = one2.y;
		lowesty = one.y;
	}
	double leftmostx = one.x;
	double rightmostx = one2.x;
	if (one2.x < one.x)
	{
		leftmostx = one2.x;
		rightmostx = one.x;
	}
	if (shapepoints.size() != 3)
	{
		cout << "triangle doesnt have 3 sides" << endl;
		return false;
	}
	if (vertical)
	{
		bool leave = false;
		int counter = 0;
		while (!leave)
		{
			if (isInside(shapepoints[0].x, shapepoints[0].y, shapepoints[1].x, shapepoints[1].y, shapepoints[2].x, shapepoints[2].y, one.x, highesty + counter))
			{
				return true;
			}
			counter++;
			if (highesty + counter > lowesty)
				leave = true;
		}
	}
	else
	{
		int counter = 0;
		bool leave = false;
		while (!leave)
		{
			if (isInside(shapepoints[0].x, shapepoints[0].y, shapepoints[1].x, shapepoints[1].y, shapepoints[2].x, shapepoints[2].y, leftmostx + counter, one.y))
			{
				return true;
			}
			counter++;
			if (leftmostx + counter > rightmostx)
				leave = true;
		}
	}
	return false;
}
void Player::checkplayerwithlinescollision(vector<line> thelines, Shapes* theshape, SDL_Renderer * grender)
{
	if (theshape->GetScriptTempDeath() == 1)//if its tempdeath dont check physics
	{
		return;
	}
	if (theshape->GetShapeType() == CIRCLE)
	{
		/*double difference = sqrt(pow(hitbox->AccessPoints()[0].x - theshape->GetOuterCircleCenter().x, 2) + pow(hitbox->AccessPoints()[0].y - theshape->GetOuterCircleCenter().y, 2));
		double difference2 = sqrt(pow(hitbox->AccessPoints()[1].x - theshape->GetOuterCircleCenter().x, 2) + pow(hitbox->AccessPoints()[1].y - theshape->GetOuterCircleCenter().y, 2));
		double difference3 = sqrt(pow(hitbox->AccessPoints()[2].x - theshape->GetOuterCircleCenter().x, 2) + pow(hitbox->AccessPoints()[2].y - theshape->GetOuterCircleCenter().y, 2));
		double difference4 = sqrt(pow(hitbox->AccessPoints()[3].x - theshape->GetOuterCircleCenter().x, 2) + pow(hitbox->AccessPoints()[3].y - theshape->GetOuterCircleCenter().y, 2));
		if (abs(difference) <= theshape->GetCircleRadiusOutside() || abs(difference2) <= theshape->GetCircleRadiusOutside() || abs(difference3) <= theshape->GetCircleRadiusOutside() || abs(difference4) <= theshape->GetCircleRadiusOutside())
		{
			if (theshape->AccessDamage() == 1)
			{
				LowerHealth(1);
			}
		}
		return;*/
	}
	//0 and 1 2 and 3 4 and 5 6 and 7
	int index;
	vector<vec2d> points = hitbox->AccessPoints();
	int doublejumpcounterstart = doublejumpcounter;
	for (int j = 0; j < thelines.size(); j++)
	{
		for (int i = 0; i < points.size(); i++)//i+=2
		{
			if (i == points.size() - 1)
				index = 0;
			else
				index = i + 1;
			//cout << SlopeofLine(thelines[j].pointone, thelines[j].pointtwo, grender) << endl;
			if (checktwolinecollision(points[i], points[index], thelines[j].pointone, thelines[j].pointtwo,grender))//checktwolinecollision(points[i], points[index], thelines[j].pointone, thelines[j].pointtwo, grender) == 1
			{
				if (theshape->GetCheckpoint() == 1)
				{
					checkpoint = theshape;
					return;
				}
				if (theshape->AccessDamage() == 1)
				{
					LowerHealth(1);
				}
				if (theshape->AccessTeleport() == 1)
				{
					teleportsidehit = j;
					teleported = 1;
					teleportright = theshape->GetTeleportRight();
					return;
				}
				if (theshape->GetDoubleJumper() == 1)
				{
					/* makes it so you automatically jump could be cool mechanic
					jumpcounter = 0;
					jumping = true;
					canjump = false;
					doublejumpcounter++;*/
					if(doublejumpcounter == doublejumpcounterstart)
						doublejumpcounter++;
					//canjump = true;
					theshape->SetScriptTempDeath(true);
					return;
				}
				collisioninfo newinfo;
				newinfo.theline = thelines[j];
				newinfo.lineslope = SlopeofLine(thelines[j].pointone, thelines[j].pointtwo, grender);
				newinfo.lineangle = AngleofLine(thelines[j].pointone, thelines[j].pointtwo,grender);
				newinfo.sidehit = i;//0 2 4 6
				playercollisioninfo.push_back(newinfo);
				//if you hit your head you cant jump
				if (newinfo.sidehit == 0)
				{
					if (checktwolinecollision(feethitbox->AccessPoints()[0], feethitbox->AccessPoints()[1], thelines[j].pointone, thelines[j].pointtwo, grender))
					{
						jumping = false;
						jumpcounter = 0;
					}
				}
				//if you get hit by anything just cancel trampoline
				beingtrampolined = false;
				trampolinecounter = 0;
				if (theshape->GetBouncer() == 1)
				{
					int value = theshape->GetBounceAmount();
					//int value = theshape->Accessbouncespeed;
					beingtrampolined = true;
					if (j == 0)
					{
						bounceleft = false;
						bounceright = false;
						bounceup = true;
						bouncedown = false;
						trampolinex = value;
					}
					else if (j == 1)
					{
						bounceleft = false;
						bounceright = true;
						bounceup = false;
						bouncedown = false;
						trampolinex = value;
						playery -= 1;
					}
					else if (j == 2)
					{
						bounceleft = false;
						bounceright = false;
						bounceup = false;
						bouncedown = true;
						trampolinex = value;
					}
					else if (j == 3)
					{
						bounceleft = true;
						bounceright = false;
						bounceup = false;
						bouncedown = false;
						playery -= 1;
						trampolinex = value;
					}
				}
				if (newinfo.sidehit == 2 && newinfo.lineslope != 0)
				{
					canjump = true;
					doublejumpcounter = 0;
					if (doublejump)
					{
						doublejumpcounter = 1;
					}
				}
				if (newinfo.sidehit == 2)
				{
					if (checktwolinecollision(feethitbox->AccessPoints()[3], feethitbox->AccessPoints()[2], thelines[j].pointone, thelines[j].pointtwo, grender))
					{
						canjump = true;
						doublejumpcounter = 0;
						if (doublejump)
						{
							doublejumpcounter = 1;
						}
					}
				}
				if (movingphysicsenabled)
				{
					movingsideshit.push_back(i);
					if (theshape->GetVelocity().x != 0 || theshape->GetVelocity().y != 0)
					{
						if (Find(1) && Find(3) || Find(0) && Find(1) || Find(0) && Find(3) || Find(2) && Find(3) || Find(2) && Find(1) && theshape->GetVelocity().y != 0)
						{
							playery += theshape->GetVelocity().y;
							
						}
						if (Find(0) && Find(2) || Find(1) && Find(0) || Find(1) && Find(2) || Find(3) && Find(0) || Find(3) && Find(2) && theshape->GetVelocity().x != 0)
						{
							playerx += theshape->GetVelocity().x;
						}
					}
				}
			}
		}
	}
}
bool Player::checktwolinecollision(vec2d one, vec2d one2, vec2d two, vec2d two2, SDL_Renderer * grender)//*slope1 is player
{
	//SDL_SetRenderDrawColor(grender, 100, 150, 50, 0);
	//SDL_RenderDrawLine(grender, one.x, one.y, one2.x, one2.y);
	//SDL_SetRenderDrawColor(grender, 0, 100, 100, 0);
	//SDL_RenderDrawLine(grender, two.x, two.y, two2.x, two2.y);

	//helper
	double larger1y = one.y;
	double smaller1y = one2.y;
	double larger1x = one.x;
	double smaller1x = one2.x;
	double larger2x = two.x;
	double smaller2x = two2.x;
	double larger2y = two.y;
	double smaller2y = two2.y;
	if (two2.x > two.x)
	{
		larger2x = two2.x;
		smaller2x = two.x;
	}
	if (two2.y > two.y)
	{
		larger2y = two2.y;
		smaller2y = two.y;
	}
	if (one2.x > one.x)
	{
		larger1x = one2.x;
		smaller1x = one.x;
	}
	if (one2.y > one.y)
	{
		larger1y = one2.y;
		smaller1y = one.y;
	}

	double slope1 = 0;
	double b1 = 0;//is the b intercept if horizontal line its the y if vertical its the x
	bool undefined1 = false;
	bool zero1 = false;
	if (one2.x == one.x)
	{
		undefined1 = true;
		b1 = one.x;
	}
	else if (one2.y == one.y)
	{
		zero1 = true;
		b1 = one.y;
	}
	else
	{
		slope1 = (one2.y - one.y) / (one2.x - one.x);
		b1 = one2.y - slope1 * one2.x;
	}

	double slope2 = 0;
	double b2 = 0;
	bool undefined2 = false;
	bool zero2 = false;
	if (two2.x == two.x)
	{
		undefined2 = true;
		b2 = two.x;
	}
	else if (two2.y == two.y)//two2.y == two.y
	{
		zero2 = true;
		b2 = two.y;
	}
	else
	{
		slope2 = (two2.y - two.y) / (two2.x - two.x);
		b2 = two2.y - slope2 * two2.x;
		if (abs(slope2) <= .005)
		{
			zero2 = true;
			b2 = two.y;
			slope2 = 0;
		}
		/*if (abs(slope2) <= .03)
		{
			zero2 = true;
			//if player is 
			if(two.y > two2.y)
				b2 = two.y;
			else
				b2 = two2.y;
			//b2 is lowest y
			if(playery >= b2)
				b2 = b2;
			else
			{
				if (two.y < two2.y)
					b2 = two.y;
				else
					b2 = two2.y;
			}
			slope2 = 0;
		}*/
		if (abs(slope2) >= 5000)
		{
			undefined2 = true;
			b2 = two.x;
			slope2 = 0;
			//cout << "slope very big" << endl;
		}
	}
	if (zero1 && zero2 == 1)
	{
		if (static_cast<int>(one.y) == static_cast<int>(b2))//static_cast<int>(one.y) == static_cast<int>(two.y)
		{
			double largestx = larger2x;
			if (larger1x > larger2x)
			{
				if (larger1x - smaller1x >= larger1x - larger2x)
				{
					return true;
				}
			}
			else
			{
				if (larger2x - smaller2x >= larger2x - larger1x)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 && undefined2 == 1)
	{
		if (movingphysicsenabled)
		{
			//cout << static_cast<int>(one.x) << " " << static_cast<int>(two.x) << endl;
		}
		if (static_cast<int>(one.x) == static_cast<int>(two.x))//static_cast<int>(one.x) == static_cast<int>(two.x)
		{

			double largesty = larger2y;
			if (larger1y > larger2y)
			{
				if (larger1y - smaller1y >= larger1y - larger2y)
				{
					return true;
				}
			}
			else
			{
				if (larger2y - smaller2y >= larger2y - larger1y)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 || undefined2 == 1)
	{
		double y = 0;
		double x = 0;
		int amount = 0;
		if (undefined1 == 1)
		{
			y = slope2 * b1 + b2;
			x = b1;
			if (abs(slope2) <= .03 && abs(slope2) != 0)
			{
				for (double i = 0; i < 1; i += .001)
				{
					y = slope2 * b1 + b2 - i;
					x = b1;
					if ((y <= larger1y + amount && y >= smaller1y - amount) && (y <= larger2y + amount && y >= smaller2y - amount))//safe check with x?
					{
						if ((x <= larger1x + amount && x >= smaller1x - amount) && (x <= larger2x + amount && x >= smaller2x - amount))
						{
							return true;
						}
					}
				}
				return false;
			}
			if (abs(slope2) >= 50)
			{
				for (double i = 0; i < 1; i += .001)
				{
					y = slope2 * b1 + b2;
					x = b1 - i;
					if ((y <= larger1y + amount && y >= smaller1y - amount) && (y <= larger2y + amount && y >= smaller2y - amount))//safe check with x?
					{
						if ((x <= larger1x + amount && x >= smaller1x - amount) && (x <= larger2x + amount && x >= smaller2x - amount))
						{
							return true;
						}
					}
				}
				return false;
			}
		}
		else
		{
			y = slope1 * b2 + b1;
			x = b2;
		}
		amount = 0;
		if ((y <= larger1y+ amount && y >= smaller1y- amount) && (y <= larger2y+ amount && y >= smaller2y- amount))//safe check with x?
		{
			if ((x <= larger1x+amount && x >= smaller1x - amount) && (x <= larger2x+amount && x >= smaller2x-amount))
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		//glitch if its a slope thats super super small
		//if slopes are same there is no solution unless they are the same
		if (slope1 - slope2 == 0)
		{
			if (b2 == b1)
			{
				return true;
			}
			return false;
		}
		if (abs(slope2) <= .03 && abs(slope2) != 0)
		{
			for (double i = 0; i < 1; i += .001)
			{
				double x = ((b2 - i) - b1) / (slope1 - slope2);
				double y = x * slope1 + b1;
				if ((y <= larger1y && y >= smaller1y) && (y <= larger2y && y >= smaller2y))
				{
					if ((x <= larger1x && x >= smaller1x) && (x <= larger2x && x >= smaller2x))//safe check with y?
					{
						return true;
					}
				}
			}
			return false;
		}
		if (abs(slope2) >= 50)
		{
			for (double i = 0; i < 1; i += .001)
			{
				double x = ((b2- b1) / (slope1 - slope2)) - i;
				double y = x * slope1 + b1;
				if ((y <= larger1y && y >= smaller1y) && (y <= larger2y && y >= smaller2y))
				{
					if ((x <= larger1x && x >= smaller1x) && (x <= larger2x && x >= smaller2x))//safe check with y?
					{
						return true;
					}
				}
			}
			return false;
		}
		double x = (b2 - b1) / (slope1 - slope2);
		double y = x * slope1 + b1;
		if ((y <= larger1y && y >= smaller1y) && (y <= larger2y && y >= smaller2y))
		{
			if ((x <= larger1x && x >= smaller1x) && (x <= larger2x && x >= smaller2x))//safe check with y?
			{
				//cout << x << endl;
				return true;
			}
		}
		return false;
	}	
}
bool Player::checktwolinecollisionwithShapes(vec2d one, vec2d one2, vec2d two, vec2d two2, SDL_Renderer * grender, Shapes theshape)
{
	//helper
	if (theshape.GetShapeType() == TRIANGLE)
	{
		if (checkplayertriangle(one, one2, theshape))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (theshape.GetShapeType() == RECTANGLE)
	{
		vector<vec2d> shapepoints = theshape.AccessPoints();
		vec2d one(shapepoints[0].x, shapepoints[0].y);
		vec2d two(shapepoints[1].x, shapepoints[1].y);
		vec2d three(shapepoints[2].x, shapepoints[2].y);
		Triangle temp(one,two,three);
		vec2d one2(shapepoints[0].x, shapepoints[0].y);
		vec2d two2(shapepoints[2].x, shapepoints[2].y);
		vec2d three2(shapepoints[3].x, shapepoints[3].y);
		Triangle temp2(one2, two2, three2);
		Shapes t1 = temp;
		Shapes t2 = temp2;
		if (checkplayertriangle(one, one2, t1) || checkplayertriangle(one, one2, t2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
	double larger1y = one.y;
	double smaller1y = one2.y;
	double larger1x = one.x;
	double smaller1x = one2.x;
	double larger2x = two.x;
	double smaller2x = two2.x;
	double larger2y = two.y;
	double smaller2y = two2.y;
	if (two2.x > two.x)
	{
		larger2x = two2.x;
		smaller2x = two.x;
	}
	if (two2.y > two.y)
	{
		larger2y = two2.y;
		smaller2y = two.y;
	}
	if (one2.x > one.x)
	{
		larger1x = one2.x;
		smaller1x = one.x;
	}
	if (one2.y > one.y)
	{
		larger1y = one2.y;
		smaller1y = one.y;
	}

	double slope1 = 0;
	double b1 = 0;//is the b intercept if horizontal line its the y if vertical its the x
	bool undefined1 = false;
	bool zero1 = false;
	if (one2.x == one.x)
	{
		undefined1 = true;
		b1 = one.x;
	}
	else if (one2.y == one.y)
	{
		zero1 = true;
		b1 = one.y;
	}
	else
	{
		slope1 = (one2.y - one.y) / (one2.x - one.x);
		b1 = one2.y - slope1 * one2.x;
	}

	double slope2 = 0;
	double b2 = 0;
	bool undefined2 = false;
	bool zero2 = false;
	if (two2.x == two.x)
	{
		undefined2 = true;
		b2 = two.x;
	}
	else if (two2.y == two.y)//two2.y == two.y
	{
		zero2 = true;
		b2 = two.y;
	}
	else
	{
		slope2 = (two2.y - two.y) / (two2.x - two.x);
		b2 = two2.y - slope2 * two2.x;
	}
	if (zero1 && zero2 == 1)
	{
		if (static_cast<int>(one.y) == static_cast<int>(b2))//static_cast<int>(one.y) == static_cast<int>(two.y)
		{
			double largestx = larger2x;
			if (larger1x > larger2x)
			{
				if (larger1x - smaller1x >= larger1x - larger2x)
				{
					return true;
				}
			}
			else
			{
				if (larger2x - smaller2x >= larger2x - larger1x)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 && undefined2 == 1)
	{
		if (static_cast<int>(one.x) == static_cast<int>(two.x))//static_cast<int>(one.x) == static_cast<int>(two.x)
		{
			double largesty = larger2y;
			if (larger1y > larger2y)
			{
				if (larger1y - smaller1y >= larger1y - larger2y)
				{
					return true;
				}
			}
			else
			{
				if (larger2y - smaller2y >= larger2y - larger1y)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 || undefined2 == 1)
	{
		double y = 0;
		double x = 0;
		int amount = 0;
		if (undefined1 == 1)
		{
			y = slope2 * b1 + b2;
			x = b1;
		}
		else
		{
			y = slope1 * b2 + b1;
			x = b2;
		}
		amount = 0;
		if ((y <= larger1y + amount && y >= smaller1y - amount) && (y <= larger2y + amount && y >= smaller2y - amount))//safe check with x?
		{
			if ((x <= larger1x + amount && x >= smaller1x - amount) && (x <= larger2x + amount && x >= smaller2x - amount))
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		//glitch if its a slope thats super super small
		//if slopes are same there is no solution unless they are the same
		if (slope1 - slope2 == 0)
		{
			if (b2 == b1)
			{
				return true;
			}
			return false;
		}
		double x = (b2 - b1) / (slope1 - slope2);
		double y = x * slope1 + b1;
		if ((y <= larger1y && y >= smaller1y) && (y <= larger2y && y >= smaller2y))
		{
			if ((x <= larger1x && x >= smaller1x) && (x <= larger2x && x >= smaller2x))//safe check with y?
			{
				return true;
			}
		}
		return false;
	}
}
bool Player::checktwolinecollisiontest(vec2d two, vec2d two2, SDL_Renderer * grender)
{
	/*int index;
	vector<vec2d> points = hitbox->AccessPoints();
	for (int i = 0; i < points.size(); i++)//i+=2
	{
		if (i == points.size() - 1)
			index = 0;
		else
			index = i + 1;
		if (checktwolinecollision(points[i], points[index], two, two2, grender) == 1)//i,index
		{
			SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
			SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[index].x, points[index].y);
			return true;
			if (i == 1 || i == 3)
			{
				//SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
				//SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[index].x, points[index].y);
				//return true;
			}
		}
	}*/
	return false;
}
//*This code is from lazyfoo.net tutorials*
bool  Player::RectangleCollision(vector<vec2d> points1, vector<vec2d> points2)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = points1[0].x;
	rightA = points1[1].x;
	topA = points1[0].y;
	bottomA = points1[2].y;

	//Calculate the sides of rect B
	//*make this rect a little bigger so its accurate
	int amount = 10;
	leftB = points2[0].x - amount;
	rightB = points2[1].x + amount;
	topB = points2[0].y - amount;
	bottomB = points2[2].y + amount;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Player::CircleCollision(int radiusplayer, vec2d center1, int radiusshape, vec2d center2)
{
	//find distance between centers and if its less than or equal to radius 1 we good
	//have to use shapes radius
	double distance = sqrt(pow(center2.x - center1.x, 2) + pow(center2.y - center1.y, 2));// /2
	if (distance <= radiusplayer + radiusshape + 10)
	{
		return true;
	}
	return false;
}
double Player::SlopeofLine(vec2d one, vec2d two, SDL_Renderer* grender)
{
	if (one.x == two.x)
	{
		return 0;
	}
	if (one.y == two.y)
	{
		return 0;
	}
	return (two.y - one.y) / (two.x - one.x);
}
int Player::AngleofLine(vec2d one, vec2d two, SDL_Renderer* grender)
{
	vec2d center(((one.x + two.x) / 2), ((one.y + two.y) / 2));
	double radius = sqrt(pow(two.x - one.x, 2) + pow(two.y - one.y, 2)) / 2;
	if (radius == 0)
	{
		cout << "radius is zero exiting....";
		return -1;
	}
	double slopeAngle = 0;
	double xdistancefromcenter = one.x - center.x;
	if (xdistancefromcenter / radius >= 1)
	{
		slopeAngle = 0;
	}
	else
	{
		slopeAngle = acos(xdistancefromcenter / radius);//% 90
	}
	slopeAngle = slopeAngle * 180 / 3.14;
	int theslope = slopeAngle;
	if (theslope > 90)
	{
		theslope = 180 - slopeAngle;
	}
	//cout << "angle is: " << theslope << endl;
	return theslope;
}
bool Player::SegmentsIntersecttest(vec2d p3, vec2d p4)
{	
	int index;
	vector<vec2d> points = hitbox->AccessPoints();
	for (int i = 0; i < points.size(); i++)//i+=2
	{
		if (i == points.size() - 1)
			index = 0;
		else
			index = i + 1;
		if (i == 0)
		{
			if (SegmentsIntersect(points[i], points[index], p3, p4) == 1)//i,index
			{
				return true;
				if (i == 1 || i == 3)
				{
					//SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
					//SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[index].x, points[index].y);
					//return true;
				}
			}
		}
	}
	return false;

}
bool Player::SegmentsIntersect(vec2d p1, vec2d p2, vec2d p3, vec2d p4)
{
	double slope;
	if (p4.x - p3.x == 0)
	{
		slope = 0;
	}
	else
	{
		slope = (p4.y - p3.y) / (p4.x - p3.x);
	}
	if (abs(slope) <= .03 && slope !=0)
	{
		//cout << "in";
		vec2d p3tmp = p3;
		vec2d p4tmp = p4;
		for (double i = 0; i < 1; i += .001)
		{
			p3.y += i;
			//p4.y += i;
			int d1 = Direction(p3, p4, p1);
			int d2 = Direction(p3, p4, p2);
			int d3 = Direction(p1, p2, p3);
			int d4 = Direction(p1, p2, p4);
			if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
			{
				return true;
			}
			else if (d1 == 0 && OnSegment(p3, p4, p1))
			{
				return true;
			}
			else if (d2 == 0 && OnSegment(p3, p4, p2))
			{
				return true;
			}
			else if (d3 == 0 && OnSegment(p1, p2, p3))
			{
				return true;
			}
			else if (d4 == 0 && OnSegment(p1, p2, p4))
			{
				return true;
			}
		}
		return false;
	}
	int d1 = Direction(p3, p4, p1);
	int d2 = Direction(p3, p4, p2);
	int d3 = Direction(p1, p2, p3);
	int d4 = Direction(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return true;
	}
	else if (d1 == 0 && OnSegment(p3, p4, p1))
	{
		return true;
	}
	else if (d2 == 0 && OnSegment(p3, p4, p2))
	{
		return true;
	}
	else if (d3 == 0 && OnSegment(p1, p2, p3))
	{
		return true;
	}
	else if (d4 == 0 && OnSegment(p1, p2, p4))
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
int Player::Direction(vec2d p1, vec2d p2, vec2d p3)
{
	int answer = (static_cast<int>(p2.x) - static_cast<int>(p1.x))*(static_cast<int>(p3.y) - static_cast<int>(p1.y)) - (static_cast<int>(p3.x) - static_cast<int>(p1.x))*(static_cast<int>(p2.y) - static_cast<int>(p1.y));
	return answer;
}
bool Player::OnSegment(vec2d p1, vec2d p2, vec2d p3)
{
	int min1 = p1.x;
	int max1 = p2.x;
	if (p2.x < p1.x)
	{
		min1 = p2.x;
		max1 = p1.x;
	}
	int min2 = p1.y;
	int max2 = p2.y;
	if (p1.y > p2.y)
	{
		min2 = p2.y;
		max2 = p1.y;
	}
	int value = 0;
	if ((min1 <= p3.x && p3.x <= max1) && (min2 - value <= p3.y && p3.y <= max2 + value))
	{
		return true;
	}
	return false;
}
float Player::area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}
bool Player::isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
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
void Player::Move2(vector<Shapes*> theshapes, SDL_Renderer * grender)
{
	for (int i = 0; i < playercollisioninfo.size(); i++)
	{
		//cout << i << " : " << playercollisioninfo[i].lineangle << " " << playercollisioninfo[i].sidehit << endl;
	}
	if (playercollisioninfo.size() == 0)
	{
		//cout << "empty" << endl;
	}
	int xsign = 1;
	if (xvelocity < 0)
		xsign = -1;

	for (int i = 0; i < abs(xvelocity); i++)
	{
		playerx += xsign;
		UpdateHitBox();
		IsPlayerHittingAnyShapes(theshapes, grender);
		for (int i = 0; i < playercollisioninfo.size(); i++)
		{
			if (playercollisioninfo[i].sidehit == 1 || playercollisioninfo[i].sidehit == 3)
			{
				playerx -= xsign;
				UpdateHitBox();
			}
		}
	}

	int ysign = 1;
	if (yvelocity < 0)
		ysign = -1;

	for (int i = 0; i < abs(yvelocity); i++)
	{
		playery += ysign;
		UpdateHitBox();
		IsPlayerHittingAnyShapes(theshapes, grender);
		for (int i = 0; i < playercollisioninfo.size(); i++)
		{
			if (playercollisioninfo[i].sidehit == 0 || playercollisioninfo[i].sidehit == 2)
			{
				playery -= ysign;
				UpdateHitBox();
			}
		}
	}


	UpdateHitBox();
	xvelocity = 0;
	yvelocity = 0;
}
bool Player::Find(int i)
{
	if (movingsideshit.size() != 0)
	{
		for (int i = 0; i < movingsideshit.size(); i++)
		{
			if (i == movingsideshit[i])
			{
				return true;
			}
		}
	}
	return false;
}









//get line equation for vectors
	/*double slope1;
	if (one2.x - one.x == 0)
	{
		slope1 = 0;
	}
	else
	{
		slope1 = (one2.y - one.y) / (one2.x - one.x);
	}
	double b1 = one2.y - slope1 * one2.x;
	//equation is y = slopex + b
	double slope2;
	if (two2.x - two.x == 0)
	{
		slope2 = 0;
	}
	else
	{
		slope2 = (two2.y - two.y) / (two2.x - two.x);
	}
	double b2 = two2.y - slope2 * two2.x;
	//x = b2-b1/m1-m2
	//cout << slope1;
	if (slope1 - slope2 == 0)
	{
		return false;
	}
	double x;
	double y;
	if (slope1 == 0)//*or slope 2
	{
		x = one2.x;
		y = slope2 * x + b2;
		double larger = one.y;
		double smaller = one2.y;
		double larger2 = two.x;
		double smaller2 = two2.x;
		if (two2.x > two.x)
		{
			larger2 = two2.x;
			smaller2 = two.x;
		}
		if (one2.y > larger)
		{
			larger = one2.y;
			smaller = one.y;
		}
		if (y <= larger && y >= smaller && (x <= larger2 && x >= smaller2))//check other colliders y as well
		{
			return true;
		}
		return false;
	}
	else
	{
		x = (b2 - b1) / (slope1 - slope2);
		//see if player boundary and box is within x if both are then you have a collision
		double larger = one.x;
		double smaller = one2.x;
		double larger2 = two.x;
		double smaller2 = two2.x;
		if (two2.x > two.x)
		{
			larger2 = two2.x;
			smaller2 = two.x;
		}
		if (one2.x > one.x)
		{
			larger = one2.x;
			smaller = one.x;
		}
		//cout << "x:" << x << endl;
		if ((x <= larger && x >= smaller) && (x <= larger2 && x >= smaller2))
		{
			return true;
		}
		return false;
	}
	return false;*/