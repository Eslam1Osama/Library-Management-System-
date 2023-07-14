/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef UTILITY_CONTROL_H_INCLUDED
#define UTILITY_CONTROL_H_INCLUDED

/********************************************************************/

typedef enum    {WRONG_DES_FORMAT , ok_des}         des_state;
typedef enum    {WRONG_CHOICE_FORMAT , ok_choice}   choice_state;

/********************************************************************/
                            /*functions prototypes*/

void erase_prev_lines(void);

/********************************************************************/

void delete_exact_lines(u16 num_lines);

/********************************************************************/

des_state check_des(u8 *ptr_des);

/********************************************************************/

choice_state check_choice(u16 *ptr_choice);

/********************************************************************/

#endif // UTILITY_CONTROL_H_INCLUDED
