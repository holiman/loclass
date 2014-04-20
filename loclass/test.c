// Test Code
// gcc -std=c99 test.c -o test -lssl
//
//
//
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <openssl/des.h>

static uint64_t output=0;
static uint16_t t=0xe012;
static uint8_t l=0, r=0, b=0x4c;
static bool B=0;
static bool x=0;
static uint8_t _select=0;

bool feeder_t(uint16_t t){
  bool x=0;
  x=(t & 0x8000)^(t & 0x4000);
  x^=(t & 0x400);
  x^=(t & 0x100);
  x^=(t & 0x20);
  x^=(t & 0x10);
  x^=(t & 0x2);
  x^=(t & 0x1);
return x;
}

bool feeder_b(uint8_t b){
 bool B=0;
 B=(b & 0x40)^(b & 0x20);
 B^=(b & 0x10);
 B^=(b & 0x1);
 return B;
}

//my attempt at the cipher state machine
uint32_t IClassAuthenticate(uint8_t *key,uint8_t *cc){
	output=0;
	l=0;
	r=0;
	b=0x4c;
	t=0xe012;
	_select=0;
	x=0;
	B=0;
	static bool t_t=0, b_b=0;
	int j=-1;
	uint8_t sr=0x1;

	printf("Pre: %x, b=%x l=%x r=%x t=%x x=%x B=%x\n",output,b,l,r,t,x,B);
	//initialisation
	uint16_t xor_s=key[0]^0x4c;
	l=(xor_s + 0xec)%256;
	r=(xor_s + 0x21)%256;

	x=feeder_t(t);
	B=feeder_b(b);
	//printf("Init: %x, b=%x l=%x r=%x t=%x x=%x B=%x\n",output,b,l,r,t,x,B);

	for(int i=0;i<96;i++){
	  if(i%8==0){
	   j++;
		sr=0x80;
	  }
	  bool cc_bit=(cc[j] & sr);
	  sr = sr >> 1;
	  printf("Inti: %x, b=%x l=%x r=%x t=%x x=%x B=%x cc=%x\n",output,b,l,r,t,x,B,cc_bit);
	  _select=0;
	  // 0=80 1=40 2=20 3=10 4=8 5=4 6=2 7=1
	  //_select= ( ( r[0] &  r[2]) ^ (r[1] & !r[3]) ^(r[2] | r[4]) );
	  bool temp1a=(r & 0x80) & (r & 0x20) ;
	  bool temp1b=(r & 0x40) & ~(r & 0x10);
	  bool temp1=(temp1a) ^ ( temp1b);
	  bool temp2=( (r & 0x20) | (r & 0x08));
	  if (temp1 ^ temp2) _select|= 0x4;
	  //_select+= ( ( r[2] |  r[0]) ^ (r[5] | r[7] ) ^ r[1] ^ r[6] ^ x ^cc_bit );
	  bool temp3a=((r & 0x20) | (r & 0x80));
	  bool temp3b=((r & 0x4)| (r & 0x1));
	  bool temp3=(temp3a ^ temp3b);
	  bool temp4=((r & 0x40) ^ (r & 0x2));
	  bool temp5= ( temp3 ^ temp4);
	  bool temp6= (temp5 ^ x);
	  if (temp6 ^ cc_bit) _select|= 0x2;
	  //_select+= ( ( r[3] & !r[5]) ^ (r[4] & r[6] ) ^ r[7] ^x );
	  bool temp7= ((r & 0x10) & ~( r & 0x4));
	  bool temp8= ((r & 0x8) & (r & 0x2));
	  bool temp9=(temp7 ^ temp8);
	  bool temp10= ((r & 0x1)^x);
	  if ( temp9 ^ temp10) _select|= 0x1;

		bool temp = ((r & 0x80) ^ (r & 0x8));
		t_t=(x ^ temp);
		t >>=1;
	   if(t_t) t= (t| 0x8000);
		x=feeder_t(t);

		b_b=B ^ (r & 0x1);
		b >>=1;
		if(b_b==1) b |= 0x80;
		B=feeder_b(b);

	  xor_s=(key[_select] ^ b);
	  //printf("xor: %02x\n",xor_s);
	  uint16_t r1=(xor_s + l)%256;
	 // printf("r1: %02x\n",r1);
	  l=(uint8_t)(r1 + r)%256;
	  //printf("l1: %02x\n",l);
	  r=r1;
	  //printf("a:%x\n",(r & 0x4));
	  //0x80 1x40 2x20 3x10 4x8 5x4 6x2 7x1
	  if (r & 0x4) output |= 0x80000000;
	  //if (r & 0x4) output |= 0x00000001;
	  printf("Inte: %x, b=%x l=%x r=%x t=%x x=%x B=%x sel=%0x\n",output,b,l,r,t,x,B,_select);
	  output >>=1;
	  //printf("Init: %x, b=%x l=%x r=%x t=%x x=%x\n",output,br,l,rr,t,x);
	  //output <<=1;

	}
	printf("%08x\n",output);
	return output;

}

