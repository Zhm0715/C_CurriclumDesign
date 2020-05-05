#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NameLen 10
#define MaxSize 128

/*
文件路径:./data.txt
学号:八位 姓名:小于十位(若有括号用_表示) 性别:M(an)/W(oman) 成绩:0~100 
*/

typedef struct{
	int StuNo;
	char name[NameLen];
	char sex;
	int mathscore;
	int clangscore;
	int physicsscore;
}StuInfo; 

typedef struct{
	int len;
	StuInfo AllStu[MaxSize];
}ALLStu;

void AllStudentInit(ALLStu *&stu){
	stu = (ALLStu *)malloc(sizeof(ALLStu));
	stu->len = 0;
}

void FileRead(ALLStu *stu){
	FILE *fp = fopen("./data.txt", "r");
	char Str[100];
	while(fscanf(fp, "%s", Str) != EOF){
		stu->AllStu[stu->len].StuNo = atoi(Str);
		strcpy(stu->AllStu[stu->len].name, Str + 9);
		int i = 9;
		while(Str[i] != '\0') ++i;		
		stu->AllStu[stu->len].sex = Str[++i];
		i += 2;    // 成绩第一个字符
		stu->AllStu[stu->len].mathscore = atoi(Str + i);
		while(Str[i] != '\0') ++i;
		++i;
		stu->AllStu[stu->len].clangscore = atoi(Str + i);
		while(Str[i] != '\0') ++i;
		++i;
		stu->AllStu[stu->len].physicsscore = atoi(Str + i);
		++stu->len;
	}
	fclose(fp);
}

void WriteFile(ALLStu *stu){
	FILE *fp = fopen("cpydata.txt", "w");
	char stuNo[8];
	char Score[3];
	for(int i = 0;i < stu->len;++i){
		itoa(stu->AllStu[i].StuNo, stuNo, 10);
		fputs(stuNo, fp);
		fputc('\0', fp);
		fputs(stu->AllStu[i].name, fp);
		fputc('\0', fp);
		fputc(stu->AllStu[i].sex, fp);
		fputc('\0', fp);
		itoa(stu->AllStu[i].mathscore, Score, 10);
		fputs(Score, fp);
		fputc('\0', fp);
		itoa(stu->AllStu[i].clangscore, Score, 10);
		fputs(Score, fp);
		fputc('\0', fp);
		itoa(stu->AllStu[i].physicsscore, Score, 10);
		fputs(Score, fp);
		fputc('\0', fp);
		fputc('\n', fp);
	}
	fclose(fp);
	if(remove("data.txt") != 0){
		printf("入库失败，请保证data.txt文件处于关闭状态\n");
	}
	rename("cpydata.txt", "data.txt");
}

void showStudent(StuInfo sInfo){
	printf("%s:\n", sInfo.name);
	printf("Student Number:%d\n", sInfo.StuNo);
	printf("Sex:%s\n",sInfo.sex == 'W' ? "Woman" : "Man");
	printf("Math Score:%d\n", sInfo.mathscore);
	printf("Physices Score:%d\n", sInfo.physicsscore);
	printf("Clang Score:%d\n", sInfo.clangscore);
}

int Found(ALLStu *stu){
	int choice;
	int pos = 0;
	int cnt = 0; 
	printf("若按学号查找 请输入1 若按姓名查找 请输入2:");
	scanf("%d", &choice);
	if(choice == 1){
		int stuNo;
		printf("请输入学号:");
		scanf("%d", &stuNo);
		for(int i = 0;i < stu->len;++i){
			if(stu->AllStu[i].StuNo == stuNo){
				showStudent(stu->AllStu[i]);
				return i;
			}
		}
	}else if(choice == 2){
		printf("请输入姓名(空格用_代替):"); 
		char stuName[NameLen];
		scanf("%s", stuName);
		for(int i = 0;i < stu->len;++i){
			if(strcmp(stuName, stu->AllStu[i].name) == 0){
				showStudent(stu->AllStu[i]);
				++cnt;
				pos = i;
			}
		}
	}else{
		printf("输入错误\n");
	}
	if(cnt == 0){
		printf("未找到该学生\n");
		return -1;
	}else if(cnt == 1){
		return pos;
	}
	return -2;
}

void ShowUnPass(ALLStu *stu){
	for(int i = 0;i < stu->len;++i){
		if(stu->AllStu[i].physicsscore < 60 || stu->AllStu[i].clangscore < 60 || stu->AllStu[i].mathscore < 60){
			showStudent(stu->AllStu[i]);
		}
	}
}

void ModifyInfo(ALLStu *&stu){
	int stuNo;
	bool flag = false;
	printf("请输入学号:");
	scanf("%d", &stuNo);
	int i;
	for(i = 0;i < stu->len;++i){
		if(stu->AllStu[i].StuNo == stuNo){
			showStudent(stu->AllStu[i]);
			flag = true;
			break;
		}
	}
	if(flag){
		printf("以上为原学生信息\n");
		printf("请输入修改后的学生信息:");
		printf("1.Student Number:\n");
		scanf("%d", &stuNo);
		getchar();
		stu->AllStu[i].StuNo = stuNo;
		printf("2 Student Name:\n");
		char s[NameLen];
		gets(s);
		strcpy(stu->AllStu[i].name, s);
		printf("3 Student Sex:\n");
		char sex;
		scanf("%c", &sex);
		getchar();
		stu->AllStu[i].sex = sex;
		printf("4 Math Score:\n");
		int score;
		scanf("%d", &score);
		getchar();
		stu->AllStu[i].mathscore = score;
		printf("5 Clang Score:\n");
		scanf("%d", &score);
		getchar();
		stu->AllStu[i].clangscore = score;
		printf("6 Physices Score:\n");
		scanf("%d", &score);
		getchar();
		stu->AllStu[i].physicsscore = score;
		printf("\n");
	}else{
		printf("未找到该学生\n");
	}
}

