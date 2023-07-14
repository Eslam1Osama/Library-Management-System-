/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef MEMBER_H_INCLUDED
#define MEMBER_H_INCLUDED

/********************************************************************/

typedef enum{PANDED , NOT_PANDED}PRM;

typedef enum{
    EMPTY_MEMBER_LL,
    WRONG_MEMBER_NAME,
    WRONG_MEMBER_CODE,
    WRONG_MEMBER_PHONNUM,
    EXSISTED_MEMBER_CODE,//<-
    NOT_EXSISTED_MEMBER_CODE,//<-
    WRONG_GOVER_NUM,
    WRONG_DISTR_FORMAT,
	WRONG_STRE_FORMAT,
	WRONG_HOME_NUM_FORMAT,
	WRONG_GENDER,
	WRONG_AGE,
    ok_mem
}DMEMBER_COND;

typedef enum{
    ADD_NEW_MEMBER_FUNC,
    CREATE_BORROWING_NODE,
    MODIFY_MEMBER_FUNC,
    DELETE_MEMBER_FUNC,
    USE_IN_BORROWING_FUNC
}USAGE;

typedef enum{
	Alexandria = 1,
	Aswan,
	Asyut,
	Beheira,
	BeniSuef,
	Cairo,
	Dakahlia,
	Damietta,
	Faiyum,
	Gharbia,
	Giza,
	Ismailia,
	KafrEl_Sheikh,
	Luxor,
	Matruh,
	Minya,
	Monufia,
	NewValley,
	NorthSinai,
	PortSaid,
	Qalyubia,
	Qena,
	RedSea,
	Sharqia,
	Sohag,
	SouthSinai,
	Suez
}EGY_GOV;

/********************************************************************/

typedef struct{
	EGY_GOV gover;
	u8 distr[36];
	u8 street[36];
	u16 home_no;
}address;

typedef struct{
    u8 member_code[6];//not more than 5 digits
    u8 member_name[36];
    u8 gender;
    u16 age;
    address member_addre;
    u8 pho_num[13];
    u16 num_late;//number of late returning books at the current (not returned until current time)
    u16 num_bor;// number of borrowing processes at the current time (max 5)
    u16 exceed_exp;// (<-) when member exceed 4 times of late returning books borrowed, his or her membership is going to be deleted
    PRM member_perm;
}data_member;

typedef struct member_node{
    data_member bo;
    struct member_node *next;
    struct member_node *prev;
}member_node;

typedef struct{
    member_node *head;
    member_node *tail;
}member;

/********************************************************************/
                            /*functions prototypes*/

void create_mem_DLL(member *ptr_m);

/********************************************************************/

bool ll_member_is_empty(member *ptrmember);

/********************************************************************/

DMEMBER_COND member_name(member_node *ptr);

/********************************************************************/

DMEMBER_COND member_code(member *ptrmember , member_node *ptr , USAGE usage);//*edit

/********************************************************************/

DMEMBER_COND search_member_with_code(member *ptrmember, u8 member_code[6]);

/********************************************************************/

DMEMBER_COND mem_gender(member_node *ptr);

/********************************************************************/

DMEMBER_COND mem_age(member_node *ptr);

/********************************************************************/

DMEMBER_COND mem_addre_gover(member_node *ptr);

/********************************************************************/

DMEMBER_COND mem_addre_distr(member_node *ptr);

/********************************************************************/

DMEMBER_COND mem_addre_stre(member_node *ptr);

/********************************************************************/

DMEMBER_COND mem_addre_home_num(member_node *ptr);

/********************************************************************/

DMEMBER_COND member_phonnum(member_node *ptr);

/********************************************************************/

void print_list_gover(void);

/********************************************************************/

void show_gover_member(member_node *ptr);

/********************************************************************/

void add_new_member(member *ptrmember);

/********************************************************************/

void modify_member(member *ptrmember);

/********************************************************************/

void print_member_data(member_node *ptr_node);

/********************************************************************/

#endif // MEMBER_H_INCLUDED
