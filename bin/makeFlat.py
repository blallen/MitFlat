#!/usr/bin/env python

from argparse import ArgumentParser
import re
import os
import collections

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


argParser = ArgumentParser(description = 'Generate C++ code for a flat tree')
argParser.add_argument('config', metavar = 'CONFIG')
argParser.add_argument('-p', '--package', metavar = 'DIR', default = 'MitFlat/DataFormats')

args = argParser.parse_args()

FULLPATH = os.environ['CMSSW_BASE'] + '/src/' + args.package

objPat = re.compile('^\\[([A-Z][a-zA-Z0-9]+)(?:|\\:(SINGLE|MAX=.+|SIZE=.+|[A-Z][a-zA-Z0-9]+))\\]$')
brnPat = re.compile('^([a-zA-Z_][a-zA-Z0-9_]*)(|\\[[0-9]+\\])/(.+)$')
fncPat = re.compile('^.* +\\{.*return +[^;]+; *\\}$')
statPat = re.compile('^static .+$')
incPat = re.compile('#include [^ ]+$')
typedefPat = re.compile('typedef [^ ]+ [^ ]+$')
enumPat = re.compile('enum *([^ ]+) *\\{')
treePat = re.compile('^\\{([^\\}]+)\\}$')

ObjDef = collections.namedtuple('ObjDef', ['branches', 'functions', 'statics'])
BranchDef = collections.namedtuple('BranchDef', ['name', 'type', 'size'])

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
            defs[currentObj] = ObjDef([], [], [])
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
            brName, arrSize, brType = [matches.group(i) for i in range(1, 4)]
            if arrSize:
                size = int(arrSize[1:len(arrSize) - 1])
            else:
                size = 1
            if currentObj:
                defs[currentObj].branches.append(BranchDef(brName, brType, size))
            elif currentTree:
                treeDefs[currentTree].branches.append(BranchDef(brName, brType, size))
            else:
                raise RuntimeError('Branch given with no context')

        elif fncPat.match(line):
            if currentObj:
                defs[currentObj].functions.append(line)
            elif currentTree:
                treeDefs[currentTree].functions.append(line)
            else:
                raise RuntimeError('Function given with no context')

        elif statPat.match(line):
            if currentObj:
                defs[currentObj].statics.append(line)
            elif currentTree:
                treeDefs[currentTree].statics.append(line)
            else:
                raise RuntimeError('Static given with no context')

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
            treeDefs[currentTree] = ObjDef([], [], [])
            currentObj = '' # no more object definitions

        else:
            if line and not line.startswith('%'):
                print 'Skipping unrecognized pattern:', line

