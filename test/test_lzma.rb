#!/usr/bin/env ruby -I../ext
#!/opt/local/bin/jruby -I../java
# Ruby/JRuby LZMA
# This code, like the LZMA SDK, is public domain.

require "test/unit"
require "lzma"

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
end
