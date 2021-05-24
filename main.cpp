#include <iostream>
#include <vector>
#include <array>

using std::array; using std::vector;


void print_sudoku(array<int, 81>);
array<int, 9> get_line(array<int, 81>, int);
array<int, 9> get_row(array<int, 81>, int);
array<int, 9> get_field(array<int, 81>, int);
array<vector<int>, 9> get_line(array<vector<int>, 81>, int);
array<vector<int>, 9> get_row(array<vector<int>, 81>, int);
array<vector<int>, 9> get_field(array<vector<int>, 81>, int);
bool sudoku_is_done(array<int, 81>);
bool in_arr(int, array<int, 9>);
int count(int, array<vector<int>, 9>);


int main() {
	/*
	* array<int, 81> sudoku = {
		4, 7, 3, 0, 0, 0, 0, 1, 0,
		5, 6, 9, 0, 0, 0, 7, 0, 0,
		0, 1, 0, 0, 7, 0, 6, 0, 0,
		8, 0, 0, 4, 0, 5, 0, 0, 0,
		1, 2, 0, 0, 0, 0, 0, 4, 8,
		0, 0, 0, 8, 0, 1, 0, 0, 9,
		0, 0, 7, 0, 6, 0, 0, 5, 0,
		0, 0, 2, 0, 0, 0, 4, 3, 6,
		0, 8, 0, 0, 0, 0, 9, 2, 7
	};
	*/
	array<int, 81> sudoku = {
		0, 0, 0, 0, 0, 0, 5, 6, 9,
		0, 0, 0, 6, 1, 2, 0, 0, 0,
		8, 3, 6, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 9, 5, 0, 0, 7, 0,
		0, 5, 9, 0, 0, 0, 1, 3, 0,
		0, 2, 0, 0, 3, 4, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 2, 4, 6,
		0, 0, 0, 8, 2, 7, 0, 0, 0,
		2, 1, 3, 0, 0, 0, 0, 0, 0
	};
	bool found_an_element;
	int final_element;
	vector<int> possibilities{};
	array<vector<int>, 81> pattern{};
	array<vector<int>, 9> pattern_e{};

	print_sudoku(sudoku);

	while (!sudoku_is_done(sudoku)) {
		found_an_element = false;
		pattern = {};

		for (int idx = 0; idx < 81; ++idx) {
			if (sudoku[idx]) {
				pattern[idx].push_back(sudoku[idx]);
			}
			else {
				possibilities = {};
				for (int i = 1; i < 10; ++i) {
					if (in_arr(i, get_line(sudoku, idx / 9))) {
						continue;
					}
					if (in_arr(i, get_row(sudoku, idx % 9))) {
						continue;
					}
					if (in_arr(i, get_field(sudoku, (idx / 27) * 3 + (idx % 9) / 3))) {
						continue;
					}
					possibilities.push_back(i);
				}

				if (possibilities.empty()) {
					std::cerr << "ERROR :: no possibilities in line " << idx / 9 << ", row " << idx % 9 << "\n";
					return(1);
				}
				if (possibilities.size() == 1) {
					sudoku[idx] = possibilities[0];
					found_an_element = true;
					std::cout << "(" << idx / 9 + 1 << "/" << idx % 9 + 1 << ") : " << possibilities[0] << "\n";
					break;
				}
				pattern[idx] = possibilities;
			}
		}

		if (found_an_element) {
			continue;
		}

		for (int idx = 0; idx < 81; ++idx) {
			if (pattern[idx].size() <= 1) {
				continue;
			}

			final_element = 0;
			for (auto e = pattern[idx].begin(); e != pattern[idx].end(); ++e) {
				if (count(*e, get_line(pattern, idx / 9)) > 1 && count(*e, get_row(pattern, idx % 9)) > 1 &&
					count(*e, get_field(pattern, (idx / 27) * 3 + (idx % 9) / 3)) > 1) {
					continue;
				}
				final_element = *e;
				break;
			}

			if (final_element) {
				sudoku[idx] = final_element;
				found_an_element = true;
				std::cout << "(" << idx / 9 + 1 << "/" << idx % 9 + 1 << ") : " << final_element << "\n";
				break;
			}
		}

		if (!found_an_element) {
			std::cout << "ERROR :: multible solutions possible\n";
			break;
		}
	}

	print_sudoku(sudoku);

	return 0;
}



void print_sudoku(array<int, 81> sudoku) {
	for (int line = 0; line < 9; ++line) {
		for (int row = 0; row < 9; ++row) {
			if (sudoku[9 * line + row]) {
				std::cout << sudoku[9 * line + row] << " ";
			}
			else {
				std::cout << ". ";
			}
		}
		std::cout << "\n";
	}
}

array<int, 9> get_line(array<int, 81> arr, int l) {
	array<int, 9> line{};
	for (int i = 0; i < 9; ++i) {
		line[i] = arr[9 * l + i];
	}
	return line;
}

array<int, 9> get_row(array<int, 81> arr, int r) {
	array<int, 9> row{};
	for (int i = 0; i < 9; ++i) {
		row[i] = arr[9 * i + r];
	}
	return row;
}

array<int, 9> get_field(array<int, 81> arr, int f) {
	array<int, 9> field{};
	for (int i = 0; i < 9; ++i) {
		field[i] = arr[(f / 3) * 27 + (f % 3) * 3 + (i / 3) * 9 + (i % 3)];
	}
	return field;
}

array<vector<int>, 9> get_line(array<vector<int>, 81> arr, int l) {
	array<vector<int>, 9> line{};
	for (int i = 0; i < 9; ++i) {
		line[i] = arr[9 * l + i];
	}
	return line;
}

array<vector<int>, 9> get_row(array<vector<int>, 81> arr, int r) {
	array<vector<int>, 9> row{};
	for (int i = 0; i < 9; ++i) {
		row[i] = arr[9 * i + r];
	}
	return row;
}

array<vector<int>, 9> get_field(array<vector<int>, 81> arr, int f) {
	array<vector<int>, 9> field{};
	for (int i = 0; i < 9; ++i) {
		field[i] = arr[(f / 3) * 27 + (f % 3) * 3 + (i / 3) * 9 + (i % 3)];
	}
	return field;
}

bool sudoku_is_done(array<int, 81> sudoku) {
	for (auto i = sudoku.begin(); i != sudoku.end(); ++i) {
		if (!*i) {
			return false;
		}
	}
	return true;
}

bool in_arr(int x, array<int, 9> arr) {
	for (auto i = arr.begin(); i != arr.end(); ++i) {
		if (*i == x) {
			return true;
		}
	}
	return false;
}

int count(int x, array<vector<int>, 9> arr) {
	int counter = 0;
	for (int idx = 0; idx < 9; ++idx) {
		for (auto e = arr[idx].begin(); e != arr[idx].end(); ++e) {
			if (x == *e) {
				++counter;
			}
		}
	}
	return counter;
}