#ifndef _COMMON_H_
/* ��� �ڵ忡�� ���������� ����Ǵ� ��ũ�� ���� �����ϴ� �������*/

#define NIL -1
#define G  6.67384*pow(10,-11)
#define MAX_DOUBLE 1.7976931348623158e+308


/* 
 * Error Macros 
 */
#define formatERR	\
	{cout << "Cannot recognize status! Please input one of \"true\", \"false\", \"0\", \"1\"" << endl; fERR = 1;}

#define is_num	i != 0 && is_number(w) /* If parameter should be a number */
#define is_not_num	i != 0 && !is_number(w)
#define is_not_num_print	\
	{cout << "Please input number as parameter\n"; continue; }
#define is_not_number	\
	else if (is_not_num){is_not_num_print;}

#define NOERR	!fERR && parameter
#define ParERR	!parameter /* Parameter Checking */
#define ParCheck	else if (ParERR)	NOP;	// It shoud be exist at the end of the command if the command is 'number parameter command'

#define NOP		cout << "No Parameter!\n";
#define ParExists	parameter = 1;

extern int time;
extern int numParticles;
extern int numSets;
extern int numForces;


#endif // !_COMMON_H_


