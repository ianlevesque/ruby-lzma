require 'mkmf'

# link with G++
CONFIG['LDSHARED'] = "$(CXX) " + CONFIG['LDSHARED'].split[1..-1].join(' ')

create_makefile("lzma_ruby")
