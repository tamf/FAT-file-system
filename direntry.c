/*
 * direntry.c
 *
 * Functions used to deal with directory entries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fatfs.h"
#include "direntry.h"
#include <inttypes.h>

/**
* Set the name of the directory entry, including file extension
*/
void set_dir_entry_name(dir_entry * entry) {
	int bytes_for_name = 8;
	int bytes_for_ext = 3;
	unsigned char name[bytes_for_name];
	unsigned char ext[bytes_for_ext];
	setByteArray(entry->entryStart, bytes_for_name, name);
	setByteArray(entry->entryStart + bytes_for_name, bytes_for_ext, ext);
	
	// add name to entry->name ignoring spaces
	int source_index;
	int dest_index = 0;
	for (source_index = 0; source_index < bytes_for_name; source_index++) {
		if (' ' != name[source_index]) {
			entry->name[dest_index] = name[source_index];
			dest_index++;
		}
	}
	// for files, add ext to entry->name ignoring spaces
	if (entry->entry_type == TYPE_FILE) {
		entry->name[dest_index++] = '.';
		for (source_index = 0; source_index < bytes_for_ext; source_index++) {
			if (' ' != ext[source_index]) {
				entry->name[dest_index] = ext[source_index];
				dest_index++;
			}
		}	
	}
	entry->name[dest_index++] = '\0';
	


	// handle case where first byte of entry is 0x05
	if (0x05 == entry->name[0]) {
		entry->name[0] = 0xe5;
	}
	
}

/*
* Initializes fields for the directory entry
*/
dir_entry * initialize_dir_entry(void *entry) {
	dir_entry *new_entry = (dir_entry *) malloc(sizeof(dir_entry));
	
	unsigned char * entry_start = (unsigned char *) entry;
	
	// read attributes
	new_entry->entryStart = entry;
	new_entry->start_cluster = getBytesAsInt(entry_start + 26, 2);
	new_entry->size = getBytesAsInt(entry_start + 28, 4);
	new_entry->entry_type = (0 == new_entry->size) ? TYPE_DIR : TYPE_FILE;
	set_dir_entry_name(new_entry);
	
	return new_entry;
}

/**
* Prints the cluster chain/range for the directory entry.
*/
void print_cluster_range(const filesystem_info *fsinfo, dir_entry * entry) {
	unsigned int curr_cluster = entry->start_cluster;
	unsigned int prev_cluster = curr_cluster - 1;
	unsigned int first_cluster_in_curr_range = curr_cluster;
	
	printf("%d", first_cluster_in_curr_range);
	while (is_last_cluster(fsinfo, curr_cluster) == FALSE) {
		// if non consecutive, start new range
		if (prev_cluster + 1 != curr_cluster) {
			// if range is not length 1, join with dash
			if (prev_cluster != first_cluster_in_curr_range) {
				printf("-");
				printf("%d", prev_cluster);
			}
			printf(",");
			printf("%d", curr_cluster);
			first_cluster_in_curr_range = curr_cluster;
		}
		// if consecutive, nothing printed
		prev_cluster = curr_cluster;
		curr_cluster = next_cluster(fsinfo, curr_cluster);
	}
	// reached end of cluster chain. Print last range.
	if (prev_cluster != first_cluster_in_curr_range) {
		printf("-");
		printf("%d", prev_cluster);
	}
	printf(",[END]");
}


/**
* Prints information about the directory entry
*/
void print_entry(const filesystem_info *fsinfo, dir_entry * entry, char * prefix) {
	// print entry type 
	if (TYPE_DIR == entry->entry_type) {
		printf("DIR ");
	} else {
		printf("FILE");
	}
	// print start cluster 
	printf("%17" PRId64, entry->start_cluster);
	
	// print size 
	printf("%12" PRId64 "  ", entry->size);
	
	// print name, including prefix, extension, and cluster range/chain
	printf(prefix);
	printf(entry->name);
	printf(" -> ");
	print_cluster_range(fsinfo, entry);
	printf("\n");
	
	// if entry is a directory, print entries inside it
	if (TYPE_DIR == entry->entry_type) {
		print_subdir(entry, prefix);
	}
}








