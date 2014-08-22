
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
 * @date   May 17, 2014
 */

#include <stdint.h>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef int32_t sint32;
typedef uint64_t uint64;

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//n = 2^3049 - 1 (Mersenne Number)

void modnadd(uint32 *a, uint32 *b, uint32 *aplusb)
{
	uint32 i, carry;
	uint64 T;

	carry = 0;
	for(i = 0; i < 96; i++)
	{
		T = (uint64)a[i] + b[i] + carry;
		*(aplusb + i) = (uint32)T;
		carry = (uint32)(T >> 32);
	}

	if((*(aplusb + 95) & 0x200) != 0)
	{
		*aplusb = *aplusb + 1;
		*(aplusb + 95) &= 0x1FF;
	}
}

//Compute asq = a^2 mod n
void modnsq(uint32 *a, uint32 *asq)
{
	uint32 i, j, k;
	uint32 c[192];
	uint32 R0, R1, R2, carry;
	uint64 T1, T2;

	R0 = 0; 
	R1 = 0; 
	R2 = 0;

	for(k = 0; k <= 190; k++)
	{
		for(i = (k <= 95 ? 0 : (k - 95)); i <= (k >> 1); i++)
		{
			j = k - i;
			T1 = (uint64)(*(a + i)) * (*(a + j));
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
	c[191] = R0;

	//fast reduction
	for(i = 191; i >= 96; i--)
		c[i] = (c[i] << 23) | (c[i - 1] >> 9);
	c[95] &= 0x1FF;
	modnadd(c, c + 96, asq);
}

//Compute public key hash function
// void rabin_mersenne_3049(uint32 *msg, uint32 *out)
void rabin_mersenne_3049(uint8_t *msg, uint8_t *out)
{
	modnsq((uint32*)msg, (uint32*)out);
}

/*
void main()
{
	uint32 i;
	uint32 msg[96] = {0x7A04F3E1,0x96488FC2,0xC799B8ED,0x9F5A86F9,0x637C48AF,0x8CD70BCE,0x043AB169,0xE03DC9C3,
		              0x3D759E10,0xF062680F,0xFD77D893,0x59C94057,0xF2ECC125,0x886741FC,0x332ADE50,0xCFC3BCB6,
					  0x7D84661C,0x21C90078,0x39320CA2,0x18B13E7F,0x7E10AD9C,0x6766C940,0x45D3249C,0xBDDF7AE4,
		              0x23E07770,0x60EC8B7D,0x8B36D663,0xA4F2087E,0xEAC83D5E,0xCB7A1247,0x5C615E22,0xD1500CB6,
		              0xDEC48F52,0x82C1ECCB,0x64C24DF6,0x822D9F9A,0x1BA9F219,0x4E6CEB4E,0xC17B7257,0x12606B78,
					  0x05E094ED,0x7A3B93D1,0x521EBD7F,0x8DBAEAD6,0x13326DAA,0x4D5D9F93,0xD1426EC9,0x591D4CD3,
					  0xC45E6160,0x6454CC86,0x179137CA,0xC0F799BB,0x477AB5B5,0xCEE76758,0x93F16C75,0x50B6E537,
					  0xC0C2E90D,0x842F906E,0xDCF755A9,0x7EDFBD22,0x4928073C,0xAFE594A3,0xF544C9F7,0x2329D360,
					  0x2E7B9D3B,0x4332093F,0xFE584A91,0x15E45CE2,0x1CFA2FA0,0x82030024,0xC82B32BB,0x6C963148,
					  0x6B919194,0x519B7462,0xA7E130FD,0x4BF2F32B,0x5330CF6E,0x1E0F1559,0xD4CA75A4,0x38C464C2,
					  0x2AE4EFAD,0xB6123CC0,0xCC200DD8,0x9A53ECA9,0x0AC40F25,0x43204F20,0x73161B54,0x984B1BEF,
					  0x223C8C36,0x68A1DD2B,0x298E5C9D,0x42108734,0xB51305FC,0x1C724F28,0xAE2F213E,0x000001F5};
	uint32 digest[96] = {0x0};
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
	for(t=0;t<1000000;t++)
	{
		rabin_mersenne_3049(msg, digest);
	}
	time_end=time(NULL);t=time_end-time_begin-t0;
	printf("\nThe time of generating message digest is %I64d us\n", t);
	printf("\nThe message digest is:\n");
	for(i = 0; i < 96; i++)
		printf("%08x ",digest[95 - i]);
	printf("\n\n");
}	

*/
