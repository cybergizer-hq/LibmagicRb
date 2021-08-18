# frozen_string_literal: true

require "libmagic_rb/version"
require "libmagic_rb/main"

class LibmagicRb
	DB = File.realpath(File.join(__dir__(), '..', 'data', 'magic.mgc'))
	STDERR.puts "\e[1;31mWARNING! Database #{DB} is unreadable\e[0m" unless File.readable?(DB)

	define_singleton_method(:check) { |db: DB, file:, mode: nil| _check_(db: DB, file: file, mode: mode) }
end
