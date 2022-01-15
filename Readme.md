
# Meowsay
It's a lot like cowsay, but less... bovine.

Give `meowsay` some text on `stdin`:

```sh
~/ $ MANWIDTH=60 man ls | head -n 15 | ./meowsay.sh
           ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
           █ LS(1)                  User Commands                 LS(1)   █
           █                                                              █
           █ NAME                                                         █
           █        ls - list directory contents                          █
           █                                                              █
           █ SYNOPSIS                                                     █
           █        ls [OPTION]... [FILE]...                              █
           █                                                              █
           █ DESCRIPTION                                                  █
           █        List  information  about the FILEs (the current       █
           █        di‐ rectory by default).  Sort  entries               █
           █        alphabetically if none of -cftuvSUX nor --sort        █
           █        is specified.                                         █
           █                                                              █
           █        Mandatory  arguments  to long options are mandatory   █
           █        for short options too.                                █
           ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄    ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
          ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄       █ ▄▀ 
        ▄▀░░░░░░░░░░░░▄░░░░░░░▀▄     █▀
        █░░▄░░░░▄░░░░░░░░░░░░░░█
        █░░░░░░░░░░░░▄█▄▄░░▄░░░█ ▄▄▄
 ▄▄▄▄▄  █░░░░░░▀░░░░▀█░░▀▄░░░░░█▀▀░██
 ██▄▀██▄█░░░▄░░░░░░░██░░░░▀▀▀▀▀░░░░██
  ▀██▄▀██░░░░░░░░▀░██▀░░░░░░░░░░░░░▀██ 
    ▀████░▀░░░░▄░░░██░░░▄█░░░░▄░▄█░░██ 
       ▀█░░░░▄░░░░░██░░░░▄░░░▄░░▄░░░██ 
       ▄█▄░░░░░░░░░░░▀▄░░▀▀▀▀▀▀▀▀░░▄▀
      █▀▀█████████▀▀▀▀████████████▀
      ████▀  ███▀      ▀███  ▀██▀

```

## TODO
- [x] Basic formatting of arguments that are over 60 characters in
      length
- [ ] Deal with the byte order mark that came from Project Gutenberg
      test text
- [ ] Update the Scanner to buffer from stdin, not the cat data.
- [ ] Unicode support

## License
ISC License

Copyright (c) 2021 Will Harding

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all
copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.


