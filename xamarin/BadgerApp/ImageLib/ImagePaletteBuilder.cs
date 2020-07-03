using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageLib.Images;
using System.Diagnostics;

namespace ImageLib
{
	class ImagePaletteBuilder
	{
		private class ColourBucket
		{
			// Colour is 24-bit 0RGB
			public uint Colour = 0;
			public uint Count = 0;
		}

		private class BSPNode
		{
			public List<ColourBucket> LeafColours = null;
			public uint SplitColour = 0;
			public uint SplitPlaneId = 0;

			public BSPNode HighChild = null;
			public BSPNode LowChild = null;
		}

		private IImageDataSource m_Source = null;
		private uint[] m_Palette = null;
		private Dictionary<uint, uint> m_ColourToPaletteIndex = null;

		public ImagePaletteBuilder(IImageDataSource source)
		{
			if ( source is null )
			{
				throw new ArgumentNullException("Source image cannot be null.");
			}

			m_Source = source;
		}

		public uint[] GetPalette()
		{
			return m_Palette;
		}

		// Maps each colour to its index in the palette.
		// The colour used as the key should be in 24-bit 0RGB format.
		public Dictionary<uint, uint> GetColourMap()
		{
			return m_ColourToPaletteIndex;
		}

		public void BuildPalettte()
		{
			m_Palette = null;
			m_ColourToPaletteIndex = null;

			Dictionary<uint, ColourBucket> histogram = CreateHistogram();

			if ( histogram.Count <= 256 )
			{
				CreatePaletteDirectly(histogram);
			}
			else
			{
				CreatePaletteViaBSP(histogram);
			}
		}

		private Dictionary<uint, ColourBucket> CreateHistogram()
		{
			Dictionary<uint, ColourBucket> buckets = new Dictionary<uint, ColourBucket>();

			for ( uint y = 0; y < m_Source.Height; ++y )
			{
				for ( uint x = 0; x < m_Source.Width; ++x )
				{
					uint col24 = ColourConversion.ColARGBTo24(m_Source.GetPixelColour(x, y));
					ColourBucket bucket = null;

					if ( !buckets.TryGetValue(col24, out bucket) )
					{
						bucket = new ColourBucket();
						bucket.Colour = col24;
						buckets[col24] = bucket;
					}

					bucket.Count += 1;
				}
			}

			return buckets;
		}

		private void CreatePaletteDirectly(Dictionary<uint, ColourBucket> histogram)
		{
			m_Palette = new uint[histogram.Count];
			m_ColourToPaletteIndex = new Dictionary<uint, uint>();

			uint paletteIndex = 0;

			foreach ( KeyValuePair<uint, ColourBucket> pair in histogram )
			{
				uint colour = pair.Key;
				m_Palette[paletteIndex] = colour;
				m_ColourToPaletteIndex[colour] = paletteIndex;

				++paletteIndex;
			}
		}

		// Algorithm taken from https://stackoverflow.com/questions/3849115/image-palette-reduction/6727451#6727451
		private void CreatePaletteViaBSP(Dictionary<uint, ColourBucket> histogram)
		{
			Queue<BSPNode> leafNodes = new Queue<BSPNode>();

			BSPNode rootNode = new BSPNode();
			rootNode.LeafColours = new List<ColourBucket>();

			foreach ( KeyValuePair<uint, ColourBucket> pair in histogram )
			{
				rootNode.LeafColours.Add(pair.Value);
			}

			// Clear up memory that's no longer required.
			histogram.Clear();

			leafNodes.Enqueue(rootNode);

			for ( uint iteration = 0; iteration < 8; ++iteration )
			{
				// 0 = red, 1 = green, 2 = blue.
				// Blue is deliberately chosen to be last (and so only iterated on twice)
				// because the eye is less sensitive to blue colour, so it can be quantised more coarsely.
				uint channelToOrderBy = iteration % 3;

				Queue<BSPNode> nextLeafNodes = new Queue<BSPNode>();

				while ( leafNodes.Count > 0 )
				{
					BSPNode node = leafNodes.Dequeue();
					SplitNode(node, channelToOrderBy);

					nextLeafNodes.Enqueue(node.LowChild);
					nextLeafNodes.Enqueue(node.HighChild);
				}

				leafNodes = nextLeafNodes;
			}

			CreatePaletteFromBSPLeafNodes(leafNodes);
		}

