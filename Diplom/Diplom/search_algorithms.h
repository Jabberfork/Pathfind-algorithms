#include "init.h"

void print_path(struct way_t* way, int** map_array, class coord_t* enter_exit) {
	for (int i = 0; i < way->value[map_array[enter_exit[1].x][enter_exit[1].y]]; i++) {
		printf_s("%d,%d \n", way->coords[i].x, way->coords[i].y);
	}
}

//Волновой алгоритм (Очередь без приоритета)
/*int** pathfind_voln(int** map_array, class coord_t* enter_exit, int max_i, int max_j) { //max_i/j здесь нужны только для вывода карты на экран
	int st = 2, is_upd = 0;

	map_array[enter_exit[0].x][enter_exit[0].y] = 1; //Запихнуть эти две строчки в какое-то адекватное место, чтобы не дуплицировать столько раз
	//map_array[enter_exit[1].x][enter_exit[1].y] = 0;

	class coord_t add;
	deque<coord_t> visited; //Поиск цели через очередь. Идем не по всему массиву покаищем препятствия, а двигаемся вдоль фронта

	add.x = enter_exit[0].x;
	add.y = enter_exit[0].y;
	visited.push_back(add);

	while (visited.empty() != true) { //тут должно быть условие выхода из цикла при нахождении цели 
		int current_x = visited.front().x;
		int current_y = visited.front().y;

		//1) Calculate neighbour's ptiorities

		if (map_array[current_x + 1][current_y] != -25000) {
			add.x = current_x + 1;
			add.y = current_y;
			visited.push_back(add);
			map_array[current_x + 1][current_y] = (map_array[current_x][current_y] + 1);
		}
		else if (map_array[current_x][current_y + 1] != -25000) {
			add.x = current_x;
			add.y = current_y + 1;
			visited.push_back(add);
			map_array[current_x][current_y + 1] = (map_array[current_x][current_y] + 1);
		}
		else if (map_array[current_x - 1][current_y] != -25000) {
			add.x = current_x - 1;
			add.y = current_y;
			visited.push_back(add);
			map_array[current_x - 1][current_y] = (map_array[current_x][current_y] + 1);
		}
		else if (map_array[current_x][current_y - 1] != -25000) {
			add.x = current_x;
			add.y = current_y - 1;
			visited.push_back(add);
			map_array[current_x][current_y - 1] = (map_array[current_x][current_y] + 1);
		}
		else {
			visited.pop_front();
		}
		if ((add.x == enter_exit[1].x) && (add.y == enter_exit[1].y)) {  //Если находит цель - завершает программу
			is_upd = 1;
			break;
		}
	}

	if (is_upd == 0) //проверка на то, что путь к выходу открыт
		return NULL;

	print_map(map_array, max_i, max_j);
	printf_s("\n\n");

	return map_array;
}*/

