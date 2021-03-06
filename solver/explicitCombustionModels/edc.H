//if you change CD2 from 0.5 to 0.8 Ccsi=2.4042 & Ctau=0.5164
scalar Ccsi = 2.1377;//2.4042;//
scalar Ctau = 0.40825;//0.5164;//
//update on Sep 2017
//it seems that by constrain on just gammaStar^2<1 not (gammaStar^2/(1-gammaStar^2)<1 the results improved
//scalar maxGammaSquared =0.75487766248;//0.99999;// //const dimensionedScalar eSgsMin( "eSgsMin",   dimensionSet(0,2,-3,0,0,0,0), SMALL ); 
maxGammaL=0.75487766248;

scalar eSgsMin=SMALL;
Info<< "min/max(k)   =       " << min(k_SGS_LES_OF) << ", " << max(k_SGS_LES_OF) << endl;
Info<< "min/max(epsilon)  = " << min(eps_SGS_LES_OF) << ", " << max(eps_SGS_LES_OF) << endl;
//bound ( k_SGS_LES_OF, kSgsMin );   
//bound ( eps_SGS_LES_OF, eSgsMin ); 
//Info<< "min/max(k) after bound =       " << min(residualKineticEnergy_LES.internalField()) << ", " << max(residualKineticEnergy_LES.internalField()) << endl;
//Info<< "min/max(epsilon) after bound= " << min(epsilonSGS_LES.internalField()) << ", " << max(epsilonSGS_LES.internalField()) << endl;

forAll( eps_SGS_LES_OF ,i) if (eps_SGS_LES_OF[i]<0) eps_SGS_LES_OF[i]=fabs(eps_SGS_LES_OF[i]);
//eps_SGS_LES_OF=fabs(eps_SGS_LES_OF);
Info<< "min/max(epsilon) after bound  = " << min(eps_SGS_LES_OF) << ", " << max(eps_SGS_LES_OF) << endl;
 

ReTau_LES = k_SGS_LES_OF * k_SGS_LES_OF / eps_SGS_LES_OF / nu_LES_OF ; 

//gammaL_LES = Ccsi * pow(  nu_LES_OF * eps_SGS_LES_OF / pow( k_SGS_LES_OF, 2.0), 0.25);		
//Fureby mod
gammaL_LES = 1.2128 * pow(  nu_LES_OF * eps_SGS_LES_OF / pow( k_SGS_LES_OF, 2.0), 0.25);		

tauStar_LES = pow( nu_LES_OF / eps_SGS_LES_OF , 0.5);
//bound ( tauStar_LES, tauMin );
//Mod: July 2017 Ali
//There is some doubts about different handling of gammaStar and gammaL
//refer to : M. Bösenhofer, C. Jordan, M. Harasek,A Flame D Modelling Study Employing Eddy Dissipation Concept Modifications,ECM2017
//So it is better to clip gammaL
//use gammaL^2 in the nominator
//use gammaL^3 in denominator


gammaL_LES= min(maxGammaL,gammaL_LES);//gammaStar_LES=0.6;//

gammaStar_LES = pow(gammaL_LES, 2.);
//gammaStar_LES= min(maxGammaSquared,gammaStar_LES);//gammaStar_LES=0.6;//

//mDotStar_LES  = (1./Ctau)/tauStar_LES;//mDotStar_LES  = pow((1./Ctau)/tauStar_LES,1./3.);
//Fureby mod
mDotStar_LES  = 1.27/tauStar_LES;//mDotStar_LES  = pow((1./Ctau)/tauStar_LES,1./3.);

tfStar_LES =(1.)/(mDotStar_LES);// (1.-gammaStar_LES)/(mDotStar_LES);

//tfStar_LES =2e-09*pow(filterWidth,3.);// 
//tfStar_LES = (1.-pow(gammaL_LES, 3.))/(mDotStar_LES);

Info<< "min/max(tfStar_LES) =       " << min(tfStar_LES) << ", " << max(tfStar_LES) << endl;

