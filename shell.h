#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>


void execute_command(const char *command);
void execute_parent(pid_t child_pid, const char *command);
void execute_child(const char *command);

/**
 * passinfo - Structure for storing command information
 * @ac: Argument count
 * @av: Argument vector (array of strings)
 * @linecnt_flag: Line count flag
 * @fname: File name
 * @path: Path information
 * @arg_cnt: Count of arguments
 * @line_cnt: Line count
 * @err_num: Error number
 * @env_vars: Environment variables array
 * @env_changed: Environment change flag
 * @status: Status code
 * @cmd_buf_ptr: Pointer to command chain buffer, for memory management
 * @cmd_buf_type: Command type: ||, &&, ;
 * @read_fd: Read file descriptor
 * @hist_cnt: History count
 */
typedef struct passinfo
{
    char *ac;
    char **av;
    char *path;
    int arg_cnt;
    int err_num;
    int linecnt_flag;
    unsigned int line_cnt;
    char *fname;
    int status;
    char **env_vars;
    int hist_cnt;
    int env_changed;
    char **cmd_buf_ptr;
    int read_fd;
    
} passinfo_t;

#endif


