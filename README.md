undaemonize
===========

This is a tiny helper utility to force programs which insist on daemonizing
themselves to run in the foreground.

It's like djb's [fghack][1], except it's not a hack, because it makes use of the
`PR_SET_CHILD_SUBREAPER` flag added to `prctl(2)` in version 3.4 of the Linux
kernel. To quote [the documentation][2]:


   When a process is marked as a child subreaper, all of the children that it
   creates, and their descendants, will be marked as having a subreaper.  In
   effect, a subreaper fulfills the role of init(1) for its descendant
   processes.  Upon termination of a process that is orphaned (i.e., its
   immediate parent has already terminated) and marked as having a subreaper,
   the nearest still living ancestor subreaper will receive a SIGCHLD signal and
   will be able to wait(2) on the process to discover its termination status.

[1]: https://cr.yp.to/daemontools/fghack.html
[2]: http://man7.org/linux/man-pages/man2/prctl.2.html

Usage
-----

    undaemonize foobard -f /etc/foobard.conf

Installation
------------

    make
    sudo install -o root -g root -m 755 undaemonize /usr/local/bin

Caveats
-------

`undaemonize` does not (currently) forward signals to its child processes. If
you kill `undaemonize`, the daemon will not be killed.

License
-------

`undaemonize` is released under the MIT license. See `LICENSE`.
