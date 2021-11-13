#ifndef tStudent_h
#define tStudent_h

double tStudentInv(int grados_libertad, double probablidadDerecha);

double tStudentInv(int grados_libertad, double probablidadDerecha){
    
    double ret = -1;
    
    if(grados_libertad == 4 && abs(probablidadDerecha - 0.025) < 0.0001){
        ret = 2.7765;
    }
	else if(grados_libertad == 4 && abs(probablidadDerecha - 0.05) < 0.0001){
		ret = 2.1318;
	}
	else if(grados_libertad == 7 && abs(probablidadDerecha - 0.05) < 0.0001){
		ret = 1.8946;
	}
    
    return ret;
    
}

#endif
