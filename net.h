#ifndef BATTALION_NET_H_
#define BATTALION_NET_H_

#include <netinet/in.h>
#include "battalion.h"

void turnBeamOnSinceLast(void);
void setUnconnected(void);
void setPortNumber(int);
void setHostAddr(char *);

void addNewNetworkTank(char *, struct tank *, int);
void updateNetworkTank(char *, struct tank *);
void tellAboutAllTanks(struct sockaddr_in *, int, struct tank *);

void updateClientMonster(char *);

int setUpClient(void);
int setUpNetwork(void);
void updateNetworkBuildings(char *, struct tree *);
void updateNetworkMonsters(char *, long);
int sendMessage(char *, struct sockaddr_in *, int);
void processClient(time_t, int, int, struct tree *, struct tank *,
    int sizeTank, struct monsterInfo, int, int *);
void tellAboutAllDeadBuildings(struct sockaddr_in *, int, int, int *);
void processNetwork(time_t, int, int, struct tree *, struct tank *,
    struct monsterInfo, int, int, int *, int *);
void addNetworkTarget(long, int, float, float, float, float, float, int);

#endif  // BATTALION_NET_H_
