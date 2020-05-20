#ifndef BATTALION_GRAPHICS_H_
#define BATTALION_GRAPHICS_H_

void makeObjects(char *);

void shadow (float,  float,  float,  float);

void makeCHH(int);
void drawHelo(float, int);
void drawAirplane(int);
void drawFighter();

void drawMonster(struct monsterInfo *, int, int, int);
void drawSimpleMonster(struct monsterInfo *, int, int, int);

void drawVapour(struct monsterInfo *, int, int);
void drawFlutter(struct monsterInfo *, int, int, float, int, int);
void drawTechs(struct monsterInfo *, int);
void drawSimpleTechs(struct monsterInfo *, int);
void drawHeroDude(int, int,  int, int, int);
void drawHeroDude2(int, int,  int, int, int);
void drawMechaMonster(int, int, int);

void wzminus(float,  float,  float,  float,  float);
void wzplus(float,  float,  float,  float,  float);
void wxplus(float,  float,  float,  float,  float);
void wxminus(float,  float,  float,  float,  float);

void drawBuilding15(float *,  float *, int);
void drawTower(int, int);
void drawBattlefield(struct road *, float, float, int, int,int);

void drawtrees(struct tree *, int, int, int, int,int);

void drawSlagTanks(struct tank *, int, int);
void drawTanks(struct tank *, int, struct monsterInfo *, struct targetInfo *, int, int,int);

void drawMaser(float, float, float, int, float, float, float, float, float, float, float, int, int, int);
void drawHeroWeapon(float, float, float, float, float, float *, float, float);

void drawBooms(struct boom *, int);
void drawBeam(float, float, int,  int, int, int);

void drawRoads(struct road *,  float,  float, int, int, int);
void drawProjectiles(struct projectile *, int, struct fireType*, int, int, int);

void andysphdraw(float loc[4], int);

#endif  // BATTALION_GRAPHICS_H_
