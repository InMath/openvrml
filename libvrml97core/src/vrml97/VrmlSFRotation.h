//
//  Vrml 97 library
//  Copyright (C) 1998 Chris Morley
//  See the file COPYING for license details.
//
#ifndef  _VRMLSFROTATION_
#define  _VRMLSFROTATION_

#include "VrmlField.h"

class VrmlSFRotation : public VrmlSField {
public:

  VrmlSFRotation(float x = 0.0, float y = 0.0, float z = 1.0, float r = 0.0);

  virtual ostream& print(ostream& os) const;

  virtual VrmlField *clone() const;

  virtual VrmlFieldType fieldType() const;
  virtual const VrmlSFRotation* toSFRotation() const;
  virtual VrmlSFRotation* toSFRotation();

  float x() const		{ return d_x[0]; }
  float y() const		{ return d_x[1]; }
  float z() const	        { return d_x[2]; }
  float r() const		{ return d_x[3]; }
  float *get()			{ return &d_x[0]; }

  void set(float x, float y, float z, float r)
    { d_x[0] = x; d_x[1] = y; d_x[2] = z; d_x[3] = r; }

  void invert(void);
  void multiply(VrmlSFRotation*);
  
  void ToQuaternion(float* theQuat);
  void FromQuaternion(float* theQuat);
  void MultQuat(float* result, float* quat1, float* quat2);
  
  void slerp(VrmlSFRotation*, float);  

private:
  float d_x[4];

};

#endif _VRMLSFROTATION_
