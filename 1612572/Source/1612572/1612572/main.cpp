/*
Hàm bool 3-4 biến: x,y,z,t
Phép toán hợp kí hiệu là: '+'
Phần tử bù của x là -x
Cần viết 1 hàm làm sạch hàm Bool đầu vào, có thể sửa lại hàm hoặc xuất ra thông báo input không hợp lệ
*/
#include<iostream>
#include<fstream>
#include"fBool.h"

int main()
{
	// P1. TÌM CÔNG THỨC ĐA THỨC TỐI TIỂU HÀM BOOL

	cout << "\n P1: HAM BOOL \n\n";
	fstream inFile;
	// Biến lưu đường dẫn tới file input
	string inPath="input.txt";
	string listBool[MAX];
	int lenListBool = 0;

	// Mở file, lấy các hàm Bool từ file lưu vào mảng listBool
	inFile.open(inPath, ios::in);
	if (inFile.fail())
		cout << "Failed to open this file!" << std::endl;
	while (!inFile.eof())
	{
		char temp[255];
		inFile.getline(temp, 255);
		listBool[lenListBool] = temp;
		lenListBool++;
	}
	inFile.close();

	// Với mỗi hàm Bool trong mảng listBool, in ra các biểu đồ Karnaugh tương ứng và các công thức đa thức tối tiểu của nó
	for (int i = 0; i < lenListBool; i++)
	{
		// In hàm bool đang xử lý
		cout << "\n ------------------------------------------------";
		cout<<"\n HAM BOOL: " << listBool[i] << endl;
		// Biểu đồ Karnaugh
		int Karnaugh[4][4] = { 0 };
		// Đánh dấu biểu đồ Karnaugh
		tickWithBool(Karnaugh, listBool[i]);
		// In ra biểu đồ Karnaugh
		cout << " BIEU DO KARNAUGH: ";
		showKar(Karnaugh);
		// Tìm các công thức đa thức tối tiểu
		cout << "\n CONG THUC DA THUC TOI TIEU: ";
		findMinimalPolynomial(listBool[i]);
		cout << "\n ------------------------------------------------";
		cout << endl;
	}
	
	// Phần footer chương trình
	cout << "\n\n Tks for watching!";
	cout << endl << endl;
	system("pause");
	return 0;
}