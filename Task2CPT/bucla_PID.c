#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "bucla_PID.h"


//#includere Biblioteci de functii
#include "00_Declaratii_Variabile_S.h" 
#include "01_Functionare_A_M_S.h" 
#include "02_Functii_Utilitare_S.h" 
#include "03_Generare_Semnale_S.h"
#include "04_elemente_FEEDBACK.h"

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR lpszCmdLine, int nCmdShow)
{
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "bucla_PID.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}
//#############################################################################
//@@@	Functia prin care se porneste aplicatia software:
//	=>se initializeaza toate variabilele necesare pentru a putea porni aplicatia
//############################################################################# 
int CVICALLBACK start_aplicatie (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
		//Task#### Initializare variabile
		//Afisare text ...Hello real-time World
				InsertTextBoxLine (panelHandle, PANEL_TEXTBOX, -1, "Hello real-time World ! SUCCES !!!!");
		//Setare perioada de esantionare 
				Te=0.01; // perioada de esantionare este de 100ms
				tk_1=0; tk=Te;
		//initializare folosita pentru a detecta trecerea prin "0" la sinus
					Refk=0; Refk_1=0;  Refk_2=0; 
					sel_ref=0;    
		//Comutare pe sinus fara socuri>>>>doar dupa trecerea fct. Sin prin 0
			comutare_Sin=0;
				GetCtrlVal (panelHandle, PANEL_A_SINUS, &A_sin);
				GetCtrlVal (panelHandle, PANEL_T_SINUS, &T_sin);
		//initializare parametrii PID
			GetCtrlVal(panelHandle,PANEL_NUMERIC_TI,&Ti);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_TD,&Td);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_KR,&Kr);
				GetCtrlVal(panelHandle,PANEL_NUMERIC_ALPHA,&alpha);
		//	Kr=37; Ti=171.29; Td=38.19; alpha=0.01;
			p0=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td) + (2/Te)*(Ti+alpha*Td) + 1);
				p1=Kr*(-(8/(Te*Te))*(alpha* Td*Ti+Td*Ti)+2);
					p2=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td) - (2/Te)*(Ti+alpha*Td) + 1); 
			
			q0=(4/(Te*Te))* Ti*alpha*Td + (2/Te)*Ti;
				q1=-(8/(Te*Te))* Ti*alpha*Td;
					q2=(4/(Te*Te))* Ti*alpha*Td - (2/Te)*Ti; 
			a1=q1/q0;  a2=q2/q0;
			b0=p0/q0;  b1=p1/q0; b2=p2/q0; 
		//Parametrii f.d.t. Proces>>>relatia iterativa obtinuta prin discretizare
			T1=37;
			T2=12;
			T3=3;
			//T1-3;
			//T2=2;
			//T3=0.3
			C1=Te/(Te+T1);
			C2=Te/(Te+T2);
			C3=Te/(Te+T3);
			//perturbatie
					Tp1=33;
			Tp2=10;
		    Tp3=2;
			Tp4=1;
			Cp1=Te/(Te+Tp1);
			Cp2=Te/(Te+Tp2);
			Cp3=Te/(Te+Tp3);
			Cp4=Te/(Te+Tp4);
		//element de executie
			Tee1=0.02*T2;
			Tee2=0.05*T2;
			    Cee1=Te/(Te+Tee1);
			Cee2=Te/(Te+Tee2);
			//traductor
			Ttr1=0.001*T2;
			Ttr2=0.0001*T2;
			
			Ctr1=Te/(Te+Ttr1);
			Ctr2=Te/(Te+Ttr1);
			//traductor perturbat
			Ttrp1=0.001*Tp2;
			Ctrp1=Te/(Te+Ttrp1);
