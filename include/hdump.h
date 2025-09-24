/**
 * @file hdump.h
 *
 * @brief Canonical hexadecimal and ASCII dump functions declaration
 *
 * @copyright Copyright (c) 2025, J. A. Corbal.
 *            Licensed under the MIT license.  See `LICENSE` for details
 */

#ifndef HDUMP_H
#define HDUMP_H


#define HDUMP_CHUNK_SIZE (1024)  /***< Default chunk size to use */


/* Public interface */
/**
 * @brief Makes a canonical hexadecimal and ASCII dump of a file
 *
 * @param input    Input stream
 * @param output   Where to be displayed
 * @param columns  Columns to display
 * @param chunk_sz Size of chunk
 *
 * @return 0 if everything OK, or otherwise
 *
 * @note Data is processed in chunks of (2 * @e columns) bytes
 * @note Complexity:
 *  - Memory: @e O(chunk_sz + line_sz)
 *  - Time: @e O(n) for @e n bytes (@a memcmp cost per line: @e O(line_sz))
 */
int hdump(FILE *input, FILE *output, size_t columns, size_t chunk_sz);


#endif  /* ! HDUMP_H */
