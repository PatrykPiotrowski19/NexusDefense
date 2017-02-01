#include "stdafx.h"

manage_bullets::manage_bullets()
{

	wsk = NULL;

}

void manage_bullets::get_pointer_manage_enemy(manage_enemy * _manage_enemy)
{
	this->_manage_enemy = _manage_enemy;
}

void manage_bullets::init_bullet()
{

	wsk = new bullet;
	wsk->next = NULL;
	wsk->prev = NULL;
	wsk->position = { 0,0,0 };
	wsk->damage = NULL;
	wsk->speed = NULL;
	wsk->target = NULL;
	wsk->bullet_type = NULL;
	wsk->distance = NULL;
	wsk->rotation = 0;

}

void manage_bullets::move_bullet(bullet * current)
{

	//Jezeli przeciwnik juz nie zyje albo nowy powsta³
	if (current->target->enabled == 0 || current->target->token != current->target_token)
	{
		remove_bullet(current);
		return;
	}

	vec3 dir;


	dir.x = current->target->pos.x - current->position.x;
	dir.z = current->target->pos.z - current->position.z;

	float sum = abs(dir.x) + abs(dir.z);

	float odleglosc = sqrt((dir.x*dir.x) + (dir.z * dir.z));

	current->rotation = atan2(dir.x, dir.z) * 180 / PI;

	current->position.x += dir.x / sum * 0.15;
	current->position.z += dir.z / sum * 0.15;

	if (odleglosc < 0.2) {

		deal_damage(current);
	}


}

void manage_bullets::set_bleeding_effect(enemy * target, int duration, float damage)
{

	target->bleeding = true;
	target->bleeding_duration = duration;
	target->bleeding_damage = damage;

}

void manage_bullets::set_slowing_effect(enemy * target, int duration, float slow)
{
}

void manage_bullets::deal_damage(bullet * _bullet)
{
	if (!_bullet->target->enabled) {
		remove_bullet(_bullet);
		return;
	}

	_bullet->target->health -= _bullet->damage;

	//Jezeli uderzyl pocisk pacynki shaco
	if (_bullet->bullet_type == 0) {
		_bullet->target->slowed = true;


		if(_bullet->target->slowing_duration <= 1000)
		_bullet->target->slowing_duration = 1000;

		if(_bullet->target->slow_value <= 15)
		_bullet->target->slow_value = 15;

	}

	//Jezeli uderzyl pocisk kwiatka Zyry
	if (_bullet->bullet_type == 3) {
		_bullet->target->slowed = true;
		_bullet->target->slowing_duration = 1500;
		_bullet->target->slow_value = 35;
	}

	//Jezeli URF uderzy w cel
	if (_bullet->bullet_type == 5) {
		_bullet->target->bleeding = true;
		_bullet->target->bleeding_damage = (_bullet->target->max_health + 1) * 0.07 / 120;
		_bullet->target->bleeding_duration = 2000;
	}

	//Pociski Heimera
	if (_bullet->bullet_type == 2) {

		_manage_enemy->deal_field_damage(1.6, _bullet->damage*0.3, _bullet->position, _bullet->target);

	}

	//Ataki Zolnierza Azira
	if (_bullet->bullet_type == 4) {

		_manage_enemy->deal_field_damage(0.8, _bullet->damage, _bullet->position, _bullet->target);

	}

	remove_bullet(_bullet);

}

void manage_bullets::LoadModels()
{
	bullet_cylinder = LoadObj("Data\\Bullets\\cylinder.obj");
	spoon = LoadObj("Data\\Bullets\\spoon.obj");
	spoon_texture = new CTexture("Data\\Bullets\\spoon_texture.bmp");

	ball = LoadObj("Data\\Bullets\\ball.obj");
	ball_texture = new CTexture("Data\\Bullets\\ball_texture.bmp");

	plant = LoadObj("Data\\Bullets\\plant.obj");
	plant_texture = new CTexture("Data\\Bullets\\plant_texture.bmp");

}

void manage_bullets::add_bullet(vec3 position, float damage, float speed, int bullet_type, enemy * target)
{
		if (damage != NULL) {

			if (wsk == NULL)
				init_bullet();
		}

		int error = 0;

		struct bullet *tmp = wsk;
		struct bullet *new_bullet = new bullet;
		struct bullet *new_address = wsk;

		struct bullet *handler = NULL;

		new_bullet->bullet_type = bullet_type;
		new_bullet->damage = damage;
		new_bullet->speed = speed;
		new_bullet->position = position;
		new_bullet->position.y = 1.0;
		new_bullet->target = target;
		new_bullet->distance = 0;
		new_bullet->rotation = 0;
		new_bullet->target_token = target->token;


		if (!error) {

			//Jezeli przedtem nie bylo zadnych pociskow
			if (tmp->damage == NULL) {

				new_address = new_bullet;
				//delete wsk;
				new_bullet->next = NULL;
				new_bullet->prev = NULL;
			}
			//Jezeli istnieja pociski
			else
			{
				while (tmp->next != NULL) {
					tmp = tmp->next;
				}

				tmp->next = new_bullet;
				handler = tmp;
				new_bullet->prev = handler;
				new_bullet->next = NULL;
			}
		}
		else
			//Jezeli blad w tworzeniu pocisku
		{
			cout << "Blad w tworzeniu pocisku\n";
			//delete new_bullet;

		}
		wsk = new_address;
}

