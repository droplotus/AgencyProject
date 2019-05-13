#pragma once

#include "Agency.h"

void menuClient(Agency& agency);
void menuPack(Agency& agency);
void menuInformation(Agency& agency);
void menuHelp(Agency& agency);
unsigned mainMenu(Agency& agency);
void showTps(vector<Packet> tps_arr);