#include "new.h"

void* new(class* type, ...) {
    va_list ap;
    va_start(ap, type);

    class** p = calloc(1, type->size);
    return (*p)->constr(p, &ap);
}

void delete(void* this) {
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

bool implements(void* this, void* _interface) {
    class** p = this;
    class* c = *p;
    for (size_t i = 0; i < c->interface_count; i++) {
        interface_id** ii = c->implements[i];
        if (c->implements[i] == _interface) {
            return true;
        }
    }
    return false;
}