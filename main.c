/*
 * Buzzer.c
 *
 * Created: 26.06.2023 13:57:01
 * Author : barto & Wisnu
 */ 

#define F_CPU 8000000UL //definiowanie zegara
#include <avr/io.h>
#include <util/delay.h>//opoznienia
#include <avr/interrupt.h>//przerwania
#include <avr/sfr_defs.h>//sprawdzanie bitow
#include "pitches.h"
#define BUZZER_PIN PD5

void delayCustom(unsigned int duration) {
	while (duration > 0) {
		_delay_ms(1);
		duration--;
	}
}

void buzzerPlay(unsigned int frequency, unsigned int duration) {
	// Ustawienie wartości rejestru OCR0B na podstawie częstotliwości dźwięku
	unsigned int prescaler = 8;  // Wybór preskalera
	unsigned int top = F_CPU / (2 * prescaler * frequency) - 1;  // Obliczenie wartości rejestru OCR0B
	
	OCR0B = top;
	
	// Włączenie trybu PWM na Timer/Counter0, ustawienie preskalera
	TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS01);
	
	// Generowanie dźwięku przez określony czas
	delayCustom(duration);
	
	// Wyłączenie generowania dźwięku
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
}

void playfurElise() {
	DDRD |= (1 << BUZZER_PIN);
  unsigned int melody[] = {
	  
  NOTE_E5, NOTE_DS5,
  NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4,
  NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4,
  NOTE_C5, 0,  NOTE_E4, NOTE_E5, NOTE_DS5,

  };

  unsigned int noteDuration[] = {
16,16,16,16,16,16,16,16,
8,16,16,16,
8,16,16,16,
8,16,16,16,16,


  };

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);

	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(8000/melody[i], 8000/noteDuration[i]);
		//unsigned int pause[i] = 1.3 * 4000/noteDuration[i];
		delayCustom(100);  // Odstęp między nutami (można dostosować)
	}

	// Wyłączenie PWM na Timer/Counter0
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	DDRD = 0x00;
}

void playImperialMarch() {
	// Marsz Gwiezdnych Wojen - Imperial March
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_C5, NOTE_E4,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5,
  NOTE_G4, NOTE_F4, NOTE_C5, NOTE_E4,
  };

	unsigned int noteDuration[] = {
4,4,4,8,
16,4,8,16,2,
4,4,4,8,
16,4,8,16,2,
	};
	
	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);
	
	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(8000/melody[i], 2000/noteDuration[i]);
		delayCustom(500);  // Odstęp między nutami
	}
	
	// Wyłączenie PWM na Timer/Counter0
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	DDRD = 0x00;
}

void playHappyBirthday() {
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
  NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_C4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_C4, NOTE_C4,

  NOTE_C5, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4,
	};

	unsigned int noteDuration[] = {
4,8,4,4,
4,2,4,8,
4,4,4,2,
4,8,4,4,
4,4,4,4,
8,4,4,4,2,
	};

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);

	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(8000/melody[i], 3000/noteDuration[i]);
		delayCustom(100);  // Odstęp między nutami
	}

	// Wyłączenie PWM na Timer/Counter0
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	DDRD = 0x00;
}

void playPinkPantherTheme() {
	DDRD |= (1 << BUZZER_PIN);
	unsigned int melody[] = {
  NOTE_DS4, NOTE_E4,
  NOTE_FS4, NOTE_G4, 
  NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5,
  NOTE_B4, NOTE_E4,
  NOTE_G4, NOTE_B4, NOTE_AS4,

  NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_E4, 
  
  NOTE_DS4, NOTE_E4,
  NOTE_FS4, NOTE_G4, NOTE_DS4,
  NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5,
  NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5, NOTE_DS5,
	};

	unsigned int noteDuration[] = {
8,2,8,2,
8,8,8,8,
8,8,8,8,8,1,
8,16,16,8,1,
8,2,8,2,
8,8,8,8,
8,8,8,8,8,1,
	};

	unsigned int numNotes = sizeof(melody) / sizeof(melody[0]);

	for (unsigned int i = 0; i < numNotes; i++) {
		buzzerPlay(4000/melody[i], 3000/noteDuration[i]);
		delayCustom(100);  // Odstęp między nutami (można dostosować)
	}

	// Wyłączenie PWM na Timer/Counter0
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	DDRD = 0x00;
}
int main(void) {
	DDRB = 0x00;//ustawienie jako wejscie
	PORTB = 0x0f;//rezystory podciagajace

	while (1) {
		//playImperialMarch();
		//CZASAMI ZMIENIAJA SIE WARTOSCI PINOW NIE WIEM CZEMU S1 = -101 0x8b, S2 = -105 0x87, S3= -99 0x8d, S4 = -98 0x8e
		if(((PINB == 0x87)||(PINB == 0x97)))//(bit_is_set(PINB, PB0))
		{
		playfurElise();
		}
		else if((PINB == 0x8b)||(PINB == 0x9b))//(bit_is_set(PINB, PB1))
		{
		playImperialMarch();
		}
		else if((PINB==0x8d)||(PINB == 0x9d))
		{
		playHappyBirthday();
		}
		else if((PINB==0x8e)||(PINB==0x9e))
		{
		playPinkPantherTheme();
		}
		//delayCustom(2000);Oczekiwanie 2 sekundy przed kolejnym odtworzeniem melodi
	}
}
