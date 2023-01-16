#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void menu();
void gotoxy(int x, int y);
char get_key();
void set_color(const char *color);
void printf_color(const char *string, const char *color);
void TinhTienDien();
void TinhTienLuong();

int xPos = 0, yPos = 2;
int Xpos = 60, Ypos = -1;

int main() {
    char a;
    menu();
    while(true){
    	gotoxy(xPos, yPos);
        get_key();
        a = get_key();
        switch (a)
        {
        case '1':
            TinhTienDien();
            break;
        case '2':
            TinhTienLuong();
            break;
        case '3':
        	gotoxy(Xpos, ++Ypos);
            printf_color("Gud Bye!!!", "95");
            exit(0);
        }
    }
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

char get_key(){
	int ch2;
	while(true){
		if(ch2 != 13) ch2 = getch();
		if(ch2 == 72 && yPos >= 3) gotoxy(xPos, --yPos);   //top
		else if(ch2 == 80 && yPos <= 3) gotoxy(xPos, ++yPos);   //down
		else if(ch2 == 13){   // enter
			gotoxy(Xpos, ++Ypos);
			return char(yPos - 1 + '0');
		}
		else fflush(stdin);
	}
	
}

void set_color(const char *color) {
    char cmd[512];
    sprintf(cmd, "echo|set /p=\"\e[%sm\"", color);
    system(cmd);
}

void printf_color(const char *string, const char *color) {
    char cmd[512];
    sprintf(cmd, "echo \e[%sm%s\e[0m", color, string);
    system(cmd);
}

void menu(){
    printf_color("============================================\n", "33");
    printf_color("Menu (Nhan Enter de chon)\n", "91");
    printf_color("1. Tinh tien dien \n", "96");
    printf_color("2. Tinh tien luong \n", "96");
    printf_color("3. Thoat chuong trinh \n", "96");
    printf_color("============================================\n", "33");
    set_color("0");
}
			
void TinhTienDien(){
    double soDien, tien1so;
    char s[6];
    fflush(stdin);
    printf_color("Nhap don vi tien te: ", "96");
    gotoxy(Xpos, ++Ypos);
	scanf("%s", s);
	gotoxy(Xpos, ++Ypos);
    printf_color("Nhap so dien da dung trong 1 thang: ", "96");
    gotoxy(Xpos, ++Ypos);
	scanf("%lf", &soDien);
    gotoxy(Xpos, ++Ypos);
    printf_color("Nhap so tien tren 1 so dien: ", "96");
    gotoxy(Xpos, ++Ypos);
	scanf("%lf", &tien1so);
    gotoxy(Xpos, ++Ypos);
    double tienDien = soDien*tien1so;
    set_color("92");
    printf("Tien dien thang nay la: %.4lf %s\n", tienDien, s);
    gotoxy(Xpos, ++Ypos);
    set_color("0");
}

void TinhTienLuong(){
    double tienLuong1Thang, ngayCong, tienPhat, tax;
    char s[6];
    fflush(stdin);
    printf_color("Nhap don vi tien te: ", "96");
	gotoxy(Xpos, ++Ypos);
	scanf("%s", s);
	gotoxy(Xpos, ++Ypos);
    printf_color("Nhap tien luong 1 thang (23 ngay): ", "96");
	gotoxy(Xpos, ++Ypos);
	scanf("%lf", &tienLuong1Thang);
	gotoxy(Xpos, ++Ypos);
    printf_color("Nhap so ngay cong: ", "96");
	gotoxy(Xpos, ++Ypos);
	scanf("%lf", &ngayCong);
	gotoxy(Xpos, ++Ypos);
    printf_color("Nhap so tien phat: ", "96");
	gotoxy(Xpos, ++Ypos);
	scanf("%lf", &tienPhat);
	gotoxy(Xpos, ++Ypos);
    printf_color("Nhap tax: ", "96");
	gotoxy(Xpos, ++Ypos);
	scanf("%lf", &tax);
	gotoxy(Xpos, ++Ypos);
    double tienLuong = tienLuong1Thang * ngayCong / 23 * (1 - tax / 100) - tienPhat;
    set_color("92");
    printf("Tien luong la: %.4lf %s\n", tienLuong, s);
    gotoxy(Xpos, ++Ypos);
    set_color("0");
}
