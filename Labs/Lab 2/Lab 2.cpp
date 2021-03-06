#include <iostream>
#include <fstream>
#include "queue.h"
#include <string>

void out(char** lab, int m, int n, bool canOut); // вывод в файл пути
void get_size(int *m, int *n); // определение размера лабиринта
void find_path(int n, int m, int x_cor, int y_cor, char** lab, int** visited, int** path, Queue *queue); // поиск пути

int main()
{
	Queue *queue = queue_create();
	std::ifstream fin("input.txt");
	if (fin) {
		std::string s;
		int m = 0, n = 0, x, y;
		bool canOut = true;
		// координаты старта и финиша
		int start_x = 0, start_y = 0, finish_x = 0, finish_y = 0;
		get_size(&m, &n);
		/* Создание динамического массива:
		lab - хранит в себе массив из файла
		visited - массив для хранения посещенных точек
		path - массив для хранения пути	*/
		char** lab = new char *[n];
		int** visited = new int *[n];
		int** path = new int *[n];
		for (int i = 0; i < m; i++) {
			lab[i] = new char[m];
			visited[i] = new int[m];
			path[i] = new int[m];
		}

		while (!fin.eof()) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					visited[i][j] = 0;
					path[i][j] = -1;
					fin >> lab[i][j];
					if (lab[i][j] == 'X') {
						start_x = i;
						start_y = j;
						queue_insert(queue, i);
						queue_insert(queue, j);
						path[i][j] = 1;
					}
					if (lab[i][j] == 'Y') {
						finish_x = i;
						finish_y = j;
					}
				}
			}
		}
		if (queue_empty(queue)) {
			canOut = false;
			out(lab, m, n, canOut);
		}

		while (!queue_empty(queue)) {
			x = queue_get(queue);
			queue_remove(queue);
			y = queue_get(queue);
			queue_remove(queue);
			find_path(n, m, x, y, lab, visited, path, queue);
		}

		if (!visited[finish_x][finish_y]) {
			canOut = false;
			out(lab, m, n, canOut);
		}
		else {
			x = finish_x;
			y = finish_y;
			while (path[x][y] != 2) { // восстановление пути
				if ((x - 1) >= 0 && (x - 1) < n && (path[x - 1][y] == path[x][y] - 1)) {
					x = x - 1;
					lab[x][y] = 'x';
				}
				else if ((x + 1) >= 0 && (x + 1) < n && (path[x + 1][y] == path[x][y] - 1)) {
					x = x + 1;
					lab[x][y] = 'x';
				}
				else if ((y - 1) >= 0 && (y - 1) < m && (path[x][y - 1] == path[x][y] - 1)) {
					y = y - 1;
					lab[x][y] = 'x';
				}
				else if ((y + 1) >= 0 && (y + 1) < m && (path[x][y + 1] == path[x][y] - 1)) {
					y = y + 1;
					lab[x][y] = 'x';
				}
			}
			canOut = true;
			out(lab, m, n, canOut);
		}
	}
	else {
		std::cout << "File cannot be opened :(.";
		exit(1);
	}
	queue_delete(queue);
	fin.close();
	return 0;
}

void out(char **lab, int m, int n, bool canOut) {
	std::ofstream fout("output.txt");
	if (canOut) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				fout << lab[i][j] << " ";
			}
			fout << "\n";
		}
	}
	else {
		fout << "IMPOSSIBLE";
	}
	exit(1);
	fout.close();
}

void get_size(int *m, int *n) {
	std::ifstream fin("input.txt");
	char *str = new char[1024];
	while (!fin.eof()) {
		fin.getline(str, 1024, '\n');
		*m = *m + 1;
		*n = strlen(str);
	}
	fin.close();
}

void find_path(int n, int m, int x_cor, int y_cor, char** lab, int** visited, int** path, Queue *queue) {
	if (!visited[x_cor][y_cor]) {
		// проверяем правую ячейку от старта
		if ((x_cor + 1) < n && (x_cor + 1) >= 0 && !visited[x_cor + 1][y_cor] &&
			(lab[x_cor + 1][y_cor] == '.' || lab[x_cor + 1][y_cor] == 'Y')) {
			path[x_cor + 1][y_cor] = path[x_cor][y_cor] + 1;
			queue_insert(queue, x_cor + 1);
			queue_insert(queue, y_cor);
		}

		// проверяем левую ячейку от старта
		if ((x_cor - 1) < n && (x_cor - 1) >= 0 && !visited[x_cor - 1][y_cor] &&
			(lab[x_cor - 1][y_cor] == '.' || lab[x_cor - 1][y_cor] == 'Y')) {
			path[x_cor - 1][y_cor] = path[x_cor][y_cor] + 1;
			queue_insert(queue, x_cor - 1);
			queue_insert(queue, y_cor);
		}

		// проверяем верхнюю ячейку от старта
		if ((y_cor + 1) < m && (y_cor + 1) >= 0 && !visited[x_cor][y_cor + 1] &&
			(lab[x_cor][y_cor + 1] == '.' || lab[x_cor][y_cor + 1] == 'Y')) {
			path[x_cor][y_cor + 1] = path[x_cor][y_cor] + 1;
			queue_insert(queue, x_cor);
			queue_insert(queue, y_cor + 1);
		}

		// проверяем нижнюю ячейку от старта
		if ((y_cor - 1) < m && (y_cor - 1) >= 0 && !visited[x_cor][y_cor - 1] &&
			(lab[x_cor][y_cor - 1] == '.' || lab[x_cor][y_cor - 1] == 'Y')) {
			path[x_cor][y_cor - 1] = path[x_cor][y_cor] + 1;
			queue_insert(queue, x_cor);
			queue_insert(queue, y_cor - 1);
		}
		visited[x_cor][y_cor] = 1;
	}
}