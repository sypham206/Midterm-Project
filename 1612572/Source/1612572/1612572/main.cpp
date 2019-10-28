/*
Hàm bool 3-4 biến: x,y,z,t
Phép toán hợp kí hiệu là: '+'
Phần tử bù của x là -x
Cần viết 1 hàm làm sạch hàm Bool đầu vào, có thể sửa lại hàm hoặc xuất ra thông báo input không hợp lệ
*/
#include<iostream>
using namespace std;
#define MAX 100

// Đánh dấu các ô với một đơn thức nhập vào
void tick(int Kar[4][4], string tmp)
{
	// Tách ra các từ đơn
	string arr[4];
	int len = 0;
	int pos = 0;
	while (pos < tmp.length())
	{
		int p = 0;
		int posTail = pos;
		while (tmp[posTail] == '-' && posTail < tmp.length() - 1) posTail++;
		string temp = "";
		for (int i = pos; i <= posTail; i++) temp += tmp[i];
		arr[len] = temp;
		len++;
		pos = posTail + 1;
	}
	// Tạo biểu đồ tạm để đánh dấu
	int tmpKar[4][4] = { 0 };
	// Với mỗi từ đơn thực hiện đánh dấu
	for (int i = 0; i < len; i++) {		
		if (arr[i] == "x") { // Đánh dấu các ô thuộc cột 1 và 2, ứng với j = 0, j = 1
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 2; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "-x") { // Đánh dấu các ô thuộc cột 3 và 4, ứng với j = 2, j = 3
			for (int i = 0; i < 4; i++)
				for (int j = 2; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "y") { // Đánh dấu các ô thuộc cột 2 và 3, ứng với j = 1, j = 2
			for (int i = 0; i < 4; i++)
				for (int j = 1; j < 3; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "-y") { // Đánh dấu các ô thuộc cột 1 và 4, ứng với j = 0, j = 3
			for (int i = 0; i < 4; i++){
				tmpKar[i][0]++;
				tmpKar[i][3]++;
			}
		}
		if (arr[i] == "z") { // Đánh dấu các ô thuộc dòng 1 và 2, ứng với i = 0, i = 1
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "-z") { // Đánh dấu các ô thuộc dòng 3 và 4, ứng với i = 2, i = 3
			for (int i = 2; i < 4; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "t") { // Đánh dấu các ô thuộc dòng 2 và 3, ứng với i = 1, i = 2
			for (int i = 1; i < 3; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arr[i] == "-t") { // Đánh dấu các ô thuộc dòng 1 và 4, ứng với i = 0, i = 3
			for (int j = 0; j < 4; j++)
				tmpKar[0][j]++;
			for (int j = 0; j < 4; j++)
				tmpKar[3][j]++;
		}
		// Các ô được đánh dấu "len" lần là những ô thỏa mãn, đánh dấu những ô này vào biểu đồ Kar
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (tmpKar[i][j] == len)
					Kar[i][j] = 1;
	}
}
int main()
{
	// Tạo giá trị hàm bool
	string str = "xyzt + x-y + x-z + yz + xy-z + xy-t";
	// Xác định các đơn thức
	string arr[MAX];
	int len = 0;
	int pos = 0;
	while (pos<str.length())
	{
		int p = 0;
		int posTail = pos;
		while (str[posTail + 1] != ' ' && str[posTail + 1] != '+' && posTail < str.length() - 1) posTail++;
		string temp = "";
		for (int i = pos; i <= posTail; i++) temp += str[i];
		arr[len] = temp;
		len++;
		pos = posTail + 1;
		while (str[pos] == ' ' || str[pos] == '+') pos++;
	}
	for (int i = 0; i < len; i++)
		cout << endl << "arr[" << i << "]= " << arr[i];
	// Biểu đồ Karnaugh
	int Karnaugh[4][4] = {0};
	// Đánh dấu biểu đồ Karnaugh
	for (int i = 0; i < len; i++)
		tick(Karnaugh, arr[i]);
	// Biểu diễn biểu đồ Karnaugh
	for (int i = 0; i < 4; i++)
	{
		cout << endl;
		for (int j = 0; j < 4; j++)
			//cout << Karnaugh[i][j] << "  ";
			if (Karnaugh[i][j]) cout << "  X";
			else cout << "  _";
	}

	/*
	
	*/
	

	cout << endl;
	system("pause");
	return 0;
}