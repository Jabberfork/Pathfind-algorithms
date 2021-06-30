#ifndef INIT_H_DEF
#define INIT_H_DEF

#ifndef TEST
#define TPRINTF(...) 
#define TFUNC(...)
#endif

#ifdef TEST
#define TPRINTF(...)    \
do{						\
printf("TEST %d: ", __LINE__);		\
printf(__VA_ARGS__);    \
printf("\n");			\
} while (0);

#define TFUNC(...)		\
do{						\
__VA_ARGS__;			\
} while (0);			

#endif




class coord_t {
public:
	int x;
	int y;
};

class add_t {
public:
	coord_t coords;
	int priority;
	int cost_so_far;

	void calc_prioritet(class coord_t* enter_exit, int** map_array) {
		//Manhattan distance:
		//priority =(abs(enter_exit[1].x - coords.x) + abs(enter_exit[1].y - coords.y)); //Эвристический приоритет (жадны сейчас)
		
		//Euklid distance
		priority = 32000 - sqrt((enter_exit[1].x - coords.x)*(enter_exit[1].x - coords.x) + (enter_exit[1].y - coords.y)*(enter_exit[1].y - coords.y));

		//priority -= (1000 + (map_array[coords.x][coords.y] + 20)); //Минимальному расстоянию соответствует максимальный приоритет; Приоритет в зависимости от проходимосьи пути
	}

	void calc_prioritet_a_star(class coord_t* enter_exit, int** map_array) {
		//Euklid distance
		priority = sqrt((enter_exit[1].x - coords.x)*(enter_exit[1].x - coords.x) + (enter_exit[1].y - coords.y)*(enter_exit[1].y - coords.y));
		priority = 32000 - priority - cost_so_far; //Минимальному расстоянию соответствует максимальный приоритет; Приоритет в зависимости от проходимосьи пути
	}

	void calc_prioritet_deikstra(class coord_t* enter_exit, int** map_array) {
		
		priority = 32000 - cost_so_far; 
	}
};

//перегрузка операторов сравнения. Нужно чтобы при сравнении add_t сравнивались только значения Priority
bool operator< (const add_t &p1, const add_t &p2) {
	return p1.priority < p2.priority;
}

bool operator> (const add_t &p1, const add_t &p2) {
	return p1.priority > p2.priority;
}

bool operator<= (const add_t &p1, const add_t &p2) {
	return p1.priority <= p2.priority;
}

bool operator>= (const add_t &p1, const add_t &p2) {
	return p1.priority >= p2.priority;
}

bool operator== (const add_t &p1, const add_t &p2) {
	return p1.priority == p2.priority;
}

bool operator!= (const add_t &p1, const add_t &p2) {
	return p1.priority != p2.priority;
}


//struct coord_t { int x; int y; };
struct way_voln_t {
	class coord_t* coords;
	int length;
};

struct way_t {
	class coord_t* coords;
	int* value;
	int size;
};

class coord_t* set_enter_exit(int** map_array, int i_enter, int j_enter, int i_exit, int j_exit) {
	class coord_t* enter_exit = new class coord_t[2];
	//Set enter/exit coords and check it's not obstacle
	if (map_array[i_enter][j_enter] == -25000) {
		printf("The enter is obstacle! Choose another one \n");
		scanf_s("%d%d", &i_enter, &j_enter);
	}
	enter_exit[0].x = i_enter;
	enter_exit[0].y = j_enter;

	if (map_array[i_exit][j_exit] == -25000) {
		printf("The exit is obstacle! Choose another one \n");
		scanf_s("%d%d", &i_exit, &j_exit);
	}

	enter_exit[1].x = i_exit;
	enter_exit[1].y = j_exit;

	return enter_exit;
}

#endif