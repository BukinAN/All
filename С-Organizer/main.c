#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h> 
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <time.h>
/* ������ ������� �������� */
#define BUFF_SIZE 20
/* ������������ ����� ������ � ��������� */
#define TEXT_LEN 40
typedef union
{
	struct { char day; char month; int year; }dmy;
	long date;
}DATE, *LPDATE;
/* ���� ����� ��������� */
typedef enum{
	FT_TIS,
	FT_PAGE,
	FT_STRING,
	FT_DATE,
}FIELDTYPE, *LPFIELDTYPE;
/* ��������� �������� ������� */
typedef struct
{
	char TIS[TEXT_LEN];	/* ����� ��������� ������ */
	int page;		    /* ����� �������� */
	int string;		    /* ����� ������ */
	DATE date;			/* ����  */
}ITEM, *LPITEM;
/* ��������� ������ (����� ������� ��������� ���������� ���� LIST)*/
typedef struct
{
	ITEM	Items[BUFF_SIZE]; /* ������ �������� */
	int Count; /* ���������� ������������ ��������� */
}LIST, *LPLIST;
/*-------------------------------------------------------------*/
/* ��������� ������� */
/*-------------------------------------------------------------*/
/* ���� ����� � ��������� ������������ */
int check_input_int(char* msg);
/* ������� ��������� */
void item_clear(LPITEM lpItem);
/* ������� ������ �������� */
void list_clear(LPLIST lpList);
/* ����� ������������ �������� �� ���� ft*/
LPITEM item_find_min(LPITEM Items, int Count, FIELDTYPE ft);
/* ����������� */
void separator();
/* ����� ��������� ������� */
void table_head();
/* ����� ��������� �� ����� */
void item_out(LPITEM Item);
/* ���� ������ � ��������� */
void item_in(LPITEM Item);
/* �������������� �������� */
void item_edit(LPITEM Item);
/* ����� �������� �������� �������� ���� ft */
LPITEM item_find(LPITEM Items, int Count, FIELDTYPE ft, void* value);
/* ���������� ������ �������� */
int list_index_of(LPLIST lpList, LPITEM lpItem);
/* �������� �������� �� ������ */
void list_delete(LPLIST lpList, LPITEM lpItem);
/* ����� �������� �������� �������� ���� ft */
LPITEM list_find(LPLIST lpList, FIELDTYPE ft, void* value);
/* ����� ������ ���������� � ������ */
LPITEM list_find_empty(LPLIST lpList);
/* ���������� ������ �������� �� ���� ft*/
void list_sort(LPLIST lpList, FIELDTYPE ft);
/* �������� �� ������ �������� � �������� Index */
void list_delete_index(LPLIST lpList, int Index);
/* ����� ����� ����� */
int total_sum(LPLIST lpList);
/* ����� ���� �� ������ ��������� ������ */
void list_out(LPLIST lpList);
/* ����� ���������� */
void sort_mode(LPLIST lpList);
/* ����� �������� �� ���������� ���� */
int find_mode(LPLIST lpList);
/* �������� ������ �������� */
void list_edit(LPLIST lpList);
/* ��������� ���������� ������ */
void text_generate(char* str, int MaxLen);
/* ������������� ������ ���������� ���������� */
void init_list(LPLIST lpList);
/*-------------------------------------------------------------*/
/* ���� ������ ����� � ��������� ������������ */
int check_input_int(char* msg)
{
	char str[TEXT_LEN]; /* ������ ����� */
	int i, sz;
	do
	{
		printf("%s", msg);	/* ������� ��������� */
		scanf("%s", str);		/* �������� ������ */
		sz = strlen(str);		/* ������ ������ */
		i = 0; /* ��������� ��� �� ������� �������� (0..9) */
		while (i < sz && isdigit(str[i])) i++;
	} while (i < sz); /* ���� ���� �� �����, �� ��������� ���� */
	return atoi(str); /* ���������� ��������� */
}
/* ������� ��������� */
void item_clear(LPITEM lpItem)
{
	lpItem->TIS[0] = 0;
	lpItem->string = 0;
	lpItem->page = 0;
	lpItem->date.date = 0;
}
/* ������� ������ �������� */
void list_clear(LPLIST lpList)
{
	int i;
	for (i = 0; i < lpList->Count; i++)
		item_clear(&lpList->Items[i]);
	lpList->Count = 0;
}
/* ����� ������������ �������� �� ���� ft*/
LPITEM item_find_min(LPITEM Items, int Count, FIELDTYPE ft)
{
	int i = 1;
	int m = 0; /* ������ ������������ ������� */

	switch (ft)
	{
	case FT_TIS:
		for (; i < Count; i++)
		if (strcmp(Items[m].TIS, Items[i].TIS) > 0)
			m = i;
		break;
	case FT_PAGE:
		for (; i < Count; i++)
		if (Items[m].page > Items[i].page)
			m = i;
		break;
	case FT_STRING:
		for (; i < Count; i++)
		if (Items[m].string > Items[i].string)
			m = i;
		break;
	case FT_DATE:
		for (; i < Count; i++)
		if (Items[m].date.date > Items[i].date.date)
			m = i;
		break;
	default: /* ���� ��� ���� ���������� */
		return 0;
	}

	/* ���������� ��������� �� ����������� ������� */
	return &Items[m];
}
/* ����������� */
void separator()
{
	printf("-------------------------------------------------------------------------------\n");
}
/* ����� ��������� ������� */
void table_head()
{
	separator();
	printf("page\tstring\tdate\t\tTIS\n");
	separator();
}
/* ����� ��������� �� ����� */
void item_out(LPITEM Item)
{
	printf("%3.d\t", Item->page);
	printf("%2.d\t", Item->string);
	printf("%2.d.%2.d.%4.d\t", Item->date.dmy.day, Item->date.dmy.month, Item->date.dmy.year);
	printf("%s\n", Item->TIS);
}
/* ���� ������ � ��������� */
void item_in(LPITEM Item)
{
	struct date d;
	int i;

	printf("TIS[%d]\t= ", TEXT_LEN); scanf("%s", Item->TIS);

	do{ i = check_input_int("page\t= "); } while (i <= 0); Item->page = i;
	Item->string = check_input_int("string\t= ");

	getdate(&d);
	Item->date.dmy.day = d.da_day;
	Item->date.dmy.month = d.da_mon;
	Item->date.dmy.year = d.da_year;
}
/* �������������� �������� */
void item_edit(LPITEM Item)
{
	clrscr();
	printf("Edit Item:\n");
	table_head(); /* ��������� ������� */
	item_out(Item); /* ����� �������� */
	separator();
	printf("\ninput new values:\n");
	separator();
	item_in(Item); /* ���� ����� ������ */
}
/* ����� �������� �������� �������� ���� ft */
LPITEM item_find(LPITEM Items, int Count, FIELDTYPE ft, void* value)
{
	LPDATE d;
	int l = 0;
	int i = 1;
	int r = 0;
	long d1, d2, d3;
	switch (ft)
	{
	case FT_TIS:
		l = strlen((char*)value);
		for (; i < Count; i++)
		if (abs(strncmp(Items[i].TIS, (char*)value, l)) <=
			abs(strncmp(Items[r].TIS, (char*)value, l)))
			r = i;
		break;
	case FT_PAGE:
		for (; i < Count; i++)
		if (abs(Items[i].page - (int)value) <
			abs(Items[r].page - (int)value))
			r = i;
		break;
	case FT_STRING:
		for (; i < Count; i++)
		if (abs(Items[i].page - *((int*)value)) <=
			abs(Items[r].page - *((int*)value)))
			r = i;
		break;
	case FT_DATE:
		d = ((LPDATE)value);
		for (; i < Count; i++)
		if (abs(Items[i].date.date - d->date) <
			abs(Items[r].date.date - d->date))
			r = i;

		break;
	default: /* ���� ��� ���� ���������� */
		return 0;
	}

	/* ���� �����, �� ���������� ��������� �� �������, ����� 0 */
	return r < Count ? &Items[r] : 0;
}
/* ���������� ������ �������� */
int list_index_of(LPLIST lpList, LPITEM lpItem)
{
	int i = 0;
	/* ���� ��������� lpItem � ������ lpList */
	while (i < lpList->Count && &lpList->Items[i] != lpItem) i++;
	/* ���� �����, �� ���������� ������, ����� -1 */
	return i < lpList->Count ? i : -1;
}
/* �������� �������� �� ������ */
void list_delete(LPLIST lpList, LPITEM lpItem)
{
	int i = list_index_of(lpList, lpItem);
	if (i >= 0)
		list_delete_index(lpList, i);
}
/* ����� �������� �������� �������� ���� ft */
LPITEM list_find(LPLIST lpList, FIELDTYPE ft, void* value)
{
	return item_find(lpList->Items, lpList->Count, ft, value);
}
/* ����� ������ ���������� � ������ */
LPITEM list_find_empty(LPLIST lpList)
{
	/* ���� � ������ ���� ��������� ��������, �� */
	/* ���������� ��������� �� ������ ������ �������, ����� 0*/
	return (lpList->Count < BUFF_SIZE) ? &lpList->Items[lpList->Count] : 0;
}
/* ���������� ������ �������� �� ���� ft*/
void list_sort(LPLIST lpList, FIELDTYPE ft)
{
	int i;
	ITEM tmp; /* ��� ������ */
	LPITEM m; /* ��������� �� ����������� ������� */
	/* ���� ���������� */
	for (i = 0; i < lpList->Count - 1; i++)
	{
		/* ����� ������������ �� ���� ft */
		m = item_find_min(lpList->Items + i, lpList->Count - i, ft);
		/* ����� */
		tmp = lpList->Items[i];
		lpList->Items[i] = *m;
		*m = tmp;
	}
}
/* �������� �� ������ �������� � �������� Index */
void list_delete_index(LPLIST lpList, int Index)
{
	lpList->Count--;
	lpList->Items[Index] = lpList->Items[lpList->Count - 1];
}
/* ����� ����� ����� */
int total_sum(LPLIST lpList)
{
	int sum = 0;
	int i;
	for (i = 0; i < lpList->Count; i++)
		sum += 1;
	return sum;
}
/* ����� ���� �� ������ ��������� ������ */
void list_out(LPLIST lpList)
{
	int i;
	clrscr();
	table_head();
	for (i = 0; i < lpList->Count; i++)
		item_out(&lpList->Items[i]);
	separator();
	printf("\t%4d\n", total_sum(lpList));
	separator();
	printf("\nelement count = %d", lpList->Count);
}
/* ����� ���������� */
void sort_mode(LPLIST lpList)
{
	printf("select field sortered\n");
	printf("t-text change string\na - page\ns - string\nd - date\n");
	switch (getch())
	{
	case 't':
		list_sort(lpList, FT_TIS);
		break;
	case 'a':
		list_sort(lpList, FT_PAGE);
		break;
	case 's':
		list_sort(lpList, FT_STRING);
		break;
	case 'd':
		list_sort(lpList, FT_DATE);
		break;
	}
}
/* ����� �������� �� ���������� ���� */
int find_mode(LPLIST lpList)
{
	static int string;
	static char a[TEXT_LEN];
	static DATE dt;
	int d, res = -1;

	printf("select field find\n");
	printf("t - text change string\na - page\ns - string\nd - date\n");
	switch (getch())
	{
	case 't': /* ������� */
		printf("text = ");
		scanf("%s", a);
		res = list_index_of(lpList, list_find(lpList, FT_TIS, a));
		break;
	case 'a': /* ����� ����� */
		printf("page = ");
		scanf("%d", &d);
		res = list_index_of(lpList, list_find(lpList, FT_PAGE, (void*)d));
		break;
	case 's': /* ����� �� ����� */
		string = check_input_int("string = ");
		res = list_index_of(lpList, list_find(lpList, FT_STRING, &string));
		break;
	case 'd': /* ���� ��������� */
		printf("input date: dd mm yyyy \n");
		do { d = check_input_int("day\t= "); } while (d < 1 || d > 31); dt.dmy.day = d;
		do { d = check_input_int("month\t= "); } while (d < 1 || d > 12); dt.dmy.month = d;
		do { d = check_input_int("year\t= "); } while (d < 1970 || d > 16000); dt.dmy.year = d;
		res = list_index_of(lpList, list_find(lpList, FT_DATE, (void*)&dt));
		break;
	}
	return res;
}
/*-----------------------------------------------------------------------------*/
/* �������� ������ �������� */
void list_edit(LPLIST lpList)
{
	int ItemIndex = -1; /* ������� ������ �������� */
	LPITEM lpItem = 0; /* ��������� ������� */


	if (lpList->Count > 0)
		ItemIndex = 0;

	/* ����  */
	while (1)
	{
		clrscr();
		/* ��������� */
		printf("Edit List [Count = %d] [Max Count = %d] ", lpList->Count, BUFF_SIZE);
		if (ItemIndex < 0)
			printf("[no selected]\n");
		else
			printf("[Current elem = %d]\n", ItemIndex);
		separator();

		/* ������� ���������� */
		printf("q - exit\n");
		printf("a - add\n");
		printf("d - delete\n");
		printf("e - edit\n");
		printf("l - print list\n");
		printf("s = sorter\n");
		printf("c - clear list\n");
		printf("f - find item\n");
		printf("b - back elem\tn - next elem\n\n");

		if (ItemIndex >= 0)
		{
			table_head();
			item_out(&lpList->Items[ItemIndex]);
		}
		separator();
		/* ��������� ������ */
		switch (getch())
		{
		case 'c': /* ������� ������ */
			list_clear(lpList);
			ItemIndex = -1;
			break;
		case 'b': /* ������� �� ���������� ������� */
			if (ItemIndex > 0)
				ItemIndex--;
			break;
		case 'n': /* ������� �� ��������� ������� */
			if (ItemIndex < lpList->Count - 1)
				ItemIndex++;
			break;
		case 's':
			sort_mode(lpList);
			list_out(lpList);
			printf("\npress any key to back menu");
			getch();
			break;
		case 'f':
			ItemIndex = find_mode(lpList);
			break;
		case 'd':
			if (ItemIndex >= 0)
			{
				list_delete_index(lpList, ItemIndex);
				if (ItemIndex >= lpList->Count)
					ItemIndex = lpList->Count - 1;
			}
			break;
		case 'e':
			if (ItemIndex >= 0)
			{
				item_edit(&lpList->Items[ItemIndex]);
			}
			break;
		case 'a': /* ���������� �������� � ������ */
			lpItem = list_find_empty(lpList); /* ����� ������ ��������� � ������ */
			if (lpItem)
			{
				lpList->Count++;
				item_in(lpItem);
				ItemIndex = list_index_of(lpList, lpItem);
			}
			else
				printf("no empty element!");
			break;
		case 'l': /* ���������� ������ � ���� ������� */
			list_out(lpList);
			printf("\npress any key to back menu");
			getch();
			break;
		case 'q': /* ����� �� ��������� */
			exit(1);
			break;
		}
	}
}
/* ��������� ���������� ������ */
void text_generate(char* str, int MaxLen)
{
	int i;
	for (i = 0; i < 3 + (rand() % (MaxLen - 3)); i++)
		str[i] = 'a' + (rand() % ('z' - 'a'));
}



/* ������������� ������ ���������� ���������� */
void init_list(LPLIST lpList)
{
	int i;
	lpList->Count = 10;
	for (i = 0; i < lpList->Count; i++)
	{
		lpList->Items[i].date.dmy.day = rand() % 30;
		lpList->Items[i].date.dmy.month = rand() % 12 + 1;
		lpList->Items[i].date.dmy.year = rand() % 10 + 2000;
		lpList->Items[i].page = rand() % 1000;
		lpList->Items[i].string = rand() % 100;
		text_generate(lpList->Items[i].TIS, TEXT_LEN);
	}
}
/* ������� ������� ��������� */
void main()
{
	LIST List;		/* ������ (������) �������� */
	srand(time(NULL));	/* ������������ */
	init_list(&List);	/* ������������� ������ ���������� ���������� */
	list_edit(&List);	/* ����������� ������ */
}
