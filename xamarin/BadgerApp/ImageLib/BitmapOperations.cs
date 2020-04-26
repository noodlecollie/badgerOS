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
			if ( bitmap.PixelFormat != PixelFormat.Format24bppRgb && bitmap.PixelFormat != PixelFormat.Format32bppArgb )
			{
				throw new ArgumentException("The provided bitmap's pixel format was not supported.");
			}

			int pixelDepth = bitmap.PixelFormat == PixelFormat.Format24bppRgb ? 3 : 4;
			Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
			BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

			byte[] bmpPixels = new byte[bmpData.Stride * bmpData.Height];
			Marshal.Copy(bmpData.Scan0, bmpPixels, 0, bmpPixels.Length);
			bitmap.UnlockBits(bmpData);

			byte[] outPixels = new byte[bitmap.Width * bitmap.Height];

			for ( int index = 0; index < outPixels.Length; ++index )
			{
				int bmpPixelIndex = 3 * index;
				int pixelBrightness = (bmpPixels[bmpPixelIndex] + bmpPixels[bmpPixelIndex + 1] + bmpPixels[bmpPixelIndex + 2]) / 3;
				outPixels[index] = (byte)(pixelBrightness > 127 ? 255 : 0);
			}

			return outPixels;
		}

		public static byte[] To65KColour(Bitmap bitmap)
		{
			if ( bitmap.PixelFormat != PixelFormat.Format24bppRgb && bitmap.PixelFormat != PixelFormat.Format32bppArgb )
			{
				throw new ArgumentException("The provided bitmap's pixel format was not supported.");
			}

			int pixelDepth = bitmap.PixelFormat == PixelFormat.Format24bppRgb ? 3 : 4;
			Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
			BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

			byte[] bmpPixels = new byte[bmpData.Stride * bmpData.Height];
			Marshal.Copy(bmpData.Scan0, bmpPixels, 0, bmpPixels.Length);
			bitmap.UnlockBits(bmpData);

			byte[] outPixels = new byte[bitmap.Width * bitmap.Height * 2];

			for ( int index = 0; index < outPixels.Length; index += 2 )
			{
				int bmpPixelIndex = (index / 2) * 3;
				ushort col16bit = Col24To16(Col24(bmpPixels[bmpPixelIndex], bmpPixels[bmpPixelIndex + 1], bmpPixels[bmpPixelIndex + 2]));

				outPixels[index] = (byte)(col16bit & 0x00FF);
				outPixels[index + 1] = (byte)((col16bit & 0xFF00) >> 8);
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
	}
}
