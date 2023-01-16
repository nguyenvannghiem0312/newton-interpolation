#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;

typedef struct Node {
    char s;
    struct Node* next;
    struct Node* pre;
    Node(char a){
        s = a;
        next = NULL;
        pre = NULL;
    }
} Node;

typedef struct List{
    Node* head;
    Node* tail;
    List(){
        head = NULL;
        tail = NULL;
    }
} List;

List L = List();
Node* curr_node = L.head;
string s;
int posInter = 4, xPos = 0, yPos = 0;

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h,c);
}

void design(){
	gotoxy(80, 0);
	cout << "Undo: <-";
	gotoxy(80, 1);
	cout << "Redo: ->";
	gotoxy(80, 2);
	cout << "Press Enter to start Interactive";
	gotoxy(80, 3);
	cout << "Press Enter again to end Interactive";
}

void addTail(Node* node){
    if(L.head == NULL){
        L.head = node;
        L.tail = node;
    }
    else{
        node->pre = L.tail;
        L.tail->next = node;
        L.tail = node;
    }
}

void inputList(){
	getline(cin, s);
	for(char a : s){
		Node* node = new Node(a);
    	addTail(node);
	}
    xPos += s.length();
	curr_node = L.tail;
	gotoxy(xPos, yPos);
}

void undoList(){
    curr_node = curr_node->pre;
    cout << "\b \b";   
    xPos--;
}

void redoList(){
	curr_node = curr_node->next;
    cout << curr_node->s;
    xPos++;
}

void Interactive(){
	while(true){
		int n;
		n = getch();
		if(n == 75 && xPos >= 1){
			gotoxy(80, posInter++);
			cout << "Undo";
			gotoxy(xPos, yPos);
			undoList();
		}
		else if(n == 77 && xPos < s.length()){
			gotoxy(80, posInter++);
			cout << "Redo";
			gotoxy(xPos, yPos);
			redoList();
		}
		else if(n == 13){
			gotoxy(80, posInter++);
			cout << "Finish";
			exit(0);
		}
	}
}


int main(){
	system("cls");
	design();
	gotoxy(0, 0);
	inputList();
    Interactive();
}