if len(treeDefs) == 0:
    treeDefs['Event'] = ObjDef([('runNumber', 'i'), ('lumiNumber', 'i'), ('eventNumber', 'i'), ('weight', 'D')], [], [])

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
    header.write('#include "MitFlat/DataFormats/interface/Utils.h"\n')
    for inc in includes:
        header.write(inc + '\n')

    header.write('#include "TString.h"\n')
    header.write('#include "Rtypes.h"\n')
    header.write('class TTree;\n\n')

    header.write('namespace ' + namespace + ' {\n')

    # typedefs
    if len(typedefs) != 0:
        for typedef in typedefs:
            if not typedef.endswith(';'):
                typedef += ';'
            header.write('\n  ' + typedef)

        header.write('\n')

    # define enums
    if len(enums) != 0:
        for name, items in enums:
            header.write('\n  enum ' + name + ' {')
            for item in items:
                header.write('\n    ' + item)
                if item != items[-1]:
                    header.write(',')
            header.write('\n  };\n')

    # define all objects
    for obj in objs:
        header.write('\n  class ' + obj)
        if obj in inheritance:
            header.write(' : public ' + inheritance[obj])
        header.write(' {')
        header.write('\n  public:')

        if len(defs[obj].statics) != 0:
            for st in defs[obj].statics:
                if not st.endswith(';'):
                    st += ';'
                header.write('\n    constexpr ' + st)

            header.write('\n')

        if obj in singleObjs:
            header.write('\n    ' + obj + '(TString const& name)')
            if obj in inheritance:
                header.write(' : ' + inheritance(obj) + '(name)')
            else:
                header.write(' : name_(name)')
            header.write(' {}')
        else:
            header.write('\n    struct array_data')
            if obj in inheritance:
                header.write(' : public ' + inheritance[obj] + '::array_data')
            header.write(' {')
            if obj not in inheritance:
                header.write('\n      static UInt_t const NMAX{' + str(sizes[obj]) + '};\n')

            if len(defs[obj].branches) != 0:
                for br in defs[obj].branches:
                    if br.size == 1:
                        header.write('\n      ' + branchType(br.type) + ' ' + br.name + '[NMAX]{};')
                    else:
                        header.write('\n      ' + branchType(br.type) + ' ' + br.name + '[NMAX][' + str(br.size) + ']{};')
                header.write('\n')
                header.write('\n      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
                header.write('\n      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
                header.write('\n      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')

            header.write('\n    };\n')

            header.write('\n    ' + obj + '(array_data&, UInt_t idx);')

        header.write('\n    ' + obj + '(' + obj + ' const&);')
        header.write('\n    virtual ~' + obj + '() {}')
        header.write('\n    ' + obj + '& operator=(' + obj + ' const&);')

        if obj in singleObjs:
            header.write('\n\n    void setName(TString const& name) { name_ = name; }')
            header.write('\n    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
            header.write('\n    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
            header.write('\n    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
        
        if len(defs[obj].functions) != 0:
            header.write('\n')

        for func in defs[obj].functions:
            header.write('\n    ' + func)

        if obj in singleObjs and obj not in inheritance:
            header.write('\n\n  protected:')
            header.write('\n    TString name_;')

        if len(defs[obj].branches) != 0:
            header.write('\n\n  public:')

        for br in defs[obj].branches:
            if obj in singleObjs:
                if br.size == 1:
                    header.write('\n    ' + branchType(br.type) + ' ' + br.name + '{};')
                else:
                    header.write('\n    ' + branchType(br.type) + ' ' + br.name + '[' + str(br.size) + ']{};')
            else:
                header.write('\n    ' + branchType(br.type) + '& ' + br.name + ';')

        header.write('\n  };\n')

    header.write('}\n\n')

    header.write('#endif\n')

# Tree header
with open(FULLPATH + '/interface/TreeEntries_' + namespace + '.h', 'w') as header:
    header.write('#ifndef TreeEntries_' + namespace + '_h\n')
    header.write('#define TreeEntries_' + namespace + '_h\n')
    header.write('#include "MitFlat/DataFormats/interface/Collection.h"\n')
    header.write('#include "' + args.package + '/interface/Objects_' + namespace + '.h"\n')

    header.write('\nnamespace ' + namespace + ' {\n')

    if len(colObjs) != 0:
        for obj in colObjs:
            if obj in inheritance:
                base = inheritance[obj] + 'Collection'
            elif obj in fixedSize:
                base = 'flatutils::BaseCollection<kTRUE>'
            else:
                base = 'flatutils::BaseCollection<kFALSE>'

            header.write('\n  typedef flatutils::Collection<' + obj + ', ' + base + '> ' + obj + 'Collection;')

        header.write('\n')

    for tree in trees:
        header.write('\n  class ' + tree + ' {')
        header.write('\n  public:')

        if len(treeDefs[tree].functions) != 0:    
            for func in treeDefs[tree].functions:
                header.write('\n    ' + func)
  
            header.write('\n')

        if len(treeDefs[tree].branches) != 0:
            for br in treeDefs[tree].branches:
                if isSimple(br.type):
                    if br.size == 1:
                        header.write('\n    ' + branchType(br.type) + ' ' + br.name + '{};')
                    else:
                        header.write('\n    ' + branchType(br.type) + ' ' + br.name + '[' + str(br.size) + ']{};')
    
            for br in treeDefs[tree].branches:
                if not isSimple(br.type):
                    header.write('\n    ' + branchType(br.type) + ' ' + br.name + ' = ' + branchType(br.type) + '("' + br.name + '");')
    
            header.write('\n')

        header.write('\n    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
        header.write('\n    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
        header.write('\n    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);')
        header.write('\n  };\n')

    if len(enums) != 0:
        for name, items in enums:
            header.write('\n  TTree* make' + name + 'Tree();')

        header.write('\n')

    header.write('\n}\n')
    header.write('\n#endif\n')

# Objects source
with open(FULLPATH + '/src/Objects_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + args.package + '/interface/Objects_' + namespace + '.h"\n')

    src.write('#include "TTree.h"\n\n')

    for obj in objs:
        if obj in singleObjs:
            # single objects

            src.write(namespace + '::' + obj + '::' + obj + '(' + obj + ' const& _src) :\n')
            if obj in inheritance:
                src.write('  ' + inheritance(obj) + '(_src)')
            else:
                src.write('  name_(_src.name_)')
            if len(defs[obj].branches) != 0:
                src.write(',')
            for br in defs[obj].branches:
                src.write('\n  ' + br.name + '(_src.' + br.name + ')')
                if br.name != defs[obj].branches[-1].name:
                    src.write(',')
            src.write('\n{\n}\n\n')

            src.write('void\n')
            src.write(namespace + '::' + obj + '::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setStatus(_tree, _status, _branches, _whitelist);\n\n')

            for br in defs[obj].branches:
                src.write('  flatutils::setStatus(_tree, name_, "' + br.name + '", _status, _branches, _whitelist);\n')

            src.write('}\n\n')

            src.write('void\n')
            src.write(namespace + '::' + obj + '::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::setAddress(_tree, _branches, _whitelist);\n\n')

            for br in defs[obj].branches:
                if br.size == 1:
                    src.write('  flatutils::setStatusAndAddress(_tree, name_, "' + br.name + '", &' + br.name + ', _branches, _whitelist);\n')
                else:
                    src.write('  flatutils::setStatusAndAddress(_tree, name_, "' + br.name + '", ' + br.name + ', _branches, _whitelist);\n')
            src.write('}\n\n')
    
            src.write('void\n')
            src.write(namespace + '::' + obj + '::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)\n')
            src.write('{\n')
            if obj in inheritance:
                src.write('  ' + inheritance[obj] + '::book(_tree, _branches, _whitelist);\n\n')

            for br in defs[obj].branches:
                if br.size == 1:
                    src.write('  flatutils::book(_tree, name_, "' + br.name + '", "", \'' + br.type + '\', &' + br.name + ', _branches, _whitelist);\n')
                else:
                    src.write('  flatutils::book(_tree, name_, "' + br.name + '", "' + str(br.size) + '", \'' + br.type + '\', ' + br.name + ', _branches, _whitelist);\n')
            src.write('}\n\n')

        else:
            # collection elements

            if len(defs[obj].branches) != 0:
                src.write('void\n')
                src.write(namespace + '::' + obj + '::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
                src.write('{\n')
                if obj in inheritance:
                    src.write('  ' + inheritance[obj] + '::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);\n\n')
    
                for br in defs[obj].branches:
                    src.write('  flatutils::setStatus(_tree, _name, "' + br.name + '", _status, _branches, _whitelist);\n')
                src.write('}\n\n') 
    
                src.write('void\n')
                src.write(namespace + '::' + obj + '::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
                src.write('{\n')
                if obj in inheritance:
                    src.write('  ' + inheritance[obj] + '::array_data::setAddress(_tree, _name, _branches, _whitelist);\n\n')
    
                for br in defs[obj].branches:
                    src.write('  flatutils::setStatusAndAddress(_tree, _name, "' + br.name + '", ' + br.name + ', _branches, _whitelist);\n')
                src.write('}\n\n')
        
                src.write('void\n')
                src.write(namespace + '::' + obj + '::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
                src.write('{\n')
                if obj in inheritance:
                    src.write('  ' + inheritance[obj] + '::array_data::book(_tree, _name, _branches, _whitelist);\n\n')
    
                if obj in fixedSize:
                    for br in defs[obj].branches:
                        src.write('  flatutils::book(_tree, _name, "' + br.name + '", TString::Format("%d", ' + str(sizes[obj]) + '), \'' + br.type + '\', ' + br.name + ', _branches, _whitelist);\n')
                else:
                    for br in defs[obj].branches:
                        src.write('  flatutils::book(_tree, _name, "' + br.name + '", _name + ".size", \'' + br.type + '\', ' + br.name + ', _branches, _whitelist);\n')
                src.write('}\n\n')

            src.write(namespace + '::' + obj + '::' + obj + '(array_data& _data, UInt_t _idx) :')
            if obj in inheritance:
                src.write('\n  ' + inheritance[obj] + '(_data, _idx)')
                if len(defs[obj].branches) != 0:
                    src.write(',')
            for br in defs[obj].branches:
                src.write('\n  ' + br.name + '(_data.' + br.name + '[_idx])')
                if br.name != defs[obj].branches[-1].name:
                    src.write(',')
            src.write('\n{\n}\n\n')

            src.write(namespace + '::' + obj + '::' + obj + '(' + obj + ' const& _src) :')
            if obj in inheritance:
                src.write('\n  ' + inheritance[obj] + '(_src)')
                if len(defs[obj].branches) != 0:
                    src.write(',')
            for br in defs[obj].branches:
                src.write('\n  ' + br.name + '(_src.' + br.name + ')')
                if br.name != defs[obj].branches[-1].name:
                    src.write(',')
            src.write('\n{\n}\n\n')

        src.write(namespace + '::' + obj + '&\n')
        src.write(namespace + '::' + obj + '::operator=(' + obj + ' const& _rhs)\n')
        src.write('{')
        if obj in inheritance:
            src.write('\n  ' + inheritance[obj] + '::operator=(_rhs);\n')
        for br in defs[obj].branches:
            src.write('\n  ' + br.name + ' = _rhs.' + br.name + ';')
        src.write('\n')
        src.write('  return *this;\n')
        src.write('}\n\n')

# Tree source
with open(FULLPATH + '/src/TreeEntries_' + namespace + '.cc', 'w') as src:
    src.write('#include "' + args.package + '/interface/TreeEntries_' + namespace + '.h"\n')
    src.write('#include "TTree.h"\n')
    src.write('#include "TFile.h"\n')
    src.write('#include "TDirectory.h"\n\n')
    src.write('#include <cstring>\n\n')

    for tree in trees:
        src.write('void\n')
        src.write(namespace + '::' + tree + '::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
        src.write('{\n')
        for br in treeDefs[tree].branches:
            if isSimple(br.type):
                src.write('  flatutils::setStatus(_tree, "", "' + br.name + '", _status, _branches, _whitelist);\n')
    
        src.write('\n')
    
        for br in treeDefs[tree].branches:
            if not isSimple(br.type):
                src.write('  ' + br.name + '.setStatus(_tree, _status, flatutils::subBranchList(_branches, "' + br.name + '"), _whitelist);\n')
    
        src.write('}\n\n')

        src.write('void\n')
        src.write(namespace + '::' + tree + '::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
        src.write('{\n')
        for br in treeDefs[tree].branches:
            if isSimple(br.type):
                if br.size == 1:
                    src.write('  flatutils::setStatusAndAddress(_tree, "", "' + br.name + '", &' + br.name + ', _branches, _whitelist);\n')
                else:
                    src.write('  flatutils::setStatusAndAddress(_tree, "", "' + br.name + '", ' + br.name + ', _branches, _whitelist);\n')
    
        src.write('\n')
    
        for br in treeDefs[tree].branches:
            if not isSimple(br.type):
                src.write('  ' + br.name + '.setAddress(_tree, flatutils::subBranchList(_branches, "' + br.name + '"), _whitelist);\n')
    
        src.write('}\n\n')
    
        src.write('void\n')
        src.write(namespace + '::' + tree + '::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)\n')
        src.write('{\n')
        for br in treeDefs[tree].branches:
            if isSimple(br.type):
                if br.size == 1:
                    src.write('  flatutils::book(_tree, "", "' + br.name + '", "", \'' + br.type + '\', &' + br.name + ', _branches, _whitelist);\n')
                else:
                    src.write('  flatutils::book(_tree, "", "' + br.name + '", "' + str(br.size) + '", \'' + br.type + '\', ' + br.name + ', _branches, _whitelist);\n')
    
        src.write('\n')
        
        for br in treeDefs[tree].branches:
            if not isSimple(br.type):
                src.write('  ' + br.name + '.book(_tree, flatutils::subBranchList(_branches, "' + br.name + '"), _whitelist);\n')
    
        src.write('}\n\n')

    for name, items in enums:
        src.write('TTree*\n')
        src.write(namespace + '::make' + name + 'Tree()\n')
        src.write('{\n')
        src.write('  auto* tree(new TTree("' + name + '", "' + name + '"));\n')
        src.write('  char name[1024];\n')
        src.write('  tree->Branch("name", name, "name/C");\n\n')
        src.write('  TString names[] = {\n')
        for item in items:
            src.write('    "' + item + '"')
            if item != items[-1]:
                src.write(',')
            src.write('\n')
        src.write('  };\n\n')
        src.write('  for (auto&& n : names) {\n')
        src.write('    std::strcpy(name, n.Data());\n')
        src.write('    tree->Fill();\n')
        src.write('  }\n\n')
        src.write('  tree->ResetBranchAddresses();\n')
        src.write('  return tree;\n')
        src.write('}\n\n')
