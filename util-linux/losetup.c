/*
 * Mini losetup implementation for busybox
 *
 * Copyright (C) 2002  Matt Kraai.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <getopt.h>
#include <stdlib.h>

#include "busybox.h"

int
losetup_main (int argc, char **argv)
{
  int offset = 0;

  /* This will need a "while(getopt()!=-1)" loop when we can have more than
     one option, but for now we can't. */
  switch(getopt(argc,argv, "do:")) {
    case 'd':
      /* detach takes exactly one argument */
      if(optind+1==argc)
        return del_loop(argv[optind]) ? EXIT_SUCCESS : EXIT_FAILURE;
      break;

    case 'o':
      offset = bb_xparse_number (optarg, NULL);
      /* Fall through to do the losetup */
    case -1:
      /* losetup takes two argument:, loop_device and file */
      if(optind+2==argc)
        return set_loop(&argv[optind], argv[optind + 1], offset)<0
	    ? EXIT_FAILURE : EXIT_SUCCESS;
      break;
  }
  bb_show_usage();
  return EXIT_FAILURE;
}
