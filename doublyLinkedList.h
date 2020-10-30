#ifndef doubly_Linked_list_H
#include<iostream>
using namespace std;
template<class T>
class doubly_linked_list {
private:
	template<class T>
	class Node {

	public:
		T data;
		Node<T> * next;
		Node<T> * prev;
		Node() {
			data = 0;
			next = NULL;
			prev = NULL;
		}
		~Node() {
			data = 0;
			if (next != NULL) {
				next = NULL;
			}
			if (prev != NULL) {
				prev = NULL;
			}
		}
	};
	Node<T> * head;
	int matchLinkedList(doubly_linked_list<T> & const LHS) {
		int size1 = this->size(); // store caller linked list size;
		int size2 = LHS.size(); // store LHS object size;
		if (size1 > size2) {
			return 1;
		}
		else if (size1 > size2) {
			return 2;
		}
		else {
			for (int i = 0; i < size1; i++) {
				if (this->getData(i) > LHS.getData(i)) {
					return 1;
				}
				else if (this->getData(i) <= LHS.getData(i)) {
					return 2;
				}
			}
			return 0;
		}
	}
	int matchSymbol(doubly_linked_list<T> & LHS) { // indicate We need to subtract two number or add two number
		if ((this->getData(0) < 0) && (LHS.getData(0) < 0)) { // means both list are negative
			return 0;
		}
		else if ((this->getData(0) > 0) && (LHS.getData(0) > 0)) {
			return 1;
		}
		else if ((this->getData(0) > 0) && (LHS.getData(0) < 0)) {
			return 2;
		}
		else
			return 3;
	}
	doubly_linked_list<T> Subtraction(doubly_linked_list<T> & const LHS) {
		doubly_linked_list<T> subtraction; // store actual answer
		Node<T> * tempLarge = NULL; // point toaward largest list
		Node<T> * tempSmall = NULL;  // point toward small list
		doubly_linked_list<T> * tempDoublySmall = NULL;
		int smallListSize;// total nodes attached with small linked list
		if (size() >= LHS.size()) { // check which list size
			tempLarge = this->head;
			tempSmall = LHS.head;
			tempDoublySmall = &LHS;
			smallListSize = LHS.size(); // total nodes attached with small linked list
		}
		else {
			smallListSize = size(); // total nodes attached with small linked list
			tempLarge = LHS.head;
			tempDoublySmall = this;
			tempSmall = this->head;
		}
		while (tempLarge != NULL) { // insert data of larger list inTO subtraction list
			subtraction.insertAtEnd(tempLarge->data);
			tempLarge = tempLarge->next;
		}
		
		int subtractSize = subtraction.size(); // total nodes attached with subtraction
		int carry = 1;
		int i; // indicate how many nodes have been added
		for (i = 0; i < smallListSize; i++) { // subtract small list with respective node of larger list
			// match 1st node data with 2nd node if same then no carry and multiply
			if (subtraction.getData(subtractSize - i) >= tempDoublySmall->getData(smallListSize - i)) {
				int tempSubtraction = subtraction.getData(subtractSize - i) - tempDoublySmall->getData(smallListSize - i);
				subtraction.setData(subtractSize - i, tempSubtraction);
				carry = 0;
			}

			else {//take carry from the previous node and then subtract;
				if (carry != 0) { 
					int tempValue = subtraction.getData(subtractSize-i-1) - 1;
					subtraction.setData(subtractSize - i-1, tempValue);
				}
				subtraction.setData(subtractSize - i, (subtraction.getData(subtractSize - i) + 10));
				int tempSubtraction = subtraction.getData(subtractSize - i) - tempDoublySmall->getData(smallListSize - i);
				subtraction.setData(subtractSize - i, tempSubtraction);
				carry = 1;
			}	
		}
		return subtraction;
	}

