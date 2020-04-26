using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageLib
{
	public static class CSourceUtils
	{
		public static List<string> ToHexArrayString(byte[] data, uint lineWidthInInputBytes = 8)
		{
			List<string> outList = new List<string>();

			if ( data is null )
			{
				return outList;
			}

			for ( uint offset = 0; offset < data.Length; offset += lineWidthInInputBytes )
			{
				uint end = Math.Min(offset + lineWidthInInputBytes, (uint)data.Length);
				StringBuilder builder = new StringBuilder();

				for ( uint index = 0; offset + index < end; ++index )
				{
					if ( index > 0 )
					{
						builder.Append(", ");
					}

					builder.AppendFormat("0x{0:X2}", data[index]);
				}

				string finalString = builder.ToString();

				if ( offset + lineWidthInInputBytes < data.Length )
				{
					// Not finished with the input yet.
					finalString += ",";
				}

				outList.Add(finalString);
			}

			return outList;
		}
	}
}
