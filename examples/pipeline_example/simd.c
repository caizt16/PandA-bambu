
int loop(){
	int i = 0, a =0;
	#pragma omp parallel for
	for (i =0; i < 3; ++i){
		a += i;
	}	
	return 0;
}

int main(){
	int res = loop();
	return res;
}

