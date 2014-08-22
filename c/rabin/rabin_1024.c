
/*
 * Copyright (c) 2014, University of Waterloo
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the University of Waterloo nor the
 *   names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior
 *   written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author Xinxin Fan <fan@openecc.org>
 * @date   May 14, 2014
 */

#include <stdint.h>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef int32_t sint32;
typedef uint64_t uint64;

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//p = 0xBDDF7AE4 45D3249C 6766C940 7E10AD9C 18B13E7F 39320CA2 21C90078 7D84661C F12A3A21 F4772B41 F4C53BAB A6E76B3B 9340DED2 C1EBC21F 0F4DB654 6F6C4393
//q = 0xBC1A8943 8D899F74 5A6899BA 0D9B6827 D239C5CB 5290106A 03F17ADB 67ACDC26 0B039B90 E88F1AFA 2B42EE31 CF239E4D A62C6E93 421FAE11 BB522891 213DA0D3
uint32 p[16] = {0x6F6C4393,0x0F4DB654,0xC1EBC21F,0x9340DED2,0xA6E76B3B,0xF4C53BAB,0xF4772B41,0xF12A3A21,
	            0x7D84661C,0x21C90078,0x39320CA2,0x18B13E7F,0x7E10AD9C,0x6766C940,0x45D3249C,0xBDDF7AE4};
uint32 q[16] = {0x213DA0D3,0xBB522891,0x421FAE11,0xA62C6E93,0xCF239E4D,0x2B42EE31,0xE88F1AFA,0x0B039B90,
	            0x67ACDC26,0x03F17ADB,0x5290106A,0xD239C5CB,0x0D9B6827,0x5A6899BA,0x8D899F74,0xBC1A8943};

//n = p * q
//= 0x8B83CCC0 D1B1A2FD 70F08A7A 1EFDD783 349C6417 5DDE8AF1 A4D9F22F 383F1E87 B3E1F6B0 971089D4 EA7911E3 F898DAC4 D2B91118 DF3BD78B 05F19726 FD910C05 
//    D206CC78 0FF691F4 6AD4F68D 9015BC94 8A5161F4 D15BDB03 2B078C31 E0DB3348 F4FE5C07 7AC5594A 21112331 A30FCF30 D6735174 65E0B738 9074CD00 8D7E9229
uint32 n[32] = {0x8D7E9229,0x9074CD00,0x65E0B738,0xD6735174,0xA30FCF30,0x21112331,0x7AC5594A,0xF4FE5C07,
	            0xE0DB3348,0x2B078C31,0xD15BDB03,0x8A5161F4,0x9015BC94,0x6AD4F68D,0x0FF691F4,0xD206CC78,
				0xFD910C05,0x05F19726,0xDF3BD78B,0xD2B91118,0xF898DAC4,0xEA7911E3,0x971089D4,0xB3E1F6B0,
				0x383F1E87,0xA4D9F22F,0x5DDE8AF1,0x349C6417,0x1EFDD783,0x70F08A7A,0xD1B1A2FD,0x8B83CCC0};

//un = [(2^32)^64/n]
//= 0x1 D5BDFC73 503879D6 9A463B70 08A40D13 62D78979 9E1FC4FC 679F5678 FB3A4184 7FB643EC 017424C9 126D2015 FBE31747 73685830 85A9DF0E 8378B078 714CB5BB 
//      0380C84F 2E9EAC39 7E838E2B 88C67345 8E07089F 3B44D9F6 215652F9 8E7DB680 86E255A5 1703EFF6 76BACB0E E49B279D 941C5894 5E9E1E33 8D706762 4B3053DC
uint32 un[33] = {0x4B3053DC,0x8D706762,0x5E9E1E33,0x941C5894,0xE49B279D,0x76BACB0E,0x1703EFF6,0x86E255A5,
	             0x8E7DB680,0x215652F9,0x3B44D9F6,0x8E07089F,0x88C67345,0x7E838E2B,0x2E9EAC39,0x0380C84F,
				 0x714CB5BB,0x8378B078,0x85A9DF0E,0x73685830,0xFBE31747,0x126D2015,0x017424C9,0x7FB643EC,
				 0xFB3A4184,0x679F5678,0x9E1FC4FC,0x62D78979,0x08A40D13,0x9A463B70,0x503879D6,0xD5BDFC73,0x1};

uint32 sub(uint32 *a, uint32 *b, uint32 *asubb, const uint32 m)
{
	uint32 i, borrow;
	uint64 T;

	borrow = 1; 
	for(i = 0; i < m; i++)
	{
		T = (uint64)*(a + i) + ~*(b + i) + borrow;
		*(asubb + i) = (uint32)T;
		borrow = (uint32)(T >> 32);
	}
	if(borrow == 0) return 1;     
	else return 0;
}

sint32 compare(uint32 *a, uint32 *b, const uint32 m)
{
	uint32 i;

	for(i = m; i != 0; i--)
	{
		if(*(a + i - 1) < *(b + i - 1)) return -1;  
		if(*(a + i - 1) > *(b + i - 1)) return 1;  
	}
	return 0;                                      
}

