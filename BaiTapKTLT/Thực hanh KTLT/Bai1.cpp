#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 50
#define epsilon  1.0e-8
#define setfill(x) for(int i = 0; i < x; i++) printf("=")
#define row 4
#define col 4

int sign, dem = 0, cntGtr = 0;
double save[MAX], Gtr[MAX];  
typedef struct {
	double MAT[row][col];
} Matrix;

typedef struct {
	double heso[MAX];        // a0 + a1 x + a2 a^2 + ....
} Dathuc;

void InPut(Matrix &mat);
void OutPut(Matrix mat);
Matrix SumMat(Matrix mat1, Matrix mat2);	
Matrix MulMat(Matrix mat1, Matrix mat2);	
Matrix Ix(int x); 							
Matrix Mx(Matrix mat, Matrix I, int i);     
Matrix Mx_1(Matrix M, int i);               	
Matrix mul3Mat(Matrix mat1, Matrix mat2, Matrix mat3);  
int Case1(Matrix mat, int i);				
void DoiHangDoiCot(Matrix &mat, int i, int q);  
Matrix TachMatrix(Matrix mat, int k);		
Matrix Frobenius(Matrix mat);				
Dathuc DaThucDacTrung(Matrix mat, int i, int j); 
void swap(double &x, double &y);
void bubbleSort(double arr[], int n);		
double f(double x, Dathuc P, int deg);      
double PPChiaDoi(double a, double b, Dathuc P, int deg);   
Dathuc DaoHamDaThuc(Dathuc P, int deg);	  
void SOLVE(Dathuc Pt, int deg);  

int main(){
	Matrix mat1, mat2;
	printf("Nhap ma tran A: \n");
	InPut(mat1);
    printf("Nhap ma tran B: \n");
	InPut(mat2);
	printf("Ma tran A la: \n"); OutPut(mat1);
    printf("Ma tran B la: \n"); OutPut(mat1);
    Matrix mul = MulMat(mat1, mat2);
    Matrix sum = SumMat(mat1, mat2);
    printf("Ma tran A*B la: \n"); OutPut(mul);
    printf("Ma tran A + B la: \n"); OutPut(sum);
    printf("Gia tri rieng cua A la: \n");
	Matrix Fro1 = Frobenius(mat1);
    return 0;
}

void InPut(Matrix &mat){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%lf", &mat.MAT[i][j]);
		}
	}
}

void OutPut(Matrix mat){
	setfill(MAX); printf("\n");
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("% 8.2lf", mat.MAT[i][j]);
			j == col - 1 ? printf("\n") : printf("");
		}
	}
	setfill(MAX); printf("\n");
}

Matrix SumMat(Matrix mat1, Matrix mat2){
	Matrix temp;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			temp.MAT[i][j] = mat1.MAT[i][j] + mat2.MAT[i][j];
		}
	}
	return temp;
}

Matrix MulMat(Matrix mat1, Matrix mat2){
	Matrix temp;
	for (int i = 0; i < row; i++) {
    	for (int j = 0; j < col; j++) {
    		double sum = 0;
    		for (int k = 0; k < row; k++) {
            	sum = sum + mat1.MAT[i][k] * mat2.MAT[k][j];
        	}
        	temp.MAT[i][j] = sum;
      }
   }
   return temp;
}

Matrix Ix(int x){   
	Matrix I;
	for(int i = 0; i < x; i++){
		for(int j = 0; j < x; j++){
			i == j ? I.MAT[i][j] = 1 : I.MAT[i][j] = 0;
		}
	}
	return I;
}

Matrix Mx(Matrix mat, Matrix I, int i){   
	for(int j = 0; j < col; j++) I.MAT[i - 1][j] = mat.MAT[i][j];
	return I;
}

Matrix Mx_1(Matrix M, int i){    
	double Ann_1 = M.MAT[i - 1][i - 1];
	for(int j = 0; j < col; j++){
		j == i - 1 ? M.MAT[i - 1][j] = 1.0 / M.MAT[i - 1][j] : M.MAT[i - 1][j] = - M.MAT[i - 1][j] / Ann_1;
	}
	return M;
}

Matrix mul3Mat(Matrix mat1, Matrix mat2, Matrix mat3){
	return MulMat(MulMat(mat1, mat2), mat3);
}

int Case1(Matrix mat, int i){
	int q = -1;
    if(i == 1) return q;
	for(int k = 0; k < i; k++){     
		if(mat.MAT[i][k] != 0){
			q = k; break;
		}
	}
	return q;
}

void DoiHangDoiCot(Matrix &mat, int i, int q){
	for(int m = 0; m < col; m++){
		double temp = mat.MAT[i][m];
		mat.MAT[i][m] = mat.MAT[q][m];
		mat.MAT[q][m] = temp;
	}
	for(int m = 0; m < row; m++){
		double temp = mat.MAT[m][i];
		mat.MAT[m][i] = mat.MAT[m][q];
		mat.MAT[m][q] = temp;
	}
}

Matrix TachMatrix(Matrix mat, int k){
	Matrix mat_ ;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			i < k && j < k ? mat_.MAT[i][j] = mat.MAT[i][j] : mat_.MAT[i][j] = 0;
		}
	}
	return mat_;
}

