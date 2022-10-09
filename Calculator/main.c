/*
 * main.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mwael
 */
#include"STD_Types.h"
#include"LCD_interface.h"
#include"Keypad_interface.h"

#define one_digit                               0
#define more_than_one_digit                     1

#define Addition                                11
#define Subtraction                             12
#define Multiplication                          13
#define Division                                14
#define Final_Result                            15
#define Restart                                 16

#define prev_NO_operation                       0
#define prev_Addition                           1
#define prev_Subtraction                        2
#define prev_Multiplication                     3
#define prev_Division                           4



#define not_negative                            0
#define negative                                1


S16 multiple_digits(S16 nu);
void take_no_from_user(void);
void Add(void);
void Subtract(void);
void Multiply(void);
void Divide(void);
void Equal(void);
void Reset(void);

U8 digit_no_flag=one_digit;
U8 operation;
U8 x_pos_counter=0;
U8 prev_operation=prev_NO_operation;
S32 no;
S32 equal=0;
F32 product=1;
F32 division;
U8 next_division_state=not_negative;
U8 next_multiplication_state=not_negative;


void main(void){
	KPD_init();
	LCD_init();

	while(1){
    take_no_from_user();
    Add();
    Subtract();
    Multiply();
    Divide();
    Equal();
    Reset();

		}
}
S16 multiple_digits(S16 nu){

	static S32 no_with_digit;

    if(digit_no_flag==one_digit){
    	no_with_digit=nu;
    	return nu;
    }
    else{
             nu=(no_with_digit*10+nu);
             no_with_digit=nu;
             return nu;
    	}
    }

void take_no_from_user(void){
	/***********Takes no from user****************/
	digit_no_flag=one_digit;
	S16 temp_no;
	while(1){
		if(x_pos_counter==16){
		   x_pos_counter--;
		}

		temp_no=no;

		do{
			no=KPD_status();
		} while(no==No_pressed_key);

		operation=no;

		if(no<10){
			LCD_write_no_pos(no,0,x_pos_counter);
			x_pos_counter++;
			no=multiple_digits(no);
			digit_no_flag=more_than_one_digit;
	}

		else if(operation>10){
			no=temp_no;
			break;
		}
	}
	/*************************************************/
}

void Add(void){
	/**************Addition**************************/
		if(operation==Addition){
			if(prev_operation==prev_Subtraction){
				equal=equal-no;
				LCD_write_string_pos("+",0,x_pos_counter);
				x_pos_counter++;
				prev_operation=prev_Addition;
			}
			else if((prev_operation==prev_Multiplication)&&(next_multiplication_state!=negative)){
			equal=equal+(product*no);
			product=1;
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Addition;
			}
			else if(next_multiplication_state==negative){
		    next_multiplication_state=not_negative;
			equal=equal-(product*no);
			product=1;
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Addition;
		    }
			else if((prev_operation==prev_Division)&&(next_division_state!=negative)){
		    equal=equal+(division/no);
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Addition;
			}
		  else if(next_division_state==negative){
			next_division_state=not_negative;
		    equal=equal-(division/no);
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Addition;
			}
			else{
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			equal+=no;
			prev_operation=prev_Addition;
			}
		}
		/*******************************************************/
}

void Subtract(void){
	/**********************Subtraction**********************/
   if(operation==Subtraction){
		if(prev_operation==prev_NO_operation){
		   LCD_write_string_pos("-",0,x_pos_counter);
		   x_pos_counter++;
		   equal=no;
		   prev_operation=prev_Subtraction;
		}
		else if(prev_operation==prev_Addition){
			equal+=no;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Subtraction;
		}
		else if((prev_operation==prev_Multiplication)&&(next_multiplication_state!=negative)){
			equal=equal+(product*no);
			product=1;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Subtraction;
		}
		else if(next_multiplication_state==negative){
			next_multiplication_state=not_negative;
			equal=equal-(product*no);
			product=1;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			prev_operation=prev_Subtraction;
		}
		else if((prev_operation==prev_Division)&&(next_division_state!=negative)){
		equal=equal+(division/no);
		LCD_write_string_pos("-",0,x_pos_counter);
		x_pos_counter++;
		prev_operation=prev_Subtraction;
		}
		else if(next_division_state==negative){
		next_division_state=not_negative;
		equal=equal-(division/no);
		LCD_write_string_pos("-",0,x_pos_counter);
		x_pos_counter++;
		prev_operation=prev_Subtraction;
						}
		else{
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			equal=equal-no;
			prev_operation=prev_Subtraction;
		}
	}
}

