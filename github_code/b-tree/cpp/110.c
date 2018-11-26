#include "Ntuple.h"

void setBranchAddresses(TTree* chain, Ntuple& treeVars)
{
  chain -> SetBranchAddress("runId",       &treeVars.runId);
  chain -> SetBranchAddress("eventId",     &treeVars.eventId);
  chain -> SetBranchAddress("isSignal",    &treeVars.isSignal);
  
  // PAT VARIABLES
  chain -> SetBranchAddress("nMuons",      &treeVars.nMuons     );
  chain -> SetBranchAddress("nJets",       &treeVars.nJets      );
  chain -> SetBranchAddress("nVertices",   &treeVars.nVertices  );
  chain -> SetBranchAddress("nGen",        &treeVars.nGen       );

  chain -> SetBranchAddress("muPx",        treeVars.muPx       );
  chain -> SetBranchAddress("muPy",        treeVars.muPy       );
  chain -> SetBranchAddress("muPz",        treeVars.muPz       );
  chain -> SetBranchAddress("muE",         treeVars.muE        );
  chain -> SetBranchAddress("muE",         treeVars.muE        );
  chain -> SetBranchAddress("muIso5",      treeVars.muIso5     );
  chain -> SetBranchAddress("muIso4",      treeVars.muIso4     );
  chain -> SetBranchAddress("muIso3",      treeVars.muIso3     );
  chain -> SetBranchAddress("muIso2",      treeVars.muIso2     );
  chain -> SetBranchAddress("muIso1",      treeVars.muIso1     );
  chain -> SetBranchAddress("muIhit5",     treeVars.muIhit5     );
  chain -> SetBranchAddress("muIhit4",     treeVars.muIhit4     );
  chain -> SetBranchAddress("muIhit3",     treeVars.muIhit3     );
  chain -> SetBranchAddress("muIhit2",     treeVars.muIhit2     );
  chain -> SetBranchAddress("muIhit1",     treeVars.muIhit1     );
  
  chain -> SetBranchAddress("jetPx",        treeVars.jetPx     );
  chain -> SetBranchAddress("jetPy",        treeVars.jetPy     );
  chain -> SetBranchAddress("jetPz",        treeVars.jetPz     );
  chain -> SetBranchAddress("jetE",         treeVars.jetE      );
  chain -> SetBranchAddress("jetNDau",      treeVars.jetNDau   );
  chain -> SetBranchAddress("jetCM",        treeVars.jetCM     );
  chain -> SetBranchAddress("jetNM",        treeVars.jetNM     ); // neutral Multiplicity
  chain -> SetBranchAddress("jetMM",        treeVars.jetMM     ); // muon Multiplicity
  chain -> SetBranchAddress("jetCEF",       treeVars.jetCEF    );
  chain -> SetBranchAddress("jetCHF",       treeVars.jetCHF    );
  chain -> SetBranchAddress("jetNHF",       treeVars.jetNHF    );
  chain -> SetBranchAddress("jetNEF",       treeVars.jetNEF    );  // muon energy fraction
  chain -> SetBranchAddress("jetMEF",        treeVars.jetMEF    );
  chain -> SetBranchAddress("jetIso5",      treeVars.jetIso5     );
  chain -> SetBranchAddress("jetIso4",      treeVars.jetIso4     );
  chain -> SetBranchAddress("jetIso3",      treeVars.jetIso3     );
  chain -> SetBranchAddress("jetIso2",      treeVars.jetIso2     );
  chain -> SetBranchAddress("jetIso1",      treeVars.jetIso1     );
  chain -> SetBranchAddress("jetIhit5",     treeVars.jetIhit5     );
  chain -> SetBranchAddress("jetIhit4",     treeVars.jetIhit4     );
  chain -> SetBranchAddress("jetIhit3",     treeVars.jetIhit3     );
  chain -> SetBranchAddress("jetIhit2",     treeVars.jetIhit2     );
  chain -> SetBranchAddress("jetIhit1",     treeVars.jetIhit1     );

  chain -> SetBranchAddress("pdgId",        treeVars.pdgId       );
  chain -> SetBranchAddress("momId",        treeVars.momId       );
  chain -> SetBranchAddress("genPx",        treeVars.genPx       );
  chain -> SetBranchAddress("genPy",        treeVars.genPy       );
  chain -> SetBranchAddress("genPz",        treeVars.genPz       );
  chain -> SetBranchAddress("genE",         treeVars.genE        );
  chain -> SetBranchAddress("genVx",        treeVars.genVx       );
  chain -> SetBranchAddress("genVy",        treeVars.genVy       );
  chain -> SetBranchAddress("genVz",        treeVars.genVz       );
  chain -> SetBranchAddress("genIso5",      treeVars.genIso5     );
  chain -> SetBranchAddress("genIso4",      treeVars.genIso4     );
  chain -> SetBranchAddress("genIso3",      treeVars.genIso3     );
  chain -> SetBranchAddress("genIso2",      treeVars.genIso2     );
  chain -> SetBranchAddress("genIso1",      treeVars.genIso1     );
  chain -> SetBranchAddress("genIhit5",     treeVars.genIhit5     );
  chain -> SetBranchAddress("genIhit4",     treeVars.genIhit4     );
  chain -> SetBranchAddress("genIhit3",     treeVars.genIhit3     );
  chain -> SetBranchAddress("genIhit2",     treeVars.genIhit2     );
  chain -> SetBranchAddress("genIhit1",     treeVars.genIhit1     );
  
}

