#ifndef _ORDERING_H_
#define _ORDERING_H_

typedef enum { LT, EQ, GT } ordering;

typedef ordering (*ordering_compare)(const void *, const void *);

#endif // _ORDERING_H_
