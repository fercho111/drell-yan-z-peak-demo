#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TClonesArray.h"   // <-- required for compiled ACLiC
#include "TROOT.h"


#include "DelphesClasses.h"
#include "ExRootTreeReader.h"

void plot_zpeak(const char* filename = "tag_1_delphes_events.root")
{
  // Load Delphes dictionary library (Muon class, etc.)
  int rc = gSystem->Load(gSystem->ExpandPathName("~/Pheno_Tools/MG5_aMC_v3_7_0/Delphes/libDelphes.so"));
  if (rc < 0) {
    std::cout << "Error: could not load libDelphes.so\n";
    return;
  }

  TFile *f = TFile::Open(filename);
  if (!f || f->IsZombie()) {
    std::cout << "Error: cannot open file: " << filename << "\n";
    return;
  }

  TTree *t = (TTree*)f->Get("Delphes");
  if (!t) {
    std::cout << "Error: cannot find TTree named 'Delphes'\n";
    return;
  }

  ExRootTreeReader *tr = new ExRootTreeReader(t);
  TClonesArray *mu = tr->UseBranch("Muon");

  TH1F *h = new TH1F("h",
    "Drell-Yan dimuon invariant mass; m_{#mu#mu} (GeV); Events",
    120, 50, 130);

  Long64_t n = tr->GetEntries();
  for (Long64_t i = 0; i < n; i++) {
    tr->ReadEntry(i);
    if (mu->GetEntries() < 2) continue;

    Muon *m1 = (Muon*) mu->At(0);
    Muon *m2 = (Muon*) mu->At(1);

    TLorentzVector p1, p2;
    p1.SetPtEtaPhiM(m1->PT, m1->Eta, m1->Phi, 0.105658);
    p2.SetPtEtaPhiM(m2->PT, m2->Eta, m2->Phi, 0.105658);

    h->Fill((p1 + p2).M());
  }

  TCanvas *c = new TCanvas("c","Z peak",900,650);
  h->SetLineWidth(2);
  h->Draw();
  c->SetGrid();

  int b = h->GetMaximumBin();
  std::cout << "Peak near ~ " << h->GetXaxis()->GetBinCenter(b) << " GeV\n";
  std::cout << "Processed " << n << " events\n";
}
