//- Copyright (c) 2008-2019 James Grenning
//- All rights reserved
//- For use by participants in Wingman Software training courses.

#ifndef TIME_SERVICE_INCLUDED
#define TIME_SERVICE_INCLUDED

#include <stdint.h>
#include <memory>

class WakeUpAction;
class Time;

class TimeService
{
public:
    TimeService();
    virtual ~TimeService();
    virtual Time getTime();
    virtual void * wakePeriodically(std::unique_ptr<WakeUpAction>);
    virtual void cancelWakePeriodically(void * wakeupCancelKey);

private:
    TimeService(const TimeService&);
    TimeService& operator=(const TimeService&);
};

class Time
{
public:
    enum Day {
      NONE=-1, SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY,
      THURSDAY, FRIDAY, SATURDAY, EVERYDAY, WEEKDAY, WEEKEND
    };

    Time();
    Time(Day day, int minute);
    Time(const Time&);
    Time& operator=(const Time&);
    ~Time();
    Day getDay() const;
    int getMinute() const;

private:
    Day day;
    int minute;
};

class WakeUpAction
{
public:
    WakeUpAction(int seconds);
    virtual ~WakeUpAction();
    virtual void wakeUp(Time t) = 0;
    int getSeconds() const { return seconds; }

private:

    int seconds;
    WakeUpAction(const WakeUpAction&);
    WakeUpAction& operator=(const WakeUpAction&);
};

#endif
