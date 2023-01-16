/*
************************************************************************************************************************
***                                                                                                                  ***
***      ****       ***      *************     ***      ***    ***     **************    ****               ****     ***
***      * * *      * *      * * * * * * *     * *      * *    * *     * ************    * * *             * * *     ***
***      * ** *     * *      * *       * *     * *      * *    * *     * *               * ** *           * ** *     ***
***      * * * *    * *      * *       ***     * *      * *    * *     * *               * * * *         * * * *     ***
***      * *  * *   * *      * *               * ******** *    * *     * ************    * *  * *       * *  * *     ***
***      * *   * *  * *      * *    ******     * ******** *    * *     * ************    * *   * *     * *   * *     ***
***      * *    * * * *      * *    **** *     * *      * *    * *     * *               * *    * *   * *    * *     ***
***      * *     * ** *      * *       * *     * *      * *    * *     * *               * *     * * * *     * *     ***
***      * *      * * *      * * * * * * *     * *      * *    * *     * ************    * *      * * *      * *     ***
***      ***       ****      *************     ***      ***    ***     **************    ***       ***       ***     *** 
***                                                                                                                  ***
************************************************************************************************************************
*/

/* library */
#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <math.h>

#define X first
#define FX second

#define FOR_EACH(x, v) 			for(auto x : v)
#define FOR(a, b, i) 			for(int i = a; i < b; i++)
#define FOR_(a, b, i) 			for(int i = a; i >= b; i--)
#define DRAW(a)					FOR(0, a, i) printf("-");
#define DRAWFILE(nameFile, a)  	FOR(0, a, i) fprintf(nameFile, "-");

#define KEY_ENTER		13

#define NORMAL			0
#define EQUID  			1

#define FORWARD 		1
#define BACKWARD 		2

#define MAX_CHOICE_1 	3
#define MAX_CHOICE_2 	6
#define MAX_CHOICE_3 	6

#define WIDTH 			1000
#define HEIGHT 			600

#define FIELDWIDTH 		30

#define FUNCTION_1 		1
#define FUNCTION_2 		2
#define FUNCTION_3 		3
#define FUNCTION_4 		4
#define FUNCTION_5 		5
#define FUNCTION_6 		6

using namespace std;

typedef vector< pair <double, double> > Inf;
typedef vector< vector <double> > Table;
typedef vector<double> Poly;

const char inFile[2][100] = {"Newton_interpolation_input.txt", "Newton_interpolation_input_2.txt"};
const char outFile[100] = {"Newton_interpolation_output.txt"};

const char menu_1[MAX_CHOICE_1][50] = {"1.    Noi suy moc bat ki", 
                "2.    Noi suy moc cach deu",
				"3.    Ket thuc"};

const char menu_2[MAX_CHOICE_2][50] = {"1.    Bang ty hieu",
                "2.    Da thuc noi suy tien",
                "3.    Da thuc noi suy lui",
                "4.    Tinh gia tri da thuc tai mot diem",
                "5.    Ve do thi",
                "6.    Quay lai"};

const char menu_3[MAX_CHOICE_3][50] = {"1.    Bang sai phan",
                "2.    Da thuc noi suy tien moc cach deu",
                "3.    Da thuc noi suy lui moc cach deu",
                "4.    Tinh gia tri da thuc tai mot diem",
                "5.    Ve do thi",
                "6.    Quay lai"};
                
/* prototypes */ 

void readData(int);
void print_poly(Poly, char); 

void frame(void);
void frame_load(void);
void set_color(int, int);

void Newton_interpolation(void);
void print_Newton_interpolation(int);
void div_diff_table(void);
void print_div_diff_table(void);
void mul_table(int);
void print_mul_table(void);

void Newton_interpolation_equidistly(int);
void print_Newton_interpolation_equidistly(int);
void diff_table(void);
void print_diff_table(void);
void mul_table_equid(int);
void print_mul_table_equid(void);
long long factorial(int n);

void cal_value(Poly, int, int);
void print_cal_value(Poly);

double fx1(double);
double fx2(Poly, double);
double fx3(Poly, double);
void draw_graph(double (*)(double), double (*)(Poly, double), Poly, double, double);

void menu(void);
int show_menu_1(void);
int show_menu_2(void);
int show_menu_3(void);
void highlight(int, int, char*);

