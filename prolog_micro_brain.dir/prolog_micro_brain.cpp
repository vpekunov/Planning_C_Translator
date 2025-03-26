// (C) V.V.Pekunov, Just For Fun :)

// g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++11 -O4 -lm -lboost_system -lboost_filesystem -ldl

#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker, "/STACK:1000000000")

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <locale>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <chrono>
#include <regex>

#include <math.h>
#include <time.h>
#include <string.h>

#include "elements.h"
#include "prolog_micro_brain.h"

#ifdef _POSIX_PRIORITY_SCHEDULING
#include <sched.h>
#endif

const unsigned int eli = 0x8f;

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = (int)strlen(s) - 1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char * __ltoa(long long n, char s[], long long radix)
{
	long long i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = (char)(n % radix) + '0';   /* get next digit */
	} while ((n /= radix) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);

	return s;
}

#define __itoa __ltoa

const char * std_lib_pro = "prolog_micro_brain.pro";

const char * nameObjFactID = "$ObjFactID";
const char * nameObjLinkID = "$ObjLinkID";

const char * STD_INPUT = "#STD_INPUT";
const char * STD_OUTPUT = "#STD_OUTPUT";

using namespace std;

const int max_n = 14; // Максимальное количество 32-разрядных слов в ключе
const int min_n = 4; // Минимальное количество 32-разрядных слов в ключе

// S-блок
unsigned int SBlock[] = { 
0x09d0c479, 0x28c8ffe0, 0x84aa6c39, 0x9dad7287, 0x7dff9be3, 0xd4268361, 
0xc96da1d4, 0x7974cc93, 0x85d0582e, 0x2a4b5705, 0x1ca16a62, 0xc3bd279d, 
0x0f1f25e5, 0x5160372f, 0xc695c1fb, 0x4d7ff1e4, 0xae5f6bf4, 0x0d72ee46, 
0xff23de8a, 0xb1cf8e83, 0xf14902e2, 0x3e981e42, 0x8bf53eb6, 0x7f4bf8ac, 
0x83631f83, 0x25970205, 0x76afe784, 0x3a7931d4, 0x4f846450, 0x5c64c3f6, 
0x210a5f18, 0xc6986a26, 0x28f4e826, 0x3a60a81c, 0xd340a664, 0x7ea820c4, 
0x526687c5, 0x7eddd12b, 0x32a11d1d, 0x9c9ef086, 0x80f6e831, 0xab6f04ad, 
0x56fb9b53, 0x8b2e095c, 0xb68556ae, 0xd2250b0d, 0x294a7721, 0xe21fb253, 
0xae136749, 0xe82aae86, 0x93365104, 0x99404a66, 0x78a784dc, 0xb69ba84b, 
0x04046793, 0x23db5c1e, 0x46cae1d6, 0x2fe28134, 0x5a223942, 0x1863cd5b, 
0xc190c6e3, 0x07dfb846, 0x6eb88816, 0x2d0dcc4a, 0xa4ccae59, 0x3798670d, 
0xcbfa9493, 0x4f481d45, 0xeafc8ca8, 0xdb1129d6, 0xb0449e20, 0x0f5407fb, 
0x6167d9a8, 0xd1f45763, 0x4daa96c3, 0x3bec5958, 0xababa014, 0xb6ccd201, 
0x38d6279f, 0x02682215, (eli<<24)|0x376cd5, 0x092c237e, 0xbfc56593, 0x32889d2c, 
0x854b3e95, 0x05bb9b43, 0x7dcd5dcd, 0xa02e926c, 0xfae527e5, 0x36a1c330, 
0x3412e1ae, 0xf257f462, 0x3c4f1d71, 0x30a2e809, 0x68e5f551, 0x9c61ba44, 
0x5ded0ab8, 0x75ce09c8, 0x9654f93e, 0x698c0cca, 0x243cb3e4, 0x2b062b97, 
0x0f3b8d9e, 0x00e050df, 0xfc5d6166, 0xe35f9288, 0xc079550d, 0x0591aee8, 
0x8e531e74, 0x75fe3578, 0x2f6d829a, 0xf60b21ae, 0x95e8eb8d, 0x6699486b, 
0x901d7d9b, 0xfd6d6e31, 0x1090acef, 0xe0670dd8, 0xdab2e692, 0xcd6d4365, 
0xe5393514, 0x3af345f0, 0x6241fc4d, 0x460da3a3, 0x7bcf3729, 0x8bf1d1e0, 
0x14aac070, 0x1587ed55, 0x3afd7d3e, 0xd2f29e01, 0x29a9d1f6, 0xefb10c53, 
0xcf3b870f, 0xb414935c, 0x664465ed, 0x024acac7, 0x59a744c1, 0x1d2936a7, 
0xdc580aa6, 0xcf574ca8, 0x040a7a10, 0x6cd81807, 0x8a98be4c, 0xaccea063, 
0xc33e92b5, 0xd1e0e03d, 0xb322517e, 0x2092bd13, 0x386b2c4a, 0x52e8dd58, 
0x58656dfb, 0x50820371, 0x41811896, 0xe337ef7e, 0xd39fb119, 0xc97f0df6, 
0x68fea01b, 0xa150a6e5, 0x55258962, 0xeb6ff41b, 0xd7c9cd7a, 0xa619cd9e, 
0xbcf09576, 0x2672c073, 0xf003fb3c, 0x4ab7a50b, 0x1484126a, 0x487ba9b1, 
0xa64fc9c6, 0xf6957d49, 0x38b06a75, 0xdd805fcd, 0x63d094cf, 0xf51c999e, 
0x1aa4d343, 0xb8495294, 0xce9f8e99, 0xbffcd770, 0xc7c275cc, 0x378453a7, 
0x7b21be33, 0x397f41bd, 0x4e94d131, 0x92cc1f98, 0x5915ea51, 0x99f861b7, 
0xc9980a88, 0x1d74fd5f, 0xb0a495f8, 0x614deed0, 0xb5778eea, 0x5941792d, 
0xfa90c1f8, 0x33f824b4, 0xc4965372, 0x3ff6d550, 0x4ca5fec0, 0x8630e964, 
0x5b3fbbd6, 0x7da26a48, 0xb203231a, 0x04297514, 0x2d639306, 0x2eb13149, 
0x16a45272, 0x532459a0, 0x8e5f4872, 0xf966c7d9, 0x07128dc0, 0x0d44db62, 
0xafc8d52d, 0x06316131, 0xd838e7ce, 0x1bc41d00, 0x3a2e8c0f, 0xea83837e, 
0xb984737d, 0x13ba4891, 0xc4f8b949, 0xa6d6acb3, 0xa215cdce, 0x8359838b, 
0x6bd1aa31, 0xf579dd52, 0x21b93f93, 0xf5176781, 0x187dfdde, 0xe94aeb76, 
0x2b38fd54, 0x431de1da, 0xab394825, 0x9ad3048f, 0xdfea32aa, 0x659473e3, 
0x623f7863, 0xf3346c59, 0xab3ab685, 0x3346a90b, 0x6b56443e, 0xc6de01f8, 
0x8d421fc0, 0x9b0ed10c, 0x88f1a1e9, 0x54c1f029, 0x7dead57b, 0x8d7ba426, 
0x4cf5178a, 0x551a7cca, 0x1a9a5f08, 0xfcd651b9, 0x25605182, 0xe11fc6c3, 
0xb6fd9676, 0x337b3027, 0xb7c8eb14, 0x9e5fd030, 
0x6b57e354, 0xad913cf7, 0x7e16688d, 0x58872a69, 0x2c2fc7df, 0xe389ccc6, 
0x30738df1, 0x0824a734, 0xe1797a8b, 0xa4a8d57b, 0x5b5d193b, 0xc8a8309b, 
0x73f9a978, 0x73398d32, 0x0f59573e, 0xe9df2b03, 0xe8a5b6c8, 0x848d0704, 
0x98df93c2, 0x720a1dc3, 0x684f259a, 0x943ba848, 0xa6370152, 0x863b5ea3, 
0xd17b978b, 0x6d9b58ef, 0x0a700dd4, 0xa73d36bf, 0x8e6a0829, 0x8695bc14, 
0xe35b3447, 0x933ac568, 0x8894b022, 0x2f511c27, 0xddfbcc3c, 0x006662b6, 
0x117c83fe, 0x4e12b414, 0xc2bca766, 0x3a2fec10, 0xf4562420, 0x55792e2a, 
0x46f5d857, 0xceda25ce, 0xc3601d3b, 0x6c00ab46, 0xefac9c28, 0xb3c35047, 
0x611dfee3, 0x257c3207, 0xfdd58482, 0x3b14d84f, 0x23becb64, 0xa075f3a3, 
0x088f8ead, 0x07adf158, 0x7796943c, 0xfacabf3d, 0xc09730cd, 0xf7679969, 
0xda44e9ed, 0x2c854c12, 0x35935fa3, 0x2f057d9f, 0x690624f8, 0x1cb0bafd, 
0x7b0dbdc6, 0x810f23bb, 0xfa929a1a, 0x6d969a17, 0x6742979b, 0x74ac7d05, 
0x010e65c4, 0x86a3d963, 0xf907b5a0, 0xd0042bd3, 0x158d7d03, 0x287a8255, 
0xbba8366f, 0x096edc33, 0x21916a7b, 0x77b56b86, 0x951622f9, 0xa6c5e650, 
0x8cea17d1, 0xcd8c62bc, 0xa3d63433, 0x358a68fd, 0x0f9b9d3c, 0xd6aa295b, 
0xfe33384a, 0xc000738e, 0xcd67eb2f, 0xe2eb6dc2, 0x97338b02, 0x06c9f246, 
0x419cf1ad, 0x2b83c045, 0x3723f18a, 0xcb5b3089, 0x160bead7, 0x5d494656, 
0x35f8a74b, 0x1e4e6c9e, 0x000399bd, 0x67466880, 0xb4174831, 0xacf423b2, 
0xca815ab3, 0x5a6395e7, 0x302a67c5, 0x8bdb446b, 0x108f8fa4, 0x10223eda, 
0x92b8b48b, 0x7f38d0ee, 0xab2701d4, 0x0262d415, 0xaf224a30, 0xb3d88aba, 
0xf8b2c3af, 0xdaf7ef70, 0xcc97d3b7, 0xe9614b6c, 0x2baebff4, 0x70f687cf, 
0x386c9156, 0xce092ee5, 0x01e87da6, 0x6ce91e6a, 0xbb7bcc84, 0xc7922c20, 
0x9d3b71fd, 0x060e41c6, 0xd7590f15, 0x4e03bb47, 0x183c198e, 0x63eeb240, 
0x2ddbf49a, 0x6d5cba54, 0x923750af, 0xf9e14236, 0x7838162b, 0x59726c72, 
0x81b66760, 0xbb2926c1, 0x48a0ce0d, 0xa6c0496d, 0xad43507b, 0x718d496a, 
0x9df057af, 0x44b1bde6, 0x054356dc, 0xde7ced35, 0xd51a138b, 0x62088cc9, 
0x35830311, 0xc96efca2, 0x686f86ec, 0x8e77cb68, 0x63e1d6b8, 0xc80f9778, 
0x79c491fd, 0x1b4c67f2, 0x72698d7d, 0x5e368c31, 0xf7d95e2e, 0xa1d3493f, 
0xdcd9433e, 0x896f1552, 0x4bc4ca7a, 0xa6d1baf4, 0xa5a96dcc, 0x0bef8b46, 
0xa169fda7, 0x74df40b7, 0x4e208804, 0x9a756607, 0x038e87c8, 0x20211e44, 
0x8b7ad4bf, 0xc6403f35, 0x1848e36d, 0x80bdb038, 0x1e62891c, 0x643d2107, 
0xbf04d6f8, 0x21092c8c, 0xf644f389, 0x0778404e, 0x7b78adb8, 0xa2c52d53, 
0x42157abe, 0xa2253e2e, 0x7bf3f4ae, 0x80f594f9, 0x953194e7, 0x77eb92ed, 
0xb3816930, 0xda8d9336, 0xbf447469, 0xf26d9483, 0xee6faed5, 0x71371235, 
0xde425f73, 0xb4e59f43, 0x7dbe2d4e, 0x2d37b185, 0x49dc9a63, 0x98c39d98, 
0x1301c9a2, 0x389b1bbf, 0x0c18588d, 0xa421c1ba, 0x7aa3865c, 0x71e08558, 
0x3c5cfcaa, 0x7d239ca4, 0x0297d9dd, 0xd7dc2830, 0x4b37802b, 0x7428ab54, 
0xaeee0347, 0x4b3fbb85, 0x692f2f08, 0x134e578e, 0x36d9e0bf, 0xae8b5fcf, 
0xedb93ecf, 0x2b27248e, 0x170eb1ef, 0x7dc57fd6, 0x1e760f16, 0xb1136601, 
0x864e1b9b, 0xd7ea7319, 0x3ab871bd, 0xcfa4d76f, 0xe31bd782, 0x0dbeb469, 
0xabb96061, 0x5370f85d, 0xffb07e37, 0xda30d0fb, 0xebc977b6, 0x0b98b40f, 
0x3a4d0fe6, 0xdf4fc26b, 0x159cf22a, 0xc298d6e2, 0x2b78ef6a, 0x61a94ac0, 
0xab561187, 0x14eea0f0, 0xdf0d4164, 0x19af70ee 
};

// Циклическое вращение v влево на d бит
unsigned int rol(unsigned int v, unsigned int d) {
	d = d % 32;
	if (d == 0)
		return v;
	else {
		unsigned int first_part = v << d;
		unsigned int second_part = v >> (32 - d);
		
		return first_part + second_part;
	}
}

// Циклическое вращение v вправо на d бит
unsigned int ror(unsigned int v, unsigned int d) {
	d = d % 32;
	if (d == 0)
		return v;
	else {
		unsigned int first_part = v >> d;
		unsigned int second_part = v << (32 - d);
		
		return first_part + second_part;
	}
}

/* Вычисляем битовую маску для слова ключа */
unsigned int BitMask(unsigned int w) {
	unsigned int M = 0; // Маска-результат
	unsigned int seq_bit = w & 1; // Первый бит последовательности
	unsigned int d = 0; // Начало последовательности
	unsigned int i = 1; // Счетчик битов

	while (i < 32) {
		unsigned int this_bit = (w & (1 << i)) != 0;
		if (seq_bit != this_bit) {
			if (i-d >= 10) {
				for (unsigned int k = d+1; k < i-1; k++)
					M |= (1 << k);
			}
			seq_bit = this_bit;
			d = i;
		}
		i++;
	}
	if (i-d >= 10) {
		for (unsigned int k = d+1; k < i-1; k++)
			M |= (1 << k);
	}

	return M;
}

// Расширение ключа k до K
void expand_key(size_t n, unsigned int k[], unsigned int ExKey[40]) {
	const unsigned int B[4] = { 0xA4A8D57B, 0x5B5D193B, 0xC8A8309B, 0x73F9A978 };

	unsigned int T[15] = { 0 };

	for (int i = 0; i < n; i++) { // Переписываем ключ в T
		T[i] = k[i];
	}
	T[n] = (unsigned int)n;

	// Генерация слов расширенного ключа, по 10 на итерацию
	for (unsigned int j = 0; j < 4; j++) {
		// Преобразование T
		for (unsigned int i = 0; i < 15; i++)
			T[i] = T[i] ^ (rol(T[(i+8) % 15] ^ T[(i+13) % 15], 3) ^ (4*i + j));
		// 4 раунда перемешивания
		for (unsigned int k = 0; k < 4; k++)
			for (unsigned int i = 0; i < 15; i++)
				T[i] = rol(T[i] + SBlock[T[(i+14) % 15] & 0x1FF], 9);
		// Еще одно перемешивание
		for (unsigned int i = 0; i < 10; i++)
			ExKey[10*j + i] = T[(4*i) % 15];
	}
	// Коррекция ключа
	for (unsigned int i = 5; i <= 35; i += 2) {
		unsigned int j = ExKey[i] & 3;
		unsigned int w = ExKey[i] | 3;
		unsigned int M = BitMask(w);
		unsigned int p = rol(B[j], ExKey[i-1] & 0x1F);
		ExKey[i] = w ^ (p & M);
	}
}

// Функция E(in, key1, key2) = (L, M, R)
void E(unsigned int in, unsigned int key1, unsigned int key2, unsigned int &L, unsigned int &M, unsigned int &R) {
	M = in + key1;
	R = rol(in, 13) ^ key2;
	unsigned int i = M & 0x1FF;
	L = SBlock[i];
	R = rol(R, 5);
	unsigned int r = R & 0x1F;
	M = rol(M, r);
	L ^= R;
	R = rol(R, 5);
	L ^= R;
	r = R & 0x1F;
	L = rol(L, r);
}

// Прямое перемешивание -- кодирование
void code_direct(unsigned int _IN[4], unsigned int ExKey[40]) {
	for (unsigned int i = 0; i < 4; i++) { // Первое наложение ключа
		_IN[i] += ExKey[i];
	}
	for (unsigned int i = 0; i < 8; i++) { // 8 раундов перемешивания
		_IN[1] ^= SBlock[_IN[0] & 0xFF];
		_IN[1] += SBlock[256 + (_IN[0] >> 8) & 0xFF];
		_IN[2] += SBlock[(_IN[0] >> 16) & 0xFF];
		_IN[3] ^= SBlock[256 + (_IN[0] >> 24) & 0xFF];
		_IN[0] = ror(_IN[0], 24);
		if (i == 0 || i == 4)
			_IN[0] += _IN[3];
		if (i == 1 || i == 5)
			_IN[0] += _IN[1];
		// Вращаем массив D
		unsigned int buf = _IN[0];
		_IN[0] = _IN[1];
		_IN[1] = _IN[2];
		_IN[2] = _IN[3];
		_IN[3] = buf;
	}
}

// Кодирование -- ядро
void code_core(unsigned int _IN[4], unsigned int ExKey[40]) {
	// 16 раундов шифрования с ключом
	for (unsigned int i = 0; i < 16; i++) {
		unsigned int out1, out2, out3;
		E(_IN[0], ExKey[2*i+4], ExKey[2*i+5], out1, out2, out3);
		_IN[0] = rol(_IN[0], 13);
		_IN[2] += out2;
		if (i < 8) { // Прямое преобразование
			_IN[1] += out1;
			_IN[3] ^= out3;
		} else { // Обратное преобразование
			_IN[3] += out1;
			_IN[1] ^= out3;
		}
		// Вращаем массив D
		unsigned int buf = _IN[0];
		_IN[0] = _IN[1];
		_IN[1] = _IN[2];
		_IN[2] = _IN[3];
		_IN[3] = buf;
	}
}

// Обратное перемешивание -- кодирование
void code_reverse(unsigned int _IN[4], unsigned int ExKey[40]) {
	for (unsigned int i = 0; i < 8; i++) { // 8 раундов обратного перемешивания
		if (i == 2 || i == 6)
			_IN[0] -= _IN[3];
		if (i == 3 || i == 7)
			_IN[0] -= _IN[1];
		_IN[1] ^= SBlock[256 + (_IN[0] & 0xFF)];
		_IN[2] -= SBlock[(_IN[0] >> 24) & 0xFF];
		_IN[3] -= SBlock[256 + (_IN[0] >> 16) & 0xFF];
		_IN[3] ^= SBlock[(_IN[0] >> 8) & 0xFF];
		_IN[0] = rol(_IN[0], 24);
		// Вращаем массив D
		unsigned int buf = _IN[0];
		_IN[0] = _IN[1];
		_IN[1] = _IN[2];
		_IN[2] = _IN[3];
		_IN[3] = buf;
	}
	for (unsigned int i = 0; i < 4; i++) { // Вычитание ключа
		_IN[i] -= ExKey[36 + i];
	}
}

// Прямое перемешивание -- декодирование
void decode_direct(unsigned int _IN[4], unsigned int ExKey[40]) {
	for (unsigned int i = 0; i < 4; i++) { // Первое наложение ключа
		_IN[i] += ExKey[36 + i];
	}
	for (int i = 7; i >= 0; i--) { // 8 раундов перемешивания
		// Вращаем массив D
		unsigned int buf = _IN[3];
		_IN[3] = _IN[2];
		_IN[2] = _IN[1];
		_IN[1] = _IN[0];
		_IN[0] = buf;

		_IN[0] = ror(_IN[0], 24);

		_IN[3] ^= SBlock[(_IN[0] >> 8) & 0xFF];
		_IN[3] += SBlock[256 + (_IN[0] >> 16) & 0xFF];
		_IN[2] += SBlock[(_IN[0] >> 24) & 0xFF];
		_IN[1] ^= SBlock[256 + (_IN[0] & 0xFF)];
		if (i == 2 || i == 6)
			_IN[0] += _IN[3];
		if (i == 3 || i == 7)
			_IN[0] += _IN[1];
	}
}

// Декодирование -- ядро
void decode_core(unsigned int _IN[4], unsigned int ExKey[40]) {
	// 16 раундов дешифрования с ключом
	for (int i = 15; i >= 0; i--) {
		unsigned int out1, out2, out3;

		// Вращаем массив D
		unsigned int buf = _IN[3];
		_IN[3] = _IN[2];
		_IN[2] = _IN[1];
		_IN[1] = _IN[0];
		_IN[0] = buf;

		_IN[0] = ror(_IN[0], 13);

		E(_IN[0], ExKey[2*i+4], ExKey[2*i+5], out1, out2, out3);

		_IN[2] -= out2;

		if (i < 8) { // Прямое преобразование
			_IN[1] -= out1;
			_IN[3] ^= out3;
		} else { // Обратное преобразование
			_IN[3] -= out1;
			_IN[1] ^= out3;
		}
	}
}

// Обратное перемешивание -- декодирование
void decode_reverse(unsigned int _IN[4], unsigned int ExKey[40]) {
	for (int i = 7; i >= 0; i--) { // 8 раундов обратного перемешивания
		// Вращаем массив D
		unsigned int buf = _IN[3];
		_IN[3] = _IN[2];
		_IN[2] = _IN[1];
		_IN[1] = _IN[0];
		_IN[0] = buf;

		if (i == 0 || i == 4)
			_IN[0] -= _IN[3];
		if (i == 1 || i == 5)
			_IN[0] -= _IN[1];

		_IN[0] = rol(_IN[0], 24);

		_IN[3] ^= SBlock[256 + (_IN[0] >> 24) & 0xFF];
		_IN[2] -= SBlock[(_IN[0] >> 16) & 0xFF];
		_IN[1] -= SBlock[256 + (_IN[0] >> 8) & 0xFF];
		_IN[1] ^= SBlock[_IN[0] & 0xFF];
	}
	for (unsigned int i = 0; i < 4; i++) { // Вычитание ключа
		_IN[i] -= ExKey[i];
	}
}

string escape(const string & s) {
	string result;

	int i = 0;
	while (i < s.length()) {
		if (s[i] == '\\') {
			result += s[i];
			result += s[i];
		}
		else
			result += s[i];
		i++;
	}

	return result;
}

string unescape(const string & s) {
	string result;

	size_t i = 0;
	while (i < s.length()) {
		if (i + 1 < s.length() && s[i] == '\\') {
			switch (s[i + 1]) {
			case 'r': result += "\r"; break;
			case 'n': result += "\n"; break;
			case 't': result += "\t"; break;
			case '0': result += "\0"; break;
			default: result += s[i + 1];
			}
			i++;
		}
		else
			result += s[i];
		i++;
	}

	return result;
}

frame_item::~frame_item() {
	int it = 0;
	while (it < vars.size()) {
		if (vars[it].ptr)
			vars[it].ptr->free();
		it++;
	}
	if (names)
		free(names);
	if (deleted)
		free(deleted);
}


tframe_item::~tframe_item() {
	lock();
	free(info_vars);
	unlock();
}

tframe_item* frame_item::tcopy(context* CTX, interpreter* INTRP, bool import_globs) {
	tframe_item* result = new tframe_item(names_capacity, (unsigned int)vars.size()+5);
	result->names_length = names_length;
	memmove(result->names, names, names_length * sizeof(char));
	long long d = &result->names[0] - &names[0];
	result->vars = vars;
	for (mapper& m : result->vars) {
		m.ptr = m.ptr ? m.ptr->const_copy(CTX, this) : NULL;
		m._name += d;
	}
	memset(result->info_vars, 0, vars.size() * sizeof(tframe_item::var_info));
	if (CTX && import_globs /* && (CTX->THR || CTX->forked()) */) {
		bool locked = INTRP->GLOCK.try_lock();
		std::map<std::string, value*>::iterator it = INTRP->GVars.begin();
		while (it != INTRP->GVars.end()) {
			if (it->first.length() && it->first[0] != '&') {
				string new_name = it->first;
				new_name.insert(0, 1, '*');
				bool use_local_copy = false;
				// find(new_name.c_str(), use_local_copy);
				// if (!use_local_copy)
				result->set(true, CTX, new_name.c_str(), it->second);
			}
			it++;
		}
		if (locked) INTRP->GLOCK.unlock();
	}
	memset(result->info_vars, 0, vars.size() * sizeof(tframe_item::var_info));
	return result;
}

tthread* thread_pool::get_thread(int _id, context* CTX) {
	guard.lock();
	if (available.size() == 0) {
		available.insert(new tthread(_id, CTX));
	}
	else
		(*available.begin())->reinit(_id, CTX);
	tthread* result = *available.begin();
	available.erase(result);
	used.insert(result);
	guard.unlock();
	return result;
}

void thread_pool::free_thread(tthread* t) {
	guard.lock();
	used.erase(t);
	available.insert(t);
	guard.unlock();
}

thread_pool::~thread_pool() {
	for (tthread* t : available)
		delete t;
}

tthread::tthread(int _id, context* CTX) : CONTEXT(NULL) {
	reinit(_id, CTX);

	allow_stop.store(false);

	runner = new std::thread(&tthread::body, this);
}

void tthread::reinit(int _id, context* CTX) {
	this->_id = _id;
	result = false;
	stopped.store(false);

	if (CTX) {
		std::lock_guard<std::mutex> lk(cv_m);
		CONTEXT.store(CTX);
		cv.notify_one();
	}
	else
		CONTEXT.store(NULL);

	set_terminated(false);
}

tthread::~tthread() {
	allow_stop.store(true);
	{
		std::lock_guard<std::mutex> lk(cv_m);
		CONTEXT.store((context*)1);
		cv.notify_one();
	}
	runner->join();
	delete runner;
}

void tthread::body() {
	do {
		tframe_item* OLD_FRAME = NULL;
		set_stopped(false);
		do {
			set_terminated(false);
			while (OLD_FRAME == CONTEXT.load()->FRAME.load())
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			// delete OLD_FRAME;
			OLD_FRAME = CONTEXT.load()->FRAME.load();
			// Process
			predicate_item* first = CONTEXT.load()->starting;
			vector<value*>* first_args = CONTEXT.load()->prolog->accept(CONTEXT.load(), OLD_FRAME, first);
			set_result(CONTEXT.load()->prolog->process(CONTEXT.load(), false, first->get_parent(), first, OLD_FRAME, &first_args));
			if (first_args) {
				for (int j = 0; j < first_args->size(); j++)
					first_args->at(j)->free();
				delete first_args;
			}

			{
				std::lock_guard<std::mutex> lk(cvf_m);
				set_stopped(true);
				cvf.notify_one();
			}

			std::unique_lock<std::mutex> lk(cvs_m);
			while (is_stopped())
				cvs.wait(lk);
		} while (!is_terminated());

		{
			std::lock_guard<std::mutex> lk(cvt_m);
			set_terminated(false);
			cvt.notify_one();
		}

		std::unique_lock<std::mutex> lk(cv_m);
		while (NULL == CONTEXT.load()) {
			cv.wait(lk);
		}
	} while (!allow_stop);
}

void frame_item::register_fact_group(bool _locked, context* CTX, string& fact, journal* J) {
	bool found = false;
	fact.insert(0, 1, '!');
	int it = find(fact.c_str(), found);
	if (!found) {
		set(_locked, CTX, fact.c_str(), NULL);
		it = find(fact.c_str(), found);
	}
}

void frame_item::unregister_fact_group(bool _locked, context* CTX, string& fact) {
	bool found = false;
	fact.insert(0, 1, '!');
	int it = find(fact.c_str(), found);
	if (found)
		unset(_locked, CTX, fact.c_str());
}

void tframe_item::register_fact_group(bool _locked, context* CTX, string& fact, journal* J) {
	bool locked = !_locked && mutex.try_lock();
	bool found = false;
	fact.insert(0, 1, '!');
	int it = find(fact.c_str(), found);
	if (!found) {
		set(locked, CTX, fact.c_str(), NULL);
		it = find(fact.c_str(), found);
	}
	if (!info_vars[it].first_writes || info_vars[it].first_writes > J->first_write) {
		info_vars[it].first_writes = J->first_write;
		if (!info_vars[it].last_writes)
			info_vars[it].last_writes = info_vars[it].first_writes;
	}
	if (!info_vars[it].last_writes || info_vars[it].last_writes < J->last_write) {
		info_vars[it].last_writes = J->last_write;
		if (!info_vars[it].first_writes)
			info_vars[it].first_writes = info_vars[it].last_writes;
	}
	if (!info_vars[it].first_reads || info_vars[it].first_reads > J->first_read) {
		info_vars[it].first_reads = J->first_read;
		if (!info_vars[it].last_reads)
			info_vars[it].last_reads = info_vars[it].first_reads;
	}
	if (!info_vars[it].last_reads || info_vars[it].last_reads < J->last_read) {
		info_vars[it].last_reads = J->last_read;
		if (!info_vars[it].first_reads)
			info_vars[it].first_reads = info_vars[it].last_reads;
	}
	if (locked) unlock();
}

void tframe_item::unregister_fact_group(bool _locked, context* CTX, string& fact) {
	bool locked = !_locked && mutex.try_lock();
	frame_item::unregister_fact_group(locked, CTX, fact);
	if (locked) unlock();
}

class string_atomizer {
	map<string, unsigned int> hash;
	vector<const string *> table;
	bool forking;
	std::mutex locker;
public:
	string_atomizer() { forking = false; }
	void set_forking(bool v) { forking = v; }
	unsigned int get_atom(const string & s) {
		if (s.length() == 1)
			return (unsigned char)s[0];
		else if (s.length() == 2)
			return (((unsigned char)s[1]) << 8) + (unsigned char)s[0];
		else {
			if (forking) locker.lock();
			unsigned int result = 0;
			map<string, unsigned int>::iterator it = hash.find(s);
			if (it != hash.end())
				result = it->second;
			else {
				if (table.size() == table.capacity()) {
					table.reserve(table.size() + 2000);
				}
				pair<map<string, unsigned int>::iterator, bool> itt =
					hash.insert(pair<string, unsigned int>(s, 0));
				table.push_back(&itt.first->first);
				itt.first->second = (unsigned int)(65536 + table.size() - 1);
				result = itt.first->second;
			}
			if (forking) locker.unlock();
			return result;
		}
	}
	const string get_string(unsigned int atom) {
		if (atom < 256) {
			char buf[2] = { (char) atom, 0 };
			return string(buf);
		}
		else if (atom < 65536) {
			char buf[3] = { (char)(atom & 0xFF), (char)(atom >> 8), 0 };
			return string(buf);
		}
		else {
			if (forking) locker.lock();
			string result = *table[atom - 65536];
			if (forking) locker.unlock();
			return result;
		}
	}
};

string_atomizer atomizer;

class any : public value {
public:
	any() : value() { }

	virtual void escape_vars(context * CTX, frame_item * ff) { }

	virtual value * fill(context * CTX, frame_item * vars) { return this; }
	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) { return new any(); }
	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		return true;
	}
	virtual bool defined() {
		return false;
	};

	virtual string to_str(bool simple = false) { return "_"; }
};

class var : public value {
	string name;
public:
	var(const string & _name) : value(), name(_name) { }

	virtual void escape_vars(context * CTX, frame_item * ff) {
		value * v = ff->get(false, CTX, name.c_str());
		if (v) {
			v->escape_vars(CTX, ff);
		}
		ff->escape(name);
	}

	virtual value * fill(context * CTX, frame_item * vars) {
		value * v = vars->get(false, CTX, name.c_str());
		if (v)
			return v->const_copy(CTX, vars);
		else {
			return this;
		}
	}

	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) {
		value * v = f->get(false, CTX, name.c_str(), unwind);
		if (v)
			return v->const_copy(CTX, f);
		else
			return new var(name);
	}

	virtual void write(basic_ostream<char> * outs, bool simple = false) {
		(*outs) << name;
	}

	virtual const string & get_name() { return name; }

	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		if (dynamic_cast<var *>(from) || dynamic_cast<any *>(from))
			return true;
		value * v = ff->get(false, CTX, name.c_str());
		if (v)
			return v->unify(CTX, ff, from);
		else
			ff->set(false, CTX, name.c_str(), from);
		return true;
	}
	
	virtual bool defined() {
		return false;
	};

	virtual string to_str(bool simple = false) { return "__VAR__" + name; }
};

class int_number : public value {
	friend class float_number;
private:
	long long v;
public:
	int_number(long long _v) : value(), v(_v) { }

	virtual void escape_vars(context * CTX, frame_item * ff) {	}

	virtual value * fill(context * CTX, frame_item * vars) { return this; }
	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) { return new int_number(v); }
	virtual bool unify(context * CTX, frame_item * ff, value * from);
	virtual bool defined() {
		return true;
	};

	virtual double get_value() { use(); return 1.0*v; }

	virtual string to_str(bool simple = false) {
		char buf[65] = { 0 };

		return string(__ltoa(v, buf, 10));
	}

	void inc() { v++; }
	void dec() { v--; }
};

class float_number : public value {
	friend class int_number;
private:
	double v;
public:
	float_number(double _v) : value(), v(_v) { }

	virtual void escape_vars(context * CTX, frame_item * ff) {	}

