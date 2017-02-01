#include "stdafx.h"
#include "Vec3.h"
#include "Fonts_management.h"

Fonts_management::Fonts_management()
{
}

void Fonts_management::load_fonts()
{
	T = 0;

	Turret_Circle = LoadObj("Data/Fonts/special/circle.obj");

	uppercase[0] = LoadObj("Data/Fonts/upper_case/A.obj");
	uppercase[1] = LoadObj("Data/Fonts/upper_case/B.obj");
	uppercase[2] = LoadObj("Data/Fonts/upper_case/C.obj");
	uppercase[3] = LoadObj("Data/Fonts/upper_case/D.obj");
	uppercase[4] = LoadObj("Data/Fonts/upper_case/E.obj");
	uppercase[5] = LoadObj("Data/Fonts/upper_case/F.obj");
	uppercase[6] = LoadObj("Data/Fonts/upper_case/G.obj");
	uppercase[7] = LoadObj("Data/Fonts/upper_case/H.obj");
	uppercase[8] = LoadObj("Data/Fonts/upper_case/I.obj");
	uppercase[9] = LoadObj("Data/Fonts/upper_case/J.obj");
	uppercase[10] = LoadObj("Data/Fonts/upper_case/K.obj");
	uppercase[11] = LoadObj("Data/Fonts/upper_case/L.obj");
	uppercase[12] = LoadObj("Data/Fonts/upper_case/M.obj");
	uppercase[13] = LoadObj("Data/Fonts/upper_case/N.obj");
	uppercase[14] = LoadObj("Data/Fonts/upper_case/O.obj");
	uppercase[15] = LoadObj("Data/Fonts/upper_case/P.obj");
	uppercase[16] = LoadObj("Data/Fonts/upper_case/Q.obj");
	uppercase[17] = LoadObj("Data/Fonts/upper_case/R.obj");
	uppercase[18] = LoadObj("Data/Fonts/upper_case/S.obj");
	uppercase[19] = LoadObj("Data/Fonts/upper_case/T.obj");
	uppercase[20] = LoadObj("Data/Fonts/upper_case/U.obj");
	uppercase[21] = LoadObj("Data/Fonts/upper_case/V.obj");
	uppercase[22] = LoadObj("Data/Fonts/upper_case/W.obj");
	uppercase[23] = LoadObj("Data/Fonts/upper_case/X.obj");
	uppercase[24] = LoadObj("Data/Fonts/upper_case/Y.obj");
	uppercase[25] = LoadObj("Data/Fonts/upper_case/Z.obj");


	lowercase[0] = LoadObj("Data/Fonts/lower_case/A.obj");
	lowercase[1] = LoadObj("Data/Fonts/lower_case/B.obj");
	lowercase[2] = LoadObj("Data/Fonts/lower_case/C.obj");
	lowercase[3] = LoadObj("Data/Fonts/lower_case/D.obj");
	lowercase[4] = LoadObj("Data/Fonts/lower_case/E.obj");
	lowercase[5] = LoadObj("Data/Fonts/lower_case/F.obj");
	lowercase[6] = LoadObj("Data/Fonts/lower_case/G.obj");
	lowercase[7] = LoadObj("Data/Fonts/lower_case/H.obj");
	lowercase[8] = LoadObj("Data/Fonts/lower_case/I.obj");
	lowercase[9] = LoadObj("Data/Fonts/lower_case/J.obj");
	lowercase[10] = LoadObj("Data/Fonts/lower_case/K.obj");
	lowercase[11] = LoadObj("Data/Fonts/lower_case/L.obj");
	lowercase[12] = LoadObj("Data/Fonts/lower_case/M.obj");
	lowercase[13] = LoadObj("Data/Fonts/lower_case/N.obj");
	lowercase[14] = LoadObj("Data/Fonts/lower_case/O.obj");
	lowercase[15] = LoadObj("Data/Fonts/lower_case/P.obj");
	lowercase[16] = LoadObj("Data/Fonts/lower_case/Q.obj");
	lowercase[17] = LoadObj("Data/Fonts/lower_case/R.obj");
	lowercase[18] = LoadObj("Data/Fonts/lower_case/S.obj");
	lowercase[19] = LoadObj("Data/Fonts/lower_case/T.obj");
	lowercase[20] = LoadObj("Data/Fonts/lower_case/U.obj");
	lowercase[21] = LoadObj("Data/Fonts/lower_case/V.obj");
	lowercase[22] = LoadObj("Data/Fonts/lower_case/W.obj");
	lowercase[23] = LoadObj("Data/Fonts/lower_case/X.obj");
	lowercase[24] = LoadObj("Data/Fonts/lower_case/Y.obj");
	lowercase[25] = LoadObj("Data/Fonts/lower_case/Z.obj");


	numbers[0] = LoadObj("Data/Fonts/numbers/0.obj");
	numbers[1] = LoadObj("Data/Fonts/numbers/1.obj");
	numbers[2] = LoadObj("Data/Fonts/numbers/2.obj");
	numbers[3] = LoadObj("Data/Fonts/numbers/3.obj");
	numbers[4] = LoadObj("Data/Fonts/numbers/4.obj");
	numbers[5] = LoadObj("Data/Fonts/numbers/5.obj");
	numbers[6] = LoadObj("Data/Fonts/numbers/6.obj");
	numbers[7] = LoadObj("Data/Fonts/numbers/7.obj");
	numbers[8] = LoadObj("Data/Fonts/numbers/8.obj");
	numbers[9] = LoadObj("Data/Fonts/numbers/9.obj");

	special_symbols[0] = LoadObj("Data/Fonts/special/33.obj");
	special_symbols[1] = LoadObj("Data/Fonts/special/34.obj");
	special_symbols[2] = LoadObj("Data/Fonts/special/35.obj");
	special_symbols[3] = LoadObj("Data/Fonts/special/36.obj");
	special_symbols[4] = LoadObj("Data/Fonts/special/37.obj");
	special_symbols[5] = LoadObj("Data/Fonts/special/38.obj");
	special_symbols[6] = LoadObj("Data/Fonts/special/39.obj");
	special_symbols[7] = LoadObj("Data/Fonts/special/40.obj");
	special_symbols[8] = LoadObj("Data/Fonts/special/41.obj");
	special_symbols[9] = LoadObj("Data/Fonts/special/42.obj");
	special_symbols[10] = LoadObj("Data/Fonts/special/43.obj");
	special_symbols[11] = LoadObj("Data/Fonts/special/44.obj");
	special_symbols[12] = LoadObj("Data/Fonts/special/45.obj");
	special_symbols[13] = LoadObj("Data/Fonts/special/46.obj");
	special_symbols[14] = LoadObj("Data/Fonts/special/47.obj");
	special_symbols[15] = LoadObj("Data/Fonts/special/58.obj");
	special_symbols[16] = LoadObj("Data/Fonts/special/59.obj");
	special_symbols[17] = LoadObj("Data/Fonts/special/60.obj");
	special_symbols[18] = LoadObj("Data/Fonts/special/61.obj");
	special_symbols[19] = LoadObj("Data/Fonts/special/62.obj");
	special_symbols[20] = LoadObj("Data/Fonts/special/63.obj");
	special_symbols[21] = LoadObj("Data/Fonts/special/64.obj");
	special_symbols[22] = LoadObj("Data/Fonts/special/91.obj");
	special_symbols[23] = LoadObj("Data/Fonts/special/92.obj");
	special_symbols[24] = LoadObj("Data/Fonts/special/93.obj");
	special_symbols[25] = LoadObj("Data/Fonts/special/94.obj");
	special_symbols[26] = LoadObj("Data/Fonts/special/95.obj");
	special_symbols[27] = LoadObj("Data/Fonts/special/96.obj");
	special_symbols[28] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[29] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[30] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[31] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[32] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[33] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[34] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[35] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[36] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[37] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[38] = LoadObj("Data/Fonts/special/dot.obj");
	special_symbols[39] = LoadObj("Data/Fonts/special/dot.obj");

}

