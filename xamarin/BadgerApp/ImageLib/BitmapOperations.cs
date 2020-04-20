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
	class BitmapOperations
	{
		public static void MakeBinary(Bitmap bitmap)
		{
			if ( bitmap.PixelFormat != PixelFormat.Format24bppRgb && bitmap.PixelFormat != PixelFormat.Format32bppArgb )
			{
				throw new ArgumentException("The provided bitmap's pixel format was not supported.");
			}

			int pixelDepth = bitmap.PixelFormat == PixelFormat.Format24bppRgb ? 3 : 4;
			Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
			BitmapData bmpData = bitmap.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

			int numBytes = Math.Abs(bmpData.Stride) * bitmap.Height;
			byte[] rgbValues = new byte[numBytes];

			Marshal.Copy(bmpData.Scan0, rgbValues, 0, numBytes);

			for ( int index = 0; index + pixelDepth <= rgbValues.Length; index += pixelDepth )
			{
				int totalValue = 0;

				for ( int subIndex = pixelDepth == 3 ? 0 : 1; subIndex < 3; ++subIndex )
				{
					totalValue += rgbValues[index + subIndex];
				}

				totalValue /= 3;

				for ( int subIndex = pixelDepth == 3 ? 0 : 1; subIndex < 3; ++subIndex )
				{
					rgbValues[index + subIndex] = (byte)(totalValue >= 127 ? 255 : 0);
				}
			}

			Marshal.Copy(rgbValues, 0, bmpData.Scan0, numBytes);
			bitmap.UnlockBits(bmpData);
		}
	}
}