	virtual value * fill(context * CTX, frame_item * vars) { return this; }
	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) { return new float_number(v); }
	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		if (dynamic_cast<any *>(from)) return true;
		if (dynamic_cast<var *>(from)) { ff->set(false, CTX, ((var *)from)->get_name().c_str(), this); return true; }
		if (dynamic_cast<float_number *>(from))
			return v == ((float_number *)from)->v;
		else if (dynamic_cast<int_number *>(from))
			return v == ((int_number *)from)->v;
		else
			return false;
	}
	virtual bool defined() {
		return true;
	};

	virtual double get_value() { use();  return v; }

	virtual string to_str(bool simple = false) {
		char buf[65];

		sprintf(buf, "%lf", v);
		return string(buf);
	}

	void inc() { v++; }
	void dec() { v--; }
};

bool int_number::unify(context * CTX, frame_item * ff, value * from) {
	if (dynamic_cast<any *>(from)) return true;
	if (dynamic_cast<var *>(from)) { ff->set(false, CTX, ((var *)from)->get_name().c_str(), this); return true; }
	if (dynamic_cast<int_number *>(from))
		return v == ((int_number *)from)->v;
	else if (dynamic_cast<float_number *>(from))
		return v == ((float_number *)from)->v;
	else
		return false;
}

class term : public value {
private:
	unsigned int name;
	vector<value *> args;
	signed char cached_defined;
public:
	term(const string & _name, const int init_refs = 1) : value() {
		this->refs = init_refs;
		name = atomizer.get_atom(_name);
		cached_defined = 1;
	}

	term(const term & src) {
		this->refs = 1;
		this->name = src.name;
		this->args = vector<value *>();
		cached_defined = 1;
	}

	virtual ~term() { }

	virtual void change_name(const string & _name) {
		name = atomizer.get_atom(_name);
	}

	virtual void free() {
		refs--;
		for (int i = 0; i < args.size(); i++)
			if (args[i]->get_refs() >= refs)
				args[i]->free();
		if (refs == 0)
			delete this;
	}

	virtual void use() {
		refs++;
		for (int i = 0; i < args.size(); i++)
			args[i]->use();
	}

	virtual void escape_vars(context * CTX, frame_item * ff) {
		for (int i = 0; i < args.size(); i++)
			args[i]->escape_vars(CTX, ff);
	}

	virtual const string get_name() { return atomizer.get_string(name); }

	virtual const vector<value *> & get_args() { return args; }

	virtual value * fill(context * CTX, frame_item * vars) {
		cached_defined = 1;
		for (int i = 0; i < args.size(); i++) {
			value * old = args[i];
			args[i] = args[i]->fill(CTX, vars);
			if (args[i] != old) old->free();
			if (cached_defined && args[i] && !args[i]->defined())
				cached_defined = 0;
		}
		return this;
	}

	virtual void add_arg(context * CTX, frame_item * f, value * v, int unwind = 0) {
		args.push_back(v->const_copy(CTX, f, unwind));
		if (cached_defined && !args[args.size() - 1]->defined())
			cached_defined = 0;
	}

	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) {
		term * result = new term(*this);
		for (int i = 0; i < args.size(); i++)
			result->add_arg(CTX, f, args[i], unwind);
		return result;
	}

	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		cached_defined = -1;
		if (dynamic_cast<any *>(from)) return true;
		if (dynamic_cast<var *>(from)) { ff->set(false, CTX, ((var *)from)->get_name().c_str(), this); return true; }
		if (dynamic_cast<term *>(from)) {
			term * v2 = ((term *)from);
			if (name != v2->name || args.size() != v2->args.size())
				return false;
			for (int i = 0; i < args.size(); i++)
				if (!args[i]->unify(CTX, ff, v2->args[i]))
					return false;
			return true;
		}
		else
			return false;
	}
	virtual bool defined() {
		if (cached_defined >= 0)
			return cached_defined == 1;
		cached_defined = 1;
		for (int i = 0; i < args.size(); i++)
			if (!args[i]->defined()) {
				cached_defined = 0;
				return false;
			}
		return true;
	};

	virtual string to_hex(char SEP) {
		string NAME = atomizer.get_string(name);
		string result;
		for (unsigned char C : NAME) {
			if (C == (unsigned char)SEP)
				result += SEP;
			else {
				int h = C >> 4;
				int l = C & 0x0F;
				if (h > 9) result += (char)('A' + h - 10);
				else result += (char)('0' + h);
				if (l > 9) result += (char)('A' + l - 10);
				else result += (char)('0' + l);
			}
		}
		return result;
	}

	virtual string from_hex(char SEP) {
		string NAME = atomizer.get_string(name);
		string result;

		auto HexDigit = [](char H)->unsigned int {
			if (H >= '0' && H <= '9')
				return H - '0';
			else if (H >= 'A' && H <= 'F')
				return H - 'A' + 10;
			else if (H >= 'a' && H <= 'f')
				return H - 'a' + 10;
			else
				return 0;
		};

		for (size_t i = 0; i < NAME.length(); i++) {
			if (NAME[i] == SEP)
				result += SEP;
			else if (i + 1 < NAME.length()) {
				result += (char)(HexDigit(NAME[i]) * 16 + HexDigit(NAME[i + 1]));
				i++;
			}
			else {
				cout << "from_hex ERROR : '" + NAME + "' can't parse!" << endl;
				exit(1343);
			}
		}
		return result;
	}

	virtual string to_str(bool simple = false) {
		string result = atomizer.get_string(name);
		if (args.size() > 0) {
			result += "(";
			for (int i = 0; i < args.size() - 1; i++) {
				result += args[i]->to_str(simple);
				result += ",";
			}
			result += args[args.size() - 1]->to_str(simple);
			result += ")";
		}
		return result;
	}

	virtual string escape_specials(const string & src, bool double_slashes = true) {
		string result;

		int i = 0;
		if (double_slashes)
			while (i < src.length()) {
				switch (src[i]) {
					case '\r': result += "\\\\r"; break;
					case '\n': result += "\\\\n"; break;
					case '\t': result += "\\\\t"; break;
					case '\0': result += "\\\\0"; break;
					default: result += src[i];
				}
				i++;
			}
		else
			while (i < src.length()) {
				switch (src[i]) {
				case '\r': result += "\\r"; break;
				case '\n': result += "\\n"; break;
				case '\t': result += "\\t"; break;
				case '\0': result += "\\0"; break;
				default: result += src[i];
				}
				i++;
			}

		return result;
	}

	virtual string export_str(bool simple = false, bool double_slashes = true) {
		string result = escape_specials(atomizer.get_string(name), double_slashes);
		if (result.length() == 0)
			result = "''";
		else {
			bool valid_atom = islower(result[0]);
			for (int i = 1; valid_atom && i < result.length(); i++)
				if (!isalnum(result[i]) && result[i] != '_')
					valid_atom = false;
			if (!valid_atom) {
				char buf[16384];
				sprintf(buf, "'%s'", result.c_str());
				result = buf;
			}
		}
		if (args.size() > 0) {
			result += "(";
			for (int i = 0; i < args.size() - 1; i++) {
				result += args[i]->export_str(simple, double_slashes);
				result += ",";
			}
			result += args[args.size() - 1]->export_str(simple, double_slashes);
			result += ")";
		}
		return result;
	}
};

class indicator : public value {
private:
	string name;
	int arity;
public:
	indicator(const string & _name, int _arity) : value(), name(_name), arity(_arity) { }

	virtual void escape_vars(context * CTX, frame_item * ff) {	}

	virtual const string & get_name() { return name; }

	virtual int get_arity() { return arity; }

	virtual value * fill(context * CTX, frame_item * vars) {
		return this;
	}

	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) {
		return new indicator(name, arity);
	}
	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		if (dynamic_cast<any *>(from)) return true;
		if (dynamic_cast<var *>(from)) { ff->set(false, CTX, ((var *)from)->get_name().c_str(), this); return true; }
		if (dynamic_cast<indicator *>(from)) {
			indicator * v2 = ((indicator *)from);
			return name == v2->name && arity == v2->arity;
		}
		else
			return false;
	}
	virtual bool defined() {
		return true;
	};

	virtual string to_str(bool simple = false) {
		string result = name;

		char buf[65];
		result += "/";
		result += __itoa(arity, buf, 10);
		
		return result;
	}
};

class list : public value {
	friend class predicate_item_nth;

	stack_container<value *> val;
	bool is_of_chars;
	string chars;
	value * tag;
	signed char cached_defined;
public:
	list(const stack_container<value *> & v, value * _tag) : value(), tag(_tag) {
		is_of_chars = true;
		chars = "";
		for (int i = 0; is_of_chars && i < v.size(); i++) {
			term * t = dynamic_cast<term *>(v[i]);
			if (t && t->get_args().size() == 0) {
				string s = t->get_name();
				if (s.length() != 1) {
					is_of_chars = false;
					chars = "";
				} else {
					chars += s[0];
				}
			} else {
				is_of_chars = false;
				chars = "";
			}
		}
		cached_defined = (tag == NULL || tag->defined()) ? 1 : 0;
		if (is_of_chars) {
			for (int i = 0; i < v.size(); i++)
				v[i]->free();
		}
		else {
			val = v;
			if (cached_defined)
				for (value * vv : v)
					if (!vv->defined()) {
						cached_defined = false;
						break;
					}
		}
	}

	list(const string & v, value * _tag) : value(), tag(_tag) {
		is_of_chars = true;
		cached_defined = (tag == NULL || tag->defined()) ? 1 : 0;
		chars = v;
	}

	virtual ~list() { }

	virtual void free() {
		for (value * v : val)
			v->free();
		if (tag) tag->free();
		refs--;
		if (refs == 0)
			delete this;
	}

	virtual void use() {
		refs++;
		for (value * v : val)
			v->use();
		if (tag) tag->use();
	}

	virtual bool of_chars() { return is_of_chars; }
	virtual const string & get_chars() { return chars; }
	virtual void convert_non_chars(context * CTX) {
		if (is_of_chars) {
			is_of_chars = false;
			for (char s : chars)
				val.push_back(new term(string(1,s), refs));
			chars = "";
		}
	}

	virtual void escape_vars(context * CTX, frame_item * ff) {
		for (value * v : val)
			v->escape_vars(CTX, ff);
		if (tag)
			tag->escape_vars(CTX, ff);
	}

	int size() {
		int result = (int)(is_of_chars ? chars.size() : val.size());
		if (tag)
			if (dynamic_cast<list *>(tag))
				result += ((list *)tag)->size();
			else
				result++;
		return result;
	}

	value * get_last(context * CTX) {
		if (tag)
			if (dynamic_cast<list *>(tag))
				return ((list *)tag)->get_last(CTX);
			else {
				tag->use();
				return tag;
			}
		else if (is_of_chars && chars.size() == 0 || !is_of_chars && val.size() == 0)
			return NULL;
		else if (is_of_chars) {
			return new term(string(1, chars[chars.length()-1]), refs);
		} else {
			stack_container<value *>::iterator it = val.end();

			(*(--it))->use();

			return *it;
		}
	}

	value * get_nth(int n, bool inc_ref) {
		if (n < 1) return NULL;

		if (is_of_chars && n <= chars.size() || !is_of_chars && n <= val.size()) {
			if (is_of_chars) {
				return new term(string(1, chars[n-1]), refs);
			} else {
				stack_container<value *>::iterator it = val.begin() + (size_t)(n - 1);
				if (inc_ref) (*it)->use();
				return *it;
			}
		}
		else
			if (tag)
				if (dynamic_cast<list *>(tag))
					return ((list *)tag)->get_nth(
						(int)(is_of_chars ? n - chars.size() : n - val.size()),
						inc_ref);
				else {
					if (inc_ref) tag->use();
					return tag;
				}
			else
				return NULL;
	}

	bool set_nth(int n, value * v) {
		if (n < 1) return false;

		if (is_of_chars && n <= chars.size() || !is_of_chars && n <= val.size()) {
			if (is_of_chars) {
				term* t = dynamic_cast<term*>(v);
				if (t && t->get_name().length() == 1) {
					chars[(size_t)(n - 1)] = t->get_name()[0];
					return true;
				}
				else
					return false;
			}
			else {
				stack_container<value*>::iterator it = val.begin() + (size_t)(n - 1);
				(*it)->free();
				(*it) = v;
				v->use();

				cached_defined = -1;
				if (v && !v->defined())
					cached_defined = 0;

				return true;
			}
		}
		else
			if (tag) {
				cached_defined = -1;
				if (v && !v->defined())
					cached_defined = 0;

				if (dynamic_cast<list*>(tag))
					return ((list*)tag)->set_nth((int)(is_of_chars ? n - chars.size() : n - val.size()), v);
				else {
					tag->free();
					tag = v;
					v->use();
					return true;
				}
			}
			else
				return false;
	}

	void iterate(std::function<void(value *)> check) {
		if (is_of_chars) {
			term * t = new term("");
			for (char s : chars) {
				t->change_name(string(1,s));
				check(t);
			}
			t->free();
		} else {
			stack_container<value *>::iterator it = val.begin();
			while (it != val.end()) {
			
				check(*it);
				it++;
			}
		}
		if (tag)
			if (dynamic_cast<list *>(tag))
				((list *)tag)->iterate(check);
			else
				check(tag);
	}

	void split(context * CTX, frame_item * f, int p, value * & L1, value * & L2) {
		if (is_of_chars && !tag) {
			string S1 = chars.substr(0, p);
			string S2 = chars.substr(p);
			L1 = new list(S1, NULL);
			L2 = new list(S2, NULL);
		} else {
			stack_container<value *> S, S1, S2;
			get(CTX, f, &S);

			stack_container<value *>::iterator it = S.begin();
			S1.reserve(p);
			for (int i = 0; i < p; i++)
				S1.push_back((*it++)->const_copy(CTX, f));
			S2.reserve(S.size() - p);
			for (int i = p; i < S.size(); i++)
				S2.push_back((*it++)->const_copy(CTX, f));
			L1 = new list(S1, NULL);
			L2 = new list(S2, NULL);
		}
	}

	void const_split(context * CTX, frame_item * f, int p, value * & L1, value * & L2) {
		if (is_of_chars && !tag) {
			string S1 = chars.substr(0, p);
			string S2 = chars.substr(p);
			L1 = new list(S1, NULL);
			L2 = new list(S2, NULL);
		}
		else {
			if (!defined()) return split(CTX, f, p, L1, L2);
			stack_container<value *> S, S1, S2;
			get(CTX, f, &S);

			stack_container<value *>::iterator it = S.begin();
			S1.reserve(p);
			for (int i = 0; i < p; i++)
				S1.push_back((*it++)->const_copy(CTX, f));
			S2.reserve(S.size() - p);
			for (int i = p; i < S.size(); i++)
				S2.push_back((*it++)->const_copy(CTX, f));
			L1 = new list(S1, NULL);
			L2 = new list(S2, NULL);
		}
	}

	list * from(context * CTX, frame_item * f, stack_container<value *>::iterator starting) {
		list * result = new list(stack_container<value *>(), NULL);
		while (starting != val.end())
		{
			result->add(CTX, (*starting)->const_copy(CTX, f));
			starting++;
		}
		if (tag) result->set_tag(tag->copy(CTX, f));
		return result;
	}

	list * from(context * CTX, frame_item * f, string::iterator starting) {
		list * result = new list(string(starting, chars.end()), NULL);
		if (tag) result->set_tag(tag->copy(CTX, f));
		return result;
	}

	list * const_from(context * CTX, frame_item * f, stack_container<value *>::iterator starting) {
		if (!defined()) return from(CTX, f, starting);
		list * result = new list(stack_container<value *>(), NULL);
		while (starting != val.end())
		{
			(*starting)->use();
			result->add(CTX, *starting);
			starting++;
		}
		if (tag) {
			tag->use();
			result->set_tag(tag);
		}
		return result;
	}

	list * const_from(context * CTX, frame_item * f, string::iterator starting) {
		if (!defined()) return from(CTX, f, starting);
		list * result = new list(string(starting, chars.end()), NULL);
		if (tag) {
			tag->use();
			result->set_tag(tag);
		}
		return result;
	}

	virtual value * fill(context * CTX, frame_item * vars) {
		cached_defined = 1;
		if (!is_of_chars) {
			stack_container<value *>::iterator it = val.begin();
			for (; it != val.end(); it++) {
				value * old = *it;
				*it = (*it)->fill(CTX, vars);
				if (*it != old) old->free();
				if (cached_defined && *it && !(*it)->defined())
					cached_defined = 0;
			}
		}
		if (tag) {
			value * old = tag;
			tag = tag->fill(CTX, vars);
			if (old && old != tag) old->free();
			if (cached_defined && tag && !tag->defined())
				cached_defined = 0;
		}
		return this;
	}

	virtual list * append(context * CTX, frame_item * f, list * L2) {
		::list * result = NULL;
		if (is_of_chars && !tag && L2->of_chars()) {
			result = new ::list(chars + L2->get_chars(), NULL);
		} else {
			result = ((list *)copy(CTX, f));
			if (is_of_chars) convert_non_chars(CTX);
			if (L2->of_chars()) {
				for (char s : L2->get_chars())
					result->add(CTX, new term(string(1, s)));
			} else
				for (value * v : L2->val) {
					result->add(CTX, v->const_copy(CTX, f));
					if (cached_defined && !v->defined())
						cached_defined = 0;
				}
		}
		if (L2->tag) {
			if (cached_defined && !L2->tag->defined())
				cached_defined = 0;
			if (dynamic_cast<::list*>(L2->tag))
				return result->append(CTX, f, ((list*)L2->tag));
			else
				result->add(CTX, L2->tag->copy(CTX, f));
		}
		return result;
	}

	virtual value * copy(context * CTX, frame_item * f, int unwind = 0) {
		if (is_of_chars)
			return new ::list(chars, tag ? tag->copy(CTX, f) : NULL);
		else {
			stack_container<value *> new_val;
			new_val.reserve(val.size());
			for (value * v : val)
				new_val.push_back(v->const_copy(CTX, f));
			return new ::list(new_val, tag ? tag->copy(CTX, f) : NULL);
		}
	}

	virtual void add(context * CTX, value * v) {
		if (cached_defined && v && !v->defined())
			cached_defined = 0;

		if (tag)
			if (dynamic_cast<list *>(tag))
				((list *)tag)->add(CTX, v);
			else {
				std::cout << "Adding to non-list tag?!" << endl;
				exit(1);
			}
		else {
			term * t = dynamic_cast<term *>(v);
			if (t && t->get_args().size() == 0) {
				if (is_of_chars) {
					string s = t->get_name();
					if (s.length() == 1)
						chars += s;
					else {
						convert_non_chars(CTX);
						val.push_back(v);
					}
				} else {
					val.push_back(v);
				}
			} else {
				convert_non_chars(CTX);
				val.push_back(v);
			}
		}
	}

	virtual void set_tag(value * new_tag) {
		if (cached_defined && new_tag && !new_tag->defined())
			cached_defined = 0;

		if (tag) tag->free();
		if (dynamic_cast<list *>(new_tag) && ((list *)new_tag)->size() == 0)
			new_tag = NULL;
		tag = new_tag;
		if (new_tag) new_tag->use();
	}

	virtual bool get(context * CTX, frame_item * f, stack_container<value *> * dest) {
		dest->clear();
		if (is_of_chars) {
			for (char s : chars)
				dest->push_back(new term(string(1,s)));
		} else
			for (value * v : val)
				dest->push_back(v->const_copy(CTX, f));
		if (tag) {
			if (dynamic_cast<list *>(tag)) {
				stack_container<value *> ltag;
				if (((list *)tag)->get(CTX, f, &ltag)) {
					for (value * v : ltag)
						dest->push_back(v->const_copy(CTX, f));
					return true;
				}
				else
					return false;
			}
			dest->push_back(tag->copy(CTX, f));
			return true;
		}
		else return true;
	}

	virtual bool unify(context * CTX, frame_item * ff, value * from) {
		cached_defined = -1;
		if (dynamic_cast<any *>(from)) return true;
		if (dynamic_cast<var *>(from)) {
			ff->set(false, CTX, ((var *)from)->get_name().c_str(), this);
			return true;
		}
		if (dynamic_cast<list *>(from)) {
			value * _from = (list *)from;
			stack_container<value *>::iterator _from_it = ((list *)_from)->val.begin();
			string::iterator _from_it_s = ((list *)_from)->chars.begin();
			value * _to = this;
			stack_container<value *>::iterator _to_it = ((list *)_to)->val.begin();
			string::iterator _to_it_s = ((list *)_to)->chars.begin();

			while (_from && _to) {
				bool advanced = false;
				if (dynamic_cast<list *>(_from))
					while (dynamic_cast<list *>(_from) && (
						((list *)_from)->is_of_chars && _from_it_s == ((list *)_from)->chars.end() ||
						!((list *)_from)->is_of_chars && _from_it == ((list *)_from)->val.end()
							)) {
						_from = ((list *)_from)->tag;
						if (dynamic_cast<list *>(_from)) {
							_from_it_s = ((list *)_from)->chars.begin();
							_from_it = ((list *)_from)->val.begin();
						}
						advanced = true;
					}
				if (dynamic_cast<list *>(_to))
					while (dynamic_cast<list *>(_to) && (
						((list *)_to)->is_of_chars && _to_it_s == ((list *)_to)->chars.end() ||
						!((list *)_to)->is_of_chars && _to_it == ((list *)_to)->val.end()
						)) {
							_to = ((list *)_to)->tag;
							if (dynamic_cast<list *>(_to)) {
								_to_it_s = ((list *)_to)->chars.begin();
								_to_it = ((list *)_to)->val.begin();
							}
							advanced = true;
						}
				if (dynamic_cast<any *>(_from) || dynamic_cast<any *>(_to))
					return true;
				if (dynamic_cast<var *>(_from))
					if (dynamic_cast<list *>(_to))
						if (((list *)_to)->of_chars())
							return _from->unify(CTX, ff, ((list *)_to)->const_from(CTX, ff, _to_it_s));
						else
							return _from->unify(CTX, ff, ((list *)_to)->const_from(CTX, ff, _to_it));
					else if (_to)
						return _from->unify(CTX, ff, _to);
					else
						return _from->unify(CTX, ff, new ::list(stack_container<value *>(), NULL));
				if (dynamic_cast<var *>(_to))
					if (dynamic_cast<list *>(_from))
						if (((list *)_from)->of_chars())
							return _to->unify(CTX, ff, ((list *)_from)->const_from(CTX, ff, _from_it_s));
						else
							return _to->unify(CTX, ff, ((list *)_from)->const_from(CTX, ff, _from_it));
					else if (_from)
						return _to->unify(CTX, ff, _from);
					else
						return _to->unify(CTX, ff, new ::list(stack_container<value *>(), NULL));
				if (dynamic_cast<list *>(_from) && dynamic_cast<list *>(_to)) {
					if (((list *)_from)->of_chars() && ((list *)_to)->of_chars())
						if ((*_to_it_s++)!=(*_from_it_s++))
							return false;
						else
							advanced = true;
					else if (((list *)_from)->of_chars() != ((list *)_to)->of_chars()) {
						if (((list *)_from)->of_chars()) {
							term * fr = new term(string(1, *_from_it_s++));
							if (!(*_to_it++)->unify(CTX, ff, fr)) {
								fr->free();
								return false;
							} else
								advanced = true;
							fr->free();
						} else {
							term * t = new term(string(1, *_to_it_s++));
							if (!(*_from_it++)->unify(CTX, ff, t)) {
								t->free();
								return false;
							}
							else
								advanced = true;
							t->free();
						}
					} else
						if (!(*_to_it++)->unify(CTX, ff, *_from_it++))
							return false;
						else
							advanced = true;
				}
				if (!advanced)
					return _to->unify(CTX, ff, _from);
			}

			return !_from && !_to;
		} else
			return false;
	}
	virtual bool defined() {
		if (cached_defined >= 0)
			return cached_defined == 1;
		cached_defined = 1;
		if (!is_of_chars)
			for (value * v : val)
				if (!v->defined()) {
					cached_defined = 0;
					return false;
				}
		if (tag) {
			bool result = tag->defined();
			cached_defined = result ? 1 : 0;
			return result;
		}
		return true;
	};

	virtual string make_str() {
		string result;
		if (is_of_chars) {
			result = chars;
		}
		else
			for (value * v : val)
				result += v->make_str();
		if (tag)
			result += tag->make_str();
		return result;
	}

	virtual string to_str(bool simple = false) {
		string result;

		int k = 0;

		if (!simple) result += "[";
		if (is_of_chars) {
			for (char s : chars) {
				result += s;
				k++;
				if (k < chars.size() || tag && !(dynamic_cast<list *>(tag) && dynamic_cast<list *>(tag)->size() == 0))
					result += ",";
			}
		} else
			for (value * v : val) {
				result += v->to_str(false);
				k++;
				if (k < val.size() || tag && !(dynamic_cast<list *>(tag) && dynamic_cast<list *>(tag)->size() == 0))
					result += ",";
			}
		if (tag) {
			result += tag->to_str(true);
		}
		if (!simple) result += "]";

		return result;
	}

	virtual string export_str(bool simple = false, bool double_slashes = true) {
		string result;

		int k = 0;

		if (!simple) result += "[";
		if (is_of_chars) {
			for (char s : chars) {
				result += string("'") + s + string("'");
				k++;
				if (k < chars.size() || tag && !(dynamic_cast<list *>(tag) && dynamic_cast<list *>(tag)->size() == 0))
					result += ",";
			}
		}
		else
			for (value * v : val) {
				result += v->export_str(false, double_slashes);
				k++;
				if (k < val.size() || tag && !(dynamic_cast<list *>(tag) && dynamic_cast<list *>(tag)->size() == 0))
					result += ",";
			}
		if (tag) {
			result += tag->export_str(true, double_slashes);
		}
		if (!simple) result += "]";

		return result;
	}
};

context::context(bool locals_in_forked, bool transactable_facts, predicate_item* forker, int RESERVE, context* parent, tframe_item* tframe, predicate_item* starting, predicate_item* ending, interpreter* prolog) {
	this->parent = parent;
	this->locals_in_forked = locals_in_forked;
	this->transactable_facts = transactable_facts;

	if (tframe && parent)
		INIT = tframe->tcopy(parent, prolog);
	else
		INIT = NULL;

	if (!transactable_facts && parent != NULL) {
		DBLOCK = parent->DBLOCK;
		DB = parent->DB;
		DBJournal = parent->DBJournal;
	}
	else {
		DBLOCK = new std::mutex();
		DB = new map< string, std::atomic<vector<term*>*>>();
		if (parent) {
			std::unique_lock<std::mutex> lock(*parent->DBLOCK);
			map< string, std::atomic<vector<term*>*>>::iterator itd = parent->DB->begin();
			while (itd != parent->DB->end()) {
				if (itd->second) {
					(*DB)[itd->first] = new vector<term*>(*itd->second);
					for (term* v : *itd->second)
						v->use();
				}
				itd++;
			}
			lock.unlock();
		}
		DBJournal = new map<string, std::atomic<journal*>>();
	}

	rollback = false;

	CALLS.reserve(RESERVE);
	FRAMES.reserve(RESERVE);
	CTXS.reserve(RESERVE);
	NEGS.reserve(RESERVE);
	_FLAGS.reserve(RESERVE);
	PARENT_CALLS.reserve(RESERVE);
	PARENT_CALL_VARIANT.reserve(RESERVE);
	CLAUSES.reserve(RESERVE);
	// FLAGS;
	LEVELS.reserve(RESERVE);
	TRACE.reserve(RESERVE);
	TRACEARGS.reserve(RESERVE);
	TRACERS.reserve(RESERVE);
	ptrTRACE.reserve(RESERVE);

	THR = NULL;
	FRAME.store(tframe);
	this->forker = forker;
	this->starting = starting;
	this->ending = ending;
	this->prolog = prolog;
}

context* context::add_page(bool locals_in_forked, bool transactable_facts, predicate_item* forker, tframe_item* f, predicate_item* starting, predicate_item* ending, interpreter* prolog) {
	std::unique_lock<std::mutex> plock(pages_mutex);

	context* result = new context(locals_in_forked, transactable_facts, forker, 100, this, f, starting, ending, prolog);

	CONTEXTS.push_back(result);

	result->THR = prolog->THREAD_POOL->get_thread((int)(CONTEXTS.size() - 1), result);

	plock.unlock();

	return result;
}

void context::register_db_read(const std::string& iid) {
	map<string, std::atomic<journal*>>::iterator it = DBJournal->find(iid);
	if (it == DBJournal->end()) {
		(*DBJournal)[iid] = new journal();
		it = DBJournal->find(iid);
	}
	it->second.load()->register_read();
}

void context::register_db_write(const std::string& iid, jTypes t, value* data, int position, journal * src) {
	map<string, std::atomic<journal*>>::iterator it = DBJournal->find(iid);
	if (it == DBJournal->end()) {
		(*DBJournal)[iid] = new journal();
		it = DBJournal->find(iid);
	}
	it->second.load()->register_write(t, data, position, src);
}

void context::apply_transactional_db_to_parent(const std::string & fact) {
	map<string, std::atomic<journal*>>::iterator its = DBJournal->find(fact);
	if (its != DBJournal->end()) {
		journal* SRC = its->second;
		map<string, std::atomic<vector<term*>*>>::iterator it = parent->DB->find(fact);
		if (it == parent->DB->end()) {
			(*parent->DB)[fact] = new vector<term*>();
			it = parent->DB->find(fact);
		}
		// Apply journal
		for (journal_item* jlog : SRC->log) {
			if (jlog->type == jInsert) {
				parent->register_db_write(fact, jInsert, jlog->data, jlog->position, SRC);
				it->second.load()->insert(it->second.load()->begin() + jlog->position, (term*)jlog->data);
				jlog->data->use(); // to prevent free in ~journal_item()
			}
			else if (jlog->type == jDelete) {
				parent->register_db_write(fact, jDelete, jlog->data, jlog->position, SRC);
				it->second.load()->erase(it->second.load()->begin() + jlog->position);
				jlog->data->use(); // to prevent free in ~journal_item()
			}
			else {
				cout << "Internal error : unknown DB journal record type!" << endl;
				exit(1700);
			}
		}
		// Clear journal
		delete SRC;
		DBJournal->erase(fact);
	}
}

