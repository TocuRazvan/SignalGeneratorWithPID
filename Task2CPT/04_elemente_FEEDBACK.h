//#############################################################################
//@@@	Implementare PID 
//############################################################################# 
double iesire_PID()
{
	double local_yPIDk;
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
	//yk_comanda=yPIDk+yComp4+yComp5;
	local_yEEk1=yEEk_1+Cee1*(yEEk-yEEk_1)+Cee2*(uEEk-uEEk_1); 
	
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
	    yTRk1=yTRk1_1+Ctr1*(uTRk1-yTRk1_1);
		uTRk2=yTRk;
local_yTRk=yTRk2_1+Ctr2*(uTRk2-yTRk2_1);
		return local_yTRk;
		
	}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//implemnatre tradcutor perturbat
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	double traductor_perturbat()
	{
		double local_yTRkp;
	   local_yTRkp=yTRkp1_1+Ctrp1*(uTRkp1-yTRkp1_1);
		return local_yTRkp;
		
	}
 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//##Implementare instalatie tehnologica_perturbata
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	double instalatie_tehnologica_p()
	{
		double local_yITkp;
		
		yITkp1=yITkp1_1+Cp1*(uITkp-yITkp1_1);
		uITkp1=yITkp1;
		
		yITkp2=yITkp2_1+Cp2*(uITkp1-yITkp2_1);
		uITkp2=yITkp2;
		
	yITkp3=yITkp3_1+Cp3*(uITkp2-yITkp3_1);
	uITkp3=yITkp3;
	
	local_yITkp=yITkp4_1+Cp4*(uITkp3-yITkp4_1);

		return local_yITkp;
	}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//#implementare compensator
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
double compensator_perturbatie()
{
	double local_yComp;
	yComp1=yComp1_1+Cc1*(uComp1-yComp1_1)+Cc2*(uComp1-uComp1_1);
	uComp2=yComp1;
	yComp2=yComp1_1+Cc3*(uComp2-yComp2_1)+Cc4*(uComp2-uComp2_1);
	uComp3=yComp2;
	yComp3=yComp3_1+Cc5*(uComp3-yComp3_1)+Cc6*(uComp3-uComp3_1);
	uComp4=yComp3;
	yComp4=yComp4_1+Cc7*(uComp4-yComp4_1)+Cc8*(uComp4-uComp4_1);
	uComp5=yComp4;
	local_yComp=yComp5_1+Cc9*(uComp5-yComp5_1)+Cc10*(uComp5-uComp5_1);
	return local_yComp;
}









