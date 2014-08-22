
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
 * @date   May 15, 2014
 */

#include <stdint.h>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef int32_t sint32;
typedef uint64_t uint64;

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//p = 0xB52E9955 8A467BFE 4D1E7ADB 04B931C9 788E6EA0 E67267F5 3B0145B6 31CA7310 D8249EEC E2D0C5D1 31DC1298 70F4055D 39D60297 25D81F3B 2BB385C9 3D500890
//      3A48350D CCB6120B 6F89F2F9 791783D6 4FA4664E 16FEA67F EC629BBF A5014386 6E221244 A21075D9 2F501F52 959A12F4 E7A64774 BA060582 FAD0CA2F 5AC993F7
//q = 0xF059C853 AE2F213E 1C724F28 B51305FC 42108734 298E5C9D 68A1DD2B 223C8C36 984B1BEF 73161B54 43204F20 0AC40F25 9A53ECA9 CC200DD8 B6123CC0 2AE4EFAD
//      38C464C2 D4CA75A4 1E0F1559 5330CF6E 4BF2F32B A7E130FD 519B7462 6B919194 6C963148 C82B32BB 82030024 1CFA2FA0 15E45CE2 FE584A91 4332093F 2E7B9D3B
uint32 p[32] = {0x5AC993F7,0xFAD0CA2F,0xBA060582,0xE7A64774,0x959A12F4,0x2F501F52,0xA21075D9,0x6E221244,
	            0xA5014386,0xEC629BBF,0x16FEA67F,0x4FA4664E,0x791783D6,0x6F89F2F9,0xCCB6120B,0x3A48350D,
	            0x3D500890,0x2BB385C9,0x25D81F3B,0x39D60297,0x70F4055D,0x31DC1298,0xE2D0C5D1,0xD8249EEC,
	            0x31CA7310,0x3B0145B6,0xE67267F5,0x788E6EA0,0x04B931C9,0x4D1E7ADB,0x8A467BFE,0xB52E9955};	            
uint32 q[32] = {0x2E7B9D3B,0x4332093F,0xFE584A91,0x15E45CE2,0x1CFA2FA0,0x82030024,0xC82B32BB,0x6C963148,
	            0x6B919194,0x519B7462,0xA7E130FD,0x4BF2F32B,0x5330CF6E,0x1E0F1559,0xD4CA75A4,0x38C464C2,
	            0x2AE4EFAD,0xB6123CC0,0xCC200DD8,0x9A53ECA9,0x0AC40F25,0x43204F20,0x73161B54,0x984B1BEF,
	            0x223C8C36,0x68A1DD2B,0x298E5C9D,0x42108734,0xB51305FC,0x1C724F28,0xAE2F213E,0xF059C853};

//n = p * q
//= 0xAA1B3ABB 218CB8CF AB4DB6C6 DE8FF07B 1E55A7B5 8072A449 6AD28AB9 0353067B FA1F55AF FEABD5C5 FC281670 C587060F 61C68EA2 B5C42047 037DFDF8 BA5B6205
//    4EB7EF59 A754C1CB F4830FFE 86F00076 8D0D9B60 0C65B5C9 7DD3D265 4B0BFB9D A478754E 9A18D0AA 1477C725 7F38BE34 95C282B9 F62AF142 5DF531EE 37F9978F
//    E7332D5F DCE9D4F7 2771A3B7 36DFCC12 F24D14B8 835A8755 D15D1CD8 3ADD34C7 2329D360 F544C9F7 AFE594A3 4928073C 7EDFBD22 DCF755A9 842F906E C0C2E90D
//    50B6E537 93F16C75 CEE76758 477AB5B5 C0F799BB 179137CA 6454CC86 C45E6160 591D4CD3 D1426EC9 4D5D9F93 13326DAA 8DBAEAD6 521EBD7F 7A3B93D1 05E094ED 
uint32 n[64] = {0x05E094ED,0x7A3B93D1,0x521EBD7F,0x8DBAEAD6,0x13326DAA,0x4D5D9F93,0xD1426EC9,0x591D4CD3,
	            0xC45E6160,0x6454CC86,0x179137CA,0xC0F799BB,0x477AB5B5,0xCEE76758,0x93F16C75,0x50B6E537,
	            0xC0C2E90D,0x842F906E,0xDCF755A9,0x7EDFBD22,0x4928073C,0xAFE594A3,0xF544C9F7,0x2329D360,
	            0x3ADD34C7,0xD15D1CD8,0x835A8755,0xF24D14B8,0x36DFCC12,0x2771A3B7,0xDCE9D4F7,0xE7332D5F,
	            0x37F9978F,0x5DF531EE,0xF62AF142,0x95C282B9,0x7F38BE34,0x1477C725,0x9A18D0AA,0xA478754E,
	            0x4B0BFB9D,0x7DD3D265,0x0C65B5C9,0x8D0D9B60,0x86F00076,0xF4830FFE,0xA754C1CB,0x4EB7EF59,
	            0xBA5B6205,0x037DFDF8,0xB5C42047,0x61C68EA2,0xC587060F,0xFC281670,0xFEABD5C5,0xFA1F55AF,
	            0x0353067B,0x6AD28AB9,0x8072A449,0x1E55A7B5,0xDE8FF07B,0xAB4DB6C6,0x218CB8CF,0xAA1B3ABB};