void InsertStu(ALLStu *&stu){
	if(stu->len == MaxSize){
		printf("空间已满\n");
		return ; 
	}
	StuInfo newStu;
	int stuNo;
	printf("1.Student Number:\n");
	scanf("%d", &stuNo);
	getchar();
	newStu.StuNo = stuNo;
	printf("2 Student Name:\n");
	char s[NameLen];
	gets(s);
	strcpy(newStu.name, s);
	printf("3 Student Sex:\n");
	char sex;
	scanf("%c", &sex);
	getchar();
	newStu.sex = sex;
	printf("4 Math Score:\n");
	int score;
	scanf("%d", &score);
	getchar();
	newStu.mathscore = score;
	printf("5 Clang Score:\n");
	scanf("%d", &score);
	getchar();
	newStu.clangscore = score;
	printf("6 Physices Score:\n");
	scanf("%d", &score);
	getchar();
	newStu.physicsscore = score;
	stu->AllStu[stu->len++] = newStu; 
}

void SortPrint(ALLStu *&stu){
	printf("请选择待排序的成绩\n");
	printf("1 Math Score\n");
	printf("2 Clang Score\n");
	printf("3 Physices Score\n");
	int choice;
	scanf("%d", &choice);
	int minpos;
	int i, j;
	StuInfo t;
	switch(choice){
		case 1:
			for(i = 0;i < stu->len;++i){
				minpos = i;
				for(j = i + 1;j < stu->len;++j){
					if(stu->AllStu[minpos].mathscore > stu->AllStu[j].mathscore){
						minpos = j;
					}	
				}
				if(minpos != i){
					t = stu->AllStu[i];
					stu->AllStu[i] = stu->AllStu[minpos];
					stu->AllStu[minpos] = t;
				}
			}
			break;
		case 2:
			for(i = 0;i < stu->len;++i){
				minpos = i;
				for(j = i + 1;j < stu->len;++j){
					if(stu->AllStu[minpos].clangscore > stu->AllStu[j].clangscore){
						minpos = j;
					}	
				}
				if(minpos != i){
					t = stu->AllStu[i];
					stu->AllStu[i] = stu->AllStu[minpos];
					stu->AllStu[minpos] = t;
				}
			}
			break;
		case 3:
			for(i = 0;i < stu->len;++i){
				minpos = i;
				for(j = i + 1;j < stu->len;++j){
					if(stu->AllStu[minpos].physicsscore > stu->AllStu[j].physicsscore){
						minpos = j;
					}	
				}
				if(minpos != i){
					t = stu->AllStu[i];
					stu->AllStu[i] = stu->AllStu[minpos];
					stu->AllStu[minpos] = t;
				}
			}
			break;
		default:
			printf("输入错误\n");
			return ;
	}
	for(int i = 0;i < stu->len;++i){
		showStudent(stu->AllStu[i]);
	}
}

void DeleteStu(ALLStu *&stu){
	printf("请查找要删除的学生\n");
	int pos = Found(stu);
	if(pos == -1){    // 未找到该生 
		return ;
	}else if(pos == -2){      // 找到多个学生 
		int StuNo;
		printf("请输入要删除的学生学号");
		scanf("%d", &StuNo);
		int i; 
		for(i = 0;i < stu->len;++i){
			if(stu->AllStu[i].StuNo == StuNo){
				for(int j = i + 1;j < stu->len;++j){
					stu->AllStu[j - 1] = stu->AllStu[j];
				}
				--stu->len;
				printf("删除完成\n");
				return ;
			}
		}
		if(i == stu->len){
			printf("未找到该生 删除失败\n");
		}
	}else{
		for(int j = pos + 1;j < stu->len;++j){
			stu->AllStu[j - 1] = stu->AllStu[j];
		}
		--stu->len;
		printf("删除完成\n");
	}
	 
}

void Show(ALLStu *&stu){
	int choice;
	int i;
	printf("菜单\n");
	printf("1 展示所有学生信息\n");
	printf("2 查找指定学生信息\n");
	printf("3 修改指定同学信息\n");
	printf("4 显示有不及格同学的信息\n");
	printf("5 按指定课程排序输出\n");
	printf("6 增加一个新同学\n");
	printf("7 删除一个同学\n");
	printf("8 学生存档\n");
	printf("9 退出\n");
	printf("请输入您的选择:"); 
	scanf("%d", &choice);
	switch(choice){
		case 1:
			for(i = 0;i < stu->len;++i){
				showStudent(stu->AllStu[i]);
			}
			break;
		case 2:
			Found(stu);
			break;
		case 3:
			ModifyInfo(stu);
			break;
		case 4:
			ShowUnPass(stu);
			break;
		case 5:
			SortPrint(stu);
			break;
		case 6:
			InsertStu(stu);
			break;
		case 7:
			DeleteStu(stu);
			break;
		case 8:
			WriteFile(stu);   // 存盘 
			break;
		case 9:
			free(stu);
			exit(0);
		default:
			printf("输入错误\n");
	}
}


int main(){
	ALLStu *stu;
	AllStudentInit(stu);
	FileRead(stu);
	while(true){
		Show(stu);
	}
	return 0;
}
