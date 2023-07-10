TOPDIR = ..
FSMINC = $(TOPDIR)/include
DEMOSRC = $(TOPDIR)/demo

SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))

CXXFLAG = "-std=c++17"
CXXFLAG += -I$(FSMINC)
CXXFLGA += -I$(DEMOSRC)

.phony: demo clean

demo: $(SRCS)
	$(CXX) $(CXXFLAG) $^ -o $@

clean:
	rm -f demo *.o

$(OBJS) : %.o : %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