//Barrett Modular Reduction
//Compute b = c mod m, where len(c) = 2*len(m) 
void modm(uint32 *c, uint32 *m, uint32 *um, uint32 *b, const uint32 num)
{
	uint32 i, j;
	uint64 T1, T2, T3;
	uint32 *r, *s;

	//dynamic array allocation
	r = (uint32 *)malloc((num + 1) * sizeof(uint32));
	s = (uint32 *)malloc((num + 1) * sizeof(uint32));

	T1 = (uint64)c[num - 1] * um[0];
	T1 = T1 >> 32;

	for(i = num; i < 2*num; i++)
	{
		T3 = 0;
		for(j = num - 1; j <= i; j++)
		{
			T2 = (uint64)c[j] * um[i - j];
			T1 += (uint32)T2;
			T3 += (T2 >> 32);
		}
		T1 = (T1 >> 32) + T3;
	}

	for(i = 0; i < num - 1; i++)
	{
		T3 = 0;
		for(j = i + num; j < 2*num; j++)
		{
			T2 = (uint64)c[j] * um[2*num + i - j];
			T1 += (uint32)T2;
			T3 += (T2 >> 32);
		}
		r[i] = (uint32)T1;
		T1 = (T1 >> 32) + T3;
	}

	T2 = (uint64)c[2*num - 1] * um[num];
	T1 += (uint32)T2;
	r[num - 1] = (uint32)T1;
	r[num] = (uint32)(T1 >> 32) + (uint32)(T2 >> 32);

	//s = r * m
	T1 = (uint64)r[0] * m[0];
	s[0] = (uint32)T1;
	T1 = T1 >> 32;

	for(i = 1; i < num + 1; i++)
	{
		T3 = 0;
		for(j = (i < num ? 0 : 1); j <= i; j++)
		{
			T2 = (uint64)r[j] * m[i - j];
			T1 += (uint32)T2;
			T3 += (T2 >> 32);
		}
		s[i] = (uint32)T1;
		T1 = (T1 >> 32) + T3;
	}

	for(i = num - 1; i != 0; i--)  
		r[i] = m[i];
	r[0] = m[0];
	r[num] = 0;

	if(sub(c, s, s, num + 1) == 1)                 
	{
		for(i = num - 1; i != 0; i--)  
			*(b + i) = *(s + i);
		*b = *s;
		return;
	}

	while(compare(s, r, num + 1) != -1)  
		sub(s, r, s, num + 1);
	for(i = num - 1; i != 0; i--)  
		*(b + i) = *(s + i);
	*b = *s;

	free(r);
	free(s);
}

//Compute asq = a^2 mod m
void modmsq(uint32 *a, uint32 *m, uint32 *um, uint32 *asq, const uint32 num)
{
	uint32 i, j, k;
	uint32 *c;
	uint32 R0, R1, R2, carry;
	uint64 T1, T2;

	//dynamic array allocation
	c = (uint32 *)malloc((2*num) * sizeof(uint32));

	R0 = 0; 
	R1 = 0; 
	R2 = 0;

	for(k = 0; k <= 2*(num-1); k++)
	{
		for(i = (k <= (num - 1) ? 0 : (k - (num - 1))); i <= (k >> 1); i++)
		{
			j = k - i;
			T1 = (uint64)(*(a + i)) *(*(a + j));
			if(i != j)
			{
				carry = (uint32)(T1 >> 63);
				T1 = T1 << 1;
				R2 += carry;
			}
			//(carry, R0) = R0 + V
			T2 = (T1 & 0xFFFFFFFF) + R0;
			carry = (uint32)(T2 >> 32);
			R0 = T2 & 0xFFFFFFFF;
			//(carry, R1) = R1 + U + carry
			T2 = (T1 >> 32) + R1 + carry;
			carry = (uint32)(T2 >> 32);
			R1 = T2 & 0xFFFFFFFF;
			//R2 = R2 + carry
			R2 = R2 + carry;
		}
		c[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}
	c[2*num-1] = R0;

	modm(c, m, um, asq, num);

	free(c);
}

//Compute public key hash function
void rabin_1024(uint8_t *msg, uint8_t *out)
{
    // assume little endian
	modmsq((uint32*)msg, n, un, (uint32*)out, 32);
}

/*
int main()
{
	int i;
	uint32 msg[32] = {0x7A04F3E1,0x96488FC2,0xC799B8ED,0x9F5A86F9,0x637C48AF,0x8CD70BCE,0x043AB169,0xE03DC9C3,
		              0x3D759E10,0xF062680F,0xFD77D893,0x59C94057,0xF2ECC125,0x886741FC,0x332ADE50,0xCFC3BCB6,  
		              0x23E07770,0x60EC8B7D,0x8B36D663,0xA4F2087E,0xEAC83D5E,0xCB7A1247,0x5C615E22,0xD1500CB6,
		              0xDEC48F52,0x82C1ECCB,0x64C24DF6,0x822D9F9A,0x1BA9F219,0x4E6CEB4E,0xC17B7257,0x72606B78};
    // uint8_t msg[128] = {0x2};
	uint8_t digest[128] = {0x0};

	rabin_1024(msg, digest);

	printf("\nThe message digest is:\n");
	for(i = 0; i < 128; i++)
		printf("%02x ", digest[127 - i]);
	printf("\n\n");

    return 0;
}	

*/
