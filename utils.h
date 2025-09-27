#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

static inline void msleep(unsigned int ms) {usleep(ms * 1000U); }

#endif /* UTILS_H*/
