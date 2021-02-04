//#############################################################################
//@@@	Declaratie variabile GLOBALE
//############################################################################# 
static int panelHandle;
//Declaratii pentru Task-ul Automat / Manual
int regim;
int stare_led;
int valoare_led; 
//Declaratii generare semnale Treapta, Rampa, Sinusoida
double Refk, Refk_1, Refk_2, Refk0;   
int sel_ref;  
double timp_rampa_tk, timp_sinus_tk;
double T_sin, A_sin;
int comutare_Sin;

//Declaratie perioada de esantionare 
double Te;
//Momentele de esantionare
double tk_1, tk;


//A,B,C,D
double a11,a12,a13,a21,a22,a23,a31,a32,a33;
double b1,b2,b3;
double c1,c2,c3;
double d;
//declaratii variabile k
double k1,k2,k3,x1k,x2k,x3k,x1k_1,x2k_1,x3k_1,uk_1,uk, yITk,  yITk_1,uk2,uk3;
//declaratii variabile element de executie
double uk,uk1,yEEk;
double yEEk_1,Cee1,uEEk,Cee2,uEEk,uEEk_1,yEEk1,yEEk1_1,uITk,uITk_1;
double Tee1,Tee2;;
		
			 
