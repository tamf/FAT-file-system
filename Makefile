CC = gcc
CFLAGS = -g 

SRC = fatinfo.c direntry.c directory.c fatfs.c fat.c 
OBJ = $(SRC:.c=.o)

fatinfo: $(OBJ)

depend: $(SRC)
	makedepend $(SRC)

clean:
	/bin/rm -f $(OBJ) fatinfo *~

# DO NOT DELETE

fatinfo.o: /usr/include/stdio.h /usr/include/features.h
fatinfo.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
fatinfo.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
fatinfo.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
fatinfo.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
fatinfo.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
fatinfo.o: fatfs.h /usr/include/stdlib.h /usr/include/bits/waitflags.h
fatinfo.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
fatinfo.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
fatinfo.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
fatinfo.o: /usr/include/time.h /usr/include/sys/select.h
fatinfo.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
fatinfo.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
fatinfo.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
fatinfo.o: /usr/include/bits/stdlib-float.h fat.h directory.h direntry.h
fatinfo.o: /usr/include/stdint.h /usr/include/bits/wchar.h
direntry.o: /usr/include/stdio.h /usr/include/features.h
direntry.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
direntry.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
direntry.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
direntry.o: /usr/include/libio.h /usr/include/_G_config.h
direntry.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
direntry.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
direntry.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
direntry.o: /usr/include/endian.h /usr/include/bits/endian.h
direntry.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
direntry.o: /usr/include/sys/types.h /usr/include/time.h
direntry.o: /usr/include/sys/select.h /usr/include/bits/select.h
direntry.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
direntry.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
direntry.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
direntry.o: /usr/include/string.h /usr/include/xlocale.h fatfs.h fat.h
direntry.o: direntry.h /usr/include/stdint.h /usr/include/bits/wchar.h
direntry.o: /usr/include/inttypes.h
directory.o: /usr/include/stdio.h /usr/include/features.h
directory.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
directory.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
directory.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
directory.o: /usr/include/libio.h /usr/include/_G_config.h
directory.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
directory.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
directory.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
directory.o: /usr/include/endian.h /usr/include/bits/endian.h
directory.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
directory.o: /usr/include/sys/types.h /usr/include/time.h
directory.o: /usr/include/sys/select.h /usr/include/bits/select.h
directory.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
directory.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
directory.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
directory.o: /usr/include/string.h /usr/include/xlocale.h
directory.o: /usr/include/stdint.h /usr/include/bits/wchar.h fatfs.h fat.h
directory.o: directory.h direntry.h
fatfs.o: /usr/include/fcntl.h /usr/include/features.h
fatfs.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
fatfs.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
fatfs.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
fatfs.o: /usr/include/bits/fcntl.h /usr/include/bits/fcntl-linux.h
fatfs.o: /usr/include/time.h /usr/include/bits/stat.h /usr/include/stdio.h
fatfs.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
fatfs.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
fatfs.o: /usr/include/sys/stat.h /usr/include/sys/types.h
fatfs.o: /usr/include/endian.h /usr/include/bits/endian.h
fatfs.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
fatfs.o: /usr/include/sys/select.h /usr/include/bits/select.h
fatfs.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
fatfs.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
fatfs.o: /usr/include/sys/mman.h /usr/include/bits/mman.h
fatfs.o: /usr/include/bits/mman-linux.h /usr/include/assert.h
fatfs.o: /usr/include/stdint.h /usr/include/bits/wchar.h
fatfs.o: /usr/include/inttypes.h fatfs.h /usr/include/stdlib.h
fatfs.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
fatfs.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h fat.h
fat.o: /usr/include/stdio.h /usr/include/features.h
fat.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
fat.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
fat.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
fat.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
fat.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h fat.h
fat.o: fatfs.h /usr/include/stdlib.h /usr/include/bits/waitflags.h
fat.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
fat.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
fat.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
fat.o: /usr/include/time.h /usr/include/sys/select.h
fat.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
fat.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
fat.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
fat.o: /usr/include/bits/stdlib-float.h
