#ifndef _SQLITE_CONFIG_H
#define _SQLITE_CONFIG_H

#define SQLITE_THREADSAFE 0
#define SQLITE_OMIT_WAL 1
#define SQLITE_OMIT_LOAD_EXTENSION 1
#define SQLITE_OMIT_POPEN 1

#define getrusage(A,B) memset(B,0,sizeof(*B))

#endif