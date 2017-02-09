undaemonize:

.PHONY: clean
clean:
	rm -f undaemonize test/testdaemon

%: %.c
	cc -Wall -pedantic -ansi $< -o $@
