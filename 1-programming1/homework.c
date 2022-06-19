#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 实现波兰表达式
char* PolishNotation(char* str1) 
{
	int i = 0;
	while (OperatorQ(str1[i]) == 1) 
	{
		i++;
	}
	if (i == strlen(str1)-1)
	{
		return str1;
	}
	char pre[30] = { '\0' };
	int num_p = 0;
	char suf[30] = { '\0' };
	int num_s = 0;
	char* sym;
	i = 0;
	while (str1[i] == '!') 
	{
		pre[num_p] = str1[i];
		num_p++;
		i++;
	}
	if (str1[i] == '(') 
	{
		int num_par = 1;//左括号的数量-右括号的数量
		i++;
		while (num_par) {
			switch (str1[i]) {
			case'(':num_par++;
				break;
			case')':num_par--;
				break;
			}
			if (!num_par) {
				break;
			}
			pre[num_p] = str1[i];
			num_p++;
			i++;
		}
		i++;
	}
	else {
		pre[num_p] = str1[i];
		i++;
	}
	sym = &str1[i];
	i++;
	if (str1[i] == '(' && str1[strlen(str1) - 1] == ')') 
	{
		i++;
		str1[strlen(str1) - 1] = '\0';
	}
	while (str1[i]!='\0')
	{
		suf[num_s] = str1[i];
		num_s++;
		i++;
	}
	sym[1] = '\0';
	str1 = strcpy(str1, sym);
	str1 = strcat(str1, PolishNotation(pre));//递归运算符前面字符串
	str1 = strcat(str1, PolishNotation(suf));//递归运算符后面字符串
	return str1;
}

// 实现逆波兰表达式
char* RPN(char* str1) 
{
	int i = 0;
	char str[20] = { '\0' };
	char* str2 = strcpy(str, str1);
	while (OperatorQ(str1[i]) == 1)
	{
		i++;
	}
	if (i == strlen(str1) - 1)
	{
		str1[0] = str2[i];
		for (int k = 0;  k < i;  k++)
		{
			str1[k + 1] = str2[k];
		}
		return str1;
	}
	char pre[30] = { '\0' };
	int num_p = 0;
	char suf[30] = { '\0' };
	int num_s = 0;
	char sym[2] = { '\0' };
	i = 0;
	while (str1[i] == '!') 
	{
		pre[num_p] = str1[i];
		num_p++;
		i++;
	}
	if (str1[i] == '(') 
	{
		int num_par = 1;//左括号的数量-右括号的数量
		i++;
		while (num_par) 
		{
			switch (str1[i]) 
			{
			case'(':num_par++;
				break;
			case')':num_par--;
				break;
			}
			if (!num_par) 
			{
				break;
			}
			pre[num_p] = str1[i];
			num_p++;
			i++;
		}
		i++;
	}
	else 
	{
		pre[num_p] = str1[i];
		i++;
	}
	sym[0] = str1[i];
	i++;
	if (str1[i] == '(' && str1[strlen(str1) - 1] == ')')
	{
		i++;
		str1[strlen(str1) - 1] = '\0';
	}
	while (str1[i] != '\0')
	{
		suf[num_s] = str1[i];
		num_s++;
		i++;
	}
	str1 = strcpy(str1, RPN(pre));//递归运算符前面字符串
	str1 = strcat(str1, RPN(suf));//递归运算符后面字符串
	str1 = strcat(str1, sym);
	return str1;
}

