#pragma once

// Scena - Jest to podstawowy element organizuj�cy hierarchi� obiekt�w w grze.
// Z za�o�enia, w danym momencie powinna istnie� tylko jedna scena.
// W sytuacji gdy scen mo�e by� wi�cej, dobrze jest utworzy� klasy dziedzicz�ce po tej.


class manage_bullets;

struct config {
	int max_enemies;
	int max_health;

	int base_speed;
	int max_speed;
	float increase_speed_per_wave;

	int min_money;
	int max_money;
	int start_money;

	int enemy_base_health;
	int enemy_gain_health;

	int start_interval;
	int min_interval;
	int interval_loose;
	
	int map_id;
	float difficulty;

	vec3 cam_pos;
	vec3 cam_dir;

};


class CScene
{
public:
	int timestamp;
	bool move_wheel;
	int arrow_dir;
	float mouse_velocity;
	bool spawned_bullet;
	bool pause_pressed;
	int pause_interval;
	CSkydome * Skydome; // Skydome - niebo.
	CTerrain * Terrain; // Teren - czyli w naszym przyk�adzie trawiasty quad.
	CPlayer Player; // Stan gracza.
	CTexture * tree;
	GLuint tree_obj;
	Coursor *_Coursor;
	Nexus *_Nexus;
	Turrets *_Turrets;
	long int time_game;
	unsigned int status;


	board *_board;
	enemy_models *_enemy_models;
	manage_enemy *_manage_enemy;
	Fonts_management fonts_man;
	HUD *_HUD;
	manage_bullets *bullets;

	config *_config;

	bool speedup_keys[2];

	// Wszystkie obiekty na scenie, wektor na podstawie kt�rego b�dzie mo�na
	// po nich �atwo iterowa�, np. w celu ich narysowania.
	vector<CSceneObject *> * Objects;

	CScene(void); // Konstruktor
	~CScene(void); // Destruktor.
	void Initialize(void); // Inicjalizacja (wywo�ywana raz).
	void Update(void); // Aktualizacja �wiata.
	void CameraUpdate(void);
	void Render(void); // Rysowanie ca�ej sceny.
	void WheelZoom();
	void WheelBack();
	void WheelMove();
	void ArrowsControl(int);
	void SpeedUpGame(void);
	void SetConfig(void);
	void SetMouseVelocity(float);
	void Zoom_Fade_Camera();


	bool DrawCollisions; // Czy maj� by� rysowane kolizje (do debugowania, klawisz "K")?
	bool DrawNormals; // Czy maj� by� rysowane wektory normalne (do debugowania, klawisz "N")?
	vec3 LastCollisionPoint; // Pozycja ostatniej kolizji.
	bool MarkCollision; // Czy ju� zaistnia�a jakakolwiek kolizja warta narysowania?

};