void manage_bullets::remove_bullet(bullet *remove)
{

	struct bullet *actual = remove;
	struct bullet *poprzednik = remove->prev;
	struct bullet *nastepnik = remove->next;


	if (wsk != NULL) {

		//Jezeli jest jedyny
		if (poprzednik == NULL && nastepnik == NULL) {



			//if(remove != NULL)
				//delete remove;
			wsk = NULL;
			return;
		}


		//Jezeli nie ma poprzednika - jest pierwszym wezlem
		if (poprzednik == NULL)
		{
			wsk = remove->next;
			remove->next->prev = NULL;

			//if (remove != NULL)
				//delete remove;
			return;

		}

		//Jezeli jest ostatnim wezlem
		if (nastepnik == NULL) {

			remove->prev->next = NULL;

			//if (remove != NULL)
				//delete remove;

			return;
		}

		poprzednik->next = remove->next;
		nastepnik->prev = remove->prev;

		//if (remove != NULL)
			//delete remove;

		return;
	
	}




}

void manage_bullets::Update()
{

	struct bullet *tmp = wsk;
	struct bullet *tmp2;

	if (!tmp)
		return;


	while (tmp != NULL) {
		tmp2 = tmp->next;

		move_bullet(tmp);

		tmp = tmp2;

	}


}

void manage_bullets::Render() {
	struct bullet *tmp = wsk;

	while (tmp != NULL) {

		if (tmp->bullet_type == 5) {
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, spoon_texture->GetId());
			glTranslatef(tmp->position.x, tmp->position.y, tmp->position.z);
			glScalef(0.25, 0.25, 0.25);
			glRotatef(-0.7 * glutGet(GLUT_ELAPSED_TIME) * !pause, 1, 0, 1);
			glRotatef(tmp->rotation, 0, 1, 0);
			glCallList(spoon);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			if (tmp->bullet_type == 2 || tmp->bullet_type == 1) {
				glEnable(GL_TEXTURE_2D);
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, ball_texture->GetId());
				glTranslatef(tmp->position.x, tmp->position.y, tmp->position.z);
				if (tmp->bullet_type == 2)
					glScalef(0.15, 0.15, 0.15);
				if (tmp->bullet_type == 1)
					glScalef(0.07, 0.07, 0.07);
				glRotatef(-0.8 * glutGet(GLUT_ELAPSED_TIME) * !pause, 1, 0, 1);
				glRotatef(tmp->rotation, 0, 1, 0);
				glCallList(ball);
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);

			}
			else {
				if (tmp->bullet_type == 3) {

					glEnable(GL_TEXTURE_2D);
					glPushMatrix();
					glBindTexture(GL_TEXTURE_2D, plant_texture->GetId());
					glTranslatef(tmp->position.x, tmp->position.y, tmp->position.z);
					glScalef(0.5, 0.5, 0.5);
					glRotatef(-0.7 * glutGet(GLUT_ELAPSED_TIME) * !pause, 1, 0, 1);
					glRotatef(tmp->rotation, 0, 1, 0);
					glCallList(plant);
					glPopMatrix();
					glDisable(GL_TEXTURE_2D);
				}
				else {


					glPushMatrix();

					switch (tmp->bullet_type) {
					case 0:	glColor4f(0.9, 0.3, 0.2, 0.6); break;
					case 1: glColor4f(0.9, 0.9, 0, 0.6); break;
					case 2: glColor4f(0.75, 0.3, 0, 0.6); break;
					case 3: glColor4f(0, 0.9, 0, 0.6); break;
					case 4: glColor4f(0, 0, 0, 0); break;
					default:	glColor4f(0.9, 0.3, 0.2, 0.6);
					}
					glTranslatef(tmp->position.x, tmp->position.y, tmp->position.z);

					glRotatef(tmp->rotation, 0, 1, 0);
					glCallList(bullet_cylinder);
					glPopMatrix();

					if (tmp->next == NULL)
						return;
				}
			}
		}
		tmp = tmp->next;


	}

}