using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageLib
{
	static class ColourConversion
	{
		// Single-channel colour.
		public static byte Col8To5(byte col)
		{
			return (byte)(((uint)col * 31) / 255);
		}

		// Single-channel colour.
		public static byte Col8To6(byte col)
		{
			return (byte)(((uint)col * 63) / 255);
		}

		// Converts 0RGB[8:8:8:8] to RGB[5:6:5].
		public static ushort Col24To16(uint col)
		{
			int red = Col8To5((byte)((col & 0x00FF0000) >> 16));
			int green = Col8To6((byte)((col & 0x0000FF00) >> 8));
			int blue = Col8To5((byte)(col & 0x000000FF));

			return (ushort)((red << 11) | (green << 5) | blue);
		}

		// Converts RGB0[8:8:8:8] to RGB[5:6:5].
		public static ushort Col32To16(uint col)
		{
			return Col24To16(col >> 8);
		}

		// Converts RGB0[8:8:8:8] to 0RGB[8:8:8:8].
		public static uint Col32To24(uint col)
		{
			return col >> 8;
		}

		// Converts ARGB[8:8:8:8] to 0RGB[8:8:8:8]
		public static uint ColARGBTo24(uint col)
		{
			return col & 0x00FFFFFF;
		}

		// Converts individual bytes to 0RGB[8:8:8:8].
		public static uint Col24(byte red, byte green, byte blue)
		{
			return (uint)((red << 16) | (green << 8) | blue);
		}

		// Converts individual bytes to RGB0[8:8:8:8].
		public static uint Col32(byte red, byte green, byte blue)
		{
			return (uint)((red << 24) | (green << 16) | (blue << 8));
		}

		// Converts individual bytes to ARGB[8:8:8:8].
		public static uint ColARGB(byte alpha, byte red, byte green, byte blue)
		{
			return (uint)((alpha << 24) | (red << 16) | (green << 8) | blue);
		}

		// Gets the red component of the 24-bit colour.
		public static byte Col24RedChannel(uint col)
		{
			return (byte)((col & 0x00FF0000) >> 16);
		}

		// Gets the green component of the 24-bit colour.
		public static byte Col24GreenChannel(uint col)
		{
			return (byte)((col & 0x0000FF00) >> 8);
		}

		// Gets the blue component of the 24-bit colour.
		public static byte Col24BlueChannel(uint col)
		{
			return (byte)(col & 0x000000FF);
		}
	}
}
