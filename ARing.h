#ifndef __ARING_H__
#define __ARING_H__


class ARing
{
public:
  ARing() {}
  ARing(double R, double C, double SigmaX, double SigmaY, double SigmaR, double XM, double YM, double RM);
  virtual ~ARing() {}

  // sets...

  // gets...
  double R()      {return r;}
  double C()      {return c;}
  double SigmaX() {return sx;}
  double SigmaY() {return sx;}
  double SigmaR() {return sr;}
  double Xmean()  {return xm;}
  double Ymean()  {return ym;}
  double Rmean()  {return rm;}

protected:
  double r;
  double c;
  double sx;
  double sy;
  double sr;
  double xm;
  double ym;
  double rm;

};

#endif /* __ARING_H__ */
