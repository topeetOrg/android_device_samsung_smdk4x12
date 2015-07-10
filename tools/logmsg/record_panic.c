/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Muuss.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

#include <time.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include "logmsg_common.h"

/**
 *  @brief Get the panic file name to be used
 *
 *  @param path
 *             path that the panic file to be stored.
 *  @param filename
 *             the file name to be used[including the path information].
 *
 *  @return 0
 */
int makePanicFileName(const char *path, char *filename)
{
	char buf[256];
	DIR *dir;
	struct dirent *ptr;
	int last_num = 0;
	int files = 0;
	char fileSuffix[DEFAULT_MAX_RECORD_RUNS][30] = {{'\0',},{'\0',},};
	int currentRound = -1, maxRound = 0;
	int prefixLen = 0;
	int i, j, pos;
	char *file1, *file2;
	time_t cur_time;
	struct  tm *tim; 
	int err;
	char filePrefix[] = "panic_";	
	
	dir = opendir(path);
	prefixLen = strlen(filePrefix);
	
	while((ptr = readdir(dir)) != NULL)
	{
		if(strncmp(ptr->d_name, filePrefix, prefixLen) == 0) {
			
			if(currentRound != (int)(ptr->d_name[prefixLen] - 48)) {
				currentRound = (int)(ptr->d_name[prefixLen] - 48);
				maxRound = maxRound < currentRound ? currentRound : maxRound;
				if(currentRound > DEFAULT_MAX_RECORD_RUNS - 1) {
					LOGE("error, record round number exceed the limitation");
					currentRound = DEFAULT_MAX_RECORD_RUNS - 1;
				}
				strncpy(fileSuffix[currentRound], &ptr->d_name[prefixLen], DEFAULT_FILE_SUFFIX_LEN);
				fileSuffix[currentRound][DEFAULT_FILE_SUFFIX_LEN] = '\0';
			}			
		}		
	}

	/*special case, no files ever created*/
	if(currentRound == -1) {
		/*first time to create*/
		goto CREATE_NEW_FILE;
	}
	
	for(i = 0; i <= maxRound; i++) {
		LOGD("suffix %d: %s", i, fileSuffix[i]);
	}
	
	/*process the existed files*/
	for(i = 0; i <= maxRound; i++) {
		if(i == DEFAULT_MAX_RECORD_RUNS - 1) {
			/*delete the oldest files*/
			sprintf(buf, "%s/%s%s", path, filePrefix, fileSuffix[maxRound]);			
			LOGD("delete lodest file %s", buf); // should be deleted
			remove(buf);
		} else {
			/*rename files e.g. kernel_i_@...*/
			sprintf(buf, "%s/%s%s", path, filePrefix, fileSuffix[i]);		
			LOGD("file series to be renamed is %s", buf);
			
			asprintf(&file1, "%s", buf);
			asprintf(&file2, "%s", buf);
			
			pos = strlen(path)+strlen(filePrefix)+1; // path/panic_pos...
			file2[pos] = file2[pos] + 1;
			LOGD("old file name: %s, new file name: %s", file1, file2);	
			
			if(access(file1, 0) == 0) {
				err = rename (file1, file2);
				LOGD("old file: %s, new file: %s", file1, file2);

				if (err < 0 && errno != ENOENT) {
					LOGE("while rotating log files");
				}
			}
			
				free(file1);
				free(file2);
			
			}					
		}		
	
CREATE_NEW_FILE:	
	/*create new name for the file*/	
	time(&cur_time);
    tim = localtime(&cur_time);
    sprintf(filename, "%s/panic_0_@%04d-%02d-%02d-%02d-%02d-%02d", 
        path, tim->tm_year+1900, tim->tm_mon+1, tim->tm_mday, tim->tm_hour, tim->tm_min, tim->tm_sec);
	
	LOGD("output file name is %s", filename);
	
	return 0;	
} 

/**
 *  @brief record last time's panic message to file
 *
 *  @param path
 *             path that the panic file to be stored.
 *
 *  @return 0 for success -1 for errors
 */
int record_panic_message(const char *path) 
{
	int input_fd, output_fd;
	char buf[256*1024];
	char inputFileName[] = "/dev/panic_msg";
	char outputFileName[256];
	size_t count;
	
	input_fd = open(inputFileName, O_RDONLY); 
	
	if(input_fd < 0) {
		LOGD("panic recording not supported");
		return -1;
	}
	
	count = read(input_fd, buf, 256*1024);
	
	if(count == 0) {
		/*no panic message existed*/
		LOGD("no panic information exist"); // first time to burn image
		close(input_fd);
		return 0;
	}
	
	makePanicFileName(path, outputFileName);
	
	output_fd = open(outputFileName, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(output_fd < 0) {
		LOGE("panic open output file error");
		close(input_fd);
		return -1;
	}
	
	write(output_fd, buf, count);
	
	close(input_fd);
	close(output_fd);	
	
	return 0;
}
 
int main(int argc, char *argv[])
{	
	if(check_outpath_ready(OUT_PUT_DIR, 3) != 0) {
		LOGE("failed to create output directory");
		return -1;
	}
	return record_panic_message(OUT_PUT_DIR);
}
