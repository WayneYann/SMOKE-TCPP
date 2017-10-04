scalar eSgsMin=SMALL;
Info<< "min/max(k)   =       " << min(k_SGS_LES_OF) << ", " << max(k_SGS_LES_OF) << endl;
Info<< "min/max(epsilon)  = " << min(eps_SGS_LES_OF) << ", " << max(eps_SGS_LES_OF) << endl;
//bound ( k_SGS_LES_OF, kSgsMin );   
//bound ( eps_SGS_LES_OF, eSgsMin ); 
forAll( eps_SGS_LES_OF ,i) if (eps_SGS_LES_OF[i]<0) eps_SGS_LES_OF[i]=fabs(eps_SGS_LES_OF[i]);
//eps_SGS_LES_OF=fabs(eps_SGS_LES_OF);

Info<< "min/max(epsilon) after bound  = " << min(eps_SGS_LES_OF) << ", " << max(eps_SGS_LES_OF) << endl;

ReTau_LES = k_SGS_LES_OF * k_SGS_LES_OF / eps_SGS_LES_OF / nu_LES_OF ; 

tauMix_LES =  sqrt( (1.2247*filterSize/sqrt(k_SGS_LES_OF))*sqrt(nu_LES_OF/epsOrig_LES_OF) ); //geometrical mean of Kolmogorov scale and filter size scale
//tauMix_LES =  sqrt( (1.2247*filterSize/sqrt(k_SGS_LES_OF))*sqrt(nu_LES_OF/eps_SGS_LES_OF) ); //geometrical mean of Kolmogorov scale and filter size scale
//tauMix_LES =  pow((nu_LES_OF*pow(filterSize,3)/pow(k_SGS_LES_OF,2.5)),0.25); //geometrical mean of Kolmogorov scale and filter size scale 

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
				//const scalarField& tauMixCells = tauMix_LES_OF; 
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
					const double tauLocal = chemicalTimes->CalculateCharacteristicChemicalTime(Ti,pi,yStar);
					//std::vector<double> tauLocal = chemicalTimes->FromEigenValueAnalysisAll(Ti,pi,yStar);
					//std::vector<double> tauLocal = chemicalTimes->FromFormationRatesAll(Ti,pi,yStar);
					
					// Mixing time				
					//const scalar tauMixLocal = tauMixCells[celli];
					
					// PASR coefficients
					const scalar kappaLocal = tauLocal/(tauLocal+tauMix_LES[celli]);
					const scalar DaLocal = max( min(tauMix_LES[celli]/tauLocal, maximum_Da), minimum_Da);
					//const scalar nu = mu[i]/(rho[i] + SMALL);
					//const scalar DaLocal = max(min(Foam::sqrt(nu/(epsilon[i] + SMALL))/tauLocal, maximum_Da), minimum_Da);
					//const scalar ReTLocal = CRe_coefficient*sqr(k[i])/(nu*epsilon[i] + SMALL);

					//const scalar C1 = Foam::sqrt(Ctau_coefficient/3.);
		        		//const scalar CtauLocal = max( min(C1/(DaLocal*Foam::sqrt(ReTLocal + 1)), 5), 0.40825);
					//const scalar CgammaLocal = min( Cgamma_coefficient *Foam::sqrt(DaLocal*(ReTLocal+1.)), 2.1377);

					// Fill fields
					//for(unsigned int j=0;j<ns;j++)
						//tauChemSpecie_LES[j][celli] = tauLocal[j];
					tauChem_LES[celli] = tauLocal;
					kappa_LES[celli] = kappaLocal;
					//DaCells[i] = DaLocal;
					//ReTCells[i] = ReTLocal;
				
					// Fine structure properties
					//tauStar[i] = CtauLocal * Foam::sqrt( nu / (epsilon[i]+SMALL) );
					//gammaL[i]  = CgammaLocal * pow025(nu*epsilon[i]/(sqr(k[i]) + SMALL));
				}
				
		}