	doubly_linked_list<T> add(doubly_linked_list<T> & const obj) {
		doubly_linked_list<T> sum;
		if (this->head != NULL && obj.head != NULL) {
			Node<T> * tempLarge = NULL;//point toaward largest list
			Node<T> * tempSmall = NULL;  // point toward small list
			doubly_linked_list<T> * tempDoublySmall = NULL;
			int smallListSize;// total nodes attached with small linked list
			if (size() >= obj.size()) { // check which list size
				tempLarge = head;
				tempSmall = obj.head;
				tempDoublySmall = &obj;
				smallListSize = obj.size(); // total nodes attached with small linked list
			}
			else {
				smallListSize = size(); // total nodes attached with small linked list
				tempLarge = obj.head;
				tempDoublySmall = this;
				tempSmall = head;
			}
			while (tempLarge != NULL) { // insert data of larger list inTO sum list
				sum.insertAtEnd(tempLarge->data);
				tempLarge = tempLarge->next;
			}
			int sumSize = sum.size(); // total nodes attached with sum
			int carry = 0;
			int i; // indicate how many nodes have been added
			for (i = 0; i < smallListSize; i++) { // add small list with respective node of larger list
				int tempSum = sum.getData(sumSize - i) + tempDoublySmall->getData(smallListSize - i) + carry;
				carry = tempSum / 10;
				tempSum = tempSum % 10;
				sum.setData(sumSize - i, tempSum);
			}
			if (carry != 0) {//check carry present or not after adding samll list
				while (i < sumSize) {
					int tempSum = sum.getData(sumSize - i) + carry;
					carry = tempSum / 10;
					tempSum = tempSum % 10;
					sum.setData(sumSize - i, tempSum);
					i++;
				}
				if (carry != 0) {//if all nodes added but still carry exist 
					sum.insertAtStart(carry);
				}
			}

		}
		sum.print();
		return sum;
	}
public:
	doubly_linked_list() {
		head = NULL;
	}
	doubly_linked_list(doubly_linked_list & d) {
		head = NULL;
		if (d.head != NULL) {
			Node<T> * temp = d.head;
			while (temp != NULL) {
				this->insertAtEnd(temp->data);
				temp = temp->next;
			}
		}
	}

