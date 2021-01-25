#include<iostream>

using namespace std;

typedef struct Node {
	int card;
	struct Node* next;
}Node;

Node* create(int n) {
	Node* p = nullptr;
	Node* head = (Node*)malloc(sizeof(Node));
	if (!head) {
		exit(1);
	}
	p = head;
	p->card = 0;

	for (int i = 1; i < n; i++) {
		Node* one = (Node*)malloc(sizeof(Node));
		if (!one) {
			exit(1);
		}
		p->next = one;
		p = p->next;
		p->card = 0;
	}

	p->next = head;
	return head;
}

Node* change(Node* head) {
	Node* temp = head;
	for (int i = 1; i <= 13; i++) {
		head->card = i;
		for (int j = 1; j <= i; j++) {
			if (head->card == 0)
				head = head->next;
			else
				head = head->next->next;
		}
		while (head->card) {
			head = head->next;
		}
	}

	return temp;
}

void print(Node* head, int n) {

	for (int i = 1; i < n; i++) {
		cout << head->card << "->";
		head = head->next;
	}
	cout << head->card;
}

void destory(Node* head, int n) {
	Node* temp;

	for (int i = 1; i <= n; i++) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main() {
	int n = 54;

	Node* list = create(n);
	list = change(list);
	print(list, n);
	destory(list, n);

	return 0;
}