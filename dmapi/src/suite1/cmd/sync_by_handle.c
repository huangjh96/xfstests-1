// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2000-2001 Silicon Graphics, Inc.
 * All Rights Reserved.
 */

#include <lib/hsm.h>

#include <getopt.h>
#include <string.h>


/*---------------------------------------------------------------------------

Test program used to test the DMAPI function dm_sync_by_handle().  The
command line is:

	sync_by_handle [-s sid] pathname

where:
'sid' is the session ID to use for the call.
'pathname' is the name of the file to be sync'd.

----------------------------------------------------------------------------*/

#ifndef linux
extern	char	*sys_errlist[];
#endif
extern  int     optind;
extern  char    *optarg;


char	*Progname;


static void
usage(void)
{
	fprintf(stderr, "usage:\t%s [-s sid] pathname\n", Progname);
	exit(1);
}


int
main(
	int	argc, 
	char	**argv)
{
	dm_sessid_t	sid = DM_NO_SESSION;
	char		*pathname = NULL;
	void		*hanp;
	size_t		hlen;
	char		*name;
	int		opt;

	Progname = strrchr(argv[0], '/');
	if (Progname) {
		Progname++;
	} else {
		Progname = argv[0];
	}

	/* Crack and validate the command line options. */

	while ((opt = getopt(argc, argv, "s:")) != EOF) {
		switch (opt) {
		case 's':
			sid = atol(optarg);
			break;
		case '?':
			usage();
		}
	}
	if (optind + 1 != argc)
		usage();
	pathname = argv[optind];

	if (dm_init_service(&name) == -1)  {
		fprintf(stderr, "Can't initialize the DMAPI\n");
		exit(1);
	}
	if (sid == DM_NO_SESSION)
		find_test_session(&sid);

	/* Get the file's handle. */

	if (dm_path_to_handle(pathname, &hanp, &hlen)) {
		fprintf(stderr, "can't get handle for file %s\n", pathname);
		exit(1);
	}

	if (dm_sync_by_handle(sid, hanp, hlen, DM_NO_TOKEN)) {
		fprintf(stderr, "dm_sync_by_handle failed, %s\n",
			strerror(errno));
		exit(1);
	}
	dm_handle_free(hanp, hlen);
	exit(0);
}
