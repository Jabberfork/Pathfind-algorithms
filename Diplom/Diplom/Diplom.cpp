// Diplom.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <ctime>
#include <time.h>
#include <queue>


using namespace std;

//#define TEST

#include "init.h"
#include "map_functions.h"
#include "search_algorithms.h"
#include "sprite_map_drawing.h"

//HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
	srand(time(0));
	int i = 0, j = 0;
	int max_i = 15, max_j = 15;

	int i_enter = max_i - 2, j_enter = 1;	//координаты начала Взяты на шару, мб клеткой с препятствием
	int i_exit = 1, j_exit = max_j - 2;		//координаты цели. Взяты на шару, мб клеткой с препятствием

	//int i_enter = max_i - 2, j_enter = 1;	
	//int i_exit = 500, j_exit = 500;

	int** map_array = map_init(max_i, max_j);
	map_generator(map_array, max_i, max_j);

	while ((map_array[i_enter][j_enter] == -25000) || (map_array[i_exit][j_exit] == -25000)) {
		map_generator(map_array, max_i, max_j);
	}
	
	int** pure_map = map_init(max_i, max_j);
	copy_map(map_array, pure_map, max_i, max_j);


	int** pure_map_0 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_0, max_i, max_j);

	int** pure_map_1 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_1, max_i, max_j);
	int** pure_map_2 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_2, max_i, max_j);
	int** pure_map_3 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_3, max_i, max_j);
	int** pure_map_4 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_4, max_i, max_j);
	int** pure_map_5 = map_init(max_i, max_j);
	copy_map(map_array, pure_map_5, max_i, max_j);


	printf("\n");
	class coord_t* enter_exit = set_enter_exit(map_array, i_enter, j_enter, i_exit, j_exit);

		
/*
		printf("Volnovoi data: \n");
	for (int i = 1; i < 21; i++) {

		clock_t start, stop;
		start = clock();

		int** map_array = map_init(max_i, max_j);
		map_generator(map_array, max_i, max_j);

		pathfind_voln(map_array, enter_exit, max_i, max_j);
		int exit_weight = map_array[enter_exit[1].x][enter_exit[1].y];

		stop = clock();

		printf("i = %d \t search time = %lf \t cost to finish %d \n", i, (stop - start) * 1000 / (double)CLOCKS_PER_SEC, exit_weight);

		delete[] map_array;
	}

	printf("\n \n Greed data: \n");
	for (int i = 1; i < 21; i++) {
		clock_t start, stop;
		start = clock();

		int** map_array = map_init(max_i, max_j);
		map_generator(map_array, max_i, max_j);

		pathfind_greed(map_array, enter_exit, max_i, max_j);
		int exit_weight = map_array[enter_exit[1].x][enter_exit[1].y];

		stop = clock();

		printf("i = %d \t search time = %lf \t cost to finish %d \n", i, (stop - start) * 1000 / (double)CLOCKS_PER_SEC, exit_weight);

		delete[] map_array;
	}

	printf("\n \n A-star data: \n");
	for (int i = 1; i < 21; i++) {
		clock_t start, stop;
		start = clock();

		int** map_array = map_init(max_i, max_j);
		map_generator(map_array, max_i, max_j);
		int** pure_map = map_init(max_i, max_j);
		copy_map(map_array, pure_map, max_i, max_j);

		pathfind_a_star(map_array, pure_map, enter_exit, max_i, max_j);
		int exit_weight = map_array[enter_exit[1].x][enter_exit[1].y];

		stop = clock();

		printf("i = %d \t search time = %lf \t cost to finish %d \n", i, (stop - start) * 1000 / (double)CLOCKS_PER_SEC, exit_weight);

		delete[] pure_map;
		delete[] map_array;
	}


	printf("\n \n Deikstra data: \n");
	for (int i = 1; i < 21; i++) {
		clock_t start, stop;
		start = clock();

		int** map_array = map_init(max_i, max_j);
		map_generator(map_array, max_i, max_j);
		int** pure_map = map_init(max_i, max_j);
		copy_map(map_array, pure_map, max_i, max_j);

		pathfind_deikstra(map_array, pure_map, enter_exit, max_i, max_j);
		int exit_weight = map_array[enter_exit[1].x][enter_exit[1].y];

		stop = clock();

		printf("i = %d \t search time = %lf \t cost to finish %d \n", i, (stop - start) * 1000 / (double)CLOCKS_PER_SEC, exit_weight);

		delete[] pure_map;
		delete[] map_array;
	}*/


	printf("\n\n Volonovoi \n");
	map_array = pure_map_0;
	pathfind_voln(map_array, enter_exit, max_i, max_j);
	print_map(pure_map_0, max_i, max_j);
	
	printf("\n\n Greed \n");
	map_array = pure_map_1;
	pathfind_greed(map_array, enter_exit, max_i, max_j);
	print_map(map_array, max_i, max_j);

	printf("\n\n Deikstra \n");
	map_array = pure_map_2;
	pure_map = pure_map_3;
	pathfind_a_star(map_array, map_array, enter_exit, max_i, max_j);
	print_map(map_array, max_i, max_j);
	
	printf("\n\n A-star \n");
	map_array = pure_map_4;
	pure_map = pure_map_5;
	pathfind_a_star(map_array, pure_map, enter_exit, max_i, max_j);
	print_map(map_array, max_i, max_j);

	//struct way_t* way = path_construction(map_array, enter_exit);
	//map_draw_main(pure_map, max_i, max_j, way, enter_exit);
	//print_map(map_array, max_i, max_j);

	//struct way_t* way = path_construction(map_array, enter_exit);
	//map_draw_main(pure_map, max_i, max_j, way, enter_exit);
	//print_map(map_array, max_i, max_j);

	

	//delete way;
	delete [] map_array;
	delete[] pure_map;
	system("pause");
	return 0;
}