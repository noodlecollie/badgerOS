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
		class CommonOptions
		{
			[Option('i', "input", Required = true, HelpText = "Input file to convert.")]
			public string InputFile { get; set; }

			[Option('o', "output", Required = true, HelpText = "Destination file to create.")]
			public string OutputFile { get; set; }

			[Option('f', "format", Required = true, HelpText = "Format of the output file. Run using 'list-formats' for a list of possible values.")]
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

		[Verb("toheader", HelpText = "Outputs the bitmap as a C++ header file containing a constexpr array of data.")]
		class HeaderOutputOptions : CommonOptions
		{
			[Option("namespace", Required = true, HelpText = "Name of outer namespace within which the bitmap file data resides.")]
			public string NamespaceName { get; set; }

			[Option("bitmap-name", Required = true, HelpText = "Name that the bitmap will be known by in code.")]
			public string BitmapName { get; set; }
		}

		[Verb("list-formats", HelpText = "Lists possible values accepted by the --format option.")]
		class ListFormatsOptions
		{
		}

		static int Main(string[] args)
		{
			return Parser.Default.ParseArguments<HeaderOutputOptions, ListFormatsOptions>(args)
				.MapResult(
					(ListFormatsOptions opts) => RunListFormats(opts),
					(HeaderOutputOptions opts) => RunConvertToHeader(opts),
					errs => 1);
		}

		static int RunListFormats(ListFormatsOptions cmdOptions)
		{
			Console.Write("Available formats:\n  ");
			Console.WriteLine(string.Join("\n  ", Enum.GetNames(typeof(FileFormatDefs.FileType))));

			return 0;
		}

		static int RunConvertToHeader(HeaderOutputOptions cmdOptions)
		{
			try
			{
				cmdOptions.ComputeProperties();

				Bitmap bitmap = LoadInputFile(cmdOptions.InputFile);
				ImageLib.Images.MutableImage image = ConvertToImage(bitmap, cmdOptions.OutputType.Value);
				ImageLib.CSource.BitmapCSourceFile outFile = ImageLib.CSource.BitmapCSourceFactory.CreateCSourceFile(image, cmdOptions.OutputType.Value);

				Console.WriteLine($"Writing to output file: {cmdOptions.OutputFile}");

				using ( StreamWriter sw = new StreamWriter(cmdOptions.OutputFile) )
				{
					ImageLib.CSource.BitmapCSourceWriter writer = new ImageLib.CSource.BitmapCSourceWriter
					{
						File = outFile,
						BitmapName = cmdOptions.BitmapName,
						OuterNamespace = cmdOptions.NamespaceName,
						TargetFileType = cmdOptions.OutputType.Value
					};

					writer.Write(sw);
				}

				Console.WriteLine("Done.");
				return 0;
			}
			catch ( Exception ex )
			{
				Console.Error.WriteLine($"An error occurred during execution. {ex.Message}");
			}

			return 1;
		}

		static ImageLib.Images.MutableImage ConvertToImage(Bitmap bitmap, FileFormatDefs.FileType fileType)
		{
			switch ( fileType )
			{
				case FileFormatDefs.FileType.Bitmap65K:
				{
					return ImageConversion.BitmapTo65K(bitmap);
				}

				case FileFormatDefs.FileType.Bitmap65KPalette:
				{
					return ImageConversion.BitmapTo65KPaletted(bitmap);
				}

				case FileFormatDefs.FileType.BitmapMask:
				{
					return ImageConversion.BitmapToMasked(bitmap);
				}

				default:
				{
					throw new NotImplementedException("The provided file type was not recognised,");
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
