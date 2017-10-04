/*{
Info<<"part 1 "<<endl;
//part 
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	const int n = 864*1008*576;//mesh size (H case DNS HAWKES)
	const int n0 =0;
	const int n1 =0;
	const int n2 =100e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72);//cell volume size (H case DNS HAWKES)
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;


	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	
		List<List<scalar> > ReactionRates_DNS(kineticsMapXML->NumberOfReactions(), List<scalar>(n2) );
	Info<<"ReactionRates_DNS made"<<endl;
		
	
		
	
	{
			
	

		//float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_T_0099_le.dat",n);
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_T_0099_le.dat",n);
		Info<<T_DNS[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		//float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_rho_0099_le.dat",n);
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_rho_0099_le.dat",n);
		Info<<rho_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		//float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_P_0099_le.dat",n);
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_P_0099_le.dat",n);
		Info<<p_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		//float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO2_0099_le.dat",n);
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO2_0099_le.dat",n);
		Info<<Y_CO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		//float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO_0099_le.dat",n);
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO_0099_le.dat",n);
		Info<<Y_CO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		//float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H_0099_le.dat",n);
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H_0099_le.dat",n);
		Info<<Y_H_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];//forAll(Y_H_DNS_OF,i) Y_H_DNS_OF[i]=Y_H_DNS[i];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		//float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2_0099_le.dat",n);
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2_0099_le.dat",n);
		Info<<Y_H2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];//forAll(Y_H2_DNS_OF,i) Y_H2_DNS_OF[i]=Y_H2_DNS[i];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		//float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2O_0099_le.dat",n);
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2O_0099_le.dat",n);	
		Info<<Y_H2O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];//forAll(Y_H2O_DNS_OF,i) Y_H2O_DNS_OF[i]=Y_H2O_DNS[i];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		//float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HCO_0099_le.dat",n);
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HCO_0099_le.dat",n);
		Info<<Y_HCO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];//forAll(Y_HCO_DNS_OF,i) Y_HCO_DNS_OF[i]=Y_HCODNS[i];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		//float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HO2_0099_le.dat",n);
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HO2_0099_le.dat",n);
		Info<<Y_HO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];//forAll(Y_HO2_DNS_OF,i) Y_HO2_DNS_OF[i]=Y_HO2_DNS[i];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		//float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O_0099_le.dat",n);
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O_0099_le.dat",n);
		Info<<Y_O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];//forAll(Y_O_DNS_OF,i) Y_O_DNS_OF[i]=Y_O_DNS[i];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		//float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O2_0099_le.dat",n);
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O2_0099_le.dat",n);
		Info<<Y_O2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];//forAll(Y_O2_DNS_OF,i) Y_O2_DNS_OF[i]=Y_O2_DNS[i];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		//float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_OH_0099_le.dat",n);
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_OH_0099_le.dat",n);	
		Info<<Y_OH_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];//forAll(Y_OH_DNS_OF,i) Y_OH_DNS_OF[i]=Y_OH_DNS[i];
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

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		//const double t0 = 0.;
		//double tf = 2e-09;//Ali 0.;	
		for(unsigned int i=0;i<ns;i++)
				omegaStar_[i+1] = Y_DNS[i][celli];
				
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xStar_.GetHandle(), MWMean, omegaStar_.GetHandle());

		const double TStar_ = T_DNS_OF[celli];
		double P_Pa_=p_DNS_OF[celli];
		double MWStar_=MWMean;
		double cTotStar_ = P_Pa_/(PhysicalConstants::R_J_kmol * TStar_);
		double rhoStar_ = cTotStar_*MWStar_;
		Product(cTotStar_, xStar_, &cStar_);
		thermodynamicsMapXML->SetTemperature(TStar_);
		thermodynamicsMapXML->SetPressure(P_Pa_);
		double cpStar_ = thermodynamicsMapXML->cpMolar_Mixture_From_MoleFractions(xStar_.GetHandle());
		cpStar_/=MWStar_;
		
		kineticsMapXML->SetTemperature(TStar_);
		kineticsMapXML->SetPressure(P_Pa_);
		kineticsMapXML->ReactionEnthalpiesAndEntropies();
		kineticsMapXML->KineticConstants();
		kineticsMapXML->ReactionRates(cStar_.GetHandle());
		kineticsMapXML->FormationRates(RStar_.GetHandle());
		const double QRStar_ = kineticsMapXML->HeatRelease(RStar_.GetHandle());

		
		//Addedd by Ali 1 Aug 2017 to get RR

		OpenSMOKE::OpenSMOKEVectorDouble rrNet;	
		ChangeDimensions(kineticsMapXML->NumberOfReactions(), &rrNet, true);
		kineticsMapXML->GiveMeReactionRates(rrNet.GetHandle());
		for(unsigned int k=0;k<kineticsMapXML->NumberOfReactions();k++)
		{
			ReactionRates_DNS[k][celli] = rrNet[k+1];
		}
		// end modification
			
			QdotCells_DNS[celli] = QRStar_;
			dQCells_DNS[celli] = QRStar_ * volume_cell;	
			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
			
	}
	counter = 0;
	//#include "Da.H"

	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_T_0099_le_out1.dat",n2,T_DNS_Final);

	
	
	//Added by ali on 1 Aug 2017 to get RR
scalarField tmp_ReactionRates_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_1_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_2_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_3_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_4_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_5_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_6_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_7_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_8_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_9_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_10_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_11_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[11][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_12_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[12][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_13_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[13][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_14_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[14][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_15_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[15][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_16_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[16][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_17_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[17][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_18_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[18][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_19_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[19][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_20_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[20][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_21_0099_AREN_out1.dat",n2,tmp_ReactionRates_i_DNS);


	
	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
}

{
Info<<"part 2 "<<endl;
//part 2
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	const int n = 864*1008*576;//mesh size (H case DNS HAWKES)
	const int n0 =0;
	const int n1 =100e6;
	const int n2 =100e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72);//cell volume size (H case DNS HAWKES)
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;


	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	
		List<List<scalar> > ReactionRates_DNS(kineticsMapXML->NumberOfReactions(), List<scalar>(n2) );
	Info<<"ReactionRates_DNS made"<<endl;
		
	
		
	
	{
			
	

		//float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_T_0099_le.dat",n);
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_T_0099_le.dat",n);
		Info<<T_DNS[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		//float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_rho_0099_le.dat",n);
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_rho_0099_le.dat",n);
		Info<<rho_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		//float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_P_0099_le.dat",n);
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_P_0099_le.dat",n);
		Info<<p_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		//float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO2_0099_le.dat",n);
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO2_0099_le.dat",n);
		Info<<Y_CO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		//float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO_0099_le.dat",n);
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO_0099_le.dat",n);
		Info<<Y_CO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		//float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H_0099_le.dat",n);
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H_0099_le.dat",n);
		Info<<Y_H_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];//forAll(Y_H_DNS_OF,i) Y_H_DNS_OF[i]=Y_H_DNS[i];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		//float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2_0099_le.dat",n);
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2_0099_le.dat",n);
		Info<<Y_H2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];//forAll(Y_H2_DNS_OF,i) Y_H2_DNS_OF[i]=Y_H2_DNS[i];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		//float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2O_0099_le.dat",n);
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2O_0099_le.dat",n);	
		Info<<Y_H2O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];//forAll(Y_H2O_DNS_OF,i) Y_H2O_DNS_OF[i]=Y_H2O_DNS[i];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		//float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HCO_0099_le.dat",n);
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HCO_0099_le.dat",n);
		Info<<Y_HCO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];//forAll(Y_HCO_DNS_OF,i) Y_HCO_DNS_OF[i]=Y_HCODNS[i];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		//float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HO2_0099_le.dat",n);
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HO2_0099_le.dat",n);
		Info<<Y_HO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];//forAll(Y_HO2_DNS_OF,i) Y_HO2_DNS_OF[i]=Y_HO2_DNS[i];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		//float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O_0099_le.dat",n);
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O_0099_le.dat",n);
		Info<<Y_O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];//forAll(Y_O_DNS_OF,i) Y_O_DNS_OF[i]=Y_O_DNS[i];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		//float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O2_0099_le.dat",n);
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O2_0099_le.dat",n);
		Info<<Y_O2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];//forAll(Y_O2_DNS_OF,i) Y_O2_DNS_OF[i]=Y_O2_DNS[i];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		//float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_OH_0099_le.dat",n);
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_OH_0099_le.dat",n);	
		Info<<Y_OH_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];//forAll(Y_OH_DNS_OF,i) Y_OH_DNS_OF[i]=Y_OH_DNS[i];
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

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		//const double t0 = 0.;
		//double tf = 2e-09;//Ali 0.;	
		for(unsigned int i=0;i<ns;i++)
				omegaStar_[i+1] = Y_DNS[i][celli];
				
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xStar_.GetHandle(), MWMean, omegaStar_.GetHandle());

		const double TStar_ = T_DNS_OF[celli];
		double P_Pa_=p_DNS_OF[celli];
		double MWStar_=MWMean;
		double cTotStar_ = P_Pa_/(PhysicalConstants::R_J_kmol * TStar_);
		double rhoStar_ = cTotStar_*MWStar_;
		Product(cTotStar_, xStar_, &cStar_);
		thermodynamicsMapXML->SetTemperature(TStar_);
		thermodynamicsMapXML->SetPressure(P_Pa_);
		double cpStar_ = thermodynamicsMapXML->cpMolar_Mixture_From_MoleFractions(xStar_.GetHandle());
		cpStar_/=MWStar_;
		
		kineticsMapXML->SetTemperature(TStar_);
		kineticsMapXML->SetPressure(P_Pa_);
		kineticsMapXML->ReactionEnthalpiesAndEntropies();
		kineticsMapXML->KineticConstants();
		kineticsMapXML->ReactionRates(cStar_.GetHandle());
		kineticsMapXML->FormationRates(RStar_.GetHandle());
		const double QRStar_ = kineticsMapXML->HeatRelease(RStar_.GetHandle());

		
		//Addedd by Ali 1 Aug 2017 to get RR

		OpenSMOKE::OpenSMOKEVectorDouble rrNet;	
		ChangeDimensions(kineticsMapXML->NumberOfReactions(), &rrNet, true);
		kineticsMapXML->GiveMeReactionRates(rrNet.GetHandle());
		for(unsigned int k=0;k<kineticsMapXML->NumberOfReactions();k++)
		{
			ReactionRates_DNS[k][celli] = rrNet[k+1];
		}
		// end modification
			
			QdotCells_DNS[celli] = QRStar_;
			dQCells_DNS[celli] = QRStar_ * volume_cell;	
			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
			
	}
	counter = 0;
	//#include "Da.H"

	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_T_0099_le_out1.dat",n2,T_DNS_Final);

	
	
	//Added by ali on 1 Aug 2017 to get RR
scalarField tmp_ReactionRates_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_1_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_2_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_3_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_4_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_5_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_6_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_7_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_8_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_9_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_10_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_11_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[11][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_12_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[12][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_13_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[13][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_14_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[14][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_15_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[15][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_16_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[16][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_17_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[17][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_18_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[18][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_19_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[19][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_20_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[20][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_21_0099_AREN_out2.dat",n2,tmp_ReactionRates_i_DNS);


	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
}

{
Info<<"part 3 "<<endl;
//part 3
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	const int n = 864*1008*576;//mesh size (H case DNS HAWKES)
	const int n0 =0;
	const int n1 =200e6;
	const int n2 =100e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72);//cell volume size (H case DNS HAWKES)
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;


	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	
		List<List<scalar> > ReactionRates_DNS(kineticsMapXML->NumberOfReactions(), List<scalar>(n2) );
	Info<<"ReactionRates_DNS made"<<endl;
		
	
		
	
	{
			
	

		//float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_T_0099_le.dat",n);
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_T_0099_le.dat",n);
		Info<<T_DNS[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		//float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_rho_0099_le.dat",n);
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_rho_0099_le.dat",n);
		Info<<rho_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		//float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_P_0099_le.dat",n);
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_P_0099_le.dat",n);
		Info<<p_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		//float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO2_0099_le.dat",n);
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO2_0099_le.dat",n);
		Info<<Y_CO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		//float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO_0099_le.dat",n);
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO_0099_le.dat",n);
		Info<<Y_CO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		//float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H_0099_le.dat",n);
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H_0099_le.dat",n);
		Info<<Y_H_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];//forAll(Y_H_DNS_OF,i) Y_H_DNS_OF[i]=Y_H_DNS[i];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		//float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2_0099_le.dat",n);
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2_0099_le.dat",n);
		Info<<Y_H2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];//forAll(Y_H2_DNS_OF,i) Y_H2_DNS_OF[i]=Y_H2_DNS[i];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		//float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2O_0099_le.dat",n);
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2O_0099_le.dat",n);	
		Info<<Y_H2O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];//forAll(Y_H2O_DNS_OF,i) Y_H2O_DNS_OF[i]=Y_H2O_DNS[i];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		//float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HCO_0099_le.dat",n);
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HCO_0099_le.dat",n);
		Info<<Y_HCO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];//forAll(Y_HCO_DNS_OF,i) Y_HCO_DNS_OF[i]=Y_HCODNS[i];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		//float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HO2_0099_le.dat",n);
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HO2_0099_le.dat",n);
		Info<<Y_HO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];//forAll(Y_HO2_DNS_OF,i) Y_HO2_DNS_OF[i]=Y_HO2_DNS[i];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		//float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O_0099_le.dat",n);
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O_0099_le.dat",n);
		Info<<Y_O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];//forAll(Y_O_DNS_OF,i) Y_O_DNS_OF[i]=Y_O_DNS[i];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		//float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O2_0099_le.dat",n);
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O2_0099_le.dat",n);
		Info<<Y_O2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];//forAll(Y_O2_DNS_OF,i) Y_O2_DNS_OF[i]=Y_O2_DNS[i];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		//float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_OH_0099_le.dat",n);
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_OH_0099_le.dat",n);	
		Info<<Y_OH_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];//forAll(Y_OH_DNS_OF,i) Y_OH_DNS_OF[i]=Y_OH_DNS[i];
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

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		//const double t0 = 0.;
		//double tf = 2e-09;//Ali 0.;	
		for(unsigned int i=0;i<ns;i++)
				omegaStar_[i+1] = Y_DNS[i][celli];
				
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xStar_.GetHandle(), MWMean, omegaStar_.GetHandle());

		const double TStar_ = T_DNS_OF[celli];
		double P_Pa_=p_DNS_OF[celli];
		double MWStar_=MWMean;
		double cTotStar_ = P_Pa_/(PhysicalConstants::R_J_kmol * TStar_);
		double rhoStar_ = cTotStar_*MWStar_;
		Product(cTotStar_, xStar_, &cStar_);
		thermodynamicsMapXML->SetTemperature(TStar_);
		thermodynamicsMapXML->SetPressure(P_Pa_);
		double cpStar_ = thermodynamicsMapXML->cpMolar_Mixture_From_MoleFractions(xStar_.GetHandle());
		cpStar_/=MWStar_;
		
		kineticsMapXML->SetTemperature(TStar_);
		kineticsMapXML->SetPressure(P_Pa_);
		kineticsMapXML->ReactionEnthalpiesAndEntropies();
		kineticsMapXML->KineticConstants();
		kineticsMapXML->ReactionRates(cStar_.GetHandle());
		kineticsMapXML->FormationRates(RStar_.GetHandle());
		const double QRStar_ = kineticsMapXML->HeatRelease(RStar_.GetHandle());

		
		//Addedd by Ali 1 Aug 2017 to get RR

		OpenSMOKE::OpenSMOKEVectorDouble rrNet;	
		ChangeDimensions(kineticsMapXML->NumberOfReactions(), &rrNet, true);
		kineticsMapXML->GiveMeReactionRates(rrNet.GetHandle());
		for(unsigned int k=0;k<kineticsMapXML->NumberOfReactions();k++)
		{
			ReactionRates_DNS[k][celli] = rrNet[k+1];
		}
		// end modification
			
			QdotCells_DNS[celli] = QRStar_;
			dQCells_DNS[celli] = QRStar_ * volume_cell;	
			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
			
	}
	counter = 0;
	//#include "Da.H"

	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_T_0099_le_out1.dat",n2,T_DNS_Final);

	
	
	//Added by ali on 1 Aug 2017 to get RR
scalarField tmp_ReactionRates_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_1_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_2_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_3_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_4_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_5_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_6_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_7_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_8_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_9_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_10_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_11_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[11][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_12_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[12][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_13_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[13][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_14_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[14][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_15_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[15][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_16_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[16][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_17_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[17][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_18_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[18][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_19_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[19][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_20_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[20][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_21_0099_AREN_out3.dat",n2,tmp_ReactionRates_i_DNS);


	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
}

{
Info<<"part 4 "<<endl;
//part 4
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	const int n = 864*1008*576;//mesh size (H case DNS HAWKES)
	const int n0 =0;
	const int n1 =300e6;
	const int n2 =100e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72);//cell volume size (H case DNS HAWKES)
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;


	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	
		List<List<scalar> > ReactionRates_DNS(kineticsMapXML->NumberOfReactions(), List<scalar>(n2) );
	Info<<"ReactionRates_DNS made"<<endl;
		
	
		
	
	{
			
	

		//float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_T_0099_le.dat",n);
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_T_0099_le.dat",n);
		Info<<T_DNS[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		//float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_rho_0099_le.dat",n);
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_rho_0099_le.dat",n);
		Info<<rho_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		//float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_P_0099_le.dat",n);
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_P_0099_le.dat",n);
		Info<<p_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		//float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO2_0099_le.dat",n);
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO2_0099_le.dat",n);
		Info<<Y_CO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		//float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO_0099_le.dat",n);
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO_0099_le.dat",n);
		Info<<Y_CO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		//float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H_0099_le.dat",n);
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H_0099_le.dat",n);
		Info<<Y_H_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];//forAll(Y_H_DNS_OF,i) Y_H_DNS_OF[i]=Y_H_DNS[i];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		//float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2_0099_le.dat",n);
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2_0099_le.dat",n);
		Info<<Y_H2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];//forAll(Y_H2_DNS_OF,i) Y_H2_DNS_OF[i]=Y_H2_DNS[i];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		//float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2O_0099_le.dat",n);
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2O_0099_le.dat",n);	
		Info<<Y_H2O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];//forAll(Y_H2O_DNS_OF,i) Y_H2O_DNS_OF[i]=Y_H2O_DNS[i];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		//float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HCO_0099_le.dat",n);
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HCO_0099_le.dat",n);
		Info<<Y_HCO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];//forAll(Y_HCO_DNS_OF,i) Y_HCO_DNS_OF[i]=Y_HCODNS[i];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		//float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HO2_0099_le.dat",n);
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HO2_0099_le.dat",n);
		Info<<Y_HO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];//forAll(Y_HO2_DNS_OF,i) Y_HO2_DNS_OF[i]=Y_HO2_DNS[i];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		//float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O_0099_le.dat",n);
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O_0099_le.dat",n);
		Info<<Y_O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];//forAll(Y_O_DNS_OF,i) Y_O_DNS_OF[i]=Y_O_DNS[i];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		//float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O2_0099_le.dat",n);
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O2_0099_le.dat",n);
		Info<<Y_O2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];//forAll(Y_O2_DNS_OF,i) Y_O2_DNS_OF[i]=Y_O2_DNS[i];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		//float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_OH_0099_le.dat",n);
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_OH_0099_le.dat",n);	
		Info<<Y_OH_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];//forAll(Y_OH_DNS_OF,i) Y_OH_DNS_OF[i]=Y_OH_DNS[i];
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

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		//const double t0 = 0.;
		//double tf = 2e-09;//Ali 0.;	
		for(unsigned int i=0;i<ns;i++)
				omegaStar_[i+1] = Y_DNS[i][celli];
				
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xStar_.GetHandle(), MWMean, omegaStar_.GetHandle());

		const double TStar_ = T_DNS_OF[celli];
		double P_Pa_=p_DNS_OF[celli];
		double MWStar_=MWMean;
		double cTotStar_ = P_Pa_/(PhysicalConstants::R_J_kmol * TStar_);
		double rhoStar_ = cTotStar_*MWStar_;
		Product(cTotStar_, xStar_, &cStar_);
		thermodynamicsMapXML->SetTemperature(TStar_);
		thermodynamicsMapXML->SetPressure(P_Pa_);
		double cpStar_ = thermodynamicsMapXML->cpMolar_Mixture_From_MoleFractions(xStar_.GetHandle());
		cpStar_/=MWStar_;
		
		kineticsMapXML->SetTemperature(TStar_);
		kineticsMapXML->SetPressure(P_Pa_);
		kineticsMapXML->ReactionEnthalpiesAndEntropies();
		kineticsMapXML->KineticConstants();
		kineticsMapXML->ReactionRates(cStar_.GetHandle());
		kineticsMapXML->FormationRates(RStar_.GetHandle());
		const double QRStar_ = kineticsMapXML->HeatRelease(RStar_.GetHandle());

		
		//Addedd by Ali 1 Aug 2017 to get RR

		OpenSMOKE::OpenSMOKEVectorDouble rrNet;	
		ChangeDimensions(kineticsMapXML->NumberOfReactions(), &rrNet, true);
		kineticsMapXML->GiveMeReactionRates(rrNet.GetHandle());
		for(unsigned int k=0;k<kineticsMapXML->NumberOfReactions();k++)
		{
			ReactionRates_DNS[k][celli] = rrNet[k+1];
		}
		// end modification
			
			QdotCells_DNS[celli] = QRStar_;
			dQCells_DNS[celli] = QRStar_ * volume_cell;	
			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
			
	}
	counter = 0;
	//#include "Da.H"

	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_T_0099_le_out1.dat",n2,T_DNS_Final);

	
	
	//Added by ali on 1 Aug 2017 to get RR
scalarField tmp_ReactionRates_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_1_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_2_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_3_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_4_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_5_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_6_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_7_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_8_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_9_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_10_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_11_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[11][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_12_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[12][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_13_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[13][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_14_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[14][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_15_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[15][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_16_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[16][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_17_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[17][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_18_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[18][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_19_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[19][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_20_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[20][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_21_0099_AREN_out4.dat",n2,tmp_ReactionRates_i_DNS);


	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
}
*/
{
Info<<"part 5 "<<endl;
//part 5
//const int n = 148635648;//mesh size (L case DNS HAWKES)
	const int n = 864*1008*576;//mesh size (H case DNS HAWKES)
	const int n0 =0;
	const int n1 =400e6;
	const int n2 =n-400e6;
	//scalar volume_cell = 3.375e-15;//cell volume size (L case DNS HAWKES)
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72);//cell volume size (H case DNS HAWKES)
	scalarField T_DNS_OF(n2,0.0);
	Info<<"T_DNS made"<<endl;
	scalarField rho_DNS_OF(n2,0.0);
	Info<<"rho_DNS made"<<endl;
	scalarField p_DNS_OF(n2,0.0);
	Info<<"p_DNS made"<<endl;

	List<List<scalar> > Y_DNS(11, List<scalar>(n2) ); 
	Info<<"Y_DNS_DNS made"<<endl;


	//scalarField T_DNS_Final(n2,0.0);
	scalarField QdotCells_DNS(n2,0.0);
	scalarField dQCells_DNS(n2,0.0);
	
	
		List<List<scalar> > ReactionRates_DNS(kineticsMapXML->NumberOfReactions(), List<scalar>(n2) );
	Info<<"ReactionRates_DNS made"<<endl;
		
	
		
	
	{
			
	

		//float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_T_0099_le.dat",n);
		float* T_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_T_0099_le.dat",n);
		Info<<T_DNS[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_DNS_OF[celli]=T_DNS[celli+n1];
		delete T_DNS;T_DNS=NULL;
	
		//float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_rho_0099_le.dat",n);
		float* rho_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_rho_0099_le.dat",n);
		Info<<rho_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_DNS_OF[celli]=rho_DNS[celli+n1];
		delete rho_DNS;rho_DNS=NULL;
	
		//float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_P_0099_le.dat",n);
		float* p_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_P_0099_le.dat",n);
		Info<<p_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_DNS_OF[celli]=p_DNS[celli+n1];
		delete p_DNS;p_DNS=NULL;
	
		//float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO2_0099_le.dat",n);
		float* Y_CO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO2_0099_le.dat",n);
		Info<<Y_CO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[8][celli]=Y_CO2_DNS[celli+n1];
		delete Y_CO2_DNS;Y_CO2_DNS=NULL; 
		
		//float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_CO_0099_le.dat",n);
		float* Y_CO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_CO_0099_le.dat",n);
		Info<<Y_CO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[7][celli]=Y_CO_DNS[celli+n1];
		delete Y_CO_DNS;Y_CO_DNS=NULL;
		
		//float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H_0099_le.dat",n);
		float* Y_H_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H_0099_le.dat",n);
		Info<<Y_H_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[5][celli]=Y_H_DNS[celli+n1];//forAll(Y_H_DNS_OF,i) Y_H_DNS_OF[i]=Y_H_DNS[i];
		delete Y_H_DNS;Y_H_DNS=NULL;
	
		//float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2_0099_le.dat",n);
		float* Y_H2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2_0099_le.dat",n);
		Info<<Y_H2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[0][celli]=Y_H2_DNS[celli+n1];//forAll(Y_H2_DNS_OF,i) Y_H2_DNS_OF[i]=Y_H2_DNS[i];
		delete Y_H2_DNS;Y_H2_DNS=NULL;
	
		//float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_H2O_0099_le.dat",n);
		float* Y_H2O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_H2O_0099_le.dat",n);	
		Info<<Y_H2O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[4][celli]=Y_H2O_DNS[celli+n1];//forAll(Y_H2O_DNS_OF,i) Y_H2O_DNS_OF[i]=Y_H2O_DNS[i];
		delete Y_H2O_DNS;Y_H2O_DNS=NULL;
	
		//float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HCO_0099_le.dat",n);
		float* Y_HCO_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HCO_0099_le.dat",n);
		Info<<Y_HCO_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[9][celli]=Y_HCO_DNS[celli+n1];//forAll(Y_HCO_DNS_OF,i) Y_HCO_DNS_OF[i]=Y_HCODNS[i];
		delete Y_HCO_DNS;Y_HCO_DNS=NULL;
	
		//float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_HO2_0099_le.dat",n);
		float* Y_HO2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_HO2_0099_le.dat",n);
		Info<<Y_HO2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[6][celli]=Y_HO2_DNS[celli+n1];//forAll(Y_HO2_DNS_OF,i) Y_HO2_DNS_OF[i]=Y_HO2_DNS[i];
		delete Y_HO2_DNS;Y_HO2_DNS=NULL;
	
		//float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O_0099_le.dat",n);
		float* Y_O_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O_0099_le.dat",n);
		Info<<Y_O_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[2][celli]=Y_O_DNS[celli+n1];//forAll(Y_O_DNS_OF,i) Y_O_DNS_OF[i]=Y_O_DNS[i];
		delete Y_O_DNS;Y_O_DNS=NULL;
	
		//float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_O2_0099_le.dat",n);
		float* Y_O2_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_O2_0099_le.dat",n);
		Info<<Y_O2_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[1][celli]=Y_O2_DNS[celli+n1];//forAll(Y_O2_DNS_OF,i) Y_O2_DNS_OF[i]=Y_O2_DNS[i];
		delete Y_O2_DNS;Y_O2_DNS=NULL;
	
		//float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_L_HAWKES_DATA_littleEndian/jet_0099/jet_Y_OH_0099_le.dat",n);
		float* Y_OH_DNS=readFloatBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099/jet_Y_OH_0099_le.dat",n);	
		Info<<Y_OH_DNS[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_DNS[3][celli]=Y_OH_DNS[celli+n1];//forAll(Y_OH_DNS_OF,i) Y_OH_DNS_OF[i]=Y_OH_DNS[i];
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

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	for(int celli=n0;celli<n2;celli++)
	{
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		//const double t0 = 0.;
		//double tf = 2e-09;//Ali 0.;	
		for(unsigned int i=0;i<ns;i++)
				omegaStar_[i+1] = Y_DNS[i][celli];
				
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xStar_.GetHandle(), MWMean, omegaStar_.GetHandle());

		const double TStar_ = T_DNS_OF[celli];
		double P_Pa_=p_DNS_OF[celli];
		double MWStar_=MWMean;
		double cTotStar_ = P_Pa_/(PhysicalConstants::R_J_kmol * TStar_);
		double rhoStar_ = cTotStar_*MWStar_;
		Product(cTotStar_, xStar_, &cStar_);
		thermodynamicsMapXML->SetTemperature(TStar_);
		thermodynamicsMapXML->SetPressure(P_Pa_);
		double cpStar_ = thermodynamicsMapXML->cpMolar_Mixture_From_MoleFractions(xStar_.GetHandle());
		cpStar_/=MWStar_;
		
		kineticsMapXML->SetTemperature(TStar_);
		kineticsMapXML->SetPressure(P_Pa_);
		kineticsMapXML->ReactionEnthalpiesAndEntropies();
		kineticsMapXML->KineticConstants();
		kineticsMapXML->ReactionRates(cStar_.GetHandle());
		kineticsMapXML->FormationRates(RStar_.GetHandle());
		const double QRStar_ = kineticsMapXML->HeatRelease(RStar_.GetHandle());

		
		//Addedd by Ali 1 Aug 2017 to get RR

		OpenSMOKE::OpenSMOKEVectorDouble rrNet;	
		ChangeDimensions(kineticsMapXML->NumberOfReactions(), &rrNet, true);
		kineticsMapXML->GiveMeReactionRates(rrNet.GetHandle());
		for(unsigned int k=0;k<kineticsMapXML->NumberOfReactions();k++)
		{
			ReactionRates_DNS[k][celli] = rrNet[k+1];
		}
		// end modification
			
			QdotCells_DNS[celli] = QRStar_;
			dQCells_DNS[celli] = QRStar_ * volume_cell;	
			if (counter%(int(0.001*n2)+1) == 0)
			{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

			}
			counter++;
			
	}
	counter = 0;
	//#include "Da.H"

	//Info<<"Y O2 10"<<Y_DNS[1][10]<<endl;
					
	//for H case
	//writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_T_0099_le_out1.dat",n2,T_DNS_Final);

	
	
	//Added by ali on 1 Aug 2017 to get RR
scalarField tmp_ReactionRates_i_DNS(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[0][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_1_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[1][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_2_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[2][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_3_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[3][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_4_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[4][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_5_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[5][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_6_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[6][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_7_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[7][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_8_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[8][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_9_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[9][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_10_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[10][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_11_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[11][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_12_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[12][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_13_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[13][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_14_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[14][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_15_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[15][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_16_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[16][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_17_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[17][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_18_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[18][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_19_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[19][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_20_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);
	for(int celli=n0;celli<n2;celli++) tmp_ReactionRates_i_DNS[celli]=ReactionRates_DNS[20][celli];
	writedoubleBinaryFile("/scratch/Ali/RAW_DNS_HAWKES_DATA_littleEndian/HIGH/jet_0099_temp/jet_ReactionRates_21_0099_AREN_out5.dat",n2,tmp_ReactionRates_i_DNS);


	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;				
}

