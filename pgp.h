/*
 * Copyright (C) 1996,1997 Michael R. Elkins <me@cs.hmc.edu>
 * Copyright (C) 1999-2000 Thomas Roessler <roessler@guug.de>
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

#ifdef HAVE_PGP

#include "crypt.h"
#include "pgplib.h"

WHERE REGEXP PgpGoodSign;

WHERE char *PgpSignAs;
WHERE short PgpTimeout;
WHERE char *PgpEntryFormat;


/* The command formats */

WHERE char *PgpClearSignCommand;
WHERE char *PgpDecodeCommand;
WHERE char *PgpVerifyCommand;
WHERE char *PgpDecryptCommand;
WHERE char *PgpSignCommand;
WHERE char *PgpEncryptSignCommand;
WHERE char *PgpEncryptOnlyCommand;
WHERE char *PgpImportCommand;
WHERE char *PgpExportCommand;
WHERE char *PgpVerifyKeyCommand;
WHERE char *PgpListSecringCommand;
WHERE char *PgpListPubringCommand;
WHERE char *PgpGetkeysCommand;

/* prototypes */

int pgp_check_traditional (FILE *, BODY *, int);
BODY *pgp_decrypt_part (BODY *, STATE *, FILE *, BODY *);
BODY *pgp_make_key_attachment (char *);
const char *pgp_micalg (const char *fname);

char *_pgp_keyid (pgp_key_t *);
char *pgp_keyid (pgp_key_t *);


int mutt_check_pgp (HEADER * h);
int mutt_is_application_pgp (BODY *);

int pgp_is_multipart_encrypted (BODY *);


int pgp_decrypt_mime (FILE *, FILE **, BODY *, BODY **);

/* int pgp_string_matches_hint (const char *s, LIST * hints); */

#define pgp_valid_passphrase() crypt_valid_passphrase(APPLICATION_PGP)

/* pgp_key_t *gpg_get_candidates (struct pgp_vinfo *, pgp_ring_t, LIST *); */
pgp_key_t *pgp_ask_for_key (char *, char *, short, pgp_ring_t);
pgp_key_t *pgp_get_candidates (pgp_ring_t, LIST *);
pgp_key_t *pgp_getkeybyaddr (ADDRESS *, short, pgp_ring_t);
pgp_key_t *pgp_getkeybystr (char *, short, pgp_ring_t);

void pgp_forget_passphrase (void);
void pgp_application_pgp_handler (BODY *, STATE *);
void pgp_encrypted_handler (BODY *, STATE *);
void pgp_extract_keys_from_attachment_list (FILE * fp, int tag, BODY * top);
void pgp_void_passphrase (void);




/* The PGP invocation interface - not really beautiful. */

pid_t pgp_invoke_decode (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd, 
			 const char *fname, short need_passphrase);
pid_t pgp_invoke_verify (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd, 
			 const char *fname, const char *sig_fname);
pid_t pgp_invoke_decrypt (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			  int pgpinfd, int pgpoutfd, int pgperrfd, 
			  const char *fname);
pid_t pgp_invoke_sign (FILE **pgpin, FILE **pgpout, FILE **pgperr,
		       int pgpinfd, int pgpoutfd, int pgperrfd, 
		       const char *fname);
pid_t pgp_invoke_encrypt (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			  int pgpinfd, int pgpoutfd, int pgperrfd,
			  const char *fname, const char *uids, int sign);
pid_t pgp_invoke_export (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd, 
			 const char *uids);
pid_t pgp_invoke_verify_key (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			     int pgpinfd, int pgpoutfd, int pgperrfd, 
			     const char *uids);
pid_t pgp_invoke_list_keys (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			    int pgpinfd, int pgpoutfd, int pgperrfd, 
			    pgp_ring_t keyring, LIST *hints);
pid_t pgp_invoke_traditional (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			  int pgpinfd, int pgpoutfd, int pgperrfd,
			  const char *fname, const char *uids, int flags);


void pgp_invoke_import (const char *fname);
void pgp_invoke_getkeys (ADDRESS *);


/* private ? */
int pgp_verify_one (BODY *, STATE *, const char *);
BODY *pgp_traditional_encryptsign (BODY *, int, char *);
BODY *pgp_encrypt_message (BODY *, char *, int);
BODY *pgp_sign_message (BODY *);


#endif /* HAVE_PGP */
