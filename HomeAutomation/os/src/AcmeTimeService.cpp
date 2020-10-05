//- Copyright (c) 2008-2020 James Grenning
//- All rights reserved
//- For use by participants in Wingman Software training courses.

#include "AcmeTimeService.h"

AcmeTimeService::AcmeTimeService()
{
    //OS dependent initialization
}

AcmeTimeService::~AcmeTimeService()
{
    //OS dependent cleanup
}

Time AcmeTimeService::getTime()
{
    //OS dependent
    Time t;
    return t;
}


void * AcmeTimeService::wakePeriodically(std::unique_ptr<WakeUpAction>)
{
    //OS dependent
    return 0;
}

void AcmeTimeService::cancelWakePeriodically(void *)
{
    //OS dependent
}