int** pathfind_voln(int** map_array, class coord_t* enter_exit, int max_i, int max_j) { //max_i/j здесь нужны только для вывода карты на экран
	int st = 2, is_upd = 0;

	map_array[enter_exit[0].x][enter_exit[0].y] = 1; //Запихнуть эти две строчки в какое-то адекватное место, чтобы не дуплицировать столько раз
													 //map_array[enter_exit[1].x][enter_exit[1].y] = 0;

	class coord_t* add = new coord_t[4];
	deque<coord_t> visited; //Поиск цели через очередь. Идем не по всему массиву покаищем препятствия, а двигаемся вдоль фронта

	add[0].x = enter_exit[0].x;
	add[0].y = enter_exit[0].y;
	visited.push_back(add[0]);

	while (visited.empty() != true) { //тут должно быть условие выхода из цикла при нахождении цели 
		int current_x = visited.front().x;
		int current_y = visited.front().y;

		TPRINTF("cur coords: %d,%d\n", current_x, current_y);

		add[0].x = current_x - 1;
		add[0].y = current_y;

		add[1].x = current_x + 1;
		add[1].y = current_y;

		add[2].x = current_x;
		add[2].y = current_y - 1;

		add[3].x = current_x;
		add[3].y = current_y + 1;

		for (int i = 0; i < 4; i++) {
			if ((map_array[add[i].x][add[i].y] != -25000) && (map_array[add[i].x][add[i].y] <= 0)) { //Выяснить почему тут срабатывает исключение. Быитый тест может сделать лажу
				
				visited.push_back(add[i]);
				map_array[add[i].x][add[i].y] = (map_array[current_x][current_y] + 1);
				TPRINTF("\t candidat %d\n; it's coord: x = %d, y = %d\n", map_array[add[i].x][add[i].y], add[i].x, add[i].y);
				
			}
			else {
				TPRINTF("\t not candidat %d\n; it's coord: x = %d, y = %d\n", map_array[add[i].x][add[i].y], add[i].x, add[i].y);
				continue;
			}
			if ((add[i].x == enter_exit[1].x) && (add[i].y == enter_exit[1].y)) {  //Если находит цель - завершает программу
				is_upd = 1;

				delete[] add;
				return map_array;
			}
		}

		//print_map(map_array, max_i, max_j);
		//printf("\n");
		visited.pop_front();

	}

	delete[] add;

	if (is_upd == 0) //проверка на то, что путь к выходу открыт
		return NULL;

}


void choosing_neighbour(class add_t* add, int** map_array, class coord_t* enter_exit) {
	add[5].priority = -1;

	for (int i = 1; i < 5; i++) {
		if (add[i].priority != 0) {
			//add[i].calc_prioritet(enter_exit, map_array);
			if ((add[i].priority) > (add[5].priority)) {
				add[5].priority = add[i].priority;
				TPRINTF("cur i = %d", i);
			}
		}
	}
}

int** pathfind_greed(int** map_array, class coord_t* enter_exit, int max_i, int max_j) {
	int st = 2, is_upd = 0;

	//class coord_t add_coords;
	class add_t add;
	priority_queue<add_t> to_visit;
	queue<add_t> visited;

	add.coords.x = enter_exit[0].x;
	add.coords.y = enter_exit[0].y;
	add.calc_prioritet(enter_exit, map_array);
	to_visit.push(add);

	map_array[enter_exit[0].x][enter_exit[0].y] = 1;


	while (to_visit.empty() != true) {

		//Put coordinates of rhe current point into int, and delete the element from the que while it's on the top
		int current_x = to_visit.top().coords.x;
		int current_y = to_visit.top().coords.y;
		to_visit.pop();

		if ((current_x == enter_exit[1].x) && (current_y == enter_exit[1].y)) {  //Если находит цель - завершает программу
			add.coords.x = current_x;
			add.coords.y = current_y;
			add.priority = 1000;			// Max because this is exit
			to_visit.push(add);
			is_upd = 1;

			TPRINTF("IT'S ALIVE");
			break;
		}

		//right point
		if ((map_array[current_x + 1][current_y] != (-25000)) &&										//the point isn't an obstacle;
				((map_array[current_x + 1][current_y] <= 0) ||										//the poin't isn't visited
				 (map_array[current_x + 1][current_y] > map_array[current_x][current_y] + 1))) {	//if it is visited, the number we want to give it less then it's current
			add.coords.x = current_x + 1;
			add.coords.y = current_y;
			add.calc_prioritet(enter_exit, map_array);
			map_array[current_x + 1][current_y] = (map_array[current_x][current_y] + 1);
			to_visit.push(add);
		}

		//up point
		if ((map_array[current_x][current_y + 1] != (-25000)) && 
				((map_array[current_x][current_y + 1] <= 0) ||
				 (map_array[current_x][current_y + 1] > map_array[current_x][current_y] + 1))) {
			add.coords.x = current_x;
			add.coords.y = current_y + 1;
			add.calc_prioritet(enter_exit, map_array);
			map_array[current_x][current_y + 1] = (map_array[current_x][current_y] + 1);
			to_visit.push(add);
		}

		//left point
		if ((map_array[current_x - 1][current_y] != (-25000)) && 
				((map_array[current_x - 1][current_y] <= 0) || 
				 (map_array[current_x - 1][current_y] > map_array[current_x][current_y] + 1))) {
			add.coords.x = current_x - 1;
			add.coords.y = current_y;
			add.calc_prioritet(enter_exit, map_array);
			map_array[current_x - 1][current_y] = (map_array[current_x][current_y] + 1);
			to_visit.push(add);
		}

		//down point
		if ((map_array[current_x][current_y - 1] != (-25000)) && 
			((map_array[current_x][current_y - 1] <= 0) ||
			 (map_array[current_x][current_y - 1] > map_array[current_x][current_y] + 1))) {
			add.coords.x = current_x;
			add.coords.y = current_y - 1;
			add.calc_prioritet(enter_exit, map_array);
			map_array[current_x][current_y - 1] = (map_array[current_x][current_y] + 1);
			to_visit.push(add);

		}

		TPRINTF("Round \n");
		TPRINTF("cur (%d %d) size = %d ", current_x, current_y, to_visit.size());
		TPRINTF("cur_p = %d, \t y+1_p = %d", to_visit.top().priority, add.priority);
	}

	if (is_upd == 0) //проверка на то, что путь к выходу открыт
		return NULL;

	//print_map(map_array, max_i, max_j);

	return map_array;
}




