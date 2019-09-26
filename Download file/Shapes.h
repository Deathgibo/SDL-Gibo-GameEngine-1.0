//parent class of shapes
#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std::chrono;
using namespace std;
/*
auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time to finish whole run: "
		<< duration.count() << "microseconds" << endl;
*/
enum shapeType { RECTANGLE,CIRCLE,TRIANGLE,PLAYERHITBOX,POLYLINE };
struct zoomedinreverter
{
	double amount;
	int xmouse;
	int ymouse;
};
struct vec2d
{
	double x;
	double y;
	~vec2d()
	{
		x = 0;
		y = 0;
	}
	vec2d(int xposition, int yposition)
	{
		x = xposition;
		y = yposition;
	}
	vec2d(){}
	double length(int xoffset, int yoffset)
	{
		return sqrt(pow(x-xoffset, 2) + pow(yoffset - y, 2));
	}
};
struct line
{
	vec2d pointone;
	vec2d pointtwo;
	line()
	{

	}
	line(vec2d point1, vec2d point2)
	{
		pointone = point1;
		pointtwo = point2;
	}
};
struct mat2x2
{
	double column1x;
	double column1y;
	double column2x;
	double column2y;

	/*Description of this function
	We translate the xy into the 0,0 origin do the transformation then add the offsets back
	so like if we have (120,120) on circle center(100,100) the x change is 20 and y is 20
	so you just do 20,20 on (0,0) origin then add (100,100) back. Of course theres the problem with
	y being flipped so thats why you see (yoffset - vector.y) and ychange * -1 
	*/
	vec2d matrixvectorMult(vec2d vector,int xoffset,int yoffset)
	{
		double ychange;
		vec2d temp;
		temp.x = column1x * (vector.x-xoffset) + column2x * (yoffset - vector.y) + xoffset;
		ychange = column1y * (vector.x - xoffset) + column2y * (yoffset - vector.y);
		ychange = ychange * -1;
		temp.y = ychange + yoffset;
		return temp;
	}
};


