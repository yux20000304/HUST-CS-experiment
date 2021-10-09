#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#define N 3          //商品数量暂定3个
unsigned long rankArr[N];                 // 保存排名信息数组
typedef struct good          //保存商品信息结构
{
	char name[10];
	BYTE discount;
	WORD buyPrice;
	WORD marketPrice;
	WORD stockNumber;
	WORD soldNumber;
	WORD recommandation;
} Good;


extern  void CAMMEND(Good *);               
int SEARCH(Good *goods, char *GNAME);       
int printAGood(Good *goods, int index);      

int main()
{
	char bname[10] = "YUXIN";
	char bpass[7] = "123456";
	char in_name[11];
	char in_pwd[7];
	char GNAME[10];
	int op = 1, op_ = 1;
	int AUTH = 0;
	int length = 0, temp_int = 0;
	Good goods[N];

	char strFormat[] = "%s";


	strcpy(goods[0].name, "PEN");
	goods[0].discount = 8;
	goods[0].buyPrice = 120;
	goods[0].marketPrice = 320;
	goods[0].stockNumber = 254;
	goods[0].soldNumber = 85;
	goods[0].recommandation = 0;

	strcpy(goods[1].name, "BOOK");
	goods[1].discount = 9;
	goods[1].buyPrice = 35;
	goods[1].marketPrice = 56;
	goods[1].stockNumber = 70;
	goods[1].soldNumber = 25;
	goods[1].recommandation = 0;

	strcpy(goods[2].name, "BAG");
	goods[2].discount = 10;
	goods[2].buyPrice = 12;
	goods[2].marketPrice = 30;
	goods[2].stockNumber = 25;
	goods[2].soldNumber = 5;
	goods[2].recommandation = 0;

	while (op)
	{
		printf("Please input your name:");
		scanf("%s", in_name);
		length = strlen(in_name);
		if (length == 1)
		{
			if (in_name[0] == 'q')
			{
				system("pause");
				return 0;
			}
			else if (in_name[0] == '0')
				AUTH = 0;
			break;
		}
		else
		{
			printf("Please input your password:");
			scanf("%s", in_pwd);
			if (strcmp(in_name, bname) != 0 || strcmp(in_pwd, bpass) != 0)
			{
				printf("ERROR!\n");
				continue;
			}
			else
			{
				AUTH = 1;
				break;
			}
		}
	}
	switch (AUTH)
	{
	case 1:
		while (op_)
		{
			system("cls");
			printf("\t\tYYX_SHOP\t\n1.SEARCH 2.BUY 3.RECOMMEND 4.PRINTGOOD 5.EXIT\n");
			printf("Please input your option:");
			scanf("%d", &op_);
			switch (op_)
			{
			case 1:
				printf("Please input the name of the commodity: ");
				scanf("%s", GNAME);
				temp_int = SEARCH(goods, GNAME);
				if (temp_int == 0)
				{
					printf("!\n");
				}
				else
				{
					printAGood(goods, temp_int - 1);
				}
				break;
			case 2:
				printf("Please input the commodity you want to buy: ");
				scanf("%s", GNAME);
				temp_int = SEARCH(goods, GNAME);
				if (temp_int == 0 || goods[temp_int - 1].stockNumber == goods[temp_int - 1].soldNumber)
					printf("Not found!\n");
				else{
					goods[temp_int - 1].soldNumber++;
					printf("Buy successfully!\n");
				}
					break;
			case 3:            
				CAMMEND(goods);
				printf("Calculate successful!\n");
				break;
			case 4:
				for (int i = 0; i < N; i++)
				{
					printAGood(goods, i);
				}
				break;
			case 5:
				return 0;

			default:
				break;
			}
			system("pause");
		}
		break;
	

	default:
		break;
		system("pause");
	}

}




int SEARCH(Good *goods, char *GNAME)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (strcmp(goods[i].name, GNAME) == 0)
			return i + 1;
	}
	return 0;
}

int printAGood(Good *goods, int index)
{
	if (index >= N || index < 0)
		return 0;
	printf("good_name：%s\n", goods[index].name);
	printf("good_discount：%d\n", goods[index].discount);
	printf("buy_price：%d\n", goods[index].buyPrice);
	printf("sell_price：%d\n", goods[index].marketPrice);
	printf("buy_number：%d\n", goods[index].stockNumber);
	printf("sold_number：%d\n", goods[index].soldNumber);
	printf("recommandation：%d\n", goods[index].recommandation);

	return 1;
}
