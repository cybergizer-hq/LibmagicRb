require 'mkmf'

dir_config('magic', '/usr/lib')

$LDFLAGS << ' -lmagic'
$CFLAGS << ' -Os'

unless have_header('magic.h')
	abort <<~EOF
		\e[1;31m*** Can't find magic.h ***
		Have you installed the header for your distribution?
		The installation guide in documentation might help!\e[0m"
	EOF
end

unless have_library('magic', 'magic_open')
	abort <<~EOF
		\e[1;31m*** Can't find magic_open() in magic.h ***
		Even though the magic.h library seems to be installed.
		Please check again if the header is installed properly.
		Maybe try to a relatively latest version ~5.40 of libmagic?\e[0m
	EOF
end

create_makefile 'libmagic_rb/main'