void Fonts_management::Render_test()
{

	for (int i = 0; i < 26; i++)
	{
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(i*0.45, 0.5, 0);
		glCallList(uppercase[i]);

		glPopMatrix();
	}

	for (int i = 0; i < 26; i++)
	{
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(i*0.45, 0.5, 0.8);
		glCallList(lowercase[i]);

		glPopMatrix();
	}

}

void Fonts_management::drawtext(string text, vec3 start_pos, bool center, float scale)
{
	float offset=0;
	int i = 0;
	float new_offset = 0;

	if (center) {

		while (text[i] != '\0') {




			if (text[i] == 32)
			{

				new_offset += 0.004 * scale;
			}


			if (text[i] >= 'A' && text[i] <= 'Z') {

				new_offset = new_offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;
				new_offset = new_offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;
			}

			if (text[i] >= '0' && text[i] <= '9') {

				new_offset = new_offset + numbers_space_mult[text[i] - 48] / 2 * 0.45;
				new_offset = new_offset + numbers_space_mult[text[i] - 48] / 2 * 0.45;

			}


			if (text[i] >= 'a' && text[i] <= 'z') {

				new_offset = new_offset + lowercase_space_mult[text[i] - 97] / 2 * 0.45;
				new_offset = new_offset + lowercase_space_mult[text[i] - 97] / 2 * 0.45;

			}

			if (text[i] >= 33 && text[i] <= 47) {

				new_offset = new_offset + special_symbols_mult[text[i] - 33] / 2 * 0.45;
				new_offset = new_offset + special_symbols_mult[text[i] - 33] / 2 * 0.45;


			}

			if (text[i] >= 58 && text[i] <= 64) {

				new_offset = new_offset + special_symbols_mult[text[i] - 58 + 15] / 2 * 0.45;
				new_offset = new_offset + special_symbols_mult[text[i] - 58 + 15] / 2 * 0.45;

			}


			if (text[i] >= 91 && text[i] <= 96) {


				new_offset = new_offset + special_symbols_mult[text[i] - 91 + 22] / 2 * 0.45;
				new_offset = new_offset + special_symbols_mult[text[i] - 91 + 22] / 2 * 0.45;

			}


			i++;
		}

	}

	new_offset = new_offset / 2;

	i = 0;

	if (text == "CIRCLE") {
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(start_pos.x + offset*scale, start_pos.y, start_pos.z);
		glScalef(scale, scale, scale);
		glRotatef(-45, 0, 1, 0);
		glCallList(Turret_Circle);
		glPopMatrix();
		offset = offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;
		glDisable(GL_TEXTURE_2D);
		return;
	}


	while (text[i] != '\0') {

		if (text[i] == 32)
		{

			offset += 0.004 * scale;
		}


		if (text[i] >= 'A' && text[i] <= 'Z') {
			
				offset = offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;
				glPushMatrix();
				glTranslatef(start_pos.x+offset*scale - new_offset*scale, start_pos.y, start_pos.z);
				glScalef(scale, scale, scale);
				glCallList(uppercase[text[i] - 65]);
				glPopMatrix();
				offset = offset + uppercase_space_mult[text[i] - 65]/2 * 0.45 ;
				
		}

		if (text[i] >= '0' && text[i] <= '9') {

			offset = offset + numbers_space_mult[text[i] - 48] / 2 * 0.45;
			glPushMatrix();
			glTranslatef(start_pos.x + offset*scale - new_offset*scale, start_pos.y, start_pos.z);
			glScalef(scale, scale, scale);
			glCallList(numbers[text[i] - 48]);
			glPopMatrix();
			offset = offset + numbers_space_mult[text[i] - 48] / 2 * 0.45;

		}

	
		if (text[i] >= 'a' && text[i] <= 'z') {

				offset = offset + lowercase_space_mult[text[i] - 97] / 2 * 0.45;
				glPushMatrix();
				glTranslatef(start_pos.x + offset*scale - new_offset*scale, start_pos.y, start_pos.z);
				glScalef(scale, scale, scale);
				glCallList(lowercase[text[i] - 97]);
				glPopMatrix();
				offset = offset + lowercase_space_mult[text[i] - 97]/2 * 0.45;
				

		}


		if (text[i] >= 33 && text[i] <= 47) {

			offset = offset + special_symbols_mult[text[i] - 33] / 2 * 0.45;
			glPushMatrix();
			glTranslatef(start_pos.x + offset*scale - new_offset*scale, start_pos.y, start_pos.z);
			glScalef(scale, scale, scale);
			glCallList(special_symbols[text[i]-33]);
			glPopMatrix();
			offset = offset + special_symbols_mult[text[i] - 33] / 2 * 0.45;


		}

		if (text[i] >= 58 && text[i] <= 64) {

			offset = offset + special_symbols_mult[text[i] - 58 + 15] / 2 * 0.45;
			glPushMatrix();
				glTranslatef(start_pos.x + offset*scale - new_offset*scale, start_pos.y, start_pos.z);
				glScalef(scale, scale, scale);
				glCallList(special_symbols[text[i] - 58 + 15]);
			glPopMatrix();
			offset = offset + special_symbols_mult[text[i] - 58 + 15] / 2 * 0.45;


		}


		if (text[i] >= 91 && text[i] <= 96) {

			offset = offset + special_symbols_mult[text[i] - 91 + 22] / 2 * 0.45;
			glPushMatrix();
				glTranslatef(start_pos.x + offset*scale - new_offset*scale, start_pos.y, start_pos.z);
				glScalef(scale, scale, scale);
				glCallList(special_symbols[text[i] - 91 + 22]);
			glPopMatrix();


		}


		i++;
	}
}