	void insertAtStart(T data) {
		Node<T> * temp = new Node<T>;
		temp->data = data;
		if (head == NULL) {
			head = temp;
		}
		else {
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
	}
	void insertAtEnd(T data) {
		if (head == NULL) {
			head = new Node<T>;
			head->data = data;
		}
		else {
			Node<T> *temp = head;
			while (temp->next != NULL) {
				temp = temp ->next;
			}
			Node<T> * newNode = new Node<T>;
			newNode->data = data;
			temp->next = newNode;
			newNode->prev = temp;
		}
	}
	int size() { // return size of linked list
		int size = 0;
		Node<T> *temp = NULL;
		temp = head;
		while (temp != NULL) { // count size of linked list
			size++;
			temp = temp->next;
		}
		return size;
	}
	void InsertAtPlace(T data, int k) {
		Node<T> * temp = head;
		int i;
		for ( i = 0; ((i < k) && (k < size())); i++) {
			temp = temp->next;
		}
		if (k == 0) {
			insertAtStart(data);
		}
		else if (k>=size()) {
			insertAtEnd(data);
		}
		else { // insert data in mid
			Node<T> * newNode = new Node<T>;
			newNode->data = data;
			newNode->next = temp;
			newNode->prev = temp->prev;
			temp->prev->next = newNode;
			newNode->next = temp;
		}
	}
	doubly_linked_list&  concatenate(doubly_linked_list & list, int opetion) {
		//concatinate two un-ordered doubly linked lists into one
		Node<T> * temp = head;
		doubly_linked_list<T> * Concatenate = new doubly_linked_list < T>;
		while (temp != NULL) { // store data of 1st list into cancatenate list
			Concatenate->insertAtEnd(temp->data);
			temp = temp->next;
		}
		temp = list.head;
		while (temp != NULL) { //store data of second list into cancatenate list
			Concatenate->insertAtEnd(temp->data);
			temp = temp->next;
		}
	
		if (opetion == 1) { // concatenate with sort
			Concatenate->sort();
		}
		return *Concatenate;
	}
	void sort() {
		int index = 0;// indicate how many nodes has been sorted
		int Size = size();
		Node<T>* temp = head;
		for (int i = 1; i <= Size; i++) { // move temp forward
			Node<T> * temp2 = temp; 

			for (int j = i; j <= Size; j++) { //move temp2 node forward
				if (temp->data > temp2->data) {
					swap(i, j);
					//swap temp1 and temp2
					//Bcz when we swap nodes temp and temp2 also swap
					Node<T> * temp3 = temp2; 
					temp2 = temp;
					temp = temp3;
				}
				temp2 = temp2->next;

			}
			index++;
			temp = temp->next;
		}
	}
	
	void swap(T x, T y) {
		int Size = size(); //find how many node are attached with head
		if (x <= 0 || x > Size || y <= 0 || y > Size) {
			cout << "\n Plese check nodes bcz input index not found :( ";
		}
		else if (x != y) { // check both input index are same if yes then terminate
			int t1, t2;
			if (x < y) {
				t1 = x;
				t2 = y;
			}
			else {
				t1 = y;
				t2 = x;
			}
			x = t1;
			y = t2;

			Node<T> *fNPrevious = NULL; // store the previous of first node
			Node<T> *fCNode = head; // first curent node that we want to swap
			Node<T> *sNPrevious = NULL; //point the previous node of the second node
			Node<T> *sCNode = head; // point second node that we want to swap with firstNode
			int fNode = 1;
			while (fCNode != NULL && x != fNode) { // find first node which we want to swap 
				fNode++;
				fNPrevious = fCNode; // store previous of the first Node
				fCNode = fCNode->next;
			}
			fNode = 1;
			while (sCNode != NULL && y != fNode) { // find second node which we want to swap
				sNPrevious = sCNode; // store previous of 2nd NOde
				fNode++;
				sCNode = sCNode->next;
			}
			if (fNPrevious == NULL) { //If first nod is head
				sCNode->prev = NULL;
				head = sCNode;
			}
			else {
				fNPrevious->next = sCNode;
				sCNode->prev = fNPrevious;
			}
			if (sNPrevious != NULL) { // list consist of just 1 node?
				sNPrevious->next = fCNode;
				fCNode->prev = sNPrevious;
			}
			Node<T> *temp = sCNode->next; // use to swap the pointer; //sCNode->next;
			sCNode->next = fCNode->next;
			fCNode->next->prev = sCNode;

			fCNode->next = temp;

			if (temp != NULL) { // check 2nd node is last NOde?
				temp->prev = fCNode;
			}
			if (fCNode->next != NULL) { // check 1st Node is going to become a last Node;
				fCNode->next->prev = fCNode;
			}
		}
	}
	void deleteNode(int p) { // delete node wih position
		Node<T> * temp = new Node < T>;
		Node<T> * tempPre = new Node<T>;
		if (head != NULL) {
			if (p == 0) { // if we want to delete 1st node
				temp->prev = NULL;
				temp = head->next;
				delete head;
				head = temp;
			}
			else if (p == size()-1) { // delete last NOde
				while (temp->next != NULL) {
					tempPre = temp;
					temp = temp->next;
				}
				tempPre->next = NULL;
				temp->prev = NULL;
				delete temp;
			}
			else { // delete form middle
				while (temp->next != NULL) {
					tempPre = temp; // previous node of temo which we wnt to delete
					temp = temp->next; // node that we want to delete
				}
				tempPre->next = temp->next;
				if (tempPre->next != NULL) {
					temp->next->prev = temp->prev;
				}
				delete temp;
			}
		}
	}
	void print() { // print list with the help of next pointer
		Node<T> * temp = head;
		cout << endl;
		while (temp != NULL) {
			cout << temp->data<<" ";
			temp = temp->next;
		}
		if (head == NULL) {
			cout << "\n Empty :(";
		}
	}
	void printI() { // print with the help of previous pointer
		Node<T> * temp = head;
		if (head != NULL) {
			while (temp->next != NULL) {
				temp = temp->next;
			}
		}
		else {
			cout << "\n Empty :(";
		}
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->prev;
		}
	}
	int getData(int num) {// return data of kth node
		int Size = size();
		if (num >= 0 && num <= Size) {
			Node<T> * temp = head;
			for (int i = 1; i < num; i++) { // find kth node
				temp = temp->next;
			}
			return temp->data; // return data of kth node
		}
	}
	void setData(int num, int data) { // insert data in kth node
		int Size = size();
		if (num >= 0 && num <= Size) {
			Node<T> * temp = head;
			for (int i = 1; i < num; i++) { // find the kth node 
				temp = temp->next;
			}
			temp->data = data; // enter data in kth node
		}
	}
	doubly_linked_list<T> operator = (doubly_linked_list<T>const & lhs);
	doubly_linked_list<T> operator + (doubly_linked_list<T> lhs);
	~doubly_linked_list() {
		for (int i = 0; head != NULL; i++) {
			deleteNode(0);
		}
	}
};

