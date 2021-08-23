#include <iostream>
#include<chrono>
#include "Game.h"
#include "SDL.h"
#include <sstream>
#include <string.h>
using namespace std;


Game* game = nullptr;		//empties the definition of the class
auto(tp1) = chrono::system_clock::now();		//gets current system time
auto(tp2) = chrono::system_clock::now();
int screenwidth = 1300;				//specify your screen resolution here
int screenheight = 700;				//note: this will not be taken into account if you chose to go in fullscreen
int full;
int test;
float tickspeed = 1;

int main(int argc, const char* argv[]) {
	cout << "fullscreen?" << endl;
	cin >> full;
	game = new Game();
	tp1 = chrono::system_clock::now();
	tp2 = chrono::system_clock::now();
	if (full == 1) { game->init("made by clemdemort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth, screenheight, true); }
	if (full == 0) { game->init("made by clemdemort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth, screenheight, false); }
	if (game->isfullscreen == true) {
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		screenwidth = DM.w;
		screenheight = DM.h;
	}

	game->load(screenwidth, screenheight);
	while (game->running()) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float timer = elapsedTime.count();
		game->handlEvents(timer);
		game->update(timer, screenwidth, screenheight);
		game->render(screenwidth, screenheight);
	}
	game->clean();		//cleans stuff
	return 0;
}
