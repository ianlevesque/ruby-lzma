# LZMA Ruby bindings

Simple LZMA compression and decompression routines.  No features to speak of presently.  Works in Ruby 1.8.6+, Ruby 1.9.1+, JRuby 1.4.1+, and MacRuby 0.6+.  All versions are compatible with each other, and with other LZMA implementations.

Send questions to <mailto:ian@ianlevesque.org>

### Installation (MRI)

    gem install ruby-lzma
    
OR

    git clone http://github.com/ianlevesque/ruby-lzma.git
    cd ruby-lzma
    rake install
    
### Installation (JRuby)

    jruby -S gem install ruby-lzma
    
### Installation (MacRuby)

    macgem install ruby-lzma

## Examples

### Compressing String Data:
  
    require 'lzma'
    compressed = LZMA.compress('data to compress')

### Decompressing String Data:

    require 'lzma'
    decompressed = LZMA.decompress(File.read("compressed.lzma"))
