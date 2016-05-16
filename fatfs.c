/*
 * fatfs.c
 *
 * Basic operations on a FAT filesystem.
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include "fatfs.h"

/**
 * How to use this program.
 */
#define USAGE "Usage: %s file-system-file\n"

/*
 * Default size of one sector.
 */
#define DEFAULT_SECTOR_SIZE 512

/*
 * Size of one directory entry.
 */
#define DIR_ENTRY_SIZE 32

/*
 * Function to open the file system and map it into memory. 
 */
void * open_filesystem(int argc, char *argv[])
{
    char *filename;
    void *memory; 
    int fd;
    struct stat statBuff;

    if (argc == 2)
    {
	filename = argv[1];
    }
    else
    {
	fprintf(stderr, USAGE, argv[0]);
	exit(1);
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
      char buff[256];
      snprintf(buff, 256, "Could not open %s", filename);
      perror(buff);
      exit(1);
    }
    
    if (fstat(fd, &statBuff)) {
	perror("Stat failed");
	exit(1);
    }
    memory = mmap(0, statBuff.st_size, PROT_READ,  MAP_FILE | MAP_PRIVATE, fd, 0);
    if (memory == NULL) {
      perror("MMAP of file failed");
      exit(1);
    }
    return memory;
}

/**
* Converts little endian byte array into unsigned int
*/
unsigned int convertArrayToInt(unsigned char * byteArray, int size) {
	// unsigned int is only four bytes
	assert(size <= 4);
	
	int i;
	int answer = 0;
	for (i = 0; i < size; i++) {
		answer = answer | (byteArray[i] << (8 * i));
	}
	return answer;
}	

/**
* Reads correct number of bytes from memory into byteArray
*/
void setByteArray(unsigned char * start, int numBytesToRead, unsigned char * byteArray) {
	unsigned int i;
	for (i = 0; i < numBytesToRead; i++) {
		byteArray[i] = *(start + i);
	}
}

/**
* Reads given number of bytes from memory starting from param start and 
* returns unsigned int representation, assuming little endian.
*/
unsigned int getBytesAsInt(unsigned char * start, int numBytesToRead) {
	unsigned char * byteArray = malloc(sizeof(unsigned char) * numBytesToRead);
	unsigned int i;
	
	setByteArray(start, numBytesToRead, byteArray);
	
	unsigned int answer = convertArrayToInt(byteArray, numBytesToRead);
	free(byteArray);
	
	return answer;
}



/**
 * This function sets up information about a FAT filesystem that will be used to read from
 * that file system.
 */
filesystem_info *initialize_filesystem_info(void *diskStart)
{
    filesystem_info *fsinfo = (filesystem_info *) malloc(sizeof(filesystem_info));
    
	unsigned char * diskStartChPtr = (unsigned char *) diskStart;
	
	// read attributes from boot sector that are common to both FAT12 and FAT 32
	fsinfo->diskStart = diskStart;
	fsinfo->sector_size = getBytesAsInt(diskStartChPtr + 11, 2);
	fsinfo->cluster_size = getBytesAsInt(diskStartChPtr + 13, 1);
	fsinfo->rootdir_size = getBytesAsInt(diskStartChPtr + 17, 2);
	fsinfo->reserved_sectors = getBytesAsInt(diskStartChPtr + 14, 2);	
	fsinfo->fat_offset = fsinfo->reserved_sectors;
	fsinfo->num_fat_copies = getBytesAsInt(diskStartChPtr + 16, 1);
	
	
	// Determine whether file system is FAT32 or FAT12
	if (fsinfo->rootdir_size == 0) {
		fsinfo->fs_type = FAT32;
	} else {
		fsinfo->fs_type = FAT12;
	}
	
	
	// read attributes from boot sector from location that varies between FAT12 and FAT32
	if (fsinfo->fs_type == FAT12) {
		fsinfo->sectors_per_fat = getBytesAsInt(diskStartChPtr + 22, 2);
		fsinfo->hidden_sectors = getBytesAsInt(diskStartChPtr + 28, 2);
	} else {
		fsinfo->sectors_per_fat = getBytesAsInt(diskStartChPtr + 36, 4);
		fsinfo->hidden_sectors = getBytesAsInt(diskStartChPtr + 28, 4);
	}
	

	// set attributes that depend on the above attributes
	fsinfo->rootdir_offset = fsinfo->fat_offset + fsinfo->num_fat_copies * fsinfo->sectors_per_fat;
	fsinfo->sectors_for_root = fsinfo->rootdir_size * 32 / fsinfo->sector_size;
	fsinfo->cluster_offset = fsinfo->rootdir_offset + fsinfo->sectors_for_root;
	
	

    return fsinfo;
}





















