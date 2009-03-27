package com.ephemeronindustries.lzma;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Random;

import SevenZip.Compression.LZMA.Decoder;
import SevenZip.Compression.LZMA.Encoder;

/**
 * Extremely simple LZMA compressor/decompressor. Encodes/decodes a single
 * buffer.
 * 
 * @author Ian Levesque
 * 
 * This code, like the underlying LZMA library it was shamelessly cut from, is public domain.
 */
public class LZMA {
	Encoder encoder = new Encoder();
	Decoder decoder = new Decoder();
	
	public LZMA() {
		
	}
	
	public byte[] compress(byte[] buffer) throws IOException {
		ByteArrayInputStream inStream = new ByteArrayInputStream(buffer);
		ByteArrayOutputStream outStream = new ByteArrayOutputStream();
		
		encoder.SetEndMarkerMode(true); // ???
		encoder.WriteCoderProperties(outStream);
		long fileSize = buffer.length;
		for (int i = 0; i < 8; i++)
			outStream.write((int)(fileSize >>> (8 * i)) & 0xFF);
		encoder.Code(inStream, outStream, -1, -1, null);

		outStream.flush();
		outStream.close();
		inStream.close();
		
		return outStream.toByteArray();
	}
	
	public byte[] decompress(byte[] buffer) throws IOException {
		ByteArrayInputStream inStream = new ByteArrayInputStream(buffer);
		ByteArrayOutputStream outStream = new ByteArrayOutputStream();
		
		int propertiesSize = 5;
		byte[] properties = new byte[propertiesSize];
		if (inStream.read(properties, 0, propertiesSize) != propertiesSize)
			throw new IOException("input .lzma file is too short");
		SevenZip.Compression.LZMA.Decoder decoder = new SevenZip.Compression.LZMA.Decoder();
		if (!decoder.SetDecoderProperties(properties))
			throw new IOException("Incorrect stream properties");
		long outSize = 0;
		for (int i = 0; i < 8; i++)
		{
			int v = inStream.read();
			if (v < 0)
				throw new IOException("Can't read stream size");
			outSize |= ((long)v) << (8 * i);
		}
		if (!decoder.Code(inStream, outStream, outSize))
			throw new IOException("Error in data stream");
		
		return outStream.toByteArray();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		for(int j = 0; j < 5; j++) {
		
			byte[] testArray = new byte[2 * 1024 * 1024];
			new Random(12345).nextBytes(testArray);

			LZMA lzma = new LZMA();
			try {
				long startTime = System.currentTimeMillis();

				byte[] compressed = lzma.compress(testArray);

				long compressedTime = System.currentTimeMillis();

				byte[] decompressed = lzma.decompress(compressed);

				long decompressedTime = System.currentTimeMillis();

				if(testArray.length != decompressed.length) throw new Exception("Wrong Length!");

				for(int i = 0; i < testArray.length; i++) {
					if(testArray[i] != decompressed[i])
						throw new Exception("Wrong Data!");
				}

				System.out.println("Compression Ratio: " + (compressed.length / (float)testArray.length) + " Compress Time: " + (compressedTime - startTime) + " ms.  Decompress Time: " + (decompressedTime - compressedTime) + " ms.");			
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}
