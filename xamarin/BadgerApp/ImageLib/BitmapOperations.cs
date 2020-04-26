using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace ImageLib
{
	public static class BitmapOperations
	{
		public static byte[] ToBinary(Bitmap bitmap)
		{
			const uint inPixelDepth = 3;

			if ( bitmap.PixelFormat != PixelFormat.Format24bppRgb && bitmap.PixelFormat != PixelFormat.Format32bppArgb )
			{
				throw new ArgumentException("The provided bitmap's pixel format was not supported.");
			}

			Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
			BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

			byte[] bmpPixels = new byte[bmpData.Stride * bmpData.Height];
			Marshal.Copy(bmpData.Scan0, bmpPixels, 0, bmpPixels.Length);
			bitmap.UnlockBits(bmpData);

			byte[] outPixels = new byte[bitmap.Width * bitmap.Height];

			for ( uint y = 0; y < bitmap.Height; ++y )
			{
				for ( uint x = 0; x < bitmap.Width; ++x )
				{
					uint sourcePixelIndex = IndexBeginningOfPixel(x, y, (uint)bmpData.Stride, inPixelDepth);
					uint pixelBrightness = (uint)((bmpPixels[sourcePixelIndex] + bmpPixels[sourcePixelIndex + 1] + bmpPixels[sourcePixelIndex + 2]) / 3);

					uint destPixelIndex = (y * (uint)bitmap.Width) + x;
					outPixels[destPixelIndex] = (byte)(pixelBrightness > 127 ? 255 : 0);
				}
			}

			return outPixels;
		}

		public static byte[] To65KColour(Bitmap bitmap)
		{
			const uint inPixelDepth = 3;
			const uint outPixelDepth = 2;

			if ( bitmap.PixelFormat != PixelFormat.Format24bppRgb && bitmap.PixelFormat != PixelFormat.Format32bppArgb )
			{
				throw new ArgumentException("The provided bitmap's pixel format was not supported.");
			}

			Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
			BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

			byte[] bmpPixels = new byte[bmpData.Stride * bmpData.Height];
			Marshal.Copy(bmpData.Scan0, bmpPixels, 0, bmpPixels.Length);
			bitmap.UnlockBits(bmpData);

			byte[] outPixels = new byte[bitmap.Width * bitmap.Height * outPixelDepth];
			
			for ( uint y = 0; y < bitmap.Height; ++y )
			{
				for ( uint x = 0; x < bitmap.Width; ++x )
				{
					uint sourcePixelIndex = IndexBeginningOfPixel(x, y, (uint)bmpData.Stride, inPixelDepth);

					// Remember endianness! 0x*RGB corresponds to blue being in the lowest channel.
					ushort col16bit = Col24To16(Col24(bmpPixels[sourcePixelIndex + 2], bmpPixels[sourcePixelIndex + 1], bmpPixels[sourcePixelIndex]));

					uint destPixelIndex = ((y * (uint)bitmap.Width) + x) * outPixelDepth;
					outPixels[destPixelIndex] = (byte)(col16bit & 0x00FF);
					outPixels[destPixelIndex + 1] = (byte)((col16bit & 0xFF00) >> 8);
				}
			}

			return outPixels;
		}

		// Single-channel colour.
		static byte Col8To5(byte col)
		{
			return (byte)(((uint)col * 31) / 255);
		}

		// Single-channel colour.
		static byte Col8To6(byte col)
		{
			return (byte)(((uint)col * 63) / 255);
		}

		// Converts 0RGB[8:8:8:8] to RGB[5:6:5].
		static ushort Col24To16(uint col)
		{
			int red = Col8To5((byte)((col & 0x00FF0000) >> 16));
			int green = Col8To6((byte)((col & 0x0000FF00) >> 8));
			int blue = Col8To5((byte)(col & 0x000000FF));

			return (ushort)((red << 11) | (green << 5) | blue);
		}

		// Converts RGB0[8:8:8:8] to RGB[5:6:5].
		static ushort Col32To16(uint col)
		{
			return Col24To16(col >> 8);
		}

		// Converts individual bytes to 0RGB[8:8:8:8].
		static uint Col24(byte red, byte green, byte blue)
		{
			return (uint)((red << 16) | (green << 8) | blue);
		}

		// Converts individual bytes to RGB0[8:8:8:8].
		static uint Col32(byte red, byte green, byte blue)
		{
			return (uint)((red << 24) | (green << 16) | (blue << 8));
		}

		// TODO: Refactor so that bitmap pixels are kept in a class, and this function is a class member.
		static uint IndexBeginningOfPixel(uint x, uint y, uint strideBytes, uint pixelDepth)
		{
			return (y * strideBytes) + (x * pixelDepth);
		}
	}
}
