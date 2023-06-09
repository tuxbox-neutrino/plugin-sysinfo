/*
 * $Id: start.c,v 1.1 2009/12/20 16:22:58 rhabarber1848 Exp $
 *
 * sysinfo - coolstream linux project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <plugin.h>

#include "current.h"

#define SCRIPT __plugin__

#define PATH "/usr/bin/sysinfo"

int main(void)
{
	int pid, status;
	pid=fork();
	if (pid == -1) {
		fprintf(stderr, "[%s.so] fork\n", SCRIPT);
		return 1;
	} else
	if (pid == 0) {
		int ret;
		fprintf(stderr, "[%s.so] forked, executing %s\n", SCRIPT, SCRIPT);
		for (ret=3 ; ret < 255; ret++)
			close (ret);
			ret = system(PATH);
			if (ret)
				fprintf(stderr, "[%s.so] script return code: %d (%m)\n", SCRIPT, ret);
			else
				fprintf(stderr, "[%s.so] script return code: %d\n", SCRIPT, ret);
		_exit(ret);
	}
	fprintf(stderr, "[%s.so] parent, waiting for child with pid %d...\n", SCRIPT, pid);
	waitpid(pid, &status, 0);
	fprintf(stderr, "[%s.so] parent, waitpid() returned..\n", SCRIPT);
	if (WIFEXITED(status))
		fprintf(stderr, "[%s.so] child returned with status %d\n", SCRIPT, WEXITSTATUS(status));
	return 0;
}
