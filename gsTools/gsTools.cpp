#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;

const double PI = 3.141592;
const double G = 10.;

double toRadians(double degree) {
	return degree * PI / 180.;
}

class Integral {
public:
	unsigned int mode;
	double A;
	double B;
	double a;
	double b;
	double c;

	double calcSq(int times) {
		int bunkatsu = times; //分割数
		double haba = (B - A) / (double)bunkatsu; //高さ
		double x = A;
		double y = A + haba;
		double S = 0.; //面積
		for (int i = 0; i < bunkatsu; i++)
		{
			S += ((((a * (x * x)) + b * x + c) + ((a * (y * y)) + b * y + c)) * haba) / 2.;
			x = y;
			y += haba;
		}
		return S;
	}

	double calcSin(int times)
	{
		int bunkatsu = times; //分割数
		double haba = (B - A) / (double)bunkatsu; //高さ
		double x = A;
		double y = A + haba;
		double S = 0.; //面積
		for (int i = 0; i < bunkatsu; i++)
		{
			S += (((a * sin(b * x) + c) + (a * sin(b * y) + c)) * haba) / 2.;
			x = y;
			y += haba;
		}
		return S;
	}

	double calcCos(int times)
	{
		int bunkatsu = times; //分割数
		double haba = (B - A) / (double)bunkatsu; //高さ
		double x = A;
		double y = A + haba;
		double S = 0.; //面積
		for (int i = 0; i < bunkatsu; i++)
		{
			S += (((a * cos(b * x) + c) + (a * cos(b * y) + c)) * haba) / 2.;
			x = y;
			y += haba;
		}
		return S;
	}

	double calc(int times)
	{
		switch (mode)
		{
		case  0:
			return calcSq(times);
			break;
		case 1:
			return calcSin(times);
			break;
		case 2:
			return calcCos(times);
			break;
		default:
			return 0.;
		}
	}

	void print(int times)
	{
		cout << "分割数" << times << " : " << calc(times) << endl;
	}

	void exec()
	{
		print(4);
		print(10);
		print(20);
		print(50);
		print(100);
	}

	Integral(unsigned int mode, double a, double b, double c, double A, double B)
	{
		this->mode = mode;
		this->a = a;
		this->b = b;
		this->c = c;
		this->A = A;
		this->B = B;
	}
};

class Differential {
public:
	double x;
	double a;
	double b;
	double c;

	double calcAdvance(double h) {
		return (calcFuncX(a, b, c, x + h) - calcFuncX(a, b, c, x)) / h;
	}

	double calcBack(double h) {
		return (calcFuncX(a, b, c, x) - calcFuncX(a, b, c, x - h)) / h;
	}

	double calcCenter(double h) {
		return (calcFuncX(a, b, c, x + h) - calcFuncX(a, b, c, x - h)) / (2 * h);
	}

	double calcFuncX(double a, double b, double c, double x) {
		return a * pow(x, 2.) + b * x + c;
	}

	void calc(double *resultArrayPtr, double  h)
	{
		resultArrayPtr[0] = calcAdvance(h);
		resultArrayPtr[1] = calcBack(h);
		resultArrayPtr[2] = calcCenter(h);
	}

	void print(double h)
	{
		double result[3];

		cout << "◆h=" << h << endl;
		calc(result, h);
		cout << "x=" << x << "での前進差分：" << result[0] << endl;
		cout << "x=" << x << "での後退差分：" << result[1] << endl;
		cout << "x=" << x << "での中心差分：" << result[2] << endl;
	}

	void exec()
	{
		print(1.);
		print(1E-1);
		print(1E-2);
		print(1E-6);
	}

