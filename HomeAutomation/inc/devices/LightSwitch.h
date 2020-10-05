//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_LightController_H
#define D_LightController_H

///////////////////////////////////////////////////////////////////////////////
//
//  LightSwitch is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class LightSwitch
  {
  public:
    explicit LightSwitch();
    virtual ~LightSwitch();

    virtual void On(int id);
    virtual void Off(int id);

  private:

    LightSwitch(const LightSwitch&);
    LightSwitch& operator=(const LightSwitch&);

  };

#endif  // D_LightController_H
