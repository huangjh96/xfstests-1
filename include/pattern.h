// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2000 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#ifndef _PATTERN_H_
#define _PATTERN_H_

/*
 * pattern_check(buf, buflen, pat, patlen, patshift)
 *
 * Check a buffer of length buflen against repeated occurrances of
 * a pattern whose length is patlen.  Patshift can be used to rotate
 * the pattern by patshift bytes to the left.
 *
 * Patshift may be greater than patlen, the pattern will be rotated by
 * (patshift % patshift) bytes.
 *
 * pattern_check returns -1 if the buffer does not contain repeated
 * occurrances of the indicated pattern (shifted by patshift).
 *
 * The algorithm used to check the buffer relies on the fact that buf is 
 * supposed to be repeated copies of pattern.  The basic algorithm is
 * to validate the first patlen bytes of buf against the pat argument
 * passed in - then validate the next patlen bytes against the 1st patlen
 * bytes - the next (2*patlen) bytes against the 1st (2*pathen) bytes, and
 * so on.  This algorithm only works when the assumption of a buffer full
 * of repeated copies of a pattern holds, and gives MUCH better results
 * then walking the buffer byte by byte.
 *
 * Performance wise, It appears to be about 5% slower than doing a straight
 * memcmp of 2 buffers, but the big win is that it does not require a
 * 2nd comparison buffer, only the pattern.
 */
int pattern_check( char * , int , char * , int , int );

/*
 * pattern_fill(buf, buflen, pat, patlen, patshift)
 *
 * Fill a buffer of length buflen with repeated occurrances of
 * a pattern whose length is patlen.  Patshift can be used to rotate
 * the pattern by patshift bytes to the left.
 *
 * Patshift may be greater than patlen, the pattern will be rotated by
 * (patshift % patlen) bytes.
 *
 * If buflen is not a multiple of patlen, a partial pattern will be written
 * in the last part of the buffer.  This implies that a buffer which is
 * shorter than the pattern length will receive only a partial pattern ...
 *
 * pattern_fill always returns 0 - no validation of arguments is done.
 *
 * The algorithm used to fill the buffer relies on the fact that buf is 
 * supposed to be repeated copies of pattern.  The basic algorithm is
 * to fill the first patlen bytes of buf with the pat argument
 * passed in - then copy the next patlen bytes with the 1st patlen
 * bytes - the next (2*patlen) bytes with the 1st (2*pathen) bytes, and
 * so on.  This algorithm only works when the assumption of a buffer full
 * of repeated copies of a pattern holds, and gives MUCH better results
 * then filling the buffer 1 byte at a time.
 */
int pattern_fill( char * , int , char * , int , int );

#endif
