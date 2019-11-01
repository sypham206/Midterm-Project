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
				cout << "\t";
				if (pMatrix.a[i][j] >= 0) cout << " ";
				cout << pMatrix.a[i][j];
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