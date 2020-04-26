using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageLib.CSource
{
	public class BitmapCSourceFile
	{
		public ushort Width { get; set; }
		public ushort Height { get; set; }

		// Shallow reference only.
		public byte[] Data { get; set; }
		public bool IsValid { get => Width > 0 && Height > 0 && !(Data is null) && Data.Length > 0; }

		// Copies contents of the array.
		public void SetDataClone(byte[] data)
		{
			if ( data is null || data.Length < 1 )
			{
				Data = null;
				return;
			}

			Data = (byte[])data.Clone();
		}
	}
}
