#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "classes.h"

#define width 630
#define height 480
#define bpp 0

#define minwidth 630
#define minheight 480

#define maxwidth 1920
#define maxheight 1080

int screen_width = width;
int screen_height = height;

int swz, shz;

#define Tick 1000
#define CasSkoku 500

#define main_menu 0
#define main_hra 1
#define main_nova 2
#define main_nast 3
#define main_gameover 4

#define menu_dale 0
#define menu_start 1
#define menu_nast 2
#define menu_konec 3
#define menu_posledni 3

#define nast_prvni 0
#define nast_sirka 0
#define nast_vyska 1
#define nast_rychlost 2
#define nast_skakani 3
#define nast_riziko 4
#define nast_zpet 5
#define nast_posledni 5

#define text_start 0
#define text_Sstart 1
#define text_konec 2
#define text_Skonec 3
#define text_dale 4
#define text_Sdale 5
#define text_Idale 6
#define text_nast 7
#define text_Snast 8
#define menutextu 9

#define text_zpet 0
#define text_Szpet 1
#define text_vyska 2
#define text_Svyska 3
#define text_sirka 4
#define text_Ssirka 5
#define text_rychlost 6
#define text_Srychlost 7
#define text_skakani 8
#define text_Sskakani 9
#define text_riziko 10
#define text_Sriziko 11
#define nasttextu 12

SDL_Surface *screen = NULL;
SDL_Surface *sprity = NULL;
SDL_Surface *pozadi = NULL;
SDL_Surface *popredi = NULL;
SDL_Surface *menu_text[menutextu];
SDL_Surface *nast_text[nasttextu];
SDL_Surface *score_text;
SDL_Surface *gameover_text;

SDL_Event event;

TTF_Font *font = NULL;
SDL_Color text1 = {255,255,255};
SDL_Color text2 = {255,255,0};
SDL_Color text3 = {50,50,50};
SDL_Color text4 = {255,10,10};
SDL_Color bg = {0,0,0};

cTimer Timer;
cTimer Pomocny;

bool hopsani = false;
bool riziko = true;

cHad Had;

std::string str;
char c[25];

int Zradlo[2];

int rychlost = 10;
#define minrych 1
#define maxrych 20

int score = 0;

void GenerujZradlo()
{
	Zradlo[0] = rand()/(RAND_MAX/(screen_width/sprt_sirka));
	Zradlo[1] = rand()/(RAND_MAX/(screen_height/sprt_vyska));
}

