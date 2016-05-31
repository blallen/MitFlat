.PHONY: simpletree

%: ../obj/Utils.o ../obj/common_dict.o ../obj/%_dict.o ../obj/Objects_%.o ../obj/TreeEntries_%.o
	g++ -std=c++11 -O2 -fPIC -shared $(shell root-config --libs) -o $(patsubst %,../obj/lib%.so,$@) $^

../obj/common_dict.o: ../interface/Collection.h ../interface/common_LinkDef.h
	mkdir -p ../obj
	rootcling -f ../obj/common_dict.cc $^
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) ../obj/common_dict.cc

../obj/%_dict.o: ../interface/Objects_%.h ../interface/TreeEntries_%.h ../interface/Collection.h ../interface/%_LinkDef.h
	mkdir -p ../obj
	rootcling -f $(patsubst ../obj/%_dict.o,../obj/%_dict.cc,$@) $^
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $(patsubst ../obj/%_dict.o,../obj/%_dict.cc,$@)

../obj/%.o: ../src/%.cc ../interface/%.h ../interface/Collection.h
	mkdir -p ../obj
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $<

.PRECIOUS: ../obj/%_dict.cc ../obj/%_dict.o ../obj/%.o
.PHONY: clean

clean:
	rm -f ../obj/*
