#include "show.h"

interface_id Show_id = { 0 };

char* show(void* this) {
    Show_object s = get_interface(this, &Show_id);
    if (s) {
        return s->show(this);
    } else {
        panicf("object class doesn't implement `Show` interface");
    }
}