int neighbours_act(class add_t* add, int** map_array, int** pure_map, priority_queue<add_t> *to_visit, class coord_t* enter_exit, int current_x, int current_y) {
	for (int i = 0; i != 4; i++) {
		TPRINTF("i = %d", i);
		if (pure_map[add[i].coords.x][add[i].coords.y] != -25000) {
			TPRINTF("\ti = %d", i);

			//Если значение в точке меньше, чем то, что мы хотим в нее записать - оставляем все как есть, иначе - перезаписываем
			if ((map_array[add[i].coords.x][add[i].coords.y] <= map_array[current_x][current_y] + 1) && (map_array[add[i].coords.x][add[i].coords.y] > 0)) {
				continue;
			}
		
			map_array[add[i].coords.x][add[i].coords.y] = map_array[current_x][current_y] + 1 + (pure_map[add[i].coords.x][add[i].coords.y] / (-10));
			add[i].cost_so_far = map_array[add[i].coords.x][add[i].coords.y];
			add[i].calc_prioritet_a_star(enter_exit, map_array);
			to_visit->push(add[i]);

			TPRINTF("\t\tRound");
			TPRINTF("\t\tcur (%d %d) view at = (%d %d) i = %d \t\tprior = %d", current_x, current_y, add[i].coords.x, add[i].coords.y, i, add[i].priority);

			if ((add[i].coords.x == enter_exit[1].x) && (add[i].coords.y == enter_exit[1].y)) {
				TPRINTF("It's alive!");
				return 1;
			}

		}
	}
	return 0;
}


