#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "folder.h"

Folder* new_folder(const char* _name, Folder* _parent)
{
	Folder* tmp = (Folder*)malloc(sizeof(Folder));

	// allocate memory for name string
	tmp->name = (char*)malloc(strlen(_name));
	strcpy(tmp->name, _name);

	// allocte memory for folders and files
	tmp->folderch = (Folder**)malloc(sizeof(Folder*));
	tmp->filech = (File**)malloc(sizeof(File*));

	tmp->folderch_len = 0;
	tmp->filech_len = 0;

	// allocate memory for parent
	if (_parent == NULL)
	{
		tmp->parent = _parent;
		return tmp;
	}

	tmp->parent = _parent;
	add_folder(_parent, tmp);

	return tmp;
}

void add_folder(Folder* _parent, Folder* _fo)
{
	_parent->folderch[_parent->folderch_len++] = _fo;
	_parent->folderch = (Folder**)realloc(_parent->folderch, sizeof(Folder*) * (_parent->folderch_len + 1));
}

void add_file(Folder* _parent, File* _fl)
{
	_parent->filech[_parent->filech_len++] = _fl;
	_parent->filech = (File**)realloc(_parent->filech, sizeof(File*) * (_parent->filech_len + 1));
}

void free_folder(Folder* _fo)
{
	free(_fo->name);

	for (int i = 0; i < _fo->folderch_len; i++)
	{
		free_folder(_fo->folderch[i]);
	}

	for (int i = 0; i < _fo->filech_len; i++)
	{
		free_file(_fo->filech[i]);
	}

	free(_fo);
}

char* list_folder(Folder* _fo)
{
	char* tmp = (char*)malloc(sizeof(char));
	tmp[0] = '\0';
	for (int i = 0; i < _fo->folderch_len; i++)
	{
		tmp = (char*)realloc(tmp,  strlen(tmp) + strlen(_fo->folderch[i]->name) + 3);
		strcat(tmp, _fo->folderch[i]->name);
		strcat(tmp, "/\n");
	}

	for (int i = 0; i < _fo->filech_len; i++)
	{
		tmp = (char*)realloc(tmp,  strlen(tmp) + strlen(_fo->filech[i]->name) + 2);
		strcat(tmp, _fo->filech[i]->name);
		strcat(tmp, "\n");
	}
	tmp = realloc(tmp,  strlen(tmp) + 1);
	strcat(tmp, "\0");

	return tmp;
}

void append_name(Folder* root, char* tmp)
{
	tmp = (char*)realloc(tmp, strlen(tmp) + strlen(root->name) + 1);
	if (root->parent == NULL)
		strcat(tmp, root->name);
	else {
		append_name(root->parent, tmp);
		strcat(tmp, root->name);
		strcat(tmp, "/");
	}
}

char* print_path(Folder* root)
{
	char *tmp = (char*)malloc(sizeof(char));
	tmp[0] = '\0';
	append_name(root, tmp);

	tmp = (char*)realloc(tmp, strlen(tmp) + 1);
	if (strlen(tmp) > 1 && tmp[strlen(tmp) - 1] == '/')
		tmp[strlen(tmp) - 1] = '\0';
	else
		strcat(tmp, "\0");

	return tmp;
}