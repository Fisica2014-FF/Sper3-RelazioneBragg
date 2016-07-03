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


void range3VSpressione() {
		TString dir =gSystem->UnixPathName(__FILE__);
		dir.ReplaceAll("range3VSpressione.C","");

		TCanvas* c3 = new TCanvas("c3", "Picchi vmax",200,10,700,500);

		TGraphErrors *g1 = new TGraphErrors((dir + "range_picco3").Data(), "%lg %lg %lg");
		//  TGraphErrors *g1 = new TGraphErrors(n,d.data(),d.data(),d.data(),d.data());
		TF2 *f2 = new TF2("f2","y*1000",300,700,0.05,0.2);
		g1->Apply(f2);

		g1->SetTitle("range picco 3");
		g1->GetXaxis()->SetTitle("mbar");
		g1->GetYaxis()->SetTitle("mm");

		g1->Draw("ALP");

		return;
}
