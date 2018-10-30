#ifndef HOUSE_DEAL
#define HOUSE_DEAL

#include "common.h"

void BuyHouse(int role_id, int house_position, GAME *game_state);
void UpdateHouse(int role_id, int house_position, GAME *game_state);
void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state);
void SellHouse(int house_position, GAME *game_state);


#endif //HOUSE_DEAL