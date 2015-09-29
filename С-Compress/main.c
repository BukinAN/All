#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>

#define LINE_MAX 128          // ����� ����� ������� ������
#define DUPE_THRESHOLD 4      // ���������� ����� ���� ��� ������������
typedef unsigned char UCHAR;  // ���������� ����������� ��� UCHAR
typedef unsigned int UINT;    // ���������� ����������� ��� UINT
long Comp_Count;              // ������� ���� ������� ������?
long Orig_Count;              // ������� ���� �� ������������� ������?
UCHAR
lbi[LINE_MAX + 1],           // ������� �����
lbo[LINE_MAX + 1];           // �������� �����
FILE *in;                     // ��������� ��� �������� �����
FILE *out;                    // ��������� ��� ��������� �����
// 5-��������� �������
unsigned char Alphabet[] = "ABCDIFGHIJKLMNOPQRSTUVWXYZ";

//  ������ ��� ������������
UCHAR AlphaMap[256];          // ����� � ASCII 

//  ���������
void Compress(void);          // ���������
int DupeCheck(UCHAR *);       // ����� ���������� ������
void Decompress(void);        // �����������
void main()
{
	UCHAR
		*ch,                      // ��������� short int, ������������ ���
		i;                        // ������ AlphaMap.

	in = NULL;
	out = NULL;
	Comp_Count = 0;				// ������� ��� ������� (���������������) ����
	Orig_Count = 0;				// ������� ��� �������� ����


	//  �������� � �������� ������ � ���������
	if (!(in = fopen("in-file.txt", "r"))){
		printf("Can\'t open in_file.txt.\n"); return 0;
	}//��������� �� ������
	if (!(out = fopen("bin-file", "wb"))){
		printf("Can\'t create bin-file.\n"); return 0;
	}//�������� �� ������


	//  ���������� ������� AlphaMap.  ��� �������� ��� ��������, ���
	//  � memchr() ������� ����� �������������� ��� ������ � ������.
	memset(AlphaMap, 0, sizeof(AlphaMap)); // ������� ������
	for (ch = Alphabet, i = 1; *ch; ch++, i++)
		AlphaMap[*ch] = (UCHAR)i;

	//  ������ �������� �����, ������ � �����������
	while (fgets((char *)lbi, sizeof(lbi)-1, in))
	{ // ������ �� ��� ���, ���� �� eof
		Orig_Count += (strlen((char *)lbi));   
		Compress();//����� ������� ���������
	} 

	//  ����� ����������� (����������� � ��������) � ������������� ������
	printf("\n\n"
		"\tOriginal text size:\t\t%ld\n"
		"\tCompressed text length:\t\t%ld\n"
		"\tSavings:\t\t\t%ld\n",
		Orig_Count, Comp_Count, Orig_Count - Comp_Count);
	fclose(in);
	fclose(out);
	//  �������� � �������� ������ � ��������� ��� ������������
	if (!(in = fopen("bin-file", "rb"))){
		printf("Can\'t open bin-file.\n"); return 0;
	}//�������� ��������� ��� ������
	if (!(out = fopen("out-file.txt", "w"))){
		printf("Can\'t create out-file.txt.\n"); return 0;
	}//�������� ���������� ��� ������

	Decompress();//����� ������� ������������

	fclose(in);
	fclose(out);
	getch();
	exit(0);
}  

//  ������ - ��������� ����������� � ����������� �����������
//  ---------------------------------------------------------
//  ��� �����. 1 - �������� ����� �
//  lbi ����� 0x8000 + ����. ��������� ���� � lbi[] ����� ���������
//  ������������� ����.

void Compress(void)
{
	register UINT k;
	UCHAR
		*ch1,               // ���������-��������
		*ch2;               // ��������� ��� ��������

	for (ch1 = lbi, ch2 = lbo; *ch1;)
	{ // ��������� �����
		if ((k = DupeCheck(ch1)) > DUPE_THRESHOLD)
		{ // �������, ���� �� ��������
			*ch2++ = 0;
			*ch2++ = (UCHAR)k;
			*ch2++ = *ch1;            // ��������� ������������� ������
			ch1 += k;
		}
		else
		{ // ���� ������ ������� ������ 127
			if (*ch1 > 127)
			{ 
				*ch2++ = 0;
				*ch2++ = *ch1++;
			}
			else
			{

				// ���� ���� ��� ���������������� ��������, ������� ��������� �
				// �������� 5-������ ��������. ��������! ����� ������ �� ������� ������������
				// �������������, �������� ��� �� �����!

				if (AlphaMap[*ch1] &&
					AlphaMap[*(ch1 + 1)] &&
					AlphaMap[*(ch1 + 2)])
				{ // ���� ��� ���������������� ������� �������
					k = 0x8000 | ((AlphaMap[*ch1] - 1) << 10) |
						((AlphaMap[*(ch1 + 1)] - 1) << 5) |
						(AlphaMap[*(ch1 + 2)] - 1);
					*ch2++ = (UCHAR)(k >> 8);   // ������� ������ ����
					*ch2++ = (UCHAR)(k & 255);  // ������� ������ ����
					ch1 += 3; //������ �������
				}
				else
					*ch2++ = *ch1++;  // ��� ���������
			} // ���� �������� ������ 128
		} // ���� ������ �� ���������
	} // ��������� �����
	Comp_Count += (ch2 - lbo);  // ��������� ������� ����������� (����������)
	fwrite((char *)lbo, (size_t)(ch2 - lbo), sizeof(UCHAR),
		out);  // ����� �����
	return;
}

//  DupeCheck - ���������� ����� ������������� ������.
//  -------------------------------------------------------
//  ��������� ������ �� �����. ������ ���������� ������� 1.

int DupeCheck(UCHAR *what)
{
	UCHAR cref;               // �������� �����������
	int k;                    // ���������� ������
	for (cref = *what++, k = 1; *what; what++, k)
	if (cref != *what)
		break;                // ��������� �� �� ��������
	return k;
} 

void Decompress(void)
{
	UCHAR ch;             // ������� ������� ����
	UINT k;               // ���������� ��� �������

	while (!feof(in))
	{ // ������ � ����������
		ch = (UCHAR)fgetc(in);
		if (ch & 0x80)
		{ // ����������� ���������� (�����), ��������� �� 5 ���
			k = (ch << 8);
			ch = (UCHAR)fgetc(in);
			k |= ch;           // ��������� �����
			fputc(Alphabet[(k >> 10) & 31], out);
			fputc(Alphabet[(k >> 5) & 31], out);
			fputc(Alphabet[k & 31], out);   // ����������� ��� ���
		}
		else
		{
			if (ch == 0)
			{ // ��� ������������� ������
				ch = (UCHAR)fgetc(in);
				if (ch < 128)
				{ // ������������� ����
					k = ch;
					ch = (UCHAR)fgetc(in);  // �������� ���������� ����
					while (k--)
						fputc(ch, out);        // ��������� ������������� ����
				}
				else
					fputc(ch, out);      // ��������� � out
			}
			else
				fputc(ch, out);        // ��������� � out
		} // ���� ��� ����� (������)
	} // ������ ������� �����
	return;
}