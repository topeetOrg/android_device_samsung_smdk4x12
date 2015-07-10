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

static const char filePrefix[FILE_TYPE_END][20] = {
	"kernel_", 
	"logcat_main_", 
	"logcat_radio_", 
	"logcat_event_", 
	"logcat_isp_",
	"logcat_user_",
};

/**
 *  @brief get file name by file type
 *
 *  @param path
 *             path that the panic file to be stored.
 *  @param fileType
 *             file types such as logcat** or kernel.
 *  @param filename
 *             file name to be used.
 *
 *  @return 0 for success -1 for errors
 */
int makeFilename(const char *path, enum logfileType fileType, char *filename)
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
	
	dir = opendir(path);
	prefixLen = strlen(filePrefix[fileType]);
	
	while((ptr = readdir(dir)) != NULL)
	{
		if(strncmp(ptr->d_name, filePrefix[fileType], prefixLen) == 0) {
			
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

#if 0	
	for(i = 0; i <= maxRound; i++) {
		LOGD("suffix %d: %s", i, fileSuffix[i]);
	}
#endif	
	
	/*process the existed files*/
	for(i = 0; i <= maxRound; i++) {
		if(i == DEFAULT_MAX_RECORD_RUNS - 1) {
			/*delete the oldest files*/
			for(j = 1; j < DEFAULT_MAX_INTERNAL_ROTATED_LOGS; j++) {
				sprintf(buf, "%s/%s%s.%d", path, filePrefix[fileType], fileSuffix[maxRound], j);				
				remove(buf);
			}
			
			buf[strlen(buf) - 2] = '\0';			
			remove(buf);
		} else {
			/*rename files e.g. kernel_i_@...*/
			sprintf(buf, "%s/%s%s", path, filePrefix[fileType], fileSuffix[i]);					
			for(j = DEFAULT_MAX_INTERNAL_ROTATED_LOGS - 1; j >= 0; j--) {
				//sprintf(buf, "%s/%s%s.%d", path, filePrefix[fileType], fileSuffix[i], j);
				
				if(j == 0) {
					asprintf(&file1, "%s", buf);
					asprintf(&file2, "%s", buf);
				} else {
					asprintf(&file1, "%s.%d", buf, j);
					asprintf(&file2, "%s.%d", buf, j);
				}				
				
				pos = strlen(path)+strlen(filePrefix[fileType])+1; // path/kernel_pos...
				file2[pos] = file2[pos] + 1;				
				
				if(access(file1, 0) == 0) {
					err = rename (file1, file2);					

					if (err < 0 && errno != ENOENT) {
						LOGE("while rotating log files");
					}
				}
				
				free(file1);
				free(file2);
			}					
		}
		
	}
	
CREATE_NEW_FILE:	
	/*create new name for the file*/	
	time(&cur_time);
    tim = localtime(&cur_time);
    sprintf(filename, "%s/%s0_@%04d-%02d-%02d-%02d-%02d-%02d", 
        path, filePrefix[fileType], tim->tm_year+1900, tim->tm_mon+1, tim->tm_mday, tim->tm_hour, tim->tm_min, tim->tm_sec);
	
	//LOGD("output file name is %s", filename);
	
	return 0;	
}

/**
 *  @brief check the specified path is exist, it will try to make 
           the path if it is not existed
 *
 *  @param path_name
 *             path that to be checked.
 *  @param try_round
 *             try_round to create the path.
 *
 *  @return 0 for path is fianlly prepared, -1 for failure
 */
int check_outpath_ready(char * path_name, int try_round)
{
    int error = -1;
    struct stat statbuf;
    int i = 0; 

    do{        
        if((lstat(path_name, &statbuf) == 0)  && (S_ISDIR(statbuf.st_mode) != 0))
        {
            LOGD("outpath %s ok\n",path_name);
            error = 0;
            break;
        }
        else
        {
            if(mkdir(path_name, 0755) == 0)
            {
                LOGD("create outpath %s ok\n",path_name);
                error = 0;
                break;                
            }
        }
		usleep(5000);
    }while( ++i <  try_round);

    return error;


}