/**
 * @file main.c
 *
 * @brief Hexadecimal and ASCII dump of a file
 *
 * @author J. A. Corbal <jacorbal@gmail.com>
 * @copyright Copyright (c) 2025, J. A. Corbal.
 *            Licensed under the MIT license.  See `LICENSE` for details
 */

/* System includes */
#include <stdio.h>  /* fprintf, fopen,... */
#include <stdlib.h> /* malloc, free,... */

/* Local includes */
#include <hdump.h>


#define COLUMNS (8) /**< Optimal columns for representation;
                         also, data is taken in '2 * columns' chunks */


/**
 * @brief Main entry to open a file and dump the content of a file
 *
 * @return Status of the operation
 * @retval 0 Everything is OK
 * @retval 1 Argument error (just one argument needed)
 * @retval 2 File error (cannot open file)
 * @retval 3 Memory error (cannot allocate)
 */
int main(int argc, char *argv[])
{
  FILE *fp;

  /* check arguments */
  if (argc != 2) {
      fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  /* open the file */
  fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n",
            argv[0],
            argv[1]);
    return 2;
  }

  /* hex dump */
  if (hdump(fp, stdout, COLUMNS, HDUMP_CHUNK_SIZE) != 0) {
    fprintf(stderr, "%s: Insufficient memory available\n", argv[0]);
    return 3;
  }

  /* close file */
  fclose(fp);

  return 0;
}
