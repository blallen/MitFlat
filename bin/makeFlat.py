#!/usr/bin/env python

from argparse import ArgumentParser
import re
import os

def isSimple(code):
    return len(code) == 1 and code in 'CBbSsIiLlFDO'

def branchType(code):
    if code == 'C':
        return 'Text_t const*'
    elif code == 'B':
        return 'Char_t'
    elif code == 'b':
        return 'UChar_t'
    elif code == 'S':
        return 'Short_t'
    elif code == 's':
        return 'UShort_t'
    elif code == 'I':
        return 'Int_t'
    elif code == 'i':
        return 'UInt_t'
    elif code == 'L':
        return 'Long64_t'
    elif code == 'l':
        return 'ULong64_t'
    elif code == 'F':
        return 'Float_t'
    elif code == 'D':
        return 'Double_t'
    elif code == 'O':
        return 'Bool_t'
    else: # object type
        return code


PACKAGE = 'MitFlat/DataFormats'
FULLPATH = os.environ['CMSSW_BASE'] + '/src/' + PACKAGE

argParser = ArgumentParser(description = 'Generate C++ code for a flat tree')
argParser.add_argument('config', metavar = 'CONFIG')

args = argParser.parse_args()

objPat = re.compile('^\\[([A-Z][a-zA-Z0-9]+)(?:|\\:(SINGLE|MAX=.+|SIZE=.+|[A-Z][a-zA-Z0-9]+))\\]$')
brnPat = re.compile('^([a-zA-Z_][a-zA-Z0-9_]*)/(.+)$')
fncPat = re.compile('^.* +\\{.*return +[^;]+; *\\}$')
incPat = re.compile('#include [^ ]+$')
typedefPat = re.compile('typedef [^ ]+ [^ ]+$')
enumPat = re.compile('enum *([^ ]+) *\\{')
treePat = re.compile('^\\{([^\\}]+)\\}$')

includes = []
typedefs = []
enums = []
objs = [] # keep object declarations in order of appearance in the input
inheritance = {}
trees = []
defs = {}
sizes = {}
fixedSize = []
treeDefs = {}
currentTree = ''
currentObj = ''

namespace = os.path.basename(args.config)
namespace = namespace[:namespace.find('.')]

with open(args.config) as configFile:
    enclosure = ''

    for line in configFile:
        line = line.strip()

        if enclosure:
            if enclosure == 'enum':
                for elem in line.split(','):
                    elem = elem.strip()
                    if '}' in elem:
                        enclosure = ''
                        elem = elem[:elem.find('}')].strip()

                    if elem:
                        enums[-1][1].append(elem)

        elif objPat.match(line):
            matches = objPat.match(line)
            objName, colSpec = [matches.group(i) for i in range(1, 3)]
            currentObj = objName
            objs.append(currentObj)
            defs[currentObj] = ([], []) # branches and functions
            if colSpec:
                if colSpec == 'SINGLE':
                    sizes[currentObj] = 0
                elif colSpec.startswith('MAX=') or colSpec.startswith('SIZE='):
                    maxSize = colSpec.replace('MAX=', '').replace('SIZE=', '')
                    try:
                        sizes[currentObj] = int(maxSize)
                    except ValueError:
                        for name, enum in enums:
                            try:
                                sizes[currentObj] = enum.index(maxSize)
                                break
                            except ValueError:
                                pass

                        else:
                            raise RuntimeError('Undefined max size ' + maxSize)

                    if colSpec.startswith('SIZE='):
                        fixedSize.append(currentObj)
                        
                else: # base class given
                    inheritance[currentObj] = colSpec
            else:
                sizes[currentObj] = 32

        elif brnPat.match(line):
            matches = brnPat.match(line)
            brName, brType = [matches.group(i) for i in range(1, 3)]
            if currentObj:
                defs[currentObj][0].append((brName, brType))
            elif currentTree:
                treeDefs[currentTree][0].append((brName, brType))
            else:
                raise RuntimeError('Branch given with no context')

        elif fncPat.match(line):
            if currentObj:
                defs[currentObj][1].append(line)
            elif currentTree:
                treeDefs[currentTree][1].append(line)
            else:
                raise RuntimeError('Branch given with no context')

        elif incPat.match(line):
            includes.append(line)

        elif typedefPat.match(line):
            typedefs.append(line)

        elif enumPat.match(line):
            enclosure = 'enum'
            matches = enumPat.match(line)
            enums.append((matches.group(1), []))

        elif treePat.match(line):
            matches = treePat.match(line)
            treeName = matches.group(1)
            currentTree = treeName
            trees.append(currentTree)
            treeDefs[currentTree] = ([], [])
            currentObj = '' # no more object definitions

        else:
            if line and not line.startswith('%'):
                print 'Skipping unrecognized pattern:', line

