#include <stdio.h>
#include <math.h>
#include <conio.h>
#define MAX 50

typedef struct {
	int deg;
	double heso[MAX];   // a0 + a1 x + a2 x^2 + ...
} Poly;

typedef struct {
	Poly tu;
	Poly mau;
} PhanThuc;

void NhapPhanThuc(PhanThuc &a);
void XuatDaThuc(Poly a);
void XuatPhanThuc(PhanThuc a);
Poly Tong2DaThuc(Poly a, Poly b);
Poly Hieu2DaThuc(Poly a, Poly b);
Poly Nhan2DaThuc(Poly a, Poly b);
int HaBac(Poly a);
Poly Chia2DaThuc(Poly a, Poly b);
Poly ChiaDaThucLayThuong(Poly a, Poly b);
Poly GCDDaThuc(Poly a, Poly b);
void ChuanHoa(Poly &a);
PhanThuc Tong2PhanThuc(PhanThuc a, PhanThuc b);
PhanThuc Hieu2PhanThuc(PhanThuc a, PhanThuc b);
PhanThuc Nhan2PhanThuc(PhanThuc a, PhanThuc b);
PhanThuc Chia2PhanThuc(PhanThuc a, PhanThuc b);
void RutGon(PhanThuc &a);

int main(){
	PhanThuc a, b;
	printf("Nhap phan thuc A: \n");
	NhapPhanThuc(a);
	RutGon(a);
	
	printf("Nhap phan thuc B: \n");
	NhapPhanThuc(b);
	RutGon(b);
	
	printf("Phan thuc A da rut gon la: \n");
	XuatPhanThuc(a);
	
	printf("Phan thuc B da rut gon la: \n");
	XuatPhanThuc(b);
	
	PhanThuc sum = Tong2PhanThuc(a, b);
	RutGon(sum);
	printf("Phan thuc A + B la: \n");
	XuatPhanThuc(sum);
	
	PhanThuc hieu = Hieu2PhanThuc(a, b);
	RutGon(hieu);
	printf("Phan thuc A - B la: \n");
	XuatPhanThuc(hieu);
	
	PhanThuc mul = Nhan2PhanThuc(a, b);
	RutGon(mul);
	printf("Phan thuc A * B la: \n");
	XuatPhanThuc(mul);
	
	PhanThuc div = Chia2PhanThuc(a, b);
	RutGon(div);
	printf("Phan thuc A / B la: \n");
	XuatPhanThuc(div);
}

void NhapPhanThuc(PhanThuc &a){
	printf("Nhap bac cua da thuc tren tu: "); scanf("%d", &a.tu.deg);
	printf("Nhap he so cua da thuc tren tu (bat dau tu bac 0): ");
	for(int i = 0; i <= a.tu.deg; i++) scanf("%lf", &a.tu.heso[i]);
	printf("Nhap bac cua da thuc duoi mau: "); scanf("%d", &a.mau.deg);
	printf("Nhap he so cua da thuc duoi mau (bat dau tu bac 0): ");
	for(int i = 0; i <= a.mau.deg; i++) scanf("%lf", &a.mau.heso[i]);
}

void XuatDaThuc(Poly a){
	for(int i = 0; i <= a.deg; i++) {
		printf("%.2lf x^{%d}", a.heso[i], i);
		if(i != a.deg) printf(" + ");
	}
	printf("\n");
}

void XuatPhanThuc(PhanThuc a){
	printf("\n%10s", "");
	for(int i = 0; i <= a.tu.deg; i++) {
		printf("%.2lf x^{%d}", a.tu.heso[i], i);
		if(i != a.tu.deg) printf(" + ");
	}
	if(a.mau.deg >= 0){
		printf("\n%5s", "");
		printf("---------------------------------------------------\n");
		printf("%10s", "");
		for(int i = 0; i <= a.mau.deg; i++){
			printf("%.2lf x^{%d}", a.mau.heso[i], i);
			if(i != a.mau.deg) printf(" + ");
		}
	}
	printf("\n\n");
}

Poly Tong2DaThuc(Poly a, Poly b){
	Poly c;
	int max = a.deg >= b.deg ? a.deg : b.deg;
	int min = a.deg <= b.deg ? a.deg : b.deg;
	c.deg = max;
	for(int i = 0; i <= c.deg; i++){
		c.heso[i] = 0;
		if(a.deg >= b.deg && i > min) c.heso[i] = a.heso[i];
		else if(b.deg >= a.deg && i > min) c.heso[i] = b.heso[i];
	}
	for(int i = 0; i <= min; i++){
		c.heso[i] = a.heso[i] + b.heso[i];
	}
	return c;
}