bool context::join(bool sequential_mode, int K, frame_item* f, interpreter* INTRP, int & sequential, vector<frame_item *> * rest) {
	std::unique_lock<std::mutex> lock(pages_mutex);
	if (CONTEXTS.size() == 0) {
		lock.unlock();
		return true;
	}

	context* C = this;
	while (C && !C->THR)
		C = C->parent;
	bool forked = C && C->THR;

	CONTEXTS.push_back(this);

	sequential = sequential_mode ? 0 : -1;

	int joined = 0;
	int success = 0;
	bool stopped_by_true = false;
	vector<bool> joineds(CONTEXTS.size(), false);
	std::set<string> names;
	vector<std::set<string>> lnames(CONTEXTS.size(), std::set<string>());

	f->add_local_names(false, lnames[CONTEXTS.size() - 1]);

	names = lnames[CONTEXTS.size() - 1];

	do {
		vector<bool> stoppeds(CONTEXTS.size(), false);
		vector<bool> rollback(CONTEXTS.size(), false);
		int stopped = (int)std::count(joineds.begin(), joineds.end(), true);
		bool mainlined = !joineds[CONTEXTS.size() - 1];
		if (mainlined) {
			stoppeds[CONTEXTS.size() - 1] = true;
			stopped++;
		}
		f->register_facts(false, this, lnames[CONTEXTS.size() - 1]);
		names.insert(lnames[CONTEXTS.size() - 1].begin(), lnames[CONTEXTS.size() - 1].end());
		while (stopped < CONTEXTS.size()) {
			for (int i = 0; i < CONTEXTS.size(); i++)
				if (!joineds[i] && !stoppeds[i] && !rollback[i]) {
					{
						std::unique_lock<std::mutex> lk(CONTEXTS[i]->THR->get_finished_mutex());
						while (!CONTEXTS[i]->THR->is_stopped())
							CONTEXTS[i]->THR->get_finished_var().wait(lk);
					}
					rollback[i] = CONTEXTS[i]->rollback;
					stoppeds[i] = !rollback[i];
					if (stoppeds[i]) {
						CONTEXTS[i]->FRAME.load()->add_local_names(CONTEXTS[i]->locals_in_forked, lnames[i]);
						if (CONTEXTS[i]->transactable_facts)
							CONTEXTS[i]->FRAME.load()->register_facts(false, CONTEXTS[i], lnames[i]);
						names.insert(lnames[i].begin(), lnames[i].end());
					}
					stopped++;
				}
		}
		stopped -= (int)std::count(rollback.begin(), rollback.end(), true);
		// In not joineds search for winners
		vector<vector<int>> M(CONTEXTS.size(), vector<int>(CONTEXTS.size(), 0));
		std::set<string> conflictors;
		for (const string& vname : names) {
			// Conflict Matrix
			for (int i = 0; i < CONTEXTS.size()-2; i++)
				for (int j = i + 1; j < CONTEXTS.size()-1; j++)
					if (stoppeds[i] && stoppeds[j] && (lnames[i].find(vname) != lnames[i].end() && lnames[j].find(vname) != lnames[j].end())) {
						clock_t cri, fwi, fri, lwi, lri;
						CONTEXTS[i]->FRAME.load()->statistics(vname, cri, fwi, fri, lwi, lri);
						clock_t crj = 0, fwj = 0, frj = 0, lwj = 0, lrj = 0;
						if (j == CONTEXTS.size() - 1 && dynamic_cast<tframe_item*>(f) == NULL)
							/* M[i][j]++ */;
						else {
							if (j == CONTEXTS.size() - 1)
								dynamic_cast<tframe_item*>(f)->statistics(vname, crj, fwj, frj, lwj, lrj);
							else
								CONTEXTS[j]->FRAME.load()->statistics(vname, crj, fwj, frj, lwj, lrj);
							if (fwi || fwj) {
								if (fwi && fwj) {
									if (fri && fri <= fwi || frj && frj <= fwj) {
										M[i][j]++;
										conflictors.insert(vname);
									}
								}
								else if (fwi) {
									if ((lwi >= crj) && lrj) {
										M[i][j]++;
										conflictors.insert(vname);
									}
								}
								else {
									if ((lwj >= cri) && lri) {
										M[i][j]++;
										conflictors.insert(vname);
									}
								}
							}
						}
					}
		}
		bool changed;
		do {
			changed = false;
			for (int i = 0; i < CONTEXTS.size(); i++)
				for (int j = i + 1; j < CONTEXTS.size(); j++)
					if (M[i][j])
						for (int k = j + 1; k < CONTEXTS.size(); k++)
							if (M[j][k] && M[i][k] == 0) {
								M[i][k] = 1;
								changed = true;
							}
		} while (changed);
		// Decide
		int first_winner = mainlined ? (int)(CONTEXTS.size() - 1) : -1;
		std::set<int> other_winners;
		int first = first_winner < 0 ? 0 : first_winner;
		int last = first_winner < 0 ? (int)(CONTEXTS.size() - 1) : first_winner;
		for (int i = first; i <= last; i++)
			if (stoppeds[i]) {
				std::set<int> conflicted;
				conflicted.insert(i);
				for (int k = 0; k < i; k++)
					if (M[k][i])
						conflicted.insert(k);
				for (int k = i + 1; k < CONTEXTS.size(); k++)
					if (M[i][k])
						conflicted.insert(k);
				std::set<int> parallels;
				for (int j = 0; j < CONTEXTS.size(); j++) {
					if (i != j && stoppeds[j] && conflicted.find(j) == conflicted.end())
						parallels.insert(j);
				}
				int candidate = i;
				if (parallels.size() > 1) {
					clock_t min_time = 0;
					if (!mainlined) parallels.insert(i);
					for (const string& vname : names) {
						for (int j : parallels) {
							if (stoppeds[j] && lnames[j].find(vname) != lnames[j].end()) {
								clock_t cr, fw, fr, lw, lr;
								CONTEXTS[j]->FRAME.load()->statistics(vname, cr, fw, fr, lw, lr);
								if (fw && (!min_time || fw < min_time && fw >= cr)) {
									candidate = j;
									min_time = fw;
								}
							}
						}
					}
					if (!mainlined) parallels.erase(i);
					for (int j = 0; j < CONTEXTS.size(); j++)
						for (int k = j + 1; k < CONTEXTS.size(); k++)
							if (M[j][k]) {
								parallels.erase(j);
								parallels.erase(k);
							}
				}
				if (mainlined) {
					parallels.insert(candidate);
					parallels.erase(i);
					parallels.insert(-i);
					candidate = i;
				}
				else {
					parallels.insert(i);
					parallels.erase(candidate);
					parallels.insert(-candidate);
				}
				if ((sequential < 0 || candidate == sequential || parallels.find(sequential) != parallels.end() || parallels.find(-sequential) != parallels.end()) &&
					parallels.size() > other_winners.size()) {
					other_winners = parallels;
					first_winner = candidate;
				}
			}
		if (first_winner < 0) {
			if (sequential >= 0)
				first_winner = sequential;
			else {
				clock_t min_time = 0;
				for (const string& vname : conflictors) {
					for (int i = 0; i < CONTEXTS.size(); i++)
						if (stoppeds[i] && lnames[i].find(vname) != lnames[i].end()) {
							clock_t cr, fw, fr, lw, lr;
							CONTEXTS[i]->FRAME.load()->statistics(vname, cr, fw, fr, lw, lr);
							if (fw && (!min_time || fw < min_time && fw >= cr)) {
								first_winner = i;
								min_time = fw;
							}
						}
				}
				for (int i = 0; first_winner < 0 && i < CONTEXTS.size(); i++)
					if (stoppeds[i])
						first_winner = i;
			}
			if (first_winner >= 0) {
				other_winners.erase(first_winner);
				other_winners.insert(-first_winner);
			}
		}
		f->unregister_facts(false, this);
		if (mainlined)
		{
			other_winners.erase(first_winner);
			other_winners.erase(-first_winner);
			joineds[CONTEXTS.size() - 1] = true;
			stoppeds[CONTEXTS.size() - 1] = false;
			success++;
			joined++;
		}
		if (sequential >= 0 && (other_winners.size() == 0 || abs(*other_winners.begin()) != sequential)) {
			other_winners.clear();
			if (!rollback[sequential])
				other_winners.insert(sequential);
		}
		// Set vars by threads with non-zero first_writes
		stopped_by_true = false;
		for (int _winner : other_winners) {
			int winner = abs(_winner);
			if (sequential >= 0 && (rollback[winner] || winner != sequential)) {
				for (int rollb = sequential; rollb < CONTEXTS.size()-1; rollb++) {
					stoppeds[rollb] = false;
					rollback[rollb] = true;
					other_winners.erase(rollb);
					other_winners.erase(-rollb);
					stopped--;
				}
				break;
			}
			for (const string& vname : names)
				if (lnames[winner].find(vname) != lnames[winner].end() && CONTEXTS[winner]->FRAME.load()->first_write(vname))
				{
					if (vname[0] == '!') {
						if (DB != CONTEXTS[winner]->DB) {
							string fact = vname.substr(1);
							std::unique_lock<std::mutex> dblock(*DBLOCK);
							std::unique_lock<std::mutex> wdblock(*CONTEXTS[winner]->DBLOCK);
							CONTEXTS[winner]->apply_transactional_db_to_parent(fact);
							wdblock.unlock();
							dblock.unlock();
						}
					}
					else if (vname[0] == '*' || CONTEXTS[winner]->THR->get_result())
					{
						f->lock();
						value* old = f->get(true, this, vname.c_str());
						value* cur = CONTEXTS[winner]->FRAME.load()->get(false, CONTEXTS[winner], vname.c_str());
						if (cur)
							if (old && (vname.length() == 0 || vname[0] != '*')) {
								if (!old->unify(this, f, cur))
									CONTEXTS[winner]->THR->set_result(false);
							}
							else
								f->set(true, this, vname.c_str(), cur);
						f->unlock();
					}
				}
			if (sequential >= 0) {
				sequential++;
				if (CONTEXTS[winner]->THR->get_result()) {
					for (int rollb = sequential; rollb < CONTEXTS.size()-1; rollb++) {
						stoppeds[rollb] = false;
						rollback[rollb] = true;
						other_winners.erase(rollb);
						other_winners.erase(-rollb);
						stopped--;
					}
					stopped_by_true = true;
					break;
				}
			}
		}
		// Join first_winner && other_winners
		for (int i = 0; i < CONTEXTS.size(); i++)
			if (stoppeds[i] || rollback[i]) {
				if (rollback[i] || other_winners.find(i) == other_winners.end() && other_winners.find(-i) == other_winners.end()) {
					if (CONTEXTS[i]->transactable_facts) { // Undo facts
						std::unique_lock<std::mutex> lock(*DBLOCK);
						std::unique_lock<std::mutex> ilock(*CONTEXTS[i]->DBLOCK);
						// Delete journal, including deleted nodes
						map<string, std::atomic<journal*>>::iterator itj = CONTEXTS[i]->DBJournal->begin();
						while (itj != CONTEXTS[i]->DBJournal->end()) {
							delete itj->second;
							itj++;
						}
						CONTEXTS[i]->DBJournal->clear();
						vector<term*> Q;
						// Clear local DB
						map< string, std::atomic<vector<term*>*>>::iterator itd = CONTEXTS[i]->DB->begin();
						while (itd != CONTEXTS[i]->DB->end()) {
							if (itd->second) {
								for (term* v : *itd->second)
									Q.push_back(v);
								delete itd->second;
							}
							itd++;
						}
						CONTEXTS[i]->DB->clear();
						// Reload DB
						itd = DB->begin();
						while (itd != DB->end()) {
							if (itd->second) {
								(*CONTEXTS[i]->DB)[itd->first] = new vector<term*>(*itd->second);
								for (term* v : *itd->second)
									v->use();
							}
							itd++;
						}
						for (term* v : Q) {
							v->free();
						}
						ilock.unlock();
						lock.unlock();
					}
					// CONTEXTS[i]->REFRESH(sequential_mode, f, this, INTRP);
					if (stopped_by_true) {
						CONTEXTS[i]->THR->set_context(NULL);
						CONTEXTS[i]->THR->set_terminated(true);
						{
							std::lock_guard<std::mutex> lk(CONTEXTS[i]->THR->get_stopped_mutex());
							CONTEXTS[i]->THR->set_stopped(false);
							CONTEXTS[i]->THR->get_stopped_var().notify_one();
						}
						{
							std::unique_lock<std::mutex> lk(CONTEXTS[i]->THR->get_terminated_mutex());
							while (CONTEXTS[i]->THR->is_terminated())
								CONTEXTS[i]->THR->get_terminated_var().wait(lk);
						}
						joineds[i] = true;
						if (CONTEXTS[i]->THR->get_result())
							success++;
						joined++;
					}
					else {
						FRAMES_TO_DELETE.push(CONTEXTS[i]->FRAME.load());
						// if (sequential >= 0) {
							tframe_item* newf = CONTEXTS[i]->INIT.load()->tcopy(this, INTRP);
							newf->forced_import_transacted_globs(this, f);
							CONTEXTS[i]->FRAME.store(newf);
						// }
						// else
						//	CONTEXTS[i]->FRAME.store(f->tcopy(this, INTRP, false));
						CONTEXTS[i]->set_rollback(false);
						{
							std::lock_guard<std::mutex> lk(CONTEXTS[i]->THR->get_stopped_mutex());
							CONTEXTS[i]->THR->set_stopped(false);
							CONTEXTS[i]->THR->get_stopped_var().notify_one();
						}
					}
				}
				else {
					CONTEXTS[i]->THR->set_context(NULL);
					CONTEXTS[i]->THR->set_terminated(true);
					{
						std::lock_guard<std::mutex> lk(CONTEXTS[i]->THR->get_stopped_mutex());
						CONTEXTS[i]->THR->set_stopped(false);
						CONTEXTS[i]->THR->get_stopped_var().notify_one();
					}
					{
						std::unique_lock<std::mutex> lk(CONTEXTS[i]->THR->get_terminated_mutex());
						while (CONTEXTS[i]->THR->is_terminated())
							CONTEXTS[i]->THR->get_terminated_var().wait(lk);
					}
					joineds[i] = true;
					if (CONTEXTS[i]->THR->get_result())
						success++;
					joined++;
				}
			}
	} while (joined < CONTEXTS.size());

	joined--;
	success--;
	CONTEXTS.pop_back();

	bool result =
		(sequential >= 0 && stopped_by_true) ||
		(sequential < 0 && (K < 0 && success == CONTEXTS.size() || K >= 0 && success >= K));

	prolog->GLOCK.lock();
	f->lock();
	for (const string& vname : names)
		if (vname[0] != '!')
		{
			value* v = f->get(true, this, vname.c_str());
			for (int i = 0; i < CONTEXTS.size(); i++)
				CONTEXTS[i]->FRAME.load()->set(false, CONTEXTS[i], vname.c_str(), NULL);
			if (!forked && v && vname.length() && vname[0] == '*') {
				string src_name = vname.substr(1);
				std::map<std::string, value*>::iterator it = prolog->GVars.find(src_name);
				if (it != prolog->GVars.end()) {
					it->second->free();
				}
				prolog->GVars[src_name] = v->const_copy(this, f);
			}
		}
	f->unlock();
	prolog->GLOCK.unlock();

	int ctx = 0;
	bool cutted = false;
	for (context* C : CONTEXTS) {
		tthread* t = C->THR;
		if (ctx < sequential) {
			for (int i = 0; i < C->cut_query.size(); i++) {
				if (C->cut_query[i](prolog, this) && parent)
					cut_query.push_back(C->cut_query[i]);
				cutted = true;
			}
		}
		else if (stopped_by_true)
			if (rest) {
				rest->push_back(C->INIT.load());
				C->INIT.store(NULL);
			}
		delete C;
		prolog->THREAD_POOL->free_thread(t);
		ctx++;
	}
	if (cutted) {
		sequential = (int) CONTEXTS.size();
		if (rest) {
			for (auto ff : *rest)
				delete ff;
			rest->clear();
		}
	}
	CONTEXTS.clear();

	lock.unlock();
	return result;
}

void context::clearDBJournals() {
	map<string, std::atomic<journal*>>::iterator itj = DBJournal->begin();
	while (itj != DBJournal->end()) {
		delete itj->second;
		itj++;
	}
	DBJournal->clear();
}

context::~context() {
	for (context* C : CONTEXTS)
		delete C;
	delete INIT;
	if (transactable_facts || parent == NULL) {
		map< string, std::atomic<vector<term*>*>>::iterator itd = DB->begin();
		while (itd != DB->end()) {
			for (term* v : *itd->second)
				v->free();
			delete itd->second;
			itd++;
		}
		delete DBLOCK;
		delete DB;

		map<string, std::atomic<journal*>>::iterator itj = DBJournal->begin();
		while (itj != DBJournal->end()) {
			delete itj->second;
			itj++;
		}
		delete DBJournal;
	}
	// delete THR;
	for (tframe_item * f : FRAMES_TO_DELETE)
		if (f != FRAME.load())
			delete f;
	if (FRAME.load())
		delete FRAME.load();
}

void predicate_item_user::bind(bool starring) {
	predicate_item::bind(starring);
	if (!starring)
		if (prolog->PREDICATES.find(id) == prolog->PREDICATES.end())
			user_p = NULL;
		else
			user_p = prolog->PREDICATES[id];
}

bool predicate_item_user::is_not_pure(std::set<string>& work_set) {
	if (user_p) {
		if (work_set.find(get_id()) != work_set.end())
			return false;
		work_set.insert(get_id());
		for (int i = 0; i < user_p->num_clauses(); i++) {
			clause* c = user_p->get_clause(i);
			for (int j = 0; j < c->num_items(); j++)
				if (c->get_item(j)->is_not_pure(work_set))
					return true;
		}
		return false;
	}
	else
		return false;
}

generated_vars * predicate_item_user::generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
	generated_vars * result = new generated_vars();
	if (user_p)
		for (int i = 0; i < user_p->num_clauses(); i++) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
	else {
		string iid = id;
		term * dummy = NULL;
		if (id.length() > 0 && id[0] >= 'A' && id[0] <= 'Z') {
			dummy = dynamic_cast<term *>(f->get(false, CTX, id.c_str()));
			if (dummy) {
				dummy = dynamic_cast<term *>(dummy->const_copy(CTX, f, 1));
				iid = dummy->get_name();
			}
		}
		else {
			dummy = new term(id);
			for (int j = 0; j < positional_vals->size(); j++) {
				dummy->add_arg(CTX, f, positional_vals->at(j));
			}
		}
		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		map<string, std::atomic<vector<term*>*>>::iterator it = CTX->DB->find(iid);
		if (dummy && it != CTX->DB->end()) {
			CTX->register_db_read(iid);
			vector<term *> * terms = it->second;
			for (int i = 0; i < terms->size(); i++) {
				frame_item * ff = f->copy(CTX);
				term * _dummy = (term *)dummy->const_copy(CTX, ff);
				if (_dummy->unify(CTX, ff, terms->at(i)))
					result->push_back(ff);
				else
					delete ff;
				_dummy->free();
			}
			dummy->free();
		}
		else {
			std::cout << "Predicate [" << id << "] is neither standard nor dynamic!" << endl;
			exit(500);
		}
		lock.unlock();

		if (result && once && result->size() > 1) {
			for (int i = 1; i < result->size(); i++)
				delete result->at(i);
			result->resize(1);
		}

		if (result && result->size() == 0) {
			delete result;
			result = NULL;
		}
	}

	return result;
}

bool predicate_item_user::processing(context * CONTEXT, bool line_neg, int variant, generated_vars * variants, vector<value *> ** positional_vals, frame_item * up_f, context * up_c) {
	predicate_item * next = get_next(variant);

	frame_item* f = dynamic_cast<tframe_item *>(up_f) ? new tframe_item(32, 8, CONTEXT, up_f) : new frame_item(32, 8, CONTEXT, up_f);

	/**/
	if (variant == 0) {
		CONTEXT->PARENT_CALLS.push(this);
		CONTEXT->PARENT_CALL_VARIANT.push(0);
		CONTEXT->CLAUSES.push(get_parent());
		CONTEXT->CALLS.push(next);
		CONTEXT->FRAMES.push(up_f->copy(CONTEXT));
		CONTEXT->CTXS.push(up_c);
		CONTEXT->NEGS.push(line_neg);
		CONTEXT->_FLAGS.push((is_once() ? ::once_flag : 0) + (is_call() ? call_flag : 0));
	}

	CONTEXT->PARENT_CALL_VARIANT.pop();
	CONTEXT->PARENT_CALL_VARIANT.push(variant);

	bool yes = false;

	if (prolog->retrieve(CONTEXT, f, user_p->get_clause(variant), *positional_vals, true)) {
		yes = user_p->get_clause(variant)->num_items() == 0;

		if (yes) {
			vector<value *> * v = NULL;
			yes = prolog->process(CONTEXT, neg, user_p->get_clause(variant), NULL, f, &v);
		}
		else {
			predicate_item * first = user_p->get_clause(variant)->get_item(0);
			vector<value *> * first_args = prolog->accept(CONTEXT, f, first);
			yes = prolog->process(CONTEXT, neg, user_p->get_clause(variant), first, f, &first_args);
			if (first_args) {
				for (int j = 0; j < first_args->size(); j++)
					first_args->at(j)->free();
				delete first_args;
			}
		}
	}
	else {
		yes = false;
	}

	if ((yes || (!variants || !variants->has_variant(variant + 1))) && (CONTEXT->PARENT_CALLS.size() > 0 && CONTEXT->PARENT_CALLS.top() == this)) {
		CONTEXT->CALLS.pop();
		CONTEXT->PARENT_CALLS.pop();
		CONTEXT->PARENT_CALL_VARIANT.pop();
		CONTEXT->CLAUSES.pop();
		CONTEXT->FRAMES.pop();
		CONTEXT->CTXS.pop();
		CONTEXT->NEGS.pop();
		CONTEXT->_FLAGS.pop();
	}

	if (up_f && f)
		up_f->sync(false, yes && CONTEXT == prolog->CONTEXT && CONTEXT->PARENT_CALLS.size() == 0, CONTEXT, f);

	delete f;

	return yes;
}

double interpreter::evaluate(context * CTX, frame_item * ff, const string & expression, size_t & p) {
	string ops = "(+-*/";
	int priors[5] = { 0, 1, 1, 2, 2 };

	stack<char> opers;

	typedef struct {
		bool is_op;
		union {
			char op;
			double v;
		};
	} pitem;

	queue<pitem> postfix;
	stack<double> vals;
	bool can_be_neg = true;

	int bracket_level = 0;

	auto calc_one = [&]() {
		double v2 = vals.top();
		vals.pop();
		double v1 = vals.top();
		vals.pop();

		double v;

		switch (postfix.front().op) {
			case '+': v = v1 + v2; break;
			case '-': v = v1 - v2; break;
			case '*': v = v1 * v2; break;
			case '/': v = v1 / v2; break;
		}
		vals.push(v);
		postfix.pop();
	};

	auto get_arg = [&](size_t & p, char ending)->double {
		double result = evaluate(CTX, ff, expression, p);
		if (p >= expression.length() || expression[p] != ending) {
			std::cout << "Expression '" << expression << "' : '" << ending << "' expected!" << endl;
			exit(105);
		}
		p++;
		bypass_spaces(expression, p);
		return result;
	};

	bypass_spaces(expression, p);
	while (p < expression.length() && expression[p] != ',') {
		if (expression[p] == '(') {
			bracket_level++;
			opers.push(expression[p]);
			can_be_neg = true;
			p++;
		}
		else if (expression[p] == ')') {
			if (bracket_level == 0) break;
			bracket_level--;
			p++;
			while (opers.size()) {
				if (opers.top() == '(') break;
				pitem p = { true };
				p.op = opers.top();
				postfix.push(p);
				opers.pop();
			}
			if (opers.size() == 0) {
				std::cout << "Evaluate(" << expression << ") : brackets disbalance!" << endl;
				exit(105);
			}
			opers.pop();
			can_be_neg = false;
		}
		else {
			string::size_type pos = ops.find(expression[p]);
			if (pos == string::npos || expression[p] == '-' && can_be_neg) {
				double sign = +1.0;
				if (expression[p] == '-') {
					sign = -1.0;
					p++;
				}
				value * v = parse(CTX, false, false, ff, expression, p);
				if (dynamic_cast<int_number *>(v)) {
					pitem p = { false };
					p.v = sign*dynamic_cast<int_number *>(v)->get_value();
					postfix.push(p);
				}
				else if (dynamic_cast<float_number *>(v)) {
					pitem p = { false };
					p.v = sign*dynamic_cast<float_number *>(v)->get_value();
					postfix.push(p);
				}
				else if (dynamic_cast<var *>(v) || dynamic_cast<term *>(v)) {
					string id = dynamic_cast<var *>(v) ? ((var*)v)->get_name() : ((term *)v)->get_name();
					pitem pp = { false };
					bypass_spaces(expression, p);
					if (p < expression.length() && expression[p] == '(') {
						p++;
						if (id == "max") {
							double a = get_arg(p, ',');
							double b = get_arg(p, ')');
							pp.v = sign*max(a, b);
							postfix.push(pp);
						}
						else if (id == "abs") {
							double a = get_arg(p, ')');
							pp.v = sign*fabs(a);
							postfix.push(pp);
						}
						else if (id == "sin") {
							double a = get_arg(p, ')');
							pp.v = sign * sin(a);
							postfix.push(pp);
						}
						else if (id == "cos") {
							double a = get_arg(p, ')');
							pp.v = sign * cos(a);
							postfix.push(pp);
						}
						else if (id == "tan") {
							double a = get_arg(p, ')');
							pp.v = sign * tan(a);
							postfix.push(pp);
						}
						else if (id == "sqrt") {
							double a = get_arg(p, ')');
							pp.v = sign * sqrt(a);
							postfix.push(pp);
						}
						else if (id == "log") {
							double a = get_arg(p, ')');
							pp.v = sign * log(a);
							postfix.push(pp);
						}
						else if (id == "floor") {
							double a = get_arg(p, ')');
							pp.v = floor(a);
							postfix.push(pp);
						}
						else if (id == "ceiling") {
							double a = get_arg(p, ')');
							pp.v = ceil(a);
							postfix.push(pp);
						}
						else if (id == "round") {
							double a = get_arg(p, ')');
							pp.v = sign*round(a);
							postfix.push(pp);
						}
						else {
							std::cout << "Evaluation(" << expression << ") : unknown function '" << id << "'!" << endl;
							exit(105);
						}
					}
					else {
						std::cout << "Evaluation(" << expression << ") : Var(" << id << ") not defined!" << endl;
						exit(105);
					}
				} else {
					std::cout << "Evaluate error : " << expression << endl;
					exit(105);
				}
				v->free();
				can_be_neg = false;
			}
			else {
				while (opers.size()) {
					if (priors[pos] > priors[ops.find(opers.top())]) break;
					pitem p = { true };
					p.op = opers.top();
					postfix.push(p);
					opers.pop();
				}
				opers.push(expression[p]);
				p++;
				can_be_neg = true;
			}
		}
		bypass_spaces(expression, p);
	}
	while (opers.size()) {
		pitem p = { true };
		p.op = opers.top();
		postfix.push(p);
		opers.pop();
	}

	while (postfix.size()) {
		pitem p = postfix.front();
		if (p.is_op)
			calc_one();
		else {
			vals.push(p.v);
			postfix.pop();
		}
	}

	if (vals.size() != 1) {
		std::cout << "Strange evaluation(" << expression << ")!" << endl;
		exit(105);
	}

	return vals.top();
}

class lazy_generated_vars : public generated_vars {
	predicate_item * p;
	int internal_variant;
	unsigned int max_num_variants;

	vector<value *> * positional_vals;

	frame_item * parent;
public:
	lazy_generated_vars(frame_item * f, predicate_item * pp, vector<value *> * _positional_vals, frame_item * first, int internal_ptr, unsigned int max_nv) : generated_vars() {
		p = pp;
		internal_variant = internal_ptr;
		max_num_variants = max_nv;

		positional_vals = _positional_vals;

		parent = f;

		if (first)
			this->push_back(first);
	}

	virtual bool has_variant(int i) { return i < this->size(); }

	virtual unsigned int get_max() {
		return max_num_variants;
	}

	virtual void trunc_from(int k) {
		if (k < (int)max_num_variants) max_num_variants = k;
		delete_from(k);
	}

	virtual frame_item * get_next_variant(context * CTX, int i) {
		frame_item * result = this->at(i);

		if (this->size() < max_num_variants && (size_t)(i + 1) == this->size()) {
			frame_item * next = p->get_next_variant(CTX, parent, internal_variant, positional_vals);
			if (next)
				this->push_back(next);
		}

		return result;
	}

	virtual void undo(int _i, vector<frame_item*>* list) {
		if (list->size())
			generated_vars::undo(_i, list);
		for (int j = 0; j < list->size(); j++)
			at((size_t)(_i + j + 1)) = list->at(j);
	}

	virtual void delete_from(int k) {
		for (int i = k; i < size(); i++) {
			delete this->at(i);
		}
		this->resize(k);
	}
};

void clause::bind(bool starring) {
	for (predicate_item * p : items)
		p->bind(starring);
}

predicate::~predicate() {
	for (clause * c : clauses) {
		delete c;
	}
}

clause::~clause() {
	for (predicate_item * p : items)
		delete p;
	for (value * v : _args)
		v->free();
}

class predicate_or : public predicate_item {
protected:
	predicate_item * ending;
public:
	predicate_or(int num, clause * c, interpreter * _prolog) : predicate_item(false, false, false, num, c, _prolog) {
		ending = NULL;
	}

	virtual const string get_id() { return "or"; }

	void set_ending(predicate_item * p) {
		ending = p;
	}

	virtual predicate_item * get_next(int variant) {
			return ending;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);
		return result;
	}
};

class predicate_left_bracket : public predicate_item {
protected:
	vector<predicate_item *> branches;
	bool inserted;
public:
	predicate_left_bracket(bool _inserted, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog), inserted(_inserted) { }

	bool is_inserted() const { return inserted; }

	virtual const string get_id() { return "left_bracket"; }

	void push_branch(predicate_item * p) {
		branches.push_back(p);
	}

	virtual predicate_item * get_next(int variant) {
		if (variant == 0)
			return predicate_item::get_next(variant);
		return branches[(size_t)(variant-1)];
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		generated_vars * result = new generated_vars();
		for (int i = 0; i <= branches.size(); i++) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		return result;
	}
};

class predicate_right_bracket : public predicate_item {
	predicate_left_bracket * left_bracket;
public:
	predicate_right_bracket(predicate_left_bracket * lb, int num, clause * c, interpreter * _prolog) :
		predicate_item(false, false, false, num, c, _prolog),
		left_bracket(lb) { }

	virtual const string get_id() { return "right_bracket"; }

	predicate_left_bracket * get_corresponding() { return left_bracket; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);
		return result;
	}
};

class predicate_item_eq : public predicate_item {
public:
	predicate_item_eq(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "eq"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "eq(A,B) incorrect call!" << endl;
			exit(-3);
		}
		var * a1 = dynamic_cast<var *>(positional_vals->at(0));
		var * a2 = dynamic_cast<var *>(positional_vals->at(1));
		if (a1 && a2) {
			std::cout << "eq(A,B) unbounded!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);
		if (!a1 && !a2)
		{
			if (!positional_vals->at(0)->unify(CTX, r, positional_vals->at(1))) {
				delete r;
				delete result;
				result = NULL;
			}
		}
		else if (a1 && !a2) {
			r->set(false, CTX, a1->get_name().c_str(), positional_vals->at(1));
		}
		else if (!a1 && a2) {
			r->set(false, CTX, a2->get_name().c_str(), positional_vals->at(0));
		}
		return result;
	}
};

