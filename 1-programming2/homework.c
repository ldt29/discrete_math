#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// ʵ�ֲ������ʽ
char* PolishNotation(char* str1)
{
	int i = 0;
	while (OperatorQ(str1[i]) == 1)
	{
		i++;
	}
	if (i == strlen(str1) - 1)
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
		int num_par = 1;//�����ŵ�����-�����ŵ�����
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
	while (str1[i] != '\0')
	{
		suf[num_s] = str1[i];
		num_s++;
		i++;
	}
	sym[1] = '\0';
	str1 = strcpy(str1, sym);
	str1 = strcat(str1, PolishNotation(pre));//�ݹ������ǰ���ַ���
	str1 = strcat(str1, PolishNotation(suf));//�ݹ�����������ַ���
	return str1;
}

//�沨�����ʽ����
char* operation(char* str1, char* str3)
{
	int str2[50][50] = { 0 };
	char str4[500] = { "\0" };
	char str5[500] = { "\0" };
	int i = 0;
	int j = 0;
	while (str1[i])
	{
		int m = 0;
		if (!OperatorQ(str1[i])) 
		{
			for (int k = 0; k < i; k++) 
			{
				if (str1[i] == str1[k]) 
				{
					m++;
				}
			}
			if (m)
			{
				for (int c = 0; c < j; c++)
				{
					if (str1[str2[c][m - 1]] == str1[i]) 
					{
						str2[c][m] = i;
						break;
					}
				}
				j--; 
			}
			else
				str2[j][m] = i;
			j++;
		}
		i++;
	}
	char str[50] = { "\0" };
	for (int i = 0; str1[i]; i++)
	{
		str[i] = str1[i];
	}
	for (int i = 0; i < j; i++)
	{
		printf("%c\t", str[str2[i][0]]);
	}
	printf("%s\n", str3);
	int a = 0;
	int b = 0;
	for (int i = 0; i < (1 << j); i++)
	{
		for (int k = 0; k < j; k++)
		{
			int m = 0;
			str[str2[k][m]] = (i >> (j - k - 1)) % 2 + '0';
			while (str2[k][m + 1])
			{
				str[str2[k][m + 1]] = (i >> (j - k - 1)) % 2 + '0';
				m++;
			}
			printf("%c\t", str[str2[k][0]]);
		}
		printf("%d\n", stack(str));
		//ͨ����ֵ�������ȡ��ʽ�ͺ�ȡ��ʽ
		if (stack(str))
		{
			//��ȡ��ʽ
			if (str4[a])
			{
				a++;
				str4[a] = ')';
				a++;
				str4[a] = '|';
				a++;
				str4[a] = '(';
				if (str[str2[0][0]] == '0')
				{
					a++;
					str4[a] = '!';
				}
				a++;
				str4[a] = str1[str2[0][0]];
				for (int k = 1; k < j; k++)
				{
					a++;
					str4[a] = '&';
					if (str[str2[k][0]] == '0')
					{
						a++;
						str4[a] = '!';
					}
					a++;
					str4[a] = str1[str2[k][0]];
				}
			}
			else
			{
				if (str[str2[0][0]] == '0')
				{
					str4[a] = '!';
					a++;
				}
				str4[a] = str1[str2[0][0]];
				a++;
				for (int k = 1; k < j; k++)
				{
					str4[a] = '&';
					a++;
					if (str[str2[k][0]] == '0')
					{
						str4[a] = '!';
						a++;
					}
					str4[a] = str1[str2[k][0]];
					a++;
				}
				a--;
			}
		}
		//��ȡ��ʽ
		else
		{
			if (str5[b])
			{
				b++;
				str5[b] = ')';
				b++;
				str5[b] = '&';
				b++;
				str5[b] = '(';
				if (str[str2[0][0]] == '1')
				{
					b++;
					str5[b] = '!';
				}
				b++;
				str5[b] = str1[str2[0][0]];
				for (int k = 1; k < j; k++)
				{
					b++;
					str5[b] = '|';
					if (str[str2[k][0]] == '1')
					{
						b++;
						str5[b] = '!';
					}
					b++;
					str5[b] = str1[str2[k][0]];
				}
			}
			else
			{
				if (str[str2[0][0]] == '1')
				{
					str5[b] = '!';
					b++;
				}
				str5[b] = str1[str2[0][0]];
				b++;
				for (int k = 1; k < j; k++)
				{
					str5[b] = '|';
					b++;
					if (str[str2[k][0]] == '1')
					{
						str5[b] = '!';
						b++;
					}
					str5[b] = str1[str2[k][0]];
					b++;
				}
				b--;
			}
		}
	}
	printf("��Ӧ����ȡ��ʽ��\n");
	if (str4[0]) {
		if (strlen(str4) > 3 * j)
		{
			printf("(");
			printf("%s", str4);
			printf(")\n");
		}
		else printf("%s\n", str4);
	}
	else printf("�շ�ʽ\n");
	printf("��Ӧ�ĺ�ȡ��ʽ��\n");
	if (str5[0]) {
		if (strlen(str5) > 3 * j)
		{
			printf("(");
			printf("%s", str5);
			printf(")\n");
		}
		else printf("%s\n", str5);
	}
	else printf("�շ�ʽ\n");
}

 //��׺���ʽջ���������ֵ
