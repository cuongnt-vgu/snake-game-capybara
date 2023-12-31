#include "mbstrings.h"
#include <stddef.h>

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 * - Hints:
 * UTF-8 characters are encoded in 1 to 4 bytes. The number of leading 1s in the
 * highest order byte indicates the length (in bytes) of the character. For
 * example, a character with the encoding 1111.... is 4 bytes long, a character
 * with the encoding 1110.... is 3 bytes long, and a character with the encoding
 * 1100.... is 2 bytes long. Single-byte UTF-8 characters were designed to be
 * compatible with ASCII. As such, the first bit of a 1-byte UTF-8 character is
 * 0.......
 *
 * You will need bitwise operations for this part of the assignment!
 */

size_t mbslen(const char* bytes) {
    if (bytes == NULL) {
        return -1;  // NULL pointer, invalid input
    }

    size_t length = 0;

    while (*bytes) {
        unsigned char current = (unsigned char)(*bytes);

        // Single-byte character
        if ((current & 0x80) == 0x00) {
            length++;
            bytes++;
        }
        // Multi-byte character
        else if ((current & 0xC0) == 0xC0) {
            int num_bytes = 0;
            while ((current & 0x80) == 0x80) {
                current <<= 1;
                num_bytes++;
            }

            // Validate the number of bytes
            if (num_bytes < 2 || num_bytes > 4) {
                return -1;  // Invalid sequence
            }

            // Verify the following bytes in the sequence
            for (int i = 1; i < num_bytes; i++) {
                if ((bytes[i] & 0xC0) != 0x80) {
                    return -1;  // Incomplete sequence
                }
            }

            length++;
            bytes += num_bytes;
        } else {
            return -1;  // Invalid character
        }
    }

    return length;
}
