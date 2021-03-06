#/* **************** CLDD:1.0 s_09/print_license.sh **************** */
#/*
# * The code herein is: Copyright 1998-2009 by Jerry Cooperstein
# *
# * This Copyright is retained for the purpose of protecting free
# * redistribution of source.
# *
# * URL:    http://www.coopj.com
# * email:  coop@coopj.com 
# *
# * The primary maintainer for this code is Jerry Cooperstein
# * The CONTRIBUTORS file (distributed with this
# * file) lists those known to have contributed to the source.
# *
# * This code is distributed under Version 2 of the GNU General Public
# * License, which you should have received with the source.
# *
# */
#
#!/bin/bash
for names in $(cat /proc/modules | awk ' {print $1;} ')
        do echo -ne "$names\t     \t"
        modinfo $names | grep  license
done
