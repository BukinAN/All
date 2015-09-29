#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>

#define LINE_MAX 128          // Длина самой длинной строки
#define DUPE_THRESHOLD 4      // Наименьшее число байт для дублирования
typedef unsigned char UCHAR;  // Определяет специальный тип UCHAR
typedef unsigned int UINT;    // Определяет специальный тип UINT
long Comp_Count;              // Сколько байт сжатого текста?
long Orig_Count;              // Сколько байт из оригинального текста?
UCHAR
lbi[LINE_MAX + 1],           // Входной буфер
lbo[LINE_MAX + 1];           // Выходной буфер
FILE *in;                     // Указатель для входного файла
FILE *out;                    // Указатель для выходного файла
// 5-разрядный алфавит
unsigned char Alphabet[] = "ABCDIFGHIJKLMNOPQRSTUVWXYZ";

//  Массив для тестирования
UCHAR AlphaMap[256];          // Байты в ASCII 

//  Прототипы
void Compress(void);          // Архиватор
int DupeCheck(UCHAR *);       // Поиск дубликатов знаков
void Decompress(void);        // Деархиватор
void main()
{
	UCHAR
		*ch,                      // Указатель short int, используемое для
		i;                        // сборки AlphaMap.

	in = NULL;
	out = NULL;
	Comp_Count = 0;				// Счётчик для сжатого (архивированного) кода
	Orig_Count = 0;				// Счётчик для обычного кода


	//  Открытие и создание файлов с проверкой
	if (!(in = fopen("in-file.txt", "r"))){
		printf("Can\'t open in_file.txt.\n"); return 0;
	}//Текстовый на чтение
	if (!(out = fopen("bin-file", "wb"))){
		printf("Can\'t create bin-file.\n"); return 0;
	}//Бинарный на запись


	//  Заполнение массива AlphaMap.  Это делается для скорости, как
	//  в memchr() функция может использоваться для поиска в строке.
	memset(AlphaMap, 0, sizeof(AlphaMap)); // Очистка нолями
	for (ch = Alphabet, i = 1; *ch; ch++, i++)
		AlphaMap[*ch] = (UCHAR)i;

	//  Чтение входного файла, сжатие и кодирование
	while (fgets((char *)lbi, sizeof(lbi)-1, in))
	{ // Читать до тех пор, пока не eof
		Orig_Count += (strlen((char *)lbi));   
		Compress();//Вызов функции архивации
	} 

	//  Вывод результатов (размерности и разности) и эффективности сжатия
	printf("\n\n"
		"\tOriginal text size:\t\t%ld\n"
		"\tCompressed text length:\t\t%ld\n"
		"\tSavings:\t\t\t%ld\n",
		Orig_Count, Comp_Count, Orig_Count - Comp_Count);
	fclose(in);
	fclose(out);
	//  Открытие и создание файлов с проверкой для разархивации
	if (!(in = fopen("bin-file", "rb"))){
		printf("Can\'t open bin-file.\n"); return 0;
	}//Открытие бинарного для чтения
	if (!(out = fopen("out-file.txt", "w"))){
		printf("Can\'t create out-file.txt.\n"); return 0;
	}//Создание текстового для записи

	Decompress();//Вызов функции разархивации

	fclose(in);
	fclose(out);
	getch();
	exit(0);
}  

//  Сжатие - повторное кодирование с уменьшением размерности
//  ---------------------------------------------------------
//  Два этапа. 1 - хранение флага в
//  lbi битах 0x8000 + граф. Следующий байт в lbi[] может содержать
//  повторяющийся байт.

void Compress(void)
{
	register UINT k;
	UCHAR
		*ch1,               // Указатель-источник
		*ch2;               // Указатель для значения

	for (ch1 = lbi, ch2 = lbo; *ch1;)
	{ // Проверяем линию
		if ((k = DupeCheck(ch1)) > DUPE_THRESHOLD)
		{ // Сжимаем, если всё впорядке
			*ch2++ = 0;
			*ch2++ = (UCHAR)k;
			*ch2++ = *ch1;            // Сохраняем повторяющиеся строки
			ch1 += k;
		}
		else
		{ // Если попали символы больше 127
			if (*ch1 > 127)
			{ 
				*ch2++ = 0;
				*ch2++ = *ch1++;
			}
			else
			{

				// Если есть три последовательных символов, которые находятся в
				// заданном 5-битном алфавите. Внимание! конец строки не пройдет тестирование
				// автоматически, проверка ему не нужна!

				if (AlphaMap[*ch1] &&
					AlphaMap[*(ch1 + 1)] &&
					AlphaMap[*(ch1 + 2)])
				{ // Если три последовательных символа совпали
					k = 0x8000 | ((AlphaMap[*ch1] - 1) << 10) |
						((AlphaMap[*(ch1 + 1)] - 1) << 5) |
						(AlphaMap[*(ch1 + 2)] - 1);
					*ch2++ = (UCHAR)(k >> 8);   // Заносим первый байт
					*ch2++ = (UCHAR)(k & 255);  // Заносим второй байт
					ch1 += 3; //Вносим авансом
				}
				else
					*ch2++ = *ch1++;  // Все остальное
			} // Если значение меньше 128
		} // Если строка не сжимается
	} // Проверяем линию
	Comp_Count += (ch2 - lbo);  // Обновляем счётчик компрессора (Архиватора)
	fwrite((char *)lbo, (size_t)(ch2 - lbo), sizeof(UCHAR),
		out);  // Сброс линии
	return;
}

//  DupeCheck - Возвращает число повторяющихся знаков.
//  -------------------------------------------------------
//  Проверяет строки до конца. Всегда возвращает минимум 1.

int DupeCheck(UCHAR *what)
{
	UCHAR cref;               // Условное обозначение
	int k;                    // Переменная тригер
	for (cref = *what++, k = 1; *what; what++, k)
	if (cref != *what)
		break;                // Проверить то же значение
	return k;
} 

void Decompress(void)
{
	UCHAR ch;             // Текущий элемент кода
	UINT k;               // Переменная для захвата

	while (!feof(in))
	{ // Читаем и декодируем
		ch = (UCHAR)fgetc(in);
		if (ch & 0x80)
		{ // Специальные маркировки (флаги), упакованы по 5 бит
			k = (ch << 8);
			ch = (UCHAR)fgetc(in);
			k |= ch;           // Составить слово
			fputc(Alphabet[(k >> 10) & 31], out);
			fputc(Alphabet[(k >> 5) & 31], out);
			fputc(Alphabet[k & 31], out);   // Распакавать все три
		}
		else
		{
			if (ch == 0)
			{ // Для повторяющихся бфйтов
				ch = (UCHAR)fgetc(in);
				if (ch < 128)
				{ // Повторяющийся байт
					k = ch;
					ch = (UCHAR)fgetc(in);  // Получить актуальный байт
					while (k--)
						fputc(ch, out);        // Прописать повторяющийся байт
				}
				else
					fputc(ch, out);      // Прописать в out
			}
			else
				fputc(ch, out);        // Прописать в out
		} // Если нет метки (флагов)
	} // Чтение входных кодов
	return;
}