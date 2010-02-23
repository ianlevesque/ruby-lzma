# Ruby/JRuby LZMA
# This code, like the LZMA SDK, is public domain.

$:.unshift File.expand_path(File.join(File.dirname(__FILE__),'..','ext')) 
$:.unshift File.expand_path(File.join(File.dirname(__FILE__),'..','lib')) 

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

  def test_decompress_sample
    rakefile_compressed = Base64.decode64 %(XQAAgACYAwAAAAAAAAA5GUqKNoFH6SMqlNELWCfVN0/ayvP6n06cnR/N5xv3\noo9rE+JmQnElb8Tya7ikChUSRZBWc5ooDLDJ1se77Hg8CyqQP4MfTg9/vuCZ\n1tAYesF25sS0JKtrKxUF8shctO9Eme6EN6e9G79JIChQ1N2LKXetNnSvtkcS\ngxOP2L2owTeuCRZ1os6lZ/OC2a7mP/1dsxQLWAKU0H66gMtv8x54orKC31IC\nqjRJIe2RSpX31ZorKNxrnoCvt3bVyvF1fJ1XeSpxjJN+OwE9wAOtSRQaeC3b\njf1qODG+J068iIBpYbrEomcriVy5CqiZJdMiumBy2lQsrNHNjfcH4ggB678/\n2b1C2CYxOMOqZQTAz/TcsdjSBzSwSV//yJHP30gZT3H/7o9mn457OgV/l7KG\nAtwYMU/zcAxHWDpTX7V4H4v8YG75aJEfMAYiNcIlV9VU6xy8CvucboFiPIQv\nm7uzw4pnUwr+tKlH335EjovKU5qv+8ZNZaONQUxtnDaB76McQuigAA==\n)
    decompressed = @lzma.decompress(rakefile_compressed)
    assert_match(/require 'rake'/, decompressed)
    assert_match(/desc "compile .classes to .jar"/, decompressed)
    assert_match(/desc "compile C extension"/, decompressed)
    assert_match(/task :test => :compile/, decompressed)
  end
end
