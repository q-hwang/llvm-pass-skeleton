# Makefile for streamcluster

PREFIX=${PARSECDIR}/pkgs/kernels/streamcluster/inst/${PARSECPLAT}

TARGET=streamcluster
OBJS=streamcluster.o

ifdef version
  ifeq "$(version)" "pthreads"
    CXXFLAGS :=	$(CXXFLAGS) -DENABLE_THREADS -pthread
    OBJS += parsec_barrier.o
  endif
  ifeq "$(version)" "tbb"
    CXXFLAGS := $(CXXFLAGS) -DTBB_VERSION
    LIBS := $(LIBS) -ltbb
  endif
endif

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

%.o : %.cpp
	# $(eval LL=$(@:.ll=.cpp))
	# $(CXX) $(CXXFLAGS) -S -emit-llvm -fprofile-instr-use=/home/qian/llvm-pass-skeleton/profile/code.profdata $< -o $(@:.o=.ll)
	# opt-9 --gvn  --simplifycfg --loop-unroll --loop-rotate --licm --tailcallelim --constprop --dce --loop-deletion --loop-fusion --loop-simplify  -S $(@:.o=.ll) -o $(@:.o=_.ll)
	# $(CXX) $(CXXFLAGS) -c $(@:.o=_.ll) -o $@
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

install:
	mkdir -p $(PREFIX)/bin
	cp -f $(TARGET) $(PREFIX)/bin/$(TARGET)

