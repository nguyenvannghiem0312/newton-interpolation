#include <iostream>
#include <cmath>
using namespace std;

typedef struct Node {
    int degree;
    int coeff;
    struct Node* next;
    Node(int d, int c){
        degree = d;
        coeff = c;
        next = NULL;
    }
} Node;

typedef struct Poly{
    Node* head;
    Node* tail;
    Poly(){
        head = NULL;
        tail = NULL;
    }
} Poly;

void addTail(Poly &P, Node* node);
void inputPoly(Poly& P);
void printPoly(Poly P);
void calculateP(int x, Poly P);
void derivative(Poly P);

int main(){
    Poly P = Poly();
    inputPoly(P);
    printPoly(P);
    int x;
    cout << "Nhap x = "; cin >> x; 
    calculateP(x, P);
    derivative(P);
}

void addTail(Poly &P, Node* node){
    if(P.head == NULL){
        P.head = node;
        P.tail = node;
    }
    else{
        P.tail->next = node;
        P.tail = node;
    }
}

void inputPoly(Poly& P){
    int n;
    cout << "Nhap bac cua da thuc: "; cin >> n;
    for(int i = 0; i <= n; i++){
        int coeff;
        cout << "Nhap he so cua x^[" << i << "] : "; cin >> coeff;
        Node* node = new Node(i, coeff);
        addTail(P, node);
    }
}

void printPoly(Poly P){
    cout << "P(x) = ";
    for(Node* p = P.head; p != NULL; p = p->next){
        if(p->coeff == 0) continue;
        if(p == P.head) cout << p->coeff;
        else{
            if(p->coeff > 0) cout << " + " ;
            else cout << " - ";
            cout << abs(p->coeff) << "x^[" << p->degree << "]";
        }
    }
    cout << endl;
}

void calculateP(int x, Poly P){
    int value = 0;
    for(Node* p = P.head; p != NULL; p = p->next){
        int y = pow(x, p->degree);
        value += p->coeff * y;
    }
    cout << "P(" << x << ") = " << value << endl;
}

void derivative(Poly P){
    cout << "P'(x) = ";
    for(Node* p = P.head; p != NULL; p = p->next){
        if(p->coeff == 0 || p == P.head) continue;
        if(p == P.head->next) cout << p->coeff;
        else{
            if(p->coeff > 0) cout << " + " ;
            else cout << " - ";
            cout << abs(p->coeff)*p->degree << "x^[" << p->degree - 1<< "]";
        }
    }
    cout << endl;
}