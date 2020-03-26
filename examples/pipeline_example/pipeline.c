//#include <stdio.h>
int loop(){
	const int A_NROWS=3, A_NCOLS=3;
	const int B_NROWS=3, B_NCOLS=3;
	int in_A[A_NROWS][A_NCOLS];
	int in_B[B_NROWS][B_NCOLS];
	int out_C[A_NROWS * B_NCOLS];
	int index_a, index_b, index_d, result;
	for (index_a = 0; index_a < A_NROWS; index_a++) {
		for (index_b = 0; index_b < B_NCOLS; index_b++) {
			result = 0;
#pragma omp simd
			for (index_d = 0; index_d < A_NCOLS; index_d++) {
				int product_term = in_A[index_a][index_d] * in_B[index_d][index_b];
				result += product_term;
			}
			out_C[index_a * B_NCOLS + index_b] = result;

			result = 0;
#pragma omp parallel for
			for (index_d = 0; index_d < A_NCOLS; index_d++) {
				int product_term = in_A[index_a][index_d] * in_B[index_d][index_b];
				result += product_term;
			}
			out_C[index_a * B_NCOLS + index_b] = result;
/*
#pragma pipeline II=1
 			result = 0;
			for (index_d = 0; index_d < A_NCOLS; index_d++) {
				int product_term = in_A[index_a][index_d] * in_B[index_d][index_b];
				result += product_term;
			}
			out_C[index_a * B_NCOLS + index_b] = result;
*/
		}
	} 
	return 0;
}

int main(){
	int res = loop();
	return res;
}

