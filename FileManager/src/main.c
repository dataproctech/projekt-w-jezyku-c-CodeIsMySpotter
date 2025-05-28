#include <gtk/gtk.h>
#include "main_window.h"
#include "system_utils.h"
#include "runtime_utils.h"

void app(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWindow *window = create_window("FileManager", 1200, 800);
    if (!window) return;

    show_window(window);
    gtk_main();

}


void test_list(){
    
}

void test_result() {
    Result r = ok(malloc(4), "ALLOCATION WORKED");
    int *ptr = unwrap(r); 

    Result fail = err("SOMETHING NOT OKAY");
    int *x = unwrap_or(fail, def_int(10));
    printf("DEFAULT VALUE: %d\n", *x);
}

void test_dirs() {
    const char *dir_path = "test_dir";
    const char *file_path = "test_dir/file.txt";
    const char *file_renamed = "test_dir/renamed.txt";
    const char *dir_moved = "test_dir_moved";

    printf("== Running test_dirs() ==\n");

    // 1. Create directory
    Result r = create_dir(dir_path);
    if (r.error_code == ERR) {
        printf("create_dir: %s\n", r.message);
        return;
    }

    // 2. Create file inside directory
    r = create_file(file_path);
    if (r.error_code == ERR) {
        printf("create_file: %s\n", r.message);
        return;
    }

    // 3. Count entries (should be 1: the file)
    r = count_entries_in_dir(dir_path);
    if (r.error_code == ERR) {
        printf("count_entries_in_dir: %s\n", r.message);
    } else {
        int count = *(int *)r.value;
        printf("count_entries_in_dir: %d entry(ies)\n", count);
    }

    // 4. Rename file
    r = rename_file(file_path, file_renamed);
    if (r.error_code == ERR) {
        printf("rename_file: %s\n", r.message);
    }

    // 5. Move directory
    r = move_dir(dir_path, dir_moved);
    if (r.error_code == ERR) {
        printf("move_dir: %s\n", r.message);
    }

    // 6. Delete file inside moved directory
    char moved_file_path[256];
    snprintf(moved_file_path, sizeof(moved_file_path), "%s/renamed.txt", dir_moved);
    r = delete_file(moved_file_path);
    if (r.error_code == ERR) {
        printf("delete_file: %s\n", r.message);
    }

    // 7. Delete moved directory
    r = delete_dir(dir_moved);
    if (r.error_code == ERR) {
        printf("delete_dir: %s\n", r.message);
    }

    printf("== test_dirs() complete ==\n");
}

int main(int argc, char *argv[]) {
    app(argc, argv);   

    return 0;
}