#ifndef Game_h
#define Game_h


#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>


constexpr auto mapwidth = 1000;
constexpr auto mapheight = 1000;
constexpr auto mapdepth = 300;

class Game {

public:
	Game();
	~Game();
	double pi = 3.14159265358979323846;
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool isfullscreen;
	void handlEvents(float timer);
	void update(float timer, int screenX, int screenY);
	void load(int screenX, int screenY);
	void render(int screenX, int screenY);
	void clean();
	bool running() { return isRunning; }
	void rect(int Xpos, int Ypos, int sizeX, int sizeY, int R, int G, int B, int A);
	void pixel(int Xpos, int Ypos, int R, int G, int B, int A);
	void line(int X1, int Y1,int X2,int Y2, int R, int G, int B, int A);
	void raycast(int FOVX, int FOVY, int screenX,int screenY,float pisizeX, float pisizeY,int dist,int mapsize);
	float square(float number);
	int map[mapwidth][mapheight][4];
	float playerX= 0;
	float playerY= 0;
	float playerZ= 20;
	float playerRX;
	float playerRY;
	int speed;




private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	long cnt = 0;

};


#endif
