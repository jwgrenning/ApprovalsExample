//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_NullHorizontalBlinds_H
#define D_NullHorizontalBlinds_H

///////////////////////////////////////////////////////////////////////////////
//
//  NullHorizontalBlinds.h
//
//  NullHorizontalBlinds is responsible for providing a test stub
//  for HorizontalBlinds
//
///////////////////////////////////////////////////////////////////////////////
#include "HorizontalBlinds.h"

class NullHorizontalBlinds: public HorizontalBlinds
{
public:
    explicit NullHorizontalBlinds(int id = -1)
    : id(id)
    { }

    virtual ~NullHorizontalBlinds() { }

    virtual void Raise() {  }
    virtual void Lower() {  }
    virtual void RaiseAbsolute(int) { }
    virtual void RaiseRelative(int) { }
    virtual void LowerRelative(int) { }
    virtual void LouverOpen() {  }
    virtual void LouverClose( ) {  }
    virtual void LouverOpenAbsolute(int) { }
    virtual void LouverRelativeOpen(int) { }
    virtual void LouverRelativeClose(int) { }
    virtual int GetLevel() const { return 0; }
    virtual int GetAngle() const { return 0; }
    virtual int GetId() const { return id; }

private:

    int id;

    NullHorizontalBlinds(const NullHorizontalBlinds&);
    NullHorizontalBlinds& operator=(const NullHorizontalBlinds&);
};

#endif  // D_NullHorizontalBlinds_H
