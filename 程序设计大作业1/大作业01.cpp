#include <stdio.h>
#include <math.h>
#define MaxSize 128   //完数最多因子数量 

/*
long long int factorial(int n){
	int i;
	long long int ans = 1;
	for(i = 1;i <= n;++i){
		ans *= i;
	}
	return ans;
}
*/ 

void factorial(int n){    // 不溢出阶乘 数组存储每一位数(倒序 索引0处不存储) 对每一个数进行迭代 
	int a[1000];
	a[1] = 1;
	int p = 1;
	int j = 0; 
    int one = 0;
    for(int i = 2;i <= n;++i){
        for(int j = 1;j <= p;++j){
			int temp = a[j] * i + one;
			one = temp / 10;
			a[j] = temp % 10;
        }
		while(one){
		a[j] = one % 10;
		one = one / 10;
		++j;
		}
		p = j - 1;
	}
	for (int i = p;i >= 1;--i)
		printf("%d",a[i]);
}

int InverseNumber(int n){
	int ans = 0;
	int flag = 1;
	while(n != 0){
		int midnum = n % 10;
		ans = ans * 10 + midnum;
		n = n / 10;
	}
	return ans;
}

bool isPrime(int n){
	int i = 2;
	while(i <= sqrt(n)){
		if(n % i == 0){
			return false;
		}
		++i;
	}
	return true;
}

bool isPrefectNumber(int n){
	int num = 0;
	int Que[MaxSize];
	int cnt = -1; 
	for(int i = 1;i < n;++i){
		if(n % i == 0){
			Que[++cnt] = i;
			num += i;
		}
	}
	if(num == n){
		printf("%d 因子有: ", n);
		for(int i = 0;i <= cnt;++i){
			printf("%d ", Que[i]);
		}
		printf("\n");
		return true;
	}
	return false;
}

bool HasSeven(int n){
	while(n){
		if(n % 10 == 7){
			return true;
		}
		n = n / 10;
	}
	return false;
}

void show(){
	int m;
	int n;
	printf("请输入两个数字(空格分隔):");
	scanf("%d %d", &m, &n);
	int Max = m > n ? m : n;
	int Min = m > n ? n : m;
	
	// 七明七暗
	printf("%d到%d的七明七暗数有:", Min, Max);
	for(int i = Min;i <= Max;++i){
		if(i % 7 == 0){
			printf("%d ", i);
		}else if(HasSeven(i)){
			printf("%d ", i);
		}
	}
	printf("\n");
	
	// 阶乘 
	printf("%d factorial is:", m);
	factorial(m);
	printf("\n%d factorial is:\n", n);
	factorial(n);
	
	//回文数
	printf("\n%d到%d的回文数有:", Min, Max);
	for(int i = Min;i <= Max;++i){
		int ans = InverseNumber(i);
		if(ans == i){
			printf("%d ", i);
		}
	}
	printf("\n");
	
	// 素数
	printf("%d到%d的素数有:", Min, Max);
	for(int i = Min;i <= Max;++i){
		if(isPrime(i)){
			printf("%d ", i);
		}
	}
	printf("\n");
	
	// 完数
	printf("%d到%d的完数有:\n", Min, Max);
	for(int i = Min;i <= Max;++i){
		isPrefectNumber(i);
	}
}

int main(){
	show();
	return 0;
}
