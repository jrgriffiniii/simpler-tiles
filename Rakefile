# encoding: utf-8

require 'rubygems'
require 'bundler'

begin
  Bundler.setup(:default, :development, :test)
rescue Bundler::BundlerError => e
  $stderr.puts e.message
  $stderr.puts "Run `bundle install` to install missing gems"
  exit e.status_code
end
Bundler::GemHelper.install_tasks
require 'rake'
require 'yard'

YARD::Rake::YardocTask.new


require 'erb'
task :doc do |t|
  File.open("index.html", 'w').write ERB.new(File.open("index.erb").read).result(binding)
end

task :publish do |t|
  `git checkout gh-pages`
  `git merge master`
  `git push`
  `git checkout master`
end


require 'rake/testtask'
Rake::TestTask.new(:test) do |test|
  test.libs << 'lib' << 'test'
  test.pattern = 'test/**/test_*.rb'
  test.verbose = true
end

task :default => :test
# e.g. DEV_CONFIG='--with-simple-tiles-include=/tmp/simple-tiles/usr/local/include/ --with-simple-tiles-lib=/tmp/simple-tiles/usr/local/lib/' bundle exec rake test
require 'rake/extensiontask'
Rake::ExtensionTask.new('simpler_tiles') do |ext|
  if ENV['DEV_CONFIG']
    ext.config_options << ENV['DEV_CONFIG']
  end
  ext.lib_dir = File.join('lib', 'simpler_tiles')
end

DATA = "data/tl_2010_us_state10.shp"
file DATA do |t|
  if !File.exists? t.name
    require 'fileutils'
    FileUtils.mkdir_p "data"
    tasks = []
    tasks << 'cd data'
    tasks << 'curl -O ftp://ftp2.census.gov/geo/tiger/TIGER2010/STATE/2010/tl_2010_us_state10.zip'
    tasks << 'unzip tl_2010_us_state10.zip'
    `#{tasks.join ';'}`
  end
end

Rake::Task[:test].prerequisites.unshift DATA
Rake::Task[:test].prerequisites.unshift :compile