//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 17 20:34:05 2018 by ROOT version 6.14/00
// from TTree clas12/clas12
// found on file: out_clas_fullTfield_wdistorOff_002391.0.9.root
//////////////////////////////////////////////////////////

#ifndef c12epx_h
#define c12epx_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class c12epx : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderArray<float> RUN_config_torus = {fReader, "RUN_config_torus"};
   TTreeReaderArray<int> RUN_config_run = {fReader, "RUN_config_run"};
   TTreeReaderArray<int> RUN_config_event = {fReader, "RUN_config_event"};
   TTreeReaderArray<float> RUN_config_solenoid = {fReader, "RUN_config_solenoid"};
   TTreeReaderArray<int> RAW_scaler_crate = {fReader, "RAW_scaler_crate"};
   TTreeReaderArray<int> RAW_scaler_slot = {fReader, "RAW_scaler_slot"};
   TTreeReaderArray<int> RAW_scaler_channel = {fReader, "RAW_scaler_channel"};
   TTreeReaderArray<int> RAW_scaler_helicity = {fReader, "RAW_scaler_helicity"};
   TTreeReaderArray<int> RAW_scaler_quartet = {fReader, "RAW_scaler_quartet"};
   TTreeReaderArray<int> RAW_scaler_value = {fReader, "RAW_scaler_value"};
   TTreeReaderArray<int> REC_Event_NRUN = {fReader, "REC_Event_NRUN"};
   TTreeReaderArray<int> REC_Event_NEVENT = {fReader, "REC_Event_NEVENT"};
   TTreeReaderArray<float> REC_Event_EVNTime = {fReader, "REC_Event_EVNTime"};
   TTreeReaderArray<int> REC_Event_TYPE = {fReader, "REC_Event_TYPE"};
   TTreeReaderArray<int> REC_Event_TRG = {fReader, "REC_Event_TRG"};
   TTreeReaderArray<float> REC_Event_BCG = {fReader, "REC_Event_BCG"};
   TTreeReaderArray<float> REC_Event_STTime = {fReader, "REC_Event_STTime"};
   TTreeReaderArray<float> REC_Event_RFTime = {fReader, "REC_Event_RFTime"};
   TTreeReaderArray<int> REC_Event_Helic = {fReader, "REC_Event_Helic"};
   TTreeReaderArray<int> REC_Particle_pid = {fReader, "REC_Particle_pid"};
   TTreeReaderArray<float> REC_Particle_px = {fReader, "REC_Particle_px"};
   TTreeReaderArray<float> REC_Particle_py = {fReader, "REC_Particle_py"};
   TTreeReaderArray<float> REC_Particle_pz = {fReader, "REC_Particle_pz"};
   TTreeReaderArray<float> REC_Particle_vx = {fReader, "REC_Particle_vx"};
   TTreeReaderArray<float> REC_Particle_vy = {fReader, "REC_Particle_vy"};
   TTreeReaderArray<float> REC_Particle_vz = {fReader, "REC_Particle_vz"};
   TTreeReaderArray<int> REC_Particle_charge = {fReader, "REC_Particle_charge"};
   TTreeReaderArray<float> REC_Particle_beta = {fReader, "REC_Particle_beta"};
   TTreeReaderArray<float> REC_Particle_chi2pid = {fReader, "REC_Particle_chi2pid"};
   TTreeReaderArray<int> REC_Particle_status = {fReader, "REC_Particle_status"};
   TTreeReaderArray<int> REC_Calorimeter_pindex = {fReader, "REC_Calorimeter_pindex"};
   TTreeReaderArray<int> REC_Calorimeter_detector = {fReader, "REC_Calorimeter_detector"};
   TTreeReaderArray<int> REC_Calorimeter_sector = {fReader, "REC_Calorimeter_sector"};
   TTreeReaderArray<int> REC_Calorimeter_layer = {fReader, "REC_Calorimeter_layer"};
   TTreeReaderArray<float> REC_Calorimeter_energy = {fReader, "REC_Calorimeter_energy"};
   TTreeReaderArray<float> REC_Calorimeter_time = {fReader, "REC_Calorimeter_time"};
   TTreeReaderArray<float> REC_Calorimeter_path = {fReader, "REC_Calorimeter_path"};
   TTreeReaderArray<float> REC_Calorimeter_x = {fReader, "REC_Calorimeter_x"};
   TTreeReaderArray<float> REC_Calorimeter_y = {fReader, "REC_Calorimeter_y"};
   TTreeReaderArray<float> REC_Calorimeter_z = {fReader, "REC_Calorimeter_z"};
   TTreeReaderArray<float> REC_Calorimeter_lu = {fReader, "REC_Calorimeter_lu"};
   TTreeReaderArray<float> REC_Calorimeter_lv = {fReader, "REC_Calorimeter_lv"};
   TTreeReaderArray<float> REC_Calorimeter_lw = {fReader, "REC_Calorimeter_lw"};
   TTreeReaderArray<int> REC_Cherenkov_pindex = {fReader, "REC_Cherenkov_pindex"};
   TTreeReaderArray<int> REC_Cherenkov_detector = {fReader, "REC_Cherenkov_detector"};
   TTreeReaderArray<int> REC_Cherenkov_sector = {fReader, "REC_Cherenkov_sector"};
   TTreeReaderArray<float> REC_Cherenkov_nphe = {fReader, "REC_Cherenkov_nphe"};
   TTreeReaderArray<float> REC_Cherenkov_time = {fReader, "REC_Cherenkov_time"};
   TTreeReaderArray<float> REC_Cherenkov_path = {fReader, "REC_Cherenkov_path"};
   TTreeReaderArray<float> REC_Cherenkov_theta = {fReader, "REC_Cherenkov_theta"};
   TTreeReaderArray<float> REC_Cherenkov_phi = {fReader, "REC_Cherenkov_phi"};
   TTreeReaderArray<int> REC_ForwardTagger_pindex = {fReader, "REC_ForwardTagger_pindex"};
   TTreeReaderArray<int> REC_ForwardTagger_detector = {fReader, "REC_ForwardTagger_detector"};
   TTreeReaderArray<float> REC_ForwardTagger_energy = {fReader, "REC_ForwardTagger_energy"};
   TTreeReaderArray<float> REC_ForwardTagger_time = {fReader, "REC_ForwardTagger_time"};
   TTreeReaderArray<float> REC_ForwardTagger_path = {fReader, "REC_ForwardTagger_path"};
   TTreeReaderArray<float> REC_ForwardTagger_x = {fReader, "REC_ForwardTagger_x"};
   TTreeReaderArray<float> REC_ForwardTagger_y = {fReader, "REC_ForwardTagger_y"};
   TTreeReaderArray<float> REC_ForwardTagger_z = {fReader, "REC_ForwardTagger_z"};
   TTreeReaderArray<float> REC_ForwardTagger_dx = {fReader, "REC_ForwardTagger_dx"};
   TTreeReaderArray<float> REC_ForwardTagger_dy = {fReader, "REC_ForwardTagger_dy"};
   TTreeReaderArray<float> REC_ForwardTagger_radius = {fReader, "REC_ForwardTagger_radius"};
   TTreeReaderArray<int> REC_ForwardTagger_size = {fReader, "REC_ForwardTagger_size"};
   TTreeReaderArray<int> REC_Scintillator_pindex = {fReader, "REC_Scintillator_pindex"};
   TTreeReaderArray<int> REC_Scintillator_detector = {fReader, "REC_Scintillator_detector"};
   TTreeReaderArray<int> REC_Scintillator_sector = {fReader, "REC_Scintillator_sector"};
   TTreeReaderArray<int> REC_Scintillator_layer = {fReader, "REC_Scintillator_layer"};
   TTreeReaderArray<int> REC_Scintillator_component = {fReader, "REC_Scintillator_component"};
   TTreeReaderArray<float> REC_Scintillator_energy = {fReader, "REC_Scintillator_energy"};
   TTreeReaderArray<float> REC_Scintillator_time = {fReader, "REC_Scintillator_time"};
   TTreeReaderArray<float> REC_Scintillator_path = {fReader, "REC_Scintillator_path"};
   TTreeReaderArray<int> REC_Track_pindex = {fReader, "REC_Track_pindex"};
   TTreeReaderArray<int> REC_Track_detector = {fReader, "REC_Track_detector"};
   TTreeReaderArray<int> REC_Track_sector = {fReader, "REC_Track_sector"};
   TTreeReaderArray<float> REC_Track_chi2 = {fReader, "REC_Track_chi2"};
   TTreeReaderArray<int> REC_Track_NDF = {fReader, "REC_Track_NDF"};
   TTreeReaderArray<float> REC_Track_chi2_nomm = {fReader, "REC_Track_chi2_nomm"};
   TTreeReaderArray<int> REC_Track_NDF_nomm = {fReader, "REC_Track_NDF_nomm"};
   TTreeReaderArray<int> REC_Traj_pindex = {fReader, "REC_Traj_pindex"};
   TTreeReaderArray<int> REC_Traj_detId = {fReader, "REC_Traj_detId"};
   TTreeReaderArray<float> REC_Traj_x = {fReader, "REC_Traj_x"};
   TTreeReaderArray<float> REC_Traj_y = {fReader, "REC_Traj_y"};
   TTreeReaderArray<float> REC_Traj_z = {fReader, "REC_Traj_z"};
   TTreeReaderArray<float> REC_Traj_cx = {fReader, "REC_Traj_cx"};
   TTreeReaderArray<float> REC_Traj_cy = {fReader, "REC_Traj_cy"};
   TTreeReaderArray<float> REC_Traj_cz = {fReader, "REC_Traj_cz"};


   c12epx(TTree * /*tree*/ =0) { }
   virtual ~c12epx() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(c12epx,0);

};

#endif

#ifdef c12epx_cxx
void c12epx::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t c12epx::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef c12epx_cxx