class predicate_item_neq : public predicate_item {
public:
	predicate_item_neq(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "neq"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "neq(A,B) incorrect call!" << endl;
			exit(-3);
		}
		var * a1 = dynamic_cast<var *>(positional_vals->at(0));
		var * a2 = dynamic_cast<var *>(positional_vals->at(1));
		if (a1 || a2) {
			std::cout << "neq(A,B) unbounded!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);
		if (positional_vals->at(0)->unify(CTX, r, positional_vals->at(1))) {
			delete r;
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_less : public predicate_item {
public:
	predicate_item_less(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "less"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "less(A,B) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 || !d2) {
			std::cout << "less(A,B) unbounded!" << endl;
			exit(-3);
		}

		int_number * i1 = dynamic_cast<int_number *>(positional_vals->at(0));
		float_number * f1 = dynamic_cast<float_number *>(positional_vals->at(0));
		term * t1 = dynamic_cast<term *>(positional_vals->at(0));
		int_number * i2 = dynamic_cast<int_number *>(positional_vals->at(1));
		float_number * f2 = dynamic_cast<float_number *>(positional_vals->at(1));
		term * t2 = dynamic_cast<term *>(positional_vals->at(1));

		generated_vars * result = new generated_vars();
		if (i1 && i2 && i1->get_value() < i2->get_value() ||
			f1 && f2 && f1->get_value() < f2->get_value() ||
			i1 && f2 && i1->get_value() < f2->get_value() ||
			f1 && i2 && f1->get_value() < i2->get_value() ||
			t1 && t2 && t1->get_args().size() == 0 && t2->get_args().size() == 0 && t1->get_name() < t2->get_name()) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_greater : public predicate_item {
public:
	predicate_item_greater(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "greater"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "greater(A,B) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 || !d2) {
			std::cout << "greater(A,B) unbounded!" << endl;
			exit(-3);
		}

		int_number * i1 = dynamic_cast<int_number *>(positional_vals->at(0));
		float_number * f1 = dynamic_cast<float_number *>(positional_vals->at(0));
		term * t1 = dynamic_cast<term *>(positional_vals->at(0));
		int_number * i2 = dynamic_cast<int_number *>(positional_vals->at(1));
		float_number * f2 = dynamic_cast<float_number *>(positional_vals->at(1));
		term * t2 = dynamic_cast<term *>(positional_vals->at(1));

		generated_vars * result = new generated_vars();
		if (i1 && i2 && i1->get_value() > i2->get_value() ||
			f1 && f2 && f1->get_value() > f2->get_value() ||
			i1 && f2 && i1->get_value() > f2->get_value() ||
			f1 && i2 && f1->get_value() > i2->get_value() ||
			t1 && t2 && t1->get_args().size() == 0 && t2->get_args().size() == 0 && t1->get_name() > t2->get_name()) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_inc : public predicate_item {
public:
	predicate_item_inc(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "inc"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "inc(A,B) incorrect call!" << endl;
			exit(-3);
		}
		var * a1 = dynamic_cast<var *>(positional_vals->at(0));
		var * a2 = dynamic_cast<var *>(positional_vals->at(1));
		if (a1 && a2) {
			std::cout << "inc(A,B) unbounded!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);
		if (!a1 && !a2)
		{
			int_number * n1 = dynamic_cast<int_number *>(positional_vals->at(0));
			int_number * n2 = dynamic_cast<int_number *>(positional_vals->at(1));
			int_number* _n2 = new int_number((int)(n1->get_value()) + 1);

			if (!n1 || !n2 || !n2->unify(CTX, r, _n2)) {
				delete r;
				delete result;
				result = NULL;
			}
			_n2->free();
		}
		else if (a1 && !a2) {
			int_number * n2 = dynamic_cast<int_number *>(positional_vals->at(1));
			int_number * _n2 = new int_number((int)(n2->get_value()) - 1);

			r->set(false, CTX, a1->get_name().c_str(), _n2);
			_n2->free();
		}
		else if (!a1 && a2) {
			int_number * n1 = dynamic_cast<int_number *>(positional_vals->at(0));
			int_number* _n1 = new int_number((int)n1->get_value() + 1);

			r->set(false, CTX, a2->get_name().c_str(), _n1);
			_n1->free();
		}
		return result;
	}
};

class predicate_item_term_split : public predicate_item {
public:
	predicate_item_term_split(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "split(=..)"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "=..(term,[term_id,arg1,...,argN]) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();

		generated_vars * result = new generated_vars();

		if (d1) {
			term * t1 = dynamic_cast<term *>(positional_vals->at(0));
			value * t2 = dynamic_cast<value *>(positional_vals->at(1));

			if (!t1) {
				std::cout << "=..(term,[term_id,arg1,...,argN]) has incorrect parameters!" << endl;
				exit(-3);
			}

			frame_item * r = f->copy(CTX);

			stack_container<value *> LL;
			LL.reserve(t1->get_args().size() + 1);
			LL.push_back(new term(t1->get_name()));

			for (int i = 0; i < t1->get_args().size(); i++)
				LL.push_back(t1->get_args().at(i)->const_copy(CTX, r));

			::list * L2 = new ::list(LL, NULL);

			if (t2->unify(CTX, r, L2)) {
				result->push_back(r);
			}
			else {
				delete result;
				result = NULL;
				delete r;
			}
			L2->free();
		}
		else {
			value * t1 = dynamic_cast<value *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			if (!L2 || L2->size() == 0 || !dynamic_cast<term *>(L2->get_nth(1, false))) {
				std::cout << "=..(term,[term_id,arg1,...,argN]) has incorrect parameters!" << endl;
				exit(-3);
			}

			frame_item * r = f->copy(CTX);

			term * TT = new term(dynamic_cast<term *>(L2->get_nth(1, false))->get_name());
			for (int i = 2; i <= L2->size(); i++)
				TT->add_arg(CTX, r, L2->get_nth(i, false)->const_copy(CTX, r));

			if (t1->unify(CTX, r, TT)) {
				result->push_back(r);
			}
			else {
				delete result;
				result = NULL;
				delete r;
			}
			TT->free();
		}

		return result;
	}
};

class predicate_item_functor : public predicate_item {
public:
	predicate_item_functor(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "functor"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "functor(indicator,name,pow) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = !dynamic_cast<var *>(positional_vals->at(0)) &&
			!dynamic_cast<any *>(positional_vals->at(0));

		generated_vars * result = new generated_vars();

		if (d1) {
			term * t1 = dynamic_cast<term *>(positional_vals->at(0));
			value * v2 = dynamic_cast<value *>(positional_vals->at(1));
			value * v3 = dynamic_cast<value *>(positional_vals->at(2));

			if (!t1) {
				std::cout << "functor(indicator,name,pow) has incorrect parameters!" << endl;
				exit(-3);
			}

			frame_item * r = f->copy(CTX);

			int_number * N = new int_number(t1->get_args().size());
			term * NM = new term(t1->get_name());

			if (v2->unify(CTX, r, NM) && v3->unify(CTX, r, N)) {
				result->push_back(r);
			}
			else {
				delete result;
				result = NULL;
				delete r;
			}
			N->free();
			NM->free();
		}
		else {
			value * t1 = dynamic_cast<value *>(positional_vals->at(0));
			term * v2 = dynamic_cast<term *>(positional_vals->at(1));
			int_number * v3 = dynamic_cast<int_number *>(positional_vals->at(2));

			if (!v2 || !v3 || v2->get_args().size() || v3->get_value() < 0) {
				std::cout << "functor(indicator,name,pow) has incorrect parameters!" << endl;
				exit(-3);
			}

			frame_item * r = f->copy(CTX);

			term * TT = new term(v2->get_name());
			int NN = (int)v3->get_value();
			for (int i = 0; i < NN; i++)
				TT->add_arg(CTX, r, new any());

			if (t1->unify(CTX, r, TT)) {
				result->push_back(r);
			}
			else {
				delete result;
				result = NULL;
				delete r;
			}
			TT->free();
		}

		return result;
	}
};

class predicate_item_load_classes : public predicate_item {
public:
	predicate_item_load_classes(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "load_classes"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "load_classes(RootDir,ObjFactID,ObjLinkID) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		if (!d1 || !d2 || !d3) {
			std::cout << "load_classes(RootDir,ObjFactID,ObjLinkID) unbounded!" << endl;
			exit(-3);
		}

		term * t1 = dynamic_cast<term *>(positional_vals->at(0));
		term * t2 = dynamic_cast<term *>(positional_vals->at(1));
		term * t3 = dynamic_cast<term *>(positional_vals->at(2));

		generated_vars * result = new generated_vars();
		if (t1 && t2 && t3 && LoadModellingDesktop(L"", utf8_to_wstring(t1->get_name())) &&
				prolog->LoadXPathing()) {
			frame_item * r = f->copy(CTX);
			prolog->CLASSES_ROOT = t1->get_name();
			prolog->SetXPathLoaded(true);
			std::unique_lock<std::mutex> glock(prolog->GLOCK);
			prolog->GVars[string(nameObjFactID)] = t2->const_copy(CTX, r);
			prolog->GVars[string(nameObjLinkID)] = t3->const_copy(CTX, r);
			glock.unlock();
			result->push_back(r);
		}
		else {
			delete result;
			prolog->SetXPathLoaded(false);
			result = NULL;
		}
		return result;
	}
};

class predicate_item_init_xpathing : public predicate_item {
public:
	predicate_item_init_xpathing(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "init_xpathing"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "init_xpathing(Version) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "init_xpathing(Version) unbounded!" << endl;
			exit(-3);
		}

		term * t1 = dynamic_cast<term *>(positional_vals->at(0));
		prolog->INDUCT_MODE = t1 ? t1->get_name() : "";

		string induct_fname = prolog->CLASSES_ROOT;
		if (induct_fname.length() && induct_fname.back() != '\\' && induct_fname.back() != '/')
			induct_fname += "/";
		string log_fname = induct_fname;
		induct_fname += "induct.im";
		log_fname += "induct.log";

		generated_vars * result = new generated_vars();
		if (t1 && prolog->XPathLoaded() && CompileXPathing(
				false,
				t1->get_name().c_str(),
				induct_fname.c_str(),
				NULL, NULL, prolog->ENV(),
				NULL
				)) {
			frame_item * r = f->copy(CTX);
			SetDeduceLogFile(log_fname.c_str());
			prolog->SetXPathCompiled(true);
			result->push_back(r);
		}
		else {
			delete result;
			ClearRestrictions();
			prolog->SetXPathCompiled(false);
			result = NULL;
		}
		return result;
	}
};

class predicate_item_induct_xpathing : public predicate_item {
public:
	predicate_item_induct_xpathing(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "induct_xpathing"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 7) {
			std::cout << "induct_xpathing(Interval,nCPU,InFName,OutFName,UseNNet,SimilarDirect,OnlyInduceModel) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		bool d4 = positional_vals->at(3)->defined();
		bool d5 = positional_vals->at(4)->defined();
		bool d6 = positional_vals->at(5)->defined();
		bool d7 = positional_vals->at(6)->defined();
		if (!d1 || !d2 || !d3 || !d4 || !d5 || !d6 && !d7) {
			std::cout << "induct_xpathing(Interval,nCPU,InFName,OutFName,UseNNet,SimilarDirect,OnlyInduceModel) unbounded!" << endl;
			exit(-3);
		}

		int_number * n1 = dynamic_cast<int_number *>(positional_vals->at(0));
		int_number * n2 = dynamic_cast<int_number *>(positional_vals->at(1));
		term * t3 = dynamic_cast<term *>(positional_vals->at(2));
		term * t4 = dynamic_cast<term *>(positional_vals->at(3));
		term * t5 = dynamic_cast<term *>(positional_vals->at(4));
		term * t6 = dynamic_cast<term *>(positional_vals->at(5));
		term * t7 = dynamic_cast<term *>(positional_vals->at(6));

		if (n1) SetInterval(1000*(uint32_t)n1->get_value());

		string IDS = "";
		int n_objs = 0;
		std::unique_lock<std::mutex> glock(prolog->GLOCK);
		map<string, value *>::iterator itf = prolog->GVars.find("$ObjFactID");
		if (itf != prolog->GVars.end()) {
			std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
			map< string, std::atomic<vector<term *> *>>::iterator itd = CTX->DB->find(itf->second->to_str());
			if (itd != CTX->DB->end()) {
				CTX->register_db_read(itd->first);
				n_objs = (int)itd->second.load()->size();
			}
			lock.unlock();
		}
		glock.unlock();
		for (int i = 1; i <= n_objs; i++) {
			char Buf[128] = { 0 };
			IDS += string(__ltoa(i, Buf, 10));
			if (i != n_objs)
				IDS += "\r\n";
		}

		bool UseNNet = t5 && t5->get_name() != "f";
		bool MainLineAllowed = t6 && t6->get_name() != "f";
		bool OnlyInduceModel = t7 && t7->get_name() != "f";

		generated_vars * result = new generated_vars();
		if (n1 && n2 && t3 && t4 && t5 && t6 && t7 && prolog->XPathCompiled() && XPathInduct(
			false,
			CreateSysF,
			ExistClassF,
			GetElementF,
			CanReachF,
			CreateContactsF,
			AddElementF,
			AddLinkF,
			AnalyzeLinkStatusIsInformF,
			SetParameterIfExistsF,
			MoveF,
			CheckSysF,
			ToStringF,
			GenerateCodeF,
			SaveToXMLF,
			_FreeF,
			NodeNameTester,
			prolog->INDUCT_MODE.c_str(),
			UseNNet,
			MainLineAllowed,
			NULL, prolog->ENV(), prolog->ENV(),
			t3->get_name().c_str(), t4->get_name().c_str(),
			(int)(0.5 + n2->get_value()),
			IDS.c_str(),
			OnlyInduceModel
			)) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			ClearRestrictions();
			result = NULL;
		}
		return result;
	}
};

class predicate_item_import_model_after_induct : public predicate_item {
public:
	predicate_item_import_model_after_induct(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "import_model_after_induct"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "import_model_after_induct(ModelFileName) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "import_model_after_induct(ModelFileName) unbounded!" << endl;
			exit(-3);
		}

		auto assertz = [&](term * t) {
			string atid = t->get_name();
			std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
			CTX->register_db_read(atid);
			if (CTX->DB->find(atid) == CTX->DB->end())
				(*CTX->DB)[atid] = new vector<term*>();

			vector<term *> * terms = (*CTX->DB)[atid];
			term* tt = (term*)t->const_copy(CTX, f);
			CTX->register_db_write(atid, jInsert, tt, (int)terms->size());
			terms->push_back(tt);
			lock.unlock();

			std::unique_lock<std::mutex> dbilock(prolog->DBILock);
			if (prolog->DBIndicators.find(atid) == prolog->DBIndicators.end()) {
				set<int> * inds = new set<int>;
				inds->insert((int)t->get_args().size());
				prolog->DBIndicators[atid] = inds;
			}
			else {
				set<int> * inds = prolog->DBIndicators[atid];
				inds->insert((int)t->get_args().size());
			}
			dbilock.unlock();
		};

		auto Import = [&](const string & FName, value * _ObjFactID,
			value * _LinkFactID)->bool {
			bool result = true;
			TSystem * S = new TSystem();
			try {
				string ObjFactID = dynamic_cast<term *>(_ObjFactID)->get_name();
				string LinkFactID = dynamic_cast<term *>(_LinkFactID)->get_name();
				wstring Lang;
				S->LoadFromXML(Lang, utf8_to_wstring(FName));
				std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
				map<string, std::atomic<vector<term *>*>>::iterator it = CTX->DB->find(ObjFactID);
				if (it != CTX->DB->end()) {
					CTX->register_db_read(ObjFactID);
					for (term * t : *it->second)
						CTX->register_db_write(ObjFactID, jDelete, t, 0);
					it->second.load()->clear();
				}
				lock.unlock();
				S->EnumerateObjs(
					[&](TElement * E) {
						term * t = new term(ObjFactID);
						t->add_arg(CTX, f, new term(wstring_to_utf8(E->Ident)));
						t->add_arg(CTX, f, new term(wstring_to_utf8(E->Ref->ClsID)));
						::list * L = new ::list(stack_container<value *>(), NULL);
						map<wstring, wstring>::iterator it = E->Parameters.begin();
						while (it != E->Parameters.end()) {
							term * tL = new term("param");
							tL->add_arg(CTX, f, new term(wstring_to_utf8(it->first)));
							tL->add_arg(CTX, f, new term(wstring_to_utf8(it->second)));
							L->add(CTX, tL);
							it++;
						}
						t->add_arg(CTX, f, L);
						t->add_arg(CTX, f, new term(""));
						assertz(t);
						t->free();
					}
				);
				lock.lock();
				it = CTX->DB->find(LinkFactID);
				if (it != CTX->DB->end()) {
					CTX->register_db_read(LinkFactID);
					for (term * t : *it->second)
						CTX->register_db_write(LinkFactID, jDelete, t, 0);
					it->second.load()->clear();
				}
				lock.unlock();
				S->EnumerateLinks(
					[&](TLink * L) {
						term * t = new term(LinkFactID);
						t->add_arg(CTX, f, new term(wstring_to_utf8(L->_From->Owner->Ident)));
						t->add_arg(CTX, f, new term(wstring_to_utf8(L->_From->Ref->CntID)));
						t->add_arg(CTX, f, new term(wstring_to_utf8(L->_To->Owner->Ident)));
						t->add_arg(CTX, f, new term(wstring_to_utf8(L->_To->Ref->CntID)));
						t->add_arg(CTX, f, new term(L->Inform ? "t" : "f"));
						assertz(t);
						t->free();
					}
				);
				delete S;
			}
			catch (...) {
				result = false;
			}
			return result;
		};

		term * t1 = dynamic_cast<term *>(positional_vals->at(0));

		generated_vars * result = new generated_vars();
		std::unique_lock<std::mutex> glock(prolog->GLOCK);
		value* OF = prolog->GVars[string(nameObjFactID)];
		value* OL = prolog->GVars[string(nameObjLinkID)];
		glock.unlock();
		if (t1 && prolog->XPathLoaded() && Import(
				t1->get_name(),
				OF,
				OL
				)
			) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			prolog->SetXPathLoaded(false);
			result = NULL;
		}
		return result;
	}
};

