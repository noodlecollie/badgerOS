using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageLib.Images;

namespace ImageLib.CSource
{
	public static class BitmapCSourceFactory
	{
		public static BitmapCSourceFile CreateCSourceFile(MutableImage image, FileFormatDefs.FileType fileType)
		{
			if ( image is null )
			{
				throw new ArgumentNullException("Image was null.");
			}

			switch ( fileType )
			{
				case FileFormatDefs.FileType.BitmapMask:
				{
					return CreateMasked(image);
				}

				case FileFormatDefs.FileType.Bitmap65K:
				{
					return Create65K(image);
				}

				case FileFormatDefs.FileType.Bitmap65KPalette:
				{
					return Create65KPalette(image);
				}

				default:
				{
					throw new NotImplementedException("Support for conversion from this file format is not yet supported.");
				}
			}
		}

		private static BitmapCSourceFile CreateMasked(MutableImage image)
		{
			// Rows need to be able to encompass all bits.
			uint bytesPerRow = (image.Width + 7) / 8;
			byte[] data = new byte[bytesPerRow * image.Height];

			BitmapCSourceFile outFile = new BitmapCSourceFile
			{
				Width = (ushort)image.Width,
				Height = (ushort)image.Height,
				Data = data
			};

			for ( uint y = 0; y < image.Height; ++y )
			{
				for ( uint x = 0; x < image.Width; ++x )
				{
					uint xMod8 = x % 8;
					uint dataIndex = (y * bytesPerRow) + (x / 8);

					if ( xMod8 == 0 )
					{
						// First bit to be put into this byte, so ensure it's zeroed.
						data[dataIndex] = 0;
					}

					uint colour = image.GetPixelColour(x, y);

					if ( colour > 0 )
					{
						data[dataIndex] |= (byte)(1 << (int)xMod8);
					}
				}
			}

			return outFile;
		}

		private static BitmapCSourceFile Create65K(MutableImage image)
		{
			byte[] data = new byte[image.Width * image.Height * 2];

			BitmapCSourceFile outFile = new BitmapCSourceFile
			{
				Width = (ushort)image.Width,
				Height = (ushort)image.Height,
				Data = data,
			};

			for ( uint y = 0; y < image.Height; ++y )
			{
				for ( uint x = 0; x < image.Width; ++x )
				{
					uint colour = image.GetPixelValue(x, y);
					uint dataIndex = 2 * ((y * image.Width) + x);

					// Little-endian, so lower byte first.
					data[dataIndex] = (byte)(colour & 0x00FF);
					data[dataIndex + 1] = (byte)((colour & 0xFF00) >> 8);
				}
			}

			return outFile;
		}

		private static BitmapCSourceFile Create65KPalette(MutableImage image)
		{
			byte[] data = new byte[image.Width * image.Height];
			byte[] palette = new byte[image.PaletteLength * 2];

			BitmapCSourceFile outFile = new BitmapCSourceFile
			{
				Width = (ushort)image.Width,
				Height = (ushort)image.Height,
				Data = data,
				Palette = palette
			};

			for ( uint y = 0; y < image.Height; ++y )
			{
				for ( uint x = 0; x < image.Width; ++x )
				{
					data[(y * image.Width) + x] = (byte)image.GetPixelValue(x, y);
				}
			}

			for ( uint index = 0; index < image.PaletteLength; ++index )
			{
				uint paletteByteIndex = 2 * index;
				uint paletteValue = image.GetPaletteValue(index);

				// Little-endian, so lower byte first.
				palette[paletteByteIndex] = (byte)(paletteValue & 0x00FF);
				palette[paletteByteIndex + 1] = (byte)((paletteValue & 0xFF00) >> 8);
			}

			return outFile;
		}
	}
}
