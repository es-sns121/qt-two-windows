top = ..
bin = $(top)/bin
config = $(top)/configure/config

include $(config)

# Production
prod = two_windows
# Executable
exe = $(bin)/$(prod)

all : $(prod)

# Input to Qt MOC
moc_in = window.h

# Ouput from Qt (Meta Object Compiler)
moc_out = moc/window_h_moc.cpp

# Source files for production
src = $(moc_out) window.cpp main.cpp

$(prod): $(src)
	@ mkdir -p $(bin)
	g++ $(CPP_FLAGS) $(src) -o $(exe) $(QT_INCLUDE) $(QT_LIBRARY)

$(moc_out): $(moc_in)
	@ mkdir -p moc
	moc -o $(moc_out) $(moc_in)

.PHONY: clean new

clean:
	@ printf "Cleaning '$(prod)' moc file and binary ...\n"
	rm -rf $(moc_out) $(exe)

new:
	@ $(MAKE) -C . clean
	@ $(MAKE) -C .
