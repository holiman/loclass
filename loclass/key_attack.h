#ifndef KEY_ATTACK_H
#define KEY_ATTACK_H

typedef struct {
	uint8_t simulated_csn[8];
	uint8_t key_indices[8];
	uint8_t recovered_keybyte;
} iclass_attack;
/**
 * @brief Returns information about the attack of a certain number. Each attack is
 * represented by
 *- A special malicious CSN, crafted to extract one more previously unknown byte of the key table.
 *- A hash1 value, representing the indices to the key-table that the key_sel is comprised of
 *- A byte to know which byte-index is recovered at this attack stage.
 *  The first one (index 0) is special, since it
 * recovered three bytes, and requires (max) 2^24  calculations to recover. That also means that the
 * recovered_keybyte index is incorrect for index 0.
 * @param i the number to get
 * @return an iclass_attack struct
 */
iclass_attack get_attack_data(uint8_t i);
#endif // KEY_ATTACK_H