Poly Hieu2DaThuc(Poly a, Poly b){
	Poly c;
	int max = a.deg >= b.deg ? a.deg : b.deg;
	int min = a.deg <= b.deg ? a.deg : b.deg;
	c.deg = max;
	for(int i = 0; i <= c.deg; i++){
		c.heso[i] = 0;
		if(a.deg >= b.deg && i > min) c.heso[i] = a.heso[i];
		else if(b.deg >= a.deg && i > min) c.heso[i] = -b.heso[i];
	}
	for(int i = 0; i <= min; i++){
		c.heso[i] = a.heso[i] - b.heso[i];
	}
	return c;
}

Poly Nhan2DaThuc(Poly a, Poly b){
	Poly c;
	c.deg = a.deg + b.deg;
	for(int i = 0; i <= c.deg; i++){
		c.heso[i] = 0;
	}
	for(int j = 0; j <= a.deg; j++){
		for(int k = 0; k <= b.deg; k++){
			c.heso[j + k] += a.heso[j] * b.heso[k];
		}
	}
	return c;
}

int HaBac(Poly a){
	for(int i = a.deg; i >= 0; i--){
		if(fabs(a.heso[i]) < 1e-8) a.deg--;
	}
	return a.deg;
}

Poly Chia2DaThuc(Poly a, Poly b){    // deg a > deg b, tra ve da thuc du R(x)
	double c = a.heso[a.deg] / b.heso[b.deg];
	int cdeg = a.deg - b.deg;
	Poly ans;
	ans.deg = cdeg;
	for(int i = 0; i < ans.deg; i++) ans.heso[i] = 0;
	ans.heso[ans.deg] = c;
	Poly tmp = Hieu2DaThuc(a, Nhan2DaThuc(ans, b)); 
	tmp.deg = HaBac(tmp);
	return tmp;
}

Poly ChiaDaThucLayThuong(Poly a, Poly b){    // deg a > deg b
	Poly ans;
	ans.deg = a.deg - b.deg;
	for(int i = 0; i <= ans.deg; i++) ans.heso[i] = 0;
	while(a.deg >= b.deg){
		double c = a.heso[a.deg] / b.heso[b.deg];
		int cdeg = a.deg - b.deg;
		Poly ans2;
		ans2.deg = cdeg;
		for(int i = 0; i < ans2.deg; i++) ans2.heso[i] = 0;
		ans.heso[cdeg] = c;
		ans2.heso[cdeg] = c;
		a = Hieu2DaThuc(a, Nhan2DaThuc(ans2, b)); 
		a.deg = HaBac(a);
	}
	return ans;
}

Poly GCDDaThuc(Poly a, Poly b){
	if(a.deg >= b.deg){
		if(b.deg == -1) return a;
		return GCDDaThuc(b, Chia2DaThuc(a, b));
	}
	if(a.deg < b.deg){
		if(a.deg == -1) return b;
		return GCDDaThuc(a, Chia2DaThuc(b, a));
	}
}

void ChuanHoa(Poly &a){
	double c = a.heso[a.deg];
	for(int i = 0; i <= a.deg; i++){
		a.heso[i] /= c;
	}	
}

PhanThuc Tong2PhanThuc(PhanThuc a, PhanThuc b){
	PhanThuc c;
	c.tu = Tong2DaThuc(Nhan2DaThuc(a.tu, b.mau), Nhan2DaThuc(a.mau, b.tu));
	c.mau = Nhan2DaThuc(a.mau, b.mau);
	return c;
}

PhanThuc Hieu2PhanThuc(PhanThuc a, PhanThuc b){
	PhanThuc c;
	c.tu = Hieu2DaThuc(Nhan2DaThuc(a.tu, b.mau), Nhan2DaThuc(a.mau, b.tu));
	c.mau = Nhan2DaThuc(a.mau, b.mau);
	return c;
}

PhanThuc Nhan2PhanThuc(PhanThuc a, PhanThuc b){
	PhanThuc c;
	c.tu = Nhan2DaThuc(a.tu, b.tu);
	c.mau = Nhan2DaThuc(a.mau, b.mau);
	return c;
}

PhanThuc Chia2PhanThuc(PhanThuc a, PhanThuc b){
	PhanThuc c;
	c.tu = Nhan2DaThuc(a.tu, b.mau);
	c.mau = Nhan2DaThuc(a.mau, b.tu);
	return c;
}

void RutGon(PhanThuc &a){
	Poly c = GCDDaThuc(a.tu, a.mau);
	ChuanHoa(c);
	a.tu = ChiaDaThucLayThuong(a.tu, c);
	a.mau = ChiaDaThucLayThuong(a.mau, c);
}