Dathuc DaThucDacTrung(Matrix mat, int i, int j){
	Dathuc P;
	int deg = 0;
	int Sign = pow(-1, j - i);
	P.heso[j - i] = Sign;
	for(; j > i; j--){
		P.heso[deg++] = -1.0*mat.MAT[i][j - 1]*Sign;
	}
	return P;
}

void swap(double &x, double &y){
    double temp = x;
    x = y;
    y = temp;
}
 
void bubbleSort(double arr[], int n){
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n - 1; i++){
        haveSwap = false;
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j+1]);
                haveSwap = true;
            }
        }
        if(haveSwap == false){
            break;
        }
    }
}

double f(double x, Dathuc P, int deg){
	double sum = P.heso[deg];
	for(int i = deg - 1; i >= 0; i--){
		sum = sum * x + P.heso[i];
	}
	return sum;
}

double PPChiaDoi(double a, double b, Dathuc P, int deg){
	double fa = f(a, P, deg), fb = f(b, P, deg), z = b - a;
	if(fabs(fa) < 1e-8) return a;
	if(fabs(fb) < 1e-8) return b;
	double c = (b + a)/2;
	while(z > 1e-4){
		if(fabs(f(c, P, deg)) < 1e-8) return c;
		if(f(a, P, deg) * f(c, P, deg) < 0) b = c;
		else a = c;
		z = fabs(b - a);
		c = (b + a)/2;
	}
	return c;
}

double BanKinhNghiem(Dathuc P, int deg){
    double m = fabs(P.heso[0]);
    for(int i = 0; i <= deg; i++){
        if(m < fabs(P.heso[i])) m = fabs(P.heso[i]);
    }
    return 1 + m * 1.0 / fabs(P.heso[deg]);
}

Dathuc DaoHamDaThuc(Dathuc P, int deg){
    Dathuc Pt;
    for(int i = 0; i < deg; i++){
        Pt.heso[i] = (i + 1)*P.heso[i + 1];
    }
    return Pt;
}

void SOLVE(Dathuc Pt, int deg){
	double SAVE[deg + 1][MAX];
    Dathuc P[deg + 1];
	for(int i = 0; i <= deg; i++){
		P[0].heso[i] = Pt.heso[i];
	}
    for(int i = 1; i <= deg - 1; i++){
        P[i] = DaoHamDaThuc(P[i - 1], deg - i + 1); 
    }
    for(int i = 0; i <= deg - 2; i++){
        double R = BanKinhNghiem(P[i], deg - i);
        SAVE[i][0] = R;
        SAVE[i][1] = -R;
    }
    SAVE[deg - 2][2] = -P[deg - 1].heso[0] / P[deg - 1].heso[1];
    int count = 2;
    for(int i = deg - 2; i >= 0; i--){
        int cnt = 2;
        if(i == 0) cnt = 0;
        if(i == deg - 2) bubbleSort(SAVE[i], cnt + 1);
        else bubbleSort(SAVE[i], count + 1);
        for(int k = 0; k <= count - 1; k++){
            if(f(SAVE[i][k], P[i], deg - i) * f(SAVE[i][k + 1], P[i], deg - i) <= 0){
                SAVE[i - 1][cnt++] = PPChiaDoi(SAVE[i][k], SAVE[i][k + 1], P[i], deg - i);
            }
        }
        count = cnt - 1;
    }
    for(int j = 0; j <= count ; j++){
		//printf("%15.2lf", SAVE[- 1][j]);
		Gtr[cntGtr++] = SAVE[-1][j];
    }
        //printf("\n");
}

Matrix Frobenius(Matrix mat){
	Matrix Fro, I = Ix(row);
	Fro = MulMat(mat, I);
	int i = row - 1, j = i;
	while(i >= 1){
		if(Fro.MAT[i][i - 1] != 0){
			Matrix M = Mx(Fro, I, i);
			Matrix M_1 = Mx_1(M, i);
			Fro = mul3Mat(M, Fro, M_1);
			// OutPut(Fro);
		}
		else{
			int q = Case1(mat, i);
			if(q != -1){
				// printf("Case 1 \n");
				DoiHangDoiCot(Fro, i - 1, q);
                // OutPut(Fro);
				i++;
			}
			else{
				// printf("Case 2 \n");
				Dathuc P = DaThucDacTrung(Fro, i, j + 1); 
				if(j - i + 1 == 1) Gtr[cntGtr++] = -P.heso[0] / P.heso[1];
				else SOLVE(P, j - i + 1);
				j = i - 1;
				Fro = TachMatrix(Fro, i);
				// OutPut(Fro);
			}
		}
		i--;
	}
	Dathuc P = DaThucDacTrung(Fro, 0, j + 1);
    //printf("\n");
	if(j + 1 == 1) Gtr[cntGtr++] = -P.heso[0] / P.heso[1];
	else SOLVE(P, j + 1);
    // printf("So gia tri rieng là: %d \n", cntGtr);
	for(int k = 0; k <= cntGtr - 1; k++){
		printf("%15.2lf", Gtr[k]);
	}
	printf("\n");
	return Fro;
}

