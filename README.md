# Zippy shell

Little shell written in bare C.

## Requirements

- cjson
- clang (can be changed to gcc in [Makefile](./Makefile))

#### Installing cjson

In arch-based systems it's available at
official repo.

```sh
sudo pacman -S cjson
```

## Building

Compiled binary can be found at `./bin/zippy`.

```sh
make
```

## Building & running

```sh
make run - <arguments>
```