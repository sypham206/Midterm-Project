#include"fMatrix.h"

/* Hàm in ra ma trận */
void printMatrix(Matrix pMatrix)
{
	if (pMatrix.N < 1 || pMatrix.M < 1)
		cout << "\n Matrix 0";
	else
	{
		refreshMatrix(pMatrix);
		for (int i = 0; i < pMatrix.N; i++) // Dòng i
		{
			cout << "\n  |";
			for (int j = 0; j < pMatrix.M; j++) // Cột j
			{
				// Làm tròn đến 2 chữ số thập phân
				float value = 0.01 * int(100 * pMatrix.a[i][j]);
				cout << "\t";
				if (value >= 0) cout << " ";
				cout << value;
			}
			cout << "\t|";
		}
	}
}

/* Hàm tạo Ma trận 0 */
void setMatrix(Matrix& pMatrix)
{
	// Các giá trị đều bằng 0
	for (int i = 0; i < MAX_MATRIX; i++) // dòng i
		for (int j = 0; j < MAX_MATRIX; j++) // cột j
			pMatrix.a[i][j] = 0;
	// Cho bậc ma trận bằng 1
	pMatrix.N = 1;
	pMatrix.M = 1;
}

/* Hàm trình bày lại ma trận trong trường hợp hiển thị -0 thay vì 0*/
void refreshMatrix(Matrix& pMatrix)
{
	for (int i = 0; i < pMatrix.N; i++)
		for (int j = 0; j < pMatrix.M; j++)
			if (pMatrix.a[i][j] == 0)
				pMatrix.a[i][j] = 0;
}

/* Hàm tìm định thức ma trận */
float detMatrix(Matrix pMatrix)
{
	float result = 0;

	// Chỉ ma trận vuông mới có định thức
	if (pMatrix.N != pMatrix.M)
	{
		return result;
	}

	// Tìm định thức ma trận vuông
	int N = pMatrix.N;
	if (N <= 1)
	{
		// Nếu ma trận bậc 1 thì kết quả là giá trị duy nhất của ma trận
		if (N == 1) result = pMatrix.a[0][0];
		// Ma trận bậc 0 thì kết quả vẫn là 0
	}
	else
		for (int j = 0; j < N; j++)
		{
			// Xác định dấu của phần phụ đại số A[0][j]
			int alpha = 1;
			if (j % 2 == 1) alpha = -1;
			// Tìm ma trận con để xác định phần phụ đại số A[0][j]
			Matrix tmp;
			tmp.N = N - 1;
			tmp.M = N - 1;
			for(int iT=0;iT<tmp.N;iT++)
				for (int jT = 0; jT < tmp.N; jT++)
				{
					int iOfpMatrix = iT + 1;			// Lưu vị trí dòng cần lấy từ ma trận gốc
					int jOfpMatrix = jT;				// Lưu vị trí cột cần lấy từ ma trận gốc
					if (jOfpMatrix >= j) jOfpMatrix++;	// Những cột kể từ cột j phải dời qua 1 cột
					tmp.a[iT][jT] = pMatrix.a[iOfpMatrix][jOfpMatrix];
				}
			// Quy nạp để tính định thức ma trận gốc
			result += pMatrix.a[0][j] * alpha * detMatrix(tmp);
		}
	return result;
}

Matrix inverseMatrix(Matrix pMatrix)
{
	// Khởi tạo ma trận 0
	Matrix inMatrix;
	setMatrix(inMatrix);

	// Kiểm tra tính khả nghịch của Ma trận pMaxtrix (định thức khác 0)
	if (detMatrix(pMatrix) == 0)
		// Nếu ma trận không khả nghịch thì trả về ma trận 0
		return inMatrix;
	else
	{
		int N = pMatrix.N;
		inMatrix.N = N;
		inMatrix.M = N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				// Xác định dấu của phần phụ đại số A[i][j]
				int alpha = 1;
				if ((i + j) % 2 == 1) alpha = -1;
				// Tìm ma trận con để xác định phần phụ đại số A[i][j]
				Matrix tmp;
				tmp.N = N - 1;
				tmp.M = N - 1;
				for (int iT = 0; iT < tmp.N; iT++)
					for (int jT = 0; jT < tmp.N; jT++)
					{
						int iOfpMatrix = iT;				// Lưu vị trí dòng cần lấy từ ma trận gốc
						int jOfpMatrix = jT;				// Lưu vị trí cột cần lấy từ ma trận gốc
						if (iOfpMatrix >= i) iOfpMatrix++;	// Những cột kể từ cột j phải dời qua 1 cột
						if (jOfpMatrix >= j) jOfpMatrix++;	// Những cột kể từ cột j phải dời qua 1 cột
						tmp.a[iT][jT] = pMatrix.a[iOfpMatrix][jOfpMatrix];
					}
				// Đưa vào ma trận nghịch đảo : P_ji = A_ij * 1/det(A)
				inMatrix.a[j][i] = alpha * detMatrix(tmp) / detMatrix(pMatrix);
			}
	}
	return inMatrix;
}

