
//#############################################################################
//@@@	Implementare element de executie
//############################################################################# 
double element_executie()
{
	double local_yEEk1;
	local_yEEk1=yEEk_1+Cee1*(uEEk-yEEk_1)+Cee2*(uEEk-uEEk_1); 
	
	return local_yEEk1;
}
//comanda
double comanda()
{
	double comd;
	       comd=Refk-k1*x1k_1-k2*x2k_1-k3*x3k_1;
		   return comd;
}
//fdt in spatiu starilor
double FDT()
{
	double raspuns;
	x1k=x1k_1+Te*a11*x1k_1+Te*a12*x2k_1+Te*a13*x3k_1+Te*b1*uITk;
	x2k=x2k_1+Te*a21*x1k_1+Te*a22*x2k_1+Te*a23*x3k_1+Te*b2*uITk;
    x3k=x3k_1+Te*a31*x1k_1+Te*a32*x2k_1+Te*a33*x3k_1+Te*b3*uITk;
	
	raspuns=c1*x1k+c2*x2k+c3*x3k+d*uk;
	
	return raspuns;
}
	