# LZMA Ruby bindings

## Java and MRI

## Examples

### Compressing String Data:
  
  require 'lzma'
  compressed = LZMA.compress('data to compress')

### Decompressing String Data:

  require 'lzma'
  decompressed = LZMA.decompress(File.read("compressed.lzma"))