if len(treeDefs) == 0:
    treeDefs['Event'] = ([('runNumber', 'i'), ('lumiNumber', 'i'), ('eventNumber', 'i'), ('weight', 'D')], [])

for obj in objs:
    if obj not in sizes and obj in inheritance:
        sizes[obj] = sizes[inheritance[obj]]


if not os.path.isdir(FULLPATH + '/interface'):
    os.makedirs(FULLPATH + '/interface')
if not os.path.isdir(FULLPATH + '/src'):
    os.makedirs(FULLPATH + '/src')
if not os.path.exists(FULLPATH + '/BuildFile.xml'):
    with open(FULLPATH + '/BuildFile.xml', 'w') as buildFile:
        buildFile.write('<use name="root"/>\n')
        buildFile.write('<export>\n')
        buildFile.write('  <lib name="1"/>\n')
        buildFile.write('</export>\n')


# Objects header
with open(FULLPATH + '/interface/Objects_' + namespace + '.h', 'w') as header:
    header.write('#ifndef Objects_' + namespace + '_h\n')
    header.write('#define Objects_' + namespace + '_h\n')
    for inc in includes:
        header.write(inc + '\n')

    header.write('#include "TString.h"\n')
    header.write('#include "Rtypes.h"\n')
    header.write('class TTree;\n\n')

    header.write('namespace ' + namespace + ' {\n\n')

    for typedef in typedefs:
        if not typedef.endswith(';'):
            typedef += ';'
        header.write('  ' + typedef + '\n')

    header.write('  typedef std::vector<void*> BranchList;\n\n')
    header.write('  Bool_t branchIn(void* bPtr, BranchList const&);\n')
    header.write('  void setStatusAndAddress(TTree&, TString const& bName, void* bPtr);\n\n')

    for name, enum in enums:
        header.write('  enum ' + name + ' {\n')
        for iK in range(len(enum) - 1):
            header.write('    ' + enum[iK] + ',\n')
        header.write('    ' + enum[-1] + '\n')
        header.write('  };\n')

    if len(enums) != 0:
        header.write('\n')

    for obj in objs:
        if sizes[obj] != 0:
            header.write('  class ' + obj + 'Collection;\n')

    for obj in objs:
        header.write('  class ' + obj)
        if obj in inheritance:
            header.write(' : public ' + inheritance[obj])
        header.write(' {\n')
        header.write('  public:\n')
        if sizes[obj] == 0:
            header.write('    ' + obj + '(TString const& name = "' + obj.lower() + '")')
            if obj in inheritance:
                header.write(' : ' + inheritance(obj) + '(name)')
            else:
                header.write(' : name_(name)')
            header.write(' {}\n')
            header.write('    virtual ~' + obj + '() {}\n')
            header.write('    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());\n')
            header.write('    virtual void setAddress(TTree&, BranchList const& = BranchList());\n')
            header.write('    virtual void book(TTree&, BranchList const& = BranchList());\n')
        else:
            header.write('    ' + obj + '(' + obj + 'Collection&, UInt_t idx);\n')
            header.write('    virtual ~' + obj + '() {}\n')

        header.write('    ' + obj + '& operator=(' + obj + ' const&);\n')
        header.write('\n')
        
        for func in defs[obj][1]:
            header.write('    ' + func + '\n')

        if len(defs[obj][1]):
            header.write('\n')

        for brName, brType in defs[obj][0]:
            if sizes[obj] == 0:
                header.write('    ' + branchType(brType) + ' ' + brName + ';\n')
            else:
                header.write('    ' + branchType(brType) + '& ' + brName + ';\n')

        if sizes[obj] == 0 and obj not in inheritance:
            header.write('  private:\n')
            header.write('    TString const name_;\n')

        header.write('  };\n\n')

    header.write('}\n\n')

    header.write('#endif\n')

