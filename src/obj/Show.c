#include "show.h"

char* show(void* this) {
    Show_object s = get_interface(this, Show_id);
    if (s) {
        return s->show(this);
    } else {
        panicf("object class doesn't implement `Show` interface");
    }
}
