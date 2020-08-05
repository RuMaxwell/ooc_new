#include "obj/Symbol.h"
#include "owner.h"

#define SUCCESSFUL 0x7fffffff

int main(int argc, char** argv) {
    Obj() tom = NULL;
    Owner(Symbol) tom_owner = NULL;

    int state;
    if (state = setjmp(panic_buf)) {
        if (state != SUCCESSFUL) {
            fprintf(stderr, "panicked %d\n", state);
        }

        if (tom_owner) delete_owner(tom_owner);
        else if (tom) delete(tom);

        return state == SUCCESSFUL ? 0 : state;
    }

    tom = new(Symbol, "tom");
    tom_owner = own(tom, false, default_disposer);

    printf("%s\n", show(tom));

    longjmp(panic_buf, SUCCESSFUL);
}
