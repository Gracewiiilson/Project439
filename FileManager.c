#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_PERMISSIONS_LENGTH 10
#define MAX_OWNER_LENGTH 50

typedef struct File {
    char* name;
    char* permissions;
    char* owner;
    char* contents; // new field for file contents
} 
File;

typedef struct Directory {
    char dirname[MAX_FILENAME_LENGTH];
    int num_files;
    File* files;
    int num_subdirs;
    struct Directory** subdirs;
    int count;
} 
Directory;

void create_file(Directory* directory, char* name, char* contents, char* permissions, char* owner) {
    File* file = malloc(sizeof(File));
    file->name = strdup(name);
    file->permissions = strdup(permissions);
    file->owner = strdup(owner);
    file->contents = strdup(contents); // set the contents of the file
}


void read_file(Directory* dir, char* filename) {
    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(filename, dir->files[i].name) == 0) {
            printf("%s\n", dir->files[i].contents);
            return;
        }
    }
    printf("File not found.\n");
}

void write_file(Directory* dir, char* filename, char* contents) {
    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(filename, dir->files[i].name) == 0) {
            strcpy(dir->files[i].contents, contents);
            printf("File updated successfully.\n");
            return;
        }
    }
    printf("File not found.\n");
}

void delete_file(Directory* dir, char* filename) {
    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(filename, dir->files[i].name) == 0) {
            for (int j = i; j < dir->num_files - 1; j++) {
                dir->files[j] = dir->files[j + 1];
            }
            dir->num_files--;
            dir->files = realloc(dir->files, dir->num_files * sizeof(File));
            printf("File deleted successfully.\n");
            return;
        }
    }
    printf("File not found.\n");
}

void change_file_permissions(Directory* dir, char* filename, char* permissions) {
    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(filename, dir->files[i].name) == 0) {
            strcpy(dir->files[i].permissions, permissions);
            printf("File permissions changed successfully.\n");
            return;
        }
    }
    printf("File not found.\n");
}

void change_file_ownership(Directory* dir, char* filename, char owner) 
{
    for (int i = 0; i < dir->num_files; i++) {
    if (strcmp(filename, dir->files[i].name) == 0)
     {
        strcpy(dir->files[i].owner, owner);
        printf("File ownership changed successfully.\n");
        return;
 }
}
    printf("File not found.\n");
 }

    Directory* create_directory(char* dirname) {
    Directory* dir = malloc(sizeof(Directory));
    strcpy(dir->dirname, dirname);
    dir->num_files = 0;
    dir->files = NULL;
    dir->num_subdirs = 0;
    dir->subdirs = NULL;
    return dir;
}

void create_subdirectory(Directory* parent_dir, Directory* subdir) 
{
    for (int i = 0; i < parent_dir->num_subdirs; i++) 
    {
        if (strcmp(subdir->dirname, parent_dir->subdirs[i]->dirname) == 0) 
    {
        printf("Subdirectory already exists.\n");
        return;
    }
}
    parent_dir->num_subdirs++;
    parent_dir->subdirs = realloc(parent_dir->subdirs, parent_dir->num_subdirs * sizeof(Directory*));
    parent_dir->subdirs[parent_dir->num_subdirs - 1] = subdir;
    printf("Subdirectory created successfully.\n");
}
Directory* find_subdirectory(Directory* dir, char* dirname) 
{
    for (int i = 0; i < dir->num_subdirs; i++) 
    {
        if (strcmp(dirname, dir->subdirs[i]->dirname) == 0) 
        {
            return dir->subdirs[i];
}
}
return NULL;
}

void delete_subdirectory(Directory* parent_dir, char* dirname)
 {
    for (int i = 0; i < parent_dir->num_subdirs; i++) 
    {
        if (strcmp(dirname, parent_dir->subdirs[i]->dirname) == 0) 
    {
        free(parent_dir->subdirs[i]);
        for (int j = i; j < parent_dir->num_subdirs - 1; j++)
     {
        parent_dir->subdirs[j] = parent_dir->subdirs[j + 1];
}
    parent_dir->num_subdirs--;
    parent_dir->subdirs = realloc(parent_dir->subdirs, parent_dir->num_subdirs * sizeof(Directory*));
    printf("Subdirectory deleted successfully.\n");
    return;
}
}
    printf("Subdirectory not found.\n");
}

void print_directory_listing(Directory* dir) 
{
    printf("Directory: %s\n", dir->dirname);
    printf("Files:\n");
    for (int i = 0; i < dir->num_files; i++) 
    {
        printf("%s\t%s\t%s\t%s\n", dir->files[i].name, dir->files[i].contents, dir->files[i].permissions, dir->files[i].owner);
}
    printf("Subdirectories:\n");
    for (int i = 0; i < dir->num_subdirs; i++) 
{
    printf("%s\n", dir->subdirs[i]->dirname);
}
}

void add_file(Directory* dir, File* file);

int main() {
    Directory* root = create_directory("root");
    create_file(root, "file1.txt", "This is file 1.", "rw-r--r--", "user1");
    create_file(root, "file2.txt", "This is file 2.", "rw-r--r--", "user2");

    Directory* subdir = create_directory("subdir");
    create_file(subdir, "file3.txt", "This is file 3.", "rw-r--r--", "user1");
    create_file(subdir, "file4.txt", "This is file 4.", "rw-r--r--", "user2");
    create_subdirectory(root, subdir);
    printf("Initial directory listing:\n");
    print_directory_listing(root);

    printf("\nModifying files...\n");
    write_file(root, "file1.txt", "This is the modified content of file 1.");
    change_file_permissions(root, "file2.txt", "rwxr-xr-x");
    change_file_ownership(subdir, "file4.txt", "user3");

    printf("\nAfter modifications:\n");
    print_directory_listing(root);

    printf("\nDeleting files...\n");
    delete_file(root, "file1.txt");
    delete_file(subdir, "file3.txt");

    printf("\nAfter deletions:\n");
    print_directory_listing(root);

    printf("\nModifying subdirectories...\n");
    Directory* subdir2 = create_directory("subdir2");
    create_subdirectory(subdir, subdir2);
    delete_subdirectory(root, "subdir");

    printf("\nAfter modifications:\n");
    print_directory_listing(root);

    return 0;
}
void add_file(Directory* dir, File* file) { // function definition
    int i = dir->count;
    dir->files[i] = *file;
    dir->count++;
}
