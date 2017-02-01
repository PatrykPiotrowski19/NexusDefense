#pragma once

// Stan gracza.
class CPlayer {

public:
	int money;
	int total_money;
	int money_buy_turrets;
	int money_turrets_upgrades;

	vec3 pos;
	vec3 dir;
	vec3 cam; // Przesuniêcie punktu zaczepienia kamery wzglêdem pozycji gracza.


	vec3 pos_def;;
	vec3 dir_def;
	float speed;
	float velRX, velRY, velM, velS;
	CCollisionEllipsoid * collisionEllipsoid; // Elipsoida s³u¿¹ca do wykrywania kolizji.

	void remove_money(int value);
	void add_money(int value);

	void add_money_turrets(int value);
	void add_money_upgrades(int value);

	void reset_money();
	
	int return_total_money();
	int return_money_turrets();
	int return_money_upgrades();

	CPlayer() {
		pos.Set(0.0f, 0.0f, 0.0f);
		dir.Set(0.0f, 0.0f, -1.0f);
		cam.Set(0.0f, 0.25f, 0.0f);
		speed = 0.0f;
		velRX = 0.0f;
		velRY = 0.0f;
		velM = 0.0f;
		velS = 0.0f;
		collisionEllipsoid = new CCollisionEllipsoid(.15f, .3f, .15f);
		money_buy_turrets = 0;
		money_turrets_upgrades = 0;
		total_money = 0;
	}

};
