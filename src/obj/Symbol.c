#include "Symbol.h"

struct Symbol_proto {
    class* type;
    char repr[MAX_SYMBOL_STR_LEN];
};

static void* _Symbol_constr(void* raw, va_list* app) {
    struct Symbol_proto* symbol = raw;

    char* repr = va_arg(*app, char*);
    va_end(*app);

    strcpy(symbol->repr, repr);
    return symbol;
}

static void* _Symbol_destr(void* this) {
    return this;
}

static char* _Symbol_Show_show(void* this) {
    struct Symbol_proto* self = this;
    return strdup(self->repr);
}

static Show _Symbol_Show = {
    .id = &Show_id,
    .show = _Symbol_Show_show
};

static INod _Symbol_implements = {
    .interface = &_Symbol_Show,
    .next = NULL
};

static class _Symbol_class = {
    .size = sizeof (struct Symbol_proto),
    .name = "Symbol",
    .implements = &_Symbol_implements,
    .constr = _Symbol_constr,
    .destr = _Symbol_destr
};

class* Symbol = &_Symbol_class;
