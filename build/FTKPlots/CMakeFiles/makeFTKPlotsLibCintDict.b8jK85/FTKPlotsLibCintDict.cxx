// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME FTKPlotsLibCintDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "FTKPlots/FTKReader.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FTKReader(void *p = 0);
   static void *newArray_FTKReader(Long_t size, void *p);
   static void delete_FTKReader(void *p);
   static void deleteArray_FTKReader(void *p);
   static void destruct_FTKReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FTKReader*)
   {
      ::FTKReader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FTKReader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FTKReader", ::FTKReader::Class_Version(), "FTKPlots/FTKReader.h", 17,
                  typeid(::FTKReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FTKReader::Dictionary, isa_proxy, 4,
                  sizeof(::FTKReader) );
      instance.SetNew(&new_FTKReader);
      instance.SetNewArray(&newArray_FTKReader);
      instance.SetDelete(&delete_FTKReader);
      instance.SetDeleteArray(&deleteArray_FTKReader);
      instance.SetDestructor(&destruct_FTKReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FTKReader*)
   {
      return GenerateInitInstanceLocal((::FTKReader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FTKReader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FTKReader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FTKReader::Class_Name()
{
   return "FTKReader";
}

//______________________________________________________________________________
const char *FTKReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FTKReader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FTKReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FTKReader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FTKReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FTKReader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FTKReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FTKReader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FTKReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FTKReader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FTKReader::Class(),this);
   } else {
      R__b.WriteClassBuffer(FTKReader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FTKReader(void *p) {
      return  p ? new(p) ::FTKReader : new ::FTKReader;
   }
   static void *newArray_FTKReader(Long_t nElements, void *p) {
      return p ? new(p) ::FTKReader[nElements] : new ::FTKReader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FTKReader(void *p) {
      delete ((::FTKReader*)p);
   }
   static void deleteArray_FTKReader(void *p) {
      delete [] ((::FTKReader*)p);
   }
   static void destruct_FTKReader(void *p) {
      typedef ::FTKReader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FTKReader

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace {
  void TriggerDictionaryInitialization_libFTKPlotsLib_Impl() {
    static const char* headers[] = {
"FTKPlots/FTKReader.h",
0
    };
    static const char* includePaths[] = {
"/home/fscutti/FTKPlotter/source/FTKPlots",
"/home/fscutti/FTKPlotter/source/FTKPlots",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccess",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/CxxUtils",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainersInterfaces",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainers",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthLinksSA",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccessInterfaces",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODCore",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventFormat",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventInfo",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTracking",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/DetectorDescription/GeoPrimitives",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/EventPrimitives",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODBase",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTruth",
"/home/fscutti/FTKPlotter/source/FTKPlots",
"/home/fscutti/FTKPlotter/source/FTKPlots",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/EventLoop",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/RootCoreUtils",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/SampleHandler",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthToolSupport/AsgTools",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccessInterfaces",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccess",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainers",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainersInterfaces",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthLinksSA",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Control/CxxUtils",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODCore",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventFormat",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/AnaAlgorithm",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventInfo",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTracking",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/DetectorDescription/GeoPrimitives",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/EventPrimitives",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODBase",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTruth",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include",
"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.8/InstallArea/x86_64-slc6-gcc62-opt/include",
"/imports/home/fscutti/FTKPlotter/build/FTKPlots/CMakeFiles/makeFTKPlotsLibCintDict.b8jK85/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libFTKPlotsLib dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$FTKPlots/FTKReader.h")))  FTKReader;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libFTKPlotsLib dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef HAVE_PRETTY_FUNCTION
  #define HAVE_PRETTY_FUNCTION 1
#endif
#ifndef HAVE_64_BITS
  #define HAVE_64_BITS 1
#endif
#ifndef __IDENTIFIER_64BIT__
  #define __IDENTIFIER_64BIT__ 1
#endif
#ifndef ATLAS
  #define ATLAS 1
#endif
#ifndef ROOTCORE
  #define ROOTCORE 1
#endif
#ifndef XAOD_STANDALONE
  #define XAOD_STANDALONE 1
#endif
#ifndef XAOD_ANALYSIS
  #define XAOD_ANALYSIS 1
#endif
#ifndef ROOTCORE_RELEASE_SERIES
  #define ROOTCORE_RELEASE_SERIES 25
#endif
#ifndef PACKAGE_VERSION
  #define PACKAGE_VERSION "FTKPlots-00-00-00"
#endif
#ifndef PACKAGE_VERSION_UQ
  #define PACKAGE_VERSION_UQ FTKPlots-00-00-00
#endif
#ifndef USE_CMAKE
  #define USE_CMAKE 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "FTKPlots/FTKReader.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FTKReader", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libFTKPlotsLib",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libFTKPlotsLib_Impl, {{"namespace DataVector_detail { template <typename B1, typename B2, typename B3> class VirtBases; }", 1},{"template <typename T> class DataVectorBase;", 1},{"template <typename T, typename BASE> class DataVector;", 1},{"namespace DataVector_detail { template <typename T> class DVLEltBaseInit; }", 1}}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libFTKPlotsLib_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libFTKPlotsLib() {
  TriggerDictionaryInitialization_libFTKPlotsLib_Impl();
}