//compensator
			Cc1=Te/(Te+Tp1);
			Cc2=Tp1/(Te+Tp2);
		    Cc3=Te/(Te+T2);
			Cc4=Tp2/(Te+Tp3);
			Cc5=Te/(Te+T3);
			Cc6=T3/(Te+Tp4);
			Cc7=Te/(Te+Tee2);
			Cc8=Tee2/(Te+T1);
			Cc9=Te/(Te+Ttrp1);
			Cc10=Ttrp1/(Te+Tee1);
			
			
		//Ascunde BUTONUL START daca a pornit aplicatia
			SetCtrlAttribute (panelHandle,PANEL_OKBUTTON, ATTR_DIMMED,1); 
		//Task#### Initializare/Pornire TIMER		
			SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_INTERVAL,Te);
					SetCtrlAttribute (panelHandle,PANEL_TIMER, ATTR_ENABLED,1); 

			break;
	}
	return 0;
}
//#############################################################################
//@@@	Functia principala a unei aplicatii de Timp-Real 
//	=>asociata intreruperilor de la ceasul de timp real; 
//	=>aici se fac toate prelucrarile necesare unei aplicatii de automatizare
//############################################################################# 
int CVICALLBACK esantionare (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
		//Functionare aplicatie Atomat / Manual
		 functiune_Automat_Manual();

//Prelucrare Bucla Reglare
		 
//Task 0.1 >>>>Preluare informatii
		//Generare semnal Referinta >>>Treapta, Rampa sau Sinus
			Refk=generare_semnal();
		//OBS: aici trebuie preluata iesire TR, iar in cazul nostru(simulare)
		//vom folosi iesirea anterioara yTRk_1=...???
  GetCtrlVal(panelHandle,PANEL_PERTURBATIE,&pert);
  
    uITkp=Refk-uITkp;
//Task 0.2 procesare informati /// calcul decizie  
		//Implementarea Element de Comparatie
			epsk=Refk-yTRk; //OBS: aici trebuie preluata iesire yTRk_1????
		//Implementare PID ==>yPIDk
			yPIDk=iesire_PID();
//traductor perturbat
	yTRkp=traductor_perturbat();
	 //compensator
	uComp1=yTRkp1;
			yComp5=compensator_perturbatie();
			
			//sumator
			//GetCtrlVal(panelHandle, PANEL_buton_comp, &buton_comp);
			if(buton_comp==0)
			{
			  yEEk=yPIDk;
			}
			else 
			{			
				uEEk=yPIDk-yComp5;
			}
			
			yEEk=element_executie();
	
			uITk3=yEEk;
			yITk3=instalatie_tehnologica();
			
		yComp5=instalatie_tehnologica_p();
			
			//sumator
		//	GetCtrlVal(panelHandle, PANEL_buton, &buton); 
		if(buton==0)
		{
		ySUMk=yITk3;
		}
		else
		{
		  ySUMk=yITk3+yITkp4;
		}	
			
			uTRk2=ySUMk;
	
			yTRk1=traductor();
			
//Task 0.3 Aplicare decizie la Elementul de Executie
		//OBS: aici trebuie implementat EE- elementul de executie 
			uEEk=yPIDk;
				yEEk=element_executie() ;
			
		//Prelucrare iesire Proces Tehnologic Discretizare cu aproximarea derivatei
		//pe o perioada de esantionare 
		uITk=yEEk;
		yITk3=instalatie_tehnologica();
		//OBS: aici trebuie implementat TR-traductorul  
	uTRk1=yITk3;
			yTRk=traductor();
	

//Task 0.4  Plotare evolutie raspunsuri
		// Afisare Referinta	
			PlotLine (panelHandle, PANEL_GRAPH, tk_1, Refk_1, tk, Refk, VAL_GREEN); 
		//Afisare raspuns proces
PlotLine (panelHandle, PANEL_GRAPH, tk_1, yITk3_1, tk, yITk3, VAL_RED);  
PlotLine (panelHandle, PANEL_GRAPH, tk_1, pert_1, tk, pert, VAL_BLUE);  
		//Afisare raspuns solutie de control PID
			PlotLine (panelHandle, PANEL_COMANDA, tk_1, yPIDk_1, tk, yPIDk, VAL_BLUE); 

//Task 0.5 reactualizare pentru o noua intrerupere de la Timer (onoua perioada de esantionare)  
		tk_1=tk;
			tk=tk+Te;
		   uEEk_1=uEEk;
				    yEEk_1=yEEk;
					uITk1_1=uITk1;
					uITk2_1=uITk2;
					yITk1_1=yITk1;
					yITk2_1=yITk2;
				    yITk3_1=yITk3;
					yTRk1_1=yTRk1;
					yTRk2_1=yTRk2;
					yTRk=yTRk_1;
					uTRkp1_1=uTRkp1;
					yTRkp1_1=yTRkp1;
					uITkp1_1=uITkp1;
					uITkp2_1=uITkp2;
					uITkp3_1=uITkp3;
					yITkp1_1=yITkp1;
					yITkp2_1=yITkp2;
					yITkp3_1=yITkp3;
					yITkp4_1=yITkp4;
					uComp1_1=uComp1;
					uComp2_1=uComp2;
					uComp3_1=uComp3;
					uComp4_1=uComp4;
					uComp5_1=uComp5;
					yComp1_1=yComp1;
					yComp2_1=yComp2;
					yComp3_1=yComp3;
					yComp4_1=yComp4;
					yComp5_1=yComp5;
					Refk_2=Refk_1;
					 Refk_1=Refk;
				epsk_2=epsk_1;
					epsk_1=epsk;
				yPIDk_2=yPIDk_1;
				yPIDk_1=yPIDk;
				pert_1=pert;
		ySUMk_1=ySUMk;
		yTRkp_1=yTRkp;
			break;
	}
	return 0;
}





