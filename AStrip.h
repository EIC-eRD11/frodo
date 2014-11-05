#ifndef __ASTRIP_H__
#define __ASTRIP_H__

//
//  Hello Astrip Fans:
//
//  The strips are charge collection regions.  These are assumed to be 
//  simple rectangles that can be defined by their corners.  Methods
//  of the strip class will return both the X center and Y center.
//  They also carry some charge.
//
//  The PadStrip class inherits all these characteristics from the 
//  Strip class and adds the "segmentation" of the pads themselves.
//
//                                                HG & TKH
//                                                11-16-2011
//

class AStrip
{
public:
  AStrip() {x1=0; y1=0; x2=0; y2=0; q=0;}
  AStrip(double, double, double, double );
  virtual ~AStrip() {}

  void Clear() {q=0;}

  // sets...
  void SetQ(double Q) {q = Q;}
  void AddQ(double Q) {q += Q;}

  // gets...
  double const XCenter()  {return (x1+x2)/2.0;}
  double const YCenter()  {return (y1+y2)/2.0;}
  double Q            ()  {return q;}

  // Graphics:
  virtual void Draw(double,double,double,double,int);

protected:
  double x1;
  double y1;
  double x2;
  double y2;
  double q;

};

#endif /* __ASTRIP_H__ */
