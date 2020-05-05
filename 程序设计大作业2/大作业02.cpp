#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 40

/*
测试结果:    数据       顺序查找     二分查找     数据个数 
	第一次： 28			  20			4			20 
	第二次： 16			  9				2 			16 
	第三次： 45			  10			4			13 
*/

double Average(int *data, int n){
	double ans = 0;
	for(int i = 0;i < n;++i){
		ans += data[i];
	}
	ans /= n;
	return ans;
}

int MinIndex(int *data, int n){
	int min = 0;
	for(int i = 0;i < n;++i){
		if(data[min] > data[i]){
			min = i;
		}
	}
	return min;
}

int MaxIndex(int *data, int n){
	int max = 0;
	for(int i = 0;i < n;++i){
		if(data[max] < data[i]){
			max = i;
		}
	}
	return max;
}

int LinearSearch(int *data, int n, int destnum){
	for(int i = 0;i < n;++i){
		printf("第 %d 次: %d ", i + 1, data[i]);
		if(data[i] == destnum){
			return i;
		}
	}
	printf("\n");
	return -1;
}

void BubbleSort(int *data, int n){
	for(int i = 0;i < n;++i){
		for(int j = 0;j < n - i;++j){
			if(data[j] > data[j + 1]){
				data[j] += data[j + 1];
				data[j + 1] = data[j] - data[j + 1];
				data[j] -= data[j + 1];
			}
		}
	}
}

// 二分查找 
static int freq = 1;
int BinarySearch(int *data, int destnum, int left, int right){
	if(left <= right){
		int mid = (left + right) / 2;
		printf("第 %d 次:%d ", freq++, data[mid]);
		if(data[mid] > destnum){
			return BinarySearch(data, destnum, left, mid - 1);
		}else if(data[mid] < destnum){
			return BinarySearch(data, destnum, mid + 1, right);
		}else{
			return mid;
		}
	}else{
		return -1;
	}
}

int main(){
	srand(time(0));
	int Data[N];
	int cnt;
	printf("请输入个数:");
	scanf("%d", &cnt);
	printf("\n初始数据:\n");
	for(int i = 0;i < cnt;++i){
		Data[i] = rand() % 100;
		printf("%d ", Data[i]);
	}
	printf("\n");
	int FindNum = Data[rand() % cnt];    // 待查找数 
	
	
	// 高于平均数
	double avr = Average(Data, cnt);
	printf("平均数为 %lf 高于平均数有:", avr);
	for(int i = 0;i < cnt;++i){
		if(Data[i] > avr){
			printf("%d ", Data[i]);
		}
	} 
	printf("\n");
	
	
	
	// 顺序查找
	printf("顺序查找 %d \n", FindNum);
	LinearSearch(Data, cnt, FindNum); 
	
	
	// 逆置
	for(int i = 0;i < cnt / 2;++i){
		Data[i] += Data[cnt - i - 1];
		Data[cnt - i - 1] = Data[i] - Data[cnt - i - 1];
		Data[i] -= Data[cnt - i - 1];
	}  
	printf("逆置结果: ");
	for(int i = 0;i < cnt;++i){
		printf("%d ", Data[i]);
	}
	printf("\n");
	
	// 最大最小换位
	int Minpos = MinIndex(Data, cnt);
	int Maxpos = MaxIndex(Data, cnt);
	Data[Minpos] += Data[Maxpos];
	Data[Maxpos] = Data[Minpos] - Data[Maxpos];
	Data[Minpos] -= Data[Maxpos];
	
	// 排序
	BubbleSort(Data, cnt);
	printf("排序结果:");
	for(int i = 0;i < cnt;++i){
		printf("%d ", Data[i]);
	} 
	printf("\n");
	
	// 二分
	printf("二分查找 %d \n", FindNum);
	freq = 1;
	BinarySearch(Data, FindNum, 0, cnt - 1); 
	return 0;
}
