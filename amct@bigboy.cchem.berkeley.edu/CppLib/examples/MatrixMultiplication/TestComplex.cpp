/*
Name: TestComplex.cpp
Author: Jay Gambetta

Dependences: Matrix.hpp  
Brief Discription: Benchmarks the Blas, my blas wrapper and simple matrix multiplication for Complex matrices.
Limitations: None


Version History
	v0: Januarary 3rd, 2009.
	
run in terminal
	i="0"; while [ $i -lt 12 ]; do i=$[$i+1]; echo $i; ./TestComplex.e $i true TestComplex.dat; done
	

*/
#include "Matrix.hpp"
using namespace std;

inline int SimpleMatrixMult(const matrix<complex<double> >& a, const matrix<complex<double> >& b, matrix<complex<double> >& c){
	unsigned int rows_a= a.GetRows(), cols_a = a.GetColumns(), cols_b = b.GetColumns();
	
	for (unsigned int i=0; i < rows_a; i++){
		for(unsigned int j=0; j < cols_b; j++){
			c(i,j) = 0;
			for (unsigned int p = 0; p< cols_a; p++){
				c(i,j) += a(i,p)*b(p,j);
			}
		}
	}
	return 0;
}

int main (int argc, char const *argv[])
{
	
	cout << "Running program " << argv[0] << endl;
	//cout << CLOCKS_PER_SEC << endl;
	double to_ms =1000.0/CLOCKS_PER_SEC;
	size_t rows=int(pow(2.0,atof(argv[1])));
	string const outfile = argv[3];
	ofstream dataout;
	UFs::AppendFile(outfile,dataout, 16);
	
	/* initialize random seed: */
	srand ( time(NULL) );
	
	matrix<complex<double> > A(rows,rows), B(rows,rows), C1(rows,rows), C2(rows,rows), C3(rows,rows);
	for(size_t i=0; i<rows; i++){
		for(size_t j=0; j<rows; j++){
			A(i,j)=complex<double>(double(rand() % 1000)/double(1000),double(rand() % 1000)/double(1000));
			B(i,j)=double(rand() % 1000)/double( 1000);
		}
	}
	
	dataout << argv[1];
	int clo = clock();
	complex<double> alpha =1.0, beta =0.0;
	size_t LDA = rows;
	size_t LDB = rows;
	size_t LDC = rows;
	zgemm_(&Trans[0], &Trans[0], &rows, &rows, &rows, &alpha, A.GetMat(), &LDA, B.GetMat(), &LDB, &beta, C1.GetMat(), &LDC);
	//cblas_zgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, rows, rows, rows, &alpha, A.GetMat(), LDA, B.GetMat(), LDB, &beta, C1.GetMat(), LDC);
	dataout << '\t' << to_ms*(clock() - clo);
	if(argv[2]=="print")
		cout << C1 << endl;
	
	clo = clock();
	C2=A*B;
	dataout << '\t' << to_ms*(clock() - clo);
	if(argv[2]=="print")
		cout << C2 << endl;
	
	clo = clock();
	if(atof(argv[1]) <=10){
		 SimpleMatrixMult(A,B,C3);
	}
	dataout << '\t' << to_ms*(clock() - clo) << endl;
	if(argv[2]=="print")
		cout << C2 << endl;
		
	return 0;
}
