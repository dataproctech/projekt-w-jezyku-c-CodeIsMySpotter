#include "runtime_utils.h"
#include "system_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>


Result count_entries_in_dir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        return err("Failed to open directory");
    }

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            count++;
        }
    }

    closedir(dir);
    return ok(def_int(count), "Directory entries counted");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Result move_dir(const char *source, const char *destination) {
    if (rename(source, destination) != 0) {
        return err(strerror(errno));
    }
    return ok(NULL, "Directory moved successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Result delete_dir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        return err(strerror(errno));
    }

    struct dirent *entry;
    char full_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) == -1) {
            closedir(dir);
            return err(strerror(errno));
        }

        if (S_ISDIR(statbuf.st_mode)) {
            Result res = delete_dir(full_path);
            if (res.error_code == ERR) {
                closedir(dir);
                return res;
            }
        } else {
            if (remove(full_path) != 0) {
                closedir(dir);
                return err(strerror(errno));
            }
        }
    }

    closedir(dir);

    if (rmdir(path) != 0) {
        return err(strerror(errno));
    }

    return ok(NULL, "Directory and contents deleted successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Result delete_file(const char *path) {
    if (remove(path) != 0) {
        return err(strerror(errno));
    }
    return ok(NULL, "File deleted successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Result create_dir(const char *path) {
    if (mkdir(path) != 0) {
        return err(strerror(errno));
    }
    return ok(NULL, "Directory created successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Result create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return err(strerror(errno));
    }
    fclose(file);
    return ok(NULL, "File created successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Result rename_file(const char *old_path, const char *new_path) {
    if (rename(old_path, new_path) != 0) {
        return err(strerror(errno));
    }
    return ok(NULL, "File renamed successfully");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Result list_dir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        return err("Could not open directory");
    }

    Result res = list_init();
    if (res.error_code == ERR) {
        closedir(dir);
        return err("Could not initialize list");
    }

    List *file_list = (List *)res.value;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Pomijamy "." i ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char *name_copy = strdup(entry->d_name);
        if (!name_copy) {
            list_deinit(file_list, free);  // Zwalniamy listę i zawartość
            closedir(dir);
            return err("Failed to allocate memory for file name");
        }

        Result add_res = list_add(file_list, name_copy);
        if (add_res.error_code == ERR) {
            free(name_copy);
            list_deinit(file_list, free);
            closedir(dir);
            return err("Failed to add file name to list");
        }
    }

    closedir(dir);
    return ok(file_list, "Directory read successfully");
}
