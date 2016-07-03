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


void range_macro() {
		TString dir =gSystem->UnixPathName(__FILE__);
		dir.ReplaceAll("range_macro.C","");

		TCanvas* c3 = new TCanvas("c3", "ranges pressione",200,10,700,500);


		TGraphErrors *g1 = new TGraphErrors((dir + "ranges").Data(), "%lg %lg %lg");
    TF2 *f2 = new TF2("f2","1/y",300,700,0.05,0.2);
    g1->Apply(f2);

    //  TGraphErrors *g1 = new TGraphErrors(n,d.data(),d.data(),d.data(),d.data());
		g1->SetTitle("Range vs Pressione");
		g1->Draw("ALP");

		return;
}
