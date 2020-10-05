//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#include "BlindsScheduler.h"
#include "HorizontalBlinds.h"
#include "NullHorizontalBlinds.h"
#include "TimeService.h"
#include "RandomMinuteGenerator.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

enum
{
    MAX_EVENTS = 64, UNUSED = -1
};

using namespace std;

class BlindsWakeUpAction: public WakeUpAction
{
    BlindsScheduler* scheduler;

public:
    BlindsWakeUpAction(BlindsScheduler* scheduler)
        : WakeUpAction(60)
        , scheduler(scheduler)
    {
    }

    virtual void wakeUp(Time t)
    {
        scheduler->WakeUp(t);
    }
};

BlindsScheduler::BlindsScheduler(TimeService* timeService) :
    timeService(timeService), blinds(0), randomMinute(0)
{
    blinds = new map<int, HorizontalBlinds*>;
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        eventList[i].id = UNUSED;
    }
    randomMinute = new RandomMinuteGenerator(-30, 30);
    timeService->wakePeriodically(std::unique_ptr<WakeUpAction>(new BlindsWakeUpAction(this)));
}

BlindsScheduler::~BlindsScheduler()
{
    map<int, HorizontalBlinds*>::iterator i = blinds->begin();
    for (; i != blinds->end(); i++)
    {
        HorizontalBlinds* b = i->second;
        delete b;
    }
    blinds->clear();
    delete blinds;
    delete randomMinute;
}

void BlindsScheduler::AddBlinds(int id, HorizontalBlinds* b)
{
//    delete RemoveBlinds(id);
    map<int, HorizontalBlinds*>::iterator found = blinds->find(id);

    if (found != blinds->end())
    {
        HorizontalBlinds* f = found->second;
        blinds->erase(found);
        delete f;
    }
    blinds->insert(make_pair(id, b));
}

static NullHorizontalBlinds nullBlinds;

HorizontalBlinds* BlindsScheduler::FindBlinds(int id)
{
    if (blinds->find(id) == blinds->end())
        return &nullBlinds;
    return blinds->find(id)->second;
}

HorizontalBlinds* BlindsScheduler::RemoveBlinds(int id)
{
    HorizontalBlinds* foundBlinds;

    map<int, HorizontalBlinds*>::iterator
            found = blinds->find(id);

    if (found != blinds->end())
    {
        foundBlinds = found->second;
        blinds->erase(found);
    }
    else
    {
        foundBlinds = new NullHorizontalBlinds();
    }

    return foundBlinds;
}

void BlindsScheduler::WakeUp(Time)
{
    TimeToCheckTheSchedule();
}

void BlindsScheduler::ScheduleTurnOnRandomize(int id, Time::Day day, int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id && eventList[i].day == day
                && eventList[i].minute == minute)
        {
            eventList[i].randomize = true;
        }
    }

}

void BlindsScheduler::Randomize(ScheduledBlindsEvent* e)
{
    if (e->randomize)
        e->randomMinutes = randomMinute->Get();
    else
        e->randomMinutes = 0;
}

void BlindsScheduler::ScheduleBlindsOperation(int id, Time::Day day,
        int minute, BlindsType type, BlindsOperation operation)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minute = minute;
            eventList[i].operation = operation;
            eventList[i].blindsType = type;
            eventList[i].randomize = false;
            eventList[i].extraRandomEventPreventer = 0;
            Randomize(&eventList[i]);
            break;
        }
    }

}

void BlindsScheduler::ScheduleBlindsOperation(int id, Time::Day day,
        int minute, BlindsType type, BlindsOperation operation, int param)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minute = minute;
            eventList[i].operation = operation;
            eventList[i].parameter = param;
            eventList[i].blindsType = type;
            eventList[i].randomize = false;
            eventList[i].extraRandomEventPreventer = 0;
            Randomize(&eventList[i]);
            break;
        }
    }

}

bool BlindsScheduler::DoesLightRespondToday(Time::Day reactionDay)
{
    int today = timeService->getTime().getDay();

    if (reactionDay == Time::EVERYDAY)
        return true;
    if (reactionDay == today)
        return true;
    if (reactionDay == Time::WEEKEND && (Time::SATURDAY == today
            || Time::SUNDAY == today))
        return true;
    if (reactionDay == Time::WEEKDAY && today >= Time::MONDAY
            && today <= Time::FRIDAY)
        return true;
    return false;
}

