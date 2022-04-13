#include <iostream>
#include "matrix.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	matrix::NodeList list;
	//list.generateRandomMatrix();
	int op;
	bool read = false;
	while (true) {
		std::cout << "Головне меню." << std::endl;
		std::cout << "Введіть 0, щоб зчитати матрицю із файлу \"input.txt\"." << std::endl;
		std::cout << "	Друк матриці:" << std::endl;
		std::cout << "1 - роздрукувати її як матрицю 100 * 100," << std::endl;
		std::cout << "2 - її зв'язано-стисле подання," << std::endl;
		std::cout << "3 - її послідовно-зв'язане індексне подання," << std::endl;
		std::cout << "4 - записати результат в файл \"output.txt\"." << std::endl;
		std::cout << "	Операції з матрицями з файлів \"input.txt\" та \"input1.txt\":" << std::endl;;
		std::cout << "5 - множення," << std::endl;
		std::cout << "6 - додавання." << std::endl << std::endl;
		std::cout << "7 - вийти із програми." << std::endl;
		std::cin >> op;
		std::cout << std::endl;
		if (!read && op) {
			std::cout << "Спочатку зчитайте матрицю!" << std::endl;
		}
		else if (!op || read)
		{
			switch (op) {
			case 0:
				list.readFromFile();
				std::cout << "Матриця успішно зчитана з файлу \"input.txt\"." << std::endl << std::endl;
				read = true;
				break;
			case 1:
				list.printMatrix(1);
				break;
			case 2:
				list.printMatrix(2);
				break;
			case 3:
				list.printMatrix(3);
				break;
			case 4:
				list.saveToFile(); 
				std::cout << "Матриця успішно збережена до файлу \"output.txt\"." << std::endl << std::endl;
				break;
			case 5:
				list.mult();
				std::cout << "Множення успішне. Для перегляду добутку введіть 1, 2 або 3." << std::endl << std::endl;
				break;
			case 6:
				list.add();
				std::cout << "Додавання успішне. Для перегляду суми введіть 1, 2 або 3." << std::endl << std::endl;
				break;
			case 7:
				return 0;
				break;
			}
		}
	}
	return 0;
}
