FROM debian:stretch

ADD undaemonize test/testdaemon /usr/local/bin/

CMD ["/usr/local/bin/undaemonize", "/usr/local/bin/testdaemon"]
