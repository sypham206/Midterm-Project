/*
P1: Hàm Bool: Tìm công thức đa thức tối tiểu
*/
#include<iostream>
#include<fstream>
#include"fBool.h"
#include"fVector.h"

int main()
{
	// P1. TÌM CÔNG THỨC ĐA THỨC TỐI TIỂU HÀM BOOL

	cout << "\n\n __________________P1: HAM BOOL__________________ \n";
	fstream inFile;
	// Biến lưu đường dẫn tới file input
	string inPath="inputBool.txt";
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
	
	// P2. PHÉP TOÁN TRÊN VECTOR

	cout << "\n\n ___________________P2: VECTOR___________________ \n";
	fstream inFile2;
	// Biến lưu đường dẫn tới file input
	string inPath2 = "inputVector.txt";
	string listLine[MAX];
	int lenLine = 0;
	Vector a, b;
	float alpha;

	// Mở file, lấy các giá trị trong file lưu vào mảng listLine
	inFile2.open(inPath2, ios::in);
	if (inFile2.fail())
		cout << "Failed to open this file!" << std::endl;
	while (!inFile2.eof())
	{
		char temp[255];
		inFile2.getline(temp, 255);
		listLine[lenLine] = temp;
		lenLine++;
	}
	inFile.close();
	
	// Xử lí dữ liệu trong mảng listLine
	// Dòng 1: Bậc của vector
	int degree = stringToInt(listLine[0]);
	// Dòng 2: Các giá trị của vector a
	string arrA[MAX_VALUE];
	int lenA = 0;
	findValue(listLine[1], arrA, lenA);	
	a.degree = lenA;
	for (int i = 0; i < lenA; i++)
		a.value[i] = stringToFloat(arrA[i]);
	// Dòng 3: Các giá trị của vector b
	string arrB[MAX_VALUE];
	int lenB = 0;
	findValue(listLine[2], arrB, lenB);
	b.degree = lenB;
	for (int i = 0; i < lenB; i++)
		b.value[i] = stringToFloat(arrB[i]);
	Vector c;
	// Dòng 4: Giá trị alpha
	alpha = stringToFloat(listLine[3]);

	// Kiểm tra dữ liệu có hợp lệ không
	if (a.degree == degree && b.degree == degree)
	{
		cout << "\n ------------------------------------------------";
		// In ra số thực Alpha
		cout << "\n ALPHA:           " << alpha;
		// In ra 2 vector a và b
		cout << "\n VECTOR A: \t";
		printVector(a);
		cout << "\n VECTOR B: \t";
		printVector(b);
		// In ra tổng vector
		cout << "\n TONG 2 VECTOR: ";
		printVector(plusVector(a, b));
		// In ra tích vector a với số thực alpha
		cout << "\n TICH A*ALPHA:  ";
		printVector(mulVector(a, alpha));
		cout << "\n ------------------------------------------------";
	}
	else
	{
		cout << "\n ------------------------------------------------";
		cout << "\n File khong hop le";
		cout << "\n ------------------------------------------------";
	}

	// Phần footer chương trình
	cout << "\n\n Tks for watching!";
	cout << endl << endl;
	system("pause");
	return 0;
}