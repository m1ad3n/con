#ifndef SHELL_H
#define SHELL_H

#include "folder.h"

typedef struct Shell {

	Folder* path;
	char* input;
	char** history;
	char* prompt;
	int exit_status;
	unsigned int command_count;
	char* prompt_id;

} Shell;

Shell* new_shell(const char* prompt_cmd, Folder* _path);
int exec(Shell* sh);
void free_shell(Shell* sh);
void print_history(Shell* sh);
void cd_dir(Shell* sh, char* dir);

#endif // SHELL_H