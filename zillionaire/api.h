#ifndef ZILLIONAIRE_API_H
#define ZILLIONAIRE_API_H

#include "common.h"

bool ChooseRole(int if_debug);
void PlayQuery(GAME *game_state);
void PlayHelp(GAME *game_state);
void Dump(GAME *game_state);
void HandlePreset(GAME *game_state);
int Flag2Id(char flag);
char Id2Flag(int id);
#endif //ZILLIONAIRE_API_H
