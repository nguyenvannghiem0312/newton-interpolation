#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm> 
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
using namespace std;

typedef struct nodeTree
{
    char a;
    struct nodeTree* left;
    struct nodeTree* right;
    nodeTree(char s){
        a = s;
        left = NULL;
        right = NULL;
    }
    nodeTree(){
        left = NULL;
        right = NULL;
    }
} nodeTree;

typedef struct nodeStack
{
    nodeTree* nodetree;
    struct nodeStack* next;
    nodeStack(nodeTree* a){
        nodetree = a;
        next = NULL;
    }
} nodeStack;

typedef struct Stack
{
    nodeStack* top;
    Stack(){
        top = NULL;
    }
} Stack;

typedef struct BinaryTree
{
    nodeTree* root;
    BinaryTree(){
        root = NULL;
    }
} BinaryTree;

bool isEmpty(Stack S){
    if(S.top == NULL) return true;
    return false;
}

void push(Stack& S, nodeTree* a){
    nodeStack* node = new nodeStack(a);
    if(S.top == NULL){
        S.top = node;
    }
    else{
        node->next = S.top;
        S.top = node;
    }
}

char top(Stack S){
    return S.top->nodetree->a;
}

nodeTree* pop(Stack& S){
    nodeTree* ptr = S.top->nodetree;
    S.top = S.top->next;
    return ptr;
}

int priority(char x){
    if(x == '(') return 0;
    if(x == '+' || x == '-') return 1;
    if(x == '*' || x == '/') return 2;
    return 3;
}

nodeTree* ExpressionTree(Stack postfix){
    Stack s = Stack();
    for(nodeStack* x = postfix.top; x != NULL; x = x->next){
        if(isalnum(x->nodetree->a)){
            nodeTree* nptr = new nodeTree(x->nodetree->a);
            push(s, nptr);
        }
        else if(priority(x->nodetree->a) == 1 || priority(x->nodetree->a) == 2){
            nodeTree* nptr = new nodeTree(x->nodetree->a);
            nptr->left = pop(s);
            nptr->right = pop(s);
            push(s, nptr);
        }
    }
    return s.top->nodetree;
}

Stack infixtoPostfix(string s){
    Stack postfix = Stack();
    Stack temp = Stack();
    for(int i = 0; i < s.length(); i++){
        char a = s[i];
        if(isalnum(a)){
            push(postfix, new nodeTree(a));
        }
        else{
            if(a == '('){
                push(temp, new nodeTree(a));   
            }
            else{
                if(a == ')'){
                    while (top(temp) != '('){
                        char x = top(temp);
                        push(postfix, new nodeTree(x));
                        pop(temp);
                    }
                    pop(temp);
                }
                else{
                    while(!isEmpty(temp)){
                        char x = top(temp);
                        if(priority(x) >= priority(a) ){
                            push(postfix, new nodeTree(x));
                            pop(temp); 
                        }
                        else break;
                    }
                    push(temp, new nodeTree(a));
                }
            }
        }
    }
    while(!isEmpty(temp)){
        char x = top(temp);
        push(postfix, new nodeTree(x));
        pop(temp);
    }
    Stack prefix = Stack();
    for(nodeStack* x = postfix.top; x != NULL; x = x->next){
        push(prefix, x->nodetree);
    }
    return prefix;
}

void posOrder(nodeTree* root)
    {
        if (root != NULL)
        {
            posOrder(root->right);
            posOrder(root->left);
            cout << root->a;
        }
    }

float value(Stack postfix){
    vector<float> value;
    for(nodeStack* x = postfix.top; x != NULL; x = x->next){
        if(isalnum(x->nodetree->a)){
            value.push_back(float(x->nodetree->a - '0'));
        }
        else{
            float x2= value.back();
            value.pop_back();
            float x1 = value.back();
            value.pop_back();
            switch (x->nodetree->a)
            {
            case '+':
            {
                float temp = x1 + x2;
                value.push_back(temp);
                break;
            }
            case '-':
            {
                float temp = x1 - x2;
                value.push_back(temp);
                break;
            }
            case '*':
            {
                float temp = x1 * x2;
                value.push_back(temp);
                break;
            }
            case '/':
            {
                float temp = x1 / x2;
                value.push_back(temp);
                break;
            }
            default:
                break;
            }
        }
    }
    return value.back();
}

int main(){
    string s = "(8/5+7)*(5-3)";  // Khong nhap dau Space
    cout << "s = " << s << endl;
    Stack postfix = infixtoPostfix(s);
    cout << endl;
    BinaryTree tree = BinaryTree();
    tree.root = ExpressionTree(postfix);
    cout << "Bieu thuc dang hau to la: ";
    posOrder(tree.root);
    float v = value(postfix);
    cout << endl << "Gia tri cua bieu thuc la: " << s << " = " << v << endl;
}