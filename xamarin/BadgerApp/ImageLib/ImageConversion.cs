using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using ImageLib.Images;
using ImageLib.CSource;

namespace ImageLib
{
	public static class ImageConversion
	{
		public static MutableImage BitmapToMasked(Bitmap bitmap)
		{
			IImageDataSource source = ImageDataSourceFactory.Get(bitmap);
			MutableImage dest = new MutableImage(source.Width, source.Height);

			for ( uint y = 0; y < source.Height; ++y )
			{
				for ( uint x = 0; x < source.Width; ++x )
				{
					uint col32 = source.GetPixelColour(x, y);

					// ARGB (32-bit colour) is equivalent to 0RGB (24-bit colour) in our case,
					// since we don't care about the alpha.
					uint red = ColourConversion.Col24RedChannel(col32);
					uint green = ColourConversion.Col24GreenChannel(col32);
					uint blue = ColourConversion.Col24BlueChannel(col32);
					uint average = (red + green + blue) / 3;
					bool isMasked = average > 127;

					dest.SetPixelValue(x, y, (uint)(isMasked ? 1 : 0));
				}
			}

			return dest;
		}

		public static MutableImage BitmapTo65K(Bitmap bitmap)
		{
			IImageDataSource source = ImageDataSourceFactory.Get(bitmap);
			MutableImage dest = new MutableImage(source.Width, source.Height);

			for ( uint y = 0; y < source.Height; ++y )
			{
				for ( uint x = 0; x < source.Width; ++x )
				{
					uint col32 = source.GetPixelColour(x, y);

					// ARGB (32-bit colour) is equivalent to 0RGB (24-bit colour) in our case,
					// since we don't care about the alpha.
					ushort col16 = ColourConversion.Col24To16(col32);

					dest.SetPixelValue(x, y, (uint)col16);
				}
			}

			return dest;
		}

		public static MutableImage BitmapTo65KPaletted(Bitmap bitmap)
		{
			IImageDataSource source = ImageDataSourceFactory.Get(bitmap);

			ImagePaletteBuilder paletteBuilder = new ImagePaletteBuilder(source);
			paletteBuilder.BuildPalettte();

			uint[] palette = paletteBuilder.GetPalette();
			uint paletteSize = (uint)palette.Length;
			Dictionary<uint, uint> colourMap = paletteBuilder.GetColourMap();

			MutableImage dest = new MutableImage(source.Width, source.Height, paletteSize);

			for ( uint index = 0; index < paletteSize; ++index )
			{
				dest.SetPaletteValue(index, ColourConversion.Col24To16(palette[index]));
			}

			for ( uint y = 0; y < source.Height; ++y )
			{
				for ( uint x = 0; x < source.Width; ++x )
				{
					uint sourceCol = ColourConversion.ColARGBTo24(source.GetPixelColour(x, y));
					uint paletteIndex = colourMap[sourceCol];
					dest.SetPixelValue(x, y, paletteIndex);
				}
			}

			return dest;
		}
	}
}
