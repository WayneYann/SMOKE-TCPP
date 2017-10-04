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

				const scalarField& TCells = T_DNS_OF;
				const scalarField& pCells = p_DNS_OF; 
				//scalarField& tauChemCells = tauChem; 
				//scalarField& DaCells = Da.internalField(); 
				//scalarField& ReTCells = ReT.internalField();


				forAll(TCells, celli)
				{
					const double Ti = TCells[celli];
					const double pi = pCells[celli];

					for(unsigned int j=0;j<ns;j++)
						yStar[j+1] =Y_DNS[j][celli];
						//yStar[j+1] = YStar_[j].internalField()[i];

					// Chemical time
					const double tauLocal = chemicalTimes->CalculateCharacteristicChemicalTime(Ti,pi,yStar);
					
					//std::vector<double> tauLocal = chemicalTimes->FromEigenValueAnalysisAll(Ti,pi,yStar);
					//std::vector<double> tauLocal = chemicalTimes->FromFormationRatesAll(Ti,pi,yStar);
					
					// Coefficients
					//const scalar nu = mu[i]/(rho[i] + SMALL);
					const scalar nu = nu_DNS_OF[celli];
					const scalar DaLocal_k = max(min(Foam::sqrt(nu/(eps_DNS_OF[celli] + SMALL))/tauLocal, maximum_Da), minimum_Da);
					
					const scalar DaLocal = max(min((1./(chi_DNS_OF[celli] + SMALL))/tauLocal, maximum_Da), minimum_Da);
					
					//const scalar ReTLocal = CRe_coefficient*sqr(k[i])/(nu*epsilon[i] + SMALL);

					//const scalar C1 = Foam::sqrt(Ctau_coefficient/3.);
		        		//const scalar CtauLocal = max( min(C1/(DaLocal*Foam::sqrt(ReTLocal + 1)), 5), 0.40825);
					//const scalar CgammaLocal = min( Cgamma_coefficient *Foam::sqrt(DaLocal*(ReTLocal+1.)), 2.1377);

					// Fill fields
					//for(unsigned int j=0;j<ns;j++)
						//tauChemSpecie_DNS[j][celli] = tauLocal[j];
					Da_DNS_k[celli] = DaLocal_k;
					
					Da_DNS[celli] = DaLocal;
										
					//ReTCells[i] = ReTLocal;
				
					// Fine structure properties
					//tauStar[i] = CtauLocal * Foam::sqrt( nu / (epsilon[i]+SMALL) );
					//gammaL[i]  = CgammaLocal * pow025(nu*epsilon[i]/(sqr(k[i]) + SMALL));
					
					if (counter%(int(0.001*n2)+1) == 0)
					{

					Info << "   Accomplished: " << counter << "/" << n2<< endl;

					}
					counter++;
				}
				
		}
