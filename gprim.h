#ifndef BATTALION_GPRIM_H_
#define BATTALION_GPRIM_H_

void drawCylinder        (float *, float *, float, int, int, int);
void drawClosedCylinder  (float *, float *, int, int);

void drawCone            (float *, float *, float, int, int);
void drawClosedCone      (float *, float *, int);

void maker               (float tail2[8][3], float, float, float, float, float, float, float *,
                          float, float, float, float);
void makerP              (float tail2[8][3], float *, float, float, float, float, float, float);
void makeitd             (int, float *, float, float, float, float, float, float);
void makeitPyr           (int, float *, float, float, float, float, float, float);
void makercube           (float x, float y, float z, float u, float v, float w, float c[4]);
void makerbluecube       (float x, float y, float z, float u, float v, float w, float c[4]);
void makercubenobacknotop(float x, float y, float z, float u, float v, float w, float c[4]);
void makerlogo           (float x, float y, float z, float u, float v, float w, int, int, int);
void makercubeTopBack    (float x, float y, float z, float u, float v, float w, float c[4]);
void makercubenobtm      (float x, float y, float z, float u, float v, float w, float c[4]);
void makercubenobtmnotop (float x, float y, float z, float u, float v, float w, float c[4]);
void makercubenobtmnotopTEX(float x, float y, float z, float u, float v, float w, float c[4]);
void makerrotcubexy      (float u, float v, float w, float theta, float c[4]);
void makerrotcubexyflat  (float u, float v, float w, float theta, float c[4]);

#endif  // BATTALION_GPRIM_H_
