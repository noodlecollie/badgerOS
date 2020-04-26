using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using CommandLine;
using ImageLib;

namespace ImageConvert
{
	class Program
	{
		class Options
		{
			[Option('i', "input", Required = true, HelpText = "Input file to convert.")]
			public string InputFile { get; set; }

			[Option('o', "output", Required = true, HelpText = "Destination file to create.")]
			public string OutputFile { get; set; }

			[Option('f', "format", Required = true, HelpText = "Format of the output file.")]
			public string Format { get; set; }

			public FileFormatDefs.FileType? OutputType = null;

			public void ComputeProperties()
			{
				try
				{
					OutputType = (FileFormatDefs.FileType)Enum.Parse(typeof(FileFormatDefs.FileType), Format);
				}
				catch
				{
					throw new ArgumentException($"An error occurred when parsing command line options. File format '{Format}' was not recognised.");
				}
			}
		}

		static int Main(string[] args)
		{
			var result = Parser.Default.ParseArguments<Options>(args);

			if ( result.GetType() != typeof(Parsed<Options>) )
			{
				return 1;
			}

			try
			{
				Options cmdOptions = ((Parsed<Options>)result).Value;
				cmdOptions.ComputeProperties();

				Bitmap bitmap = LoadInputFile(cmdOptions.InputFile);
				byte[] pixels = ConvertBitmapPixels(bitmap, cmdOptions.OutputType.Value);

				ImageLib.CSource.BitmapCSourceFile outFile = new ImageLib.CSource.BitmapCSourceFile
				{
					Width = (ushort)bitmap.Width,
					Height = (ushort)bitmap.Height,
					Data = pixels
				};

				Console.WriteLine($"Writing to output file: {cmdOptions.OutputFile}");

				using ( StreamWriter sw = new StreamWriter(cmdOptions.OutputFile) )
				{
					ImageLib.CSource.BitmapCSourceWriter writer = new ImageLib.CSource.BitmapCSourceWriter
					{
						File = outFile,
						BitmapName = "TEST", // FIXME
						OuterNamespace = "TESTNAMESPACE", // FIXME
						TargetFileType = cmdOptions.OutputType.Value
					};

					writer.Write(sw);
				}

				Console.WriteLine("Done.");
			}
			catch ( Exception ex )
			{
				Console.Error.WriteLine($"An error occurred during execution. {ex.Message}");
				return 1;
			}

			return 0;
		}

		static byte[] ConvertBitmapPixels(Bitmap bitmap, FileFormatDefs.FileType targetType)
		{
			switch ( targetType )
			{
				case FileFormatDefs.FileType.BitmapMask:
				{
					Console.WriteLine("Converting input file to a binary bitmap.");
					return BitmapOperations.ToBinary(bitmap);
				}

				case FileFormatDefs.FileType.Bitmap65K:
				{
					Console.WriteLine("Converting input file to a 65K-colour bitmap.");
					return BitmapOperations.To65KColour(bitmap);
				}

				default:
				{
					throw new ArgumentException($"Bitmap conversion to format '{targetType.ToString("G")}' is not yet supported.");
				}
			}
		}

		static Bitmap LoadInputFile(string path)
		{
			try
			{
				Console.WriteLine($"Loading input file: {path}");
				return new Bitmap(path);
			}
			catch
			{
				throw new FileNotFoundException($"The input file {path} could not be loaded.");
			}
		}
	}
}
