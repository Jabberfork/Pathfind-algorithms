#include "stdafx.h"
#include <SFML/Graphics.hpp>


sf::Sprite** init_sprite_map(int max_i, int max_j) {
	sf::Sprite** sprite_map = new sf::Sprite*[max_i];

	for (int i = 0; i < max_i; i++) {
		sprite_map[i] = new sf::Sprite[max_j];
	}

	TPRINTF("Map init \t\t %p\n", sprite_map);

	return sprite_map;
}

void fill_sprite_map(sf::Sprite** sprite_map, int** map_array, int max_i, int max_j, sf::Texture* texture, struct way_t* way) {
	TPRINTF("Map gen \t\t %p\n", sprite_map);

	int is_way = 0;

	for (int i = 0; i < max_i; i++) {
		for (int j = 0; j < max_j; j++) {
			sprite_map[i][j].setTexture(*texture);
			if (map_array[i][j] == 0) {
				sprite_map[i][j].setTextureRect(sf::IntRect(0, 0, 32, 32));
			}

			else if (map_array[i][j] == -10) {
				sprite_map[i][j].setTextureRect(sf::IntRect(64, 0, 32, 32));
			}

			else if (map_array[i][j] == -25000){
				sprite_map[i][j].setTextureRect(sf::IntRect(32, 0, 32, 32));
			}
			sprite_map[i][j].setPosition(j * 32, i * 32);
		}
	}
}

void fill_sprite_way(sf::Sprite** sprite_map, int** map_array, int max_i, int max_j, sf::Texture* texture, struct way_t* way, class coord_t* enter_exit) {
	for (int i = 0; i < way->size; i++) {
		if (map_array[way->coords[i].x][way->coords[i].y] == 0) {
			sprite_map[way->coords[i].x][way->coords[i].y].setTextureRect(sf::IntRect(96, 0, 32, 32));
		}
		else if (map_array[way->coords[i].x][way->coords[i].y] == -10) {
			sprite_map[way->coords[i].x][way->coords[i].y].setTextureRect(sf::IntRect(128, 0, 32, 32));
		}

		sprite_map[way->coords[i].x][way->coords[i].y].setPosition(way->coords[i].y * 32, way->coords[i].x * 32);
	}
}

void draw_map(sf::Sprite** sprite_map, sf::RenderWindow* window, int max_i, int max_j) {
	for (int i = 0; i < max_i; i++) {
		for (int j = 0; j < max_j; j++) {
			window->draw(sprite_map[i][j]);
		}
	}
}



int map_draw_main(int** map_array, int max_i, int max_j, struct way_t* way, class coord_t* enter_exit) {

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Map");


	sf::Texture texture;
	texture.loadFromFile("C:/Users/Jabberwock/source/repos/Diplom/Diplom/map.png");

	sf::Sprite** sprite_map = init_sprite_map(max_i, max_j);

	//If way to the end doesn't exist - print pure map; else - map and the way
	if (way == NULL) {
		printf("NO EXIT \n");
		fill_sprite_map(sprite_map, map_array, max_i, max_j, &texture, way);
	}
	else {
		fill_sprite_map(sprite_map, map_array, max_i, max_j, &texture, way);
		fill_sprite_way(sprite_map, map_array, max_i, max_j, &texture, way, enter_exit);
	}
	

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		draw_map(sprite_map, &window, max_i, max_j);
		window.display();

	}

	delete[] sprite_map;
	return 0;
}




// 1) Добавить кнопку перерисовки карты 
// 2) Установка входа выхода по клику на карте