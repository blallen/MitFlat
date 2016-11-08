trees=simpletree genkintree
enums=$(patsubst %,../obj/%_enums.o,$(trees))
enumsrc=$(enums:.o=.cc)
classes=$(patsubst %,../obj/%_classes.o,$(trees))
classsrc=$(classes:.o=.cc)
objects=$(patsubst %,../obj/Objects_%.o,$(trees))
entries=$(patsubst %,../obj/TreeEntries_%.o,$(trees))
utilsrc=$(wildcard ../src/*Utils.cc)
utils=$(patsubst ../src/%.cc,../obj/%.o,$(utilsrc))

$(trees): %: $(utils) ../obj/common.o ../obj/%_enums.o ../obj/%_classes.o ../obj/Objects_%.o ../obj/TreeEntries_%.o
	g++ -std=c++11 -O2 -fPIC -shared $(shell root-config --libs) -o $(patsubst %,../obj/lib%.so,$@) $^

../obj/common.o: ../interface/Collection.h ../interface/common_LinkDef.h
	mkdir -p ../obj
	rootcling -f ../obj/common.cc $^
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) ../obj/common.cc

$(enums) $(classes): ../obj/%.o: ../obj/%.cc
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $^

$(enumsrc): ../obj/%_enums.cc: ../interface/Objects_%.h ../dict/%_LinkDef.h
	mkdir -p ../obj
	rootcling -f $@ $^

$(classsrc): ../obj/%_classes.cc: ../interface/TreeEntries_%.h ../obj/%_classes_LinkDef.h
	mkdir -p ../obj
	rootcling -f $@ $^

$(utils) $(objects) $(entries): ../obj/%.o: ../src/%.cc ../interface/%.h ../interface/Collection.h
	mkdir -p ../obj
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $<

.PHONY: clean

clean:
	rm -f ../obj/*.cc ../obj/*.o ../obj/*.pcm ../obj/*.so
