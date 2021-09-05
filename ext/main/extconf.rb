require 'mkmf'

$LDFLAGS << ' -lmagic'
$CFLAGS << ' -Os'

abort "\e[1;31m*** Can't find magic.h ***\e[0m" unless have_header('magic.h')
abort "\e[1;31m*** Can't find magic_open() in magic.h ***\e[0m" unless have_library('magic', 'magic_open')

create_makefile 'libmagic_rb/libmagic_rb'
