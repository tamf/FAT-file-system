# FAT-file-system

Reads a .dat file representing information about a FAT file system (FAT12 or FAT32) and outputs information about the file system, including sector size, cluster size, number of entries in root dir, number of sectors per FAT, etc. Also prints out the names, sizes, and corresponding clusters of all the files starting from the root directory, recursively.

# Usage:

./fatinfo $file-system-file-name
