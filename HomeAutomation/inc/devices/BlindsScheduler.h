//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_BlindsScheduler_H
#define D_BlindsScheduler_H

///////////////////////////////////////////////////////////////////////////////
//
//  BlindsScheduler is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include <map>
#include "TimeService.h"
class HorizontalBlinds;
class RandomMinuteGenerator;
struct ScheduledBlindsEvent;

enum BlindsType { Horizontal, LeftOpeningVertical, RightOpeningVertical };
enum BlindsOperation { Raise, Lower, RaiseToLevel, RaiseRelative, LowerRelative,
    Open, Close, OpenToAngle, OpenRelative, CloseRelative,
    };

class BlindsScheduler
  {
  public:
    explicit BlindsScheduler(TimeService*);
    virtual ~BlindsScheduler();

    virtual void AddBlinds(int id, HorizontalBlinds*);
    virtual HorizontalBlinds* FindBlinds(int id);
    virtual HorizontalBlinds* RemoveBlinds(int id);

    void ScheduleBlindsOperation(int id, Time::Day day, int minute,
            BlindsType, BlindsOperation);

    void ScheduleBlindsOperation(int id, Time::Day day, int minute,
            BlindsType, BlindsOperation, int blindsParameter);

    void ScheduleRemove(int id, Time::Day day, int minute);
    void ScheduleTurnOnRandomize(int id, Time::Day day, int minute);
    void WakeUp(Time);


  private:

    TimeService* timeService;
    std::map<int, HorizontalBlinds*>* blinds;
    RandomMinuteGenerator* randomMinute;

    void CheckEvent(ScheduledBlindsEvent*);
    bool DoesLightRespondToday(Time::Day);
    void TimeToCheckTheSchedule();
    void ScheduleEvent(int id, Time::Day day, int minute, int event, int randomize);
    void Randomize(ScheduledBlindsEvent* e);

    BlindsScheduler(const BlindsScheduler&);
    BlindsScheduler& operator=(const BlindsScheduler&);

  };

struct ScheduledBlindsEvent
{
    int id;
    Time::Day day;
    int minute;
    BlindsOperation operation;
    BlindsType blindsType;
    int parameter;
    bool randomize;
    int randomMinutes;
    int extraRandomEventPreventer;
};

extern ScheduledBlindsEvent eventList[];



#endif  // D_BlindsScheduler_H
