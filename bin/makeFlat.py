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

colObjs = filter(lambda x: sizes[x] != 0, objs)
singleObjs = filter(lambda x: sizes[x] == 0, objs)

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
    header.write('#include "Utils.h"\n')
    for inc in includes:
        header.write(inc + '\n')

    header.write('#include "TString.h"\n')
    header.write('#include "Rtypes.h"\n')
    header.write('class TTree;\n\n')

    header.write('namespace ' + namespace + ' {\n')

    if len(typedefs) != 0:
        for typedef in typedefs:
            if not typedef.endswith(';'):
                typedef += ';'
            header.write('\n  ' + typedef)

        header.write('\n')

    if len(enums) != 0:
        for name, enum in enums:
            header.write('\n  enum ' + name + ' {')
            for item in enum:
                header.write('\n    ' + item)
                if item != enum[-1]:
                    header.write(',')
            header.write('\n  };\n')

    for obj in objs:
        header.write('\n  class ' + obj)
        if obj in inheritance:
            header.write(' : public ' + inheritance[obj])
        header.write(' {')
        header.write('\n  public:')

        if obj in singleObjs:
            header.write('\n    ' + obj + '(TString const& name = "' + obj.lower() + '")')
            if obj in inheritance:
                header.write(' : ' + inheritance(obj) + '(name)')
            else:
                header.write(' : name_(name)')
            header.write(' {}')
        else:
            header.write('\n    struct array_data')
            if obj in inheritance:
                header.write(' : public typename ' + inheritance[obj] + '::array_data')
            header.write(' {')
            if obj not in inheritance:
                header.write('\n    static UInt_t const NMAX{' + sizes[obj] + '};\n')

            for brName, brType in defs[obj][0]:
                header.write('\n    ' + branchType(brType) + ' ' + brName + '[NMAX];')

            header.write('\n')
            header.write('\n    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});')
            header.write('\n    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});')
            header.write('\n    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});')
            header.write('\n};')

            header.write('\n    ' + obj + '(array_data&, UInt_t idx);')

        header.write('\n    ' + obj + '(' + obj + ' const&);')
        header.write('\n    virtual ~' + obj + '() {}')
        header.write('\n    ' + obj + '& operator=(' + obj + ' const&);')

        if obj in singleObjs:
            header.write('\n\n    void setName(TString const& name) { name_ = name; }')
            header.write('\n    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});')
            header.write('\n    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});')
            header.write('\n    virtual void book(TTree&, flatutils::BranchList const& = {"*"});')
        
        if len(defs[obj][1]) != 0:
            header.write('\n')

        for func in defs[obj][1]:
            header.write('\n    ' + func)

        if obj in singleObjs and obj not in inheritance:
            header.write('\n\n  protected:')
            header.write('\n    TString name_;')

        if len(defs[obj][0]) != 0:
            header.write('\n\n  public:')

        for brName, brType in defs[obj][0]:
            if obj in singleObjs:
                header.write('\n    ' + branchType(brType) + ' ' + brName + '{};')
            else:
                header.write('\n    ' + branchType(brType) + '& ' + brName + ';')

        header.write('\n  };\n')

    header.write('}\n\n')

    header.write('#endif\n')

# Tree header
with open(FULLPATH + '/interface/TreeEntries_' + namespace + '.h', 'w') as header:
    header.write('#ifndef TreeEntries_' + namespace + '_h\n')
    header.write('#define TreeEntries_' + namespace + '_h\n')
    header.write('#include "' + PACKAGE + '/interface/Collection.h"\n')
    header.write('#include "' + PACKAGE + '/interface/Objects_' + namespace + '.h"\n')

    header.write('namespace ' + namespace + ' {\n\n')

    if len(colObjs) != 0:
        for obj in colObjs:
            if obj in inheritance:
                base = inheritance[obj]
            elif obj in fixedSize:
                base = 'BaseCollection<kTRUE>'
            else:
                base = 'BaseCollection<kFALSE>'

            header.write('\n  typedef Collection<' + obj + ', ' + base + '> ' + obj + 'Collection;')

        header.write('\n')

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
        header.write('    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});\n')
        header.write('    void setAddress(TTree&, flatutils::BranchList const& = {"*"});\n')
        header.write('    void book(TTree&, flatutils::BranchList const& = {"*"});\n')
        header.write('  };\n\n')

    header.write('}\n\n')
    header.write('#endif\n')

