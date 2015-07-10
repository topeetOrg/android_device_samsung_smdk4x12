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


#ifndef __RECORD_COMMON_H__
#define __RECORD_COMMON_H__

#define DEFAULT_FILE_SUFFIX_LEN 22

#define DEFAULT_MAX_RECORD_RUNS	4 
#define DEFAULT_MAX_INTERNAL_ROTATED_LOGS 2 //rotate number of files used by the same round running, e.g. e.g.kernel_1_time.*
#define OUT_PUT_DIR "/data/logmsg"

//for 4.2 version
#define LOGD ALOGD
#define LOGW ALOGW
#define LOGE ALOGE

/*_______________________________for file name utils*/
enum logfileType{
	FILE_TYPE_KERNEL = 0,
	FILE_TYPE_LOGCAT_MAIN,
	FILE_TYPE_LOGCAT_RADIO,
	FILE_TYPE_LOGCAT_EVENT,
	FILE_TYPE_LOGCAT_ISP,
	FILE_TYPE_LOGCAT_USER,
	FILE_TYPE_END,
};

/*_______________________________*/

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
int makeFilename(const char *path, enum logfileType fileType, char *filename);

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
int check_outpath_ready(char * path_name, int try_round);


#endif /* __RECORD_COMMON_H__ */