//将输入的表达式标准化
char* Standardize(char* str1)
{
	char str2[50] = { '\0' };
	int i = 1;
	while (str1[i]!='\0')
	{
		int flag = 0;//
		if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 0 && OperatorQ(str1[i + 2]) > 3)//p|q|r形
		{
			if (OperatorQ(str1[i]) <= OperatorQ(str1[i + 2])) 
			{
				str2[0] = '(';
				for (int j = 0; j <= i + 1; j++)
				{
					str2[j + 1] = str1[j];
				}
				str2[i + 3] = ')';
				for (int k = i + 2; k < strlen(str1); k++)
				{
					str2[k + 2] = str1[k];
				}
				str1 = strcpy(str1, str2);
			}
			else //p|q&形
			{
				for (int j = 0; j <= i ; j++)
				{
					str2[j] = str1[j];
				}
				str2[i + 1] = '(';
				if (OperatorQ(str1[i + 3]) == 0) //p|q&s形
				{
					str2[i + 2] = str1[i + 1];
					str2[i + 3] = str1[i + 2];
					str2[i + 4] = str1[i + 3];
					str2[i + 5] = ')';
					for (int k = i + 4; k < strlen(str1); k++)
					{
						str2[k + 2] = str1[k];
					}
				}
				else if (OperatorQ(str1[i + 3]) == 1) //p|q&!1形
				{
					//str2[i + 2] = 1;
					for (int j = i + 4; j <= strlen(str1) - 1; j++) {
						if (OperatorQ(str1[j]) == 0 ) {
							for (int k = i + 1; k <= j ; k++)
							{
								str2[k + 1] = str1[k];
							}
							str2[j + 2] = ')';
							for (int k = j + 1; k < strlen(str1); k++)
							{
								str2[k + 2] = str1[k];
							}
							break;
						}
					}
				}
				else if (OperatorQ(str1[i + 3]) == 2) //p|q&(r|s)形
				{
					for (int j = i + 4; j <= strlen(str1) - 1; j++) {
						if (OperatorQ(str1[j]) == 3 ) {
							for (int k = i + 1; k <= j; k++)
							{
								str2[k + 1] = str1[k];
							}
							str2[j + 2] = ')';
							for (int k = j + 1; k < strlen(str1); k++)
							{
								str2[k + 2] = str1[k];
							}
							break;
						}
					}
				}
				str1 = strcpy(str1, str2);
			}
		}
		else if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 1)//p|!q|s形
		{
			for (int j = i+2; j < strlen(str1) - 1; j++)
			{
				if (OperatorQ(str1[j]) == 0 && OperatorQ(str1[j + 1]) > 3) 
				{
					if (OperatorQ(str1[i]) <= OperatorQ(str1[j + 1]))//p|!q|s形
					{
						str2[0] = '(';
						for (int k = 0; k <= j; k++)
						{
							str2[k + 1] = str1[k];
						}
						str2[j + 2] = ')';
						for (int k = j + 1; k < strlen(str1); k++)
						{
							str2[k + 2] = str1[k];
						}
					}
					else//p|(q|r)&形
					{
						for (int j1 = 0; j1 <= i; j1++)
						{
							str2[j1] = str1[j1];
						}
						str2[i + 1] = '(';
						if (OperatorQ(str1[j + 2]) == 0)//p|!q&s形
						{
							for (int k = i + 1; k <= j + 3; k++)
							{
								str2[k + 1] = str1[k];
							}
							str2[j + 4] = ')';
							for (int k = j + 5; k < strlen(str1); k++)
							{
								str2[k + 2] = str1[k];
							}
						}
						else if (OperatorQ(str1[j + 2]) == 1)//p|!q&!s形
						{
							for (int j2 = j + 3; j2 <= strlen(str1) - 1; j2++) {
								if (OperatorQ(str1[j2]) == 0 ) {
									for (int k = i + 1; k <= j2; k++)
									{
										str2[k + 1] = str1[k];
									}
									str2[j2 + 2] = ')';
									for (int k = j2 + 1; k < strlen(str1); k++)
									{
										str2[k + 2] = str1[k];
									}
									break;
								}
							}
						}
						else if (OperatorQ(str1[j + 2]) == 2)//p|!q&(s|u)形
						{
							for (int j2 = j + 3; j2 <= strlen(str1) - 1; j2++) {
								if (OperatorQ(str1[j2]) == 3 ) {
									for (int k = i + 1; k <= j2; k++)
									{
										str2[k + 1] = str1[k];
									}
									str2[j2 + 2] = ')';
									for (int k = j2 + 1; k < strlen(str1); k++)
									{
										str2[k + 2] = str1[k];
									}
									break;
								}
							}
						}
					}
					str1 = strcpy(str1, str2);
					break;
				}
			}
			i++;
		}
		else if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 2) //p|(q|r)|s形
		{
			for (int j = i+2; j < strlen(str1)-1; j++)
			{
				if (OperatorQ(str1[j]) == 3 && OperatorQ(str1[j + 1]) > 3)
				{
					if (OperatorQ(str1[i]) <= OperatorQ(str1[j + 1]))
					{
						str2[0] = '(';
						for (int k = 0; k <= j; k++)
						{
							str2[k + 1] = str1[k];
						}
						str2[j + 2] = ')';
						for (int k = j + 1; k < strlen(str1); k++)
						{
							str2[k + 2] = str1[k];
						}
					}
					else//p|(q|r)&形
					{
						for (int j1 = 0; j1 <= i; j1++)
						{
							str2[j1] = str1[j1];
						}
						str2[i + 1] = '(';
						if (OperatorQ(str1[j + 2]) == 0)//p|(q|r)&s形
						{
							for (int k = i + 1; k <= j + 3; k++)
							{
								str2[k + 1] = str1[k];
							}
							str2[j + 4] = ')';
							for (int k = j + 5; k < strlen(str1); k++)
							{
								str2[k + 2] = str1[k];
							}
						}
						else if (OperatorQ(str1[j + 2]) == 1)//p|(q|r)&!s形
						{
							for (int j2 = j + 3; j2 <= strlen(str1) - 1; j2++) {
								if (OperatorQ(str1[j2]) == 0) {
									for (int k = i + 1; k <= j2; k++)
									{
										str2[k + 1] = str1[k];
									}
									str2[j2 + 2] = ')';
									for (int k = j2 + 1; k < strlen(str1); k++)
									{
										str2[k + 2] = str1[k];
									}
									break;
								}
							}
						}
						else if (OperatorQ(str1[j + 2]) == 2)//p|(q|r)&(u|s)形
						{
							for (int j2 = j + 3; j2 <= strlen(str1) - 1; j2++) {
								if (OperatorQ(str1[j2]) == 3) {
									for (int k = i + 1; k <= j2; k++)
									{
										str2[k + 1] = str1[k];
									}
									str2[j2 + 2] = ')';
									for (int k = j2 + 1; k < strlen(str1); k++)
									{
										str2[k + 2] = str1[k];
									}
									break;
								}
							}
						}
					}
					str1 = strcpy(str1, str2);
					break;
				}
			}
			i++;
		}	
		i++;
	}
	return str1;
}

//判断字符类型
int OperatorQ(char c) 
{
	switch (c) {
	case'|':return 5;
	case'&':return 4;
	case'^':return 6;
	case'~':return 7;	
	case'(':return 2;	
	case')':return 3;
	case'!':return 1;
	default:return 0;
	}
}

int main() 
{
	int flag = 1;//退出标志
	while (flag)
	{
		system("cls");
		printf("请输入表达式：\n");
		char str1[50] = { '\0' };
		char str2[50] = { '\0' };
		char* str3;
		char* str4;
		scanf("%s", str1);
		str3 = Standardize(str1);
		str4 = strcpy(str2, str3);
		str3 = PolishNotation(str3);
		printf("对应的波兰表达式：\n");
		puts(str3);
		printf("对应的逆波兰表达式：\n");
		puts(RPN(str4));
		printf("输入0退出，输入1-9继续...\n");
		scanf("%d", &flag);
	}
	return 0;
}
