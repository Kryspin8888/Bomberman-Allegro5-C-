#include "allegro5\allegro.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include "allegro5\keyboard.h"
#include "allegro5\mouse.h"
#include "allegro5\timer.h"
#include "allegro5\allegro_primitives.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <cstdlib>
#include <iostream>
//#include <windows.h>

enum KEYS { UP, DOWN, LEFT, RIGHT, W, S, A, D };
void tworz_mape(int ktoraplansza, bool mury[20][15], int wspmur_x[20][15], int wspmur_y[20][15]);
int main()
{
	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_TIMER *timer = NULL;

	const int FPS = 60;

	bool keys[8] = { false, false, false, false, false, false, false, false };

	//std::cout << "Wybierz plansze klawiszami 1, 2, 3, 4" << std::endl;

	if (!al_init())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO INIT FAIL", NULL, NULL);
	if (!al_init_native_dialog_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO NATIVE DIALOG INIT FAIL", NULL, NULL);
	if (!al_init_image_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO IMAGE INIT FAIL", NULL, NULL);
	if (!al_install_keyboard())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO KEYBOARD INIT FAIL", NULL, NULL);
	if (!al_init_font_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO FONT INIT FAIL", NULL, NULL);
	if (!al_init_ttf_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO TTF INIT FAIL", NULL, NULL);
	if (!al_init_primitives_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO PRIMITIVES INIT FAIL", NULL, NULL);
	if (!al_install_mouse())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO MOUSE INIT FAIL", NULL, NULL);
	if (!al_install_audio())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO AUDIO INIT FAIL", NULL, NULL);
	if (!al_init_acodec_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO AUDIO INIT FAIL", NULL, NULL);


	okno = al_create_display(800, 480);
	timer = al_create_timer(1.0 / FPS);

	ALLEGRO_FONT * font14 = al_load_ttf_font("arialbd.ttf", 14, 0);
	if (!font14)
		return 1;
	ALLEGRO_FONT * font12 = al_load_ttf_font("arialbd.ttf", 12, 0);
	if (!font12)
		return 1;
	ALLEGRO_FONT * font54 = al_load_ttf_font("arialbd.ttf", 54, 0);
	if (!font54)
		return 1;
	ALLEGRO_FONT * font20 = al_load_ttf_font("arialbd.ttf", 20, 0);
	if (!font20)
		return 1;

	ALLEGRO_BITMAP *gracz;
	gracz = al_load_bitmap("grafika\\gracze\\mojemario2.pcx");
	if (!gracz)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mojemario2!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *gracz0;
	gracz0 = al_load_bitmap("grafika\\gracze\\mojemario.pcx");
	if (!gracz0)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mojemario!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *gracz1;
	gracz1 = al_load_bitmap("grafika\\gracze\\mojemario1.pcx");
	if (!gracz1)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mojemario1!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *gracz2;
	gracz2 = al_load_bitmap("grafika\\gracze\\mojemario3.pcx");
	if (!gracz2)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mojemario3!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *przeciwnik;
	przeciwnik = al_load_bitmap("grafika\\gracze\\gracz1.pcx");
	ALLEGRO_BITMAP *npc_d = al_create_sub_bitmap(przeciwnik, 0, 64, 32, 32);
	if (!przeciwnik)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy gracz1!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *npc_u = al_create_sub_bitmap(przeciwnik, 0, 0, 32, 32);

	ALLEGRO_BITMAP *npc_l = al_create_sub_bitmap(przeciwnik, 0, 96, 32, 32);

	ALLEGRO_BITMAP *npc_r = al_create_sub_bitmap(przeciwnik, 0, 32, 32, 32);

	ALLEGRO_BITMAP *przec1;
	przec1 = al_load_bitmap("grafika\\gracze\\gracz3.pcx");
	ALLEGRO_BITMAP *npc1_d = al_create_sub_bitmap(przec1, 0, 64, 32, 32);

	ALLEGRO_BITMAP *npc1_u = al_create_sub_bitmap(przec1, 0, 0, 32, 32);

	ALLEGRO_BITMAP *npc1_l = al_create_sub_bitmap(przec1, 0, 96, 32, 32);

	ALLEGRO_BITMAP *npc1_r = al_create_sub_bitmap(przec1, 0, 32, 32, 32);

	ALLEGRO_BITMAP *przec2;
	przec2 = al_load_bitmap("grafika\\gracze\\gracz4.pcx");
	ALLEGRO_BITMAP *npc2_d = al_create_sub_bitmap(przec2, 0, 64, 32, 32);

	ALLEGRO_BITMAP *npc2_u = al_create_sub_bitmap(przec2, 0, 0, 32, 32);

	ALLEGRO_BITMAP *npc2_l = al_create_sub_bitmap(przec2, 0, 96, 32, 32);

	ALLEGRO_BITMAP *npc2_r = al_create_sub_bitmap(przec2, 0, 32, 32, 32);

	ALLEGRO_BITMAP *przec3;
	przec3 = al_load_bitmap("grafika\\gracze\\gracz0.pcx");
	ALLEGRO_BITMAP *npc3_d = al_create_sub_bitmap(przec3, 0, 64, 32, 32);

	ALLEGRO_BITMAP *npc3_u = al_create_sub_bitmap(przec3, 0, 0, 32, 32);

	ALLEGRO_BITMAP *npc3_l = al_create_sub_bitmap(przec3, 0, 96, 32, 32);

	ALLEGRO_BITMAP *npc3_r = al_create_sub_bitmap(przec3, 0, 32, 32, 32);

	ALLEGRO_BITMAP *przec4;
	przec4 = al_load_bitmap("grafika\\gracze\\gracz.pcx");
	ALLEGRO_BITMAP *npc4_d = al_create_sub_bitmap(przec4, 0, 64, 32, 32);

	ALLEGRO_BITMAP *npc4_u = al_create_sub_bitmap(przec4, 0, 0, 32, 32);

	ALLEGRO_BITMAP *npc4_l = al_create_sub_bitmap(przec4, 0, 96, 32, 32);

	ALLEGRO_BITMAP *npc4_r = al_create_sub_bitmap(przec4, 0, 32, 32, 32);

	ALLEGRO_BITMAP *mur;
	mur = al_load_bitmap("grafika\\bloczki\\mur.pcx");
	if (!mur)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mur!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *bomb;
	bomb = al_load_bitmap("grafika\\bomby\\bomba2.pcx");
	if (!bomb)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy bomba2!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *logo;
	logo = al_load_bitmap("grafika\\inne\\logo.pcx");
	if (!logo)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy logo!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *kursor;
	kursor = al_load_bitmap("grafika\\inne\\mysz.pcx");
	if (!kursor)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy mysz!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	ALLEGRO_BITMAP *instrukcja;
	instrukcja = al_load_bitmap("grafika\\inne\\instrukcja.png");
	if (!instrukcja)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy instrukcja!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}

	al_reserve_samples(10);
	ALLEGRO_SAMPLE *muzyka1;
	ALLEGRO_SAMPLE_INSTANCE *muzyka;
	muzyka1 = al_load_sample("dzwieki\\soundtrack.wav");
	muzyka = al_create_sample_instance(muzyka1);
	if (!muzyka1)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac dzwieku soundtrack!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	al_set_sample_instance_playmode(muzyka, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(muzyka, al_get_default_mixer());
	ALLEGRO_SAMPLE *muzyka2;
	ALLEGRO_SAMPLE_INSTANCE *dzwiekwybuchu;
	muzyka2 = al_load_sample("dzwieki\\boom.wav");
	dzwiekwybuchu = al_create_sample_instance(muzyka2);
	if (!muzyka2)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac dzwieku boom!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	al_attach_sample_instance_to_mixer(dzwiekwybuchu, al_get_default_mixer());
	ALLEGRO_SAMPLE *muzyka3;
	ALLEGRO_SAMPLE_INSTANCE *dzwiekzwyciestwa;
	muzyka3 = al_load_sample("dzwieki\\win.wav");
	dzwiekzwyciestwa = al_create_sample_instance(muzyka3);
	if (!muzyka3)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac dzwieku win!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	al_attach_sample_instance_to_mixer(dzwiekzwyciestwa, al_get_default_mixer());
	ALLEGRO_SAMPLE *muzyka4;
	ALLEGRO_SAMPLE_INSTANCE *gameover;
	muzyka4 = al_load_sample("dzwieki\\gameover.wav");
	gameover = al_create_sample_instance(muzyka4);
	if (!muzyka4)
	{
		al_show_native_message_box(okno, "Blad", "Cos nie tak",
			"Nie moge wczytac dzwieku gameover!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}
	al_attach_sample_instance_to_mixer(gameover, al_get_default_mixer());



	al_convert_mask_to_alpha(gracz, al_map_rgb(0, 255, 255));
	al_convert_mask_to_alpha(npc_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc_l, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc_r, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc_u, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc1_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc1_l, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc1_r, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc1_u, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc2_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc2_l, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc2_r, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc2_u, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc3_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc3_l, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc3_r, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc3_u, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc4_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc4_l, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc4_r, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(npc4_u, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(gracz1, al_map_rgb(0, 255, 255));
	al_convert_mask_to_alpha(gracz2, al_map_rgb(0, 255, 255));
	al_convert_mask_to_alpha(gracz0, al_map_rgb(0, 255, 255));
	al_convert_mask_to_alpha(npc1_d, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bomb, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(logo, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(kursor, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(instrukcja, al_map_rgb(255, 255, 255));


	bool mury[20][15];
	int gracz_x = 576, gracz_y = 416;
	int npc_x = 192, npc_y = 32;
	int npc1_x = 576, npc1_y = 32;
	int npc2_x = 32, npc2_y = 192;
	int npc3_x = 192, npc3_y = 416;
	int npc4_x = 320, npc4_y = 288;
	int wspmur_x[20][15], wspmur_y[20][15];
	int kierunek, kieruneknpc, kierunek1, kierunek2, kierunek3,kierunek4;
	int bomb_x, bomb_y;
	int bomb1_x, bomb1_y;
	float czas1, czas2;
	float czas11, czas22;
	float czaswybuch_start, czaswybuch_stop;
	float czaswybuch0_start=0, czaswybuch0_stop=5;
	float czaszmianymapy_start = 0, czaszmianymapy_stop = 0;
	int ktoraplansza=1;
	int wyswietlbombe1 = 1;
	int ktorabomba = 1;
	float czaslos1_start = 0, czaslos_stop = 3, czaslos2_start = 0, czaslos3_start = 0, czaslos4_start = 0, czaslosnpc_start = 0;
	int pokonany = 0;
	float czasgry = 0;
	int iloscbomb=0;
	int mysz_x, mysz_y;
	int opcjamysz=-5;

	tworz_mape(4, mury, wspmur_x, wspmur_y);

	for (int k = 0; k < 20; k++)
		for (int l = 0; l < 15; l++)
		{
			wspmur_x[k][l] = 0;
			wspmur_y[k][l] = 0;
		}


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	bool zamknij = false;
	bool kolizja = false;
	bool ruch = true, ruchnpc = true, ruch1=true, ruch2 = true, ruch3 = true, ruch4 = true;
	bool wyswietlgracza = true, wyswietlnpc = true, wyswietlnpc1 = true, wyswietlnpc2 = true, wyswietlnpc3 = true, wyswietlnpc4 = true;
	bool bomba = false, bomba1=false;
	bool wspbomb, wspbomb1;
	bool wybuch1, wybuch=false;
	bool zamknij1=false;
	bool doubleplayer = false;
	bool pok1 = false, pok2 = false, pok3 = false, pok4 = false, pok5 = false;
	bool czaszmianymapy=true;
	bool dzwieki = true;
	bool zamknijinstrukcje = false;

	al_start_timer(timer);
	
	srand(time(NULL));
	kieruneknpc = rand() % 4;
	kierunek1 = rand() % 4;
	kierunek2 = rand() % 4;
	kierunek3 = rand() % 4;
	kierunek4 = rand() % 4;
	
	//HWND hwnd = FindWindowA("ConsoleWindowClass", NULL);   //ukrywanie okna konsoli w c/c++
	//ShowWindow(hwnd, SW_HIDE);

	while (!zamknij1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_ESCAPE:
				if (zamknijinstrukcje) zamknijinstrukcje = true;
				else zamknij1 = true;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mysz_x = ev.mouse.x;
			mysz_y = ev.mouse.y;

		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			
			if (ev.mouse.button & 1) {
				if (mysz_x > 330 && mysz_x < 470 && mysz_y> 100 && mysz_y < 130) 
				{
					zamknij = false;
					gracz_x = 576; gracz_y = 416;
					npc_x = 192; npc_y = 32;
					npc1_x = 576; npc1_y = 32;
					npc2_x = 32; npc2_y = 192;
					npc3_x = 192; npc3_y = 416;
					npc4_x = 320; npc4_y = 288;
					wspmur_x[20][15] = { 0 }; wspmur_y[20][15] = { 0 };
					czaswybuch0_start = 0; czaswybuch0_stop = 5;
					czaszmianymapy_start = 0; czaszmianymapy_stop = 0;
					 ktoraplansza = 1;
					 wyswietlbombe1 = 1;
					 ktorabomba = 1;
					 czaslos1_start = 0; czaslos_stop = 3; czaslos2_start = 0; czaslos3_start = 0; czaslos4_start = 0; czaslosnpc_start = 0;
					 pokonany = 0;
					czasgry = 0;
					 iloscbomb = 0;
					 ruch = true; ruchnpc = true; ruch1 = true; ruch2 = true; ruch3 = true; ruch4 = true;
					 wyswietlgracza = true; wyswietlnpc = true; wyswietlnpc1 = true; wyswietlnpc2 = true; wyswietlnpc3 = true; wyswietlnpc4 = true;
					 bomba = false; bomba1 = false;
					zamknij1 = false;
					pok1 = false; pok2 = false; pok3 = false; pok4 = false; pok5 = false;
					czaszmianymapy = true;
					dzwieki = true;
					opcjamysz = 1;

				}
				else if (mysz_x > 330 && mysz_x < 470 && mysz_y> 150 && mysz_y < 180)
				{
					if (dzwieki)
					{
						dzwieki = false;
						al_stop_sample_instance(muzyka);
					}
					else dzwieki = true;
				}
				else if (mysz_x > 330 && mysz_x < 470 && mysz_y> 200 && mysz_y < 230)
				{
					
					if (doubleplayer)
					{
						doubleplayer = false;
						
					}
					else doubleplayer = true;
			

				}
				else if (mysz_x > 330 && mysz_x < 470 && mysz_y> 250 && mysz_y < 280)
				{
					zamknij1 = true;
				}
				

			}


		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_ESCAPE:
				if (zamknijinstrukcje) zamknijinstrukcje = true;
				else zamknij1 = true;
				break;
			}
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 120, 0));
		al_draw_filled_rectangle(330, 100, 470, 130, al_map_rgb(255, 191, 0));
		al_draw_text(font20, al_map_rgb(0, 0, 0), 370, 105, 0, "GRAJ");
		al_draw_filled_rectangle(330, 150, 470, 180, al_map_rgb(255, 191, 0));
		al_draw_text(font14, al_map_rgb(0, 0, 0), 350, 157, 0, "MUZYKA:");
		if(dzwieki) al_draw_text(font14, al_map_rgb(0, 150, 0), 425, 157, 0, "TAK");
		else al_draw_text(font14, al_map_rgb(255, 0, 0), 425, 157, 0, "NIE");
		al_draw_filled_rectangle(330, 200, 470, 230, al_map_rgb(255, 191, 0));
		if (!doubleplayer)
			al_draw_text(font14, al_map_rgb(0, 0, 0), 333, 207, 0, "GRA DLA 1 GRACZA");
		if(doubleplayer)
		al_draw_text(font14, al_map_rgb(0, 0, 0), 333, 207, 0, "GRA DLA 2 GRACZY");
		al_draw_filled_rectangle(330, 250, 470, 280, al_map_rgb(255, 191, 0));
		al_draw_text(font14, al_map_rgb(0, 0, 0), 370, 257, 0, "ZAMKNIJ");
		al_draw_bitmap(logo, 240, 310, 0);
		al_draw_bitmap(gracz, 500, 180, 0);
		al_draw_bitmap(bomb, 535, 180, 0);
		al_draw_bitmap(npc1_d, 570, 180, 0);
		al_draw_bitmap(npc2_d, 605, 180, 0);
		al_draw_bitmap(npc3_d, 640, 180, 0);
		al_draw_bitmap(npc4_d, 675, 180, 0);
		al_draw_bitmap(npc_d, 710, 180, 0);
		al_draw_bitmap(mur, 760, 180, 0);
		al_draw_bitmap(mur, 610, 80, 0);
		al_draw_bitmap(mur, 675, 400, 0);
		al_draw_bitmap(mur, 540, 300, 0);
		al_draw_bitmap(mur, 655, 250, 0);
		al_draw_text(font54, al_map_rgb(240, 0, 0), 320, 25, 0, "MENU");
		al_draw_bitmap(instrukcja, 10, 45,0);
		al_hide_mouse_cursor(okno);
		al_draw_bitmap(kursor, mysz_x, mysz_y, 0);
		if(dzwieki)
		al_play_sample_instance(muzyka);


	switch(opcjamysz)
	{ 
	case 1:
	while (!zamknij)
	{
		if (wyswietlnpc || wyswietlnpc1 ||wyswietlnpc2 || wyswietlnpc3 || wyswietlnpc4 ||ktoraplansza != 4)
		czasgry = al_get_time();
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

	
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				zamknij = true;
				break;
			/*case ALLEGRO_KEY_1:
				ktoraplansza = 1;
				break;
			case ALLEGRO_KEY_2:
				ktoraplansza = 2;
				break;
			case ALLEGRO_KEY_3:
				ktoraplansza = 3;
				break;
			case ALLEGRO_KEY_4:
				ktoraplansza = 4;
				break;*/
			case ALLEGRO_KEY_SPACE:
				if (ktorabomba % 2)
				{
					bomba = true;
					wspbomb = true;
					czas1 = al_get_time();
					ktorabomba++;
				}
				else
				{
					bomba1 = true;
					wspbomb1 = true;
					czas11 = al_get_time();
					ktorabomba++;
				}
				iloscbomb++;
				break;
			case ALLEGRO_KEY_Z:
				bomba = false;
				wspbomb = false;
				bomba1 = false;
				wspbomb1 = false;
				iloscbomb--;
				break;
				
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
			}
		}

		
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (ruch)
			{
				if (keys[UP])
				{
					gracz_y -= keys[UP] * 2;
					if (gracz_x % 32 == 0 || gracz_y % 32 == 0)
					kierunek = 0;
				}
				else  if (!keys[UP] && (gracz_y % 32 != 0) && kierunek == 0)
				{
					gracz_y -= 2;

				}
				
				if (keys[DOWN])
				{
					gracz_y += keys[DOWN] * 2;
					if (gracz_x % 32 == 0 || gracz_y % 32 == 0)
					kierunek = 1;
				}
				else if (!keys[DOWN] && (gracz_y % 32 != 0) && kierunek == 1)
				{
					gracz_y += 2;

				}
				
				if (keys[LEFT])
				{
					gracz_x -= keys[LEFT] * 2;
					if (gracz_x % 32 == 0 || gracz_y % 32 == 0)
					kierunek = 2;
				}
				else if (!keys[LEFT] && (gracz_x % 32 != 0) && kierunek == 2)
				{
					gracz_x -= 2;

				}
				
				if (keys[RIGHT])
				{
					gracz_x += keys[RIGHT] * 2;
					if (gracz_x % 32 == 0 || gracz_y % 32 == 0)
					kierunek = 3;
				}
				else if (!keys[RIGHT] && (gracz_x % 32 != 0) && kierunek == 3)
				{
					gracz_x += 2;

				}
			}
			
			if(doubleplayer)
			{
			if (ruchnpc)
			{
				if (keys[W])
				{
					npc_y -= keys[W] * 2;
					if (npc_x % 32 == 0 || npc_y % 32 == 0)
					kieruneknpc = 0;
				}
				else  if (!keys[W] && (npc_y % 32 != 0) && kieruneknpc == 0)
				{
					npc_y -= 2;

				}
				if (keys[S])
				{
					npc_y += keys[S] * 2;
					if (npc_x % 32 == 0 || npc_y % 32 == 0)
					kieruneknpc = 1;
				}
				else  if (!keys[S] && (npc_y % 32 != 0) && kieruneknpc == 1)
				{
					npc_y += 2;

				}
				if (keys[A])
				{
					npc_x -= keys[A] * 2;
					if (npc_x % 32 == 0 || npc_y % 32 == 0)
					kieruneknpc = 2;
				}
				else  if (!keys[A] && (npc_x % 32 != 0) && kieruneknpc == 2)
				{
					npc_x -= 2;

				}
				if (keys[D])
				{
					npc_x += keys[D] * 2;
					if (npc_x % 32 == 0 || npc_y % 32 == 0)
					kieruneknpc = 3;
				}
				else  if (!keys[D] && (npc_x % 32 != 0) && kieruneknpc == 3)
				{
					npc_x += 2;

				}

			}}
	
			if (ruch1)
			{
				if (kierunek1 == 2)
					npc1_x -= 2;
				if (kierunek1 == 3)
					npc1_x += 2;
				if (kierunek1 == 0)
					npc1_y -= 2;
				if (kierunek1 == 1)
					npc1_y += 2;

				if (czaslos_stop - czaslos1_start > 2)
				{
					for (int k = 0; k < 20; k++)
						for (int l = 0; l < 15; l++)
						{
							if (kierunek1 == 0 || kierunek1 == 1)                                     // losowe wybieranie sciezki w momencie znalezienia luki w murach
							{
								if (npc1_y % 32 == 0 && npc1_x % 32 == 0 &&
									(!mury[(npc1_x - 32) / 32][npc1_y / 32] || !mury[(npc1_x + 32) / 32][npc1_y / 32]))
								{
									kierunek1 = rand() % 4;
									czaslos1_start = al_get_time();
								}
							}

							else if (kierunek1 == 2 || kierunek1 == 3)
							{
								if (npc1_y % 32 == 0 && npc1_x % 32 == 0 &&
									(!mury[(npc1_x) / 32][(npc1_y - 32) / 32] || !mury[(npc1_x) / 32][(npc1_y + 32) / 32]))
								{
									kierunek1 = rand() % 4;
									czaslos1_start = al_get_time();
								}
							}


						}
				}
			}
			

			if (ruch2)
			{
				if (kierunek2 == 2)
					npc2_x -= 2;
				if (kierunek2 == 3)
					npc2_x += 2;
				if (kierunek2 == 0)
					npc2_y -= 2;
				if (kierunek2 == 1)
					npc2_y += 2;

				if (czaslos_stop - czaslos2_start > 2)
				{
					for (int k = 0; k < 20; k++)
						for (int l = 0; l < 15; l++)
						{
							if (kierunek2 == 0 || kierunek2 == 1)                                     // losowe wybieranie sciezki w momencie znalezienia luki w murach
							{
								if (npc2_y % 32 == 0 && npc2_x % 32 == 0 &&
									(!mury[(npc2_x - 32) / 32][npc2_y / 32] || !mury[(npc2_x + 32) / 32][npc2_y / 32]))
								{
									kierunek2 = rand() % 4;
									czaslos2_start = al_get_time();
								}
							}

							else if (kierunek2 == 2 || kierunek2 == 3)
							{
								if (npc2_y % 32 == 0 && npc2_x % 32 == 0 &&
									(!mury[(npc2_x) / 32][(npc2_y - 32) / 32] || !mury[(npc2_x) / 32][(npc2_y + 32) / 32]))
								{
									kierunek2 = rand() % 4;
									czaslos2_start = al_get_time();
								}
							}


						}
				}

			}

			if (ruch3)
			{
				if (kierunek3 == 2)
					npc3_x -= 2;
				if (kierunek3 == 3)
					npc3_x += 2;
				if (kierunek3 == 0)
					npc3_y -= 2;
				if (kierunek3 == 1)
					npc3_y += 2;

				if (czaslos_stop - czaslos3_start > 2)
				{
					for (int k = 0; k < 20; k++)
						for (int l = 0; l < 15; l++)
						{
							if (kierunek3 == 0 || kierunek3 == 1)                                     // losowe wybieranie sciezki w momencie znalezienia luki w murach
							{
								if (npc3_y % 32 == 0 && npc3_x % 32 == 0 &&
									(!mury[(npc3_x - 32) / 32][npc3_y / 32] || !mury[(npc3_x + 32) / 32][npc3_y / 32]))
								{
									kierunek3 = rand() % 4;
									czaslos3_start = al_get_time();
								}
							}

							else if (kierunek3 == 2 || kierunek3 == 3)
							{
								if (npc3_y % 32 == 0 && npc3_x % 32 == 0 &&
									(!mury[(npc3_x) / 32][(npc3_y - 32) / 32] || !mury[(npc3_x) / 32][(npc3_y + 32) / 32]))
								{
									kierunek3 = rand() % 4;
									czaslos3_start = al_get_time();
								}
							}


						}
				}

			}

			if (ruch4)
			{
				if (kierunek4 == 2)
					npc4_x -= 2;
				if (kierunek4 == 3)
					npc4_x += 2;
				if (kierunek4 == 0)
					npc4_y -= 2;
				if (kierunek4 == 1)
					npc4_y += 2;

				if (czaslos_stop - czaslos4_start > 2)
				{
					for (int k = 0; k < 20; k++)
						for (int l = 0; l < 15; l++)
						{
							if (kierunek4 == 0 || kierunek4 == 1)                                     // losowe wybieranie sciezki w momencie znalezienia luki w murach
							{
								if (npc4_y % 32 == 0 && npc4_x % 32 == 0 &&
									(!mury[(npc4_x - 32) / 32][npc4_y / 32] || !mury[(npc4_x + 32) / 32][npc4_y / 32]))
								{
									kierunek4 = rand() % 4;
									czaslos4_start = al_get_time();
								}
							}

							else if (kierunek4 == 2 || kierunek4 == 3)
							{
								if (npc4_y % 32 == 0 && npc4_x % 32 == 0 &&
									(!mury[(npc4_x) / 32][(npc4_y - 32) / 32] || !mury[(npc4_x) / 32][(npc4_y + 32) / 32]))
								{
									kierunek4 = rand() % 4;
									czaslos4_start = al_get_time();
								}
							}


						}
				}

			}

			if (ruchnpc && !doubleplayer)
			{
				if (kieruneknpc == 2)
					npc_x -= 2;
				if (kieruneknpc == 3)
					npc_x += 2;
				if (kieruneknpc == 0)
					npc_y -= 2;
				if (kieruneknpc == 1)
					npc_y += 2;
			}
		}
		/*if ((npc_x <= gracz_x + al_get_bitmap_width(gracz) - 15) &&         // warunek na kolizje
			(npc_x >= gracz_x - al_get_bitmap_width(gracz) + 15) &&
			(npc_y <= gracz_y + al_get_bitmap_height(gracz) - 15) &&
			(npc_y >= gracz_y - al_get_bitmap_height(gracz) + 15)
			)
			kolizja = true;*/

		czaslos_stop = al_get_time();

		if (!kolizja)
		{
			for (int k = 0; k < 20; k++)
				for (int l = 0; l < 15; l++)
				{
					if (mury[k][l])
					{
						al_draw_bitmap(mur, k * 32, l * 32, 0);
						wspmur_x[k][l] = k * 32;
						wspmur_y[k][l] = l * 32;
					}

				}

			if (keys[LEFT] && wyswietlgracza)
				al_draw_bitmap(gracz2, gracz_x, gracz_y, 0);
			if (keys[RIGHT] && wyswietlgracza)
				al_draw_bitmap(gracz0, gracz_x, gracz_y, 0);
			if (keys[UP] && wyswietlgracza)
				al_draw_bitmap(gracz1, gracz_x, gracz_y, 0);
			if (keys[DOWN] && wyswietlgracza)
				al_draw_bitmap(gracz, gracz_x, gracz_y, 0);
			if (!keys[LEFT] && !keys[RIGHT] && !keys[UP] && !keys[DOWN] && wyswietlgracza)
				al_draw_bitmap(gracz, gracz_x, gracz_y, 0);

			/*if (keys[A])
				al_draw_bitmap(npc_l, npc_x, npc_y, 0);
			if (keys[D])
				al_draw_bitmap(npc_r, npc_x, npc_y, 0);
			if (keys[W])
				al_draw_bitmap(npc_u, npc_x, npc_y, 0);
			if (keys[S])
				al_draw_bitmap(npc_d, npc_x, npc_y, 0);
			if (!keys[A] && !keys[D] && !keys[W] && !keys[S])

				al_draw_bitmap(npc_d, npc_x, npc_y, 0);*/


			if (kieruneknpc == 0 && wyswietlnpc)
				al_draw_bitmap(npc_u, npc_x, npc_y, 0);
			if (kieruneknpc == 1 && wyswietlnpc)
				al_draw_bitmap(npc_d, npc_x, npc_y, 0);
			if (kieruneknpc == 2 && wyswietlnpc)
				al_draw_bitmap(npc_l, npc_x, npc_y, 0);
			if (kieruneknpc == 3 && wyswietlnpc)
				al_draw_bitmap(npc_r, npc_x, npc_y, 0);


			if (kierunek1 == 0 && wyswietlnpc1)
				al_draw_bitmap(npc1_u, npc1_x, npc1_y, 0);
			if (kierunek1 == 1 && wyswietlnpc1)
				al_draw_bitmap(npc1_d, npc1_x, npc1_y, 0);
			if (kierunek1 == 2 && wyswietlnpc1)
				al_draw_bitmap(npc1_l, npc1_x, npc1_y, 0);
			if (kierunek1 == 3 && wyswietlnpc1)
				al_draw_bitmap(npc1_r, npc1_x, npc1_y, 0);

			if (kierunek2 == 0 && wyswietlnpc2)
				al_draw_bitmap(npc2_u, npc2_x, npc2_y, 0);
			if (kierunek2 == 1 && wyswietlnpc2)
				al_draw_bitmap(npc2_d, npc2_x, npc2_y, 0);
			if (kierunek2 == 2 && wyswietlnpc2)
				al_draw_bitmap(npc2_l, npc2_x, npc2_y, 0);
			if (kierunek2 == 3 && wyswietlnpc2)
				al_draw_bitmap(npc2_r, npc2_x, npc2_y, 0);


			if (kierunek3 == 0 && wyswietlnpc3)
				al_draw_bitmap(npc3_u, npc3_x, npc3_y, 0);
			if (kierunek3 == 1 && wyswietlnpc3)
				al_draw_bitmap(npc3_d, npc3_x, npc3_y, 0);
			if (kierunek3 == 2 && wyswietlnpc3)
				al_draw_bitmap(npc3_l, npc3_x, npc3_y, 0);
			if (kierunek3 == 3 && wyswietlnpc3)
				al_draw_bitmap(npc3_r, npc3_x, npc3_y, 0);


			if (kierunek4 == 0 && wyswietlnpc4)
				al_draw_bitmap(npc4_u, npc4_x, npc4_y, 0);
			if (kierunek4 == 1 && wyswietlnpc4)
				al_draw_bitmap(npc4_d, npc4_x, npc4_y, 0);
			if (kierunek4 == 2 && wyswietlnpc4)
				al_draw_bitmap(npc4_l, npc4_x, npc4_y, 0);
			if (kierunek4 == 3 && wyswietlnpc4)
				al_draw_bitmap(npc4_r, npc4_x, npc4_y, 0);

			
			if (bomba  )
			{
				
				if (wspbomb) 
				{
					bomb_x = gracz_x;
					bomb_y = gracz_y;
					wspbomb = false;
				}

				if (gracz_x < bomb_x + 32 && kierunek == 2 && gracz_y==bomb_y && gracz_x>bomb_x)
					bomb_x -= 64;
				if (gracz_x+32 > bomb_x && kierunek == 3 && gracz_y==bomb_y && gracz_x+32<bomb_x+32)
					bomb_x += 64;
				if (gracz_y < bomb_y + 32 && kierunek == 0 && gracz_x==bomb_x && gracz_y>bomb_y)
					bomb_y -= 64;
				if (gracz_y+32 > bomb_y && kierunek == 1 && gracz_x == bomb_x && gracz_y+32<bomb_y+32)
					bomb_y += 64;

				if (mury[bomb_x / 32][bomb_y / 32] || (bomb_x % 32 != 0 || bomb_y % 32 != 0))
					bomba = false;
				
				al_draw_bitmap(bomb, bomb_x, bomb_y, 0);
				czas2 = al_get_time();
				
			}
			
			if (wybuch==true || (czas2 - czas1) > 3 && (czas2 - czas1) < 3.5)
			{
				if (dzwieki)
				al_play_sample_instance(dzwiekwybuchu);
				if (!mury[bomb_x / 32][bomb_y / 32])
				{
					al_draw_filled_rectangle(bomb_x, bomb_y, bomb_x + 32, bomb_y + 32, al_map_rgb(255, 255, 0));
				}

				if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
				{
					al_draw_filled_rectangle(bomb_x, bomb_y - 32, bomb_x + 32, bomb_y, al_map_rgb(255, 255, 0));
					if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
						al_draw_filled_rectangle(bomb_x, bomb_y - 64, bomb_x + 32, bomb_y - 32, al_map_rgb(255, 255, 0));
				}

				if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
				{
					al_draw_filled_rectangle(bomb_x, bomb_y + 32, bomb_x + 32, bomb_y + 64, al_map_rgb(255, 255, 0));
					if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
						al_draw_filled_rectangle(bomb_x, bomb_y + 64, bomb_x + 32, bomb_y + 96, al_map_rgb(255, 255, 0));
				}

				if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
				{
					al_draw_filled_rectangle(bomb_x, bomb_y, bomb_x - 32, bomb_y + 32, al_map_rgb(255, 255, 0));
					if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
						al_draw_filled_rectangle(bomb_x - 32, bomb_y, bomb_x - 64, bomb_y + 32, al_map_rgb(255, 255, 0));
				}

				if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
				{
					al_draw_filled_rectangle(bomb_x + 32, bomb_y, bomb_x + 64, bomb_y + 32, al_map_rgb(255, 255, 0));
					if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
						al_draw_filled_rectangle(bomb_x + 64, bomb_y, bomb_x + 96, bomb_y + 32, al_map_rgb(255, 255, 0));
				}


					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (gracz_x == bomb_x  && gracz_y + 32 <= bomb_y && gracz_y + 32 >= bomb_y - 32)
							wyswietlgracza = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (gracz_x == bomb_x && gracz_y + 32 < bomb_y - 32 && gracz_y + 32 > bomb_y - 64)
								wyswietlgracza = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (gracz_x == bomb_x  && gracz_y >= bomb_y + 32 && gracz_y <= bomb_y + 64)
							wyswietlgracza = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (gracz_x == bomb_x && gracz_y > bomb_y + 64 && gracz_y < bomb_y + 96)
								wyswietlgracza = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (gracz_x + 32 <= bomb_x  && gracz_y == bomb_y && gracz_x + 32 >= bomb_x - 32)
							wyswietlgracza = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (gracz_x + 32 < bomb_x - 32 && gracz_y == bomb_y && gracz_x + 32 > bomb_x - 64)
								wyswietlgracza = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (gracz_x >= bomb_x + 32 && gracz_y == bomb_y && gracz_x <= bomb_x + 64)
							wyswietlgracza = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (gracz_x > bomb_x + 64 && gracz_y == bomb_y && gracz_x < bomb_x + 96)
								wyswietlgracza = false;
					}
					if (gracz_x == bomb_x  && gracz_y + 32 <= bomb_y + 32 && gracz_y + 32 >= bomb_y)
						wyswietlgracza = false;
					if (gracz_x == bomb_x  && gracz_y >= bomb_y && gracz_y <= bomb_y + 32)
						wyswietlgracza = false;
					if (gracz_x + 32 <= bomb_x + 32 && gracz_y == bomb_y && gracz_x + 32 >= bomb_x)
						wyswietlgracza = false;
					if (gracz_x <= bomb_x + 32 && gracz_y == bomb_y && gracz_x >= bomb_x)
						wyswietlgracza = false;


					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (npc_x == bomb_x  && npc_y + 32 <= bomb_y && npc_y + 32 >= bomb_y - 32)
							wyswietlnpc = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (npc_x == bomb_x && npc_y + 32 < bomb_y - 32 && npc_y + 32 > bomb_y - 64)
								wyswietlnpc = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (npc_x == bomb_x  && npc_y >= bomb_y + 32 && npc_y <= bomb_y + 64)
							wyswietlnpc = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (npc_x == bomb_x && npc_y > bomb_y + 64 && npc_y < bomb_y + 96)
								wyswietlnpc = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (npc_x + 32 <= bomb_x  && npc_y == bomb_y && npc_x + 32 >= bomb_x - 32)
							wyswietlnpc = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (npc_x + 32 < bomb_x - 32 && npc_y == bomb_y && npc_x + 32 > bomb_x - 64)
								wyswietlnpc = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (npc_x >= bomb_x + 32 && npc_y == bomb_y && npc_x <= bomb_x + 64)
							wyswietlnpc = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (npc_x > bomb_x + 64 && npc_y == bomb_y && npc_x < bomb_x + 96)
								wyswietlnpc = false;
					}
					if (npc_x == bomb_x  && npc_y + 32 <= bomb_y + 32 && npc_y + 32 >= bomb_y)
						wyswietlnpc = false;
					if (npc_x == bomb_x  && npc_y >= bomb_y && npc_y <= bomb_y + 32)
						wyswietlnpc = false;
					if (npc_x + 32 <= bomb_x + 32 && npc_y == bomb_y && npc_x + 32 >= bomb_x)
						wyswietlnpc = false;
					if (npc_x <= bomb_x + 32 && npc_y == bomb_y && npc_x >= bomb_x)
						wyswietlnpc = false;



					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (npc1_x == bomb_x  && npc1_y + 32 <= bomb_y && npc1_y + 32 >= bomb_y - 32)
							wyswietlnpc1 = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (npc1_x == bomb_x && npc1_y + 32 < bomb_y - 32 && npc1_y + 32 > bomb_y - 64)
								wyswietlnpc1 = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (npc1_x == bomb_x  && npc1_y >= bomb_y + 32 && npc1_y <= bomb_y + 64)
							wyswietlnpc1 = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (npc1_x == bomb_x && npc1_y > bomb_y + 64 && npc1_y < bomb_y + 96)
								wyswietlnpc1 = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (npc1_x + 32 <= bomb_x  && npc1_y == bomb_y && npc1_x + 32 >= bomb_x - 32)
							wyswietlnpc1 = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (npc1_x + 32 < bomb_x - 32 && npc1_y == bomb_y && npc1_x + 32 > bomb_x - 64)
								wyswietlnpc1 = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (npc1_x >= bomb_x + 32 && npc1_y == bomb_y && npc1_x <= bomb_x + 64)
							wyswietlnpc1 = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (npc1_x > bomb_x + 64 && npc1_y == bomb_y && npc1_x < bomb_x + 96)
								wyswietlnpc1 = false;
					}
					if (npc1_x == bomb_x  && npc1_y + 32 <= bomb_y + 32 && npc1_y + 32 >= bomb_y)
						wyswietlnpc1 = false;
					if (npc1_x == bomb_x  && npc1_y >= bomb_y && npc1_y <= bomb_y + 32)
						wyswietlnpc1 = false;
					if (npc1_x + 32 <= bomb_x + 32 && npc1_y == bomb_y && npc1_x + 32 >= bomb_x)
						wyswietlnpc1 = false;
					if (npc1_x <= bomb_x + 32 && npc1_y == bomb_y && npc1_x >= bomb_x)
						wyswietlnpc1 = false;


					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (npc2_x == bomb_x  && npc2_y + 32 <= bomb_y && npc2_y + 32 >= bomb_y - 32)
							wyswietlnpc2 = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (npc2_x == bomb_x && npc2_y + 32 < bomb_y - 32 && npc2_y + 32 > bomb_y - 64)
								wyswietlnpc2 = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (npc2_x == bomb_x  && npc2_y >= bomb_y + 32 && npc2_y <= bomb_y + 64)
							wyswietlnpc2 = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (npc2_x == bomb_x && npc2_y > bomb_y + 64 && npc2_y < bomb_y + 96)
								wyswietlnpc2 = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (npc2_x + 32 <= bomb_x  && npc2_y == bomb_y && npc2_x + 32 >= bomb_x - 32)
							wyswietlnpc2 = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (npc2_x + 32 < bomb_x - 32 && npc2_y == bomb_y && npc2_x + 32 > bomb_x - 64)
								wyswietlnpc2 = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (npc2_x >= bomb_x + 32 && npc2_y == bomb_y && npc2_x <= bomb_x + 64)
							wyswietlnpc2 = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (npc2_x > bomb_x + 64 && npc2_y == bomb_y && npc2_x < bomb_x + 96)
								wyswietlnpc2 = false;
					}
					if (npc2_x == bomb_x  && npc2_y + 32 <= bomb_y + 32 && npc2_y + 32 >= bomb_y)
						wyswietlnpc2 = false;
					if (npc2_x == bomb_x  && npc2_y >= bomb_y && npc2_y <= bomb_y + 32)
						wyswietlnpc2 = false;
					if (npc2_x + 32 <= bomb_x + 32 && npc2_y == bomb_y && npc2_x + 32 >= bomb_x)
						wyswietlnpc2 = false;
					if (npc2_x <= bomb_x + 32 && npc2_y == bomb_y && npc2_x >= bomb_x)
						wyswietlnpc2 = false;


					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (npc3_x == bomb_x  && npc3_y + 32 <= bomb_y && npc3_y + 32 >= bomb_y - 32)
							wyswietlnpc3 = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (npc3_x == bomb_x && npc3_y + 32 < bomb_y - 32 && npc3_y + 32 > bomb_y - 64)
								wyswietlnpc3 = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (npc3_x == bomb_x  && npc3_y >= bomb_y + 32 && npc3_y <= bomb_y + 64)
							wyswietlnpc3 = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (npc3_x == bomb_x && npc3_y > bomb_y + 64 && npc3_y < bomb_y + 96)
								wyswietlnpc3 = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (npc3_x + 32 <= bomb_x  && npc3_y == bomb_y && npc3_x + 32 >= bomb_x - 32)
							wyswietlnpc3 = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (npc3_x + 32 < bomb_x - 32 && npc3_y == bomb_y && npc3_x + 32 > bomb_x - 64)
								wyswietlnpc3 = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (npc3_x >= bomb_x + 32 && npc3_y == bomb_y && npc3_x <= bomb_x + 64)
							wyswietlnpc3 = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (npc3_x > bomb_x + 64 && npc3_y == bomb_y && npc3_x < bomb_x + 96)
								wyswietlnpc3 = false;
					}
					if (npc3_x == bomb_x  && npc3_y + 32 <= bomb_y + 32 && npc3_y + 32 >= bomb_y)
						wyswietlnpc3 = false;
					if (npc3_x == bomb_x  && npc3_y >= bomb_y && npc3_y <= bomb_y + 32)
						wyswietlnpc3 = false;
					if (npc3_x + 32 <= bomb_x + 32 && npc3_y == bomb_y && npc3_x + 32 >= bomb_x)
						wyswietlnpc3 = false;
					if (npc3_x <= bomb_x + 32 && npc3_y == bomb_y && npc3_x >= bomb_x)
						wyswietlnpc3 = false;


					if (!mury[bomb_x / 32][(bomb_y - 32) / 32])
					{
						if (npc4_x == bomb_x  && npc4_y + 32 <= bomb_y && npc4_y + 32 >= bomb_y - 32)
							wyswietlnpc4 = false;
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (npc4_x == bomb_x && npc4_y + 32 < bomb_y - 32 && npc4_y + 32 > bomb_y - 64)
								wyswietlnpc4 = false;
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32])
					{
						if (npc4_x == bomb_x  && npc4_y >= bomb_y + 32 && npc4_y <= bomb_y + 64)
							wyswietlnpc4 = false;
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (npc4_x == bomb_x && npc4_y > bomb_y + 64 && npc4_y < bomb_y + 96)
								wyswietlnpc4 = false;
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32])
					{
						if (npc4_x + 32 <= bomb_x  && npc4_y == bomb_y && npc4_x + 32 >= bomb_x - 32)
							wyswietlnpc4 = false;
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (npc4_x + 32 < bomb_x - 32 && npc4_y == bomb_y && npc4_x + 32 > bomb_x - 64)
								wyswietlnpc4 = false;
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32])
					{
						if (npc4_x >= bomb_x + 32 && npc4_y == bomb_y && npc4_x <= bomb_x + 64)
							wyswietlnpc4 = false;
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (npc4_x > bomb_x + 64 && npc4_y == bomb_y && npc4_x < bomb_x + 96)
								wyswietlnpc4 = false;
					}
					if (npc4_x == bomb_x  && npc4_y + 32 <= bomb_y + 32 && npc4_y + 32 >= bomb_y)
						wyswietlnpc4 = false;
					if (npc4_x == bomb_x  && npc4_y >= bomb_y && npc4_y <= bomb_y + 32)
						wyswietlnpc4 = false;
					if (npc4_x + 32 <= bomb_x + 32 && npc4_y == bomb_y && npc4_x + 32 >= bomb_x)
						wyswietlnpc4 = false;
					if (npc4_x <= bomb_x + 32 && npc4_y == bomb_y && npc4_x >= bomb_x)
						wyswietlnpc4 = false;

					
					
					if (!mury[bomb_x / 32][(bomb_y - 32) / 32] && bomba1)
					{
						if (bomb1_x == bomb_x  && bomb1_y + 32 <= bomb_y && bomb1_y + 32 >= bomb_y - 32)
						{
							wybuch1 = true;
							czaswybuch_start = al_get_time();
						}
						if (!mury[bomb_x / 32][(bomb_y - 64) / 32])
							if (bomb1_x == bomb_x && bomb1_y + 32 < bomb_y - 32 && bomb1_y + 32 > bomb_y - 64)
							{
								wybuch1 = true;
								czaswybuch_start = al_get_time();
							}
					}

					if (!mury[bomb_x / 32][(bomb_y + 32) / 32] && bomba1)
					{
						if (bomb1_x == bomb_x  && bomb1_y >= bomb_y + 32 && bomb1_y <= bomb_y + 64)
						{
							wybuch1 = true;
							czaswybuch_start = al_get_time();
						}
						if (!mury[bomb_x / 32][(bomb_y + 64) / 32])
							if (bomb1_x == bomb_x && bomb1_y > bomb_y + 64 && bomb1_y < bomb_y + 96)
							{
								wybuch1 = true;
								czaswybuch_start = al_get_time();
							}
					}

					if (!mury[(bomb_x - 32) / 32][bomb_y / 32] && bomba1)
					{
						if (bomb1_x + 32 <= bomb_x  && bomb1_y == bomb_y && bomb1_x + 32 >= bomb_x - 32)
						{
							wybuch1 = true;
							czaswybuch_start = al_get_time();
						}
						if (!mury[(bomb_x - 64) / 32][bomb_y / 32])
							if (bomb1_x + 32 < bomb_x - 32 && bomb1_y == bomb_y && bomb1_x + 32 > bomb_x - 64)
							{
								wybuch1 = true;
								czaswybuch_start = al_get_time();
							}
					}

					if (!mury[(bomb_x + 32) / 32][bomb_y / 32] && bomba1)
					{
						if (bomb1_x >= bomb_x + 32 && bomb1_y == bomb_y && bomb1_x <= bomb_x + 64)
						{
							wybuch1 = true;
							czaswybuch_start = al_get_time();
						}
						if (!mury[(bomb_x + 64) / 32][bomb_y / 32])
							if (bomb1_x > bomb_x + 64 && bomb1_y == bomb_y && bomb1_x < bomb_x + 96)
							{
								wybuch1 = true;
								czaswybuch_start = al_get_time();
							}
					}


                     if (czaswybuch0_stop - czaswybuch0_start>0.5)
						wybuch = false;
					
				
					czas2 = al_get_time();
					czaswybuch0_stop = al_get_time();
					bomba = false;		
					
					
				}

				



				if (bomba1 )
				{
					
					if (wspbomb1)
					{
						bomb1_x = gracz_x;
						bomb1_y = gracz_y;
						wspbomb1 = false;
					}

					if (gracz_x < bomb1_x + 32 && kierunek == 2 && gracz_y == bomb1_y && gracz_x>bomb1_x)
						bomb1_x -= 64;
					if (gracz_x + 32 > bomb1_x && kierunek == 3 && gracz_y == bomb1_y && gracz_x + 32<bomb1_x + 32)
						bomb1_x += 64;
					if (gracz_y < bomb1_y + 32 && kierunek == 0 && gracz_x == bomb1_x && gracz_y>bomb1_y)
						bomb1_y -= 64;
					if (gracz_y + 32 > bomb1_y && kierunek == 1 && gracz_x == bomb1_x && gracz_y + 32<bomb1_y + 32)
						bomb1_y += 64;

					if (mury[bomb1_x / 32][bomb1_y / 32] || (bomb1_x % 32 != 0 || bomb1_y % 32 != 0))
						bomba1 = false;

					al_draw_bitmap(bomb, bomb1_x, bomb1_y, 0);

					czas22 = al_get_time();
				

				}
				if (wybuch1 == true || (czas22 - czas11) > 3 && (czas22 - czas11) < 3.5)
				{
					if (dzwieki)
					al_play_sample_instance(dzwiekwybuchu);
					if (!mury[bomb1_x / 32][bomb1_y / 32])
						al_draw_filled_rectangle(bomb1_x, bomb1_y, bomb1_x + 32, bomb1_y + 32, al_map_rgb(255, 255, 0));

					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						al_draw_filled_rectangle(bomb1_x, bomb1_y - 32, bomb1_x + 32, bomb1_y, al_map_rgb(255, 255, 0));
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							al_draw_filled_rectangle(bomb1_x, bomb1_y - 64, bomb1_x + 32, bomb1_y - 32, al_map_rgb(255, 255, 0));
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						al_draw_filled_rectangle(bomb1_x, bomb1_y + 32, bomb1_x + 32, bomb1_y + 64, al_map_rgb(255, 255, 0));
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							al_draw_filled_rectangle(bomb1_x, bomb1_y + 64, bomb1_x + 32, bomb1_y + 96, al_map_rgb(255, 255, 0));
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						al_draw_filled_rectangle(bomb1_x, bomb1_y, bomb1_x - 32, bomb1_y + 32, al_map_rgb(255, 255, 0));
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							al_draw_filled_rectangle(bomb1_x - 32, bomb1_y, bomb1_x - 64, bomb1_y + 32, al_map_rgb(255, 255, 0));
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						al_draw_filled_rectangle(bomb1_x + 32, bomb1_y, bomb1_x + 64, bomb1_y + 32, al_map_rgb(255, 255, 0));
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							al_draw_filled_rectangle(bomb1_x + 64, bomb1_y, bomb1_x + 96, bomb1_y + 32, al_map_rgb(255, 255, 0));
					}

					bomba1 = false;
					czas22 = al_get_time();
					czaswybuch_stop = al_get_time();

					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (gracz_x == bomb1_x  && gracz_y + 32 <= bomb1_y && gracz_y + 32 >= bomb1_y - 32)
							wyswietlgracza = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (gracz_x == bomb1_x && gracz_y + 32 < bomb1_y - 32 && gracz_y + 32 > bomb1_y - 64)
								wyswietlgracza = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (gracz_x == bomb1_x  && gracz_y >= bomb1_y + 32 && gracz_y <= bomb1_y + 64)
							wyswietlgracza = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (gracz_x == bomb1_x && gracz_y > bomb1_y + 64 && gracz_y < bomb1_y + 96)
								wyswietlgracza = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (gracz_x + 32 <= bomb1_x  && gracz_y == bomb1_y && gracz_x + 32 >= bomb1_x - 32)
							wyswietlgracza = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (gracz_x + 32 < bomb1_x - 32 && gracz_y == bomb1_y && gracz_x + 32 > bomb1_x - 64)
								wyswietlgracza = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (gracz_x >= bomb1_x + 32 && gracz_y == bomb1_y && gracz_x <= bomb1_x + 64)
							wyswietlgracza = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (gracz_x > bomb1_x + 64 && gracz_y == bomb1_y && gracz_x < bomb1_x + 96)
								wyswietlgracza = false;
					}
					if (gracz_x == bomb1_x  && gracz_y + 32 <= bomb1_y + 32 && gracz_y + 32 >= bomb1_y)
						wyswietlgracza = false;
					if (gracz_x == bomb1_x  && gracz_y >= bomb1_y && gracz_y <= bomb1_y + 32)
						wyswietlgracza = false;
					if (gracz_x + 32 <= bomb1_x + 32 && gracz_y == bomb1_y && gracz_x + 32 >= bomb1_x)
						wyswietlgracza = false;
					if (gracz_x <= bomb1_x + 32 && gracz_y == bomb1_y && gracz_x >= bomb1_x)
						wyswietlgracza = false;


					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (npc_x == bomb1_x  && npc_y + 32 <= bomb1_y && npc_y + 32 >= bomb1_y - 32)
							wyswietlnpc = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (npc_x == bomb1_x && npc_y + 32 < bomb1_y - 32 && npc_y + 32 > bomb1_y - 64)
								wyswietlnpc = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (npc_x == bomb1_x  && npc_y >= bomb1_y + 32 && npc_y <= bomb1_y + 64)
							wyswietlnpc = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (npc_x == bomb1_x && npc_y > bomb1_y + 64 && npc_y < bomb1_y + 96)
								wyswietlnpc = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (npc_x + 32 <= bomb1_x  && npc_y == bomb1_y && npc_x + 32 >= bomb1_x - 32)
							wyswietlnpc = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (npc_x + 32 < bomb1_x - 32 && npc_y == bomb1_y && npc_x + 32 > bomb1_x - 64)
								wyswietlnpc = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (npc_x >= bomb1_x + 32 && npc_y == bomb1_y && npc_x <= bomb1_x + 64)
							wyswietlnpc = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (npc_x > bomb1_x + 64 && npc_y == bomb1_y && npc_x < bomb1_x + 96)
								wyswietlnpc = false;
					}
					if (npc_x == bomb1_x  && npc_y + 32 <= bomb1_y + 32 && npc_y + 32 >= bomb1_y)
						wyswietlnpc = false;
					if (npc_x == bomb1_x  && npc_y >= bomb1_y && npc_y <= bomb1_y + 32)
						wyswietlnpc = false;
					if (npc_x + 32 <= bomb1_x + 32 && npc_y == bomb1_y && npc_x + 32 >= bomb1_x)
						wyswietlnpc = false;
					if (npc_x <= bomb1_x + 32 && npc_y == bomb1_y && npc_x >= bomb1_x)
						wyswietlnpc = false;



					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (npc1_x == bomb1_x  && npc1_y + 32 <= bomb1_y && npc1_y + 32 >= bomb1_y - 32)
							wyswietlnpc1 = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (npc1_x == bomb1_x && npc1_y + 32 < bomb1_y - 32 && npc1_y + 32 > bomb1_y - 64)
								wyswietlnpc1 = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (npc1_x == bomb1_x  && npc1_y >= bomb1_y + 32 && npc1_y <= bomb1_y + 64)
							wyswietlnpc1 = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (npc1_x == bomb1_x && npc1_y > bomb1_y + 64 && npc1_y < bomb1_y + 96)
								wyswietlnpc1 = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (npc1_x + 32 <= bomb1_x  && npc1_y == bomb1_y && npc1_x + 32 >= bomb1_x - 32)
							wyswietlnpc1 = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (npc1_x + 32 < bomb1_x - 32 && npc1_y == bomb1_y && npc1_x + 32 > bomb1_x - 64)
								wyswietlnpc1 = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (npc1_x >= bomb1_x + 32 && npc1_y == bomb1_y && npc1_x <= bomb1_x + 64)
							wyswietlnpc1 = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (npc1_x > bomb1_x + 64 && npc1_y == bomb1_y && npc1_x < bomb1_x + 96)
								wyswietlnpc1 = false;
					}
					if (npc1_x == bomb1_x  && npc1_y + 32 <= bomb1_y + 32 && npc1_y + 32 >= bomb1_y)
						wyswietlnpc1 = false;
					if (npc1_x == bomb1_x  && npc1_y >= bomb1_y && npc1_y <= bomb1_y + 32)
						wyswietlnpc1 = false;
					if (npc1_x + 32 <= bomb1_x + 32 && npc1_y == bomb1_y && npc1_x + 32 >= bomb1_x)
						wyswietlnpc1 = false;
					if (npc1_x <= bomb1_x + 32 && npc1_y == bomb1_y && npc1_x >= bomb1_x)
						wyswietlnpc1 = false;


					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (npc2_x == bomb1_x  && npc2_y + 32 <= bomb1_y && npc2_y + 32 >= bomb1_y - 32)
							wyswietlnpc2 = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (npc2_x == bomb1_x && npc2_y + 32 < bomb1_y - 32 && npc2_y + 32 > bomb1_y - 64)
								wyswietlnpc2 = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (npc2_x == bomb1_x  && npc2_y >= bomb1_y + 32 && npc2_y <= bomb1_y + 64)
							wyswietlnpc2 = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (npc2_x == bomb1_x && npc2_y > bomb1_y + 64 && npc2_y < bomb1_y + 96)
								wyswietlnpc2 = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (npc2_x + 32 <= bomb1_x  && npc2_y == bomb1_y && npc2_x + 32 >= bomb1_x - 32)
							wyswietlnpc2 = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (npc2_x + 32 < bomb1_x - 32 && npc2_y == bomb1_y && npc2_x + 32 > bomb1_x - 64)
								wyswietlnpc2 = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (npc2_x >= bomb1_x + 32 && npc2_y == bomb1_y && npc2_x <= bomb1_x + 64)
							wyswietlnpc2 = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (npc2_x > bomb1_x + 64 && npc2_y == bomb1_y && npc2_x < bomb1_x + 96)
								wyswietlnpc2 = false;
					}
					if (npc2_x == bomb1_x  && npc2_y + 32 <= bomb1_y + 32 && npc2_y + 32 >= bomb1_y)
						wyswietlnpc2 = false;
					if (npc2_x == bomb1_x  && npc2_y >= bomb1_y && npc2_y <= bomb1_y + 32)
						wyswietlnpc2 = false;
					if (npc2_x + 32 <= bomb1_x + 32 && npc2_y == bomb1_y && npc2_x + 32 >= bomb1_x)
						wyswietlnpc2 = false;
					if (npc2_x <= bomb1_x + 32 && npc2_y == bomb1_y && npc2_x >= bomb1_x)
						wyswietlnpc2 = false;


					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (npc3_x == bomb1_x  && npc3_y + 32 <= bomb1_y && npc3_y + 32 >= bomb1_y - 32)
							wyswietlnpc3 = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (npc3_x == bomb1_x && npc3_y + 32 < bomb1_y - 32 && npc3_y + 32 > bomb1_y - 64)
								wyswietlnpc3 = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (npc3_x == bomb1_x  && npc3_y >= bomb1_y + 32 && npc3_y <= bomb1_y + 64)
							wyswietlnpc3 = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (npc3_x == bomb1_x && npc3_y > bomb1_y + 64 && npc3_y < bomb1_y + 96)
								wyswietlnpc3 = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (npc3_x + 32 <= bomb1_x  && npc3_y == bomb1_y && npc3_x + 32 >= bomb1_x - 32)
							wyswietlnpc3 = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (npc3_x + 32 < bomb1_x - 32 && npc3_y == bomb1_y && npc3_x + 32 > bomb1_x - 64)
								wyswietlnpc3 = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (npc3_x >= bomb1_x + 32 && npc3_y == bomb1_y && npc3_x <= bomb1_x + 64)
							wyswietlnpc3 = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (npc3_x > bomb1_x + 64 && npc3_y == bomb1_y && npc3_x < bomb1_x + 96)
								wyswietlnpc3 = false;
					}
					if (npc3_x == bomb1_x  && npc3_y + 32 <= bomb1_y + 32 && npc3_y + 32 >= bomb1_y)
						wyswietlnpc3 = false;
					if (npc3_x == bomb1_x  && npc3_y >= bomb1_y && npc3_y <= bomb1_y + 32)
						wyswietlnpc3 = false;
					if (npc3_x + 32 <= bomb1_x + 32 && npc3_y == bomb1_y && npc3_x + 32 >= bomb1_x)
						wyswietlnpc3 = false;
					if (npc3_x <= bomb1_x + 32 && npc3_y == bomb1_y && npc3_x >= bomb1_x)
						wyswietlnpc3 = false;


					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32])
					{
						if (npc4_x == bomb1_x  && npc4_y + 32 <= bomb1_y && npc4_y + 32 >= bomb1_y - 32)
							wyswietlnpc4 = false;
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (npc4_x == bomb1_x && npc4_y + 32 < bomb1_y - 32 && npc4_y + 32 > bomb1_y - 64)
								wyswietlnpc4 = false;
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32])
					{
						if (npc4_x == bomb1_x  && npc4_y >= bomb1_y + 32 && npc4_y <= bomb1_y + 64)
							wyswietlnpc4 = false;
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (npc4_x == bomb1_x && npc4_y > bomb1_y + 64 && npc4_y < bomb1_y + 96)
								wyswietlnpc4 = false;
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32])
					{
						if (npc4_x + 32 <= bomb1_x  && npc4_y == bomb1_y && npc4_x + 32 >= bomb1_x - 32)
							wyswietlnpc4 = false;
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (npc4_x + 32 < bomb1_x - 32 && npc4_y == bomb1_y && npc4_x + 32 > bomb1_x - 64)
								wyswietlnpc4 = false;
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32])
					{
						if (npc4_x >= bomb1_x + 32 && npc4_y == bomb1_y && npc4_x <= bomb1_x + 64)
							wyswietlnpc4 = false;
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (npc4_x > bomb_x + 64 && npc4_y == bomb1_y && npc4_x < bomb_x + 96)
								wyswietlnpc4 = false;
					}
					if (npc4_x == bomb1_x  && npc4_y + 32 <= bomb1_y + 32 && npc4_y + 32 >= bomb1_y)
						wyswietlnpc4 = false;
					if (npc4_x == bomb1_x  && npc4_y >= bomb1_y && npc4_y <= bomb1_y + 32)
						wyswietlnpc4 = false;
					if (npc4_x + 32 <= bomb1_x + 32 && npc4_y == bomb1_y && npc4_x + 32 >= bomb1_x)
						wyswietlnpc4 = false;
					if (npc4_x <= bomb1_x + 32 && npc4_y == bomb1_y && npc4_x >= bomb1_x)
						wyswietlnpc4 = false;


					if (!mury[bomb1_x / 32][(bomb1_y - 32) / 32] && bomba)
					{
						if (bomb_x == bomb1_x  && bomb_y + 32 <= bomb1_y && bomb_y + 32 >= bomb1_y - 32)
						{
							wybuch = true;
							czaswybuch0_start = al_get_time();
						}
						if (!mury[bomb1_x / 32][(bomb1_y - 64) / 32])
							if (bomb_x == bomb1_x && bomb_y + 32 < bomb1_y - 32 && bomb_y + 32 > bomb1_y - 64)
							{
								wybuch = true;
								czaswybuch0_start = al_get_time();
							}
					}

					if (!mury[bomb1_x / 32][(bomb1_y + 32) / 32] && bomba)
					{
						if (bomb_x == bomb1_x  && bomb_y >= bomb1_y + 32 && bomb_y <= bomb_y + 64)
						{
							wybuch = true;
							czaswybuch0_start = al_get_time();
						}
						if (!mury[bomb1_x / 32][(bomb1_y + 64) / 32])
							if (bomb_x == bomb1_x && bomb_y > bomb1_y + 64 && bomb_y < bomb1_y + 96)
							{
								wybuch = true;
								czaswybuch0_start = al_get_time();
							}
					}

					if (!mury[(bomb1_x - 32) / 32][bomb1_y / 32] && bomba)
					{
						if (bomb_x + 32 <= bomb1_x  && bomb_y == bomb1_y && bomb_x + 32 >= bomb1_x - 32)
						{
							wybuch = true;
							czaswybuch0_start = al_get_time();
						}
						if (!mury[(bomb1_x - 64) / 32][bomb1_y / 32])
							if (bomb_x + 32 < bomb1_x - 32 && bomb_y == bomb1_y && bomb_x + 32 > bomb1_x - 64)
							{
								wybuch = true;
								czaswybuch0_start = al_get_time();
							}
					}

					if (!mury[(bomb1_x + 32) / 32][bomb1_y / 32] && bomba)
					{
						if (bomb_x >= bomb1_x + 32 && bomb_y == bomb1_y && bomb_x <= bomb1_x + 64)
						{
							wybuch = true;
							czaswybuch0_start = al_get_time();
						}
						if (!mury[(bomb1_x + 64) / 32][bomb1_y / 32])
							if (bomb_x > bomb1_x + 64 && bomb_y == bomb1_y && bomb_x < bomb1_x + 96)
							{
								wybuch = true;
								czaswybuch0_start = al_get_time();
							}
					}


					if(czaswybuch_stop-czaswybuch_start>0.5)
					wybuch1 = false;
				}

			}

		
			if(!wyswietlnpc && pok1==false )
			{
				npc_x = -32;
				npc_y = -32;
				pokonany++;
				pok1 = true;
				
			}
			if (!wyswietlnpc1 && pok2==false )
			{
				npc1_x = -64;
				npc1_y = -64;
				pokonany++;
				pok2 = true;
				
			}
			if (!wyswietlnpc2 && pok3==false  )
			{
				npc2_x = -32;
				npc2_y = -32;
				pokonany++;
				pok3 = true;
			
			}
			if (!wyswietlnpc4 && pok5 == false)
			{
				npc4_x = -32;
				npc4_y = -32;
				pokonany++;
				pok5 = true;
				
			}
			if(!wyswietlnpc3 && pok4 ==false )
			{
				npc3_x = -32;
				npc3_y = -32;
				pokonany++;
				pok4 = true;
				
			}

			
				if ((gracz_x < npc_x + 32-8) &&         // warunek na kolizje postaci z potworkami
				(gracz_x > npc_x - 32+8 ) &&
				(gracz_y < npc_y + 32-8) &&
				(gracz_y > npc_y - 32+8)
				)
				wyswietlgracza=false;

			if ((gracz_x < npc1_x + 32-8) &&         // warunek na kolizje postaci z potworkami
				(gracz_x > npc1_x - 32+8) &&
				(gracz_y < npc1_y + 32-8) &&
				(gracz_y > npc1_y - 32+8)&&
				wyswietlnpc1
				)
				wyswietlgracza = false;

			if ((gracz_x < npc2_x + 32-8) &&         // warunek na kolizje postaci z potworkami
				(gracz_x > npc2_x - 32+8) &&
				(gracz_y < npc2_y + 32-8) &&
				(gracz_y > npc2_y - 32+8)&&
				wyswietlnpc2
				)
				wyswietlgracza = false;

			if ((gracz_x < npc3_x + 32-8) &&         // warunek na kolizje postaci z potworkami
				(gracz_x > npc3_x - 32+8) &&
				(gracz_y < npc3_y + 32-8) &&
				(gracz_y > npc3_y - 32+8)
				)
				wyswietlgracza = false;

			if ((gracz_x < npc4_x + 32-8) &&         // warunek na kolizje postaci z potworkami
				(gracz_x > npc4_x - 32+8) &&
				(gracz_y < npc4_y + 32-8) &&
				(gracz_y > npc4_y - 32+8)
				)
				wyswietlgracza = false;



		
		for (int k = 0; k < 20; k++)
			for (int l = 0; l < 15; l++)
			{
				if ((wspmur_x[k][l] < gracz_x + al_get_bitmap_width(gracz)) &&
					(wspmur_x[k][l] > gracz_x - al_get_bitmap_width(gracz)) &&
					(wspmur_y[k][l] < gracz_y + al_get_bitmap_height(gracz)) &&
					(wspmur_y[k][l] > gracz_y - al_get_bitmap_height(gracz)))

					ruch = false;

				if ((wspmur_x[k][l] < npc_x + al_get_bitmap_width(npc_d)) &&
					(wspmur_x[k][l] > npc_x - al_get_bitmap_width(npc_d)) &&
					(wspmur_y[k][l] < npc_y + al_get_bitmap_height(npc_d)) &&
					(wspmur_y[k][l] > npc_y - al_get_bitmap_height(npc_d)))

					ruchnpc = false;

				if ((wspmur_x[k][l] < npc1_x + al_get_bitmap_width(npc1_d)) &&
					(wspmur_x[k][l] > npc1_x - al_get_bitmap_width(npc1_d)) &&
					(wspmur_y[k][l] < npc1_y + al_get_bitmap_height(npc1_d)) &&
					(wspmur_y[k][l] > npc1_y - al_get_bitmap_height(npc1_d)))

					ruch1= false;

				if ((wspmur_x[k][l] < npc2_x + al_get_bitmap_width(npc2_d)) &&
					(wspmur_x[k][l] > npc2_x - al_get_bitmap_width(npc2_d)) &&
					(wspmur_y[k][l] < npc2_y + al_get_bitmap_height(npc2_d)) &&
					(wspmur_y[k][l] > npc2_y - al_get_bitmap_height(npc2_d)))

					ruch2 = false;

				if ((wspmur_x[k][l] < npc3_x + al_get_bitmap_width(npc3_d)) &&
					(wspmur_x[k][l] > npc3_x - al_get_bitmap_width(npc3_d)) &&
					(wspmur_y[k][l] < npc3_y + al_get_bitmap_height(npc3_d)) &&
					(wspmur_y[k][l] > npc3_y - al_get_bitmap_height(npc3_d)))

					ruch3 = false;

				if ((wspmur_x[k][l] < npc4_x + al_get_bitmap_width(npc4_d)) &&
					(wspmur_x[k][l] > npc4_x - al_get_bitmap_width(npc4_d)) &&
					(wspmur_y[k][l] < npc4_y + al_get_bitmap_height(npc4_d)) &&
					(wspmur_y[k][l] > npc4_y - al_get_bitmap_height(npc4_d)))

					ruch4 = false;
			}
		if (bomba) 
		{
			if ((npc_x < bomb_x + 32 ) &&        
				(npc_x > bomb_x - 32 ) &&
				(npc_y < bomb_y + 32 ) &&
				(npc_y > bomb_y - 32 )
				)
				ruchnpc = false;

			if ((npc1_x < bomb_x + 32) &&
				(npc1_x > bomb_x - 32) &&
				(npc1_y < bomb_y + 32) &&
				(npc1_y > bomb_y - 32)
				)
				ruch1 = false;

			if ((npc2_x < bomb_x + 32) &&
				(npc2_x > bomb_x - 32) &&
				(npc2_y < bomb_y + 32) &&
				(npc2_y > bomb_y - 32)
				)
				ruch2 = false;

			if ((npc3_x < bomb_x + 32) &&
				(npc3_x > bomb_x - 32) &&
				(npc3_y < bomb_y + 32) &&
				(npc3_y > bomb_y - 32)
				)
				ruch3 = false;

			if ((npc4_x < bomb_x + 32) &&
				(npc4_x > bomb_x - 32) &&
				(npc4_y < bomb_y + 32) &&
				(npc4_y > bomb_y - 32)
				)
				ruch4 = false;
		}


		if (bomba1)
		{
			if ((npc_x < bomb1_x + 32) &&
				(npc_x > bomb1_x - 32) &&
				(npc_y < bomb1_y + 32) &&
				(npc_y > bomb1_y - 32)
				)
				ruchnpc = false;

			if ((npc1_x < bomb1_x + 32) &&
				(npc1_x > bomb1_x - 32) &&
				(npc1_y < bomb1_y + 32) &&
				(npc1_y > bomb1_y - 32)
				)
				ruch1 = false;

			if ((npc2_x < bomb1_x + 32) &&
				(npc2_x > bomb1_x - 32) &&
				(npc2_y < bomb1_y + 32) &&
				(npc2_y > bomb1_y - 32)
				)
				ruch2 = false;

			if ((npc3_x < bomb1_x + 32) &&
				(npc3_x > bomb1_x - 32) &&
				(npc3_y < bomb1_y + 32) &&
				(npc3_y > bomb1_y - 32)
				)
				ruch3 = false;

			if ((npc4_x < bomb1_x + 32) &&
				(npc4_x > bomb1_x - 32) &&
				(npc4_y < bomb1_y + 32) &&
				(npc4_y > bomb1_y - 32)
				)
				ruch4 = false;
		}


		if (!ruch)
		{


			if (keys[LEFT])
				gracz_x += 2;
			if (keys[RIGHT])
				gracz_x -= 2;
			if (keys[UP])
				gracz_y += 2;
			if (keys[DOWN])
				gracz_y -= 2;


			ruch = true;
		}

		if (!ruchnpc)
		{

			if (doubleplayer)
			{
				if (keys[A])
					npc_x += 2;
				if (keys[D])
					npc_x -= 2;
				if (keys[W])
					npc_y += 2;
				if (keys[S])
					npc_y -= 2;
			}

			if (!doubleplayer)
			{
				if (kieruneknpc == 2)
					npc_x += 2;
				if (kieruneknpc == 3)
					npc_x -= 2;
				if (kieruneknpc == 0)
					npc_y += 2;
				if (kieruneknpc == 1)
					npc_y -= 2;

				kieruneknpc = rand() % 4;
			}
			ruchnpc = true;
		}

		if (!ruch1)
		{


			if (kierunek1==2)
				npc1_x += 2;
			if (kierunek1==3)
				npc1_x -= 2;
			if (kierunek1==0)
				npc1_y += 2;
			if (kierunek1==1)
				npc1_y -= 2;

			kierunek1 = rand() % 4;
			ruch1 = true;
		}

		if (!ruch2)
		{


			if (kierunek2 == 2)
				npc2_x += 2;
			if (kierunek2 == 3)
				npc2_x -= 2;
			if (kierunek2 == 0)
				npc2_y += 2;
			if (kierunek2 == 1)
				npc2_y -= 2;

			kierunek2 = rand() % 4;
			ruch2 = true;
		}

		if (!ruch3)
		{


			if (kierunek3 == 2)
				npc3_x += 2;
			if (kierunek3 == 3)
				npc3_x -= 2;
			if (kierunek3 == 0)
				npc3_y += 2;
			if (kierunek3 == 1)
				npc3_y -= 2;

			kierunek3 = rand() % 4;
			ruch3 = true;
		}

		if (!ruch4)
		{


			if (kierunek4 == 2)
				npc4_x += 2;
			if (kierunek4 == 3)
				npc4_x -= 2;
			if (kierunek4 == 0)
				npc4_y += 2;
			if (kierunek4 == 1)
				npc4_y -= 2;

			kierunek4 = rand() % 4;
			ruch4 = true;
		}

		if (kolizja)
			al_draw_text
			(
				font14, al_map_rgb(0, 0, 0), al_get_display_width(okno) / 2,
				al_get_display_height(okno) / 2 - 8,
				ALLEGRO_ALIGN_CENTRE, "KOLIZJA - NACISNIJ ESC ABY ZAMKNAC"
			);
		if (!wyswietlgracza && czaszmianymapy)
		{
			czaszmianymapy_start = al_get_time();
			czaszmianymapy = false;
			
		}
		if (!wyswietlgracza )
		{
			al_draw_text
			(
				font54, al_map_rgb(0, 128, 255),320 ,170,ALLEGRO_ALIGN_CENTRE, "POKONANY"
			);

		}
		if (!wyswietlgracza && al_get_time() - czaszmianymapy_start>2)
		{
			zamknij = true;
			if (dzwieki)
			al_play_sample_instance(gameover);
			czaszmianymapy = true;
		}
		if (!wyswietlnpc && !wyswietlnpc1 && !wyswietlnpc2 && !wyswietlnpc3 && !wyswietlnpc4 && ktoraplansza != 4 && czaszmianymapy)
		{
			czaszmianymapy_start = al_get_time();
			czaszmianymapy = false;
		}
		if (!wyswietlnpc && !wyswietlnpc1 && !wyswietlnpc2 && !wyswietlnpc3 && !wyswietlnpc4 && ktoraplansza!=4 && 
			al_get_time()-czaszmianymapy_start>2)
		{
			gracz_x = 576, gracz_y = 416;
			 npc_x = 192, npc_y = 32;
			 npc1_x = 576, npc1_y = 32;
			 npc2_x = 32, npc2_y = 192;
			 npc3_x = 192, npc3_y = 416;
			 npc4_x = 320, npc4_y = 288;
			 wyswietlnpc = true;
			 wyswietlnpc1 = true;
			 wyswietlnpc2 = true;
			 wyswietlnpc3 = true;
			 wyswietlnpc4 = true;
			 pok1 = false; pok2 = false; pok3 = false; pok4 = false; pok5 = false;
			 ktoraplansza=ktoraplansza+1 ;
			 czaszmianymapy = true;
		}
		if (!wyswietlnpc && !wyswietlnpc1 && !wyswietlnpc2 && !wyswietlnpc3 && !wyswietlnpc4 && ktoraplansza == 4 && czaszmianymapy)
		{
			czaszmianymapy_start = al_get_time();
			czaszmianymapy = false;
		}
		if (!wyswietlnpc && !wyswietlnpc1 && !wyswietlnpc2 && !wyswietlnpc3 && !wyswietlnpc4 && ktoraplansza == 4
			&& al_get_time() - czaszmianymapy_start>2)
		{
			if (dzwieki)
			al_play_sample_instance(dzwiekzwyciestwa);
			zamknij = true;
			czaszmianymapy = true;
		}
		

		al_draw_filled_rectangle(640, 0, 800, 480, al_map_rgb(0, 128, 255));
		al_draw_text (font12, al_map_rgb(0, 0, 0), 653,20,0, "LICZBA POKONANYCH");
		al_draw_text(font12, al_map_rgb(0, 0, 0), 690, 32, 0, "RYWALI");
		al_draw_textf(font12, al_map_rgb(0, 0, 0), 712, 50, 0,"%d", pokonany);
		al_draw_text(font12, al_map_rgb(0, 0, 0), 685, 80, 0, "CZAS GRY");
		al_draw_textf(font12, al_map_rgb(0, 0, 0), 702, 100, 0, "%.1f", czasgry);
		al_draw_text(font12, al_map_rgb(0, 0, 0), 665, 130, 0, "POZYCJA POSTACI");
		al_draw_text(font12, al_map_rgb(0, 0, 0), 700, 150, 0, "x:");
		al_draw_text(font12, al_map_rgb(0, 0, 0), 700, 160, 0, "y:");
		al_draw_textf(font12, al_map_rgb(0, 0, 0), 720, 150, 0, "%d", gracz_x);
		al_draw_textf(font12, al_map_rgb(0, 0, 0), 720, 160, 0, "%d", gracz_y);
		al_draw_text(font12, al_map_rgb(0, 0, 0), 650, 190, 0, "WYKORZYSTANE BOMBY");
		al_draw_textf(font12, al_map_rgb(0, 0, 0), 712, 210, 0, "%d", iloscbomb);
		al_draw_text(font12, al_map_rgb(0, 0, 0), 647, 240, 0, "CZY JEST DOPUSZCZALNE");
		al_draw_text(font12, al_map_rgb(0, 0, 0), 660, 250, 0, "POSTAWIENIE BOMBY");
		if (gracz_x % 32 != 0 || gracz_y % 32 != 0)
			al_draw_text(font12, al_map_rgb(255, 0, 0), 708, 270, 0, "NIE");
		else al_draw_text(font12, al_map_rgb(0, 230, 0), 708, 270, 0, "TAK");
		if(!bomba) al_draw_bitmap(bomb, 690, 320, 0);
		if (!bomba1) al_draw_bitmap(bomb, 720, 320, 0);
		if(!wyswietlnpc) al_draw_bitmap(npc_d, 640, 380, 0);
		if (!wyswietlnpc1) al_draw_bitmap(npc1_d, 670, 380, 0);
		if (!wyswietlnpc2) al_draw_bitmap(npc2_d, 700, 380, 0);
		if (!wyswietlnpc3) al_draw_bitmap(npc3_d, 730, 380, 0);
		if (!wyswietlnpc4) al_draw_bitmap(npc4_d, 760, 380, 0);


		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 100, 0));

		if (ktoraplansza == 1)
		{
			tworz_mape(ktoraplansza, mury, wspmur_x, wspmur_y);

		}


		if (ktoraplansza == 2)
		{
			tworz_mape(ktoraplansza, mury, wspmur_x, wspmur_y);
			
		}

		if (ktoraplansza == 3)
		{

			tworz_mape(ktoraplansza, mury, wspmur_x, wspmur_y);
		}

		if (ktoraplansza == 4)
		{
			tworz_mape(ktoraplansza, mury, wspmur_x, wspmur_y);
			
		}
	}
	break;
	}
	}

	al_destroy_bitmap(gracz);
	al_destroy_bitmap(przeciwnik);
	al_destroy_font(font14);
	al_destroy_display(okno);
	return 0;

}

