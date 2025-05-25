#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "system_utils.h"




static inline Result count_entriex_in_dir(const char *path){
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return -1; // Error opening directory
    }

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') { 
            count++;
        }
    }

    closedir(dir);
    return count;
}

static inline Result move_dir(const char *source, const char *destination) {
    if (rename(source, destination) != 0) {
        perror("rename");
    }
}

static inline Result delete_dir(const char *path) {
    if (rmdir(path) != 0) {
        perror("rmdir");
    }
}

static inline Result delete_file(const char *path) {
    if (remove(path) != 0) {
        perror("remove");
    }
}

static inline Result create_dir(const char *path) {
    if (mkdir(path, 0755) != 0) {
        perror("mkdir");
    }
}

static inline Result create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    fclose(file);
}


static inline Result reneme_file(const char *old_path, const char *new_path) {
    if (rename(old_path, new_path) != 0) {
        perror("rename");
    }
}



char fetch_entries()