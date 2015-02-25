/*****************************************************************************
 * WARNING
 *
 * THIS CODE IS CREATED FOR EXPERIMENTATION AND EDUCATIONAL USE ONLY. 
 * 
 * USAGE OF THIS CODE IN OTHER WAYS MAY INFRINGE UPON THE INTELLECTUAL 
 * PROPERTY OF OTHER PARTIES, SUCH AS INSIDE SECURE AND HID GLOBAL, 
 * AND MAY EXPOSE YOU TO AN INFRINGEMENT ACTION FROM THOSE PARTIES. 
 * 
 * THIS CODE SHOULD NEVER BE USED TO INFRINGE PATENTS OR INTELLECTUAL PROPERTY RIGHTS. 
 *
 *****************************************************************************
 *
 * This file is part of loclass. It is a reconstructon of the cipher engine
 * used in iClass, and RFID techology.
 *
 * The implementation is based on the work performed by
 * Flavio D. Garcia, Gerhard de Koning Gans, Roel Verdult and
 * Milosch Meriac in the paper "Dismantling IClass".
 *
 * Copyright (C) 2014 Martin Holst Swende
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with loclass.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 * 
 ****************************************************************************/


#include "optimized_cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

/**
* Definition 1 (Cipher state). A cipher state of iClass s is an element of F 40/2
* consisting of the following four components:
* 	1. the left register l = (l 0 . . . l 7 ) ∈ F 8/2 ;
* 	2. the right register r = (r 0 . . . r 7 ) ∈ F 8/2 ;
* 	3. the top register t = (t 0 . . . t 15 ) ∈ F 16/2 .
* 	4. the bottom register b = (b 0 . . . b 7 ) ∈ F 8/2 .
**/
typedef struct {
	uint8_t l;
	uint8_t r;
	uint8_t b;
	uint16_t t;
} State;


#define opt_T(s) (0x1 & ((s->t >> 15) ^ (s->t >> 14)^ (s->t >> 10)^ (s->t >> 8)^ (s->t >> 5)^ (s->t >> 4)^ (s->t >> 1)^ s->t))

#define opt_B(s) (((s->b >> 6) ^ (s->b >> 5) ^ (s->b >> 4) ^ (s->b)) & 0x1)

uint8_t opt__select(bool x, bool y, uint8_t r)
{
	uint8_t r0 = r >> 7 ;
	uint8_t r1 = r >> 6 ;
	uint8_t r2 = r >> 5 ;
	uint8_t r3 = r >> 4 ;
	uint8_t r4 = r >> 3 ;
	uint8_t r5 = r >> 2 ;
	uint8_t r6 = r >> 1 ;
	uint8_t r7 = r;

	uint8_t z0 = (r0 & r2) ^ (r1 & ~r3) ^ (r2 | r4);
	uint8_t z1 = (r0 | r2) ^ ( r5 | r7) ^ r1 ^ r6 ^ x ^ y;
	uint8_t z2 = (r3 & ~r5) ^ (r4 & r6 ) ^ r7 ^ x;

	// The three bitz z0.. z1 are packed into a uint8_t:
	// 00000ZZZ
	//Return value is a uint8_t
	uint8_t retval = (z0 << 2) & 4;
	retval |= (z1 << 1) & 2;
	retval |= z2 & 1;

	// Return value 0 <= retval <= 7
	return retval;
}

static bool _r0;
static bool _r4;
static bool _r7;

void opt_successor(uint8_t* k, State *s, bool y, State* successor)
{
	_r0 = s->r >> 7 & 0x1;
	_r4 = s->r >> 3 & 0x1;
	_r7 = s->r & 0x1;

	bool Tt = opt_T(s);

	successor->t = (s->t >> 1);
	successor->t |= (Tt ^ _r0 ^ _r4) << 15;

	successor->b = s->b >> 1;
	successor->b |= (opt_B(s) ^ _r7) << 7;

	uint8_t kk = (k[opt__select(Tt,y,s->r)] ^ successor->b) + s->l;

	successor->l = kk+s->r;
	successor->r = kk ;
}

void opt_suc(uint8_t* k,State* s, uint8_t *in)
{
	State x2;
	int i;
	bool head;
	for(i =0 ; i < 12 ; i++)
	{
		head = 1 & (in[i] >> 7);
		opt_successor(k,s,head,&x2);

		head = 1 & (in[i] >> 6);
		opt_successor(k,&x2,head,s);

		head = 1 & (in[i] >> 5);
		opt_successor(k,s,head,&x2);

		head = 1 & (in[i] >> 4);
		opt_successor(k,&x2,head,s);

		head = 1 & (in[i] >> 3);
		opt_successor(k,s,head,&x2);

		head = 1 & (in[i] >> 2);
		opt_successor(k,&x2,head,s);

		head = 1 & (in[i] >> 1);
		opt_successor(k,s,head,&x2);

		head = 1 & in[i];
		opt_successor(k,&x2,head,s);

	}

}

void opt_output(uint8_t* k,State* s,  uint8_t *buffer)
{
	uint8_t times = 0;
	uint8_t bout = 0;
	State temp = {0,0,0,0};
	for( ; times < 4 ; times++)
	{
		bout =0;
		bout |= (s->r & 0x4) << 5;
		opt_successor(k,s,0,&temp);
		bout |= (temp.r & 0x4) << 4;
		opt_successor(k,&temp,0,s);
		bout |= (s->r & 0x4) << 3;
		opt_successor(k,s,0,&temp);
		bout |= (temp.r & 0x4) << 2;
		opt_successor(k,&temp,0,s);
		bout |= (s->r & 0x4) << 1;
		opt_successor(k,s,0,&temp);
		bout |= (temp.r & 0x4) ;
		opt_successor(k,&temp,0,s);
		bout |= (s->r & 0x4) >> 1;
		opt_successor(k,s,0,&temp);
		bout |= (temp.r & 0x4) >> 2;
		opt_successor(k,&temp,0,s);
		buffer[times] = bout;
	}

}

void opt_MAC(uint8_t* k, uint8_t* input, uint8_t* out)
{
	State _init  =  {
			((k[0] ^ 0x4c) + 0xEC) & 0xFF,// l
			((k[0] ^ 0x4c) + 0x21) & 0xFF,// r
			0x4c, // b
			0xE012 // t
			};

	opt_suc(k,&_init,input);
	//printf("\noutp ");
	opt_output(k,&_init, out);
}

void opt_reverse_arraybytecpy(uint8_t* dest, uint8_t *src, size_t len)
{
	uint8_t i;
	for( i =0; i< len ; i++)
		dest[i] = reversebytes(src[i]);
}

void opt_doMAC(uint8_t *cc_nr_p, uint8_t *div_key_p, uint8_t mac[4])
{
	static uint8_t cc_nr[13];
	static uint8_t div_key[8];

	opt_reverse_arraybytecpy(cc_nr, cc_nr_p,12);
	memcpy(div_key,div_key_p,8);
	uint8_t dest []= {0,0,0,0,0,0,0,0};
	opt_MAC(div_key,cc_nr, dest);
	//The output MAC must also be reversed
	opt_reverse_arraybytecpy(mac, dest,12);
	return;
}
