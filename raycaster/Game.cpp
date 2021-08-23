#include "Game.h"
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
int mouseX, mouseY;
bool Mouse;
float timer2 = -4;



Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
		isfullscreen = true;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "subsystems inititalised" << std::endl;
		if (fullscreen)
		{
			SDL_DisplayMode DM;
			SDL_GetCurrentDisplayMode(0, &DM);
			auto widthF = DM.w;
			auto heightF = DM.h;
			

			window = SDL_CreateWindow(title, xpos, ypos, widthF, heightF, flags);
		}
		if (!fullscreen)
		{
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			isfullscreen = false;
		}
		if (window) {
			std::cout << "window created" << std::endl;

		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //SDL_RENDERER_ACCELERATED //SDL_RENDERER_SOFTWARE
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}

		isRunning = true;
	}
	else { isRunning = false; }

}


void Game::handlEvents(float timer)				//events as in user input
{
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) { isRunning = false; }		//for events like clicking the exit button on the window
	}

	//basic user input if escape is pressed then the application will close
	if (keystates[SDL_SCANCODE_ESCAPE]) {

		isRunning = false;
	}

	if (keystates[SDL_SCANCODE_W]) {
		playerX += cos(playerRX) * speed *timer;
		playerY -= sin(playerRX) * speed *timer;
	}
	if (keystates[SDL_SCANCODE_S]) {
		playerX -= cos(playerRX) * speed * timer;
		playerY += sin(playerRX) * speed * timer;
	}
	if (keystates[SDL_SCANCODE_A]) { playerRX -= 1 * timer; }
	if (keystates[SDL_SCANCODE_D]) { playerRX += 1 * timer; }

	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);
	//if left click then mouse = true
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		Mouse = true;
	}
	if ((buttons & SDL_BUTTON_LMASK) == 0) {
		Mouse = false;
	}
}

// this is the load function, it is only executed once at the start of the application
void Game::load(int screenX, int screenY) {
	srand((unsigned int)time(NULL));
	int r;
	for (int i = 0; i <= mapwidth - 1; i++)
		for (int j = 0; j <= mapheight - 1; j++)
		{
			r = rand() % 3;
			if (r == 0) {
				map[i][j][0] = 255;
				map[i][j][1] = 255;
				map[i][j][2] = 255;
				map[i][j][3] = 0;
			}
			if (r == 1) {
				map[i][j][0] = rand() % 256;
				map[i][j][1] = rand() % 256;
				map[i][j][2] = rand() % 256;
				map[i][j][3] = 1;
			}
			if (r == 2) {
				map[i][j][0] = 255;
				map[i][j][1] = 255;
				map[i][j][2] = 255;
				map[i][j][3] = 0;
			}
		}
	cout << "everything works!" << endl;
}

//this is the update function, it will repeat as fast as it can for as long as the application is running
void Game::update(float timer, int screenX, int screenY) {
	//gets the mouse position
	SDL_GetMouseState(&mouseX, &mouseY);
	timer2 += timer;
	if (timer2 >= 0.25) {
		int fps = 1 / timer;
		stringstream ss;
		ss << fps;
		string temp = ss.str();
		string temp2 = "Raycaster -FPS:" + temp;
		char* FPS = (char*)temp2.c_str();
		SDL_SetWindowTitle(window, FPS);
		timer2 = 0;

	}

	if (Mouse == true) {speed = 200;}
	if (Mouse == false) {speed = 10;}
}

//this is the render function, like update it is called every frame to render things on the screen
void Game::render(int screenX,int screenY)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);			//prepares buffer to draw in white
	SDL_RenderClear(renderer);										//buffer is reset this will clear everything with the color specified above
	
	//anything you want to render goes in between here ----------------------------------------------------------
	//for(int i = 0; i < mapwidth; i++)
	//	for(int j = 0; j < mapheight; j++)
	//		if(map[i][j][3] == 1){ rect(i*20, j*20, 20, 20, map[i][j][0], map[i][j][1], map[i][j][2], 255); }

	//rect(playerX,playerY, 5, 5, 255, 0, 0, 255);
	raycast(70,1,screenX,screenY,1,5,500,2);

	rect(mouseX-1.25 , mouseY-1.25,5,5, 0, 0, 0, 255);
	//and here --------------------------------------------------------------------------------------------------

	SDL_RenderPresent(renderer);			//render what you asked it to
}

void Game::clean()
{	
	//destroys the windows and renderers you created then ends SDL's script
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "cleaner: everything is cleaned up!" << std::endl;
}