void setBranches(TTree* chain, Ntuple& treeVars)
{
  chain -> Branch("runId",         &treeVars.runId,                "runId/i");
  chain -> Branch("eventId",       &treeVars.eventId,            "eventId/i");
  chain -> Branch("isSignal",      &treeVars.isSignal,          "isSignal/I");
  
  // RECO VARIABLES
  chain -> Branch("nMuons",      &treeVars.nMuons,               "nMuons/I");
  chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nVertices",   &treeVars.nVertices,            "nVertices/I");
  chain -> Branch("nGen",        &treeVars.nGen,                 "nGen/I");

  chain -> Branch("muPx",        treeVars.muPx,                 "muPx[nMuons]/F");
  chain -> Branch("muPy",        treeVars.muPy,                 "muPy[nMuons]/F");
  chain -> Branch("muPz",        treeVars.muPz,                 "muPz[nMuons]/F");
  chain -> Branch("muE",         treeVars.muE,                  "muE[nMuons]/F");
  chain -> Branch("muIso5",      treeVars.muIso5,               "muIso5[nMuons][5]/F");
  chain -> Branch("muIso4",      treeVars.muIso4,               "muIso4[nMuons][5]/F");
  chain -> Branch("muIso3",      treeVars.muIso3,               "muIso3[nMuons][5]/F");
  chain -> Branch("muIso2",      treeVars.muIso2,               "muIso2[nMuons][5]/F");
  chain -> Branch("muIso1",      treeVars.muIso1,               "muIso1[nMuons][5]/F");
  chain -> Branch("muIhit5",     treeVars.muIhit5,              "muIhit5[nMuons][5]/I");
  chain -> Branch("muIhit4",     treeVars.muIhit4,              "muIhit4[nMuons][5]/I");
  chain -> Branch("muIhit3",     treeVars.muIhit3,              "muIhit3[nMuons][5]/I");
  chain -> Branch("muIhit2",     treeVars.muIhit2,              "muIhit2[nMuons][5]/I");
  chain -> Branch("muIhit1",     treeVars.muIhit1,              "muIhit1[nMuons][5]/I");
  
  chain -> Branch("jetPx",        treeVars.jetPx,                 "jetPx[nJets]/F");
  chain -> Branch("jetPy",        treeVars.jetPy,                 "jetPy[nJets]/F");
  chain -> Branch("jetPz",        treeVars.jetPz,                 "jetPz[nJets]/F");
  chain -> Branch("jetE",         treeVars.jetE,                  "jetE[nJets]/F");
  chain -> Branch("jetNDau",      treeVars.jetNDau,               "jetNDau[nJets]/I");
  chain -> Branch("jetCM",        treeVars.jetCM,                 "jetCM[nJets]/I"  );
  chain -> Branch("jetNM",        treeVars.jetNM,                 "jetNM[nJets]/I"  );
  chain -> Branch("jetMM",        treeVars.jetMM,                 "jetMM[nJets]/I"  );
  chain -> Branch("jetCEF",       treeVars.jetCEF,                "jetCEF[nJets]/F" );
  chain -> Branch("jetCHF",       treeVars.jetCHF,                "jetCHF[nJets]/F" );
  chain -> Branch("jetNEF",       treeVars.jetNEF,                "jetNEF[nJets]/F" );
  chain -> Branch("jetNHF",       treeVars.jetNHF,                "jetNHF[nJets]/F" );
  chain -> Branch("jetMEF",       treeVars.jetMEF,                "jetMEF[nJets]/F" );
  chain -> Branch("jetIso5",      treeVars.jetIso5,               "jetIso5[nJets][5]/F");
  chain -> Branch("jetIso4",      treeVars.jetIso4,               "jetIso4[nJets][5]/F");
  chain -> Branch("jetIso3",      treeVars.jetIso3,               "jetIso3[nJets][5]/F");
  chain -> Branch("jetIso2",      treeVars.jetIso2,               "jetIso2[nJets][5]/F");
  chain -> Branch("jetIso1",      treeVars.jetIso1,               "jetIso1[nJets][5]/F");
  chain -> Branch("jetIhit5",     treeVars.jetIhit5,              "jetIhit5[nJets][5]/I");
  chain -> Branch("jetIhit4",     treeVars.jetIhit4,              "jetIhit4[nJets][5]/I");
  chain -> Branch("jetIhit3",     treeVars.jetIhit3,              "jetIhit3[nJets][5]/I");
  chain -> Branch("jetIhit2",     treeVars.jetIhit2,              "jetIhit2[nJets][5]/I");
  chain -> Branch("jetIhit1",     treeVars.jetIhit1,              "jetIhit1[nJets][5]/I");

  chain -> Branch("pdgId",        treeVars.pdgId,                 "pdgId[nGen]/I");
  chain -> Branch("momId",        treeVars.momId,                 "momId[nGen]/I");
  chain -> Branch("genPx",        treeVars.genPx,                 "genPx[nGen]/F");
  chain -> Branch("genPy",        treeVars.genPy,                 "genPy[nGen]/F");
  chain -> Branch("genPz",        treeVars.genPz,                 "genPz[nGen]/F");
  chain -> Branch("genE",         treeVars.genE,                  "genE[nGen]/F");
  chain -> Branch("genVx",        treeVars.genVx,                 "genVx[nGen]/F");
  chain -> Branch("genVy",        treeVars.genVy,                 "genVy[nGen]/F");
  chain -> Branch("genVz",        treeVars.genVz,                 "genVz[nGen]/F");
  chain -> Branch("genIso5",      treeVars.genIso5,               "genIso5[nGen][5]/F");
  chain -> Branch("genIso4",      treeVars.genIso4,               "genIso4[nGen][5]/F");
  chain -> Branch("genIso3",      treeVars.genIso3,               "genIso3[nGen][5]/F");
  chain -> Branch("genIso2",      treeVars.genIso2,               "genIso2[nGen][5]/F");
  chain -> Branch("genIso1",      treeVars.genIso1,               "genIso1[nGen][5]/F");
  chain -> Branch("genIhit5",     treeVars.genIhit5,              "genIhit5[nGen][5]/I");
  chain -> Branch("genIhit4",     treeVars.genIhit4,              "genIhit4[nGen][5]/I");
  chain -> Branch("genIhit3",     treeVars.genIhit3,              "genIhit3[nGen][5]/I");
  chain -> Branch("genIhit2",     treeVars.genIhit2,              "genIhit2[nGen][5]/I");
  chain -> Branch("genIhit1",     treeVars.genIhit1,              "genIhit1[nGen][5]/I");
  
}