int** pathfind_a_star(int** map_array, int** pure_map, class coord_t* enter_exit, int max_i, int max_j) {
	int st = 2, is_upd = 0;

	//class coord_t add_coords;
	class add_t* add = new class add_t[4];
	priority_queue<add_t> to_visit;

	add[0].coords.x = enter_exit[0].x;
	add[0].coords.y = enter_exit[0].y;
	add[0].cost_so_far = 0;
	add[0].calc_prioritet_a_star(enter_exit, map_array);
	to_visit.push(add[0]);

	map_array[enter_exit[0].x][enter_exit[0].y] = 1;

	//visited[0] = add;


	while (to_visit.empty() != true) {

		//Put coordinates of the current point into int, and delete the element from the que while it's on the top
		int current_x = to_visit.top().coords.x;
		int current_y = to_visit.top().coords.y;
		to_visit.pop();

		add[0].coords.x = current_x - 1;
		add[0].coords.y = current_y;

		add[1].coords.x = current_x + 1;
		add[1].coords.y = current_y;

		add[2].coords.x = current_x;
		add[2].coords.y = current_y - 1;

		add[3].coords.x = current_x;
		add[3].coords.y = current_y + 1;

		if (neighbours_act(add, map_array, pure_map, &to_visit, enter_exit, current_x, current_y) == 1) {
			delete[] add;
			return map_array;
		}

		TPRINTF("Here is map: \n");
		//TFUNC(print_map(map_array, max_i, max_j));
	}
	
	delete[] add;

	//print_map(map_array, max_i, max_j);

	return NULL;
}

int neighbours_deikstra_act(class add_t* add, int** map_array, int** pure_map, deque<add_t> *to_visit, class coord_t* enter_exit, int current_x, int current_y) {
	for (int i = 0; i != 4; i++) {
		TPRINTF("i = %d", i);
		if (pure_map[add[i].coords.x][add[i].coords.y] != -25000) {
			TPRINTF("\ti = %d", i);

			//Если значение в точке меньше, чем то, что мы хотим в нее записать - оставляем все как есть, иначе - перезаписываем
			if ((map_array[add[i].coords.x][add[i].coords.y] <= map_array[current_x][current_y] + 1) && (map_array[add[i].coords.x][add[i].coords.y] > 0)) {
				continue;
			}
		
			map_array[add[i].coords.x][add[i].coords.y] = map_array[current_x][current_y] + 1 + (pure_map[add[i].coords.x][add[i].coords.y] / (-10));
			add[i].cost_so_far = map_array[add[i].coords.x][add[i].coords.y];
			add[i].calc_prioritet_deikstra(enter_exit, map_array);
			to_visit->push_back(add[i]);

			TPRINTF("\t\tRound");
			TPRINTF("\t\tcur (%d %d) view at = (%d %d) i = %d \t\tprior = %d", current_x, current_y, add[i].coords.x, add[i].coords.y, i, add[i].priority);

			if ((add[i].coords.x == enter_exit[1].x) && (add[i].coords.y == enter_exit[1].y)) {
				TPRINTF("It's alive!");
				return 1;
			}

		}
	}
	return 0;
}

int** pathfind_deikstra(int** map_array, int** pure_map, class coord_t* enter_exit, int max_i, int max_j) {
	int st = 2, is_upd = 0;

	//class coord_t add_coords;
	class add_t* add = new class add_t[4];
	deque<add_t> to_visit;
	//	class add_t* visited = new class add_t[];

	add[0].coords.x = enter_exit[0].x;
	add[0].coords.y = enter_exit[0].y;
	add[0].cost_so_far = 0;
	add[0].calc_prioritet_a_star(enter_exit, map_array);
	to_visit.push_front(add[0]);

	map_array[enter_exit[0].x][enter_exit[0].y] = 1;

	//visited[0] = add;


	while (to_visit.empty() != true) {

		//Put coordinates of the current point into int, and delete the element from the que while it's on the top
		int current_x = to_visit.front().coords.x;
		int current_y = to_visit.front().coords.y;
		to_visit.pop_front();

		add[0].coords.x = current_x - 1;
		add[0].coords.y = current_y;

		add[1].coords.x = current_x + 1;
		add[1].coords.y = current_y;

		add[2].coords.x = current_x;
		add[2].coords.y = current_y - 1;

		add[3].coords.x = current_x;
		add[3].coords.y = current_y + 1;

		if (neighbours_deikstra_act(add, map_array, pure_map, &to_visit, enter_exit, current_x, current_y) == 1) {
			delete[] add;
			return map_array;
		}

		TPRINTF("Here is map: \n");
		//TFUNC(print_map(map_array, max_i, max_j));
	}

	delete[] add;

	//print_map(map_array, max_i, max_j);

	return NULL;
}



