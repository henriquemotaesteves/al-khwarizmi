#ifndef ORDERING_H_
#define ORDERING_H_

typedef enum { LT, EQ, GT } ordering;

typedef ordering (*ordering_compare)(const void *, const void *);

#endif // ORDERING_H_
