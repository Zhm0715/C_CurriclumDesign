#include <stdio.h>
#include <string.h>
#define MaxSize 128

/*
统计单词个数不含数字 文章应不含'符. 按照书写规范标点符号后需空格 
路径 ./data.txt
*/
void FileReadAL(char *sour, int *FreqList){ 
	FILE *inFile;
	inFile = fopen(sour, "r");
	char c; 
	do{
		c = fgetc(inFile);
		++FreqList[c];
	}while(c != EOF);
	fclose(inFile);
}

bool isWord(char *s, int *len){
	if((*s < 'A' || *s > 'Z') && (*s < 'a' || *s > 'z')){
		return false;
	}
	int i = 0;
	while(*(s + i + 1) != '\0'){
		if((*(s + i) < 'A' || *(s + i) > 'Z') && (*(s + i) < 'a' || *(s + i) > 'z')){
			return false;
		}
		++i;	
	}
	if((*(s + i) < 'A' || *(s + i) > 'Z') && (*(s + i) < 'a' || *(s + i) > 'z')){
		*(s + i) = '\0';      // 处理标点 
	}else{
		++i;
	}
	*len = i;
	return true;
}

int FileReadWD(char *sour, char *maxlenstr){
	FILE *inFile = fopen(sour, "r");
	char str[MaxSize];
	int length = 0;
	int MaxLen = 0;
	int ans = 0;
	while(fscanf(inFile, "%s", str) != EOF){
		if(isWord(str, &length)){
			++ans;
			if(length > MaxLen){
				MaxLen = length;
				strcpy(maxlenstr, str);
			}
		}
	}
	fclose(inFile);
	return ans;
} 

int main(){
	int freq[MaxSize] = {0};
	char *sour = "./data.txt";
	FileReadAL(sour, freq);
	char s[MaxSize];
	int cnt = FileReadWD(sour, s);
	for(int i = 0;i < MaxSize;++i){
		if(freq[i] != 0){
			printf("字符: %c, 个数: %d\n", i, freq[i]);
		}
	}
	printf("cnt = %d, MaxLenStr = %s", cnt, s);
	return 0;
}