//u = [(2^32)^128/n]
//= 0x1 8143CBFD BF41F9C1 78B3B2CD 4B18FD6D 83D2A777 0137E72D 3FF17B6E 81046EE3 155074C6 0033A2EF 3F0632A6 7E9466EF 61D028B2 4D23255F DA81DDC3 6EF6190B
//      0BDC2FB6 F14521D6 E0C16C8C 345B6B84 7D9DBF1C F1EF1687 7B21BAA6 3BCDECA0 14C0C7F9 15E91B07 C3F3DC73 1710C2AC D47C2E30 24F6D190 2045FABF E340952D
//      A4506A02 A0B0DA84 86A050AA 65C34704 B0EE217B 8D3BF4F6 4C29A251 BC8D53EA 2D18BDD5 B0846D80 21E868AC 3DFE31A4 B0D898CF 9016D144 65FBAF01 9AF4E8AF
//      54BD62E9 3489D08E 7494287B E21C5D32 933C3844 C8D9FCBB E1CAD6DC CB1C6176 F5148AD6 F9E30CF1 E6230A81 5AC8D434 0F733B24 5C9C0596 546B901F 5B68AAAB
uint32 un[65] = {0x5B68AAAB,0x546B901F,0x5C9C0596,0x0F733B24,0x5AC8D434,0xE6230A81,0xF9E30CF1,0xF5148AD6,
	             0xCB1C6176,0xE1CAD6DC,0xC8D9FCBB,0x933C3844,0xE21C5D32,0x7494287B,0x3489D08E,0x54BD62E9,
	             0x9AF4E8AF,0x65FBAF01,0x9016D144,0xB0D898CF,0x3DFE31A4,0x21E868AC,0xB0846D80,0x2D18BDD5,
	             0xBC8D53EA,0x4C29A251,0x8D3BF4F6,0xB0EE217B,0x65C34704,0x86A050AA,0xA0B0DA84,0xA4506A02,
	             0xE340952D,0x2045FABF,0x24F6D190,0xD47C2E30,0x1710C2AC,0xC3F3DC73,0x15E91B07,0x14C0C7F9,
	             0x3BCDECA0,0x7B21BAA6,0xF1EF1687,0x7D9DBF1C,0x345B6B84,0xE0C16C8C,0xF14521D6,0x0BDC2FB6,
	             0x6EF6190B,0xDA81DDC3,0x4D23255F,0x61D028B2,0x7E9466EF,0x3F0632A6,0x0033A2EF,0x155074C6,
	             0x81046EE3,0x3FF17B6E,0x0137E72D,0x83D2A777,0x4B18FD6D,0x78B3B2CD,0xBF41F9C1,0x8143CBFD,0x1};

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
void rabin_2048(uint8_t *msg, uint8_t *out)
{
	modmsq((uint32*)msg, n, un, (uint32*)out, 64);
}

/*
void main()
{
	uint32 i;
	uint32 msg[64] = {0x40B907F0,0xDB038AE1,0x55F6D9E0,0x280A27B6,0x7F745EF0,0xFB4C9FE6,0x879E8C26,0x75F22283,
		              0xA261B3D2,0x5E71509D,0x74DDDDC9,0x30C03C0A,0x0220E53E,0xAB4F12B3,0x17072760,0xE1C200DD,
		              0x21AE04BC,0x8FAACA38,0x1002D574,0x08588715,0xBD429ACC,0x2BCE9702,0xAC993839,0xFFC3BB81,
		              0xE1B8C1BC,0x20C58D24,0x500B9889,0x2D9A16B1,0x2F7B5A6E,0xAAA192D4,0xD2A6E5A6,0xB2B70B0D,
		              0x3E232325,0x8A043123,0xBCDFDBF3,0xAA952ED2,0x1EE2D92C,0xB37B354F,0x4F7C4522,0x4D2C26D1,
		              0x8DEBDD8C,0xFBA9538F,0x911852C9,0x6AF14701,0x2197C153,0xF1573608,0x992EB47B,0x8C41446A,
		              0x906000DA,0x6C3EF465,0xF8CCF513,0x44E502AA,0x2AACBCDB,0xBCE444B9,0xF252E312,0x0D7C3D4E,
		              0x6478DAA3,0xEB9AE161,0xE0C7EBBF,0xF39E0DC7,0x9DC40517,0x56E90A5F,0x344643F9,0x7D5C2B5B};
	uint32 digest[64] = {0x0};
	uint64 t;
	time_t time_begin,time_end,t0;

	time_begin=time(NULL);
	for(t=0;t<1000000;t++)
	{
		;
	}
	time_end=time(NULL);
	t0=time_end-time_begin;
	time_begin=time(NULL);
	// for(t=0;t<1000000;t++)
	// {
		// rabin_2048(msg, digest, 64);
		rabin_2048(msg, digest);
	// }
	time_end=time(NULL);t=time_end-time_begin-t0;
	printf("\nThe time of generating message digest is %I64d us\n", t);
	printf("\nThe message digest is:\n");
	for(i = 0; i < 64; i++)
		printf("%08x ",digest[63 - i]);
	printf("\n\n");
}	
*/