/* Global variables */
int precision;
Inf inf, infEquid;
Table divDiffTable, diffTable, mulTable, mulTableEquid;
Poly NewtonInter, NewtonInterEquid;
bool run = true, runMenu1 = false, runMenu2 = false, runMenu3 = false;
FILE* fileOut = fopen(outFile, "w");

int main(){	
	printf("Nhập số chữ số thập phân: ");
	fprintf(fileOut, "Nhập số chữ số thập phân: ");
	scanf("%d", &precision);
	fprintf(fileOut, "%d\n", precision);
	
	initwindow(WIDTH, HEIGHT);
	while(run) menu();
	fclose(fileOut);
}

void frame(void){
	setlinestyle(0, 0, 2);
	setcolor(BLUE);
	rectangle(80, 100, 880, 500);
	line(80, 150, 880, 150);
	setcolor(CYAN);
	setlinestyle(0, 0, 1);
	
	// N 
	line(72, 10, 104, 10);
	line(72, 55, 96, 55);
	line(72, 10, 72, 55);
	line(96, 15, 96, 55);
	line(96, 15, 152, 55);
	line(104, 10, 160, 50);
	line(160, 10, 160, 50);
	line(152, 55, 184, 55);
	line(184, 10, 184, 55);
	line(160,10, 184, 10);
	// G
	line(232, 10, 336, 10);
	line(248, 15, 288, 15);
	line(288, 15, 288, 25);
	line(288, 25, 336, 25);
	line(336, 10, 336, 25);
	line(232, 10, 232, 55);
	line(248, 15, 248, 50);
	line(232, 55, 336, 55);
	line(336, 55, 336, 35);
	line(272, 35, 272, 40);
	line(272, 35, 336, 35);
	line(272, 40, 288, 40);
	line(288, 40, 288, 50);
	line(248, 50, 288, 50);
	// H
	line(376, 10, 392, 10);
	line(448, 10, 464, 10);
	line(376, 10, 376, 55);
	line(464, 10, 464, 55);
	line(376, 55, 392, 55);
	line(448, 55, 464, 55);
	line(392, 10, 392, 30);
	line(392, 35, 392, 55);
	line(448, 10, 448, 30);
	line(448, 35, 448, 55);
	line(392, 30, 448, 30);
	line(392, 35, 448, 35);
	// I
	rectangle(504, 10, 520, 55);
	// E
	line(568, 10, 680, 10);
	line(568, 55, 680, 55);
	line(582, 50, 680, 50);
	line(582, 35, 680, 35);
	line(582, 30, 680, 30);
	line(582, 15, 680, 15);
	line(568, 10, 568, 55);
	line(582, 15, 582, 30);
	line(582, 35, 582, 50);
	line(680, 10, 680, 15);
	line(680, 30, 680, 35);
	line(680, 50, 680, 55);
	// M
	line(720, 10, 720, 55);
	line(736, 15, 736, 55);
	line(872, 15, 872, 55);
	line(888, 10, 888, 55);
	line(720, 10, 744, 10);
	line(864, 10, 888, 10);
	line(720, 55, 736, 55);
	line(792, 55, 808, 55);
	line(872, 55, 888, 55);
	line(744, 10, 800, 50);
	line(800, 50, 864, 10);
	line(736, 15, 792, 55);
	line(808, 55, 872, 15);
}

void frame_load(void){
	cleardevice();
	
	settextstyle(0, 0, 2);
	setcolor(WHITE);
	outtextxy(450, 280, (char*)"Loading ...");
	
	settextstyle(0, 0, 3);
	set_color(WHITE, WHITE);
	rectangle(250, 250, 750, 274);
	for(int i = 250; i < 740; i += 10){
		delay(1);
		if(i == 650) delay(200);
		outtextxy(i, 250, (char*)" ");
	}
	setbkcolor(BLACK);
}

void set_color(int colorText, int colorBkText){
	setcolor(colorText);
	setbkcolor(colorBkText);
}

