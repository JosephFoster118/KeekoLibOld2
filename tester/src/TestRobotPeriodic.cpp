#include <chrono>
#include <iostream>
#include "TestRobotPeriodic.h"


using namespace std::chrono_literals;
using std::cout;
using std::endl;

TestRobotPeriodic::TestRobotPeriodic() : RobotPeriodic{100ms,"Test System"}
{

}




void TestRobotPeriodic::disabledInit()
{
    cout << "Disable init" << endl;
}

void TestRobotPeriodic::teleopInit()
{
    cout << "Teleop init" << endl;
}

void TestRobotPeriodic::autonInit()
{
    cout << "Auton init" << endl;
}

void TestRobotPeriodic::disabledPeriodic()
{
    cout << "Disable Periodic" << endl;
}

void TestRobotPeriodic::teleopPeriodic()
{
    cout << "Teleop Periodic" << endl;
}

void TestRobotPeriodic::autonPeiodic()
{
    cout << "Auton Periodic" << endl;
}
