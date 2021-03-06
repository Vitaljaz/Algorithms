#include <iostream>
#include <fstream>
#include <algorithm>
#include "list.h"
#include "stack.h"
#include <string>

int main()
{
	Stack *stack = stack_create();
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::string inputData = "";
	if (fin) {
		while (!fin.eof()) {
			std::getline(fin, inputData);
			std::transform(inputData.begin(), inputData.end(), inputData.begin(), ::tolower);
			if (inputData.find("/") == 1) {
				if (stack_empty(stack)) {
					fout << "NO";
					exit(1);
				}
				std::string tmp = inputData;
				tmp.erase(remove(tmp.begin(), tmp.end(), '/'), tmp.end());
				std::string string_from_stack = stack_get(stack);
				if (tmp.compare(string_from_stack) == 0) {
					stack_pop(stack);
				}
				else {
					stack_push(stack, inputData);
				}
			}
			else {
				stack_push(stack, inputData);
			}
		}
	}
	else {
		std::cout << "File cannot be opened :(.";
		exit(1);
	}
	if (stack_empty(stack))  fout << "YES";
	if (!stack_empty(stack)) fout << "NO";
	fin.close();
	fout.close();
	stack_delete(stack);
	return 0;
}