void tworz_mape(int ktoraplansza,bool mury[20][15],int wspmur_x[20][15],int wspmur_y[20][15])
{
	switch (ktoraplansza)
	{
	case 1:
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				mury[i][j] = false;
			}

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				if (i == 0 || i == 19 || j == 0 || j == 14)
					mury[i][j] = true;
				else if (i % 2 != 0 && j % 2 != 0)
				{
					mury[i][j] = true;
					mury[5][4] = true;
					mury[6][4] = true;
					mury[6][3] = true;
					mury[16][5] = true;
					mury[16][7] = true;
					mury[17][6] = true;
					mury[17][4] = true;
					mury[15][10] = true;
					mury[14][5] = true;
					mury[11][4] = true;
					mury[10][5] = true;
					mury[12][3] = true;
					mury[9][2] = true;
					mury[5][12] = true;
					mury[6][8] = true;
					mury[5][8] = true;
					mury[9][12] = true;
					mury[9][10] = true;
					mury[7][8] = true;
					mury[1][13] = true;
					mury[2][11] = true;
					mury[2][7] = true;
					mury[8][1] = true;
					mury[12][1] = true;
					mury[10][11] = true;
					mury[16][13] = true;
					mury[12][13] = true;
					mury[18][11] = true;
					mury[16][11] = true;
					mury[9][13] = false;
					mury[17][8] = true;
					mury[17][9] = true;
					mury[13][10] = true;
					mury[11][8] = true;
					mury[14][10] = true;
					mury[12][8] = true;
					mury[11][8] = true;
					mury[11][8] = true;
					mury[11][8] = true;
					mury[11][8] = true;
					mury[17][11] = false;

				}
			}

		for (int k = 0; k < 20; k++)
			for (int l = 0; l < 15; l++)
			{
				wspmur_x[k][l] = 0;
				wspmur_y[k][l] = 0;
			}
		break;
	case 2:
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				mury[i][j] = false;
			}

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				if (i == 0 || i == 19 || j == 0 || j == 14)
					mury[i][j] = true;
				else if (i % 3 != 0 && j % 3 != 0)
				{
					mury[i][j] = true;
				}
				if (i % 2 != 0 && j % 2 != 0 && i != 19)
				{
					mury[i][j] = false;
					mury[2][2] = false;
					mury[1][2] = false;
					mury[4][2] = false;
					mury[4][4] = false;
					mury[8][1] = false;
					mury[10][1] = false;
					mury[16][1] = false;
					mury[14][1] = false;
					mury[15][2] = true;
					mury[1][10] = false;
					mury[1][8] = false;
					mury[8][13] = false;
					mury[9][13] = true;
					mury[2][9] = true;
					mury[3][3] = true;
					mury[1][3] = true;
					mury[6][6] = true;
					mury[12][6] = true;
					mury[5][12] = true;
					mury[7][12] = true;
					mury[12][12] = true;
					mury[18][6] = true;
					mury[18][12] = true;

				}
			}

		for (int k = 0; k < 20; k++)
			for (int l = 0; l < 15; l++)
			{
				wspmur_x[k][l] = 0;
				wspmur_y[k][l] = 0;
			}
		break;
	case 3:
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				mury[i][j] = false;
			}

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
				for (int k = 0; k < 8; k += 2)
				{
					if (i == 0 || i == 19 || j == 0 || j == 14)
						mury[i][j] = true;
					if (i == 2 + k || i == 17 - k || j == 2 + k || j == 12 - k)
					{
						mury[i][j] = true;
					}
					if (j % 2 == 1)
					{
						mury[8][j] = false;
						mury[11][j] = false;

					}
					mury[2][1] = false;
					mury[4][1] = false;
					mury[6][1] = false;
					mury[17][1] = false;
					mury[15][1] = false;
					mury[13][1] = false;
					mury[4][3] = false;
					mury[6][3] = false;
					mury[15][3] = false;
					mury[13][3] = false;
					mury[6][5] = false;
					mury[13][5] = false;
					mury[1][2] = false;
					mury[1][4] = false;
					mury[1][6] = false;
					mury[17][1] = false;
					mury[15][1] = false;
					mury[13][1] = false;
					mury[2][13] = false;
					mury[4][11] = false;
					mury[17][13] = false;
					mury[15][11] = false;
					mury[6][9] = false;
					mury[13][9] = false;
					mury[1][8] = false;
					mury[1][10] = false;
					mury[1][12] = false;
					mury[18][2] = false;
					mury[18][4] = false;
					mury[18][6] = false;
					mury[18][8] = false;
					mury[18][10] = false;
					mury[18][12] = false;
					mury[4][13] = false;
					mury[6][13] = false;
					mury[13][13] = false;
					mury[15][13] = false;
					mury[6][11] = false;
					mury[13][11] = false;
					mury[3][4] = false;
					mury[3][6] = false;
					mury[3][8] = false;
					mury[3][10] = false;
					mury[16][4] = false;
					mury[16][6] = false;
					mury[16][8] = false;
					mury[16][10] = false;
					mury[14][8] = false;
					mury[14][6] = false;
					mury[5][8] = false;
					mury[5][6] = false;
					mury[2][7] = false;
					mury[6][7] = false;
					mury[17][7] = false;
					mury[13][7] = false;
					mury[10][4] = false;
					mury[10][10] = false;
					mury[4][2] = false;
					mury[15][12] = false;
					mury[4][6] = false;
					mury[15][8] = false;
					mury[7][6] = false;
					mury[12][8] = false;
					mury[15][2] = false;
					mury[4][12] = false;

				} 

		for (int k = 0; k < 20; k++)
			for (int l = 0; l < 15; l++)
			{
				wspmur_x[k][l] = 0;
				wspmur_y[k][l] = 0;
			}
		break;
	case 4:
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				mury[i][j] = false;
			}

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 15; j++)
			{
				if (i == 0 || i == 19 || j == 0 || j == 14)
					mury[i][j] = true;
				if (i % 4 == 0 || j % 3 == 0)
					mury[i][j] = true;
				if (i % 2 != 0 && j % 2 != 1)
					mury[i][j] = true;
				if ((j == 3 || j == 9) && i != 0 && i != 19)
					mury[i][j] = false;

				mury[2][3] = false;
				mury[6][3] = false;
				mury[10][3] = false;
				mury[14][3] = false;
				mury[18][3] = false;
				mury[2][12] = false;
				mury[6][12] = false;
				mury[10][12] = false;
				mury[14][12] = false;
				mury[18][12] = false;
				mury[1][6] = false;
				mury[6][6] = false;
				mury[9][6] = false;
				mury[15][6] = false;
				mury[17][6] = false;
				mury[2][9] = false;
				mury[6][9] = false;
				mury[10][9] = false;
				mury[14][9] = false;
				mury[18][9] = false;
				mury[8][1] = false;
				mury[16][1] = false;
				mury[4][7] = false;
				mury[12][5] = false;
				mury[8][11] = false;
				mury[16][11] = false;
				mury[4][13] = false;
				mury[12][13] = false;

			} 

		for (int k = 0; k < 20; k++)
			for (int l = 0; l < 15; l++)
			{
				wspmur_x[k][l] = 0;
				wspmur_y[k][l] = 0;
			}
		break;
	}

}