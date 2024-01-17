#include <stdio.h>
#include "folder.h"
#include "shell.h"

int main(void)
{
	Folder* root = new_folder("/", NULL);
	Folder* usr = new_folder("usr", root);
	Folder* bin = new_folder("bin", usr);
	Folder* home = new_folder("home", root);
	Folder* user = new_folder("home", home);
	File* example = new_file("example.txt", user, "Simple text for example.txt\n");
	File* test = new_file("version", root, "v0.1\n");


	Shell* bash = new_shell("%", root);
	exec(bash);

	free_shell(bash);
	
	/* you need only to run free_folder() for the root folder bcs it will automatically free the child folders and files */
	free_folder(root);
	return 0;
}