#include <stdio.h>
#include <stdlib.h>
#include <math.h>



double multiply(double **matrix1, double **matrix2, double **temp, int row1, int col1, int row2, int col2)
{
	int i;
	int j;
	int k;
	if (col1 != row2)
		return EXIT_FAILURE;
	//int sum;
/*	double **temp;
	temp = (double**)malloc(size*sizeof(double*));
	for(i = 0; i < row1; i++)	//makes it 2d
		temp[i] = (double*)malloc(size*sizeof(double));
*/	

	//set temp to 0 completely
/*	for (i = 0; i < row1; i++)
	{
		for (j = 0; j < col2; j++)
			temp[i][j] = 0;
	}*/

	for (i = 0; i < row1; i++)
	{
		for(j = 0; j < col2; j++)
		{
			temp[i][j] = 0;
			for(k = 0; k < row2; k++)
				temp[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	}
/*	for (i = 0; i < row1; i++)
	{
		for (j = 0; j < col2; j++)
			matrix1[i][j] = temp[i][j];
	}
	//free temp
	for(i = 0; i < size; i++)
		free(temp[i]);
	free(temp);
	return **matrix1;*/
	return **temp;
	//return result;
}

//transpose function
double transpose(double **matrix, double **temp, int row, int col)
{
	int i;
	int j;
/*	double **temp;
	temp = (double**)malloc(size*sizeof(double*));
	for(i = 0; i < row; i++)	//makes it 2d
		temp[i] = (double*)malloc(size*sizeof(double));
*/	
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
			temp[i][j] = matrix[j][i];
	}

	return **temp;
}

//inverse function(gauss jordan elimination)
double inverse(double **M, double **N, int n)
{
	int i;
	int j;
	int k;
	//make identity matrix
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
				N[i][j] = 1;
			else
				N[i][j] = 0;
		}
	}

	int p;
	double f;
	//int l;
	//double **N = **temp;
	for (p = 0; p < n; p++)
	{
		f = M[p][p];
			//printf("%f\n", f);
		for (k = 0; k < n; k++) //divide Mp by f
			M[p][k] = M[p][k]/f;
		for (k = 0; k < n; k++)	//divide Np by f
			N[p][k] = N[p][k]/f;

		for (i = p+1; i < n; i++)
		{
			f = M[i][p];
			for (k = p; k < n; k++)	//substract Mp*f from Mi
				M[i][k] = M[i][k] - (M[p][k] * f);
			for (k = 0; k < n; k++)	//subtract Np*f from Ni
				N[i][k] = N[i][k] - (N[p][k] * f);
		}

	}

	for (p = n - 1; p >= 0; p--)
	{
		for (i = p - 1; i >= 0; i--)
		{
			f = M[i][p];
			for (k = p; k < n; k++)
				M[i][k] = M[i][k] - (M[p][k] * f);
			for (k = 0; k < n; k++)
				N[i][k] = N[i][k] - (N[p][k] * f);
		}
	}
	

	return **N;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	//int k;
	FILE *train;
	train = fopen(argv[1], "r");
	char filename[6];
	fscanf(train, "%5s", filename);
	fscanf(train,"\n");
	//have to fill X and Y matrices- last num in each row is price
	int col1;
	fscanf(train, "%d\n", &col1);
	col1++;
	//printf("%d ", col1); //test
	int row1;
	fscanf(train, "%d\n", &row1);
	//printf("%d\n", row1); //test

	int i;
	int j;
	//int k;
	double num;

	double **X = (double**)malloc(row1*sizeof(double*)); //matrix X
	for(i = 0; i < row1; i++)
		X[i] = (double*)malloc(col1*sizeof(double));

	double **Y = (double**)malloc(row1*sizeof(double*)); //matrix Y
	for(i = 0; i < row1; i++)
		Y[i] = (double*)malloc(1*sizeof(double));

	//make first column 1s
	for (i = 0; i < row1; i++)
		X[i][0] = 1.000000;

	for (i = 0; i < row1; i++)
	{	
		for(j = 1; j < col1+1; j++)
		{
			fscanf(train,"%lf ",&num);
			if (j == col1)
			{
				Y[i][0] = num;
				//printf("%lf ", Y[i][0]); //test
			}
			else
			{
				X[i][j] = num;
				//printf("%lf ", X[i][j]); //test
			}
		}
		fscanf(train,"\n");
		
	}

	fclose(train);

	//do the equation to get W
	//fclose(trainData);??
	//read and fill data matrix (new X for final equation to find Y)
	FILE *data;
	data = fopen(argv[2], "r");
	char filename2[6];
	fscanf(data, "%5s", filename2);
	fscanf(data,"\n");

	int col2;
	fscanf(data, "%d\n", &col2);
	col2++;
	//printf("%d ", col2);
	int row2;
	fscanf(data, "%d\n", &row2);
	//printf("%d ", row2);
	double num2;

	double **X2 = (double**)malloc(row2*sizeof(double*)); //matrix X
	for(i = 0; i < row2; i++)
		X2[i] = (double*)malloc(col2*sizeof(double));

	for (i = 0; i < row2; i++)
		X2[i][0] = 1;
	for (i = 0; i < row2; i++)
	{	
		for(j = 1; j < col2; j++)
		{
			fscanf(data,"%lf ",&num2);
			X2[i][j] = num2;
			//printf("%lf ", X2[i][j]); //test
		}
		fscanf(data,"\n");
		
	}
	fclose(data);


	//ALLOCATED MATRICES
	//allocated X^T (col * row)
	double **transposeMtx = (double**)malloc(col1*sizeof(double)); //for X^T
	for (i = 0; i < col1; i++)
		transposeMtx[i] = (double*)malloc(row1*sizeof(double));

	**transposeMtx = transpose(X, transposeMtx, row1, col1);
	//transpose(X, transposeMtx, row1, col1);

	//allocated X^T * X (col x col)
	double **XTX = (double**)malloc(col1*sizeof(double));
	for (i = 0; i < col1; i++)
		XTX[i] = (double*)malloc(col1*sizeof(double));

	**XTX = multiply(transposeMtx, X, XTX, col1, row1, row1, col1);
	//multiply(transposeMtx, X, XTX, col1, row1, row1, col1);

	//dont need to allocate again for inverse
	//(XTX)^-1 (col x col)
	//allocate identity matrix
	double **inverseMtx = (double**)malloc(col1*sizeof(double));
	for (i = 0; i < col1; i++)
		inverseMtx[i] = (double*)malloc(col1*sizeof(double));

	**inverseMtx = inverse(XTX, inverseMtx, col1);
	//inverse(XTX, inverseMtx, col1);

	//(XTX)^-1 * XT (col x row)
	double **inverse2 = (double**)malloc(col1*sizeof(double));
	for (i = 0; i < col1; i++)
		inverse2[i] = (double*)malloc(row1*sizeof(double));

	**inverse2 = multiply(inverseMtx, transposeMtx, inverse2, col1, col1, col1, row1);
	//multiply(inverseMtx, transposeMtx, inverse2, col1, col1, col1, row1);

	//allocated W(col x 1)
	double **W = (double**)malloc(col1*sizeof(double));
	for (i = 0; i < col1; i++)
		W[i] = (double*)malloc(1*sizeof(double));

	//(XTX)^-1 * XT * Y (col x 1)
	**W = multiply(inverse2, Y, W, col1, row1, row1, 1);
	//multiply(inverse2, Y, W, col1, row1, row1, 1);


	//Find Y'
	//X'*W (row2 x 1)
	double **result = (double**)malloc(row2*sizeof(double));
	for (i = 0; i < row2; i++)
		result[i] = (double*)malloc(1*sizeof(double));

	**result = multiply(X2, W, result, row2, col2, col1, 1);
	//multiply(X2, W, result, row2, col2, col1, 1);

	//PRINT RESULT
	for (i = 0; i < row2; i++)
	{
		for (j = 0; j < 1; j++)
		{
			//double price = result[i][j];
			printf("%.0f\n", result[i][j]);
		}
	}

	//Free X, Y, X2, transpose, XTX, W, result, inverseMtx
	for(i = 0; i < row1; i++)
		free(X[i]);
	free(X);

	for(i = 0; i < row1; i++)
		free(Y[i]);
	free(Y);

	for(i = 0; i < row2; i++)
		free(X2[i]);
	free(X2);

	for(i = 0; i < col1; i++)
		free(transposeMtx[i]);
	free(transposeMtx);

	for(i = 0; i < col1; i++)
		free(XTX[i]);
	free(XTX);

	for(i = 0; i < col1; i++)
		free(W[i]);
	free(W);

	for(i = 0; i < row2; i++)
		free(result[i]);
	free(result);

	for (i = 0; i < col1; i++)
		free(inverseMtx[i]);
	free(inverseMtx);

	for (i = 0; i < col1; i++)
		free(inverse2[i]);
	free(inverse2);

	return 0;
}