edc_coefficient_LES = gammaStar_LES*mDotStar_LES/(1.-pow(gammaL_LES,3.));
//edc_coefficient_LES = gammaStar_LES*mDotStar_LES/(1.-gammaStar_LES);//edc_coefficient_LES = gammaStar_LES/tfStar_LES;//
//edc_coefficient_PFR_tfFlow_LES = gammaStar_LES/(1.-gammaStar_LES)/tfFlow_LES;
//edc_coefficient_LES = gammaStar_LES/(1.-gammaStar_LES)/tfStar_LES;// 

// Calculation of characteristic times
{
	scalar threshold_chemical_time = 0.1;
	scalar threshold_temperature_chemical_time = 503.;
	//CharacteristicChemicalTimes::CharacteristicChemicalTimesType characteristic_chemical_times_type = CharacteristicChemicalTimes::CHEMICAL_TIMES_EIGENVALUES;
	CharacteristicChemicalTimes::CharacteristicChemicalTimesType characteristic_chemical_times_type = CharacteristicChemicalTimes::CHEMICAL_TIMES_FORMATION_RATES;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();

	CharacteristicChemicalTimes* chemicalTimes = new CharacteristicChemicalTimes(*thermodynamicsMapXML, *kineticsMapXML);
	chemicalTimes->SetThresholdChemicalTime(threshold_chemical_time);
	chemicalTimes->SetType(characteristic_chemical_times_type);
	chemicalTimes->SetThresholdTemperatureChemicalTime(threshold_temperature_chemical_time);
	const unsigned int ns = thermodynamicsMapXML->NumberOfSpecies();
	OpenSMOKE::OpenSMOKEVectorDouble yStar(ns);

	const scalarField& TCells = T_LES_OF;
	const scalarField& pCells = p_LES_OF; 
     //scalarField& tauChemCells = tauChem; 
     //scalarField& DaCells = Da.internalField(); 
     //scalarField& ReTCells = ReT.internalField();

	forAll(TCells, celli)
	{
		const double Ti = TCells[celli];
		const double pi = pCells[celli];
		for(unsigned int j=0;j<ns;j++)
			yStar[j+1] =Y_LES[j][celli];
			//yStar[j+1] = YStar_[j].internalField()[i];

		// Chemical time
		//const double tauLocal = chemicalTimes->CalculateCharacteristicChemicalTime(Ti,pi,yStar);
					
		//std::vector<double> tauLocal = chemicalTimes->FromEigenValueAnalysisAll(Ti,pi,yStar);
		std::vector<double> tauLocal = chemicalTimes->FromFormationRatesAll(Ti,pi,yStar);
			
		// Coefficients
		//const scalar nu = mu[i]/(rho[i] + SMALL);
		//const scalar DaLocal = max(min(Foam::sqrt(nu/(epsilon[i] + SMALL))/tauLocal, maximum_Da), minimum_Da);
		//const scalar ReTLocal = CRe_coefficient*sqr(k[i])/(nu*epsilon[i] + SMALL);

		//const scalar C1 = Foam::sqrt(Ctau_coefficient/3.);
   		//const scalar CtauLocal = max( min(C1/(DaLocal*Foam::sqrt(ReTLocal + 1)), 5), 0.40825);
		//const scalar CgammaLocal = min( Cgamma_coefficient *Foam::sqrt(DaLocal*(ReTLocal+1.)), 2.1377);

		// Fill fields
		for(unsigned int j=0;j<ns;j++)
			tauChemSpecie_LES[j][celli] = tauLocal[j];
		//DaCells[i] = DaLocal;
		//ReTCells[i] = ReTLocal;
				
		// Fine structure properties
		//tauStar[i] = CtauLocal * Foam::sqrt( nu / (epsilon[i]+SMALL) );
					//gammaL[i]  = CgammaLocal * pow025(nu*epsilon[i]/(sqr(k[i]) + SMALL));
	}
				
}
