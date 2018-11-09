#ifndef HOUSE_DEAL
#define HOUSE_DEAL

#include "common.h"

void BuyHouse(int role_id, int house_position, GAME *game_state);
void UpdateHouse(int house_position, GAME *game_state);
void HouseUpdateOneLeve(int house_position, char *primary_level, char *update_level, GAME *game_state);
bool SellHouse(GAME *game_state, int house_pos);
PLAYER * Map_Player(int house_id, GAME *game_state);
void PayFees(GAME *game_state);
void DeleteCurrentPlayer(GAME *game_state);
bool AbleBuyHouse(int house_id, GAME *game);
void PlayerInMineral(int mineral_id, GAME *game);
void PlayerInGiftHouse(GAME *game);
void PlayerInToolHouse(GAME *game);
bool BlockedOrBombed(int step, GAME *game_state);
void PlayerInPrison(GAME *game);
void PlayerInMagicHouse(GAME *game);

#endif //HOUSE_DEAL