class Shapes
{
public:
	Shapes();
	Shapes(Shapes & theshape);
	~Shapes();
	virtual void Print(SDL_Renderer* grender);
	void Rotate();
	void RevertMoveAmount();
	void Rotate(int degrees);
	void Zoomtomouse(double x,int mx,int my);
	void Zoomtomouseinverse(double x, int mx, int my, double determinant);
	void Zoomnomouse(double x);
	void ZoomShapeSolo(double x);
	void MoveX(double x,bool updatec = 1, bool updatemoveamount = 0);
	void MoveY(double x, bool updatec = 1, bool updatemoveamount = 0);
	void MoveYpointindex(double x, int index, bool updatec = 1);
	void MoveXpointindex(double x, int index, bool updatec = 1);
	double ResetAngle();
	void SetRotationAmount(int degress);
	int GetRotationAmount();
	virtual void UpdateCircle();
	virtual vector<line> GetLines();
	void ChangeTexture(SDL_Texture* atexture);
	shapeType GetShapeType();
	bool checktwolinecollision(vec2d one, vec2d one2, vec2d two, vec2d two2, SDL_Renderer * grender);
	virtual void Print(SDL_Renderer* grender, int r, int g, int b);
	virtual void PrintTexture(SDL_Renderer* grender);
	int GetCircleRadius();
	int GetCircleRadiusOutside();
	vec2d GetCircleCenter();
	vec2d GetOuterCircleCenter();
	int GetOuterRadius();
	vector<vec2d> AccessPoints();
	double Accesszoomedinamount();
	virtual void AddLine();
	bool Checkslopes();
	void ToggleDamage(bool i);
	bool AccessDamage();
	void ToggleTeleport(bool i);
	bool AccessTeleport();
	void ScriptTempDeath();
	void ScriptLefttoRight(SDL_Renderer* grender);
	void ScriptUptoDown();
	void ScriptBallShooter();
	void ScriptMove();
	void SetScriptSpeed(double i);
	void SetScriptSpeedReal(double i);
	void SetScriptDistance(double i);
	void SetScriptDistanceReal(double i);
	bool GetScriptLefttoRight();
	bool GetScriptTempDeath();
	void SetScriptTempDeath(bool i);
	bool GetScriptUptoDown();
	bool GetScriptMove();
	void SetScriptMove(bool i);
	void SetScriptlefttoright(bool i, bool fullreset = true);
	void SetSCriptUptoDown(bool i, bool fullreset= true);
	void SetScriptorigins(double x, double y);
	void SetScriptorigin1real(double x, double y);
	void SetScriptorigin2real(double x, double y);
	vec2d GetScriptorigin();
	vec2d GetScriptorigin2();
	void SetBallSpawner(bool i);
	bool GetBallSpawner();
	int GetScriptCounter();
	void SetScriptCounter(int x);
	double GetScriptDistance();
	double GetScriptSpeed();
	void SetScriptSpeedy(double i);
	double GetScriptSpeedy();
	int GetTotalAmountRotated();
	void SetTotalAmountRotated(int i);
	void SetDoubleJumper(bool i);
	bool GetDoubleJumper();
	bool GetBouncer();
	void SetBouncer(bool i);
	int GetBounceAmount();
	void SetBounceAmount(int i);
	vec2d GetVelocity();
	void SetVelocity(vec2d vec);
	void SetScriptdir(bool i);
	bool GetScriptdir();
	void SetScriptOnce(bool i);
	bool GetTeleportRight();
	void SetTeleportRight(bool i);
	void SetCheckpoint(bool i);
	bool GetCheckpoint();
protected:
	bool checkpoint;
	bool teleportright;
	vec2d velocity;
	int scriptcounter;
	bool scripttempdeath;
	bool scriptlefttoright;
	bool scriptuptodown;
	bool scriptmove;
	bool scriptdir;
	bool scriptonce;
	vec2d scriptorigin;
	vec2d scriptorigin2;
	double scriptspeed;
	double scriptspeedy;
	double scriptdistance;
	bool teleport;//does this shape teleport player to next scene
	bool damage;//does this shape damage player
	bool ballspawner;//does this shoot out balls
	bool doublejumper;
	bool bouncer;
	int bounceamount;
	vec2d MoveAmount;
	int totalamountrotated;
	int rotationamount;
	double zoomedinamount;
	vector<vec2d> points;
	SDL_Texture* texture;
	shapeType shapetype;
	int circleRadius;
	vec2d circleCenter;
	int insidecircleRadius;
	vec2d insidecircleCenter;
	void PrintCircle(SDL_Renderer* grender);
};
Shapes::~Shapes()
{
	texture = 0;
}
Shapes::Shapes()
{
	checkpoint = false;
	teleportright = false;
	velocity.x = 0; velocity.y = 0;
	bounceamount = 5;
	bouncer = false;
	scripttempdeath = false;
	doublejumper = false;
	ballspawner = false;
	scriptcounter = 0;
	scriptmove = false;
	scriptlefttoright = false;
	scriptuptodown = false;
	scriptdir = true;
	scriptonce = true;
	scriptorigin.x = 0; scriptorigin.y = 0;
	scriptorigin2.x = 0; scriptorigin2.y = 0;
	scriptspeed = 20;
	scriptspeedy = 20;
	scriptdistance = 100;
	damage = false;
	teleport = false;
	texture = 0;
	rotationamount = 0;
	totalamountrotated = 0;
	zoomedinamount = 0;
	MoveAmount.x = 0;
	MoveAmount.y = 0;
}
Shapes::Shapes(Shapes & theshape)
{
	checkpoint = false;
	teleportright = false;
	velocity.x = 0; velocity.y = 0;
	bounceamount = 5;
	bouncer = false;
	scripttempdeath = false;
	doublejumper = false;
	ballspawner = false;
	scriptcounter = 0;
	scriptlefttoright = false;
	scriptuptodown = false;
	scriptdir = true;
	scriptonce = true;
	scriptorigin.x = 0; scriptorigin.y = 0;
	scriptspeed = 10;
	scriptdistance = .1;
	damage = false;
	teleport = false;
	texture = 0;
	rotationamount = 0;
	totalamountrotated = 0;
	zoomedinamount = 0;
	MoveAmount.x = 0;
	MoveAmount.y = 0;
	//cout << "shape copy";
	if (theshape.GetShapeType() == TRIANGLE)
	{
		shapetype = TRIANGLE;
		vector<vec2d> thepoints = theshape.AccessPoints();
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
		return;
	}
	if (theshape.GetShapeType() == RECTANGLE)
	{
		return;
	}

}
void Shapes::SetCheckpoint(bool i)
{
	checkpoint = i;
}
bool Shapes::GetCheckpoint()
{
	return checkpoint;
}
void Shapes::ToggleDamage(bool i)
{
	damage = i;

}
vec2d Shapes::GetVelocity()
{
	return velocity;
}
void Shapes::SetVelocity(vec2d vec)
{
	velocity.x = vec.x;
	velocity.y = vec.y;
}
bool Shapes::AccessDamage()
{
	return damage;
}
void Shapes::ToggleTeleport(bool i)
{
	teleport = i;
}
bool Shapes::GetTeleportRight()
{
	return teleportright;
}
void Shapes::SetTeleportRight(bool i)
{
	teleportright = i;
}
void Shapes::SetBallSpawner(bool i)
{
	ballspawner = i;
}
void Shapes::SetDoubleJumper(bool i)
{
	doublejumper = i;
}
bool Shapes::GetDoubleJumper()
{
	return doublejumper;
}
bool Shapes::GetBallSpawner()
{
	return ballspawner;
}
bool  Shapes::AccessTeleport()
{
	return teleport;
}
void Shapes::UpdateCircle()
{
	cout << "updatecircle in shapes";
}
vector<line> Shapes::GetLines()
{
	vector<line> lines;
	cout << "shouldnt be running getlines function in shape class";
	return lines;
}
bool Shapes::GetScriptLefttoRight()
{
	return scriptlefttoright;
}
bool Shapes::GetScriptUptoDown()
{
	return scriptuptodown;
}
void Shapes::SetScriptlefttoright(bool i, bool fullreset)
{
	scriptlefttoright = i;
	if (fullreset)
	{
		scriptonce = i;
		scriptcounter = 0;
	}
}
void Shapes::SetScriptOnce(bool i)
{
	scriptonce = i;
}
void Shapes::SetSCriptUptoDown(bool i, bool fullreset)
{
	scriptuptodown = i;
	if (fullreset)
	{
		scriptonce = i;
		scriptcounter = 0;
	}
}
void Shapes::ChangeTexture(SDL_Texture* atexture)
{
	texture = atexture;
}
vector<vec2d> Shapes::AccessPoints()
{
	return points;
}
shapeType Shapes::GetShapeType()
{
	return shapetype;
}
double Shapes::ResetAngle()
{
	double tmp = totalamountrotated;
	Rotate(-totalamountrotated);
	totalamountrotated = 0;
	return tmp;
}
bool Shapes::checktwolinecollision(vec2d one, vec2d one2, vec2d two, vec2d two2,SDL_Renderer * grender)
{
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderDrawLine(grender, one.x, one.y, one2.x, one2.y);
	SDL_SetRenderDrawColor(grender, 0, 100, 100, 0);
	SDL_RenderDrawLine(grender, two.x, two.y, two2.x, two2.y);
	//get line equation for vectors
	double slope1 = (one2.y - one.y) / (one2.x - one.x);
	double b1 = one2.y - slope1 * one2.x;
	//equation is y = slopex + b
	double slope2 = (two2.y - two.y) / (two2.x - two.x);
	double b2 = two2.y - slope2 * two2.x;
	//x = b2-b1/m1-m2
	if (slope1 / slope2 == 0)
	{
		return false;
	}
	double x = (b2 - b1) / (slope1 - slope2);
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
	if ((x <= larger && x >= smaller) && (x<=larger2 && x>= smaller2))
	{
		return true;
	}
	return false;
}
void Shapes::MoveX(double x, bool updatec, bool updatemoveamount)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i].x += x;
	}
	if (updatemoveamount)
	{
		scriptorigin.x += x;
		scriptorigin2.x += x;
		MoveAmount.x += x;
	}
	if(updatec)
		UpdateCircle();
}
void Shapes::MoveY(double x, bool updatec,bool updatemoveamount)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i].y += x;
	}
	if (updatemoveamount)
	{
		scriptorigin.y += x;
		scriptorigin2.y += x;
		MoveAmount.y += x;
	}
	if (updatec)
		UpdateCircle();
}
void Shapes::MoveYpointindex(double x, int index, bool updatec)
{
	points[index].y += x;
	if (updatec)
		UpdateCircle();
}
void Shapes::MoveXpointindex(double x, int index, bool updatec)
{
	points[index].x += x;
	if (updatec)
		UpdateCircle();
}
void Shapes::SetRotationAmount(int degrees)
{
	rotationamount = degrees;
}
int Shapes::GetRotationAmount()
{
	return rotationamount;
}
void Shapes::ZoomShapeSolo(double x)
{
	mat2x2 rotatematrix;
	rotatematrix.column1x = x;
	rotatematrix.column1y = 0;
	rotatematrix.column2x = 0;
	rotatematrix.column2y = x;
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], circleCenter.x, circleCenter.y);
	}
	scriptorigin = rotatematrix.matrixvectorMult(scriptorigin, circleCenter.x, circleCenter.y);
	scriptorigin2 = rotatematrix.matrixvectorMult(scriptorigin2, circleCenter.x, circleCenter.y);
	UpdateCircle();
}
void Shapes::Zoomtomouseinverse(double x, int mx, int my, double determinant)
{
	mat2x2 rotatematrix;
	rotatematrix.column1x = 1.0/x;
	rotatematrix.column1y = 0;
	rotatematrix.column2x = 0;
	rotatematrix.column2y = 1.0/x;
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], mx, my);
		//points[i] = rotatematrix.matrixvectorMult(points[i], 500, 250);
	}
	scriptorigin = rotatematrix.matrixvectorMult(scriptorigin, mx, my);
	scriptorigin2 = rotatematrix.matrixvectorMult(scriptorigin2, mx, my);
	UpdateCircle();
}
void Shapes::Zoomtomouse(double x,int mx,int my)
{
	mat2x2 rotatematrix;
	rotatematrix.column1x = x;
	rotatematrix.column1y = 0;
	rotatematrix.column2x = 0;
	rotatematrix.column2y = x;
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], mx, my);
	}
	scriptorigin = rotatematrix.matrixvectorMult(scriptorigin, mx, my);
	scriptorigin2 = rotatematrix.matrixvectorMult(scriptorigin2, mx, my);
	UpdateCircle();
}
void Shapes::Zoomnomouse(double x)
{
	mat2x2 rotatematrix;
	rotatematrix.column1x = x;
	rotatematrix.column1y = 0;
	rotatematrix.column2x = 0;
	rotatematrix.column2y = x;
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], 500, 250);
		//scriptorigin = rotatematrix.matrixvectorMult(scriptorigin, 500, 250);
	}
	scriptorigin = rotatematrix.matrixvectorMult(scriptorigin, 500, 250);
	scriptorigin2 = rotatematrix.matrixvectorMult(scriptorigin2, circleCenter.x, circleCenter.y);
	UpdateCircle();
}
void Shapes::Rotate(int degrees)
{
	if (shapetype == CIRCLE)
	{
		totalamountrotated += degrees;
		return;
	}
	mat2x2 rotatematrix;
	rotatematrix.column1x = cos(degrees*3.14 / 180);
	rotatematrix.column1y = sin(degrees*3.14 / 180);
	rotatematrix.column2x = -sin(degrees*3.14 / 180);
	rotatematrix.column2y = cos(degrees*3.14 / 180);
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], circleCenter.x, circleCenter.y);
	}
	totalamountrotated += degrees;
	if (Checkslopes())
	{
		Rotate(-degrees);
		/*if(degrees<0)
			Rotate(-1);
		else
			Rotate(1);*/
	}
}
void Shapes::Rotate()
{
	if (shapetype == CIRCLE)
	{
		totalamountrotated += rotationamount;
		return;
	}
	int degrees = rotationamount;
	if (degrees == 0)
		return;
	mat2x2 rotatematrix;
	rotatematrix.column1x = cos(degrees*3.14 / 180);
	rotatematrix.column1y = sin(degrees*3.14 / 180);
	rotatematrix.column2x = -sin(degrees*3.14 / 180);
	rotatematrix.column2y = cos(degrees*3.14 / 180);
	for (int i = 0; i < points.size(); i++)
	{
		points[i] = rotatematrix.matrixvectorMult(points[i], circleCenter.x, circleCenter.y);
	}
	totalamountrotated += degrees;

}
void Shapes::PrintCircle(SDL_Renderer* grender)
{
	SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	double angle = 0;
	vec2d temp;
	for (int i = 0; i < 360; i++)
	{
		temp.x = circleRadius * cos(angle) + circleCenter.x;
		temp.y = circleRadius * sin(angle) + circleCenter.y;
		SDL_RenderDrawPoint(grender, temp.x, temp.y);
		angle += .0174533;
	}
}
void Shapes::Print(SDL_Renderer* grender)
{

}
void Shapes::Print(SDL_Renderer* grender, int r, int g, int b)
{

}
void Shapes::PrintTexture(SDL_Renderer* grender)
{
	SDL_Rect tmprect = { points[0].x,points[0].y,points[1].x - points[0].x,points[3].y - points[0].y };
	SDL_SetRenderDrawColor(grender, 100, 100, 100, 0);
	SDL_RenderCopy(grender, texture, 0, &tmprect);
}
int Shapes::GetCircleRadiusOutside()
{
	return circleRadius;
}
int Shapes::GetCircleRadius()
{
	return insidecircleRadius;
}
vec2d Shapes::GetCircleCenter()
{
	return insidecircleCenter;
}
int Shapes::GetOuterRadius()
{
	return circleRadius;
}
vec2d Shapes::GetOuterCircleCenter()
{
	return circleCenter;
}
double Shapes::Accesszoomedinamount()
{
	return zoomedinamount;
}
void Shapes::RevertMoveAmount()
{
	MoveX(-MoveAmount.x);
	MoveY(-MoveAmount.y);
	MoveAmount.x = 0;
	MoveAmount.y = 0;
}
bool Shapes::Checkslopes()
{
	int index;
	for (int i = 0; i < points.size(); i++)//i+=2
	{
		if (i == points.size() - 1)
			index = 0;
		else
			index = i + 1;
		if (points[i].x - points[index].x == 0)
		{

		}
		else
		{
			double undefined = points[i].x - points[index].x;
			if (undefined != 0)
			{
				double slope = abs((points[i].y - points[index].y) / (points[i].x - points[index].x));
				if (slope != 0)
				{
					if (slope <= .05 && slope >= .0001)
					{
						//return true;
					}
				}
			}
		}
	}
	return false;
}
void Shapes::AddLine()
{
}
void Shapes::SetScriptdir(bool i)
{
	scriptdir = i;
}
bool Shapes::GetScriptdir()
{
	return scriptdir;
}
vec2d Shapes::GetScriptorigin()
{
	return scriptorigin;
}
vec2d Shapes::GetScriptorigin2()
{
	return scriptorigin2;
}
void Shapes::SetScriptorigin1real(double x, double y)
{
	scriptorigin.x = x; scriptorigin.y = y;
}
void Shapes::SetScriptorigin2real(double x, double y)
{
	scriptorigin2.x = x; scriptorigin2.y = y;
}
void Shapes::SetScriptorigins(double x, double y)
{
	scriptorigin.x += x; scriptorigin.y += y;
	scriptorigin2.x += x; scriptorigin2.y += y;
}
void Shapes::ScriptLefttoRight(SDL_Renderer* grender)
{
	double scriptspeedz = abs(scriptorigin.x - scriptorigin2.x)/(scriptspeed);
	//SDL_RenderDrawLine(grender, scriptorigin.x, scriptorigin.y, scriptorigin2.x, scriptorigin2.y);
	//cout << scriptorigin.x << endl;
	if (scriptonce)
	{
		scriptorigin.x = points[0].x; scriptorigin.y = points[0].y;
		scriptorigin2.x = points[0].x + scriptdistance; scriptorigin2.y = points[0].y;
		scriptonce = false;
	}
	if (scriptdir)
	{
		MoveX(scriptspeedz);
		velocity.x = scriptspeedz;
		velocity.y = 0;
	}
	else
	{
		MoveX(-scriptspeedz);
		velocity.x = -scriptspeedz;
		velocity.y = 0;
	}
	scriptcounter += scriptspeedz;
	if (abs(scriptorigin.x - points[0].x) > abs(scriptorigin.x - scriptorigin2.x))
	{
		scriptdir = !scriptdir;
		scriptcounter = 0;
	}
}
void Shapes::ScriptUptoDown()
{
	double scriptspeedz = abs(scriptorigin.y - scriptorigin2.y) / scriptspeed;
	if (scriptonce)
	{
		scriptuptodown = true;
		scriptorigin.x = points[0].x; scriptorigin.y = points[0].y;
		scriptorigin2.x = points[0].x; scriptorigin2.y = points[0].y + scriptdistance;
		scriptonce = false;
	}
	if (scriptdir)
	{
		MoveY(scriptspeedz);
		velocity.y = scriptspeedz;
		velocity.x = 0;
	}
	else
	{
		MoveY(-scriptspeedz);
		velocity.y = -scriptspeedz;
		velocity.x = 0;
	}
	scriptcounter += scriptspeedz;
	if (abs(scriptorigin.y - points[0].y) > abs(scriptorigin.y - scriptorigin2.y))
	{
		scriptdir = !scriptdir;
		scriptcounter = 0;
	}
}
void Shapes::ScriptBallShooter()
{
	//speed will be the object speed once it spawns
	//distance will be the rate at which it fires

	scriptcounter++;
}
void Shapes::ScriptMove()
{
	//script distance positive means x negative means y
		MoveY(scriptspeedy);
		MoveX(scriptspeed);
}
void Shapes::ScriptTempDeath()
{
	scriptcounter++;
	if (scriptcounter >= 200)
	{
		scripttempdeath = false;
		scriptcounter = 0;
	}
}
void Shapes::SetScriptSpeed(double i)
{
	scriptspeed += i;
}
void Shapes::SetScriptSpeedReal(double i)
{
	scriptspeed = i;
}
void Shapes::SetScriptDistance(double i)
{
	scriptdistance += i;
}
void Shapes::SetScriptDistanceReal(double i)
{
	scriptdistance = i;
}
bool  Shapes::GetScriptMove()
{
	return scriptmove;
}
void  Shapes::SetScriptMove(bool i)
{
	scriptmove = i;
}
int Shapes::GetScriptCounter()
{
	return scriptcounter;
}
void Shapes::SetScriptCounter(int x)
{
	scriptcounter = x;
}
double Shapes::GetScriptDistance()
{
	return scriptdistance;
}
bool Shapes::GetScriptTempDeath()
{
	return scripttempdeath;
}
void Shapes::SetScriptTempDeath(bool i)
{
	scripttempdeath = i;
}
double Shapes::GetScriptSpeed()
{
	return scriptspeed;
}
int Shapes::GetTotalAmountRotated()
{
	return totalamountrotated;
}
void Shapes::SetTotalAmountRotated(int i)
{
	totalamountrotated = i;
}
double Shapes::GetScriptSpeedy()
{
	return scriptspeedy;
}
void Shapes::SetScriptSpeedy(double i)
{
	scriptspeedy = i;
}
bool Shapes::GetBouncer()
{
	return bouncer;
}
void Shapes::SetBouncer(bool i)
{
	bouncer = i;
}
int Shapes::GetBounceAmount()
{
	return bounceamount;
}
void Shapes::SetBounceAmount(int i)
{
	bounceamount = i;
}