//dont know if the one above is backwards, so this does operations in reverse
uint32_t IClassAuthenticate2(uint8_t *key,uint8_t *cc){
	output=0;
	l=0;
	r=0;
	b=0x4c;
	t=0xe012;
	_select=0;
	x=0;
	B=0;
	static bool t_t=0, b_b=0;
	int j=96;
	uint8_t sr=0x1;

	//initialisation
	uint16_t xor_s=key[0]^0x4c;
	l=((key[0]^0x4c) + 0xec)%256;
	r=((key[0]^0x4c) + 0x21)%256;

	x=feeder_t(t);
	B=feeder_b(b);
//	printf("Init: %x, b=%x l=%x r=%x t=%x x=%x\n",output,br,l,rr,t,x);

	for(int i=96;i>0;i--){
	  if(i%8==0){
	   j--;
		sr=0x1;
	  }
	  bool cc_bit=(cc[j] & sr);
	  sr = sr << 1;
	  _select=0;
	  // 0=80 1=40 2=20 3=10 4=8 5=4 6=2 7=1
	  //_select= ( ( r[0] &  r[2]) ^ (r[1] & !r[3]) ^(r[2] | r[4]) );
	  bool temp1a=(r & 0x80) & (r & 0x20) ;
	  bool temp1b=(r & 0x40) & ~(r & 0x10);
	  bool temp1=(temp1a) ^ ( temp1b);
	  bool temp2=( (r & 0x20) | (r & 0x08));
	  if (temp1 ^ temp2) _select|= 0x4;
	  //_select+= ( ( r[2] |  r[0]) ^ (r[5] | r[7] ) ^ r[1] ^ r[6] ^ x ^cc_bit );
	  bool temp3a=((r & 0x20) | (r & 0x80));
	  bool temp3b=((r & 0x4)| (r & 0x1));
	  bool temp3=(temp3a ^ temp3b);
	  bool temp4=((r & 0x40) ^ (r & 0x2));
	  bool temp5= ( temp3 ^ temp4);
	  bool temp6= (temp5 ^ x);
	  if (temp6 ^ cc_bit) _select|= 0x2;
	  //_select+= ( ( r[3] & !r[5]) ^ (r[4] & r[6] ) ^ r[7] ^x );
	  bool temp7= ((r & 0x10) & ~( r & 0x4));
	  bool temp8= ((r & 0x8) & (r & 0x2));
	  bool temp9=(temp7 ^ temp8);
	  bool temp10= ((r & 0x1)^x);
	  if ( temp9 ^ temp10) _select|= 0x1;

		bool temp = ((r & 0x80) ^ (r & 0x8));
		t_t=(x ^ temp);
		t >>=1;
	   if(t_t) t= (t| 0x8000);
		x=feeder_t(t);

		b_b=B ^ (r & 0x1);
		b >>=1;
		if(b_b==1) b |= 0x80;
		B=feeder_b(b);

	  xor_s=(key[_select] ^ b);
	  //printf("xor: %02x\n",xor_s);
	  uint16_t r1=(xor_s + l)%256;
	  l=(uint8_t)(r1 + r)%256;
	  r=r1;
	  //printf("a:%x\n",(r & 0x4));
	  //0x80 1x40 2x20 3x10 4x8 5x4 6x2 7x1
	  //if (r & 0x4) output |= 0x80000000;
	  if (r & 0x4) output |= 0x00000001;

	  //output >>=1;
	  output <<=1;

	}
	printf("%08x\n",output);
	return output;

}

