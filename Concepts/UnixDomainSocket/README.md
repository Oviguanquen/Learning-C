# 1. Search for the concept

```sh
man -k "unix domain socket"
```

These are the important results:

- sockaddr_un (3type)
- sys_un.h (0p)

Since there is no entry 7, search for unix:

```sh
man -k "unix" | grep 7
```

Good, this is the result that we are looking for:

unix (7)             - sockets for local interprocess communication

```sh
man 7 unix
```