void BlindsScheduler::CheckEvent(ScheduledBlindsEvent* blindsEvent)
{
    if (blindsEvent->extraRandomEventPreventer > 0)
    {
        blindsEvent->extraRandomEventPreventer--;
        return;
    }

    if (!DoesLightRespondToday(blindsEvent->day))
        return;
    if (timeService->getTime().getMinute() != blindsEvent->minute
            + blindsEvent->randomMinutes)
        return;

    switch (blindsEvent->blindsType)
    {
    case Horizontal:
    HorizontalBlinds* theBlinds;
        switch (blindsEvent->operation)
        {
        case Raise:
            theBlinds = FindBlinds(blindsEvent->id);
            theBlinds->Raise();
            break;
        case Lower:
            theBlinds = FindBlinds(blindsEvent->id);
            theBlinds->Lower();
            break;
        case RaiseToLevel:
            theBlinds = FindBlinds(blindsEvent->id);
            if (blindsEvent->parameter > HorizontalBlinds::FullyRaised)
                theBlinds->Raise();
            else if (blindsEvent->parameter < HorizontalBlinds::FullyLowered)
                theBlinds->Lower();
            else
                theBlinds->RaiseAbsolute(blindsEvent->parameter);
            break;
        case RaiseRelative:
            theBlinds = FindBlinds(blindsEvent->id);
            if (theBlinds->GetLevel() + blindsEvent->parameter > HorizontalBlinds::FullyRaised)
                theBlinds->Raise();
            else
                theBlinds->RaiseRelative(blindsEvent->parameter);
            break;
        case LowerRelative:
            theBlinds = FindBlinds(blindsEvent->id);
            if (theBlinds->GetLevel() - blindsEvent->parameter < HorizontalBlinds::FullyLowered)
                theBlinds->Lower();
            else
                theBlinds->LowerRelative(blindsEvent->parameter);
            break;

        case Close:
            theBlinds = FindBlinds(blindsEvent->id);
            theBlinds->LouverClose();
            break;
        case Open:
            theBlinds = FindBlinds(blindsEvent->id);
            theBlinds->LouverOpen();
            break;
        case OpenToAngle:
            theBlinds = FindBlinds(blindsEvent->id);
            if (blindsEvent->parameter > HorizontalBlinds::FullyOpen)
                theBlinds->LouverOpen();
            else if (blindsEvent->parameter < HorizontalBlinds::FullyClosed)
                theBlinds->LouverClose();
            else
                theBlinds->LouverOpenAbsolute(blindsEvent->parameter);
            break;
        case OpenRelative:
            theBlinds = FindBlinds(blindsEvent->id);
            if (theBlinds->GetAngle() + blindsEvent->parameter > HorizontalBlinds::FullyOpen)
                theBlinds->LouverOpen();
            else
                theBlinds->LouverRelativeOpen(blindsEvent->parameter);
            break;
        case CloseRelative:
            theBlinds = FindBlinds(blindsEvent->id);
            if (theBlinds->GetAngle() - blindsEvent->parameter < HorizontalBlinds::FullyClosed)
                theBlinds->LouverClose();
            else
                theBlinds->LouverRelativeClose(blindsEvent->parameter);
            break;
        default:
            printf("\nthis should not happen\n");//this should not happen!
            break;

        }
        break;
    case LeftOpeningVertical:
        break; //todo
    case RightOpeningVertical:
        break; //todo
    default:
    	break; //todo
    };

Randomize(blindsEvent);
blindsEvent->extraRandomEventPreventer = 61;
//how should we get rid of this magic number?
}

void BlindsScheduler::TimeToCheckTheSchedule()
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id != UNUSED)
            CheckEvent(&eventList[i]);
    }
}

void BlindsScheduler::ScheduleRemove(int id, Time::Day day, int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id && eventList[i].day == day
                && eventList[i].minute == minute)
        {
            eventList[i].id = UNUSED;
        }
    }
}
