using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageLib.Images
{
	// Class that holds modifiable image data. The pixel format of the data is not specified,
	// and all pixels are stored as 32-bit integers. The encoding of colour in the pixel values
	// is up to the user of the class.
	// This class also supports palettes: if the image has a palette, pixel values are
	// treated as indices into this palette, and the palette values themselves are treated as
	// colours. A palette can only be set upon creation of the class instance.
	// The dimensions of the image and palette are fixed once the class has been instanciated.
	public class MutableImage
	{
		public uint Width { get; }
		public uint Height { get; }
		public bool HasPalette { get => !(m_Palette is null); }
		public uint PaletteLength { get => HasPalette ? (uint)m_Palette.Length : 0; }

		private uint[] m_Pixels = null;
		private uint[] m_Palette = null;

		public MutableImage(uint width, uint height)
		{
			if ( width < 1 )
			{
				throw new ArgumentOutOfRangeException("Width must be greater than zero.");
			}

			if ( height < 1 )
			{
				throw new ArgumentOutOfRangeException("Height must be greater than zero.");
			}

			Width = width;
			Height = height;
			m_Pixels = new uint[Width * Height];
		}

		public MutableImage(uint width, uint height, uint paletteSize)
		{
			if ( width < 1 )
			{
				throw new ArgumentOutOfRangeException("Width must be greater than zero.");
			}

			if ( height < 1 )
			{
				throw new ArgumentOutOfRangeException("Height must be greater than zero.");
			}

			if ( paletteSize < 1 )
			{
				throw new ArgumentOutOfRangeException("Palette size must be greater than zero.");
			}

			if ( paletteSize > 256 )
			{
				throw new ArgumentOutOfRangeException("Maximum palette size is 256.");
			}

			Width = width;
			Height = height;
			m_Pixels = new uint[Width * Height];
			m_Palette = new uint[paletteSize];
		}

		// Returns the colour at the given pixel as an ARGB value. If the image
		// has a palette, it is used to get the colour for that pixel.
		public uint GetPixelColour(uint x, uint y)
		{
			ValidateCoOrdinates(x, y);

			uint value = m_Pixels[PixelIndex(x, y)];

			if ( !HasPalette )
			{
				return value;
			}

			// This *should* never happen, if the image data is valid.
			if ( value >= PaletteLength )
			{
				return 0;
			}

			return m_Palette[value];
		}

		// Returns the raw value of the given pixel. If the image uses a palette,
		// this value will be a palette index; otherwise, it will be a colour in
		// ARGB format.
		public uint GetPixelValue(uint x, uint y)
		{
			ValidateCoOrdinates(x, y);
			return m_Pixels[PixelIndex(x, y)];
		}

		// Sets the raw value of the given pixel. If the image uses a palette,
		// the specified value must be within range of the palette's size.
		public void SetPixelValue(uint x, uint y, uint value)
		{
			ValidateCoOrdinates(x, y);

			if ( HasPalette && value >= PaletteLength )
			{
				throw new ArgumentException($"Value {value} exceeded maximum palette index of {PaletteLength - 1}.");
			}

			m_Pixels[PixelIndex(x, y)] = value;
		}

		public uint GetPaletteValue(uint index)
		{
			ValidatePaletteIndex(index);
			return m_Palette[index];
		}

		public void SetPaletteValue(uint index, uint value)
		{
			ValidatePaletteIndex(index);
			m_Palette[index] = value;
		}

		private void ValidateCoOrdinates(uint x, uint y)
		{
			if ( x >= Width )
			{
				throw new ArgumentOutOfRangeException($"X co-ordinate {x} exceeded maximum value of {Width - 1}");
			}

			if ( y >= Height )
			{
				throw new ArgumentOutOfRangeException($"Y co-ordinate {y} exceeded maximum value of {Height - 1}");
			}
		}

		private void ValidatePaletteIndex(uint index)
		{
			if ( !HasPalette )
			{
				throw new ArgumentException("Cannot set palette value in image without a palette.");
			}

			if ( index >= PaletteLength )
			{
				throw new ArgumentException($"Value {index} exceeded maximum palette index of {PaletteLength - 1}.");
			}
		}

		private uint PixelIndex(uint x, uint y)
		{
			return (y * Width) + x;
		}
	}
}
