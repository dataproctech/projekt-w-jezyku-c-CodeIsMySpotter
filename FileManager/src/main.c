#include <gtk/gtk.h>
#include "main_window.h"
#include "system_utils.h"

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


int main(int argc, char *argv[]) {
    test_result();

    return 0;
}
