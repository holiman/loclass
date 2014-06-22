#ifndef FILEUTILS_H
#define FILEUTILS_H
/**
 * @brief Utility function to save data to a file. This method takes a preferred name, but if that
 * file already exists, it tries with another name until it finds something suitable.
 * E.g. dumpdata-15.txt
 * @param preferredName
 * @param suffix the file suffix. Leave out the ".".
 * @param data The binary data to write to the file
 * @param datalen the length of the data
 * @return 0 for ok, 1 for failz
 */
int saveFile(const char *preferredName, const char *suffix, const void* data, size_t datalen);
/**
 * @brief Utility function to save load binary data from a a file. This method takes a filename,
 * Should only be used for fixed-size binary files
 * @param fileName the name of the file
 * @param data a buffer to place data in
 * @param datalen the length of the data/data.
 * @return
 */

int loadFile(const char *fileName, void* data, size_t datalen);

/**
 * Utility function to print to console. This is used consistently within the library instead
 * of printf, but it actually only calls printf. The reason to have this method is to
 *make it simple to plug this library into proxmark, which has this function already to
 * write also to a logfile. When doing so, just delete this function.
 * @param fmt
 */
void PrintAndLog(char *fmt, ...);
#endif // FILEUTILS_H
