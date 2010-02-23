require 'rake'
require 'rake/testtask'

if RUBY_PLATFORM =~ /java/
  desc "compile .java to .class"
  task :compile do
    chdir('java') do
      sh 'javac com/ephemeronindustries/lzma/*.java'
      sh 'javac SevenZip/Compression/LZ/*.java'
      sh 'javac SevenZip/Compression/LZMA/*.java'
      sh 'javac SevenZip/Compression/RangeCoder/*.java'
    end
  end

  desc "compile .classes to .jar"
  task :jar => [:compile] do
    chdir('java') do
      sh "jar -cf lzma_java.jar com/ephemeronindustries/lzma/*.class SevenZip/Compression/LZ/*.class SevenZip/Compression/LZMA/*.class SevenZip/Compression/RangeCoder/*.class"
    end
  end

else
  desc "compile C extension"
  task :compile do
    chdir('ext') do
      sh 'ruby extconf.rb'
      sh 'make'
    end
  end
end
task :default => :test

Rake::TestTask.new(:test) do |t|
  t.test_files = FileList['test/test_*.rb']
  t.verbose = false
end

task :test => :compile
