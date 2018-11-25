
 
#include <string>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "res/res_path.h"
#include "res/cleanup.h"
#include "windows.h"
#include "avl.h"
#include "sdl_func.h"
 
using namespace std;
 
const int SCREEN_WIDTH = 1280; 
const int SCREEN_HEIGHT = 640; 
 
node* avl = NULL; 
SDL_Texture *background; 
SDL_Texture *root; 
SDL_Texture *list; 
 
node* inputNewElemAVL(SDL_Renderer *renderer, node* avl, int elem) { 
	SDL_RenderClear(renderer); 
	renderBackground(background, renderer);
	if (!searchElem(avl, elem)) {
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); 
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); 
		
		avl = insert(avl, elem);
 
		SDL_Delay(1000); 
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); 
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); 
		return avl;
	}
	else {
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "This element already exists"); 
		return avl;
	}
}
 
node* inputElemAVL(SDL_Renderer *renderer, node* avl, int elem) { 
	SDL_RenderClear(renderer); 
	renderBackground(background, renderer);
	renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); 
	outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); 
 
	avl = insert(avl, elem);
 
	SDL_Delay(1000); 
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); 
	outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); 
	return avl;
}
 
node* removeElemAVL(SDL_Renderer *renderer, node* avl, int elem) { 
	while (searchElem(avl, elem)) {
		SDL_RenderClear(renderer); 
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); 
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); 
 
		avl = remove(avl, elem);
 
		SDL_Delay(1000); 
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); 
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); 
		system("pause");
	}
	cout << "Удаление всех элементов завершено успешно.\n";
	return avl;
}
 
void outputMenu(SDL_Renderer *renderer) { 
	renderBackground(background, renderer);
	SDL_Delay(200); 
	renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "AVL-tree: demostraition"); 
	SDL_Delay(1000); 
	renderText("res/Arial.ttf", 25, 74, 21, 104, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6 + 60, "Choose action:"); 
 
	const int N = 7; 
	string menu[N];
	menu[1] = "1. Input AVL-tree from file";
	menu[2] = "2. Output AVL-tree on screen";
	menu[3] = "3. Input new element in tree";
	menu[4] = "4. Input element in tree";
	menu[5] = "5. Delete element";
	menu[6] = "6. Exit";
 
	for (int i = 1; i < N; i++) {
		SDL_Delay(250); 
		renderText("res/Arial.ttf", 24, 74, 21, 104, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6 + 60 + i * 30, menu[i].c_str()); 
	}
 
	char choise;
	cin >> choise;
	switch (choise) {
	case '1': {		
		inputAVL(avl); 
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	case '2': {		
		SDL_RenderClear(renderer); 
		renderBackground(background, renderer);		
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); 
		system("pause");		
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	case '3': {
		SDL_RenderClear(renderer); 
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input new element"); 
		int elem;
		cin >> elem;
		avl = inputNewElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	case '4': {
		SDL_RenderClear(renderer); 
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input new element"); 
		int elem;
		cin >> elem;
		avl = inputElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	case '5': {
		SDL_RenderClear(renderer); 
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input element to remove"); 
		int elem;
		cin >> elem;
		avl = removeElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	case '6': {
		cout << "Выполнение программы завершено успешно.\n";
		break;
	}
	default: {
		SDL_RenderClear(renderer); 
		outputMenu(renderer);
		break;
	}
	}
}
 
int main(int, char**) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(cout, "SDL_Init");
		return 1;
	}
	
	SDL_Window *window = SDL_CreateWindow("AVL-tree: demostraition", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		logSDLError(cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
 
	
	background = loadTexture("res/background.bmp", renderer);
	root = loadTexture("res/root.bmp", renderer);
	list = loadTexture("res/list.bmp", renderer);
	if (background == nullptr || root == nullptr || list == nullptr) {
		cleanup(background, root, list, renderer, window);
		SDL_Quit();
		return 1;
	}
 
	outputMenu(renderer);
 
	cleanup(background, root, list, renderer, window);
 
	SDL_Quit();
	return 0;
}
