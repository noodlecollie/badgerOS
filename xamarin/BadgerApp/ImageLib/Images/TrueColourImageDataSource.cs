using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ImageLib.Images
{
	class TrueColourImageDataSource : IImageDataSource
	{
		public uint Width { get => (uint)m_Bitmap.Width; }
		public uint Height { get => (uint)m_Bitmap.Height; }

		private Bitmap m_Bitmap = null;

		public TrueColourImageDataSource(Bitmap bitmap)
		{
			if ( bitmap is null )
			{
				throw new ArgumentNullException($"Bitmap cannot be null.");
			}

			if ( !IsSupportedPixelFormat(bitmap.PixelFormat) )
			{
				throw new ArgumentException($"The provided pixel format is not supported.");
			}

			m_Bitmap = bitmap;
		}

		public uint GetPixelColour(uint x, uint y)
		{
			Color col = m_Bitmap.GetPixel((int)x, (int)y);
			return (uint)col.ToArgb();
		}

		public static bool IsSupportedPixelFormat(System.Drawing.Imaging.PixelFormat format)
		{
			switch ( format )
			{
				// Premultiplied ARGB is not supported.
				case System.Drawing.Imaging.PixelFormat.Format24bppRgb:
				case System.Drawing.Imaging.PixelFormat.Format32bppArgb:
				case System.Drawing.Imaging.PixelFormat.Format32bppRgb:
				{
					return true;
				}
			}

			return false;
		}
	}
}
