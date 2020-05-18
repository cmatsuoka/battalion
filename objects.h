#ifndef BATTALION_OBJECTS_H_
#define BATTALION_OBJECTS_H_

#include <GL/gl.h>

GLuint makeMonsterLookat(void);
GLuint makeOverviewLookat(void);

GLuint makeshell2(void);
GLuint makeHeroShell(void);
GLuint makeWaterShell(void);

GLuint makeTankShadow(void);
GLuint makeFighterShadow(void);
GLuint makePlaneShadow(void);

GLuint makeTank(void);
GLuint makeSlagTank(void);
GLuint makeLauncherTank(void);
GLuint makeSlagLauncherTank(void);
GLuint makeMaserTank(void);
GLuint makeSlagMaserTank(void);

GLuint makeHelo(void);
GLuint makeSlagHelo(void);
GLuint makeBigRotor(void);
GLuint makeSmallRotor(void);
GLuint makePropeller(void);
GLuint makeAirplaneBody(void);
GLuint makeFighterBody(void);

GLuint makeLeg(void);
GLuint makeHead(void);
GLuint makeTail(void);
GLuint makeSimpleHead(void);
GLuint makeSimpleTail(void);
GLuint makeBody(void);

GLuint makeFlutterHead(void);
GLuint makeFlutterShadow(void);
GLuint makeFlutterXMas(void);
GLuint makeFlutterBody(void);
GLuint makeFlutterWing1(void);
GLuint makeFlutterWing2(void);

GLuint makeTechsBody(void);
GLuint makeTechsHead(void);
GLuint makeTechsSimpleBody(void);
GLuint makeTechsSimpleHead(void);
GLuint makeTechsShadow(void);

GLuint makePowerTower(void);
GLuint makeGenericWindows(void);
GLuint makebuilding1(int);
GLuint makebuilding2(int);
GLuint makebuilding5(int);
GLuint makebuilding7(void);
GLuint makebuilding9(int);
GLuint makebuilding10(void);
GLuint makebuilding12(int);
GLuint makebuilding14(void);
GLuint makebuilding19(int);
GLuint makebuilding20(int);
GLuint makebuilding21(int);
GLuint makebuilding31(void);
GLuint makebuilding32(void);
GLuint makeStrip1(int);
GLuint makeStrip2(int);
GLuint makeStrip3(int);

GLuint makeTitles(int);

GLuint makeLowDPlane(void);
GLuint makeHighDPlane(void);
GLuint makeBigPlane(void);
GLuint makePlaneDots(int);

GLuint makeRoundTreeShadow(void);

#endif  // BATTALION_OBJECTS_H_
