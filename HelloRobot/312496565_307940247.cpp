/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

using namespace PlayerCc;
using namespace std;


//#define SAMPLES_NUM 682
#define LEFT			(0)
#define MID_LEFT		(1)
#define MID				(2)
#define MID_RIGHT		(3)
#define RIGHT			(4)


#define NUM_OF_SENSORS 	(5)

#define SPEED 			(1)

int SonarDegree[] = {-90, -25, 0, 25, 90};

void PrintObjectLocationByPosition(double MyXpos, double MyYpos, double Yaw, int SensorIndex, double Distance)
{
	double TargetXpos = Distance * cos(Yaw + dtor(SonarDegree[SensorIndex])) + MyXpos;
	double TargetYpos = Distance * cos(Yaw + dtor(SonarDegree[SensorIndex])) + MyYpos;

	cout << "An object at X - " << TargetXpos << " Y - " << TargetYpos  << endl;
}

void MoveDistance(PlayerClient pc, Position2dProxy& pp, double Meters)
{
	pc.Read();
	int StartPos = pp.GetXPos();

	pp.SetSpeed(SPEED, 0);

	while ((pp.GetXPos() - StartPos) < 1)
	{
		pc.Read();
	}

	pp.SetSpeed(0, 0);

}


int main() {

	PlayerClient pc("localhost", 6665);
	//LaserProxy lp(&pc);
	SonarProxy sp(&pc);
	Position2dProxy pp(&pc);

	pc.Read();

	pp.SetSpeed(0.2, 0);

	while(1)
	{
		pc.Read();
		if ((sp[MID] < 0.6) || (sp[MID_LEFT] < 0.6) || (sp[MID_RIGHT] < 0.6))
		{

			PrintObjectLocationByPosition(pp.GetXPos(), pp.GetYPos(),  pp.GetYaw(), 2, sp[2]);

			// TURN
			float Angle;
			if (sp [LEFT] > sp[RIGHT])
			{
				Angle = dtor(30);
			}
			else
			{
				Angle = dtor(-30);
			}

			pp.SetSpeed(0, Angle);

			while ((sp[MID] < 0.6) || (sp[MID_LEFT] < 0.6) || (sp[MID_RIGHT] < 0.6))
				pc.Read();


			pp.SetSpeed(0.2, 0);

		}

	}

	return 0;

}

