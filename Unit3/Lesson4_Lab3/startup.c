/* startup.c: Eng Abdo Halem */

#include <stdint.h>
extern int main();
void Reset_Handler();

void Default_Handler(){
    Reset_Handler();
}

void NMI_Handler() __attribute__((weak, alias("Default_Handler")));
void H_Fault_Handler() __attribute__((weak, alias("Default_Handler")));

// Booking 1024 byte located by .bss through uninitialized array of 256 int (256*4 = 1024)
static unsigned int stack_top[256];

void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) = {
	(void (*)())((unsigned long)stack_top + sizeof(stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler
};

extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(){
    // Copy data section from flash to ram
    unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
    unsigned char* P_src = (unsigned char*)&_E_text;
    unsigned char* P_dst = (unsigned char*)&_S_DATA;
    unsigned int i = 0;
    for(i = 0; i < DATA_size; i++){
        *((unsigned char*)P_dst++) = *((unsigned char*)P_src++);
    }
    // Initialize .bss section in SRAM
    unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
    P_dst = (unsigned char*)&_S_bss;
    for(i = 0; i < bss_size; i++){
        *((unsigned char*)P_dst++) = (unsigned char)0;
    }
    // Jump to main()
    main();
}