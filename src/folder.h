#ifndef __FOLDER_H
#define __FOLDER_H

typedef struct File File;
typedef struct Folder Folder;

typedef struct File {

	char *name;
	struct Folder* parent;
	char *content; 

} File;

File* new_file(const char* _name, Folder* _parent, const char* _content);
char* read_file(File _fl);
char* file_name(File _fl);
void write_to_file(File* _fl, const char* _content);
void free_file(File* _fl);
void free_file(File* _fl);

typedef struct Folder {

	char *name;
	struct Folder* parent;

	struct File** filech;
	unsigned int filech_len;

	struct Folder** folderch;
	unsigned int folderch_len; 

} Folder;

Folder* new_folder(const char* _name, Folder* _parent);
void add_folder(Folder* _parent, Folder* _fo);
void add_file(Folder* _parent, File* _fl);
void free_folder(Folder* _fo);
char* list_folder(Folder* _fo);
char* print_path(Folder* _fo);

#endif // __FOLDER_H