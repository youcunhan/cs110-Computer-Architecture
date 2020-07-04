#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"
#include <stdio.h>
#include <time.h>

int pscore = 0;
int cscore = 0;

void Inp_init(void)
{
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
    RCU_CFG0|=(0b10<<14)|(1<<28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0)|=ADC_CTL1_ADCON;
}

void IO_init(void)
{
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}

bool auto_move(void)
{
    int xmin = 10;
    int xmax = 149;
    int ymin = 5;
    int ymax = 74;

    int ballx = 80;
    int bally = 40;
    int ycpunow = 30;
    int yplayernow = 30;
    //srand((unsigned)time(NULL));
    int speed[4] = {-1,-2,1,2};
    int xmov = speed[rand()%4];
    int ymov = speed[rand()%4];
    int cpumov = 1;


    while(1){

        delay_1ms(20); 

        LCD_Fill(16,ycpunow,18,ycpunow + 20,BLACK);
        if (ycpunow + 10 <= bally) cpumov = 1;    
        else if (ycpunow + 10 >= bally) cpumov = -1;
        if(ycpunow+cpumov+20 <= ymax-1 && ycpunow+cpumov >= ymin+1) ycpunow += cpumov;
        LCD_Fill(16,ycpunow,18,ycpunow + 20,WHITE);
        if(Get_BOOT0()&&yplayernow<54){
            LCD_Fill(141,yplayernow,143,yplayernow + 20,BLACK); 
            yplayernow+=1;
        }
        if(Get_Button(0)&&yplayernow<54){
            LCD_Fill(141,yplayernow,143,yplayernow + 20,BLACK); 
            yplayernow+=1;
        }
        if(Get_Button(1)&&yplayernow>5){
            LCD_Fill(141,yplayernow,143,yplayernow + 20,BLACK); 
            yplayernow-=1;
        }
        LCD_Fill(141,yplayernow, 143, yplayernow+20, WHITE);


        LCD_DrawPoint_big(ballx,bally,BLACK);
        // char a[20];
        // sprintf(a,"xmov:%d ", xmov);
        // LCD_ShowString(0, 48, (u8 *)a, YELLOW); 
        // sprintf(a,"ymov:%d ", ymov);
        // LCD_ShowString(0, 64, (u8 *)a, YELLOW); 
        ballx = ballx + xmov;
        bally = bally + ymov;

        if (ballx <= 18 && ballx >= 16 && bally <= ycpunow + 20 && bally >= ycpunow) xmov = rand()%3+1;
        else if (ballx >= 141 && ballx <= 143 && bally <= yplayernow + 20 && bally >= yplayernow) xmov = rand()%3-3;

        if (bally < ymin+3) ymov = rand()%3+1;    
        else if (bally > ymax-3) ymov = rand()%3-3;


        if (ballx < xmin+1 )
        {

            pscore = pscore + 1;
            LCD_Fill(16,ycpunow,18,ycpunow + 20,BLACK);
            LCD_Fill(141,yplayernow,143,yplayernow + 20,BLACK); 
            break;
        }    
        else if (ballx > xmax-1) 
        {
            cscore = cscore + 1;
            LCD_Fill(16,ycpunow,18,ycpunow + 20,BLACK);
            LCD_Fill(141,yplayernow,143,yplayernow + 20,BLACK); 
            break;
        }
        LCD_DrawPoint_big(ballx,bally,WHITE);

        update(cscore, pscore);
    }
}

int main(void)
{
    wait_for_start();
    while (pscore != 10 && cscore != 10)
    {
        auto_move();
        LCD_ShowString(40, 24, (u8 *)("Press btn0"), GREEN);
        LCD_ShowString(35, 40, (u8 *)("to continue"), GREEN);
        LCD_ShowNum(68,10,cscore,1,GRAY);
        LCD_ShowNum(84,10,pscore,1,GRAY);
        if((pscore != 10 && cscore != 10)){
            while(!Get_Button(0)){
                delay_1ms(10);
            }
            LCD_ShowString(40, 24, (u8 *)("            "), GREEN);
            LCD_ShowString(35, 40, (u8 *)("            "), GREEN);
        }
        
    }
    finish_game(pscore,cscore);
    // else LCD_ShowString(0, 64, (u8 *)("Debug Message"), YELLOW);
    
    //LCD_ShowString(0, 64, (u8 *)("Debug Message"), GREEN);
}
