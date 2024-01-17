# Container Project Documentation

## Overview

This container project implements a basic file system structure and a shell interface in C. The project consists of several files:

- `main.c`: Entry point of the program, where the initial folder structure is created, the shell is launched, and resources are freed at the end.
- `folder.h` and `folder.c`: Define the structures for `Folder` and `File`, along with functions for working with folders and files.
- `shell.h` and `shell.c`: Implement a shell that allows users to interact with the file system. The shell supports basic commands like `ls`, `pwd`, `cd`, `cat`, and `history`.
- `mystr.h` and `mystr.c`: Define helper functions for manipulating strings, such as extracting the first and second words from an input string.

## Usage

The program starts in `main.c`, where the initial folder structure is created, and the shell is launched. Users can interact with the file system through the shell, executing various commands.

### Supported Commands

- `ls`: List all files and folders in the current directory.
- `pwd`: Print the current working directory.
- `cd folder_name`: Change the current directory to the specified folder.
- `cat file_name`: Display the content of a specific file.
- `history`: Display the history of entered commands.

### Building and Running

To build the project, compile the source files using a C compiler:

```bash
make
```

### Run the compiled executable

```bash
./container
```

## Example usage

```bash
% ls
usr
% cd usr
/usr % ls
bin
/usr % cd bin
/usr/bin % pwd
/usr/bin
/usr/bin % cat example.txt
This is the content of the example file.
/usr/bin % cd ..
/usr %
```

## Exiting the Shell

### To exit the shell and end the program, enter the command:

```bash
exit
```

## Data Structures

- **Folder:** Represents a folder with information about its name, parent folder, and lists of subfolders and files.
- **File:** Represents a file with information about its name, parent folder, and content.
- **Shell:** Represents the shell interface with information about the current path, user input, command history, prompt, exit status, and command count.

## Helper Functions

- `get_first_word` and `get_second_word`: Functions from `mystr.c` that extract the first and second words from a given input string.

## Command Execution

The `exec_command` function in `shell.c` interprets user input and executes the corresponding command.

## Conclusion

### This container project provides a basic implementation of a file system and shell in C. It can be extended and enhanced by adding new features, supporting different file types, and improving the user interface. The README serves as a guide for building, running, and understanding the structure of the project.

### Feel free to explore and modify the code to suit your specific needs. If you have any questions or issues, please contact the project contributors.