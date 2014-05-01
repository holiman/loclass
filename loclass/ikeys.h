#ifndef IKEYS_H
#define IKEYS_H

void hash0(uint64_t c, uint8_t k[8]);
int doKeyTests(uint8_t debuglevel);
void diversifyKey(uint8_t csn[8], uint8_t key[8], uint8_t div_key[8]);
#endif // IKEYS_H
