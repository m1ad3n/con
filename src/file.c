#include "folder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

File* new_file(const char* _name, Folder* _parent, const char* _content)
{
	File* tmp_file = (File*)malloc(sizeof(File));

	// name allocation
	tmp_file->name = (char*)malloc(strlen(_name));
	strcpy(tmp_file->name, _name);

	// file content
	tmp_file->content = (char*)malloc(strlen(_content));
	strcpy(tmp_file->content, _content);

	// parent
	if (_parent != NULL)
		add_file(_parent, tmp_file);
	else
		tmp_file->parent = _parent;

	// return the pointer
	return tmp_file;
}

char* read_file(File _fl)
{
	return _fl.content;
}

char* file_name(File _fl)
{
	return _fl.name;
}

void write_to_file(File* _fl, const char* _content)
{
	// free the last allocation
	free(_fl->content);

	// new allocation
	_fl->content = (char*)malloc(strlen(_content));
	strcpy(_fl->content, _content);
}

void free_file(File* _fl)
{
	free(_fl->name);
	free(_fl->content);
}