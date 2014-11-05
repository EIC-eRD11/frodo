#ifndef __COORDINATES_H__
#define __COORDINATES_H__

#include "TObject.h"

class Coordinates
{
public:
  Coordinates() {}
  Coordinates (double COR){c=COR;}
  virtual ~Coordinates() {}

  double Cor() {return c;}

protected:
  double c;
};

#endif /* __COORDINATES_H__ */
