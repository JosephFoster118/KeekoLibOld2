
#include "RobotPeriodic.h"

RobotPeriodic::RobotPeriodic(std::chrono::microseconds thread_period, std::string subsystem_name)
{
    name = subsystem_name;
    period = thread_period;
    startState();
}

void RobotPeriodic::startState()
{
    std::function<void()> lambda;
    if(thread != nullptr)
    {
        thread->stop();
    }
    switch(robot_state)
    {
        case DISABLED:
        {
            disabledInit();
            thread = std::make_unique<PeriodicThread>(period, name,
            [this]()
            {
                this->disabledPeriodic();
            });
        }break;
        case AUTON:
        {
            autonInit();
            thread = std::make_unique<PeriodicThread>(period, name,
            [this]()
            {
                this->autonPeiodic();
            });
        }break;
        case TELEOP:
        {
            teleopInit();
            thread = std::make_unique<PeriodicThread>(period, name,
            [this]()
            {
                this->teleopPeriodic();
            });
        }break;
    }
    thread->start();
}

void RobotPeriodic::changeState(RobotState new_state)
{
    robot_state = new_state;
    startState();
}
 