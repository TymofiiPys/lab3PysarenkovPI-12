#include <iostream>
#include "matrix.h"
#include <fstream>
#include <string>

void matrix::NodeList::readFromFile() {
	std::ifstream mfile("input.txt");
	/*rhead = nullptr;
	rtail = nullptr;*/
	ihead = nullptr;
	itail = nullptr;
	int i, j, x;
	for (i = 0; i < 100; i++) {
		slist[i] = nullptr;
	}
	i = 0;
	while (!mfile.eof()) {
		std::string row;
		std::getline(mfile, row);
		j = 0;
		SNode* shead = nullptr;
		SNode* stail = nullptr;
		while (j < 100)
		{
			x = 0;
			if (row[7 * j] != '0') {
				int k = 7 * j;
				std::string xs = "";
				while (row[k] != ' ') {
					xs += row[k];
					k++;
				}
				x = std::stoi(xs);
				//Побудова зв'язаного стислого зберігання
				INode* in = new INode(i, j, x);
				if (!ihead)
				{
					ihead = in;
					itail = in;
				}
				else {
					itail->next = in;
					itail = in;
				}
				//Побудова послідовно-зв'язаного індексного зберігання
				SNode* sn = new SNode(j, x);
				if (!shead) {
					shead = sn;
					stail = sn;
				}
				else {
					stail->next = sn;
					stail = sn;
				}
			}
			j++;
		}
		slist[i] = shead;
		i++;
	}
	mfile.close();
	/*for (i = 0; i < 100; i++) {
		SNode* iter = slist[i];
		while (iter) {
			std::cout << "(" << iter->j << ", " << iter->value << ") ";
			iter = iter->next;
		}
		std::cout << std::endl;
	}*/
}

void matrix::NodeList::printMatrix(int op) {
	INode* iter = ihead;
	int i, j;
	switch (op) {
	case 1:
		int A[100][100];
		for (i = 0; i < 100; i++) {
			for (j = 0; j < 100; j++) {
				A[i][j] = 0;
			}
		}
		for (i = 0; i < 100; i++) {
			SNode* iter = slist[i];
			while (iter) {
				A[i][iter->j] = iter->value;
				iter = iter->next;
			}
		}
		for (i = 0; i < 100; i++) {
			for (j = 0; j < 100; j++) {
				std::cout << A[i][j] << " ";
			}
			std::cout << std::endl;
		}
		break;
	case 2:
		while (iter) {
			std::cout << "(" << iter->i << ", " << iter->j << ", " << iter->value << ")\n";
			iter = iter->next;
		}
		break;
	case 3:
		for (i = 0; i < 100; i++) {
			SNode* iter = slist[i];
			while (iter) {
				std::cout << "(" << iter->j << ", " << iter->value << ") ";
				iter = iter->next;
			}
			std::cout << std::endl;
		}
		break;
	}
}

void matrix::NodeList::saveToFile() {
	std::ofstream mfile;
	mfile.open("output.txt", std::ofstream::out | std::ofstream::trunc); //очистка файлу від тексту
	mfile.clear();
	std::string row, val;
	int lval;
	for (int i = 0; i < 100; i++) {
		row = "";
		SNode* iter = slist[i];
		for (int j = 0; j < 100; j++)
		{
			val = "";
			if (j == iter->j) {
				val += std::to_string(iter->value);
				lval = val.length();
				for (int k = 0; k < 7 - lval; k++) {
					val += " ";
				}
				row += val;
			}
			else
				row += "0      ";
		}
		mfile << row;
		if (i < 99)
			mfile << "\n";
	}
	mfile.close();
}

