#include<iostream>
#include"doublyLinkedList.h"

using namespace std;

int menu() {
	int operation = -1;
	cout<<endl<< endl <<"\t----------------------------------------------------";
	while (operation < 0 || operation > 7) {
		cout << "\n\t 0 : Exist";
		cout << "\n\t 1 : Enter Element in linked list";
		cout << "\n\t 2 : Concatinate two list";
		cout << "\n\t 3 : Sum two list";
		cout << "\n\t 4 : sort any List";
		cout << "\n\t 5 : Print List with the help of next Pointer";
		cout << "\n\t 6 : Print List with the help of previous Pointer\n\t------>> ";
		
		cin >> operation;
		system("CLS");
	}
	return operation;
}


int main() {
	doubly_linked_list<int> list1;
	doubly_linked_list<int> list2;
	doubly_linked_list<int> list3;
	bool islist1_1stNode= true;
	bool islist2_1stNode = true;

	int operation = -1;
	while(operation) {
		operation = menu();
		if (operation == 1) { // Insert data
			int choice = -1;
			int data = 11;
			while (choice < 0 || choice>=2) {
				cout << "\n 0: insert in list1";
				cout << "\n 1: insert in list2";
				cout << "\n------>> ";
				cin >> choice;
			}
			if (choice == 0) {
				if (islist1_1stNode == true) { // check 1st node enter or not for sign 
					while (data >= 10) {
						cout << "\n Enter data : ";
						cin >> data;
					}
					islist1_1stNode = false;
				}
				else {
					while (data < 0|| data >=10) {
						cout << "\n Enter data : ";
						cin >> data;
					}
				}
				list1.insertAtEnd(data);
			}
			else {
				if (islist2_1stNode == true) { // check 1st node enter or not for sign 
					while (data >= 10) {
						cout << "\n Enter data : ";
						cin >> data;
					}
					islist2_1stNode = false;
				}
				else {
					while (data < 0 || data >= 10) {
						cout << "\n Enter data : ";
						cin >> data;
					}
				}
				list2.insertAtEnd(data);
			}

		}
		else if (operation == 2) { //  sort list
			int choice = -1;
			while (choice < 0 || choice >= 2) {
				cout << "\n 0: concatinate list1 and list2 with out sort";
				cout << "\n 1: concatinate list1 and list2 with sort";
				cout << "\n------>> ";
				cin >> choice;
			}
			list3 = list2.concatenate(list1, choice);
		}
		else if (operation == 3) { // add 2 list
			list3 = (list1 + list2);
		}
		else if (operation == 4) {
			int choice = -1;
			while (choice < 0 || choice >= 3) {
				cout << "\n 0: sort list1 ";
				cout << "\n 1: sort list2 ";
				cout << "\n 2: sort list3 ";
				cout << "\n------>> ";
				cin >> choice;
			}
			if (choice == 0) {
				list1.sort();
			}
			else if (choice == 1) {
				list2.sort();
			}
			else if (choice == 2) {
				list3.sort();
			}
		}
		else if (operation == 5) {
			cout << "\n List1 :";
			list1.print();
			cout << "\n\n List2 :";
			list2.print();
			cout << "\n\n List3 :";
			list3.print();
		}
		else if (operation == 6) {
			cout << "\n List1 :";
			list1.printI();
			cout << "\n\n List2 :";
			list2.printI();
			cout << "\n\n List3 :";
			list3.printI();
		}
	}


	return 0;
}