//Simple DES encrypt - have to swap the parity bits etc- NOT COMPLETE
char * Encrypt( char *Key, char *Msg, int size){

		static char*    Res;
		int             n=0;
		DES_cblock      Key2;
		DES_key_schedule ks_a;
	DES_key_schedule ks_b;

		Res = ( char * ) malloc( size );

		memcpy( Key2, Key,8);
		//DES_set_odd_parity( &Key2 );
		DES_set_key( (const_DES_cblock*)&Key2[0], &ks_a );
	DES_set_key( (const_DES_cblock*)&Key2[8], &ks_b );

		DES_ede2_cbc_encrypt( ( unsigned char * ) Msg, ( unsigned char * ) Res,
						   size, &ks_a, &ks_b,&Key2, DES_ENCRYPT );

		 return (Res);
}

//Attempt to implement HASH0
uint64_t hash0(uint8_t *k){
  uint8_t x = k[0];
  uint8_t y = k[1];
  uint8_t z[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  uint8_t z1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  uint8_t pi[35] ={0x0F,0x17,0x1B,0x1D,0x1E,0x27,0x2B,0x2D,0x2E,0x33,0x35,0x39,0x36,0x3A,0x3C,0x47,0x4B,
	0x4D,0x4E,0x53,0x55,0x56,0x59,0x5A,0x5C,0x63,0x65,0x66,0x69,0x6A,0x6C,0x71,0x72,0x74,0x78};
  //   r              222222 223333 333344 444444 555555 556666 666677 777777
  //xxxxxxxx yyyyyyyy 111111 222222 333333 444444 555555 666666 777777 888888
  z[0] = (k[2] & 0xfc);
  z[1] = ((k[2] & 0x3) << 3) | ((k[3] & 0xf0) >> 2);
  z[2] = ((k[3] & 0xf) << 2) | ((k[4] & 0xc0) >> 3);
  z[3] = (k[4] & 0x3f);
  z[4] = (k[5] & 0xfc);
  z[5] = ((k[5] & 0x3) << 3) | ((k[6] & 0xf0) >> 2);
  z[6] = ((k[6] & 0xf) << 2) | ((k[7] & 0xc0) >> 3);
  z[7] = (k[7] & 0x3f);

  uint8_t x1=x%70;
  for(int i=0; i<4; i++){
	  z1[i]=(z[i] % 61 + i) + 3 - i;
  }
  for(int i=4; i<8; i++){
	  z1[i]=(z[i] % 56 + i) + 7 - i;
  }
  uint8_t p1[4]={0x00,0x00,0x00,0x00};
  uint8_t p2[4]={0x00,0x00,0x00,0x00};
  memcpy(p1,z1[0],4);
  memcpy(p2,z1[4],4);
  scramble(p1);
  scramble(p2);
  memcpy(z1,p1,4);
  memcpy(z1[4],p2,4);
  int index=pi[x1];
  //if (y[index] == 0 ){
	//todo
  //}else{
	//todo
  //}
  //more....
}

//attempt to implement scramble function
void scramble(uint8_t bytes){
  //todo
}


int davismain(){
	//taken from Dismantling_iClass_and_iClass_Elite.pdf
	static uint8_t key []={0xE0,0x33,0xCA,0x41,0x9A,0xEE,0x43,0xF9};

	static uint8_t cc[]={0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00};
	static uint8_t check[]={0x1d, 0x49, 0xc9, 0xda};
	static uint8_t card_id[]={0x47,0x47, 0x6C, 0x00, 0xF7, 0xFF, 0x12, 0xE0};

	char * div_key=Encrypt(key,card_id,8);
	//its not iclass DES have to re-arrange parity bits
	printf("%08x\n\n",div_key);
	//key=hash0(div_key);

	IClassAuthenticate(key,cc);
	IClassAuthenticate2(key,cc);

	//compare computed MACs against those from the Dismantling_iClass_and_iClass_Elite paper
	for (int j=0;j<4;j++){
	printf("%02x",check[j]);
	}
	printf("\n-------------\n");
	IClassAuthenticate(key2,cc2);
	IClassAuthenticate2(key2,cc2);
	for (int j=0;j<4;j++){
	printf("%02x",check2[j]);
	}
}

*/
