/*
 * Keybad_program.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mwael
 */
#include"STD_Types.h"
#include"DIO_interface.h"
#include"Keypad_config.h"
#include"Keypad_private.h"
#include"Keypad_interface.h"

U8 Column_index,Row_index,Pin_state;
U8 Pressed_key=No_pressed_key;
static U8 Rows_pins[Row_no]={Row_pin_0,Row_pin_1,Row_pin_2,Row_pin_3};
static U8 Column_pins[Column_no]={Column_pin_0,Column_pin_1,Column_pin_2,Column_pin_3};
static U8 Keypad_arr[Column_no][Row_no]=Keypad_values;


void KPD_init(void){
	for(U8 i =0;i<4;i++){
			DIO_set_pin_direction(Keypad_port,Rows_pins[i],INPUT);
			DIO_set_pin_direction(Keypad_port,Column_pins[i],OUTPUT);
		}
		DIO_set_port_value(Keypad_port,Port_HIGH);
}

U8 KPD_status(void){
for(Column_index =0 ; Column_index <Column_no; Column_index++){
	DIO_set_pin_value(Keypad_port,Column_pins[Column_index],LOW);
	for(Row_index=0 ; Row_index < Row_no ; Row_index++){
      DIO_get_pin_value(Keypad_port,Rows_pins[Row_index],&Pin_state);
      if(Pin_state==LOW){
    	  Pressed_key=Keypad_arr[Column_index][Row_index];
    	  while(Pin_state==LOW){
    		  DIO_get_pin_value(Keypad_port,Rows_pins[Row_index],&Pin_state);
    	  }
    	  return  Pressed_key;
      }
	}
	DIO_set_pin_value(Keypad_port,Column_pins[Column_index],HIGH);
}
return No_pressed_key;
}

