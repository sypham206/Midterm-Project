#pragma once
#include<iostream>
using namespace std;
#define MAX_DEGREE 100
#define MAX_VALUE 100

/* Định nghĩa vector bậc N (degree) */
struct Vector
{
	int degree;
	float value[MAX_DEGREE];
};

/* Hàm tạo Vector 0
Tham số truyền vào: Vector A
Hàm set các giá trị 0 cho Vector A*/
void setVector(Vector &A);

/* Hàm chuyển đổi số nguyên kiểu string về kiểu int
Tham số truyền vào: số nguyên dương kiểu string
Trả về kết quả là số nguyên dương kiểu int */
int stringToInt(string str);

/* Hàm chuyển đổi số thực dương kiểu string về kiểu float
Tham số truyền vào: số thực dương kiểu string
Trả về kết quả là số thực dương kiểu float */
float stFloat(string str);

/* Hàm chuyển đổi số thực kiểu string về kiểu float
Tham số truyền vào: số thực kiểu string
Trả về kết quả là số thực kiểu float */
float stringToFloat(string str);

/* Hàm lấy ra các giá trị của vector từ biểu diễn vector dạng chuỗi
Tham số truyền vào: chuỗi str là vector dạng chuỗi, mảng chuỗi arrValue lưu các giá trị của vector, len là số phần tử mảng
Hàm lưu các giá trị của vector str vào mảng arrValue cùng số phần tử vào biến len */
void findValue(string str, string arrValue[MAX_VALUE], int& len);

/* Hàm in ra vector
Tham số truyền vào: vector a
Hàm in ra màn hình giá trị vector a */
void printVector(Vector a);

/* Hàm cộng 2 vector
Tham số truyền vào: vector a, vector b
Trả về kết quả là vector tổng của 2 vector a và b */
Vector plusVector(Vector a, Vector b);

/* Hàm nhân vector với một số alpha
Tham số truyền vào: vector a, số thực alpha
Trả về kết quả là vector tích của vector a với số thực alpha */
Vector mulVector(Vector a, float alpha);