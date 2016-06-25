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

    void reset() { TreeInterface::singleton()->reset(); }
    bool pass(Event const&);

  private:
    class TreeInterface {
    public:
      void reset();
      bool initRun(Event const&);
      unsigned& index(char const* path);

      static TreeInterface* singleton();

    private:
      TreeInterface() {}
      ~TreeInterface() {}

      unsigned currentRun_{0};
      int currentTreeNumber_{-1};
      unsigned currentMenuIndex_{0xffffffff};

      std::map<unsigned, unsigned> runToMenuIndex_{};
      std::vector<std::vector<TString>> menus_{};

      std::map<TString, unsigned> pathIndices_{};
    };

    unsigned* index_{0};
  };
}

#endif
