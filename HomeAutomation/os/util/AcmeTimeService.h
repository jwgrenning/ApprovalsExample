//- Copyright (c) 2008-2019 James Grenning
//- All rights reserved
//- For use by participants in Wingman Software training courses.

#ifndef ACME_TIME_SERVICE_INCLUDED
#define ACME_TIME_SERVICE_INCLUDED

#include "TimeService.h"

class WakeupAction;
class Time;

class AcmeTimeService : public TimeService
{
public:
    explicit AcmeTimeService();
    virtual ~AcmeTimeService();

    virtual Time getTime();
    virtual void * wakePeriodically(std::unique_ptr<WakeUpAction>) = 0;
    virtual void cancelWakePeriodically(void * wakeupCancelKey) = 0;

private:
    AcmeTimeService(const AcmeTimeService&);
    AcmeTimeService& operator=(const AcmeTimeService&);
};

#endif
