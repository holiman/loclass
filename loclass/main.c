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
#include <unistd.h>
#include <ctype.h>
#include "cipherutils.h"
#include "cipher.h"
#include "ikeys.h"
#include "fileutils.h"
#include "elite_crack.h"

int unitTests()
{
	int errors = testCipherUtils();
	errors += testMAC();
	errors += doKeyTests(0);
	errors += testElite();
	return errors;
}
int showHelp()
{
	PrintAndLog("Usage: iclazz [options]");
	PrintAndLog("Options:");
	PrintAndLog("-t                 Perform self-test");
	PrintAndLog("-h                 Show this help");
	PrintAndLog("-f <filename>      Bruteforce iclass dumpfile");
	PrintAndLog("                   An iclass dumpfile is assumed to consist of 8 malicious CSNs,");
	PrintAndLog("                   on the binary format: ");
	PrintAndLog("                   <8 byte CSN><4 byte NR><4 byte MAC>");
	PrintAndLog("                   <8 byte CSN><4 byte NR><4 byte MAC>");
	PrintAndLog("                  ... totalling 8*16 bytes");

	return 0;
}

int main (int argc, char **argv)
{
	PrintAndLog("IClass Cipher version 1.2, Copyright (C) 2014 Martin Holst Swende\n");
	PrintAndLog("Comes with ABSOLUTELY NO WARRANTY");
	PrintAndLog("This is free software, and you are welcome to use, abuse and repackage, please keep the credits\n");
	char *fileName = NULL;
	int c;
	while ((c = getopt (argc, argv, "thf:")) != -1)
	  switch (c)
		{
		case 't':
		  return unitTests();
		case 'h':
		  return showHelp();
		case 'f':
		  fileName = optarg;
		  return bruteforceFile(fileName,0);
		case '?':
		  if (optopt == 'f')
			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		  else if (isprint (optopt))
			fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		  else
			fprintf (stderr,
					 "Unknown option character `\\x%x'.\n",
					 optopt);
		  return 1;
		//default:
		  //showHelp();
		}
	showHelp();
	return 0;
}