void matrix::NodeList::add() {
	//Конвертуємо послідовно-зв'язане індексне представлення в звичайний масив
	int A[100][100];
	int i, j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			A[i][j] = 0;
		}
	}
	for (i = 0; i < 100; i++) {
		SNode* iter = slist[i];
		while (iter) {
			A[i][iter->j] = iter->value;
			iter = iter->next;
		}
	}
	//Зчитуємо другий масив одразу в звичайний масив, бо одразу після додавання він нам не буде потрібний, а результат суми буде записаний в slist[].
	int B[100][100], x;
	std::ifstream mfile("input1.txt");
	i = 0;
	while (!mfile.eof()) {
		std::string row;
		std::getline(mfile, row);
		j = 0;
		while (j < 100)
		{
			x = 0;
			if (row[7 * j] != '0') {
				int k = 7 * j;
				std::string xs = "";
				while (row[k] != ' ') {
					xs += row[k];
					k++;
				}
				x = std::stoi(xs);
			}
			B[i][j] = x;
			j++;
		}
		i++;
	}
	//Обнуляємо slist[], ihead для того, щоб видалити дані про старий масив і записати дані про новий
	for (i = 0; i < 100; i++) {
		slist[i] = nullptr;
	}
	ihead = nullptr;
	for (i = 0; i < 100; i++)
	{
		SNode* shead = nullptr;
		SNode* stail = nullptr;
		for (j = 0; j < 100; j++) {
			A[i][j] += B[i][j];
			if (A[i][j]) {
				x = A[i][j];
				INode* in = new INode(i, j, x);
				if (!ihead)
				{
					ihead = in;
					itail = in;
				}
				else {
					itail->next = in;
					itail = in;
				}
				SNode* sn = new SNode(j, x);
				if (!shead) {
					shead = sn;
					stail = sn;
				}
				else {
					stail->next = sn;
					stail = sn;
				}
			}
		}
		slist[i] = shead;
	}
	mfile.close();
}

void matrix::NodeList::mult() {
	//Конвертуємо послідовно-зв'язане індексне представлення в звичайний масив
	int A[100][100];
	int i, j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			A[i][j] = 0;
		}
	}
	for (i = 0; i < 100; i++) {
		SNode* iter = slist[i];
		while (iter) {
			A[i][iter->j] = iter->value;
			iter = iter->next;
		}
	}
	int B[100][100], x;
	std::ifstream mfile("input1.txt");
	i = 0;
	while (!mfile.eof()) {
		std::string row;
		std::getline(mfile, row);
		j = 0;
		while (j < 100)
		{
			x = 0;
			if (row[7 * j] != '0') {
				int k = 7 * j;
				std::string xs = "";
				while (row[k] != ' ') {
					xs += row[k];
					k++;
				}
				x = std::stoi(xs);
			}
			B[i][j] = x;
			j++;
		}
		i++;
	}
	for (i = 0; i < 100; i++) {
		slist[i] = nullptr;
	}
	ihead = nullptr;
	int k;
	int C[100][100];
	for (i = 0; i < 100; i++)
	{
		SNode* shead = nullptr;
		SNode* stail = nullptr;
		for (j = 0; j < 100; j++) {
			x = 0;
			for (k = 0; k < 100; k++) {
				x += A[i][k] + B[k][j];
			}
			C[i][j] = x;
			if (x) {
				INode* in = new INode(i, j, x);
				if (!ihead)
				{
					ihead = in;
					itail = in;
				}
				else {
					itail->next = in;
					itail = in;
				}
				SNode* sn = new SNode(j, x);
				if (!shead) {
					shead = sn;
					stail = sn;
				}
				else {
					stail->next = sn;
					stail = sn;
				}
			}
		}
	}
	mfile.close();
}

void matrix::NodeList::generateRandomMatrix() {
	int a[100][100];
	std::ofstream mfile("input.txt");
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{
			if (rand() - 24576 < 0)
				a[i][j] = 0;
			else
				a[i][j] = (int)(rand() / 3276) /*+ (int)(rand()/3276)*/;
		}
	std::string line;
	for (int i = 0; i < 100; i++)
	{
		line = "";
		for (int j = 0; j < 100; j++)
		{
			line += std::to_string(a[i][j]) + "     ";
			if (a[i][j] < 10)
				line += " ";
		}
		const char* x = line.c_str();
		mfile << x;
		mfile << "\n";
	}

}

matrix::NodeList::INode::INode(int i, int j, int value) {
	this->i = i;
	this->j = j;
	this->value = value;
	this->next = nullptr;
}

matrix::NodeList::SNode::SNode(int j, int value) {
	this->j = j;
	this->value = value;
	this->next = nullptr;
}

matrix::NodeList::RowNode::RowNode(ColumnNode *col)
{
	this->col = col;
	this->next = nullptr;
}

matrix::NodeList::ColumnNode::ColumnNode(int value)
{
	this->value = value;
	this->next = nullptr;
}