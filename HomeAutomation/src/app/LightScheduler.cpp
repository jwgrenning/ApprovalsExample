//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.


#include "TimeService.h"
#include "LightScheduler.h"
#include "LightSwitch.h"
#include "RandomMinuteGenerator.h"
#include <stdlib.h>
#include <memory.h>

extern "C"
{
    #include "logger.h"
}

enum {
    TURNON, TURNOFF, RANDOM_ON, RANDOM_OFF
};

enum {
    MAX_EVENTS = 64,
    UNUSED = -1
};

class LightSchedulerWakeUpAction : public WakeUpAction
{
    LightScheduler* scheduler;

public:
    LightSchedulerWakeUpAction(LightScheduler* scheduler)
    : WakeUpAction(60)
    , scheduler(scheduler) {}

    virtual void wakeUp(Time t) {
        scheduler->WakeUp(t);
    }
};

LightScheduler::LightScheduler()
: randomMinute(0)
{
    log_debug("LightScheduler::LightScheduler()");
    for(int i = 0;i < MAX_EVENTS;i++)
    {
        eventList[i].id = UNUSED;
    }
    timeService = new TimeService;
    lightSwitch = new LightSwitch;
    timeService->wakePeriodically(std::unique_ptr<WakeUpAction>(new LightSchedulerWakeUpAction(this)));
}

LightScheduler::~LightScheduler()
{
    log_debug("LightScheduler::~LightScheduler()");
    delete timeService;
    delete lightSwitch;
}

void LightScheduler::WakeUp(Time t)
{
    TimeToCheckTheSchedule();
}

void LightScheduler::AddTurnOn(int id, Time::Day day, int minute)
{
    log_debug("LightScheduler::AddTurnOn");
	int event = TURNON;
	int random = RANDOM_OFF;
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].d = day;
            eventList[i].min = minute;
            eventList[i].evnt = event;
            eventList[i].rndmiz = random;
            eventList[i].extraREPreventer = 0;
            eventList[i].rndMin = 0;
            break;
        }
    }
}

void LightScheduler::AddTurnOff(int id, Time::Day day, int minute)
{
    log_debug("LightScheduler::AddTurnOn");
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].d = day;
            eventList[i].min = minute;
            eventList[i].evnt = TURNOFF;
            eventList[i].rndmiz = RANDOM_OFF;
            eventList[i].extraREPreventer = 0;
            eventList[i].rndMin = 0;
            break;
        }
    }
}

void LightScheduler::RandomizeTurnOn(int id, Time::Day day, int minute)
{
    log_debug("LightScheduler::AddTurnOn");
    if (!randomMinute)
        randomMinute = new RandomMinuteGenerator(-30, 30);
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].d = day;
            eventList[i].min = minute;
            eventList[i].evnt = TURNON;
            eventList[i].rndmiz = RANDOM_ON;
            eventList[i].extraREPreventer = 0;
            eventList[i].rndMin = 0;
            break;
        }
    }
}

void LightScheduler::RandomizeTurnOff(int id, Time::Day day, int minute)
{
    log_debug("LightScheduler::AddTurnOn");
    if (!randomMinute)
        randomMinute = new RandomMinuteGenerator(-3, 30);
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].d = day;
            eventList[i].min = minute;
            eventList[i].evnt = TURNON;
            eventList[i].rndmiz = RANDOM_OFF;
            eventList[i].extraREPreventer = 0;
            eventList[i].rndMin = 0;
            break;
        }
    }
}

void LightScheduler::TimeToCheckTheSchedule()
{
    log_debug("LightScheduler::AddTurnOn");
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id != UNUSED)
        {
            ScheduledLightEvent* sle = &eventList[i];
            if (sle->extraREPreventer > 0)
            {
                sle->extraREPreventer--;
            }
            else
            {
                Time t = timeService->getTime();
                int today = t.getDay();


                if ((sle->d == Time::EVERYDAY || sle->d == today
                || (sle->d == Time::WEEKEND
                && (Time::SATURDAY == today
                || Time::SUNDAY == today))
                || (sle->d == Time::WEEKDAY
                && today >= Time::MONDAY
                && today <= Time::FRIDAY)))
                {
                    if (t.getMinute() == sle->min
                            + sle->rndMin)
                    {
                        if (TURNON == sle->evnt)
                            lightSwitch->On(sle->id);
                        else if (TURNOFF == sle->evnt)
                            lightSwitch->Off(sle->id);

                        if (sle->rndmiz == RANDOM_ON)
                            sle->rndMin = randomMinute->Get();
                        else
                            sle->rndMin = 0;

                        sle->extraREPreventer = 61;
                    }
                }
            }
        }
    }
}

void LightScheduler::Remove(int id, Time::Day day, int minute)
{
    log_debug("LightScheduler::AddTurnOn");
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id
        && eventList[i].d == day
        && eventList[i].min == minute)
        {
            eventList[i].id = UNUSED;
        }
    }
}
