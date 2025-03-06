ENTRY(main)
SECTIONS
 {
   . = 0x90000000;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss : { *(.bss) }
 }