# Objects source
with open(FULLPATH + '/src/Objects_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/Objects_' + namespace + '.h"\n')

    src.write('#include "TTree.h"\n\n')

    for obj in objs:
        if obj in singleObjs:
            src.write(namespace + '::' + obj + '::' + obj + '(' + obj + ' const& _src) :\n')
            if obj in inheritance:
                src.write('  ' + inheritance(obj) + '(_src)')
            else:
                src.write('  name_(_src.name_)')
            if len(defs[obj][0]) != 0:
                src.write(',')
            for brName, brType in defs[obj][0]:
                src.write('\n  ' + brName + '(_src.' + brName + ')')
                if brName != defs[obj][0][-1][0]:
                    src.write(',')
            src.write('\n{\n}\n\n')

            src.write('void\n')
            src.write(namespace + '::' + obj + '::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setStatus(_tree, _status, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::setStatus(_tree, name_, "' + brName + '", _status, _branches);\n')

            src.write('}\n\n')

            src.write('void\n')
            src.write(namespace + '::' + obj + '::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setAddress(_tree, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::setStatusAndAddress(_tree, name_, "' + brName + '", &' + brName + ', _branches);\n')
            src.write('}\n\n')
    
            src.write('void\n')
            src.write(namespace + '::' + obj + '::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::book(_tree, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::book(_tree, name_, "' + brName + '", "", \'' + brType + '\', &' + brName + ', _branches);\n')
            src.write('}\n\n')

        else:
            src.write('void\n')
            src.write(namespace + '::' + obj + '::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::array_data::setStatus(_tree, _name, _status, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::setStatus(_tree, _name, "' + brName + '", _status, _branches);\n')
            src.write('}\n\n') 

            src.write('void\n')
            src.write(namespace + '::' + obj + '::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::array_data::setAddress(_tree, _name, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::setStatusAndAddress(_tree, _name, "' + brName + '", ' + brName + ', _branches);\n')
            src.write('}\n\n')
    
            src.write('void\n')
            src.write(namespace + '::' + obj + '::array_data::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::array_data::book(_tree, _branches);\n\n')

            for brName, brType in defs[obj][0]:
                src.write('  flatutils::book(_tree, _name, "' + brName + '", "", \'' + brType + '\', ' + brName + ', _branches);\n')
            src.write('}\n\n')

            src.write(namespace + '::' + obj + '::' + obj + '(array_data& _data, UInt_t _idx) :')
            if obj in inheritance:
                src.write('\n  ' + inheritance[obj] + '(_data, _idx)')
                if len(defs[obj][0]) != 0:
                    src.write(',')
            for brName, brType in defs[obj][0]:
                src.write('\n  ' + brName + '(_data.' + brName + '[idx])')
                if brName != defs[obj][0][-1][0]:
                    src.write(',')
            src.write('\n{\n}\n\n')

            src.write(namespace + '::' + obj + '::' + obj + '(' + obj + ' const& _src) :')
            if obj in inheritance:
                src.write('\n  ' + inheritance[obj] + '(_src)')
                if len(defs[obj][0]) != 0:
                    src.write(',')
            for brName, brType in defs[obj][0]:
                src.write('\n  ' + brName + '(_src.' + brName + ')')
                if brName != defs[obj][0][-1][0]:
                    src.write(',')
            src.write('\n{\n}\n\n')

        src.write(namespace + '::' + obj + '&\n')
        src.write(namespace + '::' + obj + '::operator=(' + obj + ' const& _rhs)\n')
        src.write('{')
        if obj in inheritance:
            src.write('\n  ' + inheritance[obj] + '::operator=(_rhs);\n')
        for brName, brType in defs[obj][0]:
            src.write('\n  ' + brName + ' = _rhs.' + brName + ';')
        src.write('\n')
        src.write('  return *this;\n')
        src.write('}\n\n')


