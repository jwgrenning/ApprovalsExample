/*
    Fakes generated from: tmp-build-errors.txt

    Generated file to help to quickly stub C++ undefined external functions.

    * Add this file to your test build.
    * One at a time
      * Uncomment an exploing fake function definition.
      * Add needed the include file.
      * Modify non-void function return types and propvide a return value.
      * Fix errors.
      * Work carefully. Use the compiler and link error output to test your changes.

    * You could customize the BOOM macros to only fail the test, rather than exit the
      test runner.

*/

#include <stdio.h>
#include <stdlib.h>

#define BOOM_MESSAGE printf("BOOM! time to write a better fake for %s\n", __func__)
#define BOOM_VOID_CPP BOOM_MESSAGE; exit(1);
#define BOOM_VALUE_CPP(result) BOOM_MESSAGE; exit(1); return result;

/*
*   Production code header files
*/

#include "LightSwitch.h"

LightSwitch::LightSwitch() { BOOM_VOID_CPP }
LightSwitch::~LightSwitch() { BOOM_VOID_CPP }
void LightSwitch::Off(int) { BOOM_VOID_CPP }
void LightSwitch::On(int) { BOOM_VOID_CPP }

#include "RandomMinuteGenerator.h"
int RandomMinuteGenerator::Get() { BOOM_VOID_CPP }
RandomMinuteGenerator::RandomMinuteGenerator(int, int) { BOOM_VOID_CPP }
RandomMinuteGenerator::~RandomMinuteGenerator() { BOOM_VOID_CPP }

#include "TimeService.h"
void TimeService::cancelWakePeriodically(void*) { BOOM_VOID_CPP }
Time TimeService::getTime() { BOOM_VOID_CPP }
void * TimeService::wakePeriodically(std::__1::unique_ptr<WakeUpAction, std::__1::default_delete<WakeUpAction> >) { BOOM_VOID_CPP }


Time::Time(Time const&) { BOOM_VOID_CPP }
Time::Day Time::getDay() const { BOOM_VOID_CPP }
int Time::getMinute() const { BOOM_VOID_CPP }
Time::~Time() { BOOM_VOID_CPP }
TimeService::TimeService() { BOOM_VOID_CPP }
TimeService::~TimeService() { BOOM_VOID_CPP }
WakeUpAction::WakeUpAction(int) { BOOM_VOID_CPP }
WakeUpAction::~WakeUpAction() { BOOM_VOID_CPP }
