#include "shell.h"
#include "folder.h"
#include "mystr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _get_input(Shell* sh);
void exec_command(Shell* sh);

Shell* new_shell(const char* _prompt_cmd, Folder* _path)
{
	Shell* tmp = (Shell*)malloc(sizeof(Shell));

	// history allocation
	tmp->history = (char**)malloc(sizeof(char*));
	tmp->command_count = 0;

	// path is a folder your currently in
	tmp->path = _path;
    tmp->prompt_id = (char*)malloc(strlen(_prompt_cmd));
    strcpy(tmp->prompt_id, _prompt_cmd);

	// prompt
	tmp->prompt = (char*)malloc(strlen(print_path(_path)));
	strcpy(tmp->prompt, print_path(_path));

	// exit status is return of the previous command
	tmp->exit_status = 0;

	return tmp;
}

int exec(Shell* sh)
{
	unsigned int buffer_size = 64;
	sh->input = (char*)malloc(sizeof(char) * buffer_size);
    
    if (_get_input(sh)) return 1;

    while (strcmp(sh->input, "exit"))
    {
        if (sh->input[0] != '\0')
        {
            sh->history[sh->command_count] = (char*)malloc(strlen(sh->input));
            strcpy(sh->history[sh->command_count++], sh->input);
            sh->history = (char**)realloc(sh->history, sizeof(char*) * (sh->command_count + 1));
        }

        exec_command(sh);

        if (_get_input(sh)) return 1;
    }
    return 0;
}

void exec_command(Shell* sh)
{
    if (!strcmp(sh->input, "history"))
        print_history(sh);

    else if (!strcmp(sh->input, "ls"))
        printf("%s", list_folder(sh->path));

    else if (!strcmp(sh->input, "clear"))
        system("clear");

    else if (!strcmp(sh->input, "pwd"))
        printf("%s\n", print_path(sh->path));

    else if (!strcmp(get_first_word(sh->input), "cd"))
        cd_dir(sh, get_second_word(sh->input));

    else if (!strcmp(get_first_word(sh->input), "cat"))
    {
        if (!get_second_word(sh->input)) return;
        for (int i = 0; i < sh->path->filech_len; i++)
            if (!strcmp(sh->path->filech[i]->name, get_second_word(sh->input)))
            {
                printf("%s", sh->path->filech[i]->content);

                if (sh->path->filech[i]->content[strlen(sh->path->filech[i]->content) - 1] != '\n')
                    printf("\e[7m%%\n\e[0m");
            }
    }

    else
        printf("Command not found\n");
}

int _get_input(Shell* sh)
{
    printf("%s %s ", sh->prompt, sh->prompt_id);
    putc('l', stdin);
    if (fgets(sh->input, 64, stdin) == NULL) {
        fprintf(stderr, "Can't read the user input\n");
        free(sh->input);
        return 1;
    }
    size_t length = strlen(sh->input);
    if (length > 1 && sh->input[length - 1] == '\n') {
        sh->input[length - 1] = '\0';
    }
    return 0;
}

void cd_dir(Shell* sh, char* dir)
{
    if (!dir) return;
    if (!strcmp(dir, "..") && sh->path->parent != NULL)
    {
        sh->path = sh->path->parent;
        sh->prompt = print_path(sh->path);
        return;
    }
    else if (!strcmp(dir, "..") && sh->path->parent == NULL)
        return;

    for (int i = 0; i < sh->path->folderch_len; i++)
    {
        if (!strcmp(sh->path->folderch[i]->name, dir))
        {
            sh->path = sh->path->folderch[i];
            break;
        }
    }
    sh->prompt = print_path(sh->path);
}

void print_history(Shell* sh)
{
	for (int i = 0; i < sh->command_count; i++)
		printf("%s\n", sh->history[i]);
}

void free_shell(Shell* sh)
{
	free(sh->prompt);
	for (int i = 0; i < sh->command_count; i++) {
		free(sh->history[i]);
	}
	free(sh->history);
	free(sh->input);
	free(sh);
}