# Collection source
with open(FULLPATH + '/src/Collections_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/Collections_' + namespace + '.h"\n')
    src.write('#include "TTree.h"\n')
    src.write('#include <stdexcept>\n')
    src.write('#include <memory>\n\n')

    for obj in colObjs:
        src.write(namespace + '::' + obj + 'Collection::' + obj + 'Collection(TString const& _name) :\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection(_name, kFALSE)\n')
        else:
            src.write('  name_(_name)\n')
        src.write('{\n')
        src.write('  objSize_ = sizeof(value_type);\n')
        src.write('  array_ = std::allocator<value_type>().allocate(NMAX);\n')
        src.write('  auto* p(array_);\n')
        src.write('  for (unsigned iP(0); iP != NMAX; ++iP) {\n')
        src.write('    new (static_cast<pointer>(p)) value_type(*this, iP);\n')
        src.write('    flatutils::shiftAddr(p, objSize_);\n')
        src.write('  }\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::' + obj + 'Collection(' + obj + 'Collection const& _src) :\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection(_src.name_, kFALSE)\n')
        else:
            src.write('  name_(_src.name_)\n')
        src.write('{\n')
        src.write('  objSize_ = sizeof(value_type);\n')
        src.write('  array_ = std::allocator<value_type>().allocate(NMAX);\n')
        src.write('  auto* p(array_);\n')
        src.write('  for (unsigned iP(0); iP != NMAX; ++iP) {\n')
        src.write('    new (static_cast<pointer>(p)) value_type(*this, iP);\n')
        src.write('    static_cast<pointer>(p)->operator=(_src[iP]);\n')
        src.write('    flatutils::shiftAddr(p, objSize_);\n')
        src.write('  }\n')
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
        src.write('    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);\n')
        src.write('    array_ = 0;\n')
        src.write('  }\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection&\n')
        src.write(namespace + '::' + obj + 'Collection::operator=(self_type const& _rhs)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::operator=(_rhs);\n')
        else:
            src.write('  name_ = _rhs.name_;\n')
        src.write('  auto* p(array_);\n')
        src.write('  for (unsigned iP(0); iP != NMAX; ++iP) {\n')
        src.write('    static_cast<pointer>(p)->operator=(_rhs[iP]);\n')
        src.write('    flatutils::shiftAddr(p, objSize_);\n')
        src.write('  }\n')
        src.write('  return *this;\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::reference\n')
        src.write(namespace + '::' + obj + 'Collection::at(UInt_t _idx)\n')
        src.write('{\n')
        src.write('  if (_idx >= size)\n')
        src.write('    throw std::out_of_range("' + obj + 'Collection::at");\n\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<pointer>(p);\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::const_reference\n')
        src.write(namespace + '::' + obj + 'Collection::at(UInt_t _idx) const\n')
        src.write('{\n')
        src.write('  if (_idx < size)\n')
        src.write('    throw std::out_of_range("' + obj + 'Collection::at");\n\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<const_pointer>(p);\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::reference\n')
        src.write(namespace + '::' + obj + 'Collection::operator[](UInt_t _idx)\n')
        src.write('{\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<pointer>(p);\n')
        src.write('}\n\n')

        src.write(namespace + '::' + obj + 'Collection::const_reference\n')
        src.write(namespace + '::' + obj + 'Collection::operator[](UInt_t _idx) const\n')
        src.write('{\n')
        src.write('  auto* p(array_);\n')
        src.write('  flatutils::shiftAddr(p, _idx * objSize_);\n')
        src.write('  return *static_cast<const_pointer>(p);\n')
        src.write('}\n\n')

        if obj not in fixedSize:
            src.write('void\n')
            src.write(namespace + '::' + obj + 'Collection::push_back(const_reference val)\n')
            src.write('{\n')
            src.write('  if (size == NMAX)\n')
            src.write('    throw std::length_error("' + obj + 'Collection::push_back");\n\n')
            src.write('  auto* p(array_);\n')
            src.write('  flatutils::shiftAddr(p, size * objSize_);\n')
            src.write('  static_cast<pointer>(p)->operator=(val);\n')
            src.write('  ++size;\n')
            src.write('}\n\n')

        if obj not in inheritance and obj not in fixedSize:
            src.write('void\n')
            src.write(namespace + '::' + obj + 'Collection::resize(UInt_t _size)\n')
            src.write('{\n')
            src.write('  if (_size > NMAX)\n')
            src.write('    throw std::length_error("' + obj + 'Collection::resize");\n\n')
            src.write('  size = _size;\n')
            src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::setStatus(_tree, _status, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  if (_status || flatutils::branchIn("size", _branches))\n') # always set size branch status to true if any of the branches is going to be
            src.write('    _tree.SetBranchStatus(name_ + ".size", _status);\n')

        for brName, brType in defs[obj][0]:
            src.write('  flatutils::setStatus(_tree, name_, "' + brName + '", _status, _branches);\n')

        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::setAddress(_tree, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  flatutils::setStatusAndAddress(_tree, name_, "size", &size, {"size"});\n')

        for brName, brType in defs[obj][0]:
            src.write('  flatutils::setStatusAndAddress(_tree, name_, "' + brName + '", ' + brName + ', _branches);\n')
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + obj + 'Collection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        if obj in inheritance:
            src.write('  ' + inheritance[obj] + 'Collection::book(_tree, _branches);\n\n')
        elif obj not in fixedSize:
            src.write('  _tree.Branch(name_ + ".size", &size, "size/i");\n')

        for brName, brType in defs[obj][0]:
            if obj in fixedSize:
                sizeExpr = 'TString::Format("%d", NMAX)'
            else:
                sizeExpr = 'name_ + ".size"'

            src.write('  flatutils::book(_tree, name_, "' + brName + '", ' + sizeExpr + ', \'' + brType + '\', ' + brName + ', _branches);\n')

        src.write('}\n\n')

# Tree source
with open(FULLPATH + '/src/TreeEntries_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + PACKAGE + '/interface/TreeEntries_' + namespace + '.h"\n')
    src.write('#include "TTree.h"\n\n')

    for tree in trees:
        src.write('void\n')
        src.write(namespace + '::' + tree + '::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  flatutils::setStatus(_tree, "", "' + brName + '", _status, _branches);\n')
    
        src.write('\n')
    
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  ' + brName + '.setStatus(_tree, _status, flatutils::subBranchList(_branches, "' + brName + '"));\n')
    
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + tree + '::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  flatutils::setStatusAndAddress(_tree, "", "' + brName + '", &' + brName + ', _branches);\n')
    
        src.write('\n')
    
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  ' + brName + '.setAddress(_tree, flatutils::subBranchList(_branches, "' + brName + '"));\n')
    
        src.write('}\n\n')
    
        src.write('void\n')
        src.write(namespace + '::' + tree + '::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)\n')
        src.write('{\n')
        for brName, brType in treeDefs[tree][0]:
            if isSimple(brType):
                src.write('  flatutils::book(_tree, "", "' + brName + '", "", \'' + brType + '\', &' + brName + ', _branches);\n')
    
        src.write('\n')
        
        for brName, brType in treeDefs[tree][0]:
            if not isSimple(brType):
                src.write('  ' + brName + '.book(_tree, flatutils::subBranchList(_branches, "' + brName + '"));\n')
    
        src.write('}\n\n')
