#pragma once
#include<iostream>
using namespace std;
#define MAX 100

/* Xác định độ dài đơn thức
Tham số truyền vào: chuỗi str đại điện đơn thức.
Trả về độ dài đơn thức (số biến x/y/z/t của đơn thức) */
int lenOfMonomial(string str);

/* Tìm danh sách đơn thức trong hàm Bool
Tham số truyền vào: chuỗi str đại diện cho hàm Bool, mảng chuỗi arrMonomimal lưu danh sách đơn thức, biến len kiểu int lưu độ dài của mảng
Hàm thay đổi giá trị mảng arrMonomimal và biến len tương ứng là danh sách đơn thức của hàm Bool và độ dài mảng */
void findMonomial(string str, string arrMonomial[MAX], int& len);

/* Đánh dấu các ô trong biểu đồ Karnaugh với một đơn thức nhập vào. Dùng để bổ trợ cho hàm tickWithBool()
Tham số truyền vào: Mảng int 2 chiều Kar thể hiện cho biểu đồ Karnaugh, chuỗi tmp đại diện đơn thức
Hàm thay đổi giá trị mảng 2 chiều Kar thành biểu đồ Karnaugh của đơn thức tmp */
void tickWithMonomial(int Kar[4][4], string tmp);

/* Đánh dấu các ô trong biểu đồ Karnaugh với hàm Bool nhập vào
Tham số truyền vào: Mảng int 2 chiều Kar thể hiện cho biểu đồ Karnaugh, chuỗi str đại diện cho hàm Bool
Hàm thay đổi giá trị mảng 2 chiều Kar thành biểu đồ Karnaugh của hàm Bool str */
void tickWithBool(int Kar[4][4], string str);

/* Xác định một đơn thức/ đa thức có thuộc đơn thức/ đa thức khác hay không
Tham số truyền vào: chuỗi child và chuỗi parent
Hàm trả về 1 nếu child thuộc parent, ngược lại trả về 0 */
int isChild(string child, string parent);

/* In ra biểu đồ Karnaugh
Tham số truyền vào: mảng 2 chiều Kar
Hàm in ra biểu đồ Karnaugh tương ứng */
void showKar(int Kar[4][4]);

/* Tìm tất cả các tế bào của biểu đồ Karnaugh
Hàm không có tham số truyền vào
Hàm in ra tất cả các tế bào có thể có của biểu đồ Karnaugh ( có tất cả 80 tế bào tìm được với trường hợp n = 4) */
void printAllCell();

/* Tìm các công thức đa thức tối tiểu của hàm Bool
Tham số truyền vào: chuỗi str đại diện hàm Bool
Hàm in ra tất cả các đa thức tối tiểu của hàm Bool */
void findMinimalPolynomial(string str);