/* Hàm tính tích 2 ma trận */
Matrix mulMatrix(Matrix x, Matrix y)
{
	// Khởi tạo kết quả là ma trận 0
	Matrix result;
	setMatrix(result);
	if (x.M != y.N)
		// Kiểm tra điều kiện 2 ma trận có thể nhân được không. Trả về ma trận 0 nếu không thể nhân
		return result;
	else
		// Nhân ma trận
	{
		result.N = x.N;
		result.M = y.M;
		for(int i=0;i<x.N;i++)
			for (int j = 0; j < y.M; j++)
			{
				float value = 0;
				for (int index = 0; index < x.M; index++)
					value += x.a[i][index] * y.a[index][j];
				result.a[i][j] = value;
			}
	}
	return result;
}

/* Hàm tạo các ma trận con*/
void createChildMatrix(Matrix t, Matrix listChild[100], int& len)
{
	int N = t.N;
	if (N > 1)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				// Tìm ma trận con để xác định phần phụ đại số A[i][j]
				Matrix tmp;
				tmp.N = N - 1;
				tmp.M = N - 1;
				for (int iT = 0; iT < tmp.N; iT++)
					for (int jT = 0; jT < tmp.N; jT++)
					{
						int iOfpMatrix = iT;				// Lưu vị trí dòng cần lấy từ ma trận gốc
						int jOfpMatrix = jT;				// Lưu vị trí cột cần lấy từ ma trận gốc
						if (iOfpMatrix >= i) iOfpMatrix++;	// Những cột kể từ cột j phải dời qua 1 cột
						if (jOfpMatrix >= j) jOfpMatrix++;	// Những cột kể từ cột j phải dời qua 1 cột
						tmp.a[iT][jT] = t.a[iOfpMatrix][jOfpMatrix];
					}
				// Đưa vào list ma trận
				listChild[len] = tmp;
				len++;
				// Tạo ma trận con của nó (đệ quy)
				//createChildMatrix(listChild[len - 1], listChild, len);
			}
	}

}

/* Hàm tìm hạng của ma trận vuông */
int findRank(Matrix pMatrix)
{
	int rank = 0;
	int isFound = 0;
	float detpMatrix = detMatrix(pMatrix);
	// Nếu định thức ma trận khác không thì hạng chính là cấp của ma trận
	if (detMatrix != 0)
		rank = pMatrix.N;
	else
	{
		rank = pMatrix.N - 1;
		// Tạo mảng chứa ma trận bậc tối đa
		Matrix curMatrix[100];
		int curLen = 0;

		// Đặt giá trị
		curMatrix[0] = pMatrix;
		curLen = 1;

		while (isFound == 0)
		{
			Matrix listChild[100];
			int lenChild = 0;
			for (int i = 0; i < curLen; i++)
				createChildMatrix(curMatrix[i], listChild, lenChild);
			// Đặt những ma trận con này thành ma trận hiện tại
			curLen = lenChild;
			for (int i = 0; i > curLen; i++)
				curMatrix[i] = listChild[i];
			// Kiểm tra xem những ma trận này đã thỏa hạng chưa
			for (int i = 0; i > curLen; i++)
				if (detMatrix(curMatrix[i]) != 0)
				{
					isFound = 1;
				}
			if (isFound == 0) rank--;
		}
	}
	return rank;
}

