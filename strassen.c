#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Matrix
{
	int rows , columns;
	int **matrix;
}Matrix;

void InitMatrix(Matrix *m , int r , int c , int ini);
void Strassen(Matrix *A, Matrix *B);
Matrix AddMatrix(Matrix *a,Matrix *b);
Matrix SubtractMatrix(Matrix *a, Matrix *b);
void PrintMatrix(Matrix *m);
void CopyMatrix(Matrix *a, Matrix *b,int lb,int rb,int db,int ub);
void AcceptMatrix(Matrix *m);
void main()
{
	Matrix A,B;
	int r1,r2,c1,c2;
	printf("Give number of rows and columns of first matrix : ");
	scanf("%d%d",&r1,&c1);
	printf("Give number of rows and columns of second matrix : ");
	scanf("%d%d",&r2,&c2);
	InitMatrix(&A,r1,c1,0);
	InitMatrix(&B,r2,c2,0);
	printf("Give Matrix A : ");
	AcceptMatrix(&A);
	printf("Give matrix B : ");
	AcceptMatrix(&B);
	printf("\nMatrix A : ");
	PrintMatrix(&A);
	printf("\nMatrix B : ");
	PrintMatrix(&B);
	if(c1!=r2)
	{
		printf("Can't multiply matrices.");
		return;
	}
	
	Strassen(&A,&B);
	printf("\n");
}

void InitMatrix(Matrix *m , int r , int c , int ini)
{
	int i , j;
	m->rows = r;
	m->columns = c;
	m->matrix=(int**)malloc(sizeof(int*)*r);
	for( i = 0 ; i < r ; i++)
	{
		m->matrix[i] = (int*)malloc(sizeof(int));
		for(j = 0 ; j < c ; j++)
			m->matrix[i][j] = ini;
	}
}

void Strassen(Matrix *A, Matrix *B)
{
	Matrix a,b,c,d,e,f,g,h;
	int firstRowDiv,firstColDiv,secondRowDiv,secondColDiv;
	
	firstRowDiv = A->rows/2;
	firstColDiv = A->columns/2;
	secondRowDiv = B->rows/2;
	secondColDiv = B->columns/2;
	
	InitMatrix(&a,            firstRowDiv,               firstColDiv, 0);
	InitMatrix(&b,            firstRowDiv,    A->columns-firstColDiv, 0);
	InitMatrix(&c,    A->rows-firstRowDiv,               firstColDiv, 0);
	InitMatrix(&d,	A->rows-firstRowDiv,	A->columns-firstColDiv,	0);
	InitMatrix(&e,           secondRowDiv,              secondColDiv, 0);
	InitMatrix(&f,           secondRowDiv,   B->columns-secondColDiv, 0);
	InitMatrix(&g,   B->rows-secondRowDiv,              secondColDiv, 0);
	InitMatrix(&h,   B->rows-secondRowDiv,   B->columns-secondColDiv,	0);
	
	CopyMatrix(A,&a,             1, firstRowDiv,             1,  firstColDiv);
	CopyMatrix(A,&b,             1, firstRowDiv, firstColDiv+1,   A->columns);
	CopyMatrix(A,&c, firstRowDiv+1,     A->rows,             1,  firstColDiv);
	CopyMatrix(A,&d, firstRowDiv+1,     A->rows, firstColDiv+1,   A->columns);
	CopyMatrix(B,&e,             1,secondRowDiv,             1, secondColDiv);
	CopyMatrix(B,&f,             1,secondRowDiv,secondColDiv+1,   B->columns);
	CopyMatrix(B,&g,secondRowDiv+1,     B->rows,             1, secondColDiv);
	CopyMatrix(B,&h,secondRowDiv+1,     B->rows,secondColDiv+1,   B->columns);
	
	PrintMatrix(&a);
	PrintMatrix(&b);
	PrintMatrix(&c);
	PrintMatrix(&d);
	PrintMatrix(&e);
	PrintMatrix(&f);
	PrintMatrix(&g);
	PrintMatrix(&h);
}

Matrix AddMatrix(Matrix *a,Matrix *b)
{
	int row,column;
	Matrix c;
	InitMatrix(&c,a->rows,a->columns,0);
	for(row=0;row<a->rows;row++)
		for(column=0;column<a->columns;column++)
			c.matrix[row][column] = a->matrix[row][column] + b->matrix[row][column];
	return c;
}

Matrix SubtractMatrix(Matrix *a, Matrix *b)
{
	int row,column;
	Matrix c;
	InitMatrix(&c,a->rows,a->columns,0);
	for(row=0;row<a->rows;row++)
		for(column=0;column<a->columns;column++)
			c.matrix[row][column] = a->matrix[row][column] - b->matrix[row][column];
	return c;
}

void PrintMatrix(Matrix *m)
{
	int i,j;
	printf("\n");
	for(i=0;i<m->rows;i++)
	{
		printf("\n");
		for(j=0;j<m->columns;j++)
			printf("%10d",m->matrix[i][j]);
	}
}

void CopyMatrix(Matrix *a, Matrix *b,int lb,int rb,int db,int ub)
{
	lb--;
	rb--;
	db--;
	ub--;
	int i,j;
	for(i=lb;i<=rb;i++)
		for(j=ub;j<=db;j++)
			b->matrix[i-lb][j-ub] = a->matrix[i][j];
	
}	
