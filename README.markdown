# LZMA Ruby bindings

Simple LZMA compression and decompression routines.  No features to speak of presently.  Works in Ruby 1.8.6+ and JRuby, with compatibility between the two and
with other LZMA implementations.

Send questions to <mailto:ian@ianlevesque.org>

### Installation (MRI)

    gem install ruby-lzma
    
OR

    git clone http://github.com/ianlevesque/ruby-lzma.git
    cd ruby-lzma
    rake install
    
### Installation (JRuby)

    jruby -S gem install ruby-lzma

## Examples

### Compressing String Data:
  
    require 'lzma'
    compressed = LZMA.compress('data to compress')

### Decompressing String Data:

    require 'lzma'
    decompressed = LZMA.decompress(File.read("compressed.lzma"))
