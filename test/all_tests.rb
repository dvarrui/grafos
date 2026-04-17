#!/usr/bin/env ruby

base_dir = File.expand_path('..', __FILE__)
$LOAD_PATH.unshift File.join(base_dir, '..', 'lib')
$LOAD_PATH.unshift base_dir

require "test/unit"

Dir.glob("#{base_dir}/**/*_test.rb").each do |file|
  require file
end