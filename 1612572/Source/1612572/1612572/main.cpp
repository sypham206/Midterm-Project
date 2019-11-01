/*
P1: Hàm Bool: Tìm công thức đa thức tối tiểu
P2: Vector: Phép cộng, phép nhân với hằng số 
P3: Ma trận: 
+ Tìm định thức của ma trận
+ Nghịch đảo ma trận.
+ Tích hai ma trận.
+ Tìm hạng của ma trận.
+ Hệ phương trình tuyến tính (chưa hoàn thành)

- Chương trình chạy theo dữ liệu từ các file inputBool.txt inputVector.txt inputMatrix.txt trong thư mục chương trình */

#include<iostream>
#include<fstream>
#include"fBool.h"
#include"fVector.h"
#include"fMatrix.h"

int main()
{	
	// P1. TÌM CÔNG THỨC ĐA THỨC TỐI TIỂU HÀM BOOL

	cout << "\n\n __________________P1: HAM BOOL__________________ \n";
	fstream inFile1;
	// Biến lưu đường dẫn tới file input
	string inPath="inputBool.txt";
	string listBool[MAX];
	int lenListBool = 0;

	// Mở file, lấy các hàm Bool từ file lưu vào mảng listBool
	inFile1.open(inPath, ios::in);
	if (inFile1.fail())
		cout << "Failed to open this file!" << std::endl;
	while (!inFile1.eof())
	{
		char temp[255];
		inFile1.getline(temp, 255);
		listBool[lenListBool] = temp;
		lenListBool++;
	}
	inFile1.close();

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
	inFile2.close();
	
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

	// P3. PHÉP TOÁN TRÊN MA TRẬN

	cout << "\n\n ___________________P3: MATRIX___________________ \n";
	cout << "\n ------------------------------------------------";	
	fstream inFile3;
	Matrix p, q;
	// Biến lưu đường dẫn tới file input
	string inPath3 = "inputMatrix.txt";
	string listRow[MAX_MATRIX];	
	int lenRow = 0;

	// Mở file, lấy các giá trị trong file lưu vào mảng listRow ( các dòng có index từ 1->n, index 0 lưu bậc của ma trận
	inFile3.open(inPath3, ios::in);
	if (inFile3.fail())
		cout << "Failed to open this file!" << std::endl;
	while (!inFile3.eof())
	{
		char temp[255];
		inFile3.getline(temp, 255);
		listRow[lenRow] = temp;
		lenRow++;
	}
	inFile3.close();

	// Xử lí dữ liệu trong mảng listRow
	// Dòng 1: Lấy ra kích thước ma trận
	string sizeMatrix[MAX_MATRIX];
	int s = 0;
	findValue(listRow[0], sizeMatrix, s);
	if (s != 2)
	{
		setMatrix(p);
		cout << "\n File khong hop le";
	}
	else
	{
		p.N = stringToInt(sizeMatrix[0]);
		p.M = stringToInt(sizeMatrix[1]);
	}

	// Kiểm tra xem ma trận thứ nhất (p) có vuông không
	if (p.N == p.M)
	{
		// Lưu giá trị cấp ma trận
		int level = p.N;
		// Lấy ra từng dòng	của ma trận thứ nhất (p)
		for (int i = 1; i <= level; i++) 
		{	// 
			string row[MAX_MATRIX];
			int lenR = 0;
			findValue(listRow[i], row, lenR);
			if (lenR == level)
				for (int j = 0; j < lenR; j++)
					p.a[i - 1][j] = stringToFloat(row[j]);
			else
				// Số phần tử không đúng với cấp ma trận	
			{
				setMatrix(p);
				cout << "\n File khong hop le";
			}
		}
		// Lấy ra kích thước ma trận thứ hai (q)
		string sizeMatrix2[MAX_MATRIX];
		int s2 = 0;
		findValue(listRow[level + 1], sizeMatrix2, s2);
		if (s2 != 2)
		{
			setMatrix(q);
			cout << "\n File khong hop le";
		}
		else
		{
			q.N = stringToInt(sizeMatrix2[0]);
			q.M = stringToInt(sizeMatrix2[1]);
		}
		// Lấy ra từng dòng	của ma trận thứ hai (q)
		for (int i = level + 2; i < level + 2 + q.N; i++)
		{	// 
			string row[MAX_MATRIX];
			int lenR = 0;
			findValue(listRow[i], row, lenR);
			if (lenR == q.M)
				for (int j = 0; j < lenR; j++)
					q.a[i - level - 2][j] = stringToFloat(row[j]);
			else
				// Số phần tử không đúng với cấp ma trận	
			{
				setMatrix(q);
				cout << "\n File khong hop le";
			}
		}
	}
	
	// In kết quả
	cout << "\n MA TRAN P:";

	printMatrix(p);
	cout << "\n * DINH THUC MA TRAN: " << detMatrix(p);
	cout << "\n * HANG CUA MA TRAN: " << findRank(p);

	if (detMatrix(p) != 0)
	{
		cout << "\n * MA TRAN NGHICH DAO:";
		printMatrix(inverseMatrix(p));
	}
	else
	{
		cout << "\n * MA TRAN KHONG KHA NGHICH";
	}
	cout << "\n\n MA TRAN Q:";
	printMatrix(q);
	cout << "\n\n MA TRAN QxP:";
	printMatrix(mulMatrix(q, p));
	cout << "\n ------------------------------------------------";
	

	// Phần footer chương trình
	cout << "\n\n THANK YOU !";
	cout << endl << endl;
	system("pause");
	return 0;
}