void menu(void){
	int choice1 = 0, choice2 = 0, choice3 = 0;
	runMenu1 = true;
	while(runMenu1){
		choice1 = show_menu_1();
		switch (choice1){
			case FUNCTION_1: frame_load();
							 readData(NORMAL); 
							 runMenu2 = true;
							 runMenu1 = false;	break;
			case FUNCTION_2: frame_load();
							 readData(EQUID);
							 runMenu3 = true;
							 runMenu1 = false;  break;
			case FUNCTION_3: runMenu1 = false;
							 run = false;		break;
		}
	}

	while(runMenu2){
		div_diff_table();
		choice2 = show_menu_2();  
		switch (choice2){
			case FUNCTION_1: frame_load();
							 print_div_diff_table();    	 		  			  					break;
			case FUNCTION_2: frame_load();
							 print_Newton_interpolation(FORWARD);	  			  					break;
			case FUNCTION_3: frame_load();
							 print_Newton_interpolation(BACKWARD); 	  			  					break;
			case FUNCTION_4: frame_load();
							 Newton_interpolation();
							 cal_value(NewtonInter, NORMAL, FORWARD); 			  					break;
			case FUNCTION_5: frame_load();
							 Newton_interpolation();
							 draw_graph(fx1, fx2, NewtonInter, inf[0].X, inf[inf.size() - 1].X);	break;
			case FUNCTION_6: frame_load();  
							 runMenu2 = false; 														break;
		}
	}
	
	while(runMenu3){
		diff_table();
		choice3 = show_menu_3();
		switch (choice3){
			case FUNCTION_1: frame_load(); 
							 print_diff_table();    	 		  		  										break;
			case FUNCTION_2: frame_load(); 
							 print_Newton_interpolation_equidistly(FORWARD);	  								break;
			case FUNCTION_3: frame_load(); 
							 print_Newton_interpolation_equidistly(BACKWARD);  									break;
			case FUNCTION_4: frame_load(); 
							 Newton_interpolation_equidistly(FORWARD);
							 cal_value(NewtonInterEquid, EQUID, FORWARD); 										break;
			case FUNCTION_5: frame_load(); 
							 Newton_interpolation_equidistly(FORWARD);
							 draw_graph(fx1, fx3, NewtonInterEquid, infEquid[0].X, infEquid[infEquid.size() - 1].X);	break;
			case FUNCTION_6: frame_load();  
							 runMenu3 = false; 																	break;
		}
	}
}

/* Display menu and select function */
int show_menu_1(void){
	cleardevice();
	frame();
	
	setcolor(RED);
	settextstyle(0, 0, 4);
	outtextxy(450, 110, (char*)"MENU");
	settextstyle(0, 0, THICK_WIDTH);
	
	int curFunction = FUNCTION_1;
    MOVE_MENU_1:
	for(int i = 220, j = FUNCTION_1; j <= MAX_CHOICE_1; i += 70, j += 1){
		if(j == curFunction) highlight(200, i, (char *)menu_1[j - 1]);
		else outtextxy(200, i, (char*)menu_1[j - 1]);
	}
	do{
        int n = getch();
        if(n == KEY_UP && curFunction >= FUNCTION_2){
        	curFunction--;
            goto MOVE_MENU_1;	
        }
        else if(n == KEY_DOWN && curFunction < MAX_CHOICE_1){ 
            curFunction++;	
            goto MOVE_MENU_1;
        }
        else if(n == KEY_ENTER) return curFunction; 
    }
    while(true);
}

int show_menu_2(void){
	cleardevice();
	frame();
	
	setcolor(RED);
	settextstyle(0, 0, 4);
	outtextxy(350, 110, (char*)"Noi suy moc bat ki");
	settextstyle(0, 0, THICK_WIDTH);
	
	int curFunction = FUNCTION_1;
    MOVE_MENU_2:
	for(int i = 200, j = FUNCTION_1; j <= MAX_CHOICE_2; i += 50, j += 1){
		if(j == curFunction) highlight(200, i, (char *)menu_2[j - 1]);
		else outtextxy(200, i, (char*)menu_2[j - 1]);
	}
	do{
        int n = getch();
        if(n == KEY_UP && curFunction >= FUNCTION_2){
        	curFunction--;
            goto MOVE_MENU_2;	
        }
        else if(n == KEY_DOWN && curFunction < MAX_CHOICE_2){ 
            curFunction++;	
            goto MOVE_MENU_2;
        }
        else if(n == KEY_ENTER) return curFunction; 
    }
    while(true);
}

