// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIlocaldIyiiyamadIcmsswdI042dICMSSW_7_4_6dIsrcdIMitFlatdIDataFormatsdIsrcdIsimpletree_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

// Header files passed via #pragma extra_include

namespace simpletree {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *simpletree_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("simpletree", 0 /*version*/, "MitFlat/DataFormats/interface/Objects_simpletree.h", 11,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &simpletree_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *simpletree_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static TClass *simpletreecLcLParticle_Dictionary();
   static void simpletreecLcLParticle_TClassManip(TClass*);
   static void delete_simpletreecLcLParticle(void *p);
   static void deleteArray_simpletreecLcLParticle(void *p);
   static void destruct_simpletreecLcLParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Particle*)
   {
      ::simpletree::Particle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Particle));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Particle", "MitFlat/DataFormats/interface/Objects_simpletree.h", 30,
                  typeid(::simpletree::Particle), DefineBehavior(ptr, ptr),
                  &simpletreecLcLParticle_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Particle) );
      instance.SetDelete(&delete_simpletreecLcLParticle);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLParticle);
      instance.SetDestructor(&destruct_simpletreecLcLParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Particle*)
   {
      return GenerateInitInstanceLocal((::simpletree::Particle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Particle*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Particle*)0x0)->GetClass();
      simpletreecLcLParticle_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLParticleM_Dictionary();
   static void simpletreecLcLParticleM_TClassManip(TClass*);
   static void delete_simpletreecLcLParticleM(void *p);
   static void deleteArray_simpletreecLcLParticleM(void *p);
   static void destruct_simpletreecLcLParticleM(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::ParticleM*)
   {
      ::simpletree::ParticleM *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::ParticleM));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::ParticleM", "MitFlat/DataFormats/interface/Objects_simpletree.h", 57,
                  typeid(::simpletree::ParticleM), DefineBehavior(ptr, ptr),
                  &simpletreecLcLParticleM_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::ParticleM) );
      instance.SetDelete(&delete_simpletreecLcLParticleM);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLParticleM);
      instance.SetDestructor(&destruct_simpletreecLcLParticleM);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::ParticleM*)
   {
      return GenerateInitInstanceLocal((::simpletree::ParticleM*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::ParticleM*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLParticleM_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::ParticleM*)0x0)->GetClass();
      simpletreecLcLParticleM_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLParticleM_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLJet_Dictionary();
   static void simpletreecLcLJet_TClassManip(TClass*);
   static void delete_simpletreecLcLJet(void *p);
   static void deleteArray_simpletreecLcLJet(void *p);
   static void destruct_simpletreecLcLJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Jet*)
   {
      ::simpletree::Jet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Jet));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Jet", "MitFlat/DataFormats/interface/Objects_simpletree.h", 78,
                  typeid(::simpletree::Jet), DefineBehavior(ptr, ptr),
                  &simpletreecLcLJet_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Jet) );
      instance.SetDelete(&delete_simpletreecLcLJet);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLJet);
      instance.SetDestructor(&destruct_simpletreecLcLJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Jet*)
   {
      return GenerateInitInstanceLocal((::simpletree::Jet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Jet*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLJet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Jet*)0x0)->GetClass();
      simpletreecLcLJet_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLJet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLMet_Dictionary();
   static void simpletreecLcLMet_TClassManip(TClass*);
   static void delete_simpletreecLcLMet(void *p);
   static void deleteArray_simpletreecLcLMet(void *p);
   static void destruct_simpletreecLcLMet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Met*)
   {
      ::simpletree::Met *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Met));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Met", "MitFlat/DataFormats/interface/Objects_simpletree.h", 89,
                  typeid(::simpletree::Met), DefineBehavior(ptr, ptr),
                  &simpletreecLcLMet_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Met) );
      instance.SetDelete(&delete_simpletreecLcLMet);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLMet);
      instance.SetDestructor(&destruct_simpletreecLcLMet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Met*)
   {
      return GenerateInitInstanceLocal((::simpletree::Met*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Met*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLMet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Met*)0x0)->GetClass();
      simpletreecLcLMet_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLMet_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLIsolatable_Dictionary();
   static void simpletreecLcLIsolatable_TClassManip(TClass*);
   static void delete_simpletreecLcLIsolatable(void *p);
   static void deleteArray_simpletreecLcLIsolatable(void *p);
   static void destruct_simpletreecLcLIsolatable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Isolatable*)
   {
      ::simpletree::Isolatable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Isolatable));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Isolatable", "MitFlat/DataFormats/interface/Objects_simpletree.h", 112,
                  typeid(::simpletree::Isolatable), DefineBehavior(ptr, ptr),
                  &simpletreecLcLIsolatable_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Isolatable) );
      instance.SetDelete(&delete_simpletreecLcLIsolatable);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLIsolatable);
      instance.SetDestructor(&destruct_simpletreecLcLIsolatable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Isolatable*)
   {
      return GenerateInitInstanceLocal((::simpletree::Isolatable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Isolatable*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLIsolatable_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Isolatable*)0x0)->GetClass();
      simpletreecLcLIsolatable_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLIsolatable_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLPhoton_Dictionary();
   static void simpletreecLcLPhoton_TClassManip(TClass*);
   static void delete_simpletreecLcLPhoton(void *p);
   static void deleteArray_simpletreecLcLPhoton(void *p);
   static void destruct_simpletreecLcLPhoton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Photon*)
   {
      ::simpletree::Photon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Photon));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Photon", "MitFlat/DataFormats/interface/Objects_simpletree.h", 145,
                  typeid(::simpletree::Photon), DefineBehavior(ptr, ptr),
                  &simpletreecLcLPhoton_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Photon) );
      instance.SetDelete(&delete_simpletreecLcLPhoton);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLPhoton);
      instance.SetDestructor(&destruct_simpletreecLcLPhoton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Photon*)
   {
      return GenerateInitInstanceLocal((::simpletree::Photon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Photon*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLPhoton_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Photon*)0x0)->GetClass();
      simpletreecLcLPhoton_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLPhoton_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLLepton_Dictionary();
   static void simpletreecLcLLepton_TClassManip(TClass*);
   static void delete_simpletreecLcLLepton(void *p);
   static void deleteArray_simpletreecLcLLepton(void *p);
   static void destruct_simpletreecLcLLepton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Lepton*)
   {
      ::simpletree::Lepton *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Lepton));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Lepton", "MitFlat/DataFormats/interface/Objects_simpletree.h", 194,
                  typeid(::simpletree::Lepton), DefineBehavior(ptr, ptr),
                  &simpletreecLcLLepton_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Lepton) );
      instance.SetDelete(&delete_simpletreecLcLLepton);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLLepton);
      instance.SetDestructor(&destruct_simpletreecLcLLepton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Lepton*)
   {
      return GenerateInitInstanceLocal((::simpletree::Lepton*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Lepton*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLLepton_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Lepton*)0x0)->GetClass();
      simpletreecLcLLepton_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLLepton_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLElectron_Dictionary();
   static void simpletreecLcLElectron_TClassManip(TClass*);
   static void delete_simpletreecLcLElectron(void *p);
   static void deleteArray_simpletreecLcLElectron(void *p);
   static void destruct_simpletreecLcLElectron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Electron*)
   {
      ::simpletree::Electron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Electron));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Electron", "MitFlat/DataFormats/interface/Objects_simpletree.h", 221,
                  typeid(::simpletree::Electron), DefineBehavior(ptr, ptr),
                  &simpletreecLcLElectron_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Electron) );
      instance.SetDelete(&delete_simpletreecLcLElectron);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLElectron);
      instance.SetDestructor(&destruct_simpletreecLcLElectron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Electron*)
   {
      return GenerateInitInstanceLocal((::simpletree::Electron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Electron*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLElectron_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Electron*)0x0)->GetClass();
      simpletreecLcLElectron_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLElectron_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLMuon_Dictionary();
   static void simpletreecLcLMuon_TClassManip(TClass*);
   static void delete_simpletreecLcLMuon(void *p);
   static void deleteArray_simpletreecLcLMuon(void *p);
   static void destruct_simpletreecLcLMuon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Muon*)
   {
      ::simpletree::Muon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Muon));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Muon", "MitFlat/DataFormats/interface/Objects_simpletree.h", 261,
                  typeid(::simpletree::Muon), DefineBehavior(ptr, ptr),
                  &simpletreecLcLMuon_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Muon) );
      instance.SetDelete(&delete_simpletreecLcLMuon);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLMuon);
      instance.SetDestructor(&destruct_simpletreecLcLMuon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Muon*)
   {
      return GenerateInitInstanceLocal((::simpletree::Muon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Muon*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLMuon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Muon*)0x0)->GetClass();
      simpletreecLcLMuon_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLMuon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLHLT_Dictionary();
   static void simpletreecLcLHLT_TClassManip(TClass*);
   static void delete_simpletreecLcLHLT(void *p);
   static void deleteArray_simpletreecLcLHLT(void *p);
   static void destruct_simpletreecLcLHLT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::HLT*)
   {
      ::simpletree::HLT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::HLT));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::HLT", "MitFlat/DataFormats/interface/Objects_simpletree.h", 284,
                  typeid(::simpletree::HLT), DefineBehavior(ptr, ptr),
                  &simpletreecLcLHLT_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::HLT) );
      instance.SetDelete(&delete_simpletreecLcLHLT);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLHLT);
      instance.SetDestructor(&destruct_simpletreecLcLHLT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::HLT*)
   {
      return GenerateInitInstanceLocal((::simpletree::HLT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::HLT*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLHLT_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::HLT*)0x0)->GetClass();
      simpletreecLcLHLT_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLHLT_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)
   {
      ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >","simpletree::ParticleCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)
   {
      ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >","simpletree::ParticleMCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >","simpletree::JetCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)
   {
      ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >","simpletree::IsolatableCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >","simpletree::PhotonCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >","simpletree::LeptonCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)
   {
      ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >","simpletree::ElectronCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)
   {
      ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >","simpletree::MuonCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_Dictionary();
   static void flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_TClassManip(TClass*);
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p = 0);
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(Long_t size, void *p);
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p);
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p);
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)
   {
      ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >));
      static ::ROOT::TGenericClassInfo 
         instance("flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >", "MitFlat/DataFormats/interface/Collection.h", 40,
                  typeid(::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >), DefineBehavior(ptr, ptr),
                  &flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >) );
      instance.SetNew(&new_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR);
      instance.SetNewArray(&newArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR);
      instance.SetDelete(&delete_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR);
      instance.SetDeleteArray(&deleteArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR);
      instance.SetDestructor(&destruct_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR);

      ROOT::AddClassAlternate("flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >","simpletree::HLTCollection");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)
   {
      return GenerateInitInstanceLocal((::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)0x0)->GetClass();
      flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLEvent_Dictionary();
   static void simpletreecLcLEvent_TClassManip(TClass*);
   static void *new_simpletreecLcLEvent(void *p = 0);
   static void *newArray_simpletreecLcLEvent(Long_t size, void *p);
   static void delete_simpletreecLcLEvent(void *p);
   static void deleteArray_simpletreecLcLEvent(void *p);
   static void destruct_simpletreecLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Event*)
   {
      ::simpletree::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Event));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Event", "MitFlat/DataFormats/interface/TreeEntries_simpletree.h", 18,
                  typeid(::simpletree::Event), DefineBehavior(ptr, ptr),
                  &simpletreecLcLEvent_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Event) );
      instance.SetNew(&new_simpletreecLcLEvent);
      instance.SetNewArray(&newArray_simpletreecLcLEvent);
      instance.SetDelete(&delete_simpletreecLcLEvent);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLEvent);
      instance.SetDestructor(&destruct_simpletreecLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Event*)
   {
      return GenerateInitInstanceLocal((::simpletree::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Event*)0x0)->GetClass();
      simpletreecLcLEvent_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *simpletreecLcLWeight_Dictionary();
   static void simpletreecLcLWeight_TClassManip(TClass*);
   static void *new_simpletreecLcLWeight(void *p = 0);
   static void *newArray_simpletreecLcLWeight(Long_t size, void *p);
   static void delete_simpletreecLcLWeight(void *p);
   static void deleteArray_simpletreecLcLWeight(void *p);
   static void destruct_simpletreecLcLWeight(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::simpletree::Weight*)
   {
      ::simpletree::Weight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::simpletree::Weight));
      static ::ROOT::TGenericClassInfo 
         instance("simpletree::Weight", "MitFlat/DataFormats/interface/TreeEntries_simpletree.h", 61,
                  typeid(::simpletree::Weight), DefineBehavior(ptr, ptr),
                  &simpletreecLcLWeight_Dictionary, isa_proxy, 0,
                  sizeof(::simpletree::Weight) );
      instance.SetNew(&new_simpletreecLcLWeight);
      instance.SetNewArray(&newArray_simpletreecLcLWeight);
      instance.SetDelete(&delete_simpletreecLcLWeight);
      instance.SetDeleteArray(&deleteArray_simpletreecLcLWeight);
      instance.SetDestructor(&destruct_simpletreecLcLWeight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::simpletree::Weight*)
   {
      return GenerateInitInstanceLocal((::simpletree::Weight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::simpletree::Weight*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *simpletreecLcLWeight_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::simpletree::Weight*)0x0)->GetClass();
      simpletreecLcLWeight_TClassManip(theClass);
   return theClass;
   }

   static void simpletreecLcLWeight_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLParticle(void *p) {
      delete ((::simpletree::Particle*)p);
   }
   static void deleteArray_simpletreecLcLParticle(void *p) {
      delete [] ((::simpletree::Particle*)p);
   }
   static void destruct_simpletreecLcLParticle(void *p) {
      typedef ::simpletree::Particle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Particle

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLParticleM(void *p) {
      delete ((::simpletree::ParticleM*)p);
   }
   static void deleteArray_simpletreecLcLParticleM(void *p) {
      delete [] ((::simpletree::ParticleM*)p);
   }
   static void destruct_simpletreecLcLParticleM(void *p) {
      typedef ::simpletree::ParticleM current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::ParticleM

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLJet(void *p) {
      delete ((::simpletree::Jet*)p);
   }
   static void deleteArray_simpletreecLcLJet(void *p) {
      delete [] ((::simpletree::Jet*)p);
   }
   static void destruct_simpletreecLcLJet(void *p) {
      typedef ::simpletree::Jet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Jet

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLMet(void *p) {
      delete ((::simpletree::Met*)p);
   }
   static void deleteArray_simpletreecLcLMet(void *p) {
      delete [] ((::simpletree::Met*)p);
   }
   static void destruct_simpletreecLcLMet(void *p) {
      typedef ::simpletree::Met current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Met

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLIsolatable(void *p) {
      delete ((::simpletree::Isolatable*)p);
   }
   static void deleteArray_simpletreecLcLIsolatable(void *p) {
      delete [] ((::simpletree::Isolatable*)p);
   }
   static void destruct_simpletreecLcLIsolatable(void *p) {
      typedef ::simpletree::Isolatable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Isolatable

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLPhoton(void *p) {
      delete ((::simpletree::Photon*)p);
   }
   static void deleteArray_simpletreecLcLPhoton(void *p) {
      delete [] ((::simpletree::Photon*)p);
   }
   static void destruct_simpletreecLcLPhoton(void *p) {
      typedef ::simpletree::Photon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Photon

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLLepton(void *p) {
      delete ((::simpletree::Lepton*)p);
   }
   static void deleteArray_simpletreecLcLLepton(void *p) {
      delete [] ((::simpletree::Lepton*)p);
   }
   static void destruct_simpletreecLcLLepton(void *p) {
      typedef ::simpletree::Lepton current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Lepton

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLElectron(void *p) {
      delete ((::simpletree::Electron*)p);
   }
   static void deleteArray_simpletreecLcLElectron(void *p) {
      delete [] ((::simpletree::Electron*)p);
   }
   static void destruct_simpletreecLcLElectron(void *p) {
      typedef ::simpletree::Electron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Electron

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLMuon(void *p) {
      delete ((::simpletree::Muon*)p);
   }
   static void deleteArray_simpletreecLcLMuon(void *p) {
      delete [] ((::simpletree::Muon*)p);
   }
   static void destruct_simpletreecLcLMuon(void *p) {
      typedef ::simpletree::Muon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Muon

namespace ROOT {
   // Wrapper around operator delete
   static void delete_simpletreecLcLHLT(void *p) {
      delete ((::simpletree::HLT*)p);
   }
   static void deleteArray_simpletreecLcLHLT(void *p) {
      delete [] ((::simpletree::HLT*)p);
   }
   static void destruct_simpletreecLcLHLT(void *p) {
      typedef ::simpletree::HLT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::HLT

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > : new ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >[nElements] : new ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > : new ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >[nElements] : new ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > : new ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements] : new ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLJetcOflatutilscLcLCollectionlEsimpletreecLcLParticleMcOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > : new ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >[nElements] : new ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > : new ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements] : new ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLPhotoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > : new ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements] : new ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > : new ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >[nElements] : new ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLElectroncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > : new ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >[nElements] : new ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLMuoncOflatutilscLcLCollectionlEsimpletreecLcLLeptoncOflatutilscLcLCollectionlEsimpletreecLcLIsolatablecOflatutilscLcLCollectionlEsimpletreecLcLParticlecOflatutilscLcLBaseCollectionlEfalsegRsPgRsPgRsPgRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> > : new ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >;
   }
   static void *newArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >[nElements] : new ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p) {
      delete ((::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)p);
   }
   static void deleteArray_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p) {
      delete [] ((::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >*)p);
   }
   static void destruct_flatutilscLcLCollectionlEsimpletreecLcLHLTcOflatutilscLcLBaseCollectionlEtruegRsPgR(void *p) {
      typedef ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >

namespace ROOT {
   // Wrappers around operator new
   static void *new_simpletreecLcLEvent(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::simpletree::Event : new ::simpletree::Event;
   }
   static void *newArray_simpletreecLcLEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::simpletree::Event[nElements] : new ::simpletree::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_simpletreecLcLEvent(void *p) {
      delete ((::simpletree::Event*)p);
   }
   static void deleteArray_simpletreecLcLEvent(void *p) {
      delete [] ((::simpletree::Event*)p);
   }
   static void destruct_simpletreecLcLEvent(void *p) {
      typedef ::simpletree::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Event

namespace ROOT {
   // Wrappers around operator new
   static void *new_simpletreecLcLWeight(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::simpletree::Weight : new ::simpletree::Weight;
   }
   static void *newArray_simpletreecLcLWeight(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::simpletree::Weight[nElements] : new ::simpletree::Weight[nElements];
   }
   // Wrapper around operator delete
   static void delete_simpletreecLcLWeight(void *p) {
      delete ((::simpletree::Weight*)p);
   }
   static void deleteArray_simpletreecLcLWeight(void *p) {
      delete [] ((::simpletree::Weight*)p);
   }
   static void destruct_simpletreecLcLWeight(void *p) {
      typedef ::simpletree::Weight current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::simpletree::Weight

namespace {
  void TriggerDictionaryInitialization_simpletree_Dict_Impl() {
    static const char* headers[] = {
"MitFlat/DataFormats/interface/Objects_simpletree.h",
"MitFlat/DataFormats/interface/TreeEntries_simpletree.h",
0
    };
    static const char* includePaths[] = {
"/local/yiiyama/cmssw/042/CMSSW_7_4_6/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd4/include",
"/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Particle;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  ParticleM;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Jet;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Met;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Isolatable;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Photon;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Lepton;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Electron;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Muon;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  HLT;}
namespace flatutils{template <Bool_t F> class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  BaseCollection;
}
namespace flatutils{template <class T, class B> class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Collection;
}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Event;}
namespace simpletree{class __attribute__((annotate("$clingAutoload$/local/yiiyama/cmssw/042/CMSSW_7_4_6/src/MitFlat/DataFormats/interface/simpletree_LinkDef.h")))  Weight;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"flatutils::Collection<simpletree::Electron,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >", payloadCode, "@",
"flatutils::Collection<simpletree::HLT,flatutils::BaseCollection<true> >", payloadCode, "@",
"flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >", payloadCode, "@",
"flatutils::Collection<simpletree::Jet,flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", payloadCode, "@",
"flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", payloadCode, "@",
"flatutils::Collection<simpletree::Muon,flatutils::Collection<simpletree::Lepton,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > > >", payloadCode, "@",
"flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> >", payloadCode, "@",
"flatutils::Collection<simpletree::ParticleM,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > >", payloadCode, "@",
"flatutils::Collection<simpletree::Photon,flatutils::Collection<simpletree::Isolatable,flatutils::Collection<simpletree::Particle,flatutils::BaseCollection<false> > > >", payloadCode, "@",
"simpletree::Electron", payloadCode, "@",
"simpletree::ElectronCollection", payloadCode, "@",
"simpletree::Event", payloadCode, "@",
"simpletree::HLT", payloadCode, "@",
"simpletree::HLTCollection", payloadCode, "@",
"simpletree::HLTPath", payloadCode, "@",
"simpletree::Isolatable", payloadCode, "@",
"simpletree::IsolatableCollection", payloadCode, "@",
"simpletree::Jet", payloadCode, "@",
"simpletree::JetCollection", payloadCode, "@",
"simpletree::Lepton", payloadCode, "@",
"simpletree::LeptonCollection", payloadCode, "@",
"simpletree::Met", payloadCode, "@",
"simpletree::Muon", payloadCode, "@",
"simpletree::MuonCollection", payloadCode, "@",
"simpletree::Particle", payloadCode, "@",
"simpletree::ParticleCollection", payloadCode, "@",
"simpletree::ParticleM", payloadCode, "@",
"simpletree::ParticleMCollection", payloadCode, "@",
"simpletree::Photon", payloadCode, "@",
"simpletree::PhotonCollection", payloadCode, "@",
"simpletree::Weight", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("simpletree_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_simpletree_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_simpletree_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_simpletree_Dict() {
  TriggerDictionaryInitialization_simpletree_Dict_Impl();
}
