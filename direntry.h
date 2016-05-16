/*
 * direntry.h
 *
 * Functions used to deal with directory entries.
 */

#ifndef DIRENTRY_H
#define DIRENTRY_H

#include <stdint.h>

typedef enum {
  TYPE_DIR = 0,
  TYPE_FILE = 1,
} ENTRY_TYPE;



typedef struct {
	ENTRY_TYPE entry_type;
	void *entryStart;                      /* where the entry starts in memory */
	uint64_t start_cluster;                /* start cluster for the file */
	uint64_t size;                         /* file size in bytes */ 
	unsigned char name[13];                /* entry name */
	
} dir_entry;

/*
* Initialize information for the directory entry 
*/
dir_entry * initialize_dir_entry(void *entry);


#endif
