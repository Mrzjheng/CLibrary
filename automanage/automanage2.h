#ifndef AUTOMANAGE2_H
#define AUTOMANAGE2_H

void memory_cleanup_default(void* ptr);

#define auto_ptr_unique(type, name, ...) \
    [[gnu::cleanup(AUTOCHOOSE_CLEANUP(__VA_ARGS__))]] type* name

#define AUTOCHOOSE_CLEANUP(...) \
    AUTOCHOOSE_CLEANUP_IN(__VA_OPT__(__VA_ARGS__ ,) memory_cleanup_default, _)

#define AUTOCHOOSE_CLEANUP_IN(first, ...) first


#endif