int show_menu_3(void){
	cleardevice();
	frame();
	
	setcolor(RED);
	settextstyle(0, 0, 4);
	outtextxy(345, 110, (char*)"Noi suy moc cach deu");
	settextstyle(0, 0, THICK_WIDTH);
	
	int curFunction = FUNCTION_1;
    MOVE_MENU_3:
	for(int i = 200, j = FUNCTION_1; j <= MAX_CHOICE_3; i += 50, j += 1){
		if(j == curFunction) highlight(200, i, (char *)menu_3[j - 1]);
		else outtextxy(200, i, (char*)menu_3[j - 1]);
	}
	do{
        int n = getch();
        if(n == KEY_UP && curFunction >= FUNCTION_2){
        	curFunction--;
            goto MOVE_MENU_3;	
        }
        else if(n == KEY_DOWN && curFunction < MAX_CHOICE_2){ 
            curFunction++;	
            goto MOVE_MENU_3;
        }
        else if(n == KEY_ENTER) return curFunction; 
    }
    while(true);
}

void highlight(int x, int y, char* text){
	setbkcolor(YELLOW);
	outtextxy(x, y, text);
	setbkcolor(BLACK);
}

/* get data from file */
void readData(int TYPE){
	inf.clear(); infEquid.clear();
	// open file, get and print data
	FILE* fileIn = fopen(TYPE == NORMAL ? inFile[NORMAL] : inFile[EQUID], "r");
	
	DRAW(FIELDWIDTH + 3); DRAWFILE(fileOut, FIELDWIDTH + 3);
    printf("\n|    %-*s|    %-*s|\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx");
    fprintf(fileOut, "\n|    %-*s|    %-*s|\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx");
    DRAW(FIELDWIDTH + 3); DRAWFILE(fileOut, FIELDWIDTH + 3);
    
    double x, fx;
    while(!feof(fileIn)){
    	fscanf(fileIn, "%lf %lf", &x, &fx);
    	printf("\n|  % -*.*lf|  % -*.*lf|", FIELDWIDTH/2 - 2, precision, x, FIELDWIDTH/2 - 2, precision, fx);
    	fprintf(fileOut, "\n|  % -*.*lf|  % -*.*lf|", FIELDWIDTH/2 - 2, precision, x, FIELDWIDTH/2 - 2, precision, fx);
        TYPE == NORMAL ? inf.push_back({x, fx}) : infEquid.push_back({x, fx});
    }
    printf("\n"); fprintf(fileOut, "\n"); 
    DRAW(FIELDWIDTH + 3); DRAWFILE(fileOut, FIELDWIDTH + 3);
    printf("\n"); fprintf(fileOut, "\n"); 
    fclose(fileIn);
}

/* calculate divided differences table */
void div_diff_table(void){
	divDiffTable.clear();
	FOR(0, inf.size(), i){
		divDiffTable.push_back(vector<double> (inf.size() + 1, 0));
        divDiffTable[i][0] = inf[i].X; // cột X
        divDiffTable[i][1] = inf[i].FX; // cột FX
    }
    FOR(1, inf.size(), i){
        FOR(2, i + 2, j){
            divDiffTable[i][j] = (divDiffTable[i][j - 1] - divDiffTable[i - 1][j - 1]) / (divDiffTable[i][0] - divDiffTable[i - j + 1][0]);
        }
    }
}

/* print divided differences table */
void print_div_diff_table(void){
	printf("\nBảng tỷ hiệu:\n");
	fprintf(fileOut, "\nBảng tỷ hiệu:\n");
	DRAW(FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2);
	printf("\n|    %-*s|    %-*s|%*s\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx", FIELDWIDTH/2*(inf.size() - 1) + inf.size() - 1, "|");
    fprintf(fileOut, "\n|    %-*s|    %-*s|%*s\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx", FIELDWIDTH/2*(inf.size() - 1) + inf.size() - 1, "|");
    DRAW(FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2);
    
	FOR_EACH(v, divDiffTable){
		printf("\n|"); fprintf(fileOut, "\n|"); 
		FOR(0, v.size(), i){
			printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
			fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
		}
	}
	printf("\n"); fprintf(fileOut, "\n"); 
	DRAW(FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(inf.size() + 1) + inf.size() + 2);
	printf("\n"); fprintf(fileOut, "\n");
}

