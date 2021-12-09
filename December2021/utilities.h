#ifndef _UTILITIES_H_
#define _UTILITIES_H_

/* 
* Wrapper for calloc function that errors out
* when the calloc fails, will close program and
* print informative message
*/
void* Calloc(int total, int size);

/*
* Wrapper for realloc function that errors out
* when the realloc fails, will close program and
* print informative message
*/
void* Realloc(void* pointer, int total, int size);

#endif
