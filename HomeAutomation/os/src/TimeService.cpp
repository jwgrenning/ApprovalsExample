//- Copyright (c) 2008-2020 James Grenning
//- All rights reserved
//- For use by participants in Wingman Software training courses.

#include "TimeService.h"

TimeService::TimeService()
{
}

TimeService::~TimeService()
{
}

Time::Time()
: day(NONE), minute(-1)
{
}

Time::Time(Day day, int minute)
:day(day), minute(minute)
{
}

Time::~Time()
{
}

Time::Time(const Time& other)
{
    this->day = other.day;
    this->minute = other.minute;
}

Time& Time::operator=(const Time& other)
{
    if (this != &other)
    {
        this->day = other.day;
        this->minute = other.minute;
    }

    return *this;
}

Time::Day Time::getDay() const
{
    return day;
}

int Time::getMinute() const
{
    return minute;
}

WakeUpAction::WakeUpAction(int seconds)
: seconds(seconds)
{
}

WakeUpAction::~WakeUpAction()
{
}
