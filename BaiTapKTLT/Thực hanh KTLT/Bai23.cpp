#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

typedef struct STUDENT{
    int ID;
    char NAME[50];
    double GRADE;
} STUDENT;

void menu();
void WriteFile(char *FileName);
void ReadFile(char *FileName);
void Max(char *FileName);
void Swap(STUDENT &sv1, STUDENT &sv2);
void Sort(char *FileName);
void Add(char *FileName);
void Edit(char *FileName);
void Remove(char *FileName);

int n = 0;

int main(){
    char FileName[] = "baitap23.dat";
    int choose;
	while(1){
		menu();
		CHOOSE: printf("\n Nhap yeu cau: "); scanf("%d", &choose);
		if(choose != 1 && n == 0){
			printf("\n Vui long nhap STUDENT dau tien.");
			continue;
		} 
		switch (choose)
		{
		case 1:
			WriteFile(FileName);
			break;
		case 2:
			ReadFile(FileName);
			break;
		case 3:
			Sort(FileName);
			break;	
		case 4:
			Max(FileName);
			break;
		case 5:
			Add(FileName);
			break;
		case 6:
			Edit(FileName);
			break;	
		case 7:
			Remove(FileName);
			break;	
		case 8:
			printf("\nHave a nice day!!!");
			return 0;
			break;	
		default:
			printf("\nMoi nhap lai!!!");
			goto CHOOSE;
			break;
		}
		printf("\nNhan nut bat ky de tiep tuc!");
		getch();
	}
}

void menu(){
    printf("\n============================================\n");
    printf("Menu\n");
    printf("1. Nhap STUDENT \n");
    printf("2. Xuat STUDENT \n");
    printf("3. Sap xep STUDENT tang dan theo NAME \n");
	printf("4. Hien thi STUDENT co GRADE cao nhat \n");
	printf("5. Them SUTDENT \n");
	printf("6. Sua STUDENT \n");
	printf("7. Xoa STUDENT \n");
	printf("8. Thoat \n");
    printf("============================================\n");
    
}

void WriteFile(char *FileName){
    FILE *f;   
	STUDENT sv;   	
	f = fopen(FileName, "w+");   
	printf("Nhap vao so luong sinh vien: "); 
	scanf("%d", &n);   	
	for(int i = 1; i <= n; i++)  
	{  
		printf("Sinh vien thu %i\n", i);   	 	
		fflush(stdin); 
		printf(" - ID: ");
		scanf("%d", &sv.ID);  
        fflush(stdin);
		printf(" - Ho ten: ");
		gets(sv.NAME);
        printf(" - Diem: ");
	    scanf("%lf", &sv.GRADE);
		fwrite(&sv, sizeof(sv), 1, f);  
	}  
	fclose(f);  
}

void ReadFile(char *FileName){
    FILE *f;   	
	STUDENT sv;   	
	f = fopen(FileName,"r+");   
    printf("\n%-10s %-30s %-5s\n", "ID", "NAME", "GRADE");	
	fread(&sv, sizeof(sv), 1, f);   	
	while (!feof(f))  
	{  
        printf("%-10d %-30s %-5.2lf\n", sv.ID, sv.NAME, sv.GRADE);  
        fread(&sv, sizeof(sv), 1, f);
	}  
	fclose(f);    
}

void Swap(STUDENT &sv1, STUDENT &sv2){
	STUDENT svtemp;
	svtemp = sv1;
	sv1 = sv2;
	sv2 = svtemp;
}

void Sort(char *FileName){
	FILE *f;
	STUDENT sv[n];
	f = fopen(FileName, "r+");
	int cnt = 0;
	while(!feof(f) && cnt <= n - 1){
		STUDENT svtemp;
		fread(&svtemp, sizeof(svtemp), 1, f);
		sv[cnt].ID = svtemp.ID;
		strcpy(sv[cnt].NAME, svtemp.NAME);
		sv[cnt++].GRADE = svtemp.GRADE;
	}
	
	fclose(f);
	
	bool haveSwap = false;
	for (int i = 0; i < n - 1; i++){
        haveSwap = false;
        for (int j = 0; j < n - i - 1; j++){
            if (strcmp(sv[j].NAME, sv[j + 1].NAME) > 0){
                Swap(sv[j], sv[j + 1]);
                haveSwap = true; 
            }
        }
        if(haveSwap == false){
            break;
        }
    }
    printf("\nSap xep theo ten: \n");
    printf("\n%-10s %-30s %-5s\n", "ID", "NAME", "GRADE");	
	for(int i = 0; i < n; i++)
	{  
        printf("%-10d %-30s %-5.2lf\n", sv[i].ID, sv[i].NAME, sv[i].GRADE);  
	}  
}

