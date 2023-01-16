#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    FILE *f;
    f = fopen("baitap21.txt", "w+");
    char s[2];
    while(!feof(stdin)){
        fgets(s, sizeof(s), stdin);
        fprintf(f, "%s", s);
    }
    
    int cnt1 = 0, cnt2 = 0;
    rewind(f);
    while(!feof(f)){
        char c;
        fscanf(f, "%c", &c);
        if(c == ' ') cnt1++;
        else if(c == '.') cnt2++;
    }
    printf("So tu la: %d", cnt1 != 0 ? cnt1 + 1 : cnt1);
    printf("\nSo cau la: %d", cnt2);

    char sFind[] = "Nghiem";
    rewind(f);
    int check = 0;
    while(!feof(f)){
        char c;
        fscanf(f, "%c", &c);
        while(c == sFind[check]){
            check++;
            fscanf(f, "%c", &c);
            if(check == strlen(sFind)){
                printf("\nCo xuat hien \" %s \"", sFind);
                break;
            } 
        }
        if(check == strlen(sFind)) break;
        check = 0;
    }
    if(check == 0) printf("\nKhong xuat hien \" %s \"", sFind);
}