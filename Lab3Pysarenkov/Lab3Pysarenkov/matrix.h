#pragma once

namespace matrix {
	struct NodeList {
	private:
		struct ColumnNode {
			int value;
			ColumnNode* next;
			ColumnNode(int value);
		};
		struct RowNode {
			ColumnNode* col;
			RowNode* next;
			RowNode(ColumnNode* col);
		};
		struct INode {
			int i, j, value;
			INode* next;
			INode(int i, int j, int value);
		};
		struct SNode {
			int j, value;
			SNode* next;
			SNode(int j, int value);
		};
		SNode* slist[100];
		INode* ihead = nullptr;
		INode* itail = nullptr;
		/*RowNode* rhead = nullptr;
		RowNode* rtail = nullptr;
		ColumnNode* chead = nullptr;
		ColumnNode* ctail = nullptr;*/
	public:
		void readFromFile();
		void printMatrix(int op);
		void saveToFile();
		void add();
		void mult();
		void generateRandomMatrix();
	};
}