		private void CreatePaletteFromBSPLeafNodes(Queue<BSPNode> nodes)
		{
			Debug.Assert(nodes.Count == 256);

			m_Palette = new uint[nodes.Count];
			m_ColourToPaletteIndex = new Dictionary<uint, uint>();
			uint paletteIndex = 0;

			foreach ( BSPNode node in nodes )
			{
				uint paletteColour = GetAverageColour(node.LeafColours);
				m_Palette[paletteIndex] = paletteColour;

				foreach ( ColourBucket bucket in node.LeafColours )
				{
					m_ColourToPaletteIndex[bucket.Colour] = paletteIndex;
				}

				++paletteIndex;
			}
		}

		private static void SplitNode(BSPNode node, uint channelToOrderBy)
		{
			// We shouldn't have started this process if there were not enough colour
			// entries to be divided into 256 nodes.
			Debug.Assert(node.LeafColours.Count > 2);

			node.LeafColours.Sort((bucketX, bucketY) => OrderColourBuckets(bucketX, bucketY, channelToOrderBy));
			uint firstIndexOfHighList = (uint)node.LeafColours.Count / 2;

			node.LowChild = new BSPNode
			{
				LeafColours = node.LeafColours.GetRange(0, (int)firstIndexOfHighList)
			};

			node.HighChild = new BSPNode
			{
				LeafColours = node.LeafColours.GetRange((int)firstIndexOfHighList, node.LeafColours.Count - (int)firstIndexOfHighList)
			};

			// Clear up memory that's no longer required.
			node.LeafColours = null;

			// Record the parameters that were used for the split.
			node.SplitColour = node.HighChild.LeafColours[0].Colour;
			node.SplitPlaneId = channelToOrderBy;
		}

		private uint GetAverageColour(List<ColourBucket> colours)
		{
			uint totalCount = 0;

			foreach ( ColourBucket bucket in colours )
			{
				totalCount += bucket.Count;
			}

			// Declared as floats in order to keep better track of fine increments.
			float avgRed = 0;
			float avgGreen = 0;
			float avgBlue = 0;

			foreach ( ColourBucket bucket in colours )
			{
				float normalisationFactor = (float)bucket.Count / (float)totalCount;

				avgRed += (float)ColourConversion.Col24RedChannel(bucket.Colour) * normalisationFactor;
				avgGreen += (float)ColourConversion.Col24GreenChannel(bucket.Colour) * normalisationFactor;
				avgBlue += (float)ColourConversion.Col24BlueChannel(bucket.Colour) * normalisationFactor;
			}

			return ColourConversion.Col24((byte)avgRed, (byte)avgGreen, (byte)avgBlue);
		}

		private static int OrderColourBuckets(ColourBucket bucketX, ColourBucket bucketY, uint colourChannel)
		{
			int colourX = 0;
			int colourY = 0;

			if ( colourChannel == 0 )
			{
				// Red
				colourX = ColourConversion.Col24RedChannel(bucketX.Colour);
				colourY = ColourConversion.Col24RedChannel(bucketY.Colour);
			}
			else if ( colourChannel == 1 )
			{
				// Green
				colourX = ColourConversion.Col24GreenChannel(bucketX.Colour);
				colourY = ColourConversion.Col24GreenChannel(bucketY.Colour);
			}
			else
			{
				// Blue
				colourX = ColourConversion.Col24BlueChannel(bucketX.Colour);
				colourY = ColourConversion.Col24BlueChannel(bucketY.Colour);
			}

			return colourX - colourY;
		}
	}
}