//just a basic function to draw a rectangle
void Game::rect(int Xpos, int Ypos, int sizeX, int sizeY, int R, int G, int B, int A)
{
	
	SDL_Rect r;
	r.x = Xpos;
	r.y = Ypos;
	r.w = sizeX;
	r.h = sizeY;
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
	SDL_RenderFillRect(renderer, &r);
}
//just a basic function to draw a pixel
void Game::pixel(int Xpos, int Ypos, int R, int G, int B, int A)
{
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
	SDL_RenderDrawPoint(renderer, Xpos, Ypos);
}
void Game::line(int X1, int Y1, int X2, int Y2, int R, int G, int B, int A)
{
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
	SDL_RenderDrawLine(renderer, X1, Y1, X2, Y2);
}

void Game::raycast(int FOVX, int FOVY, int screenX, int screenY, float pisizeX, float pisizeY, int dist,int mapsize)
{
		int X = (screenX / pisizeX);
		int Y = (screenY / pisizeY);
		float angleX = FOVX * pi / 180;
		float StepX = angleX / X; // step of the ray in X dimension
		float angleY = FOVY * pi / 180;
		float StepY = angleY / Y; // step of the ray in Y dimension
		int tx = -1;
		int ty{};

		for (float i = playerRX - (angleX / 2); i <= playerRX + (angleX / 2); i += StepX) //playerRX is the rotation of the camera in the 2D space
		{
			tx++;
			bool touched = false;

			float dirX = (cos(i));
			float dirY = (-sin(i));

			int dirSignX = (dirX > 0) - (dirX < 0);
			int dirSignY = (dirY > 0) - (dirY < 0);

			// is 1 if dirSign is positive and 0 if it's 0 OR negative
			int dirPositivityX = (1 + dirSignX) >> 1;
			int dirPositivityY = (1 + dirSignY) >> 1;

			// integer position of the current cell / pixel
			int gridCoordsX = playerX/mapsize;
			int gridCoordsY = playerY/mapsize;

			// fractional position within the current cell
			float fractCoordsX = playerX / mapsize - gridCoordsX ;
			float fractCoordsY = playerY / mapsize - gridCoordsY ;

			for (int s = 0; s < dist; s++) //s = the amount of steps dist =  max amount of steps allowed
			{
				if (touched == false)
				{
					// remaining distance to the next cell border in multiples of the dir vector
					float distanceX = (dirPositivityX - fractCoordsX) / dirX;
					float distanceY = (dirPositivityY - fractCoordsY) / dirY;

					// move to the next cell border
					if (distanceX <= distanceY)
					{
						gridCoordsX += dirSignX; // jump over the border
						fractCoordsX = 1 - dirPositivityX; // set the new fract pos for the jumped X axis to 0
						fractCoordsY += dirY * distanceX; // adjust the Y axis accordingly
					}
					else
					{
						gridCoordsY += dirSignY;
						fractCoordsY = 1 - dirPositivityY;
						fractCoordsX += dirX * distanceY;
					}

					// check bounds
					if (gridCoordsX >= 0 && gridCoordsY >= 0 && gridCoordsX < mapwidth && gridCoordsY < mapheight)
					{
						// check if the new cell is filled (hit)
						if (map[gridCoordsX][gridCoordsY][3] == 1)
						{
							touched = true;
							float hitPosX = gridCoordsX + fractCoordsX;
							float hitPosY = gridCoordsY + fractCoordsY;

							//calculating distance and fisheye correction
							float correction = cos(playerRX - i);
							float distancetocam = sqrt(square(playerX-hitPosX*mapsize) + square(playerY-hitPosY*mapsize))*correction;

							rect(tx * pisizeX, (screenY/2)-(screenY/distancetocam),pisizeX ,(screenY/distancetocam*2), map[gridCoordsX][gridCoordsY][0], map[gridCoordsX][gridCoordsY][1], map[gridCoordsX][gridCoordsY][2], 255);
							
							
							//line(playerX, playerY, hitPosX * 20, hitPosY * 20, map[gridCoordsX][gridCoordsY][0], map[gridCoordsX][gridCoordsY][1], map[gridCoordsX][gridCoordsY][2], 255);
							//pixel(hitPosX * 20, hitPosY * 20, 0, 0, 0, 255);


						}
					}
				}
			}
			//line(playerX, playerY, playerX + dirX * 10, playerY + dirY * 10, 0, 255, 0, 255);
		}
	
}

float Game::square(float number)
{
	return (number*number);
}



