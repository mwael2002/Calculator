/*
 * main.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mwael
 */
#include"STD_Types.h"
#include"LCD_interface.h"
#include"Keypad_interface.h"

#define one_digit                 0
#define more_than_one_digit       1

#define Addition                  11
#define Subtraction               12
#define Multiplication            13
#define Division                  14
#define Final_Result              15
#define Restart                   16

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
U8 flag=10;
S32 no;
S32 equal=0;
F32 product=1;
F32 division;
U8 divi=0;
U8 pro=0;


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
		} while(no==255);

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
			if(flag==1){
				equal=equal-no;
				LCD_write_string_pos("+",0,x_pos_counter);
				x_pos_counter++;
				flag=0;
			}
			else if((flag==2)&&(pro!=1)){
			equal=equal+(product*no);
			product=1;
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			flag=0;
			}
			else if(pro==1){
				pro=0;
			equal=equal-(product*no);
			product=1;
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			flag=0;
		    }
			else if(flag==4){
		    equal=equal+(division/no);
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			flag=0;
							}
		  else if(divi==1){
			  divi=0;
		  equal=equal-(division/no);
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			flag=0;
			}
			else{
			LCD_write_string_pos("+",0,x_pos_counter);
			x_pos_counter++;
			equal+=no;
			flag=0;
			}
		}
		/*******************************************************/
}

void Subtract(void){
	/**********************Subtraction**********************/
   if(operation==Subtraction){
		if(flag==10){
		   LCD_write_string_pos("-",0,x_pos_counter);
		   x_pos_counter++;
		   equal=no;
		   flag=1;
		}
		else if(flag==0){
			equal+=no;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			flag=1;
		}
		else if((flag==2)&&(pro!=1)){
			equal=equal+(product*no);
			product=1;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			flag=1;
		}
		else if(pro==1){
			pro=0;
			equal=equal-(product*no);
			product=1;
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			flag=1;
					}
		else if(flag==4){
		equal=equal+(division/no);
		LCD_write_string_pos("-",0,x_pos_counter);
		x_pos_counter++;
		flag=1;
		}
		else if(divi==1){
			divi=0;
		equal=equal-(division/no);
		LCD_write_string_pos("-",0,x_pos_counter);
		x_pos_counter++;
		flag=1;
						}
		else{
			LCD_write_string_pos("-",0,x_pos_counter);
			x_pos_counter++;
			equal=equal-no;
			flag=1;
		}
	}
}

void Multiply(void){
	/*****************Multiplication*********************/
if(operation==Multiplication){
	 if(flag==1){
		 product=product*no;
		LCD_write_string_pos("x",0,x_pos_counter);
		x_pos_counter++;
		flag=2;
		pro=1;
					}
	 else if((flag==4)&&(divi!=1)){
	 product=division/no;
	 LCD_write_string_pos("x",0,x_pos_counter);
	 x_pos_counter++;
	 flag=2;
	 }
	 else if(divi==1){
		 divi=0;
	 product=-(division/no);
	 LCD_write_string_pos("x",0,x_pos_counter);
	 x_pos_counter++;
	 flag=2;
	 }
		else{
		product=product*no;
		LCD_write_string_pos("x",0,x_pos_counter);
		x_pos_counter++;
	    flag=2;
	}
	}
	/*************************************************/
}

void Divide(void){
	/******************Division***********************/
if(operation==Division){
    if(((flag==10) || (flag==0))&&(flag!=1)){
    	division=no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	flag=4;
    }
    else if(flag==1){
    	divi=1;
    	division=no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	flag=4;
    }
    else if((flag==2)&&(pro!=1)){
     division=product*no;
     product=1;
     LCD_write_string_pos("/",0,x_pos_counter);
     x_pos_counter++;
     flag=4;
     }
    else if(pro==1){
    	pro=0;
    	division=-(product*no);
    	product=1;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	 x_pos_counter++;
    	 flag=4;
    }
    else{
    	division=division/no;
    	LCD_write_string_pos("/",0,x_pos_counter);
    	x_pos_counter++;
    	flag=4;
    }
	}
	/********************************************/
}

void Equal(void){
	/******************Equal********************/
if(operation==Final_Result){
		if(flag==0){
			equal+=no;}
		else if(flag==1){
			equal=equal-no;}
		else if((flag==2)&&(pro!=1)){
			equal=equal+(product*no);
		}
		else if(pro==1){
		equal=equal-(product*no);
						}
		else if((flag==4)&&(divi!=1)){
			equal=equal+(division/no);
		}
		else if(divi==1){
						equal=equal-(division/no);
										}
		else if(flag==10){
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
		      x_pos_counter =0;
			 flag=10;
			 equal=0;
			 product=1;
			 divi=0;
			 pro=0;
	}
	/*************************************************/
}




