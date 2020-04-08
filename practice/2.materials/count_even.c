int count_even(int *arr, int N){
	int ans = 0;
	for (int i = 0; i < N; i++){
		if (arr[i]%2 == 0)  ans++;
	}
	return ans;
}