	Differential(double x, double a, double b, double c)
	{
		this->x = x;
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

class PhysicalObject {
public:
	double v0Array[2];
	double vArray[2];
	double aArray[2];
	double v0Angle;
	double aAngle;
	double v0;
	double a;
	double t;
	double x;
	double y;
	double m;

	void v(double dt) {
		t += dt;
		vArray[0] += aArray[0] * dt;
		vArray[1] += aArray[1] * dt;
		x += vArray[0] * dt;
		y += vArray[1] * dt;
	}

	void v(double dt, double k) {
		t += dt;
		vArray[0] = v0 * exp(-1 * k / m * t) * cos(v0Angle);
		vArray[1] = (v0 * sin(v0Angle) + m / k * G) * exp(-1 * k / m * t) - m / k * G;
		x += vArray[0] * dt;
		y += vArray[1] * dt;
	}

	void print() {
		cout << x << ", " << y << endl;
	}

	PhysicalObject(double v0, double a = G, double v0Degree = 90., double m = 1., double t = 0., double x = 0., double y = 0., double aDegree = 270.) {
		this->v0 = v0;
		this->a = a;
		this->v0Angle = toRadians(v0Degree);
		this->v0Array[0] = cos(v0Angle) * v0;
		this->v0Array[1] = sin(v0Angle) * v0;
		this->vArray[0] = v0Array[0];
		this->vArray[1] = v0Array[1];
		this->aAngle = toRadians(aDegree);
		this->aArray[0] = cos(aAngle) * a;
		this->aArray[1] = sin(aAngle) * a;
		this->t = t;
		this->x = x;
		this->y = y;
		this->m = m;
	}
};

void exec0()
{
	unsigned int mode;
	cout << "0: 二次関数, 1: 正弦関数, 2: 余弦関数" << endl << "mode: ";
	cin >> mode;
	switch (mode)
	{
	case 0:
		cout << "f(x) = a * x^2 + b * x + c" << endl;
		break;;
	case 1:
		cout << "f(x) = a * sin(b * x) + c" << endl;
		break;
	case 2:
		cout << "f(x) = a * cos(b * x) + c" << endl;
		break;
	}
	double a;
	double b;
	double c;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "c: ";
	cin >> c;
	double A;
	double B;
	cout << "積分区間を入力" << endl << "A: ";
	cin >> A;
	cout << "B: ";
	cin >> B;

	Integral *it = new Integral(mode, a, b, c, A ,B);

	it->exec();
}
void exec1()
{
	double a;
	double b;
	double c;
	double x;

	cout << "f(x) = a * x^2 + b * x + c" << endl;
	cout << "x: ";
	cin >> x;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "c: ";
	cin >> c;


	Differential *df = new Differential(x, a, b, c);

	df->exec();
}
void exec2()
{
	double x = 0.;
	double v0;
	double degree = 90.;
	double t = 0.;
	cout << "初速度を入力 [m/s]: ";
	cin >> v0;
	cout << "初速度ベクトルが地表面となす角を入力 [°]: ";
	cin >> degree;
	double k = 0.;
	cout << "空気抵抗の係数を入力 : ";
	cin >> k;
	double m = 0.;
	if (abs(k) > 0) {
		cout << "質量を入力 : ";
		cin >> m;
	}
	double vArray[] = { 0, 0 };
	PhysicalObject *po = new PhysicalObject(v0, G, degree, m, 0., 0., 0., 270.);
	double y = 0.;
	double dt = 1E-5;

	long count = 0;

	cout << "距離, 高さ" << endl;

	bool airFlag = abs(k) > 0 && m > 0;

	po->print();

	if (airFlag) {
		do {
			po->v(dt, k);
			if (++count % 10000 == 0) {
				po->print();
			}

		} while (po->y >= 0);
	}
	else {
		do {
			po->v(dt);
			if (++count % 10000 == 0) {
				po->print();
			}

		} while (po->y >= 0);
	}
	po->print();
}

int main() {
	unsigned int mode = 3;
	bool endFlag = false;

	while (!endFlag)
	{
		cout << "モードを選択 (0: 積分, 1: 微分, 2: 斜方投射): ";
		cin >> mode;

		switch (mode)
		{
		case 0:
			exec0();
			break;
		case 1:
			exec1();
			break;
		case 2:
			exec2();
			break;
		default:
			endFlag = true;
			break;
		}
	}


	return 0;
}
