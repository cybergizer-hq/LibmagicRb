# frozen_string_literal: true
require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

task(:default) do
	puts "LibmagicRb version #{LibmagicRb::VERSION}"
end

Rake::ExtensionTask.new { |ext|
	ext.name = 'main'
	ext.ext_dir = 'ext/libmagic/'
	ext.lib_dir = 'lib/libmagic_rb'
}

RSpec::Core::RakeTask.new(:spec)
task test: :spec