void Multiply(void){
	/*****************Multiplication*********************/
if(operation==Multiplication){
	 if(prev_operation==prev_Subtraction){
		 product=product*no;
		LCD_write_string_pos("x",0,x_pos_counter);
		x_pos_counter++;
		prev_operation=prev_Multiplication;
		next_multiplication_state=negative;
		}
	 else if((prev_operation==prev_Division)&&(next_division_state!=negative)){
	 product=division/no;
	 LCD_write_string_pos("x",0,x_pos_counter);
	 x_pos_counter++;
	 prev_operation=prev_Multiplication;
	 }
	 else if(next_division_state==negative){
	 next_division_state=not_negative;
	 product=-(division/no);
	 LCD_write_string_pos("x",0,x_pos_counter);
	 x_pos_counter++;
	 prev_operation=prev_Multiplication;
	 }
	 else{
	 product=product*no;
	 LCD_write_string_pos("x",0,x_pos_counter);
	 x_pos_counter++;
	 prev_operation=prev_Multiplication;
	}
	}
	/*************************************************/
}

void Divide(void){
	/******************Division***********************/
if(operation==Division){
    if(((prev_operation==prev_NO_operation) || (prev_operation==prev_Addition))&&(prev_operation!=prev_Subtraction)){
    	division=no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	prev_operation=prev_Division;
    }
    else if(prev_operation==prev_Subtraction){
    	next_division_state=negative;
    	division=no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	prev_operation=prev_Division;
    }
    else if((prev_operation==prev_Multiplication)&&(next_multiplication_state!=negative)){
     division=product*no;
     product=1;
     LCD_write_string_pos("/",0,x_pos_counter);
     x_pos_counter++;
     prev_operation=prev_Division;
     }
    else if(next_multiplication_state==negative){
    	next_multiplication_state=not_negative;
    	division=-(product*no);
    	product=1;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	 x_pos_counter++;
    	 prev_operation=prev_Division;
    }
    else{
    	division=division/no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	prev_operation=prev_Division;
    }
	}
	/********************************************/
}

void Equal(void){
	/******************Equal********************/
if(operation==Final_Result){
		if(prev_operation==prev_Addition){
			equal+=no;
		}
		else if(prev_operation==prev_Subtraction){
			equal=equal-no;
		}
		else if((prev_operation==prev_Multiplication)&&(next_multiplication_state!=negative)){
			equal=equal+(product*no);
		}
		else if(next_multiplication_state==negative){
		equal=equal-(product*no);
		}
		else if((prev_operation==prev_Division)&&(next_division_state!=negative)){
			equal=equal+(division/no);
		}
		else if(next_division_state==negative){
			equal=equal-(division/no);
		}
		else if(prev_operation==prev_NO_operation){
			equal=no;
		}

		LCD_write_string_pos("=",0,x_pos_counter);
	    x_pos_counter++;

	    if(x_pos_counter==16){
	    x_pos_counter--;
	    }

	    LCD_write_no_pos(equal,0,x_pos_counter);
	    x_pos_counter++;
	}
	/*************************************************/
}

void Reset(void){
	/****************Reset**************************/
if(operation==Restart){
		     LCD_init();
		     x_pos_counter=0;
		     prev_operation=prev_NO_operation;
			 equal=0;
			 product=1;
			 next_division_state=not_negative;
			 next_multiplication_state=not_negative;
	}

	/*************************************************/
}




