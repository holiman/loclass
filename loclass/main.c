/*****************************************************************************
 * This file is part of iClassCipher. It is a reconstructon of the cipher engine
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
 * along with IClassCipher.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include <stdio.h>
#include <cipherutils.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cipherutils.h>
#include <cipher.h>
#include <ikeys.h>

#include <elite_crack.h>

int main(void)
{

	PrintAndLog("IClass Cipher version 1.0, Copyright (C) 2014 Martin Holst Swende\n");
	PrintAndLog("Comes with ABSOLUTELY NO WARRANTY");
	PrintAndLog("This is free software, and you are welcome to use, abuse and repackage, please keep the credits\n");


	testCipherUtils();
	testMAC();

	doKeyTests(0);

	testElite();

	return 0;
}

