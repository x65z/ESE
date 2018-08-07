//Zack H Matrix Multiplication
void  MultiplyAx(float *A, int	n, int	m, float *x, float *y)// A - Matrix, n - Num rows, m - num columns in A, x - m by 1 vector input, n by 1 vector input
{
	int r, c;
	float *tempx;
	float fTotal;

	for (r = 0; r < n; r++)//Going through rows
	{
		tempx = x;
		fTotal = 0.0;
		for(c = 0; c < m; c++)//Going through columns
		{
			fTotal += (*A) * (*tempx);
			A++;
			tempx++;
		}
		y[r] = fTotal;//Save Total for current Row
	}
	
}