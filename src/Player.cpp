#include "stdafx.h"

void CPlayer::remove_money(int value)
{

	money -= value;

}

void CPlayer::add_money(int value)
{
	money += value;
	total_money += value;
}

void CPlayer::add_money_turrets(int value) {

	money_buy_turrets += value;

}

void CPlayer::add_money_upgrades(int value) {

	money_turrets_upgrades += value;

}

void CPlayer::reset_money()
{
	total_money = 0;
	money = 0;
	money_buy_turrets = 0;
	money_turrets_upgrades = 0;

}


int CPlayer::return_total_money() {

	return total_money;

}



int CPlayer::return_money_turrets() {

	return money_buy_turrets;

}


int CPlayer::return_money_upgrades(){

	return money_turrets_upgrades;
}
