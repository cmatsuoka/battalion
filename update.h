#ifndef BATTALION_UPDATE_H_
#define BATTALION_UPDATE_H_

float buildingHeight(int,  int);
struct monsterInfo resetMonsterParameters(struct monsterInfo);

void updateGun(float, float, int, int, int,struct monsterInfo *);
void updateVap(float, float, int,struct monsterInfo *);
void updatetrees(struct tree *, int);
void updateBeam(struct monsterInfo *, struct targetInfo *, float, float, struct tank *, struct tree **, int, struct monsterInfo *);
void updateTanks(struct tank *, float, float, float, int, int, struct tank *, 
		float, int, int, struct monsterInfo *, struct targetInfo *);
void updateSlagTanks(struct tank *);
void updateBooms(struct boom *, struct tank *);
int tankHit(struct tank *, float, float, float);

#endif  // BATTALION_UPDATE_H_
