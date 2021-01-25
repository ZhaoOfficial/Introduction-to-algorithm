#include<iostream>
#include<random>
#include<time.h>

using namespace std;

typedef struct Node {
	int data;
	int secret;
	struct Node* next;
}Node;

Node* create(int n) {
	if (n > 0) {
		Node* p = nullptr;
		Node* head = (Node*)malloc(sizeof(Node));
		if (!head) {
			exit(1);
		}

		p = head;
		p->data = 1;
		p->secret = rand() % 9 + 2;

		for (int i = 1; i < n; i++) {
			Node* one = (Node*)malloc(sizeof(Node));
			if (!one) {
				exit(1);
			}
			p->next = one;
			p = p->next;
			p->data = i + 1;
			p->secret = rand() % 9 + 2;
		}

		p->next = head;
		return head;
	}
	else {
		return nullptr;
	}
}

void destroy(Node* head, int n) {
	Node* temp;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j < head->secret - 1; j++) {
			head = head->next;
		}

		cout << head->next->data << "->";
		temp = head->next;
		head->next = temp->next;
		free(temp);
		if (head->next == head) {
			cout << head->next->data;
			free(head);
			return;
		}
		head = head->next;
	}

}

int main() {
	srand(time(0));
	int n;
	scanf("%d", &n);

	Node* list = create(n);
	destroy(list, n);

	return 0;
}