/* calculate multiply table */
void mul_table(int TYPE){
	mulTable.clear();
	int type = (TYPE == FORWARD ? 0 : inf.size() - 1);
	mulTable.push_back(vector<double> (inf.size(), 0));
	mulTable[0][0] = -inf[type].X;
    mulTable[0][1] = 1;
    FOR(1, inf.size() - 1, i){					// use Hoocner schema
    	mulTable.push_back(vector<double> (inf.size(), 0));
        mulTable[i][i + 1] = 1;
        FOR_(i, 1, j){
            mulTable[i][j] = mulTable[i - 1][j - 1] - inf[abs(type - i)].X * mulTable[i - 1][j];
        }
        mulTable[i][0] = - inf[abs(type - i)].X * mulTable[i - 1][0]; 
    }
}

/* print multiply table */
void print_mul_table(void){
	printf("\nBảng tính tích: \n");
	fprintf(fileOut, "\nBảng tính tích: \n");
	
	DRAW(FIELDWIDTH/2*inf.size() + inf.size() + 1); DRAWFILE(fileOut, FIELDWIDTH/2*inf.size() + inf.size() + 1);
	FOR_EACH(v, mulTable){
		printf("\n|"); fprintf(fileOut, "\n|"); 
		FOR(0, v.size(), i){
			printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
			fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
		}
	}
	printf("\n"); fprintf(fileOut, "\n"); 
	DRAW(FIELDWIDTH/2*inf.size() + inf.size() + 1); DRAWFILE(fileOut, FIELDWIDTH/2*inf.size() + inf.size() + 1);
}

/* Newton Interpolation formula */
void Newton_interpolation(void){
	NewtonInter.clear();
	mul_table(FORWARD);
	NewtonInter.push_back(divDiffTable[0][1]);
	FOR(1, inf.size(), i){
    	NewtonInter.push_back(0);
        FOR(0, i + 1, j){
        	NewtonInter[j] += divDiffTable[i][i + 1] * mulTable[i - 1][j];
        }
    }
}

/* print Newton Interpolation formula */
void print_Newton_interpolation(int TYPE){
	NewtonInter.clear();
	mul_table(TYPE);
	print_mul_table();
	printf("\n"); fprintf(fileOut, "\n"); 
	
	int type = (TYPE == FORWARD ? 0 : inf.size() - 1);
	NewtonInter.push_back(divDiffTable[type][1]);
	printf("--> f(x) = %.*lf\n", precision, NewtonInter[0]);
	fprintf(fileOut, "--> f(x) = %.*lf\n", precision, NewtonInter[0]);
	
    FOR(1, inf.size(), i){
    	NewtonInter.push_back(0);
        FOR(0, i + 1, j){
        	if(TYPE == FORWARD) NewtonInter[j] += divDiffTable[i][i + 1] * mulTable[i - 1][j];
            else NewtonInter[j] += divDiffTable[type][i + 1] * mulTable[i - 1][j];
        }
        printf("--> ");
		fprintf(fileOut, "--> ");
		print_poly(NewtonInter, 'x');
    }
    if(TYPE == FORWARD) {
    	printf("Đa thức nội suy tiến là: \n");
    	fprintf(fileOut, "Đa thức nội suy tiến là: \n");
	}
	else{
		printf("Đa thức nội suy lùi là: \n");
		fprintf(fileOut, "Đa thức nội suy lùi là: \n");
	}
	print_poly(NewtonInter, 'x');
	printf("\n"); fprintf(fileOut, "\n"); 
}

/* print polynomial */
void print_poly(Poly P, char c){
	printf("f(%c) = ", c); 
    fprintf(fileOut, "f(%c) = ", c); 
    
    FOR(0, P.size(), deg){
        if(P[deg] == 0) continue;
        if(deg == 0){
        	printf("%.*lf", precision, P[deg]); 
        	fprintf(fileOut, "%.*lf", precision, P[deg]); 
		}
        else if(P[deg] > 0){
            printf(" + "); 
    		fprintf(fileOut, " + "); 
            if(P[deg] != 1){
            	printf("%.*lf", precision, P[deg]); 
        		fprintf(fileOut, "%.*lf", precision, P[deg]); 
			}
            if(deg == 1){
            	printf("%c", c); 
    			fprintf(fileOut, "%c", c); 
			}
            else{
            	printf("%c^[%d]", c, deg); 
            	fprintf(fileOut, "%c^[%d]", c, deg); 
			}
        }
        else if(P[deg] < 0){
            printf(" - "); 
    		fprintf(fileOut, " - "); 
            if(P[deg] != -1){
            	printf("%.*lf", precision, -P[deg]); 
        		fprintf(fileOut, "%.*lf", precision, -P[deg]); 
			}
            if(deg == 1){
            	printf("%c", c); 
    			fprintf(fileOut, "%c", c); 
			}
            else{
            	printf("%c^[%d]", c, deg); 
            	fprintf(fileOut, "%c^[%d]", c, deg); 
			}
        }
    }
    printf("\n"); fprintf(fileOut, "\n"); 
}

