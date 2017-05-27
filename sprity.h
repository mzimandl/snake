#define sprt_vyska 30
#define sprt_sirka 30

const SDL_Rect sprt_hlava_u = {0, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_r = {0, sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_d = {0, 2*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_l = {0, 3*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_hlava_skok_u = {0, 5*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_skok_r = {sprt_sirka, 5*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_skok_d = {2*sprt_sirka, 5*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_hlava_skok_l = {3*sprt_sirka, 5*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_zadek_d = {sprt_sirka, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadek_l = {sprt_sirka, sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadek_u = {sprt_sirka, 2*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadek_r = {sprt_sirka, 3*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_zadekT_d = {0, 4*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadekT_l = {sprt_sirka, 4*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadekT_u = {2*sprt_sirka, 4*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zadekT_r = {3*sprt_sirka, 4*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_lomT_dl = {2*sprt_sirka, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lomT_lu = {2*sprt_sirka, sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lomT_ur = {2*sprt_sirka, 2*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lomT_rd = {2*sprt_sirka, 3*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_lom_dl = {3*sprt_sirka, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lom_lu = {3*sprt_sirka, sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lom_ur = {3*sprt_sirka, 2*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_lom_rd = {3*sprt_sirka, 3*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_telo_v = {4*sprt_sirka, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_teloT_v = {4*sprt_sirka, sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_telo_h = {4*sprt_sirka, 2*sprt_vyska, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_teloT_h = {4*sprt_sirka, 3*sprt_vyska, sprt_sirka, sprt_vyska};

const SDL_Rect sprt_zradlo = {5*sprt_sirka, 0, sprt_sirka, sprt_vyska};
const SDL_Rect sprt_zed = {5*sprt_sirka, sprt_vyska, sprt_sirka, sprt_vyska};
