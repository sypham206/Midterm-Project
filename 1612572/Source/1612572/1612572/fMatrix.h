#pragma once
#include<iostream>
using namespace std;
#define MAX_MATRIX 100

// Định nghĩa ma trận cấp NxM
struct Matrix
{
	int N;
	int M;
	float a[MAX_MATRIX][MAX_MATRIX]; // a[dòng][cột]
};

/* Hàm in ra ma trận
Tham số truyền vào: ma trận pMatrix
Hàm in ra ma trận pMatrix */
void printMatrix(Matrix pMatrix);

/* Hàm tạo Ma trận 0
Tham số truyền vào: ma trận pMatrix
Hàm set các giá trị 0 cho ma trận pMatrix */
void setMatrix(Matrix & pMatrix);

/* Hàm trình bày lại ma trận trong trường hợp hiển thị -0 thay vì 0
Tham số truyền vào: ma trận pMatrix
Hàm sửa các giá trị -0 thay bằng 0 */
void refreshMatrix(Matrix& pMatrix);

/* Hàm tìm định thức ma trận
Tham số truyền vào: ma trận pMatrix
Trả về kết quả số thực là định thức của ma trận pMatrix */
float detMatrix(Matrix pMatrix);

/* Hàm tìm ma trận nghịch đảo
Tham số truyền vào: ma trận pMatrix
Trả về kết quả ma trận là ma trận nghịch đảo của pMatrix */
Matrix inverseMatrix(Matrix pMatrix);

/* Hàm tính tích 2 ma trận
Tham số truyền vào: ma trận x và ma trận y
Trả về kết quả ma trận là tích của 2 ma trận truyền vào */
Matrix mulMatrix(Matrix x, Matrix y);
