/*
 * Copyright (C) 1996-2000 Michael R. Elkins <me@mutt.org>
 * 
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 */ 

/* flags to _mutt_copy_message */
#define M_CM_NOHEADER	1	/* don't copy the message header */
#define M_CM_PREFIX	(1<<1)	/* quote the message */
#define M_CM_DECODE	(1<<2)	/* decode the message body into text/plain */
#define M_CM_DISPLAY	(1<<3)	/* output is displayed to the user */
#define M_CM_UPDATE	(1<<4)  /* update structs on sync */
#define M_CM_WEED	(1<<5)  /* weed message/rfc822 attachment headers */
#define M_CM_CHARCONV	(1<<6)  /* perform character set conversions */
#define M_CM_PRINTING	(1<<7)	/* printing the message - display light */


#ifdef HAVE_PGP
#define M_CM_DECODE_PGP	(1<<8)	/* used for decoding PGP messages */
#define M_CM_DECODE_CRYPT	(1<<8)
#endif


#ifdef HAVE_SMIME
#ifdef M_CM_DECODE_CRYPT
#undef M_CM_DECODE_CRYPT
#endif
#define M_CM_DECODE_SMIME	(1<<9)	/* used for decoding S/MIME messages */
#ifdef HAVE_PGP
#undef M_CM_DECODE_CRYPT
#define M_CM_DECODE_CRYPT  (M_CM_DECODE_PGP | M_CM_DECODE_SMIME)
#else
#define M_CM_DECODE_CRYPT	(1<<9)	/* used for decoding S/MIME messages */
#endif
#endif


#if defined(HAVE_PGP) || defined(HAVE_SMIME)
#define M_CM_VERIFY	(1<<10)	/* do signature verification */
#endif




int mutt_copy_hdr (FILE *, FILE *, long, long, int, const char *);

int mutt_copy_header (FILE *, HEADER *, FILE *, int, const char *);

int _mutt_copy_message (FILE *fpout,
			FILE *fpin,
			HEADER *hdr,
			BODY *body,
			int flags,
			int chflags);

int mutt_copy_message (FILE *fpout,
		       CONTEXT *src,
		       HEADER *hdr,
		       int flags,
		       int chflags);

int _mutt_append_message (CONTEXT *dest,
			  FILE *fpin,
			  CONTEXT *src,
			  HEADER *hdr,
			  BODY *body,
			  int flags,
			  int chflags);

int mutt_append_message (CONTEXT *dest,
			 CONTEXT *src,
			 HEADER *hdr,
			 int cmflags,
			 int chflags);