struct way_t* path_construction(int** map_array, class coord_t* enter_exit) {

	if (map_array[enter_exit[1].x][enter_exit[1].y] <= 0) {
		return NULL;
	}

	int is_upd = 0;

	//Создаем указатель на структуру путь - содержит координаты пути и его длину
	struct way_t* way = new struct way_t;
	way->coords = new class coord_t[map_array[enter_exit[1].x][enter_exit[1].y]]; //кек в том, что его размер нихуя не value
	way->value = new int[map_array[enter_exit[1].x][enter_exit[1].y]];

	//Последний элемент - точка выхода 
	way->value[0] = map_array[enter_exit[1].x][enter_exit[1].y];
	way->coords[0].x = enter_exit[1].x;
	way->coords[0].y = enter_exit[1].y;
	

	int st = way->value[0];

	int i = 1;
	while (st != 1) {
		int prev_x = way->coords[i - 1].x;
		int prev_y = way->coords[i - 1].y;
		int prev_value = way->value[i - 1];

		int next_point = min(min(abs(map_array[prev_x - 1][prev_y]), abs(map_array[prev_x + 1][prev_y])), min(abs(map_array[prev_x][prev_y - 1]), abs(map_array[prev_x][prev_y + 1]))); //НЕПОНЯТНОЕ НАРУШЕНИЕ

		if (next_point > 0) {
			if (next_point == map_array[prev_x - 1][prev_y]) {
				way->coords[i].x = prev_x - 1;
				way->coords[i].y = prev_y;
				way->value[i] = next_point;
			}
			else if (next_point == map_array[prev_x + 1][prev_y]) {
				way->coords[i].x = prev_x + 1;
				way->coords[i].y = prev_y;
				way->value[i] = next_point;
			}
			else if (next_point == map_array[prev_x][prev_y - 1]) {
				way->coords[i].x = prev_x;
				way->coords[i].y = prev_y - 1;
				way->value[i] = next_point;
			}
			else if (next_point == map_array[prev_x][prev_y + 1]) {
				way->coords[i].x = prev_x;
				way->coords[i].y = prev_y + 1;
				way->value[i] = next_point;
			}
			st = way->value[i];
			
			if (st == 1)
				is_upd = 1;
		}


		TPRINTF(" corrent coords: %d,%d \n", prev_x, prev_y);
		i++;

	}

	way->size = i;


	//TFUNC(print_path(way));

	TPRINTF("sucseed mthfckrs");
	TPRINTF("Test mode active!");

	return way;
}







//Черновик:
/*
class add_t* add = new add_t[5];
deque<add_t> to_visit; //Поиск цели через очередь. Идем не по всему массиву покаищем препятствия, а двигаемся вдоль фронта

add[0].coords.x = enter_exit[0].x;
add[0].coords.y = enter_exit[0].y;
to_visit.push_back(add[0]);

while (to_visit.empty() != true) { //тут должно быть условие выхода из цикла при нахождении цели 
	int current_x = to_visit.front().coords.x;
	int current_y = to_visit.front().coords.y;

	//1) Calculate neighbour's ptiorities
	if (map_array[current_x + 1][current_y] != -25000) {
		add[1].coords.x = current_x + 1;
		add[1].coords.y = current_y;
	}
	if (map_array[current_x][current_y + 1] != -25000) {
		add[2].coords.x = current_x;
		add[2].coords.y = current_y + 1;
	}
	if (map_array[current_x - 1][current_y] != -25000) {
		add[3].coords.x = current_x - 1;
		add[3].coords.y = current_y;
	}
	if (map_array[current_x][current_y - 1] != -25000) {
		add[4].coords.x = current_x;
		add[4].coords.y = current_y - 1;
	}





	for (int i = 1; i < 4; i++) {
		if (add[i + 1].priority > add[i].priority) {
			to_visit.push_back(add[i + 1]);
		}
	}

	else {
		visited.pop_front();
	}
	*/

