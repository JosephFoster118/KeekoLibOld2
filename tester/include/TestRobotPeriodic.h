#pragma once
#include "RobotPeriodic.h"



class TestRobotPeriodic: public RobotPeriodic
{   
public:
    TestRobotPeriodic(const TestRobotPeriodic&) = delete;//Removes the copy constructor
    TestRobotPeriodic();
    virtual ~TestRobotPeriodic(){};

private:

    void disabledInit();
    void teleopInit();
    void autonInit();

    void disabledPeriodic();
    void teleopPeriodic();
    void autonPeiodic();

};