/* Hàm tìm hạng của ma trận */
int findRankMatrix(Matrix pMatrix)
{
	// Hạng của ma trận không thể lớn hơn số hàng, số cột của ma trận
	int rank = pMatrix.N;
	if (rank > pMatrix.M)
		rank = pMatrix.M;

	// Tạo bản sao ma trận
	Matrix copyMatrix;
	copyMatrix.N = pMatrix.N;
	copyMatrix.M = pMatrix.M;
	for (int i = 0; i < pMatrix.N; i++)
		for (int j = 0; j < pMatrix.M; j++)
			copyMatrix.a[i][j] = pMatrix.a[i][j];

	// Chương trình xử lí khi cột nhiều hơn hàng, nếu hàng nhiều hơn thì xoay ma trận
	if (rank < pMatrix.N)
	{
		pMatrix.N = copyMatrix.M;
		pMatrix.M = copyMatrix.N;
		for (int i = 0; i < pMatrix.N; i++)
			for (int j = 0; j < pMatrix.M; j++)
				pMatrix.a[i][j] = copyMatrix.a[j][i];
	}

	// Ma trận đầu tiên ( "rank" hàng, "rank" cột )
	Matrix tmp;
	tmp.N = rank;
	tmp.M = rank;
	int col[100][10]; // Tối đa 1000 cách chọn ra "rank" cột từ pMatrix.M cột
	int amountCol = 0; // Số lượng cột
	// Ma trận đầu tiên sẽ lấy ra đúng "rank" cột đầu tiên
	for (int i = 0; i < rank; i++)
		col[0][i] = i;
	amountCol++;
	// Tạo ra một cách chọn mới
	int isFull = 0;
	while (isFull == 0)
	{
		// Sao chép cách chọn cuối vào cách chọn mới
		for (int i = 0; i < rank; i++)
			col[amountCol][i] = col[amountCol - 1][i];
		amountCol++;
		// Tìm vị trí xa nhất có thể tăng lên: posUp
		int posUp = rank - 1;
		while (posUp == pMatrix.M - 1 && posUp > 0) posUp--;
		//B1: tăng giá trị ở vị trí posUp lên 1 đơn vị
		col[amountCol - 1][posUp]++;
		//B2: đặt lại các giá trị sau đó bằng 0
		for (int i = posUp + 1; i < rank; i++)
			col[amountCol - 1][i] = 0;
		// Kiểm tra nếu tất cả giá trị đều tối đa thì mảng đã đầy
		int temp = 1;
		for (int i = 0; i < rank; i++)
			if (col[amountCol - 1][i] < pMatrix.M - 1)
				temp = 0;
		if (temp == 1) isFull = 1;
	}
	// Lọc lại mảng
	int selectedCol[100][10];
	int amountSelectedCol = 0; // Số lượng cột
	for (int i = 0; i < amountCol; i++)
	{
		// chỉ chọn ra các cách chọn tăng dần
		int Valid = 1;
		for (int j = 1; j < rank; j++)
			if (col[i][j] <= col[i][j - 1])
				Valid = 0;
		if (Valid == 1)
		{
			//selectedCol[amountSelectedCol] = col[i];
			for (int j = 0; j < rank; j++)
				selectedCol[amountSelectedCol][j] = col[i][j];
			amountSelectedCol++;
		}
	}
	// Với mỗi phần tử trong mảng ta xác định được một ma trận con
	Matrix listMatrix[100];
	int amountMatrix = 0;
	for (int i = 0; i < amountSelectedCol; i++)
	{
		Matrix tmp;
		tmp.N = rank;
		tmp.M = rank;
		for (int iT = 0; iT < rank; iT++)
			for (int jT = 0; jT < rank; jT++)
				tmp.a[iT][jT] = pMatrix.a[iT][selectedCol[i][jT]];
		listMatrix[amountMatrix] = tmp;
		amountMatrix++;
	}

	int result = findRank(listMatrix[0]);
	// Duyệt tất cả ma trận con
	for (int i = 1; i < amountMatrix; i++)
	{
		int tmpRes = findRank(listMatrix[i]);
		if (result < tmpRes)
			result = tmpRes;
	}
	return result;
}