//A* version 1
/*
if ((map_array[current_x + 1][current_y] != (-25000)) && (map_array[current_x + 1][current_y] <= 0)) {
add.coords.x = current_x + 1;
add.coords.y = current_y;
add.calc_prioritet(enter_exit, map_array);
visited.push(add);
map_array[current_x + 1][current_y] = (map_array[current_x][current_y] + 1);
}
else if ((map_array[current_x][current_y + 1] != (-25000)) && (map_array[current_x][current_y + 1] <= 0)) {
add.coords.x = current_x;
add.coords.y = current_y + 1;
add.calc_prioritet(enter_exit, map_array);
visited.push(add);
map_array[current_x][current_y + 1] = (map_array[current_x][current_y] + 1);
}
else if ((map_array[current_x - 1][current_y] != (-25000)) && (map_array[current_x - 1][current_y] <= 0)) {
add.coords.x = current_x - 1;
add.coords.y = current_y;
add.calc_prioritet(enter_exit, map_array);
visited.push(add);
map_array[current_x - 1][current_y] = (map_array[current_x][current_y] + 1);
}
else if ((map_array[current_x][current_y - 1] != (-25000)) && (map_array[current_x][current_y - 1] <= 0)) {
add.coords.x = current_x;
add.coords.y = current_y - 1;
add.calc_prioritet(enter_exit, map_array);
visited.push(add);
map_array[current_x][current_y - 1] = (map_array[current_x][current_y] + 1);
}
else {
visited.pop();
}

if ((add.coords.x == enter_exit[1].x) && (add.coords.y == enter_exit[1].y)) {  //Если находит цель - завершает программу
is_upd = 1;
break;
}
*/

struct way_voln_t* path_construction_voln(int** map_array, class coord_t* enter_exit) {

	if (map_array[enter_exit[1].x][enter_exit[1].y] <= 0) {
		return NULL;
	}

	int st = map_array[enter_exit[1].x][enter_exit[1].y];

	int length = st;

	//Создаем указатель на структуру путь - содержит координаты пути и его длину
	struct way_voln_t* way = new struct way_voln_t;
	way->coords = new class coord_t[length];
	way->length = length;

	//Последний элемент - точка выхода 
	way->coords[length - 1].x = enter_exit[1].x;
	way->coords[length - 1].y = enter_exit[1].y;
	for (st = length - 2; st != -1; st--) {
		int prev_x = way->coords[st + 1].x;
		int prev_y = way->coords[st + 1].y;

		//TFUNC(print_map(map_array, enter_exit[1].x + 1, enter_exit[1].y + 1));
 		if (map_array[prev_x - 1][prev_y] == st + 1) { // Можно поменять последовательность else if, чтобы поменять приоритет выбора путей //ТУТ КОСЯК ИНОГДА ВСПЛЫВАЕТ
			way->coords[st].x = (prev_x - 1);
			way->coords[st].y = prev_y;
		}
		else if (map_array[prev_x + 1][prev_y] == st + 1) {
			way->coords[st].x = (prev_x + 1);
			way->coords[st].y = prev_y;
		}
		else if (map_array[prev_x][prev_y - 1] == st + 1) {
			way->coords[st].x = prev_x;
			way->coords[st].y = (prev_y - 1);
		}
		else if (map_array[prev_x][prev_y + 1] == st + 1) {
			way->coords[st].x = prev_x;
			way->coords[st].y = (prev_y + 1);
		}

		//if ((way->coords[0].x == enter_exit[0].x) && (way->coords[0].y == enter_exit[0].y)) { 
		//}
	}

	

	//TFUNC(print_path(way));

	TPRINTF("Test mode active!");

	return way;
}