template<class T>
doubly_linked_list<T> doubly_linked_list<T>:: operator = (doubly_linked_list<T>const& lhs) {
	if (head != NULL) { // if head not empty make it empty
		Node<T> * temp = this-> head;
		int Size = this->size();
		for (int i = 0; i < Size; i++) { // delete first node one by one
			this->deleteNode(0);
		}
	}
	Node<T> * temp = lhs.head;
	while (temp != NULL) { // insert data of L.H.S list into R.H.S list
		insertAtEnd(temp->data);
		temp = temp->next;
	}
	return *this;
}

template<class T>
doubly_linked_list<T> doubly_linked_list<T>:: operator + (doubly_linked_list<T> obj) {
	bool anyLinkEmpty = false;
	doubly_linked_list<T> Sum;
	if (this->head == NULL && obj.head != NULL) { // if caller list Null but second !NULL
		Node<T> * temp = obj.head;
		while (temp != NULL) { // insert second list data into sum list
			Sum.insertAtEnd(temp->data);
			temp = temp->next;
		}
		anyLinkEmpty = true;
	}
	else if (this->head != NULL && obj.head == NULL) {// if caller !NULL nut second NULL
		Node<T> * temp = this->head;
		while (temp != NULL) { // insert 1st list data into sum list
			Sum.insertAtEnd(temp->data);
			temp = temp->next;
		}
		anyLinkEmpty = true;
	}
	if (anyLinkEmpty == false) {
		int opetion = this->matchSymbol(obj);
		if (opetion == 0) { // if both list are consist on negative Number
			// make 1st node of +ve
			int data1 = this->getData(0) * -1;
			this->setData(0, data1);
			data1 = obj.getData(0) * -1;
			obj.setData(0, data1);
			//make 1st node of sum negative;

			Sum = this->add(obj);
			data1 = Sum.getData(0) * -1;
			Sum.setData(0, data1);
			// again make 1st node -ve
			data1 = this->getData(0) * -1;
			this->setData(0, data1);
			data1 = obj.getData(0) * -1;
			obj.setData(0, data1);
		}
		else if (opetion == 1) { // if both are positive number
			Sum = this->add(obj);
		}

		else if (opetion == 2) { // if 1st is +ve and 2nd -ve
			//make 2nd node + ve;
			int data1 = obj.getData(0) * -1;
			obj.setData(0, data1);
			int largerList = matchLinkedList(obj);
			if (largerList == 1) {
				Sum = this->Subtraction(obj);
			}
			else if (largerList == 2) {
				Sum = obj.Subtraction(*this);
				data1 = Sum.getData(0) * -1;
				Sum.setData(0, data1);
			}
			// now again change 2nd list sign
			data1 = obj.getData(0) * -1;
			obj.setData(0, data1);
		}
		else {// if 1st is -ve and 2nd +ve;
			//make 1st node + ve;
			int data1 = this->getData(0) * -1;
			this->setData(0, data1);
			int largerList = matchLinkedList(obj);
			if (largerList == 2) {
				Sum = obj.Subtraction(*this);
			}
			else if (largerList == 1) {
				Sum = this->Subtraction(obj);
				data1 = Sum.getData(0) * -1;
				Sum.setData(0, data1);
			}
			// now again change 1st list sign
			data1 = this->getData(0) * -1;
			this->setData(0, data1);
		}
	}
	//Sum.print();
	return Sum;
}
#endif // !doubly_Linked_list_H
