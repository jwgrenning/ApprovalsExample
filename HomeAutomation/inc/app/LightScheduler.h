//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.


extern int lights[];
void turn_on();


#if 0

class LightSwitch;
class RandomMinuteGenerator;

class LightScheduler
  {
  public:
    explicit LightScheduler();
    virtual ~LightScheduler();

    void AddTurnOn(int id, Time::Day day, int minute);
    void AddTurnOff(int id, Time::Day day, int minute);
    void Remove(int id, Time::Day day, int minute);
    void RandomizeTurnOn(int id, Time::Day day, int minute);
    void RandomizeTurnOff(int id, Time::Day day, int minute);
    void WakeUp(Time);

  private:
    TimeService* timeService;
    LightSwitch* lightSwitch;
    RandomMinuteGenerator* randomMinute;

struct ScheduledLightEvent {
    int id;
    Time::Day d;
    int min;
    int evnt;
    int rndmiz;
    int rndMin;
    int extraREPreventer;
};

    static ScheduledLightEvent eventList[];

    void TimeToCheckTheSchedule();
    void ClearEventList();

    LightScheduler(const LightScheduler&);
    LightScheduler& operator=(const LightScheduler&);

  };



#endif  // D_LightScheduler_H
