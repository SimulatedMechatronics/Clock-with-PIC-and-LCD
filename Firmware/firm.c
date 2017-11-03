#include <firm.h>

struct tempo {
   int segundo, minuto, hora;
} relogio;
long cont = 0;

#int_TIMER0
void  TIMER0_isr(void) {
   cont++;
   if(cont==1000) {
      relogio.segundo++;
      if(relogio.segundo==60) {
         relogio.segundo=0;
         relogio.minuto++;
         if(relogio.minuto==60) {
            relogio.minuto=0;
            relogio.hora++;
         }
      }
      cont=0;
   }
}

#define LCD_ENABLE_PIN PIN_B3
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_TYPE 2
#include <lcd.c>
void main() {
   lcd_init();
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(true) {
      printf(lcd_putc,"\fHora Certa:\n%02i:%02i:%02i", relogio.hora, relogio.minuto, relogio.segundo);
      delay_ms(200);
   }

}