void Max(char *FileName){
	FILE *f;   	
	STUDENT sv;   	
	f = fopen(FileName,"r+");   
	fread(&sv, sizeof(sv), 1, f);
	double maxGrade = sv.GRADE;
	while (!feof(f))  
	{  
        if(sv.GRADE > maxGrade) maxGrade = sv.GRADE;
        fread(&sv, sizeof(sv), 1, f);
	}
	
	rewind(f);	

	fread(&sv, sizeof(sv), 1, f);
	printf("\nSinh vien co diem cao nhat la: \n");
	while (!feof(f))  
	{ 
        if(sv.GRADE == maxGrade){
        	printf("%-10d %-30s %-5.2lf\n", sv.ID, sv.NAME, sv.GRADE);  
		} 
		fread(&sv, sizeof(sv), 1, f);
	}
	fclose(f);    
}

void Add(char *FileName){
	FILE *f;   	
	STUDENT sv;   	
	f = fopen(FileName,"r+");
	fseek(f, 0, SEEK_END);
	printf("\nNhap sinh vien moi: \n");   	 	
	printf(" - ID: ");
	scanf("%d", &sv.ID);  
    fflush(stdin);
	printf(" - Ho ten: ");
	gets(sv.NAME);
    printf(" - Diem: ");
	scanf("%lf", &sv.GRADE);
	fwrite(&sv, sizeof(sv), 1, f);   
	n++;
	fclose(f);  
}

void Edit(char *FileName){
	FILE *f; 
	f = fopen(FileName,"r+");
	int id;
	bool check = false;
	printf("\nNhap ID sinh vien muon sua: ");
	scanf("%d", &id);
	STUDENT sv;
	while(!feof(f)){
		fread(&sv, sizeof(sv), 1, f);
		if(sv.ID == id){
			check = true;
			int key;
			fflush(stdin);
			printf("\nNhap thong tin muon sua (ID - 1, NAME - 2, GRADE - 3) : "); scanf("%d", &key);
			fflush(stdin);
			KEY: switch (key)
			{
			case 1:
				int ID;
				fseek(f, -sizeof(STUDENT), SEEK_CUR);
				printf("Nhap ID sinh vien muon sua: ");
				scanf("%d", &ID);
				fwrite(&ID, sizeof(ID), 1, f);
				break;
			case 2:
				char NAME[50];
				fseek(f, -sizeof(STUDENT) + sizeof(int), SEEK_CUR);
				printf("Nhap NAME sinh vien muon sua: ");
				gets(NAME);
				fwrite(&NAME, sizeof(NAME), 1, f);
				break;
			case 3:
				double GRADE;
				fseek(f, -sizeof(double), SEEK_CUR);
				printf("Nhap GRADE sinh vien muon sua: ");
				scanf("%lf", &GRADE);
				fwrite(&GRADE, sizeof(GRADE), 1, f);
				break;
			default:
				printf("Moi nhap lai KEY!!!");
				goto KEY; 
				break;
			}
			break;
		}
	}
	if(check == false) printf("\nKhong ton tai STUDENT co ID = %d", id);
	fclose(f);
}

void Remove(char *FileName){
	FILE *f, *e; 
	f = fopen(FileName, "r+");
	e = fopen("Temp.dat", "w+");
	STUDENT sv;
	int id;
	bool check = false;
	printf("\nNhap ID sinh vien muon xoa: ");
	scanf("%d", &id);
	fread(&sv, sizeof(sv), 1, f);
	while(!feof(f)){
		if(sv.ID != id) fwrite(&sv, sizeof(sv), 1, e);
		else{
			check = true; n--;
		}
		fread(&sv, sizeof(sv), 1, f);
	}
	if(check == false) printf("\nKhong ton tai STUDENT co ID = %d", id);
	fclose(e);
	fclose(f);
	remove(FileName);
	rename("Temp.dat", FileName);
	remove("Temp.dat");
}