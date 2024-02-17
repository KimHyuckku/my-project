# Linux BSP 공부용 코드 모음


## cmd_kcci_led.c


U-boot에서 LED제어기능 추가 함수


vi ~/pi_bsp/u-boot/arch/arm/cpu/armv7/start.S

ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

127	bl kcci_led_test
128	bl  _main

ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

396 ENTRY(kcci_led_test)
397     ldr r0,=0xFE200000      /*BCM2711 GPIO BASE*/

398     ldr r1,=0x09240000      /*gpio6~9 signal output*/

399     str r1,[r0,#0x00]       /*GPFSEL0*/

400     ldr r1,=0x00012249      /*gpio10~13 signal output,txd rxd,gpio16~19 inpu    t*/

401     str r1,[r0,#0x04]       /*GPFSEL1*/

402 @    ldr r1,=0x00000000      /*gpio20~23 signal input*/

403 @    str r1,[r0,#0x08]       /*GPFSEL2*/

404

405     ldr r1,=0x00000040      /*gpio6 set led0 on*/

406     mov r5, #0              /*shift mode :0 left*/

407     mov r2, #8              /*led count*/

408 ledloop:

409     str r1, [r0,#0x1C]      /*GPSET0 ledX on*/

410     ldr r3,=0x100000        /*delay count*/

411 delay:

412     ldr r4,[r0,#0x34]       /*GPLEV0*/

411     delay:

412     ldr r4,[r0,#0x34]       /*GPLEV0*/

413     ands r4,#0x00800000     /*key7 on*/

414     bne testend

415

416     subs r3,r3, #1

417     bne delay

418     str r1,[r0,#0x28]       /*GPCLR0 ledX off*/

419     teq r5, #0

420     moveq r1, r1, LSL #1

421     movne r1, r1, LSR #1

422

423     subs r2, r2, #1

424     bne ledloop

425     teq r5, #0

426     moveq r5, #1            /*shift mode :1 right*/

427     movne r5, #0            /*shift mode :0 left*/

428     mov r2, #8              /*led count*/

429     b ledloop

430

431 testend:

432     mov pc, lr

433 ENDPROC(kcci_led_test)

ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

추가


위치(우분투) -  pi_bsp/u-boot/common$




## syscall_app.c , test_mysyscall.c




