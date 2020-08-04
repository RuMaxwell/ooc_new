#include "sp.h"

#include "throw.h"

typedef void* (*dereferencer)(void*);

/************** owner **************/

struct owner {
    dereferencer deref;
    void* ptr;
    bool readonly;
    disposer ptr_disposer;
    int w_count;
    int r_count;
};

struct mut_ref {
    owner* owner;
};

struct immut_ref {
    owner* owner;
};

static void* owner_deref(void* sp) {
    owner* o = sp;
    // when it is borrowed as mutable, it is no longer usable
    if (o->w_count) {
        panicf("owner is not usable, it is borrowed as mutable");
    }

    return o->ptr;
}

owner* own(void* raw_ptr, bool readonly, disposer ptr_disposer) {
    owner* o = calloc(1, sizeof (struct owner));
    o->ptr = raw_ptr;
    o->readonly = readonly;
    o->deref = owner_deref;
    o->ptr_disposer = ptr_disposer;
    return o;
}

void delete_owner(owner* o) {
    if (o->ptr_disposer && o->ptr) {
        o->ptr_disposer(o->ptr);
    }
    free(o);
}

mut_ref* borrow_mut(owner* _owner) {
    if (_owner->readonly || _owner->w_count) {
        return NULL;
    }

    mut_ref* mr = calloc(1, sizeof (mut_ref));
    mr->owner = _owner;

    mr->owner->w_count++;

    return mr;
}

immut_ref* borrow_immut(owner* _owner) {
    if (_owner->w_count) {
        return NULL;
    }

    immut_ref* ir =  calloc(1, sizeof (immut_ref));
    ir->owner = _owner;

    ir->owner->r_count++;

    return ir;
}


/************** shared_ptr **************/

struct shared_ptr {
    dereferencer deref;
    void* ptr;
    disposer ptr_disposer;
    int hard_count;
    int soft_count;
};

struct weak_ptr {
    shared_ptr* sp;
};

void* shared_ptr_deref(void* sp) {
    shared_ptr* spsp = sp;
    return spsp->ptr;
}

shared_ptr* new_shared(void* ptr, disposer ptr_disposer) {
    shared_ptr* sp = calloc(1, sizeof (shared_ptr));
    sp->deref = shared_ptr_deref;
    sp->ptr = ptr;
    sp->ptr_disposer = ptr_disposer;
    sp->hard_count = 1;
    return sp;
}

shared_ptr* shared_ref(shared_ptr* sp) {
    sp->hard_count++;
    return sp;
}

weak_ptr* weak_ref(shared_ptr* sp) {
    sp->soft_count++;
    weak_ptr* wp = calloc(1, sizeof (weak_ptr));
    wp->sp = sp;
    return wp;
}

void remove_shared(shared_ptr* sp) {
    sp->hard_count--;
    if (sp->hard_count <= 0) {
        if (sp->ptr && sp->ptr_disposer) {
            sp->ptr_disposer(sp->ptr);
        }
        free(sp);
    }
}

void remove_weak(weak_ptr* wp) {
    wp->sp->soft_count--;
    if (wp->sp->soft_count < 0) wp->sp->soft_count = 0;
    free(wp);
}

/************** auto_ptr **************/

#define AUTO_PTR_TABLE_SIZE 4096

// hash table <void* -> auto_ptr*>
static auto_ptr* PTR_TABLE[AUTO_PTR_TABLE_SIZE] = {0};

struct auto_ptr {
    void* ptr;
    disposer ptr_disposer;
    auto_ptr* next;
    int ref_count;
};

void* auto_ptr_deref(void* ap) {
    auto_ptr* apap = ap;
    return apap->ptr;
}

int auto_ptr_hash(void* ptr) {
    return (int)ptr % AUTO_PTR_TABLE_SIZE;
}

static auto_ptr* lookup(void* ptr) {
    auto_ptr* ap = PTR_TABLE[auto_ptr_hash(ptr)];
    for (; ap; ap = ap->next) {
        if (ap->ptr == ptr) {
            return ap;
        }
    }
    return NULL;
}

void* automize(void* ptr, disposer ptr_disposer) {
    auto_ptr* ap = lookup(ptr);
    if (ap) {
        ap->ref_count++;
        return ap->ptr;
    }

    ap = calloc(1, sizeof (auto_ptr));
    ap->ptr = ptr;
    ap->ptr_disposer = ptr_disposer;
    int hash = auto_ptr_hash(ptr);
    ap->next = PTR_TABLE[hash];
    PTR_TABLE[hash] = ap;
    return ptr;
}

void deactivate(void* ptr) {
    int hash = auto_ptr_hash(ptr);
    auto_ptr* ap = PTR_TABLE[hash];
    if (ap->ptr == ptr) {
        PTR_TABLE[hash] = ap->next;
        ap->ref_count--;
        if (ap->ref_count <= 0 && ap->ptr && ap->ptr_disposer) {
            ap->ptr_disposer(ap->ptr);
        }
        free(ap);
    }

    ap = ap->next;
    auto_ptr* fol = ap;
    for (; ap; fol = ap, ap = ap->next) {
        if (ap->ptr == ptr) {
            fol->next = ap->next;
            ap->ref_count--;
            if (ap->ref_count <= 0 && ap->ptr && ap->ptr_disposer) {
                ap->ptr_disposer(ap->ptr);
            }
            free(ap);
        }
    }

    // pointer not found
}


void* deref(void* sp) {
    dereferencer* dp = sp;
    return (*dp)(sp);
}
