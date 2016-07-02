#include <Riostream.h>
#include <stdlib.h>
#include <TROOT.h>
#include <TSystem.h>
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"

struct bragg_signal {
  short int s[128];
};

int AnaBraggWidth(char *filename, int intto=80, float blfix=13, int nsig=0) {

  bragg_signal signal;

  TFile *fin=new TFile(filename);
  if (!fin->IsOpen()) {
    std::cout << "file not found! " << std::endl;
    return -1;
  }

  TTree *tree = (TTree*)fin->Get("bragg");
  if (!tree) {
    std::cout << "Bragg tree not found! " << std::endl;
    return -2;
  }

  TBranch *br = tree->GetBranch("signals");
  if (!br) {
    std::cout << "Signal branch not found! " << std::endl;
    return -3;
  }

  br->SetAddress(&signal);
  int nev = br->GetEntries();
  std::cout << "Number of events in file : " << nev << std::endl;

  // ANALIZZA EVENTO x EVENTO

  // altri parametri iniziali
  float thr_frac = 0.4; // soglia rispetto al vmax per il calcolo della larghezza
  int intfrom = 0;// regione di integrazione da 0 a intto
  if (intto>128) intto=128;
  int blfrom = 108, blto = 128; // regione per il calcolo della baseline


  float bl; // baseline evento x evento
  float integral; 
  float vmax; // massimo relativo alla bl
  float width; // larghezza dei segnali


  char outfilename[200];
  strcpy(outfilename,"anabragg_");
  char *cc=strrchr(filename,'/');
  if (cc) {cc++; strcat(outfilename,cc);}
  else strcat(outfilename,filename);

  TFile *fout=new TFile(outfilename,"RECREATE"); // output file

  TNtuple *nt=new TNtuple("nt","","ev:vmax:width:integral:baseline");

  int maxev=nev;
  if (nsig && nsig<nev) maxev=nsig;
  
  // LOOP SUGLI EVENTI
  for (int i=0; i<maxev; i++) {

    // recupera l'evento
    br->GetEntry(i);

    // inizializza a zero
    bl=0; 
    integral=0;
    vmax=0;				     
    width=0;

    // calcolo baseline
    for (int j=blfrom; j<blto; j++) 
      bl += signal.s[j]; bl /= (blto-blfrom);    
    
    // calcolo integrali e vmax
    for (int j=intfrom; j<intto; j++) {
      integral += (signal.s[j] - blfix);
      if ( (signal.s[j] - blfix) > vmax ) vmax = (signal.s[j] - blfix);
    }
    
    // CALCOLO DELLA LARGHEZZA DEL SEGNALE A UNA CERTA PERCENTUALE DEL VMAX
    // ...
    float ratio = 0.4;
    for (int j = 0; j < 128; ++j)
    {
        if (signal.s[j] > ratio*vmax) ++width;
    }
    /* alternativamente
    int start = 0; 
    int end = 0;
    for (int j = 0; j < 128; ++j){
    	if (!start && signal.s[j] > ratio*vmax) ++width;
    	if (start && !end && signal.s[j] > ratio*vmax) ++width;
    }*/
    

    nt->Fill(i,vmax,width,integral,bl);
  }
  std::cout << maxev << " events analyzed..." << std::endl;

  fout->Write();
  fout->Close();

  fin->Close();

  new TFile(outfilename); // riapre il file dei risultati

  return 0;
}
