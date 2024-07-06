#define _CRT_SECURE_NO_WARNINGS

#include <string.h>

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

extern "C" {

	// ������� �������� ��������� ��������, ��������� � ��������� ������ �� S
	void stripLeading(wchar_t * S) {
		int i = 0; // ������� ������� ��������
		int j = 0; // ������� �������� ��������
		// ���������� �������/���������/�������� �����
		while (S[i] == ' ' || S[i] == '\t' || S[i] == '\n' || S[i] == '\r')
			i++;
		if (i == 0) // ���� ������ �� ����������, �� �������
			return;
		while (S[i] != 0) { // ���� �� ����� �� ��������� �������� �������
			S[j] = S[i]; // �������� ������ ���� � ������
			i++;
			j++;
		}
		S[j] = 0; // ��������� ������ ������� ��������
	}

	enum { qtNone = 0, qtSingle, qtDouble }; // ��������� ������ ������ ������ (�������, ������ � ����������, ������ � �������� )

	/* ��� ��������� ����������� �������� �������� *count �������� ������ S. ���� ������
	S ���������, �� � ��� ���������������� ��������� ������ �� ������� lines. ���
	����� � ������� ���������� lines, ����� ����� ����� nL, ��������� �� ����� �������
	������ nline, ��������� K �� ����� ����� ������ S.
	*/
	void inc_count(wchar_t * S, wchar_t ** lines, int nL, int * nline, int * count, int * K) {
		(*count)++;
		while (*count >= *K && *nline < nL - 1) {
			(*nline)++;
			wcscat(S, L"\n");
			wcscat(S, lines[*nline]);
			*K = wcslen(S);
		}
	}

	/* ���������� ������� �������� *count ������ S ������ *K ����� �������, ����� ��
	��������� ���������������� �� ���� ����� ������ ���������, ���������������
	����� �� �������� �� ������ before. ������� ���������� 1 ��� 0 � �����������
	�� ������������ (������������������) ������� ������.
	�� ����� -- ���������� ������� ������ S, ����� ������ ����� lines, ����� ����� nL,
	��������� �� ����� ������� ������ nline.
	���������������� ��������� ����� ������������� � ���������� �������, �������
	������ ������� ����� �� "����������" � S, ���������� *nline.
	*/
	int trace(int * count, int * K, wchar_t * before, wchar_t * S, wchar_t ** lines, int nL,
		int * nline, bool use_triang) {
		wchar_t _quote = qtNone; // ������� ������� ����� ������
		int result = 1;

		if (wcslen(S) == 0) { // ���� ������� ������ �����
			inc_count(S, lines, nL, nline, count, K); // �� ���������� � ��� ��� ���� ������,
			// ���������� ������� *count �� �������
			(*count)--; // ���������� ������� *count �� ����� -- �� 1 ������ �����.
		}
		while (*count < *K && result && (_quote != qtNone || wcschr(before, S[*count]) == NULL)) {
			wchar_t C = S[*count];
			if (_quote != qtNone && C == '\\') { // ���������� ������������ ������ � ������
				inc_count(S, lines, nL, nline, count, K); // ������������� � ���������� �������
			}
			else if (C == '\'') { // ���� ���������� ��������
				if (_quote == qtSingle) _quote = qtNone; // ��� ��� ����������� ��������
				else if (_quote == qtNone) _quote = qtSingle; // ��� ����������� ��������
			}
			else if (C == '"') { // ���� ����������� �������
				if (_quote == qtDouble) _quote = qtNone; // ��� ���� ����������� �������
				else if (_quote == qtNone) _quote = qtDouble; // ��� ����������� �������
			}
			else if (_quote == qtNone && (C == '(' || C == '[' || C == '{' || use_triang && C == '<')) {
				// ���� �� �� ���������� ������ � ����������/�������� � ��������� ����������� ������
				inc_count(S, lines, nL, nline, count, K); // ���� � ���������� �������
				switch (C) { // ���������� ����� ������ �� ��������������� ����������� ������
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
			else if (_quote == qtNone && (C == ')' || C == ']' || C == '}' || use_triang && C == '>') && wcschr(before, C) == NULL)
				// ���� �� �� ���������� ������ � ����������/�������� � ���������������� ��������� ����������� ������
				result = 0; // �� ��� ������.

			if (result) // ���� ��� ������
				inc_count(S, lines, nL, nline, count, K); // �� ������������� � ���������� �������
		}
		// ���������, ����� �� �� �� ������������ ������� �� ������ before.
		result = result && *count < *K && wcschr(before, S[*count]) != NULL;
		return result;
	}

	/* ���������� ���������������� �� ���� ����� ������ ���������, ���������������
	����� �� �������� ������ terms. �� ����� -- ���������� ������� ������ S,
	����� ������ ����� lines, ����� ����� nL, ��������� �� ����� ������� ������ nline.
	���������������� ��������� ����� ������������� � ���������� �������, �������
	������ ������� ����� �� "����������" � S, ���������� *nline.
	count - ������� �������� � ������
	*/
	wchar_t * getBalancedItem(wchar_t * S, wchar_t ** lines, int nL, int * nline, wchar_t * terms,
		int & count, bool use_triang = false) {
		wchar_t * result = new wchar_t[65536]; // ���������

		int K; // ������� ����� ������ � ������
		int i;

		wcscpy(result, L"");

		if (wcslen(S) == 0) { // ���� ������� ������ �����
			inc_count(S, lines, nL, nline, &count, &K); // �� ���������� � ��� ��� ���� ������,
			// ���������� ������� count �� �������
			count--; // ���������� ������� count �� ����� -- �� 1 ������ �����.
		}

		K = wcslen(S);
		trace(&count, &K, terms, S, lines, nL, nline, use_triang);
		// �������� ������ count-1 �������� � ���������
		for (i = 0; i < count; i++)
			result[i] = S[i];
		result[count] = 0; // ��������� ������ � result ������� ��������
		// ������� �� S ������ count-1 ��������
		for (i = 0; S[count + i] != 0; i++)
			S[i] = S[count + i];
		S[i] = 0; // ��������� ������ S ������� ��������

		return result;
	}

	EXPORT bool BAL(int N, short int * Map, short int ** Args) {
		if (N < 2 || Map[0] || Map[1])
			return false;

		wchar_t * Args0 = walloc(Args[0]);
		wchar_t * Args1 = walloc(Args[1]);

		stripLeading(Args0); // ������� ��������� �������, ���� ��� ����

		int L = wcslen(Args0);

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

		stripLeading(Args0); // ������� ��������� �������, ���� ��� ����

		int L = wcslen(Args0);

		int NN = 0;
		int count = 0;

		delete[] getBalancedItem(Args0, &Args0, 1, &NN, Args1, count, true);

		wfree(Args0, Args[0]);
		wfree(Args1, Args[1]);

		return count + 1 == L;
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