#include "MitFlat/DataFormats/interface/Utils.h"

#include "TString.h"
#include "TObjArray.h"
#include "TTree.h"

#include <utility>

namespace flatutils {

  typedef std::vector<TString> BName;

  BName
  tokenizeBrName_(TString const& _name)
  {
    auto* parts(_name.Tokenize("."));

    BName bname;
    for (auto* s : *parts)
      bname.emplace_back(s->GetName());

    delete parts;

    return bname;
  }

  TString
  concatenateBrName_(BName const& _bname)
  {
    TString name;
    for (auto&& n : _bname)
      name += n + ".";

    if (name.Length() != 0)
      name.Remove(name.Length() - 1, 1);

    return name;
  }

  bool
  bnameMatch_(BName const& _rhs, BName const& _lhs)
  {
    if (_rhs.size() == 0 || _lhs.size() == 0)
      return false;

    bool match(false);
    unsigned iP(0);
    while (true) {
      if (iP == _rhs.size() - 1) {
        if (_rhs[iP] == _lhs[iP] || _rhs[iP] == "*" || (iP == _lhs.size() - 1 && _lhs[iP] == "*"))
          match = true;
        break;
      }
      if (iP == _lhs.size() - 1) {
        if (_lhs[iP] == _rhs[iP] || _lhs[iP] == "*")
          match = true;
        break;
      }
      if (_rhs[iP] != _lhs[iP] && _rhs[iP] != "*" && _lhs[iP] != "*")
        break;

      ++iP;
    }

    return match;
  }

}

Bool_t
flatutils::branchIn(TString const& _bName, BranchList const& _bList)
{
  // Branch names are always "relative to" the current object, i.e. not the full name
  // of the branch but whatever is after the "." of the current object name.
 
 if (_bList.size() == 0)
    return false;

  BName search(tokenizeBrName_(_bName));

  unsigned iB(0);
  for (; iB != _bList.size(); ++iB) {
    if (bnameMatch_(tokenizeBrName_(_bList[iB]), search))
      break;
  }

  return iB != _bList.size();
}

flatutils::BranchList
flatutils::subBranchList(BranchList const& _bList, TString const& _objName)
{
  BranchList list;

  for (auto&& b : _bList) {
    if (b.Length() == 0)
      continue;

    BName bname(tokenizeBrName_(b));
    if (bname[0] != "*" && bname[0] != _objName)
      continue;

    if (bname.size() == 1)
      bname.emplace_back("*");
    bname.erase(bname.begin());

    list.push_back(concatenateBrName_(bname));
  }

  return list;
}

Int_t
flatutils::setStatus(TTree& _tree, TString const& _objName, TString const& _bName, Bool_t _status, BranchList const& _bList)
{
  TString bFullName(_bName);
  if (_objName.Length() != 0)
    bFullName.Prepend(_objName + ".");

  if (!_tree.GetBranch(bFullName) || !branchIn(_bName, _bList))
    return -1;

  if (_tree.GetBranchStatus(bFullName) == _status)
    return 0;

  _tree.SetBranchStatus(bFullName, _status);
  return 1;
}

Int_t
flatutils::setStatusAndAddress(TTree& _tree, TString const& _objName, TString const& _bName, void* _bPtr, BranchList const& _bList)
{
  if (setStatus(_tree, _objName, _bName, true, _bList) == -1)
    return -1;

  TString bFullName(_bName);
  if (_objName.Length() != 0)
    bFullName.Prepend(_objName + ".");

  _tree.SetBranchAddress(bFullName, _bPtr);

  return 1;
}

Int_t 
flatutils::book(TTree& _tree, TString const& _objName, TString const& _bName, TString const& _size, char _lType, void* _bPtr, BranchList const& _bList)
{
  // bName: electrons.pt
  // size: electrons.size
  // lType: F

  if (!branchIn(_bName, _bList))
    return -1;

  TString bFullName(_bName);
  if (_objName.Length() != 0)
    bFullName.Prepend(_objName + ".");

  TString lExpr(_bName);
  if (_size.Length() != 0)
    lExpr += "[" + _size + "]";

  lExpr += "/";
  lExpr += _lType;

  _tree.Branch(bFullName, _bPtr, lExpr);

  return 0;
}
