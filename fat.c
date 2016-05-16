/*
 * fat.c
 *
 */
#include <stdio.h>

#include "fat.h"
#include "fatfs.h"



/*
* Returns true if last cluster in chain, otherwise false 
*/
boolean is_last_cluster(const filesystem_info *fsinfo, unsigned int cluster) {
	// FAT32 end of cluster chain
	if (FAT32 == fsinfo->fs_type) {
		if (0xfff == cluster || 0xffff == cluster || 0xfffffff == cluster) {
			return TRUE;
		}
	// FAT12 end of cluster chain
	} else {
		if (0xff8 <= cluster) {
			return TRUE;
		}
	}
	return FALSE;
}

/*
* Look in FAT for next cluster number and return it
*/
unsigned int next_cluster(const filesystem_info *fsinfo, unsigned int curr_cluster) {
	// FAT32 next cluster
	if (FAT32 == fsinfo->fs_type) {
		unsigned int bytes_for_cluster = 4; 
		void * fat_byte_offset = fsinfo->diskStart + (fsinfo->sector_size * fsinfo->fat_offset);
		void * curr_cluster_offset = fat_byte_offset + curr_cluster * bytes_for_cluster;

		return getBytesAsInt(curr_cluster_offset, bytes_for_cluster);

	// FAT12 next cluster
	} else {
		unsigned int cluster_offset;
		if (0 == curr_cluster % 2) {
			cluster_offset = curr_cluster * 3 / 2;
		} else {
			cluster_offset = (curr_cluster - 1) * 3 / 2;
		}
		void * fat_byte_offset = fsinfo->diskStart + (fsinfo->sector_size * fsinfo->fat_offset);
		void * curr_cluster_offset = fat_byte_offset + cluster_offset;
		
		unsigned int x = getBytesAsInt(curr_cluster_offset, 3);
		return (0 == curr_cluster % 2) ? (x % 4096) : (x / 4096);
	}
}