/* calculate the polynomial value at one point */
void cal_value(Poly P, int TYPE1, int TYPE2){
	printf("\n"); fprintf(fileOut, "\n"); 
	double point;
	printf("Nhập điểm cần tính giá trị : ");
	scanf("%lf", &point);
	fprintf(fileOut, "Nhập điểm cần tính giá trị :");
	fprintf(fileOut, "%.*lf\n", precision, point);
	
	printf("\n"); fprintf(fileOut, "\n"); 
	printf("Sơ đồ Hoocne: \n");
	fprintf(fileOut, "Sơ đồ Hoocne: \n");
	
	DRAW(FIELDWIDTH/2*(P.size() + 1) + P.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(P.size() + 1) + P.size() + 2);
	printf("\n"); fprintf(fileOut, "\n"); 
	printf("|   %-*s|", FIELDWIDTH/2 - 3, "coeff");
	fprintf(fileOut, "|   %-*s|", FIELDWIDTH/2 - 3, "coeff");
	
	FOR_(P.size() - 1, 0, i){
        printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, P[i]);
		fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, P[i]);
    }
    printf("\n"); fprintf(fileOut, "\n"); 
    
    DRAW(FIELDWIDTH/2*(P.size() + 1) + P.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(P.size() + 1) + P.size() + 2);
    printf("\n"); fprintf(fileOut, "\n");
	
	double point_t;
	if(TYPE1 == EQUID && TYPE2 == FORWARD){
		point_t = (point - infEquid[0].X) / (infEquid[1].X - infEquid[0].X);
	}
	else if (TYPE1 == EQUID && TYPE2 == BACKWARD){
		point_t = (point - infEquid[infEquid.size() - 1].X) / (infEquid[1].X - infEquid[0].X);
	}
	else point_t = point;
	double value =  P[P.size() - 1];
	
	printf("|  % -*.*lf|", FIELDWIDTH/2 - 2, precision, point_t);
	fprintf(fileOut, "|  % -*.*lf|", FIELDWIDTH/2 - 2, precision, point_t);
	
	printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, value);
	fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, value); 
	
	double value_temp = value;
	FOR_(P.size() - 2, 0, i){
        value_temp = value_temp * point_t + P[i];
        printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, value_temp);
		fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, value_temp); 
    }
    printf("\n"); fprintf(fileOut, "\n"); 
    DRAW(FIELDWIDTH/2*(P.size() + 1) + P.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(P.size() + 1) + P.size() + 2);
    printf("\n"); fprintf(fileOut, "\n");
    printf("\n"); fprintf(fileOut, "\n");
    FOR_(P.size() - 2, 0, i){
    	printf("value = %.*lf * %.*lf + %.*lf = %.*lf\n", precision, value, precision, point_t, precision, P[i], precision, value * point_t + P[i]);
    	fprintf(fileOut, "value = %.*lf * %.*lf + %.*lf = %.*lf\n", precision, value, precision, point_t, precision, P[i], precision, value * point_t + P[i]);
        value = value * point_t + P[i];
    }
    printf("--> f(%.*lf) = %.*lf", precision, point_t, precision, value); 
    fprintf(fileOut, "--> f(%.*lf) = %.*lf", precision, point_t, precision, value); 
    printf("\n"); fprintf(fileOut, "\n");
}

/* calculate differences table */
void diff_table(void){
	diffTable.clear();
	FOR(0, infEquid.size(), i){
		diffTable.push_back(vector<double> (infEquid.size() + 1, 0));
        diffTable[i][0] = infEquid[i].X; // cột X
        diffTable[i][1] = infEquid[i].FX;
    }
    FOR(1, infEquid.size(), i){
        FOR(2, i + 2, j){
            diffTable[i][j] = diffTable[i][j - 1] - diffTable[i - 1][j - 1];
        }
    }
}

