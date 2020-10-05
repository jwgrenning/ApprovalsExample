//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#include "RandomMinuteGenerator.h"
#include <stdlib.h>

RandomMinuteGenerator::RandomMinuteGenerator(int lowerBound, int upperBound)
: lowerBound(lowerBound)
, upperBound(upperBound)
{
}

RandomMinuteGenerator::~RandomMinuteGenerator()
{
}

int RandomMinuteGenerator::Get()
{
    int range = upperBound - lowerBound;

    return upperBound - rand() % (range + 1);
;
}

