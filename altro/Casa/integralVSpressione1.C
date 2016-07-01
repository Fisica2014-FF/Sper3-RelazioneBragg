#include <Riostream.h>
#include <stdlib.h>
#include <TROOT.h>
#include <TSystem.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1F.h"


void integralVSpressione1() {
		TString dir =gSystem->UnixPathName(__FILE__);
		dir.ReplaceAll("integralVSpressione1.C","");

		TCanvas* c1 = new TCanvas("c1", "Picchi integral 1",200,10,700,500);
		//TFile* f = new Tfile("picchi_integral.root","RECREATE");
		//TNtuple* = new nt1("nt1","picchi integrali 1", "P:mean:err_mean:RMS:err_RMS");
		//TNtuple* = new nt2("nt2","picchi integrali 2", "P:mean:err_mean:RMS:err_RMS");
		//TNtuple* = new nt3("nt3","picchi integrali 3", "P:mean:err_mean:RMS:err_RMS");

		std::vector<double> P;
		std::vector<double> mean;
		std::vector<double> err_mean;
		std::vector<double> err_P;

		ifstream inputf((dir + "picchi_integral1").Data());
		std::clog << (dir + "picchi_integral1").Data() << endl;

		double tP = 0;
		double tmean = 0;
		double terr_mean = 0;
		double tRMS = 0;
		double terr_RMS = 0;

		unsigned i = 0;
		while (inputf >> tP) {
			inputf >> tmean;
			inputf >> terr_mean;
			inputf >> tRMS;
			inputf >> terr_RMS;

			P.push_back(tP);
			mean.push_back(tmean);
			err_mean.push_back(terr_mean);
			err_P.push_back(0);
			clog << P.size() << "\n";
			clog << P.back() << "\n";
		}

		unsigned n = 5;
		std::vector<double> d = {1,2,3,4,5};

		TGraphErrors *g1 = new TGraphErrors(P.size(),P.data(),mean.data(),err_P.data(),err_mean.data());
		//  TGraphErrors *g1 = new TGraphErrors(n,d.data(),d.data(),d.data(),d.data());
		g1->SetTitle("Picchi integral 1");
		g1->Draw("ALP");

		return;
}
