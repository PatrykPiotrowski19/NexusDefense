#pragma once


class Nexus {

	int health;
	int max_health;
	

public:
	Nexus(int health);
	void Remove_health(int health);
	int return_health();
	int return_max_health();
	void reset();


};