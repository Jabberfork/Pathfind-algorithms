int** map_init(int max_i, int max_j) {
	int** map_array = new int*[max_i];
	for (int i = 0; i < max_i; i++) {
		map_array[i] = new int[max_j];
	}
	return map_array;
}
void map_generator(int** map_array, int max_i, int max_j) {
	for (int j = 0; j < max_j; j++) {
		for (int i = 0; i < max_i; i++) {
			map_array[i][j] = rand() % 100;
			if (map_array[i][j] > 80) { 
				map_array[i][j] = -25000;
			}
			else if ((map_array[i][j] > 60) && (map_array[i][j] <= 80)) {
				map_array[i][j] = -10; 
			}
			else {
				map_array[i][j] = 0; 
			}

			if (i == 0 || j == 0 || i == max_i - 1 || j == max_j - 1) //Borders
				map_array[i][j] = -25000;

			//map_array[1][7] = -25000; //ѕроверка проги на заблоченный выход
			//map_array[2][8] = -25000;
		}
	}
}

void print_map(int** map_array, int max_i, int max_j) {
	for (int i = 0; i < max_i; i++) {
		for (int j = 0; j < max_j; j++) {
			printf("%d\t", map_array[i][j]);
		}
		printf("\n");
	}
	return;
}

void copy_map(int** from, int** to, int max_i, int max_j) {
	for (int j = 0; j < max_j; j++) {
		for (int i = 0; i < max_i; i++) {
			to[i][j] = from[i][j];
		}
	}
}