/* print differences table */
void print_diff_table(void){
	printf("\nBảng sai phân: \n");
	fprintf(fileOut, "\nBảng sai phân: \n");
	DRAW(FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2);
	printf("\n|    %-*s|    %-*s|%*s\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx", FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size() - 1, "|");
    fprintf(fileOut, "\n|    %-*s|    %-*s|%*s\n", FIELDWIDTH/2 - 4, "x", FIELDWIDTH/2 - 4, "fx", FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size() - 1, "|");
    DRAW(FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2);
    
	FOR_EACH(v, diffTable){
		printf("\n|"); fprintf(fileOut, "\n|"); 
		FOR(0, v.size(), i){
			printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
			fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
		}
	}
	printf("\n"); fprintf(fileOut, "\n"); 
	DRAW(FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2); DRAWFILE(fileOut, FIELDWIDTH/2*(infEquid.size() + 1) + infEquid.size() + 2);
	printf("\n"); fprintf(fileOut, "\n");
}

/* calculate multiply table with x equidistant*/
void mul_table_equid(int TYPE){
	mulTableEquid.clear();
	mulTableEquid.push_back(vector<double> (infEquid.size() - 1, 0));
	mulTableEquid[0][0] = 1;
    FOR(1, infEquid.size() - 1, i){
    	mulTableEquid.push_back(vector<double> (infEquid.size() - 1, 0));
        mulTableEquid[i][i] = 1;
        int type = TYPE == FORWARD ? i : -i;
        FOR_(i - 1, 1, j){
            mulTableEquid[i][j] = mulTableEquid[i - 1][j - 1] - type * mulTableEquid[i - 1][j];
        }
        mulTableEquid[i][0] = - type * mulTableEquid[i - 1][0]; 
    }
}

