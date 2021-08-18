require 'mkmf'

dir_config('magic', '/usr/lib')
$LDFLAGS << ' -lmagic'

have_library('magic', 'magic_open')
have_header('magic.h')

create_makefile 'libmagic_rb/main'
