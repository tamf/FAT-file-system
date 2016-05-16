/*
 * Program to print information about a FAT file system.
 */
#include <stdio.h>

#include "fatfs.h"
#include "directory.h"

/**
 * Function to print information about a FAT filesystem (useful for debugging).
 */
void print_filesystem_info(const filesystem_info *fsinfo)
{
    printf ("Sector size:                          %zu\n", fsinfo->sector_size);
    printf ("Cluster size in sectors:              %u\n", fsinfo->cluster_size);
    printf ("Root directory size (nb of entries):  %u\n", fsinfo->rootdir_size);

    printf ("Sectors per fat:                      %u\n", fsinfo->sectors_per_fat);
    printf ("Reserved sectors:                     %u\n", fsinfo->reserved_sectors);
    printf ("Hidden sectors:                       %u\n", fsinfo->hidden_sectors);

    printf ("Fat offset in sectors:                %u\n", fsinfo->fat_offset);
    printf ("Root directory offset in sectors:     %u\n", fsinfo->rootdir_offset);
    printf ("First cluster offset in sectors:      %u\n", fsinfo->cluster_offset);
}

/**
 * Main function. Reads FAT file and prints out directory tree starting at the root directory.
 */
int main(int argc, char *argv[])
{
    void * mem = open_filesystem(argc, argv);
    int i;

    filesystem_info *fsinfo = initialize_filesystem_info(mem);
    print_filesystem_info(fsinfo);
    putchar('\n');

    // print the directory tree
	print_root_dir_files(fsinfo);
	
	free(fsinfo);
	
	return EXIT_SUCCESS;
}

