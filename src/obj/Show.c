#include "show.h"

char* show(Ptr(T) this) {
    class** p = this;
    class* c = (*p)->implements;

    for (size_t i = 0; i < c->interface_count; i++) {
        interface_id** iipp = c->implements[i];
    }
}
