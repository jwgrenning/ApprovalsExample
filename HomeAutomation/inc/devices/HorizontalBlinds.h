//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_HorizontalBlinds_H
#define D_HorizontalBlinds_H

///////////////////////////////////////////////////////////////////////////////
//
//  HorizontalBlinds is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class HorizontalBlinds
  {
  public:
    explicit HorizontalBlinds();
    virtual ~HorizontalBlinds();

    virtual void Raise() = 0;
    virtual void Lower() = 0;
    virtual void RaiseAbsolute(int percentUp) = 0;
    virtual void RaiseRelative(int percentUp) = 0;
    virtual void LowerRelative(int percentDown) = 0;
    virtual void LouverOpen() = 0;
    virtual void LouverClose() = 0;
    virtual void LouverOpenAbsolute(int angle) = 0;
    virtual void LouverRelativeOpen(int angle) = 0;
    virtual void LouverRelativeClose(int angle) = 0;
    virtual int GetLevel() const = 0;
    virtual int GetAngle() const = 0;
    virtual int GetId() const = 0;
    enum { FullyOpen = 90, FullyClosed = 0,
        FullyRaised = 100, FullyLowered = 0};

  private:

    HorizontalBlinds(const HorizontalBlinds&);
    HorizontalBlinds& operator=(const HorizontalBlinds&);

  };

#endif  // D_HorizontalBlinds_H
