#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>

#if defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT

#include <wchar.h>

wchar_t * walloc(short int * Arg) {
	int L = 0;

	while (Arg[L]) L++;
	wchar_t * result = new wchar_t[L+1];
	wchar_t * ptr = result;
	while (*ptr++ = *Arg++);

	return result;
}

void wfree(wchar_t * _Arg, short int * Arg) {
	wchar_t * ptr = _Arg;
	while (*Arg++ = *ptr++);
	delete[] _Arg;
}
#else
//  Microsoft 
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)

wchar_t * walloc(short int * Arg) {
	return reinterpret_cast<wchar_t *>(Arg);
}

void wfree(wchar_t * _Arg, short int * Arg) {
}
#endif


long _wcslen(wchar_t * Arg) {
    wchar_t * End = Arg;
    while (*End++);
    return End - Arg - 1;
}

wchar_t * _wcschr(wchar_t * Str, wchar_t C) {
    while (*Str && *Str != C)
        Str++;
    return *Str == C ? Str : NULL;
}

void _swprintf(wchar_t * Dest, char * fmt, int val) {
    char buf[30];
    char * ptr = (char *)buf;
    sprintf(ptr, fmt, val);
    while (*Dest++ = *ptr++);
}

extern "C" {

	// Функция удаления начальных пробелов, табуляций и переводов строки из S
	void stripLeading(wchar_t * S) {
		int i = 0; // Счетчик входных символов
		int j = 0; // Счетчик выходных символов
		// Пропускаем пробелы/табуляции/переводы строк
		while (S[i] == ' ' || S[i] == '\t' || S[i] == '\n' || S[i] == '\r')
			i++;
		if (i == 0) // Если ничего не пропускаем, то выходим
			return;
		while (S[i] != 0) { // Пока не дошли до конечного нулевого символа
			S[j] = S[i]; // Копируем символ биже к началу
			i++;
			j++;
		}
		S[j] = 0; // Закрываем строку нулевым символом
	}

	enum { qtNone = 0, qtSingle, qtDouble }; // Константы режима чтения строки (обычный, строка в апострофах, строка в кавычках )

	/* Эта процедура увеличивает значение счетчика *count символов строки S. Если строка
	S кончилась, то к ней приплюсовывается следующая строка из массива lines. Для
	этого в функцию передается lines, общее число строк nL, указатель на номер текущей
	строки nline, указатель K на общую длину строки S.
	*/
	void inc_count(wchar_t * S, wchar_t ** lines, int nL, int * nline, int * count, int * K) {
		(*count)++;
		while (*count >= *K && *nline < nL - 1) {
			(*nline)++;
			wcscat(S, L"\n");
			wcscat(S, lines[*nline]);
			*K = _wcslen(S);
		}
	}

	/* Продвигает счетчик символов *count строки S длиной *K таким образом, чтобы он
	пропустил сбалансированную по всем видам скобок подстроку, заканчивающуюся
	одним из символов из строки before. Функция возвращает 1 или 0 в зависимости
	от корректности (сбалансированности) входной строки.
	На входе -- содержимое текущей строки S, общий массив строк lines, число строк nL,
	указатель на номер текущей строки nline.
	Сбалансированная подстрока может располагаться в нескольких строках, поэтому
	данная функция может их "дочитывать" в S, увеличивая *nline.
	*/
	int trace(int * count, int * K, wchar_t * before, wchar_t * S, wchar_t ** lines, int nL,
		int * nline, bool use_triang) {
		wchar_t _quote = qtNone; // Сначала обычный режим чтения
		int result = 1;

		if (_wcslen(S) == 0) { // Если входная строка пуста
			inc_count(S, lines, nL, nline, count, K); // то дочитываем в нее еще одну строку,
			// увеличивая счетчик *count на единицу
			(*count)--; // Возвращаем счетчик *count на место -- на 1 символ назад.
		}
		while (*count < *K && result && (_quote != qtNone || _wcschr(before, S[*count]) == NULL)) {
			wchar_t C = S[*count];

			if (_quote != qtNone && C == '\\') { // Пропускаем экранируемый символ в строке
				inc_count(S, lines, nL, nline, count, K); // передвигаемся к следующему символу
			}
			else if (C == '\'') { // Если встретился апостроф
				if (_quote == qtSingle) _quote = qtNone; // Это был закрывающий апостроф
				else if (_quote == qtNone) _quote = qtSingle; // Это открывающий апостроф
			}
			else if (C == '"') { // Если встретились кавычки
				if (_quote == qtDouble) _quote = qtNone; // Это были закрывающие кавычки
				else if (_quote == qtNone) _quote = qtDouble; // Это открывающие кавычки
			}
			else if (_quote == qtNone && (C == '(' || C == '[' || C == '{' || use_triang && C == '<')) {
				// Если мы не посередине строки в апострофах/кавычках и встретили открывающую скобку
				inc_count(S, lines, nL, nline, count, K); // Идем к следующему символу
				switch (C) { // Пропускаем часть строки до соответствующей закрывающей скобки
				case '(':	result = trace(count, K, L")", S, lines, nL, nline, use_triang);
					break;
				case '[':	result = trace(count, K, L"]", S, lines, nL, nline, use_triang);
					break;
				case '{':	result = trace(count, K, L"}", S, lines, nL, nline, use_triang);
					break;
				case '<':	result = trace(count, K, L">", S, lines, nL, nline, use_triang);
					break;
				}
			}
			else if (_quote == qtNone && (C == ')' || C == ']' || C == '}' || use_triang && C == '>') && _wcschr(before, C) == NULL)
				// Если мы не посередине строки в апострофах/кавычках и незапланированно встретили закрывающую скобку
				result = 0; // то это ошибка.

			if (result) // Если все хорошо
				inc_count(S, lines, nL, nline, count, K); // то передвигаемся к следующему символу
		}
		// Проверяем, дошли ли мы до завершающего символа из строки before.
		result = result && *count < *K && _wcschr(before, S[*count]) != NULL;
		return result;
	}

	/* Возвращает сбалансированную по всем видам скобок подстроку, заканчивающуюся
	одним из символов строки terms. На входе -- содержимое текущей строки S,
	общий массив строк lines, число строк nL, указатель на номер текущей строки nline.
	Сбалансированная подстрока может располагаться в нескольких строках, поэтому
	данная функция может их "дочитывать" в S, увеличивая *nline.
	count - Счетчик символов в строке
	*/
	wchar_t * getBalancedItem(wchar_t * S, wchar_t ** lines, int nL, int * nline, wchar_t * terms,
		int & count, bool use_triang = false) {
		wchar_t * result = new wchar_t[10*65536]; // Результат

		int K; // Текущая длина строки в буфере
		int i;

		wcscpy(result, L"");

		if (_wcslen(S) == 0) { // Если входная строка пуста
			inc_count(S, lines, nL, nline, &count, &K); // то дочитываем в нее еще одну строку,
			// увеличивая счетчик count на единицу
			count--; // Возвращаем счетчик count на место -- на 1 символ назад.
		}

		K = _wcslen(S);

		trace(&count, &K, terms, S, lines, nL, nline, use_triang);
		// Копируем первые count-1 символов в результат
		for (i = 0; i < count; i++)
			result[i] = S[i];
		result[count] = 0; // Закрываем строку в result нулевым символом
		// Удаляем из S первые count-1 символов
		for (i = 0; S[count + i] != 0; i++)
			S[i] = S[count + i];
		S[i] = 0; // Закрываем строку S нулевым символом

		return result;
	}

	EXPORT bool BAL(int N, short int * Map, short int ** Args) {
		if (N < 2 || Map[0] || Map[1])
			return false;
		wchar_t * Args0 = walloc(Args[0]);
		wchar_t * Args1 = walloc(Args[1]);

		stripLeading(Args0); // Удаляем начальные пробелы, если они есть

		int L = _wcslen(Args0);

		int NN = 0;
		int count = 0;

		delete[] getBalancedItem(Args0, &Args0, 1, &NN, Args1, count);

		wfree(Args0, Args[0]);
		wfree(Args1, Args[1]);

		return count + 1 == L;
	}

	EXPORT bool TBAL(int N, short int * Map, short int ** Args) {
		if (N < 2 || Map[0] || Map[1])
			return false;

		wchar_t * Args0 = walloc(Args[0]);
		wchar_t * Args1 = walloc(Args[1]);

		stripLeading(Args0); // Удаляем начальные пробелы, если они есть

		int L = _wcslen(Args0);

		int NN = 0;
		int count = 0;

		delete[] getBalancedItem(Args0, &Args0, 1, &NN, Args1, count, true);

		wfree(Args0, Args[0]);
		wfree(Args1, Args[1]);

		return count + 1 == L;
	}

	EXPORT bool getBAL(int N, short int * Map, short int ** Args) {
		if (N < 3 || Map[0] || Map[1])
			return false;

		wchar_t * Args0 = walloc(Args[0]);
		wchar_t * Args1 = walloc(Args[1]);
		short int _Args2[50] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
		wchar_t * Args2 = (wchar_t *) _Args2;

		stripLeading(Args0); // Удаляем начальные пробелы, если они есть

		int L = _wcslen(Args0);

		int NN = 0;
		int count = 0;

		delete[] getBalancedItem(Args0, &Args0, 1, &NN, Args1, count);

		_swprintf(Args2, "%i", (count+1)-L);

		wfree(Args0, Args[0]);
		wfree(Args1, Args[1]);
		wchar_t * dest = (wchar_t *)Args[2];
		while (*dest++ = *Args2++);

		return true;
	}

	EXPORT bool set(int N, short int * Map, short int ** Args) {
		if (N < 2 || !Map[0] || Map[1])
			return false;

		short int * Args0 = Args[0];
		short int * Args1 = Args[1];

		while (*Args0++ = *Args1++);

		return true;
	}

}