bool init()
{
	printf("Inicializuji SDL ...");
	
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		printf("\n Nemohu inicializovat SDL: %s\n", SDL_GetError());
		return false;
	}
	
	if ( TTF_Init() == -1 )
	{
		printf("\n Nemohu inicializovat fonty: %s\n", TTF_GetError());
		return false;
	}
	
	screen = SDL_SetVideoMode(screen_width, screen_height, bpp, SDL_HWSURFACE);
	if ( screen == NULL )
	{
		printf("\n Nemohu nastavit obraz: %s\n", SDL_GetError());
		return false;
	}
	
	printf(" hotovo\n");
	
	printf("Nacitam data ...");
	sprity = LoadIMG("sprity.png");
	pozadi = LoadIMG("pozadi.png");
	popredi = LoadIMG("popredi.png");
	font = TTF_OpenFont("font.ttf",50);
	if (font == NULL)
	{
		printf("\n Chyba pri nacitani fontu: %s\n", TTF_GetError());
		return false;
	}
	printf(" hotovo\n");
	
	printf("Nastavuji zbytek ...");
	menu_text[text_start] = TTF_RenderUTF8_Shaded( font, "Rozehrát", text1, bg ); // ošetřit NULL
	menu_text[text_Sstart] = TTF_RenderUTF8_Shaded( font, "Rozehrát", text2, bg ); // ošetřit NULL
	menu_text[text_konec] = TTF_RenderUTF8_Shaded( font, "Konec", text1, bg ); // ošetřit NULL
	menu_text[text_Skonec] = TTF_RenderUTF8_Shaded( font, "Konec", text2, bg ); // ošetřit NULL
	menu_text[text_dale] = TTF_RenderUTF8_Shaded( font, "Pokračovat", text1, bg ); // ošetřit NULL
	menu_text[text_Sdale] = TTF_RenderUTF8_Shaded( font, "Pokračovat", text2, bg ); // ošetřit NULL
	menu_text[text_Idale] = TTF_RenderUTF8_Shaded( font, "Pokračovat", text3, bg ); // ošetřit NULL
	menu_text[text_nast] = TTF_RenderUTF8_Shaded( font, "Nastavení", text1, bg ); // ošetřit NULL
	menu_text[text_Snast] = TTF_RenderUTF8_Shaded( font, "Nastavení", text2, bg ); // ošetřit NULL
	
	nast_text[text_zpet] = TTF_RenderUTF8_Shaded( font, "Zpět", text1, bg ); // ošetřit NULL
	nast_text[text_Szpet] = TTF_RenderUTF8_Shaded( font, "Zpět", text2, bg ); // ošetřit NULL
	
	str.clear();
	sprintf(c,"Výška	%i",screen_height);
	str = c;
	
	nast_text[text_vyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
	nast_text[text_Svyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	
	str.clear();
	sprintf(c,"Šířka	%i",screen_width);
	str = c;
	
	nast_text[text_sirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
	nast_text[text_Ssirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	
	sprintf(c,"Rychlost	%i",rychlost);
	str = c;
	
	nast_text[text_rychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
	nast_text[text_Srychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	
	if ( hopsani ) sprintf(c,"Skákání	ON"); else sprintf(c,"Skákání	OFF");
	str = c;
	
	nast_text[text_skakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
	nast_text[text_Sskakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	
	if ( riziko ) sprintf(c,"Hra bez rizika	OFF"); else sprintf(c,"Hra bez rizika	ON");
	str = c;
	
	nast_text[text_riziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
	nast_text[text_Sriziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	
	sprintf(c,"%i",score);
	str = c;
	
	score_text = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
	SDL_SetColorKey( score_text, SDL_SRCCOLORKEY, 0 );
	
	gameover_text = TTF_RenderUTF8_Shaded( font, " - KONČÍŠ - ", text4, bg ); // ošetřit NULL
	SDL_SetColorKey( gameover_text, SDL_SRCCOLORKEY, 0 );
	
	Had.Init();
	
	SDL_WM_SetCaption("Had",NULL);
	srand(time(0));
	printf(" hotovo\n");
	
	return true;
}

void final()
{
	int i;
	
	printf("Ukoncuji ...");
	
	SDL_FreeSurface(sprity);
	SDL_FreeSurface(pozadi);
	SDL_FreeSurface(popredi);
	
	for (i=0;i<menutextu;i++) SDL_FreeSurface(menu_text[i]);
	for (i=0;i<nasttextu;i++) SDL_FreeSurface(nast_text[i]);
	
	SDL_FreeSurface(score_text);
	SDL_FreeSurface(gameover_text);
	
	Had.Zrus();
	
	TTF_CloseFont(font);
	TTF_Quit();
	
	SDL_Quit();
	printf(" hotovo\n");
}

int main(int argc, char **argv)
{	
	if ( !init() ) return 1;
	
	bool cycling = true;
	bool go;
	int SmerHada;
	int status = main_menu;
	int menu_select = menu_start;
	int nast_select = nast_zpet;
	bool zacnuto = false;
	
	int prvni;
	
	while ( cycling )
	{
		switch ( status ) {
			case main_menu:
				if ( zacnuto ) prvni = menu_dale; else prvni = menu_start;
				while ( SDL_PollEvent(&event) )
				{
					switch ( event.type ) {
						case SDL_KEYDOWN:
							switch ( event.key.keysym.sym )	{
								case SDLK_UP:
									menu_select--;
									if ( menu_select < prvni ) menu_select = menu_posledni;
									break;
								case SDLK_DOWN:
									menu_select++;
									if ( menu_select > menu_posledni ) menu_select = prvni;
									break;
								case SDLK_RETURN:
									switch ( menu_select ) {
										case menu_start:
											status = main_nova;
											break;
										case menu_konec:
											cycling = false;
											break;
										case menu_dale:
											status = main_hra;
											break;
										case menu_nast:
											shz = screen_height;
											swz = screen_width;
											status = main_nast;
											break;
									}
									break;
							}
							break;				
						case SDL_QUIT:
							cycling = false;
					}
				}
				
				SDL_FillRect(screen,NULL,0);
				switch ( menu_select ) {
					case menu_start:
						if ( zacnuto ) BlitScreen(menu_text[text_dale], screen, screen_width/3, 50); else BlitScreen(menu_text[text_Idale], screen, screen_width/3, 50);
						BlitScreen(menu_text[text_Sstart], screen, screen_width/3, 100);
						BlitScreen(menu_text[text_nast], screen, screen_width/3, 150);
						BlitScreen(menu_text[text_konec], screen, screen_width/3, 200);
						break;
					case menu_konec:
						if ( zacnuto ) BlitScreen(menu_text[text_dale], screen, screen_width/3, 50); else BlitScreen(menu_text[text_Idale], screen, screen_width/3, 50);
						BlitScreen(menu_text[text_start], screen, screen_width/3, 100);
						BlitScreen(menu_text[text_nast], screen, screen_width/3, 150);
						BlitScreen(menu_text[text_Skonec], screen, screen_width/3, 200);
						break;
					case menu_dale:
						BlitScreen(menu_text[text_Sdale], screen, screen_width/3, 50);
						BlitScreen(menu_text[text_start], screen, screen_width/3, 100);
						BlitScreen(menu_text[text_nast], screen, screen_width/3, 150);
						BlitScreen(menu_text[text_konec], screen, screen_width/3, 200);
						break;
					case menu_nast:
						if ( zacnuto ) BlitScreen(menu_text[text_dale], screen, screen_width/3, 50); else BlitScreen(menu_text[text_Idale], screen, screen_width/3, 50);
						BlitScreen(menu_text[text_start], screen, screen_width/3, 100);
						BlitScreen(menu_text[text_Snast], screen, screen_width/3, 150);
						BlitScreen(menu_text[text_konec], screen, screen_width/3, 200);
						break;
				}
				SDL_Flip(screen);
				
				break;
			case main_hra:
				Timer.Start();
				
				while ( SDL_PollEvent(&event) )
				{
					switch ( event.type ) {
						case SDL_KEYDOWN:
							switch ( event.key.keysym.sym )	{
								case SDLK_ESCAPE:
									menu_select = menu_dale;
									status = main_menu;
									break;
								case SDLK_UP:
									SmerHada = had_nahoru;
									break;
								case SDLK_DOWN:
									SmerHada = had_dolu;
									break;
								case SDLK_LEFT:
									SmerHada = had_vlevo;
									break;
								case SDLK_RIGHT:
									SmerHada = had_vpravo;
									break;
								case SDLK_SPACE:
									if ( hopsani ) if ( !Pomocny.Counting() )
									{
										Had.Skace(true);
										Had.NastavSebekolizi(false);
										Pomocny.Start();
									}
							}
							break;				
						case SDL_QUIT:
							cycling = false;
					}
				}
				
				if ( Pomocny.Counting() && Pomocny.GetTicks() >= CasSkoku )
				{
					Had.Skace(false);
					Had.NastavSebekolizi(true);
					Pomocny.Stop();
				}
		
				if ( !Had.ZmenaSmeru(SmerHada) ) SmerHada = Had.dejSmer(0);
		
				switch ( Had.Posun(Zradlo[0],Zradlo[1]) ) {
					case had_stav_zere:
						score += rychlost;
						sprintf(c,"%i",score);
						str = c;
						SDL_FreeSurface(score_text);	
						score_text = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg );
						SDL_SetColorKey( score_text, SDL_SRCCOLORKEY, 0 );
						GenerujZradlo();
						break;
					case had_stav_kolize:
						if ( riziko ) status = main_gameover;
						break;
				}
		
				BlitScreen(pozadi, screen, 0, 0);
				BlitScreen(score_text, screen, 10, 10);
				BlitScreenRect(sprity, sprt_zradlo, screen, sprt_sirka*Zradlo[0], sprt_vyska*Zradlo[1]);
				
				Had.Vykresli(sprity, screen);
				
				BlitScreen(popredi, screen, 0, 0);
				SDL_Flip(screen);
		
				while (Timer.GetTicks() < Tick/rychlost) {}
				break;
			case main_nova:
				score = 0;
				Had.Vytvor(5);
				Had.Pocatecni(screen_width/(2*sprt_sirka)-1, screen_height/(2*sprt_vyska)-1, had_vlevo);
				Had.Plocha(screen_width/sprt_sirka-1, screen_height/sprt_vyska-1);
				Had.NastavSebekolizi(true);
				SmerHada = Had.dejSmer(0);
				zacnuto = true;
				status = main_hra;
				break;
			case main_nast:
				while ( SDL_PollEvent(&event) )
				{
					switch ( event.type ) {
						case SDL_KEYDOWN:
							switch ( event.key.keysym.sym )	{
								case SDLK_ESCAPE:
									status = main_menu;
									break;
								case SDLK_UP:
									nast_select--;
									if ( nast_select < nast_prvni ) nast_select = nast_posledni;
									break;
								case SDLK_DOWN:
									nast_select++;
									if ( nast_select > nast_posledni ) nast_select = nast_prvni;
									break;
								case SDLK_RETURN:
									switch ( nast_select ) {
										case nast_riziko:
											if ( riziko )
											{
												sprintf(c,"Hra bez rizika	ON");
												riziko = false;
											} else {
												sprintf(c,"Hra bez rizika	OFF");
												riziko = true;
											}
											str = c;
	
											nast_text[text_riziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sriziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_skakani:
											if ( hopsani )
											{
												sprintf(c,"Skákání	OFF");
												hopsani = false;
											} else {
												sprintf(c,"Skákání	ON");
												hopsani = true;
											}
											str = c;
	
											nast_text[text_skakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sskakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_zpet:
											status = main_menu;
											break;
										case nast_vyska:
										case nast_sirka:
											if ( shz != screen_height || swz != screen_width)
											{
												final();
												screen_width = swz;
												screen_height = shz;
												if ( !init() ) return 1;
												zacnuto = false;
											}
											break;
									}
									break;
								case SDLK_LEFT:
									switch ( nast_select ) {
										case nast_riziko:
											if ( riziko )
											{
												sprintf(c,"Hra bez rizika	ON");
												riziko = false;
											} else {
												sprintf(c,"Hra bez rizika	OFF");
												riziko = true;
											}
											str = c;
	
											nast_text[text_riziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sriziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_skakani:
											if ( hopsani )
											{
												sprintf(c,"Skákání	OFF");
												hopsani = false;
											} else {
												sprintf(c,"Skákání	ON");
												hopsani = true;
											}
											str = c;
	
											nast_text[text_skakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sskakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_rychlost:
											rychlost--;
											
											if ( rychlost < minrych) rychlost = minrych;
											
											str.clear();
											sprintf(c,"Rychlost	%i",rychlost);
											str = c;
	
											SDL_FreeSurface(nast_text[text_rychlost]);
											SDL_FreeSurface(nast_text[text_Srychlost]);
											
											nast_text[text_rychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Srychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_vyska:
											shz -= 10;
											
											if ( shz < minheight ) shz = minheight;
											
											str.clear();
											sprintf(c,"Výška	%i",shz);
											str = c;
											
											SDL_FreeSurface(nast_text[text_vyska]);
											SDL_FreeSurface(nast_text[text_Svyska]);
	
											nast_text[text_vyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Svyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL											
											break;
										case nast_sirka:
											swz -= 10;
											
											if ( swz < minwidth ) swz = minwidth;
											
											str.clear();
											sprintf(c,"Šířka	%i",swz);
											str = c;
											
											SDL_FreeSurface(nast_text[text_sirka]);
											SDL_FreeSurface(nast_text[text_Ssirka]);
	
											nast_text[text_sirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Ssirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL											
											break;
									}
									break;
								case SDLK_RIGHT:
									switch ( nast_select ) {
										case nast_riziko:
											if ( riziko )
											{
												sprintf(c,"Hra bez rizika	ON");
												riziko = false;
											} else {
												sprintf(c,"Hra bez rizika	OFF");
												riziko = true;
											}
											str = c;
	
											nast_text[text_riziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sriziko] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_skakani:
											if ( hopsani )
											{
												sprintf(c,"Skákání	OFF");
												hopsani = false;
											} else {
												sprintf(c,"Skákání	ON");
												hopsani = true;
											}
											str = c;
	
											nast_text[text_skakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Sskakani] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_rychlost:
											rychlost++;
											
											if ( rychlost > maxrych) rychlost = maxrych;
											
											str.clear();
											sprintf(c,"Rychlost	%i",rychlost);
											str = c;
											
											SDL_FreeSurface(nast_text[text_rychlost]);
											SDL_FreeSurface(nast_text[text_Srychlost]);
	
											nast_text[text_rychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Srychlost] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL
											break;
										case nast_vyska:
											shz += 10;
											
											if ( shz > maxheight ) shz = maxheight;
											
											str.clear();
											sprintf(c,"Výška	%i",shz);
											str = c;
											
											SDL_FreeSurface(nast_text[text_vyska]);
											SDL_FreeSurface(nast_text[text_Svyska]);
	
											nast_text[text_vyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Svyska] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL											
											break;
										case nast_sirka:
											swz += 10;
											
											if ( swz > maxwidth ) swz = maxwidth;
											
											str.clear();
											sprintf(c,"Šířka	%i",swz);
											str = c;
											
											SDL_FreeSurface(nast_text[text_sirka]);
											SDL_FreeSurface(nast_text[text_Ssirka]);
	
											nast_text[text_sirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text1, bg ); // ošetřit NULL
											nast_text[text_Ssirka] = TTF_RenderUTF8_Shaded( font, str.c_str(), text2, bg ); // ošetřit NULL											
											break;
									}
									break;
							}
							break;				
						case SDL_QUIT:
							cycling = false;
					}
				}
				
				SDL_FillRect(screen,NULL,0);
				switch ( nast_select ) {
					case nast_zpet:
						BlitScreen(nast_text[text_sirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_vyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_rychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_skakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_riziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_Szpet], screen, screen_width/3, 350);
						break;
					case nast_sirka:
						BlitScreen(nast_text[text_Ssirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_vyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_rychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_skakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_riziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_zpet], screen, screen_width/3, 350);
						break;
					case nast_vyska:
						BlitScreen(nast_text[text_sirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_Svyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_rychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_skakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_riziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_zpet], screen, screen_width/3, 350);
						break;
					case nast_rychlost:
						BlitScreen(nast_text[text_sirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_vyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_Srychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_skakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_riziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_zpet], screen, screen_width/3, 350);
						break;
					case nast_skakani:
						BlitScreen(nast_text[text_sirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_vyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_rychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_Sskakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_riziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_zpet], screen, screen_width/3, 350);
						break;
					case nast_riziko:
						BlitScreen(nast_text[text_sirka], screen, screen_width/3, 50);
						BlitScreen(nast_text[text_vyska], screen, screen_width/3, 100);
						BlitScreen(nast_text[text_rychlost], screen, screen_width/3, 150);
						BlitScreen(nast_text[text_skakani], screen, screen_width/3, 200);
						BlitScreen(nast_text[text_Sriziko], screen, screen_width/3, 250);
						BlitScreen(nast_text[text_zpet], screen, screen_width/3, 350);
						break;
				}
				SDL_Flip(screen);

				break;
			case main_gameover:
				go = true;
				zacnuto = false;
				BlitScreen(gameover_text, screen, screen_width/3, screen_height/2);
				SDL_Flip(screen);
				
				while ( go ) while ( SDL_PollEvent(&event) ) switch ( event.type ) {
					case SDL_KEYDOWN:
						switch ( event.key.keysym.sym )	{
							case SDLK_ESCAPE:
								go = false;
								break;
						}
						break;
					case SDL_QUIT:
						cycling = false;
						go = false;
						break;
				}
				
				status = main_menu;
				break;
		}
	}
	
	final();
	
	return 0;
}
