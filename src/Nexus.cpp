#include "stdafx.h"
#include "Nexus.h"

Nexus::Nexus(int health)
{
	this->health = health;
	this->max_health = this->health;
}

void Nexus::Remove_health(int health)
{

	this->health -= health;

}

int Nexus::return_health()
{
	return health;
}

int Nexus::return_max_health()
{
	return max_health;
}

void Nexus::reset()
{
	health = max_health;
}
