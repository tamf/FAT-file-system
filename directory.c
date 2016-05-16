/*
 * directory.c
 *
 * Functions used to deal with directory entries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "fatfs.h"

#include "directory.h"
#include "fat.h"

#define DIR_ENTRY_SIZE 32
#define MAX_NAME_SIZE 10000

void print_root_dir_files(const filesystem_info *fsinfoinput);
void print_subdir(dir_entry * dir, char * prefix);
void print_entries_in_cluster(uint64_t cluster, char * prefix);

const filesystem_info * fsinfo;

/*
* Prints information for entries in the root directory
*/
void print_root_dir_files(const filesystem_info *fsinfoinput) {
	fsinfo = fsinfoinput;
	// get byte offset for current entry in root directory
	void * root_dir_byte_offset = fsinfo->diskStart + (fsinfo->sector_size * fsinfo->rootdir_offset);
	void * entry_byte_offset = root_dir_byte_offset;
	unsigned char first_byte_of_entry = getBytesAsInt(entry_byte_offset, 1);
	
	printf("Type    Start Cluster        Size  Name  -> Cluster Chain\n");
	printf("=================================================================\n");
	
	dir_entry * current_entry;
	
	while (first_byte_of_entry != 0) {
		current_entry = initialize_dir_entry(entry_byte_offset);
		
		// only print entries that are not deleted based on first byte != 0xe5, and do not have cluster number 0
		if (0xe5 != first_byte_of_entry && 0 != current_entry->start_cluster) {
			char prefix[MAX_NAME_SIZE] = "";
			print_entry(fsinfo, current_entry, prefix);
		}
		
		// increment offset to next entry (32 bytes after)
		entry_byte_offset += DIR_ENTRY_SIZE;
		first_byte_of_entry = getBytesAsInt(entry_byte_offset, 1);
	}
}

/**
* Prints information for entries in a sub-directory 
*/	
void print_subdir(dir_entry * dir, char * prefix) {
	// get start cluster for sub-directory
	uint64_t curr_cluster = dir->start_cluster;
	
	strcat(prefix, dir->name);
	strcat(prefix, "/");
	
	// print out all entries in all clusters the sub-directory occupies
	while (!is_last_cluster(fsinfo, curr_cluster)) {
		print_entries_in_cluster(curr_cluster, prefix);
		curr_cluster = next_cluster(fsinfo, curr_cluster);
	}
	
}

/**
* Prints all entries in the cluster given the cluster number.
*/
void print_entries_in_cluster(uint64_t cluster, char * prefix) {
	// get cluster size in bytes
	uint64_t cluster_size = fsinfo->cluster_size * fsinfo->sector_size;
	
	// get offset of first entry 
	void * cluster_byte_offset = fsinfo->diskStart + (fsinfo->cluster_offset + (cluster - 2) * fsinfo->cluster_size) * fsinfo->sector_size;
	void * entry_byte_offset = cluster_byte_offset;
	void * end_of_cluster = cluster_byte_offset + cluster_size;
	unsigned char first_byte_of_entry = getBytesAsInt(entry_byte_offset, 1);
	
	dir_entry * current_entry;
	
	// print out entries until we reach zero for first byte, or reach end of cluster
	while (first_byte_of_entry != 0 && entry_byte_offset < end_of_cluster) {
		current_entry = initialize_dir_entry(entry_byte_offset);
		
		// do not print entries that are deleted or have cluster number 0
		if (0xe5 != first_byte_of_entry && 0 != current_entry->start_cluster) {
			// ignore sub-dir with name "." or ".."
			if ((	0 != strcmp(current_entry->name, ".") 
				&& 	0 != strcmp(current_entry->name, ".."))
				||	TYPE_FILE == current_entry->entry_type) {
					
				print_entry(fsinfo, current_entry, prefix);
			}
		}
		
		// increment offset to next entry (32 bytes after)
		entry_byte_offset += DIR_ENTRY_SIZE;
		first_byte_of_entry = getBytesAsInt(entry_byte_offset, 1);		
	}
}
	
	
