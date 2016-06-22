#ifndef SimpleTreeUtils_h
#define SimpleTreeUtils_h

#include "TreeEntries_simpletree.h"

#include "TString.h"
#include "TTree.h"

#include <vector>

namespace simpletree {
  class TriggerHelper {
  public:
    TriggerHelper(char const* path);

    bool pass(Event const&);

  private:
    class TreeInterface {
    public:
      bool initRun(Event const&);
      std::vector<TString> const* menu() const { return hltMenu_; }
      unsigned& index(char const* path);

      static TreeInterface* singleton();

    private:
      TreeInterface();
      ~TreeInterface();

      Run run_;
      int currentTreeNumber_{-1};
      TTree* hltTree_{0};
      unsigned hltTreeEntry_{0};
      std::vector<TString>* hltMenu_;

      std::map<TString, unsigned> pathIndices_;
    };

    unsigned* index_{0};
  };
}

#endif
