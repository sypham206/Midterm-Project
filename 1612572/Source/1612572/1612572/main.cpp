/*
Hàm bool 3-4 biến: x,y,z,t
Phép toán hợp kí hiệu là: '+'
Phần tử bù của x là -x
Cần viết 1 hàm làm sạch hàm Bool đầu vào, có thể sửa lại hàm hoặc xuất ra thông báo input không hợp lệ
*/
#include<iostream>
#include"fBool.h"

int main()
{
	// Tạo giá trị hàm bool
	string str2 = "xyzt + x-y + x-z + yz + xy-z + xy-t";
	string str = "-yzt + -y-z-t + y-z-t + xyzt + -xz-t";
	// Biểu đồ Karnaugh
	int Karnaugh[4][4] = { 0 };
	// Đánh dấu biểu đồ Karnaugh
	tickWithBool(Karnaugh, str);
	// In ra biểu đồ Karnaugh
	showKar(Karnaugh);
	// Tìm các công thức đa thức tối tiểu
	findMinimalPolynomial(str);

	// Phần footer chương trình
	cout << "\n\n Tks for watching!";
	cout << endl << endl;
	system("pause");
	return 0;
}