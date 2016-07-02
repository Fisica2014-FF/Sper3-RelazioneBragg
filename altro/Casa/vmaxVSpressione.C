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


void vmaxVSpressione() {
		TString dir =gSystem->UnixPathName(__FILE__);
		dir.ReplaceAll("vmaxVSpressione.C","");

		TCanvas* c3 = new TCanvas("c3", "Picchi vmax",200,10,700,500);

		TGraphErrors *g1 = new TGraphErrors((dir + "picchi_vmax").Data(), "%lg %lg %lg");
		//  TGraphErrors *g1 = new TGraphErrors(n,d.data(),d.data(),d.data(),d.data());
		g1->SetTitle("Vmax");
		g1->Draw("ALP");

		return;
}
