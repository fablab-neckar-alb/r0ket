#Errata  
Things that go awry while trying to compile

    cmaier@DrEvil:~/CCC2011/r0ket/r0ket/firmware$ echo $PATH
    /home/cmaier/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

So far, so good ...  

    cmaier@DrEvil:~/CCC2011/r0ket/r0ket/firmware$ make

[...]  

    arm-none-eabi-ld -nostartfiles --gc-sections -Map=firmware.map -T lpc1xxx/memory.ld -o firmware.elf  main.o table.o lpc1xxx/LPC13xx_handlers.o lpc1xxx/LPC1xxx_startup.o  -Lapplications -lapp -Lfunk -lfunk -Lusbcdc -lusbcdc -Lfilesystem -lfat -Lbasic -lbasic -Llcd -llcd -Lcore -lcore -Lusb -lusb -lbasic -lfunk -Lflame -lflame
    applications/libapp.a(final.o): In function `main_final':
    /home/cmaier/CCC2011/r0ket/r0ket/firmware/applications/final.c:40: undefined reference to `init_final'
    funk/libfunk.a(nrf24l01p.o): In function `nrf_read_reg':
    /home/cmaier/CCC2011/r0ket/r0ket/firmware/funk/nrf24l01p.c:57: undefined reference to `rcv_spi'
    filesystem/libfat.a(util.o): In function `fsInit':
    /home/cmaier/CCC2011/r0ket/r0ket/firmware/filesystem/util.c:68: undefined reference to `format_formatDF'
    Makefile:114: recipe for target 'firmware.elf' failed
    make: *** [firmware.elf] Error 1

Same thing with CodeSourcery compiler

    cmaier@DrEvil:~/CCC2011/r0ket/r0ket/firmware$ source ~/scripts/sourceSourcery 
    cmaier@DrEvil:~/CCC2011/r0ket/r0ket/firmware$ echo $PATH
    /home/cmaier/CCC2011/r0ket/CodeSourcery/Sourcery_G++_Lite/bin:/home/cmaier/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

    arm-none-eabi-ld -nostartfiles --gc-sections -Map=firmware.map -T lpc1xxx/memory.ld -o firmware.elf  main.o table.o lpc1xxx/LPC13xx_handlers.o lpc1xxx/LPC1xxx_startup.o  -Lapplications -lapp -Lfunk -lfunk -Lusbcdc -lusbcdc -Lfilesystem -lfat -Lbasic -lbasic -Llcd -llcd -Lcore -lcore -Lusb -lusb -lbasic -lfunk -Lflame -lflame

    arm-none-eabi-size firmware.elf
     text	   data	    bss	    dec	    hex	filename
    31905	    332	   3027	  35264	   89c0	firmware.elf

    arm-none-eabi-objcopy --strip-unneeded -O binary firmware.elf firmware.bin

    ../tools/bootloader/lpcfix -c firmware.bin

