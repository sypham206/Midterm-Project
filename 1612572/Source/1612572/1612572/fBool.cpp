#include"fBool.h"

// Xác định độ dài đơn thức
int lenOfMonomial(string str)
{
	int len = 0;
	if (str.find('x') != -1) len++;
	if (str.find('y') != -1) len++;
	if (str.find('z') != -1) len++;
	if (str.find('t') != -1) len++;
	return len;
}

// Tìm các đơn thức có trong hàm bool
void findMonomial(string str, string arrMonomial[MAX], int& len)
{
	int pos = 0;
	while (pos < str.length())
	{
		int p = 0;
		int posTail = pos;
		while (str[posTail + 1] != ' ' && str[posTail + 1] != '+' && posTail < str.length() - 1) posTail++;
		string temp = "";
		for (int i = pos; i <= posTail; i++) temp += str[i];
		arrMonomial[len] = temp;
		len++;
		pos = posTail + 1;
		while (str[pos] == ' ' || str[pos] == '+') pos++;
	}
}

// Đánh dấu các ô trong biểu đồ Karnaugh với một đơn thức nhập vào. Dùng để bổ trợ cho hàm tickWithBool()
void tickWithMonomial(int Kar[4][4], string tmp)
{
	// Tách ra các từ đơn
	string arrMonomial[4]; // Mảng lưu các từ đơn, mỗi đơn thức có đối đa 4 từ đơn (x/-x, y/-y, z/-z, t/-t)
	int len = 0;
	int pos = 0;
	while (pos < tmp.length())
	{
		int p = 0;
		int posTail = pos;
		while (tmp[posTail] == '-' && posTail < tmp.length() - 1) posTail++;
		string temp = "";
		for (int i = pos; i <= posTail; i++) temp += tmp[i];
		arrMonomial[len] = temp;
		len++;
		pos = posTail + 1;
	}
	// Tạo biểu đồ tạm để đánh dấu
	int tmpKar[4][4] = { 0 };
	// Với mỗi từ đơn thực hiện đánh dấu
	for (int i = 0; i < len; i++) {
		if (arrMonomial[i] == "x") { // Đánh dấu các ô thuộc cột 1 và 2, ứng với j = 0, j = 1
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 2; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "-x") { // Đánh dấu các ô thuộc cột 3 và 4, ứng với j = 2, j = 3
			for (int i = 0; i < 4; i++)
				for (int j = 2; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "y") { // Đánh dấu các ô thuộc cột 2 và 3, ứng với j = 1, j = 2
			for (int i = 0; i < 4; i++)
				for (int j = 1; j < 3; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "-y") { // Đánh dấu các ô thuộc cột 1 và 4, ứng với j = 0, j = 3
			for (int i = 0; i < 4; i++) {
				tmpKar[i][0]++;
				tmpKar[i][3]++;
			}
		}
		if (arrMonomial[i] == "z") { // Đánh dấu các ô thuộc dòng 1 và 2, ứng với i = 0, i = 1
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "-z") { // Đánh dấu các ô thuộc dòng 3 và 4, ứng với i = 2, i = 3
			for (int i = 2; i < 4; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "t") { // Đánh dấu các ô thuộc dòng 2 và 3, ứng với i = 1, i = 2
			for (int i = 1; i < 3; i++)
				for (int j = 0; j < 4; j++)
					tmpKar[i][j]++;
		}
		if (arrMonomial[i] == "-t") { // Đánh dấu các ô thuộc dòng 1 và 4, ứng với i = 0, i = 3
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

// Đánh dấu các ô trong biểu đồ Karnaugh với một hàm Bool nhập vào
void tickWithBool(int Kar[4][4], string str)
{
	// Tìm các đơn thức của hàm Bool
	string arrMonomial[MAX];
	int len = 0;
	findMonomial(str, arrMonomial, len);
	for (int i = 0; i < len; i++)
		tickWithMonomial(Kar, arrMonomial[i]);
}

// Xác định một đơn thức/ đa thức có thuộc đơn thức/ đa thức khác hay không
int isChild(string child, string parent)
{
	int result = 1;
	// Khởi tạo và đánh dấu đơn thức/ đa thức con
	int childKar[4][4] = { 0 };
	tickWithBool(childKar, child);
	// Khởi tạo và đánh dấu đơn thức/ đa thức cha
	int parentKar[4][4] = { 0 };
	tickWithBool(parentKar, parent);
	// Kiểm tra xem các ô của con tương ứng có đánh dấu trong cha không
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (childKar[i][j] == 1 && parentKar[i][j] == 0) result = 0;
	return result;
}

// In ra biểu đồ Karnaugh
void showKar(int Kar[4][4])
{
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << endl;
		for (int j = 0; j < 4; j++)
			//cout << Karnaugh[i][j] << "  ";
			if (Kar[i][j]) cout << "  Q";
			else cout << "  .";
	}
}

// Tìm tất cả các tế bào (có tất cả 80 tế bào với trường hợp biểu đồ Karnaugh n = 4)
void printAllCell()
{
	string listCell[MAX];
	int lenCell = 0;
	for (int i = 7777; i < 9999; i++) // Trường hợp 9999 tức là không có cả x,y,z,y, ta không lấy trường hợp này
	{
		// Lấy ra chữ số
		int pX = i / 1000;
		int pY = (i - pX * 1000) / 100;
		int pZ = (i - pX * 1000 - pY * 100) / 10;
		int pT = (i - pX * 1000 - pY * 100 - pZ * 10);
		// Đưa về tế bào
		string temp = "";
		if (pX == 7) temp += "x";
		if (pX == 8) temp += "-x";
		if (pY == 7) temp += "y";
		if (pY == 8) temp += "-y";
		if (pZ == 7) temp += "z";
		if (pZ == 8) temp += "-z";
		if (pT == 7) temp += "t";
		if (pT == 8) temp += "-t";
		// Nếu không tồn tại chữ số khác 7,8,9 thì đó là 1 tế bào hợp lệ
		if (pX > 6 && pY > 6 && pZ > 6 && pT > 6)
		{
			listCell[lenCell] = temp;
			lenCell++;
		}
	}
	for (int i = 0; i < lenCell; i++)
	{
		cout << "\n Cell [" << i + 1 << "]: " << listCell[i];
	}
}

// Tìm các công thức đa thức tối tiểu của hàm Bool
void findMinimalPolynomial(string str)
{
	// Xác định các tế bào: có x/ có -x/ không có lần lượt là 7/8/9, tương tự với y,z,t. Ví dụ: xyzt là 7777, x-yzt là 7877, yt là 9797
	string listCell[MAX];
	int lenCell = 0;
	for (int i = 7777; i < 9999; i++) // Trường hợp 9999 tức là không có cả x,y,z,y, ta không lấy trường hợp này
	{
		// Lấy ra chữ số
		int pX = i / 1000;
		int pY = (i - pX * 1000) / 100;
		int pZ = (i - pX * 1000 - pY * 100) / 10;
		int pT = (i - pX * 1000 - pY * 100 - pZ * 10);
		// Đưa về tế bào
		string temp = "";
		if (pX == 7) temp += "x";
		if (pX == 8) temp += "-x";
		if (pY == 7) temp += "y";
		if (pY == 8) temp += "-y";
		if (pZ == 7) temp += "z";
		if (pZ == 8) temp += "-z";
		if (pT == 7) temp += "t";
		if (pT == 8) temp += "-t";
		// Nếu không tồn tại chữ số khác 7,8,9 thì đó là 1 tế bào hợp lệ
		if (pX > 6 && pY > 6 && pZ > 6 && pT > 6)
		{
			listCell[lenCell] = temp;
			lenCell++;
		}
	}

	// Xác định các tế bào của hàm Bool. Duyệt tất cả 80 tế bào, nếu tìm thấy tế bào là của hàm Bool thì lưu vào listCellofBool
	string listCellofBool[MAX];
	int len = 0;
	for (int i = 0; i < lenCell; i++)
		if (isChild(listCell[i], str))
		{
			listCellofBool[len] = listCell[i];
			len++;
		}

	// Xác định các tế bào lớn. Duyệt tất cả tế bào của hàm Bool, loại các tế bào nhỏ (thuộc tế bào lớn khác)
	string listBigCell[MAX];
	int lenOfBigCell = 0;
	for (int i = 0; i < len; i++)
	{
		int isBig = 1;
		for (int j = 0; j < len; j++)
			if (i != j && isChild(listCellofBool[i], listCellofBool[j]))
				isBig = 0;
		if (isBig == 1)
		{
			listBigCell[lenOfBigCell] = listCellofBool[i];
			lenOfBigCell++;
		}
	}

	// Xác định các ô của hàm Bool
	string listMinCell[MAX];
	int lenOfMinCell = 0;
	for (int i = 0; i < len; i++)
	{
		string tmp = listCellofBool[i]; // Lưu tế bào hiện tại
		if (tmp.find('x') != -1 && tmp.find('y') != -1 && tmp.find('z') != -1 && tmp.find('t') != -1)
		{
			listMinCell[lenOfMinCell] = tmp;
			lenOfMinCell++;
		}
	}

	// Xác định tế bào lớn nhất thiết phải chọn
	string listMainBigCell[MAX];
	int lenOfMainBigCell = 0;
	for (int i = 0; i < lenOfMinCell; i++)
	{
		int lenParent = 0;
		string itsParent;
		for (int j = 0; j < lenOfBigCell; j++)
			if (isChild(listMinCell[i], listBigCell[j]))
			{
				lenParent++;
				itsParent = listBigCell[j];
			}
		if (lenParent == 1) // Chỉ có 1 tế bào cha
		{
			// Kiểm tra xem tế bào cha này đã có trong mảng các tế bào nhất thiết phải chọn chưa
			int isAvailable = 0;
			for (int l = 0; l < lenOfMainBigCell; l++)
				if (listMainBigCell[l] == itsParent)
					isAvailable = 1;
			// Nếu chưa có trong mảng thì thêm vào
			if (isAvailable == 0)
			{
				listMainBigCell[lenOfMainBigCell] = itsParent;
				lenOfMainBigCell++;
			}
		}
	}

	// Lấy các tế bào lớn nhất thiết phải chọn này, tạm thời lưu thành kết quả	
	string tmpResult = listMainBigCell[0];
	for (int i = 1; i < lenOfMainBigCell; i++)
		tmpResult = tmpResult + " + " + listMainBigCell[i];

	// Tìm các đa thức tối tiểu lưu vào mảng arrRes. Kết quả đầu lưu vào mảng là kết quả tạm tmpResult
	string arrRes[MAX];
	int lenRes = 1;
	arrRes[0] = tmpResult;
	// Tìm các ô chưa được phủ
	for (int i = 0; i < lenOfMinCell; i++)
		for (int iR = 0; iR < lenRes; iR++)
		{
			// Kiểm tra nếu ô này chưa bị kết quả iR phủ
			if (isChild(listMinCell[i], arrRes[iR]) == 0)
			{
				// Tìm các tế bào lớn chứa ô này
				string itsParent[MAX];
				int lenParent = 0;
				for (int j = 0; j < lenOfBigCell; j++)
					if (isChild(listMinCell[i], listBigCell[j]))
					{
						itsParent[lenParent] = listBigCell[j];
						lenParent++;
					}
				// Số tế bào lớn chứ ô này chính là số cách phủ tiếp
				string preRes = arrRes[iR]; // lưu lại kết quả iR, từ đây sẽ tạo ra "lenParent" kết quả mới
				arrRes[iR] = preRes + " + " + itsParent[0]; // Vị trí iR thay bằng kết quả mới
				for (int iP = 1; iP < lenParent; iP++)
				{
					// Với mỗi tế bào lớn khác tạo thêm 1 kết quả nữa cho arrRes
					arrRes[lenRes] = preRes + " + " + itsParent[iP];
					lenRes++;
				}
			}
		}
	
	// Làm sạch kết quả (sắp xếp lại các đơn thức) với từng kết quả trong arrRes
	for (int iR = 0; iR < lenRes; iR++)
	{
		// B1: Tìm các đơn thức
		string arrM[MAX];
		int lenM = 0;
		findMonomial(arrRes[iR], arrM, lenM);
		// B2: Sắp xếp lại thứ tự đơn thức
		for (int i = 0; i < lenM; i++)
		{
			int min = i;
			for (int j = i + 1; j < lenM; j++)
				if (lenOfMonomial(arrM[j]) < lenOfMonomial(arrM[min]))
					min = j;
			if (i != min)
			{
				string tmpM = arrM[i];
				arrM[i] = arrM[min];
				arrM[min] = tmpM;
			}
		}
		// B3: Trả về kết quả
		string Result = arrM[0];
		for (int i = 1; i < lenM; i++)
			Result = Result + " + " + arrM[i];

		cout << endl << " CT " << iR + 1 << ": " << Result;
	}
}