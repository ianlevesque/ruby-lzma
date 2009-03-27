#!/usr/bin/env ruby -I../ext -I../lib
#!/opt/local/bin/jruby -I../java
# Ruby/JRuby LZMA
# This code, like the LZMA SDK, is public domain.

require "test/unit"
require "lzma"
require 'base64'

class TestLzma < Test::Unit::TestCase
  def setup
    @lzma = LZMA.new
  end
  
  def teardown
    @lzma = nil
  end
  
  def test_lzma_both_ways
    compressed = @lzma.compress("leroy was here")
    assert_not_nil(compressed)
    assert_equal("leroy was here", @lzma.decompress(compressed))
  end
  
  def test_decompress_both_encoders
    java_compressed = Base64.decode64("XQAAQAAOAAAAAAAAAAA2GUqrt5owxRYShsh3Etc9r5jV/9OkAAA=")
    assert_equal("leroy was here", @lzma.decompress(java_compressed))
        
    native_compressed = Base64.decode64("EXQAAgAAOAAAAAAAAAAA2GUqrt5owxRYShsh3EtbQeg4A")
    assert_equal("leroy was here", @lzma.decompress(java_compressed))
  end
end
