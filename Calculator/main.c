/*
 * main.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mwael
 */
#include"STD_Types.h"
#include"LCD_interface.h"
#include"Keypad_interface.h"
S16 multiple_digits(S16 nu);
void take_no_from_user(void);
void Add(void);
void Subtract(void);
void Multiply(void);
void Divide(void);
void Equal(void);
void Reset(void);

U8 counter=0;
S32 dig;
U8 symbol;
U8 x_pos_counter =0;
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
    if(counter==0){
    	dig=nu;
    	return nu;
    }
    else{
             nu=(dig*10+nu);
             dig=nu;
             return nu;
    	}
    }

void take_no_from_user(void){
	/***********Takes no from user****************/
	counter=0;
	S16 y;
	while(1){
		if(x_pos_counter==16){
			x_pos_counter--;
		}
		y=no;
		do{
			no=KPD_status();
		} while(no==255);
		symbol=no;
		if(no<10){
			LCD_write_no_pos(no,0,x_pos_counter);
			x_pos_counter++;
			no=multiple_digits(no);
			counter=1;
	}
		else if(symbol>10){
			no=y;
			break;
		}
	}
	/*************************************************/
}
void Add(void){
	/**************Addition**************************/
		if(symbol==11){
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
   if(symbol==12){
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
if(symbol==13){
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
if(symbol==14){
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
if(symbol==15){
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
	/****************Restart**************************/
if(symbol==16){
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




