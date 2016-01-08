%: ../obj/Utils.o ../obj/%_dict.o ../obj/common_dict.o ../obj/Objects_%.o ../obj/TreeEntries_%.o
	g++ -std=c++11 -O2 -fPIC -shared $(shell root-config --libs) -o $(patsubst %,../obj/lib%.so,$@) $^

../obj/common_dict.o: ../interface/Collection.h ../interface/common_LinkDef.h
	mkdir -p ../obj
	rootcling -f ../src/common_dict.cc $^
	mv ../src/common_dict_rdict.pcm ../obj/
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) ../src/common_dict.cc

../obj/%_dict.o: ../interface/Objects_%.h ../interface/TreeEntries_%.h ../interface/Collection.h ../interface/%_LinkDef.h 
	mkdir -p ../obj
	rootcling -f $(patsubst ../obj/%_dict.o,../src/%_dict.cc,$@) $^
	mv $(patsubst ../obj/%.o,../src/%_rdict.pcm,$@) ../obj/
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $(patsubst ../obj/%_dict.o,../src/%_dict.cc,$@)

../obj/%.o: ../src/%.cc ../interface/%.h ../interface/Collection.h
	mkdir -p ../obj
	g++ -std=c++11 -O2 -fPIC -c -o $@ -I$(shell root-config --incdir) $<

.PRECIOUS: ../obj/%_dict.o ../obj/%.o
.PHONY: clean

clean:
	rm -f ../obj/* ../src/*_dict.cc
