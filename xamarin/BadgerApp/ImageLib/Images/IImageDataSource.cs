using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageLib.Images
{
	// Interface used to abstract away from the complexity of palettes and pixel formats.
	// When converting an image, the source image should be exposed via this interface.
	interface IImageDataSource
	{
		// Returns the width of the image in pixels.
		uint Width { get; }

		// Returns the height of the image in piels.
		uint Height { get; }

		// Returns the colour of the given pixel as an ARGB value.
		uint GetPixelColour(uint x, uint y);
	}
}
