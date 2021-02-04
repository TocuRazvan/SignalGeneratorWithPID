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


//Declaratii semnale Proces OBS: in exemplu avem o F.D.T. de ordinul I
double y_Procesk_1, y_Procesk,y_raspuns,ref_pert;
double u_Procesk_1, u_Procesk; 
double C, T; //Declaratii pm. discretizare F.D.T  

//Declaratii variabile PID
double epsk_2, epsk_1,epsk;
double yPIDk_2, yPIDk_1, yPIDk;
double alpha, Kr, Ti, Td; 
double p0, p1, p2, q0, q1, q2;
double a1, a2, b0, b1, b2;

//declaratii variabile element de executie
double uk,uk1,yEEk;
double yEEk_1,Cee1,uEEk,Cee2,uEEk,uEEk_1,yEEk1,yEEk1_1;
double Tee1,Tee2;

//declaratii variabile instalatie tehnologica
double yITk;
double C1,C2,C3,yITk1,uITk1,yITk2,uITk2,yITk3,uITk1_1,uITk2_1 ;
double   yITk1_1,uITk,yITk2_1,uITk1,yITk3_1,uITk2,uITk3;
double T1,T2,T3;

//declaratii variabile traductor
double yTRk,yTRk_1;
double yTRk1,uTRk2,yTRk2,yTRk1_1,yTRk2_1,uTRk1,Ctr1,Ctr2,uTRk1_1;
double Ttr1,Ttr2;
  
		
			 
