# -*- encoding: utf-8 -*-
require "#{File.expand_path(File.dirname(__FILE__))}/lib/simpler_tiles/version"

Gem::Specification.new do |s|
  s.name = %q{simpler-tiles}
  s.version = SimplerTiles::VERSION

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Jeff Larson"]
  s.date = %q{2011-06-23}
  s.description = %q{mappy maps!}
  s.email = %q{thejefflarson@gmail.com}
  s.extensions = ["ext/simpler_tiles/extconf.rb"]
  s.extra_rdoc_files = [
    "LICENSE.txt",
    "README.rdoc"
  ]
  s.files = `git ls-files`.split("\n")
  s.test_files = `git ls-files -- {test}/*`.split("\n")
  s.homepage = %q{http://github.com/thejefflarson/simpler-tiles}
  s.licenses = ["MIT"]
  s.require_paths = ["lib"]
  s.summary = %q{maps!}

  s.add_development_dependency(%q<rake-compiler>, [">= 0"])
  s.add_development_dependency(%q<bundler>, ["~> 1.0.0"])
  s.add_development_dependency(%q<shoulda>, ["~> 2.11.3"])
  s.add_development_dependency(%q<redgreen>, ["~> 1.2.2"])
end
