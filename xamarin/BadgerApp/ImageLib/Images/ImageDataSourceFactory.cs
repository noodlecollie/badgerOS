using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ImageLib.Images
{
	static class ImageDataSourceFactory
	{
		public static IImageDataSource Get(Bitmap bitmap)
		{
			if ( bitmap is null )
			{
				throw new ArgumentNullException("Bitmap cannot be null.");
			}

			if ( !TrueColourImageDataSource.IsSupportedPixelFormat(bitmap.PixelFormat) )
			{
				throw new ArgumentException("The provided bitmap's pixel format is not supported.");
			}

			return new TrueColourImageDataSource(bitmap);
		}
	}
}