# Collections header
with open(FULLPATH + '/interface/Collections_' + namespace + '.h', 'w') as header:
    header.write('#ifndef Collections_' + namespace + '_h\n')
    header.write('#define Collections_' + namespace + '_h\n')
    header.write('#include "' + PACKAGE + '/interface/Objects_' + namespace + '.h"\n')
    header.write('#include "' + PACKAGE + '/interface/Utils.h"\n\n')

    header.write('class TTree;\n\n')

    header.write('namespace ' + namespace + ' {\n\n')

    for obj in objs:
        if sizes[obj] == 0:
            continue

        header.write('  class ' + obj + 'Collection')
        if obj in inheritance:
            header.write(' : public ' + inheritance[obj] + 'Collection')
        header.write(' {\n')
        header.write('  public:\n')
        if obj not in inheritance:
            header.write('    static UInt_t const NMAX = ' + str(sizes[obj]) + ';\n')
        if obj in fixedSize:
            header.write('    static UInt_t const size = NMAX;\n')

        header.write('    typedef ' + namespace + '::' + obj + ' value_type;\n')
        header.write('    typedef value_type& reference;\n')
        header.write('    typedef value_type const& const_reference;\n')
        header.write('    typedef flatutils::iterator<' + obj + '> iterator;\n')
        header.write('    typedef flatutils::const_iterator<' + obj + '> const_iterator;\n\n')

        header.write('    ' + obj + 'Collection(TString const& name = "' + obj.lower() + 's");\n')
        header.write('    virtual ~' + obj + 'Collection();\n\n')

        header.write('    reference at(UInt_t idx);\n')
        header.write('    const_reference at(UInt_t idx) const;\n')
        header.write('    reference operator[](UInt_t);\n')
        header.write('    const_reference operator[](UInt_t) const;\n')
        header.write('    iterator begin() { return iterator(static_cast<' + obj + '*>(array_), objSize_); }\n')
        header.write('    const_iterator begin() const { return const_iterator(static_cast<' + obj + '*>(array_), objSize_); }\n')
        header.write('    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<' + obj + '*>(p), objSize_); }\n')
        header.write('    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<' + obj + '*>(p), objSize_); }\n')
        if obj not in fixedSize:
            header.write('    void push_back(const_reference);\n')
        if obj not in inheritance and obj not in fixedSize:
            header.write('    void clear() { resize(0); }\n')
            header.write('    void resize(UInt_t size);\n')

        header.write('\n')

        header.write('    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());\n')
        header.write('    virtual void setAddress(TTree&, BranchList const& = BranchList());\n')
        header.write('    virtual void book(TTree&, BranchList const& = BranchList());\n\n')

        if obj not in inheritance and obj not in fixedSize:
            header.write('    UInt_t size = 0;\n')

        for brName, brType in defs[obj][0]:
            header.write('    ' + branchType(brType) + ' ' + brName + '[NMAX] = {};\n')

        header.write('\n')
        header.write('  protected:\n')
        header.write('    ' + obj + 'Collection(TString const&, Bool_t);\n') # no-init version
        if obj not in inheritance: # derived classes use the base class array_
            header.write('    TString const name_;\n')
            header.write('    UInt_t objSize_{0};\n')
            header.write('    value_type* array_{0};\n')

        header.write('  };\n\n')

    header.write('}\n\n')
    header.write('#endif\n')

# Tree header
with open(FULLPATH + '/interface/TreeEntries_' + namespace + '.h', 'w') as header:
    header.write('#ifndef TreeEntries_' + namespace + '_h\n')
    header.write('#define TreeEntries_' + namespace + '_h\n')
    header.write('#include "' + PACKAGE + '/interface/Collections_' + namespace + '.h"\n\n')

    header.write('namespace ' + namespace + ' {\n\n')

    for tree in trees:
        header.write('  class ' + tree + ' {\n')
        header.write('  public:\n')
    
        for func in treeDefs[tree][1]:
            header.write('    ' + func + '\n')
        
        if len(treeDefs[tree][1]):
            header.write('\n')
    
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                header.write('    ' + branchType(brType) + ' ' + brName + '{};\n')

        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                header.write('    ' + branchType(brType) + ' ' + brName + ' = ' + branchType(brType) + '("' + brName + '");\n')
    
        header.write('\n')
        header.write('    void setStatus(TTree&, Bool_t, BranchList const& = BranchList());\n')
        header.write('    void setAddress(TTree&, BranchList const& = BranchList());\n')
        header.write('    void book(TTree&, BranchList const& = BranchList());\n')
        header.write('  };\n\n')

    header.write('}\n\n')
    header.write('#endif\n')

