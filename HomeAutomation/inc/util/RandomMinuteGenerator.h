//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_RandomMinuteGenerator_H
#define D_RandomMinuteGenerator_H

///////////////////////////////////////////////////////////////////////////////
//
//  RandomMinuteGenerator is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class RandomMinuteGenerator
  {
  public:
    explicit RandomMinuteGenerator(int lowerBound, int upperBound);
    virtual ~RandomMinuteGenerator();

    int Get();

  private:

      int lowerBound;
      int upperBound;

    RandomMinuteGenerator(const RandomMinuteGenerator&);
    RandomMinuteGenerator& operator=(const RandomMinuteGenerator&);

  };

#endif  // D_RandomMinuteGenerator_H