class predicate_item_unload_classes : public predicate_item {
public:
	predicate_item_unload_classes(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "unload_classes"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "unload_classes incorrect call!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		try {
			ClearAllRegistered();
			prolog->UnloadXPathing();
			prolog->CLASSES_ROOT = "";
			prolog->INDUCT_MODE = "";
			prolog->SetXPathCompiled(false);
			prolog->SetXPathLoaded(false);
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		catch (exception E) {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_var : public predicate_item {
public:
	predicate_item_var(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "var"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "var(V) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		generated_vars * result = new generated_vars();
		if (!d1) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_nonvar : public predicate_item {
public:
	predicate_item_nonvar(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "nonvar"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "nonvar(V) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		generated_vars * result = new generated_vars();
		if (d1) {
			frame_item * r = f->copy(CTX);
			result->push_back(r);
		}
		else {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_get_contacts : public predicate_item {
private:
	TIODirection Dir;
public:
	predicate_item_get_contacts(TIODirection dir, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog)
	{
		Dir = dir;
	}

	virtual const string get_id() { return "get_(i/o)contacts"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "get_icontacts(ID,ContList) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		term * t1 = dynamic_cast<term *>(positional_vals->at(0));
		value * v2 = dynamic_cast<value *>(positional_vals->at(1));
		generated_vars * result = new generated_vars();
		if (d1 && !d2 && t1) {
			frame_item * r = f->copy(CTX);
			vector<TContactReg *> Contacts;
			GetContactsRegByClassID(
				utf8_to_wstring(t1->get_name()),
				Dir,
				Contacts);
			::list * received = new ::list(stack_container<value *>(), NULL);
			for (TContactReg * C : Contacts) {
				term * t = new ::term("contact");
				char Buf[128] = { 0 };
				t->add_arg(CTX, r, new term(wstring_to_utf8(C->CntID)));
				t->add_arg(CTX, r, new term(__itoa(rand(), Buf, 10)));
				received->add(CTX, t);
			}
			if (v2->unify(CTX, r, received))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			received->free();
		}
		else {
			delete result;
			result = NULL;
		}
		return result;
	}
};

class predicate_item_g_assign : public predicate_item {
public:
	predicate_item_g_assign(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "g_assign"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "g_assign(Name,Val) incorrect call!" << endl;
			exit(-3);
		}
		term * a1 = dynamic_cast<term *>(positional_vals->at(0));
		value * a2 = dynamic_cast<value *>(positional_vals->at(1));
		if (!a1 || !a1->defined() || a1->get_args().size() > 0 || !a2) {
			std::cout << "g_assign(Name,Val) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		string new_name = a1->get_name();
		if (CTX->forked() && (new_name.length() == 0 || new_name[0] != '&')) {
			new_name.insert(0, 1, '*');
			r->set(false, CTX, new_name.c_str(), a2->const_copy(CTX, r));
		}
		else {
			std::unique_lock<std::mutex> glock(prolog->GLOCK);
			std::map<std::string, value*>::iterator it = prolog->GVars.find(a1->get_name());
			if (it != prolog->GVars.end())
				it->second->free();
			prolog->GVars[a1->get_name()] = a2->const_copy(CTX, r);
			glock.unlock();
		}

		return result;
	}
};

class predicate_item_g_assign_nth : public predicate_item {
public:
	predicate_item_g_assign_nth(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "g_assign_nth"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "g_assign_nth(Name,N,Val) incorrect call!" << endl;
			exit(-3);
		}
		term* a1 = dynamic_cast<term*>(positional_vals->at(0));
		int_number* a2 = dynamic_cast<int_number*>(positional_vals->at(1));
		value* a3 = dynamic_cast<value*>(positional_vals->at(2));
		if (!a1 || !a1->defined() || a1->get_args().size() > 0 || !a2 || !a2->defined() || !a3 || !a3->defined()) {
			std::cout << "g_assign_nth(Name,N,Val) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();
		frame_item* r = f->copy(CTX);

		string new_name = a1->get_name();
		if (CTX->forked() && (new_name.length() == 0 || new_name[0] != '&')) {
			new_name.insert(0, 1, '*');
			::list* L = dynamic_cast<::list*>(r->get(false, CTX, new_name.c_str()));
			if (L && L->set_nth((int)a2->get_value(), a3->const_copy(CTX, r))) {
				r->register_write(new_name);
				result->push_back(r);
			}
			else {
				delete r;
				delete result;
				result = NULL;
			}
		}
		else {
			std::unique_lock<std::mutex> glock(prolog->GLOCK);
			::list* L = dynamic_cast<::list*>(prolog->GVars[a1->get_name()]);
			if (L && L->set_nth((int)a2->get_value(), a3->const_copy(CTX, r)))
				result->push_back(r);
			else {
				delete r;
				delete result;
				result = NULL;
			}
			glock.unlock();
		}

		return result;
	}
};

class predicate_item_g_read : public predicate_item {
public:
	predicate_item_g_read(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "g_read"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "g_read(Name,A) incorrect call!" << endl;
			exit(-3);
		}
		term * a1 = dynamic_cast<term *>(positional_vals->at(0));
		value * a2 = dynamic_cast<value *>(positional_vals->at(1));
		if (!a1 || !a1->defined() || a1->get_args().size() > 0 || !a2) {
			std::cout << "g_read(Name,A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		string new_name = a1->get_name();
		if (CTX->forked() && (new_name.length() == 0 || new_name[0] != '&')) {
			new_name.insert(0, 1, '*');
			value* v = r->get(false, CTX, new_name.c_str());
			if (v) {
				if (!a2->unify(CTX, r, v)) {
					delete result;
					result = NULL;
					delete r;
				}
			}
			else {
				v = new int_number(0);
				if (!a2->unify(CTX, r, v)) {
					delete result;
					result = NULL;
					delete r;
				}
				v->free();
			}
		}
		else {
			std::unique_lock<std::mutex> glock(prolog->GLOCK);
			map<string, value*>::iterator it = prolog->GVars.find(a1->get_name());
			if (it == prolog->GVars.end()) {
				value* v = new int_number(0);
				if (!a2->unify(CTX, r, v)) {
					delete result;
					result = NULL;
					delete r;
				}
				v->free();
			}
			else {
				if (!a2->unify(CTX, r, it->second)) {
					delete result;
					result = NULL;
					delete r;
				}
			}
			glock.unlock();
		}

		return result;
	}
};

class predicate_item_page_id : public predicate_item {
public:
	predicate_item_page_id(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "page_id"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "page_id(ID) incorrect call!" << endl;
			exit(-3);
		}
		value* a = dynamic_cast<value*>(positional_vals->at(0));
		if (!a) {
			std::cout << "page_id(ID) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();
		frame_item* r = f->copy(CTX);

		int_number* id = new int_number(CTX->THR ? CTX->THR->get_nthread() : -1);
		if (id && a->unify(CTX, r, id))
			result->push_back(r);
		else {
			delete r;
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_thread_id : public predicate_item {
public:
	predicate_item_thread_id(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "thread_id"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "thread_id(ID) incorrect call!" << endl;
			exit(-3);
		}
		value* a = dynamic_cast<value*>(positional_vals->at(0));
		if (!a) {
			std::cout << "thread_id(ID) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();
		frame_item* r = f->copy(CTX);

		ostringstream ss;
		ss << std::this_thread::get_id();

		term* id = new term(ss.str());
		if (id && a->unify(CTX, r, id))
			result->push_back(r);
		else {
			delete r;
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_cut : public predicate_item {
	predicate_item * frontier;
public:
	predicate_item_cut(predicate_item * fr, int num, clause * c, interpreter * _prolog) :
		predicate_item(false, false, false, num, c, _prolog),
		frontier(fr)
	{ }

	virtual const string get_id() { return "cut(!)"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (prolog->block_process(CTX, false, true, frontier) && CTX && CTX->parent)
			CTX->cut_query.push_back(
				[this](interpreter * prolog, context * ctx)->bool {
					return prolog->block_process(ctx, false, true, this->frontier);
				}
			);
		generated_vars * result = new generated_vars();
		result->push_back(f->copy(CTX));
		return result;
	}
};

class predicate_item_is : public predicate_item {
	value * arg;
	string expression;
public:
	predicate_item_is(value * _arg, const string & _expr, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog),
		arg(_arg), expression(_expr)
	{ }

	~predicate_item_is() {
		arg->free();
	}

	virtual const string get_id() { return "is"; }

	virtual const string & get_expression() { return expression; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		generated_vars * result = new generated_vars();
		value * res;
		if (expression.length() && expression[0] == '\'') {
			string a;
			int i = 1;
			for (; i < expression.length() && expression[i] != '\''; i++)
				a += expression[i];
			if (i != expression.length() - 1) {
				std::cout << "'is' evaluation : incorrect 'atom' : " << expression << "'" << endl;
				exit(2000);
			}
			res = new term(a);
		} else {
			// Evaluate expression
			size_t p = 0;
			double _res = prolog->evaluate(CTX, f, expression, p);

			if (p < expression.length()) {
				std::cout << "'is' evaluation : can't understand the following : '" << expression.substr(p) << "'" << endl;
				exit(2000);
			}

			if (_res == (long long)_res)
				res = new int_number((long long)_res);
			else
				res = new float_number(_res);
		}
		frame_item * ff = f->copy(CTX);
		value * V = arg->const_copy(CTX, f);
		if (V->unify(CTX, ff, res))
			result->push_back(ff);
		else {
			delete ff;
			delete result;
			result = NULL;
		}

		res->free();

		return result;
	}
};

class predicate_item_fail : public predicate_item {
public:
	predicate_item_fail(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "fail"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		return NULL;
	}
};

class predicate_item_true : public predicate_item {
public:
	predicate_item_true(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "true"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		generated_vars * result = new generated_vars();
		result->push_back(f->copy(CTX));
		return result;
	}
};

class predicate_item_repeat : public predicate_item {
	map<context*, lazy_generated_vars*> d;
public:
	predicate_item_repeat(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "repeat"; }

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) {
		if (d[CTX]->get_max() >= (unsigned int)internal_variant) {
			if (internal_variant == 0x7FFFFFFF)
				internal_variant = 0;
			internal_variant++;
			return f->copy(CTX);
		}
		else
			return NULL;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "repeat incorrect call!" << endl;
			exit(-3);
		}
		int internal_ptr = 1;
		frame_item * first = f->copy(CTX);
		
		lazy_generated_vars* v = new lazy_generated_vars(f, this, positional_vals, first, internal_ptr, once ? 1 : 0x7FFFFFFF);

		d[CTX] = v;

		return v;
	}
};

class predicate_item_append : public predicate_item {
	typedef struct { bool d1, d2, d3; } params;
	std::map<context*, params> d;
public:
	predicate_item_append(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "append"; }

	virtual frame_item* get_next_variant(context* CTX, frame_item* f, int& internal_variant, vector<value*>* positional_vals) {
		frame_item* result = NULL;

		lock();
		params p = d[CTX];
		unlock();
		bool d1 = p.d1;
		bool d2 = p.d2;
		bool d3 = p.d3;

		if (d1 && d2 && d3 && internal_variant == 0) {
			::list* L1 = dynamic_cast<::list*>(positional_vals->at(0));
			::list* L2 = dynamic_cast<::list*>(positional_vals->at(1));
			::list* L3 = dynamic_cast<::list*>(positional_vals->at(2));

			if (L1 && L2 && L3) {
				::list* conc = L1->append(CTX, f, L2);
				frame_item* r = f->copy(CTX);
				if (conc->unify(CTX, r, L3))
					result = r;
				else {
					delete r;
				}
				conc->free();
			}
			internal_variant++;
		}
		if (d1 && d2 && !d3 && internal_variant == 0) {
			::list* L1 = dynamic_cast<::list*>(positional_vals->at(0));
			::list* L2 = dynamic_cast<::list*>(positional_vals->at(1));
			value* L3 = dynamic_cast<::value*>(positional_vals->at(2));

			if (L1 && L2 && L3) {
				::list* conc = L1->append(CTX, f, L2);
				frame_item* r = f->copy(CTX);
				if (L3->unify(CTX, r, conc))
					result = r;
				else {
					delete r;
				}
				conc->free();
			}
			internal_variant++;
		}
		if (d1 && !d2 && d3) {
			::list* L1 = dynamic_cast<::list*>(positional_vals->at(0));
			value* L2 = dynamic_cast<::value*>(positional_vals->at(1));
			::list* L3 = dynamic_cast<::list*>(positional_vals->at(2));

			if (L1 && L2 && L3 && !result && L1->size() <= L3->size() && internal_variant <= L1->size()) {
				internal_variant = L1->size();
				value* K1 = NULL;
				value* K2 = NULL;
				L3->const_split(CTX, f, internal_variant, K1, K2);

				frame_item* r = f->copy(CTX);

				if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
					result = r;
				else {
					delete r;
					internal_variant = L3->size();
				}
				K1->free();
				K2->free();
			}
			else
				internal_variant = L3->size();
			internal_variant++;
		}
		if (!d1 && d2 && d3) {
			value* L1 = dynamic_cast<::value*>(positional_vals->at(0));
			::list* L2 = dynamic_cast<::list*>(positional_vals->at(1));
			::list* L3 = dynamic_cast<::list*>(positional_vals->at(2));

			if (L1 && L2 && L3 && !result && L2->size() <= L3->size() && internal_variant <= L3->size() - L2->size()) {
				internal_variant = L3->size() - L2->size();
				value* K1;
				value* K2;
				L3->const_split(CTX, f, internal_variant, K1, K2);

				frame_item* r = f->copy(CTX);

				if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
					result = r;
				else {
					delete r;
					internal_variant = L3->size();
				}
				K1->free();
				K2->free();
			}
			else
				internal_variant = L3->size();
			internal_variant++;
		}
		if (!d1 && !d2 && d3 || !d1 && !d2 && !d3) {
			value* L1 = dynamic_cast<::value*>(positional_vals->at(0));
			value* L2 = dynamic_cast<::value*>(positional_vals->at(1));
			::list* L3 = dynamic_cast<::list*>(positional_vals->at(2));

			if (L1 && L2 && L3)
				for (; !result && internal_variant <= L3->size(); internal_variant++) {
					value* K1 = new ::list(stack_container<value*>(), NULL);
					value* K2 = new ::list(stack_container<value*>(), NULL);
					L3->const_split(CTX, f, internal_variant, K1, K2);

					frame_item* r = f->copy(CTX);

					if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
						result = r;
					else {
						delete r;
					}
					K1->free();
					K2->free();
				}
		}

		return result;
	}

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 3 && positional_vals->size() != 1) {
			std::cout << "append(A,B,C)/append(F) incorrect call!" << endl;
			exit(-3);
		}
		if (positional_vals->size() == 3) {
			params p = { 0 };
			p.d1 = positional_vals->at(0)->defined();
			p.d2 = positional_vals->at(1)->defined();
			p.d3 = positional_vals->at(2)->defined();

			lock();
			d[CTX] = p;
			unlock();

			int internal_ptr = 0;
			frame_item* first = get_next_variant(CTX, f, internal_ptr, positional_vals);

			if (first)
				return new lazy_generated_vars(f, this, positional_vals, first, internal_ptr, once ? 1 : 0x7FFFFFFF);
			else
				return NULL;
		}
		else {
			if (!positional_vals->at(0)->defined()) {
				std::cout << "append(F) indeterminated!" << endl;
				exit(-3);
			}

			prolog->current_output = positional_vals->at(0)->make_str();
			prolog->outs = new std::ofstream(prolog->current_output, ios::out | ios::app);

			generated_vars* result = new generated_vars();

			result->push_back(f->copy(CTX));

			return result;
		}
	}
};

class predicate_item_sublist : public predicate_item {
	typedef struct {
		bool d1, d2;
	} params;
	std::map<context*, params> d;
public:
	predicate_item_sublist(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "sublist"; }

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) {
		frame_item * result = NULL;

		params p;
		lock();
		p = d[CTX];
		unlock();
		bool d1 = p.d1;
		bool d2 = p.d2;

		if (d1 && d2 && internal_variant == 0) {
			::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			if (L1 && L2) {
				stack_values LL1;
				L1->get(CTX, f, &LL1);
				int p = 0;
				frame_item * r = f->copy(CTX);
				L2->iterate([&](value * v) {
					if (p < LL1.size()) {
						if (LL1[p]->unify(CTX, r, v))
							p++;
					}
				});
				if (p == LL1.size())
					result = r;
				else {
					delete r;
				}
				LL1.free();
			}
			internal_variant++;
		}
		if (!d1 && d2) {
			value * V1 = dynamic_cast<::value *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			if (V1 && L2) {
				int N = 1 << L2->size();
				for (; !result && internal_variant < N; internal_variant++) {
					stack_values SUBSET;
					int mask = 1;
					for (int i = 0; i < L2->size() && mask; i++, mask <<= 1) {
						if (internal_variant & mask)
							SUBSET.push_back(L2->get_nth(i+1, true));
					}
					::list * K = new ::list(SUBSET, NULL);

					frame_item * r = f->copy(CTX);

					if (V1->unify(CTX, r, K))
						result = r;
					else {
						delete r;
					}
					K->free();
				}
			}
		}

		return result;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "sublist(A,B) incorrect call!" << endl;
			exit(-3);
		}

		params p = { 0 };
		p.d1 = positional_vals->at(0)->defined();
		p.d2 = positional_vals->at(1)->defined();

		lock();
		d[CTX] = p;
		unlock();

		int internal_ptr = 0;
		frame_item * first = get_next_variant(CTX, f, internal_ptr, positional_vals);

		if (first)
			return new lazy_generated_vars(f, this, positional_vals, first, internal_ptr, once ? 1 : 0x7FFFFFFF);
		else
			return NULL;
	}
};

class predicate_item_atom_concat : public predicate_item {
	typedef struct {
		bool d1, d2, d3;
	} params;
	std::map<context*, params> d;
public:
	predicate_item_atom_concat(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "atom_concat"; }

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) {
		frame_item * result = NULL;

		params p;
		lock();
		p = d[CTX];
		unlock();
		bool d1 = p.d1;
		bool d2 = p.d2;
		bool d3 = p.d3;

		if (d1 && d2 && d3 && internal_variant == 0) {
			::term * L1 = dynamic_cast<::term *>(positional_vals->at(0));
			::term * L2 = dynamic_cast<::term *>(positional_vals->at(1));
			::term * L3 = dynamic_cast<::term *>(positional_vals->at(2));

			::term * conc = new term(L1->make_str() + L2->make_str());
			frame_item * r = f->copy(CTX);
			if (conc->unify(CTX, r, L3))
				result = r;
			else {
				delete r;
			}
			conc->free();
			internal_variant++;
		}
		if (d1 && d2 && !d3 && internal_variant == 0) {
			::term * L1 = dynamic_cast<::term *>(positional_vals->at(0));
			::term * L2 = dynamic_cast<::term *>(positional_vals->at(1));
			value * L3 = dynamic_cast<::value *>(positional_vals->at(2));

			::term * conc = new term(L1->make_str() + L2->make_str());
			frame_item * r = f->copy(CTX);
			if (L3->unify(CTX, r, conc))
				result = r;
			else {
				delete r;
			}
			conc->free();
			internal_variant++;
		}
		if (d1 && !d2 && d3) {
			::term * L1 = dynamic_cast<::term *>(positional_vals->at(0));
			value * L2 = dynamic_cast<::value *>(positional_vals->at(1));
			::term * L3 = dynamic_cast<::term *>(positional_vals->at(2));

			string LL1S = L1->make_str();
			string LL3S = L3->make_str();

			if (L1 && L2 && L3 && !result && LL1S.size() <= LL3S.size() && internal_variant <= LL1S.size()) {
				internal_variant = (int)LL1S.size();
				value * K1 = new term(LL3S.substr(0, internal_variant));
				value * K2 = new term(LL3S.substr(internal_variant, LL3S.length() - internal_variant));

				frame_item * r = f->copy(CTX);

				if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
					result = r;
				else {
					delete r;
					internal_variant = (int)LL3S.size();
				}
				K1->free();
				K2->free();
			}
			else
				internal_variant = (int)LL3S.size();
			internal_variant++;
		}
		if (!d1 && d2 && d3) {
			value * L1 = dynamic_cast<::value *>(positional_vals->at(0));
			::term * L2 = dynamic_cast<::term *>(positional_vals->at(1));
			::term * L3 = dynamic_cast<::term *>(positional_vals->at(2));

			string LL2S = L2->make_str();
			string LL3S = L3->make_str();

			if (L1 && L2 && L3 && !result && LL2S.size() <= LL3S.size() && internal_variant <= LL3S.size() - LL2S.size()) {
				internal_variant = (int)(LL3S.size() - LL2S.size());
				value * K1 = new term(LL3S.substr(0, internal_variant));
				value * K2 = new term(LL3S.substr(internal_variant, LL3S.length() - internal_variant));

				frame_item * r = f->copy(CTX);

				if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
					result = r;
				else {
					delete r;
					internal_variant = (int)LL3S.size();
				}
				K1->free();
				K2->free();
			} else
				internal_variant = (int)LL3S.size();
			internal_variant++;
		}
		if (!d1 && !d2 && d3) {
			value * L1 = dynamic_cast<::value *>(positional_vals->at(0));
			value * L2 = dynamic_cast<::value *>(positional_vals->at(1));
			::term * L3 = dynamic_cast<::term *>(positional_vals->at(2));

			string LL3S = L3->make_str();

			for (; !result && internal_variant <= LL3S.length(); internal_variant++) {
				value * K1 = new term(LL3S.substr(0, internal_variant));
				value * K2 = new term(LL3S.substr(internal_variant, LL3S.length() - internal_variant));

				frame_item * r = f->copy(CTX);

				if (L1->unify(CTX, r, K1) && L2->unify(CTX, r, K2))
					result = r;
				else {
					delete r;
				}
				K1->free();
				K2->free();
			}
		}

		return result;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "atom_concat(A,B,C) incorrect call!" << endl;
			exit(-3);
		}
		params p = { 0 };
		p.d1 = positional_vals->at(0)->defined();
		p.d2 = positional_vals->at(1)->defined();
		p.d3 = positional_vals->at(2)->defined();
		lock();
		d[CTX] = p;
		unlock();
		if (!p.d1 && !p.d2 && !p.d3) {
			std::cout << "atom_concat(A,B,C) indeterminated!" << endl;
			exit(-3);
		}

		int internal_ptr = 0;
		frame_item * first = get_next_variant(CTX, f, internal_ptr, positional_vals);

		if (first)
			return new lazy_generated_vars(f, this, positional_vals, first, internal_ptr, once ? 1 : 0x7FFFFFFF);
		else
			return NULL;
	}
};

class predicate_item_delete : public predicate_item {
public:
	predicate_item_delete(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "delete"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "delete(A,B,C) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		if (!d1 && !d2 && !d3) {
			std::cout << "delete(A,B,C) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		if (d1 && d2 && d3) {
			::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
			value * V2 = positional_vals->at(1);
			::list * L3 = dynamic_cast<::list *>(positional_vals->at(2));

			stack_values LL1;
			frame_item * r = f->copy(CTX);
			L1->iterate([&](value * v) {
				if (!V2->unify(CTX, r, v))
					LL1.push_back(v->const_copy(CTX, r));
			});
			::list * LL3 = new ::list(LL1, NULL);

			if (L3->unify(CTX, r, LL3))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			LL3->free();
		}
		if (d1 && d2 && !d3) {
			::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
			value * V2 = positional_vals->at(1);
			value * V3 = positional_vals->at(2);

			stack_values LL1;
			frame_item * r = f->copy(CTX);
			L1->iterate([&](value * v) {
				if (!V2->unify(CTX, r, v))
					LL1.push_back(v->const_copy(CTX, r));
			});
			::list * LL3 = new ::list(LL1, NULL);

			if (V3->unify(CTX, r, LL3))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			LL3->free();
		}
		if (!d1 && d3 || d1 && !d2 && !d3) {
			value * A1 = dynamic_cast<::value *>(positional_vals->at(0));
			value * A2 = dynamic_cast<::value *>(positional_vals->at(1));
			::list * L3 = dynamic_cast<::list *>(positional_vals->at(2));

			frame_item * r = f->copy(CTX);

			if (A1->unify(CTX, r, L3))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
		}
		if (!d1 && d2 && !d3 || d1 && !d2 && d3) {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_atom_chars : public predicate_item {
public:
	predicate_item_atom_chars(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "atom_chars"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "atom_chars(A,B) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "atom_chars(A,B) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		if (d1 && d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			string S2 = L2->make_str();

			frame_item * r = f->copy(CTX);
			if (A1->make_str() == S2)
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
		}
		if (d1 && !d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
			value * L2 = dynamic_cast<::value *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			::list * L = NULL;

			if (L1 && L1->size() == 0) {
				L = new ::list("[]", NULL);
			}
			else {
				string S = A1->make_str();
				L = new ::list(S, NULL);
			}

			if (L2->unify(CTX, r, L))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			L->free();
		}
		if (!d1 && d2) {
			value * A1 = dynamic_cast<::value *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			string S = L2->make_str();
			term * tt = new ::term(S);

			if (A1->unify(CTX, r, tt))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			tt->free();
		}

		return result;
	}
};

class predicate_item_atom_codes : public predicate_item {
public:
	predicate_item_atom_codes(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "atom_codes"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "atom_codes(A,B) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "atom_codes(A,B) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		if (d1 && d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			string S2;
			L2->iterate([&] (value * v) {
				int_number * n = dynamic_cast<int_number *>(v);
				if (n) S2 += (char) (0.5 + n->get_value());
			});

			frame_item * r = f->copy(CTX);
			if (A1->make_str() == S2)
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
		}
		if (d1 && !d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
			value * L2 = dynamic_cast<::value *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			::list * L = new ::list(stack_container<value *>(), NULL);

			if (L1 && L1->size() == 0) {
				//
			}
			else {
				string S = A1->make_str();
				for (char c : S)
					L->add(CTX, new int_number(c));
			}

			if (L2->unify(CTX, r, L))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			L->free();
		}
		if (!d1 && d2) {
			value * A1 = dynamic_cast<::value *>(positional_vals->at(0));
			::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			string S;
			L2->iterate([&](value * v) {
				int_number * n = dynamic_cast<int_number *>(v);
				if (n) S += (char)(0.5 + n->get_value());
			});
			term * tt = new ::term(S);

			if (A1->unify(CTX, r, tt))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			tt->free();
		}

		return result;
	}
};

class predicate_item_atom_hex : public predicate_item {
private:
	char SEP;
public:
	predicate_item_atom_hex(char sep, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) {
		SEP = sep;
	}

	virtual const string get_id() { return "atom_hex[s]"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "atom_hex[s](A,B) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "atom_hex[s](A,B) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		if (d1 && d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			::term * A2 = dynamic_cast<::term *>(positional_vals->at(1));

			string S2 = A2->from_hex(SEP);

			frame_item * r = f->copy(CTX);
			if (A1->make_str() == S2)
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
		}
		if (d1 && !d2) {
			::term * A1 = dynamic_cast<::term *>(positional_vals->at(0));
			value * L2 = dynamic_cast<::value *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			::term * H = new ::term(A1->to_hex(SEP));

			if (L2->unify(CTX, r, H))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			H->free();
		}
		if (!d1 && d2) {
			value * A1 = dynamic_cast<::value *>(positional_vals->at(0));
			::term * H2 = dynamic_cast<::term *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			string S = H2->from_hex(SEP);
			term * tt = new ::term(S);

			if (A1->unify(CTX, r, tt))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			tt->free();
		}

		return result;
	}
};

class predicate_item_number_atom : public predicate_item {
public:
	predicate_item_number_atom(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "number_atom"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "number_atom(A,B) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "number_atom(A,B) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		if (d1 && d2) {
			::int_number * N1 = dynamic_cast<::int_number *>(positional_vals->at(0));
			::float_number * F1 = dynamic_cast<::float_number *>(positional_vals->at(0));
			::term * A2 = dynamic_cast<::term *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);
			if (F1 && F1->make_str() == A2->make_str() || N1 && N1->make_str() == A2->make_str())
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
		}
		if (d1 && !d2) {
			::int_number * N1 = dynamic_cast<::int_number *>(positional_vals->at(0));
			::float_number * F1 = dynamic_cast<::float_number *>(positional_vals->at(0));
			value * A2 = dynamic_cast<::value *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			::term * S = new ::term(F1 ? F1->make_str() : N1->make_str());

			if (A2->unify(CTX, r, S))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			S->free();
		}
		if (!d1 && d2) {
			value * N1 = dynamic_cast<::value *>(positional_vals->at(0));
			::term * A2 = dynamic_cast<::term *>(positional_vals->at(1));

			frame_item * r = f->copy(CTX);

			size_t p = 0;
			value * S = prolog->parse(CTX, false, true, r, A2->make_str(), p);

			if ((dynamic_cast<int_number *>(S) || dynamic_cast<float_number *>(S)) && N1->unify(CTX, r, S))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			S->free();
		}

		return result;
	}
};

class predicate_item_number : public predicate_item {
public:
	predicate_item_number(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "number"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "number(A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "number(A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		if (dynamic_cast<int_number *>(positional_vals->at(0)) || dynamic_cast<float_number *>(positional_vals->at(0)))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}

		return result;
	}
};

class predicate_item_change_directory : public predicate_item {
public:
	predicate_item_change_directory(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "change_directory"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "change_directory(Dir) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "change_directory(Dir) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		term * A = dynamic_cast<::term *>(positional_vals->at(0));
		if (A) {
			current_path(A->get_name());
		} else {
			delete r;
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_open_url : public predicate_item {
public:
	predicate_item_open_url(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "open_url"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "open_url(URL|URLList) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "open_url(URL|URLList) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		::list * L = dynamic_cast<::list *>(positional_vals->at(0));
		string cmd;
		unsigned int ret = 0;
		if (L) {
			L->iterate([&](value * v) {
#ifdef __linux__
				cmd = "xdg-open ";
#else
				cmd = "start ";
#endif
				cmd += v->make_str();
				ret += abs(system(cmd.c_str()));
			});
		}
		else {
#ifdef __linux__
			cmd = "xdg-open ";
#else
			cmd = "start ";
#endif
			cmd += positional_vals->at(0)->make_str();
			ret += abs(system(cmd.c_str()));
		}

		if (ret != 0) {
			delete r;
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_track_post : public predicate_item {
public:
	predicate_item_track_post(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "track_post"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "track_post(ID|IDList) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "track_post(ID|IDList) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		::list * L = dynamic_cast<::list *>(positional_vals->at(0));
		unsigned int ret = 0;
		string cmd;
		if (L) {
			L->iterate([&](value * v) {
#ifdef __linux__
				cmd = "xdg-open ";
#else
				cmd = "start ";
#endif
				cmd += "https://gdeposylka.ru/";
				cmd += v->make_str();
				ret += abs(system(cmd.c_str()));
			});
		}
		else {
#ifdef __linux__
			cmd = "xdg-open ";
#else
			cmd = "start ";
#endif
			cmd += "https://gdeposylka.ru/";
			cmd += positional_vals->at(0)->make_str();
			ret += abs(system(cmd.c_str()));
		}

		if (ret != 0) {
			delete r;
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_consistency : public predicate_item {
public:
	predicate_item_consistency(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "consistency"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "consistency(PrefixesList) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "consistency(PrefixesList) indeterminated!" << endl;
			exit(-3);
		}
		::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
		if (!L1) {
			std::cout << "consistency(PrefixesList) has incorrect parameter!" << endl;
			exit(-3);
		}

		set<string> L;
		auto push = [&](value * v) {
			term * t = dynamic_cast<term *>(v);
			if (t && t->get_args().size() == 0)
				L.insert(t->get_name());
		};
		L1->iterate(push);

		generated_vars * result = new generated_vars();
		if (prolog->check_consistency(L))
			result->push_back(f->copy(CTX));
		else {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_last : public predicate_item {
public:
	predicate_item_last(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "last"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "last(L,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "last(L,A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));

		if (!L1) {
			std::cout << "last(L,A) : L is not a list!" << endl;
			exit(-3);
		}

		::value * V2 = dynamic_cast<::value *>(positional_vals->at(1));
		::value * LAST = ((::list *)L1)->get_last(CTX);

		if (LAST) {
			frame_item * r = f->copy(CTX);
			if (V2->unify(CTX, r, LAST))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			LAST->free();
		}
		else {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_reverse : public predicate_item {
public:
	predicate_item_reverse(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "reverse"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "reverse(A,B) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "reverse(A,B) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));
		::value * V1 = dynamic_cast<::value *>(positional_vals->at(0));
		::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));
		::value * V2 = dynamic_cast<::value *>(positional_vals->at(1));

		if (d1 && !L1 || d2 && !L2) {
			std::cout << "reverse(A,B) : A and B are not lists!" << endl;
			exit(-3);
		}

		if (d2) {
			swap(d1, d2);
			swap(L1, L2);
			swap(V1, V2);
		}

		frame_item * r = f->copy(CTX);
		stack_container<value *> REV1;
		L1->get(CTX, r, &REV1);
		reverse(REV1.begin(), REV1.end());

		::list * R1 = new ::list(REV1, NULL);

		if (V2->unify(CTX, r, R1))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}
		R1->free();

		return result;
	}
};

class predicate_item_member : public predicate_item {
	typedef struct {
		bool d1;
		::list* L2;
	} params;
	std::map<context*, params> d;
public:
	predicate_item_member(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "member"; }

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) {
		frame_item * result = NULL;

		::value * V1 = dynamic_cast<::value *>(positional_vals->at(0));

		lock();
		::list* L2 = d[CTX].L2;
		unlock();

		for (; !result && internal_variant < L2->size(); internal_variant++) {
			frame_item * r = f->copy(CTX);

			if (L2->get_nth(internal_variant + 1, false)->unify(CTX, r, V1))
				result = r;
			else
				delete r;
		}

		return result;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "member(A,L) incorrect call!" << endl;
			exit(-3);
		}
		params p = { 0 };
		p.d1 = positional_vals->at(0)->defined();
		p.L2 = dynamic_cast<::list *>(positional_vals->at(1));
		if (p.L2)
			p.L2->use();
		lock();

		if (d.find(CTX) != d.end()) {
			::list* L2 = d[CTX].L2;
			if (L2)
				L2->free();
		}
		d[CTX] = p;

		unlock();

		if (!p.L2) {
			return NULL;
		}

		int internal_ptr = 0;
		frame_item * first = get_next_variant(CTX, f, internal_ptr, positional_vals);

		if (first)
			return new lazy_generated_vars(f, this, positional_vals, first, internal_ptr, once ? 1 : 0x7FFFFFFF);
		else
			return NULL;
	}
};

class predicate_item_for : public predicate_item {
	typedef struct {
		int first;
		int last;
		var* V;
	} params;
	std::map<context*, params> d;
public:
	predicate_item_for(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "for"; }

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) {
		frame_item * result = NULL;

		::value * V1 = dynamic_cast<::value *>(positional_vals->at(0));

		params p;
		lock();
		p = d[CTX];
		unlock();

		for (; !result && internal_variant < p.last - p.first + 1; internal_variant++) {
			frame_item * r = f->copy(CTX);
			int_number * N = new int_number(p.first + internal_variant);
			if (p.V->unify(CTX, r, N))
				result = r;
			else
				delete r;
			N->free();
		}

		return result;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "for(V,From,To) incorrect call!" << endl;
			exit(-3);
		}
		if (!positional_vals->at(1)->defined() || !positional_vals->at(2)->defined()) {
			std::cout << "for(V,From,To) indeterminated!" << endl;
			exit(-3);
		}

		params p = { 0 };
		p.V = dynamic_cast<::var *>(positional_vals->at(0));
		int_number * FROM = dynamic_cast<::int_number *>(positional_vals->at(1));
		int_number * TO = dynamic_cast<::int_number *>(positional_vals->at(2));

		if (!p.V || !FROM || !TO) {
			return NULL;
		}

		p.first = (int)(0.5 + FROM->get_value());
		p.last = (int)(0.5 + TO->get_value());

		p.V->use();

		lock();
		if (d.find(CTX) != d.end()) {
			var * V = d[CTX].V;
			if (V)
				V->free();
		}
		d[CTX] = p;
		unlock();

		int internal_ptr = 0;
		frame_item * _first = get_next_variant(CTX, f, internal_ptr, positional_vals);

		if (_first)
			return new lazy_generated_vars(f, this, positional_vals, _first, internal_ptr, once ? 1 : 0x7FFFFFFF);
		else
			return NULL;
	}
};

class predicate_item_length : public predicate_item {
public:
	predicate_item_length(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "length"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "length(L,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "length(L,A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));

		if (!L1) {
			std::cout << "length(L,A) : L is not a list!" << endl;
			exit(-3);
		}

		::value * V2 = dynamic_cast<::value *>(positional_vals->at(1));
		::value * L = new int_number(L1->size());

		if (L) {
			frame_item * r = f->copy(CTX);
			if (V2->unify(CTX, r, L))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			L->free();
		}
		else {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_max_list : public predicate_item {
public:
	predicate_item_max_list(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "max__list"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "max_list(L,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "max_list(L,A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::list * L1 = dynamic_cast<::list *>(positional_vals->at(0));

		if (!L1) {
			std::cout << "max_list(L,A) : L is not a list!" << endl;
			exit(-3);
		}

		::value * V2 = dynamic_cast<::value *>(positional_vals->at(1));
		if (L1->size() == 0) {
			delete result;
			result = NULL;
		} else {
			double MAX = -1E300;
			bool error = false;
			L1->iterate([&] (value * v) {
				if (error) return;
				if (!v->defined())
					error = true;
				else {
					int_number * ni = dynamic_cast<int_number *>(v);
					if (ni) {
						if (ni->get_value() > MAX)
							MAX = ni->get_value();
					} else {
						float_number * nf = dynamic_cast<float_number *>(v);
						if (nf) {
							if (nf->get_value() > MAX)
								MAX = nf->get_value();
						} else
							error = true;
					}
				}
			});
			if (error) {
				delete result;
				result = NULL;
			} else {
				::value * L = new float_number(MAX);

				if (L) {
					frame_item * r = f->copy(CTX);
					if (V2->unify(CTX, r, L))
						result->push_back(r);
					else {
						delete result;
						result = NULL;
						delete r;
					}
					L->free();
				}
				else {
					delete result;
					result = NULL;
				}
			}
		}

		return result;
	}
};

class predicate_item_atom_length : public predicate_item {
public:
	predicate_item_atom_length(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "atom_length"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "atom_length(A,N) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "atom_length(A,N) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::term * T1 = dynamic_cast<::term *>(positional_vals->at(0));

		if (!T1 || T1->get_args().size() > 0) {
			std::cout << "atom_length(A,N) : A is not a simple atom!" << endl;
			exit(-3);
		}

		::value * V2 = dynamic_cast<::value *>(positional_vals->at(1));
		::value * L = new int_number(T1->get_name().length());

		if (L) {
			frame_item * r = f->copy(CTX);
			if (V2->unify(CTX, r, L))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			L->free();
		}
		else {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_nth : public predicate_item {
public:
	predicate_item_nth(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "nth"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "nth(Index,L,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		if (!d2) {
			std::cout << "nth(Index,L,A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::value * V1 = dynamic_cast<::value *>(positional_vals->at(0));
		::any * ANY1 = dynamic_cast<::any *>(positional_vals->at(0));
		::var * VAR1 = dynamic_cast<::var *>(positional_vals->at(0));
		::int_number * NUM1 = dynamic_cast<::int_number *>(positional_vals->at(0));
		::list * L2 = dynamic_cast<::list *>(positional_vals->at(1));
		::value * V3 = dynamic_cast<::value *>(positional_vals->at(2));

		if (!L2 || !ANY1 && !VAR1 && !NUM1) {
			std::cout << "nth(Index,L,A) : incorrect params!" << endl;
			exit(-3);
		}

		frame_item * r = f->copy(CTX);

		if (!d1 && !d3 || ANY1 || VAR1) { // Search or Variants
			int n = 1;
			auto check = [&](value * item) {
				if (V3->unify(CTX, r, item)) {
					::int_number * NN = new ::int_number(n);
					if (V1->unify(CTX, r, NN)) {
						result->push_back(r);
						r = f->copy(CTX);
					}
					NN->free();
				}
				n++;
			};
			L2->iterate(check);
			if (result->size() == 0) {
				delete result;
				result = NULL;
			}
			delete r;
		}
		else { // Unify nth-element
			value * V = L2->get_nth((int)NUM1->get_value(), true);
			if (V && V3->unify(CTX, r, V))
				result->push_back(r);
			else {
				delete result;
				result = NULL;
				delete r;
			}
			if (V) V->free();
		}

		if (result && once && result->size() > 1) {
			for (int i = 1; i < result->size(); i++)
				delete result->at(i);
			result->resize(1);
		}

		return result;
	}
};

class predicate_item_listing : public predicate_item {
public:
	predicate_item_listing(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "listing"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "listing/listing(A/n) incorrect call!" << endl;
			exit(-3);
		}
		indicator * t = NULL;
		if (positional_vals->size() == 1) {
			bool d1 = positional_vals->at(0)->defined();
			t = dynamic_cast<indicator *>(positional_vals->at(0));
			if (!d1) {
				std::cout << "listing(A/n) indeterminated!" << endl;
				exit(-3);
			}
			if (!t) {
				std::cout << "listing(A/n) has incorrect parameter!" << endl;
				exit(-3);
			}
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		map< string, std::atomic<vector<term *> *>>::iterator it = CTX->DB->begin();
		while (it != CTX->DB->end()) {
			if (!t || it->first == t->get_name()) {
				CTX->register_db_read(it->first);
				for (int i = 0; i < it->second.load()->size(); i++)
					if (!t || it->second.load()->at(i)->get_args().size() == t->get_arity()) {
						if (prolog->out_buf.size() == 0) {
							(*prolog->outs) << it->second.load()->at(i)->export_str(false, false);
							(*prolog->outs) << "." << endl;
						}
						else {
							prolog->out_buf += it->second.load()->at(i)->export_str(false, false);
							prolog->out_buf += ".\n";
						}
					}
			}
			it++;
		}
		lock.unlock();

		return result;
	}
};

class predicate_item_current_predicate : public predicate_item {
public:
	predicate_item_current_predicate(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "current_predicate"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "current_predicate(A/n) incorrect call!" << endl;
			exit(-3);
		}

		bool d1 = positional_vals->at(0)->defined();

		generated_vars * result = new generated_vars();

		if (d1) {
			indicator * t = dynamic_cast<indicator *>(positional_vals->at(0));
			if (!t) {
				std::cout << "current_predicate(A/n) has incorrect parameter!" << endl;
				exit(-3);
			}
			std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
			map< string, std::atomic<vector<term *> *>>::iterator it = CTX->DB->begin();
			while (it != CTX->DB->end()) {
				if (it->first == t->get_name()) {
					CTX->register_db_read(it->first);
					for (int i = 0; i < it->second.load()->size(); i++)
						if (it->second.load()->at(i)->get_args().size() == t->get_arity()) {
							frame_item* r = f->copy(CTX);
							result->push_back(r);

							lock.unlock();
							return result;
						}
				}
				it++;
			}
			lock.unlock();
			delete result;

			return NULL;
		}

		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		map< string, std::atomic<vector<term *> *>>::iterator it = CTX->DB->begin();
		value * t = dynamic_cast<value *>(positional_vals->at(0));
		while (it != CTX->DB->end()) {
			set<int> seen;
			CTX->register_db_read(it->first);
			for (int i = 0; i < it->second.load()->size(); i++) {
				int n = (int)it->second.load()->at(i)->get_args().size();
				if (seen.find(n) == seen.end()) {
					frame_item * r = f->copy(CTX);
					indicator * tt = new indicator(it->first, n);
					if (t->unify(CTX, r, tt)) {
						result->push_back(r);
					}
					else
						delete r;
					tt->free();
					seen.insert(n);
				}
			}
			it++;
		}
		lock.unlock();
		if (result->size() == 0) {
			delete result;
			result = NULL;
		}

		if (result && once && result->size() > 1) {
			for (int i = 1; i < result->size(); i++)
				delete result->at(i);
			result->resize(1);
		}

		return result;
	}
};

class predicate_item_findall : public predicate_item {
public:
	predicate_item_findall(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "findall"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "findall(Template,Term,Result) incorrect call!" << endl;
			exit(-3);
		}

		term * t = dynamic_cast<term *>(positional_vals->at(1));
		var * v = dynamic_cast<var *>(positional_vals->at(1));

		if (!t && !v) {
			std::cout << "findall(Template,Term,Result) has incorrect parameters!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();

		if (v) {
			t = dynamic_cast<term *>(f->get(false, CTX, v->get_name().c_str()));
			if (t) {
				t = dynamic_cast<term *>(t->const_copy(CTX, f, 1));
			} else {
				std::cout << "findall(Template,Term,Result) has incorrect parameters!" << endl;
				exit(-3);
			}
		}
		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		if (t && CTX->DB->find(t->get_name()) != CTX->DB->end()) {
			CTX->register_db_read(t->get_name());
			vector<term *> * terms = (*CTX->DB)[t->get_name()];
			stack_container<value *> L;
			for (int i = 0; i < terms->size(); i++) {
				frame_item * ff = f->copy(CTX);
				term * _dummy = (term *)t->copy(CTX, ff);
				if (_dummy->unify(CTX, ff, terms->at(i))) {
					value * item = positional_vals->at(0)->const_copy(CTX, ff);
					L.push_back(item);
				}
				delete ff;
				_dummy->free();
			}
			if (v) t->free();
			::list * LL = new ::list(L, NULL);
			frame_item * ff = f->copy(CTX);
			if (positional_vals->at(2)->unify(CTX, ff, LL))
				result->push_back(ff);
			else {
				delete ff;
				delete result;
				result = NULL;
			}
			LL->free();
			lock.unlock();
		}
		else {
			std::cout << "Predicate [" << t->get_name() << "] is neither standard nor dynamic!" << endl;
			exit(500);
		}

		return result;
	}
};

class predicate_item_internal_predicate_property : public predicate_item {
public:
	predicate_item_internal_predicate_property(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "predicate_property"; }

	virtual generated_vars * _generate_variants(context * CTX, frame_item * f, term * signature, value * & prop) {
		generated_vars * result = new generated_vars();

		std::unique_lock<std::mutex> lock(prolog->DBILock);
		map< string, set<int> *>::iterator it = prolog->DBIndicators.find(signature->get_name());
		term * prop_val = new term("dynamic");
		int n = (int)signature->get_args().size();
		if (it != prolog->DBIndicators.end()) {
			if (it->second->find(n) != it->second->end()) {
				frame_item * r = f->copy(CTX);
				if (prop->unify(CTX, r, prop_val)) {
					result->push_back(r);
				}
				else
					delete r;
			}
		}
		lock.unlock();
		prop_val->free();
		if (result->size() == 0) {
			delete result;
			result = NULL;
		}

		return result;
	}
};

class predicate_item_predicate_property : public predicate_item_internal_predicate_property {
public:
	predicate_item_predicate_property(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item_internal_predicate_property(_neg, _once, _call, num, c, _prolog) { }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "predicate_property(pred(_,...,_),Prop) incorrect call!" << endl;
			exit(-3);
		}

		term * tt = dynamic_cast<term *>(positional_vals->at(0));
		if (tt) {
			term * functor = new term(tt->get_name());
			for (int i = 0; i < tt->get_args().size(); i++)
				functor->add_arg(CTX, f, new any());
			generated_vars * result = _generate_variants(CTX, f, functor, positional_vals->at(1));
			functor->free();
			return result;
		}

		return NULL;
	}
};

class predicate_item_predicate_property_pi : public predicate_item_internal_predicate_property {
public:
	predicate_item_predicate_property_pi(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item_internal_predicate_property(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "$predicate_property_pi"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "'$predicate_property_pi'(A/n,Prop) incorrect call!" << endl;
			exit(-3);
		}

		indicator * tt = dynamic_cast<indicator *>(positional_vals->at(0));
		if (tt) {
			term * t = new term(tt->get_name());
			for (int i = 0; i < tt->get_arity(); i++)
				t->add_arg(CTX, f, new any());
			generated_vars * result = _generate_variants(CTX, f, t, positional_vals->at(1));
			t->free();
			return result;
		}

		return NULL;
	}
};

class predicate_item_consult : public predicate_item {
public:
	predicate_item_consult(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "consult"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "consult(FName) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "consult(FName) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);

		prolog->consult(positional_vals->at(0)->make_str(), true);

		result->push_back(r);

		return result;
	}
};

class predicate_item_open : public predicate_item {
public:
	predicate_item_open(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "open"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "open(fName,mode,S) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		if (!d1 || !d2 || d3) {
			std::cout << "open(fName,mode,S) incorrect params!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::term * fName = dynamic_cast<::term *>(positional_vals->at(0));
		::term * mode = dynamic_cast<::term *>(positional_vals->at(1));
		::value * S = dynamic_cast<::value *>(positional_vals->at(2));

		::term * id = new term(prolog->open_file(fName->make_str(), mode->make_str()));
		frame_item * r = f->copy(CTX);
		if (S->unify(CTX, r, id))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}
		id->free();
		return result;
	}
};

class predicate_item_close : public predicate_item {
public:
	predicate_item_close(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "close"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "close(S) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "close(S) : undefined parameter!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		::term * S = dynamic_cast<::term *>(positional_vals->at(0));

		prolog->close_file(S->make_str());
		frame_item * r = f->copy(CTX);
		result->push_back(r);

		return result;
	}
};

class predicate_item_mars : public predicate_item {
public:
	predicate_item_mars(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "mars"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "mars(A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "mars(A) indeterminated!" << endl;
			exit(-3);
		}
		::term * t = dynamic_cast<::term *>(positional_vals->at(0));
		if (!t) {
			std::cout << "mars(A) : A is not a term!" << endl;
			exit(-3);
		}
		string arg = t->to_str();
		if (arg == "on")
			prolog->out_buf = "#";
		else {
			string password; // Пароль

			cout << "MARS: Input password: ";
			getline(cin, password);
			fflush(stdin);
			prolog->out_buf.erase(0, 1);

			size_t L = prolog->out_buf.length(); // Длина входного сообщения
			size_t NB = L/16 + (L % 16 == 0 ? 0 : 1); // Число 16-байтных блоков входного сообщения

			unsigned int * _IN = new unsigned int[NB*4];

			memset(_IN, 0, NB*16);
			// Копируем входную строку в _IN
			memmove(_IN, prolog->out_buf.c_str(), L);

			size_t LP = password.length(); // Длина пароля
			size_t NPW = max((size_t)min_n, (size_t)(LP/4 + (LP % 4 == 0 ? 0 : 1))); // Число 4-байтных слов пароля

			size_t n; // Число 4-байтных блоков ключа
			if (NPW > max_n)
				n = max_n;
			else
				n = NPW;
			unsigned int * KEY = new unsigned int[n];
			memset(KEY, 0, n*4);
			// Копируем пароль в KEY
			memmove(KEY, password.c_str(), min(LP, n*4));
			unsigned int ExKey[40]; // Расширенный ключ
			expand_key(n, KEY, ExKey);

			// Кодирование
			for (int i = 0; i < NB; i++) {
				code_direct(&_IN[i*4], ExKey);
				code_core(&_IN[i*4], ExKey);
				code_reverse(&_IN[i*4], ExKey);
			}
			std::ofstream out(arg, ios_base::binary);
			if (out) {
				out.write((char *) _IN, NB*16);
				out.close();
			} else
				cout << "Can't write to file!" << endl;
			delete[] _IN;
			delete[] KEY;
			prolog->out_buf.clear();
		}

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_mars_decode : public predicate_item {
public:
	predicate_item_mars_decode(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "mars_decode"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "mars_decode(FName) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "mars_decode(FName) indeterminated!" << endl;
			exit(-3);
		}
		::term * t = dynamic_cast<::term *>(positional_vals->at(0));
		if (!t) {
			std::cout << "mars_decode(FName) : FName is not a term!" << endl;
			exit(-3);
		}
		string arg = t->to_str();

		string password; // Пароль

		std::streamoff L;

		std::ifstream inf(arg, ios_base::binary);
		if (inf) {
			inf.seekg(0, std::ios::end);
			L = inf.tellg();
			inf.seekg(0, std::ios::beg);

			cout << "MARS: Input password: ";
			getline(cin, password);
			fflush(stdin);
		}
		else {
			cout << "Can't read from file!" << endl;
			L = 0;
		}

		size_t NB = (L / 16 + (L % 16 == 0 ? 0 : 1)); // Число 16-байтных блоков входного сообщения

		unsigned int * _IN = new unsigned int[NB * 4];

		memset(_IN, 0, NB * 16);
		// Копируем входную строку в IN
		if (inf) {
			inf.read((char *)_IN, L);
			inf.close();
		}

		size_t LP = password.length(); // Длина пароля
		size_t NPW = max((size_t)min_n, (size_t)(LP / 4 + (LP % 4 == 0 ? 0 : 1))); // Число 4-байтных слов пароля

		size_t n; // Число 4-байтных блоков ключа
		if (NPW > max_n)
			n = max_n;
		else
			n = NPW;

		unsigned int * KEY = new unsigned int[n];

		memset(KEY, 0, n * 4);
		// Копируем пароль в KEY
		memmove(KEY, password.c_str(), min(LP, n * 4));

		unsigned int ExKey[40]; // Расширенный ключ
		expand_key(n, KEY, ExKey);

		// Декодирование
		for (int i = 0; i < NB; i++) {
			decode_direct(&_IN[i * 4], ExKey);
			decode_core(&_IN[i * 4], ExKey);
			decode_reverse(&_IN[i * 4], ExKey);
		}

		// Создаем выходную строку из декодированных блоков
		std::stringstream sst;
		string buf;
		sst.write((char *)_IN, L);
		while (getline(sst, buf))
			(*prolog->outs) << buf << endl;
		delete[] _IN;
		delete[] KEY;

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_unset : public predicate_item {
public:
	predicate_item_unset(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "unset"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "unset(A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "unset(A) indeterminated!" << endl;
			exit(-3);
		}

		term* t = dynamic_cast<term*>(positional_vals->at(0));
		if (t && t->get_args().size() == 0) {
			frame_item* r = f->copy(CTX);

			r->unset(false, CTX, t->get_name().c_str());

			generated_vars* result = new generated_vars();

			result->push_back(r);

			return result;
		}
		else
			return NULL;
	}
};

class predicate_item_write : public predicate_item {
public:
	predicate_item_write(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "write"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() < 1 || positional_vals->size() > 2) {
			std::cout << "write(A)/write(S,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1 || positional_vals->size() == 2 && !positional_vals->at(1)->defined()) {
			std::cout << "write(A)/write(S,A) indeterminated!" << endl;
			exit(-3);
		}
		if (positional_vals->size() == 1)
			if (prolog->out_buf.size() == 0)
				positional_vals->at(0)->write(prolog->outs);
			else
				prolog->out_buf += positional_vals->at(0)->to_str();
		else {
			::term * S = dynamic_cast<::term *>(positional_vals->at(0));
			int fn;
			prolog->get_file(S->make_str(), fn) << positional_vals->at(1)->to_str();
		}

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_write_to_atom : public predicate_item {
public:
	predicate_item_write_to_atom(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "write_to_atom"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "write_to_atom(A,What) incorrect call!" << endl;
			exit(-3);
		}
		bool d2 = positional_vals->at(1)->defined();
		if (!d2) {
			std::cout << "write_to_atom(A,What) indeterminated!" << endl;
			exit(-3);
		}
		frame_item * ff = f->copy(CTX);
		term * t = new term(positional_vals->at(1)->to_str());
		generated_vars * result = NULL;
		if (positional_vals->at(0)->unify(CTX, ff, t)) {
			result = new generated_vars();

			result->push_back(ff);
		} else
			delete ff;

		t->free();

		return result;
	}
};

class predicate_item_write_term : public predicate_item {
public:
	predicate_item_write_term(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "write_term"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() < 2 || positional_vals->size() > 3) {
			std::cout << "write_term(A,[opts])/write(S,A,[opts]) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		frame_item * ff = f->copy(CTX);
		term * quoted = new term("quoted");
		quoted->add_arg(CTX, ff, new term("true"));
		stack_container<value *> LL;
		LL.push_back(quoted);
		::list * LQ = new ::list(LL, NULL);
		if (!d1 || !d2 || positional_vals->size() == 3 &&
					!positional_vals->at(2)->defined()) {
			std::cout << "write_term(A,[opts])/write(S,A,[opts]) indeterminated!" << endl;
			exit(-3);
		}
		if (positional_vals->size() == 2 && LQ->unify(CTX, ff, positional_vals->at(1)) ||
			positional_vals->size() == 3 && LQ->unify(CTX, ff, positional_vals->at(2)))
			if (positional_vals->size() == 2)
				if (prolog->out_buf.size() == 0)
					(*prolog->outs) << (positional_vals->at(0)->export_str());
				else
					prolog->out_buf += positional_vals->at(0)->export_str();
			else {
				::term * S = dynamic_cast<::term *>(positional_vals->at(0));
				int fn;
				prolog->get_file(S->make_str(), fn) << positional_vals->at(1)->export_str();
			}
		else
			if (positional_vals->size() == 2)
				if (prolog->out_buf.size() == 0)
					positional_vals->at(0)->write(prolog->outs);
				else
					prolog->out_buf += positional_vals->at(0)->to_str();
			else {
				::term * S = dynamic_cast<::term *>(positional_vals->at(0));
				int fn;
				prolog->get_file(S->make_str(), fn) << positional_vals->at(1)->to_str();
			}

		generated_vars * result = new generated_vars();

		result->push_back(ff);

		LQ->free();

		return result;
	}
};

class predicate_item_write_term_to_atom : public predicate_item {
public:
	predicate_item_write_term_to_atom(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "write_term_to_atom"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 3) {
			std::cout << "write_term_to_atom(A,What,[opts]) incorrect call!" << endl;
			exit(-3);
		}
		bool d2 = positional_vals->at(1)->defined();
		bool d3 = positional_vals->at(2)->defined();
		frame_item * ff = f->copy(CTX);
		term * quoted = new term("quoted");
		quoted->add_arg(CTX, ff, new term("true"));
		stack_container<value *> LL;
		LL.push_back(quoted);
		::list * LQ = new ::list(LL, NULL);
		if (!d2 || !d3) {
			std::cout << "write_term_to_atom(A,What,[opts]) indeterminated!" << endl;
			exit(-3);
		}
		std::string What;
		if (LQ->unify(CTX, ff, positional_vals->at(2)))
			What = positional_vals->at(1)->export_str();
		else
			What = positional_vals->at(1)->to_str();
		term * W = new term(What);
		generated_vars * result = NULL;
		if (positional_vals->at(0)->unify(CTX, ff, W)) {
			result = new generated_vars();

			result->push_back(ff);
		} else
			delete ff;
		W->free();
		LQ->free();

		return result;
	}
};

class predicate_item_nl : public predicate_item {
public:
	predicate_item_nl(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "nl"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "nl/nl(S) incorrect call!" << endl;
			exit(-3);
		}

		if (positional_vals->size() == 0)
			if (prolog->out_buf.size() == 0)
				(*prolog->outs) << endl;
			else
				prolog->out_buf += "\n";
		else {
			::term * S = dynamic_cast<::term *>(positional_vals->at(0));
			int fn;
			prolog->get_file(S->make_str(), fn) << endl;
		}

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_file_exists : public predicate_item {
public:
	predicate_item_file_exists(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "file_exists"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "file_exists(F) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "file_exists(F) indeterminated!" << endl;
			exit(-3);
		}
		term * t = dynamic_cast<term*>(positional_vals->at(0));
		if (t && exists(t->get_name())) {
			generated_vars * result = new generated_vars();

			result->push_back(f->copy(CTX));

			return result;
		} else
			return NULL;
	}
};

class predicate_item_unlink : public predicate_item {
public:
	predicate_item_unlink(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "unlink"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "unlink(F) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "unlink(F) indeterminated!" << endl;
			exit(-3);
		}
		term * t = dynamic_cast<term*>(positional_vals->at(0));
		if (t && exists(t->get_name())) {
			remove(t->get_name());
		}

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_rename_file : public predicate_item {
public:
	predicate_item_rename_file(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "rename_file"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "rename_file(Old,New) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 || !d2) {
			std::cout << "rename_file(Old,New) indeterminated!" << endl;
			exit(-3);
		}
		term * t_old = dynamic_cast<term*>(positional_vals->at(0));
		term * t_new = dynamic_cast<term*>(positional_vals->at(1));
		if (t_old && exists(t_old->get_name())) {
			remove(t_new->get_name());
			rename(t_old->get_name(), t_new->get_name());
		} else {
			std::cout << "rename_file(Old,New) error!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_tell : public predicate_item {
public:
	predicate_item_tell(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "tell"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "tell(FName) incorrect call!" << endl;
			exit(-3);
		}

		if (!positional_vals->at(0)->defined()) {
			std::cout << "tell(FName) indeterminated!" << endl;
			exit(-3);
		}

		prolog->current_output = positional_vals->at(0)->make_str();
		if (prolog->current_output == STD_OUTPUT)
			prolog->outs = &std::cout;
		else
			prolog->outs = new std::ofstream(prolog->current_output, ios::out | ios::trunc);

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_see : public predicate_item {
public:
	predicate_item_see(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "see"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "see(FName) incorrect call!" << endl;
			exit(-3);
		}

		if (!positional_vals->at(0)->defined()) {
			std::cout << "see(FName) indeterminated!" << endl;
			exit(-3);
		}

		prolog->current_input = positional_vals->at(0)->make_str();
		if (prolog->current_input == STD_INPUT)
			prolog->ins = &std::cin;
		else
			prolog->ins = new std::ifstream(prolog->current_input, ios::in);

		generated_vars * result = new generated_vars();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_telling : public predicate_item {
public:
	predicate_item_telling(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "telling"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "telling(FName) incorrect call!" << endl;
			exit(-3);
		}

		::term * S = new term(prolog->current_output);

		generated_vars * result = new generated_vars();
		frame_item * ff = f->copy(CTX);

		if (positional_vals->at(0)->unify(CTX, ff, S))
			result->push_back(ff);
		else {
			delete ff;
			delete result;
			result = NULL;
		}

		S->free();

		return result;
	}
};

class predicate_item_seeing : public predicate_item {
public:
	predicate_item_seeing(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "seeing"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 1) {
			std::cout << "seeing(FName) incorrect call!" << endl;
			exit(-3);
		}

		::term * S = new term(prolog->current_input);

		generated_vars * result = new generated_vars();
		frame_item * ff = f->copy(CTX);

		if (positional_vals->at(0)->unify(CTX, ff, S))
			result->push_back(ff);
		else {
			delete ff;
			delete result;
			result = NULL;
		}

		S->free();

		return result;
	}
};

class predicate_item_told : public predicate_item {
public:
	predicate_item_told(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "told"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 0) {
			std::cout << "told/0 incorrect call!" << endl;
			exit(-3);
		}

		if (prolog->current_output != STD_OUTPUT)
			dynamic_cast<std::basic_ofstream<char> *>(prolog->outs)->close();
		prolog->outs = &std::cout;
		prolog->current_output = STD_OUTPUT;

		generated_vars * result = new generated_vars();
		frame_item * ff = f->copy(CTX);

		result->push_back(ff);

		return result;
	}
};

class predicate_item_seen : public predicate_item {
public:
	predicate_item_seen(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "seen"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() > 0) {
			std::cout << "seen/0 incorrect call!" << endl;
			exit(-3);
		}

		if (prolog->current_input != STD_INPUT)
			dynamic_cast<std::basic_ifstream<char> *>(prolog->ins)->close();
		prolog->ins = &cin;
		prolog->current_input = STD_INPUT;

		generated_vars * result = new generated_vars();
		frame_item * ff = f->copy(CTX);

		result->push_back(ff);

		return result;
	}
};

class predicate_item_get_or_peek_char : public predicate_item {
	bool peek;
public:
	predicate_item_get_or_peek_char(bool _peek, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog), peek(_peek) { }

	virtual const string get_id() { return peek ? "peek_char" : "get_char"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << (peek ? "peek" : "get") << "_char(S,A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1) {
			std::cout << (peek ? "peek" : "get") << "_char(S,A) : S is indeterminated!" << endl;
			exit(-3);
		}

		::term * S = dynamic_cast<::term *>(positional_vals->at(0));

		int fn;
		std::basic_fstream<char> & ff = prolog->get_file(S->make_str(), fn);

		char CS[2] = { 0 };
		value * v = NULL;
		if (peek) {
			int V = ff.peek();
			if (V == EOF) v = new term("end_of_file");
			else {
				CS[0] = V;
				v = new term(CS);
			}
		}
		else {
			ff.get(CS[0]);
			if (ff.eof()) v = new term("end_of_file");
			else
				v = new term(CS);
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);

		if (positional_vals->at(1)->unify(CTX, r, v))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}
		v->free();

		return result;
	}
};

class predicate_item_at_end_of_stream : public predicate_item {
public:
	predicate_item_at_end_of_stream(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "at_end_of_stream"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "at_end_of_stream(S) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "at_end_of_stream(S) : S is indeterminated!" << endl;
			exit(-3);
		}

		::term * S = dynamic_cast<::term *>(positional_vals->at(0));

		int fn;
		std::basic_fstream<char> & ff = prolog->get_file(S->make_str(), fn);

		if (ff.peek() == EOF) {
			generated_vars * result = new generated_vars();
			frame_item * r = f->copy(CTX);

			result->push_back(r);

			return result;
		}
		else
			return NULL;
	}
};

class predicate_item_get_code : public predicate_item {
public:
	predicate_item_get_code(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "get_code"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "get_code(S,N) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1) {
			std::cout << "get_code(S,N) : S is indeterminated!" << endl;
			exit(-3);
		}

		::term * S = dynamic_cast<::term *>(positional_vals->at(0));

		int fn;
		std::basic_fstream<char> & ff = prolog->get_file(S->make_str(), fn);

		char C;
		value * v = NULL;
		ff.get(C);
		if (ff.eof()) v = new term("end_of_file");
		else
			v = new int_number(C);

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);

		if (positional_vals->at(1)->unify(CTX, r, v))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}
		v->free();

		return result;
	}
};

class predicate_item_char_code : public predicate_item {
public:
	predicate_item_char_code(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "char_code"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "char_code(S,C) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1 && !d2) {
			std::cout << "char_code(S,C) : indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = NULL;
		frame_item * r = f->copy(CTX);

		if (d1) {
			::term * S = dynamic_cast<::term *>(positional_vals->at(0));
			string SC = unescape(S->get_name());
			if (SC.length() != 1) {
				std::cout << "char_code(S,C) : S is not a char!" << endl;
				exit(-4);
			}
			int_number * v = new int_number(SC[0]);
			if (positional_vals->at(1)->unify(CTX, r, v)) {
				result = new generated_vars();
				result->push_back(r);
			} else
				delete r;
			v->free();
		}
		else {
			int_number * C = dynamic_cast<int_number *>(positional_vals->at(1));
			if (!C) {
				std::cout << "char_code(S,C) : C is not an integer!" << endl;
				exit(-4);
			}
			term * v = new term(string(1, (char)(0.5 + C->get_value())));
			if (positional_vals->at(0)->unify(CTX, r, v)) {
				result = new generated_vars();
				result->push_back(r);
			}
			else
				delete r;
			v->free();
		}

		return result;
	}
};

class predicate_item_set_iteration_star_packet : public predicate_item {
public:
	predicate_item_set_iteration_star_packet(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "set_iteration_star_packet"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "set_iteration_star_packet(R) incorrect call!" << endl;
			exit(-3);
		}
		generated_vars* result = NULL;
		int_number * a = dynamic_cast<int_number*>(positional_vals->at(0));
		if (!a || (int)(a->get_value()) < 1) {
			std::cout << "set_iteration_star_packet(R): R mus be greater or equal to 1!" << endl;
			exit(-3);
		}
		frame_item* ff = f->copy(CTX);
		result = new generated_vars();
		result->push_back(ff);

		prolog->VARLOCK.lock();
		prolog->ITERATION_STAR_PACKET = (int) a->get_value();
		prolog->VARLOCK.unlock();

		return result;
	}
};

class predicate_item_random : public predicate_item {
public:
	predicate_item_random(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "random"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1 && positional_vals->size() != 3) {
			std::cout << "random(R)/random(Base,Max,Number) incorrect call!" << endl;
			exit(-3);
		}
		generated_vars * result = NULL;
		if (positional_vals->size() == 1) {
			value * a = dynamic_cast<value *>(positional_vals->at(0));
			frame_item * ff = f->copy(CTX);
			float_number * fv = new float_number(1.0*rand()/RAND_MAX);
			if (a->unify(CTX, ff, fv)) {
				result = new generated_vars();
				result->push_back(ff);
			} else {
				delete ff;
			}
			fv->free();
		}
		else {
			bool d1 = positional_vals->at(0)->defined();
			bool d2 = positional_vals->at(1)->defined();
			if (!d1 || !d2) {
				std::cout << "random(Base,Max,Number) indeterminated!" << endl;
				exit(-3);
			}
			int_number * base = dynamic_cast<int_number *>(positional_vals->at(0));
			int_number * max = dynamic_cast<int_number *>(positional_vals->at(1));
			value * a = positional_vals->at(2);
			if (!base || !max) {
				std::cout << "random(Base,Max,Number) error call!" << endl;
				exit(-3);
			}
			frame_item * ff = f->copy(CTX);
			int_number * iv = new int_number(((long long)base->get_value() + rand() % ((long long)max->get_value() - (long long)base->get_value())));
			if (a->unify(CTX, ff, iv)) {
				result = new generated_vars();
				result->push_back(ff);
			}
			else {
				delete ff;
			}
			iv->free();
		}

		return result;
	}
};

class predicate_item_randomize : public predicate_item {
public:
	predicate_item_randomize(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "randomize"; }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "randomize: extra arguments!" << endl;
			exit(-3);
		}
		generated_vars * result = new generated_vars();
		frame_item * ff = f->copy(CTX);
		srand((unsigned int)time(NULL) ^ (unsigned int)clock());
		result->push_back(ff);

		return result;
	}
};

class predicate_item_read_token_common : public predicate_item {
public:
	predicate_item_read_token_common(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual bool is_not_pure(std::set<string>& work_set) {
		work_set.insert(get_id());
		return true;
	}

	virtual generated_vars * get_token(context * CTX, frame_item * f, vector<value *> * & positional_vals, int arg_num, std::basic_istream<char> & ff) {
		streampos beg;
		string line;
		size_t p = 0;
		do {
			beg = ff.tellg();
			getline(ff, line);
			p = 0;
			bypass_spaces(line, p);
		} while (!ff.eof() && p == line.length());
		
		frame_item * dummy = new frame_item();
		value * v = NULL;
		if (p < line.length())
			if (line[p] >= '0' && line[p] <= '9') {
				v = prolog->parse(CTX, false, true, dummy, line, p);
				ff.seekg(beg + (streamoff)p);
			}
			else if (line[p] == '\'' || line[p] == '"') {
				v = prolog->parse(CTX, false, true, dummy, line, p);
				term * _v = new term("string");
				_v->add_arg(CTX, dummy, new term(unescape(v->make_str())));
				v->free();
				v = _v;
				ff.seekg(beg + (streamoff)p);
			}
			else if (line[p] >= 'A' && line[p] <= 'Z') {
				v = prolog->parse(CTX, false, true, dummy, line, p);
				term * _v = new term("var");
				_v->add_arg(CTX, dummy, new term(((var *)v)->get_name()));
				v->free();
				v = _v;
				ff.seekg(beg + (streamoff)p);
			}
			else if (line[p] != '(' && line[p] != ')' &&
				line[p] != '[' && line[p] != ']' && line[p] != '{' && line[p] != '}' &&
				line[p] != '|') {
				size_t st = p;
				if (line[p] == '_' || isalnum(line[p]))
					while (p < line.length() && (line[p] == '_' || isalnum(line[p])))
						p++;
				else
					p++;
				v = new term(line.substr(st, p - st));
				ff.seekg(beg + (streamoff)p);
			}
			else {
				char C[2] = { 0 };
				ff.seekg(beg + (streamoff)p);
				ff.get(C[0]);
				v = new term("punct");
				if (!ff.eof()) {
					((term *)v)->add_arg(CTX, dummy, new term(C));
				}
				else {
					((term *)v)->add_arg(CTX, dummy, new term("end_of_file"));
				}
			}
		else {
			v = new term("punct");
			((term *)v)->add_arg(CTX, dummy, new term("end_of_file"));
		}

		generated_vars * result = new generated_vars();
		frame_item * r = f->copy(CTX);

		delete dummy;

		if (v && positional_vals->at(arg_num)->unify(CTX, r, v))
			result->push_back(r);
		else {
			delete result;
			result = NULL;
			delete r;
		}
		v->free();

		return result;
	}
};

class predicate_item_read_token : public predicate_item_read_token_common {
public:
	predicate_item_read_token(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item_read_token_common(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "read_token"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1 && positional_vals->size() != 2) {
			std::cout << "read_token(A)/read_token(S,A) incorrect call!" << endl;
			exit(-3);
		}
		if (positional_vals->size() == 2) {
			bool d1 = positional_vals->at(0)->defined();
			bool d2 = positional_vals->at(1)->defined();
			if (!d1) {
				std::cout << "read_token(S,A) : S is indeterminated!" << endl;
				exit(-3);
			}

			::term * S = dynamic_cast<::term *>(positional_vals->at(0));

			int fn;
			std::basic_fstream<char> & ff = prolog->get_file(S->make_str(), fn);

			return get_token(CTX, f, positional_vals, 1, ff);
		} else {
			return get_token(CTX, f, positional_vals, 0, *(prolog->ins));
		}
	}
};

class predicate_item_read_token_from_atom : public predicate_item_read_token_common {
public:
	predicate_item_read_token_from_atom(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item_read_token_common(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "read_token_from_atom"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 2) {
			std::cout << "read_token_from_atom(A,T) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		bool d2 = positional_vals->at(1)->defined();
		if (!d1) {
			std::cout << "read_token_from_atom(A,T) : A is indeterminated!" << endl;
			exit(-3);
		}

		::term * A = dynamic_cast<::term *>(positional_vals->at(0));

		std::stringstream ff(A->make_str());

		return get_token(CTX, f, positional_vals, 1, ff);
	}
};

class predicate_item_assert : public predicate_item {
	bool z;
public:
	predicate_item_assert(bool _z, bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog), z(_z) { }

	virtual const string get_id() { return z ? "assertz" : "asserta"; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "assert(A) incorrect call!" << endl;
			exit(-3);
		}
		bool d1 = positional_vals->at(0)->defined();
		if (!d1) {
			std::cout << "assert(A) indeterminated!" << endl;
			exit(-3);
		}

		generated_vars * result = new generated_vars();
		term * t = dynamic_cast<term *>(positional_vals->at(0));
		if (!t) {
			std::cout << "assert(A) : A is not a term!" << endl;
			exit(-3);
		}

		string atid = t->get_name();
		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		map<string, std::atomic<vector<term*>*>>::iterator it = CTX->DB->find(atid);
		if (it == CTX->DB->end()) {
			(*CTX->DB)[atid] = new vector<term*>();
			it = CTX->DB->find(atid);
		}
		
		// CTX->register_db_read(atid);

		vector<term *> * terms = it->second;
		term* tt = (term*)t->const_copy(CTX, f);
		if (z) {
			CTX->register_db_write(atid, jInsert, tt, (int)terms->size());
			terms->push_back(tt);
		}
		else {
			CTX->register_db_write(atid, jInsert, tt, 0);
			terms->insert(terms->begin(), tt);
		}

		lock.unlock();

		std::unique_lock<std::mutex> dbilock(prolog->DBILock);
		if (prolog->DBIndicators.find(atid) == prolog->DBIndicators.end()) {
			set<int> * inds = new set<int>;
			inds->insert((int)t->get_args().size());
			prolog->DBIndicators[atid] = inds;
		}
		else {
			set<int> * inds = prolog->DBIndicators[atid];
			inds->insert((int)t->get_args().size());
		}
		dbilock.unlock();

		result->push_back(f->copy(CTX));

		return result;
	}
};

class predicate_item_retract : public predicate_item {
	bool all;
public:
	predicate_item_retract(bool _all, bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog), all(_all) { }

	virtual const string get_id() { return all ? "retractall" : "retract"; }

	virtual generated_vars* generate_variants(context * CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 1) {
			std::cout << "retract[all](A) incorrect call!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();
		term* t = dynamic_cast<term*>(positional_vals->at(0));
		if (!t) {
			std::cout << "retract[all](A) : A is not a term!" << endl;
			exit(-3);
		}

		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		map<string, std::atomic<vector<term*>*>>::iterator itdb = CTX->DB->find(t->get_name());
		if (itdb == CTX->DB->end()) {
			(*CTX->DB)[t->get_name()] = new vector<term*>();
			itdb = CTX->DB->find(t->get_name());
		}
		CTX->register_db_read(itdb->first);

		vector<term*>* terms = itdb->second.load();
		vector<term*>::iterator it = terms->begin();
		while (it != terms->end()) {
			term* tt = (term*)t->const_copy(CTX, f);
			if (tt->unify(CTX, f, *it)) {
				if (all) {
					CTX->register_db_write(itdb->first, jDelete, *it, (int)(it - terms->begin()));
					it = terms->erase(it);
				}
				else {
					frame_item* ff = f->copy(CTX);
					value* v1 = new int_number((long long)(*it));
					ff->lock();
					ff->set(true, CTX, "$RETRACTOR$", v1);
					v1->free();
					value* v3 = new term(itdb->first);
					ff->set(true, CTX, "$FUNCTOR$", v3);
					ff->unlock();
					v3->free();
					result->push_back(ff);
					tt->free();
					break;
				}
			}
			else
				it++;
			tt->free();
		}

		if (all)
			result->push_back(f->copy(CTX));
		lock.unlock();

		if (result && once && result->size() > 1) {
			for (int i = 1; i < result->size(); i++)
				delete result->at(i);
			result->resize(1);
		}

		return result;
	}

	virtual bool execute(context * CTX, frame_item* &f, int i, generated_vars* variants) {
		if (all) return true;

		std::unique_lock<std::mutex> lock(*CTX->DBLOCK);
		f->lock();
		string iid = ((term*)f->get(true, CTX, "$FUNCTOR$"))->get_name();
		f->get(true, CTX, "$FUNCTOR$")->free();
		f->unset(true, CTX, "$FUNCTOR$");

		map<string, std::atomic<vector<term*>*>>::iterator itdb = CTX->DB->find(iid);

		CTX->register_db_read(iid);

		term* v = (term*)((long long)(0.5 + ((int_number*)f->get(true, CTX, "$RETRACTOR$"))->get_value()));
		f->get(true, CTX, "$RETRACTOR$")->free();
		f->unset(true, CTX, "$RETRACTOR$");
		f->unlock();
		if (v && itdb->second.load()) {
			vector<term*>::iterator it = find(itdb->second.load()->begin(), itdb->second.load()->end(), v);
			if (it != itdb->second.load()->end()) {
				CTX->register_db_write(iid, jDelete, *it, (int)(it - itdb->second.load()->begin()));
				itdb->second.load()->erase(it);
			}
			lock.unlock();
			return true;
		}
		else {
			lock.unlock();
			return false;
		}
	}
};

class predicate_item_fork : public predicate_item {
	// predicate_item* start; // Starts from get_start()
	int ending_number;
	value * n_threads;
	bool locals_in_forked;
	bool transactable_facts;
public:
	predicate_item_fork(bool locals, bool transactable_facts, bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog), ending_number(0) {
		this->locals_in_forked = locals;
		this->transactable_facts = transactable_facts;
		this->n_threads = new int_number(1);
	}
	virtual ~predicate_item_fork() {
		if (n_threads)
			n_threads->free();
	}

	virtual const string get_id() { return "fork"; }

	virtual generated_vars* generate_variants(context * CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "fork branch incorrect call!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();

		frame_item* ff = f->copy(CTX);
		result->push_back(ff);

		return result;
	}

	virtual void set_n_threads(value* v) {
		if (n_threads)
			n_threads->free();
		n_threads = v;
		if (n_threads)
			n_threads->use();
	}

	virtual void set_end(int end) {
		ending_number = end;
	}

	virtual predicate_item* get_next(int variant) {
		return parent->get_item(ending_number);
	}

	virtual predicate_item* get_start(int variant) {
		return predicate_item::get_next(variant);
	}

	virtual predicate_item* get_last(int variant) {
		return ending_number == 0 ? NULL : parent->get_item(ending_number-1);
	}

	virtual bool execute(context * CTX, frame_item* &f, int i, generated_vars* variants) {
		int N = 1;
		int_number* ni = NULL;

		var* nv = dynamic_cast<var*>(n_threads);
		if (nv) {
			value* v = f->get(false, CTX, nv->get_name().c_str());

			if (!v || !v->defined()) {
				std::cout << "Number of threads [" << nv->get_name() << "] is not defined!" << endl;
				exit(-3);
			}

			ni = dynamic_cast<int_number*>(v);

			if (ni == NULL) {
				std::cout << "Value of number of threads [" << nv->get_name() << "] is not int!" << endl;
				exit(-3);
			}
		}
		else {
			ni = dynamic_cast<int_number*>(n_threads);
			if (ni == NULL) {
				std::cout << "Number of threads must be a variable or int!" << endl;
				exit(-3);
			}
		}
		if (ni->get_value() >= 0)
			N = (int)(0.5 + ni->get_value());
		else
			N = (int)(-0.5 + ni->get_value());
		if (N < 1) {
			std::cout << "Incorrect number of threads [" << N << "] !" << endl;
			exit(-3);
		}
		// Process
		CTX->SEQUENTIAL.push(false);
		for (int m = 0; m < N; m++) {
			CTX->add_page(locals_in_forked, transactable_facts, this, f->tcopy(CTX, prolog, true), parent->get_item(self_number+1), parent->get_item(ending_number), prolog);
		}

		return true;
	}
};

class predicate_item_join : public predicate_item {
	value* k;
	bool ending;
public:
	predicate_item_join(bool _ending, value * _k, bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) {
		ending = _ending;
		k = _k;
	}
	virtual ~predicate_item_join() {
		if (k)
			k->free();
	}

	virtual const string get_id() { return "join"; }

	virtual void bind(bool starring) { }

	virtual generated_vars* generate_variants(context * CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "join branches incorrect call!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();

		frame_item* ff = f->copy(CTX);
		result->push_back(ff);

		return result;
	}

	virtual bool execute(context * CTX, frame_item* &f, int i, generated_vars* variants) {
		if (this->conditional_star_mode && !this->is_starred)
			return true;

		if ((int)CTX->SEQUENTIAL.size() == 0 || !CTX->SEQUENTIAL.top()) {
			int K = -1;
			int_number* ni = NULL;

			var* nv = dynamic_cast<var*>(k);
			if (nv) {
				value* v = f->get(false, CTX, nv->get_name().c_str());

				if (!v || !v->defined()) {
					std::cout << "Number of &-joined threads [" << nv->get_name() << "] is not defined!" << endl;
					exit(-3);
				}

				ni = dynamic_cast<int_number*>(v);

				if (ni == NULL) {
					std::cout << "Value of number of &-joined threads [" << nv->get_name() << "] is not int!" << endl;
					exit(-3);
				}
			}
			else {
				ni = dynamic_cast<int_number*>(k);
				if (ni == NULL) {
					std::cout << "Number of &-joined threads must be a variable or int!" << endl;
					exit(-3);
				}
			}
			if (ni->get_value() >= 0)
				K = (int)(0.5 + ni->get_value());
			else
				K = (int)(-0.5 + ni->get_value());

			if (CTX->SEQUENTIAL.size())
				CTX->SEQUENTIAL.pop();
			// Process
			int dummy = 0;
			return CTX->join(false, K, f, prolog, dummy, NULL);
		}
		else {
			predicate_item* starting = CTX->SEQ_START.top();
			predicate_item* ending = CTX->SEQ_END.top();
			tframe_item* new_f = f->tcopy(CTX, prolog, true);
			new_f->set_written_new(CTX->SEQ_RESULT.top());
			CTX->add_page(false, true, this, new_f, starting, ending, prolog);

			prolog->VARLOCK.lock();
			unsigned short warp_size = (unsigned short)prolog->ITERATION_STAR_PACKET;
			prolog->VARLOCK.unlock();

			generated_vars* _variants = CTX->TRACE[CTX->TRACE.size() - 2];
			int& _i = CTX->ptrTRACE[CTX->ptrTRACE.size() - 2];

			CTX->SEQUENTIAL.pop();

			bool must_end = !_variants || !_variants->has_variant(_i + 1);
			int offset = 0;

			if (must_end || CTX->CONTEXTS.size() >= max(warp_size, (unsigned short)2)) {
				vector<frame_item*> rest;
				size_t n = CTX->CONTEXTS.size();
				frame_item* result = CTX->SEQ_RESULT.top()->copy(CTX);
				if (CTX->join(true, -1, result, prolog, offset, &rest)) {
					size_t undo = n - offset;
					_i -= (int)undo;
					_variants->undo(_i, &rest);

					delete f;
					f = result;
					if (variants)
						variants->at(i) = f;

					return true;
				}
				else {
					delete result;
					return false;
				}
			}
			else
				return false;
		}
	}
};

class predicate_item_rollback : public predicate_item {
public:
	predicate_item_rollback(bool _neg, bool _once, bool _call, int num, clause* c, interpreter* _prolog) :
		predicate_item(_neg, _once, _call, num, c, _prolog) { }

	virtual const string get_id() { return "rollback"; }

	virtual generated_vars* generate_variants(context* CTX, frame_item* f, vector<value*>*& positional_vals) {
		if (positional_vals->size() != 0) {
			std::cout << "rollback incorrect call!" << endl;
			exit(-3);
		}

		generated_vars* result = new generated_vars();

		frame_item* ff = f->copy(CTX);
		result->push_back(ff);

		return result;
	}

	virtual bool execute(context* CTX, frame_item* &f, int i, generated_vars* variants) {
		if (CTX)
			CTX->set_rollback(true);
		// Process
		return true;
	}
};

bool interpreter::block_process(context * CNT, bool clear_flag, bool cut_flag, predicate_item * frontier, bool frontier_enough) {
	std::list<int>::iterator itf = CNT->FLAGS.end();
	bool passed_frontier = false;
	int nn = (int)(CNT->TRACE.size() - 1);
	while (nn >= 0) {
		generated_vars * T = CNT->TRACE[nn];
		vector<value *> ** A = CNT->TRACEARGS[nn];
		predicate_item * WHO = CNT->TRACERS[nn];
		int n = CNT->ptrTRACE[nn];
		int flags = *(--itf);
		int level = CNT->LEVELS[nn];

		if (cut_flag && frontier && CNT->PARENT_CALLS.size() && CNT->PARENT_CALLS.top() && CNT->PARENT_CALLS.top()->get_parent() &&
			WHO && WHO->get_parent() == CNT->PARENT_CALLS.top()->get_parent() &&
			n == CNT->PARENT_CALL_VARIANT.top() &&
			level == CNT->PARENT_CALLS.size() - 1)
			return false;

		if (cut_flag) {
			if (T) T->trunc_from(n + 1);
			if (A && *A) {
				for (int j = 0; j < (*A)->size(); j++)
					(*A)->at(j)->free();
				delete *A;
				*A = NULL;
			}
		}

		if ((flags & (call_flag | ::once_flag))) {
			if (clear_flag) *itf &= ~(call_flag | ::once_flag);
			return false;
		}

		if (cut_flag && CNT->PARENT_CALLS.size() && CNT->PARENT_CALLS.top() && CNT->PARENT_CALLS.top()->get_parent() &&
			WHO && WHO->get_parent() == CNT->PARENT_CALLS.top()->get_parent() &&
			n == CNT->PARENT_CALL_VARIANT.top() &&
			level == CNT->PARENT_CALLS.size()-1)
			return false;

		if (cut_flag && passed_frontier &&
			WHO && dynamic_cast<predicate_left_bracket *>(WHO) &&
			!dynamic_cast<predicate_left_bracket *>(WHO)->is_inserted() &&
			level == CNT->PARENT_CALLS.size())
			return false;

		if (cut_flag && !passed_frontier && frontier &&
			WHO == frontier &&
			level == CNT->PARENT_CALLS.size())
			passed_frontier = true;

		if (passed_frontier && frontier_enough)
			return false;

		nn--;
	}

	return true;
}

value * interpreter::parse(context * CTX, bool exit_on_error, bool parse_complex_terms, frame_item * ff, const string & s, size_t & p) {
	if (p < s.length()) {
		value * result = NULL;

		if (!bypass_spaces(s, p)) return NULL;
		if (s[p] >= '0' && s[p] <= '9' || (p + 1) < s.length() && (s[p] == '-' || s[p] == '+') && s[p + 1] >= '0' && s[p + 1] <= '9') {
			double v = 0;
			long long sign = +1;
			bool flt = false;

			if (s[p] == '+') p++;
			else if (s[p] == '-') {
				sign = -1;
				p++;
			}

			while (p < s.length() && s[p] >= '0' && s[p] <= '9')
				v = v * 10 + (s[p++] - '0');
			if (s[p] == '.') {
				flt = true;
				p++;
				double q = 0.1;
				while (p < s.length() && s[p] >= '0' && s[p] <= '9') {
					v += q*(s[p++] - '0');
					q /= 10.0;
				}
			}
			if (s[p] == 'E' || s[p] == 'e') {
				flt = true;
				p++;
				long long n = 0;
				while (p < s.length() && s[p] >= '0' && s[p] <= '9')
					n = n * 10 + (long long)(s[p++] - '0');
				v *= pow(10.0, n);
			}
			if (flt)
				result = new float_number(sign*v);
			else
				result = new int_number(sign*((long long)(v + 0.5)));
		}
		else if (s[p] == '"' || s[p] == '\'') {
			size_t oldp = p++;
			string st;
			int n = -1;
			while (p < s.length() && (s[p] != s[oldp] || (p + 1)<s.length() && s[p + 1] == s[oldp])) {
				if (s[p] == '\\')
					st += s[p++];
				else if (s[p] == s[oldp])
					p++;
				st += s[p++];
			}
			p++;
			if (p < s.length()) {
				if (s[p] == '/') {
					p++;
					n = 0;
					while (p < s.length() && isdigit(s[p]))
						n = n * 10 + (s[p++] - '0');
				}
			}
			if (n < 0)
				result = new term(unescape(st));
			else
				result = new indicator(unescape(st), n);
		}
		else if (s[p] == '[') {
			result = new ::list(stack_container<value *>(), NULL);
			p++;
			bypass_spaces(s, p);
			size_t oldp = p;
			while (p < s.length() && s[p] != ']' && s[p] != '|') {
				value * v = parse(CTX, exit_on_error, true, ff, s, p);
				if (p >= s.length() || v == NULL) {
					if (exit_on_error) {
						std::cout << "[" << s.substr(oldp, (size_t)(p - oldp)) << "] : incorrect list!" << endl;
						exit(-1);
					}
					else
						return NULL;
				}
				((::list *)result)->add(CTX, v);
				if (!bypass_spaces(s, p)) {
					if (exit_on_error) {
						std::cout << "[" << s.substr(oldp, (size_t)(p - oldp)) << "] : incorrect list!" << endl;
						exit(-1);
					}
					else
						return NULL;
				}
				if (s[p] == ',') p++;
				else if (s[p] != ']' && s[p] != '|') {
					if (exit_on_error) {
						std::cout << "[" << s.substr(oldp, (size_t)(p - oldp)) << "] : incorrect list!" << endl;
						exit(-1);
					}
					else
						return NULL;
				}
			}
			if (s[p] == '|') {
				p++;
				value * t = parse(CTX, exit_on_error, true, ff, s, p);
				if (p >= s.length() || t == NULL) {
					if (exit_on_error) {
						std::cout << "[" << s.substr(oldp, (size_t)(p - oldp)) << "] : incorrect tag of list!" << endl;
						exit(-1);
					}
					else
						return NULL;
				}
				((::list *)result)->set_tag(t);
				t->free();
				if (bypass_spaces(s, p) && s[p] == ']') p++;
				else {
					if (exit_on_error) {
						std::cout << "[" << s.substr(oldp, (size_t)(p - oldp)) << "] : incorrect tag of list!" << endl;
						exit(-1);
					}
					else
						return NULL;
				}
			} else
				p++;
		}
		else if (s[p] >= 'A' && s[p] <= 'Z') {
			string st = string("") + s[p++];
			while (p < s.length() &&
				(s[p] >= 'A' && s[p] <= 'Z' || s[p] >= 'a' && s[p] <= 'z' || s[p] >= '0' && s[p] <= '9' ||
				 s[p] == '_'))
				st += s[p++];
			bool found = false;
			int it = ff->find(st.c_str(), found);
			if (found)
				result = ff->at(it)->const_copy(CTX, ff);
			else
				result = new var(st);
		}
		else if (s[p] == '_') {
			p++;
			result = new any();
		}
		else if (s[p] >= 'a' && s[p] <= 'z') {
			string st = string("") + s[p++];
			int n = -1;
			while (p < s.length() &&
				(s[p] >= 'A' && s[p] <= 'Z' || s[p] >= 'a' && s[p] <= 'z' || s[p] >= '0' && s[p] <= '9' ||
				s[p] == '_'))
				st += s[p++];

			if (p < s.length()) {
				if (s[p] == '/') {
					p++;
					n = 0;
					while (p < s.length() && isdigit(s[p]))
						n = n * 10 + (s[p++] - '0');
				}
			}

			if (n >= 0)
				result = new indicator(st, n);
			else {
				result = new term(st);

				if (parse_complex_terms && s[p] == '(') {
					p++;
					size_t oldp = p;
					bypass_spaces(s, p);
					while (p < s.length() && s[p] != ')') {
						value * v = parse(CTX, exit_on_error, true, ff, s, p);
						if (p >= s.length() || v == NULL) {
							if (exit_on_error) {
								std::cout << "(" << s.substr(oldp, (size_t)(p - oldp)) << ") : incorrect term!" << endl;
								exit(-1);
							}
							else
								return NULL;
						}
						((term *)result)->add_arg(CTX, ff, v);
						v->free();
						if (!bypass_spaces(s, p)) {
							if (exit_on_error) {
								std::cout << "(" << s.substr(oldp, (size_t)(p - oldp)) << ") : incorrect term!" << endl;
								exit(-1);
							}
							else
								return NULL;
						}
						if (s[p] == ',') p++;
						else if (s[p] != ')') {
							if (exit_on_error) {
								std::cout << "(" << s.substr(oldp, (size_t)(p - oldp)) << ") : incorrect term!" << endl;
								exit(-1);
							}
							else
								return NULL;
						}
					}
					p++;
				}
			}
		}

		return result;
	}
	else {
		if (exit_on_error) {
			std::cout << "parse : syntax error!" << endl;
			exit(-2);
		}
		else
			return NULL;
	}
}

bool interpreter::unify(context * CTX, frame_item * ff, value * from, value * to) {
	return to->unify(CTX, ff, from);
}

vector<value *> * interpreter::accept(context * CTX, frame_item * ff, predicate_item * current) {
	vector<value *> * result = new vector<value *>();
	if (forking) current->lock();
	if (current->get_args()->size() > current->_get_args()->size())
		for (const string & s : *current->get_args()) {
			frame_item * empty = new frame_item();
			size_t p = 0;
			value * item = parse(CTX, true, true, empty, s, p);
			current->push_cashed_arg(item);
			value * _item = item->const_copy(CTX, ff);
			item->free();
			_item = _item->fill(CTX, ff); // Собираем item из доступных значений

			result->push_back(_item);
			delete empty;
		}
	else {
		for (value * v : *current->_get_args())
			result->push_back(v->const_copy(CTX, ff));
	}
	if (forking) current->unlock();

	return result;
}

bool interpreter::retrieve(context * CTX, frame_item * ff, clause * current, vector<value *> * vals, bool escape_vars) {
	bool result = true;

	if (escape_vars)
		for (value * v : *vals)
			v->escape_vars(CTX, ff);

	int k = 0;
	if (forking) current->lock();
	if (current->get_args()->size() > current->_get_args()->size())
		for (const string & s : *current->get_args()) {
			frame_item * empty = new frame_item();
			size_t p = 0;
			value * item = parse(CTX, true, true, empty, s, p);
			current->push_cashed_arg(item);
			value * _item = item->const_copy(CTX, ff);
			item->free();
			if (!unify(CTX, ff, vals->at(k++), _item)) // Заполняем item, попутно заполняются унифицированные переменные
				result = false;
			_item->free();
			delete empty;
		}
	else {
		for (value * proto : *current->_get_args()) {
			value * _item = proto->const_copy(CTX, ff);
			if (!unify(CTX, ff, vals->at(k++), _item)) // Заполняем item, попутно заполняются унифицированные переменные
				result = false;
			if (CTX)
				_item->free();
			else {
				cout << "retrieve: NULL context?!" << endl;
				exit(1257);
			}
		}
	}
	if (forking) current->unlock();

	return result;
}

vector<value *> * interpreter::accept(context * CTX, frame_item * ff, clause * current) {
	vector<value *> * result = new vector<value *>();
	if (forking) current->lock();
	if (current->get_args()->size() > current->_get_args()->size())
		for (const string & s : *current->get_args()) {
			frame_item * empty = new frame_item();
			size_t p = 0;
			value * item = parse(CTX, true, true, empty, s, p);
			current->push_cashed_arg(item);
			value * _item = item->const_copy(CTX, ff);
			item->free();
			_item = _item->fill(CTX, ff); // Собираем item из доступных значений

			result->push_back(_item);
			delete empty;
		}
	else {
		for (value* v : *current->_get_args())
			result->push_back(v->const_copy(CTX, ff));
	}
	if (forking) current->unlock();

	return result;
}

bool interpreter::retrieve(context * CTX, frame_item * ff, predicate_item * current, vector<value *> * vals, bool escape_vars) {
	bool result = true;

	if (escape_vars)
		for (value * v : *vals)
			v->escape_vars(CTX, ff);

	int k = 0;
	if (forking) current->lock();
	if (current->get_args()->size() > current->_get_args()->size())
		for (const string & s : *current->get_args()) {
			frame_item * empty = new frame_item();
			size_t p = 0;
			value * item = parse(CTX, true, true, empty, s, p);
			current->push_cashed_arg(item);
			value * _item = item->const_copy(CTX, ff);
			item->free();
			if (!unify(CTX, ff, vals->at(k++), _item)) // Заполняем item, попутно заполняются унифицированные переменные
				result = false;
			_item->free();
			delete empty;
		}
	else {
		for (value * proto : *current->_get_args()) {
			value * _item = proto->const_copy(CTX, ff);
			if (!unify(CTX, ff, vals->at(k++), _item)) // Заполняем item, попутно заполняются унифицированные переменные
				result = false;
			_item->free();
		}
	}
	if (forking) current->unlock();

	return result;
}

bool interpreter::process(context * CONTEXT, bool neg, clause * this_clause, predicate_item * p, frame_item * f, vector<value *> ** positional_vals) {
	predicate_item_user * user = dynamic_cast<predicate_item_user *>(p);

	predicate* user_p = user ? user->get_user_predicate() : NULL;

	bool context_locals = CONTEXT && CONTEXT->locals_in_forked;

	context* CNT = user_p && user_p->is_forking() ? new context(context_locals, false, NULL, 100, CONTEXT, NULL, NULL, NULL, this) : CONTEXT;

	generated_vars * variants = p ? p->generate_variants(CNT, f, *positional_vals) : new generated_vars(1, f->copy(CNT));

	if (p && p->get_starred_end() >= 0) {
		CONTEXT->SEQ_RESULT.push(f->copy(CNT));
		CONTEXT->GENERATORS.push(p);
		CONTEXT->SEQ_START.push(p->get_strict_next());
		CONTEXT->SEQ_END.push(p->get_parent()->get_item(p->get_starred_end()));
	}

	auto seqDone = [&]() {
		if (p && p->get_starred_end() >= 0) {
			delete CONTEXT->SEQ_RESULT.top();
			CONTEXT->SEQ_RESULT.pop();
			CONTEXT->GENERATORS.pop();
			CONTEXT->SEQ_START.pop();
			CONTEXT->SEQ_END.pop();
		}
	};

	/*
	if (p) {
		cout << p->get_id() << "(";
		if (positional_vals && *positional_vals)
		for (int i = 0; i < (*positional_vals)->size(); i++) {
			cout << (*positional_vals)->at(i)->make_str();
			if (i < (*positional_vals)->size()-1) cout << ",";
		}
		cout << ")" << endl;
	}
	*/
	bool neg_standard = !(user && !user->is_dynamic()) && p && p->is_negated();
	int i = 0;
	if (variants || neg_standard) {
		if (!CNT) {
			cout << "process: NULL context?!" << endl;
			exit(1257);
		}
		CNT->FLAGS.push_back((p && p->is_once() ? ::once_flag : 0) + (p && p->is_call() ? call_flag : 0));
		CNT->LEVELS.push((int)CNT->PARENT_CALLS.size());
		CNT->TRACE.push(variants);
		CNT->TRACEARGS.push(positional_vals);
		CNT->TRACERS.push(p);

		predicate_right_bracket* rb = dynamic_cast<predicate_right_bracket*>(p);
		predicate_left_bracket* lb = dynamic_cast<predicate_left_bracket*>(p);

		if (lb) lb->enter_critical();
		if (rb) rb->get_corresponding()->leave_critical();

		for (i = 0; neg_standard || variants && variants->has_variant(i); i++) {
			predicate_item * next =
				p ? (
					CNT->ending == NULL || CNT->ending != p->get_next(i) ?
						p->get_next(i) :
						NULL
				) : NULL;

			if (p && p->get_starred_end() >= 0) {
				CNT->SEQUENTIAL.push(true);
			}

			frame_item * ff = variants ? variants->get_next_variant(CNT, i) : f->copy(CNT);
			bool success = false;
			CNT->ptrTRACE.push(i);
			// if (!p || variants)
			if (user && !user->is_dynamic()) {
				if (!user->is_negated()) {
					if (user->processing(CNT, neg, CNT->ptrTRACE.top(), variants, positional_vals, ff, CONTEXT)) {
						CNT->TRACE.pop();
						CNT->TRACEARGS.pop();
						CNT->TRACERS.pop();
						CNT->FLAGS.pop_back();
						CNT->LEVELS.pop();

						if (variants)
							variants->delete_from(CNT->ptrTRACE.top());
						else
							delete ff;

						delete variants;

						seqDone();

						CNT->ptrTRACE.pop();

						if (CNT != CONTEXT)
							delete CNT;

						return true;
					}
					else if (!variants || !variants->has_variant(CNT->ptrTRACE.top()+1)) {
						bool result = false;

						CNT->FLAGS.pop_back();
						CNT->LEVELS.pop();
						CNT->TRACE.pop();
						CNT->TRACEARGS.pop();
						CNT->TRACERS.pop();

						if (!result && f && ff)
							f->sync(false, false, CNT, ff);

						if (variants)
							variants->delete_from(CNT->ptrTRACE.top());
						else
							delete ff;

						delete variants;

						seqDone();

						CNT->ptrTRACE.pop();

						if (CNT != CONTEXT)
							delete CNT;

						return result;
					}
				}
				else {
					if (user->processing(CNT, neg, CNT->ptrTRACE.top(), variants, positional_vals, ff, CONTEXT)) {
						CNT->TRACE.pop();
						CNT->TRACEARGS.pop();
						CNT->TRACERS.pop();
						CNT->FLAGS.pop_back();
						CNT->LEVELS.pop();

						if (f && ff)
							f->sync(false, false, CNT, ff);

						if (variants)
							variants->delete_from(CNT->ptrTRACE.top());
						else
							delete ff;
						delete variants;

						seqDone();

						CNT->ptrTRACE.pop();

						if (CNT != CONTEXT)
							delete CNT;

						return false;
					}
					else if (!variants->has_variant(CNT->ptrTRACE.top() + 1)) {
						success = true;
					}
				}
			}
			else {
				if (neg_standard) {
					if (variants && variants->had_variants() && (!p || p->execute(CNT, ff, CNT->ptrTRACE.top(), variants))) {
						CNT->TRACE.pop();
						CNT->TRACEARGS.pop();
						CNT->TRACERS.pop();
						CNT->FLAGS.pop_back();
						CNT->LEVELS.pop();

						if (f && ff)
							f->sync(false, false, CNT, ff);

						if (variants)
							variants->delete_from(CNT->ptrTRACE.top());
						else
							delete ff;
						delete variants;

						seqDone();

						CNT->ptrTRACE.pop();

						if (CNT != CONTEXT)
							delete CNT;

						if (lb) lb->leave_critical();
						if (rb) rb->get_corresponding()->enter_critical();

						return false;
					}
					neg_standard = false;
				}
				success = !p || p->execute(CNT, ff, CNT->ptrTRACE.top(), variants);
			}

			if (success) {
				bool yes = next == NULL;

				bool rbc = rb && rb->get_corresponding()->is_call();
				bool rbo = rb && rb->get_corresponding()->is_once();

				if (rbc || rbo) {
					if (block_process(CNT, true, rbo, NULL) && CNT && CNT->parent)
						CNT->cut_query.push_back(
							[rbo](interpreter* prolog, context* ctx)->bool {
								return prolog->block_process(ctx, true, rbo, NULL);
							}
						);
				}
				else if (!user && !lb && p && (p->is_call() || p->is_once())) {
					CNT->FLAGS.back() &= ~(call_flag | ::once_flag);
					if (variants && p->is_once())
						variants->trunc_from(CNT->ptrTRACE.top()+1);
				}

				if (!yes) {
					vector<value *> * next_args = accept(CNT, ff, next);
					if (next_args) {
						yes = process(CNT, neg, this_clause, next, ff, &next_args);

						if (*positional_vals && !(neg_standard || variants && variants->has_variant(CNT->ptrTRACE.top() + 1))) {
							for (int j = 0; j < (*positional_vals)->size(); j++)
								(*positional_vals)->at(j)->free();
							delete (*positional_vals);
							(*positional_vals) = NULL;
						}

						if (next_args) {
							for (int j = 0; j < next_args->size(); j++)
								next_args->at(j)->free();
							delete next_args;
						}
						if (yes) {
							CNT->TRACE.pop();
							CNT->TRACEARGS.pop();
							CNT->TRACERS.pop();
							CNT->FLAGS.pop_back();
							CNT->LEVELS.pop();

							predicate_item_fork* FORKER = CNT && CNT->FRAME && CNT->forker ?
								dynamic_cast<predicate_item_fork*>(CNT->forker) :
								NULL;

							if (CNT && CNT->FRAME && CNT->forker && p &&
								(
									FORKER && p == FORKER->get_last(CNT->ptrTRACE.top()) ||
									!FORKER && CNT->forker->get_starred_end() >= 0 && p == CNT->forker->get_last(CNT->ptrTRACE.top())
								))
								CNT->FRAME.load()->sync(false, true, CNT, ff);

							if (f && ff)
								f->sync(false, CNT->PARENT_CALLS.size() == 0, CNT, ff);

							if (variants)
								variants->delete_from(CNT->ptrTRACE.top());
							else
								delete ff;
							delete variants;

							seqDone();

							CNT->ptrTRACE.pop();

							if (CNT != CONTEXT)
								delete CNT;

							if (lb) lb->leave_critical();
							if (rb) rb->get_corresponding()->enter_critical();

							return true;
						}
					}
				}
				else {
					// f->sync(ff);

					predicate_item * next_clause_call = NULL;
					predicate_item * parent_call = NULL;
					clause * next_clause = NULL;
					bool next_neg = false;
					int _flags = 0;
					int old_variant = 0;
					bool got = CNT->CALLS.size() > 0;
					if (got) {
						next_clause_call = CNT->CALLS.top();
						CNT->CALLS.pop();
						next_clause = CNT->CLAUSES.top();
						CNT->CLAUSES.pop();
						parent_call = CNT->PARENT_CALLS.top();
						CNT->PARENT_CALLS.pop();
						old_variant = CNT->PARENT_CALL_VARIANT.top();
						CNT->PARENT_CALL_VARIANT.pop();
						next_neg = CNT->NEGS.top();
						CNT->NEGS.pop();
						_flags = CNT->_FLAGS.top();
						CNT->_FLAGS.pop();
					}

					if (got) {
						frame_item * up_ff = NULL;
						context* up_c = NULL;
						if (CNT->FRAMES.size() > 0) {
							up_ff = CNT->FRAMES.top();
							CNT->FRAMES.pop();
							up_c = CNT->CTXS.top();
							CNT->CTXS.pop();
						}
						frame_item * _up_ff = !got /* next_clause == this_clause */ ? ff->copy(CNT) : up_ff->copy(CNT);

						if (this_clause) {
							vector<value *> * up_args = accept(CNT, ff, this_clause);
							if (up_args) {
								retrieve(CNT, _up_ff, parent_call, up_args, false);
								for (int j = 0; j < up_args->size(); j++)
									up_args->at(j)->free();
								delete up_args;
							}
						}

						if (neg) {
							CNT->TRACE.pop();
							CNT->TRACEARGS.pop();
							CNT->TRACERS.pop();
							CNT->FLAGS.pop_back();
							CNT->LEVELS.pop();

							if (variants)
								variants->delete_from(CNT->ptrTRACE.top());
							else
								delete ff;
							delete variants;
							delete _up_ff;

							seqDone();

							CNT->ptrTRACE.pop();

							if (CNT != CONTEXT)
								delete CNT;

							if (lb) lb->leave_critical();
							if (rb) rb->get_corresponding()->enter_critical();

							return true;
						}

						if (_flags & (call_flag | ::once_flag)) {
							if (block_process(CNT, true, (_flags & ::once_flag) != 0, NULL) && CNT && CNT->parent)
								CNT->cut_query.push_back(
									[rbo, _flags](interpreter* prolog, context* ctx)->bool {
										return prolog->block_process(ctx, true, (_flags& ::once_flag) != 0, NULL);
									}
								);
						}

						vector<value *> * next_args =
							next_clause_call ? accept(CNT, _up_ff, next_clause_call) : new vector<value *>();
						if (next_args) {
							_up_ff->import_transacted_globs(CNT, ff);
							yes = process(up_c, next_neg, next_clause, next_clause_call, _up_ff, &next_args);

							if (*positional_vals && !(neg_standard || variants && variants->has_variant(CNT->ptrTRACE.top() + 1))) {
								for (int j = 0; j < (*positional_vals)->size(); j++)
									(*positional_vals)->at(j)->free();
								delete (*positional_vals);
								(*positional_vals) = NULL;
							}

							if (!yes) {
								CNT->PARENT_CALLS.push(dynamic_cast<predicate_item_user *>(parent_call));
								CNT->PARENT_CALL_VARIANT.push(old_variant);
								CNT->CLAUSES.push(next_clause);
								CNT->CALLS.push(next_clause_call);
								CNT->FRAMES.push(up_ff);
								CNT->CTXS.push(up_c);
								CNT->NEGS.push(next_neg);
								CNT->_FLAGS.push(_flags);

								if (ff && _up_ff)
									ff->sync(false, false, CNT, _up_ff);
							}
							if (next_args) {
								for (int j = 0; j < next_args->size(); j++)
									next_args->at(j)->free();
								delete next_args;
							}
							if (yes) {
								CNT->TRACE.pop();
								CNT->TRACEARGS.pop();
								CNT->TRACERS.pop();
								CNT->FLAGS.pop_back();
								CNT->LEVELS.pop();

								if (variants)
									variants->delete_from(CNT->ptrTRACE.top());
								else
									delete ff;
								delete variants;
								delete _up_ff;

								seqDone();

								CNT->ptrTRACE.pop();

								if (CNT != CONTEXT)
									delete CNT;

								if (lb) lb->leave_critical();
								if (rb) rb->get_corresponding()->enter_critical();

								return true;
							}
						}
						delete _up_ff;
					}
					else {
						CNT->TRACE.pop();
						CNT->TRACEARGS.pop();
						CNT->TRACERS.pop();
						CNT->FLAGS.pop_back();
						CNT->LEVELS.pop();

						predicate_item_fork* FORKER = CNT && CNT->FRAME && CNT->forker ?
							dynamic_cast<predicate_item_fork*>(CNT->forker) :
							NULL;

						if (CNT && CNT->FRAME && CNT->forker && p &&
							(
								FORKER && p == FORKER->get_last(CNT->ptrTRACE.top()) ||
								!FORKER && CNT->forker->get_starred_end() >= 0 && p == CNT->forker->get_last(CNT->ptrTRACE.top())
							))
							CNT->FRAME.load()->sync(false, true, CNT, ff);

						if (variants)
							variants->delete_from(CNT->ptrTRACE.top());
						else
							delete ff;
						delete variants;

						seqDone();

						CNT->ptrTRACE.pop();

						if (CNT != CONTEXT)
							delete CNT;

						if (lb) lb->leave_critical();
						if (rb) rb->get_corresponding()->enter_critical();

						return true;
					}
				}
			}

			i = CNT->ptrTRACE.top();
			CNT->ptrTRACE.pop();
			if (f && ff)
				f->sync(false, false, CNT, ff);
			delete ff;
		}
		if (lb) lb->leave_critical();
		if (rb) rb->get_corresponding()->enter_critical();
		CNT->FLAGS.pop_back();
		CNT->LEVELS.pop();
		CNT->TRACE.pop();
		CNT->TRACEARGS.pop();
		CNT->TRACERS.pop();
	}

	if (variants)
		variants->delete_from(i);
	delete variants;

	seqDone();

	if (CNT != CONTEXT)
		delete CNT;

	return false;
}

void interpreter::parse_clause(context * CTX, vector<string> & renew, frame_item * ff, string & s, size_t & p) {
	stack<predicate_left_bracket *> brackets;
	stack< stack<predicate_or *> > ors;
	stack<int> or_levels;
	stack<predicate_item*> fork_stack;
	int bracket_level = 0;
	stack<int> fork_bracket_levels;
	bool or_branch = false;

	bypass_spaces(s, p);

	if (p < s.length() && s[p] == ':') {
		string haystack = s.substr(p);
		regex incl("^:\\s*-\\s*include\\s*\\(\\s*(\\w+)\\s*\\)\\s*\\..*");
		smatch match;
		if (regex_search(haystack, match, incl)) {
			string file = match[1].str();
			std::ifstream in;
			in.open(file + ".pro");
			if (!in)
				in.open(file + ".pl");
			if (in) {
				string body;
				char buf[65536];
				while (in.getline(buf, sizeof(buf))) {
					body.append(buf);
					body.append("\n");
				}
				in.close();
				string::size_type pos = haystack.find("\n");
				if (pos != string::npos)
					p += (size_t)(pos + 1);
				else {
					std::cout << s.substr(p, 20) << " : end of line expected!" << endl;
					exit(22);
				}
				s.insert(p, body);
				return;
			}
			else {
				std::cout << s.substr(p, 20) << " : can't open including file!" << endl;
				exit(23);
			}
		}
	}

	string id;
	while (p < s.length() &&
		(s[p] >= 'A' && s[p] <= 'Z' || s[p] >= 'a' && s[p] <= 'z' || s[p] >= '0' && s[p] <= '9' ||
		s[p] == '_'))
		id += s[p++];

	if (id.length() == 0) {
		std::cout << s.substr(p,10) << " : strange clause head!" << endl;
		exit(2);
	}

	predicate * pr = PREDICATES[id];

	vector<string>::iterator itr = find(renew.begin(), renew.end(), id);
	if (itr != renew.end()) {
		delete PREDICATES[id];
		PREDICATES.erase(id);
		renew.erase(itr);
		pr = NULL;
	}

	if (pr == NULL)
		PREDICATES[id] = pr = new predicate(id);

	clause * cl = new clause(pr);
	pr->add_clause(cl);

	if (p < s.length() && s[p] == '(') {
		p++;
		while (p < s.length() && s[p] != ')') {
			size_t oldp = p;
			value * dummy = parse(CTX, true, true, ff, s, p);
			if (dummy) {
				dummy->free();
				cl->add_arg(s.substr(oldp, (size_t)(p - oldp)));
			}
			else {
				std::cout << id << " : strange clause head!" << endl;
				exit(2);
			}
			if (!bypass_spaces(s, p)) {
				std::cout << id << " : strange clause head!" << endl;
				exit(2);
			}
			if (s[p] == ',') p++;
			else if (s[p] != ')') {
				std::cout << id << " : unexpected '" << s[p] << "' in clause head!" << endl;
				exit(2);
			}
		}
		p++;
	}

	bypass_spaces(s, p);

	if (p < s.length() && s[p] == '.') {
		p++;
	}
	else if (p < s.length()-1 && s[p] == ':' && s[p + 1] == '-') {
		int num = 0;
		p += 2;

		s.insert(s.begin() + p, '(');

		predicate_item * prev_pi = NULL;

		cl->set_forking(false);
		bool bracket_inserted = false;

		do {
			predicate_item * pi = NULL;

			bypass_spaces(s, p);

			bool or_request = false;

			bool neg = false;
			bool once = false;
			bool call = false;
			bool star = false;
			bool starred = false;
			bool conditional_starred = false;
			bool locals_in_forked = false;
			bool transactable_facts = false;
			std::recursive_mutex * starlock = &STARLOCK;
			
			if ((p + 2) < s.length() && s[p] == '!' && (((s[p + 1] == '*') && s[p + 2] == '{') || s[p + 1] == '{')) {
				p++;
				transactable_facts = true;
			}

			if ((p + 1) < s.length() && s[p] == '*' && (s[p + 1] == '(' || s[p + 1] == '[' || s[p + 1] == '{')) {
				star = true;
				p++;
				if (s[p] == '[') {
					p++;
					bypass_spaces(s, p);
					string lock_name;
					while (p < s.length() && (isalnum(s[p]) || s[p] == '_'))
						lock_name += s[p++];
					bypass_spaces(s, p);
					if (s[p] == ']') {
						p++;
						bypass_spaces(s, p);
						if (s[p] != '(') {
							std::cout << "'(' expected after [critical_id] in [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
							exit(2);
						}
						if (lock_name.length()) {
							map<string, std::recursive_mutex *>::iterator itstar = STARLOCKS.find(lock_name);
							if (itstar == STARLOCKS.end()) {
								starlock = new recursive_mutex();
								STARLOCKS[lock_name] = starlock;
							} else
								starlock = itstar->second;
						}
					} else {
						std::cout << "[critical_id] expected in [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
						exit(2);
					}
				} else if (s[p] == '{')
					locals_in_forked = true;
			}
			else if ((p + 1) < s.length() && s[p] == '*' && (isalpha(s[p + 1]) || s[p+1] == '?' && (p + 2) < s.length() && isalpha(s[p+2]))) {
				cl->set_forking(true);
				pr->set_forking(true);
				atomizer.set_forking(true);
				forking = true;
				starred = true;
				if (s[p + 1] == '?') {
					conditional_starred = true;
					p++;
				}
				p++;
			}

			if ((p + 1) < s.length() && s[p] == '\\' && s[p + 1] == '+') {
				neg = true;
				p += 2;
			}

			if (p < s.length() && s[p] == '{') {
				p++;
				if (p < s.length()) {
					if ((p + 1) < s.length() && s[p] == '=' && s[p + 1] != '(') {
						p++;
						// {=} or {=N}
						// Handle '}'!
						value* v = NULL;
						bypass_spaces(s, p);
						if (p < s.length() && s[p] != '}') {
							v = parse(CTX, false, false, ff, s, p);
							if (!v) {
								std::cout << "Variable or int expected after '{=' [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
								exit(2);
							}
						}
						if (p < s.length() && s[p] == '}') {
							p++;
							if (!v)
								v = new int_number(1);
							pi = new predicate_item_join(false, v, false, false, false, num, cl, this);
						}
						else {
							std::cout << "'}' expected after '{=' or '{=N' [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
							exit(2);
						}
					}
					else if (s[p] == '&') {
						p++;
						if (p < s.length() && s[p] == '}') {
							p++;
							// {&}
							pi = new predicate_item_join(false, new int_number(-1), false, false, false, num, cl, this);
						} else {
							std::cout << "Clause [" << s.substr((size_t)(p - 30), 100) << "] : premature end of file!" << endl;
							exit(2);
						}
					}
					else {
						// {...
						pi = new predicate_item_fork(locals_in_forked, transactable_facts, false, false, false, num, cl, this);
						fork_stack.push(pi);
						fork_bracket_levels.push(bracket_level);
						cl->set_forking(true);
						pr->set_forking(true);
						atomizer.set_forking(true);
						forking = true;
						bypass_spaces(s, p);
						s.insert(s.begin() + p, 1, '(');
					}
				}
				else {
					std::cout << "Clause [" << s.substr((size_t)(p - 30), 100) << "] : premature end of file!" << endl;
					exit(2);
				}
			}
			else if (p < s.length() && s[p] == '}')
				if (bracket_inserted) {
					bracket_inserted = false;
					p++;
					// }
					if (fork_stack.size() == 0) {
						std::cout << "'}' without corresponding '{' [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
						exit(2);
					}
					if (fork_bracket_levels.top() != bracket_level) {
						std::cout << "Mangled '( / }' structure [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
						exit(2);
					}
					// Handle
					predicate_item_fork* forker = dynamic_cast<predicate_item_fork*>(fork_stack.top());
					if (forker) {
						forker->set_end(num);
						bypass_spaces(s, p);
						if (p < s.length() && s[p] == '*') {
							p++;
							bypass_spaces(s, p);
							value* v = parse(CTX, false, false, ff, s, p);
							if (v)
								forker->set_n_threads(v);
							else {
								std::cout << "Variable or int expected after '}*' [" << s.substr((size_t)(p - 30), 100) << "]!" << endl;
								exit(2);
							}
						}
						if (p < s.length() && s[p] == '}') {
							// Do not p++
							pi = new predicate_item_join(true, new int_number(-1), false, false, false, num, cl, this);
						}
						bypass_spaces(s, p);
						if (p < s.length() && s[p] == '{')
							s.insert(s.begin() + p, 1, ',');
					}
					else {
						predicate_item* last = fork_stack.top();
						last->set_starred_end(num);

						pi = new predicate_item_join(true, new int_number(-1), false, false, false, num, cl, this);
						pi->set_conditional_star_mode(last->get_conditional_star_mode());
					}
					fork_stack.pop();
					fork_bracket_levels.pop();
				}
				else {
					s.insert(s.begin() + p, 1, ')');
					bracket_inserted = true;
				}
			else {
				bypass_spaces(s, p);
				if (s.substr(p, 5) == "once(") {
					if (starred) {
						cout << "*once() is not allowed!" << endl;
						exit(2);
					}
					if (neg) {
						p += 4;
					}
					else {
						once = true;
						// brackets.push(NULL);
						p += 5;
						// bracket_level++;
					}
				}
				else if (s.substr(p, 5) == "call(") {
					if (starred) {
						cout << "*call() is not allowed!" << endl;
						exit(2);
					}
					if (!neg) call = true;
					p += 4;
				}

				bypass_spaces(s, p);

				if ((p + 1) < s.length() && s[p] == '\\' && s[p + 1] == '+') {
					neg = true;
					p += 2;
					if (once) {
						s.insert(p, "(");
						// brackets.pop();
						// bracket_level--;
					}
					once = false;
				}
				else if (once)
					s.insert(p, "(");

				bypass_spaces(s, p);
				if ((p + 2) < s.length() && s[p] == '\'' && s[p + 1] == ',' && s[p + 2] == '\'')
					p += 3;
				else if (p < s.length() && s[p] == ';') {
					or_request = true;
					p++;
				}

				bypass_spaces(s, p);
				if (s[p] == '!') {
					pi = new predicate_item_cut(NULL, num, cl, this);
					p++;
				}
				else if (s[p] == '(') {
					bracket_level++;
					if (neg) {
						predicate_item* _pi = new predicate_left_bracket(false, false, false, true, num++, cl, this);
						if (or_branch) {
							brackets.top()->push_branch(_pi);
							or_branch = false;
						}
						cl->add_item(_pi);
						brackets.push((predicate_left_bracket*)_pi);
						ors.push(stack<predicate_or*>());
					}
					p++;
					pi = new predicate_left_bracket(brackets.size() == 0, neg, once, call, num, cl, this);
					if (star) pi->set_critical(starlock);
					if (or_branch) {
						brackets.top()->push_branch(pi);
						or_branch = false;
					}
					brackets.push((predicate_left_bracket*)pi);
					ors.push(stack<predicate_or*>());
					if (or_request) {
						or_levels.push((int)brackets.size());
						or_request = false;
					}
				}
				else if (s[p] == ')') {
					bracket_level--;
					p++;
					if (!brackets.top()) {
						brackets.pop();
					}
					else {
						bool neg = brackets.top()->is_negated();
						brackets.top()->clear_negated();

						if (or_levels.size() > 0 && or_levels.top() == brackets.size()) {
							or_levels.pop();
						}

						pi = new predicate_right_bracket(brackets.top(), num, cl, this);
						if (or_branch) {
							brackets.top()->push_branch(pi);
							or_branch = false;
						}
						brackets.pop();
						stack<predicate_or*>& or_items = ors.top();
						while (!or_items.empty()) {
							or_items.top()->set_ending(pi);
							or_items.pop();
						}
						ors.pop();

						if (neg) {
							cl->add_item(pi);
							num++;
							predicate_right_bracket* _pi = new predicate_right_bracket(brackets.top(), num + 4, cl, this);
							pi = new predicate_item_cut(NULL, num++, cl, this);
							cl->add_item(pi);
							pi = new predicate_item_fail(false, false, false, num++, cl, this);
							cl->add_item(pi);
							pi = new predicate_or(num++, cl, this);
							ors.top().push((predicate_or*)pi);

							cl->add_item(pi);
							pi = new predicate_item_true(false, false, false, num++, cl, this);
							cl->add_item(pi);
							brackets.top()->push_branch(pi);

							stack<predicate_or*>& or_items = ors.top();
							while (!or_items.empty()) {
								or_items.top()->set_ending(_pi);
								or_items.pop();
							}
							brackets.pop();
							ors.pop();

							pi = _pi;
						}
						/*if (brackets.size() && !brackets.top())
							s.insert(p, ")");*/
					}
				}
				else {
					string iid;
					bypass_spaces(s, p);

					if ((p + 2) < s.length() && s[p] == '=' && s[p + 1] == '.' && s[p + 2] == '.') {
						iid = "term_split";
						p += 3;
					}
					else if ((p + 1) < s.length() && s[p] == '=' && s[p + 1] == '=') {
						iid = "eq";
						p += 2;
					}
					else if (p < s.length() && s[p] == '=') {
						iid = "eq";
						p++;
					}
					else if (p < s.length() && s[p] == '<') {
						iid = "less";
						p++;
					}
					else if (p < s.length() && s[p] == '>') {
						iid = "greater";
						p++;
					}
					else if ((p + 1) < s.length() && s[p] == '\\' && s[p + 1] == '=') {
						iid = "neq";
						p += 2;
					}
					else {
						size_t start = p;
						value* dummy = parse(CTX, false, false, ff, s, p);
						term* t = dynamic_cast<term*>(dummy);
						iid = t && t->get_args().size() == 0 ? t->get_name() : s.substr(start, p - start);
						dummy->free();
					}

					if (iid.length() == 0) {
						std::cout << id << " : " << s.substr(p, 10) << " : strange item call!" << endl;
						exit(2);
					}

					bypass_spaces(s, p);
					if (s.substr(p, 2) == "is" || p < s.length() && (s[p] == '>' || s[p] == '<')) {
						string op = s[p] == '>' ? "greater" : (s[p] == '<' ? "less" : "is");
						if (op == "is")
							p += 2;
						else
							p++;
						bypass_spaces(s, p);
						string expr_chars = "\"'+-*/\\()<>^=!";
						string expr;
						bool in_quote = false;
						int br_level = 0;
						while (p < s.length() && ((p+1) >= s.length() || s[p] != '-' || s[p + 1] != '>') && (
							(in_quote || s[p] == '_' || isspace(s[p]) || isalnum(s[p]) || expr_chars.find(s[p]) != string::npos) ||
							(s[p] == ',' || s[p] == ';') && br_level ||
							(p + 1) < s.length() && s[p] == '.' && isdigit(s[p + 1])
							)) {
							if (in_quote && s[p] == '\\') p++;
							else if (s[p] == '\'') in_quote = !in_quote;
							else if (!in_quote) {
								if (s[p] == '(') br_level++;
								else if (s[p] == ')')
									if (br_level)
										br_level--;
									else
										break;
							}
							expr += s[p];
							p++;
						}
						if (op == "is") {
							size_t pp = 0;
							value* dummy = parse(CTX, false, false, ff, iid, pp);
							if (!dummy) {
								std::cout << iid << " : strange 'is' first part!" << endl;
								exit(2);
							}
							pi = new predicate_item_is(dummy, expr, neg, once, call, num, cl, this);
						}
						else if (op == "less") {
							pi = new predicate_item_less(neg, once, call, num, cl, this);
							pi->add_arg(iid);
							pi->add_arg(expr);
						}
						else if (op == "greater") {
							pi = new predicate_item_greater(neg, once, call, num, cl, this);
							pi->add_arg(iid);
							pi->add_arg(expr);
						}
					}
					else {
						map<string, ids>::iterator id = MAP.find(iid);
						if (id == MAP.end()) {
							pi = new predicate_item_user(neg, once, call, num, cl, this, iid);
						}
						else {
							ids _iid = id->second;
							if (_iid == id_append) {
								pi = new predicate_item_append(neg, once, call, num, cl, this);
							}
							else if (_iid == id_sublist) {
								pi = new predicate_item_sublist(neg, once, call, num, cl, this);
							}
							else if (_iid == id_delete) {
								pi = new predicate_item_delete(neg, once, call, num, cl, this);
							}
							else if (_iid == id_member) {
								pi = new predicate_item_member(neg, once, call, num, cl, this);
							}
							else if (_iid == id_last) {
								pi = new predicate_item_last(neg, once, call, num, cl, this);
							}
							else if (_iid == id_reverse) {
								pi = new predicate_item_reverse(neg, once, call, num, cl, this);
							}
							else if (_iid == id_for) {
								pi = new predicate_item_for(neg, once, call, num, cl, this);
							}
							else if (_iid == id_length) {
								pi = new predicate_item_length(neg, once, call, num, cl, this);
							}
							else if (_iid == id_max_list) {
								pi = new predicate_item_max_list(neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_length) {
								pi = new predicate_item_atom_length(neg, once, call, num, cl, this);
							}
							else if (_iid == id_nth) {
								pi = new predicate_item_nth(neg, once, call, num, cl, this);
							}
							else if (_iid == id_page_id) {
								pi = new predicate_item_page_id(neg, once, call, num, cl, this);
							}
							else if (_iid == id_thread_id) {
								pi = new predicate_item_thread_id(neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_concat) {
								pi = new predicate_item_atom_concat(neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_chars) {
								pi = new predicate_item_atom_chars(neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_codes) {
								pi = new predicate_item_atom_codes(neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_hex) {
								pi = new predicate_item_atom_hex(0, neg, once, call, num, cl, this);
							}
							else if (_iid == id_atom_hexs) {
								pi = new predicate_item_atom_hex(' ', neg, once, call, num, cl, this);
							}
							else if (_iid == id_number_atom) {
								pi = new predicate_item_number_atom(neg, once, call, num, cl, this);
							}
							else if (_iid == id_number) {
								pi = new predicate_item_number(neg, once, call, num, cl, this);
							}
							else if (_iid == id_consistency) {
								pi = new predicate_item_consistency(neg, once, call, num, cl, this);
							}
							else if (_iid == id_listing) {
								pi = new predicate_item_listing(neg, once, call, num, cl, this);
							}
							else if (_iid == id_current_predicate) {
								pi = new predicate_item_current_predicate(neg, once, call, num, cl, this);
							}
							else if (_iid == id_findall) {
								pi = new predicate_item_findall(neg, once, call, num, cl, this);
							}
							else if (_iid == id_functor) {
								pi = new predicate_item_functor(neg, once, call, num, cl, this);
							}
							else if (_iid == id_predicate_property) {
								pi = new predicate_item_predicate_property(neg, once, call, num, cl, this);
							}
							else if (_iid == id_spredicate_property_pi) {
								pi = new predicate_item_predicate_property_pi(neg, once, call, num, cl, this);
							}
							else if (_iid == id_eq) {
								pi = new predicate_item_eq(neg, once, call, num, cl, this);
							}
							else if (_iid == id_neq) {
								pi = new predicate_item_neq(neg, once, call, num, cl, this);
							}
							else if (_iid == id_less) {
								pi = new predicate_item_less(neg, once, call, num, cl, this);
							}
							else if (_iid == id_greater) {
								pi = new predicate_item_greater(neg, once, call, num, cl, this);
							}
							else if (_iid == id_term_split) {
								pi = new predicate_item_term_split(neg, once, call, num, cl, this);
							}
							else if (_iid == id_g_assign) {
								pi = new predicate_item_g_assign(neg, once, call, num, cl, this);
							}
							else if (_iid == id_g_assign_nth) {
								pi = new predicate_item_g_assign_nth(neg, once, call, num, cl, this);
							}
							else if (_iid == id_g_read) {
								pi = new predicate_item_g_read(neg, once, call, num, cl, this);
							}
							else if (_iid == id_fail) {
								pi = new predicate_item_fail(neg, once, call, num, cl, this);
							}
							else if (_iid == id_true) {
								pi = new predicate_item_true(neg, once, call, num, cl, this);
							}
							else if (_iid == id_change_directory) {
								pi = new predicate_item_change_directory(neg, once, call, num, cl, this);
							}
							else if (_iid == id_open) {
								pi = new predicate_item_open(neg, once, call, num, cl, this);
							}
							else if (_iid == id_close) {
								pi = new predicate_item_close(neg, once, call, num, cl, this);
							}
							else if (_iid == id_get_char) {
								pi = new predicate_item_get_or_peek_char(false, neg, once, call, num, cl, this);
							}
							else if (_iid == id_peek_char) {
								pi = new predicate_item_get_or_peek_char(true, neg, once, call, num, cl, this);
							}
							else if (_iid == id_read_token) {
								pi = new predicate_item_read_token(neg, once, call, num, cl, this);
							}
							else if (_iid == id_read_token_from_atom) {
								pi = new predicate_item_read_token_from_atom(neg, once, call, num, cl, this);
							}
							else if (_iid == id_mars) {
								pi = new predicate_item_mars(neg, once, call, num, cl, this);
							}
							else if (_iid == id_mars_decode) {
								pi = new predicate_item_mars_decode(neg, once, call, num, cl, this);
							}
							else if (_iid == id_unset) {
								pi = new predicate_item_unset(neg, once, call, num, cl, this);
							}
							else if (_iid == id_write) {
								pi = new predicate_item_write(neg, once, call, num, cl, this);
							}
							else if (_iid == id_write_to_atom) {
								pi = new predicate_item_write_to_atom(neg, once, call, num, cl, this);
							}
							else if (_iid == id_write_term) {
								pi = new predicate_item_write_term(neg, once, call, num, cl, this);
							}
							else if (_iid == id_write_term_to_atom) {
								pi = new predicate_item_write_term_to_atom(neg, once, call, num, cl, this);
							}
							else if (_iid == id_nl) {
								pi = new predicate_item_nl(neg, once, call, num, cl, this);
							}
							else if (_iid == id_file_exists) {
								pi = new predicate_item_file_exists(neg, once, call, num, cl, this);
							}
							else if (_iid == id_unlink) {
								pi = new predicate_item_unlink(neg, once, call, num, cl, this);
							}
							else if (_iid == id_rename_file) {
								pi = new predicate_item_rename_file(neg, once, call, num, cl, this);
							}
							else if (_iid == id_seeing) {
								pi = new predicate_item_seeing(neg, once, call, num, cl, this);
							}
							else if (_iid == id_telling) {
								pi = new predicate_item_telling(neg, once, call, num, cl, this);
							}
							else if (_iid == id_seen) {
								pi = new predicate_item_seen(neg, once, call, num, cl, this);
							}
							else if (_iid == id_told) {
								pi = new predicate_item_told(neg, once, call, num, cl, this);
							}
							else if (_iid == id_see) {
								pi = new predicate_item_see(neg, once, call, num, cl, this);
							}
							else if (_iid == id_tell) {
								pi = new predicate_item_tell(neg, once, call, num, cl, this);
							}
							else if (_iid == id_set_iteration_star_packet) {
								pi = new predicate_item_set_iteration_star_packet(neg, once, call, num, cl, this);
							}
							else if (_iid == id_repeat) {
								pi = new predicate_item_repeat(neg, once, call, num, cl, this);
							}
							else if (_iid == id_random) {
								pi = new predicate_item_random(neg, once, call, num, cl, this);
							}
							else if (_iid == id_randomize) {
								pi = new predicate_item_randomize(neg, once, call, num, cl, this);
							}
							else if (_iid == id_char_code) {
								pi = new predicate_item_char_code(neg, once, call, num, cl, this);
							}
							else if (_iid == id_get_code) {
								pi = new predicate_item_get_code(neg, once, call, num, cl, this);
							}
							else if (_iid == id_at_end_of_stream) {
								pi = new predicate_item_at_end_of_stream(neg, once, call, num, cl, this);
							}
							else if (_iid == id_open_url) {
								pi = new predicate_item_open_url(neg, once, call, num, cl, this);
							}
							else if (_iid == id_track_post) {
								pi = new predicate_item_track_post(neg, once, call, num, cl, this);
							}
							else if (_iid == id_consult) {
								pi = new predicate_item_consult(neg, once, call, num, cl, this);
							}
							else if (_iid == id_assert || _iid == id_asserta || _iid == id_assertz) {
								pi = new predicate_item_assert(_iid != id_asserta, neg, once, call, num, cl, this);
							}
							else if (_iid == id_retract) {
								pi = new predicate_item_retract(false, neg, once, call, num, cl, this);
							}
							else if (_iid == id_retractall) {
								pi = new predicate_item_retract(true, neg, once, call, num, cl, this);
							}
							else if (_iid == id_inc) {
								pi = new predicate_item_inc(neg, once, call, num, cl, this);
							}
							else if (_iid == id_halt) {
								exit(0);
							}
							else if (_iid == id_load_classes) {
								pi = new predicate_item_load_classes(neg, once, call, num, cl, this);
							}
							else if (_iid == id_init_xpathing) {
								pi = new predicate_item_init_xpathing(neg, once, call, num, cl, this);
							}
							else if (_iid == id_induct_xpathing) {
								pi = new predicate_item_induct_xpathing(neg, once, call, num, cl, this);
							}
							else if (_iid == id_import_model_after_induct) {
								pi = new predicate_item_import_model_after_induct(neg, once, call, num, cl, this);
							}
							else if (_iid == id_unload_classes) {
								pi = new predicate_item_unload_classes(neg, once, call, num, cl, this);
							}
							else if (_iid == id_var) {
								pi = new predicate_item_var(neg, once, call, num, cl, this);
							}
							else if (_iid == id_nonvar) {
								pi = new predicate_item_nonvar(neg, once, call, num, cl, this);
							}
							else if (_iid == id_get_icontacts) {
								pi = new predicate_item_get_contacts(dirInput, neg, once, call, num, cl, this);
							}
							else if (_iid == id_get_ocontacts) {
								pi = new predicate_item_get_contacts(dirOutput, neg, once, call, num, cl, this);
							}
							else if (_iid == id_rollback) {
								pi = new predicate_item_rollback(neg, once, call, num, cl, this);
							}
							else {
								cout << "Unmapped construction : " << iid << "!" << endl;
								exit(1730);
							}
						}
						if (starred) {
							fork_stack.push(pi);
							fork_bracket_levels.push(bracket_level);
							pi->set_conditional_star_mode(conditional_starred);
						}
					}

					if (p < s.length() && s[p] == '(') {
						p++;
						while (p < s.length() && s[p] != ')') {
							size_t oldp = p;
							value* dummy = parse(CTX, true, true, ff, s, p);
							if (dummy) {
								dummy->free();
								pi->add_arg(s.substr(oldp, (size_t)(p - oldp)));
							}
							else {
								std::cout << id << ":" << iid << " : strange call head!" << endl;
								exit(2);
							}
							if (!bypass_spaces(s, p)) {
								std::cout << id << ":" << iid << " : strange call head!" << endl;
								exit(2);
							}
							if (s[p] == ',') p++;
							else if (s[p] != ')') {
								std::cout << id << ":" << iid << " : unexpected '" << s[p] << "' in call head!" << endl;
								exit(2);
							}
						}
						p++;
					}
				}
			}

			if (pi) {
				if (or_branch) {
					int n = 0;
					while (!brackets.empty() && !brackets.top()) {
						brackets.pop();
						n++;
					}
					if (brackets.empty()) {
						std::cout << "Can't understand logical structure in " << id << " clause [" << s.substr((size_t)(p - 10), 100) << "] : probably 'once' tangled?" << endl;
						exit(2);
					}
					brackets.top()->push_branch(pi);
					while (n--) brackets.push(NULL);
					or_branch = false;
				}
				cl->add_item(pi);
				num++;
				prev_pi = pi;
			}

			bool open_bracket = dynamic_cast<predicate_left_bracket *>(pi) != NULL;

			bypass_spaces(s, p);
			if (p < s.length()) {
				if (!open_bracket && s[p] == '{') {
					if (starred) {
						p++;
						s.insert(s.begin() + p, 1, '(');
					}
					else {
						std::cout << "'*Predicate(...){...}' expected in " << id << " clause [" << s.substr((size_t)(p - 10), 100) << "]" << endl;
						exit(2);
					}
				}
				else if (!open_bracket && (s[p] == ',' && (or_levels.size() == 0 || or_levels.top() != brackets.size()))) p++;
				else if (!open_bracket && (s[p] == ';' || s[p] == ',' && or_levels.size() > 0 && or_levels.top() == brackets.size())) {
					p++;
					if (brackets.size() == 0) {
						if (cl->is_forking()) {
							pi = new predicate_item_join(true, new int_number(-1), false, false, false, num++, cl, this);
							cl->add_item(pi);
						}
						clause * _cl = new clause(pr);
						pr->add_clause(_cl);
						_cl->set_args(*cl->get_args());
						num = 0;
						cl = _cl;
					}
					else {
						predicate_or * _pi = new predicate_or(num, cl, this);
						ors.top().push(_pi);
						cl->add_item(_pi);
						num++;
						or_branch = true;
					}
				}
				else if ((p + 1) < s.length() && s[p] == '-' && s[p + 1] == '>') {
					p += 2;
					if (pi == NULL) pi = prev_pi;
					if (dynamic_cast<predicate_right_bracket *>(pi))
						pi = ((predicate_right_bracket *)pi)->get_corresponding();
					if (pi) {
						predicate_item_cut * frontier = new predicate_item_cut(pi, num, cl, this);
						cl->add_item(frontier);
						num++;
						prev_pi = frontier;
					}
					else {
						std::cout << "Can't understand -> in " << id << " clause [" << s.substr((size_t)(p-10), 100) << "]!" << endl;
						exit(2);
					}
				}
				else if (s[p] == '.') {
					p++;
					s.insert(s.begin() + p, ')');
					p++;

					if (cl->is_forking()) {
						pi = new predicate_item_join(true, new int_number(-1), false, false, false, num++, cl, this);
						cl->add_item(pi);
					}

					if (!brackets.top()) {
						std::cout << "Brackets not balanced or problems with ';'-branches in " << id << " clause!" << endl;
						exit(2);
					}
					else {
						brackets.top()->clear_negated();

						if (or_levels.size() > 0 && or_levels.top() == brackets.size()) {
							or_levels.pop();
						}

						pi = new predicate_right_bracket(brackets.top(), num, cl, this);
						if (or_branch) {
							brackets.top()->push_branch(pi);
							or_branch = false;
						}
						brackets.pop();
						stack<predicate_or*>& or_items = ors.top();
						while (!or_items.empty()) {
							or_items.top()->set_ending(pi);
							or_items.pop();
						}
						ors.pop();

						cl->add_item(pi);
						num++;
					}

					if (or_branch || brackets.size()) {
						std::cout << "Brackets not balanced or problems with ';'-branches in " << id << " clause!" << endl;
						exit(2);
					}
					break;
				}
			}
			else {
				std::cout << "'(' or ')' or '.' or ',' or ';' expected in " << id << " clause!" << endl;
				exit(2);
			}
		} while (true);
	}
}

void interpreter::parse_program(vector<string> & renew, string & s) {
	size_t p = 0;
	do {
		bypass_spaces(s, p);
		if (p < s.length()) {
			frame_item * dummy = new frame_item();
			parse_clause(CONTEXT, renew, dummy, s, p);
			delete dummy;
		}
		else
			break;
	} while (true);
}

void interpreter::add_std_body(string & body) {
	std::ifstream in(std_lib_pro);
	if (in) {
		char buf[65536];
		while (!in.eof()) {
			in.getline(buf, sizeof(buf));
			body.append(buf);
			body.append("\n");
		}
		in.close();
	}
	body.append("subtract([],_,[]).");
	body.append("\n");
	body.append("subtract([H|T],L1,L2):-once(member(H,L1)), once(subtract(T,L1,L2)).");
	body.append("\n");
	body.append("subtract([H|T],L1,[H|L2]):-\\+ member(H,L1), once(subtract(T,L1,L2)).");
	body.append("\n");
}

void interpreter::consult(const string & fname, bool renew) {
	string body;
	std::ifstream in(fname);

	if (in) {
		string line;
		add_std_body(body);
		while (getline(in, line)) {
			body += line;
			body += "\n";
		}
		in.close();
	}

	vector<string> _renew;
	if (renew) {
		map<string, predicate *>::iterator it = PREDICATES.begin();
		while (it != PREDICATES.end()) {
			_renew.push_back(it->first);
			it++;
		}
	}

	parse_program(_renew, body);
	bind();
}

void interpreter::bind() {
	map<string, predicate *>::iterator it = PREDICATES.begin();
	while (it != PREDICATES.end()) {
		it->second->bind(false);
		it++;
	}
	it = PREDICATES.begin();
	while (it != PREDICATES.end()) {
		it->second->bind(true);
		it++;
	}
}

predicate_item_user * interpreter::load_program(const string & fname, const string & starter_name) {
	consult(fname, false);

	predicate_item_user * result = PREDICATES[starter_name] ? new predicate_item_user(false, false, false, 0, NULL, this, starter_name) : NULL;

	if (result) {
		result->bind(false);
		result->bind(true);
	}

	return result;
}

bool interpreter::loaded() {
	return starter != NULL;
}

void interpreter::run() {
	vector<value *> * args = new vector<value *>();
	generated_vars * variants = new generated_vars();
	frame_item * ff = new frame_item();
	variants->push_back(ff);
	starter->processing(CONTEXT, false, 0, variants, &args, ff, CONTEXT);
	delete args;
	delete variants;
	delete ff;
}

interpreter::interpreter(const string & fname, const string & starter_name) {
	THREAD_POOL = new thread_pool();

	ITERATION_STAR_PACKET = max((unsigned short)(getTotalProcs() / 3), (unsigned short)2);

	file_num = 0;
	current_input = STD_INPUT;
	current_output = STD_OUTPUT;
	ins = &cin;
	outs = &std::cout;
	xpathInductLib = 0;

	env[0] = 0;
	xpath_compiled = false;
	xpath_loaded = false;

	forking = false;

	CONTEXT = new context(false, false, NULL, 50000, NULL, NULL, NULL, NULL, this);

	if (fname.length() > 0)
		starter = load_program(fname, starter_name);
	else
		starter = NULL;
}

interpreter::~interpreter() {
	if (current_output != STD_OUTPUT) {
		dynamic_cast<std::basic_ofstream<char> *>(outs)->close();
		delete outs;
	}

	if (current_input != STD_INPUT) {
		dynamic_cast<std::basic_ifstream<char> *>(ins)->close();
		delete ins;
	}

	map<string, predicate *>::iterator it = PREDICATES.begin();
	while (it != PREDICATES.end()) {
		delete it->second;
		it++;
	}
	map<string, value *>::iterator itg = GVars.begin();
	while (itg != GVars.end()) {
		delete itg->second;
		itg++;
	}
	delete CONTEXT;
	map<string, std::recursive_mutex *>::iterator itstars = STARLOCKS.begin();
	while (itstars != STARLOCKS.end()) {
		delete itstars->second;
		itstars++;
	}
	map< string, set<int>*>::iterator iti = DBIndicators.begin();
	while (iti != DBIndicators.end()) {
		delete iti->second;
		iti++;
	}
	delete THREAD_POOL;
}

string interpreter::open_file(const string & fname, const string & mode) {
	string result = "#";
	char buf[65];
	result += __itoa(file_num, buf, 10);

	files[file_num] = std::basic_fstream<char>();
	if (mode == "read")
		files[file_num].open(fname, ios_base::in);
	else if (mode == "write")
		files[file_num].open(fname, ios_base::out | ios_base::trunc);
	else if (mode == "append")
		files[file_num].open(fname, ios_base::app);
	else {
		std::cout << "Unknown file [" << fname << "] open mode = [" << mode << "]" << endl;
		exit(504);
	}

	if (files[file_num])
		file_num++;
	else {
		std::cout << "File [" << fname << "] can't be opened with mode = [" << mode << "]" << endl;
		exit(505);
	}

	return result;
}

void interpreter::close_file(const string & obj) {
	int fn = -1;
	std::basic_fstream<char> & ff = get_file(obj, fn);
	if (ff.is_open()) ff.close();
	files.erase(fn);
}

std::basic_fstream<char> & interpreter::get_file(const string & obj, int & fn) {
	if (obj.length() < 2 || obj[0] != '#') {
		std::cout << "No such file: id = [" << obj << "]" << endl;
		exit(501);
	}
	fn = atoi(obj.substr(1).c_str());
	if (fn < 0 || fn >= file_num) {
		std::cout << "Incorrect file number = [" << fn << "]" << endl;
		exit(502);
	}

	map<int, std::basic_fstream<char> >::iterator it = files.find(fn);
	if (it == files.end()) {
		std::cout << "Probably file [" << fn << "] is already closed" << endl;
		exit(503);
	}

	return it->second;
}

bool interpreter::check_consistency(set<string> & dynamic_prefixes) {
	bool result = true;

	map<string, predicate *>::iterator pit = PREDICATES.begin();
	while (pit != PREDICATES.end()) {
		for (int c = 0; c < pit->second->num_clauses(); c++) {
			clause * cl = pit->second->get_clause(c);
			for (int i = 0; i < cl->num_items(); i++) {
				predicate_item_user * pp = dynamic_cast<predicate_item_user *>(cl->get_item(i));
				if (pp) {
					map<string, predicate *>::iterator ppit = PREDICATES.find(pp->get_id());
					if (ppit == PREDICATES.end() || pp->get_args()->size() != ppit->second->get_clause(0)->get_args()->size()) {
						set<string>::iterator pref_it = dynamic_prefixes.end();
						string ppid = pp->get_id();
						bool found = false;
						do {
							if (pref_it == dynamic_prefixes.begin()) break;
							pref_it--;
							if (ppid.substr(0, pref_it->length()) == *pref_it) {
								found = true;
							}
						} while (!found);
						if (!found) {
							(*outs) << "Predicate[" << pit->first << "][clause_" << c << "] : probably unknown predicate '" << ppid << "'/" << (pp->get_args()->size()) << endl;
							result = false;
						}
					}
				}
			}
		}
		pit++;
	}

	return result;
}

#ifdef __linux__
unsigned long long getTotalSystemMemory()
{
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return (long long)pages * page_size;
}
unsigned int getTotalProcs()
{
	return sysconf(_SC_NPROCESSORS_ONLN);
}
#else
unsigned long long getTotalSystemMemory()
{
	MEMORYSTATUSEX status = { 0 };
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}
unsigned int getTotalProcs()
{
	SYSTEM_INFO sysinfo = { 0 };
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}
#endif

int main(int argc, char ** argv) {
#ifdef __linux__
	struct rlimit rl = { RLIM_INFINITY, RLIM_INFINITY };
	int result = setrlimit(RLIMIT_STACK, &rl);
	if (result != 0) {
		std::cout << "setrlimit returned result = " << result << endl;
		exit(1000);
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	size_t default_stack_size;
	pthread_attr_getstacksize(&attr, &default_stack_size);

	pthread_attr_setstacksize(&attr, 16 * default_stack_size);
	pthread_setattr_default_np(&attr);
#endif

	setlocale(LC_ALL, "en_US.UTF-8");

	int main_part = 1;
	while (main_part < argc) {
		string flag = string(argv[main_part]);
		if (flag == "--saluer")
			std::cout << "Bonjour!" << endl;
		else break;
		main_part++;
	}

	std::cout << "Prolog MicroBrain by V.V.Pekunov V0.23beta3" << endl;
	if (argc == main_part) {
		interpreter prolog("", "");
		std::cout << "  Enter 'halt.' or 'end_of_file' to exit." << endl << endl;
		while (true) {
			string line;
			size_t p = 0;

			std::cout << ">";
			getline(cin, line);

			if (line == "end_of_file" || line == "end_of_file.")
				break;

			vector<string> renew;
			frame_item * f = new frame_item();
			string body;

			map<string, predicate *>::iterator it = prolog.PREDICATES.begin();
			while (it != prolog.PREDICATES.end()) {
				renew.push_back(it->first);
				it++;
			}

			prolog.add_std_body(body);

			body.append("internal_goal:-");
			body.append(line);
			body.append("\n");
			bypass_spaces(body, p);
			while (p < body.length()) {
				prolog.parse_clause(prolog.CONTEXT, renew, f, body, p);
				bypass_spaces(body, p);
			}
			prolog.bind();

			auto start = std::chrono::high_resolution_clock::now(); // Засекаем время

			vector<value *> * args = new vector<value *>();
			generated_vars * variants = new generated_vars();
			variants->push_back(f);
			predicate_item_user * pi = new predicate_item_user(false, false, false, 0, NULL, &prolog, "internal_goal");
			pi->bind(false);
			pi->bind(true);
			bool ret = pi->processing(prolog.CONTEXT, false, 0, variants, &args, f, prolog.CONTEXT);

			auto end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
			std::chrono::duration<double, std::ratio<1, 1>> elapsed = end - start; // Вычисляем длительность исполнения

			int itv = 0;
			while (itv < f->get_size()) {
				std::cout << "  " << f->atn(itv) << " = ";
				f->at(itv)->write(&std::cout);
				std::cout << endl;
				itv++;
			}

			delete args;
			delete variants;

			std::cout << endl;
			std::cout << "Elapsed: " << elapsed.count() << " sec." << std::endl;
			std::cout << (ret ? "true" : "false") << endl;
			
			delete pi;
			delete f;

			prolog.CONTEXT->clearDBJournals();
		}
	}
	else if (argc - main_part == 3 && (string(argv[main_part]) == "-consult" || string(argv[main_part]) == "--consult")) {
		interpreter prolog(argv[main_part+1], argv[main_part+2]);

		if (prolog.loaded()) {
			prolog.run();
		}
		else
			std::cout << "Goal absent!" << endl;
	}
	else if ((argc - main_part) % 2 == 0) {
		interpreter * _prolog = new interpreter("", "");

		vector<string> renew;
		string body;
		size_t p = 0;

		frame_item * f = new frame_item();

		map<string, predicate *>::iterator it = _prolog->PREDICATES.begin();
		while (it != _prolog->PREDICATES.end()) {
			renew.push_back(it->first);
			it++;
		}

		_prolog->add_std_body(body);

		bypass_spaces(body, p);
		while (p < body.length()) {
			_prolog->parse_clause(_prolog->CONTEXT, renew, f, body, p);
			bypass_spaces(body, p);
		}
		_prolog->bind();

		delete f;

		while (main_part != argc && string(argv[main_part]) == "--query-goal") {
			string line = argv[main_part + 1];
			main_part += 2;

			if (line.length() >= 2 && line[0] == '"' && line[line.length()-1] == '"')
				line = line.substr(1, line.length()-2);

			std::cout << ">" << line << "." << std::endl;

			p = 0;

			if (line == "end_of_file" || line == "end_of_file.")
				break;

			vector<string> renew;
			frame_item * f = new frame_item();
			string body;

			renew.push_back("internal_goal");

			body.append("internal_goal:-");
			body.append(line + ".");
			body.append("\n");
			bypass_spaces(body, p);
			while (p < body.length()) {
				_prolog->parse_clause(_prolog->CONTEXT, renew, f, body, p);
				bypass_spaces(body, p);
			}
			_prolog->bind();

			auto start = std::chrono::high_resolution_clock::now(); // Засекаем время

			vector<value *> * args = new vector<value *>();
			generated_vars * variants = new generated_vars();
			variants->push_back(f);
			predicate_item_user * pi = new predicate_item_user(false, false, false, 0, NULL, _prolog, "internal_goal");
			pi->bind(false);
			pi->bind(true);
			bool ret = pi->processing(_prolog->CONTEXT, false, 0, variants, &args, f, _prolog->CONTEXT);

			auto end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
			std::chrono::duration<double, std::ratio<1, 1>> elapsed = end - start; // Вычисляем длительность исполнения

			int itv = 0;
			while (itv < f->get_size()) {
				std::cout << "  " << f->atn(itv) << " = ";
				f->at(itv)->write(&std::cout);
				std::cout << endl;
				itv++;
			}

			delete args;
			delete variants;

			std::cout << endl;
			std::cout << "Elapsed: " << elapsed.count() << " sec." << std::endl;
			std::cout << (ret ? "true" : "false") << endl;

			delete pi;
			delete f;
		}
		delete _prolog;
	}
	else {
		std::cout << "Usage: prolog_micro_brain.exe [FLAGS] [--query-goal <goal> ... | -consult <file.pro> <goal_predicate_name>]" << endl;
		std::cout << "   FLAGS:" << endl;
		std::cout << "      --saluer    -- Undocumented" << endl;
	}
	return 0;
}