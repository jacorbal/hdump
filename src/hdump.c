/**
 * @file hdump.c
 *
 * @brief Canonical hexadecimal and ASCII dump implementation
 *
 * @copyright Copyright (c) 2025, J. A. Corbal.
 *            Licensed under the MIT license.  See `LICENSE` for details
 */

/* System includes */
#include <ctype.h>      /* isprint */
#include <stdint.h>     /* uint32_t */
#include <stdio.h>      /* fprintf, fread */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memcmp, memcpy */

/* Local includes */
#include <hdump.h>


/* Print hexadecimal dump */
int hdump(FILE *input, FILE *output, size_t columns, size_t chunk_sz)
{
    if (input == NULL || output == NULL || columns == 0 || chunk_sz == 0) {
        return -1;
    }

    unsigned char *buffer = malloc(chunk_sz);
    if (buffer == NULL) {
        return -1;
    }

    /* Buffer to compare complete lines (2 * columns bytes) */
    size_t line_sz = 2 * columns;
    unsigned char *prev = malloc(line_sz);
    if (prev == NULL) {
        free(buffer);
        return -1;
    }

    int have_prev = 0;     /* have a previous line saved */
    int in_repeat = 0;     /* there's a repetition sequence */
    uint32_t offset = 0;   /* counter for total read bytes */
    while (1) {
        size_t tsize = 0;
        size_t bytes_read = fread(buffer, 1, chunk_sz, input);
        if (bytes_read == 0) {
            break;
        }

        while (tsize < bytes_read) {
            size_t line_bytes = (bytes_read - tsize) >=
                (line_sz) ? line_sz : (bytes_read - tsize);

            /* Build normalized line of size 'line_sz' to compare */
            unsigned char linebuf[line_sz];
            for (size_t i = 0; i < line_sz; ++i) {
                if (i < line_bytes) linebuf[i] = buffer[tsize + i];
                else linebuf[i] = 0;
            }

            if (!have_prev) {
                /* First read line: print and save */
                fprintf(output, "%08x  ", offset);
                for (size_t i = 0; i < line_sz; ++i) {
                    if (i < line_bytes) {
                        fprintf(output, "%02x ", linebuf[i]);
                    }
                    else {
                        fprintf(output, "   ");
                    }
                    if (i == columns - 1) {
                        fprintf(output, " ");
                    }
                }
                fprintf(output, " |");

                for (size_t i = 0; i < line_bytes; ++i) {
                    unsigned char c = linebuf[i];
                    fputc(isprint(c) ? c : '.', output);
                }
                fprintf(output, "|\n");

                memcpy(prev, linebuf, line_sz);
                have_prev = 1;
                in_repeat = 0;
            } else {
                if (memcmp(prev, linebuf, line_sz) == 0) {
                    /* Line equal to the previous one... */
                    if (!in_repeat) {
                        fprintf(output, "*\n");
                        in_repeat = 1;
                    }
                    /* ...if it's repeated, don't print more */
                } else {
                    /* Different line: print and update 'prev' */
                    fprintf(output, "%08x  ", offset);
                    for (size_t i = 0; i < line_sz; ++i) {
                        if (i < line_bytes) {
                            fprintf(output, "%02x ", linebuf[i]);
                        }
                        else {
                            fprintf(output, "   ");
                        }
                        if (i == columns - 1) {
                            fprintf(output, " ");
                        }
                    }

                    fprintf(output, " |");
                    for (size_t i = 0; i < line_bytes; ++i) {
                        unsigned char c = linebuf[i];
                        fputc(isprint(c) ? c : '.', output);
                    }
                    fprintf(output, "|\n");

                    memcpy(prev, linebuf, line_sz);
                    in_repeat = 0;
                }
            }

            tsize += line_bytes;
            offset += (uint32_t)line_bytes;
        }
    }

    /* Print final offset */
    fprintf(output, "%08x\n", offset);

    free(prev);
    free(buffer);

    return 0;
}