void initializeBranches(TTree* chain, Ntuple& treeVars)
{
  treeVars.runId       = 0;
  treeVars.eventId     = 0; 
  treeVars.isSignal    = 0; 
  
  treeVars.nJets      = 0 ; 
  treeVars.nMuons     = 0 ; 
  treeVars.nGen       = 0 ; 
  treeVars.nVertices  = 0 ; 

  for ( int i=0; i< MAXJET; i++) {
      treeVars.jetPx[i] = 0 ;
      treeVars.jetPy[i] = 0 ;
      treeVars.jetPz[i] = 0 ;
      treeVars.jetE[i]  = 0 ;
      treeVars.jetNDau[i] = 0 ;
      treeVars.jetCM[i] = 0 ;
      treeVars.jetNM[i] = 0 ;
      treeVars.jetMM[i] = 0 ;
      treeVars.jetCEF[i] = 0 ;
      treeVars.jetCHF[i] = 0 ;
      treeVars.jetNEF[i] = 0 ;
      treeVars.jetNHF[i] = 0 ;
      treeVars.jetMEF[i] = 0 ;
      for ( int j=0; j< 5; j++ ) {
          treeVars.jetIso5[i][j] = 0 ;
          treeVars.jetIso4[i][j] = 0 ;
          treeVars.jetIso3[i][j] = 0 ;
          treeVars.jetIso2[i][j] = 0 ;
          treeVars.jetIso1[i][j] = 0 ;
          treeVars.jetIhit5[i][j] = 0 ;
          treeVars.jetIhit4[i][j] = 0 ;
          treeVars.jetIhit3[i][j] = 0 ;
          treeVars.jetIhit2[i][j] = 0 ;
          treeVars.jetIhit1[i][j] = 0 ;
      }	   

  }
  for ( int i=0; i< MAXMU; i++) {
      treeVars.muPx[i] = 0 ;
      treeVars.muPy[i] = 0 ;
      treeVars.muPz[i] = 0 ;
      treeVars.muE[i] = 0 ;
      for ( int j=0; j< 5; j++ ) {
          treeVars.muIso5[i][j] = 0 ;
          treeVars.muIso4[i][j] = 0 ;
          treeVars.muIso3[i][j] = 0 ;
          treeVars.muIso2[i][j] = 0 ;
          treeVars.muIso1[i][j] = 0 ;
          treeVars.muIhit5[i][j] = 0 ;
          treeVars.muIhit4[i][j] = 0 ;
          treeVars.muIhit3[i][j] = 0 ;
          treeVars.muIhit2[i][j] = 0 ;
          treeVars.muIhit1[i][j] = 0 ;
      }	   
  } 
  for ( int i=0; i< MAXGEN; i++) {
      treeVars.pdgId[i] = 0 ;
      treeVars.momId[i] = 0 ;
      treeVars.genPx[i] = 0 ;
      treeVars.genPy[i] = 0 ;
      treeVars.genPz[i] = 0 ;
      treeVars.genE[i]  = 0 ;
      treeVars.genVx[i] = 0 ;
      treeVars.genVy[i] = 0 ;
      treeVars.genVz[i] = 0 ;
      for ( int j=0; j< 5; j++ ) {
          treeVars.genIso5[i][j] = 0 ;
          treeVars.genIso4[i][j] = 0 ;
          treeVars.genIso3[i][j] = 0 ;
          treeVars.genIso2[i][j] = 0 ;
          treeVars.genIso1[i][j] = 0 ;
          treeVars.genIhit5[i][j] = 0 ;
          treeVars.genIhit4[i][j] = 0 ;
          treeVars.genIhit3[i][j] = 0 ;
          treeVars.genIhit2[i][j] = 0 ;
          treeVars.genIhit1[i][j] = 0 ;
      }	   
  }

}
