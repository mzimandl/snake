#include "functions.h"
#include "sprity.h"

class cTimer
{
	private:
		int StartTicks;
		bool Running;
	public:
		void Reset();
		
		void Start();
		void Stop();
		
		int GetTicks();
		bool Counting();
};

void cTimer::Reset() //asi ani nemusi byt
{
	StartTicks = 0;
	Running = false;
}

void cTimer::Start()
{
	StartTicks = SDL_GetTicks();
	Running = true;
}

void cTimer::Stop()
{
	Running = false;
}

int cTimer::GetTicks()
{
	return SDL_GetTicks() - StartTicks;
}

bool cTimer::Counting()
{
	return Running;
}

//------------------------------------------------

#define had_nahoru 1
#define had_dolu 2
#define had_vlevo 3
#define had_vpravo 4

#define had_stav_nic 0
#define had_stav_zere 1
#define had_stav_kolize 2

class cHad
{
	private:		
		int plochax;
		int plochay;
		
		int *smer_clanku;
		bool sebekolize;
		bool skok;
		bool je;
		
		bool Kolize(int smer);
		void Prodluz(void);
	public:
		int *px;
		int *py;
		bool *nazrany;
		
		int delka;
		
		void Vytvor(int clanku);
		void Zrus(void);
		void Pocatecni(int x, int y, int kam);
		bool ZmenaSmeru(int kam);
		void Plocha(int x, int y);
		int Posun(int x, int y);
		
		int dejSmer(int i);
		void NastavSebekolizi(bool a);
		
		void Skace(bool stav);
		bool VeSkoku(void);
		
		bool Init(void);
		
		void Vykresli(SDL_Surface *sprity, SDL_Surface *surface);
};