void Fonts_management::drawtext_HUD(string text, vec3 start_pos, vec3 rotate, float scale)
{
	glDisable(GL_LIGHTING);
	float offset = 0;
	int i = 0;
	while (text[i] != '\0') {
		glPushMatrix();


		if (text[i] == 32)
		{

			offset += 0.2 * scale;
		}


		if (text[i] >= 'A' && text[i] <= 'Z') {

			offset = offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;
			glTranslatef(start_pos.x + offset*scale, start_pos.y, start_pos.z);
			
			glCallList(uppercase[text[i] - 65]);
			offset = offset + uppercase_space_mult[text[i] - 65] / 2 * 0.45;

		}

		if (text[i] >= 'a' && text[i] <= 'z') {

			offset = offset + lowercase_space_mult[text[i] - 97] / 2 * 0.45;
			glTranslatef(start_pos.x + offset*scale, start_pos.y, start_pos.z);
			glTranslatef(-0.2, 0, -0.2);
			glScalef(scale, scale, scale);
			//glRotatef(atan2(rotate.x, rotate.z) * 180 / 3.1415, 0, 1, 0);
			//glRotatef(acos(rotate.y) * 180 / 3.1415 - 90, 0, 0, 1);
			//glRotatef(65, 1, 0, 0);
			glCallList(lowercase[text[i] - 97]);
			
			offset = offset + lowercase_space_mult[text[i] - 97] / 2 * 0.45;


		}

		glPopMatrix();
		i++;
	}
	glEnable(GL_LIGHTING);
}
