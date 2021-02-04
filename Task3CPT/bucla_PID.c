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

		//Parametrii f.d.t. Proces>>>relatia iterativa obtinuta prin discretizare
		Tee1=4;
			Tee2=3.7;
			 Cee1=Te/(Te+Tee1);
			Cee2=Tee1/(Te+Tee2);
			a11=-4.1667;
			a12=-2.9444;
			a13=-0.5556;
			a21=1;
			a22=0;
			a23=0;
			a31=0;
			a32=1;
			a33=0;
			b1=1;
			b2=0;
			b3=0;
			c1=0;
			c2=0;
			c3=0.5556;
			d=0;
			//lqr
			k1=0.003599298381878;
			k2=0.000717839779863;
			k3=0.000000000257143;
;
			//k1=-0.2919;
			//k2=-0.0286;
			//k3=-0.015;
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
		uk=comanda();
		  uEEk=uk;
		  yEEk=element_executie();
		  uITk=yEEk;
		  yITk=FDT();


//Task 0.4  Plotare evolutie raspunsuri
		// Afisare Referinta	
			PlotLine (panelHandle, PANEL_GRAPH, tk_1, Refk_1, tk, Refk, VAL_GREEN); 
		//Afisare raspuns proces
			PlotLine (panelHandle, PANEL_GRAPH, tk_1, yITk_1, tk, yITk, VAL_RED);  


//Task 0.5 reactualizare pentru o noua intrerupere de la Timer (onoua perioada de esantionare)  
		tk_1=tk;
			tk=tk+Te;
		Refk_2=Refk_1;//operatie de reactualizare folosita si pentru detectarea trecerii prin "Ref0" a sinusului 
			Refk_1=Refk;
	        uk2=uk_1;	
			uEEk_1=uEEk;
			yEEk_1=yEEk;
			x1k_1=x1k;
			x2k_1=x2k;
			x3k_1=x3k;
				  yITk_1=yITk;
				  uk3=uk;
		uITk_1=uITk;
			break;
	}
	return 0;
}








