#include "Symbol.h"

struct Symbol_proto {
    class* type;
    char repr[MAX_SYMBOL_STR_LEN];
};

class _Symbol_class = {
    .size = sizeof (struct Symbol_proto),
    .name = "Symbol",
    .interface_count = 1,
    .implements = {  },
    .constr = _Symbol_constr,
    .destr = _Symbol_destr
};