# Object source
with open(FULLPATH + '/src/Objects_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/Objects_' + namespace + '.h"\n\n')
    src.write('#include "' + PACKAGE + '/interface/Collections_' + namespace + '.h"\n\n')

    src.write('#include "TTree.h"\n\n')
    src.write('#include <algorithm>\n\n')

    src.write('Bool_t\n')
    src.write(namespace + '::branchIn(void* _bPtr, BranchList const& _bList)\n')
    src.write('{\n')
    src.write('  return _bList.size() == 0 || std::find(_bList.begin(), _bList.end(), _bPtr) != _bList.end();\n')
    src.write('}\n\n')

    src.write('void\n')
    src.write(namespace + '::setStatusAndAddress(TTree& _tree, TString const& _bName, void* _bPtr)\n')
    src.write('{\n')
    src.write('  if (!_tree.GetBranchStatus(_bName))\n')
    src.write('    _tree.SetBranchStatus(_bName, true);\n')
    src.write('  _tree.SetBranchAddress(_bName, _bPtr);\n')
    src.write('}\n\n')

    for obj in objs:
        if sizes[obj] == 0:
            src.write('void\n')
            src.write(namespace + '::' + obj + '::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setStatus(_tree, _status, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    _tree.SetBranchStatus(name_ + ".' + brName + '", _status);\n')
            src.write('}\n\n')

            src.write('void\n')
            src.write(namespace + '::' + obj + '::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setAddress(_tree, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    setStatusAndAddress(_tree, name_ + ".' + brName + '", &' + brName + ');\n')
            src.write('}\n\n')
    
            src.write('void\n')
            src.write(namespace + '::' + obj + '::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::book(_tree, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    _tree.Branch(name_ + ".' + brName + '", &' + brName + ', "' + brName + '/' + brType + '");\n')
            src.write('}\n\n')

        else:
            src.write(namespace + '::' + obj + '::' + obj + '(' + obj + 'Collection& col, UInt_t idx) :\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '(col, idx)')
                if len(defs[obj][0]) != 0:
                    src.write(',')
                src.write('\n')
            for iB, (brName, brType) in enumerate(defs[obj][0]):
                src.write('  ' + brName + '(col.' + brName + '[idx])')
                if iB == len(defs[obj][0]) - 1:
                    src.write('\n')
                else:
                    src.write(',\n')
    
            src.write('{\n}\n')

        src.write(namespace + '::' + obj + '&\n')
        src.write(namespace + '::' + obj + '::operator=(' + obj + ' const& _rhs)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + '::operator=(_rhs);\n\n')
        for brName, brType in defs[obj][0]:
            src.write('  ' + brName + ' = _rhs.' + brName + ';\n')
        src.write('\n')
        src.write('  return *this;\n')
        src.write('}\n\n')


# Collection source
with open(FULLPATH + '/src/Collections_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/Collections_' + namespace + '.h"\n')
    src.write('#include "TTree.h"\n')
    src.write('#include <stdexcept>\n')
    src.write('#include <memory>\n\n')

    for obj in objs:
        if sizes[obj] == 0:
            continue

        src.write(namespace + '::' + obj + 'Collection::' + obj + 'Collection(TString const& _name) :\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection(_name, kFALSE)\n')
        else:
            src.write('  name_(_name)\n')
        src.write('{\n')
        src.write('  objSize_ = sizeof(' + obj + ');\n')
        src.write('  array_ = std::allocator<' + obj + '>().allocate(NMAX);\n')
        src.write('  for (unsigned iP(0); iP != NMAX; ++iP)\n')
        src.write('    new (static_cast<' + obj + '*>(array_) + iP) ' + obj + '(*this, iP);\n')
        src.write('}\n\n')

        src.write('//protected\n')
        src.write(namespace + '::' + obj + 'Collection::' + obj + 'Collection(TString const& _name, Bool_t) :\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection(_name, kFALSE)\n')
        else:
            src.write('  name_(_name)\n')
        src.write('{\n}\n\n')

        src.write(namespace + '::' + obj + 'Collection::~' + obj + 'Collection()\n')
        src.write('{\n')
        src.write('  if (array_) {\n')
        src.write('    std::allocator<' + obj + '>().deallocate(static_cast<' + obj + '*>(array_), NMAX);\n')
        src.write('    array_ = 0;\n')
        src.write('  }\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::reference\n')
        src.write(namespace + '::' + obj + 'Collection::at(UInt_t _idx)\n')
        src.write('{\n')
        src.write('  if (_idx < size) {\n')
        src.write('    auto* p(array_);\n')
        src.write('    flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('    return *static_cast<' + obj + '*>(p);\n')
        src.write('  }\n\n')
        src.write('  throw std::out_of_range("' + obj + 'Collection::at");\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::const_reference\n')
        src.write(namespace + '::' + obj + 'Collection::at(UInt_t _idx) const\n')
        src.write('{\n')
        src.write('  if (_idx < size) {\n')
        src.write('    auto* p(array_);\n')
        src.write('    flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('    return *static_cast<' + obj + ' const*>(p);\n')
        src.write('  }\n\n')
        src.write('  throw std::out_of_range("' + obj + 'Collection::at");\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::reference\n')
        src.write(namespace + '::' + obj + 'Collection::operator[](UInt_t _idx)\n')
        src.write('{\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<' + obj + '*>(p);\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::const_reference\n')
        src.write(namespace + '::' + obj + 'Collection::operator[](UInt_t _idx) const\n')
        src.write('{\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<' + obj + ' const*>(p);\n')
        src.write('}\n\n')

        if obj not in fixedSize:
            src.write('void\n')
            src.write(namespace + '::' + obj + 'Collection::push_back(const_reference val)\n')
            src.write('{\n')
            src.write('  UInt_t current(size);\n')
            src.write('  resize(current + 1);\n')
            src.write('  array_[current] = val;\n')
            src.write('}\n\n')

        if obj not in inheritance and obj not in fixedSize:
            src.write('void\n')
            src.write(namespace + '::' + obj + 'Collection::resize(UInt_t _size)\n')
            src.write('{\n')
            src.write('  if (_size <= NMAX) {\n')
            src.write('    size = _size;\n')
            src.write('    return;\n')
            src.write('  }\n')
            src.write('  throw std::length_error("' + obj + 'Collection::resize");\n')
            src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::setStatus(_tree, _status, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  if (_branches.size() == 0 || _status)\n') # only set status of size branch if it's a "blanket" call
            src.write('    _tree.SetBranchStatus(name_ + ".size", _status);\n')

        for brName, brType in defs[obj][0]:
            src.write('  if (branchIn(&' + brName + ', _branches))\n')
            src.write('    _tree.SetBranchStatus(name_ + ".' + brName + '", _status);\n')
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::setAddress(_tree, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  setStatusAndAddress(_tree, name_ + ".size", &size);\n')

        for brName, brType in defs[obj][0]:
            src.write('  if (branchIn(&' + brName + ', _branches))\n')
            src.write('    setStatusAndAddress(_tree, name_ + ".' + brName + '", ' + brName + ');\n')
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::book(_tree, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  _tree.Branch(name_ + ".size", &size, "size/i");\n')

        for brName, brType in defs[obj][0]:
            if obj in fixedSize:
                sizeExpr = '[" + TString::Format("%d", NMAX) + "]'
            else:
                sizeExpr = '[" + name_ + ".size]'

            src.write('  if (branchIn(&' + brName + ', _branches))\n')
            src.write('    _tree.Branch(name_ + ".' + brName + '", ' + brName + ', "' + brName + sizeExpr + '/' + brType + '");\n')
        src.write('}\n\n')

# Tree source
with open(FULLPATH + '/src/TreeEntries_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/TreeEntries_' + namespace + '.h"\n')
    src.write('#include "TTree.h"\n\n')

    for tree in trees:
        src.write('void\n')
        src.write(namespace + '::' + tree + '::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    _tree.SetBranchStatus("' + brName + '", _status);\n')
    
        src.write('\n')
    
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    ' + brName + '.setStatus(_tree, _status);\n')
    
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + tree + '::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    setStatusAndAddress(_tree, "' + brName + '", &' + brName + ');\n')
    
        src.write('\n')
    
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    ' + brName + '.setAddress(_tree);\n')
    
        src.write('}\n\n')
    
        src.write('void\n')
        src.write(namespace + '::' + tree + '::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    _tree.Branch("' + brName + '", &' + brName + ', "' + brName + '/' + brType + '");\n')
    
        src.write('\n')
        
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  if (branchIn(&' + brName + ', _branches))\n')
                src.write('    ' + brName + '.book(_tree);\n')
    
        src.write('}\n\n')
