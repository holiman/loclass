#ifndef ELITE_CRACK_H
#define ELITE_CRACK_H
void permutekey(uint8_t key[8], uint8_t dest[8]);
/**
 * Permutes  a key from iclass specific format to NIST format
 * @brief permutekey_rev
 * @param key
 * @param dest
 */
void permutekey_rev(uint8_t key[8], uint8_t dest[8]);
/**
 * @brief Performs brute force attack against the remaining 126 bytes after the initial 2^24-attack has
 * recovered three bytes already. This attack runs considerably faster; 126 * 256 (max) diversify+MAC
 * calculations.
 * @param dump The dumpdata from iclass reader attack.
 * @param keytable where to write found values.
 * @return
 */
int bruteforceRemaining(uint8_t dump[], uint8_t keytable[]);
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
int bruteforceThreeBytes(uint8_t dump[], uint8_t keytable[]);

int bruteforceFile(const char *filename, int verify);

/**
 * @brief Test function
 * @return
 */
int testElite();

typedef struct {
	uint8_t simulated_csn[8];
	uint8_t key_indices[8];
	uint8_t recovered_keybytes[2];
} iclass_attack;

/**
  The malicious CSNs used, and their respective hash1 values, and the bytes they retrieve
**/
iclass_attack attack_data[8];



#endif
