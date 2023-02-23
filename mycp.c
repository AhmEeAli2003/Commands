/**
 * *******************************************************************************************
 *    @author: Ahmed Ali
 *    @file  : mycp.c
 *    @date  : 24 Feb 2023
 *    @brief : Write an itty-bitty cp command to copy content from file to another using
 *             system call warapper functions in C language.
 * *******************************************************************************************
 */

/* ************************************* Includes Section Start ************************************* */
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
/* ************************************* Includes Section End   ************************************* */

/* ************************************* Macros Section Start   ************************************* */
#define SUCCESS_RET           0
#define OPEN_FAILER_RET      -1
#define ARG_FAILER_RET       -1
#define ALLOC_FAILER_RET     -2
#define STDOUT                1
#define ZERO                  0
#define NULL_PTR              ((void *)(ZERO))
#define ONE	              1
#define TWO                   2
#define ARG_NUM               3
#define LEN                   100
/* ************************************* Macros Section End     ************************************* */

int main(int argc, char *argv[])
{
	unsigned int src_err_msg_len, dist_err_msg_len, arg_err_msg_len, arg_form_msg_len;
        signed int fd1 = ZERO, fd2 = ZERO, source_len = ZERO, temp = ZERO;

	char *arg_err_msg       = "too few arguments to 'mycp' command\n";
	char *arg_form_msg      = "\tmycp <source> <distination>\n"      ;
	char *src_file_err_msg  = "Can't open source file\n"             ;
	char *dist_file_err_msg = "Can't open disination file\n"         ;
	char *buf               = NULL_PTR                               ;

	arg_err_msg_len  = strlen(arg_err_msg)      ;
	arg_form_msg_len = strlen(arg_form_msg)     ;
	src_err_msg_len  = strlen(src_file_err_msg) ;
	dist_err_msg_len = strlen(dist_file_err_msg);


	if(argc != ARG_NUM)
	{
		write(STDOUT, arg_err_msg, arg_err_msg_len)  ;
		write(STDOUT, arg_form_msg, arg_form_msg_len);
		return ARG_FAILER_RET;
	}
	

	fd1 = open(argv[ONE], O_RDONLY);

	if(fd1 == OPEN_FAILER_RET)
	{
		write(STDOUT, src_file_err_msg, src_err_msg_len);
	}

	fd2 = open(argv[TWO], O_WRONLY|O_CREAT);

	if(fd2 == OPEN_FAILER_RET)
	{
		write(STDOUT, dist_file_err_msg, dist_err_msg_len);
	}

	buf = (char *) malloc(sizeof(char) * LEN);

	if(buf == NULL)
	{
	    return ALLOC_FAILER_RET;
	}

	while(temp = read(fd1, buf, LEN)) 
	{
		write(fd2, buf, temp);
	}
	
        
	free(buf);
	close(fd1);
	close(fd2);

	return SUCCESS_RET;

}