int stack(char* str1) 

{
	int str[50] = { 0 };
	int j = 0;
	for (int i = 0; str1[i] ; i++)
	{
		if (!OperatorQ(str1[i])) 
		{
			str[j] = str1[i] - '0';
			j++;
		}
		else if (OperatorQ(str1[i]) == 1) 
		{
			j--;
			str[j] = !str[j];
			j++;
		}
		else if (str1[i] == '&') 
		{
			j-=2;
			str[j] = str[j ] && str[j + 1];
			j++;
		}
		else if (str1[i] == '|') 
		{
			j -=2;
			str[j] = str[j + 1] || str[j ];
			j++;
		}
		else if (str1[i] == '^') 
		{
			j-=2;
			str[j] = str[j + 1] || !str[j ];
			j++;
		}
		else if (str1[i] == '~') 
		{
			j-=2;
			str[j] = (!str[j + 1] || str[j]) && (!str[j] || str[j + 1]);
			j++;
		}
	}
	if (str[0])str[0] = 1;
	return str[0];
}

// ʵ���沨�����ʽ
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
		for (int k = 0; k < i; k++)
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
		int num_par = 1;//�����ŵ�����-�����ŵ�����
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
	str1 = strcpy(str1, RPN(pre));//�ݹ������ǰ���ַ���
	str1 = strcat(str1, RPN(suf));//�ݹ�����������ַ���
	str1 = strcat(str1, sym);
	return str1;
}

//������ı��ʽ��׼��
char* Standardize(char* str1)
{
	char str2[50] = { '\0' };
	int i = 1;
	while (str1[i] != '\0')
	{
		int flag = 0;//
		if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 0 && OperatorQ(str1[i + 2]) > 3)//p|q|r��
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
			else //p|q&��
			{
				for (int j = 0; j <= i; j++)
				{
					str2[j] = str1[j];
				}
				str2[i + 1] = '(';
				if (OperatorQ(str1[i + 3]) == 0) //p|q&s��
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
				else if (OperatorQ(str1[i + 3]) == 1) //p|q&!1��
				{
					//str2[i + 2] = 1;
					for (int j = i + 4; j <= strlen(str1) - 1; j++) {
						if (OperatorQ(str1[j]) == 0) {
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
				else if (OperatorQ(str1[i + 3]) == 2) //p|q&(r|s)��
				{
					for (int j = i + 4; j <= strlen(str1) - 1; j++) {
						if (OperatorQ(str1[j]) == 3) {
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
		else if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 1)//p|!q|s��
		{
			for (int j = i + 2; j < strlen(str1) - 1; j++)
			{
				if (OperatorQ(str1[j]) == 0 && OperatorQ(str1[j + 1]) > 3)
				{
					if (OperatorQ(str1[i]) <= OperatorQ(str1[j + 1]))//p|!q|s��
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
					else//p|(q|r)&��
					{
						for (int j1 = 0; j1 <= i; j1++)
						{
							str2[j1] = str1[j1];
						}
						str2[i + 1] = '(';
						if (OperatorQ(str1[j + 2]) == 0)//p|!q&s��
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
						else if (OperatorQ(str1[j + 2]) == 1)//p|!q&!s��
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
						else if (OperatorQ(str1[j + 2]) == 2)//p|!q&(s|u)��
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
		else if (OperatorQ(str1[i]) > 3 && OperatorQ(str1[i + 1]) == 2) //p|(q|r)|s��
		{
			for (int j = i + 2; j < strlen(str1) - 1; j++)
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
					else//p|(q|r)&��
					{
						for (int j1 = 0; j1 <= i; j1++)
						{
							str2[j1] = str1[j1];
						}
						str2[i + 1] = '(';
						if (OperatorQ(str1[j + 2]) == 0)//p|(q|r)&s��
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
						else if (OperatorQ(str1[j + 2]) == 1)//p|(q|r)&!s��
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
						else if (OperatorQ(str1[j + 2]) == 2)//p|(q|r)&(u|s)��
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

//�ж��ַ�����
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
	int flag = 1;//�˳���־
	while (flag)
	{
		system("cls");
		printf("��������ʽ��\n");
		char str1[50] = { '\0' };
		char str2[50] = { '\0' };
		char* str3;
		char* str4;
		char str5[50] = { '\0' };
		scanf("%s", str1);
		for(int i=0;str1[i];i++)
		{
			str5[i] = str1[i];
		}
		str3 = Standardize(str1);
		str4 = strcpy(str2, str3);
		str3 = PolishNotation(str3);
		printf("��Ӧ�Ĳ������ʽ��\n");
		puts(str3);
		printf("��Ӧ���沨�����ʽ��\n");
		puts(RPN(str4));
		printf("��Ӧ����ֵ��\n");
		operation(str4, str5);
		printf("����0�˳�������1-9����...\n");
		scanf("%d", &flag);
	}
	return 0;
}