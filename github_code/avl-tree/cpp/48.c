/**************************************************************
АВТОР: Дронников Игорь
ПРОГРАММА: Курсовая работа, 3 семестр, вариант 16
НАЗНАЧЕНИЕ: Продемонстрировать работу с АВЛ-деревьями,
реализовать вставку элемента, если он не существует, вставку
простого элемента, удаление элемента. Для реализации рекомендуется
использовать графическую оболочку SDL.
***************************************************************/
 
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
 
const int SCREEN_WIDTH = 1280; //ширина окна
const int SCREEN_HEIGHT = 640; //высота окна
 
node* avl = NULL; //АВЛ-дерево
SDL_Texture *background; //изображение фона
SDL_Texture *root; //изображение корня
SDL_Texture *list; //изображение листа
 
node* inputNewElemAVL(SDL_Renderer *renderer, node* avl, int elem) { //добавление нового элемента
	SDL_RenderClear(renderer); //Очистка экрана
	renderBackground(background, renderer);
	if (!searchElem(avl, elem)) {
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); //Вывод текста на экран
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); //Вывод дерева на экран
		
		avl = insert(avl, elem);
 
		SDL_Delay(1000); //Пауза
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); //Вывод текста на экран
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //Вывод дерева на экран
		return avl;
	}
	else {
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "This element already exists"); //Вывод текста на экран
		return avl;
	}
}
 
node* inputElemAVL(SDL_Renderer *renderer, node* avl, int elem) { //добавление любого элемента
	SDL_RenderClear(renderer); //Очистка экрана
	renderBackground(background, renderer);
	renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); //Вывод текста на экран
	outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); //Вывод дерева на экран
 
	avl = insert(avl, elem);
 
	SDL_Delay(1000); //Пауза
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); //Вывод текста на экран
	outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //Вывод дерева на экран
	return avl;
}
 
node* removeElemAVL(SDL_Renderer *renderer, node* avl, int elem) { //удаление элемента из дерева
	while (searchElem(avl, elem)) {
		SDL_RenderClear(renderer); //Очистка экрана
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, 25, "Before"); //Вывод текста на экран
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); //Вывод дерева на экран
 
		avl = remove(avl, elem);
 
		SDL_Delay(1000); //Пауза
		renderText("res/Arial.ttf", 30, 255, 0, 0, renderer, 45, SCREEN_HEIGHT / 2, "After"); //Вывод текста на экран
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //Вывод дерева на экран
		system("pause");
	}
	cout << "Удаление всех элементов завершено успешно.\n";
	return avl;
}
 
void outputMenu(SDL_Renderer *renderer) { //вывод меню на экран
	renderBackground(background, renderer);
	SDL_Delay(200); //Пауза
	renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "AVL-tree: demostraition"); //Вывод текста на экран
	SDL_Delay(1000); //Пауза
	renderText("res/Arial.ttf", 25, 74, 21, 104, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6 + 60, "Choose action:"); //Вывод текста на экран
 
	const int N = 7; //Количество элементов меню
	string menu[N];
	menu[1] = "1. Input AVL-tree from file";
	menu[2] = "2. Output AVL-tree on screen";
	menu[3] = "3. Input new element in tree";
	menu[4] = "4. Input element in tree";
	menu[5] = "5. Delete element";
	menu[6] = "6. Exit";
 
	for (int i = 1; i < N; i++) {
		SDL_Delay(250); //Пауза
		renderText("res/Arial.ttf", 24, 74, 21, 104, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6 + 60 + i * 30, menu[i].c_str()); //Вывод текста на экран
	}
 
	char choise;
	cin >> choise;
	switch (choise) {
	case '1': {		
		inputAVL(avl); //Загрузка АВЛ-дерева из файла
		SDL_RenderClear(renderer); //Очистка экрана 
		outputMenu(renderer);
		break;
	}
	case '2': {		
		SDL_RenderClear(renderer); //Очистка экрана
		renderBackground(background, renderer);		
		outputAVL(avl, root, list, renderer, 0, SCREEN_WIDTH / 2, 25); //Вывод дерева на экран
		system("pause");		
		SDL_RenderClear(renderer); //Очистка экрана
		outputMenu(renderer);
		break;
	}
	case '3': {
		SDL_RenderClear(renderer); //Очистка экрана
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input new element"); //Вывод текста на экран
		int elem;
		cin >> elem;
		avl = inputNewElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); //Очистка экрана
		outputMenu(renderer);
		break;
	}
	case '4': {
		SDL_RenderClear(renderer); //Очистка экрана
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input new element"); //Вывод текста на экран
		int elem;
		cin >> elem;
		avl = inputElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); //Очистка экрана
		outputMenu(renderer);
		break;
	}
	case '5': {
		SDL_RenderClear(renderer); //Очистка экрана
		renderBackground(background, renderer);
		renderText("res/Arial.ttf", 35, 255, 0, 0, renderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6, "Input element to remove"); //Вывод текста на экран
		int elem;
		cin >> elem;
		avl = removeElemAVL(renderer, avl, elem);
		system("pause");
		SDL_RenderClear(renderer); //Очистка экрана
		outputMenu(renderer);
		break;
	}
	case '6': {
		cout << "Выполнение программы завершено успешно.\n";
		break;
	}
	default: {
		SDL_RenderClear(renderer); //Очистка экрана
		outputMenu(renderer);
		break;
	}
	}
}
 
int main(int, char**) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(cout, "SDL_Init");
		return 1;
	}
	//Установки параметров окна и области вывода
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
 
	//Загрузка изображений
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
