#!/usr/bin/env bash
#
# Use as: $0 > src/descriptors/dr.h
#
readonly DR_H="src/descriptors/dr.h"
readonly DR_H_DIR=${DR_H%/*} # Bash's internal dirname equivalent

# check directory
if [[ ! -d $DR_H_DIR ]]; then
	echo >&2 "Directory $DR_H_DIR does not exist!!."
	echo >&2 "Please run this script in the libdvbpsi top directory."
	exit 1;
fi

cat <<EOF
/*****************************************************************************
 * dr.h
 * Copyright (C) 2001-2010 VideoLAN
 *
 * Authors: Arnaud de Bossoreille de Ribou <bozo@via.ecp.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

/*!
 * \file <dr.h>
 * \author Arnaud de Bossoreille de Ribou <bozo@via.ecp.fr>
 * \brief Gather all dr_*.h into one.
 *
 * Gathers all dr_*.h into one. Use this header if you need a lot of them.
 */

#ifndef _DVBPSI_DR_H_
#define _DVBPSI_DR_H_
EOF

cd $DR_H_DIR
for dir in atsc dvb mpeg custom; do
	cd $dir || { echo >&2 "$dir not found - tree incomplete" && exit 1; }
	for h in *.h; do
		echo "#include \"$dir/$h\""
	done
	cd ..
done

cat <<EOF

#else
#error "Multiple inclusions of dr.h"
#endif
EOF

exit 0
