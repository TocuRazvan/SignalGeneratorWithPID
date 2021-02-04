//#############################################################################
//@@@	Implementare PID 
//############################################################################# 
double iesire_PID()
{
	double local_yPIDk;
//initializare parametrii PID
	
	//Implementare PID, unde: 
		//local_yPIDk este variabila locala calculata la momentul de esantionare tk
		//yPIDk_1, yPIDk_2 sunt variabile globale calculate la momentele anterioare tk_1, tk_2
		//epsk, epsk_1, epsk_2 sunt variabilele globale ale erorii, calculate la momentele anterioare tk, tk_1, tk_2
		//a1,a2,b0,b1,b2 sunt parametrii PID calculati in fct. start_aplicatie()
		local_yPIDk=-a1*yPIDk_1-a2*yPIDk_2+b0*epsk+b1*epsk_1+b2*epsk_2;

return local_yPIDk; 
}
 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//##Implementare EE
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
double element_executie()
{
	double local_yEEk1;
	local_yEEk1=yEEk_1+Cee1*(yPIDk-yEEk_1)+Cee2*(uEEk-uEEk_1); 
	
	return local_yEEk1;
}

 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//##Implementare instalatie tehnologica
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	double instalatie_tehnologica()
	{
		double local_yITk;
		
		yITk1=yITk1_1+C1*(uITk-yITk1_1);
		uITk1=yITk1;
		yITk2=yITk2_1+C2*(uITk1-yITk2_1);
		uITk2=yITk2;
		local_yITk=yITk3_1+C3*(uITk2-yITk3_1);
		
	
		
		return local_yITk;
	}

	
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//Implementare traductor
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	double traductor()
	{
		double local_yTRk;
	  local_yTRk=yTRk1_1+Ctr1*(uTRk1-yTRk1_1);
		return local_yTRk;
		
	}