void cHad::Vykresli(SDL_Surface *sprity, SDL_Surface *surface)
{
	int i;
	
	i = delka - 1;	// vykresleni zadku
	switch ( nazrany[i] ) {
		case true:
			switch ( smer_clanku[i] ) {
				case had_nahoru:
					BlitScreenRect(sprity, sprt_zadekT_d, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_dolu:
					BlitScreenRect(sprity, sprt_zadekT_u, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_vlevo:
					BlitScreenRect(sprity, sprt_zadekT_r, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_vpravo:
					BlitScreenRect(sprity, sprt_zadekT_l, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
			}
			break;
		case false:
			switch ( smer_clanku[i] ) {
				case had_nahoru:
					BlitScreenRect(sprity, sprt_zadek_d, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_dolu:
					BlitScreenRect(sprity, sprt_zadek_u, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_vlevo:
					BlitScreenRect(sprity, sprt_zadek_r, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					break;
				case had_vpravo:
					BlitScreenRect(sprity, sprt_zadek_l, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
			}
	}
	
	for (i=delka-2;i>0;i--) switch ( nazrany[i] ) {		// vykresleni tela
		case true:
			switch ( smer_clanku[i] ) {
				case had_nahoru:
					switch ( smer_clanku[i+1] ) {
						case had_vlevo:
							BlitScreenRect(sprity, sprt_lomT_ur, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_vpravo:
							BlitScreenRect(sprity, sprt_lomT_lu, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_teloT_v, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_dolu:
					switch ( smer_clanku[i+1] ) {
						case had_vlevo:
							BlitScreenRect(sprity, sprt_lomT_rd, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_vpravo:
							BlitScreenRect(sprity, sprt_lomT_dl, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_teloT_v, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_vlevo:
					switch ( smer_clanku[i+1] ) {
						case had_nahoru:
							BlitScreenRect(sprity, sprt_lomT_dl, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_dolu:
							BlitScreenRect(sprity, sprt_lomT_lu, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_teloT_h, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_vpravo:
					switch ( smer_clanku[i+1] ) {
						case had_nahoru:
							BlitScreenRect(sprity, sprt_lomT_rd, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_dolu:
							BlitScreenRect(sprity, sprt_lomT_ur, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_teloT_h, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
			}
			break;
		case false:
			switch ( smer_clanku[i] ) {
				case had_nahoru:
					switch ( smer_clanku[i+1] ) {
						case had_vlevo:
							BlitScreenRect(sprity, sprt_lom_ur, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_vpravo:
							BlitScreenRect(sprity, sprt_lom_lu, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_telo_v, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_dolu:
					switch ( smer_clanku[i+1] ) {
						case had_vlevo:
							BlitScreenRect(sprity, sprt_lom_rd, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_vpravo:
							BlitScreenRect(sprity, sprt_lom_dl, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_telo_v, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_vlevo:
					switch ( smer_clanku[i+1] ) {
						case had_nahoru:
							BlitScreenRect(sprity, sprt_lom_dl, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_dolu:
							BlitScreenRect(sprity, sprt_lom_lu, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_telo_h, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
					break;
				case had_vpravo:
					switch ( smer_clanku[i+1] ) {
						case had_nahoru:
							BlitScreenRect(sprity, sprt_lom_rd, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						case had_dolu:
							BlitScreenRect(sprity, sprt_lom_ur, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
							break;
						default:
							BlitScreenRect(sprity, sprt_telo_h, surface, sprt_sirka*px[i], sprt_vyska*py[i]);
					}
			}
	}

	switch ( skok ) {	// vykresleni hlavy
		case true:
			switch ( smer_clanku[0] ) {
				case had_nahoru:
					BlitScreenRect(sprity, sprt_hlava_skok_u, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_dolu:
					BlitScreenRect(sprity, sprt_hlava_skok_d, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_vlevo:
					BlitScreenRect(sprity, sprt_hlava_skok_l, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_vpravo:
					BlitScreenRect(sprity, sprt_hlava_skok_r, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
			}
			break;
		case false:
			switch ( smer_clanku[0] ) {
				case had_nahoru:
					BlitScreenRect(sprity, sprt_hlava_u, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_dolu:
					BlitScreenRect(sprity, sprt_hlava_d, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_vlevo:
					BlitScreenRect(sprity, sprt_hlava_l, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
				case had_vpravo:
					BlitScreenRect(sprity, sprt_hlava_r, surface, sprt_sirka*px[0], sprt_vyska*py[0]);
					break;
			}
	}
}

bool cHad::Init(void)
{
	je = false;
	
	return true;
}

bool cHad::VeSkoku(void)
{
	return skok;
}

void cHad::Skace(bool stav)
{
	skok = stav;
}

void cHad::NastavSebekolizi(bool stav)
{
	sebekolize = stav;
}

bool cHad::Kolize(int smer)
{
	int i;
	
	if ( sebekolize )
	{
		for (i=1;i<delka-2;i++) switch ( smer ) {
			case had_nahoru:
				if ( ((py[0]>0 && py[0]-1 == py[i]) || (py[0]==0 && plochay == py[i])) && (px[0] == px[i]) ) return true;
				break;
			case had_dolu:
				if ( ((py[0]<plochay && py[0]+1 == py[i]) || (py[0]==plochay && 0 == py[i])) && (px[0] == px[i]) ) return true;
				break;
			case had_vlevo:
				if ( ((px[0]>0 && px[0]-1 == px[i]) || (px[0]==0 && plochax == px[i])) && (py[0] == py[i]) ) return true;
				break;
			case had_vpravo:
				if ( ((px[0]<plochax && px[0]+1 == px[i]) || (px[0]==plochax && 0 == px[i])) && (py[0] == py[i]) ) return true;
				break;
		}
		
		switch ( smer ) {
			case had_nahoru:
				if ( ((py[0]>0 && py[0]-1 == py[delka-1]) || (py[0]==0 && plochay == py[delka-1])) && (nazrany[delka-1]) && (px[0] == px[delka-1]) ) return true;
				break;
			case had_dolu:
				if ( ((py[0]<plochay && py[0]+1 == py[delka-1]) || (py[0]==plochay && 0 == py[delka-1])) && (nazrany[delka-1]) && (px[0] == px[delka-1]) ) return true;
				break;
			case had_vlevo:
				if ( ((px[0]>0 && px[0]-1 == px[delka-1]) || (px[0]==0 && plochax == px[delka-1])) && (nazrany[delka-1]) && (py[0] == py[delka-1]) ) return true;
				break;
			case had_vpravo:
				if ( ((px[0]<plochax && px[0]+1 == px[delka-1]) || (px[0]==plochax && 0 == px[delka-1])) && (nazrany[delka-1]) && (py[0] == py[delka-1]) ) return true;
				break;
		}
	}
	
	return false;
}

int cHad::dejSmer(int i)
{
	return smer_clanku[i];
}

void cHad::Plocha(int x, int y)
{
	plochax = x;
	plochay = y;
}

void cHad::Vytvor(int clanku)
{
	if ( je ) Zrus();
	
	px = new int[clanku];
	py = new int[clanku];
	
	smer_clanku = new int[clanku];
	
	nazrany = new bool[clanku];
	
	delka = clanku;
	
	je = true;
}

void cHad::Prodluz(void)
{	
	int *novy;
	bool *nakrmeny;
	
	novy = new int[delka+1];
	memcpy(novy,px,sizeof(int)*delka);
	delete px;
	px = novy;
	
	novy = new int[delka+1];
	memcpy(novy,py,sizeof(int)*delka);
	delete py;
	py = novy;
	
	novy = new int[delka+1];
	memcpy(novy,smer_clanku,sizeof(int)*delka);
	delete smer_clanku;
	smer_clanku = novy;
		
	nakrmeny = new bool[delka+1];
	memcpy(nakrmeny,nazrany,sizeof(bool)*delka);
	delete nazrany;
	nazrany = nakrmeny;
	
	delka++;
}

void cHad::Zrus(void)
{	
	delete px;
	delete py;
	
	delete smer_clanku;
	
	delete nazrany;
	
	je = false;
	
	delka = 0;
}

void cHad::Pocatecni(int x, int y, int kam)
{
	int i;
	
	px[0] = x;
	py[0] = y;
	
	for (i=0;i<delka;i++)
	{
		nazrany[i] = false;
		smer_clanku[i] = kam;
	}
	
	for (i=1;i<delka;i++)
	{
		switch ( kam )
		{
			case had_nahoru:
				px[i] = px[i-1];
				py[i] = py[i-1] + 1;
				break;
			case had_dolu:
				px[i] = px[i-1];
				py[i] = py[i-1] - 1;
				break;
			case had_vlevo:
				px[i] = px[i-1] + 1;
				py[i] = py[i-1];
				break;
			case had_vpravo:
				px[i] = px[i-1] - 1;
				py[i] = py[i-1];
				break;
		}
	}
}

bool cHad::ZmenaSmeru(int kam)
{
	if ( smer_clanku[0]+kam != had_nahoru+had_dolu && smer_clanku[0]+kam != had_vlevo+had_vpravo && !Kolize(kam) && !skok )
	{
		smer_clanku[0] = kam;
		return true;
	} else return false;
}

int cHad::Posun(int x, int y)
{
	int i;
	int a;
	
	if ( Kolize(smer_clanku[0]) ) return had_stav_kolize;
	
	a = delka-1;
	if ( nazrany[delka-1] )
	{
		Prodluz();	
		nazrany[delka-1] = false;
		px[delka-1] = px[a];
		py[delka-1] = py[a];
		smer_clanku[delka-1] = smer_clanku[a];
	}
	
	for (i=a;i>0;i--)
	{
		nazrany[i] = nazrany[i-1];
		px[i] = px[i-1];
		py[i] = py[i-1];
		smer_clanku[i] = smer_clanku[i-1];
	}
	
	switch ( smer_clanku[0] )
	{
		case had_nahoru:
			py[0]--;
			break;
		case had_dolu:
			py[0]++;
			break;
		case had_vlevo:
			px[0]--;
			break;
		case had_vpravo:
			px[0]++;
			break;
	}
	
	if ( px[0] > plochax ) px[0]=0;
	else if ( px[0] < 0 ) px[0]=plochax;
	
	if ( py[0] > plochay ) py[0]=0;
	else if ( py[0] < 0 ) py[0]=plochay;
	
	if (px[0] == x && py[0] == y && !skok)
	{
		nazrany[0] = true;
		return had_stav_zere;
	} else {
		nazrany[0] = false;
		return had_stav_nic;
	}
}
