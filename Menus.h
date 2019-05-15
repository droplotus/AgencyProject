#pragma once

#include "Agency.h"

void showAllTravelPacks(Agency agency);
void showTravelPacks(Agency & agency);
void menuClient(Agency& agency);
void menuPack(Agency& agency);
void menuEstatistics(Agency& agency);
void menuInformation(Agency& agency);
void menuHelp(Agency& agency);
unsigned mainMenu(Agency& agency);
void showTps(vector<Packet> tps_arr);