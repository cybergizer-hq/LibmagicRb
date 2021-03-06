require_relative 'lib/libmagic_rb/version'

Gem::Specification.new do |s|
	s.name = "libmagic_rb"
	s.version = LibmagicRb::VERSION
	s.authors = ["Cybergizer"]
	s.email = %w(sourav.goswami@cybergizer.com)
	s.summary = %q(Check filetype with libmagic)
	s.description = s.summary
	s.homepage = "https://github.com/cybergizer-hq/LibmagicRb/"
	s.license = "MIT"
	s.required_ruby_version = Gem::Requirement.new(">= 1.9.0")
	s.files = Dir.glob(%w(exe/** lib/**/*.rb ext/**/*.{c,rb,h} bin/** README.md LICENSE.txt))
	s.executables = s.files.grep(%r{^exe/}) { |f| File.basename(f) }
	s.extensions = Dir.glob("ext/**/extconf.rb")
	s.require_paths = ["lib"]
	s.extra_rdoc_files = Dir.glob(%w(README.md))
	s.bindir = "exe"
end
