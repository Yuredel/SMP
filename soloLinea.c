#include "tarjeta.h"
#use delay (clock=48000000)
#include "srf02.h"
#include "lcd03.h"


#define mov_parar 0
#define mov_adelante 1
#define mov_atras 2
#define mov_girar_izq 3
#define mov_girar_drc 4

#define inicio 0
#define lapa 1
#define oponente 2
#define linea 3
#define sondeo 4


int tipo_mov = mov_parar;
int velocidad = 127;
int val = 0;
int duracion = 12;
int estado = inicio;

#INT_TIMER0
void tmr0_isr(){
		val++;

		if (val <= velocidad){
			switch(tipo_mov){
				case mov_parar:
					M1_P();
					M2_P();
					M3_P();
					M4_P();
					break;
				case mov_adelante:
					M1_H();
					M2_A();
					M3_H();
					M4_A();
					break;
				case mov_atras:
					M1_A();
					M2_H();
					M3_A();
					M4_H();
					break;
				case mov_girar_drc:
					M1_H();
					M2_H();
					M3_H();
					M4_H();
					break;
				case mov_girar_izq:
					M1_A();
					M2_A();
					M3_A();
					M4_A();
					break;
			}
		}
		else{
			M1_P();
			M2_P();
			M3_P();
			M4_P();
		}
		if(val==0){
			if(duracion !=255){
				duracion--;
				if(duracion==0){
					estado = sondeo;
				}
			}
		}
}





void main() {
int16 margen = 5;
int16 distancia_l;
int16 distancia_r;
int16 distancia_l1;
int16 distancia_l2;
int16 distancia_r1;
int16 distancia_r2;
char msg[21];

int linea_r=0;
int linea_l=0;

lcd_init();
led_off();

set_tris_a(0x00);
set_tris_b(0x13);
set_tris_c(0x00);
set_tris_d(0x1F);
set_tris_e(0x00);

setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_BIT);
enable_interrupts(INT_TIMER0);
enable_interrupts(GLOBAL);

while(1){


	switch(estado){
		case inicio:
			//Sondeo inicial
			break;

		case linea:
			if(IN4 && IN5){
				tipo_mov = mov_atras;
				velocidad = 127;
				duracion = 2;
			}
			else if(IN4 || IN5){
				if(IN4){//Si es en el lado izquierdo
					//girar derecha
					tipo_mov=mov_girar_izq;
					velocidad = 127;
					duracion = 2;
				}
				else{ //Si es el derecho
					//girar derecha
					tipo_mov=mov_girar_drc;
					velocidad = 127;
					duracion = 2;
				}
			}
			else
				tipo_mov = mov_adelante;
			break;


	}

// Mostrar por pantalla distancias

}

}
