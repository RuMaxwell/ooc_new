#include "new.h"

void* new(class* type, ...) {
    va_list ap;
    va_start(ap, type);

    class** p = calloc(1, type->size);
    *p = type;
    return (*p)->constr(p, &ap);
}

void delete(void* this) {
    if (!this) {
        panicf("deleting null pointer");
    }
    class** p = this;
    p = (*p)->destr(this);
    if (p) {
        free(p);
    }
}

class* type_of(void* this) {
    class** p = this;
    return *p;
}

const char* typename(void* this) {
    class** p = this;
    return (*p)->name;
}

bool instanceof(void* this, class* type) {
    class** p = this;
    return *p == type;
}

void* get_interface(void* this, interface_id* i) {
    class** p = this;
    class* c = *p;

    for (INod* n = c->implements; n; n = n->next) {
        interface_id** iipp = n->interface;
        if (*iipp == i) {
            return iipp;
        }
    }

    return NULL;
}
