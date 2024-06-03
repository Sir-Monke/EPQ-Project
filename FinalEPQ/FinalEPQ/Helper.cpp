#include "Helper.h"

Entity* Entity::GetClosestEnemy(bool team) {
	int playerCount = GetPlayerCount();
	int index = 1;
	float distance = 1000;

	for (int i = 1; i < playerCount; i++) { // start at index 1 which i think might be local player
		Entity* ent = GetEntById(i);
		if (ent->GetHealth() == 4294967255 || ent->GetHealth() < 0) {
			continue;
		}
		if (team && ent->GetTeam() == GetTeam()) {

		}
		if (GetPos().Distance(ent->GetPos()) < distance) {
			distance = GetPos().Distance(ent->GetPos());
			index = i;
		}
	}
	return GetEntById(index);
}