/* print multiply table with x equidistant*/
void print_mul_table_equid(void){
	printf("\nBảng tính tích: \n");
	fprintf(fileOut, "\nBảng tính tích: \n");
	
	DRAW(FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size()); DRAWFILE(fileOut, FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size());
	FOR_EACH(v, mulTableEquid){
		printf("\n|"); fprintf(fileOut, "\n|"); 
		FOR(0, v.size(), i){
			printf("  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
			fprintf(fileOut, "  % -*.*lf|", FIELDWIDTH/2 - 2, precision, v[i]);
		}
	}
	printf("\n"); fprintf(fileOut, "\n"); 
	DRAW(FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size()); DRAWFILE(fileOut, FIELDWIDTH/2*(infEquid.size() - 1) + infEquid.size());
}

/* calculate factorial*/
long long factorial(int n){
    if(n == 1) return 1;
    else return n * factorial(n - 1);
}

/* Newton Interpolation formula with x equidistant*/
void Newton_interpolation_equidistly(int TYPE){	
	NewtonInterEquid.clear();
	mul_table_equid(TYPE);
	int type = (TYPE == FORWARD ? 0 : infEquid.size() - 1);
	NewtonInterEquid.push_back(diffTable[type][1]);
	
    FOR(1, infEquid.size(), i){
    	NewtonInterEquid.push_back(0);
        FOR(1, i + 1, j){
            if(TYPE == FORWARD) NewtonInterEquid[j] += diffTable[i][i + 1] * mulTableEquid[i - 1][j - 1] / factorial(i);
            else NewtonInterEquid[j] += diffTable[type][i + 1] * mulTableEquid[i - 1][j - 1] / factorial(i);
        }
    }
}

/* print Newton Interpolation formula with x equidistant*/
void print_Newton_interpolation_equidistly(int TYPE){
	NewtonInterEquid.clear();
	mul_table_equid(TYPE);
	print_mul_table_equid();
	
	printf("\n"); fprintf(fileOut, "\n"); 
	
	int type = (TYPE == FORWARD ? 0 : infEquid.size() - 1);
	NewtonInterEquid.push_back(diffTable[type][1]);
	printf("--> f(t) = %.*lf\n", precision, NewtonInterEquid[0]);
	fprintf(fileOut, "--> f(t) = %.*lf\n", precision, NewtonInterEquid[0]);
	
	FOR(1, infEquid.size(), i){
		NewtonInterEquid.push_back(0);
        FOR(1, i + 1, j){
            if(TYPE == FORWARD) NewtonInterEquid[j] += diffTable[i][i + 1] * mulTableEquid[i - 1][j - 1] / factorial(i);
            else NewtonInterEquid[j] += diffTable[infEquid.size() - 1][i + 1] * mulTableEquid[i - 1][j - 1] / factorial(i);
        }
        printf("--> ");
		fprintf(fileOut, "--> ");
		print_poly(NewtonInterEquid, 't');
    }
    if(TYPE == FORWARD) {
    	printf("Đa thức nội suy tiến mốc cách đều là : \n");
    	fprintf(fileOut, "Đa thức nội suy tiến mốc cách đều là : \n");
	}
	else{
		printf("Đa thức nội suy lùi mốc cách đều là : \n");
		fprintf(fileOut, "Đa thức nội suy lùi mốc cách đều là : \n");
	}
	print_poly(NewtonInterEquid, 't');
	printf("\n"); fprintf(fileOut, "\n"); 
}

// standard function
double fx1(double x){
	return 1 / (25 * pow(x, 2) + 1);
	// return 0;
}

// Newton polynomial interpolation 
double fx2(Poly P, double x){
	double value = P[P.size() - 1];
	FOR_(P.size() - 2, 0, i){
    	value = value * x + P[i];
	}
	return value;
}

// Newton polynomial interpolation with x equidistant
double fx3(Poly P, double x){
	double t = (x - infEquid[0].X)/(infEquid[1].X-infEquid[0].X);
	double value = P[P.size() - 1];
	FOR_(P.size() - 2, 0, i){
    	value = value * t + P[i];
	}
	return value;
}

// draw functions f1 and f2 in paragraphs [a, b] on the new graphic console
void draw_graph(double (*f1)(double x), double (*f2)(Poly P, double x), Poly P, double a, double b){
	closegraph();
	initwindow(800, 800);
	
	int x1 = 100, y1 = 100, x2 = 700, y2 = 700;
	double fx1, fx2, maxf = f1(a), minf = f1(a), h = 0.01, r = a;
	
	if(f1(a) > f2(P, a)) maxf = f1(a), minf = f2(P, a);
	else maxf = f2(P, a), minf = f1(a);

	while(r <= b){
		fx1 = f1(r);
		fx2 = f2(P, r);
		if(fx1 < minf) minf = fx1;
		if(fx1 > maxf) maxf = fx1;
		if(fx2 < minf) minf = fx2;
		if(fx2 > maxf) maxf = fx2;
		r += h;
	}
	
	double n = x2 - x1, m = y2 - y1;
	double k = (maxf - minf)/m;
	h = (b - a)/n;
	double x0 = x1 + (int)(-a/h + 0.5), y0 = y2 - (int)(-minf/k + 0.5);
	
	setcolor(BLUE);
	line(x1 - 20, y0, x2 + 20, y0);
	line(x2 + 10, y0 - 10, x2 + 20, y0);
	line(x2 + 10, y0 + 10, x2 + 20, y0);
	
	line(x0, y1 - 20, x0, y2 + 20);
	line(x0 - 10, y1 - 10, x0, y1 - 20);
	line(x0 + 10, y1 - 10, x0, y1 - 20);
	
	settextstyle(0, 0, 3);
	outtextxy(x2, y0 + 14, (char*)"x");
	outtextxy(x0 - 18, y1 - 10, (char*)"y");
	
	rectangle(1, 1, 99, 99);
	
	setcolor(CYAN);
	line(10, 35, 50, 35);
	outtextxy(55, 25, (char*)": fx1");
	
	setcolor(RED);
	line(10, 60, 50, 60);
	outtextxy(55, 50, (char*)": fx2");
	
	setcolor(CYAN);
	FOR(0, n + 1, i){
		double x = x1 + i;
		fx1 = f1(a + i*h);
		double y = (int)((fx1 - minf)/k + 0.5) + y1;
		y = y2 - y + y1;
		if(i == 0) moveto(x, y);
		else lineto(x, y);
	}
	
	setcolor(RED);
	FOR(0, n + 1, i){
		double x = x1 + i;
		fx2 = f2(P, a + i*h);
		double y = (int)((fx2 - minf)/k + 0.5) + y1;
		y = y2 - y + y1;
		if(i == 0) moveto(x, y);
		else lineto(x, y);
	}  
	getch();
	closegraph();
	initwindow(WIDTH, HEIGHT);
}
