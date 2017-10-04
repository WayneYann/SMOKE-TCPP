/*-----------------------------------------------------------------------*\
|                  _       _____ __  __  ____  _  ________                |
|                 | |     / ____|  \/  |/ __ \| |/ /  ____|               |
|          ___  __| | ___| (___ | \  / | |  | | ' /| |__                  |
|         / _ \/ _` |/ __|\___ \| |\/| | |  | |  < |  __|                 |
|        |  __/ (_| | (__ ____) | |  | | |__| | . \| |____                |
|         \___|\__,_|\___|_____/|_|  |_|\____/|_|\_\______|               |
|                                                                         |
|                                                                         |
|   Authors: A. Cuoci, M.R. Malik, Z. Li, A. Parente                      |
|                                                                         |
|   Contacts: Alberto Cuoci                                               |
|   email: alberto.cuoci@polimi.it                                        |
|   Department of Chemistry, Materials and Chemical Engineering           |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano (Italy)                      |
|                                                                         |
|   Contacts: Mohammad Rafi Malik, Zhiyi Li, Alessandro Parente           |
|   Aero-Thermo-Mechanical Department                                     |
|   Université Libre de Bruxelles                                         |
|   Avenue F. D. Roosevelt 50, 1050 Bruxelles (Belgium)                   |
|                                                                         |
|-------------------------------------------------------------------------|
|                                                                         |
|   This file is part of edcSMOKE solver.                                 |
|                                                                         |
|	License                                                           |
|                                                                         |
|   Copyright(C) 2017-2014 A. Cuoci, A. Parente                           |
|   edcSMOKE is free software: you can redistribute it and/or modify      |
|   it under the terms of the GNU General Public License as published by  |
|   the Free Software Foundation, either version 3 of the License, or     |
|   (at your option) any later version.                                   |
|                                                                         |
|   edcSMOKE is distributed in the hope that it will be useful,           |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of        |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
|   GNU General Public License for more details.                          |
|                                                                         |
|   You should have received a copy of the GNU General Public License     |
|   along with edcSMOKE. If not, see <http://www.gnu.org/licenses/>.      |
|                                                                         |
\*-----------------------------------------------------------------------*/
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	int filterWidth = 8;
	const int n = 768*896*512/(pow(filterWidth,3));//mesh size for LES with filterwidth 12 compared to H case DNS
	//const int n = 576*672*384/(pow(8,3));//mesh size for LES with filterwidth 8 compared to H case DNS
	const int n0 =0;
	const int n1 =0;
	const int n2 =n;//100e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72)*pow(filterWidth,3);//cell volume size 
	//scalar volume_cell = ((1.37*0.001)/48)*((1.37*0.001)/48)*((1.37*0.001)/48)*pow(8,3);//cell volume size
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;
	List<List<scalar> > R_DNS(11, List<scalar>(n2) );
	Info<<"R_DNS_DNS made"<<endl;
	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	List<List<scalar> > YStar_DNS(11, List<scalar>(n2) ); 
	Info<<"YStar_DNS made"<<endl;
		scalarField TStar_DNS(n2,0.0);
	Info<<"TStar_DNS made"<<endl;
	
	{
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_T_0055.dat",n);
		Info<<T_DNS[n2-1]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_rho_0055.dat",n);
		Info<<rho_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_P_0055.dat",n);
		Info<<p_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_CO2_0055.dat",n);
		Info<<Y_CO2_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_CO_0055.dat",n);
		Info<<Y_CO_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_H_0055.dat",n);
		Info<<Y_H_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_H2_0055.dat",n);
		Info<<Y_H2_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_H2O_0055.dat",n);	
		Info<<Y_H2O_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_HCO_0055.dat",n);
		Info<<Y_HCO_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_HO2_0055.dat",n);
		Info<<Y_HO2_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_O_0055.dat",n);
		Info<<Y_O_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_O2_0055.dat",n);
		Info<<Y_O2_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/MED/jet_0055/jet_Filtered8_Y_OH_0055.dat",n);	
		Info<<Y_OH_DNS[n2-1]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];
		delete Y_OH_DNS;Y_OH_DNS=NULL;
	
		for(int celli=n0;celli<n2;celli++)
		{
			scalar sum=0.0;
			for(int i=0;i<10;i++)
			{
				sum+=Y_DNS[i][celli];
			}
			Y_DNS[10][celli]=1.0-sum;
		}


	}
	
	unsigned int counter = 0;
	const int unsigned ns = thermodynamicsMapXML->NumberOfSpecies();
		
	//OpenSMOKE::OpenSMOKEVectorDouble omegaMean(ns);
	OpenSMOKE::OpenSMOKEVectorDouble omegaStar_(ns);
	//OpenSMOKE::OpenSMOKEVectorDouble xMean(ns);
	//OpenSMOKE::OpenSMOKEVectorDouble cMean(ns);
	//OpenSMOKE::OpenSMOKEVectorDouble h_species(ns);
	OpenSMOKE::OpenSMOKEVectorDouble xStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble cStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble RStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble rStar_(ns);

    Eigen::VectorXd yStar0(ns+3);
	Eigen::VectorXd yStarf(ns+3);

	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);

		const double t0 = 0.;
		double tf = 2e-09*pow(filterWidth,3);//Ali 0.;

		for(unsigned int i=0;i<ns;i++)
				yStar0(i) = Y_DNS[i][celli];
		yStar0(ns) = T_DNS_OF[celli];
		yStar0(ns+1) = 0.;
		yStar0(ns+2) = 0.;

		#include "solvePFR_DI.H"

		for(unsigned int i=0;i<ns;i++)
				YStar_DNS[i][celli] = yStarf(i);
		TStar_DNS[celli] = yStarf(ns);
		for(unsigned int i=0;i<ns;i++)
			R_DNS[i][celli]  = rho_DNS_OF[celli]*(YStar_DNS[i][celli]-Y_DNS[i][celli])/tf;

			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
	}
	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_T_0055_PFR.dat",n2,T_DNS_Final);
	scalarField tmp_R_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_H2_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_O2_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_O_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_OH_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_H2O_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_H_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_HO2_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_CO_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_CO2_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_HCO_0055_PFR.dat",n2,tmp_R_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_DNS[celli]=R_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_RR_N2_0055_PFR.dat",n2,tmp_R_i_DNS);

	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_QdotCells_DNS_0055_PFR.dat",n2,QdotCells_DNS);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/MED/jet_0055/filterWidth8/jet_dQCells_DNS_0055_PFR.dat",n2,dQCells_DNS);

	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
