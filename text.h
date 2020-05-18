#ifndef BATTALION_TEXT_H_
#define BATTALION_TEXT_H_

void initFonts  (void);
void showText   (struct targetInfo *, float,  int,  long, int, int);
void showText2  (long, int, int, int, int, int, int, int, int, int);
void showText3  (int);
void showText4  (void);

void doOptions  (struct monsterInfo *, long, int, int, float, int);
void doSummary  (int,  int, long, int,
		int, int, int,
		int, int, int, int, int, int, int,int);

void showScores (int, struct score*, struct score*, struct score*,
                 struct score*, struct monsterInfo *, int, float, int);

#endif  // BATTALION_TEXT_H_
