#include"fVector.h"

/* Hàm tạo Vector 0
Tham số truyền vào: Vector A
Hàm set các giá trị 0 cho Vector A*/
void setVector(Vector& A)
{
	A.degree = MAX_DEGREE;
	for (int i = 0; i < A.degree; i++)
		A.value[i] = 0;
}

/* Hàm chuyển đổi số nguyên kiểu string về kiểu int */
int stringToInt(string str)
{
	int result = 0;
	if (str[0] == '-')
	{
		int tmp = 0;
		for (int i = 1; i < str.length(); i++)
		{
			tmp = tmp * 10 + int(str[i]) - '0';
		}
		result = 0 - tmp;
	}
	else
		for (int i = 0; i < str.length(); i++)
		{
			result = result * 10 + int(str[i]) - '0';
		}
	return result;
}

/* Hàm chuyển đổi số thực dương kiểu string về kiểu float */
float stFloat (string str)
{
	float result = 0;
	// Xác định vị trí dấu chấm
	int pos = str.find('.');
	if (pos != -1)
	{
		// Tính phần nguyên
		for (int i = 0; i < pos; i++)
		{
			result = result * 10 + int(str[i]) - '0';
		}
		// Tính phần thực
		int k = 10;
		for (int i = pos + 1; i < str.length(); i++)
		{
			float temp = 1.0 * (int(str[i]) - '0');
			result = result + temp / k;
			k *= 10;
		}
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			result = result * 10 + int(str[i]) - '0';
		}
	}	
	return result;
}

/* Hàm chuyển đổi số thực kiểu string về kiểu float */
float stringToFloat(string str)
{
	float result = 0;
	if (str == "0") return result;
	if (str[0] == '-')
	{
		string abs = "";
		for (int iS = 1; iS < str.length(); iS++)
			abs += str[iS];
		result = stFloat(abs);
		result = 0 - result;
	}
	else result = stFloat(str);
	return result;
}

/* Hàm lấy ra các giá trị của vector từ biểu diễn vector dạng chuỗi */
void findValue(string str, string arrValue[MAX_VALUE], int& len)
{
	int pos = 0;
	// Mảng ban đầu chưa có phần tử, len = 0
	len = 0;
	while (pos < str.length())
	{
		int p = 0;
		int posTail = pos;
		while (str[posTail + 1] != ' ' && posTail < str.length() - 1) posTail++;
		string temp = "";
		for (int i = pos; i <= posTail; i++) temp += str[i];
		arrValue[len] = temp;
		len++;
		pos = posTail + 1;
		while (str[pos] == ' ') pos++;
	}
}

/* Hàm in ra vector
Tham số truyền vào: vector a
Hàm in ra màn hình giá trị vector a */
void printVector(Vector a)
{
	cout << " (";
	for (int i = 0; i < a.degree; i++)
	{
		if (i > 0) cout << ", ";
		cout << a.value[i];
	}
	cout << ")";
}

/* Hàm cộng 2 vector */
Vector plusVector(Vector a, Vector b)
{
	// Tạo vector kết quả trả về, khởi tạo giá trị ban đầu là vector 0
	Vector result;
	result.degree = a.degree;
	for (int i = 0; i < MAX_DEGREE; i++)
		result.value[i] = 0;
	
	// Kiểm tra 2 vector có cùng bậc không
	if (a.degree == b.degree)
	{
		int degree = a.degree;
		for (int i = 0; i < degree; i++)
			result.value[i] = a.value[i] + b.value[i];
	}
	return result;
}

/* Hàm nhân vector với một số alpha */
Vector mulVector(Vector a, float alpha)
{
	// Tạo vector kết quả trả về, khởi tạo giá trị ban đầu là vector 0
	Vector result;
	result.degree = a.degree;
	for (int i = 0; i < MAX_DEGREE; i++)
		result.value[i] = 0;

	// Nhân vector
	for (int i = 0; i < a.degree; i++)
		result.value[i] = alpha * a.value[i];
	return result;
}