#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define ROW  100
#define COL  100
typedef struct array{
	float element[ ROW ][ COL ];
	int row;
	int column;
}ar;

/* CAC HAM VE VA DINH NGHIA MAU */
void color(int color);
void gotoxy(int x, int y);
void drawframe();

/* CAC HAM CHINH CUA CHUONG TRINH*/
void Nhap(ar &M);
void Xuatmang(ar M);
void Cong(ar &M, ar &N, ar &A);
void Nhanvohuong(ar &M);
void Nhanhaimatran(ar &M, ar &N, ar &A);

int main(){
    ar Mang[10];
    int Set[] = {7,7,7,7,7,7}; /* default colors in menu */
	int counter = 1, counterin = 1;         /* cuonter in menu */
	char key;
    int num = 0, num1 = 0, num2 = 0; /* counter in Mang[] */ 

	while(1){
		
		/* VE MENU CHUONG TRINH */
	    drawframe();
		if(counter == 1){
			Set[0] = 20;
		}
		gotoxy(30,6);
		color(Set[0]);
		printf(" 1. NHAP MA TRAN  ");
		
		gotoxy(30,7);
		color(Set[1]);
		printf(" 2. IN MA TRAN ");
		
		gotoxy(30,8);
		color(Set[2]);
		printf(" 3. CONG MA TRAN ");
		
		gotoxy(30,9);
		color(Set[3]);
		printf(" 4. NHAN VO HUONG ");
				
		gotoxy(30,10);
		color(Set[4]);
		printf(" 5. NHAN HAI MA TRAN ");
		
		gotoxy(30,11);
		color(Set[5]);
		printf(" 6. EXIT()");
		key = getch();
		if(key == 72 && (counter >= 2 && counter <=6)){
			counter--;
			
		}
		else if(key == 80 && (counter >= 1 && counter <=5)){
			counter++;
			
		}
		else if(key == 72 && (counter <=1)){
			counter = 6;
		}
		else if(key == 80 && (counter >= 6)){
			counter = 1;
		}
		if(key == '\r'){
			if(counter == 6){
				gotoxy(0,17);	
				color(7);
				break;
			}
			system("cls");
			gotoxy(0,5);
			
			/* NHAP MA TRAN */
			if(counter == 1){
				printf("NHAP SO THU TU MA TRAN MUON NHAP DU LIEU: ");
				scanf("%d", &num);
				Nhap(Mang[num]);
				
			}
			
			/* IN MA TRAN */
			if(counter == 2){	
				printf("NHAP SO THU TU MA TRAN MUON IN: "); 
				scanf("%d", &num);
				Xuatmang(Mang[num]);
			}
			
			/* CONG HAI MA TRAN */
			if(counter == 3){
				Set[0] = 20;
				Set[1] = 7;
				Set[2] = 7;
				while(1){
					
					drawframe();
					gotoxy(30,6);
					color(Set[0]);
					printf("1. NHAP MOI DU LIEU 2 MANG");
					
					gotoxy(30,7);
					color(Set[1]);
					printf("2. CONG MANG CO SAN");
					
					gotoxy(30,8);
					color(Set[2]);
					printf("3. EXIT()");
					
					key = getch();
					if(key == 72 && (counterin == 2 || counterin ==3)){
					counterin--;
			
					}
					else if(key == 80 && (counterin == 1 || counterin ==2)){
					counterin++;
			
					}
					else if(key == 72 && (counterin =1)){
					counterin = 3;
					}
					else if(key == 80 && (counterin = 3)){
					counterin = 1;
					}
					if(key == '\r'){
						if(counterin == 3){	
						color(7);
						break;
						}
						system("cls");
						gotoxy(0,5);
						if(counterin == 1){
						    system("cls");
							printf("NHAP SO THU TU MA TRAN MUON NHAP DU LIEU (ARRAY1 ARRAY2): ");
							scanf("%d%d", &num1, &num2);
							Nhap(Mang[num1]);
							Nhap(Mang[num2]);
							printf("\nSO THU TU MATRAN MUON LUU GIA TRI TONG: ");
							scanf("%d", &num);
							Cong(Mang[num1], Mang[num2], Mang[num]);
							printf("\nMUON IN KET QUA TONG MATRAN[%d] + MATRAN[%d] khong?(Y,N)", num1, num2);
							
							do{
								key = getch();
							}while((key != 'Y') && (key != 'y') && (key != 'N') && (key == 'n'));
							if(key == 'Y' || key == 'y'){
								Xuatmang(Mang[num]);
								key = getch();
								break;
							}
							else{
								break;
							}
						}
						else if(counterin == 2){
							system("cls");
							printf("NHAP HAI MATRAN CAN TINH TONG (MATRIX1 MATRIX2): ");
							scanf("%d%d", &num1, &num2);
							printf("SO THU TU MATRAN MUON LUU GIA TRI TONG: ");
							scanf("%d", &num);
							Cong(Mang[num1], Mang[num2], Mang[num]);
							printf("MUON IN KET QUA TONG MATRAN[%d] + MATRAN[%d] khong?(Y,N)", num1, num2);
							
							do{
								key = getch();
							}while((key != 'Y') && (key != 'y') && (key != 'N') && (key == 'n'));
							if(key == 'Y' || key == 'y'){
								Xuatmang(Mang[num]);
								key = getch();
								system("cls");
								break;
							}
							else{
								system("cls");
								break;
							}
						}
						system("cls");
						
					}
					Set[0] = 7;
					Set[1] = 7;
					Set[2] = 7;
					if(counterin == 1){
						Set[0] = 20;
					}
					else if(counterin == 2){
						Set[1] = 20;
					}
					else if(counterin == 3){
						Set[2] = 20;
					}
					
					
				}
			}
				
			/* NHAN VO HUONG */
			if(counter == 4){
				printf("NHAP MA TRAN CAN NHAN VO HUONG: \n");
				printf("NHAP SO THU TU LUU MA TRAN: ");
				scanf("%d", &num);
				Nhap(Mang[num]);
				Nhanvohuong(Mang[num]);
				printf("\n\tKET QUA NHAN VO HUONG: \n");
				Xuatmang(Mang[num]);
				
			}
			/* NHAN HAI MA TRAN */
			if(counter == 5){
				printf("CHON SO THU TU LUU HAI MA TRAN: ");
				scanf("%d%d", &num1, &num2);
				printf("CHON SO THU TU LUU MA TRAN TICH: ");
				scanf("%d", &num);
				printf("NHAP HAI MA TRAN (MATRIX1[m][n], MATRIX2[n][p]): \n");
				do{
					Nhap(Mang[num1]);
					Nhap(Mang[num2]);
				}while(Mang[num1].column != Mang[num2].row);
				Nhanhaimatran(Mang[num1], Mang[num2], Mang[num]);
				printf("KET QUA NHAN HAI MA TRAN: \n");
				Xuatmang(Mang[num]);
				
			}
			
			key = getch();
			if(key == '\r')
			system("cls");
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;
		Set[5] = 7;
		
		if(counter == 1){
			Set[0] = 20;
		}
		if(counter == 2){
			Set[1] = 20;
		}
		if(counter == 3){
			Set[2] = 20;
		}
		if(counter == 4){
			Set[3] = 20;
		}
		if(counter == 5){
			Set[4] = 20;
		}
		if(counter == 6){
			Set[5] = 20;
		}
		
	}
	return 1;

}
    


void color(int color){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	}
	
void gotoxy(int x, int y){
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void drawframe(){
	int i;
	gotoxy(50,3);
	color(12);
	printf("MENU");
	color(7);
	for(i=0; i<65; i++){
		gotoxy(20+i,2);
		printf("-");
		gotoxy(20+i,17);
		printf("-");
	}
	for(i=0; i<=13; i++){
		gotoxy(20,2);
		gotoxy(19,3+i);
	    printf("||");
		gotoxy(84,3+i);
		printf("||");	
	}		
}
	
void Nhap(ar &M){
    
    int i, j; /* counter */
    printf("Nhap so hang, cot: "); scanf("%d%d", &M.row, &M.column);
    for(i = 0; i < M.row; i++){
	
    	for(j = 0; j < M.column; j++){
    		printf("M[%d][%d]  ", i + 1, j + 1);
		}
		printf("= ");
		for(j = 0; j < M.column; j++)
			scanf("%f", &M.element[i][j]);
	}
}

void Xuatmang(ar M){
	int i, j; /* counter */
	printf("\nARRAY OUTPUT: \n");
	for(i = 0; i < M.row; i++){
    	for(j = 0; j < M.column; j++){
    		printf("\t%f", M.element[i][j]);
		}
		printf("\n");
	}
}

void Cong(ar &M, ar &N, ar &A){
	int i, j; /* counter */
    A.row = N.row;
    A.column = N.column;
    
	for(i = 0; i < A.row; i++)
		for(j = 0; j < A.column; j++){
			A.element[i][j] = M.element[i][j] + N.element[i][j];
			}
}	


void Nhanvohuong(ar &M){
	int i, j; // counter
	float k; // HE SO VO HUONG
	printf("NHAP HE SO VO HUONG: ");
	scanf("%f", &k);
	for(i = 0; i < M.row; i++)
		for(j = 0; j < M.column; j++){
			M.element[i][j] = k*M.element[i][j];
			}
}

// M[m][n]  N[n,p] => A[m,p]
void Nhanhaimatran(ar &M, ar &N, ar &A){
	int m, n, i; // counter 
	A.row = M.row;
	A.column = N.column;
	for(m = 0; m < A.row; m++)
		for(n = 0; n < A.column; n++){
			A.element[m][n] = 0;
			for(i = 0; i < M.column; i++){
				A.element[m][n] += M.element[m][i]*N.element[i][n];
			} 
		}
}
