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
    unsigned index() const { return *index_; }
    bool pass(Event const&);

    // Used when assigning indices by hand
    static void assignIndex(char const*, unsigned);

  private:
    // Used when reading paths from the input files
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

    // Used when path indices are assigned by hand
    static bool staticAssignment_;
    static std::map<TString, unsigned> indices_;

    unsigned* index_{0};
  };
}

#endif
