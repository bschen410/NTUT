#include <reg51.h>

sbit SPEAKER = P1^0;

#define NOTE_DO_L  0x89
#define NOTE_DO_H  0xF8

#define NOTE_RE_L  0x59
#define NOTE_RE_H  0xF9

#define NOTE_MI_L  0xE3
#define NOTE_MI_H  0xF9

#define NOTE_FA_L  0x38
#define NOTE_FA_H  0xFA

#define NOTE_SO_L  0xDC
#define NOTE_SO_H  0xFA

#define NOTE_LA_L  0x8F
#define NOTE_LA_H  0xFB

#define NOTE_TI_L  0x0C
#define NOTE_TI_H  0xFC

#define NOTE_HDO_L 0x44
#define NOTE_HDO_H 0xFC


void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1200; j++);
    }
}

void play_note(unsigned char TH_val, unsigned char TL_val, unsigned int duration_ms) {
    TMOD = 0x01;
    ET0 = 1;
    EA = 1;

    TH0 = TH_val;
    TL0 = TL_val;
    TR0 = 1;

    delay_ms(duration_ms);

    TR0 = 0;
    SPEAKER = 0;
}

void timer0_isr() interrupt 1 {
    TH0 = TH0;
    TL0 = TL0;
    SPEAKER = ~SPEAKER;
}

void main() {
    while (1) {
        play_note(NOTE_DO_H, NOTE_DO_L, 500);
        delay_ms(50);
        play_note(NOTE_RE_H, NOTE_RE_L, 500);
        delay_ms(50);
        play_note(NOTE_MI_H, NOTE_MI_L, 500);
        delay_ms(50);
        play_note(NOTE_FA_H, NOTE_FA_L, 500);
        delay_ms(50);
        play_note(NOTE_SO_H, NOTE_SO_L, 500);
        delay_ms(50);
        play_note(NOTE_LA_H, NOTE_LA_L, 500);
        delay_ms(50);
        play_note(NOTE_TI_H, NOTE_TI_L, 500);
        delay_ms(50);
        play_note(NOTE_HDO_H, NOTE_HDO_L, 500);
        delay_ms(500);
    }
}
